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
    cmocka_unit_test(test__fl_path_canonical__back_paths),
    cmocka_unit_test(test__fl_path_canonical__empty_becomes_pwd),
    cmocka_unit_test(test__fl_path_canonical__present_paths),
    cmocka_unit_test(test__fl_path_canonical__root_paths),
    cmocka_unit_test(test__fl_path_canonical__tilde_remains),

    #ifndef _di_level_0_parameter_checking_
      cmocka_unit_test(test__fl_path_canonical__parameter_checking),
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
