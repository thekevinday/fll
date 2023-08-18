#include "test-string.h"
#include "test-string-dynamicss_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_string_dynamicss_append__works(void **state) {

  const int length_inner = 2;
  f_string_dynamics_t source = f_string_dynamics_t_initialize;
  f_string_dynamicss_t destination = f_string_dynamicss_t_initialize;

  const f_string_static_t test_names[] = {
    macro_f_string_static_t_initialize_1("test1", 0, 5),
    macro_f_string_static_t_initialize_1("test2", 0, 5),
  };

  {
    f_status_t status = f_string_dynamics_resize(length_inner, &source);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.size, length_inner);

    for (; source.used < length_inner; ++source.used) {

      status = f_string_dynamic_append(test_names[source.used], &source.array[source.used]);

      assert_int_equal(status, F_okay);
      assert_string_equal(source.array[source.used].string, test_names[source.used].string);
      assert_int_equal(source.array[source.used].used, test_names[source.used].used);
    } // for
  }

  {
    const f_status_t status = f_string_dynamicss_append(source, &destination);

    assert_int_equal(status, F_okay);
    assert_int_equal(destination.array[0].used, length_inner);

    for (f_number_unsigned_t i = 0; i < length_inner; ++i) {

      assert_int_equal(destination.array[0].array[i].used, test_names[i].used);
      assert_string_equal(destination.array[0].array[i].string, test_names[i].string);
    } // for
  }

  for (f_number_unsigned_t i = 0; i < source.used; ++i) {
    free((void *) source.array[i].string);
  } // for


  for (f_number_unsigned_t i = 0; i < destination.array[0].used; ++i) {
    free((void *) destination.array[0].array[i].string);
  } // for

  free((void *) destination.array[0].array);

  free((void *) source.array);
  free((void *) destination.array);
}

void test__f_string_dynamicss_append__returns_data_not(void **state) {

  const int length = 5;
  f_string_dynamics_t source = f_string_dynamicss_t_initialize;
  f_string_dynamicss_t destination = f_string_dynamicss_t_initialize;

  {
    const f_status_t status = f_string_dynamics_resize(length, &source);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_string_dynamicss_append(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_string_dynamicss_append__parameter_checking(void **state) {

  f_string_dynamics_t data = f_string_dynamics_t_initialize;

  {
    const f_status_t status = f_string_dynamicss_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
