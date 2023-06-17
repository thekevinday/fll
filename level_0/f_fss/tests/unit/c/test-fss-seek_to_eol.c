#include "test-fss.h"
#include "test-fss-seek_to_eol.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_seek_to_eol__parameter_checking(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);
  f_state_t state_data = f_state_t_initialize;

  {
    f_fss_seek_to_eol(test, 0, &state_data);

    assert_int_equal(state_data.status, F_status_set_error(F_parameter));
  }
}

void test__f_fss_seek_to_eol__returns_data_not(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);
  f_state_t state_data = f_state_t_initialize;

  {
    f_string_range_t range = f_string_range_t_initialize;

    f_fss_seek_to_eol(f_string_empty_s, &range, &state_data);

    assert_int_equal(state_data.status, F_data_not);
  }

  {
    f_string_range_t range = f_string_range_t_initialize;

    f_fss_seek_to_eol(test, &range, &state_data);

    assert_int_equal(state_data.status, F_data_not);
  }

  {
    f_string_range_t range = macro_f_string_range_t_initialize_1(0, 1);

    f_fss_seek_to_eol(f_string_empty_s, &range, &state_data);

    assert_int_equal(state_data.status, F_data_not);
  }
}

void test__f_fss_seek_to_eol__works(void **state) {

  f_state_t state_data = f_state_t_initialize;

  f_string_static_t tests[] = {
    macro_f_string_static_t_initialize_1("  ", 0, 2),
    macro_f_string_static_t_initialize_1("\0\0", 0, 2),
    macro_f_string_static_t_initialize_1("\n\n", 0, 2),
    macro_f_string_static_t_initialize_1("  \ntest", 0, 7),
    macro_f_string_static_t_initialize_1("test\ntest\n", 0, 6),
    macro_f_string_static_t_initialize_1("\ntest\n\n", 0, 7),
    macro_f_string_static_t_initialize_1("  ", 0, 2),
    macro_f_string_static_t_initialize_1("\0\0", 0, 2),
    macro_f_string_static_t_initialize_1("\n\n", 0, 2),
    macro_f_string_static_t_initialize_1("  \ntest", 0, 7),
    macro_f_string_static_t_initialize_1("test\ntest\n", 0, 6),
    macro_f_string_static_t_initialize_1("\ntest\n\n", 0, 7),
  };

  f_string_range_t ranges[] = {
    macro_f_string_range_t_initialize_1(0, tests[0].used - 1),
    macro_f_string_range_t_initialize_1(0, tests[1].used - 1),
    macro_f_string_range_t_initialize_1(0, tests[2].used - 1),
    macro_f_string_range_t_initialize_1(0, tests[3].used - 1),
    macro_f_string_range_t_initialize_1(0, tests[4].used - 1),
    macro_f_string_range_t_initialize_1(0, tests[5].used - 1),
    macro_f_string_range_t_initialize_1(0, tests[6].used - 2),
    macro_f_string_range_t_initialize_1(0, tests[7].used - 2),
    macro_f_string_range_t_initialize_1(0, tests[8].used - 2),
    macro_f_string_range_t_initialize_1(0, tests[9].used - 2),
    macro_f_string_range_t_initialize_1(0, tests[10].used - 2),
    macro_f_string_range_t_initialize_1(1, tests[11].used - 2),
  };

  f_number_unsigned_t expects[] = {
    2,
    2,
    0,
    2,
    4,
    0,
    1,
    1,
    0,
    2,
    4,
    5,
  };

  f_status_t statuss[] = {
    F_none_eos,
    F_none_eos,
    F_none,
    F_none,
    F_none,
    F_none,
    F_none_stop,
    F_none_stop,
    F_none,
    F_none,
    F_none,
    F_none,
  };

  for (uint8_t i = 0; i < 12; ++i) {

    f_string_range_t range = ranges[i];

    f_fss_seek_to_eol(tests[i], &range, &state_data);

    assert_int_equal(state_data.status, statuss[i]);
    assert_int_equal(range.start, expects[i]);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
