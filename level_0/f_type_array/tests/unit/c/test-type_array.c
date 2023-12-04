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
    cmocka_unit_test(test__f_type_array_cellss_delete_callback__fails),
    cmocka_unit_test(test__f_type_array_cellss_delete_callback__works),

    cmocka_unit_test(test__f_type_array_cellss_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_cellss_destroy_callback__works),

    cmocka_unit_test(test__f_type_array_filess_delete_callback__fails),
    cmocka_unit_test(test__f_type_array_filess_delete_callback__works),

    cmocka_unit_test(test__f_type_array_filess_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_filess_destroy_callback__works),

    cmocka_unit_test(test__f_type_array_fll_idss_delete_callback__fails),
    cmocka_unit_test(test__f_type_array_fll_idss_delete_callback__works),

    cmocka_unit_test(test__f_type_array_fll_idss_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_fll_idss_destroy_callback__works),

    cmocka_unit_test(test__f_type_array_int8ss_delete_callback__fails),
    cmocka_unit_test(test__f_type_array_int8ss_delete_callback__works),

    cmocka_unit_test(test__f_type_array_int8ss_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_int8ss_destroy_callback__works),

    cmocka_unit_test(test__f_type_array_int16ss_delete_callback__fails),
    cmocka_unit_test(test__f_type_array_int16ss_delete_callback__works),

    cmocka_unit_test(test__f_type_array_int16ss_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_int16ss_destroy_callback__works),

    cmocka_unit_test(test__f_type_array_int32ss_delete_callback__fails),
    cmocka_unit_test(test__f_type_array_int32ss_delete_callback__works),

    cmocka_unit_test(test__f_type_array_int32ss_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_int32ss_destroy_callback__works),

    cmocka_unit_test(test__f_type_array_int64ss_delete_callback__fails),
    cmocka_unit_test(test__f_type_array_int64ss_delete_callback__works),

    cmocka_unit_test(test__f_type_array_int64ss_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_int64ss_destroy_callback__works),

    cmocka_unit_test(test__f_type_array_int128ss_delete_callback__fails),
    cmocka_unit_test(test__f_type_array_int128ss_delete_callback__works),

    cmocka_unit_test(test__f_type_array_int128ss_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_int128ss_destroy_callback__works),

    cmocka_unit_test(test__f_type_array_number_signedss_delete_callback__fails),
    cmocka_unit_test(test__f_type_array_number_signedss_delete_callback__works),

    cmocka_unit_test(test__f_type_array_number_signedss_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_number_signedss_destroy_callback__works),

    cmocka_unit_test(test__f_type_array_number_unsignedss_delete_callback__fails),
    cmocka_unit_test(test__f_type_array_number_unsignedss_delete_callback__works),

    cmocka_unit_test(test__f_type_array_number_unsignedss_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_number_unsignedss_destroy_callback__works),

    cmocka_unit_test(test__f_type_array_pollss_delete_callback__fails),
    cmocka_unit_test(test__f_type_array_pollss_delete_callback__works),

    cmocka_unit_test(test__f_type_array_pollss_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_pollss_destroy_callback__works),

    cmocka_unit_test(test__f_type_array_ranges_append__works),
    cmocka_unit_test(test__f_type_array_ranges_append_all__works),
    cmocka_unit_test(test__f_type_array_ranges_append_all__returns_data_not),

    cmocka_unit_test(test__f_type_array_rangess_append__works),
    cmocka_unit_test(test__f_type_array_rangess_append__returns_data_not),
    cmocka_unit_test(test__f_type_array_rangess_append_all__works),
    cmocka_unit_test(test__f_type_array_rangess_append_all__returns_data_not),

    cmocka_unit_test(test__f_type_array_rangess_delete_callback__fails),
    cmocka_unit_test(test__f_type_array_rangess_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_rangess_delete_callback__works),
    cmocka_unit_test(test__f_type_array_rangess_destroy_callback__works),

    cmocka_unit_test(test__f_type_array_statess_delete_callback__fails),
    cmocka_unit_test(test__f_type_array_statess_delete_callback__works),

    cmocka_unit_test(test__f_type_array_statess_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_statess_destroy_callback__works),

    cmocka_unit_test(test__f_type_array_statusss_delete_callback__fails),
    cmocka_unit_test(test__f_type_array_statusss_delete_callback__works),

    cmocka_unit_test(test__f_type_array_statusss_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_statusss_destroy_callback__works),

    cmocka_unit_test(test__f_type_array_uint8ss_delete_callback__fails),
    cmocka_unit_test(test__f_type_array_uint8ss_delete_callback__works),

    cmocka_unit_test(test__f_type_array_uint8ss_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_uint8ss_destroy_callback__works),

    cmocka_unit_test(test__f_type_array_uint16ss_delete_callback__fails),
    cmocka_unit_test(test__f_type_array_uint16ss_delete_callback__works),

    cmocka_unit_test(test__f_type_array_uint16ss_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_uint16ss_destroy_callback__works),

    cmocka_unit_test(test__f_type_array_uint32ss_delete_callback__fails),
    cmocka_unit_test(test__f_type_array_uint32ss_delete_callback__works),

    cmocka_unit_test(test__f_type_array_uint32ss_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_uint32ss_destroy_callback__works),

    cmocka_unit_test(test__f_type_array_uint64ss_delete_callback__fails),
    cmocka_unit_test(test__f_type_array_uint64ss_delete_callback__works),

    cmocka_unit_test(test__f_type_array_uint64ss_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_uint64ss_destroy_callback__works),

    cmocka_unit_test(test__f_type_array_uint128ss_delete_callback__fails),
    cmocka_unit_test(test__f_type_array_uint128ss_delete_callback__works),

    cmocka_unit_test(test__f_type_array_uint128ss_destroy_callback__fails),
    cmocka_unit_test(test__f_type_array_uint128ss_destroy_callback__works),

    #ifndef _di_level_0_parameter_checking_
      // f_cellss_destroy_callback() doesn't use parameter checking.
      // f_cellss_delete_callback() doesn't use parameter checking.

      // f_filess_destroy_callback() doesn't use parameter checking.
      // f_filess_delete_callback() doesn't use parameter checking.

      // f_fll_idss_destroy_callback() doesn't use parameter checking.
      // f_fll_idss_delete_callback() doesn't use parameter checking.

      // f_int8ss_destroy_callback() doesn't use parameter checking.
      // f_int8ss_delete_callback() doesn't use parameter checking.

      // f_int16ss_destroy_callback() doesn't use parameter checking.
      // f_int16ss_delete_callback() doesn't use parameter checking.

      // f_int32ss_destroy_callback() doesn't use parameter checking.
      // f_int32ss_delete_callback() doesn't use parameter checking.

      // f_int64ss_destroy_callback() doesn't use parameter checking.
      // f_int64ss_delete_callback() doesn't use parameter checking.

      // f_int128ss_destroy_callback() doesn't use parameter checking.
      // f_int128ss_delete_callback() doesn't use parameter checking.

      // f_number_signedss_destroy_callback() doesn't use parameter checking.
      // f_number_signedss_delete_callback() doesn't use parameter checking.

      // f_number_unsignedss_destroy_callback() doesn't use parameter checking.
      // f_number_unsignedss_delete_callback() doesn't use parameter checking.

      // f_pollss_destroy_callback() doesn't use parameter checking.
      // f_pollss_delete_callback() doesn't use parameter checking.

      cmocka_unit_test(test__f_type_array_ranges_append__parameter_checking),
      cmocka_unit_test(test__f_type_array_ranges_append_all__parameter_checking),
      cmocka_unit_test(test__f_type_array_rangess_append__parameter_checking),
      cmocka_unit_test(test__f_type_array_rangess_append_all__parameter_checking),

      // f_rangess_delete_callback() doesn't use parameter checking.
      // f_rangess_destroy_callback() doesn't use parameter checking.

      // f_statess_destroy_callback() doesn't use parameter checking.
      // f_statess_delete_callback() doesn't use parameter checking.

      // f_statusss_destroy_callback() doesn't use parameter checking.
      // f_statusss_delete_callback() doesn't use parameter checking.

      // f_uint8ss_destroy_callback() doesn't use parameter checking.
      // f_uint8ss_delete_callback() doesn't use parameter checking.

      // f_uint16ss_destroy_callback() doesn't use parameter checking.
      // f_uint16ss_delete_callback() doesn't use parameter checking.

      // f_uint32ss_destroy_callback() doesn't use parameter checking.
      // f_uint32ss_delete_callback() doesn't use parameter checking.

      // f_uint64ss_destroy_callback() doesn't use parameter checking.
      // f_uint64ss_delete_callback() doesn't use parameter checking.

      // f_uint128ss_destroy_callback() doesn't use parameter checking.
      // f_uint128ss_delete_callback() doesn't use parameter checking.
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
