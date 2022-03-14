#include "test-type_array.h"
#include "test-type_array-statuss_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_statuss_append__works(void **state) {

  const f_status_t source = 3;
  f_statuss_t destination = f_statuss_t_initialize;

  {
    const f_status_t status = f_statuss_append(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, 1);
    assert_int_equal(destination.array[0], source);
  }

  free((void *) destination.array);
}

void test__f_type_array_statuss_append__parameter_checking(void **state) {

  const f_status_t data = f_status_t_initialize;

  {
    const f_status_t status = f_statuss_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
