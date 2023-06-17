#include "test-fss.h"
#include "test-fss-is_space.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_is_space__works(void **state) {

  f_state_t state_data = f_state_t_initialize;

  f_string_static_t tests[] = {
    macro_f_string_static_t_initialize_1("\0", 0, 1),
    macro_f_string_static_t_initialize_1("\a", 0, 1),
    macro_f_string_static_t_initialize_1("\t", 0, 1),
    macro_f_string_static_t_initialize_1("\n", 0, 1),
    macro_f_string_static_t_initialize_1(" ", 0, 1),
    macro_f_string_static_t_initialize_1("⸙", 0, 3),
    macro_f_string_static_t_initialize_1("t", 0, 1),
    macro_f_string_static_t_initialize_1("全", 0, 3),
    macro_f_string_static_t_initialize_1("$", 0, 1),
    macro_f_string_static_t_initialize_1(".", 0, 1),
    macro_f_string_static_t_initialize_1(" ́", 0, 3), // Space followed by a combining character (U+0020 U+0301).
    macro_f_string_static_t_initialize_1("​", 0, 3), // Zero-width space (U+200B).
  };

  f_status_t expects[] = {
    F_false,
    F_false,
    F_true,
    F_true,
    F_true,
    F_false,
    F_false,
    F_false,
    F_false,
    F_false,
    F_true,
    F_false,
  };

  for (f_number_unsigned_t i = 0; i < 12; ++i) {

    const f_string_range_t range = macro_f_string_range_t_initialize_1(0, tests[i].used - 1);

    const f_status_t status = f_fss_is_space(tests[i], range, &state_data);

    assert_int_equal(status, expects[i]);
  } // for

  {
    const f_string_range_t range = f_string_range_t_initialize;

    const f_status_t status = f_fss_is_space(f_string_empty_s, range, &state_data);

    assert_int_equal(status, F_false);
  }

  {
    const f_string_range_t range = macro_f_string_range_t_initialize_1(0, 2);

    const f_status_t status = f_fss_is_space(f_string_empty_s, range, &state_data);

    assert_int_equal(status, F_false);
  }

  {
    const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);
    const f_string_range_t range = f_string_range_t_initialize;

    const f_status_t status = f_fss_is_space(test, range, &state_data);

    assert_int_equal(status, F_false);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
