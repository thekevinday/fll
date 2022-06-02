#include "test-fss.h"
#include "test-fss-seek_to_eol.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_seek_to_eol__parameter_checking(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize("test", 0, 4);
  f_state_t state_data = f_state_t_initialize;

  {
    const f_status_t status = f_fss_seek_to_eol(state_data, test, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_fss_seek_to_eol__returns_data_not(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize("test", 0, 4);
  f_state_t state_data = f_state_t_initialize;

  {
    f_string_range_t range = f_string_range_t_initialize;
    const f_status_t status = f_fss_seek_to_eol(state_data, f_string_empty_s, &range);

    assert_int_equal(status, F_data_not);
  }

  {
    f_string_range_t range = f_string_range_t_initialize;
    const f_status_t status = f_fss_seek_to_eol(state_data, test, &range);

    assert_int_equal(status, F_data_not);
  }

  {
    f_string_range_t range = macro_f_string_range_t_initialize(0, 1);
    const f_status_t status = f_fss_seek_to_eol(state_data, f_string_empty_s, &range);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_fss_seek_to_eol__works(void **state) {

  f_state_t state_data = f_state_t_initialize;

  f_string_static_t tests[] = {
    macro_f_string_static_t_initialize("  ", 0, 2),
    macro_f_string_static_t_initialize("\0\0", 0, 2),
    macro_f_string_static_t_initialize("\n\n", 0, 2),
    macro_f_string_static_t_initialize("  \ntest", 0, 7),
    macro_f_string_static_t_initialize("test\ntest\n", 0, 6),
    macro_f_string_static_t_initialize("\ntest\n\n", 0, 7),
    macro_f_string_static_t_initialize("  ", 0, 2),
    macro_f_string_static_t_initialize("\0\0", 0, 2),
    macro_f_string_static_t_initialize("\n\n", 0, 2),
    macro_f_string_static_t_initialize("  \ntest", 0, 7),
    macro_f_string_static_t_initialize("test\ntest\n", 0, 6),
    macro_f_string_static_t_initialize("\ntest\n\n", 0, 7),
  };

  f_string_range_t ranges[] = {
    macro_f_string_range_t_initialize(0, tests[0].used - 1),
    macro_f_string_range_t_initialize(0, tests[1].used - 1),
    macro_f_string_range_t_initialize(0, tests[2].used - 1),
    macro_f_string_range_t_initialize(0, tests[3].used - 1),
    macro_f_string_range_t_initialize(0, tests[4].used - 1),
    macro_f_string_range_t_initialize(0, tests[5].used - 1),
    macro_f_string_range_t_initialize(0, tests[6].used - 2),
    macro_f_string_range_t_initialize(0, tests[7].used - 2),
    macro_f_string_range_t_initialize(0, tests[8].used - 2),
    macro_f_string_range_t_initialize(0, tests[9].used - 2),
    macro_f_string_range_t_initialize(0, tests[10].used - 2),
    macro_f_string_range_t_initialize(1, tests[11].used - 2),
  };

  f_array_length_t expects[] = {
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

    const f_status_t status = f_fss_seek_to_eol(state_data, tests[i], &range);

    assert_int_equal(status, statuss[i]);
    assert_int_equal(range.start, expects[i]);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
