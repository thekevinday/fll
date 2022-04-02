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
