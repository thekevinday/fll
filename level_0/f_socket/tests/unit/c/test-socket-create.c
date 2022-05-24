#include "test-socket.h"
#include "test-socket-create.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_socket_create__fails(void **state) {

  f_socket_t socket = f_socket_t_initialize;

  int errnos[] = {
    EACCES,
    EAFNOSUPPORT,
    EINVAL,
    EMFILE,
    ENFILE,
    ENOBUFS,
    ENOMEM,
    EPROTONOSUPPORT,
    ESOCKTNOSUPPORT,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_access_denied,
    F_domain_not,
    F_parameter,
    F_file_descriptor_max,
    F_file_open_max,
    F_buffer_not,
    F_memory_not,
    F_protocol_not,
    F_type_not,
    F_failure,
  };

  for (uint8_t i = 0; i < 10; ++i) {

    will_return(__wrap_socket, true);
    will_return(__wrap_socket, errnos[i]);

    const f_status_t status = f_socket_create(&socket);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_socket_create__parameter_checking(void **state) {

  {
    const f_status_t status = f_socket_create(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_socket_create__works(void **state) {

  f_socket_t socket = f_socket_t_initialize;

  {

    will_return(__wrap_socket, false);

    const f_status_t status = f_socket_create(&socket);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
