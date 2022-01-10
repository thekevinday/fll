#include "test-capability.h"

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
    cmocka_unit_test(test__f_capability_ambient_get__works),
    cmocka_unit_test(test__f_capability_ambient_get__fails),

    cmocka_unit_test(test__f_capability_ambient_reset__works),
    cmocka_unit_test(test__f_capability_ambient_reset__fails),

    cmocka_unit_test(test__f_capability_ambient_set__works),
    cmocka_unit_test(test__f_capability_ambient_set__fails),

    cmocka_unit_test(test__f_capability_clear__works),
    cmocka_unit_test(test__f_capability_clear__fails),

    cmocka_unit_test(test__f_capability_clear_flag__works),
    cmocka_unit_test(test__f_capability_clear_flag__fails),

    cmocka_unit_test(test__f_capability_compare__works),
    cmocka_unit_test(test__f_capability_compare__fails),

    cmocka_unit_test(test__f_capability_copy__works),
    cmocka_unit_test(test__f_capability_copy__fails),

    cmocka_unit_test(test__f_capability_copy_external__works),
    cmocka_unit_test(test__f_capability_copy_external__fails),

    cmocka_unit_test(test__f_capability_copy_internal__works),
    cmocka_unit_test(test__f_capability_copy_internal__fails),

    cmocka_unit_test(test__f_capability_delete__works),
    cmocka_unit_test(test__f_capability_delete__fails),

    cmocka_unit_test(test__f_capability_file_descriptor_get__works),
    cmocka_unit_test(test__f_capability_file_descriptor_get__fails),

    cmocka_unit_test(test__f_capability_file_descriptor_set__works),
    cmocka_unit_test(test__f_capability_file_descriptor_set__fails),

    cmocka_unit_test(test__f_capability_file_get__works),
    cmocka_unit_test(test__f_capability_file_get__fails),

    cmocka_unit_test(test__f_capability_file_set__works),
    cmocka_unit_test(test__f_capability_file_set__fails),

    cmocka_unit_test(test__f_capability_flag_get__works),
    cmocka_unit_test(test__f_capability_flag_get__fails),

    cmocka_unit_test(test__f_capability_flag_set__works),
    cmocka_unit_test(test__f_capability_flag_set__fails),

    cmocka_unit_test(test__f_capability_from_name__works),
    cmocka_unit_test(test__f_capability_from_name__fails),

    cmocka_unit_test(test__f_capability_from_text__works),
    cmocka_unit_test(test__f_capability_from_text__fails),

    cmocka_unit_test(test__f_capability_groups_set__works),
    cmocka_unit_test(test__f_capability_groups_set__fails),

    cmocka_unit_test(test__f_capability_initialize__works),
    cmocka_unit_test(test__f_capability_initialize__fails),

    cmocka_unit_test(test__f_capability_mode_get__works),
    // cap_get_mode() doesn't return failure.

    cmocka_unit_test(test__f_capability_mode_get_name__works),
    // cap_mode_name() doesn't return failure.

    cmocka_unit_test(test__f_capability_mode_set__works),
    cmocka_unit_test(test__f_capability_mode_set__fails),

    cmocka_unit_test(test__f_capability_owner_get__works),
    // cap_get_nsowner() doesn't return failure.

    cmocka_unit_test(test__f_capability_owner_set__works),
    cmocka_unit_test(test__f_capability_owner_set__fails),

    cmocka_unit_test(test__f_capability_process_bound_drop__works),
    cmocka_unit_test(test__f_capability_process_bound_drop__fails),

    cmocka_unit_test(test__f_capability_process_bound_get__works),
    cmocka_unit_test(test__f_capability_process_bound_get__fails),

    cmocka_unit_test(test__f_capability_process_get_by_id__works),
    cmocka_unit_test(test__f_capability_process_get_by_id__fails),

    cmocka_unit_test(test__f_capability_process_get__works),
    cmocka_unit_test(test__f_capability_process_get__fails),

    cmocka_unit_test(test__f_capability_process_set__works),
    cmocka_unit_test(test__f_capability_process_set__fails),

    cmocka_unit_test(test__f_capability_security_bits_get__works),
    cmocka_unit_test(test__f_capability_security_bits_get__fails),

    cmocka_unit_test(test__f_capability_security_bits_set__works),
    cmocka_unit_test(test__f_capability_security_bits_set__fails),

    cmocka_unit_test(test__f_capability_size__works),
    cmocka_unit_test(test__f_capability_size__fails),

    cmocka_unit_test(test__f_capability_supported__works),
    // f_capability_supported() doesn't return failure.

    cmocka_unit_test(test__f_capability_supported_ambient__works),
    // f_capability_supported_ambient() doesn't return failure.

    cmocka_unit_test(test__f_capability_supported_code__works),
    // f_capability_supported_code() doesn't return failure.

    cmocka_unit_test(test__f_capability_to_name__works),
    cmocka_unit_test(test__f_capability_to_name__fails),

    cmocka_unit_test(test__f_capability_to_text__works),
    cmocka_unit_test(test__f_capability_to_text__fails),

    cmocka_unit_test(test__f_capability_user_set__works),
    cmocka_unit_test(test__f_capability_user_set__fails),
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
