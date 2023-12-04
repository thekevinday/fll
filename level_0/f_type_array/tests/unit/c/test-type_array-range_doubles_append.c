#include "test-type_array.h"
#include "test-type_array-range_doubles_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_range_doubles_append__works(void **state) {

  const f_range_double_t source = macro_f_range_double_t_initialize_1(1, 2, 3, 4);
  f_range_doubles_t destination = f_range_doubles_t_initialize;

  {
    const f_status_t status = f_range_doubles_append(source, &destination);

    assert_int_equal(status, F_okay);
    assert_int_equal(destination.used, 1);
    assert_int_equal(destination.array[0].start_1, source.start_1);
    assert_int_equal(destination.array[0].start_2, source.start_2);
    assert_int_equal(destination.array[0].stop_1, source.stop_1);
    assert_int_equal(destination.array[0].stop_2, source.stop_2);
  }

  free((void *) destination.array);
}

void test__f_type_array_range_doubles_append__parameter_checking(void **state) {

  const f_range_double_t data = f_range_double_t_initialize;

  {
    const f_status_t status = f_range_doubles_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
