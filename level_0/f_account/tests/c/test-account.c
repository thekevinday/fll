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

    cmocka_unit_test(test__f_account_id_group_by_name__fails),
    cmocka_unit_test(test__f_account_id_group_by_name__not_found),
    cmocka_unit_test(test__f_account_id_group_by_name__works),

    cmocka_unit_test(test__f_account_id_user_by_name__fails),
    cmocka_unit_test(test__f_account_id_user_by_name__not_found),
    cmocka_unit_test(test__f_account_id_user_by_name__works),

    cmocka_unit_test(test__f_account_name_group_by_id__fails),
    cmocka_unit_test(test__f_account_name_group_by_id__not_found),
    cmocka_unit_test(test__f_account_name_group_by_id__works),

    cmocka_unit_test(test__f_account_name_user_by_id__fails),
    cmocka_unit_test(test__f_account_name_user_by_id__not_found),
    cmocka_unit_test(test__f_account_name_user_by_id__works),

    #ifndef _di_level_0_parameter_checking_
      cmocka_unit_test(test__f_account_by_id__parameter_checking),
      cmocka_unit_test(test__f_account_by_name__parameter_checking),
      cmocka_unit_test(test__f_account_id_group_by_name__parameter_checking),
      cmocka_unit_test(test__f_account_id_user_by_name__parameter_checking),
      cmocka_unit_test(test__f_account_name_group_by_id__parameter_checking),
      cmocka_unit_test(test__f_account_name_user_by_id__parameter_checking),
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
