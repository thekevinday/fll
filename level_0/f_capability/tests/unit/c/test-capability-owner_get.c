#include "test-capability.h"
#include "test-capability-owner_get.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_capability_owner_get__parameter_checking(void **state) {

  const f_capability_t capability = f_capability_t_initialize;

  {
    const f_status_t status = f_capability_owner_get(capability, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_capability_owner_get__works(void **state) {

  const f_capability_t capability = f_capability_t_initialize;
  uid_t id;

  #if defined(_di_libcap_) || defined(_libcap_legacy_only_)
    printf("[  WARN    ] f_capability_owner_get() is not implemented and cannot be fully tested.\n");
  #else
    will_return(__wrap_cap_get_nsowner, false);
  #endif // defined(_di_libcap_) || defined(_libcap_legacy_only_)

  {
    const f_status_t status = f_capability_owner_get(capability, &id);

    #if defined(_di_libcap_) || defined(_libcap_legacy_only_)
      assert_int_equal(F_status_set_fine(status), F_implemented_not);
    #else
      assert_int_equal(status, F_none);
      assert_int_equal(id, 1);
    #endif // defined(_di_libcap_) || defined(_libcap_legacy_only_)
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
