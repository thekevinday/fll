#include "test-utf.h"
#include "test-utf-tripless_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_tripless_append__works(void **state) {

  const int length_sources = 2;

  const f_utf_string_static_t test_a = macro_f_utf_string_static_t_initialize_1((f_utf_string_t) "\0\0\0a", 0, 1);
  const f_utf_string_static_t test_b = macro_f_utf_string_static_t_initialize_1((f_utf_string_t) "\0\0\0b", 0, 1);
  const f_utf_string_static_t test_c = macro_f_utf_string_static_t_initialize_1((f_utf_string_t) "\0\0\0c", 0, 1);

  const f_utf_string_static_t test_d = macro_f_utf_string_static_t_initialize_1((f_utf_string_t) "\0\0\0d", 0, 1);
  const f_utf_string_static_t test_e = macro_f_utf_string_static_t_initialize_1((f_utf_string_t) "\0\0\0e", 0, 1);
  const f_utf_string_static_t test_f = macro_f_utf_string_static_t_initialize_1((f_utf_string_t) "\0\0\0f", 0, 1);

  f_utf_string_triple_t sources_array[] = {
    macro_f_utf_string_triple_t_initialize_1(test_a, test_b, test_c),
    macro_f_utf_string_triple_t_initialize_1(test_d, test_e, test_f),
  };

  const f_utf_string_triples_t source = macro_f_utf_string_triples_t_initialize_1(sources_array, 0, length_sources);
  f_utf_string_tripless_t destination = f_utf_string_tripless_t_initialize;

  {
    const f_status_t status = f_utf_string_tripless_append(source, &destination);

    assert_int_equal(status, F_okay);
    assert_int_equal(destination.array[0].used, length_sources);

    for (f_number_unsigned_t i = 0; i < length_sources; ++i) {

      assert_int_equal(destination.array[0].array[i].a.used, sources_array[i].a.used);
      assert_int_equal(destination.array[0].array[i].b.used, sources_array[i].b.used);
      assert_int_equal(destination.array[0].array[i].c.used, sources_array[i].c.used);

      assert_string_equal(destination.array[0].array[i].a.string, sources_array[i].a.string);
      assert_string_equal(destination.array[0].array[i].b.string, sources_array[i].b.string);
      assert_string_equal(destination.array[0].array[i].c.string, sources_array[i].c.string);
    } // for
  }

  for (f_number_unsigned_t i = 0; i < destination.array[0].used; ++i) {

    free((void *) destination.array[0].array[i].a.string);
    free((void *) destination.array[0].array[i].b.string);
    free((void *) destination.array[0].array[i].c.string);
  } // for

  free((void *) destination.array[0].array);
  free((void *) destination.array);
}

void test__f_utf_tripless_append__returns_data_not(void **state) {

  const int length = 5;
  f_utf_string_triples_t source = f_utf_string_tripless_t_initialize;
  f_utf_string_tripless_t destination = f_utf_string_tripless_t_initialize;

  {
    const f_status_t status = f_utf_string_triples_resize(length, &source);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_utf_string_tripless_append(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_utf_tripless_append__parameter_checking(void **state) {

  f_utf_string_triples_t data = f_utf_string_triples_t_initialize;

  {
    const f_status_t status = f_utf_string_tripless_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
