#include "test-utf.h"
#include "test-utf-string_dynamic_partial_compare.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__fl_utf_string_dynamic_partial_compare__works(void **state) {

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
    macro_f_string_static_t_initialize("xxxyyy", 0, 6),
    macro_f_string_static_t_initialize("xxxyyy", 0, 6),
    macro_f_string_static_t_initialize("xxxyyy", 0, 6),
    macro_f_string_static_t_initialize("xxxyyy", 0, 6),
    macro_f_string_static_t_initialize("xxxyyy", 0, 6),
    macro_f_string_static_t_initialize("xxxyyy", 0, 6),
    macro_f_string_static_t_initialize("xxxyyy", 0, 6),
    macro_f_string_static_t_initialize("xxxyyy", 0, 6),

    // 3.
    macro_f_string_static_t_initialize("xxx1yyy", 0, 7),
    macro_f_string_static_t_initialize("xxx1yyy", 0, 7),
    macro_f_string_static_t_initialize("xxx1yyy", 0, 7),
    macro_f_string_static_t_initialize("xxx1yyy", 0, 7),
    macro_f_string_static_t_initialize("xxx1yyy", 0, 7),
    macro_f_string_static_t_initialize("xxx1yyy", 0, 7),
    macro_f_string_static_t_initialize("xxx1yyy", 0, 7),
    macro_f_string_static_t_initialize("xxx1yyy", 0, 7),

    // 4.
    macro_f_string_static_t_initialize("xxxoneyyy", 0, 9),
    macro_f_string_static_t_initialize("xxxoneyyy", 0, 9),
    macro_f_string_static_t_initialize("xxxoneyyy", 0, 9),
    macro_f_string_static_t_initialize("xxxoneyyy", 0, 9),
    macro_f_string_static_t_initialize("xxxoneyyy", 0, 9),
    macro_f_string_static_t_initialize("xxxoneyyy", 0, 9),
    macro_f_string_static_t_initialize("xxxoneyyy", 0, 9),
    macro_f_string_static_t_initialize("xxxoneyyy", 0, 9),

    // 5.
    macro_f_string_static_t_initialize("xxxOneyyy", 0, 9),
    macro_f_string_static_t_initialize("xxxOneyyy", 0, 9),
    macro_f_string_static_t_initialize("xxxOneyyy", 0, 9),
    macro_f_string_static_t_initialize("xxxOneyyy", 0, 9),
    macro_f_string_static_t_initialize("xxxOneyyy", 0, 9),
    macro_f_string_static_t_initialize("xxxOneyyy", 0, 9),
    macro_f_string_static_t_initialize("xxxOneyyy", 0, 9),
    macro_f_string_static_t_initialize("xxxOneyyy", 0, 9),

    // 6.
    macro_f_string_static_t_initialize("xxx\0neyyy", 0, 9),
    macro_f_string_static_t_initialize("xxx\0neyyy", 0, 9),
    macro_f_string_static_t_initialize("xxx\0neyyy", 0, 9),
    macro_f_string_static_t_initialize("xxx\0neyyy", 0, 9),
    macro_f_string_static_t_initialize("xxx\0neyyy", 0, 9),
    macro_f_string_static_t_initialize("xxx\0neyyy", 0, 9),
    macro_f_string_static_t_initialize("xxx\0neyyy", 0, 9),
    macro_f_string_static_t_initialize("xxx\0neyyy", 0, 9),

    // 7.
    macro_f_string_static_t_initialize("xxxo\0neyyy", 0, 10),
    macro_f_string_static_t_initialize("xxxo\0neyyy", 0, 10),
    macro_f_string_static_t_initialize("xxxo\0neyyy", 0, 10),
    macro_f_string_static_t_initialize("xxxo\0neyyy", 0, 10),
    macro_f_string_static_t_initialize("xxxo\0neyyy", 0, 10),
    macro_f_string_static_t_initialize("xxxo\0neyyy", 0, 10),
    macro_f_string_static_t_initialize("xxxo\0neyyy", 0, 10),
    macro_f_string_static_t_initialize("xxxo\0neyyy", 0, 10),

    // 8.
    macro_f_string_static_t_initialize("xxxone\0yyy", 0, 10),
    macro_f_string_static_t_initialize("xxxone\0yyy", 0, 10),
    macro_f_string_static_t_initialize("xxxone\0yyy", 0, 10),
    macro_f_string_static_t_initialize("xxxone\0yyy", 0, 10),
    macro_f_string_static_t_initialize("xxxone\0yyy", 0, 10),
    macro_f_string_static_t_initialize("xxxone\0yyy", 0, 10),
    macro_f_string_static_t_initialize("xxxone\0yyy", 0, 10),
    macro_f_string_static_t_initialize("xxxone\0yyy", 0, 10),
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

  f_string_range_t range_1 = macro_f_string_range_t_initialize(3, 9);
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
  f_utf_string_dynamic_t utf_string_1 = f_utf_string_dynamic_t_initialize;
  f_utf_string_dynamic_t utf_string_2 = f_utf_string_dynamic_t_initialize;

  // First eight are against empty strings for first argument.
  for (; i < 8; ++i) {

    utf_string_1.used = 0;
    utf_string_2.used = 0;

    status = test_convert_dynamic_to_utf(string_1s[i], &utf_string_1);
    assert_int_equal(status, F_none);

    status = test_convert_dynamic_to_utf(string_2s[i], &utf_string_2);
    assert_int_equal(status, F_none);

    if (i % 8 == 0) {
      status = fl_utf_string_dynamic_partial_compare(utf_string_1, utf_string_2, f_string_range_empty_c, f_string_range_empty_c);
    }
    else {
      range_2.stop = string_2s[i].used - 1;

      status = fl_utf_string_dynamic_partial_compare(utf_string_1, utf_string_2, f_string_range_empty_c, range_2);
    }

    assert_int_equal(status, expects[i]);
  } // for

  for (; i < 64; ++i) {

    utf_string_1.used = 0;
    utf_string_2.used = 0;

    status = test_convert_dynamic_to_utf(string_1s[i], &utf_string_1);
    assert_int_equal(status, F_none);

    status = test_convert_dynamic_to_utf(string_2s[i], &utf_string_2);
    assert_int_equal(status, F_none);

    range_1.stop = string_1s[i].used - 4;

    if (i % 8 == 0) {
      status = fl_utf_string_dynamic_partial_compare(utf_string_1, utf_string_2, range_1, f_string_range_empty_c);
    }
    else {
      range_2.stop = string_2s[i].used - 1;

      status = fl_utf_string_dynamic_partial_compare(utf_string_1, utf_string_2, range_1, range_2);
    }

    assert_int_equal(status, expects[i]);
  } // for

  f_utf_string_dynamic_resize(0, &utf_string_1);
  f_utf_string_dynamic_resize(0, &utf_string_2);
}

#ifdef __cplusplus
} // extern "C"
#endif
