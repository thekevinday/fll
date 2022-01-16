#include "../controller/controller.h"
#include "../common/private-common.h"
#include "../control/private-control.h"
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
    controller_control_t control = macro_controller_control_t_initialize(&global->setting->control_socket, 0);

    do {

      // Shrink any overly large buffers.
      if (control.cache_1.size > controller_control_default_socket_cache_d) {
        status = f_string_dynamic_resize(controller_control_default_socket_cache_d, &control.cache_1);
      }

      if (F_status_is_error_not(status) && control.cache_2.size > controller_control_default_socket_buffer_d) {
        status = f_string_dynamic_resize(controller_control_default_socket_buffer_d, &control.cache_2);
      }

      if (F_status_is_error_not(status) && control.cache_3.size > controller_control_default_socket_buffer_d) {
        status = f_string_dynamic_resize(controller_control_default_socket_buffer_d, &control.cache_3);
      }

      if (F_status_is_error_not(status) && control.input.size > controller_control_default_socket_buffer_d) {
        status = f_string_dynamic_resize(controller_control_default_socket_buffer_d, &control.input);
      }

      if (F_status_is_error_not(status) && control.output.size > controller_control_default_socket_buffer_d) {
        status = f_string_dynamic_resize(controller_control_default_socket_buffer_d, &control.output);
      }

      if (F_status_is_error(status)) {
        controller_print_error(global->thread, global->main->error, F_status_set_fine(status), "f_string_dynamic_resize", F_true);
      }

      status = controller_control_accept(global, &control);

      if (F_status_is_error(status)) {
        controller_print_error(global->thread, global->main->error, F_status_set_fine(status), "controller_control_accept", F_true);
      }

    } while (F_status_is_fine(status) && status != F_child && global->thread->enabled == controller_thread_enabled_e);

    controller_control_delete_simple(&control);

    return 0;
  }
#endif // _di_controller_thread_control_

#ifndef _di_controller_thread_control_listen_
  void * controller_thread_control_listen(void * const arguments) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_ASYNCHRONOUS, 0);

    const controller_global_t *global = (controller_global_t *) arguments;

    if (global->thread->enabled != controller_thread_enabled_e) return 0;

    if (global->setting->interruptible) {
      f_signal_mask(SIG_UNBLOCK, &global->main->signal.set, 0);
    }

    f_socket_t * const server = &global->setting->control_socket;

    const f_status_t status = f_socket_listen(server, controller_control_default_socket_backlog_d);

    if (F_status_is_error(status)) {
      controller_print_error(global->thread, global->main->error, F_status_set_fine(status), "f_socket_listen", F_true);
    }

    return 0;
  }
#endif // _di_controller_thread_control_listen_

#ifdef __cplusplus
} // extern "C"
#endif
