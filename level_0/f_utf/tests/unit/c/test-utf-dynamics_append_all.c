#include "test-utf.h"
#include "test-utf-dynamics_append_all.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_string_dynamics_append_all__works(void **state) {

  const int length_inner = 2;
  f_utf_string_dynamics_t source = f_utf_string_dynamics_t_initialize;
  f_utf_string_dynamics_t destination = f_utf_string_dynamics_t_initialize;

  const f_utf_string_static_t test_sources[] = {
    macro_f_utf_string_static_t_initialize_1((f_utf_string_t) "t\0\0\0e\0\0\0\0\0\0\0s\0\0\0t\0\0\01\0\0\0", 0, 6),
    macro_f_utf_string_static_t_initialize_1((f_utf_string_t) "t\0\0\0e\0\0\0s\0\0\0t\0\0\02\0\0\0", 0, 5),
  };

  {
    f_status_t status = f_memory_array_increase_by(length_inner, sizeof(f_utf_string_dynamic_t), (void **) &source.array, &source.used, &source.size);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.size, length_inner);

    for (; source.used < length_inner; ++source.used) {

      status = f_utf_string_dynamic_append(test_sources[source.used], &source.array[source.used]);

      assert_int_equal(status, F_okay);
      assert_int_equal(source.array[source.used].used, test_sources[source.used].used);

      for (f_number_unsigned_t i = 0; i < source.array[source.used].used; ++i) {
        assert_int_equal(source.array[source.used].string[i], test_sources[source.used].string[i]);
      } // for
    } // for
  }

  {
    const f_status_t status = f_utf_string_dynamics_append_all(source, &destination);

    assert_int_equal(status, F_okay);
    assert_int_equal(destination.used, source.used);
    assert_int_equal(destination.size, source.used);

    for (f_number_unsigned_t i = 0; i < source.used; ++i) {

      assert_int_equal(destination.array[i].used, source.array[i].used);

      for (f_number_unsigned_t j = 0; j < destination.array[i].used; ++j) {
        assert_int_equal(destination.array[i].string[j], source.array[i].string[j]);
      } // for
    } // for
  }

  for (f_number_unsigned_t i = 0; i < source.used; ++i) {
    free((void *) source.array[i].string);
  } // for

  for (f_number_unsigned_t i = 0; i < destination.used; ++i) {
    free((void *) destination.array[i].string);
  } // for

  free((void *) source.array);
  free((void *) destination.array);
}

void test__f_utf_string_dynamics_append_all__returns_data_not(void **state) {

  const int length = 5;
  f_utf_string_dynamics_t source = f_utf_string_dynamics_t_initialize;
  f_utf_string_dynamics_t destination = f_utf_string_dynamics_t_initialize;

  {
    const f_status_t status = f_memory_array_increase_by(length, sizeof(f_utf_string_dynamic_t), (void **) &source.array, &source.used, &source.size);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_utf_string_dynamics_append_all(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_utf_string_dynamics_append_all__parameter_checking(void **state) {

  const f_utf_string_dynamics_t data = f_utf_string_dynamics_t_initialize;

  {
    const f_status_t status = f_utf_string_dynamics_append_all(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
