#include "controller.h"
#include "private-common.h"
#include "private-controller.h"
#include "private-lock.h"
#include "private-lock_print.h"
#include "private-process.h"
#include "private-rule.h"
#include "private-thread.h"
#include "private-thread_process.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_process_find_
  f_status_t controller_process_find(const f_array_length_t action, const f_string_static_t alias, const controller_processs_t processs, f_array_length_t *at) {

    if (!alias.used) return F_none;
    if (!processs.used) return F_false;

    for (f_array_length_t i = 0; i < processs.used; ++i) {

      if (processs.array[i] && processs.array[i]->action == action && fl_string_dynamic_compare(alias, processs.array[i]->rule.alias) == F_equal_to) {
        if (at) *at = i;

        return F_true;
      }
    } // for

    return F_false;
  }
#endif // _di_controller_process_find_

#ifndef _di_controller_process_prepare_
  f_status_t controller_process_prepare(const bool is_normal, const uint8_t action, const f_string_static_t alias, const controller_global_t global, f_array_length_t *id) {

    f_status_t status = F_none;

    if (status == F_signal || F_status_is_error(status)) {
      controller_lock_print_error_critical(global.main->error, F_status_set_fine(status), F_true, global.thread);

      return status;
    }

    if (controller_process_find(action, alias, global.thread->processs, id) == F_false) {
      f_thread_unlock(&global.thread->lock.process);

      status = controller_lock_write(is_normal, global.thread, &global.thread->lock.process);

      if (status == F_signal || F_status_is_error(status)) {
        controller_lock_print_error_critical(global.main->error, F_status_set_fine(status), F_false, global.thread);

        const f_status_t status_lock = controller_lock_read(is_normal, global.thread, &global.thread->lock.process);

        if (status_lock == F_signal || F_status_is_error(status_lock)) {
          return F_status_set_error(F_lock);
        }

        return status;
      }

      status = controller_processs_increase(&global.thread->processs);

      if (F_status_is_error_not(status) && global.thread->processs.array[global.thread->processs.used]) {

        controller_process_t *process = global.thread->processs.array[global.thread->processs.used];

        status = controller_lock_write(is_normal, global.thread, &process->lock);

        if (status == F_signal || F_status_is_error(status)) {
          controller_lock_print_error_critical(global.main->error, F_status_set_fine(status), F_false, global.thread);

          f_thread_unlock(&global.thread->lock.process);

          const f_status_t status_lock = controller_lock_read(is_normal, global.thread, &global.thread->lock.process);

          if (status_lock == F_signal || F_status_is_error(status_lock)) {
            return F_status_set_error(F_lock);
          }

          return status;
        }

        process->action = action;
        process->rule.alias.used = 0;

        status = f_string_dynamic_append(alias, &process->rule.alias);

        if (F_status_is_error_not(status)) {
          status = f_string_dynamic_terminate_after(&process->rule.alias);

          if (F_status_is_error_not(status)) {
            process->id = global.thread->processs.used++;
            status = F_none;

            if (id) {
              *id = process->id;
            }
          }
        }

        f_thread_unlock(&process->lock);
      }

      f_thread_unlock(&global.thread->lock.process);

      const f_status_t status_lock = controller_lock_read(is_normal, global.thread, &global.thread->lock.process);

      if (status_lock == F_signal || F_status_is_error(status_lock)) {
        return F_status_set_error(F_lock);
      }
    }
    else {
      status = F_found;
    }

    return status;
  }
#endif // _di_controller_process_prepare_

#ifndef _di_controller_process_prepare_process_type_
  f_status_t controller_process_prepare_process_type(const uint8_t type, const uint8_t action, const f_string_static_t alias, const controller_global_t global, f_array_length_t *id) {

    return controller_process_prepare(type != controller_process_type_exit, action, alias, global, id);
  }
#endif // _di_controller_process_prepare_process_type_

#ifndef _di_controller_process_wait_
  f_status_t controller_process_wait(const controller_global_t global, controller_process_t *process) {

    if (!controller_thread_is_enabled_process(process, global.thread)) {
      return F_signal;
    }

    struct timespec time;

    f_status_t status = F_none;
    f_status_t status_lock = F_none;

    uint8_t count = 0;

    do {
      f_thread_mutex_lock(&process->wait_lock);

      if (count < controller_thread_wait_timeout_1_before_d) {
        controller_time(controller_thread_wait_timeout_1_seconds_d, controller_thread_wait_timeout_1_nanoseconds_d, &time);
      }
      else if (count < controller_thread_wait_timeout_2_before_d) {
        controller_time(controller_thread_wait_timeout_2_seconds_d, controller_thread_wait_timeout_2_nanoseconds_d, &time);
      }
      else if (count < controller_thread_wait_timeout_3_before_d) {
        controller_time(controller_thread_wait_timeout_3_seconds_d, controller_thread_wait_timeout_3_nanoseconds_d, &time);
      }
      else {
        controller_time(controller_thread_wait_timeout_4_seconds_d, controller_thread_wait_timeout_4_nanoseconds_d, &time);
      }

      status = f_thread_condition_wait_timed(&time, &process->wait, &process->wait_lock);

      f_thread_mutex_unlock(&process->wait_lock);

      if (!controller_thread_is_enabled_process(process, global.thread)) {
        return F_signal;
      }

      if (F_status_is_error(status)) {
        break;
      }

      status_lock = controller_lock_read_process(process, global.thread, &process->lock);

      if (status_lock == F_signal || F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(global.main->error, F_status_set_fine(status_lock), F_true, global.thread);

        break;
      }

      if (!controller_rule_status_is_available(process->action, process->rule) && !(process->state == controller_process_state_active || process->state == controller_process_state_busy)) {
        f_thread_unlock(&process->lock);

        return F_none;
      }
      else if (status != F_time) {

        // move up the wait timer after a trigger was received.
        if (count < controller_thread_wait_timeout_2_before_d) {
          count = 0;
        }
        else if (count < controller_thread_wait_timeout_3_before_d) {
          count = controller_thread_wait_timeout_1_before_d;
        }
        else {
          count = controller_thread_wait_timeout_2_before_d;
        }
      }

      f_thread_unlock(&process->lock);

      if (count < controller_thread_wait_timeout_3_before_d) {
        ++count;
      }

    } while (status == F_time && controller_thread_is_enabled_process(process, global.thread));

    return status;
  }
#endif // _di_controller_process_wait_

#ifdef __cplusplus
} // extern "C"
#endif
