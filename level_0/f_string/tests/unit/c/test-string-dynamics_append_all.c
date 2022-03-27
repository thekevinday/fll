#include "test-string.h"
#include "test-string-dynamics_append_all.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_string_dynamics_append_all__works(void **state) {

  const int length_inner = 2;
  f_string_dynamics_t source = f_string_dynamics_t_initialize;
  f_string_dynamics_t destination = f_string_dynamics_t_initialize;

  const f_string_static_t test_sources[] = {
    macro_f_string_static_t_initialize("te\0st1", 0, 6),
    macro_f_string_static_t_initialize("test2", 0, 5),
  };

  {
    f_status_t status = f_string_dynamics_resize(length_inner, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.size, length_inner);

    for (; source.used < length_inner; ++source.used) {

      status = f_string_dynamic_append(test_sources[source.used], &source.array[source.used]);

      assert_int_equal(status, F_none);
      assert_int_equal(source.array[source.used].used, test_sources[source.used].used);

      assert_string_equal(source.array[source.used].string, test_sources[source.used].string);
      assert_string_equal(source.array[source.used].string + 3, test_sources[source.used].string + 3);
    } // for
  }

  {
    const f_status_t status = f_string_dynamics_append_all(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, source.used);
    assert_int_equal(destination.size, source.used);

    for (f_array_length_t i = 0; i < length_inner; ++i) {

      assert_int_equal(destination.array[i].used, source.array[i].used);

      assert_string_equal(destination.array[i].string, source.array[i].string);
    } // for
  }

  for (f_array_length_t i = 0; i < source.used; ++i) {
    free((void *) source.array[i].string);
  } // for

  for (f_array_length_t i = 0; i < destination.used; ++i) {
    free((void *) destination.array[i].string);
  } // for

  free((void *) source.array);
  free((void *) destination.array);
}

void test__f_string_dynamics_append_all__returns_data_not(void **state) {

  const int length = 5;
  f_string_dynamics_t source = f_string_dynamics_t_initialize;
  f_string_dynamics_t destination = f_string_dynamics_t_initialize;

  {
    const f_status_t status = f_string_dynamics_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_string_dynamics_append_all(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_string_dynamics_append_all__parameter_checking(void **state) {

  const f_string_dynamics_t data = f_string_dynamics_t_initialize;

  {
    const f_status_t status = f_string_dynamics_append_all(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
