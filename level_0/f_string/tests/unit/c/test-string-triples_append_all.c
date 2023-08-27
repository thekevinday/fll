#include "test-string.h"
#include "test-string-triples_append_all.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_string_triples_append_all__works(void **state) {

  const int length_sources = 2;

  const f_string_static_t test_a = macro_f_string_static_t_initialize_1("a", 0, 1);
  const f_string_static_t test_b = macro_f_string_static_t_initialize_1("b", 0, 1);
  const f_string_static_t test_c = macro_f_string_static_t_initialize_1("c", 0, 1);

  const f_string_static_t test_d = macro_f_string_static_t_initialize_1("d", 0, 1);
  const f_string_static_t test_e = macro_f_string_static_t_initialize_1("e", 0, 1);
  const f_string_static_t test_f = macro_f_string_static_t_initialize_1("f", 0, 1);

  f_string_triple_t sources_array[] = {
    macro_f_string_triple_t_initialize_1(test_a, test_b, test_c),
    macro_f_string_triple_t_initialize_1(test_d, test_e, test_f),
  };

  const f_string_triples_t source = macro_f_string_triples_t_initialize_1(sources_array, 0, length_sources);
  f_string_triples_t destination = f_string_triples_t_initialize;

  {
    const f_status_t status = f_string_triples_append_all(source, &destination);

    assert_int_equal(status, F_okay);
    assert_int_equal(destination.used, source.used);
    assert_int_equal(destination.size, source.used);

    for (f_number_unsigned_t i = 0; i < length_sources; ++i) {

      assert_int_equal(destination.array[i].a.used, source.array[i].a.used);
      assert_int_equal(destination.array[i].b.used, source.array[i].b.used);
      assert_int_equal(destination.array[i].c.used, source.array[i].c.used);

      assert_string_equal(destination.array[i].a.string, source.array[i].a.string);
      assert_string_equal(destination.array[i].b.string, source.array[i].b.string);
      assert_string_equal(destination.array[i].c.string, source.array[i].c.string);
    } // for
  }

  for (f_number_unsigned_t i = 0; i < destination.used; ++i) {

    free((void *) destination.array[i].a.string);
    free((void *) destination.array[i].b.string);
    free((void *) destination.array[i].c.string);
  } // for

  free((void *) destination.array);
}

void test__f_string_triples_append_all__returns_data_not(void **state) {

  const int length = 5;
  f_string_triples_t source = f_string_triples_t_initialize;
  f_string_triples_t destination = f_string_triples_t_initialize;

  {
    const f_status_t status = f_memory_arrays_resize(length, sizeof(f_string_triple_t), (void **) &source.array, &source.used, &source.size, &f_string_triples_delete_callback);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_string_triples_append_all(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_string_triples_append_all__parameter_checking(void **state) {

  const f_string_triples_t data = f_string_triples_t_initialize;

  {
    const f_status_t status = f_string_triples_append_all(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
