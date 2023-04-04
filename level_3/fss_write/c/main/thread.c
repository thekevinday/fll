#include "fss_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fss_write_thread_signal_) && !defined(_di_thread_support_)
  void * fss_write_thread_signal(void * const main) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    if (main) {
      fss_write_signal_handler((fss_write_main_t *) main);
    }

    return 0;
  }
#endif // !defined(_di_fss_write_thread_signal_) && !defined(_di_thread_support_)

#ifdef __cplusplus
} // extern "C"
#endif
