#include "test-network.h"
#include "test-network-from_ip_string.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_network_from_ip_string__fails(void **state) {

  const f_string_static_t ip = macro_f_string_static_t_initialize_1("127.0.0.1", 0, 9);

  int errnos[] = {
    EAFNOSUPPORT,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_support_not,
    F_failure,
  };

  for (uint8_t i = 0; i < 2; ++i) {

    f_network_family_ip_t family = f_network_family_ip_t_initialize;

    family.type = f_network_family_ip_4_e;

    will_return(__wrap_inet_pton, true);
    will_return(__wrap_inet_pton, errnos[i]);

    const f_status_t status = f_network_from_ip_string(ip, &family);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for

  // Should return F_address_not (with error bit) for when non-errno return result of inet_pton() is 0.
  {
    f_network_family_ip_t family = f_network_family_ip_t_initialize;

    family.type = f_network_family_ip_4_e;

    will_return(__wrap_inet_pton, false);
    will_return(__wrap_inet_pton, 0);

    const f_status_t status = f_network_from_ip_string(ip, &family);

    assert_int_equal(status, F_status_set_error(F_address_not));
  }
}

void test__f_network_from_ip_string__parameter_checking(void **state) {

  {
    const f_status_t status = f_network_from_ip_string(f_string_empty_s, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_network_from_ip_string__returns_data_not(void **state) {

  f_network_family_ip_t family = f_network_family_ip_t_initialize;

  const f_string_static_t ip = macro_f_string_static_t_initialize_1("127.0.0.1", 0, 9);

  {
    const f_status_t status = f_network_from_ip_string(ip, &family);

    assert_int_equal(status, F_data_not);
  }

  family.type = f_network_family_ip_4_e;

  {
    const f_status_t status = f_network_from_ip_string(f_string_empty_s, &family);

    assert_int_equal(status, F_data_not);
  }

  family.type = f_network_family_ip_6_e;

  {
    const f_status_t status = f_network_from_ip_string(f_string_empty_s, &family);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_network_from_ip_string__works(void **state) {

  f_network_family_ip_t family = f_network_family_ip_t_initialize;

  const f_string_static_t ip = macro_f_string_static_t_initialize_1("127.0.0.1", 0, 9);

  family.type = f_network_family_ip_4_e;

  {
    will_return(__wrap_inet_pton, false);
    will_return(__wrap_inet_pton, 1);

    const f_status_t status = f_network_from_ip_string(ip, &family);

    assert_int_equal(status, F_okay);
  }

  family.type = f_network_family_ip_6_e;

  {
    will_return(__wrap_inet_pton, false);
    will_return(__wrap_inet_pton, 1);

    const f_status_t status = f_network_from_ip_string(ip, &family);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
