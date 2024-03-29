#include "test-capability.h"
#include "test-capability-clear.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_capability_clear__fails(void **state) {

  #if !defined(_di_libcap_)
    f_capability_t capability = f_capability_t_initialize;

    int errnos[] = {
      EINVAL,
      ENOMEM,
      ERANGE,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_parameter,
      F_memory_not,
      F_range_not,
      F_failure,
    };

    for (int i = 0; i < 4; ++i) {

      will_return(__wrap_cap_clear, true);
      will_return(__wrap_cap_clear, errnos[i]);

      const f_status_t status = f_capability_clear(&capability);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  #endif // !defined(_di_libcap_)
}

void test__f_capability_clear__parameter_checking(void **state) {

  {
    const f_status_t status = f_capability_clear(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_capability_clear__works(void **state) {

  f_capability_t capability = f_capability_t_initialize;

  #if defined(_di_libcap_)
    printf("[  WARN    ] f_capability_clear() is not implemented and cannot be fully tested.\n");
  #else
    will_return(__wrap_cap_clear, false);
  #endif // defined(_di_libcap_)

  {
    const f_status_t status = f_capability_clear(&capability);

    #if defined(_di_libcap_)
      assert_int_equal(F_status_set_fine(status), F_implemented_not);
    #else
      assert_int_equal(status, F_none);
    #endif // defined(_di_libcap_)
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
