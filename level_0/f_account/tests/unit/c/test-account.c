#include "test-account.h"

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
    cmocka_unit_test(test__f_account_by_id__fails),
    cmocka_unit_test(test__f_account_by_id__not_found),
    cmocka_unit_test(test__f_account_by_id__works),

    cmocka_unit_test(test__f_account_by_name__fails),
    cmocka_unit_test(test__f_account_by_name__not_found),
    cmocka_unit_test(test__f_account_by_name__works),

    cmocka_unit_test(test__f_account_group_id_by_name__fails),
    cmocka_unit_test(test__f_account_group_id_by_name__not_found),
    cmocka_unit_test(test__f_account_group_id_by_name__works),

    cmocka_unit_test(test__f_account_group_name_by_id__fails),
    cmocka_unit_test(test__f_account_group_name_by_id__not_found),
    cmocka_unit_test(test__f_account_group_name_by_id__works),

    cmocka_unit_test(test__f_account_id_by_name__fails),
    cmocka_unit_test(test__f_account_id_by_name__not_found),
    cmocka_unit_test(test__f_account_id_by_name__works),

    cmocka_unit_test(test__f_account_name_by_id__fails),
    cmocka_unit_test(test__f_account_name_by_id__not_found),
    cmocka_unit_test(test__f_account_name_by_id__works),

    cmocka_unit_test(test__f_accounts_adjust_callback__fails),
    cmocka_unit_test(test__f_accounts_resize_callback__fails),

    cmocka_unit_test(test__f_accounts_adjust_callback__works),
    cmocka_unit_test(test__f_accounts_resize_callback__works),

    cmocka_unit_test(test__f_accounts_append_all__returns_data_not),

    cmocka_unit_test(test__f_accounts_append__works),
    cmocka_unit_test(test__f_accounts_append_all__works),

    cmocka_unit_test(test__f_accountss_append__returns_data_not),
    cmocka_unit_test(test__f_accountss_append_all__returns_data_not),

    cmocka_unit_test(test__f_accountss_append__works),
    cmocka_unit_test(test__f_accountss_append_all__works),

    #ifndef _di_level_0_parameter_checking_
      cmocka_unit_test(test__f_account_by_id__parameter_checking),
      cmocka_unit_test(test__f_account_by_name__parameter_checking),
      cmocka_unit_test(test__f_account_group_id_by_name__parameter_checking),
      cmocka_unit_test(test__f_account_group_name_by_id__parameter_checking),
      cmocka_unit_test(test__f_account_id_by_name__parameter_checking),
      cmocka_unit_test(test__f_account_name_by_id__parameter_checking),

      // f_accounts_adjust_callback() doesn't use parameter checking.
      // f_accounts_resize_callback() doesn't use parameter checking.

      cmocka_unit_test(test__f_accounts_append__parameter_checking),
      cmocka_unit_test(test__f_accounts_append_all__parameter_checking),

      cmocka_unit_test(test__f_accountss_append__parameter_checking),
      cmocka_unit_test(test__f_accountss_append_all__parameter_checking),
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
