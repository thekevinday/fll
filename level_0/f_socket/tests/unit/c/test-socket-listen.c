#include "test-socket.h"
#include "test-socket-listen.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_socket_listen__fails(void **state) {

  f_socket_t socket = f_socket_t_initialize;

  int errnos[] = {
    EADDRINUSE,
    EBADF,
    ENOTSOCK,
    EOPNOTSUPP,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_busy_address,
    F_file_descriptor,
    F_socket_not,
    F_support_not,
    F_failure,
  };

  for (uint8_t i = 0; i < 5; ++i) {

    will_return(__wrap_listen, true);
    will_return(__wrap_listen, errnos[i]);

    const f_status_t status = f_socket_listen(&socket, 0);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_socket_listen__parameter_checking(void **state) {

  {
    const f_status_t status = f_socket_listen(0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_socket_listen__works(void **state) {

  f_socket_t socket = f_socket_t_initialize;

  {
    will_return(__wrap_listen, false);

    const f_status_t status = f_socket_listen(&socket, 0);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
