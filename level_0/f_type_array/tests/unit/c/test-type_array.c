#include "test-type_array.h"

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
    cmocka_unit_test(test__f_type_array_cells_adjust_callback__fails),
    cmocka_unit_test(test__f_type_array_cells_resize_callback__fails),

    cmocka_unit_test(test__f_type_array_files_adjust_callback__fails),
    cmocka_unit_test(test__f_type_array_files_resize_callback__fails),

    cmocka_unit_test(test__f_type_array_fll_ids_adjust_callback__fails),
    cmocka_unit_test(test__f_type_array_fll_ids_resize_callback__fails),

    cmocka_unit_test(test__f_type_array_int8s_adjust_callback__fails),
    cmocka_unit_test(test__f_type_array_int8s_resize_callback__fails),

    cmocka_unit_test(test__f_type_array_int16s_adjust_callback__fails),
    cmocka_unit_test(test__f_type_array_int16s_resize_callback__fails),

    cmocka_unit_test(test__f_type_array_int32s_adjust_callback__fails),
    cmocka_unit_test(test__f_type_array_int32s_resize_callback__fails),

    cmocka_unit_test(test__f_type_array_int64s_adjust_callback__fails),
    cmocka_unit_test(test__f_type_array_int64s_resize_callback__fails),

    cmocka_unit_test(test__f_type_array_int128s_adjust_callback__fails),
    cmocka_unit_test(test__f_type_array_int128s_resize_callback__fails),

    cmocka_unit_test(test__f_type_array_number_unsigneds_adjust_callback__fails),
    cmocka_unit_test(test__f_type_array_number_unsigneds_resize_callback__fails),

    cmocka_unit_test(test__f_type_array_polls_adjust_callback__fails),
    cmocka_unit_test(test__f_type_array_polls_resize_callback__fails),

    cmocka_unit_test(test__f_type_array_states_adjust_callback__fails),
    cmocka_unit_test(test__f_type_array_states_resize_callback__fails),

    cmocka_unit_test(test__f_type_array_statuss_adjust_callback__fails),
    cmocka_unit_test(test__f_type_array_statuss_resize_callback__fails),

    cmocka_unit_test(test__f_type_array_uint8s_adjust_callback__fails),
    cmocka_unit_test(test__f_type_array_uint8s_resize_callback__fails),

    cmocka_unit_test(test__f_type_array_uint16s_adjust_callback__fails),
    cmocka_unit_test(test__f_type_array_uint16s_resize_callback__fails),

    cmocka_unit_test(test__f_type_array_uint32s_adjust_callback__fails),
    cmocka_unit_test(test__f_type_array_uint32s_resize_callback__fails),

    cmocka_unit_test(test__f_type_array_uint64s_adjust_callback__fails),
    cmocka_unit_test(test__f_type_array_uint64s_resize_callback__fails),

    cmocka_unit_test(test__f_type_array_uint128s_adjust_callback__fails),
    cmocka_unit_test(test__f_type_array_uint128s_resize_callback__fails),

    cmocka_unit_test(test__f_type_array_cells_adjust_callback__works),
    cmocka_unit_test(test__f_type_array_cells_resize_callback__works),

    cmocka_unit_test(test__f_type_array_files_adjust_callback__works),
    cmocka_unit_test(test__f_type_array_files_resize_callback__works),

    cmocka_unit_test(test__f_type_array_fll_ids_adjust_callback__works),
    cmocka_unit_test(test__f_type_array_fll_ids_resize_callback__works),

    cmocka_unit_test(test__f_type_array_int8s_adjust_callback__works),
    cmocka_unit_test(test__f_type_array_int8s_resize_callback__works),

    cmocka_unit_test(test__f_type_array_int16s_adjust_callback__works),
    cmocka_unit_test(test__f_type_array_int16s_resize_callback__works),

    cmocka_unit_test(test__f_type_array_int32s_adjust_callback__works),
    cmocka_unit_test(test__f_type_array_int32s_resize_callback__works),

    cmocka_unit_test(test__f_type_array_int64s_adjust_callback__works),
    cmocka_unit_test(test__f_type_array_int64s_resize_callback__works),

    cmocka_unit_test(test__f_type_array_int128s_adjust_callback__works),
    cmocka_unit_test(test__f_type_array_int128s_resize_callback__works),

    cmocka_unit_test(test__f_type_array_number_unsigneds_adjust_callback__works),
    cmocka_unit_test(test__f_type_array_number_unsigneds_resize_callback__works),

    cmocka_unit_test(test__f_type_array_polls_adjust_callback__works),
    cmocka_unit_test(test__f_type_array_polls_resize_callback__works),

    cmocka_unit_test(test__f_type_array_states_adjust_callback__works),
    cmocka_unit_test(test__f_type_array_states_resize_callback__works),

    cmocka_unit_test(test__f_type_array_statuss_adjust_callback__works),
    cmocka_unit_test(test__f_type_array_statuss_resize_callback__works),

    cmocka_unit_test(test__f_type_array_uint8s_adjust_callback__works),
    cmocka_unit_test(test__f_type_array_uint8s_resize_callback__works),

    cmocka_unit_test(test__f_type_array_uint16s_adjust_callback__works),
    cmocka_unit_test(test__f_type_array_uint16s_resize_callback__works),

    cmocka_unit_test(test__f_type_array_uint32s_adjust_callback__works),
    cmocka_unit_test(test__f_type_array_uint32s_resize_callback__works),

    cmocka_unit_test(test__f_type_array_uint64s_adjust_callback__works),
    cmocka_unit_test(test__f_type_array_uint64s_resize_callback__works),

    cmocka_unit_test(test__f_type_array_uint128s_adjust_callback__works),
    cmocka_unit_test(test__f_type_array_uint128s_resize_callback__works),

    #ifndef _di_level_0_parameter_checking_
      // f_cells_adjust_callback() doesn't use parameter checking.
      // f_cells_resize_callback() doesn't use parameter checking.

      // f_files_adjust_callback() doesn't use parameter checking.
      // f_files_resize_callback() doesn't use parameter checking.

      // f_fll_ids_adjust_callback() doesn't use parameter checking.
      // f_fll_ids_resize_callback() doesn't use parameter checking.

      // f_int8s_adjust_callback() doesn't use parameter checking.
      // f_int8s_resize_callback() doesn't use parameter checking.

      // f_int16s_adjust_callback() doesn't use parameter checking.
      // f_int16s_resize_callback() doesn't use parameter checking.

      // f_int32s_adjust_callback() doesn't use parameter checking.
      // f_int32s_resize_callback() doesn't use parameter checking.

      // f_int64s_adjust_callback() doesn't use parameter checking.
      // f_int64s_resize_callback() doesn't use parameter checking.

      // f_int128s_adjust_callback() doesn't use parameter checking.
      // f_int128s_resize_callback() doesn't use parameter checking.

      // f_number_unsigneds_adjust_callback() doesn't use parameter checking.
      // f_number_unsigneds_resize_callback() doesn't use parameter checking.

      // f_polls_adjust_callback() doesn't use parameter checking.
      // f_polls_resize_callback() doesn't use parameter checking.

      // f_states_adjust_callback() doesn't use parameter checking.
      // f_states_resize_callback() doesn't use parameter checking.

      // f_statuss_adjust_callback() doesn't use parameter checking.
      // f_statuss_resize_callback() doesn't use parameter checking.

      // f_uint8s_adjust_callback() doesn't use parameter checking.
      // f_uint8s_resize_callback() doesn't use parameter checking.

      // f_uint16s_adjust_callback() doesn't use parameter checking.
      // f_uint16s_resize_callback() doesn't use parameter checking.

      // f_uint32s_adjust_callback() doesn't use parameter checking.
      // f_uint32s_resize_callback() doesn't use parameter checking.

      // f_uint64s_adjust_callback() doesn't use parameter checking.
      // f_uint64s_resize_callback() doesn't use parameter checking.

      // f_uint128s_adjust_callback() doesn't use parameter checking.
      // f_uint128s_resize_callback() doesn't use parameter checking.
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
