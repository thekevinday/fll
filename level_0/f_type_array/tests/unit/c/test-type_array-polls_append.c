#include "test-type_array.h"
#include "test-type_array-polls_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_polls_append__parameter_checking(void **poll) {

  const f_poll_t data = f_poll_t_initialize;

  {
    const f_status_t status = f_polls_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_type_array_polls_append__works(void **poll) {

  const f_poll_t source = macro_f_poll_t_initialize_1(0, 1, 2);
  f_polls_t destination = f_polls_t_initialize;

  {
    const f_status_t status = f_polls_append(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, 1);
    assert_int_equal(destination.array[0].fd, source.fd);
    assert_int_equal(destination.array[0].events, source.events);
    assert_int_equal(destination.array[0].revents, source.revents);
  }

  free((void *) destination.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
