#include "test-capability.h"
#include "test-capability-from_name.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_capability_from_name__works(void **state) {

  f_string_t name = f_string_t_initialize;
  f_capability_value_t capability_value = f_capability_value_t_initialize;

  #if defined(_di_libcap_)
    printf("[  WARN    ] f_capability_from_name() is not implemented and cannot be fully tested.\n");
  #else
    will_return(__wrap_cap_from_name, false);
  #endif // defined(_di_libcap_)

  {
    const f_status_t status = f_capability_from_name(name, &capability_value);

    #if defined(_di_libcap_)
      assert_int_equal(F_status_set_fine(status), F_implemented_not);
    #else
      assert_int_equal(status, F_none);
    #endif // defined(_di_libcap_)
  }
}

void test__f_capability_from_name__fails(void **state) {

  #if !defined(_di_libcap_)
    f_string_t name = f_string_t_initialize;
    f_capability_value_t capability_value = f_capability_value_t_initialize;

    int errnos[] = {
      EINVAL,
      ENOMEM,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_parameter,
      F_memory_not,
      F_failure,
    };

    for (int i = 0; i < 3; ++i) {

      will_return(__wrap_cap_from_name, true);
      will_return(__wrap_cap_from_name, errnos[i]);

      const f_status_t status = f_capability_from_name(name, &capability_value);

      assert_int_equal(F_status_set_fine(status), statuss[i]);
    } // for
  #endif // !defined(_di_libcap_)
}

#ifdef __cplusplus
} // extern "C"
#endif
