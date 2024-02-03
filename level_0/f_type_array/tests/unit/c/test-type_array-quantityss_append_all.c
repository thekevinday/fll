#include "test-type_array.h"
#include "test-type_array-quantityss_append_all.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_quantityss_append_all__works(void **state) {

  const int length_sources = 2;
  const int length_sources_set = 2;

  f_quantity_t sources_array1[] = {
    macro_f_quantity_t_initialize_1(1, 2),
    macro_f_quantity_t_initialize_1(3, 4),
  };

  f_quantity_t sources_array2[] = {
    macro_f_quantity_t_initialize_1(5, 6),
    macro_f_quantity_t_initialize_1(7, 8),
  };

  f_quantitys_t sources_set_array[] = {
    macro_f_quantitys_t_initialize_1(sources_array1, 0, length_sources),
    macro_f_quantitys_t_initialize_1(sources_array2, 0, length_sources),
  };

  const f_quantityss_t source = macro_f_quantityss_t_initialize_1(sources_set_array, 0, length_sources_set);
  f_quantityss_t destination = f_quantityss_t_initialize;

  {
    const f_status_t status = f_quantityss_append_all(source, &destination);

    assert_int_equal(status, F_okay);
    assert_int_equal(destination.used, source.used);

    for (f_number_unsigned_t j = 0; j < length_sources_set; ++j) {

      for (f_number_unsigned_t i = 0; i < length_sources; ++i) {

        assert_int_equal(destination.array[j].array[i].start, sources_set_array[j].array[i].start);
        assert_int_equal(destination.array[j].array[i].total, sources_set_array[j].array[i].total);
      } // for
    } // for
  }

  for (f_number_unsigned_t i = 0; i < destination.used; ++i) {
    free((void *) destination.array[i].array);
  } // for

  free((void *) destination.array);
}

void test__f_type_array_quantityss_append_all__returns_data_not(void **state) {

  const int length = 5;
  f_quantityss_t source = f_quantityss_t_initialize;
  f_quantityss_t destination = f_quantityss_t_initialize;

  {
    const f_status_t status = f_memory_arrays_resize(length, sizeof(f_quantitys_t), (void **) &source.array, &source.used, &source.size, &f_quantityss_delete_callback);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_quantityss_append_all(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_type_array_quantityss_append_all__parameter_checking(void **state) {

  const f_quantityss_t data = f_quantityss_t_initialize;

  {
    const f_status_t status = f_quantityss_append_all(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
