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
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_signed__works_combined),
    cmocka_unit_test(test__fl_fss_payload_header_map__abstruse_unsigned__works_combined),

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
