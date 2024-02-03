#include "test-string.h"

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
    cmocka_unit_test(test__f_string_append__works),
    cmocka_unit_test(test__f_string_append_assure__works),
    cmocka_unit_test(test__f_string_append_assure_nulless__works),
    cmocka_unit_test(test__f_string_append_nulless__works),

    cmocka_unit_test(test__f_string_dynamic_append__works),
    cmocka_unit_test(test__f_string_dynamic_append_assure__works),
    cmocka_unit_test(test__f_string_dynamic_append_assure_nulless__works),
    cmocka_unit_test(test__f_string_dynamic_append_nulless__works),

    cmocka_unit_test(test__f_string_dynamic_mash__works),
    cmocka_unit_test(test__f_string_dynamic_mash_nulless__works),

    cmocka_unit_test(test__f_string_dynamic_mish__works),
    cmocka_unit_test(test__f_string_dynamic_mish_nulless__works),

    cmocka_unit_test(test__f_string_dynamic_partial_append__works),
    cmocka_unit_test(test__f_string_dynamic_partial_append_assure__works),
    cmocka_unit_test(test__f_string_dynamic_partial_append_assure_nulless__works),
    cmocka_unit_test(test__f_string_dynamic_partial_append_nulless__works),

    cmocka_unit_test(test__f_string_dynamic_partial_mash__works),
    cmocka_unit_test(test__f_string_dynamic_partial_mash_nulless__works),

    cmocka_unit_test(test__f_string_dynamic_partial_mish__works),
    cmocka_unit_test(test__f_string_dynamic_partial_mish_nulless__works),

    cmocka_unit_test(test__f_string_dynamic_partial_prepend__works),
    cmocka_unit_test(test__f_string_dynamic_partial_prepend_assure__works),
    cmocka_unit_test(test__f_string_dynamic_partial_prepend_assure_nulless__works),
    cmocka_unit_test(test__f_string_dynamic_partial_prepend_nulless__works),

    cmocka_unit_test(test__f_string_dynamic_prepend__works),
    cmocka_unit_test(test__f_string_dynamic_prepend_assure__works),
    cmocka_unit_test(test__f_string_dynamic_prepend_assure_nulless__works),
    cmocka_unit_test(test__f_string_dynamic_prepend_nulless__works),

    cmocka_unit_test(test__f_string_dynamic_seek_line__returns_data_not_stop),
    cmocka_unit_test(test__f_string_dynamic_seek_line__returns_none_eos),
    cmocka_unit_test(test__f_string_dynamic_seek_line__returns_none_stop),
    cmocka_unit_test(test__f_string_dynamic_seek_line__works),

    cmocka_unit_test(test__f_string_dynamic_seek_line_to__at_newline),
    cmocka_unit_test(test__f_string_dynamic_seek_line_to__returns_data_not_stop),
    cmocka_unit_test(test__f_string_dynamic_seek_line_to__returns_none_eos),
    cmocka_unit_test(test__f_string_dynamic_seek_line_to__returns_none_stop),
    cmocka_unit_test(test__f_string_dynamic_seek_line_to__works),

    cmocka_unit_test(test__f_string_dynamic_seek_to__returns_data_not_stop),
    cmocka_unit_test(test__f_string_dynamic_seek_to__returns_none_eos),
    cmocka_unit_test(test__f_string_dynamic_seek_to__returns_none_stop),
    cmocka_unit_test(test__f_string_dynamic_seek_to__works),

    cmocka_unit_test(test__f_string_dynamic_strip_null__returns_data_not),
    cmocka_unit_test(test__f_string_dynamic_strip_null__works),

    cmocka_unit_test(test__f_string_dynamic_strip_null_range__returns_data_not),
    cmocka_unit_test(test__f_string_dynamic_strip_null_range__returns_data_not_eos),
    cmocka_unit_test(test__f_string_dynamic_strip_null_range__returns_data_not_stop),
    cmocka_unit_test(test__f_string_dynamic_strip_null_range__works),

    cmocka_unit_test(test__f_string_dynamic_terminate__appends_null),
    cmocka_unit_test(test__f_string_dynamic_terminate__doesnt_append_null),

    cmocka_unit_test(test__f_string_dynamic_terminate_after__appends_null),
    cmocka_unit_test(test__f_string_dynamic_terminate_after__doesnt_append_null),

    cmocka_unit_test(test__f_string_dynamics_append__works),
    cmocka_unit_test(test__f_string_dynamics_append_all__works),
    cmocka_unit_test(test__f_string_dynamics_append_all__returns_data_not),

    cmocka_unit_test(test__f_string_dynamicss_append__works),
    cmocka_unit_test(test__f_string_dynamicss_append__returns_data_not),
    cmocka_unit_test(test__f_string_dynamicss_append_all__works),
    cmocka_unit_test(test__f_string_dynamicss_append_all__returns_data_not),

    cmocka_unit_test(test__f_string_map_multis_append__works),
    cmocka_unit_test(test__f_string_map_multis_append_all__works),
    cmocka_unit_test(test__f_string_map_multis_append_all__returns_data_not),

    cmocka_unit_test(test__f_string_map_multiss_append__works),
    cmocka_unit_test(test__f_string_map_multiss_append__returns_data_not),
    cmocka_unit_test(test__f_string_map_multiss_append_all__works),
    cmocka_unit_test(test__f_string_map_multiss_append_all__returns_data_not),

    cmocka_unit_test(test__f_string_maps_append__works),
    cmocka_unit_test(test__f_string_maps_append_all__works),
    cmocka_unit_test(test__f_string_maps_append_all__returns_data_not),

    cmocka_unit_test(test__f_string_mapss_append__works),
    cmocka_unit_test(test__f_string_mapss_append__returns_data_not),
    cmocka_unit_test(test__f_string_mapss_append_all__works),
    cmocka_unit_test(test__f_string_mapss_append_all__returns_data_not),

    cmocka_unit_test(test__f_string_mash__works),
    cmocka_unit_test(test__f_string_mash_nulless__works),

    cmocka_unit_test(test__f_string_mish__works),
    cmocka_unit_test(test__f_string_mish_nulless__works),

    cmocka_unit_test(test__f_string_prepend__works),
    cmocka_unit_test(test__f_string_prepend_assure__works),
    cmocka_unit_test(test__f_string_prepend_assure_nulless__works),
    cmocka_unit_test(test__f_string_prepend_nulless__works),

    cmocka_unit_test(test__f_string_triples_append__works),
    cmocka_unit_test(test__f_string_triples_append_all__works),
    cmocka_unit_test(test__f_string_triples_append_all__returns_data_not),

    cmocka_unit_test(test__f_string_tripless_append__works),
    cmocka_unit_test(test__f_string_tripless_append__returns_data_not),
    cmocka_unit_test(test__f_string_tripless_append_all__works),
    cmocka_unit_test(test__f_string_tripless_append_all__returns_data_not),

    cmocka_unit_test(test__f_string_seek_line__returns_data_not_stop),
    cmocka_unit_test(test__f_string_seek_line__returns_none_stop),
    cmocka_unit_test(test__f_string_seek_line__works),

    cmocka_unit_test(test__f_string_seek_line_to__at_newline),
    cmocka_unit_test(test__f_string_seek_line_to__returns_data_not_stop),
    cmocka_unit_test(test__f_string_seek_line_to__returns_none_stop),
    cmocka_unit_test(test__f_string_seek_line_to__works),

    cmocka_unit_test(test__f_string_seek_to__returns_data_not_stop),
    cmocka_unit_test(test__f_string_seek_to__returns_none_stop),
    cmocka_unit_test(test__f_string_seek_to__works),

    cmocka_unit_test(test__f_string_dynamics_delete_callback__fails),
    cmocka_unit_test(test__f_string_dynamics_destroy_callback__fails),
    cmocka_unit_test(test__f_string_dynamics_delete_callback__works),
    cmocka_unit_test(test__f_string_dynamics_destroy_callback__works),

    cmocka_unit_test(test__f_string_dynamicss_delete_callback__fails),
    cmocka_unit_test(test__f_string_dynamicss_destroy_callback__fails),
    cmocka_unit_test(test__f_string_dynamicss_delete_callback__works),
    cmocka_unit_test(test__f_string_dynamicss_destroy_callback__works),

    cmocka_unit_test(test__f_string_map_multis_delete_callback__fails),
    cmocka_unit_test(test__f_string_map_multis_destroy_callback__fails),
    cmocka_unit_test(test__f_string_map_multis_delete_callback__works),
    cmocka_unit_test(test__f_string_map_multis_destroy_callback__works),

    cmocka_unit_test(test__f_string_map_multiss_delete_callback__fails),
    cmocka_unit_test(test__f_string_map_multiss_destroy_callback__fails),
    cmocka_unit_test(test__f_string_map_multiss_delete_callback__works),
    cmocka_unit_test(test__f_string_map_multiss_destroy_callback__works),

    cmocka_unit_test(test__f_string_maps_delete_callback__fails),
    cmocka_unit_test(test__f_string_maps_destroy_callback__fails),
    cmocka_unit_test(test__f_string_maps_delete_callback__works),
    cmocka_unit_test(test__f_string_maps_destroy_callback__works),

    cmocka_unit_test(test__f_string_mapss_delete_callback__fails),
    cmocka_unit_test(test__f_string_mapss_destroy_callback__fails),
    cmocka_unit_test(test__f_string_mapss_delete_callback__works),
    cmocka_unit_test(test__f_string_mapss_destroy_callback__works),

    cmocka_unit_test(test__f_string_triples_delete_callback__fails),
    cmocka_unit_test(test__f_string_triples_destroy_callback__fails),
    cmocka_unit_test(test__f_string_triples_delete_callback__works),
    cmocka_unit_test(test__f_string_triples_destroy_callback__works),

    cmocka_unit_test(test__f_string_tripless_delete_callback__fails),
    cmocka_unit_test(test__f_string_tripless_destroy_callback__fails),
    cmocka_unit_test(test__f_string_tripless_delete_callback__works),
    cmocka_unit_test(test__f_string_tripless_destroy_callback__works),

    #ifndef _di_level_0_parameter_checking_
      cmocka_unit_test(test__f_string_append__parameter_checking),
      cmocka_unit_test(test__f_string_append_assure__parameter_checking),
      cmocka_unit_test(test__f_string_append_assure_nulless__parameter_checking),
      cmocka_unit_test(test__f_string_append_nulless__parameter_checking),

      cmocka_unit_test(test__f_string_dynamic_append__parameter_checking),
      cmocka_unit_test(test__f_string_dynamic_append_assure__parameter_checking),
      cmocka_unit_test(test__f_string_dynamic_append_assure_nulless__parameter_checking),
      cmocka_unit_test(test__f_string_dynamic_append_nulless__parameter_checking),

      cmocka_unit_test(test__f_string_dynamic_mash__parameter_checking),
      cmocka_unit_test(test__f_string_dynamic_mash_nulless__parameter_checking),

      cmocka_unit_test(test__f_string_dynamic_mish__parameter_checking),
      cmocka_unit_test(test__f_string_dynamic_mish_nulless__parameter_checking),

      cmocka_unit_test(test__f_string_dynamic_partial_append__parameter_checking),
      cmocka_unit_test(test__f_string_dynamic_partial_append_assure__parameter_checking),
      cmocka_unit_test(test__f_string_dynamic_partial_append_assure_nulless__parameter_checking),
      cmocka_unit_test(test__f_string_dynamic_partial_append_nulless__parameter_checking),

      cmocka_unit_test(test__f_string_dynamic_partial_mash__parameter_checking),
      cmocka_unit_test(test__f_string_dynamic_partial_mash_nulless__parameter_checking),

      cmocka_unit_test(test__f_string_dynamic_partial_mish__parameter_checking),
      cmocka_unit_test(test__f_string_dynamic_partial_mish_nulless__parameter_checking),

      cmocka_unit_test(test__f_string_dynamic_partial_prepend__parameter_checking),
      cmocka_unit_test(test__f_string_dynamic_partial_prepend_assure__parameter_checking),
      cmocka_unit_test(test__f_string_dynamic_partial_prepend_assure_nulless__parameter_checking),
      cmocka_unit_test(test__f_string_dynamic_partial_prepend_nulless__parameter_checking),

      cmocka_unit_test(test__f_string_dynamic_prepend__parameter_checking),
      cmocka_unit_test(test__f_string_dynamic_prepend_assure__parameter_checking),
      cmocka_unit_test(test__f_string_dynamic_prepend_assure_nulless__parameter_checking),
      cmocka_unit_test(test__f_string_dynamic_prepend_nulless__parameter_checking),

      cmocka_unit_test(test__f_string_dynamic_seek_line__parameter_checking),
      cmocka_unit_test(test__f_string_dynamic_seek_line_to__parameter_checking),
      cmocka_unit_test(test__f_string_dynamic_seek_to__parameter_checking),

      cmocka_unit_test(test__f_string_dynamic_strip_null__parameter_checking),
      cmocka_unit_test(test__f_string_dynamic_strip_null_range__parameter_checking),

      cmocka_unit_test(test__f_string_dynamic_terminate__parameter_checking),
      cmocka_unit_test(test__f_string_dynamic_terminate_after__parameter_checking),

      cmocka_unit_test(test__f_string_dynamics_append__parameter_checking),
      cmocka_unit_test(test__f_string_dynamics_append_all__parameter_checking),
      cmocka_unit_test(test__f_string_dynamicss_append__parameter_checking),
      cmocka_unit_test(test__f_string_dynamicss_append_all__parameter_checking),

      cmocka_unit_test(test__f_string_map_multis_append__parameter_checking),
      cmocka_unit_test(test__f_string_map_multis_append_all__parameter_checking),
      cmocka_unit_test(test__f_string_map_multiss_append__parameter_checking),
      cmocka_unit_test(test__f_string_map_multiss_append_all__parameter_checking),

      cmocka_unit_test(test__f_string_maps_append__parameter_checking),
      cmocka_unit_test(test__f_string_maps_append_all__parameter_checking),
      cmocka_unit_test(test__f_string_mapss_append__parameter_checking),
      cmocka_unit_test(test__f_string_mapss_append_all__parameter_checking),

      cmocka_unit_test(test__f_string_mash__parameter_checking),
      cmocka_unit_test(test__f_string_mash_nulless__parameter_checking),

      cmocka_unit_test(test__f_string_mish__parameter_checking),
      cmocka_unit_test(test__f_string_mish_nulless__parameter_checking),

      cmocka_unit_test(test__f_string_prepend__parameter_checking),
      cmocka_unit_test(test__f_string_prepend_assure__parameter_checking),
      cmocka_unit_test(test__f_string_prepend_assure_nulless__parameter_checking),
      cmocka_unit_test(test__f_string_prepend_nulless__parameter_checking),

      cmocka_unit_test(test__f_string_triples_append__parameter_checking),
      cmocka_unit_test(test__f_string_triples_append_all__parameter_checking),
      cmocka_unit_test(test__f_string_tripless_append__parameter_checking),
      cmocka_unit_test(test__f_string_tripless_append_all__parameter_checking),

      cmocka_unit_test(test__f_string_seek_line__parameter_checking),

      cmocka_unit_test(test__f_string_seek_line_to__parameter_checking),

      cmocka_unit_test(test__f_string_seek_to__parameter_checking),

      // f_string_dynamics_delete_callback() doesn't use parameter checking.
      // f_string_dynamics_destroy_callback() doesn't use parameter checking.

      // f_string_dynamicss_delete_callback() doesn't use parameter checking.
      // f_string_dynamicss_destroy_callback() doesn't use parameter checking.

      // f_string_map_multis_delete_callback() doesn't use parameter checking.
      // f_string_map_multis_destroy_callback() doesn't use parameter checking.

      // f_string_map_multiss_delete_callback() doesn't use parameter checking.
      // f_string_map_multiss_destroy_callback() doesn't use parameter checking.

      // f_string_maps_delete_callback() doesn't use parameter checking.
      // f_string_maps_destroy_callback() doesn't use parameter checking.

      // f_string_mapss_delete_callback() doesn't use parameter checking.
      // f_string_mapss_destroy_callback() doesn't use parameter checking.

      // f_string_triples_delete_callback() doesn't use parameter checking.
      // f_string_triples_destroy_callback() doesn't use parameter checking.

      // f_string_tripless_delete_callback() doesn't use parameter checking.
      // f_string_tripless_destroy_callback() doesn't use parameter checking.
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
