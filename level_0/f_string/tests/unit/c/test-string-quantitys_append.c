#include "test-string.h"
#include "test-string-quantitys_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_string_quantitys_append__works(void **state) {

  const f_string_quantity_t source = macro_f_string_quantity_t_initialize(1, 2);
  f_string_quantitys_t destination = f_string_quantitys_t_initialize;

  {
    const f_status_t status = f_string_quantitys_append(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, 1);
    assert_int_equal(destination.array[0].start, source.start);
    assert_int_equal(destination.array[0].total, source.total);
  }

  free((void *) destination.array);
}

void test__f_string_quantitys_append__parameter_checking(void **state) {

  const f_string_quantity_t data = f_string_quantity_t_initialize;

  {
    const f_status_t status = f_string_quantitys_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
