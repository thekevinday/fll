#include "test-socket.h"
#include "test-socket-socketss_append_all.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_socket_socketss_append_all__parameter_checking(void **state) {

  const f_socketss_t data = f_socketss_t_initialize;

  {
    const f_status_t status = f_socketss_append_all(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_socket_socketss_append_all__returns_data_not(void **state) {

  const int length = 5;
  f_socketss_t source = f_socketss_t_initialize;
  f_socketss_t destination = f_socketss_t_initialize;

  {
    const f_status_t status = f_socketss_resize(length, &source);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_socketss_append_all(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_socket_socketss_append_all__works(void **state) {

  const int length = 5;
  const int length_inner = 2;

  f_string_static_t tests[] = {
    macro_f_string_static_t_initialize_1("test_1", 0, 6),
    macro_f_string_static_t_initialize_1("test_2", 0, 6),
  };

  f_socket_t sources[] = {
    macro_f_socket_t_initialize_3(1, 2, 3, 4, f_socket_address_t_initialize, 0, tests[0]),
    macro_f_socket_t_initialize_3(5, 6, 7, 8, f_socket_address_t_initialize, 0, tests[1]),
  };

  f_socketss_t source = f_socketss_t_initialize;
  f_socketss_t destination = f_socketss_t_initialize;

  {
    const f_status_t status = f_socketss_resize(length, &source);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    for (; source.used < length; ++source.used) {

      const f_status_t status = f_sockets_resize(length_inner, &source.array[source.used]);

      assert_int_equal(status, F_okay);

      for (f_number_unsigned_t i = 0; i < length_inner; ++i) {
        source.array[source.used].array[source.array[source.used].used++] = sources[i];
      } // for
    } // for
  }

  {
    const f_status_t status = f_socketss_append_all(source, &destination);

    assert_int_equal(status, F_okay);
    assert_int_equal(destination.used, source.used);
    assert_int_equal(destination.size, source.used);

    for (f_number_unsigned_t i = 0; i < destination.used; ++i) {

      assert_int_equal(destination.array[i].used, length_inner);
      assert_int_equal(destination.array[i].size, length_inner);

      for (f_number_unsigned_t j = 0; j < length_inner; ++j) {

        assert_int_equal(destination.array[i].array[j].id, sources[j].id);
        assert_int_equal(destination.array[i].array[j].domain, sources[j].domain);
        assert_int_equal(destination.array[i].array[j].protocol, sources[j].protocol);
        assert_int_equal(destination.array[i].array[j].type, sources[j].type);
        assert_int_equal(destination.array[i].array[j].name.used, sources[j].name.used);

        assert_string_equal(destination.array[i].array[j].name.string, sources[j].name.string);
      } // for
    } // for
  }

  for (f_number_unsigned_t i = 0; i < source.used; ++i) {
    free((void *) source.array[i].array);
  } // for

  for (f_number_unsigned_t i = 0; i < destination.used; ++i) {
    free((void *) destination.array[i].array);
  } // for

  free((void *) source.array);
  free((void *) destination.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
