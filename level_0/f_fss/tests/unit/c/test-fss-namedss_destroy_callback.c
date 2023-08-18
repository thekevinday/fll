#include "test-fss.h"
#include "test-fss-namedss_destroy_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_namedss_destroy_callback__fails(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 0;

  f_fss_named_t data = f_fss_named_t_initialize;
  f_fss_named_t data_array[] = { data };
  f_fss_nameds_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_fss_nameds_t datas_array[] = { datas };

  {
    will_return(__wrap_f_string_ranges_adjust, true);
    will_return(__wrap_f_string_ranges_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_fss_namedss_destroy_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_ranges_adjust, false);
    will_return(__wrap_f_string_ranges_adjust, F_okay);

    will_return(__wrap_f_string_rangess_adjust, true);
    will_return(__wrap_f_string_rangess_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_fss_namedss_destroy_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_ranges_adjust, false);
    will_return(__wrap_f_string_ranges_adjust, F_okay);

    will_return(__wrap_f_string_rangess_adjust, false);
    will_return(__wrap_f_string_rangess_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, true);
    will_return(__wrap_f_memory_arrays_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_fss_namedss_destroy_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_fss_namedss_destroy_callback__works(void **state) {

  mock_unwrap = 1;
  mock_unwrap_f_memory = 1;

  const f_number_unsigned_t length = 1;

  f_fss_namedss_t datass = f_fss_namedss_t_initialize;

  {
    f_status_t status = f_memory_array_adjust(length, sizeof(f_fss_nameds_t), (void **) &datass.array, &datass.used, &datass.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_adjust(1, sizeof(f_fss_named_t), (void **) &datass.array[0].array, &datass.array[0].used, &datass.array[0].size);
    assert_int_equal(status, F_okay);

    status = f_string_ranges_adjust(1, &datass.array[0].array[0].objects);
    assert_int_equal(status, F_okay);

    status = f_string_rangess_adjust(1, &datass.array[0].array[0].contents);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_adjust(1, sizeof(f_uint8s_t), (void **) &datass.array[0].array[0].quotess.array, &datass.array[0].array[0].quotess.used, &datass.array[0].array[0].quotess.size, &f_uint8ss_delete_callback);
    assert_int_equal(status, F_okay);

    status = f_memory_array_adjust(1, sizeof(uint8_t), (void **) &datass.array[0].array[0].quotess.array[0].array, &datass.array[0].array[0].quotess.array[0].used, &datass.array[0].array[0].quotess.array[0].size);
    assert_int_equal(status, F_okay);
  }

  {
    const f_status_t status = f_fss_namedss_destroy_callback(0, length, (void *) datass.array);

    assert_int_equal(status, F_okay);
    assert_int_equal(datass.array[0].size, 0);
  }

  free((void *) datass.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
