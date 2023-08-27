#include "test-path.h"

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
    cmocka_unit_test(test__f_path_change__fails),
    cmocka_unit_test(test__f_path_change__works),

    cmocka_unit_test(test__f_path_change_at__fails),
    cmocka_unit_test(test__f_path_change_at__works),

    cmocka_unit_test(test__f_path_directory_cleanup__works),

    cmocka_unit_test(test__f_path_is__returns_false),
    cmocka_unit_test(test__f_path_is__returns_data_not),
    cmocka_unit_test(test__f_path_is__returns_true),

    cmocka_unit_test(test__f_path_is_absolute__returns_false),
    cmocka_unit_test(test__f_path_is_absolute__returns_data_not),
    cmocka_unit_test(test__f_path_is_absolute__returns_true),

    cmocka_unit_test(test__f_path_is_relative__returns_false),
    cmocka_unit_test(test__f_path_is_relative__returns_data_not),
    cmocka_unit_test(test__f_path_is_relative__returns_true),

    cmocka_unit_test(test__f_path_is_relative_current__returns_false),
    cmocka_unit_test(test__f_path_is_relative_current__returns_data_not),
    cmocka_unit_test(test__f_path_is_relative_current__returns_true),

    cmocka_unit_test(test__f_path_real__fails),
    cmocka_unit_test(test__f_path_real__works),

    #ifndef _di_level_0_parameter_checking_
      // f_path_change() doesn't use parameter checking.
      // f_path_change_at() doesn't use parameter checking.
      cmocka_unit_test(test__f_path_current__parameter_checking),
      cmocka_unit_test(test__f_path_directory_cleanup__parameter_checking),
      // f_path_is() doesn't use parameter checking.
      // f_path_is_absolute() doesn't use parameter checking.
      // f_path_is_relative() doesn't use parameter checking.
      // f_path_is_relative_current() doesn't use parameter checking.
      cmocka_unit_test(test__f_path_real__parameter_checking),
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
