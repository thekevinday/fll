#include "test-capability.h"
#include "test-capability-copy.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_capability_copy__fails(void **state) {

  #if !defined(_di_libcap_)
    const f_capability_t capability_1 = f_capability_t_initialize;
    f_capability_t capability_2 = f_capability_t_initialize;

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

      will_return(__wrap_cap_dup, true);
      will_return(__wrap_cap_dup, EINVAL);

      const f_status_t status = f_capability_copy(capability_1, &capability_2);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    } // for
  #endif // !defined(_di_libcap_)
}

#ifndef _di_level_0_parameter_checking_
  void test__f_capability_copy__parameter_checking(void **state) {

    const f_capability_t capability = f_capability_t_initialize;

    {
      const f_status_t status = f_capability_copy(capability, 0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_capability_copy__works(void **state) {

  const f_capability_t capability_1 = f_capability_t_initialize;
  f_capability_t capability_2 = f_capability_t_initialize;

  #if defined(_di_libcap_)
    printf("[  WARN    ] f_capability_copy() is not implemented and cannot be fully tested.\n");
  #else
    will_return(__wrap_cap_dup, false);
  #endif // defined(_di_libcap_)

  {
    const f_status_t status = f_capability_copy(capability_1, &capability_2);

    #if defined(_di_libcap_)
      assert_int_equal(F_status_set_fine(status), F_implemented_not);
    #else
      assert_int_equal(status, F_none);
      assert_int_equal(capability_2, 1);
    #endif // defined(_di_libcap_)
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
