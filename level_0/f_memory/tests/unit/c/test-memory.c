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

    cmocka_unit_test(test__f_memory_array_adjust__returns_array_too_large),
    cmocka_unit_test(test__f_memory_array_append__returns_array_too_large),
    cmocka_unit_test(test__f_memory_array_append_all__returns_array_too_large),
    cmocka_unit_test(test__f_memory_array_increase__returns_array_too_large),
    cmocka_unit_test(test__f_memory_array_increase_by__returns_array_too_large),
    cmocka_unit_test(test__f_memory_array_resize__returns_array_too_large),

    cmocka_unit_test(test__f_memory_arrays_adjust__returns_array_too_large),
    cmocka_unit_test(test__f_memory_arrays_resize__returns_array_too_large),

    cmocka_unit_test(test__f_memory_array_append_all__returns_data_not),
    cmocka_unit_test(test__f_memory_array_decimate_by__returns_data_not),
    cmocka_unit_test(test__f_memory_array_decrease_by__returns_data_not),
    cmocka_unit_test(test__f_memory_array_increase__returns_data_not),
    cmocka_unit_test(test__f_memory_array_increase_by__returns_data_not),

    cmocka_unit_test(test__f_memory_array_adjust__works),
    cmocka_unit_test(test__f_memory_array_append__works),
    cmocka_unit_test(test__f_memory_array_append_all__works),
    cmocka_unit_test(test__f_memory_array_decimate_by__works),
    cmocka_unit_test(test__f_memory_array_decrease_by__works),
    cmocka_unit_test(test__f_memory_array_increase__works),
    cmocka_unit_test(test__f_memory_array_increase_by__works),
    cmocka_unit_test(test__f_memory_array_resize__works),

    cmocka_unit_test(test__f_memory_arrays_adjust__works),
    cmocka_unit_test(test__f_memory_arrays_resize__works),

    #ifndef _di_level_0_parameter_checking_
      cmocka_unit_test(test__f_memory_adjust__parameter_checking),
      cmocka_unit_test(test__f_memory_delete__parameter_checking),
      cmocka_unit_test(test__f_memory_destroy__parameter_checking),
      cmocka_unit_test(test__f_memory_new__parameter_checking),
      cmocka_unit_test(test__f_memory_resize__parameter_checking),

      cmocka_unit_test(test__f_memory_array_adjust__parameter_checking),
      cmocka_unit_test(test__f_memory_array_append__parameter_checking),
      cmocka_unit_test(test__f_memory_array_append_all__parameter_checking),
      cmocka_unit_test(test__f_memory_array_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_memory_array_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_memory_array_increase__parameter_checking),
      cmocka_unit_test(test__f_memory_array_increase_by__parameter_checking),
      cmocka_unit_test(test__f_memory_array_resize__parameter_checking),

      cmocka_unit_test(test__f_memory_arrays_adjust__parameter_checking),
      cmocka_unit_test(test__f_memory_arrays_resize__parameter_checking),
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

f_status_t test_memory_array_callback(const f_number_unsigned_t start, const f_number_unsigned_t size, void * const void_array) {

  {
    test_memory_array_t * const array = (test_memory_array_t *) void_array;
    f_status_t status = F_okay;

    for (f_number_unsigned_t i = start; i < size; ++i) {

      status = f_memory_array_adjust(0, sizeof(int), (void **) &array[i].array, &array[i].used, &array[i].size);
      if (F_status_is_error(status)) return status;
    } // for
  }

  return F_okay;
}

#ifdef __cplusplus
} // extern "C"
#endif
