#include "../controller.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_pids_increase_
  f_status_t controller_pids_increase(controller_pids_t * const pids) {

    if (pids->used + 1 > pids->size) {
      f_number_unsigned_t length = pids->used + controller_common_allocation_small_d;

      if (length > F_number_t_size_unsigned_d) {
        if (pids->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        length = F_number_t_size_unsigned_d;
      }

      return controller_pids_resize(length, pids);
    }

    return F_data_not;
  }
#endif // _di_controller_pids_increase_

#ifndef _di_controller_pids_resize_
  f_status_t controller_pids_resize(const f_number_unsigned_t length, controller_pids_t * const pids) {

    const f_status_t status = f_memory_resize(pids->size, length, sizeof(controller_rule_t), (void **) & pids->array);
    if (F_status_is_error(status)) return status;

    pids->size = length;

    if (pids->used > pids->size) {
      pids->used = length;
    }

    return F_okay;
  }
#endif // _di_controller_pids_resize_

#ifndef _di_controller_process_delete_simple_
  void controller_process_delete_simple(controller_process_t * const process) {

    if (process->id_thread) {
      f_thread_signal_write(process->id_thread, F_signal_kill);
      f_thread_join(process->id_thread, 0);

      process->id_thread = 0;
    }

    f_thread_condition_delete(&process->wait);

    controller_lock_delete_rw(&process->lock);
    controller_lock_delete_rw(&process->active);
    controller_lock_delete_mutex(&process->wait_lock);

    controller_cache_delete_simple(&process->cache);
    controller_pids_resize(0, &process->childs);
    controller_rule_delete_simple(&process->rule);

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &process->path_pids.array, &process->path_pids.used, &process->path_pids.size, &f_string_dynamics_delete_callback);

    f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &process->stack.array, &process->stack.used, &process->stack.size);
  }
#endif // _di_controller_process_delete_simple_

#ifndef _di_controller_processs_delete_simple_
  void controller_processs_delete_simple(controller_processs_t * const processs) {

    controller_processs_resize(0, processs);
  }
#endif // _di_controller_processs_delete_simple_

#ifndef _di_controller_processs_increase_
  f_status_t controller_processs_increase(controller_processs_t * const processs) {

    if (processs->used + 1 > processs->size) {
      f_number_unsigned_t length = processs->used + controller_common_allocation_small_d;

      if (length > F_number_t_size_unsigned_d) {
        if (processs->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        length = F_number_t_size_unsigned_d;
      }

      return controller_processs_resize(length, processs);
    }

    return F_data_not;
  }
#endif // _di_controller_processs_increase_

#ifndef _di_controller_processs_resize_
  f_status_t controller_processs_resize(const f_number_unsigned_t length, controller_processs_t * const processs) {

    f_status_t status = F_okay;

    for (f_number_unsigned_t i = length; i < processs->size; ++i) {

      if (processs->array[i]) {
        controller_process_delete_simple(processs->array[i]);

        f_memory_delete(1, sizeof(f_number_unsigned_t *), (void **) & processs->array[i]);
      }
    } // for

    status = f_memory_resize(processs->size, length, sizeof(controller_process_t), (void **) & processs->array);
    if (F_status_is_error(status)) return status;

    if (length) {
      controller_process_t *process = 0;

      // The lock must be initialized, but only once, so initialize immediately upon allocation.
      for (; processs->size < length; ++processs->size) {

        status = f_memory_new(1, sizeof(controller_process_t), (void **) &processs->array[processs->size]);

        if (F_status_is_error_not(status)) {
          process = processs->array[processs->size];

          status = f_thread_lock_create(0, &process->lock);
        }

        if (F_status_is_error_not(status)) {
          status = f_thread_lock_create(0, &process->active);
        }

        if (F_status_is_error_not(status)) {
          status = f_thread_condition_create(0, &process->wait);
        }

        if (F_status_is_error_not(status)) {
          status = f_thread_mutex_create(0, &process->wait_lock);
        }

        if (F_status_is_error(status)) {
          processs->size = length;

          return status;
        }

        for (f_number_unsigned_t i = 0; i < controller_rule_action_type__enum_size_e; ++i) {
          process->rule.status[i] = F_known_not;
        } // for
      } // for

      processs->size = length;

      if (processs->used > processs->size) {
        processs->used = length;
      }
    }

    return F_okay;
  }
#endif // _di_controller_processs_resize_

#ifdef __cplusplus
} // extern "C"
#endif
