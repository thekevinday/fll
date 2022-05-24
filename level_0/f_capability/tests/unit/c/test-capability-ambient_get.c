#include "test-capability.h"
#include "test-capability-ambient_get.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_capability_ambient_get__fails(void **state) {

  #if !defined(_di_libcap_) && !defined(_libcap_legacy_only_)
    f_capability_value_t value = f_capability_value_t_initialize;
    int ambient = 0;

    {
      will_return(__wrap_cap_get_ambient, true);

      const f_status_t status = f_capability_ambient_get(value, &ambient);

      assert_int_equal(F_status_set_fine(status), F_supported_not);
      assert_int_equal(ambient, -1);
    }
  #endif // !defined(_di_libcap_) && !defined(_libcap_legacy_only_)
}

#ifndef _di_level_0_parameter_checking_
  void test__f_capability_ambient_get__parameter_checking(void **state) {

    const f_capability_value_t value = f_capability_value_t_initialize;

    {
      const f_status_t status = f_capability_ambient_get(value, 0);

      assert_int_equal(status, F_status_set_error(F_parameter));
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_capability_ambient_get__works(void **state) {

  const f_capability_value_t value = f_capability_value_t_initialize;
  int ambient = 0;

  #if defined(_di_libcap_) || defined(_libcap_legacy_only_)
    printf("[  WARN    ] f_capability_ambient_get() is not implemented and cannot be fully tested.\n");
  #else
    will_return(__wrap_cap_get_ambient, false);
  #endif // defined(_di_libcap_) || defined(_libcap_legacy_only_)

  {
    const f_status_t status = f_capability_ambient_get(value, &ambient);

    #if defined(_di_libcap_) || defined(_libcap_legacy_only_)
      assert_int_equal(F_status_set_fine(status), F_implemented_not);
    #else
      assert_int_equal(status, F_none);
      assert_int_equal(ambient, 1);
    #endif // defined(_di_libcap_) || defined(_libcap_legacy_only_)
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
