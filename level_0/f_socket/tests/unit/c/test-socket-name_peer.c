#include "test-socket.h"
#include "test-socket-listen.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_socket_name_peer__fails(void **state) {

  f_socket_t socket = f_socket_t_initialize;

  int errnos[] = {
    EBADF,
    EFAULT,
    EINVAL,
    ENOBUFS,
    ENOTCONN,
    ENOTSOCK,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_file_descriptor,
    F_buffer,
    F_parameter,
    F_buffer_not,
    F_connect_not,
    F_socket_not,
    F_failure,
  };

  for (uint8_t i = 0; i < 7; ++i) {

    will_return(__wrap_getpeername, true);
    will_return(__wrap_getpeername, errnos[i]);

    const f_status_t status = f_socket_name_peer(&socket);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_socket_name_peer__parameter_checking(void **state) {

  {
    const f_status_t status = f_socket_name_peer(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_socket_name_peer__works(void **state) {

  f_socket_t socket = f_socket_t_initialize;

  {
    will_return(__wrap_getpeername, false);

    const f_status_t status = f_socket_name_peer(&socket);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
