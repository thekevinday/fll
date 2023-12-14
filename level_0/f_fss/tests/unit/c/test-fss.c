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
    cmocka_unit_test(test__f_fss_apply_delimit__returns_data_not),
    cmocka_unit_test(test__f_fss_apply_delimit_range__returns_data_not),
    cmocka_unit_test(test__f_fss_count_lines__returns_data_not),
    cmocka_unit_test(test__f_fss_count_lines_range__returns_data_not),
    cmocka_unit_test(test__f_fss_seek_to_eol__returns_data_not),
    cmocka_unit_test(test__f_fss_skip_past_delimit__returns_data_not),
    cmocka_unit_test(test__f_fss_skip_past_space__returns_data_not),

    cmocka_unit_test(test__f_fss_apply_delimit__works),
    cmocka_unit_test(test__f_fss_apply_delimit_range__works),
    cmocka_unit_test(test__f_fss_count_lines__works),
    cmocka_unit_test(test__f_fss_count_lines_range__works),
    cmocka_unit_test(test__f_fss_is_combining__works),
    cmocka_unit_test(test__f_fss_is_graph__works),
    cmocka_unit_test(test__f_fss_is_space__works),
    cmocka_unit_test(test__f_fss_is_zero_width__works),
    cmocka_unit_test(test__f_fss_seek_to_eol__works),
    cmocka_unit_test(test__f_fss_skip_past_delimit__works),
    cmocka_unit_test(test__f_fss_skip_past_space__works),

    cmocka_unit_test(test__f_fss_fail_utf__works_for_error),
    cmocka_unit_test(test__f_fss_fail_utf_to_false__works_for_error),

    cmocka_unit_test(test__f_fss_fail_utf__works_for_no_error),
    cmocka_unit_test(test__f_fss_fail_utf_to_false__works_for_no_error),

    cmocka_unit_test(test__f_fss_item_delete__fails),
    cmocka_unit_test(test__f_fss_item_destroy__fails),
    cmocka_unit_test(test__f_fss_items_delete_callback__fails),
    cmocka_unit_test(test__f_fss_items_destroy_callback__fails),
    cmocka_unit_test(test__f_fss_itemss_delete_callback__fails),
    cmocka_unit_test(test__f_fss_itemss_destroy_callback__fails),

    cmocka_unit_test(test__f_fss_item_delete__works),
    cmocka_unit_test(test__f_fss_item_destroy__works),
    cmocka_unit_test(test__f_fss_items_delete_callback__works),
    cmocka_unit_test(test__f_fss_items_destroy_callback__works),
    cmocka_unit_test(test__f_fss_itemss_delete_callback__works),
    cmocka_unit_test(test__f_fss_itemss_destroy_callback__works),

    cmocka_unit_test(test__f_fss_named_delete__fails),
    cmocka_unit_test(test__f_fss_named_destroy__fails),
    cmocka_unit_test(test__f_fss_nameds_delete_callback__fails),
    cmocka_unit_test(test__f_fss_nameds_destroy_callback__fails),
    cmocka_unit_test(test__f_fss_namedss_delete_callback__fails),
    cmocka_unit_test(test__f_fss_namedss_destroy_callback__fails),

    cmocka_unit_test(test__f_fss_named_delete__works),
    cmocka_unit_test(test__f_fss_named_destroy__works),
    cmocka_unit_test(test__f_fss_nameds_delete_callback__works),
    cmocka_unit_test(test__f_fss_nameds_destroy_callback__works),
    cmocka_unit_test(test__f_fss_namedss_delete_callback__works),
    cmocka_unit_test(test__f_fss_namedss_destroy_callback__works),

    cmocka_unit_test(test__f_fss_nest_delete__fails),
    cmocka_unit_test(test__f_fss_nest_destroy__fails),
    cmocka_unit_test(test__f_fss_nests_delete_callback__fails),
    cmocka_unit_test(test__f_fss_nests_destroy_callback__fails),
    cmocka_unit_test(test__f_fss_nestss_delete_callback__fails),
    cmocka_unit_test(test__f_fss_nestss_destroy_callback__fails),

    cmocka_unit_test(test__f_fss_nest_delete__works),
    cmocka_unit_test(test__f_fss_nest_destroy__works),
    cmocka_unit_test(test__f_fss_nests_delete_callback__works),
    cmocka_unit_test(test__f_fss_nests_destroy_callback__works),
    cmocka_unit_test(test__f_fss_nestss_delete_callback__works),
    cmocka_unit_test(test__f_fss_nestss_destroy_callback__works),

    cmocka_unit_test(test__f_fss_set_delete__fails),
    cmocka_unit_test(test__f_fss_set_destroy__fails),
    cmocka_unit_test(test__f_fss_sets_delete_callback__fails),
    cmocka_unit_test(test__f_fss_sets_destroy_callback__fails),
    cmocka_unit_test(test__f_fss_setss_delete_callback__fails),
    cmocka_unit_test(test__f_fss_setss_destroy_callback__fails),

    cmocka_unit_test(test__f_fss_set_delete__works),
    cmocka_unit_test(test__f_fss_set_destroy__works),
    cmocka_unit_test(test__f_fss_sets_delete_callback__works),
    cmocka_unit_test(test__f_fss_sets_destroy_callback__works),
    cmocka_unit_test(test__f_fss_setss_delete_callback__works),
    cmocka_unit_test(test__f_fss_setss_destroy_callback__works),

    cmocka_unit_test(test__f_fss_set_quote_delete__fails),
    cmocka_unit_test(test__f_fss_set_quote_destroy__fails),
    cmocka_unit_test(test__f_fss_set_quotes_delete_callback__fails),
    cmocka_unit_test(test__f_fss_set_quotes_destroy_callback__fails),
    cmocka_unit_test(test__f_fss_set_quotess_delete_callback__fails),
    cmocka_unit_test(test__f_fss_set_quotess_destroy_callback__fails),

    cmocka_unit_test(test__f_fss_set_quote_delete__works),
    cmocka_unit_test(test__f_fss_set_quote_destroy__works),
    cmocka_unit_test(test__f_fss_set_quotes_delete_callback__works),
    cmocka_unit_test(test__f_fss_set_quotes_destroy_callback__works),
    cmocka_unit_test(test__f_fss_set_quotess_delete_callback__works),
    cmocka_unit_test(test__f_fss_set_quotess_destroy_callback__works),

    cmocka_unit_test(test__f_fss_simple_packet_delete__fails),
    cmocka_unit_test(test__f_fss_simple_packet_destroy__fails),
    cmocka_unit_test(test__f_fss_simple_packets_delete_callback__fails),
    cmocka_unit_test(test__f_fss_simple_packets_destroy_callback__fails),
    cmocka_unit_test(test__f_fss_simple_packetss_delete_callback__fails),
    cmocka_unit_test(test__f_fss_simple_packetss_destroy_callback__fails),

    cmocka_unit_test(test__f_fss_simple_packet_delete__works),
    cmocka_unit_test(test__f_fss_simple_packet_destroy__works),
    cmocka_unit_test(test__f_fss_simple_packets_delete_callback__works),
    cmocka_unit_test(test__f_fss_simple_packets_destroy_callback__works),
    cmocka_unit_test(test__f_fss_simple_packetss_delete_callback__works),
    cmocka_unit_test(test__f_fss_simple_packetss_destroy_callback__works),

    cmocka_unit_test(test__f_fss_simple_packet_encode__works_little_endian),
    cmocka_unit_test(test__f_fss_simple_packet_extract__works_little_endian),
    cmocka_unit_test(test__f_fss_simple_packet_extract_range__works_little_endian),

    cmocka_unit_test(test__f_fss_simple_packet_extract__works_big_endian),
    cmocka_unit_test(test__f_fss_simple_packet_extract_range__works_big_endian),
    cmocka_unit_test(test__f_fss_simple_packet_encode__works_big_endian),

    cmocka_unit_test(test__f_fss_simple_packet_extract__returns_packet_too_small),
    cmocka_unit_test(test__f_fss_simple_packet_extract_range__returns_packet_too_small),

    #ifndef _di_level_0_parameter_checking_
      cmocka_unit_test(test__f_fss_apply_delimit__parameter_checking),
      cmocka_unit_test(test__f_fss_apply_delimit_range__parameter_checking),
      cmocka_unit_test(test__f_fss_count_lines__parameter_checking),
      cmocka_unit_test(test__f_fss_count_lines_range__parameter_checking),
      // f_fss_fail_utf() doesn't use parameter checking.
      // f_fss_fail_utf_false() doesn't use parameter checking.
      // f_fss_is_combining() doesn't use parameter checking.
      // f_fss_is_graph() doesn't use parameter checking.
      // f_fss_is_space() doesn't use parameter checking.
      // f_fss_is_zero_width() doesn't use parameter checking.
      cmocka_unit_test(test__f_fss_seek_to_eol__parameter_checking),
      cmocka_unit_test(test__f_fss_skip_past_delimit__parameter_checking),
      cmocka_unit_test(test__f_fss_skip_past_space__parameter_checking),

      cmocka_unit_test(test__f_fss_item_delete__parameter_checking),
      cmocka_unit_test(test__f_fss_item_destroy__parameter_checking),

      cmocka_unit_test(test__f_fss_named_delete__parameter_checking),
      cmocka_unit_test(test__f_fss_named_destroy__parameter_checking),

      cmocka_unit_test(test__f_fss_named_delete__parameter_checking),
      cmocka_unit_test(test__f_fss_named_destroy__parameter_checking),

      cmocka_unit_test(test__f_fss_set_delete__parameter_checking),
      cmocka_unit_test(test__f_fss_set_destroy__parameter_checking),

      cmocka_unit_test(test__f_fss_set_quote_delete__parameter_checking),
      cmocka_unit_test(test__f_fss_set_quote_destroy__parameter_checking),

      cmocka_unit_test(test__f_fss_simple_packet_delete__parameter_checking),
      cmocka_unit_test(test__f_fss_simple_packet_destroy__parameter_checking),
      cmocka_unit_test(test__f_fss_simple_packet_encode__parameter_checking),
      cmocka_unit_test(test__f_fss_simple_packet_extract__parameter_checking),
      cmocka_unit_test(test__f_fss_simple_packet_extract_range__parameter_checking),

      // f_fss_items_delete_callback() doesn't use parameter checking.
      // f_fss_items_destroy_callback() doesn't use parameter checking.
      // f_fss_itemss_delete_callback() doesn't use parameter checking.
      // f_fss_itemss_destroy_callback() doesn't use parameter checking.
      // f_fss_nameds_delete_callback() doesn't use parameter checking.
      // f_fss_nameds_destroy_callback() doesn't use parameter checking.
      // f_fss_namedss_delete_callback() doesn't use parameter checking.
      // f_fss_namedss_destroy_callback() doesn't use parameter checking.
      // f_fss_nests_delete_callback() doesn't use parameter checking.
      // f_fss_nests_destroy_callback() doesn't use parameter checking.
      // f_fss_nestss_delete_callback() doesn't use parameter checking.
      // f_fss_nestss_destroy_callback() doesn't use parameter checking.
      // f_fss_sets_delete_callback() doesn't use parameter checking.
      // f_fss_sets_destroy_callback() doesn't use parameter checking.
      // f_fss_setss_delete_callback() doesn't use parameter checking.
      // f_fss_setss_destroy_callback() doesn't use parameter checking.
      // f_fss_set_quotes_delete_callback() doesn't use parameter checking.
      // f_fss_set_quotes_destroy_callback() doesn't use parameter checking.
      // f_fss_set_quotess_delete_callback() doesn't use parameter checking.
      // f_fss_set_quotess_destroy_callback() doesn't use parameter checking.
      // f_fss_simple_packets_delete_callback() doesn't use parameter checking.
      // f_fss_simple_packets_destroy_callback() doesn't use parameter checking.
      // f_fss_simple_packetss_delete_callback() doesn't use parameter checking.
      // f_fss_simple_packetss_destroy_callback() doesn't use parameter checking.
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
