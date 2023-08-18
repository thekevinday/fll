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
    will_return(__wrap_f_string_ranges_adjust, true);
    will_return(__wrap_f_string_ranges_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_iki_datas_destroy_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_ranges_adjust, false);
    will_return(__wrap_f_string_ranges_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, true);
    will_return(__wrap_f_memory_array_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_iki_datas_destroy_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_ranges_adjust, false);
    will_return(__wrap_f_string_ranges_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_string_ranges_adjust, true);
    will_return(__wrap_f_string_ranges_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_iki_datas_destroy_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_ranges_adjust, false);
    will_return(__wrap_f_string_ranges_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_string_ranges_adjust, false);
    will_return(__wrap_f_string_ranges_adjust, F_okay);

    will_return(__wrap_f_string_ranges_adjust, true);
    will_return(__wrap_f_string_ranges_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_iki_datas_destroy_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_iki_datas_destroy_callback__works(void **state) {

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
  const f_number_unsigned_t length = 1;

  {
    will_return(__wrap_f_string_ranges_adjust, false);
    will_return(__wrap_f_string_ranges_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_string_ranges_adjust, false);
    will_return(__wrap_f_string_ranges_adjust, F_okay);

    will_return(__wrap_f_string_ranges_adjust, false);
    will_return(__wrap_f_string_ranges_adjust, F_okay);

    const f_status_t status = f_iki_datas_destroy_callback(0, length, (void *) datas_array);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
