#include "test-type_array.h"
#include "test-type_array-polls_append_all.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_polls_append_all__parameter_checking(void **poll) {

  const f_polls_t data = f_polls_t_initialize;

  {
    const f_status_t status = f_polls_append_all(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_type_array_polls_append_all__returns_data_not(void **poll) {

  const int length = 5;
  f_polls_t source = f_polls_t_initialize;
  f_polls_t destination = f_polls_t_initialize;

  {
    const f_status_t status = f_polls_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_polls_append_all(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_type_array_polls_append_all__works(void **poll) {

  const int length = 5;
  f_polls_t source = f_polls_t_initialize;
  f_polls_t destination = f_polls_t_initialize;

  const f_poll_t poll_0 = { 0, 1, 2 };
  const f_poll_t poll_1 = { 0, 2, 3 };

  {
    const f_status_t status = f_polls_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  memcpy(&source.array[source.used++], (void *) &poll_0, sizeof(f_poll_t));
  memcpy(&source.array[source.used++], (void *) &poll_1, sizeof(f_poll_t));

  {
    const f_status_t status = f_polls_append_all(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, source.used);
    assert_int_equal(destination.size, source.used);

    for (f_number_unsigned_t i = 0; i < source.used; ++i) {

      assert_int_equal(destination.array[i].fd, source.array[i].fd);
      assert_int_equal(destination.array[i].events, source.array[i].events);
      assert_int_equal(destination.array[i].revents, source.array[i].revents);
    } // for
  }

  free((void *) source.array);
  free((void *) destination.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
