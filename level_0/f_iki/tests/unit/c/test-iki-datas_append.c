#include "test-iki.h"
#include "test-iki-datas_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_iki_datas_append__works(void **state) {

  const f_number_unsigned_t length = 5;
  f_iki_data_t source = f_iki_data_t_initialize;
  f_iki_datas_t destination = f_iki_datas_t_initialize;

  {
    f_number_unsigned_t i = 1;

    f_status_t status = f_memory_array_resize(length, sizeof(f_string_range_t), (void **) &source.content.array, &source.content.used, &source.content.size);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.content.size, length);

    status = f_memory_array_resize(length, sizeof(f_number_unsigned_t), (void **) &source.delimits.array, &source.delimits.used, &source.delimits.size);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.delimits.size, length);

    status = f_memory_array_resize(length, sizeof(f_string_range_t), (void **) &source.variable.array, &source.variable.used, &source.variable.size);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.variable.size, length);

    status = f_memory_array_resize(length, sizeof(f_string_range_t), (void **) &source.vocabulary.array, &source.vocabulary.used, &source.vocabulary.size);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.vocabulary.size, length);

    for (; source.content.used < length; ++i) {

      source.content.array[source.content.used].start = i - 1;
      source.content.array[source.content.used++].stop = i;
    } // for

    for (; source.delimits.used < length; ++i) {
      source.delimits.array[source.delimits.used++] = i;
    } // for

    for (; source.variable.used < length; ++i) {

      source.variable.array[source.variable.used].start = i - 1;
      source.variable.array[source.variable.used++].stop = i;
    } // for

    for (; source.vocabulary.used < length; ++i) {

      source.vocabulary.array[source.vocabulary.used].start = i - 1;
      source.vocabulary.array[source.vocabulary.used++].stop = i;
    } // for
  }

  {
    const f_status_t status = f_iki_datas_append(source, &destination);

    assert_int_equal(status, F_okay);
    assert_int_equal(destination.used, 1);
    assert_int_equal(destination.array[0].content.used, source.content.used);
    assert_int_equal(destination.array[0].delimits.used, source.delimits.used);
    assert_int_equal(destination.array[0].variable.used, source.variable.used);
    assert_int_equal(destination.array[0].vocabulary.used, source.vocabulary.used);

    for (f_number_unsigned_t i = 0; i < length; ++i) {

      assert_int_equal(destination.array[0].content.array[i].start, source.content.array[i].start);
      assert_int_equal(destination.array[0].content.array[i].stop, source.content.array[i].stop);

      assert_int_equal(destination.array[0].delimits.array[i], source.delimits.array[i]);

      assert_int_equal(destination.array[0].variable.array[i].start, source.variable.array[i].start);
      assert_int_equal(destination.array[0].variable.array[i].stop, source.variable.array[i].stop);

      assert_int_equal(destination.array[0].vocabulary.array[i].start, source.vocabulary.array[i].start);
      assert_int_equal(destination.array[0].vocabulary.array[i].stop, source.vocabulary.array[i].stop);
    } // for
  }

  free((void *) source.content.array);
  free((void *) source.delimits.array);
  free((void *) source.variable.array);
  free((void *) source.vocabulary.array);

  free((void *) destination.array[0].content.array);
  free((void *) destination.array[0].delimits.array);
  free((void *) destination.array[0].variable.array);
  free((void *) destination.array[0].vocabulary.array);

  free((void *) destination.array);
}

void test__f_iki_datas_append__parameter_checking(void **state) {

  const f_iki_data_t data = f_iki_data_t_initialize;

  {
    const f_status_t status = f_iki_datas_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
