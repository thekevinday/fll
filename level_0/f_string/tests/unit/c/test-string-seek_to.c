#include "test-string.h"
#include "test-string-seek_to.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_string_seek_to__returns_data_not_stop(void **state) {

  const f_string_static_t to = macro_f_string_static_t_initialize_1("X", 0, 1);
  const f_string_static_t source = macro_f_string_static_t_initialize_1("test\nafter", 0, 10);

  {
    f_string_range_t range = f_string_range_t_initialize;

    const f_status_t status = f_string_seek_to(source.string, to.string[0], &range);

    assert_int_equal(status, F_data_not_stop);
  }
}

void test__f_string_seek_to__returns_none_stop(void **state) {

  const f_string_static_t to = macro_f_string_static_t_initialize_1("X", 0, 1);
  const f_string_static_t source = macro_f_string_static_t_initialize_1("test\nafter", 0, 10);

  {
    f_string_range_t range = macro_f_string_range_t_initialize_1(0, source.used - 1);

    const f_status_t status = f_string_seek_to(source.string, to.string[0], &range);

    assert_int_equal(status, F_none_stop);

    assert_int_equal(range.start, source.used);
    assert_int_equal(range.stop, source.used - 1);
  }
}

void test__f_string_seek_to__works(void **state) {

  const f_string_static_t to = macro_f_string_static_t_initialize_1("X", 0, 1);
  const f_string_static_t source = macro_f_string_static_t_initialize_1("te\nXst", 0, 6);

  {
    f_string_range_t range = macro_f_string_range_t_initialize_1(0, source.used - 1);

    const f_status_t status = f_string_seek_to(source.string, to.string[0], &range);

    assert_int_equal(status, F_none);

    assert_int_equal(range.start, 3);
    assert_int_equal(range.stop, source.used - 1);
  }
}

void test__f_string_seek_to__parameter_checking(void **state) {

  const f_string_static_t to = macro_f_string_static_t_initialize_1("X", 0, 1);
  const f_string_static_t source = macro_f_string_static_t_initialize_1("teX\nst", 0, 6);

  {
    const f_status_t status = f_string_seek_to(source.string, to.string[0], 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
