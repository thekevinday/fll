#include "test-network.h"
#include "test-network-to_ip_string.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_network_to_ip_string__fails(void **state) {

  f_network_family_ip_t family = f_network_family_ip_t_initialize;
  f_string_dynamic_t ip = f_string_dynamic_t_initialize;

  int errnos[] = {
    EAFNOSUPPORT,
    ENOSPC,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_support_not,
    F_space_not,
    F_failure,
  };

  for (uint8_t i = 0; i < 3; ++i) {

    will_return(__wrap_inet_pton, true);
    will_return(__wrap_inet_pton, errnos[i]);

    const f_status_t status = f_network_to_ip_string(family, &ip);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for

  free(ip.string);
}

void test__f_network_to_ip_string__parameter_checking(void **state) {

  f_network_family_ip_t family = f_network_family_ip_t_initialize;

  {
    const f_status_t status = f_network_to_ip_string(family, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_network_to_ip_string__returns_data_not(void **state) {

  f_network_family_ip_t family = f_network_family_ip_t_initialize;
  f_string_dynamic_t ip = f_string_dynamic_t_initialize;

  {
    const f_status_t status = f_network_to_ip_string(family, &ip);

    assert_int_equal(status, F_data_not);
  }

  free(ip.string);
}

void test__f_network_to_ip_string__works(void **state) {

  f_network_family_ip_t family = f_network_family_ip_t_initialize;

  f_string_dynamic_t ip = f_string_dynamic_t_initialize;

  const f_string_static_t expect = macro_f_string_static_t_initialize_1("127.0.0.1", 0, 9);

  family.type = f_network_family_ip_4_e;

  {
    will_return(__wrap_inet_ntop, false);
    will_return(__wrap_inet_ntop, expect.string);
    will_return(__wrap_inet_ntop, expect.used);

    const f_status_t status = f_network_to_ip_string(family, &ip);

    assert_int_equal(status, F_none);
    assert_int_equal(ip.used, expect.used);
    assert_string_equal(ip.string, expect.string);
  }

  free(ip.string);

  family.type = f_network_family_ip_6_e;
  ip.used = 0;

  {
    will_return(__wrap_inet_ntop, false);
    will_return(__wrap_inet_ntop, expect.string);
    will_return(__wrap_inet_ntop, expect.used);

    const f_status_t status = f_network_to_ip_string(family, &ip);

    assert_int_equal(status, F_none);
    assert_int_equal(ip.used, expect.used);
    assert_string_equal(ip.string, expect.string);
  }

  free(ip.string);
}

#ifdef __cplusplus
} // extern "C"
#endif
