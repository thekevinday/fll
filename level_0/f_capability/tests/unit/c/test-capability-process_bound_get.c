#include "test-capability.h"
#include "test-capability-process_bound_get.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_capability_process_bound_get__fails(void **state) {

  #if !defined(_di_libcap_)
    const f_capability_value_t value = f_capability_value_t_initialize;
    int bound = 0;

    int errnos[] = {
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_known_not,
    };

    for (int i = 0; i < 1; ++i) {

      will_return(__wrap_cap_get_bound, true);
      will_return(__wrap_cap_get_bound, errnos[i]);

      const f_status_t status = f_capability_process_bound_get(value, &bound);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  #endif // !defined(_di_libcap_)
}

#ifndef _di_level_0_parameter_checking_
  void test__f_capability_process_bound_get__parameter_checking(void **state) {

    const f_capability_value_t value = f_capability_value_t_initialize;

    {
      const f_status_t status = f_capability_process_bound_get(value, 0);

      assert_int_equal(status, F_status_set_error(F_parameter));
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_capability_process_bound_get__works(void **state) {

  const f_capability_value_t value = f_capability_value_t_initialize;
  int bound = 0;

  #if defined(_di_libcap_)
    printf("[  WARN    ] f_capability_process_bound_get() is not implemented and cannot be fully tested.\n");
  #else
    will_return(__wrap_cap_get_bound, false);
  #endif // defined(_di_libcap_)

  {
    const f_status_t status = f_capability_process_bound_get(value, &bound);

    #if defined(_di_libcap_)
      assert_int_equal(F_status_set_fine(status), F_implemented_not);
    #else
      assert_int_equal(status, F_none);
      assert_int_equal(bound, 1);
    #endif // defined(_di_libcap_)
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
