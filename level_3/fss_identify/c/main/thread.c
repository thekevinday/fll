#include "fss_identify.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fss_identify_thread_signal_) && !defined(_di_thread_support_)
  void * fss_identify_thread_signal(void * const main) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    if (main) {
      fss_identify_signal_handler((fss_identify_main_t *) main);
    }

    return 0;
  }
#endif // !defined(_di_fss_identify_thread_signal_) && !defined(_di_thread_support_)

#ifdef __cplusplus
} // extern "C"
#endif
