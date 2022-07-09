#include "test-environment.h"

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
    cmocka_unit_test(test__f_environment_clear__fails),
    cmocka_unit_test(test__f_environment_clear__works),

    cmocka_unit_test(test__f_environment_exists__fails),
    cmocka_unit_test(test__f_environment_exists__returns_data_not),
    cmocka_unit_test(test__f_environment_exists__works),

    cmocka_unit_test(test__f_environment_get__fails),
    cmocka_unit_test(test__f_environment_get__returns_data_not),
    cmocka_unit_test(test__f_environment_get__works),

    cmocka_unit_test(test__f_environment_get_all__works),

    cmocka_unit_test(test__f_environment_secure_is__fails),
    cmocka_unit_test(test__f_environment_secure_is__works),

    cmocka_unit_test(test__f_environment_set__fails),
    cmocka_unit_test(test__f_environment_set__returns_data_not),
    cmocka_unit_test(test__f_environment_set__works),

    cmocka_unit_test(test__f_environment_unset__fails),
    cmocka_unit_test(test__f_environment_unset__returns_data_not),
    cmocka_unit_test(test__f_environment_unset__works),

    #ifndef _di_level_0_parameter_checking_
      // f_environment_clear() doesn't use parameter checking.
      // f_environment_exists() doesn't use parameter checking.
      cmocka_unit_test(test__f_environment_get__parameter_checking),
      cmocka_unit_test(test__f_environment_get_all__parameter_checking),
      // f_environment_secure_is() doesn't use parameter checking.
      // f_environment_set() doesn't use parameter checking.
      // f_environment_unset() doesn't use parameter checking.
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
