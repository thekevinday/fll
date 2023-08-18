#include "test-environment.h"
#include "test-environment-get.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_environment_get__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

  {
    will_return(__wrap_getenv, 0);

    const f_status_t status = f_environment_get(path, &buffer);

    assert_int_equal(status, F_exist_not);
  }

  f_string_dynamic_resize(0, &buffer);
}

void test__f_environment_get__parameter_checking(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    const f_status_t status = f_environment_get(path, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_environment_get__returns_data_not(void **state) {

  f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

  {
    const f_status_t status = f_environment_get(f_string_empty_s, &buffer);

    assert_int_equal(status, F_data_not);
  }

  f_string_dynamic_resize(0, &buffer);
}

void test__f_environment_get__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

  {
    will_return(__wrap_getenv, path.string);

    const f_status_t status = f_environment_get(path, &buffer);

    assert_int_equal(status, F_okay);
    assert_int_equal(buffer.used, path.used);
    assert_string_equal(buffer.string, path.string);
  }

  buffer.used = 0;

  {
    will_return(__wrap_getenv, f_string_empty_s.string);

    const f_status_t status = f_environment_get(path, &buffer);

    assert_int_equal(status, F_okay);
    assert_int_equal(buffer.used, f_string_empty_s.used);
    assert_string_equal(buffer.string, f_string_empty_s.string);
  }

  f_string_dynamic_resize(0, &buffer);
}

#ifdef __cplusplus
} // extern "C"
#endif
