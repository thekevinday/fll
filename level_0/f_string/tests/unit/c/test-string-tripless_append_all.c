#include "test-string.h"
#include "test-string-tripless_append_all.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_string_tripless_append_all__works(void **state) {

  const int length_sources = 2;
  const int length_sources_set = 2;

  const f_string_static_t test_a = macro_f_string_static_t_initialize("a", 0, 1);
  const f_string_static_t test_b = macro_f_string_static_t_initialize("b", 0, 1);
  const f_string_static_t test_c = macro_f_string_static_t_initialize("c", 0, 1);

  const f_string_static_t test_d = macro_f_string_static_t_initialize("d", 0, 1);
  const f_string_static_t test_e = macro_f_string_static_t_initialize("e", 0, 1);
  const f_string_static_t test_f = macro_f_string_static_t_initialize("f", 0, 1);

  const f_string_static_t test_g = macro_f_string_static_t_initialize("g", 0, 1);
  const f_string_static_t test_h = macro_f_string_static_t_initialize("h", 0, 1);
  const f_string_static_t test_i = macro_f_string_static_t_initialize("i", 0, 1);

  const f_string_static_t test_j = macro_f_string_static_t_initialize("j", 0, 1);
  const f_string_static_t test_k = macro_f_string_static_t_initialize("k", 0, 1);
  const f_string_static_t test_l = macro_f_string_static_t_initialize("l", 0, 1);

  f_string_triple_t sources_array1[] = {
    macro_f_string_triple_t_initialize(test_a, test_b, test_c),
    macro_f_string_triple_t_initialize(test_d, test_e, test_f),
  };

  f_string_triple_t sources_array2[] = {
    macro_f_string_triple_t_initialize(test_g, test_h, test_i),
    macro_f_string_triple_t_initialize(test_j, test_k, test_l),
  };

  f_string_triples_t sources_set_array[] = {
    macro_f_string_triples_t_initialize(sources_array1, 0, length_sources),
    macro_f_string_triples_t_initialize(sources_array2, 0, length_sources),
  };

  const f_string_tripless_t source = macro_f_string_tripless_t_initialize(sources_set_array, 0, length_sources_set);
  f_string_tripless_t destination = f_string_tripless_t_initialize;

  {
    const f_status_t status = f_string_tripless_append_all(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, source.used);

    for (f_array_length_t j = 0; j < length_sources_set; ++j) {

      for (f_array_length_t i = 0; i < length_sources; ++i) {

        assert_int_equal(destination.array[j].array[i].a.used, sources_set_array[j].array[i].a.used);
        assert_int_equal(destination.array[j].array[i].b.used, sources_set_array[j].array[i].b.used);
        assert_int_equal(destination.array[j].array[i].c.used, sources_set_array[j].array[i].c.used);

        assert_string_equal(destination.array[j].array[i].a.string, sources_set_array[j].array[i].a.string);
        assert_string_equal(destination.array[j].array[i].b.string, sources_set_array[j].array[i].b.string);
        assert_string_equal(destination.array[j].array[i].c.string, sources_set_array[j].array[i].c.string);
      } // for
    } // for
  }

  for (f_array_length_t j = 0; j < destination.used; ++j) {

    for (f_array_length_t i = 0; i < destination.array[j].used; ++i) {

      free((void *) destination.array[j].array[i].a.string);
      free((void *) destination.array[j].array[i].b.string);
      free((void *) destination.array[j].array[i].c.string);
    } // for

    free((void *) destination.array[j].array);
  } // for

  free((void *) destination.array);
}

void test__f_string_tripless_append_all__returns_data_not(void **state) {

  const int length = 5;
  f_string_tripless_t source = f_string_tripless_t_initialize;
  f_string_tripless_t destination = f_string_tripless_t_initialize;

  {
    const f_status_t status = f_string_tripless_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_string_tripless_append_all(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_string_tripless_append_all__parameter_checking(void **state) {

  const f_string_tripless_t data = f_string_tripless_t_initialize;

  {
    const f_status_t status = f_string_tripless_append_all(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
