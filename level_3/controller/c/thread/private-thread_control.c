#include "../controller.h"
#include "../common/private-common.h"
#include "../control/private-control.h"
#include "../controller/private-controller.h"
#include "../controller/private-controller_print.h"
#include "private-thread.h"
#include "private-thread_control.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_thread_control_
  void * controller_thread_control(void * const arguments) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    const controller_global_t *global = (controller_global_t *) arguments;

    if (global->thread->enabled != controller_thread_enabled_e) return 0;

    f_status_t status = F_none;
    struct timespec time;
    controller_control_t *control = &global->setting->control;

    do {

      // Remove any overly large buffers.
      if (control->cache_1.size > controller_control_default_socket_cache_d) {
        status = f_string_dynamic_resize(0, &control->cache_1);
      }

      if (F_status_is_error_not(status) && control->cache_2.size > controller_control_default_socket_buffer_d) {
        status = f_string_dynamic_resize(0, &control->cache_2);
      }

      if (F_status_is_error_not(status) && control->cache_3.size > controller_control_default_socket_buffer_d) {
        status = f_string_dynamic_resize(0, &control->cache_3);
      }

      if (F_status_is_error_not(status) && control->input.size > controller_control_default_socket_buffer_d) {
        status = f_string_dynamic_resize(0, &control->input);
      }

      if (F_status_is_error_not(status) && control->output.size > controller_control_default_socket_buffer_d) {
        status = f_string_dynamic_resize(0, &control->output);
      }

      if (F_status_is_error(status)) {
        controller_print_error(global->thread, global->main->error, F_status_set_fine(status), "f_string_dynamic_resize", F_true);

        status = F_none;
      }

      status = f_socket_listen(&control->server, controller_control_default_socket_backlog_d);

      if (F_status_is_error(status)) {
        controller_print_error(global->thread, global->main->error, F_status_set_fine(status), "f_socket_listen", F_true);

        /*controller_time(controller_thread_wait_timeout_2_seconds_d, controller_thread_wait_timeout_2_nanoseconds_d, &time);

        controller_time_sleep_nanoseconds(global->main, global->setting, time);
        */

        status = F_none;

        continue;
      }

      status = controller_control_accept(global, control);
      if (status == F_child) break;

      if (F_status_is_error(status)) {
        controller_print_error(global->thread, global->main->error, F_status_set_fine(status), "controller_control_accept", F_true);
      }

      status = F_none;

    } while (global->thread->enabled == controller_thread_enabled_e);

    if (status == F_child) {

      // A forked child process should deallocate memory on exit.
      // It seems that this function doesn't return to the calling thread for a forked child process, even with the "return 0;" below.
      // Deallocate as much as possible.
      controller_thread_delete_simple(global->thread);
      controller_setting_delete_simple(global->setting);
      controller_main_delete(global->main);
    }

    return 0;
  }
#endif // _di_controller_thread_control_

#ifdef __cplusplus
} // extern "C"
#endif
