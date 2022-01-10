#include "test-capability.h"
#include "test-capability-supported.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_capability_supported__works(void **state) {

  {
    const f_status_t status = f_capability_supported();

    #if defined(_di_libcap_)
      assert_int_equal(status, F_false);
    #else
      assert_int_equal(status, F_true);
    #endif // defined(_di_libcap_)
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
