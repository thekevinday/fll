#include "test-pipe.h"

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
    cmocka_unit_test(test__f_pipe_error_exists__fails),
    cmocka_unit_test(test__f_pipe_error_exists__returns_false),
    cmocka_unit_test(test__f_pipe_error_exists__returns_true),

    cmocka_unit_test(test__f_pipe_input_exists__fails),
    cmocka_unit_test(test__f_pipe_input_exists__returns_false),
    cmocka_unit_test(test__f_pipe_input_exists__returns_true),

    cmocka_unit_test(test__f_pipe_output_exists__fails),
    cmocka_unit_test(test__f_pipe_output_exists__returns_false),
    cmocka_unit_test(test__f_pipe_output_exists__returns_true),

    #ifndef _di_level_0_parameter_checking_
      // f_pipe_error_exists() doesn't use parameter checking.
      // f_pipe_input_exists() doesn't use parameter checking.
      // f_pipe_output_exists() doesn't use parameter checking.
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
