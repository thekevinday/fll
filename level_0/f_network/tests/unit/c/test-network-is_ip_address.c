#include "test-network.h"
#include "test-network-is_ip_address.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_network_is_ip_address__returns_data_not(void **state) {

  f_state_t state_data = f_state_t_initialize;
  f_range_double_t where = f_range_double_t_initialize;

  {
    state_data.status = F_okay;
    where.start_1 = 1;
    where.start_2 = 1;
    where.stop_1 = 0;
    where.stop_2 = 0;

    f_network_is_ip_address(f_string_empty_s, &where, &state_data);

    assert_int_equal(state_data.status, F_data_not);
    assert_int_equal(where.start_1, 1);
    assert_int_equal(where.stop_1, 0);
    assert_int_equal(where.start_2, 1);
    assert_int_equal(where.stop_2, 0);

  }

  {
    state_data.status = F_okay;

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
    macro_f_string_static_t_initialize_1("[", 0, 1),
  };

  f_range_double_t where = f_range_double_t_initialize;

  for (uint8_t i = 0; i < 8; ++i) {

    state_data.status = F_okay;
    where.start_1 = 1;
    where.start_2 = 1;
    where.stop_1 = 0;
    where.stop_2 = 0;

    f_network_is_ip_address(ips[i], &where, &state_data);

    assert_int_equal(state_data.status, F_false);
    assert_int_equal(where.start_1, 1);
    assert_int_equal(where.stop_1, 0);
    assert_int_equal(where.start_2, 1);
    assert_int_equal(where.stop_2, 0);

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

  const f_range_double_t wheres[] = {
    { .start_1 = 0,  .stop_1 = 8,  .start_2 = 1,  .stop_2 = 0  },
    { .start_1 = 0,  .stop_1 = 11, .start_2 = 1,  .stop_2 = 0  },
    { .start_1 = 0,  .stop_1 = 8,  .start_2 = 10, .stop_2 = 11 },
    { .start_1 = 0,  .stop_1 = 11, .start_2 = 13, .stop_2 = 14 },
  };

  f_range_double_t where = f_range_double_t_initialize;

  for (uint8_t i = 0; i < 4; ++i) {

    state_data.status = F_okay;
    where.start_1 = 1;
    where.start_2 = 1;
    where.stop_1 = 0;
    where.stop_2 = 0;

    f_network_is_ip_address(ips[i], &where, &state_data);

    assert_int_equal(state_data.status, F_network_version_four);
    assert_int_equal(where.start_1, wheres[i].start_1);
    assert_int_equal(where.stop_1, wheres[i].stop_1);
    assert_int_equal(where.start_2, wheres[i].start_2);
    assert_int_equal(where.stop_2, wheres[i].stop_2);

    state_data.status = F_okay;

    f_network_is_ip_address(ips[i], 0, &state_data);

    assert_int_equal(state_data.status, F_network_version_four);
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

  f_range_double_t where = f_range_double_t_initialize;

  for (uint8_t i = 0; i < 17; ++i) {

    state_data.status = F_okay;
    where.start_1 = 1;
    where.start_2 = 1;
    where.stop_1 = 0;
    where.stop_2 = 0;

    f_network_is_ip_address(ips[i], &where, &state_data);

    assert_int_equal(state_data.status, F_network_version_four_not);
    assert_int_equal(where.start_1, 1);
    assert_int_equal(where.stop_1, 0);
    assert_int_equal(where.start_2, 1);
    assert_int_equal(where.stop_2, 0);

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
    macro_f_string_static_t_initialize_1("[:", 0, 2),
    macro_f_string_static_t_initialize_1("[::", 0, 3),
    macro_f_string_static_t_initialize_1("[:/24", 0, 5),
    macro_f_string_static_t_initialize_1("[::/24", 0, 6),
    macro_f_string_static_t_initialize_1("[:/2a", 0, 5),
    macro_f_string_static_t_initialize_1("[::/2a", 0, 6),
    macro_f_string_static_t_initialize_1("[:1/24", 0, 6),
    macro_f_string_static_t_initialize_1("[::1/24", 0, 7),
    macro_f_string_static_t_initialize_1("[:12345", 0, 7),
    macro_f_string_static_t_initialize_1("[::12345", 0, 8),
    macro_f_string_static_t_initialize_1("[:12345/24", 0, 10),
    macro_f_string_static_t_initialize_1("[::12345/24", 0, 11),
    macro_f_string_static_t_initialize_1("[::1/1234", 0, 9),
    macro_f_string_static_t_initialize_1("[::1", 0, 4),
    macro_f_string_static_t_initialize_1("[::1/24", 0, 7),
    macro_f_string_static_t_initialize_1("[:example", 0, 9),
    macro_f_string_static_t_initialize_1("[::example", 0, 10),
    macro_f_string_static_t_initialize_1("[:example/24", 0, 12),
    macro_f_string_static_t_initialize_1("[::example/24", 0, 13),
    macro_f_string_static_t_initialize_1("[:example/2a", 0, 12),
    macro_f_string_static_t_initialize_1("[::example/2a", 0, 13),
    macro_f_string_static_t_initialize_1("[:]", 0, 3),
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
    macro_f_string_static_t_initialize_1("[::example]:80_map", 0, 18),
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
    macro_f_string_static_t_initialize_1("[2001:0DB8:0:CD30:123:4567:89AB:CDEF]:80_map", 0, 44),
    macro_f_string_static_t_initialize_1("[::1]:80not", 0, 11),
    macro_f_string_static_t_initialize_1("[::1/24]:80ton", 0, 14),
    macro_f_string_static_t_initialize_1("[2001:0DB8:0:CD30:123:4567:89AB:CDEF]:80ton", 0, 43),
    macro_f_string_static_t_initialize_1("[2001:0DB8:0:CD30:123:4567::CDEF]:80not", 0, 39),
    macro_f_string_static_t_initialize_1("[2001:0DB8:0:CD30:123::CDEF]:80otn", 0, 34),
    macro_f_string_static_t_initialize_1("[2001:0DB8:0:CD30::CDEF]:80nto", 0, 30),
    macro_f_string_static_t_initialize_1("[2001:0DB8:0::CDEF]:80ttt", 0, 25),
    macro_f_string_static_t_initialize_1("[2001:0DB8::CDEF]:80ooo", 0, 23),
    macro_f_string_static_t_initialize_1("[2001::CDEF]:80nnn", 0, 18),
    macro_f_string_static_t_initialize_1("[2001::0DB8:CDEF]:80_to", 0, 23),
    macro_f_string_static_t_initialize_1("[2001:0DB8::0:CDEF]:80_no", 0, 25),
    macro_f_string_static_t_initialize_1("[2001::0DB8:0:CD30:CDEF]:80*to", 0, 30),
    macro_f_string_static_t_initialize_1("[2001:0DB8:0:CD30::123:4567:CDEF]:80$ot", 0, 39),
  };

  f_range_double_t where = f_range_double_t_initialize;

  for (uint8_t i = 0; i < 112; ++i) {

    state_data.status = F_okay;
    where.start_1 = 1;
    where.start_2 = 1;
    where.stop_1 = 0;
    where.stop_2 = 0;

    f_network_is_ip_address(ips[i], &where, &state_data);

    assert_int_equal(state_data.status, F_network_version_six_not);
    assert_int_equal(where.start_1, 1);
    assert_int_equal(where.stop_1, 0);
    assert_int_equal(where.start_2, 1);
    assert_int_equal(where.stop_2, 0);

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
    macro_f_string_static_t_initialize_1("2001:0DB8:CD30:123:4567:89AB:CDEF", 0, 33),
    macro_f_string_static_t_initialize_1("[2001:0DB8:CD30:123:4567:89AB:CDEF]", 0, 35),
    macro_f_string_static_t_initialize_1("[2001:0DB8:CD30:123:4567:89AB:CDEF]:80", 0, 38),
    macro_f_string_static_t_initialize_1("2001:0DB8:CD30:123:4567::CDEF", 0, 29),
    macro_f_string_static_t_initialize_1("[2001:0DB8:CD30:123:4567::CDEF]", 0, 31),
    macro_f_string_static_t_initialize_1("[2001:0DB8:CD30:123:4567::CDEF]:80", 0, 34),
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
    macro_f_string_static_t_initialize_1("2001:0DB8:CD30::123:4567:CDEF", 0, 29),
    macro_f_string_static_t_initialize_1("[2001:0DB8:CD30::123:4567:CDEF]", 0, 31),
    macro_f_string_static_t_initialize_1("[2001:0DB8:CD30::123:4567:CDEF]:80", 0, 34),
  };

  const f_range_double_t wheres[] = {
    { .start_1 = 2,  .stop_1 = 2,  .start_2 = 1,  .stop_2 = 0  },
    { .start_1 = 3,  .stop_1 = 3,  .start_2 = 1,  .stop_2 = 0  },
    { .start_1 = 3,  .stop_1 = 3,  .start_2 = 6,  .stop_2 = 7  },
    { .start_1 = 2,  .stop_1 = 5,  .start_2 = 1,  .stop_2 = 0  },
    { .start_1 = 3,  .stop_1 = 6,  .start_2 = 1,  .stop_2 = 0  },
    { .start_1 = 3,  .stop_1 = 6,  .start_2 = 9,  .stop_2 = 10 },
    { .start_1 = 0,  .stop_1 = 32, .start_2 = 1,  .stop_2 = 0  },
    { .start_1 = 1,  .stop_1 = 33, .start_2 = 1,  .stop_2 = 0  },
    { .start_1 = 1,  .stop_1 = 33, .start_2 = 36, .stop_2 = 37 },
    { .start_1 = 0,  .stop_1 = 28, .start_2 = 1,  .stop_2 = 0  },
    { .start_1 = 1,  .stop_1 = 29, .start_2 = 1,  .stop_2 = 0  },
    { .start_1 = 1,  .stop_1 = 29, .start_2 = 32, .stop_2 = 33 },
    { .start_1 = 0,  .stop_1 = 25, .start_2 = 1,  .stop_2 = 0  },
    { .start_1 = 1,  .stop_1 = 26, .start_2 = 1,  .stop_2 = 0  },
    { .start_1 = 1,  .stop_1 = 26, .start_2 = 29, .stop_2 = 30 },
    { .start_1 = 0,  .stop_1 = 21, .start_2 = 1,  .stop_2 = 0  },
    { .start_1 = 1,  .stop_1 = 22, .start_2 = 1,  .stop_2 = 0  },
    { .start_1 = 1,  .stop_1 = 22, .start_2 = 25, .stop_2 = 26 },
    { .start_1 = 0,  .stop_1 = 16, .start_2 = 1,  .stop_2 = 0  },
    { .start_1 = 1,  .stop_1 = 17, .start_2 = 1,  .stop_2 = 0  },
    { .start_1 = 1,  .stop_1 = 17, .start_2 = 20, .stop_2 = 21 },
    { .start_1 = 0,  .stop_1 = 14, .start_2 = 1,  .stop_2 = 0  },
    { .start_1 = 1,  .stop_1 = 15, .start_2 = 1,  .stop_2 = 0  },
    { .start_1 = 1,  .stop_1 = 15, .start_2 = 18, .stop_2 = 19 },
    { .start_1 = 0,  .stop_1 = 9,  .start_2 = 1,  .stop_2 = 0  },
    { .start_1 = 1,  .stop_1 = 10, .start_2 = 1,  .stop_2 = 0  },
    { .start_1 = 1,  .stop_1 = 10, .start_2 = 13, .stop_2 = 14 },
    { .start_1 = 0,  .stop_1 = 14, .start_2 = 1,  .stop_2 = 0  },
    { .start_1 = 1,  .stop_1 = 15, .start_2 = 1,  .stop_2 = 0  },
    { .start_1 = 1,  .stop_1 = 15, .start_2 = 18, .stop_2 = 19 },
    { .start_1 = 0,  .stop_1 = 16, .start_2 = 1,  .stop_2 = 0  },
    { .start_1 = 1,  .stop_1 = 17, .start_2 = 1,  .stop_2 = 0  },
    { .start_1 = 1,  .stop_1 = 17, .start_2 = 20, .stop_2 = 21 },
    { .start_1 = 0,  .stop_1 = 21, .start_2 = 1,  .stop_2 = 0  },
    { .start_1 = 1,  .stop_1 = 22, .start_2 = 1,  .stop_2 = 0  },
    { .start_1 = 1,  .stop_1 = 22, .start_2 = 25, .stop_2 = 26  },
    { .start_1 = 0,  .stop_1 = 25, .start_2 = 1,  .stop_2 = 0  },
    { .start_1 = 1,  .stop_1 = 26, .start_2 = 1,  .stop_2 = 0  },
    { .start_1 = 1,  .stop_1 = 26, .start_2 = 29, .stop_2 = 30 },
    { .start_1 = 0,  .stop_1 = 28, .start_2 = 1,  .stop_2 = 0  },
    { .start_1 = 1,  .stop_1 = 29, .start_2 = 1,  .stop_2 = 0  },
    { .start_1 = 1,  .stop_1 = 29, .start_2 = 32, .stop_2 = 33 },
  };

  f_range_double_t where = f_range_double_t_initialize;

  for (uint8_t i = 0; i < 42; ++i) {

    state_data.status = F_okay;
    where.start_1 = 1;
    where.start_2 = 1;
    where.stop_1 = 0;
    where.stop_2 = 0;

    f_network_is_ip_address(ips[i], &where, &state_data);

    assert_int_equal(state_data.status, F_network_version_six);
    assert_int_equal(where.start_1, wheres[i].start_1);
    assert_int_equal(where.stop_1, wheres[i].stop_1);
    assert_int_equal(where.start_2, wheres[i].start_2);
    assert_int_equal(where.stop_2, wheres[i].stop_2);

    state_data.status = F_okay;

    f_network_is_ip_address(ips[i], 0, &state_data);

    assert_int_equal(state_data.status, F_network_version_six);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
