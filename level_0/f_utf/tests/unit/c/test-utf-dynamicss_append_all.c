#include "test-utf.h"
#include "test-utf-dynamicss_append_all.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_string_dynamicss_append_all__works(void **state) {

  const int length_inner = 2;
  const int length_outer = 2;
  f_utf_string_dynamicss_t source = f_utf_string_dynamicss_t_initialize;
  f_utf_string_dynamicss_t destination = f_utf_string_dynamicss_t_initialize;

  const f_utf_string_static_t test_names[] = {
    macro_f_utf_string_static_t_initialize_1((f_utf_string_t) "t\0\0\0e\0\0\0s\0\0\0t\0\0\01\0\0\0", 0, 5),
    macro_f_utf_string_static_t_initialize_1((f_utf_string_t) "t\0\0\0e\0\0\0s\0\0\0t\0\0\02\0\0\0", 0, 5),
  };

  {
    f_status_t status = f_memory_array_increase_by(length_outer, sizeof(f_utf_string_dynamics_t), (void **) &source.array, &source.used, &source.size);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length_outer);

    f_number_unsigned_t i = 0;

    for (; source.used < length_outer; ++source.used) {

      status = f_memory_array_increase_by(length_inner, sizeof(f_utf_string_dynamic_t), (void **) &source.array[source.used].array, &source.array[source.used].used, &source.array[source.used].size);

      assert_int_equal(status, F_okay);
      assert_int_equal(source.array[source.used].used, 0);
      assert_int_equal(source.array[source.used].size, length_inner);

      for (i = 0; i < length_inner; ++i) {

        status = f_utf_string_dynamic_append(test_names[i], &source.array[source.used].array[i]);

        assert_int_equal(status, F_okay);
        assert_int_equal(source.array[source.used].array[i].used, test_names[i].used);

        for (f_number_unsigned_t j = 0; j < source.array[source.used].array[i].used; ++j) {
          assert_int_equal(source.array[source.used].array[i].string[j], test_names[i].string[j]);
        } // for
      } // for

      source.array[source.used].used = length_inner;
    } // for
  }

  {
    const f_status_t status = f_utf_string_dynamicss_append_all(source, &destination);

    assert_int_equal(status, F_okay);
    assert_int_equal(destination.used, source.used);

    for (f_number_unsigned_t j = 0; j < length_outer; ++j) {

      for (f_number_unsigned_t i = 0; i < length_inner; ++i) {

        assert_int_equal(destination.array[j].array[i].used, test_names[i].used);

        for (f_number_unsigned_t k = 0; k < destination.array[j].array[i].used; ++k) {
          assert_int_equal(destination.array[j].array[i].string[k], test_names[i].string[k]);
        } // for
      } // for
    } // for
  }

  for (f_number_unsigned_t j = 0; j < source.used; ++j) {

    for (f_number_unsigned_t i = 0; i < source.array[j].used; ++i) {
      free((void *) source.array[j].array[i].string);
    } // for

    free((void *) source.array[j].array);
  } // for

  for (f_number_unsigned_t j = 0; j < destination.used; ++j) {

    for (f_number_unsigned_t i = 0; i < destination.array[j].used; ++i) {
      free((void *) destination.array[j].array[i].string);
    } // for

    free((void *) destination.array[j].array);
  } // for

  free((void *) source.array);
  free((void *) destination.array);
}

void test__f_utf_string_dynamicss_append_all__returns_data_not(void **state) {

  const int length = 5;
  f_utf_string_dynamicss_t source = f_utf_string_dynamicss_t_initialize;
  f_utf_string_dynamicss_t destination = f_utf_string_dynamicss_t_initialize;

  {
    const f_status_t status = f_memory_array_increase_by(length, sizeof(f_utf_string_dynamics_t), (void **) &source.array, &source.used, &source.size);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_utf_string_dynamicss_append_all(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_utf_string_dynamicss_append_all__parameter_checking(void **state) {

  const f_utf_string_dynamicss_t data = f_utf_string_dynamicss_t_initialize;

  {
    const f_status_t status = f_utf_string_dynamicss_append_all(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
