#include "test-socket.h"
#include "test-socket-accept.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_socket_accept__fails(void **state) {

  f_socket_t socket = f_socket_t_initialize;

  int errnos[] = {
    EACCES,
    EAGAIN,
    EBADF,
    EFAULT,
    EHOSTDOWN,
    EHOSTUNREACH,
    EINTR,
    EINVAL,
    EMFILE,
    ENETDOWN,
    ENFILE,
    ENETUNREACH,
    ENOBUFS,
    ENOMEM,
    ENONET,
    ENOPROTOOPT,
    ENOTSOCK,
    EOPNOTSUPP,
    EPROTO,
    EPERM,
    ESOCKTNOSUPPORT,
    EPROTONOSUPPORT,
    ETIMEDOUT,
    EWOULDBLOCK,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_access_denied,
    F_block,
    F_file_descriptor,
    F_buffer,
    F_network_client_not,
    F_network_reach_client_not,
    F_interrupt,
    F_parameter,
    F_file_descriptor_max,
    F_network_not,
    F_file_open_max,
    F_network_reach_not,
    F_buffer_not,
    F_memory_not,
    F_network_device_not,
    F_option_not,
    F_socket_not,
    F_stream_not,
    F_protocol,
    F_prohibited,
    F_support_not,
    F_protocol_not,
    F_time_out,
    F_block,
    F_failure,
  };

  for (uint8_t i = 0; i < 25; ++i) {

    will_return(__wrap_accept, true);
    will_return(__wrap_accept, errnos[i]);

    const f_status_t status = f_socket_accept(&socket);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_socket_accept__parameter_checking(void **state) {

  {
    const f_status_t status = f_socket_accept(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_socket_accept__works(void **state) {

  f_socket_t socket = f_socket_t_initialize;

  socket.id = 1;

  {
    const int id = 2;

    will_return(__wrap_accept, false);
    will_return(__wrap_accept, id);

    const f_status_t status = f_socket_accept(&socket);

    assert_int_equal(status, F_none);
    assert_int_equal(socket.id_data, id);
    assert_int_not_equal(socket.id, id);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
