#include "test-fss.h"
#include "test-fss-extended_list_content_write.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__fl_fss_extended_list_content_write__parameter_checking(void **void_state) {

  f_state_t state = f_state_t_initialize;
  f_range_t range = f_range_t_initialize;
  f_ranges_t ignore = f_ranges_t_initialize;
  f_string_dynamic_t destination = f_string_dynamic_t_initialize;

  {
    state.status = F_none;

    fl_fss_extended_list_content_write(f_string_empty_s, 0, 0, 0, 0, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_extended_list_content_write(f_string_empty_s, 0, &f_string_empty_s, 0, 0, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_extended_list_content_write(f_string_empty_s, 0, &f_string_empty_s, &ignore, 0, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_extended_list_content_write(f_string_empty_s, 0, &f_string_empty_s, &ignore, &range, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_extended_list_content_write(f_string_empty_s, 0, &f_string_empty_s, &ignore, 0, &destination, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_extended_list_content_write(f_string_empty_s, 0, &f_string_empty_s, 0, &range, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_extended_list_content_write(f_string_empty_s, 0, &f_string_empty_s, 0, 0, &destination, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_extended_list_content_write(f_string_empty_s, 0, 0, &ignore, 0, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_extended_list_content_write(f_string_empty_s, 0, 0, &ignore, &range, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_extended_list_content_write(f_string_empty_s, 0, 0, &ignore, 0, &destination, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_extended_list_content_write(f_string_empty_s, 0, 0, 0, &range, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_extended_list_content_write(f_string_empty_s, 0, 0, 0, 0, &destination, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  if (destination.string) {
    free(destination.string);
  }
}

void test__fl_fss_extended_list_content_write__returns_data_not(void **void_state) {

  f_state_t state = f_state_t_initialize;
  f_range_t range = f_range_t_initialize;
  f_ranges_t ignore = f_ranges_t_initialize;
  f_string_dynamic_t destination = f_string_dynamic_t_initialize;

  {
    state.status = F_none;

    fl_fss_extended_list_content_write(f_string_empty_s, 0, 0, 0, &range, &destination, &state);

    assert_int_equal(state.status, F_data_not);
  }

  {
    state.status = F_none;

    fl_fss_extended_list_content_write(f_string_empty_s, 0, &f_string_empty_s, 0, &range, &destination, &state);

    assert_int_equal(state.status, F_data_not);
  }

  {
    state.status = F_none;

    fl_fss_extended_list_content_write(f_string_empty_s, 0, 0, &ignore, &range, &destination, &state);

    assert_int_equal(state.status, F_data_not);
  }

  {
    state.status = F_none;

    fl_fss_extended_list_content_write(f_string_empty_s, 0, &f_string_empty_s, &ignore, &range, &destination, &state);

    assert_int_equal(state.status, F_data_not);
  }

  if (destination.string) {
    free(destination.string);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif