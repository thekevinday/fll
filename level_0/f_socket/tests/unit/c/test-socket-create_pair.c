#include "test-socket.h"
#include "test-socket-create_pair.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_socket_create_pair__fails(void **state) {

  int id_1 = 1;
  int id_2 = 2;

  int errnos[] = {
    EACCES,
    EAFNOSUPPORT,
    EINVAL,
    EMFILE,
    ENFILE,
    ENOBUFS,
    ENOMEM,
    EPROTONOSUPPORT,
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
    F_failure,
  };

  for (uint8_t i = 0; i < 9; ++i) {

    will_return(__wrap_socketpair, true);
    will_return(__wrap_socketpair, errnos[i]);

    const f_status_t status = f_socket_create_pair(0, 0, 0, &id_1, &id_2);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_socket_create_pair__parameter_checking(void **state) {

  int id = 0;

  {
    const f_status_t status = f_socket_create_pair(0, 0, 0, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_socket_create_pair(0, 0, 0, &id, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_socket_create_pair(0, 0, 0, 0, &id);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_socket_create_pair__works(void **state) {

  int id_1 = 1;
  int id_2 = 2;

  {
    will_return(__wrap_socketpair, false);

    const f_status_t status = f_socket_create_pair(0, 0, 0, &id_1, &id_2);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
