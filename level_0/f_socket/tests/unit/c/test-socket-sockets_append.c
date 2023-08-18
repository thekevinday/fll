#include "test-socket.h"
#include "test-socket-sockets_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_socket_sockets_append__parameter_checking(void **state) {

  const f_socket_t data = f_socket_t_initialize;

  {
    const f_status_t status = f_sockets_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_socket_sockets_append__works(void **state) {

  f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_socket_t source = macro_f_socket_t_initialize_3(1, 2, 3, 4, f_socket_address_t_initialize, 0, test);
  f_sockets_t destination = f_sockets_t_initialize;

  {
    const f_status_t status = f_sockets_append(source, &destination);

    assert_int_equal(status, F_okay);
    assert_int_equal(destination.used, 1);
    assert_int_equal(destination.array[0].id, source.id);
    assert_int_equal(destination.array[0].domain, source.domain);
    assert_int_equal(destination.array[0].protocol, source.protocol);
    assert_int_equal(destination.array[0].type, source.type);
    assert_int_equal(destination.array[0].name.used, source.name.used);

    assert_string_equal(destination.array[0].name.string, source.name.string);
  }

  free((void *) destination.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
