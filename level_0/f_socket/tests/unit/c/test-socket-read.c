#include "test-socket.h"
#include "test-socket-read.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_socket_read__fails(void **state) {

  f_socket_t socket = f_socket_t_initialize;
  char * const buffer = "test";
  size_t length = 0;

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

  for (uint8_t i = 0; i < 19; ++i) {

    will_return(__wrap_recvfrom, true);
    will_return(__wrap_recvfrom, errnos[i]);

    const f_status_t status = f_socket_read(&socket, 0, (void *) buffer, &length);

    assert_int_equal(status, F_status_set_error(statuss[i]));
    assert_int_equal(length, 0);
  } // for
}

void test__f_socket_read__parameter_checking(void **state) {

  f_socket_t socket = f_socket_t_initialize;
  char * const buffer = "test";

  {
    const f_status_t status = f_socket_read(0, 0, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_socket_read(&socket, 0, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_socket_read(0, 0, buffer, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_socket_read__works(void **state) {

  f_socket_t socket = f_socket_t_initialize;
  char * const buffer = "test";
  size_t length = 0;

  {
    will_return(__wrap_recvfrom, false);
    will_return(__wrap_recvfrom, 1);

    const f_status_t status = f_socket_read(&socket, 0, (void *) buffer, &length);

    assert_int_equal(status, F_okay);
    assert_int_equal(length, 1);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
