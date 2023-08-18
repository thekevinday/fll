#include "test-network.h"
#include "test-network-from_host_long.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_network_from_host_long__parameter_checking(void **state) {

  {
    const f_status_t status = f_network_from_host_long(0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_network_from_host_long__works(void **state) {

  const uint32_t expect = 100;
  uint32_t to = 0;

  {
    will_return(__wrap_htonl, expect);

    const f_status_t status = f_network_from_host_long(0, &to);

    assert_int_equal(status, F_okay);
    assert_int_equal(to, expect);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
