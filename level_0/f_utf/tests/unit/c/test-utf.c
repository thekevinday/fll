#include "test-utf.h"

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
    cmocka_unit_test(test__f_utf_append__works),
    cmocka_unit_test(test__f_utf_append_assure__works),
    cmocka_unit_test(test__f_utf_append_assure_nulless__works),
    cmocka_unit_test(test__f_utf_append_nulless__works),

    cmocka_unit_test(test__f_utf_character_is_symbol__works),

    cmocka_unit_test(test__f_utf_dynamic_adjust__works),

    cmocka_unit_test(test__f_utf_dynamic_append__works),
    cmocka_unit_test(test__f_utf_dynamic_append_assure__works),
    cmocka_unit_test(test__f_utf_dynamic_append_assure_nulless__works),
    cmocka_unit_test(test__f_utf_dynamic_append_nulless__works),

    cmocka_unit_test(test__f_utf_dynamic_decimate_by__works),
    cmocka_unit_test(test__f_utf_dynamic_decrease_by__works),
    cmocka_unit_test(test__f_utf_dynamic_increase__works),
    cmocka_unit_test(test__f_utf_dynamic_increase__returns_data_not),
    cmocka_unit_test(test__f_utf_dynamic_increase_by__works),

    cmocka_unit_test(test__f_utf_dynamic_mash__works),
    cmocka_unit_test(test__f_utf_dynamic_mash_nulless__works),

    cmocka_unit_test(test__f_utf_dynamic_mish__works),
    cmocka_unit_test(test__f_utf_dynamic_mish_nulless__works),

    cmocka_unit_test(test__f_utf_dynamic_partial_append__works),
    cmocka_unit_test(test__f_utf_dynamic_partial_append_assure__works),
    cmocka_unit_test(test__f_utf_dynamic_partial_append_assure_nulless__works),
    cmocka_unit_test(test__f_utf_dynamic_partial_append_nulless__works),

    cmocka_unit_test(test__f_utf_dynamic_partial_mash__works),
    cmocka_unit_test(test__f_utf_dynamic_partial_mash_nulless__works),

    cmocka_unit_test(test__f_utf_dynamic_partial_mish__works),
    cmocka_unit_test(test__f_utf_dynamic_partial_mish_nulless__works),

    cmocka_unit_test(test__f_utf_dynamic_partial_prepend__works),
    cmocka_unit_test(test__f_utf_dynamic_partial_prepend_assure__works),
    cmocka_unit_test(test__f_utf_dynamic_partial_prepend_assure_nulless__works),
    cmocka_unit_test(test__f_utf_dynamic_partial_prepend_nulless__works),

    cmocka_unit_test(test__f_utf_dynamic_prepend__works),
    cmocka_unit_test(test__f_utf_dynamic_prepend_assure__works),
    cmocka_unit_test(test__f_utf_dynamic_prepend_assure_nulless__works),
    cmocka_unit_test(test__f_utf_dynamic_prepend_nulless__works),

    cmocka_unit_test(test__f_utf_dynamic_resize__works),

    cmocka_unit_test(test__f_utf_dynamic_seek_line__returns_data_not_stop),
    cmocka_unit_test(test__f_utf_dynamic_seek_line__returns_none_eos),
    cmocka_unit_test(test__f_utf_dynamic_seek_line__returns_none_stop),
    cmocka_unit_test(test__f_utf_dynamic_seek_line__works),

    cmocka_unit_test(test__f_utf_dynamic_seek_line_to__after_newline),
    cmocka_unit_test(test__f_utf_dynamic_seek_line_to__before_newline),
    cmocka_unit_test(test__f_utf_dynamic_seek_line_to__returns_data_not_stop),
    cmocka_unit_test(test__f_utf_dynamic_seek_line_to__returns_none_eos),
    cmocka_unit_test(test__f_utf_dynamic_seek_line_to__returns_none_stop),

    cmocka_unit_test(test__f_utf_dynamic_seek_to__after_newline),
    cmocka_unit_test(test__f_utf_dynamic_seek_to__before_newline),
    cmocka_unit_test(test__f_utf_dynamic_seek_to__returns_data_not_stop),
    cmocka_unit_test(test__f_utf_dynamic_seek_to__returns_none_eos),
    cmocka_unit_test(test__f_utf_dynamic_seek_to__returns_none_stop),

    cmocka_unit_test(test__f_utf_dynamic_terminate__appends_null),
    cmocka_unit_test(test__f_utf_dynamic_terminate__doesnt_append_null),

    cmocka_unit_test(test__f_utf_dynamic_terminate_after__appends_null),
    cmocka_unit_test(test__f_utf_dynamic_terminate_after__doesnt_append_null),

    cmocka_unit_test(test__f_utf_dynamics_adjust__works),
    cmocka_unit_test(test__f_utf_dynamics_append__works),
    cmocka_unit_test(test__f_utf_dynamics_append_all__works),
    cmocka_unit_test(test__f_utf_dynamics_append_all__returns_data_not),
    cmocka_unit_test(test__f_utf_dynamics_decimate_by__works),
    cmocka_unit_test(test__f_utf_dynamics_decrease_by__works),
    cmocka_unit_test(test__f_utf_dynamics_increase__works),
    cmocka_unit_test(test__f_utf_dynamics_increase__returns_data_not),
    cmocka_unit_test(test__f_utf_dynamics_increase_by__works),
    cmocka_unit_test(test__f_utf_dynamics_resize__works),

    cmocka_unit_test(test__f_utf_dynamicss_adjust__works),
    cmocka_unit_test(test__f_utf_dynamicss_append__works),
    cmocka_unit_test(test__f_utf_dynamicss_append__returns_data_not),
    cmocka_unit_test(test__f_utf_dynamicss_append_all__works),
    cmocka_unit_test(test__f_utf_dynamicss_append_all__returns_data_not),
    cmocka_unit_test(test__f_utf_dynamicss_decimate_by__works),
    cmocka_unit_test(test__f_utf_dynamicss_decrease_by__works),
    cmocka_unit_test(test__f_utf_dynamicss_increase__works),
    cmocka_unit_test(test__f_utf_dynamicss_increase__returns_data_not),
    cmocka_unit_test(test__f_utf_dynamicss_increase_by__works),
    cmocka_unit_test(test__f_utf_dynamicss_resize__works),

    cmocka_unit_test(test__f_utf_is_symbol__works),

    cmocka_unit_test(test__f_utf_map_multis_adjust__works),
    cmocka_unit_test(test__f_utf_map_multis_append__works),
    cmocka_unit_test(test__f_utf_map_multis_append_all__works),
    cmocka_unit_test(test__f_utf_map_multis_append_all__returns_data_not),
    cmocka_unit_test(test__f_utf_map_multis_decimate_by__works),
    cmocka_unit_test(test__f_utf_map_multis_decrease_by__works),
    cmocka_unit_test(test__f_utf_map_multis_increase__works),
    cmocka_unit_test(test__f_utf_map_multis_increase__returns_data_not),
    cmocka_unit_test(test__f_utf_map_multis_increase_by__works),
    cmocka_unit_test(test__f_utf_map_multis_resize__works),

    cmocka_unit_test(test__f_utf_map_multiss_adjust__works),
    cmocka_unit_test(test__f_utf_map_multiss_append__works),
    cmocka_unit_test(test__f_utf_map_multiss_append__returns_data_not),
    cmocka_unit_test(test__f_utf_map_multiss_append_all__works),
    cmocka_unit_test(test__f_utf_map_multiss_append_all__returns_data_not),
    cmocka_unit_test(test__f_utf_map_multiss_decimate_by__works),
    cmocka_unit_test(test__f_utf_map_multiss_decrease_by__works),
    cmocka_unit_test(test__f_utf_map_multiss_increase__works),
    cmocka_unit_test(test__f_utf_map_multiss_increase__returns_data_not),
    cmocka_unit_test(test__f_utf_map_multiss_increase_by__works),
    cmocka_unit_test(test__f_utf_map_multiss_resize__works),

    cmocka_unit_test(test__f_utf_maps_adjust__works),
    cmocka_unit_test(test__f_utf_maps_append__works),
    cmocka_unit_test(test__f_utf_maps_append_all__works),
    cmocka_unit_test(test__f_utf_maps_append_all__returns_data_not),
    cmocka_unit_test(test__f_utf_maps_decimate_by__works),
    cmocka_unit_test(test__f_utf_maps_decrease_by__works),
    cmocka_unit_test(test__f_utf_maps_increase__works),
    cmocka_unit_test(test__f_utf_maps_increase__returns_data_not),
    cmocka_unit_test(test__f_utf_maps_increase_by__works),
    cmocka_unit_test(test__f_utf_maps_resize__works),

    cmocka_unit_test(test__f_utf_mapss_adjust__works),
    cmocka_unit_test(test__f_utf_mapss_append__works),
    cmocka_unit_test(test__f_utf_mapss_append__returns_data_not),
    cmocka_unit_test(test__f_utf_mapss_append_all__works),
    cmocka_unit_test(test__f_utf_mapss_append_all__returns_data_not),
    cmocka_unit_test(test__f_utf_mapss_decimate_by__works),
    cmocka_unit_test(test__f_utf_mapss_decrease_by__works),
    cmocka_unit_test(test__f_utf_mapss_increase__works),
    cmocka_unit_test(test__f_utf_mapss_increase__returns_data_not),
    cmocka_unit_test(test__f_utf_mapss_increase_by__works),
    cmocka_unit_test(test__f_utf_mapss_resize__works),

    cmocka_unit_test(test__f_utf_mash__works),
    cmocka_unit_test(test__f_utf_mash_nulless__works),

    cmocka_unit_test(test__f_utf_mish__works),
    cmocka_unit_test(test__f_utf_mish_nulless__works),

    cmocka_unit_test(test__f_utf_prepend__works),
    cmocka_unit_test(test__f_utf_prepend_assure__works),
    cmocka_unit_test(test__f_utf_prepend_assure_nulless__works),
    cmocka_unit_test(test__f_utf_prepend_nulless__works),

    cmocka_unit_test(test__f_utf_triples_adjust__works),
    cmocka_unit_test(test__f_utf_triples_append__works),
    cmocka_unit_test(test__f_utf_triples_append_all__works),
    cmocka_unit_test(test__f_utf_triples_append_all__returns_data_not),
    cmocka_unit_test(test__f_utf_triples_decimate_by__works),
    cmocka_unit_test(test__f_utf_triples_decrease_by__works),
    cmocka_unit_test(test__f_utf_triples_increase__works),
    cmocka_unit_test(test__f_utf_triples_increase__returns_data_not),
    cmocka_unit_test(test__f_utf_triples_increase_by__works),
    cmocka_unit_test(test__f_utf_triples_resize__works),

    cmocka_unit_test(test__f_utf_tripless_adjust__works),
    cmocka_unit_test(test__f_utf_tripless_append__works),
    cmocka_unit_test(test__f_utf_tripless_append__returns_data_not),
    cmocka_unit_test(test__f_utf_tripless_append_all__works),
    cmocka_unit_test(test__f_utf_tripless_append_all__returns_data_not),
    cmocka_unit_test(test__f_utf_tripless_decimate_by__works),
    cmocka_unit_test(test__f_utf_tripless_decrease_by__works),
    cmocka_unit_test(test__f_utf_tripless_increase__works),
    cmocka_unit_test(test__f_utf_tripless_increase__returns_data_not),
    cmocka_unit_test(test__f_utf_tripless_increase_by__works),
    cmocka_unit_test(test__f_utf_tripless_resize__works),

    cmocka_unit_test(test__f_utf_seek_line__returns_data_not_stop),
    cmocka_unit_test(test__f_utf_seek_line__returns_none_stop),
    cmocka_unit_test(test__f_utf_seek_line__works),

    cmocka_unit_test(test__f_utf_seek_line_to__after_newline),
    cmocka_unit_test(test__f_utf_seek_line_to__before_newline),
    cmocka_unit_test(test__f_utf_seek_line_to__returns_data_not_stop),
    cmocka_unit_test(test__f_utf_seek_line_to__returns_none_stop),

    cmocka_unit_test(test__f_utf_seek_to__after_newline),
    cmocka_unit_test(test__f_utf_seek_to__before_newline),
    cmocka_unit_test(test__f_utf_seek_to__returns_data_not_stop),
    cmocka_unit_test(test__f_utf_seek_to__returns_none_stop),

    #ifndef _di_level_0_parameter_checking_
      cmocka_unit_test(test__f_utf_append__parameter_checking),
      cmocka_unit_test(test__f_utf_append_assure__parameter_checking),
      cmocka_unit_test(test__f_utf_append_assure_nulless__parameter_checking),
      cmocka_unit_test(test__f_utf_append_nulless__parameter_checking),

      cmocka_unit_test(test__f_utf_dynamic_adjust__parameter_checking),

      cmocka_unit_test(test__f_utf_dynamic_append__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamic_append_assure__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamic_append_assure_nulless__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamic_append_nulless__parameter_checking),

      cmocka_unit_test(test__f_utf_dynamic_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamic_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamic_increase__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamic_increase__returns_data_not),
      cmocka_unit_test(test__f_utf_dynamic_increase_by__parameter_checking),

      cmocka_unit_test(test__f_utf_dynamic_mash__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamic_mash_nulless__parameter_checking),

      cmocka_unit_test(test__f_utf_dynamic_mish__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamic_mish_nulless__parameter_checking),

      cmocka_unit_test(test__f_utf_dynamic_partial_append__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamic_partial_append_assure__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamic_partial_append_assure_nulless__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamic_partial_append_nulless__parameter_checking),

      cmocka_unit_test(test__f_utf_dynamic_partial_mash__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamic_partial_mash_nulless__parameter_checking),

      cmocka_unit_test(test__f_utf_dynamic_partial_mish__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamic_partial_mish_nulless__parameter_checking),

      cmocka_unit_test(test__f_utf_dynamic_partial_prepend__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamic_partial_prepend_assure__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamic_partial_prepend_assure_nulless__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamic_partial_prepend_nulless__parameter_checking),

      cmocka_unit_test(test__f_utf_dynamic_prepend__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamic_prepend_assure__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamic_prepend_assure_nulless__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamic_prepend_nulless__parameter_checking),

      cmocka_unit_test(test__f_utf_dynamic_resize__parameter_checking),

      cmocka_unit_test(test__f_utf_dynamic_seek_line__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamic_seek_line_to__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamic_seek_to__parameter_checking),

      cmocka_unit_test(test__f_utf_dynamic_terminate__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamic_terminate_after__parameter_checking),

      cmocka_unit_test(test__f_utf_dynamics_adjust__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamics_append__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamics_append_all__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamics_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamics_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamics_increase__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamics_increase_by__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamics_resize__parameter_checking),

      cmocka_unit_test(test__f_utf_dynamicss_adjust__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamicss_append__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamicss_append_all__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamicss_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamicss_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamicss_increase__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamicss_increase_by__parameter_checking),
      cmocka_unit_test(test__f_utf_dynamicss_resize__parameter_checking),

      cmocka_unit_test(test__f_utf_map_multis_adjust__parameter_checking),
      cmocka_unit_test(test__f_utf_map_multis_append__parameter_checking),
      cmocka_unit_test(test__f_utf_map_multis_append_all__parameter_checking),
      cmocka_unit_test(test__f_utf_map_multis_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_utf_map_multis_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_utf_map_multis_increase__parameter_checking),
      cmocka_unit_test(test__f_utf_map_multis_increase_by__parameter_checking),
      cmocka_unit_test(test__f_utf_map_multis_resize__parameter_checking),

      cmocka_unit_test(test__f_utf_map_multiss_adjust__parameter_checking),
      cmocka_unit_test(test__f_utf_map_multiss_append__parameter_checking),
      cmocka_unit_test(test__f_utf_map_multiss_append_all__parameter_checking),
      cmocka_unit_test(test__f_utf_map_multiss_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_utf_map_multiss_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_utf_map_multiss_increase__parameter_checking),
      cmocka_unit_test(test__f_utf_map_multiss_increase_by__parameter_checking),
      cmocka_unit_test(test__f_utf_map_multiss_resize__parameter_checking),

      cmocka_unit_test(test__f_utf_maps_adjust__parameter_checking),
      cmocka_unit_test(test__f_utf_maps_append__parameter_checking),
      cmocka_unit_test(test__f_utf_maps_append_all__parameter_checking),
      cmocka_unit_test(test__f_utf_maps_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_utf_maps_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_utf_maps_increase__parameter_checking),
      cmocka_unit_test(test__f_utf_maps_increase_by__parameter_checking),
      cmocka_unit_test(test__f_utf_maps_resize__parameter_checking),

      cmocka_unit_test(test__f_utf_mapss_adjust__parameter_checking),
      cmocka_unit_test(test__f_utf_mapss_append__parameter_checking),
      cmocka_unit_test(test__f_utf_mapss_append_all__parameter_checking),
      cmocka_unit_test(test__f_utf_mapss_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_utf_mapss_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_utf_mapss_increase__parameter_checking),
      cmocka_unit_test(test__f_utf_mapss_increase_by__parameter_checking),
      cmocka_unit_test(test__f_utf_mapss_resize__parameter_checking),

      cmocka_unit_test(test__f_utf_mash__parameter_checking),
      cmocka_unit_test(test__f_utf_mash_nulless__parameter_checking),

      cmocka_unit_test(test__f_utf_mish__parameter_checking),
      cmocka_unit_test(test__f_utf_mish_nulless__parameter_checking),

      cmocka_unit_test(test__f_utf_prepend__parameter_checking),
      cmocka_unit_test(test__f_utf_prepend_assure__parameter_checking),
      cmocka_unit_test(test__f_utf_prepend_assure_nulless__parameter_checking),
      cmocka_unit_test(test__f_utf_prepend_nulless__parameter_checking),

      cmocka_unit_test(test__f_utf_triples_adjust__parameter_checking),
      cmocka_unit_test(test__f_utf_triples_append__parameter_checking),
      cmocka_unit_test(test__f_utf_triples_append_all__parameter_checking),
      cmocka_unit_test(test__f_utf_triples_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_utf_triples_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_utf_triples_increase__parameter_checking),
      cmocka_unit_test(test__f_utf_triples_increase_by__parameter_checking),
      cmocka_unit_test(test__f_utf_triples_resize__parameter_checking),

      cmocka_unit_test(test__f_utf_tripless_adjust__parameter_checking),
      cmocka_unit_test(test__f_utf_tripless_append__parameter_checking),
      cmocka_unit_test(test__f_utf_tripless_append_all__parameter_checking),
      cmocka_unit_test(test__f_utf_tripless_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_utf_tripless_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_utf_tripless_increase__parameter_checking),
      cmocka_unit_test(test__f_utf_tripless_increase_by__parameter_checking),
      cmocka_unit_test(test__f_utf_tripless_resize__parameter_checking),

      cmocka_unit_test(test__f_utf_seek_line__parameter_checking),

      cmocka_unit_test(test__f_utf_seek_line_to__parameter_checking),

      cmocka_unit_test(test__f_utf_seek_to__parameter_checking),
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
