#include "test-compare.h"
#include "test-compare-dynamic_trim.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_compare_dynamic_trim__trims(void **state) {

  const f_string_static_t string_1s[] = {
    macro_f_string_static_t_initialize_1(" ", 0, 1),
    macro_f_string_static_t_initialize_1("\t", 0, 1),
    macro_f_string_static_t_initialize_1(" \0\t", 0, 3),
    macro_f_string_static_t_initialize_1("space", 0, 5),
    macro_f_string_static_t_initialize_1(" space", 0, 6),
    macro_f_string_static_t_initialize_1("space ", 0, 6),
    macro_f_string_static_t_initialize_1(" space ", 0, 7),
    macro_f_string_static_t_initialize_1(" \t space \t ", 0, 11),
    macro_f_string_static_t_initialize_1("space space", 0, 11),
    macro_f_string_static_t_initialize_1(" space\tspace ", 0, 13),
    macro_f_string_static_t_initialize_1("\t\0\tspace\t\0 space \0 ", 0, 19),
    macro_f_string_static_t_initialize_1(" space\tspace ", 0, 13),
    macro_f_string_static_t_initialize_1("\t\0\tspace\t\0 space \0 ", 0, 19),
  };

  const f_string_static_t string_2s[] = {
    f_string_empty_s,
    f_string_empty_s,
    f_string_empty_s,
    macro_f_string_static_t_initialize_1("space", 0, 5),
    macro_f_string_static_t_initialize_1("space", 0, 5),
    macro_f_string_static_t_initialize_1("space", 0, 5),
    macro_f_string_static_t_initialize_1("space", 0, 5),
    macro_f_string_static_t_initialize_1("space", 0, 5),
    macro_f_string_static_t_initialize_1("space space", 0, 11),
    macro_f_string_static_t_initialize_1("space\tspace", 0, 11),
    macro_f_string_static_t_initialize_1("space\t\0 space", 0, 13),
    macro_f_string_static_t_initialize_1("space space", 0, 11),
    macro_f_string_static_t_initialize_1("space space", 0, 11),
  };

  const f_status_t expects[] = {
    F_equal_to,
    F_equal_to,
    F_equal_to,
    F_equal_to,
    F_equal_to,
    F_equal_to,
    F_equal_to,
    F_equal_to,
    F_equal_to,
    F_equal_to,
    F_equal_to,
    F_equal_to_not,
    F_equal_to_not,
  };

  uint8_t i = 0;

  for (; i < 13; ++i) {

    const f_status_t status = f_compare_dynamic_trim(string_1s[i], string_2s[i]);

    assert_int_equal(status, expects[i]);
  } // for

  for (i = 0; i < 13; ++i) {

    const f_status_t status = f_compare_dynamic_trim(string_2s[i], string_1s[i]);

    assert_int_equal(status, expects[i]);
  } // for

  for (i = 0; i < 10; ++i) {

    const f_status_t status = f_compare_dynamic_trim(string_1s[i], string_1s[i]);

    assert_int_equal(status, F_equal_to);
  } // for

  for (i = 0; i < 10; ++i) {

    const f_status_t status = f_compare_dynamic_trim(string_2s[i], string_2s[i]);

    assert_int_equal(status, F_equal_to);
  } // for
}

void test__f_compare_dynamic_trim__something_misses_nothing(void **state) {

  const f_string_static_t string_1s[] = {
    macro_f_string_static_t_initialize_1("space", 0, 5),
    macro_f_string_static_t_initialize_1(" space", 0, 6),
    macro_f_string_static_t_initialize_1("space ", 0, 6),
    macro_f_string_static_t_initialize_1(" space ", 0, 7),
    macro_f_string_static_t_initialize_1(" \t space \t ", 0, 11),
    macro_f_string_static_t_initialize_1("space space", 0, 11),
    macro_f_string_static_t_initialize_1(" space\tspace ", 0, 11),
    macro_f_string_static_t_initialize_1("\t\0\tspace\t\0 space \0 ", 0, 19),
    macro_f_string_static_t_initialize_1(" space\tspace ", 0, 11),
    macro_f_string_static_t_initialize_1("\t\0\tspace\t\0 space \0 ", 0, 19),
  };

  for (uint8_t i = 0; i < 10; ++i) {

    const f_status_t status = f_compare_dynamic_trim(string_1s[i], f_string_empty_s);

    assert_int_equal(status, F_equal_to_not);
  } // for
}

void test__f_compare_dynamic_trim__works(void **state) {

  const f_string_static_t string_1s[] = {

    // 1.
    macro_f_string_static_t_initialize_1(0, 0, 0),
    macro_f_string_static_t_initialize_1(0, 0, 0),
    macro_f_string_static_t_initialize_1(0, 0, 0),
    macro_f_string_static_t_initialize_1(0, 0, 0),
    macro_f_string_static_t_initialize_1(0, 0, 0),
    macro_f_string_static_t_initialize_1(0, 0, 0),
    macro_f_string_static_t_initialize_1(0, 0, 0),
    macro_f_string_static_t_initialize_1(0, 0, 0),

    // 2.
    macro_f_string_static_t_initialize_1("", 0, 0),
    macro_f_string_static_t_initialize_1("", 0, 0),
    macro_f_string_static_t_initialize_1("", 0, 0),
    macro_f_string_static_t_initialize_1("", 0, 0),
    macro_f_string_static_t_initialize_1("", 0, 0),
    macro_f_string_static_t_initialize_1("", 0, 0),
    macro_f_string_static_t_initialize_1("", 0, 0),
    macro_f_string_static_t_initialize_1("", 0, 0),

    // 3.
    macro_f_string_static_t_initialize_1("1", 0, 1),
    macro_f_string_static_t_initialize_1("1", 0, 1),
    macro_f_string_static_t_initialize_1("1", 0, 1),
    macro_f_string_static_t_initialize_1("1", 0, 1),
    macro_f_string_static_t_initialize_1("1", 0, 1),
    macro_f_string_static_t_initialize_1("1", 0, 1),
    macro_f_string_static_t_initialize_1("1", 0, 1),
    macro_f_string_static_t_initialize_1("1", 0, 1),

    // 4.
    macro_f_string_static_t_initialize_1("one", 0, 3),
    macro_f_string_static_t_initialize_1("one", 0, 3),
    macro_f_string_static_t_initialize_1("one", 0, 3),
    macro_f_string_static_t_initialize_1("one", 0, 3),
    macro_f_string_static_t_initialize_1("one", 0, 3),
    macro_f_string_static_t_initialize_1("one", 0, 3),
    macro_f_string_static_t_initialize_1("one", 0, 3),
    macro_f_string_static_t_initialize_1("one", 0, 3),

    // 5.
    macro_f_string_static_t_initialize_1("One", 0, 3),
    macro_f_string_static_t_initialize_1("One", 0, 3),
    macro_f_string_static_t_initialize_1("One", 0, 3),
    macro_f_string_static_t_initialize_1("One", 0, 3),
    macro_f_string_static_t_initialize_1("One", 0, 3),
    macro_f_string_static_t_initialize_1("One", 0, 3),
    macro_f_string_static_t_initialize_1("One", 0, 3),
    macro_f_string_static_t_initialize_1("One", 0, 3),

    // 6.
    macro_f_string_static_t_initialize_1("\0ne", 0, 3),
    macro_f_string_static_t_initialize_1("\0ne", 0, 3),
    macro_f_string_static_t_initialize_1("\0ne", 0, 3),
    macro_f_string_static_t_initialize_1("\0ne", 0, 3),
    macro_f_string_static_t_initialize_1("\0ne", 0, 3),
    macro_f_string_static_t_initialize_1("\0ne", 0, 3),
    macro_f_string_static_t_initialize_1("\0ne", 0, 3),
    macro_f_string_static_t_initialize_1("\0ne", 0, 3),

    // 7.
    macro_f_string_static_t_initialize_1("o\0ne", 0, 4),
    macro_f_string_static_t_initialize_1("o\0ne", 0, 4),
    macro_f_string_static_t_initialize_1("o\0ne", 0, 4),
    macro_f_string_static_t_initialize_1("o\0ne", 0, 4),
    macro_f_string_static_t_initialize_1("o\0ne", 0, 4),
    macro_f_string_static_t_initialize_1("o\0ne", 0, 4),
    macro_f_string_static_t_initialize_1("o\0ne", 0, 4),
    macro_f_string_static_t_initialize_1("o\0ne", 0, 4),

    // 8.
    macro_f_string_static_t_initialize_1("one\0", 0, 4),
    macro_f_string_static_t_initialize_1("one\0", 0, 4),
    macro_f_string_static_t_initialize_1("one\0", 0, 4),
    macro_f_string_static_t_initialize_1("one\0", 0, 4),
    macro_f_string_static_t_initialize_1("one\0", 0, 4),
    macro_f_string_static_t_initialize_1("one\0", 0, 4),
    macro_f_string_static_t_initialize_1("one\0", 0, 4),
    macro_f_string_static_t_initialize_1("one\0", 0, 4),
  };

  const f_string_static_t string_2s[] = {

    // 1.
    macro_f_string_static_t_initialize_1(0, 0, 0),
    macro_f_string_static_t_initialize_1("", 0, 0),
    macro_f_string_static_t_initialize_1("1", 0, 1),
    macro_f_string_static_t_initialize_1("one", 0, 3),
    macro_f_string_static_t_initialize_1("One", 0, 3),
    macro_f_string_static_t_initialize_1("\0ne", 0, 3),
    macro_f_string_static_t_initialize_1("o\0ne", 0, 4),
    macro_f_string_static_t_initialize_1("one\0", 0, 4),

    // 2.
    macro_f_string_static_t_initialize_1(0, 0, 0),
    macro_f_string_static_t_initialize_1("", 0, 0),
    macro_f_string_static_t_initialize_1("1", 0, 1),
    macro_f_string_static_t_initialize_1("one", 0, 3),
    macro_f_string_static_t_initialize_1("One", 0, 3),
    macro_f_string_static_t_initialize_1("\0ne", 0, 3),
    macro_f_string_static_t_initialize_1("o\0ne", 0, 4),
    macro_f_string_static_t_initialize_1("one\0", 0, 4),

    // 3.
    macro_f_string_static_t_initialize_1(0, 0, 0),
    macro_f_string_static_t_initialize_1("", 0, 0),
    macro_f_string_static_t_initialize_1("1", 0, 1),
    macro_f_string_static_t_initialize_1("one", 0, 3),
    macro_f_string_static_t_initialize_1("One", 0, 3),
    macro_f_string_static_t_initialize_1("\0ne", 0, 3),
    macro_f_string_static_t_initialize_1("o\0ne", 0, 4),
    macro_f_string_static_t_initialize_1("one\0", 0, 4),

    // 4.
    macro_f_string_static_t_initialize_1(0, 0, 0),
    macro_f_string_static_t_initialize_1("", 0, 0),
    macro_f_string_static_t_initialize_1("1", 0, 1),
    macro_f_string_static_t_initialize_1("one", 0, 3),
    macro_f_string_static_t_initialize_1("One", 0, 3),
    macro_f_string_static_t_initialize_1("\0ne", 0, 3),
    macro_f_string_static_t_initialize_1("o\0ne", 0, 4),
    macro_f_string_static_t_initialize_1("one\0", 0, 4),

    // 5.
    macro_f_string_static_t_initialize_1(0, 0, 0),
    macro_f_string_static_t_initialize_1("", 0, 0),
    macro_f_string_static_t_initialize_1("1", 0, 1),
    macro_f_string_static_t_initialize_1("one", 0, 3),
    macro_f_string_static_t_initialize_1("One", 0, 3),
    macro_f_string_static_t_initialize_1("\0ne", 0, 3),
    macro_f_string_static_t_initialize_1("o\0ne", 0, 4),
    macro_f_string_static_t_initialize_1("one\0", 0, 4),

    // 6.
    macro_f_string_static_t_initialize_1(0, 0, 0),
    macro_f_string_static_t_initialize_1("", 0, 0),
    macro_f_string_static_t_initialize_1("1", 0, 1),
    macro_f_string_static_t_initialize_1("one", 0, 3),
    macro_f_string_static_t_initialize_1("One", 0, 3),
    macro_f_string_static_t_initialize_1("\0ne", 0, 3),
    macro_f_string_static_t_initialize_1("o\0ne", 0, 4),
    macro_f_string_static_t_initialize_1("one\0", 0, 4),

    // 7.
    macro_f_string_static_t_initialize_1(0, 0, 0),
    macro_f_string_static_t_initialize_1("", 0, 0),
    macro_f_string_static_t_initialize_1("1", 0, 1),
    macro_f_string_static_t_initialize_1("one", 0, 3),
    macro_f_string_static_t_initialize_1("One", 0, 3),
    macro_f_string_static_t_initialize_1("\0ne", 0, 3),
    macro_f_string_static_t_initialize_1("o\0ne", 0, 4),
    macro_f_string_static_t_initialize_1("one\0", 0, 4),

    // 8.
    macro_f_string_static_t_initialize_1(0, 0, 0),
    macro_f_string_static_t_initialize_1("", 0, 0),
    macro_f_string_static_t_initialize_1("1", 0, 1),
    macro_f_string_static_t_initialize_1("one", 0, 3),
    macro_f_string_static_t_initialize_1("One", 0, 3),
    macro_f_string_static_t_initialize_1("\0ne", 0, 3),
    macro_f_string_static_t_initialize_1("o\0ne", 0, 4),
    macro_f_string_static_t_initialize_1("one\0", 0, 4),
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

  for (uint8_t i = 0; i < 64; ++i) {

    const f_status_t status = f_compare_dynamic_trim(string_1s[i], string_2s[i]);

    assert_int_equal(status, expects[i]);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif