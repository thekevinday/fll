#include "test-string.h"
#include "test-string-compare_dynamic_partial_except_trim.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__fl_string_dynamic_partial_compare_except_trim__works(void **state) {

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
    macro_f_string_static_t_initialize(0, 0, 0),
    macro_f_string_static_t_initialize(0, 0, 0),
    macro_f_string_static_t_initialize(0, 0, 0),
    macro_f_string_static_t_initialize(0, 0, 0),
    macro_f_string_static_t_initialize(0, 0, 0),
    macro_f_string_static_t_initialize(0, 0, 0),
    macro_f_string_static_t_initialize(0, 0, 0),
    macro_f_string_static_t_initialize(0, 0, 0),

    // 2.
    macro_f_string_static_t_initialize("SKIP ", 0, 5),
    macro_f_string_static_t_initialize("SKIP\t", 0, 5),
    macro_f_string_static_t_initialize("SKIP\0", 0, 5),
    macro_f_string_static_t_initialize("SKIP    ", 0, 8),
    macro_f_string_static_t_initialize("SKIP  \t ", 0, 8),
    macro_f_string_static_t_initialize("SKIP\0 \0\t", 0, 8),
    macro_f_string_static_t_initialize("SKIP\0 \0", 0, 7),
    macro_f_string_static_t_initialize("SKIP\0\0\t", 0, 7),

    // 3.
    macro_f_string_static_t_initialize("SKIP 1", 0, 6),
    macro_f_string_static_t_initialize("SKIP\t1", 0, 6),
    macro_f_string_static_t_initialize(null_before_one_1, 0, 6),
    macro_f_string_static_t_initialize("SKIP  1  ", 0, 9),
    macro_f_string_static_t_initialize("SKIP  1\t ", 0, 9),
    macro_f_string_static_t_initialize(null_before_one_2, 0, 9),
    macro_f_string_static_t_initialize(null_before_one_3, 0, 8),
    macro_f_string_static_t_initialize("SKIP1\0\0\t", 0, 8),

    // 4.
    macro_f_string_static_t_initialize("SKIP one", 0, 8),
    macro_f_string_static_t_initialize("SKIP\tone", 0, 8),
    macro_f_string_static_t_initialize("SKIP\0one", 0, 8),
    macro_f_string_static_t_initialize("SKIP  one  ", 0, 11),
    macro_f_string_static_t_initialize("SKIP  one\t ", 0, 11),
    macro_f_string_static_t_initialize("SKIP\0one \0\t", 0, 11),
    macro_f_string_static_t_initialize("SKIP\0 \0one", 0, 10),
    macro_f_string_static_t_initialize("SKIPone\0\0\t", 0, 10),

    // 5.
    macro_f_string_static_t_initialize("SKIP One", 0, 8),
    macro_f_string_static_t_initialize("SKIP\tOne", 0, 8),
    macro_f_string_static_t_initialize("SKIP\0One", 0, 8),
    macro_f_string_static_t_initialize("SKIP  One  ", 0, 11),
    macro_f_string_static_t_initialize("SKIP  One\t ", 0, 11),
    macro_f_string_static_t_initialize("SKIP\0One \0\t", 0, 11),
    macro_f_string_static_t_initialize("SKIP\0 \0One", 0, 10),
    macro_f_string_static_t_initialize("SKIPOne\0\0\t", 0, 10),

    // 6.
    macro_f_string_static_t_initialize("SKIP \0ne", 0, 8),
    macro_f_string_static_t_initialize("SKIP\t\0ne", 0, 8),
    macro_f_string_static_t_initialize("SKIP\0\0ne", 0, 8),
    macro_f_string_static_t_initialize("SKIP  \0ne  ", 0, 11),
    macro_f_string_static_t_initialize("SKIP  \0ne\t ", 0, 11),
    macro_f_string_static_t_initialize("SKIP\0\0ne \0\t", 0, 11),
    macro_f_string_static_t_initialize("SKIP\0 \0\0ne", 0, 10),
    macro_f_string_static_t_initialize("SKIP\0ne\0\0\t", 0, 10),

    // 7.
    macro_f_string_static_t_initialize("SKIP o\0ne", 0, 9),
    macro_f_string_static_t_initialize("SKIP\to\0ne", 0, 9),
    macro_f_string_static_t_initialize("SKIP\0o\0ne", 0, 9),
    macro_f_string_static_t_initialize("SKIP  o\0ne  ", 0, 12),
    macro_f_string_static_t_initialize("SKIP  o\0ne\t ", 0, 12),
    macro_f_string_static_t_initialize("SKIP\0o\0ne \0\t", 0, 12),
    macro_f_string_static_t_initialize("SKIP\0 \0o\0ne", 0, 11),
    macro_f_string_static_t_initialize("SKIPo\0ne\0\0\t", 0, 11),

    // 8.
    macro_f_string_static_t_initialize("SKIP one\0", 0, 9),
    macro_f_string_static_t_initialize("SKIP\tone\0", 0, 9),
    macro_f_string_static_t_initialize("SKIP\0one\0", 0, 9),
    macro_f_string_static_t_initialize("SKIP  one\0  ", 0, 12),
    macro_f_string_static_t_initialize("SKIP  one\0\t ", 0, 12),
    macro_f_string_static_t_initialize("SKIP\0one\0 \0\t", 0, 12),
    macro_f_string_static_t_initialize("SKIP\0 \0one\0", 0, 11),
    macro_f_string_static_t_initialize("SKIPone\0\0\0\t", 0, 11),
  };

  f_string_range_t range_1 = macro_f_string_range_t_initialize(3, 9);
  f_string_range_t range_2 = macro_f_string_range_t_initialize(2, 0);

  const f_string_static_t string_2s[] = {

    // 1.
    macro_f_string_static_t_initialize(0, 0, 0),
    macro_f_string_static_t_initialize("aa", 0, 2),
    macro_f_string_static_t_initialize("aa1", 0, 3),
    macro_f_string_static_t_initialize("aaone", 0, 5),
    macro_f_string_static_t_initialize("aaOne", 0, 5),
    macro_f_string_static_t_initialize("aa\0ne", 0, 5),
    macro_f_string_static_t_initialize("aao\0ne", 0, 6),
    macro_f_string_static_t_initialize("aaone\0", 0, 6),

    // 2.
    macro_f_string_static_t_initialize(0, 0, 0),
    macro_f_string_static_t_initialize("aa", 0, 2),
    macro_f_string_static_t_initialize("aa1", 0, 3),
    macro_f_string_static_t_initialize("aaone", 0, 5),
    macro_f_string_static_t_initialize("aaOne", 0, 5),
    macro_f_string_static_t_initialize("aa\0ne", 0, 5),
    macro_f_string_static_t_initialize("aao\0ne", 0, 6),
    macro_f_string_static_t_initialize("aaone\0", 0, 6),

    // 3.
    macro_f_string_static_t_initialize(0, 0, 0),
    macro_f_string_static_t_initialize("aa", 0, 2),
    macro_f_string_static_t_initialize("aa1", 0, 3),
    macro_f_string_static_t_initialize("aaone", 0, 5),
    macro_f_string_static_t_initialize("aaOne", 0, 5),
    macro_f_string_static_t_initialize("aa\0ne", 0, 5),
    macro_f_string_static_t_initialize("aao\0ne", 0, 6),
    macro_f_string_static_t_initialize("aaone\0", 0, 6),

    // 4.
    macro_f_string_static_t_initialize(0, 0, 0),
    macro_f_string_static_t_initialize("aa", 0, 2),
    macro_f_string_static_t_initialize("aa1", 0, 3),
    macro_f_string_static_t_initialize("aaone", 0, 5),
    macro_f_string_static_t_initialize("aaOne", 0, 5),
    macro_f_string_static_t_initialize("aa\0ne", 0, 5),
    macro_f_string_static_t_initialize("aao\0ne", 0, 6),
    macro_f_string_static_t_initialize("aaone\0", 0, 6),

    // 5.
    macro_f_string_static_t_initialize(0, 0, 0),
    macro_f_string_static_t_initialize("aa", 0, 2),
    macro_f_string_static_t_initialize("aa1", 0, 3),
    macro_f_string_static_t_initialize("aaone", 0, 5),
    macro_f_string_static_t_initialize("aaOne", 0, 5),
    macro_f_string_static_t_initialize("aa\0ne", 0, 5),
    macro_f_string_static_t_initialize("aao\0ne", 0, 6),
    macro_f_string_static_t_initialize("aaone\0", 0, 6),

    // 6.
    macro_f_string_static_t_initialize(0, 0, 0),
    macro_f_string_static_t_initialize("aa", 0, 2),
    macro_f_string_static_t_initialize("aa1", 0, 3),
    macro_f_string_static_t_initialize("aaone", 0, 5),
    macro_f_string_static_t_initialize("aaOne", 0, 5),
    macro_f_string_static_t_initialize("aa\0ne", 0, 5),
    macro_f_string_static_t_initialize("aao\0ne", 0, 6),
    macro_f_string_static_t_initialize("aaone\0", 0, 6),

    // 7.
    macro_f_string_static_t_initialize(0, 0, 0),
    macro_f_string_static_t_initialize("aa", 0, 2),
    macro_f_string_static_t_initialize("aa1", 0, 3),
    macro_f_string_static_t_initialize("aaone", 0, 5),
    macro_f_string_static_t_initialize("aaOne", 0, 5),
    macro_f_string_static_t_initialize("aa\0ne", 0, 5),
    macro_f_string_static_t_initialize("aao\0ne", 0, 6),
    macro_f_string_static_t_initialize("aaone\0", 0, 6),

    // 8.
    macro_f_string_static_t_initialize(0, 0, 0),
    macro_f_string_static_t_initialize("aa", 0, 2),
    macro_f_string_static_t_initialize("aa1", 0, 3),
    macro_f_string_static_t_initialize("aaone", 0, 5),
    macro_f_string_static_t_initialize("aaOne", 0, 5),
    macro_f_string_static_t_initialize("aa\0ne", 0, 5),
    macro_f_string_static_t_initialize("aao\0ne", 0, 6),
    macro_f_string_static_t_initialize("aaone\0", 0, 6),
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

  f_array_length_t except_1[] = {
    0, 1, 2, 3,
  };
  const f_array_lengths_t excepts_1 = macro_f_array_lengths_t_initialize(except_1, 0, 4);
  const f_array_lengths_t excepts_2 = f_array_lengths_t_initialize;
  uint8_t i = 0;
  f_status_t status = F_none;

  // First eight are against empty strings for first argument.
  for (; i < 8; ++i) {

    if (i % 8 == 0) {
      status = fl_string_dynamic_partial_compare_except_trim(string_1s[i], string_2s[i], range_1, f_string_range_empty_c, excepts_1, excepts_2);
    }
    else {
      range_2.stop = string_2s[i].used - 1;

      status = fl_string_dynamic_partial_compare_except_trim(string_1s[i], string_2s[i], range_1, range_2, excepts_1, excepts_2);
    }

    assert_int_equal(status, expects[i]);
  } // for

  for (; i < 64; ++i) {

    range_1.stop = string_1s[i].used - 1;

    if (i % 8 == 0) {
      status = fl_string_dynamic_partial_compare_except_trim(string_1s[i], string_2s[i], range_1, f_string_range_empty_c, excepts_1, excepts_2);
    }
    else {
      range_2.stop = string_2s[i].used - 1;

      status = fl_string_dynamic_partial_compare_except_trim(string_1s[i], string_2s[i], range_1, range_2, excepts_1, excepts_2);
    }

    assert_int_equal(status, expects[i]);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
