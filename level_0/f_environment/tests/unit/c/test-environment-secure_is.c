#include "test-environment.h"
#include "test-environment-secure_is.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_environment_secure_is__fails(void **state) {

  #ifndef _di_libcap_
    {
      int errnos[] = {
        EINVAL,
        EPERM,
        ENOMEM,
        mock_errno_generic,
      };

      f_status_t statuss[] = {
        F_parameter,
        F_prohibited,
        F_memory_not,
        F_failure,
      };

      for (int i = 0; i < 4; ++i) {

        will_return(__wrap_geteuid, 1);
        will_return(__wrap_getuid, 2);

        will_return(__wrap_cap_get_proc, true);
        will_return(__wrap_cap_get_proc, errnos[i]);

        const f_status_t status = f_environment_secure_is();

        assert_int_equal(F_status_set_fine(status), statuss[i]);
      } // for
    }

    {
      int errnos[] = {
        EINVAL,
        mock_errno_generic,
      };

      f_status_t statuss[] = {
        F_parameter,
        F_failure,
      };

      for (int i = 0; i < 2; ++i) {

        long stub = 0;
        cap_t capability = (cap_t) &stub;

        will_return(__wrap_geteuid, 1);
        will_return(__wrap_getuid, 1);

        will_return(__wrap_getegid, 3);
        will_return(__wrap_getgid, 4);

        will_return(__wrap_cap_get_proc, false);
        will_return(__wrap_cap_get_proc, capability);

        will_return(__wrap_cap_get_flag, true);
        will_return(__wrap_cap_get_flag, errnos[i]);

        will_return(__wrap_cap_free, 0);

        const f_status_t status = f_environment_secure_is();

        assert_int_equal(F_status_set_fine(status), statuss[i]);
      } // for
    }
  #endif // _di_libcap_
}

void test__f_environment_secure_is__works(void **state) {

  {
    will_return(__wrap_geteuid, 1);
    will_return(__wrap_getuid, 1);

    will_return(__wrap_getegid, 1);
    will_return(__wrap_getgid, 1);

    const f_status_t status = f_environment_secure_is();

    assert_int_equal(status, F_true);
  }

  {
    #ifndef _di_libcap_
      long stub = 0;
      cap_t capability = (cap_t) &stub;
    #endif // _di_libcap_

    will_return(__wrap_geteuid, 1);
    will_return(__wrap_getuid, 0);

    #ifndef _di_libcap_
      will_return(__wrap_cap_get_proc, false);
      will_return(__wrap_cap_get_proc, capability);

      will_return(__wrap_cap_get_flag, false);
      will_return(__wrap_cap_get_flag, CAP_CLEAR);
      will_return(__wrap_cap_get_flag, 0);

      will_return(__wrap_cap_free, 0);
    #endif // _di_libcap_

    const f_status_t status = f_environment_secure_is();

    assert_int_equal(status, F_false);
  }

  #ifndef _di_libcap_
    {
      long stub = 0;
      cap_t capability = (cap_t) &stub;

      will_return(__wrap_geteuid, 1);
      will_return(__wrap_getuid, 1);

      will_return(__wrap_getegid, 1);
      will_return(__wrap_getgid, 2);

      will_return(__wrap_cap_get_proc, false);
      will_return(__wrap_cap_get_proc, capability);

      will_return(__wrap_cap_get_flag, false);
      will_return(__wrap_cap_get_flag, CAP_CLEAR);
      will_return(__wrap_cap_get_flag, 0);

      will_return(__wrap_cap_free, 0);

      const f_status_t status = f_environment_secure_is();

      assert_int_equal(status, F_false);
    }
  #endif // _di_libcap_

  #ifndef _di_libcap_
    {
      long stub = 0;
      cap_t capability = (cap_t) &stub;;

      will_return(__wrap_geteuid, 1);
      will_return(__wrap_getuid, 2);

      will_return(__wrap_cap_get_proc, false);
      will_return(__wrap_cap_get_proc, capability);

      will_return(__wrap_cap_get_flag, false);
      will_return(__wrap_cap_get_flag, CAP_SET);
      will_return(__wrap_cap_get_flag, 0);

      will_return(__wrap_cap_free, 0);

      const f_status_t status = f_environment_secure_is();

      assert_int_equal(status, F_true);
    }
  #endif // _di_libcap_
}

#ifdef __cplusplus
} // extern "C"
#endif
