#include "test-capability.h"
#include "test-capability-process_bound_drop.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_capability_process_bound_drop__fails(void **state) {

  #if !defined(_di_libcap_)
    const f_capability_value_t value = f_capability_value_t_initialize;
    int bound = 0;

    int errnos[] = {
      EINVAL,
      ENOMEM,
      EPERM,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_parameter,
      F_memory_not,
      F_prohibited,
      F_failure,
    };

    for (int i = 0; i < 4; ++i) {

      will_return(__wrap_cap_drop_bound, true);
      will_return(__wrap_cap_drop_bound, errnos[i]);

      const f_status_t status = f_capability_process_bound_drop(value, &bound);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  #endif // !defined(_di_libcap_)
}

void test__f_capability_process_bound_drop__parameter_checking(void **state) {

  const f_capability_value_t value = f_capability_value_t_initialize;

  {
    const f_status_t status = f_capability_process_bound_drop(value, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_capability_process_bound_drop__works(void **state) {

  const f_capability_value_t value = f_capability_value_t_initialize;
  int bound = 0;

  #if defined(_di_libcap_)
    printf("[  WARN    ] f_capability_process_bound_drop() is not implemented and cannot be fully tested.\n");
  #else
    will_return(__wrap_cap_drop_bound, false);
  #endif // defined(_di_libcap_)

  {
    const f_status_t status = f_capability_process_bound_drop(value, &bound);

    #if defined(_di_libcap_)
      assert_int_equal(F_status_set_fine(status), F_implemented_not);
    #else
      assert_int_equal(status, F_none);
      assert_int_equal(bound, 1);
    #endif // defined(_di_libcap_)
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
