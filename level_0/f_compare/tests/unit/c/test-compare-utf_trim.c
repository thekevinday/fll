#include "test-compare.h"
#include "test-compare-utf_trim.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_compare_utf_trim__trims(void **state) {

  const f_string_static_t string_1s[] = {
    macro_f_string_static_t_initialize(" ", 0, 1),
    macro_f_string_static_t_initialize("\t", 0, 1),
    macro_f_string_static_t_initialize(" \0\t", 0, 3),
    macro_f_string_static_t_initialize("space", 0, 5),
    macro_f_string_static_t_initialize(" space", 0, 6),
    macro_f_string_static_t_initialize("space ", 0, 6),
    macro_f_string_static_t_initialize(" space ", 0, 7),
    macro_f_string_static_t_initialize(" \t space \t ", 0, 11),
    macro_f_string_static_t_initialize("space space", 0, 11),
    macro_f_string_static_t_initialize(" space\tspace ", 0, 13),
    macro_f_string_static_t_initialize("\t\0\tspace\t\0 space \0 ", 0, 19),
    macro_f_string_static_t_initialize(" space\tspace ", 0, 13),
    macro_f_string_static_t_initialize("\t\0\tspace\t\0 space \0 ", 0, 19),
  };

  const f_string_static_t string_2s[] = {
    f_string_empty_s,
    f_string_empty_s,
    f_string_empty_s,
    macro_f_string_static_t_initialize("space", 0, 5),
    macro_f_string_static_t_initialize("space", 0, 5),
    macro_f_string_static_t_initialize("space", 0, 5),
    macro_f_string_static_t_initialize("space", 0, 5),
    macro_f_string_static_t_initialize("space", 0, 5),
    macro_f_string_static_t_initialize("space space", 0, 11),
    macro_f_string_static_t_initialize("space\tspace", 0, 11),
    macro_f_string_static_t_initialize("space\t\0 space", 0, 13),
    macro_f_string_static_t_initialize("space space", 0, 11),
    macro_f_string_static_t_initialize("space space", 0, 11),
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

  f_status_t status = F_none;
  f_utf_string_dynamic_t utf_string_1 = f_utf_string_dynamic_t_initialize;
  f_utf_string_dynamic_t utf_string_2 = f_utf_string_dynamic_t_initialize;

  for (; i < 13; ++i) {

    utf_string_1.used = 0;
    utf_string_2.used = 0;

    status = test_convert_dynamic_to_utf(string_1s[i], &utf_string_1);
    assert_int_equal(status, F_none);

    status = test_convert_dynamic_to_utf(string_2s[i], &utf_string_2);
    assert_int_equal(status, F_none);

    status = f_compare_utf_trim(utf_string_1.string, utf_string_2.string, utf_string_1.used, utf_string_2.used);

    assert_int_equal(status, expects[i]);
  } // for

  for (i = 0; i < 13; ++i) {

    utf_string_1.used = 0;
    utf_string_2.used = 0;

    status = test_convert_dynamic_to_utf(string_1s[i], &utf_string_1);
    assert_int_equal(status, F_none);

    status = test_convert_dynamic_to_utf(string_2s[i], &utf_string_2);
    assert_int_equal(status, F_none);

    status = f_compare_utf_trim(utf_string_2.string, utf_string_1.string, utf_string_2.used, utf_string_1.used);

    assert_int_equal(status, expects[i]);
  } // for

  for (i = 0; i < 10; ++i) {

    utf_string_1.used = 0;

    status = test_convert_dynamic_to_utf(string_1s[i], &utf_string_1);
    assert_int_equal(status, F_none);

    status = f_compare_utf_trim(utf_string_1.string, utf_string_1.string, utf_string_1.used, utf_string_1.used);

    assert_int_equal(status, F_equal_to);
  } // for

  for (i = 0; i < 10; ++i) {

    utf_string_2.used = 0;

    status = test_convert_dynamic_to_utf(string_2s[i], &utf_string_2);
    assert_int_equal(status, F_none);

    status = f_compare_utf_trim(utf_string_2.string, utf_string_2.string, utf_string_2.used, utf_string_2.used);

    assert_int_equal(status, F_equal_to);
  } // for

  f_utf_string_dynamic_resize(0, &utf_string_1);
  f_utf_string_dynamic_resize(0, &utf_string_2);
}

void test__f_compare_utf_trim__something_misses_nothing(void **state) {

  const f_string_static_t string_1s[] = {
    macro_f_string_static_t_initialize("space", 0, 5),
    macro_f_string_static_t_initialize(" space", 0, 6),
    macro_f_string_static_t_initialize("space ", 0, 6),
    macro_f_string_static_t_initialize(" space ", 0, 7),
    macro_f_string_static_t_initialize(" \t space \t ", 0, 11),
    macro_f_string_static_t_initialize("space space", 0, 11),
    macro_f_string_static_t_initialize(" space\tspace ", 0, 11),
    macro_f_string_static_t_initialize("\t\0\tspace\t\0 space \0 ", 0, 19),
    macro_f_string_static_t_initialize(" space\tspace ", 0, 11),
    macro_f_string_static_t_initialize("\t\0\tspace\t\0 space \0 ", 0, 19),
  };

  f_status_t status = F_none;
  f_utf_string_dynamic_t utf_string_1 = f_utf_string_dynamic_t_initialize;

  for (uint8_t i = 0; i < 10; ++i) {

    utf_string_1.used = 0;

    status = test_convert_dynamic_to_utf(string_1s[i], &utf_string_1);
    assert_int_equal(status, F_none);

    status = f_compare_utf_trim(utf_string_1.string, f_utf_string_empty_s.string, utf_string_1.used, f_utf_string_empty_s.used);

    assert_int_equal(status, F_equal_to_not);
  } // for

  f_utf_string_dynamic_resize(0, &utf_string_1);
}

void test__f_compare_utf_trim__works(void **state) {

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

    status = f_compare_utf_trim(utf_string_1.string, utf_string_2.string, utf_string_1.used, utf_string_2.used);

    assert_int_equal(status, expects[i]);
  } // for

  f_utf_string_dynamic_resize(0, &utf_string_1);
  f_utf_string_dynamic_resize(0, &utf_string_2);
}

#ifdef __cplusplus
} // extern "C"
#endif
