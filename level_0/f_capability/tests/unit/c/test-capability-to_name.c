#include "test-capability.h"
#include "test-capability-to_name.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_capability_to_name__fails(void **state) {

  #if !defined(_di_libcap_)
    const int code = CAP_CHOWN;
    f_string_dynamic_t name = f_string_dynamic_t_initialize;

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

      will_return(__wrap_cap_to_name, true);
      will_return(__wrap_cap_to_name, errnos[i]);

      const f_status_t status = f_capability_to_name(code, &name);

      assert_int_equal(status, F_status_set_error(statuss[i]));
      assert_int_equal(name.used, 0);
    } // for
  #endif // !defined(_di_libcap_)
}

void test__f_capability_to_name__parameter_checking(void **state) {

  const int code = CAP_CHOWN;

  {
    const f_status_t status = f_capability_to_name(code, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_capability_to_name__works(void **state) {

  const int code = CAP_CHOWN;
  char string[] = "CAP_CHOWN";
  f_string_dynamic_t name = f_string_dynamic_t_initialize;

  #if defined(_di_libcap_)
    printf("[  WARN    ] f_capability_to_name() is not implemented and cannot be fully tested.\n");
  #else
    will_return(__wrap_cap_to_name, false);
    will_return(__wrap_cap_to_name, string);
    will_return(__wrap_cap_free, false);
  #endif // defined(_di_libcap_)

  {
    const f_status_t status = f_capability_to_name(code, &name);

    #if defined(_di_libcap_)
      assert_int_equal(F_status_set_fine(status), F_implemented_not);
    #else
      assert_int_equal(status, F_none);
      assert_string_equal(name.string, string);
      assert_int_equal(name.used, 9);
    #endif // defined(_di_libcap_)
  }

  f_string_dynamic_resize(0, &name);
}

#ifdef __cplusplus
} // extern "C"
#endif
