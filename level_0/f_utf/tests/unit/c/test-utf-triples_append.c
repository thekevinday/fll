#include "test-utf.h"
#include "test-utf-triples_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_triples_append__works(void **state) {

  const f_utf_string_static_t test_a = macro_f_utf_string_static_t_initialize((f_utf_string_t) "\0\0\0a", 0, 1);
  const f_utf_string_static_t test_b = macro_f_utf_string_static_t_initialize((f_utf_string_t) "\0\0\0b", 0, 1);
  const f_utf_string_static_t test_c = macro_f_utf_string_static_t_initialize((f_utf_string_t) "\0\0\0c", 0, 1);

  const f_utf_string_triple_t source = macro_f_utf_string_triple_t_initialize(test_a, test_b, test_c);
  f_utf_string_triples_t destination = f_utf_string_triples_t_initialize;

  {
    const f_status_t status = f_utf_string_triples_append(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, 1);
    assert_int_equal(destination.array[0].a.used, source.a.used);
    assert_int_equal(destination.array[0].b.used, source.b.used);
    assert_int_equal(destination.array[0].c.used, source.c.used);

    assert_string_equal(destination.array[0].a.string, source.a.string);
    assert_string_equal(destination.array[0].b.string, source.b.string);
    assert_string_equal(destination.array[0].c.string, source.c.string);
  }

  free((void *) destination.array[0].a.string);
  free((void *) destination.array[0].b.string);
  free((void *) destination.array[0].c.string);
  free((void *) destination.array);
}

void test__f_utf_triples_append__parameter_checking(void **state) {

  const f_utf_string_triple_t data = f_utf_string_triple_t_initialize;

  {
    const f_status_t status = f_utf_string_triples_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
