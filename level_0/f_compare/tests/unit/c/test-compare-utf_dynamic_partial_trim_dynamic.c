#include "test-compare.h"
#include "test-compare-utf_dynamic_partial_dynamic.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_compare_utf_dynamic_partial_trim_dynamic__works(void **state) {

  // A necessary work-around to to have "\01" with the "\0" being separate from the "1".
  f_char_t null_before_one_1[] = {
    '\0', '1'
  };

  f_char_t null_before_one_2[] = {
    '\0', '1', ' ', '\0', '\t'
  };

  f_char_t null_before_one_3[] = {
    '\0', ' ', '\0', '1'
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
    macro_f_string_static_t_initialize_1(" ", 0, 1),
    macro_f_string_static_t_initialize_1("\t", 0, 1),
    macro_f_string_static_t_initialize_1("\0", 0, 1),
    macro_f_string_static_t_initialize_1("    ", 0, 4),
    macro_f_string_static_t_initialize_1("  \t ", 0, 4),
    macro_f_string_static_t_initialize_1("\0 \0\t", 0, 4),
    macro_f_string_static_t_initialize_1("\0 \0", 0, 3),
    macro_f_string_static_t_initialize_1("\0\0\t", 0, 3),

    // 3.
    macro_f_string_static_t_initialize_1(" 1", 0, 2),
    macro_f_string_static_t_initialize_1("\t1", 0, 2),
    macro_f_string_static_t_initialize_1(null_before_one_1, 0, 2),
    macro_f_string_static_t_initialize_1("  1  ", 0, 5),
    macro_f_string_static_t_initialize_1("  1\t ", 0, 5),
    macro_f_string_static_t_initialize_1(null_before_one_2, 0, 5),
    macro_f_string_static_t_initialize_1(null_before_one_3, 0, 4),
    macro_f_string_static_t_initialize_1("1\0\0\t", 0, 4),

    // 4.
    macro_f_string_static_t_initialize_1(" one", 0, 4),
    macro_f_string_static_t_initialize_1("\tone", 0, 4),
    macro_f_string_static_t_initialize_1("\0one", 0, 4),
    macro_f_string_static_t_initialize_1("  one  ", 0, 7),
    macro_f_string_static_t_initialize_1("  one\t ", 0, 7),
    macro_f_string_static_t_initialize_1("\0one \0\t", 0, 7),
    macro_f_string_static_t_initialize_1("\0 \0one", 0, 6),
    macro_f_string_static_t_initialize_1("one\0\0\t", 0, 6),

    // 5.
    macro_f_string_static_t_initialize_1(" One", 0, 4),
    macro_f_string_static_t_initialize_1("\tOne", 0, 4),
    macro_f_string_static_t_initialize_1("\0One", 0, 4),
    macro_f_string_static_t_initialize_1("  One  ", 0, 7),
    macro_f_string_static_t_initialize_1("  One\t ", 0, 7),
    macro_f_string_static_t_initialize_1("\0One \0\t", 0, 7),
    macro_f_string_static_t_initialize_1("\0 \0One", 0, 6),
    macro_f_string_static_t_initialize_1("One\0\0\t", 0, 6),

    // 6.
    macro_f_string_static_t_initialize_1(" \0ne", 0, 4),
    macro_f_string_static_t_initialize_1("\t\0ne", 0, 4),
    macro_f_string_static_t_initialize_1("\0\0ne", 0, 4),
    macro_f_string_static_t_initialize_1("  \0ne  ", 0, 7),
    macro_f_string_static_t_initialize_1("  \0ne\t ", 0, 7),
    macro_f_string_static_t_initialize_1("\0\0ne \0\t", 0, 7),
    macro_f_string_static_t_initialize_1("\0 \0\0ne", 0, 6),
    macro_f_string_static_t_initialize_1("\0ne\0\0\t", 0, 6),

    // 7.
    macro_f_string_static_t_initialize_1(" o\0ne", 0, 5),
    macro_f_string_static_t_initialize_1("\to\0ne", 0, 5),
    macro_f_string_static_t_initialize_1("\0o\0ne", 0, 5),
    macro_f_string_static_t_initialize_1("  o\0ne  ", 0, 8),
    macro_f_string_static_t_initialize_1("  o\0ne\t ", 0, 8),
    macro_f_string_static_t_initialize_1("\0o\0ne \0\t", 0, 8),
    macro_f_string_static_t_initialize_1("\0 \0o\0ne", 0, 7),
    macro_f_string_static_t_initialize_1("o\0ne\0\0\t", 0, 7),

    // 8.
    macro_f_string_static_t_initialize_1(" one\0", 0, 5),
    macro_f_string_static_t_initialize_1("\tone\0", 0, 5),
    macro_f_string_static_t_initialize_1("\0one\0", 0, 5),
    macro_f_string_static_t_initialize_1("  one\0  ", 0, 8),
    macro_f_string_static_t_initialize_1("  one\0\t ", 0, 8),
    macro_f_string_static_t_initialize_1("\0one\0 \0\t", 0, 8),
    macro_f_string_static_t_initialize_1("\0 \0one\0", 0, 7),
    macro_f_string_static_t_initialize_1("one\0\0\0\t", 0, 7),
  };

  const f_string_static_t string_2s[] = {

    // 1.
    macro_f_string_static_t_initialize_1(0, 0, 0),
    macro_f_string_static_t_initialize_1("aa", 0, 2),
    macro_f_string_static_t_initialize_1("aa1", 0, 3),
    macro_f_string_static_t_initialize_1("aaone", 0, 5),
    macro_f_string_static_t_initialize_1("aaOne", 0, 5),
    macro_f_string_static_t_initialize_1("aa\0ne", 0, 5),
    macro_f_string_static_t_initialize_1("aao\0ne", 0, 6),
    macro_f_string_static_t_initialize_1("aaone\0", 0, 6),

    // 2.
    macro_f_string_static_t_initialize_1(0, 0, 0),
    macro_f_string_static_t_initialize_1("aa", 0, 2),
    macro_f_string_static_t_initialize_1("aa1", 0, 3),
    macro_f_string_static_t_initialize_1("aaone", 0, 5),
    macro_f_string_static_t_initialize_1("aaOne", 0, 5),
    macro_f_string_static_t_initialize_1("aa\0ne", 0, 5),
    macro_f_string_static_t_initialize_1("aao\0ne", 0, 6),
    macro_f_string_static_t_initialize_1("aaone\0", 0, 6),

    // 3.
    macro_f_string_static_t_initialize_1(0, 0, 0),
    macro_f_string_static_t_initialize_1("aa", 0, 2),
    macro_f_string_static_t_initialize_1("aa1", 0, 3),
    macro_f_string_static_t_initialize_1("aaone", 0, 5),
    macro_f_string_static_t_initialize_1("aaOne", 0, 5),
    macro_f_string_static_t_initialize_1("aa\0ne", 0, 5),
    macro_f_string_static_t_initialize_1("aao\0ne", 0, 6),
    macro_f_string_static_t_initialize_1("aaone\0", 0, 6),

    // 4.
    macro_f_string_static_t_initialize_1(0, 0, 0),
    macro_f_string_static_t_initialize_1("aa", 0, 2),
    macro_f_string_static_t_initialize_1("aa1", 0, 3),
    macro_f_string_static_t_initialize_1("aaone", 0, 5),
    macro_f_string_static_t_initialize_1("aaOne", 0, 5),
    macro_f_string_static_t_initialize_1("aa\0ne", 0, 5),
    macro_f_string_static_t_initialize_1("aao\0ne", 0, 6),
    macro_f_string_static_t_initialize_1("aaone\0", 0, 6),

    // 5.
    macro_f_string_static_t_initialize_1(0, 0, 0),
    macro_f_string_static_t_initialize_1("aa", 0, 2),
    macro_f_string_static_t_initialize_1("aa1", 0, 3),
    macro_f_string_static_t_initialize_1("aaone", 0, 5),
    macro_f_string_static_t_initialize_1("aaOne", 0, 5),
    macro_f_string_static_t_initialize_1("aa\0ne", 0, 5),
    macro_f_string_static_t_initialize_1("aao\0ne", 0, 6),
    macro_f_string_static_t_initialize_1("aaone\0", 0, 6),

    // 6.
    macro_f_string_static_t_initialize_1(0, 0, 0),
    macro_f_string_static_t_initialize_1("aa", 0, 2),
    macro_f_string_static_t_initialize_1("aa1", 0, 3),
    macro_f_string_static_t_initialize_1("aaone", 0, 5),
    macro_f_string_static_t_initialize_1("aaOne", 0, 5),
    macro_f_string_static_t_initialize_1("aa\0ne", 0, 5),
    macro_f_string_static_t_initialize_1("aao\0ne", 0, 6),
    macro_f_string_static_t_initialize_1("aaone\0", 0, 6),

    // 7.
    macro_f_string_static_t_initialize_1(0, 0, 0),
    macro_f_string_static_t_initialize_1("aa", 0, 2),
    macro_f_string_static_t_initialize_1("aa1", 0, 3),
    macro_f_string_static_t_initialize_1("aaone", 0, 5),
    macro_f_string_static_t_initialize_1("aaOne", 0, 5),
    macro_f_string_static_t_initialize_1("aa\0ne", 0, 5),
    macro_f_string_static_t_initialize_1("aao\0ne", 0, 6),
    macro_f_string_static_t_initialize_1("aaone\0", 0, 6),

    // 8.
    macro_f_string_static_t_initialize_1(0, 0, 0),
    macro_f_string_static_t_initialize_1("aa", 0, 2),
    macro_f_string_static_t_initialize_1("aa1", 0, 3),
    macro_f_string_static_t_initialize_1("aaone", 0, 5),
    macro_f_string_static_t_initialize_1("aaOne", 0, 5),
    macro_f_string_static_t_initialize_1("aa\0ne", 0, 5),
    macro_f_string_static_t_initialize_1("aao\0ne", 0, 6),
    macro_f_string_static_t_initialize_1("aaone\0", 0, 6),
  };

  f_range_t range_2 = macro_f_range_t_initialize_1(2, 0);

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

  uint8_t i = 0;

  f_status_t status = F_okay;
  f_utf_string_dynamic_t utf_string_1 = f_utf_string_dynamic_t_initialize;
  f_utf_string_dynamic_t utf_string_2 = f_utf_string_dynamic_t_initialize;

  // First eight are against empty strings for first argument.
  for (; i < 8; ++i) {

    utf_string_1.used = 0;
    utf_string_2.used = 0;

    status = test_convert_dynamic_to_utf(string_1s[i], &utf_string_1);
    assert_int_equal(status, F_okay);

    status = test_convert_dynamic_to_utf(string_2s[i], &utf_string_2);
    assert_int_equal(status, F_okay);

    if (i % 8 == 0) {
      status = f_compare_utf_dynamic_partial_trim_dynamic(utf_string_1, utf_string_2, f_range_empty_c);
    }
    else {
      range_2.stop = string_2s[i].used - 1;

      status = f_compare_utf_dynamic_partial_trim_dynamic(utf_string_1, utf_string_2, range_2);
    }

    assert_int_equal(status, expects[i]);
  } // for

  for (; i < 64; ++i) {

    utf_string_1.used = 0;
    utf_string_2.used = 0;

    status = test_convert_dynamic_to_utf(string_1s[i], &utf_string_1);
    assert_int_equal(status, F_okay);

    status = test_convert_dynamic_to_utf(string_2s[i], &utf_string_2);
    assert_int_equal(status, F_okay);

    if (i % 8 == 0) {
      status = f_compare_utf_dynamic_partial_trim_dynamic(utf_string_1, utf_string_2, f_range_empty_c);
    }
    else {
      range_2.stop = string_2s[i].used - 1;

      status = f_compare_utf_dynamic_partial_trim_dynamic(utf_string_1, utf_string_2, range_2);
    }

    assert_int_equal(status, expects[i]);
  } // for

  free((void *) utf_string_1.string);
  free((void *) utf_string_2.string);
}

#ifdef __cplusplus
} // extern "C"
#endif
