#include "test-compare.h"
#include "test-compare-utf_dynamic_trim.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_compare_utf_dynamic_trim__trims(void **state) {

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

  f_status_t status = F_okay;
  f_utf_string_dynamic_t utf_string_1 = f_utf_string_dynamic_t_initialize;
  f_utf_string_dynamic_t utf_string_2 = f_utf_string_dynamic_t_initialize;

  for (; i < 13; ++i) {

    utf_string_1.used = 0;
    utf_string_2.used = 0;

    status = test_convert_dynamic_to_utf(string_1s[i], &utf_string_1);
    assert_int_equal(status, F_okay);

    status = test_convert_dynamic_to_utf(string_2s[i], &utf_string_2);
    assert_int_equal(status, F_okay);

    status = f_compare_utf_dynamic_trim(utf_string_1, utf_string_2);

    assert_int_equal(status, expects[i]);
  } // for

  for (i = 0; i < 13; ++i) {

    utf_string_1.used = 0;
    utf_string_2.used = 0;

    status = test_convert_dynamic_to_utf(string_1s[i], &utf_string_1);
    assert_int_equal(status, F_okay);

    status = test_convert_dynamic_to_utf(string_2s[i], &utf_string_2);
    assert_int_equal(status, F_okay);

    status = f_compare_utf_dynamic_trim(utf_string_2, utf_string_1);

    assert_int_equal(status, expects[i]);
  } // for

  for (i = 0; i < 10; ++i) {

    utf_string_1.used = 0;

    status = test_convert_dynamic_to_utf(string_1s[i], &utf_string_1);
    assert_int_equal(status, F_okay);

    status = f_compare_utf_dynamic_trim(utf_string_1, utf_string_1);

    assert_int_equal(status, F_equal_to);
  } // for

  for (i = 0; i < 10; ++i) {

    utf_string_2.used = 0;

    status = test_convert_dynamic_to_utf(string_2s[i], &utf_string_2);
    assert_int_equal(status, F_okay);

    status = f_compare_utf_dynamic_trim(utf_string_2, utf_string_2);

    assert_int_equal(status, F_equal_to);
  } // for

  f_utf_string_dynamic_resize(0, &utf_string_1);
  f_utf_string_dynamic_resize(0, &utf_string_2);
}

void test__f_compare_utf_dynamic_trim__something_misses_nothing(void **state) {

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

  f_status_t status = F_okay;
  f_utf_string_dynamic_t utf_string_1 = f_utf_string_dynamic_t_initialize;

  for (uint8_t i = 0; i < 10; ++i) {

    utf_string_1.used = 0;

    status = test_convert_dynamic_to_utf(string_1s[i], &utf_string_1);
    assert_int_equal(status, F_okay);

    status = f_compare_utf_dynamic_trim(utf_string_1, f_utf_string_empty_s);

    assert_int_equal(status, F_equal_to_not);
  } // for

  f_utf_string_dynamic_resize(0, &utf_string_1);
}

void test__f_compare_utf_dynamic_trim__works(void **state) {

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

  f_status_t status = F_okay;
  f_utf_string_dynamic_t utf_string_1 = f_utf_string_dynamic_t_initialize;
  f_utf_string_dynamic_t utf_string_2 = f_utf_string_dynamic_t_initialize;

  for (uint8_t i = 0; i < 64; ++i) {

    utf_string_1.used = 0;
    utf_string_2.used = 0;

    status = test_convert_dynamic_to_utf(string_1s[i], &utf_string_1);
    assert_int_equal(status, F_okay);

    status = test_convert_dynamic_to_utf(string_2s[i], &utf_string_2);
    assert_int_equal(status, F_okay);

    status = f_compare_utf_dynamic_trim(utf_string_1, utf_string_2);

    assert_int_equal(status, expects[i]);
  } // for

  f_utf_string_dynamic_resize(0, &utf_string_1);
  f_utf_string_dynamic_resize(0, &utf_string_2);
}

#ifdef __cplusplus
} // extern "C"
#endif
