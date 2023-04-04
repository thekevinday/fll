#include "status_code.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_status_code_thread_signal_) && !defined(_di_thread_support_)
  void * status_code_thread_signal(void * const main) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    if (main) {
      status_code_signal_handler((status_code_main_t *) main);
    }

    return 0;
  }
#endif // !defined(_di_status_code_thread_signal_) && !defined(_di_thread_support_)

#ifdef __cplusplus
} // extern "C"
#endif
