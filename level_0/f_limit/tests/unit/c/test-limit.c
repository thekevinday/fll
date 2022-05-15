#include "test-limit.h"

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
    cmocka_unit_test(test__f_limit_process__fails),
    cmocka_unit_test(test__f_limit_process__works),

    cmocka_unit_test(test__f_limit_sets_adjust__works),
    cmocka_unit_test(test__f_limit_sets_append__works),
    cmocka_unit_test(test__f_limit_sets_append_all__works),
    cmocka_unit_test(test__f_limit_sets_decimate_by__works),
    cmocka_unit_test(test__f_limit_sets_decrease_by__works),
    cmocka_unit_test(test__f_limit_sets_increase__works),
    cmocka_unit_test(test__f_limit_sets_increase_by__works),
    cmocka_unit_test(test__f_limit_sets_resize__works),

    cmocka_unit_test(test__f_limit_setss_append__returns_data_not),
    cmocka_unit_test(test__f_limit_setss_append_all__returns_data_not),
    cmocka_unit_test(test__f_limit_setss_decimate_by__returns_data_not),
    cmocka_unit_test(test__f_limit_setss_decrease_by__returns_data_not),
    cmocka_unit_test(test__f_limit_setss_increase__returns_data_not),
    cmocka_unit_test(test__f_limit_setss_increase_by__returns_data_not),

    cmocka_unit_test(test__f_limit_setss_adjust__works),
    cmocka_unit_test(test__f_limit_setss_append__works),
    cmocka_unit_test(test__f_limit_setss_append_all__works),
    cmocka_unit_test(test__f_limit_setss_decimate_by__works),
    cmocka_unit_test(test__f_limit_setss_decrease_by__works),
    cmocka_unit_test(test__f_limit_setss_increase__works),
    cmocka_unit_test(test__f_limit_setss_increase_by__works),
    cmocka_unit_test(test__f_limit_setss_resize__works),

    cmocka_unit_test(test__f_limit_values_adjust__works),
    cmocka_unit_test(test__f_limit_values_append__works),
    cmocka_unit_test(test__f_limit_values_append_all__works),
    cmocka_unit_test(test__f_limit_values_decimate_by__works),
    cmocka_unit_test(test__f_limit_values_decrease_by__works),
    cmocka_unit_test(test__f_limit_values_increase__works),
    cmocka_unit_test(test__f_limit_values_increase_by__works),
    cmocka_unit_test(test__f_limit_values_resize__works),

    cmocka_unit_test(test__f_limit_valuess_append__returns_data_not),
    cmocka_unit_test(test__f_limit_valuess_append_all__returns_data_not),
    cmocka_unit_test(test__f_limit_valuess_decimate_by__returns_data_not),
    cmocka_unit_test(test__f_limit_valuess_decrease_by__returns_data_not),
    cmocka_unit_test(test__f_limit_valuess_increase__returns_data_not),
    cmocka_unit_test(test__f_limit_valuess_increase_by__returns_data_not),

    cmocka_unit_test(test__f_limit_valuess_adjust__works),
    cmocka_unit_test(test__f_limit_valuess_append__works),
    cmocka_unit_test(test__f_limit_valuess_append_all__works),
    cmocka_unit_test(test__f_limit_valuess_decimate_by__works),
    cmocka_unit_test(test__f_limit_valuess_decrease_by__works),
    cmocka_unit_test(test__f_limit_valuess_increase__works),
    cmocka_unit_test(test__f_limit_valuess_increase_by__works),
    cmocka_unit_test(test__f_limit_valuess_resize__works),

    #ifndef _di_level_0_parameter_checking_
      cmocka_unit_test(test__f_limit_process__parameter_checking),

      cmocka_unit_test(test__f_limit_sets_adjust__parameter_checking),
      cmocka_unit_test(test__f_limit_sets_append__parameter_checking),
      cmocka_unit_test(test__f_limit_sets_append_all__parameter_checking),
      cmocka_unit_test(test__f_limit_sets_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_limit_sets_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_limit_sets_increase__parameter_checking),
      cmocka_unit_test(test__f_limit_sets_increase_by__parameter_checking),
      cmocka_unit_test(test__f_limit_sets_resize__parameter_checking),

      cmocka_unit_test(test__f_limit_setss_adjust__parameter_checking),
      cmocka_unit_test(test__f_limit_setss_append__parameter_checking),
      cmocka_unit_test(test__f_limit_setss_append_all__parameter_checking),
      cmocka_unit_test(test__f_limit_setss_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_limit_setss_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_limit_setss_increase__parameter_checking),
      cmocka_unit_test(test__f_limit_setss_increase_by__parameter_checking),
      cmocka_unit_test(test__f_limit_setss_resize__parameter_checking),

      cmocka_unit_test(test__f_limit_values_adjust__parameter_checking),
      cmocka_unit_test(test__f_limit_values_append__parameter_checking),
      cmocka_unit_test(test__f_limit_values_append_all__parameter_checking),
      cmocka_unit_test(test__f_limit_values_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_limit_values_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_limit_values_increase__parameter_checking),
      cmocka_unit_test(test__f_limit_values_increase_by__parameter_checking),
      cmocka_unit_test(test__f_limit_values_resize__parameter_checking),

      cmocka_unit_test(test__f_limit_valuess_adjust__parameter_checking),
      cmocka_unit_test(test__f_limit_valuess_append__parameter_checking),
      cmocka_unit_test(test__f_limit_valuess_append_all__parameter_checking),
      cmocka_unit_test(test__f_limit_valuess_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_limit_valuess_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_limit_valuess_increase__parameter_checking),
      cmocka_unit_test(test__f_limit_valuess_increase_by__parameter_checking),
      cmocka_unit_test(test__f_limit_valuess_resize__parameter_checking),
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
