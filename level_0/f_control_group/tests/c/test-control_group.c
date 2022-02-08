#include "test-control_group.h"

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

    // f_control_group_copy() only returns memory failures.
    cmocka_unit_test(test__f_control_group_copy__works),

    #ifndef _di_level_0_parameter_checking_
      cmocka_unit_test(test__f_control_group_copy__parameter_checking),
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif