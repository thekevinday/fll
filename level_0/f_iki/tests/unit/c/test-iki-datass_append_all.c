#include "test-iki.h"
#include "test-iki-datass_append_all.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_iki_datass_append_all__works(void **state) {

  const int length = 5;
  const int length_inner = 2;
  const int length_outer = 2;
  f_iki_datass_t source = f_iki_datass_t_initialize;
  f_iki_datass_t destination = f_iki_datass_t_initialize;

  {
    f_status_t status = f_memory_arrays_resize(length_outer, sizeof(f_iki_data_t), (void **) &source.array, &source.used, &source.size, &f_iki_datas_resize_callback);

    assert_int_equal(status, F_none);
    assert_int_equal(source.size, length_outer);

    f_number_unsigned_t i = 1;
    f_number_unsigned_t j = 0;

    for (; source.used < length_outer; ++source.used) {

      status = f_memory_array_resize(length_inner, sizeof(f_iki_data_t), (void **) &source.array[source.used].array, &source.array[source.used].used, &source.array[source.used].size);

      assert_int_equal(status, F_none);
      assert_int_equal(source.array[source.used].size, length_inner);

      for (j = 0; j < length_inner; ++j) {

        status = f_string_ranges_resize(length, &source.array[source.used].array[j].content);

        assert_int_equal(status, F_none);
        assert_int_equal(source.array[source.used].array[j].content.size, length);

        status = f_memory_array_resize(length, sizeof(f_number_unsigned_t), (void **) &source.array[source.used].array[j].delimits.array, &source.array[source.used].array[j].delimits.used, &source.array[source.used].array[j].delimits.size);

        assert_int_equal(status, F_none);
        assert_int_equal(source.array[source.used].array[j].delimits.size, length);

        status = f_string_ranges_resize(length, &source.array[source.used].array[j].variable);

        assert_int_equal(status, F_none);
        assert_int_equal(source.array[source.used].array[j].variable.size, length);

        status = f_string_ranges_resize(length, &source.array[source.used].array[j].vocabulary);

        assert_int_equal(status, F_none);
        assert_int_equal(source.array[source.used].array[j].vocabulary.size, length);

        for (; source.array[source.used].array[j].content.used < length; ++i) {

          source.array[source.used].array[j].content.array[source.array[source.used].array[j].content.used].start = i - 1;
          source.array[source.used].array[j].content.array[source.array[source.used].array[j].content.used++].stop = i;
        } // for

        for (; source.array[source.used].array[j].delimits.used < length; ++i) {
          source.array[source.used].array[j].delimits.array[source.array[source.used].array[j].delimits.used++] = i;
        } // for

        for (; source.array[source.used].array[j].variable.used < length; ++i) {

          source.array[source.used].array[j].variable.array[source.array[source.used].array[j].variable.used].start = i - 1;
          source.array[source.used].array[j].variable.array[source.array[source.used].array[j].variable.used++].stop = i;
        } // for

        for (; source.array[source.used].array[j].vocabulary.used < length; ++i) {

          source.array[source.used].array[j].vocabulary.array[source.array[source.used].array[j].vocabulary.used].start = i - 1;
          source.array[source.used].array[j].vocabulary.array[source.array[source.used].array[j].vocabulary.used++].stop = i;
        } // for
      } // for

      source.array[source.used].used = length_inner;
    } // for
  }

  {
    const f_status_t status = f_iki_datass_append_all(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, source.used);

    for (f_number_unsigned_t k = 0; k < length_outer; ++k) {

      for (f_number_unsigned_t j = 0; j < length_inner; ++j) {

        assert_int_equal(destination.array[k].array[j].content.used, source.array[k].array[j].content.used);
        assert_int_equal(destination.array[k].array[j].delimits.used, source.array[k].array[j].delimits.used);
        assert_int_equal(destination.array[k].array[j].variable.used, source.array[k].array[j].variable.used);
        assert_int_equal(destination.array[k].array[j].vocabulary.used, source.array[k].array[j].vocabulary.used);

        for (f_number_unsigned_t i = 0; i < length; ++i) {

          assert_int_equal(destination.array[k].array[j].content.array[i].start, source.array[k].array[j].content.array[i].start);
          assert_int_equal(destination.array[k].array[j].content.array[i].stop, source.array[k].array[j].content.array[i].stop);

          assert_int_equal(destination.array[k].array[j].delimits.array[i], source.array[k].array[j].delimits.array[i]);

          assert_int_equal(destination.array[k].array[j].variable.array[i].start, source.array[k].array[j].variable.array[i].start);
          assert_int_equal(destination.array[k].array[j].variable.array[i].stop, source.array[k].array[j].variable.array[i].stop);

          assert_int_equal(destination.array[k].array[j].vocabulary.array[i].start, source.array[k].array[j].vocabulary.array[i].start);
          assert_int_equal(destination.array[k].array[j].vocabulary.array[i].stop, source.array[k].array[j].vocabulary.array[i].stop);
        } // for
      } // for
    } // for
  }

  for (f_number_unsigned_t j = 0; j < source.used; ++j) {

    for (f_number_unsigned_t i = 0; i < source.array[j].used; ++i) {

      free((void *) source.array[j].array[i].content.array);
      free((void *) source.array[j].array[i].delimits.array);
      free((void *) source.array[j].array[i].variable.array);
      free((void *) source.array[j].array[i].vocabulary.array);
    } // for

    free((void *) source.array[j].array);
  } // for

  for (f_number_unsigned_t j = 0; j < destination.used; ++j) {

    for (f_number_unsigned_t i = 0; i < destination.array[j].used; ++i) {

      free((void *) destination.array[j].array[i].content.array);
      free((void *) destination.array[j].array[i].delimits.array);
      free((void *) destination.array[j].array[i].variable.array);
      free((void *) destination.array[j].array[i].vocabulary.array);
    } // for

    free((void *) destination.array[j].array);
  } // for

  free((void *) source.array);
  free((void *) destination.array);
}

void test__f_iki_datass_append_all__returns_data_not(void **state) {

  const int length = 5;
  f_iki_datass_t source = f_iki_datass_t_initialize;
  f_iki_datass_t destination = f_iki_datass_t_initialize;

  {
    const f_status_t status = f_memory_arrays_resize(length, sizeof(f_iki_data_t), (void **) &source.array, &source.used, &source.size, &f_iki_datas_resize_callback);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_iki_datass_append_all(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_iki_datass_append_all__parameter_checking(void **state) {

  const f_iki_datass_t data = f_iki_datass_t_initialize;

  {
    const f_status_t status = f_iki_datass_append_all(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
