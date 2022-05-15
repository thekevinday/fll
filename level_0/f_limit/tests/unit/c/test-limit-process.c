#include "test-limit.h"
#include "test-limit-process.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_limit_process__fails(void **state) {

  const f_limit_value_t value = f_limit_value_t_initialize;

  int errnos[] = {
    EFAULT,
    EINVAL,
    EPERM,
    ESRCH,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_address_not,
    F_parameter,
    F_prohibited,
    F_found_not,
    F_failure,
  };

  for (int i = 0; i < 5; ++i) {

    will_return(__wrap_prlimit, true);
    will_return(__wrap_prlimit, errnos[i]);

    const f_status_t status = f_limit_process(1, 1, &value, 0);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

#ifndef _di_level_0_parameter_checking_
  void test__f_limit_process__parameter_checking(void **state) {

    {
      const f_status_t status = f_limit_process(1, 1, 0, 0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_limit_process__works(void **state) {

  const f_limit_value_t value = macro_f_limit_value_t_initialize(1, 2);
  f_limit_value_t destination = f_limit_value_t_initialize;

  {
    will_return(__wrap_prlimit, F_false);
    will_return(__wrap_prlimit, &value);
    will_return(__wrap_prlimit, 0);

    const f_status_t status = f_limit_process(1, 1, &value, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.rlim_cur, value.rlim_cur);
    assert_int_equal(destination.rlim_max, value.rlim_max);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
