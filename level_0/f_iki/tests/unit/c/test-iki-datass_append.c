#include "test-iki.h"
#include "test-iki-datass_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_iki_datass_append__works(void **state) {

  const int length = 5;
  const int length_outer = 2;
  f_iki_datas_t source = f_iki_datas_t_initialize;
  f_iki_datass_t destination = f_iki_datass_t_initialize;

  {
    f_status_t status = f_memory_array_resize(length_outer, sizeof(f_iki_data_t), (void **) &source.array, &source.used, &source.size);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.size, length_outer);

    f_number_unsigned_t i = 1;

    for (f_number_unsigned_t j = 0; j < length_outer; ++j) {

      status = f_string_ranges_resize(length, &source.array[j].content);

      assert_int_equal(status, F_okay);
      assert_int_equal(source.array[j].content.size, length);

      status = f_memory_array_resize(length, sizeof(f_number_unsigned_t), (void **) &source.array[j].delimits.array, &source.array[j].delimits.used, &source.array[j].delimits.size);

      assert_int_equal(status, F_okay);
      assert_int_equal(source.array[j].delimits.size, length);

      status = f_string_ranges_resize(length, &source.array[j].variable);

      assert_int_equal(status, F_okay);
      assert_int_equal(source.array[j].variable.size, length);

      status = f_string_ranges_resize(length, &source.array[j].vocabulary);

      assert_int_equal(status, F_okay);
      assert_int_equal(source.array[j].vocabulary.size, length);

      for (; source.array[j].content.used < length; ++i) {

        source.array[j].content.array[source.array[j].content.used].start = i - 1;
        source.array[j].content.array[source.array[j].content.used++].stop = i;
      } // for

      for (; source.array[j].delimits.used < length; ++i) {

        source.array[j].delimits.array[source.array[j].delimits.used++] = i;
      } // for

      for (; source.array[j].variable.used < length; ++i) {

        source.array[j].variable.array[source.array[j].variable.used].start = i - 1;
        source.array[j].variable.array[source.array[j].variable.used++].stop = i;
      } // for

      for (; source.array[j].vocabulary.used < length; ++i) {

        source.array[j].vocabulary.array[source.array[j].vocabulary.used].start = i - 1;
        source.array[j].vocabulary.array[source.array[j].vocabulary.used++].stop = i;
      } // for
    } // for

    source.used = length_outer;
  }

  {
    const f_status_t status = f_iki_datass_append(source, &destination);

    assert_int_equal(status, F_okay);
    assert_int_equal(destination.used, 1);
    assert_int_equal(destination.array[0].used, source.used);

    for (f_number_unsigned_t j = 0; j < length_outer; ++j) {

      assert_int_equal(destination.array[0].array[j].content.used, source.array[j].content.used);
      assert_int_equal(destination.array[0].array[j].delimits.used, source.array[j].delimits.used);
      assert_int_equal(destination.array[0].array[j].variable.used, source.array[j].variable.used);
      assert_int_equal(destination.array[0].array[j].vocabulary.used, source.array[j].vocabulary.used);

      for (f_number_unsigned_t i = 0; i < length; ++i) {

        assert_int_equal(destination.array[0].array[j].content.array[i].start, source.array[j].content.array[i].start);
        assert_int_equal(destination.array[0].array[j].content.array[i].stop, source.array[j].content.array[i].stop);

        assert_int_equal(destination.array[0].array[j].delimits.array[i], source.array[j].delimits.array[i]);

        assert_int_equal(destination.array[0].array[j].variable.array[i].start, source.array[j].variable.array[i].start);
        assert_int_equal(destination.array[0].array[j].variable.array[i].stop, source.array[j].variable.array[i].stop);

        assert_int_equal(destination.array[0].array[j].vocabulary.array[i].start, source.array[j].vocabulary.array[i].start);
        assert_int_equal(destination.array[0].array[j].vocabulary.array[i].stop, source.array[j].vocabulary.array[i].stop);
      } // for
    } // for
  }

  for (f_number_unsigned_t i = 0; i < source.used; ++i) {

    free((void *) source.array[i].content.array);
    free((void *) source.array[i].delimits.array);
    free((void *) source.array[i].variable.array);
    free((void *) source.array[i].vocabulary.array);
  } // for

  for (f_number_unsigned_t j = 0; j < length_outer; ++j) {

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

void test__f_iki_datass_append__returns_data_not(void **state) {

  const int length = 5;
  f_iki_datas_t source = f_iki_datass_t_initialize;
  f_iki_datass_t destination = f_iki_datass_t_initialize;

  {
    f_status_t status = f_memory_array_resize(length, sizeof(f_iki_data_t), (void **) &source.array, &source.used, &source.size);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_iki_datass_append(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_iki_datass_append__parameter_checking(void **state) {

  f_iki_datas_t data = f_iki_datas_t_initialize;

  {
    const f_status_t status = f_iki_datass_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
