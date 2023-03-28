#include "test-compare.h"
#include "test-compare-dynamic_partial_dynamic.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_compare_dynamic_partial_trim_dynamic__works(void **state) {

  // A necessary work-around to to have "\01" with the "\0" being separate from the "1".
  f_char_t null_before_one[] = {
    '\0', '1'
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
    macro_f_string_static_t_initialize(" ", 0, 1),
    macro_f_string_static_t_initialize("\t", 0, 1),
    macro_f_string_static_t_initialize("\0", 0, 1),
    macro_f_string_static_t_initialize("    ", 0, 4),
    macro_f_string_static_t_initialize("  \t ", 0, 4),
    macro_f_string_static_t_initialize("\0 \0\t", 0, 4),
    macro_f_string_static_t_initialize("\0 \0", 0, 3),
    macro_f_string_static_t_initialize("\0\0\t", 0, 3),

    // 3.
    macro_f_string_static_t_initialize(" 1", 0, 2),
    macro_f_string_static_t_initialize("\t1", 0, 2),
    macro_f_string_static_t_initialize(null_before_one, 0, 2),
    macro_f_string_static_t_initialize("  1  ", 0, 5),
    macro_f_string_static_t_initialize("  1\t ", 0, 5),
    macro_f_string_static_t_initialize("\01 \0\t", 0, 5),
    macro_f_string_static_t_initialize("\0 \01", 0, 4),
    macro_f_string_static_t_initialize("1\0\0\t", 0, 4),

    // 4.
    macro_f_string_static_t_initialize(" one", 0, 4),
    macro_f_string_static_t_initialize("\tone", 0, 4),
    macro_f_string_static_t_initialize("\0one", 0, 4),
    macro_f_string_static_t_initialize("  one  ", 0, 7),
    macro_f_string_static_t_initialize("  one\t ", 0, 7),
    macro_f_string_static_t_initialize("\0one \0\t", 0, 7),
    macro_f_string_static_t_initialize("\0 \0one", 0, 6),
    macro_f_string_static_t_initialize("one\0\0\t", 0, 6),

    // 5.
    macro_f_string_static_t_initialize(" One", 0, 4),
    macro_f_string_static_t_initialize("\tOne", 0, 4),
    macro_f_string_static_t_initialize("\0One", 0, 4),
    macro_f_string_static_t_initialize("  One  ", 0, 7),
    macro_f_string_static_t_initialize("  One\t ", 0, 7),
    macro_f_string_static_t_initialize("\0One \0\t", 0, 7),
    macro_f_string_static_t_initialize("\0 \0One", 0, 6),
    macro_f_string_static_t_initialize("One\0\0\t", 0, 6),

    // 6.
    macro_f_string_static_t_initialize(" \0ne", 0, 4),
    macro_f_string_static_t_initialize("\t\0ne", 0, 4),
    macro_f_string_static_t_initialize("\0\0ne", 0, 4),
    macro_f_string_static_t_initialize("  \0ne  ", 0, 7),
    macro_f_string_static_t_initialize("  \0ne\t ", 0, 7),
    macro_f_string_static_t_initialize("\0\0ne \0\t", 0, 7),
    macro_f_string_static_t_initialize("\0 \0\0ne", 0, 6),
    macro_f_string_static_t_initialize("\0ne\0\0\t", 0, 6),

    // 7.
    macro_f_string_static_t_initialize(" o\0ne", 0, 5),
    macro_f_string_static_t_initialize("\to\0ne", 0, 5),
    macro_f_string_static_t_initialize("\0o\0ne", 0, 5),
    macro_f_string_static_t_initialize("  o\0ne  ", 0, 8),
    macro_f_string_static_t_initialize("  o\0ne\t ", 0, 8),
    macro_f_string_static_t_initialize("\0o\0ne \0\t", 0, 8),
    macro_f_string_static_t_initialize("\0 \0o\0ne", 0, 7),
    macro_f_string_static_t_initialize("o\0ne\0\0\t", 0, 7),

    // 8.
    macro_f_string_static_t_initialize(" one\0", 0, 5),
    macro_f_string_static_t_initialize("\tone\0", 0, 5),
    macro_f_string_static_t_initialize("\0one\0", 0, 5),
    macro_f_string_static_t_initialize("  one\0  ", 0, 8),
    macro_f_string_static_t_initialize("  one\0\t ", 0, 8),
    macro_f_string_static_t_initialize("\0one\0 \0\t", 0, 8),
    macro_f_string_static_t_initialize("\0 \0one\0", 0, 7),
    macro_f_string_static_t_initialize("one\0\0\0\t", 0, 7),
  };

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

  const f_string_range_t range_0 = macro_f_string_range_t_initialize(1, 0);
  f_string_range_t range_2 = macro_f_string_range_t_initialize(2, 0);

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
  f_status_t status = F_none;

  // First eight are against empty strings for first argument.
  for (; i < 8; ++i) {

    if (i % 8 == 0) {
      status = f_compare_dynamic_partial_trim_dynamic(string_1s[i], string_2s[i], range_0);
    }
    else {
      range_2.stop = string_2s[i].used - 1;

      status = f_compare_dynamic_partial_trim_dynamic(string_1s[i], string_2s[i], range_2);
    }

    assert_int_equal(status, expects[i]);
  } // for

  for (; i < 64; ++i) {

    if (i % 8 == 0) {
      status = f_compare_dynamic_partial_trim_dynamic(string_1s[i], string_2s[i], range_0);
    }
    else {
      range_2.stop = string_2s[i].used - 1;

      status = f_compare_dynamic_partial_trim_dynamic(string_1s[i], string_2s[i], range_2);
    }

    assert_int_equal(status, expects[i]);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
