#include "test-thread.h"
#include "test-thread-attribute_scope_get.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_attribute_scope_get__fails(void **state) {

  f_thread_attribute_t attribute = f_thread_attribute_t_initialize;
  int scope = 0;

  int errnos[] = {
    EINVAL,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_parameter,
    F_failure,
  };

  for (uint8_t i = 0; i < 2; ++i) {

    will_return(__wrap_pthread_attr_getscope, true);
    will_return(__wrap_pthread_attr_getscope, errnos[i]);

    const f_status_t status = f_thread_attribute_scope_get(attribute, &scope);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_attribute_scope_get__parameter_checking(void **state) {

  f_thread_attribute_t attribute = f_thread_attribute_t_initialize;

  {
    const f_status_t status = f_thread_attribute_scope_get(attribute, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_attribute_scope_get__works(void **state) {

  f_thread_attribute_t attribute = f_thread_attribute_t_initialize;
  int scope = 0;

  {
    will_return(__wrap_pthread_attr_getscope, false);

    const f_status_t status = f_thread_attribute_scope_get(attribute, &scope);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
