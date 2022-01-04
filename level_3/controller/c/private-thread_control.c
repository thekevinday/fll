#include "controller.h"
#include "private-common.h"
#include "private-control.h"
#include "private-controller_print.h"
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
    f_socket_t * const server = &global->setting->control_socket;
    controller_packet_t packet = controller_packet_t_initialize;

    controller_control_configure_server(global, server);

    do {
      status = controller_control_accept(global, server, &packet);
    } while (F_status_is_fine(status) && status != F_child && global->thread->enabled == controller_thread_enabled_e);

    controller_packet_delete_simple(&packet);

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
