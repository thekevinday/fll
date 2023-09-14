#include "test-socket.h"
#include "test-socket-connect.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_socket_connect__fails(void **state) {

  f_socket_t socket = f_socket_t_initialize;

  int errnos[] = {
    EACCES,
    EADDRINUSE,
    EADDRNOTAVAIL,
    EAFNOSUPPORT,
    EAGAIN,
    EALREADY,
    EBADF,
    ECONNREFUSED,
    EINPROGRESS,
    EINTR,
    EINVAL,
    EISCONN,
    ENETUNREACH,
    ENOTSOCK,
    EPERM,
    EPROTONOSUPPORT,
    ETIMEDOUT,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_access_denied,
    F_busy_address,
    F_available_not_address,
    F_domain_not,
    F_block,
    F_complete_not,
    F_file_descriptor,
    F_connect_refuse,
    F_progress,
    F_interrupt,
    F_parameter,
    F_connect,
    F_network_reach_not,
    F_socket_not,
    F_prohibited,
    F_protocol_not,
    F_time_out,
    F_failure,
  };

  for (uint8_t i = 0; i < 17; ++i) {

    will_return(__wrap_connect, true);
    will_return(__wrap_connect, errnos[i]);

    const f_status_t status = f_socket_connect(socket);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_socket_connect__returns_file_descriptor(void **state) {

  {
    f_socket_t socket = f_socket_t_initialize;
    socket.id = 1;

    const f_status_t status = f_socket_connect(socket);

    assert_int_equal(status, F_file_descriptor);
  }
}

void test__f_socket_connect__works(void **state) {

  f_socket_t socket = f_socket_t_initialize;

  {
    will_return(__wrap_connect, false);

    const f_status_t status = f_socket_connect(socket);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
