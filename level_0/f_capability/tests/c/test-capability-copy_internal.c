#include "test-capability.h"
#include "test-capability-copy_internal.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_capability_copy_internal__works(void **state) {

  f_capability_t capability = f_capability_t_initialize;
  int stub = 0;
  void *external = (void *) &stub;

  #if defined(_di_libcap_)
    printf("[  WARN    ] f_capability_copy_internal() is not implemented and cannot be fully tested.\n");
  #else
    will_return(__wrap_cap_copy_int, false);
  #endif // defined(_di_libcap_)

  {
    const f_status_t status = f_capability_copy_internal(external, &capability);

    #if defined(_di_libcap_)
      assert_int_equal(F_status_set_fine(status), F_implemented_not);
    #else
      assert_int_equal(status, F_none);
      assert_int_equal(capability, 1);
    #endif // defined(_di_libcap_)
  }
}

void test__f_capability_copy_internal__fails(void **state) {

  #if !defined(_di_libcap_)
    f_capability_t capability = f_capability_t_initialize;
    int stub = 0;
    void *external = (void *) &stub;

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

      will_return(__wrap_cap_copy_int, true);
      will_return(__wrap_cap_copy_int, errnos[i]);

      const f_status_t status = f_capability_copy_internal(external, &capability);

      assert_int_equal(F_status_set_fine(status), statuss[i]);
    } // for
  #endif // !defined(_di_libcap_)
}

#ifdef __cplusplus
} // extern "C"
#endif
