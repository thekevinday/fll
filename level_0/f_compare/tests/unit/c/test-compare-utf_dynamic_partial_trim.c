#include "test-compare.h"
#include "test-compare-utf_dynamic_partial.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_compare_utf_dynamic_partial_trim__works(void **state) {

  // A necessary work-around to to have "\01" with the "\0" being separate from the "1".
  f_char_t null_before_one_1[] = {
    'x', 'x', 'x', '\0', '1', 'y', 'y', 'y'
  };

  f_char_t null_before_one_2[] = {
    'x', 'x', 'x', '\0', '1', ' ', '\0', '\t', 'y', 'y', 'y'
  };

  f_char_t null_before_one_3[] = {
    'x', 'x', 'x', '\0', ' ', '\0', '1', 'y', 'y', 'y'
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
    macro_f_string_static_t_initialize_1("xxx yyy", 0, 7),
    macro_f_string_static_t_initialize_1("xxx\tyyy", 0, 7),
    macro_f_string_static_t_initialize_1("xxx\0yyy", 0, 7),
    macro_f_string_static_t_initialize_1("xxx    yyy", 0, 10),
    macro_f_string_static_t_initialize_1("xxx  \t yyy", 0, 10),
    macro_f_string_static_t_initialize_1("xxx\0 \0\tyyy", 0, 10),
    macro_f_string_static_t_initialize_1("xxx\0 \0yyy", 0, 9),
    macro_f_string_static_t_initialize_1("xxx\0\0\tyyy", 0, 9),

    // 3.
    macro_f_string_static_t_initialize_1("xxx 1yyy", 0, 8),
    macro_f_string_static_t_initialize_1("xxx\t1yyy", 0, 8),
    macro_f_string_static_t_initialize_1(null_before_one_1, 0, 8),
    macro_f_string_static_t_initialize_1("xxx  1  yyy", 0, 11),
    macro_f_string_static_t_initialize_1("xxx  1\t yyy", 0, 11),
    macro_f_string_static_t_initialize_1(null_before_one_2, 0, 11),
    macro_f_string_static_t_initialize_1(null_before_one_3, 0, 10),
    macro_f_string_static_t_initialize_1("xxx1\0\0\tyyy", 0, 10),

    // 4.
    macro_f_string_static_t_initialize_1("xxx oneyyy", 0, 10),
    macro_f_string_static_t_initialize_1("xxx\toneyyy", 0, 10),
    macro_f_string_static_t_initialize_1("xxx\0oneyyy", 0, 10),
    macro_f_string_static_t_initialize_1("xxx  one  yyy", 0, 13),
    macro_f_string_static_t_initialize_1("xxx  one\t yyy", 0, 13),
    macro_f_string_static_t_initialize_1("xxx\0one \0\tyyy", 0, 13),
    macro_f_string_static_t_initialize_1("xxx\0 \0oneyyy", 0, 12),
    macro_f_string_static_t_initialize_1("xxxone\0\0\tyyy", 0, 12),

    // 5.
    macro_f_string_static_t_initialize_1("xxx Oneyyy", 0, 10),
    macro_f_string_static_t_initialize_1("xxx\tOneyyy", 0, 10),
    macro_f_string_static_t_initialize_1("xxx\0Oneyyy", 0, 10),
    macro_f_string_static_t_initialize_1("xxx  One  yyy", 0, 13),
    macro_f_string_static_t_initialize_1("xxx  One\t yyy", 0, 13),
    macro_f_string_static_t_initialize_1("xxx\0One \0\tyyy", 0, 13),
    macro_f_string_static_t_initialize_1("xxx\0 \0Oneyyy", 0, 12),
    macro_f_string_static_t_initialize_1("xxxOne\0\0\tyyy", 0, 12),

    // 6.
    macro_f_string_static_t_initialize_1("xxx \0neyyy", 0, 10),
    macro_f_string_static_t_initialize_1("xxx\t\0neyyy", 0, 10),
    macro_f_string_static_t_initialize_1("xxx\0\0neyyy", 0, 10),
    macro_f_string_static_t_initialize_1("xxx  \0ne  yyy", 0, 13),
    macro_f_string_static_t_initialize_1("xxx  \0ne\t yyy", 0, 13),
    macro_f_string_static_t_initialize_1("xxx\0\0ne \0\tyyy", 0, 13),
    macro_f_string_static_t_initialize_1("xxx\0 \0\0neyyy", 0, 12),
    macro_f_string_static_t_initialize_1("xxx\0ne\0\0\tyyy", 0, 12),

    // 7.
    macro_f_string_static_t_initialize_1("xxx o\0neyyy", 0, 11),
    macro_f_string_static_t_initialize_1("xxx\to\0neyyy", 0, 11),
    macro_f_string_static_t_initialize_1("xxx\0o\0neyyy", 0, 11),
    macro_f_string_static_t_initialize_1("xxx  o\0ne  yyy", 0, 14),
    macro_f_string_static_t_initialize_1("xxx  o\0ne\t yyy", 0, 14),
    macro_f_string_static_t_initialize_1("xxx\0o\0ne \0\tyyy", 0, 14),
    macro_f_string_static_t_initialize_1("xxx\0 \0o\0neyyy", 0, 13),
    macro_f_string_static_t_initialize_1("xxxo\0ne\0\0\tyyy", 0, 13),

    // 8.
    macro_f_string_static_t_initialize_1("xxx one\0yyy", 0, 11),
    macro_f_string_static_t_initialize_1("xxx\tone\0yyy", 0, 11),
    macro_f_string_static_t_initialize_1("xxx\0one\0yyy", 0, 11),
    macro_f_string_static_t_initialize_1("xxx  one\0  yyy", 0, 14),
    macro_f_string_static_t_initialize_1("xxx  one\0\t yyy", 0, 14),
    macro_f_string_static_t_initialize_1("xxx\0one\0 \0\tyyy", 0, 14),
    macro_f_string_static_t_initialize_1("xxx\0 \0one\0yyy", 0, 13),
    macro_f_string_static_t_initialize_1("xxxone\0\0\0\tyyy", 0, 13),
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

  f_string_range_t range_1 = macro_f_string_range_t_initialize_1(3, 9);
  f_string_range_t range_2 = macro_f_string_range_t_initialize_1(2, 0);

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
      status = f_compare_utf_dynamic_partial_trim(utf_string_1, utf_string_2, f_string_range_empty_c, f_string_range_empty_c);
    }
    else {
      range_2.stop = string_2s[i].used - 1;

      status = f_compare_utf_dynamic_partial_trim(utf_string_1, utf_string_2, f_string_range_empty_c, range_2);
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

    range_1.stop = string_1s[i].used - 4;

    if (i % 8 == 0) {
      status = f_compare_utf_dynamic_partial_trim(utf_string_1, utf_string_2, range_1, f_string_range_empty_c);
    }
    else {
      range_2.stop = string_2s[i].used - 1;

      status = f_compare_utf_dynamic_partial_trim(utf_string_1, utf_string_2, range_1, range_2);
    }

    assert_int_equal(status, expects[i]);
  } // for

  free((void *) utf_string_1.string);
  free((void *) utf_string_2.string);
}

#ifdef __cplusplus
} // extern "C"
#endif
