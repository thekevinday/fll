#include "test-capability.h"
#include "test-capability-to_text.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_capability_to_text__fails(void **state) {

  #if !defined(_di_libcap_)
    const f_capability_t capability = f_capability_t_initialize;
    f_string_dynamic_t text = f_string_dynamic_t_initialize;

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

      will_return(__wrap_cap_to_text, true);
      will_return(__wrap_cap_to_text, errnos[i]);

      const f_status_t status = f_capability_to_text(capability, &text);

      assert_int_equal(F_status_set_fine(status), statuss[i]);
      assert_int_equal(text.used, 0);
    } // for
  #endif // !defined(_di_libcap_)
}

#ifndef _di_level_0_parameter_checking_
  void test__f_capability_to_text__parameter_checking(void **state) {

    const f_capability_t capability = f_capability_t_initialize;

    {
      const f_status_t status = f_capability_to_text(capability, 0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_capability_to_text__works(void **state) {

  const f_capability_t capability = f_capability_t_initialize;
  char string[] = "CAP_CHOWN";
  f_string_dynamic_t text = f_string_dynamic_t_initialize;

  #if defined(_di_libcap_)
    printf("[  WARN    ] f_capability_to_text() is not implemented and cannot be fully tested.\n");
  #else
    will_return(__wrap_cap_to_text, false);
    will_return(__wrap_cap_to_text, 9);
    will_return(__wrap_cap_to_text, string);
    will_return(__wrap_cap_free, false);
  #endif // defined(_di_libcap_)

  {
    const f_status_t status = f_capability_to_text(capability, &text);

    #if defined(_di_libcap_)
      assert_int_equal(F_status_set_fine(status), F_implemented_not);
    #else
      assert_int_equal(status, F_none);
      assert_string_equal(text.string, string);
      assert_int_equal(text.used, 9);
    #endif // defined(_di_libcap_)
  }

  f_string_dynamic_resize(0, &text);
}

#ifdef __cplusplus
} // extern "C"
#endif
