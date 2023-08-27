#include "test-compare.h"
#include "test-compare-utf_except.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_compare_utf_except__works(void **state) {

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
    macro_f_string_static_t_initialize_1("SKIP", 0, 4),
    macro_f_string_static_t_initialize_1("SKIP", 0, 4),
    macro_f_string_static_t_initialize_1("SKIP", 0, 4),
    macro_f_string_static_t_initialize_1("SKIP", 0, 4),
    macro_f_string_static_t_initialize_1("SKIP", 0, 4),
    macro_f_string_static_t_initialize_1("SKIP", 0, 4),
    macro_f_string_static_t_initialize_1("SKIP", 0, 4),
    macro_f_string_static_t_initialize_1("SKIP", 0, 4),

    // 3.
    macro_f_string_static_t_initialize_1("SKIP1", 0, 5),
    macro_f_string_static_t_initialize_1("SKIP1", 0, 5),
    macro_f_string_static_t_initialize_1("SKIP1", 0, 5),
    macro_f_string_static_t_initialize_1("SKIP1", 0, 5),
    macro_f_string_static_t_initialize_1("SKIP1", 0, 5),
    macro_f_string_static_t_initialize_1("SKIP1", 0, 5),
    macro_f_string_static_t_initialize_1("SKIP1", 0, 5),
    macro_f_string_static_t_initialize_1("SKIP1", 0, 5),

    // 4.
    macro_f_string_static_t_initialize_1("SKIPone", 0, 7),
    macro_f_string_static_t_initialize_1("SKIPone", 0, 7),
    macro_f_string_static_t_initialize_1("SKIPone", 0, 7),
    macro_f_string_static_t_initialize_1("SKIPone", 0, 7),
    macro_f_string_static_t_initialize_1("SKIPone", 0, 7),
    macro_f_string_static_t_initialize_1("SKIPone", 0, 7),
    macro_f_string_static_t_initialize_1("SKIPone", 0, 7),
    macro_f_string_static_t_initialize_1("SKIPone", 0, 7),

    // 5.
    macro_f_string_static_t_initialize_1("SKIPOne", 0, 7),
    macro_f_string_static_t_initialize_1("SKIPOne", 0, 7),
    macro_f_string_static_t_initialize_1("SKIPOne", 0, 7),
    macro_f_string_static_t_initialize_1("SKIPOne", 0, 7),
    macro_f_string_static_t_initialize_1("SKIPOne", 0, 7),
    macro_f_string_static_t_initialize_1("SKIPOne", 0, 7),
    macro_f_string_static_t_initialize_1("SKIPOne", 0, 7),
    macro_f_string_static_t_initialize_1("SKIPOne", 0, 7),

    // 6.
    macro_f_string_static_t_initialize_1("SKIP\0ne", 0, 7),
    macro_f_string_static_t_initialize_1("SKIP\0ne", 0, 7),
    macro_f_string_static_t_initialize_1("SKIP\0ne", 0, 7),
    macro_f_string_static_t_initialize_1("SKIP\0ne", 0, 7),
    macro_f_string_static_t_initialize_1("SKIP\0ne", 0, 7),
    macro_f_string_static_t_initialize_1("SKIP\0ne", 0, 7),
    macro_f_string_static_t_initialize_1("SKIP\0ne", 0, 7),
    macro_f_string_static_t_initialize_1("SKIP\0ne", 0, 7),

    // 7.
    macro_f_string_static_t_initialize_1("SKIPo\0ne", 0, 8),
    macro_f_string_static_t_initialize_1("SKIPo\0ne", 0, 8),
    macro_f_string_static_t_initialize_1("SKIPo\0ne", 0, 8),
    macro_f_string_static_t_initialize_1("SKIPo\0ne", 0, 8),
    macro_f_string_static_t_initialize_1("SKIPo\0ne", 0, 8),
    macro_f_string_static_t_initialize_1("SKIPo\0ne", 0, 8),
    macro_f_string_static_t_initialize_1("SKIPo\0ne", 0, 8),
    macro_f_string_static_t_initialize_1("SKIPo\0ne", 0, 8),

    // 8.
    macro_f_string_static_t_initialize_1("SKIPone\0", 0, 8),
    macro_f_string_static_t_initialize_1("SKIPone\0", 0, 8),
    macro_f_string_static_t_initialize_1("SKIPone\0", 0, 8),
    macro_f_string_static_t_initialize_1("SKIPone\0", 0, 8),
    macro_f_string_static_t_initialize_1("SKIPone\0", 0, 8),
    macro_f_string_static_t_initialize_1("SKIPone\0", 0, 8),
    macro_f_string_static_t_initialize_1("SKIPone\0", 0, 8),
    macro_f_string_static_t_initialize_1("SKIPone\0", 0, 8),
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

  f_status_t status = F_okay;
  f_utf_string_dynamic_t utf_string_1 = f_utf_string_dynamic_t_initialize;
  f_utf_string_dynamic_t utf_string_2 = f_utf_string_dynamic_t_initialize;

  for (; i < 64; ++i) {

    utf_string_1.used = 0;
    utf_string_2.used = 0;

    status = test_convert_dynamic_to_utf(string_1s[i], &utf_string_1);
    assert_int_equal(status, F_okay);

    status = test_convert_dynamic_to_utf(string_2s[i], &utf_string_2);
    assert_int_equal(status, F_okay);

    status = f_compare_utf_except(utf_string_1.string, utf_string_2.string, utf_string_1.used, utf_string_2.used, excepts_1, excepts_2);

    assert_int_equal(status, expects[i]);
  } // for

  for (i = 0; i < 64; ++i) {

    utf_string_1.used = 0;
    utf_string_2.used = 0;

    status = test_convert_dynamic_to_utf(string_1s[i], &utf_string_1);
    assert_int_equal(status, F_okay);

    status = test_convert_dynamic_to_utf(string_2s[i], &utf_string_2);
    assert_int_equal(status, F_okay);

    status = f_compare_utf_except(utf_string_2.string, utf_string_1.string, utf_string_2.used, utf_string_1.used, excepts_2, excepts_1);

    assert_int_equal(status, expects[i]);
  } // for

  free((void *) utf_string_1.string);
  free((void *) utf_string_2.string);
}

#ifdef __cplusplus
} // extern "C"
#endif
