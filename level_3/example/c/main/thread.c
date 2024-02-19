#include "example.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_example_thread_signal_) && !defined(_di_thread_support_)
  void * example_thread_signal(void * const main) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    if (main) {
      example_signal_handler((example_main_t *) main);
    }

    return 0;
  }
#endif // !defined(_di_example_thread_signal_) && !defined(_di_thread_support_)

#ifdef __cplusplus
} // extern "C"
#endif
