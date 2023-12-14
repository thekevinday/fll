#include "test-fss.h"
#include "test-fss-simple_packet_encode.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_simple_packet_encode__parameter_checking(void **state) {

  {
    const f_status_t status = f_fss_simple_packet_encode(0, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_fss_simple_packet_encode__works_big_endian(void **state) {

  const f_char_t datas[3][5] = {
    { 0x80, 0x05, 0x00, 0x00, 0x00 },
    { 0x80, 0x06, 0x00, 0x00, 0x00 },
    { 0x80, 0x07, 0x00, 0x00, 0x00 },
  };

  const f_number_unsigned_t size[] = {
    5,
    6,
    7,
  };

  {
    for (uint8_t i = 0; i < 3; ++i) {

      f_string_dynamic_t dynamic = f_string_dynamic_t_initialize;

      const f_status_t status = f_fss_simple_packet_encode(F_fss_simple_packet_endian_d, size[i], &dynamic);

      assert_int_equal(status, F_okay);
      assert_int_equal(dynamic.string[0], datas[i][0]);
      assert_int_equal(dynamic.string[1], datas[i][1]);
      assert_int_equal(dynamic.string[2], datas[i][2]);
      assert_int_equal(dynamic.string[3], datas[i][3]);
      assert_int_equal(dynamic.string[4], datas[i][4]);
      assert_int_equal(dynamic.used, F_fss_simple_packet_block_header_size_d);

      free(dynamic.string);
    } // for
  }
}

void test__f_fss_simple_packet_encode__works_little_endian(void **state) {

  const f_char_t datas[3][5] = {
    { 0x00, 0x00, 0x00, 0x00, 0x05 },
    { 0x00, 0x00, 0x00, 0x00, 0x06 },
    { 0x00, 0x00, 0x00, 0x00, 0x07 },
  };

  const f_number_unsigned_t size[] = {
    5,
    6,
    7,
  };

  {
    for (uint8_t i = 0; i < 3; ++i) {

      f_string_dynamic_t dynamic = f_string_dynamic_t_initialize;

      const f_status_t status = f_fss_simple_packet_encode(0, size[i], &dynamic);

      assert_int_equal(status, F_okay);
      assert_int_equal(dynamic.string[0], datas[i][0]);
      assert_int_equal(dynamic.string[1], datas[i][1]);
      assert_int_equal(dynamic.string[2], datas[i][2]);
      assert_int_equal(dynamic.string[3], datas[i][3]);
      assert_int_equal(dynamic.string[4], datas[i][4]);
      assert_int_equal(dynamic.used, F_fss_simple_packet_block_header_size_d);

      free(dynamic.string);
    } // for
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
