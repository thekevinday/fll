#include "test-print.h"

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
    cmocka_unit_test(test__f_print__fails),
    cmocka_unit_test(test__f_print__returns_data_not),
    cmocka_unit_test(test__f_print__works),

    cmocka_unit_test(test__f_print_character__fails),
    cmocka_unit_test(test__f_print_character__works),

    cmocka_unit_test(test__f_print_character_safely__fails),
    cmocka_unit_test(test__f_print_character_safely__returns_utf),
    cmocka_unit_test(test__f_print_character_safely__works),

    cmocka_unit_test(test__f_print_character_safely_get__returns_character_control),
    cmocka_unit_test(test__f_print_character_safely_get__returns_character_delete),
    cmocka_unit_test(test__f_print_character_safely_get__returns_character_unknown),
    cmocka_unit_test(test__f_print_character_safely_get__returns_empty),

    cmocka_unit_test(test__f_print_dynamic__fails),
    cmocka_unit_test(test__f_print_dynamic__returns_data_not),
    cmocka_unit_test(test__f_print_dynamic__works),

    cmocka_unit_test(test__f_print_dynamic_partial__fails),
    cmocka_unit_test(test__f_print_dynamic_partial__returns_data_not),
    cmocka_unit_test(test__f_print_dynamic_partial__works),

    cmocka_unit_test(test__f_print_dynamic_partial_raw__fails),
    cmocka_unit_test(test__f_print_dynamic_partial_raw__returns_data_not),
    cmocka_unit_test(test__f_print_dynamic_partial_raw__works),

    cmocka_unit_test(test__f_print_dynamic_partial_raw_safely__fails),
    cmocka_unit_test(test__f_print_dynamic_partial_raw_safely__returns_data_not),
    cmocka_unit_test(test__f_print_dynamic_partial_raw_safely__works),

    cmocka_unit_test(test__f_print_dynamic_partial_safely__fails),
    cmocka_unit_test(test__f_print_dynamic_partial_safely__returns_data_not),
    cmocka_unit_test(test__f_print_dynamic_partial_safely__works),

    cmocka_unit_test(test__f_print_dynamic_raw__fails),
    cmocka_unit_test(test__f_print_dynamic_raw__returns_data_not),
    cmocka_unit_test(test__f_print_dynamic_raw__works),

    cmocka_unit_test(test__f_print_dynamic_raw_safely__fails),
    cmocka_unit_test(test__f_print_dynamic_raw_safely__returns_data_not),
    cmocka_unit_test(test__f_print_dynamic_raw_safely__works),

    cmocka_unit_test(test__f_print_dynamic_safely__fails),
    cmocka_unit_test(test__f_print_dynamic_safely__returns_data_not),
    cmocka_unit_test(test__f_print_dynamic_safely__works),

    cmocka_unit_test(test__f_print_except__fails),
    cmocka_unit_test(test__f_print_except__returns_data_not),
    cmocka_unit_test(test__f_print_except__works),

    cmocka_unit_test(test__f_print_except_dynamic__fails),
    cmocka_unit_test(test__f_print_except_dynamic__returns_data_not),
    cmocka_unit_test(test__f_print_except_dynamic__works),

    cmocka_unit_test(test__f_print_except_dynamic_partial__fails),
    cmocka_unit_test(test__f_print_except_dynamic_partial__returns_data_not),
    cmocka_unit_test(test__f_print_except_dynamic_partial__works),

    cmocka_unit_test(test__f_print_except_dynamic_partial_raw__fails),
    cmocka_unit_test(test__f_print_except_dynamic_partial_raw__returns_data_not),
    cmocka_unit_test(test__f_print_except_dynamic_partial_raw__works),

    cmocka_unit_test(test__f_print_except_dynamic_partial_raw_safely__fails),
    cmocka_unit_test(test__f_print_except_dynamic_partial_raw_safely__returns_data_not),
    cmocka_unit_test(test__f_print_except_dynamic_partial_raw_safely__works),

    cmocka_unit_test(test__f_print_except_dynamic_partial_safely__fails),
    cmocka_unit_test(test__f_print_except_dynamic_partial_safely__returns_data_not),
    cmocka_unit_test(test__f_print_except_dynamic_partial_safely__works),

    cmocka_unit_test(test__f_print_except_dynamic_raw__fails),
    cmocka_unit_test(test__f_print_except_dynamic_raw__returns_data_not),
    cmocka_unit_test(test__f_print_except_dynamic_raw__works),

    cmocka_unit_test(test__f_print_except_dynamic_raw_safely__fails),
    cmocka_unit_test(test__f_print_except_dynamic_raw_safely__returns_data_not),
    cmocka_unit_test(test__f_print_except_dynamic_raw_safely__works),

    cmocka_unit_test(test__f_print_except_dynamic_safely__fails),
    cmocka_unit_test(test__f_print_except_dynamic_safely__returns_data_not),
    cmocka_unit_test(test__f_print_except_dynamic_safely__works),

    cmocka_unit_test(test__f_print_except_in__fails),
    cmocka_unit_test(test__f_print_except_in__returns_data_not),
    cmocka_unit_test(test__f_print_except_in__works),

    cmocka_unit_test(test__f_print_except_in_dynamic__fails),
    cmocka_unit_test(test__f_print_except_in_dynamic__returns_data_not),
    cmocka_unit_test(test__f_print_except_in_dynamic__works),

    cmocka_unit_test(test__f_print_except_in_dynamic_partial__fails),
    cmocka_unit_test(test__f_print_except_in_dynamic_partial__returns_data_not),
    cmocka_unit_test(test__f_print_except_in_dynamic_partial__works),

    cmocka_unit_test(test__f_print_except_in_dynamic_partial_raw__fails),
    cmocka_unit_test(test__f_print_except_in_dynamic_partial_raw__returns_data_not),
    cmocka_unit_test(test__f_print_except_in_dynamic_partial_raw__works),

    cmocka_unit_test(test__f_print_except_in_dynamic_partial_raw_safely__fails),
    cmocka_unit_test(test__f_print_except_in_dynamic_partial_raw_safely__returns_data_not),
    cmocka_unit_test(test__f_print_except_in_dynamic_partial_raw_safely__works),

    cmocka_unit_test(test__f_print_except_in_dynamic_partial_safely__fails),
    cmocka_unit_test(test__f_print_except_in_dynamic_partial_safely__returns_data_not),
    cmocka_unit_test(test__f_print_except_in_dynamic_partial_safely__works),

    cmocka_unit_test(test__f_print_except_in_dynamic_raw__fails),
    cmocka_unit_test(test__f_print_except_in_dynamic_raw__returns_data_not),
    cmocka_unit_test(test__f_print_except_in_dynamic_raw__works),

    cmocka_unit_test(test__f_print_except_in_dynamic_raw_safely__fails),
    cmocka_unit_test(test__f_print_except_in_dynamic_raw_safely__returns_data_not),
    cmocka_unit_test(test__f_print_except_in_dynamic_raw_safely__works),

    cmocka_unit_test(test__f_print_except_in_dynamic_safely__fails),
    cmocka_unit_test(test__f_print_except_in_dynamic_safely__returns_data_not),
    cmocka_unit_test(test__f_print_except_in_dynamic_safely__works),

    cmocka_unit_test(test__f_print_except_in_raw__fails),
    cmocka_unit_test(test__f_print_except_in_raw__returns_data_not),
    cmocka_unit_test(test__f_print_except_in_raw__works),

    cmocka_unit_test(test__f_print_except_in_raw_safely__fails),
    cmocka_unit_test(test__f_print_except_in_raw_safely__returns_data_not),
    cmocka_unit_test(test__f_print_except_in_raw_safely__works),

    cmocka_unit_test(test__f_print_except_in_safely__fails),
    cmocka_unit_test(test__f_print_except_in_safely__returns_data_not),
    cmocka_unit_test(test__f_print_except_in_safely__works),

    cmocka_unit_test(test__f_print_except_raw__fails),
    cmocka_unit_test(test__f_print_except_raw__returns_data_not),
    cmocka_unit_test(test__f_print_except_raw__works),

    cmocka_unit_test(test__f_print_except_raw_safely__fails),
    cmocka_unit_test(test__f_print_except_raw_safely__returns_data_not),
    cmocka_unit_test(test__f_print_except_raw_safely__works),

    cmocka_unit_test(test__f_print_except_safely__fails),
    cmocka_unit_test(test__f_print_except_safely__returns_data_not),
    cmocka_unit_test(test__f_print_except_safely__works),

    cmocka_unit_test(test__f_print_raw__fails),
    cmocka_unit_test(test__f_print_raw__returns_data_not),
    cmocka_unit_test(test__f_print_raw__works),

    cmocka_unit_test(test__f_print_raw_safely__fails),
    cmocka_unit_test(test__f_print_raw_safely__returns_data_not),
    cmocka_unit_test(test__f_print_raw_safely__works),

    cmocka_unit_test(test__f_print_raw_terminated__fails),
    cmocka_unit_test(test__f_print_raw_terminated__returns_data_not),
    cmocka_unit_test(test__f_print_raw_terminated__works),

    cmocka_unit_test(test__f_print_safely__fails),
    cmocka_unit_test(test__f_print_safely__returns_data_not),
    cmocka_unit_test(test__f_print_safely__works),

    cmocka_unit_test(test__f_print_safely_get__returns_character_control),
    cmocka_unit_test(test__f_print_safely_get__returns_character_delete),
    cmocka_unit_test(test__f_print_safely_get__returns_character_unknown),
    cmocka_unit_test(test__f_print_safely_get__returns_empty),

    cmocka_unit_test(test__f_print_safely_terminated__fails),
    cmocka_unit_test(test__f_print_safely_terminated__returns_data_not),
    cmocka_unit_test(test__f_print_safely_terminated__works),

    cmocka_unit_test(test__f_print_terminated__fails),
    cmocka_unit_test(test__f_print_terminated__returns_data_not),
    cmocka_unit_test(test__f_print_terminated__works),

    cmocka_unit_test(test__f_print_to__fails),
    cmocka_unit_test(test__f_print_to__returns_data_not),
    cmocka_unit_test(test__f_print_to__works),

    cmocka_unit_test(test__f_print_to_character__fails),
    cmocka_unit_test(test__f_print_to_character__works),

    cmocka_unit_test(test__f_print_to_character_safely__fails),
    cmocka_unit_test(test__f_print_to_character_safely__returns_utf),
    cmocka_unit_test(test__f_print_to_character_safely__works),

    cmocka_unit_test(test__f_print_to_dynamic__fails),
    cmocka_unit_test(test__f_print_to_dynamic__returns_data_not),
    cmocka_unit_test(test__f_print_to_dynamic__works),

    cmocka_unit_test(test__f_print_to_dynamic_partial__fails),
    cmocka_unit_test(test__f_print_to_dynamic_partial__returns_data_not),
    cmocka_unit_test(test__f_print_to_dynamic_partial__works),

    cmocka_unit_test(test__f_print_to_dynamic_partial_raw__fails),
    cmocka_unit_test(test__f_print_to_dynamic_partial_raw__returns_data_not),
    cmocka_unit_test(test__f_print_to_dynamic_partial_raw__works),

    cmocka_unit_test(test__f_print_to_dynamic_partial_raw_safely__fails),
    cmocka_unit_test(test__f_print_to_dynamic_partial_raw_safely__returns_data_not),
    cmocka_unit_test(test__f_print_to_dynamic_partial_raw_safely__works),

    cmocka_unit_test(test__f_print_to_dynamic_partial_safely__fails),
    cmocka_unit_test(test__f_print_to_dynamic_partial_safely__returns_data_not),
    cmocka_unit_test(test__f_print_to_dynamic_partial_safely__works),

    cmocka_unit_test(test__f_print_to_dynamic_raw__fails),
    cmocka_unit_test(test__f_print_to_dynamic_raw__returns_data_not),
    cmocka_unit_test(test__f_print_to_dynamic_raw__works),

    cmocka_unit_test(test__f_print_to_dynamic_raw_safely__fails),
    cmocka_unit_test(test__f_print_to_dynamic_raw_safely__returns_data_not),
    cmocka_unit_test(test__f_print_to_dynamic_raw_safely__works),

    cmocka_unit_test(test__f_print_to_dynamic_safely__fails),
    cmocka_unit_test(test__f_print_to_dynamic_safely__returns_data_not),
    cmocka_unit_test(test__f_print_to_dynamic_safely__works),

    cmocka_unit_test(test__f_print_to_except__fails),
    cmocka_unit_test(test__f_print_to_except__returns_data_not),
    cmocka_unit_test(test__f_print_to_except__works),

    cmocka_unit_test(test__f_print_to_except_dynamic__fails),
    cmocka_unit_test(test__f_print_to_except_dynamic__returns_data_not),
    cmocka_unit_test(test__f_print_to_except_dynamic__works),

    cmocka_unit_test(test__f_print_to_except_dynamic_partial__fails),
    cmocka_unit_test(test__f_print_to_except_dynamic_partial__returns_data_not),
    cmocka_unit_test(test__f_print_to_except_dynamic_partial__works),

    cmocka_unit_test(test__f_print_to_except_dynamic_partial_raw__fails),
    cmocka_unit_test(test__f_print_to_except_dynamic_partial_raw__returns_data_not),
    cmocka_unit_test(test__f_print_to_except_dynamic_partial_raw__works),

    cmocka_unit_test(test__f_print_to_except_dynamic_partial_raw_safely__fails),
    cmocka_unit_test(test__f_print_to_except_dynamic_partial_raw_safely__returns_data_not),
    cmocka_unit_test(test__f_print_to_except_dynamic_partial_raw_safely__works),

    cmocka_unit_test(test__f_print_to_except_dynamic_partial_safely__fails),
    cmocka_unit_test(test__f_print_to_except_dynamic_partial_safely__returns_data_not),
    cmocka_unit_test(test__f_print_to_except_dynamic_partial_safely__works),

    cmocka_unit_test(test__f_print_to_except_dynamic_raw__fails),
    cmocka_unit_test(test__f_print_to_except_dynamic_raw__returns_data_not),
    cmocka_unit_test(test__f_print_to_except_dynamic_raw__works),

    cmocka_unit_test(test__f_print_to_except_dynamic_raw_safely__fails),
    cmocka_unit_test(test__f_print_to_except_dynamic_raw_safely__returns_data_not),
    cmocka_unit_test(test__f_print_to_except_dynamic_raw_safely__works),

    cmocka_unit_test(test__f_print_to_except_dynamic_safely__fails),
    cmocka_unit_test(test__f_print_to_except_dynamic_safely__returns_data_not),
    cmocka_unit_test(test__f_print_to_except_dynamic_safely__works),

    cmocka_unit_test(test__f_print_to_except_in__fails),
    cmocka_unit_test(test__f_print_to_except_in__returns_data_not),
    cmocka_unit_test(test__f_print_to_except_in__works),

    cmocka_unit_test(test__f_print_to_except_in_dynamic__fails),
    cmocka_unit_test(test__f_print_to_except_in_dynamic__returns_data_not),
    cmocka_unit_test(test__f_print_to_except_in_dynamic__works),

    cmocka_unit_test(test__f_print_to_except_in_dynamic_partial__fails),
    cmocka_unit_test(test__f_print_to_except_in_dynamic_partial__returns_data_not),
    cmocka_unit_test(test__f_print_to_except_in_dynamic_partial__works),

    cmocka_unit_test(test__f_print_to_except_in_dynamic_partial_raw__fails),
    cmocka_unit_test(test__f_print_to_except_in_dynamic_partial_raw__returns_data_not),
    cmocka_unit_test(test__f_print_to_except_in_dynamic_partial_raw__works),

    cmocka_unit_test(test__f_print_to_except_in_dynamic_partial_raw_safely__fails),
    cmocka_unit_test(test__f_print_to_except_in_dynamic_partial_raw_safely__returns_data_not),
    cmocka_unit_test(test__f_print_to_except_in_dynamic_partial_raw_safely__works),

    cmocka_unit_test(test__f_print_to_except_in_dynamic_partial_safely__fails),
    cmocka_unit_test(test__f_print_to_except_in_dynamic_partial_safely__returns_data_not),
    cmocka_unit_test(test__f_print_to_except_in_dynamic_partial_safely__works),

    cmocka_unit_test(test__f_print_to_except_in_dynamic_raw__fails),
    cmocka_unit_test(test__f_print_to_except_in_dynamic_raw__returns_data_not),
    cmocka_unit_test(test__f_print_to_except_in_dynamic_raw__works),

    cmocka_unit_test(test__f_print_to_except_in_dynamic_raw_safely__fails),
    cmocka_unit_test(test__f_print_to_except_in_dynamic_raw_safely__returns_data_not),
    cmocka_unit_test(test__f_print_to_except_in_dynamic_raw_safely__works),

    cmocka_unit_test(test__f_print_to_except_in_dynamic_safely__fails),
    cmocka_unit_test(test__f_print_to_except_in_dynamic_safely__returns_data_not),
    cmocka_unit_test(test__f_print_to_except_in_dynamic_safely__works),

    cmocka_unit_test(test__f_print_to_except_in_raw__fails),
    cmocka_unit_test(test__f_print_to_except_in_raw__returns_data_not),
    cmocka_unit_test(test__f_print_to_except_in_raw__works),

    cmocka_unit_test(test__f_print_to_except_in_raw_safely__fails),
    cmocka_unit_test(test__f_print_to_except_in_raw_safely__returns_data_not),
    cmocka_unit_test(test__f_print_to_except_in_raw_safely__works),

    cmocka_unit_test(test__f_print_to_except_in_safely__fails),
    cmocka_unit_test(test__f_print_to_except_in_safely__returns_data_not),
    cmocka_unit_test(test__f_print_to_except_in_safely__works),

    cmocka_unit_test(test__f_print_to_except_raw__fails),
    cmocka_unit_test(test__f_print_to_except_raw__returns_data_not),
    cmocka_unit_test(test__f_print_to_except_raw__works),

    cmocka_unit_test(test__f_print_to_except_raw_safely__fails),
    cmocka_unit_test(test__f_print_to_except_raw_safely__returns_data_not),
    cmocka_unit_test(test__f_print_to_except_raw_safely__works),

    cmocka_unit_test(test__f_print_to_except_safely__fails),
    cmocka_unit_test(test__f_print_to_except_safely__returns_data_not),
    cmocka_unit_test(test__f_print_to_except_safely__works),

    cmocka_unit_test(test__f_print_to_raw__fails),
    cmocka_unit_test(test__f_print_to_raw__returns_data_not),
    cmocka_unit_test(test__f_print_to_raw__works),

    cmocka_unit_test(test__f_print_to_raw_safely__fails),
    cmocka_unit_test(test__f_print_to_raw_safely__returns_data_not),
    cmocka_unit_test(test__f_print_to_raw_safely__works),

    cmocka_unit_test(test__f_print_to_raw_terminated__fails),
    cmocka_unit_test(test__f_print_to_raw_terminated__returns_data_not),
    cmocka_unit_test(test__f_print_to_raw_terminated__works),

    cmocka_unit_test(test__f_print_to_safely__fails),
    cmocka_unit_test(test__f_print_to_safely__returns_data_not),
    cmocka_unit_test(test__f_print_to_safely__works),

    cmocka_unit_test(test__f_print_to_safely_terminated__fails),
    cmocka_unit_test(test__f_print_to_safely_terminated__returns_data_not),
    cmocka_unit_test(test__f_print_to_safely_terminated__works),

    cmocka_unit_test(test__f_print_to_terminated__fails),
    cmocka_unit_test(test__f_print_to_terminated__returns_data_not),
    cmocka_unit_test(test__f_print_to_terminated__works),

    #ifndef _di_level_0_parameter_checking_
      cmocka_unit_test(test__f_print__parameter_checking),
      cmocka_unit_test(test__f_print_character__parameter_checking),
      cmocka_unit_test(test__f_print_character_safely__parameter_checking),
      // f_print_character_safely_get() doesn't use parameter checking.
      cmocka_unit_test(test__f_print_dynamic__parameter_checking),
      cmocka_unit_test(test__f_print_dynamic_partial__parameter_checking),
      cmocka_unit_test(test__f_print_dynamic_partial_raw__parameter_checking),
      cmocka_unit_test(test__f_print_dynamic_partial_raw_safely__parameter_checking),
      cmocka_unit_test(test__f_print_dynamic_partial_safely__parameter_checking),
      cmocka_unit_test(test__f_print_dynamic_raw__parameter_checking),
      cmocka_unit_test(test__f_print_dynamic_raw_safely__parameter_checking),
      cmocka_unit_test(test__f_print_dynamic_safely__parameter_checking),
      cmocka_unit_test(test__f_print_except__parameter_checking),
      cmocka_unit_test(test__f_print_except_dynamic__parameter_checking),
      cmocka_unit_test(test__f_print_except_dynamic_partial__parameter_checking),
      cmocka_unit_test(test__f_print_except_dynamic_partial_raw__parameter_checking),
      cmocka_unit_test(test__f_print_except_dynamic_partial_raw_safely__parameter_checking),
      cmocka_unit_test(test__f_print_except_dynamic_partial_safely__parameter_checking),
      cmocka_unit_test(test__f_print_except_dynamic_raw__parameter_checking),
      cmocka_unit_test(test__f_print_except_dynamic_raw_safely__parameter_checking),
      cmocka_unit_test(test__f_print_except_dynamic_safely__parameter_checking),
      cmocka_unit_test(test__f_print_except_in__parameter_checking),
      cmocka_unit_test(test__f_print_except_in_dynamic__parameter_checking),
      cmocka_unit_test(test__f_print_except_in_dynamic_partial__parameter_checking),
      cmocka_unit_test(test__f_print_except_in_dynamic_partial_raw__parameter_checking),
      cmocka_unit_test(test__f_print_except_in_dynamic_partial_raw_safely__parameter_checking),
      cmocka_unit_test(test__f_print_except_in_dynamic_partial_safely__parameter_checking),
      cmocka_unit_test(test__f_print_except_in_dynamic_raw__parameter_checking),
      cmocka_unit_test(test__f_print_except_in_dynamic_raw_safely__parameter_checking),
      cmocka_unit_test(test__f_print_except_in_dynamic_safely__parameter_checking),
      cmocka_unit_test(test__f_print_except_in_raw__parameter_checking),
      cmocka_unit_test(test__f_print_except_in_raw_safely__parameter_checking),
      cmocka_unit_test(test__f_print_except_in_safely__parameter_checking),
      cmocka_unit_test(test__f_print_except_raw__parameter_checking),
      cmocka_unit_test(test__f_print_except_raw_safely__parameter_checking),
      cmocka_unit_test(test__f_print_except_safely__parameter_checking),
      cmocka_unit_test(test__f_print_raw__parameter_checking),
      cmocka_unit_test(test__f_print_raw_safely__parameter_checking),
      cmocka_unit_test(test__f_print_raw_terminated__parameter_checking),
      cmocka_unit_test(test__f_print_safely__parameter_checking),
      // f_print_safely_get() doesn't use parameter checking.
      cmocka_unit_test(test__f_print_safely_terminated__parameter_checking),
      cmocka_unit_test(test__f_print_terminated__parameter_checking),
      cmocka_unit_test(test__f_print_to__parameter_checking),
      cmocka_unit_test(test__f_print_to_character__parameter_checking),
      cmocka_unit_test(test__f_print_to_character_safely__parameter_checking),
      cmocka_unit_test(test__f_print_to_dynamic__parameter_checking),
      cmocka_unit_test(test__f_print_to_dynamic_partial__parameter_checking),
      cmocka_unit_test(test__f_print_to_dynamic_partial_raw__parameter_checking),
      cmocka_unit_test(test__f_print_to_dynamic_partial_raw_safely__parameter_checking),
      cmocka_unit_test(test__f_print_to_dynamic_partial_safely__parameter_checking),
      cmocka_unit_test(test__f_print_to_dynamic_raw__parameter_checking),
      cmocka_unit_test(test__f_print_to_dynamic_raw_safely__parameter_checking),
      cmocka_unit_test(test__f_print_to_dynamic_safely__parameter_checking),
      cmocka_unit_test(test__f_print_to_except__parameter_checking),
      cmocka_unit_test(test__f_print_to_except_dynamic__parameter_checking),
      cmocka_unit_test(test__f_print_to_except_dynamic_partial__parameter_checking),
      cmocka_unit_test(test__f_print_to_except_dynamic_partial_raw__parameter_checking),
      cmocka_unit_test(test__f_print_to_except_dynamic_partial_raw_safely__parameter_checking),
      cmocka_unit_test(test__f_print_to_except_dynamic_partial_safely__parameter_checking),
      cmocka_unit_test(test__f_print_to_except_dynamic_raw__parameter_checking),
      cmocka_unit_test(test__f_print_to_except_dynamic_raw_safely__parameter_checking),
      cmocka_unit_test(test__f_print_to_except_dynamic_safely__parameter_checking),
      cmocka_unit_test(test__f_print_to_except_in__parameter_checking),
      cmocka_unit_test(test__f_print_to_except_in_dynamic__parameter_checking),
      cmocka_unit_test(test__f_print_to_except_in_dynamic_partial__parameter_checking),
      cmocka_unit_test(test__f_print_to_except_in_dynamic_partial_raw__parameter_checking),
      cmocka_unit_test(test__f_print_to_except_in_dynamic_partial_raw_safely__parameter_checking),
      cmocka_unit_test(test__f_print_to_except_in_dynamic_partial_safely__parameter_checking),
      cmocka_unit_test(test__f_print_to_except_in_dynamic_raw__parameter_checking),
      cmocka_unit_test(test__f_print_to_except_in_dynamic_raw_safely__parameter_checking),
      cmocka_unit_test(test__f_print_to_except_in_dynamic_safely__parameter_checking),
      cmocka_unit_test(test__f_print_to_except_in_raw__parameter_checking),
      cmocka_unit_test(test__f_print_to_except_in_raw_safely__parameter_checking),
      cmocka_unit_test(test__f_print_to_except_in_safely__parameter_checking),
      cmocka_unit_test(test__f_print_to_except_raw__parameter_checking),
      cmocka_unit_test(test__f_print_to_except_raw_safely__parameter_checking),
      cmocka_unit_test(test__f_print_to_except_safely__parameter_checking),
      cmocka_unit_test(test__f_print_to_raw__parameter_checking),
      cmocka_unit_test(test__f_print_to_raw_safely__parameter_checking),
      cmocka_unit_test(test__f_print_to_raw_terminated__parameter_checking),
      cmocka_unit_test(test__f_print_to_safely__parameter_checking),
      cmocka_unit_test(test__f_print_to_safely_terminated__parameter_checking),
      cmocka_unit_test(test__f_print_to_terminated__parameter_checking),
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
