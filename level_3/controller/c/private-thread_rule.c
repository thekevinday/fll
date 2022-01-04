#include "controller.h"
#include "private-common.h"
#include "private-thread.h"
#include "private-thread_rule.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_thread_rule_
  void * controller_thread_rule(void * const arguments) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    const controller_global_t *global = (controller_global_t *) arguments;

    if (!controller_thread_is_enabled(F_true, global->thread)) return 0;

    return 0;
  }
#endif // _di_controller_thread_rule_

#ifdef __cplusplus
} // extern "C"
#endif
