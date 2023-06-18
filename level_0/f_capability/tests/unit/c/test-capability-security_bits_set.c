#include "test-capability.h"
#include "test-capability-security_bits_set.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_capability_security_bits_set__fails(void **state) {

  #if !defined(_di_libcap_) && !defined(_libcap_legacy_only_)
    const f_capability_bits_t bits = f_capability_bits_t_initialize;

    int errnos[] = {
      EACCES,
      EBADFD,
      ENAMETOOLONG,
      ENOENT,
      ENOMEM,
      ENOTDIR,
      EPERM,
      EROFS,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_access_denied,
      F_descriptor_not,
      F_name_not,
      F_file_found_not,
      F_memory_not,
      F_directory_not,
      F_prohibited,
      F_support_not,
      F_failure,
    };

    for (int i = 0; i < 9; ++i) {

      will_return(__wrap_cap_set_secbits, true);
      will_return(__wrap_cap_set_secbits, errnos[i]);

      const f_status_t status = f_capability_security_bits_set(bits);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  #endif // !defined(_di_libcap_) && !defined(_libcap_legacy_only_)
}

void test__f_capability_security_bits_set__works(void **state) {

  const f_capability_bits_t bits = f_capability_bits_t_initialize;

  #if defined(_di_libcap_) || defined(_libcap_legacy_only_)
    printf("[  WARN    ] f_capability_security_bits_set() is not implemented and cannot be fully tested.\n");
  #else
    will_return(__wrap_cap_set_secbits, false);
  #endif // defined(_di_libcap_) || defined(_libcap_legacy_only_)

  {
    const f_status_t status = f_capability_security_bits_set(bits);

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
