#include "test-limit.h"

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
    cmocka_unit_test(test__f_limit_process__fails),
    cmocka_unit_test(test__f_limit_process__works),

    cmocka_unit_test(test__f_limit_setss_destroy_callback__fails),
    cmocka_unit_test(test__f_limit_setss_delete_callback__fails),

    cmocka_unit_test(test__f_limit_setss_delete_callback__works),
    cmocka_unit_test(test__f_limit_setss_destroy_callback__works),

    cmocka_unit_test(test__f_limit_valuess_destroy_callback__fails),
    cmocka_unit_test(test__f_limit_valuess_delete_callback__fails),

    cmocka_unit_test(test__f_limit_valuess_delete_callback__works),
    cmocka_unit_test(test__f_limit_valuess_destroy_callback__works),

    #ifndef _di_level_0_parameter_checking_
      cmocka_unit_test(test__f_limit_process__parameter_checking),

      // f_limit_setss_destroy_callback() doesn't use parameter checking.
      // f_limit_setss_delete_callback() doesn't use parameter checking.

      // f_limit_valuess_destroy_callback() doesn't use parameter checking.
      // f_limit_valuess_delete_callback() doesn't use parameter checking.
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
