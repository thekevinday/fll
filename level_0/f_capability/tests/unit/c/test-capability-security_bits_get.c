#include "test-capability.h"
#include "test-capability-security_bits_get.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_capability_security_bits_get__fails(void **state) {

  #if !defined(_di_libcap_) && !defined(_libcap_legacy_only_)
    f_capability_bits_t bits = f_capability_bits_t_initialize;

    int errnos[] = {
      EINVAL,
      ENOMEM,
      EPERM,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_parameter,
      F_memory_not,
      F_prohibited,
      F_failure,
    };

    for (int i = 0; i < 4; ++i) {

      will_return(__wrap_cap_get_secbits, true);
      will_return(__wrap_cap_get_secbits, errnos[i]);

      const f_status_t status = f_capability_security_bits_get(&bits);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  #endif // !defined(_di_libcap_) && !defined(_libcap_legacy_only_)
}

void test__f_capability_security_bits_get__parameter_checking(void **state) {

  {
    const f_status_t status = f_capability_security_bits_get(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_capability_security_bits_get__works(void **state) {

  f_capability_bits_t bits = f_capability_bits_t_initialize;

  #if defined(_di_libcap_) || defined(_libcap_legacy_only_)
    printf("[  WARN    ] f_capability_security_bits_get() is not implemented and cannot be fully tested.\n");
  #else
    will_return(__wrap_cap_get_secbits, false);
  #endif // defined(_di_libcap_) || defined(_libcap_legacy_only_)

  {
    const f_status_t status = f_capability_security_bits_get(&bits);

    #if defined(_di_libcap_) || defined(_libcap_legacy_only_)
      assert_int_equal(F_status_set_fine(status), F_implement_not);
    #else
      assert_int_equal(status, F_okay);
    #endif // defined(_di_libcap_) || defined(_libcap_legacy_only_)
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
