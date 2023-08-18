#include "test-capability.h"
#include "test-capability-process_get_by_id.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_capability_process_get_by_id__fails(void **state) {

  #if !defined(_di_libcap_)
    f_capability_t capability = f_capability_t_initialize;
    const pid_t pid = 0;

    int errnos[] = {
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_failure,
    };

    for (int i = 0; i < 1; ++i) {

      will_return(__wrap_cap_get_pid, true);
      will_return(__wrap_cap_get_pid, errnos[i]);

      const f_status_t status = f_capability_process_get_by_id(pid, &capability);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  #endif // !defined(_di_libcap_)
}

void test__f_capability_process_get_by_id__parameter_checking(void **state) {

  {
    const f_status_t status = f_capability_process_get_by_id(0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_capability_process_get_by_id__works(void **state) {

  f_capability_t capability = f_capability_t_initialize;
  const pid_t pid = 0;

  #if defined(_di_libcap_)
    printf("[  WARN    ] f_capability_process_get_by_id() is not implemented and cannot be fully tested.\n");
  #else
    will_return(__wrap_cap_get_pid, false);
  #endif // defined(_di_libcap_)

  {
    const f_status_t status = f_capability_process_get_by_id(pid, &capability);

    #if defined(_di_libcap_)
      assert_int_equal(F_status_set_fine(status), F_implement_not);
    #else
      assert_int_equal(status, F_okay);
      assert_int_equal(capability, 1);
    #endif // defined(_di_libcap_)
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
