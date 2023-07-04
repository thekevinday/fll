#include "test-socket.h"
#include "test-socket-sockets_append_all.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_socket_sockets_append_all__parameter_checking(void **state) {

  const f_sockets_t data = f_sockets_t_initialize;

  {
    const f_status_t status = f_sockets_append_all(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_socket_sockets_append_all__returns_data_not(void **state) {

  const int length = 5;
  f_sockets_t source = f_sockets_t_initialize;
  f_sockets_t destination = f_sockets_t_initialize;

  {
    const f_status_t status = f_sockets_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_sockets_append_all(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_socket_sockets_append_all__works(void **state) {

  const int length = 5;
  const int length_used = 2;

  f_string_static_t tests[] = {
    macro_f_string_static_t_initialize_1("test_1", 0, 6),
    macro_f_string_static_t_initialize_1("test_2", 0, 6),
  };

  f_socket_t sources[] = {
    macro_f_socket_t_initialize_3(1, 2, 3, 4, 0, 0, tests[0]),
    macro_f_socket_t_initialize_3(5, 6, 7, 8, 0, 0, tests[1]),
  };

  f_sockets_t source = f_sockets_t_initialize;
  f_sockets_t destination = f_sockets_t_initialize;

  {
    const f_status_t status = f_sockets_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  for (; source.used < length_used; ++source.used) {
    source.array[source.used] = sources[source.used];
    //memcpy((void *) &source.array[source.used], (void *) &sources[source.used], sizeof(f_sockets_t));
  } // for

  {
    const f_status_t status = f_sockets_append_all(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, source.used);
    assert_int_equal(destination.size, source.used);

    for (f_number_unsigned_t i = 0; i < source.used; ++i) {

      assert_int_equal(destination.array[i].id, sources[i].id);
      assert_int_equal(destination.array[i].domain, sources[i].domain);
      assert_int_equal(destination.array[i].protocol, sources[i].protocol);
      assert_int_equal(destination.array[i].type, sources[i].type);
      assert_int_equal(destination.array[i].name.used, sources[i].name.used);

      assert_string_equal(destination.array[i].name.string, sources[i].name.string);
    } // for
  }

  free((void *) source.array);
  free((void *) destination.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
