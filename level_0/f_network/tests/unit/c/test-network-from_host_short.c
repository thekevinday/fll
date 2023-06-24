#include "test-network.h"
#include "test-network-from_host_short.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_network_from_host_short__parameter_checking(void **state) {

  {
    const f_status_t status = f_network_from_host_short(0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_network_from_host_short__works(void **state) {

  const uint16_t expect = 100;
  uint16_t to = 0;

  {
    will_return(__wrap_htons, expect);

    const f_status_t status = f_network_from_host_short(0, &to);

    assert_int_equal(status, F_none);
    assert_int_equal(to, expect);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif