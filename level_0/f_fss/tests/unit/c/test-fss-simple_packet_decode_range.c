#include "test-fss.h"
#include "test-fss-simple_packet_decode_range.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_simple_packet_decode_range__parameter_checking(void **state) {

  {
    const f_status_t status = f_fss_simple_packet_decode_range(f_string_empty_s, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_fss_simple_packet_decode_range__returns_packet_too_small(void **state) {

  f_string_static_t test = macro_f_string_static_t_initialize_1("testing", 0, 0);
  f_fss_simple_packet_range_t packet = f_fss_simple_packet_range_t_initialize;

  {
    for (test.used = 0; test.used < F_fss_simple_packet_block_header_size_d; ++test.used) {

      const f_status_t status = f_fss_simple_packet_decode_range(f_string_empty_s, &packet);

      assert_int_equal(status, F_packet_too_small);
    } // for
  }
}

void test__f_fss_simple_packet_decode_range__works_big_endian(void **state) {

  f_char_t string_1[] = { 0x80, 0x05, 0x00, 0x00, 0x00 };
  f_char_t string_2[] = { 0x80, 0x06, 0x00, 0x00, 0x00, 0x01 };
  f_char_t string_3[] = { 0x80, 0x07, 0x00, 0x00, 0x00, 0x01, 0x02 };

  const f_string_static_t datas[] = {
    macro_f_string_static_t_initialize_1(string_1, 0, 5 ),
    macro_f_string_static_t_initialize_1(string_2, 0, 6 ),
    macro_f_string_static_t_initialize_1(string_3, 0, 7 ),
  };

  const f_number_unsigned_t size[] = {
    5,
    6,
    7,
  };

  {
    for (uint8_t i = 0; i < 3; ++i) {

      f_fss_simple_packet_range_t packet = f_fss_simple_packet_range_t_initialize;

      const f_status_t status = f_fss_simple_packet_decode_range(datas[i], &packet);

      assert_int_equal(status, F_okay);
      assert_int_equal(packet.control & F_fss_simple_packet_endian_d, F_fss_simple_packet_endian_d);
      assert_int_equal(packet.size, size[i]);
    } // for
  }
}

void test__f_fss_simple_packet_decode_range__works_little_endian(void **state) {

  f_char_t string_1[] = { 0x00, 0x00, 0x00, 0x00, 0x05 };
  f_char_t string_2[] = { 0x00, 0x00, 0x00, 0x00, 0x06, 0x01 };
  f_char_t string_3[] = { 0x00, 0x00, 0x00, 0x00, 0x07, 0x01, 0x02 };

  const f_string_static_t datas[] = {
    macro_f_string_static_t_initialize_1(string_1, 0, 5 ),
    macro_f_string_static_t_initialize_1(string_2, 0, 6 ),
    macro_f_string_static_t_initialize_1(string_3, 0, 7 ),
  };

  const f_number_unsigned_t size[] = {
    5,
    6,
    7,
  };

  {
    for (uint8_t i = 0; i < 3; ++i) {

      f_fss_simple_packet_range_t packet = f_fss_simple_packet_range_t_initialize;

      const f_status_t status = f_fss_simple_packet_decode_range(datas[i], &packet);

      assert_int_equal(status, F_okay);
      assert_int_equal(packet.control & F_fss_simple_packet_endian_d, 0);
      assert_int_equal(packet.size, size[i]);
    } // for
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
