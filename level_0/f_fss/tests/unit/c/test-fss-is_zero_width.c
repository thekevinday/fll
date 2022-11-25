#include "test-fss.h"
#include "test-fss-is_zero_width.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_is_zero_width__works(void **state) {

  f_state_t state_data = f_state_t_initialize;

  f_string_static_t tests[] = {
    macro_f_string_static_t_initialize("\0", 0, 1),
    macro_f_string_static_t_initialize("\a", 0, 1),
    macro_f_string_static_t_initialize("\t", 0, 1),
    macro_f_string_static_t_initialize("\n", 0, 1),
    macro_f_string_static_t_initialize(" ", 0, 1),
    macro_f_string_static_t_initialize("⸙", 0, 3),
    macro_f_string_static_t_initialize("t", 0, 1),
    macro_f_string_static_t_initialize("全", 0, 3),
    macro_f_string_static_t_initialize("$", 0, 1),
    macro_f_string_static_t_initialize(".", 0, 1),
    macro_f_string_static_t_initialize(" ́", 0, 3), // Space followed by a combining character (U+0020 U+0301).
    macro_f_string_static_t_initialize(" ॐ", 0, 5), // Space followed by a printing character (U+0020 U+0061).
    macro_f_string_static_t_initialize("​", 0, 3), // Zero-width space (U+200B).
    macro_f_string_static_t_initialize("a b", 0, 3),
  };

  f_status_t expects[] = {
    F_true,
    F_true,
    F_false,
    F_false,
    F_false,
    F_false,
    F_false,
    F_false,
    F_false,
    F_false,
    F_true,
    F_false,
    F_true,
    F_false,
  };

  // Use range to designate which part of a string is to be tested.
  f_string_range_t ranges[] = {
    { .start = 0, .stop = tests[0].used },
    { .start = 0, .stop = tests[1].used },
    { .start = 0, .stop = tests[2].used },
    { .start = 0, .stop = tests[3].used },
    { .start = 0, .stop = tests[4].used },
    { .start = 0, .stop = tests[5].used },
    { .start = 0, .stop = tests[6].used },
    { .start = 0, .stop = tests[7].used },
    { .start = 0, .stop = tests[8].used },
    { .start = 0, .stop = tests[9].used },
    { .start = 1, .stop = tests[10].used },
    { .start = 1, .stop = tests[11].used },
    { .start = 0, .stop = tests[12].used },
    { .start = 1, .stop = 1 },
  };

  for (f_array_length_t i = 0; i < 14; ++i) {

    const f_status_t status = f_fss_is_zero_width(state_data, tests[i], ranges[i]);

    assert_int_equal(status, expects[i]);
  } // for

  {
    const f_string_range_t range = f_string_range_t_initialize;

    const f_status_t status = f_fss_is_zero_width(state_data, f_string_empty_s, range);

    assert_int_equal(status, F_false);
  }

  {
    const f_string_range_t range = macro_f_string_range_t_initialize(0, 2);

    const f_status_t status = f_fss_is_zero_width(state_data, f_string_empty_s, range);

    assert_int_equal(status, F_false);
  }

  {
    const f_string_static_t test = macro_f_string_static_t_initialize("test", 0, 4);
    const f_string_range_t range = f_string_range_t_initialize;

    const f_status_t status = f_fss_is_zero_width(state_data, test, range);

    assert_int_equal(status, F_false);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
