#include "test-fss.h"
#include "test-fss-set_quotess_delete_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_set_quotess_delete_callback__fails(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 0;

  f_string_range_t base = f_string_range_t_initialize;
  f_string_range_t base_array[] = { base };
  f_string_ranges_t objects = { .array = base_array, .used = 0, .size = 1 };
  f_string_ranges_t objects_array[] = { objects };
  f_string_rangess_t contents = { .array = objects_array, .used = 0, .size = 1 };

  uint8_t quote_array[] = { 0 };
  f_uint8s_t quotes = { .array = quote_array, .used = 0, .size = 1 };
  f_uint8s_t quotes_array[] = { quotes };
  f_uint8ss_t quotess = { .array = quotes_array, .used = 0, .size = 1 };;

  f_fss_set_quote_t data = { .objects = objects, .contents = contents, .objects_quote = quotes, .contents_quote = quotess };
  f_fss_set_quote_t data_array[] = { data };
  f_fss_set_quotes_t datas = { .array = data_array, .used = 0, .size = 1 };
  f_fss_set_quotes_t datas_array[] = { datas };

  {
    will_return(__wrap_f_memory_array_resize, true);
    will_return(__wrap_f_memory_array_resize, F_status_set_error(F_failure));

    const f_status_t status = f_fss_set_quotess_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0].size = 1;
  datas_array[0].array[0].objects = objects;
  datas_array[0].array[0].contents = contents;
  datas_array[0].array[0].objects_quote = quotes;
  datas_array[0].array[0].contents_quote = quotess;

  {
    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, true);
    will_return(__wrap_f_memory_arrays_resize, F_status_set_error(F_failure));

    const f_status_t status = f_fss_set_quotess_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0].size = 1;
  datas_array[0].array[0].objects = objects;
  datas_array[0].array[0].contents = contents;
  datas_array[0].array[0].objects_quote = quotes;
  datas_array[0].array[0].contents_quote = quotess;

  {
    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, true);
    will_return(__wrap_f_memory_array_resize, F_status_set_error(F_failure));

    const f_status_t status = f_fss_set_quotess_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0].size = 1;
  datas_array[0].array[0].objects = objects;
  datas_array[0].array[0].contents = contents;
  datas_array[0].array[0].objects_quote = quotes;
  datas_array[0].array[0].contents_quote = quotess;

  {
    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, true);
    will_return(__wrap_f_memory_arrays_resize, F_status_set_error(F_failure));

    const f_status_t status = f_fss_set_quotess_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_fss_set_quotess_delete_callback__works(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 1;

  const f_number_unsigned_t length = 1;

  f_fss_set_quotess_t datass = f_fss_set_quotess_t_initialize;

  {
    f_status_t status = f_memory_array_resize(length, sizeof(f_fss_set_quotes_t), (void **) &datass.array, &datass.used, &datass.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_fss_set_quote_t), (void **) &datass.array[0].array, &datass.array[0].used, &datass.array[0].size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_string_range_t), (void **) &datass.array[0].array[0].objects.array, &datass.array[0].array[0].objects.used, &datass.array[0].array[0].objects.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_string_range_t), (void **) &datass.array[0].array[0].contents.array, &datass.array[0].array[0].contents.used, &datass.array[0].array[0].contents.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(uint8_t), (void **) &datass.array[0].array[0].objects_quote.array, &datass.array[0].array[0].objects_quote.used, &datass.array[0].array[0].objects_quote.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_uint8s_t), (void **) &datass.array[0].array[0].contents_quote.array, &datass.array[0].array[0].contents_quote.used, &datass.array[0].array[0].contents_quote.size);
    assert_int_equal(status, F_okay);
  }

  {
    const f_status_t status = f_fss_set_quotess_delete_callback(0, length, (void *) datass.array);

    assert_int_equal(status, F_okay);
    assert_int_equal(datass.array[0].size, 0);
  }

  free((void *) datass.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
