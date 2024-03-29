#include "../controller.h"
#include "../common/private-common.h"
#include "../controller/private-controller.h"
#include "../lock/private-lock.h"
#include "../lock/private-lock_print.h"
#include "../process/private-process.h"
#include "../rule/private-rule.h"
#include "../thread/private-thread.h"
#include "../thread/private-thread_process.h"

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
  f_status_t controller_process_prepare(const controller_global_t global, const bool is_normal, const uint8_t action, const f_string_static_t alias, f_array_length_t *id) {

    f_status_t status = F_none;

    if (controller_process_find(action, alias, global.thread->processs, id) == F_false) {
      f_thread_unlock(&global.thread->lock.process);

      status = controller_lock_write(is_normal, global.thread, &global.thread->lock.process);

      if (F_status_is_error(status)) {
        controller_lock_print_error_critical(global.main->error, F_status_set_fine(status), F_false, global.thread);
      }
      else {
        status = controller_processs_increase(&global.thread->processs);
      }

      if (F_status_is_error_not(status) && global.thread->processs.array[global.thread->processs.used]) {

        controller_process_t *process = global.thread->processs.array[global.thread->processs.used];

        status = controller_lock_write(is_normal, global.thread, &process->lock);

        if (F_status_is_error(status)) {
          controller_lock_print_error_critical(global.main->error, F_status_set_fine(status), F_false, global.thread);
        }
        else {
          process->action = action;
          process->rule.alias.used = 0;

          status = f_string_dynamic_append(alias, &process->rule.alias);

          if (F_status_is_error_not(status)) {
            process->id = global.thread->processs.used++;
            status = F_none;

            if (id) {
              *id = process->id;
            }
          }

          f_thread_unlock(&process->lock);
        }
      }

      f_thread_unlock(&global.thread->lock.process);

      // The read lock must be restored on return.
      const f_status_t status_lock = controller_lock_read(is_normal, global.thread, &global.thread->lock.process);

      if (F_status_is_error(status_lock)) {
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
  f_status_t controller_process_prepare_process_type(const controller_global_t global, const uint8_t type, const uint8_t action, const f_string_static_t alias, f_array_length_t *id) {

    return controller_process_prepare(global, type != controller_process_type_exit_e, action, alias, id);
  }
#endif // _di_controller_process_prepare_process_type_

#ifndef _di_controller_process_wait_
  f_status_t controller_process_wait(const controller_global_t global, controller_process_t * const process) {

    if (!controller_thread_is_enabled_process(process, global.thread)) {
      return F_status_set_error(F_interrupt);
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
        return F_status_set_error(F_interrupt);
      }

      if (F_status_is_error(status)) break;

      status_lock = controller_lock_read_process(process, global.thread, &process->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(global.main->error, F_status_set_fine(status_lock), F_true, global.thread);

        break;
      }

      if (!controller_rule_status_is_available(process->action, process->rule) && !(process->state == controller_process_state_active_e || process->state == controller_process_state_busy_e)) {
        f_thread_unlock(&process->lock);

        return F_none;
      }

      if (status != F_time) {

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
