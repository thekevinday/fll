#include "fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fake_thread_signal_) && !defined(_di_thread_support_)
  void * fake_thread_signal(void * const main) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    if (main) {
      fake_signal_handler((fake_main_t *) main);
    }

    return 0;
  }
#endif // !defined(_di_fake_thread_signal_) && !defined(_di_thread_support_)

#ifdef __cplusplus
} // extern "C"
#endif
