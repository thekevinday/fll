#include "test-random.h"
#include "test-random-seed.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_random_seed__fails(void **state) {

  int errnos[] = {
    EAGAIN,
    EFAULT,
    EINTR,
    EINVAL,
    ENOSYS,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_again,
    F_buffer,
    F_interrupt,
    F_parameter,
    F_support_not,
    F_failure,
  };

  for (uint8_t i = 0; i < 6; ++i) {

    will_return(__wrap_getrandom, true);
    will_return(__wrap_getrandom, errnos[i]);
    will_return(__wrap_getrandom, -1);

    const f_status_t status = f_random_seed(0);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_random_seed__works(void **state) {

  const f_number_unsigned_t length = 4;

  {
    char mocked_data[4] = "abcd";

    will_return(__wrap_getrandom, false);
    will_return(__wrap_getrandom, (void *) mocked_data);
    will_return(__wrap_getrandom, length);

    const f_status_t status = f_random_seed(0);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
