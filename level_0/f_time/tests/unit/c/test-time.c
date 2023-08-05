#include "test-time.h"

#ifdef __cplusplus
extern "C" {
#endif

int setup(void **state) {

  return 0;
}

int setdown(void **state) {

  errno = 0;

  return 0;
}

int main(void) {

  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test__f_time_spec_millisecond__number_overflow),
    cmocka_unit_test(test__f_time_spec_millisecond__number_underflow),
    cmocka_unit_test(test__f_time_spec_millisecond__works),

    cmocka_unit_test(test__f_time_spec_nanosecond__number_overflow),
    cmocka_unit_test(test__f_time_spec_nanosecond__number_underflow),
    cmocka_unit_test(test__f_time_spec_nanosecond__works),

    #ifndef _di_level_0_parameter_checking_
      cmocka_unit_test(test__f_time_spec_millisecond__parameter_checking),
      cmocka_unit_test(test__f_time_spec_nanosecond__parameter_checking),
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
