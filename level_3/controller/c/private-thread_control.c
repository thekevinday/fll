#include "controller.h"
#include "private-common.h"
#include "private-thread.h"
#include "private-thread_control.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_thread_control_
  void * controller_thread_control(void *arguments) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_global_t *global = (controller_global_t *) arguments;

    if (global->thread->enabled != controller_thread_enabled_e) return 0;

    return 0;
  }
#endif // _di_controller_thread_control_

#ifdef __cplusplus
} // extern "C"
#endif
