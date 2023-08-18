#include "test-utf.h"
#include "test-utf-triples_increase_by.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_triples_increase_by__works(void **state) {

  const int length = 5;
  f_utf_string_triples_t data = f_utf_string_triples_t_initialize;

  {
    const f_status_t status = f_utf_string_triples_resize(length, &data);

    assert_int_equal(status, F_okay);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  {
    data.used = length;

    const f_status_t status = f_utf_string_triples_increase_by(length, &data);

    assert_int_equal(status, F_okay);
    assert_int_equal(data.used, length);
    assert_int_equal(data.size, length * 2);
  }

  free((void *) data.array);
}

void test__f_utf_triples_increase_by__parameter_checking(void **state) {

  const int length = 5;
  f_utf_string_triples_t data = f_utf_string_triples_t_initialize;

  {
    const f_status_t status = f_utf_string_triples_increase_by(length, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  assert_null(data.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
