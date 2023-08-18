#include "test-capability.h"
#include "test-capability-copy_external.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_capability_copy_external__fails(void **state) {

  #if !defined(_di_libcap_)
    f_capability_t capability = f_capability_t_initialize;
    const ssize_t max = 0;
    int stub = 0;
    void *external = (void *) &stub;
    ssize_t size = 0;

    int errnos[] = {
      EINVAL,
      ERANGE,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_parameter,
      F_range_not,
      F_failure,
    };

    for (int i = 0; i < 3; ++i) {

      will_return(__wrap_cap_copy_ext, true);
      will_return(__wrap_cap_copy_ext, errnos[i]);

      const f_status_t status = f_capability_copy_external(capability, max, external, &size);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  #endif // !defined(_di_libcap_)
}

void test__f_capability_copy_external__parameter_checking(void **state) {

  f_capability_t capability = f_capability_t_initialize;

  {
    const f_status_t status = f_capability_copy_external(capability, 0, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_capability_copy_external__works(void **state) {

  f_capability_t capability = f_capability_t_initialize;
  const ssize_t max = 0;
  int stub = 0;
  void *external = (void *) &stub;
  ssize_t size = 0;

  #if defined(_di_libcap_)
    printf("[  WARN    ] f_capability_copy_external() is not implemented and cannot be fully tested.\n");
  #else
    will_return(__wrap_cap_copy_ext, false);
  #endif // defined(_di_libcap_)

  {
    const f_status_t status = f_capability_copy_external(capability, max, external, &size);

    #if defined(_di_libcap_)
      assert_int_equal(F_status_set_fine(status), F_implement_not);
    #else
      assert_int_equal(status, F_okay);
      assert_int_equal(size, 1);
    #endif // defined(_di_libcap_)
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
