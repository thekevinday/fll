#include "test-fss.h"
#include "test-fss-set_quotes_destroy_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_set_quotes_destroy_callback__fails(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 0;

  f_fss_set_quote_t data = f_fss_set_quote_t_initialize;
  f_fss_set_quote_t data_array[] = { data };
  f_fss_set_quotes_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_fss_set_quotes_t datas_array[] = { datas };

  {
    will_return(__wrap_f_memory_array_adjust, true);
    will_return(__wrap_f_memory_array_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_fss_set_quotes_destroy_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, true);
    will_return(__wrap_f_memory_arrays_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_fss_set_quotes_destroy_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, true);
    will_return(__wrap_f_memory_array_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_fss_set_quotes_destroy_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, true);
    will_return(__wrap_f_memory_arrays_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_fss_set_quotes_destroy_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_fss_set_quotes_destroy_callback__works(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 1;

  const f_number_unsigned_t length = 1;

  f_fss_set_quotes_t datas = f_fss_set_quotes_t_initialize;

  {
    f_status_t status = f_memory_array_resize(length, sizeof(f_fss_set_quote_t), (void **) &datas.array, &datas.used, &datas.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_string_range_t), (void **) &datas.array[0].objects.array, &datas.array[0].objects.used, &datas.array[0].objects.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_string_ranges_t), (void **) &datas.array[0].contents.array, &datas.array[0].contents.used, &datas.array[0].contents.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_string_range_t), (void **) &datas.array[0].contents.array[0].array, &datas.array[0].contents.array[0].used, &datas.array[0].contents.array[0].size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(uint8_t), (void **) &datas.array[0].objects_quote.array, &datas.array[0].objects_quote.used, &datas.array[0].objects_quote.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_uint8s_t), (void **) &datas.array[0].contents_quote.array, &datas.array[0].contents_quote.used, &datas.array[0].contents_quote.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(uint8_t), (void **) &datas.array[0].contents_quote.array[0].array, &datas.array[0].contents_quote.array[0].used, &datas.array[0].contents_quote.array[0].size);
    assert_int_equal(status, F_okay);
  }

  {
    const f_status_t status = f_fss_set_quotes_destroy_callback(0, length, (void *) datas.array);

    assert_int_equal(status, F_okay);
    assert_int_equal(datas.array[0].objects.size, 0);
    assert_int_equal(datas.array[0].contents.size, 0);
    assert_int_equal(datas.array[0].objects_quote.size, 0);
    assert_int_equal(datas.array[0].contents_quote.size, 0);
  }

  free((void *) datas.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
