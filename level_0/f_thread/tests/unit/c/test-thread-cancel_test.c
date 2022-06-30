#include "test-thread.h"
#include "test-thread-cancel_test.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_cancel_test__works(void **state) {

  {
    const f_status_t status = f_thread_cancel_test();

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
