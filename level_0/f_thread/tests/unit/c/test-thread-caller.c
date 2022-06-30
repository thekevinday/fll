#include "test-thread.h"
#include "test-thread-caller.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_caller__works(void **state) {

  {
    will_return(__wrap_pthread_self, 1);

    const f_thread_id_t id = f_thread_caller();

    assert_int_equal(id, 1);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
