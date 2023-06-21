#include "test-network.h"

#ifdef __cplusplus
extern "C" {
#endif

int setup(void **state) {

  return 0;
}

int setdown(void **state) {

  errno = 0;

  return 0;
}

int main(void) {

  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test__f_network_from_host_long__works),
    cmocka_unit_test(test__f_network_from_host_short__works),
    cmocka_unit_test(test__f_network_to_host_long__works),
    cmocka_unit_test(test__f_network_to_host_short__works),

    #ifndef _di_level_0_parameter_checking_
      cmocka_unit_test(test__f_network_from_host_long__parameter_checking),
      cmocka_unit_test(test__f_network_from_host_short__parameter_checking),
      cmocka_unit_test(test__f_network_to_host_long__parameter_checking),
      cmocka_unit_test(test__f_network_to_host_short__parameter_checking),
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
