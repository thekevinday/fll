#include "test-capability.h"
#include "test-capability-owner_set.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_capability_owner_set__fails(void **state) {

  #if !defined(_di_libcap_) && !defined(_libcap_legacy_only_)
    const f_capability_t capability = f_capability_t_initialize;
    const uid_t id;

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

      will_return(__wrap_cap_owner_set, true);
      will_return(__wrap_cap_owner_set, errnos[i]);

      const f_status_t status = f_capability_owner_set(capability, id);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  #endif // !defined(_di_libcap_) && !defined(_libcap_legacy_only_)
}

void test__f_capability_owner_set__works(void **state) {

  const f_capability_t capability = f_capability_t_initialize;
  const uid_t id = 0;

  #if defined(_di_libcap_) || defined(_libcap_legacy_only_)
    printf("[  WARN    ] f_capability_owner_set() is not implemented and cannot be fully tested.\n");
  #else
    will_return(__wrap_cap_set_nsowner, false);
  #endif // defined(_di_libcap_) || defined(_libcap_legacy_only_)

  {
    const f_status_t status = f_capability_owner_set(capability, id);

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
