#include "test-capability.h"
#include "test-capability-supported_ambient.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_capability_supported_ambient__works(void **state) {

  #if defined(_di_libcap_) || defined(_libcap_legacy_only_)
    {
      const f_status_t status = f_capability_supported_ambient();

      assert_int_equal(status, F_false);
    }
  #else
    {
      const f_status_t status = f_capability_supported_ambient();

      will_return(__wrap_cap_get_ambient, false);

      assert_int_equal(status, F_true);
    }

    {
      const f_status_t status = f_capability_supported_ambient();

      will_return(__wrap_cap_get_ambient, true);
      will_return(__wrap_cap_get_ambient, mock_errno_generic);

      assert_int_equal(status, F_false);
    }
  #endif // defined(_di_libcap_) || defined(_libcap_legacy_only_)
}

#ifdef __cplusplus
} // extern "C"
#endif
