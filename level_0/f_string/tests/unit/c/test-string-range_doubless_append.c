#include "test-string.h"
#include "test-string-range_doubless_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_string_range_doubless_append__works(void **state) {

  const int length_sources = 2;

  f_string_range_double_t sources_array[] = {
    macro_f_string_range_double_t_initialize_1(1, 2),
    macro_f_string_range_double_t_initialize_1(3, 4),
  };

  const f_string_range_doubles_t source = macro_f_string_range_doubles_t_initialize_1(sources_array, 0, length_sources);
  f_string_range_doubless_t destination = f_string_range_doubless_t_initialize;

  {
    const f_status_t status = f_string_range_doubless_append(source, &destination);

    assert_int_equal(status, F_okay);
    assert_int_equal(destination.array[0].used, length_sources);

    for (f_number_unsigned_t i = 0; i < length_sources; ++i) {

      assert_int_equal(destination.array[0].array[i].start, sources_array[i].start);
      assert_int_equal(destination.array[0].array[i].stop, sources_array[i].stop);
    } // for
  }

  free((void *) destination.array[0].array);
  free((void *) destination.array);
}

void test__f_string_range_doubless_append__returns_data_not(void **state) {

  const int length = 5;
  f_string_range_doubles_t source = f_string_range_doubless_t_initialize;
  f_string_range_doubless_t destination = f_string_range_doubless_t_initialize;

  {
    const f_status_t status = f_memory_arrays_resize(length, sizeof(f_string_range_doubles_t), (void **) &source.array, &source.used, &source.size, &f_string_range_doubless_delete_callback);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_string_range_doubless_append(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_string_range_doubless_append__parameter_checking(void **state) {

  f_string_range_doubles_t data = f_string_range_doubles_t_initialize;

  {
    const f_status_t status = f_string_range_doubless_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
