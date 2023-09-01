#include "test-directory.h"

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
    cmocka_unit_test(test__f_directory_create__fails),
    cmocka_unit_test(test__f_directory_create__returns_data_not),
    cmocka_unit_test(test__f_directory_create__works),

    cmocka_unit_test(test__f_directory_create_at__fails),
    cmocka_unit_test(test__f_directory_create_at__returns_data_not),
    cmocka_unit_test(test__f_directory_create_at__works),

    cmocka_unit_test(test__f_directory_exists__fails),
    cmocka_unit_test(test__f_directory_exists__returns_data_not),
    cmocka_unit_test(test__f_directory_exists__returns_false),
    cmocka_unit_test(test__f_directory_exists__returns_true),

    cmocka_unit_test(test__f_directory_exists_at__fails),
    cmocka_unit_test(test__f_directory_exists_at__returns_data_not),
    cmocka_unit_test(test__f_directory_exists_at__returns_false),
    cmocka_unit_test(test__f_directory_exists_at__returns_true),

    cmocka_unit_test(test__f_directory_is__fails),
    cmocka_unit_test(test__f_directory_is__returns_data_not),
    cmocka_unit_test(test__f_directory_is__returns_false),
    cmocka_unit_test(test__f_directory_is__returns_true),

    cmocka_unit_test(test__f_directory_is_at__fails),
    cmocka_unit_test(test__f_directory_is_at__returns_data_not),
    cmocka_unit_test(test__f_directory_is_at__returns_false),
    cmocka_unit_test(test__f_directory_is_at__returns_true),

    cmocka_unit_test(test__f_directory_list__fails),
    cmocka_unit_test(test__f_directory_list__returns_data_not),
    cmocka_unit_test(test__f_directory_list__returns_directory_empty),
    cmocka_unit_test(test__f_directory_list__works),

    cmocka_unit_test(test__f_directory_open__fails),
    cmocka_unit_test(test__f_directory_open__returns_data_not),
    cmocka_unit_test(test__f_directory_open__works),

    cmocka_unit_test(test__f_directory_open_at__fails),
    cmocka_unit_test(test__f_directory_open_at__returns_data_not),
    cmocka_unit_test(test__f_directory_open_at__works),

    cmocka_unit_test(test__f_directory_remove__fails),
    cmocka_unit_test(test__f_directory_remove__returns_data_not),
    cmocka_unit_test(test__f_directory_remove__works),

    cmocka_unit_test(test__f_directory_remove_custom__fails),
    cmocka_unit_test(test__f_directory_remove_custom__returns_data_not),
    cmocka_unit_test(test__f_directory_remove_custom__works),

    cmocka_unit_test(test__f_directory_listings_delete_callback__fails),
    cmocka_unit_test(test__f_directory_listings_destroy_callback__fails),
    cmocka_unit_test(test__f_directory_listingss_delete_callback__fails),
    cmocka_unit_test(test__f_directory_listingss_destroy_callback__fails),

    cmocka_unit_test(test__f_directory_listings_delete_callback__works),
    cmocka_unit_test(test__f_directory_listings_destroy_callback__works),
    cmocka_unit_test(test__f_directory_listingss_delete_callback__works),
    cmocka_unit_test(test__f_directory_listingss_destroy_callback__works),

    cmocka_unit_test(test__f_directory_recurse_dos_delete_callback__fails),
    cmocka_unit_test(test__f_directory_recurse_dos_destroy_callback__fails),
    cmocka_unit_test(test__f_directory_recurse_doss_delete_callback__fails),
    cmocka_unit_test(test__f_directory_recurse_doss_destroy_callback__fails),

    cmocka_unit_test(test__f_directory_recurse_dos_delete_callback__works),
    cmocka_unit_test(test__f_directory_recurse_dos_destroy_callback__works),
    cmocka_unit_test(test__f_directory_recurse_doss_delete_callback__works),
    cmocka_unit_test(test__f_directory_recurse_doss_destroy_callback__works),

    cmocka_unit_test(test__f_directory_statuss_delete_callback__fails),
    cmocka_unit_test(test__f_directory_statuss_destroy_callback__fails),
    cmocka_unit_test(test__f_directory_statusss_delete_callback__fails),
    cmocka_unit_test(test__f_directory_statusss_destroy_callback__fails),

    cmocka_unit_test(test__f_directory_statuss_delete_callback__works),
    cmocka_unit_test(test__f_directory_statuss_destroy_callback__works),
    cmocka_unit_test(test__f_directory_statusss_delete_callback__works),
    cmocka_unit_test(test__f_directory_statusss_destroy_callback__works),

    cmocka_unit_test(test__f_directory_touch__fails),
    cmocka_unit_test(test__f_directory_touch__returns_data_not),
    cmocka_unit_test(test__f_directory_touch__works),

    cmocka_unit_test(test__f_directory_touch_at__fails),
    cmocka_unit_test(test__f_directory_touch_at__returns_data_not),
    cmocka_unit_test(test__f_directory_touch_at__works),

    #ifndef _di_level_0_parameter_checking_
      // f_directory_create() doesn't use parameter checking.
      // f_directory_create_at() doesn't use parameter checking.
      // f_directory_exists() doesn't use parameter checking.
      // f_directory_exists_at() doesn't use parameter checking.
      // f_directory_is() doesn't use parameter checking.
      // f_directory_is_at() doesn't use parameter checking.
      cmocka_unit_test(test__f_directory_list__parameter_checking),
      cmocka_unit_test(test__f_directory_open__parameter_checking),
      cmocka_unit_test(test__f_directory_open_at__parameter_checking),
      cmocka_unit_test(test__f_directory_remove__parameter_checking),
      cmocka_unit_test(test__f_directory_remove_custom__parameter_checking),
      // f_directory_touch() doesn't use parameter checking.
      // f_directory_touch_at() doesn't use parameter checking.

      // f_directory_listings_delete_callback() doesn't use parameter checking.
      // f_directory_listings_destroy_callback() doesn't use parameter checking.
      // f_directory_listingss_delete_callback() doesn't use parameter checking.
      // f_directory_listingss_destroy_callback() doesn't use parameter checking.
      // f_directory_recurse_dos_delete_callback() doesn't use parameter checking.
      // f_directory_recurse_dos_destroy_callback() doesn't use parameter checking.
      // f_directory_recurse_doss_delete_callback() doesn't use parameter checking.
      // f_directory_recurse_doss_destroy_callback() doesn't use parameter checking.
      // f_directory_statuss_delete_callback() doesn't use parameter checking.
      // f_directory_statuss_destroy_callback() doesn't use parameter checking.
      // f_directory_statusss_delete_callback() doesn't use parameter checking.
      // f_directory_statusss_destroy_callback() doesn't use parameter checking.
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
