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
    macro_f_string_static_t_initialize("​", 0, 3), // Zero-width space (U+200B).
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
    F_false,
    F_true,
  };

  // Apply an offset so that the combining character is combining into something inside the quotes rather than the quotes for convenience and code safety.
  f_array_length_t offset[] = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    1,
    0,
  };

  for (f_array_length_t i = 0; i < 12; ++i) {

    const f_string_range_t range = macro_f_string_range_t_initialize(offset[i], tests[i].used - 1);

    const f_status_t status = f_fss_is_zero_width(state_data, tests[i], range);

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
