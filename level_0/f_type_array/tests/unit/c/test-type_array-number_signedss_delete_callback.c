#include "test-type_array.h"
#include "test-type_array-number_signedss_delete_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_number_signedss_delete_callback__fails(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 0;

  f_number_signed_t data = f_number_signed_t_initialize;
  f_number_signed_t data_array[] = { data };
  f_number_signeds_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_number_signeds_t datas_array[] = { datas };

  {
    will_return(__wrap_f_memory_array_resize, true);
    will_return(__wrap_f_memory_array_resize, F_status_set_error(F_failure));

    const f_status_t status = f_number_signedss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_type_array_number_signedss_delete_callback__works(void **state) {

  mock_unwrap = 1;
  mock_unwrap_f_memory = 1;

  const f_number_signed_t length = 1;

  f_number_signedss_t datass = f_number_signedss_t_initialize;

  {
    f_status_t status = f_memory_array_resize(length, sizeof(f_number_signeds_t), (void **) &datass.array, &datass.used, &datass.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_number_signed_t), (void **) &datass.array[0].array, &datass.array[0].used, &datass.array[0].size);
    assert_int_equal(status, F_okay);
  }

  {
    const f_status_t status = f_number_signedss_delete_callback(0, length, (void *) datass.array);

    assert_int_equal(status, F_okay);
    assert_int_equal(datass.array[0].size, 0);
  }

  free((void *) datass.array);
}

#ifdef __cplusplus
} // extern "C"
#endif