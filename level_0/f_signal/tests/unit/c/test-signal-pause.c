#include "test-signal.h"
#include "test-signal-pause.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_signal_pause__works(void **state) {

  {
    const f_status_t status = f_signal_pause();

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
