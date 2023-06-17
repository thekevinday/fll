#include "test-compare.h"
#include "test-compare-dynamic_except_trim_string.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_compare_dynamic_except_trim_string__works(void **state) {

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

  for (; i < 64; ++i) {

    const f_status_t status = f_compare_dynamic_except_trim_string(string_1s[i].string, string_2s[i], string_1s[i].used, excepts_1, excepts_2);

    assert_int_equal(status, expects[i]);
  } // for

  for (i = 0; i < 64; ++i) {

    const f_status_t status = f_compare_dynamic_except_trim_string(string_2s[i].string, string_1s[i], string_2s[i].used, excepts_2, excepts_1);

    assert_int_equal(status, expects[i]);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
