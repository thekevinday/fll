#include "test-capability.h"
#include "test-capability-ambient_reset.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_capability_ambient_reset__fails(void **state) {

  #if !defined(_di_libcap_) && !defined(_libcap_legacy_only_)
    {
      will_return(__wrap_cap_get_ambient, true);
      will_return(__wrap_cap_clear, EINVAL);

      const f_status_t status = f_capability_ambient_reset();

      assert_int_equal(status, F_status_set_error(F_parameter));
    }

    int errnos[] = {
      ENOMEM,
      EPERM,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_memory_not,
      F_prohibited,
      F_failure,
    };

    for (int i = 0; i < 3; ++i) {

      will_return(__wrap_cap_get_ambient, true);
      will_return(__wrap_cap_clear, errnos[i]);

      const f_status_t status = f_capability_ambient_reset();

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  #endif // !defined(_di_libcap_) && !defined(_libcap_legacy_only_)
}

void test__f_capability_ambient_reset__works(void **state) {

  #if defined(_di_libcap_) || defined(_libcap_legacy_only_)
    printf("[  WARN    ] f_capability_ambient_reset() is not implemented and cannot be fully tested.\n");
  #else
    will_return(__wrap_cap_get_ambient, false);
  #endif // defined(_di_libcap_) || defined(_libcap_legacy_only_)

  {
    const f_status_t status = f_capability_ambient_reset();

    #if defined(_di_libcap_) || defined(_libcap_legacy_only_)
      assert_int_equal(F_status_set_fine(status), F_implemented_not);
    #else
      assert_int_equal(status, F_none);
    #endif // defined(_di_libcap_) || defined(_libcap_legacy_only_)
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
