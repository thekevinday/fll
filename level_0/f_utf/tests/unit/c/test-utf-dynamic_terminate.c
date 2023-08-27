#include "test-utf.h"
#include "test-utf-dynamic_terminate.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_string_dynamic_terminate__appends_null(void **state) {

  const f_number_unsigned_t length = 2;
  f_utf_string_dynamic_t data = f_utf_string_dynamic_t_initialize;

  // Put some value in the unused section at the end so that it gets overridden.
  {
    const f_status_t status = f_memory_array_increase_by(length, sizeof(f_utf_char_t), (void **) &data.string, &data.used, &data.size);

    assert_int_equal(status, F_okay);

    data.string[0] = (f_utf_char_t) 'X';
  }

  {
    const f_status_t status = f_utf_string_dynamic_terminate(&data);

    assert_int_equal(status, F_okay);
    assert_int_equal(data.used, 1);
    assert_int_equal(data.string[0], 0);
  }

  free((void *) data.string);
}

void test__f_utf_string_dynamic_terminate__doesnt_append_null(void **state) {

  const f_number_unsigned_t length = 2;
  f_utf_string_dynamic_t data = f_utf_string_dynamic_t_initialize;

  // Ensure a NULL already exists so that the test can confirm that another NULL is not appended.
  {
    const f_status_t status = f_memory_array_increase_by(length, sizeof(f_utf_char_t), (void **) &data.string, &data.used, &data.size);

    assert_int_equal(status, F_okay);

    data.string[0] = 0;
  }

  {
    const f_status_t status = f_utf_string_dynamic_terminate(&data);

    assert_int_equal(status, F_okay);
    assert_int_equal(data.used, 1);
    assert_int_equal(data.string[0], 0);
  }

  free((void *) data.string);
}

void test__f_utf_string_dynamic_terminate__parameter_checking(void **state) {

  {
    const f_status_t status = f_utf_string_dynamic_terminate(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
