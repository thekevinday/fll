#include "test-capability.h"
#include "test-capability-mode_set.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_capability_mode_set__fails(void **state) {

  #if !defined(_di_libcap_) && !defined(_libcap_legacy_only_)
    const f_capability_mode_t mode = f_capability_mode_t_initialize;

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

      will_return(__wrap_cap_mode_set, true);
      will_return(__wrap_cap_mode_set, errnos[i]);

      const f_status_t status = f_capability_mode_set(mode);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  #endif // !defined(_di_libcap_) && !defined(_libcap_legacy_only_)
}

void test__f_capability_mode_set__works(void **state) {

  const f_capability_mode_t mode = f_capability_mode_t_initialize;

  #if defined(_di_libcap_) || defined(_libcap_legacy_only_)
    printf("[  WARN    ] f_capability_mode_set() is not implemented and cannot be fully tested.\n");
  #else
    will_return(__wrap_cap_mode_set, false);
  #endif // defined(_di_libcap_) || defined(_libcap_legacy_only_)

  {
    const f_status_t status = f_capability_mode_set(mode);

    #if defined(_di_libcap_) || defined(_libcap_legacy_only_)
      assert_int_equal(F_status_set_fine(status), F_implement_not);
    #else
      assert_int_equal(status, F_none);
    #endif // defined(_di_libcap_) || defined(_libcap_legacy_only_)
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
