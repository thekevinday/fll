#include "test-type_array.h"
#include "test-type_array-pollss_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_pollss_append__parameter_checking(void **poll) {

  f_polls_t data = f_polls_t_initialize;

  {
    const f_status_t status = f_pollss_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_type_array_pollss_append__returns_data_not(void **poll) {

  const int length = 5;
  f_polls_t source = f_polls_t_initialize;
  f_pollss_t destination = f_pollss_t_initialize;

  {
    const f_status_t status = f_polls_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_pollss_append(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_type_array_pollss_append__works(void **poll) {

  const int length = 5;
  f_polls_t source = f_polls_t_initialize;
  f_pollss_t destination = f_pollss_t_initialize;

  const f_poll_t poll_data = macro_f_poll_t_initialize_1(0, 1, 2);

  {
    const f_status_t status = f_polls_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  while (source.used < length) {
    memcpy(&source.array[source.used++], (void *) &poll_data, sizeof(f_poll_t));
  } // while

  {
    const f_status_t status = f_pollss_append(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, 1);
    assert_int_equal(destination.array[0].used, source.used);
    assert_int_equal(destination.array[0].size, source.used);

    for (f_number_unsigned_t i = 0; i < destination.array[0].used; ++i) {

      assert_int_equal(destination.array[0].array[i].fd, source.array[0].fd);
      assert_int_equal(destination.array[0].array[i].events, source.array[0].events);
      assert_int_equal(destination.array[0].array[i].revents, source.array[0].revents);
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
