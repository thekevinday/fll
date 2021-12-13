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
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
