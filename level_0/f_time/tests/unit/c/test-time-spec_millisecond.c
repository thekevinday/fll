#include "test-time.h"
#include "test-time-spec_millisecond.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_time_spec_millisecond__number_overflow(void **state) {

  f_number_unsigned_t second = 0;

  // If is signed, then...
  if (((time_t) (-1)) < 0) {
    second = (((f_number_unsigned_t) ((time_t) -1)) >> 1);
  }
  else {
    second = (f_number_unsigned_t) ((time_t) (-1));
  }

  struct timespec time = { 0 };

  {
    const f_status_t status = f_time_spec_millisecond(second, 1000, &time);

    assert_int_equal(status, F_status_set_error(F_number_overflow));
  }

  {
    const f_status_t status = f_time_spec_millisecond(second, 1000, &time);

    assert_int_equal(status, F_status_set_error(F_number_overflow));
  }
}

void test__f_time_spec_millisecond__number_underflow(void **state) {

  struct timespec time = { .tv_sec = -1, .tv_nsec = -1 };

  // If this system has uses unsigned, then this test is not needed.
  if (time.tv_sec >= 0 && time.tv_nsec >= 0) return;

  if (time.tv_sec < 0) {
    const f_status_t status = f_time_spec_millisecond(-1, 0, &time);

    assert_int_equal(status, F_status_set_error(F_number_underflow));
  }

  if (time.tv_sec < 0) {
    const f_status_t status = f_time_spec_millisecond(-1, 1, &time);

    assert_int_equal(status, F_status_set_error(F_number_underflow));
  }

  time.tv_nsec = -1;

  if (time.tv_nsec < 0) {
    const f_status_t status = f_time_spec_millisecond(0, -1, &time);

    assert_int_equal(status, F_status_set_error(F_number_underflow));
  }

  if (time.tv_nsec < 0) {
    const f_status_t status = f_time_spec_millisecond(1, -1, &time);

    assert_int_equal(status, F_status_set_error(F_number_underflow));
  }
}

void test__f_time_spec_millisecond__parameter_checking(void **state) {

  {
    const f_status_t status = f_time_spec_millisecond(0, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_time_spec_millisecond__works(void **state) {

  struct timespec time = { 0 };

  {
    const f_number_unsigned_t seconds[] = {
      1000,
      1000,
      0,
      0,
    };

    const f_number_unsigned_t milliseconds[] = {
      100,
      0,
      100,
      0,
    };

    for (uint8_t i = 0; i < 4; ++i) {

      const f_status_t status = f_time_spec_millisecond(seconds[i], milliseconds[i], &time);

      assert_int_equal(status, F_none);
      assert_int_equal(time.tv_sec, seconds[i]);
      assert_int_equal(time.tv_nsec, milliseconds[i] * 1000);
    } // for
  }

  {
    const f_number_unsigned_t seconds[] = {
      1,
      2,
    };

    const f_number_unsigned_t milliseconds[] = {
      1000,
      1001,
    };

    for (uint8_t i = 0; i < 2; ++i) {

      const f_status_t status = f_time_spec_millisecond(seconds[i], milliseconds[i], &time);

      assert_int_equal(status, F_none);
      assert_int_equal(time.tv_sec, seconds[i] + 1);
      assert_int_equal(time.tv_nsec, (milliseconds[i] - 1000) * 1000);
    } // for
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
