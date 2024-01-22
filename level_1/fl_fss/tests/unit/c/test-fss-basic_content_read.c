#include "test-fss.h"
#include "test-fss-basic_content_read.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__fl_fss_basic_content_read__parameter_checking(void **void_state) {

  f_state_t state = f_state_t_initialize;
  f_range_t range = f_range_t_initialize;
  f_ranges_t found = f_ranges_t_initialize;
  f_number_unsigneds_t delimits = f_number_unsigneds_t_initialize;

  {
    state.status = F_none;

    fl_fss_basic_content_read(f_string_empty_s, 0, 0, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_basic_content_read(f_string_empty_s, &range, 0, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_basic_content_read(f_string_empty_s, &range, &found, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_basic_content_read(f_string_empty_s, &range, 0, &delimits, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_basic_content_read(f_string_empty_s, 0, &found, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_basic_content_read(f_string_empty_s, 0, &found, &delimits, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;

    fl_fss_basic_content_read(f_string_empty_s, 0, 0, &delimits, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }
}

void test__fl_fss_basic_content_read__returns_data_not(void **void_state) {

  f_state_t state = f_state_t_initialize;
  f_range_t range = f_range_t_initialize;
  f_ranges_t found = f_ranges_t_initialize;
  f_number_unsigneds_t delimits = f_number_unsigneds_t_initialize;

  {
    state.status = F_none;

    fl_fss_basic_content_read(f_string_empty_s, &range, &found, &delimits, &state);

    assert_int_equal(state.status, F_data_not);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
