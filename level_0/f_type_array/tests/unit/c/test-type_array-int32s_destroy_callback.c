#include "test-type_array.h"
#include "test-type_array-int32s_destroy_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_int32s_destroy_callback__fails(void **state) {

  int32_t data = 0;
  int32_t data_array[] = { data };
  f_int32s_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_int32s_t datass_array[] = { datas };

  {
    will_return(__wrap_f_memory_array_adjust, true);
    will_return(__wrap_f_memory_array_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_int32s_destroy_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_type_array_int32s_destroy_callback__works(void **state) {

  int32_t data = 0;
  int32_t data_array[] = { data };
  f_int32s_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_int32s_t datass_array[] = { datas };
  const f_number_unsigned_t length = 1;

  {
    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_none);

    const f_status_t status = f_int32s_destroy_callback(0, length, (void *) datass_array);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
