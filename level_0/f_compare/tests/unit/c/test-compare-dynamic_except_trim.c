#include "test-compare.h"
#include "test-compare-dynamic_except_trim.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_compare_dynamic_except_trim__works(void **state) {

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

  f_array_length_t except_1[] = {
    0, 1, 2, 3,
  };
  const f_array_lengths_t excepts_1 = macro_f_array_lengths_t_initialize(except_1, 0, 4);
  const f_array_lengths_t excepts_2 = f_array_lengths_t_initialize;
  uint8_t i = 0;

  for (; i < 64; ++i) {

    const f_status_t status = f_compare_dynamic_except_trim(string_1s[i], string_2s[i], excepts_1, excepts_2);

    assert_int_equal(status, expects[i]);
  } // for

  for (i = 0; i < 64; ++i) {

    const f_status_t status = f_compare_dynamic_except_trim(string_2s[i], string_1s[i], excepts_2, excepts_1);

    assert_int_equal(status, expects[i]);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif