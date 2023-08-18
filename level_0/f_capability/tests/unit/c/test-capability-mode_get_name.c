#include "test-capability.h"
#include "test-capability-mode_get_name.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_capability_mode_get_name__parameter_checking(void **state) {

  const f_capability_mode_t mode = f_capability_mode_t_initialize;

  {
    const f_status_t status = f_capability_mode_get_name(mode, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_capability_mode_get_name__works(void **state) {

  const f_capability_mode_t mode = f_capability_mode_t_initialize;
  f_string_constant_t name = f_string_constant_t_initialize;

  #if defined(_di_libcap_) || defined(_libcap_legacy_only_)
    printf("[  WARN    ] f_capability_mode_get_name() is not implemented and cannot be fully tested.\n");
  #else
    will_return(__wrap_cap_mode_get_name, false);
  #endif // defined(_di_libcap_) || defined(_libcap_legacy_only_)

  {
    const f_status_t status = f_capability_mode_get_name(mode, &name);

    #if defined(_di_libcap_) || defined(_libcap_legacy_only_)
      assert_int_equal(F_status_set_fine(status), F_implement_not);
    #else
      assert_int_equal(status, F_okay);
    #endif // defined(_di_libcap_) || defined(_libcap_legacy_only_)
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
