#include "test-string.h"
#include "test-string-dynamic_strip_null.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_string_dynamic_strip_null__returns_data_not(void **state) {

  f_string_static_t buffer = f_string_static_t_initialize;

  {
    const f_status_t status = f_string_dynamic_strip_null(&buffer);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_string_dynamic_strip_null__works(void **state) {

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
    macro_f_string_static_t_initialize_1("test", 0, 4),
    macro_f_string_static_t_initialize_1("test\0", 0, 4),
    macro_f_string_static_t_initialize_1("test\0", 0, 4),
    macro_f_string_static_t_initialize_1("test\0\0", 0, 4),
    macro_f_string_static_t_initialize_1("test\0\0", 0, 4),
    macro_f_string_static_t_initialize_1("test\0\0\0", 0, 4),
    macro_f_string_static_t_initialize_1("test\0\0\0", 0, 4),
    macro_f_string_static_t_initialize_1("test\0\0\0\0\0", 0, 4),
    macro_f_string_static_t_initialize_1("test\0\0\0\0\0", 0, 4),

    // Second Set.
    macro_f_string_static_t_initialize_1("test", 0, 4),
    macro_f_string_static_t_initialize_1("test", 0, 4),
    macro_f_string_static_t_initialize_1("test\0", 0, 4),
    macro_f_string_static_t_initialize_1("test\0", 0, 4),
    macro_f_string_static_t_initialize_1("test\0\0", 0, 4),
    macro_f_string_static_t_initialize_1("test\0\0", 0, 4),
    macro_f_string_static_t_initialize_1("test\0\0\0", 0, 4),
    macro_f_string_static_t_initialize_1("test\0\0\0", 0, 4),
    macro_f_string_static_t_initialize_1("test\0\0\0\0\0", 0, 4),
    macro_f_string_static_t_initialize_1("test\0\0\0\0\0", 0, 4),

    // Third Set.
    macro_f_string_static_t_initialize_1("test\0\0", 0, 4),
    macro_f_string_static_t_initialize_1("test\0\0", 0, 4),
    macro_f_string_static_t_initialize_1("test\0\0\0", 0, 4),
    macro_f_string_static_t_initialize_1("test\0\0\0", 0, 4),
    macro_f_string_static_t_initialize_1("test\0\0\0\0", 0, 4),
    macro_f_string_static_t_initialize_1("test\0\0\0\0", 0, 4),
    macro_f_string_static_t_initialize_1("test\0\0\0\0\0", 0, 4),
    macro_f_string_static_t_initialize_1("test\0\0\0\0\0", 0, 4),
    macro_f_string_static_t_initialize_1("test\0\0\0\0\0\0\0", 0, 4),
    macro_f_string_static_t_initialize_1("test\0\0\0\0\0\0\0", 0, 4),

    // Fourth Set.
    macro_f_string_static_t_initialize_1("\0\0\0\0", 0, 0),
    macro_f_string_static_t_initialize_1("\0\0\0\0", 0, 0),
    macro_f_string_static_t_initialize_1("\0", 0, 0),
    macro_f_string_static_t_initialize_1("t", 0, 1),
  };

  for (uint8_t i = 0; i < 34; ++i) {

    char string[sources[i].used];
    f_string_static_t buffer = macro_f_string_static_t_initialize_1(string, 0, sources[i].used);

    memcpy(string, sources[i].string, sources[i].used);

    const f_status_t status = f_string_dynamic_strip_null(&buffer);

    assert_int_equal(status, F_okay);
    assert_int_equal(buffer.used, expects[i].used);

    // Compare strings using integer tests because assert_string_equal() assumes NULL terminated strings (using souces to confirm that the NULLs are moved).
    for (uint8_t j = 0; j < sources[i].used; ++j) {
      assert_int_equal(buffer.string[j], expects[i].string[j]);
    } // for
  } // for
}

void test__f_string_dynamic_strip_null__parameter_checking(void **state) {

  {
    const f_status_t status = f_string_dynamic_strip_null(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
