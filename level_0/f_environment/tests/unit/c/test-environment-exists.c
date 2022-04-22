#include "test-environment.h"
#include "test-environment-exists.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_environment_exists__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    will_return(__wrap_getenv, 0);

    const f_status_t status = f_environment_exists(path);

    assert_int_equal(status, F_false);
  }
}

void test__f_environment_exists__returns_data_not(void **state) {

  {
    const f_status_t status = f_environment_exists(f_string_empty_s);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_environment_exists__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    will_return(__wrap_getenv, path.string);

    const f_status_t status = f_environment_exists(path);

    assert_int_equal(status, F_true);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
