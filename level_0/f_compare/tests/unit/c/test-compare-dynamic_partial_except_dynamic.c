#include "test-compare.h"
#include "test-compare-dynamic_partial_except_dynamic.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_compare_dynamic_partial_except_dynamic__works(void **state) {

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

  f_string_range_t range_2 = macro_f_string_range_t_initialize_1(2, 0);

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

  // First eight are against empty strings for first argument.
  for (; i < 8; ++i) {

    if (i % 8 == 0) {
      status = f_compare_dynamic_partial_except_dynamic(string_1s[i], string_2s[i], f_string_range_empty_c, excepts_1, excepts_2);
    }
    else {
      range_2.stop = string_2s[i].used - 1;

      status = f_compare_dynamic_partial_except_dynamic(string_1s[i], string_2s[i], range_2, excepts_1, excepts_2);
    }

    assert_int_equal(status, expects[i]);
  } // for

  for (; i < 64; ++i) {

    if (i % 8 == 0) {
      status = f_compare_dynamic_partial_except_dynamic(string_1s[i], string_2s[i], f_string_range_empty_c, excepts_1, excepts_2);
    }
    else {
      range_2.stop = string_2s[i].used - 1;

      status = f_compare_dynamic_partial_except_dynamic(string_1s[i], string_2s[i], range_2, excepts_1, excepts_2);
    }

    assert_int_equal(status, expects[i]);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
