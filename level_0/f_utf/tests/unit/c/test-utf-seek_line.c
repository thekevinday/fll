#include "test-utf.h"
#include "test-utf-seek_line.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_seek_line__returns_data_not_stop(void **state) {

  const f_utf_string_static_t source = macro_f_utf_string_static_t_initialize_1((f_utf_string_t) "\0\0\0t\0\0\0e\0\0\0s\0\0\0t\0\0\0\n\0\0\0a\0\0\0f\0\0\0t\0\0\0e\0\0\0r", 0, 10);

  {
    f_range_t range = f_range_t_initialize;

    const f_status_t status = f_utf_string_seek_line(source.string, &range);

    assert_int_equal(status, F_data_not_stop);
  }
}

void test__f_utf_seek_line__returns_none_stop(void **state) {

  const f_utf_string_static_t source = macro_f_utf_string_static_t_initialize_1((f_utf_string_t) "\0\0\0t\0\0\0e\0\0\0s\0\0\0t", 0, 4);

  {
    f_range_t range = macro_f_range_t_initialize_1(0, source.used - 1);

    const f_status_t status = f_utf_string_seek_line(source.string, &range);

    assert_int_equal(status, F_okay_stop);

    assert_int_equal(range.start, source.used);
    assert_int_equal(range.stop, source.used - 1);
  }
}

void test__f_utf_seek_line__works(void **state) {

  const f_utf_string_static_t source = macro_f_utf_string_static_t_initialize_1((f_utf_string_t) "\0\0\0t\0\0\0e\0\0\0s\0\0\0t\0\0\0\n\0\0\0a\0\0\0f\0\0\0t\0\0\0e\0\0\0r", 0, 10);

  {
    f_range_t range = macro_f_range_t_initialize_1(0, source.used - 1);

    const f_status_t status = f_utf_string_seek_line(source.string, &range);

    assert_int_equal(status, F_okay);

    assert_int_equal(range.start, 4);
    assert_int_equal(range.stop, source.used - 1);
  }
}

void test__f_utf_seek_line__parameter_checking(void **state) {

  const f_utf_string_static_t source = macro_f_utf_string_static_t_initialize_1((f_utf_string_t) "\0\0\0t\0\0\0e\0\0\0X\0\0\0\n\0\0\0s\0\0\0t", 0, 6);

  {
    const f_status_t status = f_utf_string_seek_line(source.string, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
