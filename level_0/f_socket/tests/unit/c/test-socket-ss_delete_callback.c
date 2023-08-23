#include "test-socket.h"
#include "test-socket-ss_delete_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_socket_ss_delete_callback__fails(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 0;

  f_socket_t data = f_socket_t_initialize;
  f_socket_t data_array[] = { data };
  f_sockets_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_sockets_t datas_array[] = { datas };

  {
    will_return(__wrap_f_memory_array_resize, true);
    will_return(__wrap_f_memory_array_resize, F_status_set_error(F_failure));

    const f_status_t status = f_socketss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_socket_ss_delete_callback__works(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 1;

  const f_number_unsigned_t length = 1;

  f_socketss_t datass = f_socketss_t_initialize;

  {
    f_status_t status = f_memory_array_resize(length, sizeof(f_sockets_t), (void **) &datass.array, &datass.used, &datass.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_socket_t), (void **) &datass.array[0].array, &datass.array[0].used, &datass.array[0].size);
    assert_int_equal(status, F_okay);
  }

  {
    const f_status_t status = f_socketss_delete_callback(0, length, (void *) datass.array);

    assert_int_equal(status, F_okay);
    assert_int_equal(datass.array[0].size, 0);
  }

  free((void *) datass.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
