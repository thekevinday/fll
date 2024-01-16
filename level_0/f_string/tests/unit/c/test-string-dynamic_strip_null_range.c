#include "test-string.h"
#include "test-string-dynamic_strip_null_range.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_string_dynamic_strip_null_range__returns_data_not(void **state) {

  f_string_static_t buffer = f_string_static_t_initialize;
  const f_range_t range = macro_f_range_t_initialize_1(0, 0);

  {
    const f_status_t status = f_string_dynamic_strip_null_range(range, &buffer);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_string_dynamic_strip_null_range__returns_data_not_eos(void **state) {

  f_string_static_t buffer = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_range_t range = macro_f_range_t_initialize_1(buffer.used, buffer.used);

  {
    const f_status_t status = f_string_dynamic_strip_null_range(range, &buffer);

    assert_int_equal(status, F_data_not_eos);
  }
}

void test__f_string_dynamic_strip_null_range__returns_data_not_stop(void **state) {

  f_string_static_t buffer = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_range_t range = f_range_t_initialize;

  {
    const f_status_t status = f_string_dynamic_strip_null_range(range, &buffer);

    assert_int_equal(status, F_data_not_stop);
  }
}

void test__f_string_dynamic_strip_null_range__works(void **state) {

  const f_string_static_t sources[] = {

    // First Set.
    macro_f_string_static_t_initialize_1("test", 0, 4),
    macro_f_string_static_t_initialize_1("test", 0, 5),
    macro_f_string_static_t_initialize_1("te\0st", 0, 5),
    macro_f_string_static_t_initialize_1("te\0st", 0, 6),
    macro_f_string_static_t_initialize_1("te\0\0st", 0, 6),
    macro_f_string_static_t_initialize_1("te\0\0st", 0, 7),
    macro_f_string_static_t_initialize_1("te\0\0s\0t", 0, 7),
    macro_f_string_static_t_initialize_1("te\0\0s\0t", 0, 8),
    macro_f_string_static_t_initialize_1("te\0\0s\0\0\0t", 0, 9),
    macro_f_string_static_t_initialize_1("te\0\0s\0\0\0t", 0, 10),

    // Second Set.
    macro_f_string_static_t_initialize_1("test", 0, 4),
    macro_f_string_static_t_initialize_1("test", 0, 5),
    macro_f_string_static_t_initialize_1("te\0st", 0, 5),
    macro_f_string_static_t_initialize_1("te\0st", 0, 6),
    macro_f_string_static_t_initialize_1("te\0\0st", 0, 6),
    macro_f_string_static_t_initialize_1("te\0\0st", 0, 7),
    macro_f_string_static_t_initialize_1("te\0\0s\0t", 0, 7),
    macro_f_string_static_t_initialize_1("te\0\0s\0t", 0, 8),
    macro_f_string_static_t_initialize_1("te\0\0s\0\0\0t", 0, 9),
    macro_f_string_static_t_initialize_1("te\0\0s\0\0\0t", 0, 10),

    // Third Set.
    macro_f_string_static_t_initialize_1("\0\0test", 0, 6),
    macro_f_string_static_t_initialize_1("\0\0test", 0, 7),
    macro_f_string_static_t_initialize_1("\0\0te\0st", 0, 7),
    macro_f_string_static_t_initialize_1("\0\0te\0st", 0, 8),
    macro_f_string_static_t_initialize_1("\0\0te\0\0st", 0, 8),
    macro_f_string_static_t_initialize_1("\0\0te\0\0st", 0, 9),
    macro_f_string_static_t_initialize_1("\0\0te\0\0s\0t", 0, 9),
    macro_f_string_static_t_initialize_1("\0\0te\0\0s\0t", 0, 10),
    macro_f_string_static_t_initialize_1("\0\0te\0\0s\0\0\0t", 0, 11),
    macro_f_string_static_t_initialize_1("\0\0te\0\0s\0\0\0t", 0, 12),

    // Fourth Set.
    macro_f_string_static_t_initialize_1("\0\0\0\0", 0, 4),
    macro_f_string_static_t_initialize_1("\0\0\0\0", 0, 4),
    macro_f_string_static_t_initialize_1("\0", 0, 1),
    macro_f_string_static_t_initialize_1("t", 0, 1),
  };

  const f_string_static_t expects[] = {

    // First Set.
    macro_f_string_static_t_initialize_1("test", 0, 4),
    macro_f_string_static_t_initialize_1("test", 0, 5),
    macro_f_string_static_t_initialize_1("test\0", 0, 5),
    macro_f_string_static_t_initialize_1("test\0", 0, 6),
    macro_f_string_static_t_initialize_1("test\0\0", 0, 6),
    macro_f_string_static_t_initialize_1("test\0\0", 0, 7),
    macro_f_string_static_t_initialize_1("test\0\0\0", 0, 7),
    macro_f_string_static_t_initialize_1("test\0\0\0", 0, 8),
    macro_f_string_static_t_initialize_1("test\0\0\0\0\0", 0, 9),
    macro_f_string_static_t_initialize_1("test\0\0\0\0\0", 0, 10),

    // Second Set.
    macro_f_string_static_t_initialize_1("test", 0, 4),
    macro_f_string_static_t_initialize_1("test", 0, 5),
    macro_f_string_static_t_initialize_1("test\0", 0, 5),
    macro_f_string_static_t_initialize_1("test\0", 0, 6),
    macro_f_string_static_t_initialize_1("test\0\0", 0, 6),
    macro_f_string_static_t_initialize_1("test\0\0", 0, 7),
    macro_f_string_static_t_initialize_1("test\0\0\0", 0, 7),
    macro_f_string_static_t_initialize_1("test\0\0\0", 0, 8),
    macro_f_string_static_t_initialize_1("test\0\0\0\0\0", 0, 9),
    macro_f_string_static_t_initialize_1("test\0\0\0\0\0", 0, 10),

    // Third Set.
    macro_f_string_static_t_initialize_1("te\0\0st", 0, 6),
    macro_f_string_static_t_initialize_1("te\0\0st", 0, 7),
    macro_f_string_static_t_initialize_1("te\0\0\0st", 0, 7),
    macro_f_string_static_t_initialize_1("te\0\0\0st", 0, 8),
    macro_f_string_static_t_initialize_1("te\0\0\0\0st", 0, 8),
    macro_f_string_static_t_initialize_1("te\0\0\0\0st", 0, 9),
    macro_f_string_static_t_initialize_1("te\0\0\0\0s\0t", 0, 9),
    macro_f_string_static_t_initialize_1("te\0\0\0\0s\0t", 0, 10),
    macro_f_string_static_t_initialize_1("te\0\0\0\0s\0\0\0t", 0, 11),
    macro_f_string_static_t_initialize_1("te\0\0\0\0s\0\0\0t", 0, 12),

    // Fourth Set.
    macro_f_string_static_t_initialize_1("\0\0\0\0", 0, 4),
    macro_f_string_static_t_initialize_1("\0\0\0\0", 0, 4),
    macro_f_string_static_t_initialize_1("\0", 0, 1),
    macro_f_string_static_t_initialize_1("t", 0, 1),
  };

  const f_range_t ranges[] = {

    // First Set.
    macro_f_range_t_initialize_1(0, sources[0].used - 1),
    macro_f_range_t_initialize_1(0, sources[1].used - 1),
    macro_f_range_t_initialize_1(0, sources[2].used - 1),
    macro_f_range_t_initialize_1(0, sources[3].used - 1),
    macro_f_range_t_initialize_1(0, sources[4].used - 1),
    macro_f_range_t_initialize_1(0, sources[5].used - 1),
    macro_f_range_t_initialize_1(0, sources[6].used - 1),
    macro_f_range_t_initialize_1(0, sources[7].used - 1),
    macro_f_range_t_initialize_1(0, sources[8].used - 1),
    macro_f_range_t_initialize_1(0, sources[9].used - 1),

    // Second Set.
    macro_f_range_t_initialize_1(2, 3),
    macro_f_range_t_initialize_1(2, 3),
    macro_f_range_t_initialize_1(2, 4),
    macro_f_range_t_initialize_1(2, 4),
    macro_f_range_t_initialize_1(2, 5),
    macro_f_range_t_initialize_1(2, 5),
    macro_f_range_t_initialize_1(2, 6),
    macro_f_range_t_initialize_1(2, 6),
    macro_f_range_t_initialize_1(2, 8),
    macro_f_range_t_initialize_1(2, 8),

    // Third Set.
    macro_f_range_t_initialize_1(0, 3),
    macro_f_range_t_initialize_1(0, 3),
    macro_f_range_t_initialize_1(0, 3),
    macro_f_range_t_initialize_1(0, 3),
    macro_f_range_t_initialize_1(0, 3),
    macro_f_range_t_initialize_1(0, 3),
    macro_f_range_t_initialize_1(0, 3),
    macro_f_range_t_initialize_1(0, 3),
    macro_f_range_t_initialize_1(0, 3),
    macro_f_range_t_initialize_1(0, 3),

    // Fourth Set.
    macro_f_range_t_initialize_1(0, 0),
    macro_f_range_t_initialize_1(0, 3),
    macro_f_range_t_initialize_1(0, 0),
    macro_f_range_t_initialize_1(0, 0),
  };

  for (uint8_t i = 0; i < 34; ++i) {

    char string[sources[i].used];
    f_string_static_t buffer = macro_f_string_static_t_initialize_1(string, 0, sources[i].used);

    memcpy(string, sources[i].string, sources[i].used);

    const f_status_t status = f_string_dynamic_strip_null_range(ranges[i], &buffer);

    assert_int_equal(status, F_okay);
    assert_int_equal(buffer.used, expects[i].used);

    // Compare strings using integer tests because assert_string_equal() assumes NULL terminated strings.
    for (uint8_t j = 0; j < buffer.used; ++j) {
      assert_int_equal(buffer.string[j], expects[i].string[j]);
    } // for
  } // for
}

void test__f_string_dynamic_strip_null_range__parameter_checking(void **state) {

  const f_range_t range = f_range_t_initialize;

  {
    const f_status_t status = f_string_dynamic_strip_null_range(range, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
