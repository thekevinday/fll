#include "test-thread.h"
#include "test-thread-attribute_affinity_set.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_attribute_affinity_set__fails(void **state) {

  f_thread_attribute_t attribute = f_thread_attribute_t_initialize;
  cpu_set_t cpu_set;

  memset(&cpu_set, 0, sizeof(cpu_set_t));

  #if defined(_pthread_attr_unsupported_)
    const f_status_t status = f_thread_attribute_affinity_set(0, &cpu_set, &attribute);

    assert_int_equal(status, F_status_set_error(F_implemented_not));
  #else
    int errnos[] = {
      EINVAL,
      ENOMEM,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_parameter,
      F_memory_not,
      F_failure,
    };

    for (uint8_t i = 0; i < 3; ++i) {

      will_return(__wrap_pthread_attr_setaffinity_np, true);
      will_return(__wrap_pthread_attr_setaffinity_np, errnos[i]);

      const f_status_t status = f_thread_attribute_affinity_set(0, &cpu_set, &attribute);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  #endif // defined(_pthread_attr_unsupported_)
}

void test__f_thread_attribute_affinity_set__parameter_checking(void **state) {

  cpu_set_t cpu_set;

  memset(&cpu_set, 0, sizeof(cpu_set_t));

  {
    const f_status_t status = f_thread_attribute_affinity_set(0, &cpu_set, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_attribute_affinity_set__works(void **state) {

  f_thread_attribute_t attribute = f_thread_attribute_t_initialize;
  cpu_set_t cpu_set;

  memset(&cpu_set, 0, sizeof(cpu_set_t));

  #if defined(_pthread_attr_unsupported_)
    {
      const f_status_t status = f_thread_attribute_affinity_set(0, &cpu_set, &attribute);

      assert_int_equal(status, F_status_set_error(F_implemented_not));
    }
  #else
    {
      will_return(__wrap_pthread_attr_setaffinity_np, false);

      const f_status_t status = f_thread_attribute_affinity_set(0, &cpu_set, &attribute);

      assert_int_equal(status, F_none);
    }
  #endif // defined(_pthread_attr_unsupported_)
}

#ifdef __cplusplus
} // extern "C"
#endif
