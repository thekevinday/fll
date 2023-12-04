#include "test-fss.h"
#include "test-fss-is_combining.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_is_combining__works(void **state) {

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
    macro_f_string_static_t_initialize_1(" ́", 0, 3),
  };

  f_status_t expects[] = {
    F_false,
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
  f_number_unsigned_t offset[] = {
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
  };

  for (f_number_unsigned_t i = 0; i < 11; ++i) {

    const f_range_t range = macro_f_range_t_initialize_1(offset[i], tests[i].used - 1);

    const f_status_t status = f_fss_is_combining(tests[i], range, &state_data);

    assert_int_equal(status, expects[i]);
  } // for

  {
    const f_range_t range = f_range_t_initialize;

    const f_status_t status = f_fss_is_combining(f_string_empty_s, range, &state_data);

    assert_int_equal(status, F_false);
  }

  {
    const f_range_t range = macro_f_range_t_initialize_1(0, 2);

    const f_status_t status = f_fss_is_combining(f_string_empty_s, range, &state_data);

    assert_int_equal(status, F_false);
  }

  {
    const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);
    const f_range_t range = f_range_t_initialize;

    const f_status_t status = f_fss_is_combining(test, range, &state_data);

    assert_int_equal(status, F_false);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
