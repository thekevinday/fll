#include "test-type_array.h"
#include "test-type_array-polls_resize_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_polls_resize_callback__fails(void **state) {

  f_poll_t data = f_poll_t_initialize;
  f_poll_t data_array[] = { data };
  f_polls_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_polls_t datass_array[] = { datas };

  {
    will_return(__wrap_f_memory_array_resize, true);
    will_return(__wrap_f_memory_array_resize, F_status_set_error(F_failure));

    const f_status_t status = f_polls_resize_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_type_array_polls_resize_callback__works(void **state) {

  f_poll_t data = f_poll_t_initialize;
  f_poll_t data_array[] = { data };
  f_polls_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_polls_t datass_array[] = { datas };
  const f_number_unsigned_t length = 1;

  {
    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_none);

    const f_status_t status = f_polls_resize_callback(0, length, (void *) datass_array);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
