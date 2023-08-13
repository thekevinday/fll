#include "test-type_array.h"
#include "test-type_array-int64s_destroy_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_int64s_destroy_callback__fails(void **state) {

  int64_t data = 0;
  int64_t data_array[] = { data };
  f_int64s_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_int64s_t datass_array[] = { datas };

  {
    will_return(__wrap_f_memory_array_adjust, true);
    will_return(__wrap_f_memory_array_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_int64s_destroy_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_type_array_int64s_destroy_callback__works(void **state) {

  int64_t data = 0;
  int64_t data_array[] = { data };
  f_int64s_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_int64s_t datass_array[] = { datas };
  const f_number_unsigned_t length = 1;

  {
    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_none);

    const f_status_t status = f_int64s_destroy_callback(0, length, (void *) datass_array);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
