#include "test-capability.h"
#include "test-capability-file_descriptor_get.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_capability_file_descriptor_get__fails(void **state) {

  #if !defined(_di_libcap_)
    const int descriptor = 0;
    f_capability_t capability = f_capability_t_initialize;

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
      F_supported_not,
      F_failure,
    };

    for (int i = 0; i < 9; ++i) {

      will_return(__wrap_cap_get_fd, true);
      will_return(__wrap_cap_get_fd, errnos[i]);

      const f_status_t status = f_capability_file_descriptor_get(descriptor, &capability);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  #endif // !defined(_di_libcap_)
}

void test__f_capability_file_descriptor_get__parameter_checking(void **state) {

  const int descriptor = 0;

  {
    const f_status_t status = f_capability_file_descriptor_get(descriptor, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_capability_file_descriptor_get__works(void **state) {

  const int descriptor = 0;
  f_capability_t capability = f_capability_t_initialize;

  #if defined(_di_libcap_)
    printf("[  WARN    ] f_capability_file_descriptor_get() is not implemented and cannot be fully tested.\n");
  #else
    will_return(__wrap_cap_get_fd, false);
  #endif // defined(_di_libcap_)

  {
    const f_status_t status = f_capability_file_descriptor_get(descriptor, &capability);

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
