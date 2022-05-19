#include "test-serialize.h"

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
    cmocka_unit_test(test__f_serialize_from_simple__returns_data_not),
    cmocka_unit_test(test__f_serialize_from_simple__works),

    cmocka_unit_test(test__f_serialize_from_simple_get__returns_data_not),
    cmocka_unit_test(test__f_serialize_from_simple_get__works),

    cmocka_unit_test(test__f_serialize_from_simple_select__returns_data_not),
    cmocka_unit_test(test__f_serialize_from_simple_select__works),

    cmocka_unit_test(test__f_serialize_from_simple_range__returns_data_not),
    cmocka_unit_test(test__f_serialize_from_simple_range__works),

    cmocka_unit_test(test__f_serialize_to_simple__returns_data_not),
    cmocka_unit_test(test__f_serialize_to_simple__works),

    #ifndef _di_level_0_parameter_checking_
      cmocka_unit_test(test__f_serialize_from_simple__parameter_checking),
      cmocka_unit_test(test__f_serialize_from_simple_get__parameter_checking),
      cmocka_unit_test(test__f_serialize_from_simple_range__parameter_checking),
      cmocka_unit_test(test__f_serialize_from_simple_select__parameter_checking),
      cmocka_unit_test(test__f_serialize_to_simple__parameter_checking),
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
