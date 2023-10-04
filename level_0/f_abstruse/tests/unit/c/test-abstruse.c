#include "test-abstruse.h"

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
    cmocka_unit_test(test__f_abstruse_s_delete_callback__fails),
    cmocka_unit_test(test__f_abstruse_s_destroy_callback__fails),
    cmocka_unit_test(test__f_abstruse_ss_destroy_callback__fails),
    cmocka_unit_test(test__f_abstruse_ss_delete_callback__fails),

    cmocka_unit_test(test__f_abstruse_s_delete_callback__works),
    cmocka_unit_test(test__f_abstruse_s_destroy_callback__works),
    cmocka_unit_test(test__f_abstruse_ss_delete_callback__works),
    cmocka_unit_test(test__f_abstruse_ss_destroy_callback__works),

    cmocka_unit_test(test__f_abstruse_maps_delete_callback__fails),
    cmocka_unit_test(test__f_abstruse_maps_destroy_callback__fails),
    cmocka_unit_test(test__f_abstruse_mapss_destroy_callback__fails),
    cmocka_unit_test(test__f_abstruse_mapss_delete_callback__fails),

    cmocka_unit_test(test__f_abstruse_maps_delete_callback__works),
    cmocka_unit_test(test__f_abstruse_maps_destroy_callback__works),
    cmocka_unit_test(test__f_abstruse_mapss_delete_callback__works),
    cmocka_unit_test(test__f_abstruse_mapss_destroy_callback__works),

    #ifndef _di_level_0_parameter_checking_
      // f_abstruse_maps_destroy_callback() doesn't use parameter checking.
      // f_abstruse_maps_delete_callback() doesn't use parameter checking.
      // f_abstruse_mapss_destroy_callback() doesn't use parameter checking.
      // f_abstruse_mapss_delete_callback() doesn't use parameter checking.

      // f_abstruse_s_destroy_callback() doesn't use parameter checking.
      // f_abstruse_s_delete_callback() doesn't use parameter checking.
      // f_abstruse_ss_destroy_callback() doesn't use parameter checking.
      // f_abstruse_ss_delete_callback() doesn't use parameter checking.
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
