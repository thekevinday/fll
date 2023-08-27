#include "test-fss.h"
#include "test-fss-set_quote_destroy.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_set_quote_destroy__fails(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 0;

  f_fss_set_quote_t data = f_fss_set_quote_t_initialize;

  {
    will_return(__wrap_f_memory_array_adjust, true);
    will_return(__wrap_f_memory_array_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_fss_set_quote_destroy(&data);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_fss_set_quote_destroy__parameter_checking(void **state) {

  {
    const f_status_t status = f_fss_set_quote_destroy(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_fss_set_quote_destroy__works(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 1;

  const f_number_unsigned_t length = 1;

  f_fss_set_quote_t data = f_fss_set_quote_t_initialize;

  {
    f_status_t status = f_memory_array_resize(length, sizeof(f_string_range_t), (void **) &data.objects.array, &data.objects.used, &data.objects.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_string_ranges_t), (void **) &data.contents.array, &data.contents.used, &data.contents.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_string_range_t), (void **) &data.contents.array[0].array, &data.contents.array[0].used, &data.contents.array[0].size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(uint8_t), (void **) &data.objects_quote.array, &data.objects_quote.used, &data.objects_quote.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_uint8s_t), (void **) &data.contents_quote.array, &data.contents_quote.used, &data.contents_quote.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(uint8_t), (void **) &data.contents_quote.array[0].array, &data.contents_quote.array[0].used, &data.contents_quote.array[0].size);
    assert_int_equal(status, F_okay);
  }

  {
    const f_status_t status = f_fss_set_quote_delete(&data);

    assert_int_equal(status, F_okay);
    assert_int_equal(data.objects.size, 0);
    assert_int_equal(data.contents.size, 0);
    assert_int_equal(data.objects_quote.size, 0);
    assert_int_equal(data.contents_quote.size, 0);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
