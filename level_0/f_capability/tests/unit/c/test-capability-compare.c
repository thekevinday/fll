#include "test-capability.h"
#include "test-capability-compare.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_capability_compare__fails(void **state) {

  #if !defined(_di_libcap_)
    const f_capability_t capability_1 = f_capability_t_initialize;
    const f_capability_t capability_2 = f_capability_t_initialize;
    int flags = 0;

    int errnos[] = {
      EINVAL,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_parameter,
      F_failure,
    };

    for (int i = 0; i < 2; ++i) {

      will_return(__wrap_cap_compare, true);
      will_return(__wrap_cap_compare, errnos[i]);

      const f_status_t status = f_capability_compare(capability_1, capability_2, &flags);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  #endif // !defined(_di_libcap_)
}

void test__f_capability_compare__works(void **state) {

  const f_capability_t capability_1 = f_capability_t_initialize;
  const f_capability_t capability_2 = f_capability_t_initialize;
  int flags = 0;

  #if defined(_di_libcap_)
    printf("[  WARN    ] f_capability_compare() is not implemented and cannot be fully tested.\n");

    {
      const f_status_t status = f_capability_compare(capability_1, capability_2, &flags);

      assert_int_equal(F_status_set_fine(status), F_implement_not);
    }
  #else
    {
      will_return(__wrap_cap_compare, false);
      will_return(__wrap_cap_compare, 0);

      const f_status_t status = f_capability_compare(capability_1, capability_2, &flags);

      assert_int_equal(status, F_equal_to);
    }

    {
      will_return(__wrap_cap_compare, false);
      will_return(__wrap_cap_compare, 1);

      const f_status_t status = f_capability_compare(capability_1, capability_2, &flags);

      assert_int_equal(status, F_equal_to_not);
      assert_int_equal(flags, 1);
    }
  #endif // defined(_di_libcap_)
}

#ifdef __cplusplus
} // extern "C"
#endif
