#include "test-iki.h"
#include "test-iki-datass_destroy_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_iki_datass_destroy_callback__fails(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 0;

  f_string_range_t base = macro_f_string_range_t_initialize_1(1, 0);
  f_string_range_t base_array[] = { base };
  f_string_ranges_t bases = { .array = base_array, .used = 0, .size = 1 };

  f_string_ranges_t content = bases;
  f_number_unsigned_t delimit_array[] = { 0 };
  f_number_unsigneds_t delimits = { .array = delimit_array, .used = 0, .size = 1 };
  f_string_ranges_t variable = bases;
  f_string_ranges_t vocabulary = bases;

  f_iki_data_t data = { .content = content, .delimits = delimits, .variable = variable, .vocabulary = vocabulary };
  f_iki_data_t data_array[] = { data };
  f_iki_datas_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_iki_datas_t datas_array[] = { datas };

  {
    will_return(__wrap_f_memory_array_adjust, true);
    will_return(__wrap_f_memory_array_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_iki_datass_destroy_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0].size = 1;
  datas_array[0].array[0].content = content;
  datas_array[0].array[0].delimits = delimits;
  datas_array[0].array[0].variable = variable;
  datas_array[0].array[0].vocabulary = vocabulary;

  {
    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, true);
    will_return(__wrap_f_memory_array_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_iki_datass_destroy_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0].size = 1;
  datas_array[0].array[0].content = content;
  datas_array[0].array[0].delimits = delimits;
  datas_array[0].array[0].variable = variable;
  datas_array[0].array[0].vocabulary = vocabulary;

  {
    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, true);
    will_return(__wrap_f_memory_array_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_iki_datass_destroy_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0].size = 1;
  datas_array[0].array[0].content = content;
  datas_array[0].array[0].delimits = delimits;
  datas_array[0].array[0].variable = variable;
  datas_array[0].array[0].vocabulary = vocabulary;

  {
    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, true);
    will_return(__wrap_f_memory_array_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_iki_datass_destroy_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0].size = 1;
  datas_array[0].array[0].content = content;
  datas_array[0].array[0].delimits = delimits;
  datas_array[0].array[0].variable = variable;
  datas_array[0].array[0].vocabulary = vocabulary;

  {
    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, true);
    will_return(__wrap_f_memory_array_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_iki_datass_destroy_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_iki_datass_destroy_callback__works(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 1;

  const f_number_unsigned_t length = 1;

  f_iki_datass_t datass = f_iki_datass_t_initialize;

  {
    f_status_t status = f_memory_array_resize(length, sizeof(f_iki_datas_t), (void **) &datass.array, &datass.used, &datass.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_iki_data_t), (void **) &datass.array[0].array, &datass.array[0].used, &datass.array[0].size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_string_range_t), (void **) &datass.array[0].array[0].content.array, &datass.array[0].array[0].content.used, &datass.array[0].array[0].content.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_number_unsigned_t), (void **) &datass.array[0].array[0].delimits.array, &datass.array[0].array[0].delimits.used, &datass.array[0].array[0].delimits.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_string_range_t), (void **) &datass.array[0].array[0].variable.array, &datass.array[0].array[0].variable.used, &datass.array[0].array[0].variable.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_string_range_t), (void **) &datass.array[0].array[0].vocabulary.array, &datass.array[0].array[0].vocabulary.used, &datass.array[0].array[0].vocabulary.size);
    assert_int_equal(status, F_okay);
  }

  {
    const f_status_t status = f_iki_datass_destroy_callback(0, length, (void *) datass.array);

    assert_int_equal(status, F_okay);
    assert_int_equal(datass.array[0].size, 0);
  }

  free((void *) datass.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
