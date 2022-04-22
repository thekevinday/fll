#include "test-environment.h"
#include "test-environment-set.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_environment_set__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    int errnos[] = {
      EINVAL,
      ENOMEM,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_parameter,
      F_memory_not,
      F_failure,
    };

    for (int i = 0; i < 3; ++i) {

      will_return(__wrap_setenv, true);
      will_return(__wrap_setenv, errnos[i]);

      const f_status_t status = f_environment_set(path, path, F_false);

      assert_int_equal(F_status_set_fine(status), statuss[i]);
    } // for
  }
}

void test__f_environment_set__returns_data_not(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    const f_status_t status = f_environment_set(f_string_empty_s, f_string_empty_s, F_false);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_environment_set(f_string_empty_s, path, F_false);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_environment_set__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    will_return(__wrap_setenv, false);
    will_return(__wrap_setenv, 0);

    const f_status_t status = f_environment_set(path, path, F_false);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
