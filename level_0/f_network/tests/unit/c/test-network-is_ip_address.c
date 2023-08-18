#include "test-network.h"
#include "test-network-is_ip_address.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_network_is_ip_address__returns_data_not(void **state) {

  f_state_t state_data = f_state_t_initialize;

  {
    f_network_is_ip_address(f_string_empty_s, 0, &state_data);

    assert_int_equal(state_data.status, F_data_not);
  }
}

void test__f_network_is_ip_address__returns_false(void **state) {

  f_state_t state_data = f_state_t_initialize;

  const f_string_static_t ips[] = {
    macro_f_string_static_t_initialize_1("127", 0, 3),
    macro_f_string_static_t_initialize_1("a", 0, 1),
    macro_f_string_static_t_initialize_1("www.example.com", 0, 15),
    macro_f_string_static_t_initialize_1("www.example.com:80", 0, 18),
    macro_f_string_static_t_initialize_1("localhost", 0, 9),
    macro_f_string_static_t_initialize_1("___", 0, 3),
    macro_f_string_static_t_initialize_1("]", 0, 1),
  };

  for (uint8_t i = 0; i < 7; ++i) {

    state_data.status = F_okay;

    f_network_is_ip_address(ips[i], 0, &state_data);

    assert_int_equal(state_data.status, F_false);
  } // for
}

void test__f_network_is_ip_address__returns_network_version_four(void **state) {

  f_state_t state_data = f_state_t_initialize;

  const f_string_static_t ips[] = {
    macro_f_string_static_t_initialize_1("127.0.0.1", 0, 9),
    macro_f_string_static_t_initialize_1("127.0.0.1/24", 0, 12),
    macro_f_string_static_t_initialize_1("127.0.0.1:80", 0, 12),
    macro_f_string_static_t_initialize_1("127.0.0.1/24:80", 0, 15),
  };

  const f_number_unsigned_t ports[] = {
    0,
    0,
    10,
    13,
  };

  f_number_unsigned_t port = 0;

  for (uint8_t i = 0; i < 4; ++i) {

    state_data.status = F_okay;
    port = 100000;

    f_network_is_ip_address(ips[i], &port, &state_data);

    assert_int_equal(state_data.status, F_network_version_four);
    assert_int_equal(port, ports[i]);
  } // for
}

void test__f_network_is_ip_address__returns_network_version_four_not(void **state) {

  f_state_t state_data = f_state_t_initialize;

  const f_string_static_t ips[] = {
    macro_f_string_static_t_initialize_1("127.", 0, 4),
    macro_f_string_static_t_initialize_1("127./24", 0, 7),
    macro_f_string_static_t_initialize_1("127./2a", 0, 7),
    macro_f_string_static_t_initialize_1("0..", 0, 3),
    macro_f_string_static_t_initialize_1("0.1111", 0, 6),
    macro_f_string_static_t_initialize_1("0.1.2.3.4.", 0, 10),
    macro_f_string_static_t_initialize_1("0.1.2.3.4.5.6", 0, 13),
    macro_f_string_static_t_initialize_1("1274.", 0, 5),
    macro_f_string_static_t_initialize_1("127.1234", 0, 8),
    macro_f_string_static_t_initialize_1("127.hello", 0, 9),
    macro_f_string_static_t_initialize_1("a.0.0.1", 0, 7),
    macro_f_string_static_t_initialize_1("a.b", 0, 9),
    macro_f_string_static_t_initialize_1("127.0.0.1/1234", 0, 14),
    macro_f_string_static_t_initialize_1("127.0.0.1/2a", 0, 12),
    macro_f_string_static_t_initialize_1(".", 0, 1),
    macro_f_string_static_t_initialize_1("..", 0, 2),
    macro_f_string_static_t_initialize_1(".127.0.0.1", 0, 10),
  };

  for (uint8_t i = 0; i < 17; ++i) {

    state_data.status = F_okay;

    f_network_is_ip_address(ips[i], 0, &state_data);

    assert_int_equal(state_data.status, F_network_version_four_not);
  } // for
}

void test__f_network_is_ip_address__returns_network_version_six_not(void **state) {

  f_state_t state_data = f_state_t_initialize;

  const f_string_static_t ips[] = {
    macro_f_string_static_t_initialize_1(":", 0, 1),
    macro_f_string_static_t_initialize_1("::", 0, 2),
    macro_f_string_static_t_initialize_1(":/24", 0, 4),
    macro_f_string_static_t_initialize_1("::/24", 0, 5),
    macro_f_string_static_t_initialize_1(":/2a", 0, 4),
    macro_f_string_static_t_initialize_1("::/2a", 0, 5),
    macro_f_string_static_t_initialize_1(":12345", 0, 6),
    macro_f_string_static_t_initialize_1("::12345", 0, 7),
    macro_f_string_static_t_initialize_1(":12345/24", 0, 9),
    macro_f_string_static_t_initialize_1("::12345/24", 0, 10),
    macro_f_string_static_t_initialize_1(":12345/2a", 0, 9),
    macro_f_string_static_t_initialize_1("::12345/2a", 0, 10),
    macro_f_string_static_t_initialize_1("::1/1234", 0, 8),
    macro_f_string_static_t_initialize_1("::1/12a", 0, 7),
    macro_f_string_static_t_initialize_1(":example", 0, 8),
    macro_f_string_static_t_initialize_1("::example", 0, 9),
    macro_f_string_static_t_initialize_1(":example/24", 0, 11),
    macro_f_string_static_t_initialize_1("::example/24", 0, 12),
    macro_f_string_static_t_initialize_1(":example/2a", 0, 11),
    macro_f_string_static_t_initialize_1("::example/2a", 0, 12),
    macro_f_string_static_t_initialize_1("[:", 0, 1),
    macro_f_string_static_t_initialize_1("[::", 0, 2),
    macro_f_string_static_t_initialize_1("[:/24", 0, 4),
    macro_f_string_static_t_initialize_1("[::/24", 0, 5),
    macro_f_string_static_t_initialize_1("[:/2a", 0, 4),
    macro_f_string_static_t_initialize_1("[::/2a", 0, 5),
    macro_f_string_static_t_initialize_1("[:1/24", 0, 5),
    macro_f_string_static_t_initialize_1("[::1/24", 0, 6),
    macro_f_string_static_t_initialize_1("[:12345", 0, 6),
    macro_f_string_static_t_initialize_1("[::12345", 0, 7),
    macro_f_string_static_t_initialize_1("[:12345/24", 0, 9),
    macro_f_string_static_t_initialize_1("[::12345/24", 0, 10),
    macro_f_string_static_t_initialize_1("[::1/1234", 0, 8),
    macro_f_string_static_t_initialize_1("[::1", 0, 4),
    macro_f_string_static_t_initialize_1("[::1/24", 0, 7),
    macro_f_string_static_t_initialize_1("[:example", 0, 9),
    macro_f_string_static_t_initialize_1("[::example", 0, 10),
    macro_f_string_static_t_initialize_1("[:example/24", 0, 12),
    macro_f_string_static_t_initialize_1("[::example/24", 0, 13),
    macro_f_string_static_t_initialize_1("[:example/2a", 0, 12),
    macro_f_string_static_t_initialize_1("[::example/2a", 0, 13),
    macro_f_string_static_t_initialize_1("[:]", 0, 1),
    macro_f_string_static_t_initialize_1("[:1/24]", 0, 7),
    macro_f_string_static_t_initialize_1("[:1]/24", 0, 7),
    macro_f_string_static_t_initialize_1("[:1/2a]", 0, 7),
    macro_f_string_static_t_initialize_1("[:1]/2a", 0, 7),
    macro_f_string_static_t_initialize_1("[::]", 0, 2),
    macro_f_string_static_t_initialize_1("[::1]/24", 0, 8),
    macro_f_string_static_t_initialize_1("[::1]/2a", 0, 8),
    macro_f_string_static_t_initialize_1("[:/24]", 0, 4),
    macro_f_string_static_t_initialize_1("[:/2a]", 0, 4),
    macro_f_string_static_t_initialize_1("[::/24]", 0, 5),
    macro_f_string_static_t_initialize_1("[::/2a]", 0, 5),
    macro_f_string_static_t_initialize_1("[:12345]", 0, 6),
    macro_f_string_static_t_initialize_1("[::12345]", 0, 7),
    macro_f_string_static_t_initialize_1("[:12345/24]", 0, 9),
    macro_f_string_static_t_initialize_1("[::12345/24]", 0, 10),
    macro_f_string_static_t_initialize_1("[:12345/2a]", 0, 9),
    macro_f_string_static_t_initialize_1("[::12345/2a]", 0, 10),
    macro_f_string_static_t_initialize_1("[::1/1234]", 0, 8),
    macro_f_string_static_t_initialize_1("[:example]", 0, 10),
    macro_f_string_static_t_initialize_1("[::example]", 0, 11),
    macro_f_string_static_t_initialize_1("[:example/24]", 0, 13),
    macro_f_string_static_t_initialize_1("[::example/24]", 0, 14),
    macro_f_string_static_t_initialize_1("[:example]/24", 0, 13),
    macro_f_string_static_t_initialize_1("[::example]/24", 0, 14),
    macro_f_string_static_t_initialize_1("[:example/2a]", 0, 13),
    macro_f_string_static_t_initialize_1("[::example/2a]", 0, 14),
    macro_f_string_static_t_initialize_1("[:example]/2a", 0, 13),
    macro_f_string_static_t_initialize_1("[::example]/2a", 0, 14),
    macro_f_string_static_t_initialize_1("1234::example", 0, 13),
    macro_f_string_static_t_initialize_1("1234:example", 0, 12),
    macro_f_string_static_t_initialize_1("1234:1234:1234:1234:1234:1234:1234:1234:1234", 0, 44),
    macro_f_string_static_t_initialize_1("1234::1234:1234:1234:1234::1234:1234:1234", 0, 41),
    macro_f_string_static_t_initialize_1("1234::1234::1234", 0, 16),
    macro_f_string_static_t_initialize_1("a234:1234:1234:1234:1234:1234:1234:1234:1234", 0, 44),
    macro_f_string_static_t_initialize_1("a234::1234:1234:1234:1234::1234:1234:1234", 0, 41),
    macro_f_string_static_t_initialize_1("a234::1234::1234", 0, 16),
    macro_f_string_static_t_initialize_1("1234:aaaa:1234:1234:1234:1234:1234:1234:1234", 0, 44),
    macro_f_string_static_t_initialize_1("1234::aaaa:1234:1234:1234::1234:1234:1234", 0, 41),
    macro_f_string_static_t_initialize_1("1234::aaaa::1234", 0, 16),
    macro_f_string_static_t_initialize_1("1234::www.example.com", 0, 21),
    macro_f_string_static_t_initialize_1("2001:0DB8:0:CD30:123:4567:89AB:CDEF/1234", 0, 40),
    macro_f_string_static_t_initialize_1("2001:0DB8:0:CD30:123:4567:89AB:CDEF/2a", 0, 38),
    macro_f_string_static_t_initialize_1("2001:0DB83:0:CD30:123:4567:89AB:CDEF", 0, 36),
    macro_f_string_static_t_initialize_1("2001:0DB83:0:CD30:123:4567:89AB:CDEF/1234", 0, 41),
    macro_f_string_static_t_initialize_1("[2001:0DB8:0:CD30:123:4567:89AB:CDEF/1234]", 0, 42),
    macro_f_string_static_t_initialize_1("2001:0DB83:0:CD30:123:4567:89AB:CDEF/2a", 0, 39),
    macro_f_string_static_t_initialize_1("[2001:0DB8:0:CD30:123:4567:89AB:CDEF/2a]", 0, 40),
    macro_f_string_static_t_initialize_1("[2001:0DB83:0:CD30:123:4567:89AB:CDEF]", 0, 38),
    macro_f_string_static_t_initialize_1("[2001:0DB83:0:CD30:123:4567:89AB:CDEF/1234]", 0, 43),
    macro_f_string_static_t_initialize_1("[2001:0DB83:0:CD30:123:4567:89AB:CDEF/2a]", 0, 41),
    macro_f_string_static_t_initialize_1("[2001:0DB8:0:CD30:123:4567:89AB:CDEF]a", 0, 38),
    macro_f_string_static_t_initialize_1("[2001:0DB8:0:CD30:123:4567:89AB:CDEF]1", 0, 38),
    macro_f_string_static_t_initialize_1("[2001:0DB8:0:CD30:123:4567:89AB:CDEF]hello", 0, 42),
    macro_f_string_static_t_initialize_1("[2001:0DB8:0:CD30:123:4567:89AB:CDEF]/24", 0, 40),
    macro_f_string_static_t_initialize_1("[2001:0DB8:0:CD30:123:4567:89AB:CDEF]/2a", 0, 40),
    macro_f_string_static_t_initialize_1("[2001:0DB8:0:CD30:123:4567:89AB:CDEF]/1234", 0, 42),
  };

  for (uint8_t i = 0; i < 98; ++i) {

    state_data.status = F_okay;

    f_network_is_ip_address(ips[i], 0, &state_data);

    assert_int_equal(state_data.status, F_network_version_six_not);
  } // for
}

void test__f_network_is_ip_address__returns_network_version_six(void **state) {

  f_state_t state_data = f_state_t_initialize;

  const f_string_static_t ips[] = {
    macro_f_string_static_t_initialize_1("::1", 0, 3),
    macro_f_string_static_t_initialize_1("[::1]", 0, 5),
    macro_f_string_static_t_initialize_1("[::1]:80", 0, 8),
    macro_f_string_static_t_initialize_1("::1/24", 0, 6),
    macro_f_string_static_t_initialize_1("[::1/24]", 0, 8),
    macro_f_string_static_t_initialize_1("[::1/24]:80", 0, 11),
    macro_f_string_static_t_initialize_1("2001:0DB8:0:CD30:123:4567:89AB:CDEF", 0, 35),
    macro_f_string_static_t_initialize_1("[2001:0DB8:0:CD30:123:4567:89AB:CDEF]", 0, 37),
    macro_f_string_static_t_initialize_1("[2001:0DB8:0:CD30:123:4567:89AB:CDEF]:80", 0, 40),
    macro_f_string_static_t_initialize_1("2001:0DB8:0:CD30:123:4567::CDEF", 0, 31),
    macro_f_string_static_t_initialize_1("[2001:0DB8:0:CD30:123:4567::CDEF]", 0, 33),
    macro_f_string_static_t_initialize_1("[2001:0DB8:0:CD30:123:4567::CDEF]:80", 0, 36),
    macro_f_string_static_t_initialize_1("2001:0DB8:0:CD30:123::CDEF", 0, 26),
    macro_f_string_static_t_initialize_1("[2001:0DB8:0:CD30:123::CDEF]", 0, 28),
    macro_f_string_static_t_initialize_1("[2001:0DB8:0:CD30:123::CDEF]:80", 0, 31),
    macro_f_string_static_t_initialize_1("2001:0DB8:0:CD30::CDEF", 0, 22),
    macro_f_string_static_t_initialize_1("[2001:0DB8:0:CD30::CDEF]", 0, 24),
    macro_f_string_static_t_initialize_1("[2001:0DB8:0:CD30::CDEF]:80", 0, 27),
    macro_f_string_static_t_initialize_1("2001:0DB8:0::CDEF", 0, 17),
    macro_f_string_static_t_initialize_1("[2001:0DB8:0::CDEF]", 0, 19),
    macro_f_string_static_t_initialize_1("[2001:0DB8:0::CDEF]:80", 0, 22),
    macro_f_string_static_t_initialize_1("2001:0DB8::CDEF", 0, 15),
    macro_f_string_static_t_initialize_1("[2001:0DB8::CDEF]", 0, 17),
    macro_f_string_static_t_initialize_1("[2001:0DB8::CDEF]:80", 0, 20),
    macro_f_string_static_t_initialize_1("2001::CDEF", 0, 10),
    macro_f_string_static_t_initialize_1("[2001::CDEF]", 0, 12),
    macro_f_string_static_t_initialize_1("[2001::CDEF]:80", 0, 15),
    macro_f_string_static_t_initialize_1("2001::0DB8:CDEF", 0, 15),
    macro_f_string_static_t_initialize_1("[2001::0DB8:CDEF]", 0, 17),
    macro_f_string_static_t_initialize_1("[2001::0DB8:CDEF]:80", 0, 20),
    macro_f_string_static_t_initialize_1("2001:0DB8::0:CDEF", 0, 17),
    macro_f_string_static_t_initialize_1("[2001:0DB8::0:CDEF]", 0, 19),
    macro_f_string_static_t_initialize_1("[2001:0DB8::0:CDEF]:80", 0, 22),
    macro_f_string_static_t_initialize_1("2001::0DB8:0:CD30:CDEF", 0, 22),
    macro_f_string_static_t_initialize_1("[2001::0DB8:0:CD30:CDEF]", 0, 24),
    macro_f_string_static_t_initialize_1("[2001::0DB8:0:CD30:CDEF]:80", 0, 27),
    macro_f_string_static_t_initialize_1("2001:0DB8:0:CD30::123:CDEF", 0, 26),
    macro_f_string_static_t_initialize_1("[2001:0DB8:0:CD30::123:CDEF]", 0, 28),
    macro_f_string_static_t_initialize_1("[2001:0DB8:0:CD30::123:CDEF]:80", 0, 31),
    macro_f_string_static_t_initialize_1("2001:0DB8:0:CD30::123:4567:CDEF", 0, 31),
    macro_f_string_static_t_initialize_1("[2001:0DB8:0:CD30::123:4567:CDEF]", 0, 33),
    macro_f_string_static_t_initialize_1("[2001:0DB8:0:CD30::123:4567:CDEF]:80", 0, 36),
  };

  const f_number_unsigned_t ports[] = {
    0,
    0,
    6,
    0,
    0,
    9,
    0,
    0,
    38,
    0,
    0,
    34,
    0,
    0,
    29,
    0,
    0,
    25,
    0,
    0,
    20,
    0,
    0,
    18,
    0,
    0,
    13,
    0,
    0,
    18,
    0,
    0,
    20,
    0,
    0,
    25,
    0,
    0,
    29,
    0,
    0,
    34,
  };

  f_number_unsigned_t port = 0;

  for (uint8_t i = 0; i < 42; ++i) {

    state_data.status = F_okay;
    port = 100000;

    f_network_is_ip_address(ips[i], &port, &state_data);

    assert_int_equal(state_data.status, F_network_version_six);
    assert_int_equal(port, ports[i]);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
