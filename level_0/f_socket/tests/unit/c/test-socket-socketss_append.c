#include "test-socket.h"
#include "test-socket-socketss_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_socket_socketss_append__parameter_checking(void **state) {

  f_sockets_t data = f_sockets_t_initialize;

  {
    const f_status_t status = f_socketss_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_socket_socketss_append__returns_data_not(void **state) {

  const int length = 5;
  f_sockets_t source = f_sockets_t_initialize;
  f_socketss_t destination = f_socketss_t_initialize;

  {
    const f_status_t status = f_sockets_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_socketss_append(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_socket_socketss_append__works(void **state) {

  const int length = 5;

  f_string_static_t tests[] = {
    macro_f_string_static_t_initialize_1("test_1", 0, 6),
    macro_f_string_static_t_initialize_1("test_2", 0, 6),
    macro_f_string_static_t_initialize_1("test_3", 0, 6),
    macro_f_string_static_t_initialize_1("test_4", 0, 6),
    macro_f_string_static_t_initialize_1("test_5", 0, 6),
  };

  f_socket_t sources[] = {
    macro_f_socket_t_initialize_3(1, 2, 3, 4, 0, 0, tests[0]),
    macro_f_socket_t_initialize_3(5, 6, 7, 8, 0, 0, tests[1]),
    macro_f_socket_t_initialize_3(9, 10, 11, 12, 0, 0, tests[2]),
    macro_f_socket_t_initialize_3(13, 14, 15, 16, 0, 0, tests[3]),
    macro_f_socket_t_initialize_3(17, 18, 19, 20, 0, 0, tests[4]),
  };

  f_sockets_t source = f_sockets_t_initialize;
  f_socketss_t destination = f_socketss_t_initialize;

  {
    const f_status_t status = f_sockets_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  for (; source.used < length; ++source.used) {
    source.array[source.used] = sources[source.used];
  } // for

  {
    const f_status_t status = f_socketss_append(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, 1);
    assert_int_equal(destination.array[0].used, source.used);
    assert_int_equal(destination.array[0].size, source.used);

    for (f_number_unsigned_t i = 0; i < destination.array[0].used; ++i) {

      assert_int_equal(destination.array[0].array[i].id, sources[i].id);
      assert_int_equal(destination.array[0].array[i].domain, sources[i].domain);
      assert_int_equal(destination.array[0].array[i].protocol, sources[i].protocol);
      assert_int_equal(destination.array[0].array[i].type, sources[i].type);
      assert_int_equal(destination.array[0].array[i].name.used, sources[i].name.used);

      assert_string_equal(destination.array[0].array[i].name.string, sources[i].name.string);
    } // for
  }

  for (f_number_unsigned_t i = 0; i < destination.used; ++i) {
    free((void *) destination.array[i].array);
  } // for

  free((void *) source.array);
  free((void *) destination.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
