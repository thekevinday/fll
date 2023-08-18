#include "test-compare.h"
#include "test-compare-dynamic_partial_string.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_compare_dynamic_partial_trim_string__works(void **state) {

  // A necessary work-around to to have "\01" with the "\0" being separate from the "1".
  f_char_t null_before_one_1[] = {
    'x', 'x', 'x', '\0', '1'
  };

  f_char_t null_before_one_2[] = {
    'x', 'x', 'x', '\0', '1', ' ', '\0', '\t'
  };

  f_char_t null_before_one_3[] = {
    'x', 'x', 'x', '\0', ' ', '\0', '1'
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
    macro_f_string_static_t_initialize_1("xxx ", 0, 4),
    macro_f_string_static_t_initialize_1("xxx\t", 0, 4),
    macro_f_string_static_t_initialize_1("xxx\0", 0, 4),
    macro_f_string_static_t_initialize_1("xxx    ", 0, 7),
    macro_f_string_static_t_initialize_1("xxx  \t ", 0, 7),
    macro_f_string_static_t_initialize_1("xxx\0 \0\t", 0, 7),
    macro_f_string_static_t_initialize_1("xxx\0 \0", 0, 6),
    macro_f_string_static_t_initialize_1("xxx\0\0\t", 0, 6),

    // 3.
    macro_f_string_static_t_initialize_1("xxx 1", 0, 5),
    macro_f_string_static_t_initialize_1("xxx\t1", 0, 5),
    macro_f_string_static_t_initialize_1(null_before_one_1, 0, 5),
    macro_f_string_static_t_initialize_1("xxx  1  ", 0, 8),
    macro_f_string_static_t_initialize_1("xxx  1\t ", 0, 8),
    macro_f_string_static_t_initialize_1(null_before_one_2, 0, 8),
    macro_f_string_static_t_initialize_1(null_before_one_3, 0, 7),
    macro_f_string_static_t_initialize_1("xxx1\0\0\t", 0, 7),

    // 4.
    macro_f_string_static_t_initialize_1("xxx one", 0, 7),
    macro_f_string_static_t_initialize_1("xxx\tone", 0, 7),
    macro_f_string_static_t_initialize_1("xxx\0one", 0, 7),
    macro_f_string_static_t_initialize_1("xxx  one  ", 0, 10),
    macro_f_string_static_t_initialize_1("xxx  one\t ", 0, 10),
    macro_f_string_static_t_initialize_1("xxx\0one \0\t", 0, 10),
    macro_f_string_static_t_initialize_1("xxx\0 \0one", 0, 9),
    macro_f_string_static_t_initialize_1("xxxone\0\0\t", 0, 9),

    // 5.
    macro_f_string_static_t_initialize_1("xxx One", 0, 7),
    macro_f_string_static_t_initialize_1("xxx\tOne", 0, 7),
    macro_f_string_static_t_initialize_1("xxx\0One", 0, 7),
    macro_f_string_static_t_initialize_1("xxx  One  ", 0, 10),
    macro_f_string_static_t_initialize_1("xxx  One\t ", 0, 10),
    macro_f_string_static_t_initialize_1("xxx\0One \0\t", 0, 10),
    macro_f_string_static_t_initialize_1("xxx\0 \0One", 0, 9),
    macro_f_string_static_t_initialize_1("xxxOne\0\0\t", 0, 9),

    // 6.
    macro_f_string_static_t_initialize_1("xxx \0ne", 0, 7),
    macro_f_string_static_t_initialize_1("xxx\t\0ne", 0, 7),
    macro_f_string_static_t_initialize_1("xxx\0\0ne", 0, 7),
    macro_f_string_static_t_initialize_1("xxx  \0ne  ", 0, 10),
    macro_f_string_static_t_initialize_1("xxx  \0ne\t ", 0, 10),
    macro_f_string_static_t_initialize_1("xxx\0\0ne \0\t", 0, 10),
    macro_f_string_static_t_initialize_1("xxx\0 \0\0ne", 0, 9),
    macro_f_string_static_t_initialize_1("xxx\0ne\0\0\t", 0, 9),

    // 7.
    macro_f_string_static_t_initialize_1("xxx o\0ne", 0, 8),
    macro_f_string_static_t_initialize_1("xxx\to\0ne", 0, 8),
    macro_f_string_static_t_initialize_1("xxx\0o\0ne", 0, 8),
    macro_f_string_static_t_initialize_1("xxx  o\0ne  ", 0, 11),
    macro_f_string_static_t_initialize_1("xxx  o\0ne\t ", 0, 11),
    macro_f_string_static_t_initialize_1("xxx\0o\0ne \0\t", 0, 11),
    macro_f_string_static_t_initialize_1("xxx\0 \0o\0ne", 0, 10),
    macro_f_string_static_t_initialize_1("xxxo\0ne\0\0\t", 0, 10),

    // 8.
    macro_f_string_static_t_initialize_1("xxx one\0", 0, 8),
    macro_f_string_static_t_initialize_1("xxx\tone\0", 0, 8),
    macro_f_string_static_t_initialize_1("xxx\0one\0", 0, 8),
    macro_f_string_static_t_initialize_1("xxx  one\0  ", 0, 11),
    macro_f_string_static_t_initialize_1("xxx  one\0\t ", 0, 11),
    macro_f_string_static_t_initialize_1("xxx\0one\0 \0\t", 0, 11),
    macro_f_string_static_t_initialize_1("xxx\0 \0one\0", 0, 10),
    macro_f_string_static_t_initialize_1("xxxone\0\0\0\t", 0, 10),
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

  // First eight are against empty strings for first argument.
  for (; i < 8; ++i) {

    if (i % 8 == 0) {
      status = f_compare_dynamic_partial_trim_string(string_1s[i].string, string_2s[i], 0, f_string_range_empty_c);
    }
    else {
      range_2.stop = string_2s[i].used - 1;

      status = f_compare_dynamic_partial_trim_string(string_1s[i].string, string_2s[i], 0, range_2);
    }

    assert_int_equal(status, expects[i]);
  } // for

  for (; i < 64; ++i) {

    range_1.stop = string_1s[i].used - 1;

    if (i % 8 == 0) {
      status = f_compare_dynamic_partial_trim_string(string_1s[i].string + range_1.start, string_2s[i], (range_1.stop - range_1.start) + 1, f_string_range_empty_c);
    }
    else {
      range_2.stop = string_2s[i].used - 1;

      status = f_compare_dynamic_partial_trim_string(string_1s[i].string + range_1.start, string_2s[i], (range_1.stop - range_1.start) + 1, range_2);
    }

    assert_int_equal(status, expects[i]);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
