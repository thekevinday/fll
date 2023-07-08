#include "test-socket.h"
#include "test-socket-bind_inet6.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_socket_bind_inet6__fails(void **state) {

  int errnos[] = {
    EACCES,
    EADDRINUSE,
    EADDRNOTAVAIL,
    EFAULT,
    EINVAL,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOTDIR,
    ENOTSOCK,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_access_denied,
    F_busy_address,
    F_available_not_address,
    F_buffer,
    F_parameter,
    F_loop,
    F_string_too_large,
    F_file_found_not,
    F_memory_not,
    F_directory_found_not,
    F_socket_not,
    F_failure,
  };

  {
    f_socket_t socket = f_socket_t_initialize;
    socket.domain = f_socket_protocol_family_inet6_e;
    socket.protocol = f_socket_protocol_tcp_e;
    socket.type = f_socket_address_family_inet6_e;

    for (uint8_t i = 0; i < 12; ++i) {

      will_return(__wrap_bind, true);
      will_return(__wrap_bind, errnos[i]);

      const f_status_t status = f_socket_bind_inet6(&socket);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  }

  {
    f_socket_t socket = f_socket_t_initialize;
    socket.domain = f_socket_protocol_family_inet6_e;
    socket.protocol = f_socket_protocol_tcp_e;
    socket.type = f_socket_address_family_inet6_e;

    for (uint8_t i = 0; i < 12; ++i) {

      will_return(__wrap_bind, true);
      will_return(__wrap_bind, errnos[i]);

      const f_status_t status = f_socket_bind_inet6(&socket);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  }
}

void test__f_socket_bind_inet6__parameter_checking(void **state) {

  {
    const f_status_t status = f_socket_bind_inet6(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_socket_bind_inet6__works(void **state) {

  {
    f_socket_t socket = f_socket_t_initialize;
    socket.domain = f_socket_protocol_family_inet6_e;
    socket.protocol = f_socket_protocol_tcp_e;
    socket.type = f_socket_address_family_inet6_e;

    will_return(__wrap_bind, false);

    const f_status_t status = f_socket_bind_inet6(&socket);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
