#include "test-socket.h"
#include "test-socket-disconnect.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_socket_disconnect__fails_for_close_fast(void **state) {

  f_socket_t socket = f_socket_t_initialize;

  int errnos[] = {
    EBADF,
    EDQUOT,
    EINTR,
    EINVAL,
    EIO,
    ENOTCONN,
    ENOTSOCK,
    ENOSPC,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_status_set_error(F_file_descriptor),
    F_status_set_error(F_filesystem_quota_block),
    F_status_set_error(F_interrupt),
    F_status_set_error(F_value),
    F_status_set_error(F_input_output),
    F_connect_not,
    F_status_set_error(F_socket_not),
    F_status_set_error(F_parameter),
    F_status_set_error(F_failure),
  };

  for (uint8_t i = 0; i < 9; ++i) {

    socket.id = 1;

    will_return(__wrap_close, true);
    will_return(__wrap_close, errnos[i]);

    const f_status_t status = f_socket_disconnect(&socket, f_socket_close_fast_e);

    assert_int_equal(status, statuss[i]);

    if (errnos[i] != EBADF) {
      assert_int_equal(socket.id, -1);
    }
  } // for
}

void test__f_socket_disconnect__fails_for_close_read(void **state) {

  f_socket_t socket = f_socket_t_initialize;

  int errnos[] = {
    EBADF,
    EDQUOT,
    EINTR,
    EINVAL,
    EIO,
    ENOTCONN,
    ENOTSOCK,
    ENOSPC,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_status_set_error(F_file_descriptor),
    F_status_set_error(F_filesystem_quota_block),
    F_status_set_error(F_interrupt),
    F_status_set_error(F_value),
    F_status_set_error(F_input_output),
    F_connect_not,
    F_status_set_error(F_socket_not),
    F_status_set_error(F_parameter),
    F_status_set_error(F_failure),
  };

  for (uint8_t i = 0; i < 9; ++i) {

    socket.id = 1;

    will_return(__wrap_shutdown, true);
    will_return(__wrap_shutdown, errnos[i]);

    const f_status_t status = f_socket_disconnect(&socket, f_socket_close_read_e);

    assert_int_equal(status, statuss[i]);
    assert_int_equal(socket.id, 1);
  } // for
}

void test__f_socket_disconnect__fails_for_close_unknown(void **state) {

  f_socket_t socket = f_socket_t_initialize;

  {
    socket.id = 1;

    const f_status_t status = f_socket_disconnect(&socket, 100);

    assert_int_equal(status, F_status_set_error(F_support_not));
    assert_int_equal(socket.id, 1);
  }
}

void test__f_socket_disconnect__fails_for_close_write(void **state) {

  f_socket_t socket = f_socket_t_initialize;

  int errnos[] = {
    EBADF,
    EDQUOT,
    EINTR,
    EINVAL,
    EIO,
    ENOTCONN,
    ENOTSOCK,
    ENOSPC,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_status_set_error(F_file_descriptor),
    F_status_set_error(F_filesystem_quota_block),
    F_status_set_error(F_interrupt),
    F_status_set_error(F_value),
    F_status_set_error(F_input_output),
    F_connect_not,
    F_status_set_error(F_socket_not),
    F_status_set_error(F_parameter),
    F_status_set_error(F_failure),
  };

  for (uint8_t i = 0; i < 9; ++i) {

    socket.id = 1;

    will_return(__wrap_shutdown, true);
    will_return(__wrap_shutdown, errnos[i]);

    const f_status_t status = f_socket_disconnect(&socket, f_socket_close_write_e);

    assert_int_equal(status, statuss[i]);
    assert_int_equal(socket.id, 1);
  } // for
}

void test__f_socket_disconnect__parameter_checking(void **state) {

  {
    const f_status_t status = f_socket_disconnect(0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_socket_disconnect__works_for_close_fast(void **state) {

  f_socket_t socket = f_socket_t_initialize;

  {
    socket.id = 1;

    will_return(__wrap_close, false);

    const f_status_t status = f_socket_disconnect(&socket, f_socket_close_fast_e);

    assert_int_equal(status, F_okay);
    assert_int_equal(socket.id, -1);
  }
}

void test__f_socket_disconnect__works_for_close_read(void **state) {

  f_socket_t socket = f_socket_t_initialize;

  {
    socket.id = 1;

    will_return(__wrap_shutdown, false);

    const f_status_t status = f_socket_disconnect(&socket, f_socket_close_read_e);

    assert_int_equal(status, F_okay);
    assert_int_equal(socket.id, 1);
  }
}

void test__f_socket_disconnect__works_for_close_write(void **state) {

  f_socket_t socket = f_socket_t_initialize;

  {
    socket.id = 1;

    will_return(__wrap_shutdown, false);

    const f_status_t status = f_socket_disconnect(&socket, f_socket_close_write_e);

    assert_int_equal(status, F_okay);
    assert_int_equal(socket.id, 1);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
