#include "test-compare.h"
#include "test-compare-utf_dynamic.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_compare_utf_dynamic__works(void **state) {

  const f_string_static_t string_1s[] = {

    // 1.
    macro_f_string_static_t_initialize(0, 0, 0),
    macro_f_string_static_t_initialize(0, 0, 0),
    macro_f_string_static_t_initialize(0, 0, 0),
    macro_f_string_static_t_initialize(0, 0, 0),
    macro_f_string_static_t_initialize(0, 0, 0),
    macro_f_string_static_t_initialize(0, 0, 0),
    macro_f_string_static_t_initialize(0, 0, 0),
    macro_f_string_static_t_initialize(0, 0, 0),

    // 2.
    macro_f_string_static_t_initialize("", 0, 0),
    macro_f_string_static_t_initialize("", 0, 0),
    macro_f_string_static_t_initialize("", 0, 0),
    macro_f_string_static_t_initialize("", 0, 0),
    macro_f_string_static_t_initialize("", 0, 0),
    macro_f_string_static_t_initialize("", 0, 0),
    macro_f_string_static_t_initialize("", 0, 0),
    macro_f_string_static_t_initialize("", 0, 0),

    // 3.
    macro_f_string_static_t_initialize("1", 0, 1),
    macro_f_string_static_t_initialize("1", 0, 1),
    macro_f_string_static_t_initialize("1", 0, 1),
    macro_f_string_static_t_initialize("1", 0, 1),
    macro_f_string_static_t_initialize("1", 0, 1),
    macro_f_string_static_t_initialize("1", 0, 1),
    macro_f_string_static_t_initialize("1", 0, 1),
    macro_f_string_static_t_initialize("1", 0, 1),

    // 4.
    macro_f_string_static_t_initialize("one", 0, 3),
    macro_f_string_static_t_initialize("one", 0, 3),
    macro_f_string_static_t_initialize("one", 0, 3),
    macro_f_string_static_t_initialize("one", 0, 3),
    macro_f_string_static_t_initialize("one", 0, 3),
    macro_f_string_static_t_initialize("one", 0, 3),
    macro_f_string_static_t_initialize("one", 0, 3),
    macro_f_string_static_t_initialize("one", 0, 3),

    // 5.
    macro_f_string_static_t_initialize("One", 0, 3),
    macro_f_string_static_t_initialize("One", 0, 3),
    macro_f_string_static_t_initialize("One", 0, 3),
    macro_f_string_static_t_initialize("One", 0, 3),
    macro_f_string_static_t_initialize("One", 0, 3),
    macro_f_string_static_t_initialize("One", 0, 3),
    macro_f_string_static_t_initialize("One", 0, 3),
    macro_f_string_static_t_initialize("One", 0, 3),

    // 6.
    macro_f_string_static_t_initialize("\0ne", 0, 3),
    macro_f_string_static_t_initialize("\0ne", 0, 3),
    macro_f_string_static_t_initialize("\0ne", 0, 3),
    macro_f_string_static_t_initialize("\0ne", 0, 3),
    macro_f_string_static_t_initialize("\0ne", 0, 3),
    macro_f_string_static_t_initialize("\0ne", 0, 3),
    macro_f_string_static_t_initialize("\0ne", 0, 3),
    macro_f_string_static_t_initialize("\0ne", 0, 3),

    // 7.
    macro_f_string_static_t_initialize("o\0ne", 0, 4),
    macro_f_string_static_t_initialize("o\0ne", 0, 4),
    macro_f_string_static_t_initialize("o\0ne", 0, 4),
    macro_f_string_static_t_initialize("o\0ne", 0, 4),
    macro_f_string_static_t_initialize("o\0ne", 0, 4),
    macro_f_string_static_t_initialize("o\0ne", 0, 4),
    macro_f_string_static_t_initialize("o\0ne", 0, 4),
    macro_f_string_static_t_initialize("o\0ne", 0, 4),

    // 8.
    macro_f_string_static_t_initialize("one\0", 0, 4),
    macro_f_string_static_t_initialize("one\0", 0, 4),
    macro_f_string_static_t_initialize("one\0", 0, 4),
    macro_f_string_static_t_initialize("one\0", 0, 4),
    macro_f_string_static_t_initialize("one\0", 0, 4),
    macro_f_string_static_t_initialize("one\0", 0, 4),
    macro_f_string_static_t_initialize("one\0", 0, 4),
    macro_f_string_static_t_initialize("one\0", 0, 4),
  };

  const f_string_static_t string_2s[] = {

    // 1.
    macro_f_string_static_t_initialize(0, 0, 0),
    macro_f_string_static_t_initialize("", 0, 0),
    macro_f_string_static_t_initialize("1", 0, 1),
    macro_f_string_static_t_initialize("one", 0, 3),
    macro_f_string_static_t_initialize("One", 0, 3),
    macro_f_string_static_t_initialize("\0ne", 0, 3),
    macro_f_string_static_t_initialize("o\0ne", 0, 4),
    macro_f_string_static_t_initialize("one\0", 0, 4),

    // 2.
    macro_f_string_static_t_initialize(0, 0, 0),
    macro_f_string_static_t_initialize("", 0, 0),
    macro_f_string_static_t_initialize("1", 0, 1),
    macro_f_string_static_t_initialize("one", 0, 3),
    macro_f_string_static_t_initialize("One", 0, 3),
    macro_f_string_static_t_initialize("\0ne", 0, 3),
    macro_f_string_static_t_initialize("o\0ne", 0, 4),
    macro_f_string_static_t_initialize("one\0", 0, 4),

    // 3.
    macro_f_string_static_t_initialize(0, 0, 0),
    macro_f_string_static_t_initialize("", 0, 0),
    macro_f_string_static_t_initialize("1", 0, 1),
    macro_f_string_static_t_initialize("one", 0, 3),
    macro_f_string_static_t_initialize("One", 0, 3),
    macro_f_string_static_t_initialize("\0ne", 0, 3),
    macro_f_string_static_t_initialize("o\0ne", 0, 4),
    macro_f_string_static_t_initialize("one\0", 0, 4),

    // 4.
    macro_f_string_static_t_initialize(0, 0, 0),
    macro_f_string_static_t_initialize("", 0, 0),
    macro_f_string_static_t_initialize("1", 0, 1),
    macro_f_string_static_t_initialize("one", 0, 3),
    macro_f_string_static_t_initialize("One", 0, 3),
    macro_f_string_static_t_initialize("\0ne", 0, 3),
    macro_f_string_static_t_initialize("o\0ne", 0, 4),
    macro_f_string_static_t_initialize("one\0", 0, 4),

    // 5.
    macro_f_string_static_t_initialize(0, 0, 0),
    macro_f_string_static_t_initialize("", 0, 0),
    macro_f_string_static_t_initialize("1", 0, 1),
    macro_f_string_static_t_initialize("one", 0, 3),
    macro_f_string_static_t_initialize("One", 0, 3),
    macro_f_string_static_t_initialize("\0ne", 0, 3),
    macro_f_string_static_t_initialize("o\0ne", 0, 4),
    macro_f_string_static_t_initialize("one\0", 0, 4),

    // 6.
    macro_f_string_static_t_initialize(0, 0, 0),
    macro_f_string_static_t_initialize("", 0, 0),
    macro_f_string_static_t_initialize("1", 0, 1),
    macro_f_string_static_t_initialize("one", 0, 3),
    macro_f_string_static_t_initialize("One", 0, 3),
    macro_f_string_static_t_initialize("\0ne", 0, 3),
    macro_f_string_static_t_initialize("o\0ne", 0, 4),
    macro_f_string_static_t_initialize("one\0", 0, 4),

    // 7.
    macro_f_string_static_t_initialize(0, 0, 0),
    macro_f_string_static_t_initialize("", 0, 0),
    macro_f_string_static_t_initialize("1", 0, 1),
    macro_f_string_static_t_initialize("one", 0, 3),
    macro_f_string_static_t_initialize("One", 0, 3),
    macro_f_string_static_t_initialize("\0ne", 0, 3),
    macro_f_string_static_t_initialize("o\0ne", 0, 4),
    macro_f_string_static_t_initialize("one\0", 0, 4),

    // 8.
    macro_f_string_static_t_initialize(0, 0, 0),
    macro_f_string_static_t_initialize("", 0, 0),
    macro_f_string_static_t_initialize("1", 0, 1),
    macro_f_string_static_t_initialize("one", 0, 3),
    macro_f_string_static_t_initialize("One", 0, 3),
    macro_f_string_static_t_initialize("\0ne", 0, 3),
    macro_f_string_static_t_initialize("o\0ne", 0, 4),
    macro_f_string_static_t_initialize("one\0", 0, 4),
  };

  const f_status_t expects[] = {

    // 1.
    F_equal_to,
    F_equal_to,
    F_equal_to_not,
    F_equal_to_not,
    F_equal_to_not,
    F_equal_to_not,
    F_equal_to_not,
    F_equal_to_not,

    // 2.
    F_equal_to,
    F_equal_to,
    F_equal_to_not,
    F_equal_to_not,
    F_equal_to_not,
    F_equal_to_not,
    F_equal_to_not,
    F_equal_to_not,

    // 3.
    F_equal_to_not,
    F_equal_to_not,
    F_equal_to,
    F_equal_to_not,
    F_equal_to_not,
    F_equal_to_not,
    F_equal_to_not,
    F_equal_to_not,

    // 4.
    F_equal_to_not,
    F_equal_to_not,
    F_equal_to_not,
    F_equal_to,
    F_equal_to_not,
    F_equal_to_not,
    F_equal_to,
    F_equal_to,

    // 5.
    F_equal_to_not,
    F_equal_to_not,
    F_equal_to_not,
    F_equal_to_not,
    F_equal_to,
    F_equal_to_not,
    F_equal_to_not,
    F_equal_to_not,

    // 6.
    F_equal_to_not,
    F_equal_to_not,
    F_equal_to_not,
    F_equal_to_not,
    F_equal_to_not,
    F_equal_to,
    F_equal_to_not,
    F_equal_to_not,

    // 7.
    F_equal_to_not,
    F_equal_to_not,
    F_equal_to_not,
    F_equal_to,
    F_equal_to_not,
    F_equal_to_not,
    F_equal_to,
    F_equal_to,

    // 8.
    F_equal_to_not,
    F_equal_to_not,
    F_equal_to_not,
    F_equal_to,
    F_equal_to_not,
    F_equal_to_not,
    F_equal_to,
    F_equal_to,
  };

  f_status_t status = F_none;
  f_utf_string_dynamic_t utf_string_1 = f_utf_string_dynamic_t_initialize;
  f_utf_string_dynamic_t utf_string_2 = f_utf_string_dynamic_t_initialize;

  for (uint8_t i = 0; i < 64; ++i) {

    utf_string_1.used = 0;
    utf_string_2.used = 0;

    status = test_convert_dynamic_to_utf(string_1s[i], &utf_string_1);
    assert_int_equal(status, F_none);

    status = test_convert_dynamic_to_utf(string_2s[i], &utf_string_2);
    assert_int_equal(status, F_none);

    status = f_compare_utf_dynamic(utf_string_1, utf_string_2);

    assert_int_equal(status, expects[i]);
  } // for

  f_utf_string_dynamic_resize(0, &utf_string_1);
  f_utf_string_dynamic_resize(0, &utf_string_2);
}

#ifdef __cplusplus
} // extern "C"
#endif
