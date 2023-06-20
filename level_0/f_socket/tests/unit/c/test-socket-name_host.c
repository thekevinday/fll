#include "test-socket.h"
#include "test-socket-listen.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_socket_name_host__allocates_default(void **state) {

  f_string_dynamic_t name = f_string_static_t_initialize;
  f_socket_t socket = f_socket_t_initialize;

  {
    will_return(__wrap_gethostname, false);

    const f_status_t status = f_socket_name_host(&socket, &name);

    assert_int_equal(status, F_none);
    assert_int_equal(name.size, F_socket_default_name_max_d);
  }

  free(name.string);
}

void test__f_socket_name_host__fails(void **state) {

  f_string_t name_string = "";
  f_string_static_t name = f_string_static_t_initialize;
  name.string = name_string;
  name.used = 0;
  name.size = 1;

  f_socket_t socket = f_socket_t_initialize;

  int errnos[] = {
    EFAULT,
    EINVAL,
    ENAMETOOLONG,
    EPERM,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_buffer,
    F_parameter,
    F_string_too_large,
    F_prohibited,
    F_failure,
  };

  for (uint8_t i = 0; i < 5; ++i) {

    will_return(__wrap_gethostname, true);
    will_return(__wrap_gethostname, errnos[i]);

    const f_status_t status = f_socket_name_host(&socket, &name);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_socket_name_host__parameter_checking(void **state) {

  f_string_t name_string = "";
  f_string_static_t name = f_string_static_t_initialize;
  name.string = name_string;
  name.used = 0;
  name.size = 1;

  f_socket_t socket = f_socket_t_initialize;

  {
    const f_status_t status = f_socket_name_host(0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_socket_name_host(&socket, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_socket_name_host(0, &name);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_socket_name_host__works(void **state) {

  f_string_t name_string = "";
  f_string_static_t name = f_string_static_t_initialize;
  name.string = name_string;
  name.used = 0;
  name.size = 1;

  f_socket_t socket = f_socket_t_initialize;

  {
    will_return(__wrap_gethostname, false);

    const f_status_t status = f_socket_name_host(&socket, &name);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
