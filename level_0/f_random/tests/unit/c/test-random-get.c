#include "test-random.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_random_get__works(void **state) {

  mock_unwrap = 0;

  const long mocked_data = 1234;

  {
    long data = 0;

    will_return(__wrap_random, mocked_data);

    const f_status_t status = f_random_get(&data);

    assert_int_equal(status, F_okay);

    assert_int_equal(data, mocked_data);
  }
}

void test__f_random_get__parameter_checking(void **state) {

  mock_unwrap = 0;

  {
    const f_status_t status = f_random_get(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
