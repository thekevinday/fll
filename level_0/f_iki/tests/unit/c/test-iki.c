#include "test-iki.h"

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
    cmocka_unit_test(test__f_iki_content_is__returns_false),
    cmocka_unit_test(test__f_iki_content_is__returns_data_not),
    cmocka_unit_test(test__f_iki_content_is__returns_true),

    cmocka_unit_test(test__f_iki_content_partial_is__returns_data_not),
    cmocka_unit_test(test__f_iki_content_partial_is__returns_data_not_eos),
    cmocka_unit_test(test__f_iki_content_partial_is__returns_data_not_stop),
    cmocka_unit_test(test__f_iki_content_partial_is__returns_false),
    cmocka_unit_test(test__f_iki_content_partial_is__returns_true),

    cmocka_unit_test(test__f_iki_datas_adjust__works),
    cmocka_unit_test(test__f_iki_datas_append__works),
    cmocka_unit_test(test__f_iki_datas_append_all__works),
    cmocka_unit_test(test__f_iki_datas_append_all__returns_data_not),
    cmocka_unit_test(test__f_iki_datas_decimate_by__works),
    cmocka_unit_test(test__f_iki_datas_decrease_by__works),
    cmocka_unit_test(test__f_iki_datas_increase__works),
    cmocka_unit_test(test__f_iki_datas_increase__returns_data_not),
    cmocka_unit_test(test__f_iki_datas_increase_by__works),
    cmocka_unit_test(test__f_iki_datas_resize__works),

    cmocka_unit_test(test__f_iki_datass_adjust__works),
    cmocka_unit_test(test__f_iki_datass_append__works),
    cmocka_unit_test(test__f_iki_datass_append__returns_data_not),
    cmocka_unit_test(test__f_iki_datass_append_all__works),
    cmocka_unit_test(test__f_iki_datass_append_all__returns_data_not),
    cmocka_unit_test(test__f_iki_datass_decimate_by__works),
    cmocka_unit_test(test__f_iki_datass_decrease_by__works),
    cmocka_unit_test(test__f_iki_datass_increase__works),
    cmocka_unit_test(test__f_iki_datass_increase__returns_data_not),
    cmocka_unit_test(test__f_iki_datass_increase_by__works),
    cmocka_unit_test(test__f_iki_datass_resize__works),

    cmocka_unit_test(test__f_iki_object_is__returns_data_not),
    cmocka_unit_test(test__f_iki_object_is__returns_false),
    cmocka_unit_test(test__f_iki_object_is__returns_true),

    cmocka_unit_test(test__f_iki_object_partial_is__returns_data_not),
    cmocka_unit_test(test__f_iki_object_partial_is__returns_data_not_eos),
    cmocka_unit_test(test__f_iki_object_partial_is__returns_data_not_stop),
    cmocka_unit_test(test__f_iki_object_partial_is__returns_false),
    cmocka_unit_test(test__f_iki_object_partial_is__returns_true),

    cmocka_unit_test(test__f_iki_read__returns_data_not),
    cmocka_unit_test(test__f_iki_read__returns_data_not_eos),
    cmocka_unit_test(test__f_iki_read__returns_data_not_stop),
    cmocka_unit_test(test__f_iki_read__works),

    #ifndef _di_level_0_parameter_checking_
      cmocka_unit_test(test__f_iki_content_is__parameter_checking),
      cmocka_unit_test(test__f_iki_content_partial_is__parameter_checking),

      cmocka_unit_test(test__f_iki_datas_adjust__parameter_checking),
      cmocka_unit_test(test__f_iki_datas_append__parameter_checking),
      cmocka_unit_test(test__f_iki_datas_append_all__parameter_checking),
      cmocka_unit_test(test__f_iki_datas_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_iki_datas_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_iki_datas_increase__parameter_checking),
      cmocka_unit_test(test__f_iki_datas_increase_by__parameter_checking),
      cmocka_unit_test(test__f_iki_datas_resize__parameter_checking),

      cmocka_unit_test(test__f_iki_datass_adjust__parameter_checking),
      cmocka_unit_test(test__f_iki_datass_append__parameter_checking),
      cmocka_unit_test(test__f_iki_datass_append_all__parameter_checking),
      cmocka_unit_test(test__f_iki_datass_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_iki_datass_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_iki_datass_increase__parameter_checking),
      cmocka_unit_test(test__f_iki_datass_increase_by__parameter_checking),
      cmocka_unit_test(test__f_iki_datass_resize__parameter_checking),

      // f_iki_object_is() doesn't use parameter checking.
      // f_iki_object_partial_is() doesn't use parameter checking.

      cmocka_unit_test(test__f_iki_read__parameter_checking),
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
