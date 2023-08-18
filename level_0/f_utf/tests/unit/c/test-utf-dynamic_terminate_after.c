#include "test-utf.h"
#include "test-utf-dynamic_terminate_after.h"

#ifdef __cplusplus
extern "C" {
#endif
void test__f_utf_dynamic_terminate_after__appends_null(void **state) {

  const f_number_unsigned_t length = 2;
  f_utf_string_dynamic_t data = f_utf_string_dynamic_t_initialize;

  // Put some value in the unused section at the end so that it gets overridden.
  {
    const f_status_t status = f_utf_string_dynamic_resize(length, &data);

    assert_int_equal(status, F_okay);

    data.string[0] = (f_utf_char_t) 'X';
  }

  {
    const f_status_t status = f_utf_string_dynamic_terminate_after(&data);

    assert_int_equal(status, F_okay);
    assert_int_equal(data.used, 0);
    assert_in_range(data.size, 1, 1 + F_memory_default_allocation_small_d);

    assert_int_equal(data.string[data.used], 0);
  }

  free((void *) data.string);
}

void test__f_utf_dynamic_terminate_after__doesnt_append_null(void **state) {

  const f_number_unsigned_t length = 2;
  f_utf_string_dynamic_t data = f_utf_string_dynamic_t_initialize;

  // Ensure a NULL already exists so that the test can confirm that another NULL is not appended.
  {
    const f_status_t status = f_utf_string_dynamic_resize(length, &data);

    assert_int_equal(status, F_okay);
    assert_in_range(data.size, length, length + F_memory_default_allocation_small_d);

    data.string[0] = 0;
  }

  {
    const f_status_t status = f_utf_string_dynamic_terminate_after(&data);

    assert_int_equal(status, F_okay);
    assert_int_equal(data.used, 0);
    assert_in_range(data.size, length, length + F_memory_default_allocation_small_d);

    assert_int_equal(data.string[data.used], 0);
  }

  free((void *) data.string);
}

void test__f_utf_dynamic_terminate_after__parameter_checking(void **state) {

  {
    const f_status_t status = f_utf_string_dynamic_terminate_after(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
