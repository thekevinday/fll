#include "test-console.h"

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

    // f_console_environment_process() only returns memory failures.
    cmocka_unit_test(test__f_console_environment_process__data_not),
    cmocka_unit_test(test__f_console_environment_process__works),

    // f_console_identify() doesn't return failure.
    cmocka_unit_test(test__f_console_identify__works),

    cmocka_unit_test(test__f_console_parameter_prioritize_left__fails),
    cmocka_unit_test(test__f_console_parameter_prioritize_left__works),

    cmocka_unit_test(test__f_console_parameter_prioritize_right__fails),
    cmocka_unit_test(test__f_console_parameter_prioritize_right__works),

    // f_console_parameter_process() only returns memory failures.
    cmocka_unit_test(test__f_console_parameter_process__no_arguments_no_program),
    cmocka_unit_test(test__f_console_parameter_process__no_arguments),
    cmocka_unit_test(test__f_console_parameter_process__null_arguments),
    cmocka_unit_test(test__f_console_parameter_process__only_remaining),
    cmocka_unit_test(test__f_console_parameter_process__works),

    cmocka_unit_test(test__f_console_parameters_delete__frees_memory),

    cmocka_unit_test(test__f_console_parameters_destroy__frees_memory),

    #ifndef _di_level_0_parameter_checking_
      cmocka_unit_test(test__f_console_environment_process__parameter_checking),
      cmocka_unit_test(test__f_console_identify__parameter_checking),
      cmocka_unit_test(test__f_console_parameter_prioritize_left__parameter_checking),
      cmocka_unit_test(test__f_console_parameter_prioritize_right__parameter_checking),
      cmocka_unit_test(test__f_console_parameter_process__parameter_checking),
      cmocka_unit_test(test__f_console_parameters_delete__parameter_checking),
      cmocka_unit_test(test__f_console_parameters_destroy__parameter_checking),
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
