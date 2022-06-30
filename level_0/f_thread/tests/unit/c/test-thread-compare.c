#include "test-thread.h"
#include "test-thread-compare.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_compare__works(void **state) {

  f_thread_id_t id1 = 0;
  f_thread_id_t id2 = 0;

  {
    will_return(__wrap_pthread_equal, false);

    const f_status_t status = f_thread_compare(id1, id2);

    assert_int_equal(status, F_equal_to_not);
  }

  {
    will_return(__wrap_pthread_equal, true);

    const f_status_t status = f_thread_compare(id1, id2);

    assert_int_equal(status, F_equal_to);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
