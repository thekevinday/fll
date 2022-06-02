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

    cmocka_unit_test(test__f_fss_items_decimate_by__returns_data_not),
    cmocka_unit_test(test__f_fss_items_decrease_by__returns_data_not),
    cmocka_unit_test(test__f_fss_items_increase__returns_data_not),
    cmocka_unit_test(test__f_fss_items_increase_by__returns_data_not),

    cmocka_unit_test(test__f_fss_named_decimate_by__returns_data_not),
    cmocka_unit_test(test__f_fss_named_decrease_by__returns_data_not),
    cmocka_unit_test(test__f_fss_named_increase__returns_data_not),
    cmocka_unit_test(test__f_fss_named_increase_by__returns_data_not),

    cmocka_unit_test(test__f_fss_nameds_decimate_by__returns_data_not),
    cmocka_unit_test(test__f_fss_nameds_decrease_by__returns_data_not),
    cmocka_unit_test(test__f_fss_nameds_increase__returns_data_not),
    cmocka_unit_test(test__f_fss_nameds_increase_by__returns_data_not),

    cmocka_unit_test(test__f_fss_nest_decimate_by__returns_data_not),
    cmocka_unit_test(test__f_fss_nest_decrease_by__returns_data_not),
    cmocka_unit_test(test__f_fss_nest_increase__returns_data_not),
    cmocka_unit_test(test__f_fss_nest_increase_by__returns_data_not),

    cmocka_unit_test(test__f_fss_nests_decimate_by__returns_data_not),
    cmocka_unit_test(test__f_fss_nests_decrease_by__returns_data_not),
    cmocka_unit_test(test__f_fss_nests_increase__returns_data_not),
    cmocka_unit_test(test__f_fss_nests_increase_by__returns_data_not),

    cmocka_unit_test(test__f_fss_set_decimate_by__returns_data_not),
    cmocka_unit_test(test__f_fss_set_decrease_by__returns_data_not),
    cmocka_unit_test(test__f_fss_set_increase__returns_data_not),
    cmocka_unit_test(test__f_fss_set_increase_by__returns_data_not),

    cmocka_unit_test(test__f_fss_set_quote_decimate_by__returns_data_not),
    cmocka_unit_test(test__f_fss_set_quote_decrease_by__returns_data_not),
    cmocka_unit_test(test__f_fss_set_quote_increase__returns_data_not),
    cmocka_unit_test(test__f_fss_set_quote_increase_by__returns_data_not),

    cmocka_unit_test(test__f_fss_set_quotes_decimate_by__returns_data_not),
    cmocka_unit_test(test__f_fss_set_quotes_decrease_by__returns_data_not),
    cmocka_unit_test(test__f_fss_set_quotes_increase__returns_data_not),
    cmocka_unit_test(test__f_fss_set_quotes_increase_by__returns_data_not),

    cmocka_unit_test(test__f_fss_sets_decimate_by__returns_data_not),
    cmocka_unit_test(test__f_fss_sets_decrease_by__returns_data_not),
    cmocka_unit_test(test__f_fss_sets_increase__returns_data_not),
    cmocka_unit_test(test__f_fss_sets_increase_by__returns_data_not),

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

      cmocka_unit_test(test__f_fss_items_adjust__parameter_checking),
      cmocka_unit_test(test__f_fss_items_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_fss_items_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_fss_items_increase__parameter_checking),
      cmocka_unit_test(test__f_fss_items_increase_by__parameter_checking),
      cmocka_unit_test(test__f_fss_items_resize__parameter_checking),

      cmocka_unit_test(test__f_fss_named_adjust__parameter_checking),
      cmocka_unit_test(test__f_fss_named_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_fss_named_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_fss_named_increase__parameter_checking),
      cmocka_unit_test(test__f_fss_named_increase_by__parameter_checking),
      cmocka_unit_test(test__f_fss_named_resize__parameter_checking),

      cmocka_unit_test(test__f_fss_nameds_adjust__parameter_checking),
      cmocka_unit_test(test__f_fss_nameds_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_fss_nameds_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_fss_nameds_increase__parameter_checking),
      cmocka_unit_test(test__f_fss_nameds_increase_by__parameter_checking),
      cmocka_unit_test(test__f_fss_nameds_resize__parameter_checking),

      cmocka_unit_test(test__f_fss_nest_adjust__parameter_checking),
      cmocka_unit_test(test__f_fss_nest_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_fss_nest_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_fss_nest_increase__parameter_checking),
      cmocka_unit_test(test__f_fss_nest_increase_by__parameter_checking),
      cmocka_unit_test(test__f_fss_nest_resize__parameter_checking),

      cmocka_unit_test(test__f_fss_nests_adjust__parameter_checking),
      cmocka_unit_test(test__f_fss_nests_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_fss_nests_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_fss_nests_increase__parameter_checking),
      cmocka_unit_test(test__f_fss_nests_increase_by__parameter_checking),
      cmocka_unit_test(test__f_fss_nests_resize__parameter_checking),

      cmocka_unit_test(test__f_fss_set_adjust__parameter_checking),
      cmocka_unit_test(test__f_fss_set_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_fss_set_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_fss_set_increase__parameter_checking),
      cmocka_unit_test(test__f_fss_set_increase_by__parameter_checking),
      cmocka_unit_test(test__f_fss_set_resize__parameter_checking),

      cmocka_unit_test(test__f_fss_set_quote_adjust__parameter_checking),
      cmocka_unit_test(test__f_fss_set_quote_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_fss_set_quote_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_fss_set_quote_increase__parameter_checking),
      cmocka_unit_test(test__f_fss_set_quote_increase_by__parameter_checking),
      cmocka_unit_test(test__f_fss_set_quote_resize__parameter_checking),

      cmocka_unit_test(test__f_fss_set_quotes_adjust__parameter_checking),
      cmocka_unit_test(test__f_fss_set_quotes_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_fss_set_quotes_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_fss_set_quotes_increase__parameter_checking),
      cmocka_unit_test(test__f_fss_set_quotes_increase_by__parameter_checking),
      cmocka_unit_test(test__f_fss_set_quotes_resize__parameter_checking),

      cmocka_unit_test(test__f_fss_sets_adjust__parameter_checking),
      cmocka_unit_test(test__f_fss_sets_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_fss_sets_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_fss_sets_increase__parameter_checking),
      cmocka_unit_test(test__f_fss_sets_increase_by__parameter_checking),
      cmocka_unit_test(test__f_fss_sets_resize__parameter_checking),
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
