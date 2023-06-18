#include "test-capability.h"
#include "test-capability-flag_get.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_capability_flag_get__fails(void **state) {

  #if !defined(_di_libcap_)
    const f_capability_flag_t flag = f_capability_flag_t_initialize;
    const f_capability_t capability = f_capability_t_initialize;
    const f_capability_value_t capability_value = f_capability_value_t_initialize;
    f_capability_flag_value_t value = f_capability_flag_value_t_initialize;

    int errnos[] = {
      EINVAL,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_parameter,
      F_failure,
    };

    for (int i = 0; i < 2; ++i) {

      will_return(__wrap_cap_get_flag, true);
      will_return(__wrap_cap_get_flag, errnos[i]);

      const f_status_t status = f_capability_flag_get(capability, capability_value, flag, &value);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  #endif // !defined(_di_libcap_)
}

void test__f_capability_flag_get__parameter_checking(void **state) {

  const f_capability_flag_t flag = f_capability_flag_t_initialize;
  const f_capability_t capability = f_capability_t_initialize;
  const f_capability_value_t capability_value = f_capability_value_t_initialize;

  {
    const f_status_t status = f_capability_flag_get(capability, capability_value, flag, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_capability_flag_get__works(void **state) {

  const f_capability_flag_t flag = f_capability_flag_t_initialize;
  const f_capability_t capability = f_capability_t_initialize;
  const f_capability_value_t capability_value = f_capability_value_t_initialize;
  f_capability_flag_value_t value = f_capability_flag_value_t_initialize;

  #if defined(_di_libcap_)
    printf("[  WARN    ] f_capability_flag_get() is not implemented and cannot be fully tested.\n");
  #else
    will_return(__wrap_cap_get_flag, false);
  #endif // defined(_di_libcap_)

  {
    const f_status_t status = f_capability_flag_get(capability, capability_value, flag, &value);

    #if defined(_di_libcap_)
      assert_int_equal(F_status_set_fine(status), F_implement_not);
    #else
      assert_int_equal(status, F_none);
    #endif // defined(_di_libcap_)
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
