#include "test-string.h"
#include "test-string-quantityss_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_string_quantityss_append__works(void **state) {

  const int length_sources = 2;

  f_string_quantity_t sources_array[] = {
    macro_f_string_quantity_t_initialize(1, 2),
    macro_f_string_quantity_t_initialize(3, 4),
  };

  const f_string_quantitys_t source = macro_f_string_quantitys_t_initialize(sources_array, 0, length_sources);
  f_string_quantityss_t destination = f_string_quantityss_t_initialize;

  {
    const f_status_t status = f_string_quantityss_append(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.array[0].used, length_sources);

    for (f_array_length_t i = 0; i < length_sources; ++i) {

      assert_int_equal(destination.array[0].array[i].start, sources_array[i].start);
      assert_int_equal(destination.array[0].array[i].total, sources_array[i].total);
    } // for
  }

  free((void *) destination.array[0].array);
  free((void *) destination.array);
}

void test__f_string_quantityss_append__returns_data_not(void **state) {

  const int length = 5;
  f_string_quantitys_t source = f_string_quantityss_t_initialize;
  f_string_quantityss_t destination = f_string_quantityss_t_initialize;

  {
    const f_status_t status = f_string_quantitys_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_string_quantityss_append(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_string_quantityss_append__parameter_checking(void **state) {

  f_string_quantitys_t data = f_string_quantitys_t_initialize;

  {
    const f_status_t status = f_string_quantityss_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
