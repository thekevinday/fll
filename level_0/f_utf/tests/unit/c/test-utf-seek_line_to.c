#include "test-utf.h"
#include "test-utf-seek_line_to.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_seek_line_to__at_newline(void **state) {

  const f_utf_string_static_t to = macro_f_utf_string_static_t_initialize((f_utf_string_t) "X\0\0\0", 0, 1);
  const f_utf_string_static_t source = macro_f_utf_string_static_t_initialize((f_utf_string_t) "t\0\0\0e\0\0\0\n\0\0\0X\0\0\0s\0\0\0t\0\0\0", 0, 6);

  {
    f_string_range_t range = macro_f_string_range_t_initialize(0, source.used - 1);

    const f_status_t status = f_utf_string_seek_line_to(source.string, to.string[0], &range);

    assert_int_equal(status, F_none_eol);

    assert_int_equal(range.start, 2);
    assert_int_equal(range.stop, source.used - 1);
  }
}

void test__f_utf_seek_line_to__returns_data_not_stop(void **state) {

  const f_utf_string_static_t to = macro_f_utf_string_static_t_initialize((f_utf_string_t) "X\0\0\0", 0, 1);
  const f_utf_string_static_t source = macro_f_utf_string_static_t_initialize((f_utf_string_t) "t\0\0\0e\0\0\0s\0\0\0t\0\0\0\n\0\0\0a\0\0\0f\0\0\0t\0\0\0e\0\0\0r\0\0\0", 0, 10);

  {
    f_string_range_t range = f_string_range_t_initialize;

    const f_status_t status = f_utf_string_seek_line_to(source.string, to.string[0], &range);

    assert_int_equal(status, F_data_not_stop);
  }
}

void test__f_utf_seek_line_to__returns_none_stop(void **state) {

  const f_utf_string_static_t to = macro_f_utf_string_static_t_initialize((f_utf_string_t) "X\0\0\0", 0, 1);
  const f_utf_string_static_t source = macro_f_utf_string_static_t_initialize((f_utf_string_t) "t\0\0\0e\0\0\0s\0\0\0t\0\0\0", 0, 4);

  {
    f_string_range_t range = macro_f_string_range_t_initialize(0, source.used - 1);

    const f_status_t status = f_utf_string_seek_line_to(source.string, to.string[0], &range);

    assert_int_equal(status, F_none_stop);

    assert_int_equal(range.start, source.used);
    assert_int_equal(range.stop, source.used - 1);
  }
}

void test__f_utf_seek_line_to__works(void **state) {

  const f_utf_string_static_t to = macro_f_utf_string_static_t_initialize((f_utf_string_t) "X\0\0\0", 0, 1);
  const f_utf_string_static_t source = macro_f_utf_string_static_t_initialize((f_utf_string_t) "t\0\0\0e\0\0\0X\0\0\0\n\0\0\0s\0\0\0t\0\0\0", 0, 6);

  {
    f_string_range_t range = macro_f_string_range_t_initialize(0, source.used - 1);

    const f_status_t status = f_utf_string_seek_line_to(source.string, to.string[0], &range);

    assert_int_equal(status, F_none);

    assert_int_equal(range.start, 2);
    assert_int_equal(range.stop, source.used - 1);
  }
}

void test__f_utf_seek_line_to__parameter_checking(void **state) {

  const f_utf_string_static_t to = macro_f_utf_string_static_t_initialize((f_utf_string_t) "X\0\0\0", 0, 1);
  const f_utf_string_static_t source = macro_f_utf_string_static_t_initialize((f_utf_string_t) "t\0\0\0e\0\0\0X\0\0\0\n\0\0\0s\0\0\0t\0\0\0", 0, 6);

  {
    const f_status_t status = f_utf_string_seek_line_to(source.string, to.string[0], 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
