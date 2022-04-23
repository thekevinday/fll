#include "test-execute.h"

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

    cmocka_unit_test(test__f_execute_status_from_status__fails),
    cmocka_unit_test(test__f_execute_status_from_status__works),

    cmocka_unit_test(test__f_execute_status_to_status__fails),
    cmocka_unit_test(test__f_execute_status_to_status__works),

    #ifndef _di_level_0_parameter_checking_
      // f_execute_status_from_status() doesn't use parameter checking.
      // f_execute_status_to_status() doesn't use parameter checking.
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
