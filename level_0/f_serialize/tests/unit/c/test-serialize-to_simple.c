#include "test-serialize.h"
#include "test-serialize-to_simple.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_serialize_to_simple__parameter_checking(void **state) {

  const f_string_static_t source = macro_f_string_static_t_initialize("test", 0, 4);

  {
    const f_status_t status = f_serialize_to_simple(source, 0);

    assert_int_equal(F_status_set_fine(status), F_parameter);
  }
}

void test__f_serialize_to_simple__returns_data_not(void **state) {

  const f_string_static_t source = f_string_static_t_initialize;

  f_string_dynamic_t destination = f_string_dynamic_t_initialize;

  {
    const f_status_t status = f_serialize_to_simple(source, &destination);

    assert_int_equal(status, F_data_not);
  }

  f_string_dynamic_resize(0, &destination);
}

void test__f_serialize_to_simple__works(void **state) {

  const f_string_static_t source = macro_f_string_static_t_initialize("test", 0, 4);
  const f_string_static_t multiple = macro_f_string_static_t_initialize("test:test", 0, 9);

  f_string_dynamic_t destination = f_string_dynamic_t_initialize;

  {
    const f_status_t status = f_serialize_to_simple(source, &destination);

    assert_int_equal(status, F_none);
    assert_string_equal(destination.string, source.string);
  }

  {
    const f_status_t status = f_serialize_to_simple(source, &destination);

    assert_int_equal(status, F_none);
    assert_string_equal(destination.string, multiple.string);
  }

  f_string_dynamic_resize(0, &destination);
}

#ifdef __cplusplus
} // extern "C"
#endif
