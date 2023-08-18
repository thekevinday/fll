#include "test-string.h"
#include "test-string-dynamic_seek_line_to.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_string_dynamic_seek_line_to__at_newline(void **state) {

  const f_string_static_t to = macro_f_string_static_t_initialize_1("X", 0, 1);
  const f_string_static_t source = macro_f_string_static_t_initialize_1("te\nXst", 0, 6);

  {
    f_string_range_t range = macro_f_string_range_t_initialize_1(0, source.used - 1);

    const f_status_t status = f_string_dynamic_seek_line_to(source, to.string[0], &range);

    assert_int_equal(status, F_okay_eol);

    assert_int_equal(range.start, 2);
    assert_int_equal(range.stop, source.used - 1);
  }
}

void test__f_string_dynamic_seek_line_to__returns_data_not_stop(void **state) {

  const f_string_static_t to = macro_f_string_static_t_initialize_1("X", 0, 1);
  const f_string_static_t source = macro_f_string_static_t_initialize_1("test\nafter", 0, 10);

  {
    f_string_range_t range = f_string_range_t_initialize;

    const f_status_t status = f_string_dynamic_seek_line_to(source, to.string[0], &range);

    assert_int_equal(status, F_data_not_stop);
  }
}

void test__f_string_dynamic_seek_line_to__returns_none_eos(void **state) {

  const f_string_static_t to = macro_f_string_static_t_initialize_1("X", 0, 1);
  const f_string_static_t source = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    f_string_range_t range = macro_f_string_range_t_initialize_1(0, source.used - 1);

    const f_status_t status = f_string_dynamic_seek_line_to(source, to.string[0], &range);

    assert_int_equal(status, F_okay_eos);

    assert_int_equal(range.start, source.used);
    assert_int_equal(range.stop, source.used - 1);
  }
}

void test__f_string_dynamic_seek_line_to__returns_none_stop(void **state) {

  const f_string_static_t to = macro_f_string_static_t_initialize_1("X", 0, 1);
  const f_string_static_t source = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    f_string_range_t range = macro_f_string_range_t_initialize_1(0, source.used - 2);

    const f_status_t status = f_string_dynamic_seek_line_to(source, to.string[0], &range);

    assert_int_equal(status, F_okay_stop);

    assert_int_equal(range.start, source.used - 1);
    assert_int_equal(range.stop, source.used - 2);
  }
}

void test__f_string_dynamic_seek_line_to__works(void **state) {

  const f_string_static_t to = macro_f_string_static_t_initialize_1("X", 0, 1);
  const f_string_static_t source = macro_f_string_static_t_initialize_1("teX\nst", 0, 6);

  {
    f_string_range_t range = macro_f_string_range_t_initialize_1(0, source.used - 1);

    const f_status_t status = f_string_dynamic_seek_line_to(source, to.string[0], &range);

    assert_int_equal(status, F_okay);

    assert_int_equal(range.start, 2);
    assert_int_equal(range.stop, source.used - 1);
  }
}

void test__f_string_dynamic_seek_line_to__parameter_checking(void **state) {

  const f_string_static_t to = macro_f_string_static_t_initialize_1("X", 0, 1);
  const f_string_static_t source = macro_f_string_static_t_initialize_1("teX\nst", 0, 6);

  {
    const f_status_t status = f_string_dynamic_seek_line_to(source, to.string[0], 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
