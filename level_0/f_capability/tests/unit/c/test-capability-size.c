#include "test-capability.h"
#include "test-capability-size.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_capability_size__fails(void **state) {

  #if !defined(_di_libcap_)
    const f_capability_t capability = f_capability_t_initialize;
    ssize_t size = 0;

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

      will_return(__wrap_cap_size, true);
      will_return(__wrap_cap_size, errnos[i]);

      const f_status_t status = f_capability_size(capability, &size);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  #endif // !defined(_di_libcap_)
}

void test__f_capability_size__parameter_checking(void **state) {

  const f_capability_t capability = f_capability_t_initialize;

  {
    const f_status_t status = f_capability_size(capability, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_capability_size__works(void **state) {

  const f_capability_t capability = f_capability_t_initialize;
  ssize_t size = 0;

  #if defined(_di_libcap_)
    printf("[  WARN    ] f_capability_size() is not implemented and cannot be fully tested.\n");
  #else
    will_return(__wrap_cap_size, false);
  #endif // defined(_di_libcap_)

  {
    const f_status_t status = f_capability_size(capability, &size);

    #if defined(_di_libcap_)
      assert_int_equal(F_status_set_fine(status), F_implement_not);
    #else
      assert_int_equal(status, F_none);
      assert_int_equal(size, 1);
    #endif // defined(_di_libcap_)
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
