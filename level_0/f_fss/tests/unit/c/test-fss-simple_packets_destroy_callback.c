#include "test-fss.h"
#include "test-fss-simple_packets_destroy_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_simple_packets_destroy_callback__fails(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 0;

  f_string_static_t base = macro_f_string_static_t_initialize_1(F_string_empty_s, 1, 0);

  f_fss_simple_packet_t data = { .payload = base };
  f_fss_simple_packet_t data_array[] = { data };

  {
    will_return(__wrap_f_memory_array_adjust, true);
    will_return(__wrap_f_memory_array_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_fss_simple_packets_destroy_callback(0, 1, (void *) data_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_fss_simple_packets_destroy_callback__works(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 1;

  const f_number_unsigned_t length = 1;

  f_fss_simple_packets_t datas = f_fss_simple_packets_t_initialize;

  {
    f_status_t status = f_memory_array_resize(1, sizeof(f_fss_simple_packet_t), (void **) &datas.array, &datas.used, &datas.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_char_t), (void **) &datas.array[0].payload, &datas.array[0].payload.used, &datas.array[0].payload.size);
    assert_int_equal(status, F_okay);
  }

  {
    const f_status_t status = f_fss_simple_packets_destroy_callback(0, length, (void *) datas.array);

    assert_int_equal(status, F_okay);
    assert_int_equal(datas.array[0].payload.size, 0);
  }

  free((void *) datas.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
