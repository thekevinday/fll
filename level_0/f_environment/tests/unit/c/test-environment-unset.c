#include "test-environment.h"
#include "test-environment-unset.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_environment_unset__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

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

      will_return(__wrap_unsetenv, true);
      will_return(__wrap_unsetenv, errnos[i]);

      const f_status_t status = f_environment_unset(path);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  }
}

void test__f_environment_unset__returns_data_not(void **state) {

  {
    const f_status_t status = f_environment_unset(f_string_empty_s);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_environment_unset__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    will_return(__wrap_unsetenv, false);
    will_return(__wrap_unsetenv, 0);

    const f_status_t status = f_environment_unset(path);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
