#include "test-fss.h"
#include "test-fss-skip_past_space.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_skip_past_space__parameter_checking(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);
  f_state_t state_data = f_state_t_initialize;

  {
    const f_status_t status = f_fss_skip_past_space(state_data, test, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_fss_skip_past_space__returns_data_not(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);
  f_state_t state_data = f_state_t_initialize;

  {
    f_string_range_t range = f_string_range_t_initialize;

    const f_status_t status = f_fss_skip_past_space(state_data, f_string_empty_s, &range);

    assert_int_equal(status, F_data_not);
  }

  {
    f_string_range_t range = f_string_range_t_initialize;

    const f_status_t status = f_fss_skip_past_space(state_data, test, &range);

    assert_int_equal(status, F_data_not);
  }

  {
    f_string_range_t range = macro_f_string_range_t_initialize_1(0, test.used - 1);

    const f_status_t status = f_fss_skip_past_space(state_data, f_string_empty_s, &range);

    assert_int_equal(status, F_data_not);
  }

  {
    f_string_range_t range = macro_f_string_range_t_initialize_1(test.used, test.used + 2);

    const f_status_t status = f_fss_skip_past_space(state_data, test, &range);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_fss_skip_past_space__works(void **state) {

  f_state_t state_data = f_state_t_initialize;

  f_string_static_t tests[] = {
    macro_f_string_static_t_initialize_1("test", 0, 4),
    macro_f_string_static_t_initialize_1(" test", 0, 5),
    macro_f_string_static_t_initialize_1("   test", 0, 7),
    macro_f_string_static_t_initialize_1("  \0test  ", 0, 9),
    macro_f_string_static_t_initialize_1(" \t\atest  ", 0, 9),
    macro_f_string_static_t_initialize_1("\a\t $test  ", 0, 10),
    macro_f_string_static_t_initialize_1(" ́test", 0, 7),
  };

  f_array_length_t expects[] = {
    0,
    1,
    3,
    3,
    3,
    3,
    3,
  };

  for (uint8_t i = 0; i < 7; ++i) {

    f_string_range_t range = macro_f_string_range_t_initialize_1(0, tests[i].used - 1);

    const f_status_t status = f_fss_skip_past_space(state_data, tests[i], &range);

    assert_int_equal(status, F_none);
    assert_int_equal(range.start, expects[i]);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
