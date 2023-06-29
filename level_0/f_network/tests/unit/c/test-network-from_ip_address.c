#include "test-network.h"
#include "test-network-from_ip_address.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_network_from_ip_address__fails(void **state) {

  f_network_family_ip_t family = f_network_family_ip_t_initialize;

  int errnos[] = {
    HOST_NOT_FOUND,
    NO_DATA,
    NO_ADDRESS,
    NO_RECOVERY,
    TRY_AGAIN,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_found_not,
    F_data_not,
    F_data_not,
    F_recover_not,
    F_again,
    F_failure,
  };

  for (uint8_t i = 0; i < 6; ++i) {

    struct hostent host;

    will_return(__wrap_gethostbyaddr, true);
    will_return(__wrap_gethostbyaddr, errnos[i]);

    const f_status_t status = f_network_from_ip_address(family, &host);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_network_from_ip_address__parameter_checking(void **state) {

  f_network_family_ip_t family = f_network_family_ip_t_initialize;

  {
    const f_status_t status = f_network_from_ip_address(family, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_network_from_ip_address__returns_data_not(void **state) {

  f_network_family_ip_t family = f_network_family_ip_t_initialize;

  struct hostent host;

  {
    const f_status_t status = f_network_from_ip_address(family, &host);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_network_from_ip_address__works(void **state) {

  f_network_family_ip_t family = f_network_family_ip_t_initialize;

  struct hostent host;
  struct hostent mocked;

  char *mocked_strings[] = {
    "localhost",
    0,
  };

  char *mocked_ips[] = {
    "127.0.0.1",
    "::1",
    0,
  };

  memset(&mocked, 0, sizeof(struct hostent));

  mocked.h_name = mocked_strings[0];
  mocked.h_aliases = mocked_strings;
  mocked.h_addrtype = 1;
  mocked.h_length = 2;
  mocked.h_addr_list = mocked_ips;

  family.type = f_network_family_ip_4_e;

  {
    will_return(__wrap_gethostbyaddr, false);
    will_return(__wrap_gethostbyaddr, &mocked);

    const f_status_t status = f_network_from_ip_address(family, &host);

    assert_int_equal(status, F_none);
    assert_string_equal(host.h_name, mocked.h_name);
    assert_int_equal(host.h_aliases, mocked.h_aliases);
    assert_int_equal(host.h_length, mocked.h_length);
    assert_int_equal(host.h_aliases, mocked.h_aliases);
    assert_int_equal(host.h_aliases[0], mocked.h_aliases[0]);
    assert_int_equal(host.h_addr_list, mocked.h_addr_list);
    assert_int_equal(host.h_addr_list[0], mocked.h_addr_list[0]);
    assert_int_equal(host.h_addr_list[1], mocked.h_addr_list[1]);
  }

  family.type = f_network_family_ip_6_e;

  {
    will_return(__wrap_gethostbyaddr, false);
    will_return(__wrap_gethostbyaddr, &mocked);

    const f_status_t status = f_network_from_ip_address(family, &host);

    assert_int_equal(status, F_none);
    assert_string_equal(host.h_name, mocked.h_name);
    assert_int_equal(host.h_aliases, mocked.h_aliases);
    assert_int_equal(host.h_length, mocked.h_length);
    assert_int_equal(host.h_aliases, mocked.h_aliases);
    assert_int_equal(host.h_aliases[0], mocked.h_aliases[0]);
    assert_int_equal(host.h_addr_list, mocked.h_addr_list);
    assert_int_equal(host.h_addr_list[0], mocked.h_addr_list[0]);
    assert_int_equal(host.h_addr_list[1], mocked.h_addr_list[1]);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
