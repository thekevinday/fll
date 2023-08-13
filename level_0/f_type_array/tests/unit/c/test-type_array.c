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
    cmocka_unit_test(test__f_type_array_cells_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_cells_delete_callback__fails),

    cmocka_unit_test(test__f_type_array_files_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_files_delete_callback__fails),

    cmocka_unit_test(test__f_type_array_fll_ids_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_fll_ids_delete_callback__fails),

    cmocka_unit_test(test__f_type_array_int8s_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_int8s_delete_callback__fails),

    cmocka_unit_test(test__f_type_array_int16s_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_int16s_delete_callback__fails),

    cmocka_unit_test(test__f_type_array_int32s_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_int32s_delete_callback__fails),

    cmocka_unit_test(test__f_type_array_int64s_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_int64s_delete_callback__fails),

    cmocka_unit_test(test__f_type_array_int128s_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_int128s_delete_callback__fails),

    cmocka_unit_test(test__f_type_array_number_unsigneds_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_number_unsigneds_delete_callback__fails),

    cmocka_unit_test(test__f_type_array_polls_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_polls_delete_callback__fails),

    cmocka_unit_test(test__f_type_array_states_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_states_delete_callback__fails),

    cmocka_unit_test(test__f_type_array_statuss_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_statuss_delete_callback__fails),

    cmocka_unit_test(test__f_type_array_uint8s_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_uint8s_delete_callback__fails),

    cmocka_unit_test(test__f_type_array_uint16s_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_uint16s_delete_callback__fails),

    cmocka_unit_test(test__f_type_array_uint32s_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_uint32s_delete_callback__fails),

    cmocka_unit_test(test__f_type_array_uint64s_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_uint64s_delete_callback__fails),

    cmocka_unit_test(test__f_type_array_uint128s_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_uint128s_delete_callback__fails),

    cmocka_unit_test(test__f_type_array_cells_destroy_callback__works),
    cmocka_unit_test(test__f_type_array_cells_delete_callback__works),

    cmocka_unit_test(test__f_type_array_files_destroy_callback__works),
    cmocka_unit_test(test__f_type_array_files_delete_callback__works),

    cmocka_unit_test(test__f_type_array_fll_ids_destroy_callback__works),
    cmocka_unit_test(test__f_type_array_fll_ids_delete_callback__works),

    cmocka_unit_test(test__f_type_array_int8s_destroy_callback__works),
    cmocka_unit_test(test__f_type_array_int8s_delete_callback__works),

    cmocka_unit_test(test__f_type_array_int16s_destroy_callback__works),
    cmocka_unit_test(test__f_type_array_int16s_delete_callback__works),

    cmocka_unit_test(test__f_type_array_int32s_destroy_callback__works),
    cmocka_unit_test(test__f_type_array_int32s_delete_callback__works),

    cmocka_unit_test(test__f_type_array_int64s_destroy_callback__works),
    cmocka_unit_test(test__f_type_array_int64s_delete_callback__works),

    cmocka_unit_test(test__f_type_array_int128s_destroy_callback__works),
    cmocka_unit_test(test__f_type_array_int128s_delete_callback__works),

    cmocka_unit_test(test__f_type_array_number_unsigneds_destroy_callback__works),
    cmocka_unit_test(test__f_type_array_number_unsigneds_delete_callback__works),

    cmocka_unit_test(test__f_type_array_polls_destroy_callback__works),
    cmocka_unit_test(test__f_type_array_polls_delete_callback__works),

    cmocka_unit_test(test__f_type_array_states_destroy_callback__works),
    cmocka_unit_test(test__f_type_array_states_delete_callback__works),

    cmocka_unit_test(test__f_type_array_statuss_destroy_callback__works),
    cmocka_unit_test(test__f_type_array_statuss_delete_callback__works),

    cmocka_unit_test(test__f_type_array_uint8s_destroy_callback__works),
    cmocka_unit_test(test__f_type_array_uint8s_delete_callback__works),

    cmocka_unit_test(test__f_type_array_uint16s_destroy_callback__works),
    cmocka_unit_test(test__f_type_array_uint16s_delete_callback__works),

    cmocka_unit_test(test__f_type_array_uint32s_destroy_callback__works),
    cmocka_unit_test(test__f_type_array_uint32s_delete_callback__works),

    cmocka_unit_test(test__f_type_array_uint64s_destroy_callback__works),
    cmocka_unit_test(test__f_type_array_uint64s_delete_callback__works),

    cmocka_unit_test(test__f_type_array_uint128s_destroy_callback__works),
    cmocka_unit_test(test__f_type_array_uint128s_delete_callback__works),

    #ifndef _di_level_0_parameter_checking_
      // f_cells_destroy_callback() doesn't use parameter checking.
      // f_cells_delete_callback() doesn't use parameter checking.

      // f_files_destroy_callback() doesn't use parameter checking.
      // f_files_delete_callback() doesn't use parameter checking.

      // f_fll_ids_destroy_callback() doesn't use parameter checking.
      // f_fll_ids_delete_callback() doesn't use parameter checking.

      // f_int8s_destroy_callback() doesn't use parameter checking.
      // f_int8s_delete_callback() doesn't use parameter checking.

      // f_int16s_destroy_callback() doesn't use parameter checking.
      // f_int16s_delete_callback() doesn't use parameter checking.

      // f_int32s_destroy_callback() doesn't use parameter checking.
      // f_int32s_delete_callback() doesn't use parameter checking.

      // f_int64s_destroy_callback() doesn't use parameter checking.
      // f_int64s_delete_callback() doesn't use parameter checking.

      // f_int128s_destroy_callback() doesn't use parameter checking.
      // f_int128s_delete_callback() doesn't use parameter checking.

      // f_number_unsigneds_destroy_callback() doesn't use parameter checking.
      // f_number_unsigneds_delete_callback() doesn't use parameter checking.

      // f_polls_destroy_callback() doesn't use parameter checking.
      // f_polls_delete_callback() doesn't use parameter checking.

      // f_states_destroy_callback() doesn't use parameter checking.
      // f_states_delete_callback() doesn't use parameter checking.

      // f_statuss_destroy_callback() doesn't use parameter checking.
      // f_statuss_delete_callback() doesn't use parameter checking.

      // f_uint8s_destroy_callback() doesn't use parameter checking.
      // f_uint8s_delete_callback() doesn't use parameter checking.

      // f_uint16s_destroy_callback() doesn't use parameter checking.
      // f_uint16s_delete_callback() doesn't use parameter checking.

      // f_uint32s_destroy_callback() doesn't use parameter checking.
      // f_uint32s_delete_callback() doesn't use parameter checking.

      // f_uint64s_destroy_callback() doesn't use parameter checking.
      // f_uint64s_delete_callback() doesn't use parameter checking.

      // f_uint128s_destroy_callback() doesn't use parameter checking.
      // f_uint128s_delete_callback() doesn't use parameter checking.
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
