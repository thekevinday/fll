#include "test-serialize.h"
#include "test-serialize-from_simple_get.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_serialize_from_simple_get__parameter_checking(void **state) {

  const f_string_static_t source = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    const f_status_t status = f_serialize_from_simple_get(source, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_serialize_from_simple_get__returns_data_not(void **state) {

  f_string_dynamic_t destination = f_string_dynamic_t_initialize;

  {
    const f_status_t status = f_serialize_from_simple_get(f_string_empty_s, 0, &destination);

    assert_int_equal(status, F_data_not);
  }

  free((void *) destination.string);
}

void test__f_serialize_from_simple_get__works(void **state) {

  const f_string_static_t source = macro_f_string_static_t_initialize_1("test:2::other:им:蠇:м:", 0, 26);

  const f_string_static_t matchs[] = {
    macro_f_string_static_t_initialize_1("test", 0, 4),
    macro_f_string_static_t_initialize_1("2", 0, 1),
    f_string_empty_s,
    macro_f_string_static_t_initialize_1("other", 0, 5),
    macro_f_string_static_t_initialize_1("им", 0, 4),
    macro_f_string_static_t_initialize_1("蠇", 0, 3),
    macro_f_string_static_t_initialize_1("м", 0, 2),
    f_string_empty_s,
  };

  f_string_dynamic_t destination = f_string_dynamic_t_initialize;

  for (uint8_t i = 0; i < 8; ++i) {

    destination.used = 0;

    const f_status_t status = f_serialize_from_simple_get(source, i, &destination);

    assert_int_equal(status, F_okay);
    assert_int_equal(destination.used, matchs[i].used);

    if (destination.used) {
      assert_string_equal(destination.string, matchs[i].string);
    }
  } // for

  free((void *) destination.string);
}

#ifdef __cplusplus
} // extern "C"
#endif
