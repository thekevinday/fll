#include "test-random.h"

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
    cmocka_unit_test(test__f_random_array_shuffle__fails),
    cmocka_unit_test(test__f_random_read__fails),
    cmocka_unit_test(test__f_random_seed__fails),

    cmocka_unit_test(test__f_random_array_shuffle__returns_data_not),
    cmocka_unit_test(test__f_random_array_shuffle__returns_too_small),
    cmocka_unit_test(test__f_random_array_shuffle__works),
    cmocka_unit_test(test__f_random_get__works),
    cmocka_unit_test(test__f_random_read__works),
    cmocka_unit_test(test__f_random_seed__works),
    cmocka_unit_test(test__f_random_seed_set__works),

    #ifndef _di_level_0_parameter_checking_
      cmocka_unit_test(test__f_random_array_shuffle__parameter_checking),
      cmocka_unit_test(test__f_random_get__parameter_checking),
      cmocka_unit_test(test__f_random_read__parameter_checking),

      // f_random_seed() doesn't use parameter checking.
      // f_random_seed_set() doesn't use parameter checking.
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
