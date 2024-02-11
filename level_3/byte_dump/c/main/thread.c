#include "byte_dump.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_byte_dump_thread_signal_) && !defined(_di_thread_support_)
  void * byte_dump_thread_signal(void * const main) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    if (main) {
      byte_dump_signal_handler((byte_dump_main_t *) main);
    }

    return 0;
  }
#endif // !defined(_di_byte_dump_thread_signal_) && !defined(_di_thread_support_)

#ifdef __cplusplus
} // extern "C"
#endif
