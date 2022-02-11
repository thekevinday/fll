#include "test-capability.h"
#include "test-capability-supported_code.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_capability_supported_code__works(void **state) {

  const f_capability_value_t value = f_capability_value_t_initialize;

  #if defined(_di_libcap_)
    {
      const f_status_t status = f_capability_supported_code(value);

      assert_int_equal(status, F_false);
    }
  #else
    {
      will_return(__wrap_cap_get_bound, false);

      const f_status_t status = f_capability_supported_code(value);

      assert_int_equal(status, F_true);
    }

    {
      will_return(__wrap_cap_get_bound, F_true);
      will_return(__wrap_cap_get_bound, mock_errno_generic);

      const f_status_t status = f_capability_supported_code(value);

      assert_int_equal(status, F_false);
    }
  #endif // defined(_di_libcap_)
}

#ifdef __cplusplus
} // extern "C"
#endif
