#include "test-thread.h"
#include "test-thread-attribute_affinity_get.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_attribute_affinity_get__fails(void **state) {

  f_thread_attribute_t attribute = f_thread_attribute_t_initialize;
  cpu_set_t cpu_set;

  memset(&cpu_set, 0, sizeof(cpu_set_t));

  #if defined(_pthread_attr_unsupported_)
    const f_status_t status = f_thread_attribute_affinity_get(attribute, 0, &cpu_set);

    assert_int_equal(status, F_status_set_error(F_implement_not));
  #else
    int errnos[] = {
      EINVAL,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_parameter,
      F_failure,
    };

    for (uint8_t i = 0; i < 2; ++i) {

      will_return(__wrap_pthread_attr_getaffinity_np, true);
      will_return(__wrap_pthread_attr_getaffinity_np, errnos[i]);

      const f_status_t status = f_thread_attribute_affinity_get(attribute, 0, &cpu_set);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  #endif // defined(_pthread_attr_unsupported_)
}

void test__f_thread_attribute_affinity_get__parameter_checking(void **state) {

  f_thread_attribute_t attribute = f_thread_attribute_t_initialize;

  {
    const f_status_t status = f_thread_attribute_affinity_get(attribute, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_attribute_affinity_get__works(void **state) {

  f_thread_attribute_t attribute = f_thread_attribute_t_initialize;
  cpu_set_t cpu_set;

  memset(&cpu_set, 0, sizeof(cpu_set_t));

  #if defined(_pthread_attr_unsupported_)
    {
      const f_status_t status = f_thread_attribute_affinity_get(attribute, 0, &cpu_set);

      assert_int_equal(status, F_status_set_error(F_implement_not));
    }
  #else
    {
      will_return(__wrap_pthread_attr_getaffinity_np, false);

      const f_status_t status = f_thread_attribute_affinity_get(attribute, 0, &cpu_set);

      assert_int_equal(status, F_okay);
    }
  #endif // defined(_pthread_attr_unsupported_)
}

#ifdef __cplusplus
} // extern "C"
#endif
