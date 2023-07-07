#include "test-compare.h"
#include "test-compare-utf_dynamic_except_trim.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_compare_utf_dynamic_except_trim__works(void **state) {

  // A necessary work-around to to have "\01" with the "\0" being separate from the "1".
  f_char_t null_before_one_1[] = {
    'S', 'K', 'I', 'P', '\0', '1'
  };

  f_char_t null_before_one_2[] = {
    'S', 'K', 'I', 'P', '\0', '1', ' ', '\0', '\t'
  };

  f_char_t null_before_one_3[] = {
    'S', 'K', 'I', 'P', '\0', ' ', '\0', '1'
  };

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
    macro_f_string_static_t_initialize_1("SKIP ", 0, 5),
    macro_f_string_static_t_initialize_1("SKIP\t", 0, 5),
    macro_f_string_static_t_initialize_1("SKIP\0", 0, 5),
    macro_f_string_static_t_initialize_1("SKIP    ", 0, 8),
    macro_f_string_static_t_initialize_1("SKIP  \t ", 0, 8),
    macro_f_string_static_t_initialize_1("SKIP\0 \0\t", 0, 8),
    macro_f_string_static_t_initialize_1("SKIP\0 \0", 0, 7),
    macro_f_string_static_t_initialize_1("SKIP\0\0\t", 0, 7),

    // 3.
    macro_f_string_static_t_initialize_1("SKIP 1", 0, 6),
    macro_f_string_static_t_initialize_1("SKIP\t1", 0, 6),
    macro_f_string_static_t_initialize_1(null_before_one_1, 0, 6),
    macro_f_string_static_t_initialize_1("SKIP  1  ", 0, 9),
    macro_f_string_static_t_initialize_1("SKIP  1\t ", 0, 9),
    macro_f_string_static_t_initialize_1(null_before_one_2, 0, 9),
    macro_f_string_static_t_initialize_1(null_before_one_3, 0, 8),
    macro_f_string_static_t_initialize_1("SKIP1\0\0\t", 0, 8),

    // 4.
    macro_f_string_static_t_initialize_1("SKIP one", 0, 8),
    macro_f_string_static_t_initialize_1("SKIP\tone", 0, 8),
    macro_f_string_static_t_initialize_1("SKIP\0one", 0, 8),
    macro_f_string_static_t_initialize_1("SKIP  one  ", 0, 11),
    macro_f_string_static_t_initialize_1("SKIP  one\t ", 0, 11),
    macro_f_string_static_t_initialize_1("SKIP\0one \0\t", 0, 11),
    macro_f_string_static_t_initialize_1("SKIP\0 \0one", 0, 10),
    macro_f_string_static_t_initialize_1("SKIPone\0\0\t", 0, 10),

    // 5.
    macro_f_string_static_t_initialize_1("SKIP One", 0, 8),
    macro_f_string_static_t_initialize_1("SKIP\tOne", 0, 8),
    macro_f_string_static_t_initialize_1("SKIP\0One", 0, 8),
    macro_f_string_static_t_initialize_1("SKIP  One  ", 0, 11),
    macro_f_string_static_t_initialize_1("SKIP  One\t ", 0, 11),
    macro_f_string_static_t_initialize_1("SKIP\0One \0\t", 0, 11),
    macro_f_string_static_t_initialize_1("SKIP\0 \0One", 0, 10),
    macro_f_string_static_t_initialize_1("SKIPOne\0\0\t", 0, 10),

    // 6.
    macro_f_string_static_t_initialize_1("SKIP \0ne", 0, 8),
    macro_f_string_static_t_initialize_1("SKIP\t\0ne", 0, 8),
    macro_f_string_static_t_initialize_1("SKIP\0\0ne", 0, 8),
    macro_f_string_static_t_initialize_1("SKIP  \0ne  ", 0, 11),
    macro_f_string_static_t_initialize_1("SKIP  \0ne\t ", 0, 11),
    macro_f_string_static_t_initialize_1("SKIP\0\0ne \0\t", 0, 11),
    macro_f_string_static_t_initialize_1("SKIP\0 \0\0ne", 0, 10),
    macro_f_string_static_t_initialize_1("SKIP\0ne\0\0\t", 0, 10),

    // 7.
    macro_f_string_static_t_initialize_1("SKIP o\0ne", 0, 9),
    macro_f_string_static_t_initialize_1("SKIP\to\0ne", 0, 9),
    macro_f_string_static_t_initialize_1("SKIP\0o\0ne", 0, 9),
    macro_f_string_static_t_initialize_1("SKIP  o\0ne  ", 0, 12),
    macro_f_string_static_t_initialize_1("SKIP  o\0ne\t ", 0, 12),
    macro_f_string_static_t_initialize_1("SKIP\0o\0ne \0\t", 0, 12),
    macro_f_string_static_t_initialize_1("SKIP\0 \0o\0ne", 0, 11),
    macro_f_string_static_t_initialize_1("SKIPo\0ne\0\0\t", 0, 11),

    // 8.
    macro_f_string_static_t_initialize_1("SKIP one\0", 0, 9),
    macro_f_string_static_t_initialize_1("SKIP\tone\0", 0, 9),
    macro_f_string_static_t_initialize_1("SKIP\0one\0", 0, 9),
    macro_f_string_static_t_initialize_1("SKIP  one\0  ", 0, 12),
    macro_f_string_static_t_initialize_1("SKIP  one\0\t ", 0, 12),
    macro_f_string_static_t_initialize_1("SKIP\0one\0 \0\t", 0, 12),
    macro_f_string_static_t_initialize_1("SKIP\0 \0one\0", 0, 11),
    macro_f_string_static_t_initialize_1("SKIPone\0\0\0\t", 0, 11),
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

  f_number_unsigned_t except_1[] = {
    0, 1, 2, 3,
  };
  const f_number_unsigneds_t excepts_1 = macro_f_number_unsigneds_t_initialize_1(except_1, 0, 4);
  const f_number_unsigneds_t excepts_2 = f_number_unsigneds_t_initialize;
  uint8_t i = 0;

  f_status_t status = F_none;
  f_utf_string_dynamic_t utf_string_1 = f_utf_string_dynamic_t_initialize;
  f_utf_string_dynamic_t utf_string_2 = f_utf_string_dynamic_t_initialize;

  for (; i < 64; ++i) {

    utf_string_1.used = 0;
    utf_string_2.used = 0;

    status = test_convert_dynamic_to_utf(string_1s[i], &utf_string_1);
    assert_int_equal(status, F_none);

    status = test_convert_dynamic_to_utf(string_2s[i], &utf_string_2);
    assert_int_equal(status, F_none);

    status = f_compare_utf_dynamic_except_trim(utf_string_1, utf_string_2, excepts_1, excepts_2);

    assert_int_equal(status, expects[i]);
  } // for

  for (i = 0; i < 64; ++i) {

    utf_string_1.used = 0;
    utf_string_2.used = 0;

    status = test_convert_dynamic_to_utf(string_1s[i], &utf_string_1);
    assert_int_equal(status, F_none);

    status = test_convert_dynamic_to_utf(string_2s[i], &utf_string_2);
    assert_int_equal(status, F_none);

    status = f_compare_utf_dynamic_except_trim(utf_string_2, utf_string_1, excepts_2, excepts_1);

    assert_int_equal(status, expects[i]);
  } // for

  f_utf_string_dynamic_resize(0, &utf_string_1);
  f_utf_string_dynamic_resize(0, &utf_string_2);
}

#ifdef __cplusplus
} // extern "C"
#endif