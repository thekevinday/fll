#include "test-string.h"
#include "test-string-compare_dynamic_except_string.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__fl_string_dynamic_compare_except_string__works(void **state) {

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
    macro_f_string_static_t_initialize("SKIP", 0, 4),
    macro_f_string_static_t_initialize("SKIP", 0, 4),
    macro_f_string_static_t_initialize("SKIP", 0, 4),
    macro_f_string_static_t_initialize("SKIP", 0, 4),
    macro_f_string_static_t_initialize("SKIP", 0, 4),
    macro_f_string_static_t_initialize("SKIP", 0, 4),
    macro_f_string_static_t_initialize("SKIP", 0, 4),
    macro_f_string_static_t_initialize("SKIP", 0, 4),

    // 3.
    macro_f_string_static_t_initialize("SKIP1", 0, 5),
    macro_f_string_static_t_initialize("SKIP1", 0, 5),
    macro_f_string_static_t_initialize("SKIP1", 0, 5),
    macro_f_string_static_t_initialize("SKIP1", 0, 5),
    macro_f_string_static_t_initialize("SKIP1", 0, 5),
    macro_f_string_static_t_initialize("SKIP1", 0, 5),
    macro_f_string_static_t_initialize("SKIP1", 0, 5),
    macro_f_string_static_t_initialize("SKIP1", 0, 5),

    // 4.
    macro_f_string_static_t_initialize("SKIPone", 0, 7),
    macro_f_string_static_t_initialize("SKIPone", 0, 7),
    macro_f_string_static_t_initialize("SKIPone", 0, 7),
    macro_f_string_static_t_initialize("SKIPone", 0, 7),
    macro_f_string_static_t_initialize("SKIPone", 0, 7),
    macro_f_string_static_t_initialize("SKIPone", 0, 7),
    macro_f_string_static_t_initialize("SKIPone", 0, 7),
    macro_f_string_static_t_initialize("SKIPone", 0, 7),

    // 5.
    macro_f_string_static_t_initialize("SKIPOne", 0, 7),
    macro_f_string_static_t_initialize("SKIPOne", 0, 7),
    macro_f_string_static_t_initialize("SKIPOne", 0, 7),
    macro_f_string_static_t_initialize("SKIPOne", 0, 7),
    macro_f_string_static_t_initialize("SKIPOne", 0, 7),
    macro_f_string_static_t_initialize("SKIPOne", 0, 7),
    macro_f_string_static_t_initialize("SKIPOne", 0, 7),
    macro_f_string_static_t_initialize("SKIPOne", 0, 7),

    // 6.
    macro_f_string_static_t_initialize("SKIP\0ne", 0, 7),
    macro_f_string_static_t_initialize("SKIP\0ne", 0, 7),
    macro_f_string_static_t_initialize("SKIP\0ne", 0, 7),
    macro_f_string_static_t_initialize("SKIP\0ne", 0, 7),
    macro_f_string_static_t_initialize("SKIP\0ne", 0, 7),
    macro_f_string_static_t_initialize("SKIP\0ne", 0, 7),
    macro_f_string_static_t_initialize("SKIP\0ne", 0, 7),
    macro_f_string_static_t_initialize("SKIP\0ne", 0, 7),

    // 7.
    macro_f_string_static_t_initialize("SKIPo\0ne", 0, 8),
    macro_f_string_static_t_initialize("SKIPo\0ne", 0, 8),
    macro_f_string_static_t_initialize("SKIPo\0ne", 0, 8),
    macro_f_string_static_t_initialize("SKIPo\0ne", 0, 8),
    macro_f_string_static_t_initialize("SKIPo\0ne", 0, 8),
    macro_f_string_static_t_initialize("SKIPo\0ne", 0, 8),
    macro_f_string_static_t_initialize("SKIPo\0ne", 0, 8),
    macro_f_string_static_t_initialize("SKIPo\0ne", 0, 8),

    // 8.
    macro_f_string_static_t_initialize("SKIPone\0", 0, 8),
    macro_f_string_static_t_initialize("SKIPone\0", 0, 8),
    macro_f_string_static_t_initialize("SKIPone\0", 0, 8),
    macro_f_string_static_t_initialize("SKIPone\0", 0, 8),
    macro_f_string_static_t_initialize("SKIPone\0", 0, 8),
    macro_f_string_static_t_initialize("SKIPone\0", 0, 8),
    macro_f_string_static_t_initialize("SKIPone\0", 0, 8),
    macro_f_string_static_t_initialize("SKIPone\0", 0, 8),
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

    const f_status_t status = fl_string_dynamic_compare_except_string(string_1s[i].string, string_2s[i], string_1s[i].used, excepts_1, excepts_2);

    assert_int_equal(status, expects[i]);
  } // for

  for (i = 0; i < 64; ++i) {

    const f_status_t status = fl_string_dynamic_compare_except_string(string_2s[i].string, string_1s[i], string_2s[i].used, excepts_2, excepts_1);

    assert_int_equal(status, expects[i]);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
