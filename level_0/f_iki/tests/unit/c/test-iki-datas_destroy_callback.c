#include "test-iki.h"
#include "test-iki-datas_destroy_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_iki_datas_destroy_callback__fails(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 0;

  f_string_ranges_t content = f_string_ranges_t_initialize;
  f_number_unsigneds_t delimits = f_number_unsigneds_t_initialize;
  f_string_ranges_t variable = f_string_ranges_t_initialize;
  f_string_ranges_t vocabulary = f_string_ranges_t_initialize;
  f_iki_data_t data = { .content = content, .delimits = delimits, .variable = variable, .vocabulary = vocabulary };
  f_iki_data_t data_array[] = { data };
  f_iki_datas_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_iki_datas_t datas_array[] = { datas };

  {
    will_return(__wrap_f_memory_array_adjust, true);
    will_return(__wrap_f_memory_array_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_iki_datas_destroy_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, true);
    will_return(__wrap_f_memory_array_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_iki_datas_destroy_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, true);
    will_return(__wrap_f_memory_array_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_iki_datas_destroy_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, true);
    will_return(__wrap_f_memory_array_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_iki_datas_destroy_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_iki_datas_destroy_callback__works(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 1;

  const f_number_unsigned_t length = 1;

  f_iki_datas_t datas = f_iki_datas_t_initialize;

  {
    f_status_t status = f_memory_array_resize(1, sizeof(f_iki_data_t), (void **) &datas.array, &datas.used, &datas.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_string_range_t), (void **) &datas.array[0].content.array, &datas.array[0].content.used, &datas.array[0].content.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_number_unsigned_t), (void **) &datas.array[0].delimits.array, &datas.array[0].delimits.used, &datas.array[0].delimits.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_string_range_t), (void **) &datas.array[0].variable.array, &datas.array[0].variable.used, &datas.array[0].variable.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_string_range_t), (void **) &datas.array[0].vocabulary.array, &datas.array[0].vocabulary.used, &datas.array[0].vocabulary.size);
    assert_int_equal(status, F_okay);
  }

  {
    const f_status_t status = f_iki_datas_destroy_callback(0, length, (void *) datas.array);

    assert_int_equal(status, F_okay);
    assert_int_equal(datas.array[0].content.size, 0);
    assert_int_equal(datas.array[0].delimits.size, 0);
    assert_int_equal(datas.array[0].variable.size, 0);
    assert_int_equal(datas.array[0].vocabulary.size, 0);
  }

  free((void *) datas.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
