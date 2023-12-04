#include "test-serialize.h"
#include "test-serialize-from_simple_select.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_serialize_from_simple_select__parameter_checking(void **state) {

  const f_string_static_t source = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    const f_status_t status = f_serialize_from_simple_select(source, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_serialize_from_simple_select__returns_data_not(void **state) {

  f_range_t range = f_range_t_initialize;

  {
    const f_status_t status = f_serialize_from_simple_select(f_string_empty_s, 0, &range);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_serialize_from_simple_select__works(void **state) {

  const f_string_static_t source = macro_f_string_static_t_initialize_1("test:2::other:им:蠇:м:", 0, 26);

  const f_range_t ranges[] = {
    { 0, 3 },
    { 5, 5 },
    { 1, 0 },
    { 8, 12 },
    { 14, 17 },
    { 19, 21 },
    { 23, 24 },
    { 1, 0 },
  };

  for (uint8_t i = 0; i < 8; ++i) {

    f_range_t range = f_range_t_initialize;

    const f_status_t status = f_serialize_from_simple_select(source, i, &range);

    assert_int_equal(status, F_okay);
    assert_int_equal(range.start, ranges[i].start);
    assert_int_equal(range.stop, ranges[i].stop);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
