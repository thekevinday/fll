#include "test-type_array.h"
#include "test-type_array-number_unsignedss_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_number_unsignedss_append__parameter_checking(void **state) {

  const f_number_unsigneds_t data = f_number_unsigneds_t_initialize;

  {
    const f_status_t status = f_number_unsignedss_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_type_array_number_unsignedss_append__returns_data_not(void **state) {

  const int length = 5;
  f_number_unsigneds_t source = f_number_unsigneds_t_initialize;
  f_number_unsignedss_t destination = f_number_unsignedss_t_initialize;

  {
    const f_status_t status = f_number_unsigneds_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_number_unsignedss_append(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_type_array_number_unsignedss_append__works(void **state) {

  const int length = 5;
  f_number_unsigneds_t source = f_number_unsigneds_t_initialize;
  f_number_unsignedss_t destination = f_number_unsignedss_t_initialize;

  {
    const f_status_t status = f_number_unsigneds_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  for (; source.used < length; ++source.used) {
    source.array[source.used] = source.used + 1;
  } // for

  {
    const f_status_t status = f_number_unsignedss_append(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, 1);
    assert_int_equal(destination.array[0].used, source.used);
    assert_int_equal(destination.array[0].size, source.used);

    for (f_number_unsigned_t i = 0; i < destination.array[0].used; ++i) {
      assert_int_equal(destination.array[0].array[i], i + 1);
    } // for
  }

  for (f_number_unsigned_t i = 0; i < destination.used; ++i) {
    free((void *) destination.array[i].array);
  } // for

  free((void *) source.array);
  free((void *) destination.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
