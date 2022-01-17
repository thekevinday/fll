#include "test-color.h"

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

    // f_color_load_context() only returns failures by other functions that have their own tests.
    cmocka_unit_test(test__f_color_load_context__works),

    // f_color_save_1() only returns failures by other functions that have their own tests.
    cmocka_unit_test(test__f_color_save_1_works),

    // f_color_save_2() only returns failures by other functions that have their own tests.
    cmocka_unit_test(test__f_color_save_2_works),

    // f_color_save_3() only returns failures by other functions that have their own tests.
    cmocka_unit_test(test__f_color_save_3_works),

    // f_color_save_4() only returns failures by other functions that have their own tests.
    cmocka_unit_test(test__f_color_save_4_works),

    // f_color_save_5() only returns failures by other functions that have their own tests.
    cmocka_unit_test(test__f_color_save_5_works),

    #ifndef _di_level_0_parameter_checking_
      cmocka_unit_test(test__f_color_load_context__parameter_checking),
      cmocka_unit_test(test__f_color_save_1_parameter_checking),
      cmocka_unit_test(test__f_color_save_2_parameter_checking),
      cmocka_unit_test(test__f_color_save_3_parameter_checking),
      cmocka_unit_test(test__f_color_save_4_parameter_checking),
      cmocka_unit_test(test__f_color_save_5_parameter_checking),
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
