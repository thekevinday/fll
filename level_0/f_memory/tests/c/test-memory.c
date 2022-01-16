#include "test-memory.h"

#ifdef __cplusplus
extern "C" {
#endif

int setup(void **state) {

  return 0;
}

int setdown(void **state) {

  return 0;
}

int main(void) {

  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test__f_memory_adjust__works),

    cmocka_unit_test(test__f_memory_delete__frees_adjusted_memory),
    cmocka_unit_test(test__f_memory_delete__frees_aligned_memory),
    cmocka_unit_test(test__f_memory_delete__frees_memory),
    cmocka_unit_test(test__f_memory_delete__frees_resized_memory),

    cmocka_unit_test(test__f_memory_destroy__frees_adjusted_memory),
    cmocka_unit_test(test__f_memory_destroy__frees_aligned_memory),
    cmocka_unit_test(test__f_memory_destroy__frees_memory),
    cmocka_unit_test(test__f_memory_destroy__frees_resized_memory),

    cmocka_unit_test(test__f_memory_new__works),
    cmocka_unit_test(test__f_memory_new_aligned__works),

    cmocka_unit_test(test__f_memory_resize__works),

    #ifndef _di_level_0_parameter_checking_
      cmocka_unit_test(test__f_memory_adjust__parameter_checking),
      cmocka_unit_test(test__f_memory_delete__parameter_checking),
      cmocka_unit_test(test__f_memory_destroy__parameter_checking),
      cmocka_unit_test(test__f_memory_new__parameter_checking),
      cmocka_unit_test(test__f_memory_resize__parameter_checking),
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
