#include "test-socket.h"
#include "test-socket-write_message.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_socket_write_message__fails(void **state) {

  f_socket_t socket = f_socket_t_initialize;
  struct msghdr header;
  size_t length = 0;

  memset(&header, 0, sizeof(struct msghdr));

  int errnos[] = {
    EACCES,
    EAGAIN,
    EALREADY,
    EBADF,
    ECONNREFUSED,
    ECONNRESET,
    EDESTADDRREQ,
    EFAULT,
    EINTR,
    EINVAL,
    EISCONN,
    EMSGSIZE,
    ENOBUFS,
    ENOMEM,
    ENOTCONN,
    ENOTSOCK,
    EOPNOTSUPP,
    EPERM,
    EPIPE,
    ETIMEDOUT,
    EWOULDBLOCK,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_access_denied,
    F_block,
    F_complete_not,
    F_file_descriptor,
    F_connect_refuse,
    F_connect_reset,
    F_address_not,
    F_buffer,
    F_interrupt,
    F_parameter,
    F_connect,
    F_size,
    F_buffer_not,
    F_memory_not,
    F_connect_not,
    F_socket_not,
    F_option_not,
    F_prohibited,
    F_pipe,
    F_time_out,
    F_block,
    F_failure,
  };

  for (uint8_t i = 0; i < 22; ++i) {

    will_return(__wrap_sendmsg, true);
    will_return(__wrap_sendmsg, errnos[i]);

    const f_status_t status = f_socket_write_message(&socket, 0, &header, &length);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_socket_write_message__parameter_checking(void **state) {

  f_socket_t socket = f_socket_t_initialize;
  struct msghdr header;

  memset(&header, 0, sizeof(struct msghdr));

  {
    const f_status_t status = f_socket_write_message(0, 0, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_socket_write_message(&socket, 0, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_socket_write_message(0, 0, &header, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_socket_write_message__returns_data_not(void **state) {

  struct msghdr header;

  memset(&header, 0, sizeof(struct msghdr));

  {
    f_socket_t socket = f_socket_t_initialize;
    socket.size_write = 0;

    const f_status_t status = f_socket_write_message(&socket, 0, &header, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    size_t length = 0;
    f_socket_t socket = f_socket_t_initialize;
    socket.size_write = 0;

    const f_status_t status = f_socket_write_message(&socket, 0, &header, &length);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_socket_write_message__works(void **state) {

  f_socket_t socket = f_socket_t_initialize;
  struct msghdr header;
  size_t length = 0;

  memset(&header, 0, sizeof(struct msghdr));

  {
    will_return(__wrap_sendmsg, false);
    will_return(__wrap_sendmsg, 1);

    const f_status_t status = f_socket_write_message(&socket, 0, &header, &length);

    assert_int_equal(status, F_okay);
    assert_int_equal(length, 1);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
