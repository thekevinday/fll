#include "test-random.h"
#include "test-random-read.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_random_read__fails(void **state) {

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

    f_char_t buffer[4] = { 0, 0, 0, 0 };
    f_string_t buffer_ptr = buffer;
    ssize_t total = 0;

    const f_status_t status = f_random_read(0, 4, &buffer_ptr, &total);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for

  for (uint8_t i = 0; i < 6; ++i) {

    will_return(__wrap_getrandom, true);
    will_return(__wrap_getrandom, errnos[i]);
    will_return(__wrap_getrandom, -1);

    f_char_t buffer[4] = { 0, 0, 0, 0 };
    f_string_t buffer_ptr = buffer;

    const f_status_t status = f_random_read(0, 4, &buffer_ptr, 0);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_random_read__works(void **state) {

  const f_number_unsigned_t length = 4;

  {
    char mocked_data[4] = "abcd";
    f_char_t buffer[4] = { 0, 0, 0, 0 };
    f_string_t buffer_ptr = buffer;
    ssize_t total = 0;

    will_return(__wrap_getrandom, false);
    will_return(__wrap_getrandom, (void *) mocked_data);
    will_return(__wrap_getrandom, length);

    const f_status_t status = f_random_read(0, length, &buffer_ptr, &total);

    assert_int_equal(status, F_okay);

    assert_int_equal(buffer[0], mocked_data[0]);
    assert_int_equal(buffer[1], mocked_data[1]);
    assert_int_equal(buffer[2], mocked_data[2]);
    assert_int_equal(buffer[3], mocked_data[3]);

    assert_int_equal(total, length);
  }

  {
    char mocked_data[4] = "abcd";
    f_char_t buffer[4] = { 0, 0, 0, 0 };
    f_string_t buffer_ptr = buffer;

    will_return(__wrap_getrandom, false);
    will_return(__wrap_getrandom, (void *) mocked_data);
    will_return(__wrap_getrandom, length);

    const f_status_t status = f_random_read(0, length, &buffer_ptr, 0);

    assert_int_equal(status, F_okay);

    assert_int_equal(buffer[0], mocked_data[0]);
    assert_int_equal(buffer[1], mocked_data[1]);
    assert_int_equal(buffer[2], mocked_data[2]);
    assert_int_equal(buffer[3], mocked_data[3]);
  }
}

void test__f_random_read__parameter_checking(void **state) {

  {
    const f_status_t status = f_random_read(0, 0, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
