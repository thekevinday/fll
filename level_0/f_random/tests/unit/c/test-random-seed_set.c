#include "test-random.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_random_seed_set__works(void **state) {

  mock_unwrap = 0;

  {
    const f_status_t status = f_random_seed_set(1);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
