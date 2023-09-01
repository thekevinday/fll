#include "test-fss.h"
#include "test-fss-simple_packet_destroy.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_simple_packet_destroy__fails(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 0;

  f_string_static_t base = macro_f_string_static_t_initialize_1(F_string_empty_s, 1, 0);

  f_fss_simple_packet_t data = { .payload = base };

  {
    will_return(__wrap_f_memory_array_adjust, true);
    will_return(__wrap_f_memory_array_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_fss_simple_packet_destroy(&data);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_fss_simple_packet_destroy__parameter_checking(void **state) {

  {
    const f_status_t status = f_fss_simple_packet_destroy(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_fss_simple_packet_destroy__works(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 1;

  const f_number_unsigned_t length = 1;

  f_fss_simple_packet_t data = f_fss_simple_packet_t_initialize;

  {
    const f_status_t status = f_memory_array_resize(length, sizeof(f_char_t), (void **) &data.payload, &data.payload.used, &data.payload.size);
    assert_int_equal(status, F_okay);
  }

  {
    const f_status_t status = f_fss_simple_packet_destroy(&data);

    assert_int_equal(status, F_okay);
    assert_int_equal(data.payload.size, 0);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
