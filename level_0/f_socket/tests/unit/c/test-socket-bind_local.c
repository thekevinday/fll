#include "test-socket.h"
#include "test-socket-bind_local.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_socket_bind_local__fails(void **state) {

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
    struct sockaddr_un address;

    memset(&address, 0, sizeof(struct sockaddr_un));

    address.sun_family = f_socket_protocol_family_local_e;

    socket.address = (struct sockaddr *) &address;

    for (uint8_t i = 0; i < 12; ++i) {

      const f_status_t status = f_socket_bind_local(&socket);

      assert_int_equal(status, F_status_set_error(F_local_not));
    } // for
  }

  {
    f_socket_t socket = f_socket_t_initialize;
    struct sockaddr_un address;

    memset(&address, 0, sizeof(struct sockaddr_un));

    address.sun_family = f_socket_protocol_family_local_e;

    socket.address = (struct sockaddr *) &address;
    socket.domain = f_socket_protocol_family_local_e;

    for (uint8_t i = 0; i < 12; ++i) {

      will_return(__wrap_bind, true);
      will_return(__wrap_bind, errnos[i]);

      const f_status_t status = f_socket_bind_local(&socket);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  }
}

void test__f_socket_bind_local__parameter_checking(void **state) {

  {
    const f_status_t status = f_socket_bind_local(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_socket_bind_local__works(void **state) {

  {
    f_socket_t socket = f_socket_t_initialize;
    struct sockaddr_un address;

    memset(&address, 0, sizeof(struct sockaddr_un));

    address.sun_family = f_socket_protocol_family_local_e;

    socket.address = (struct sockaddr *) &address;
    socket.domain = f_socket_protocol_family_local_e;

    will_return(__wrap_bind, false);

    const f_status_t status = f_socket_bind_local(&socket);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
