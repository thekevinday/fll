#include "test-environment.h"
#include "test-environment-get.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_environment_get_all__parameter_checking(void **state) {

  {
    const f_status_t status = f_environment_get_all(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_environment_get_all__works(void **state) {

  const f_string_static_t name = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_string_static_t value = macro_f_string_static_t_initialize_1("works", 0, 5);

  f_string_maps_t environment = f_string_maps_t_initialize;

  {
    // Cannot easily mock because this is used: extern char **environ;
    clearenv();
    setenv(name.string, value.string, true);

    const f_status_t status = f_environment_get_all(&environment);

    assert_int_equal(status, F_none);
    assert_int_equal(environment.used, 1);
    assert_string_equal(environment.array[0].name.string, name.string);
    assert_string_equal(environment.array[0].value.string, value.string);
  }

  f_string_maps_resize(0, &environment);
}

#ifdef __cplusplus
} // extern "C"
#endif
