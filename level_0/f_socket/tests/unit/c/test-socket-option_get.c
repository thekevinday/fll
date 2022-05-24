#include "test-socket.h"
#include "test-socket-option_get.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_socket_option_get__fails(void **state) {

  f_socket_t socket = f_socket_t_initialize;
  int value = 0;
  socklen_t length = 0;

  int errnos[] = {
    EBADF,
    EFAULT,
    EINVAL,
    ENOTSOCK,
    ENOPROTOOPT,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_file_descriptor,
    F_buffer,
    F_value,
    F_socket_not,
    F_option_not,
    F_failure,
  };

  for (uint8_t i = 0; i < 6; ++i) {

    will_return(__wrap_getsockopt, true);
    will_return(__wrap_getsockopt, errnos[i]);

    const f_status_t status = f_socket_option_get(&socket, 0, 0, (void *) &value, &length);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_socket_option_get__parameter_checking(void **state) {

  f_socket_t socket = f_socket_t_initialize;
  int value = 0;
  socklen_t length = 0;

  {
    const f_status_t status = f_socket_option_get(0, 0, 0, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_socket_option_get(&socket, 0, 0, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_socket_option_get(&socket, 0, 0, (void *) &value, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_socket_option_get(&socket, 0, 0, 0, &length);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_socket_option_get(0, 0, 0, (void *) &value, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_socket_option_get(0, 0, 0, (void *) &value, &length);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_socket_option_get(0, 0, 0, 0, &length);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_socket_option_get__works(void **state) {

  f_socket_t socket = f_socket_t_initialize;
  int value = 0;
  socklen_t length = 0;

  {
    will_return(__wrap_getsockopt, false);

    const f_status_t status = f_socket_option_get(&socket, 0, 0, (void *) &value, &length);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
