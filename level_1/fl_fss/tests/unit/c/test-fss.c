#include "test-fss.h"

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
    cmocka_unit_test(test__fl_fss_basic_content_read__returns_data_not),
    cmocka_unit_test(test__fl_fss_basic_content_write__returns_data_not),
    cmocka_unit_test(test__fl_fss_basic_object_read__returns_data_not),
    cmocka_unit_test(test__fl_fss_basic_object_write__returns_data_not),

    cmocka_unit_test(test__fl_fss_basic_content_read__works),
    cmocka_unit_test(test__fl_fss_basic_object_read__works),

    cmocka_unit_test(test__fl_fss_basic_list_content_read__returns_data_not),
    cmocka_unit_test(test__fl_fss_basic_list_content_write__returns_data_not),
    cmocka_unit_test(test__fl_fss_basic_list_object_read__returns_data_not),
    cmocka_unit_test(test__fl_fss_basic_list_object_write__returns_data_not),

    cmocka_unit_test(test__fl_fss_basic_list_content_read__works),
    cmocka_unit_test(test__fl_fss_basic_list_object_read__works),

    cmocka_unit_test(test__fl_fss_embedded_list_content_read__returns_data_not),
    cmocka_unit_test(test__fl_fss_embedded_list_content_write__returns_data_not),
    cmocka_unit_test(test__fl_fss_embedded_list_object_read__returns_data_not),
    cmocka_unit_test(test__fl_fss_embedded_list_object_write__returns_data_not),

    cmocka_unit_test(test__fl_fss_embedded_list_content_read__works),
    cmocka_unit_test(test__fl_fss_embedded_list_object_read__works),

    cmocka_unit_test(test__fl_fss_extended_content_read__returns_data_not),
    cmocka_unit_test(test__fl_fss_extended_content_write__returns_data_not),
    cmocka_unit_test(test__fl_fss_extended_object_read__returns_data_not),
    cmocka_unit_test(test__fl_fss_extended_object_write__returns_data_not),

    cmocka_unit_test(test__fl_fss_extended_content_read__works),
    cmocka_unit_test(test__fl_fss_extended_object_read__works),

    cmocka_unit_test(test__fl_fss_extended_list_content_read__returns_data_not),
    cmocka_unit_test(test__fl_fss_extended_list_content_write__returns_data_not),
    cmocka_unit_test(test__fl_fss_extended_list_object_read__returns_data_not),
    cmocka_unit_test(test__fl_fss_extended_list_object_write__returns_data_not),

    cmocka_unit_test(test__fl_fss_extended_list_content_read__works),
    cmocka_unit_test(test__fl_fss_extended_list_object_read__works),

    cmocka_unit_test(test__fl_fss_payload_header_map__returns_data_not),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_dynamic__works_join),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_dynamics__works_join),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_dynamics__works_split),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_int8s__works_join),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_int8s__works_split),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_int16s__works_join),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_int16s__works_split),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_int32s__works_join),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_int32s__works_split),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_int64s__works_join),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_int64s__works_split),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_map__works_join),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_map__works_split),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_map_multi__works_join),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_map_multi__works_split),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_map_multis__works_join),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_map_multis__works_split),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_maps__works_join),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_maps__works_split),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_quantity__works_join),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_quantity__works_split),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_quantitys__works_join),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_quantitys__works_split),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_range__works_join),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_range__works_split),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_ranges__works_join),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_ranges__works_split),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_signed__works_join),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_signeds__works_join),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_signeds__works_split),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_string__works_join),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_strings__works_join),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_strings__works_split),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_triple__works_join),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_triple__works_split),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_triples__works_join),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_triples__works_split),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_uint8s__works_join),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_uint8s__works_split),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_uint16s__works_join),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_uint16s__works_split),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_uint32s__works_join),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_uint32s__works_split),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_uint64s__works_join),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_uint64s__works_split),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_unsigned__works_join),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_unsigneds__works_join),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_unsigneds__works_split),

    #ifndef _di_level_0_parameter_checking_
      cmocka_unit_test(test__fl_fss_basic_content_read__parameter_checking),
      cmocka_unit_test(test__fl_fss_basic_content_write__parameter_checking),
      cmocka_unit_test(test__fl_fss_basic_object_read__parameter_checking),
      cmocka_unit_test(test__fl_fss_basic_object_write__parameter_checking),

      cmocka_unit_test(test__fl_fss_basic_list_content_read__parameter_checking),
      cmocka_unit_test(test__fl_fss_basic_list_content_write__parameter_checking),
      cmocka_unit_test(test__fl_fss_basic_list_object_read__parameter_checking),
      cmocka_unit_test(test__fl_fss_basic_list_object_write__parameter_checking),

      cmocka_unit_test(test__fl_fss_embedded_list_content_read__parameter_checking),
      cmocka_unit_test(test__fl_fss_embedded_list_content_write__parameter_checking),
      cmocka_unit_test(test__fl_fss_embedded_list_object_read__parameter_checking),
      cmocka_unit_test(test__fl_fss_embedded_list_object_write__parameter_checking),

      cmocka_unit_test(test__fl_fss_extended_content_read__parameter_checking),
      cmocka_unit_test(test__fl_fss_extended_content_write__parameter_checking),
      cmocka_unit_test(test__fl_fss_extended_object_read__parameter_checking),
      cmocka_unit_test(test__fl_fss_extended_object_write__parameter_checking),

      cmocka_unit_test(test__fl_fss_extended_list_content_read__parameter_checking),
      cmocka_unit_test(test__fl_fss_extended_list_content_write__parameter_checking),
      cmocka_unit_test(test__fl_fss_extended_list_object_read__parameter_checking),
      cmocka_unit_test(test__fl_fss_extended_list_object_write__parameter_checking),

      cmocka_unit_test(test__fl_fss_payload_header_map__parameter_checking),
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
