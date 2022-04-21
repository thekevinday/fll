#include "test-file.h"

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
    cmocka_unit_test(test__f_file_access__fails),
    cmocka_unit_test(test__f_file_access__returns_data_not),
    cmocka_unit_test(test__f_file_access__works),

    cmocka_unit_test(test__f_file_access_at__fails),
    cmocka_unit_test(test__f_file_access_at__returns_data_not),
    cmocka_unit_test(test__f_file_access_at__works),

    cmocka_unit_test(test__f_file_clone__fails_during_read_write),
    cmocka_unit_test(test__f_file_clone__fails_for_link),
    cmocka_unit_test(test__f_file_clone__fails_for_other),
    cmocka_unit_test(test__f_file_clone__fails_for_regular),
    cmocka_unit_test(test__f_file_clone__returns_data_not),
    cmocka_unit_test(test__f_file_clone__works_for_regular),
    cmocka_unit_test(test__f_file_clone__works_for_link),

    cmocka_unit_test(test__f_file_close__fails),
    cmocka_unit_test(test__f_file_close__works),
    cmocka_unit_test(test__f_file_close__works_already_closed),

    cmocka_unit_test(test__f_file_close_flush__fails),
    cmocka_unit_test(test__f_file_close_flush__works),
    cmocka_unit_test(test__f_file_close_flush__works_already_closed),

    cmocka_unit_test(test__f_file_copy__fails_during_read_write),
    cmocka_unit_test(test__f_file_copy__fails_for_block),
    cmocka_unit_test(test__f_file_copy__fails_for_character),
    cmocka_unit_test(test__f_file_copy__fails_for_directory),
    cmocka_unit_test(test__f_file_copy__fails_for_fifo),
    cmocka_unit_test(test__f_file_copy__fails_for_link),
    cmocka_unit_test(test__f_file_copy__fails_for_regular),
    cmocka_unit_test(test__f_file_copy__fails_for_socket),
    cmocka_unit_test(test__f_file_copy__returns_data_not),
    cmocka_unit_test(test__f_file_copy__works_for_block),
    cmocka_unit_test(test__f_file_copy__works_for_character),
    cmocka_unit_test(test__f_file_copy__works_for_directory),
    cmocka_unit_test(test__f_file_copy__works_for_fifo),
    cmocka_unit_test(test__f_file_copy__works_for_link),
    cmocka_unit_test(test__f_file_copy__works_for_regular),
    cmocka_unit_test(test__f_file_copy__works_for_socket),

    cmocka_unit_test(test__f_file_create__fails),
    cmocka_unit_test(test__f_file_create__returns_data_not),
    cmocka_unit_test(test__f_file_create__works),

    cmocka_unit_test(test__f_file_create_at__fails),
    cmocka_unit_test(test__f_file_create_at__returns_data_not),
    cmocka_unit_test(test__f_file_create_at__works),

    cmocka_unit_test(test__f_file_create_device__fails),
    cmocka_unit_test(test__f_file_create_device__returns_data_not),
    cmocka_unit_test(test__f_file_create_device__returns_supported_not),
    cmocka_unit_test(test__f_file_create_device__works),

    cmocka_unit_test(test__f_file_create_device_at__fails),
    cmocka_unit_test(test__f_file_create_device_at__returns_data_not),
    cmocka_unit_test(test__f_file_create_device_at__returns_supported_not),
    cmocka_unit_test(test__f_file_create_device_at__works),

    cmocka_unit_test(test__f_file_create_fifo__fails),
    cmocka_unit_test(test__f_file_create_fifo__returns_data_not),
    cmocka_unit_test(test__f_file_create_fifo__works),

    cmocka_unit_test(test__f_file_create_fifo_at__fails),
    cmocka_unit_test(test__f_file_create_fifo_at__returns_data_not),
    cmocka_unit_test(test__f_file_create_fifo_at__works),

    cmocka_unit_test(test__f_file_create_node__fails),
    cmocka_unit_test(test__f_file_create_node__returns_data_not),
    cmocka_unit_test(test__f_file_create_node__returns_supported_not),
    cmocka_unit_test(test__f_file_create_node__works),

    cmocka_unit_test(test__f_file_create_node_at__fails),
    cmocka_unit_test(test__f_file_create_node_at__returns_data_not),
    cmocka_unit_test(test__f_file_create_node_at__returns_supported_not),
    cmocka_unit_test(test__f_file_create_node_at__works),

    cmocka_unit_test(test__f_file_descriptor__fails),
    cmocka_unit_test(test__f_file_descriptor__works),

    cmocka_unit_test(test__f_file_exists__fails),
    cmocka_unit_test(test__f_file_exists__returns_data_not),
    cmocka_unit_test(test__f_file_exists__works),

    cmocka_unit_test(test__f_file_exists_at__fails),
    cmocka_unit_test(test__f_file_exists_at__returns_data_not),
    cmocka_unit_test(test__f_file_exists_at__works),

    cmocka_unit_test(test__f_file_flush__fails),
    cmocka_unit_test(test__f_file_flush__works),

    cmocka_unit_test(test__f_file_group_read__fails),
    cmocka_unit_test(test__f_file_group_read__returns_data_not),
    cmocka_unit_test(test__f_file_group_read__works),

    cmocka_unit_test(test__f_file_is__fails),
    cmocka_unit_test(test__f_file_is__returns_data_not),
    cmocka_unit_test(test__f_file_is__returns_false),
    cmocka_unit_test(test__f_file_is__returns_true),

    cmocka_unit_test(test__f_file_is_at__fails),
    cmocka_unit_test(test__f_file_is_at__returns_data_not),
    cmocka_unit_test(test__f_file_is_at__returns_false),
    cmocka_unit_test(test__f_file_is_at__returns_true),

    cmocka_unit_test(test__f_file_link__fails),
    cmocka_unit_test(test__f_file_link__returns_data_not),
    cmocka_unit_test(test__f_file_link__works),

    cmocka_unit_test(test__f_file_link_at__fails),
    cmocka_unit_test(test__f_file_link_at__returns_data_not),
    cmocka_unit_test(test__f_file_link_at__works),

    cmocka_unit_test(test__f_file_link_hard__fails),
    cmocka_unit_test(test__f_file_link_hard__returns_data_not),
    cmocka_unit_test(test__f_file_link_hard__works),

    cmocka_unit_test(test__f_file_link_hard_at__fails),
    cmocka_unit_test(test__f_file_link_hard_at__returns_data_not),
    cmocka_unit_test(test__f_file_link_hard_at__works),

    cmocka_unit_test(test__f_file_link_read__fails),
    cmocka_unit_test(test__f_file_link_read__returns_data_not),
    cmocka_unit_test(test__f_file_link_read__works),

    cmocka_unit_test(test__f_file_link_read_at__fails),
    cmocka_unit_test(test__f_file_link_read_at__returns_data_not),
    cmocka_unit_test(test__f_file_link_read_at__works),

    cmocka_unit_test(test__f_file_mode_determine__works_basic),
    cmocka_unit_test(test__f_file_mode_determine__works_basic_replace),

    cmocka_unit_test(test__f_file_mode_from_string__fails_basic),
    cmocka_unit_test(test__f_file_mode_from_string__returns_data_not),
    cmocka_unit_test(test__f_file_mode_from_string__works_basic_alphabet),
    cmocka_unit_test(test__f_file_mode_from_string__works_basic_digit),

    cmocka_unit_test(test__f_file_mode_read__fails),
    cmocka_unit_test(test__f_file_mode_read__returns_data_not),
    cmocka_unit_test(test__f_file_mode_read__works),

    cmocka_unit_test(test__f_file_mode_read_at__fails),
    cmocka_unit_test(test__f_file_mode_read_at__returns_data_not),
    cmocka_unit_test(test__f_file_mode_read_at__works),

    cmocka_unit_test(test__f_file_mode_set__fails),
    cmocka_unit_test(test__f_file_mode_set__returns_data_not),
    cmocka_unit_test(test__f_file_mode_set__works),

    cmocka_unit_test(test__f_file_mode_set_at__fails),
    cmocka_unit_test(test__f_file_mode_set_at__returns_data_not),
    cmocka_unit_test(test__f_file_mode_set_at__works),

    cmocka_unit_test(test__f_file_mode_to_mode__works),

    cmocka_unit_test(test__f_file_name_base__returns_data_not),
    cmocka_unit_test(test__f_file_name_base__works),

    cmocka_unit_test(test__f_file_name_directory__returns_data_not),
    cmocka_unit_test(test__f_file_name_directory__works),

    cmocka_unit_test(test__f_file_open__fails),
    cmocka_unit_test(test__f_file_open__returns_data_not),
    cmocka_unit_test(test__f_file_open__works),

    cmocka_unit_test(test__f_file_open_at__fails),
    cmocka_unit_test(test__f_file_open_at__returns_data_not),
    cmocka_unit_test(test__f_file_open_at__works),

    cmocka_unit_test(test__f_file_owner_read__fails),
    cmocka_unit_test(test__f_file_owner_read__returns_data_not),
    cmocka_unit_test(test__f_file_owner_read__works),

    cmocka_unit_test(test__f_file_read__fails),
    cmocka_unit_test(test__f_file_read__returns_file_closed),
    cmocka_unit_test(test__f_file_read__works),

    cmocka_unit_test(test__f_file_read_block__fails),
    cmocka_unit_test(test__f_file_read_block__returns_file_closed),
    cmocka_unit_test(test__f_file_read_block__works),

    cmocka_unit_test(test__f_file_read_until__fails),
    cmocka_unit_test(test__f_file_read_until__returns_file_closed),
    cmocka_unit_test(test__f_file_read_until__works),

    cmocka_unit_test(test__f_file_remove__fails),
    cmocka_unit_test(test__f_file_remove__returns_data_not),
    cmocka_unit_test(test__f_file_remove__works),

    cmocka_unit_test(test__f_file_remove_at__fails),
    cmocka_unit_test(test__f_file_remove_at__returns_data_not),
    cmocka_unit_test(test__f_file_remove_at__works),

    cmocka_unit_test(test__f_file_rename__fails),
    cmocka_unit_test(test__f_file_rename__returns_data_not),
    cmocka_unit_test(test__f_file_rename__works),

    cmocka_unit_test(test__f_file_rename_at__fails),
    cmocka_unit_test(test__f_file_rename_at__returns_data_not),
    cmocka_unit_test(test__f_file_rename_at__works),

    cmocka_unit_test(test__f_file_role_change__fails_for_dereference),
    cmocka_unit_test(test__f_file_role_change__fails_for_reference),
    cmocka_unit_test(test__f_file_role_change__returns_data_not),
    cmocka_unit_test(test__f_file_role_change__works_for_dereference),
    cmocka_unit_test(test__f_file_role_change__works_for_reference),

    cmocka_unit_test(test__f_file_role_change_at__fails_for_dereference),
    cmocka_unit_test(test__f_file_role_change_at__fails_for_reference),
    cmocka_unit_test(test__f_file_role_change_at__returns_data_not),
    cmocka_unit_test(test__f_file_role_change_at__works_for_dereference),
    cmocka_unit_test(test__f_file_role_change_at__works_for_reference),

    cmocka_unit_test(test__f_file_seek__fails),
    cmocka_unit_test(test__f_file_seek__works),

    cmocka_unit_test(test__f_file_size__fails),
    cmocka_unit_test(test__f_file_size__returns_data_not),
    cmocka_unit_test(test__f_file_size__works),

    cmocka_unit_test(test__f_file_size_at__fails),
    cmocka_unit_test(test__f_file_size_at__returns_data_not),
    cmocka_unit_test(test__f_file_size_at__works),

    cmocka_unit_test(test__f_file_size_by_id__fails),
    cmocka_unit_test(test__f_file_size_by_id__returns_file_closed),
    cmocka_unit_test(test__f_file_size_by_id__works),

    cmocka_unit_test(test__f_file_stat__fails),
    cmocka_unit_test(test__f_file_stat__returns_data_not),
    cmocka_unit_test(test__f_file_stat__works),

    cmocka_unit_test(test__f_file_stat_at__fails),
    cmocka_unit_test(test__f_file_stat_at__returns_data_not),
    cmocka_unit_test(test__f_file_stat_at__works),

    cmocka_unit_test(test__f_file_stat_by_id__fails),
    cmocka_unit_test(test__f_file_stat_by_id__returns_file_closed),
    cmocka_unit_test(test__f_file_stat_by_id__works),

    cmocka_unit_test(test__f_file_stream_close__fails_for_file_descriptor),
    cmocka_unit_test(test__f_file_stream_close__fails_for_stream),
    cmocka_unit_test(test__f_file_stream_close__works),

    // __wrap_fdopen does not appear to be working.
    //cmocka_unit_test(test__f_file_stream_open_descriptor__fails),
    //cmocka_unit_test(test__f_file_stream_open_descriptor__works),

    cmocka_unit_test(test__f_file_stream_open__fails),
    cmocka_unit_test(test__f_file_stream_open__returns_data_not),
    cmocka_unit_test(test__f_file_stream_open__works),

    cmocka_unit_test(test__f_file_stream_read__fails),
    cmocka_unit_test(test__f_file_stream_read__returns_file_closed),
    cmocka_unit_test(test__f_file_stream_read__works),

    cmocka_unit_test(test__f_file_stream_read_block__fails),
    cmocka_unit_test(test__f_file_stream_read_block__returns_file_closed),
    cmocka_unit_test(test__f_file_stream_read_block__works),

    cmocka_unit_test(test__f_file_stream_read_until__fails),
    cmocka_unit_test(test__f_file_stream_read_until__returns_file_closed),
    cmocka_unit_test(test__f_file_stream_read_until__works),

    cmocka_unit_test(test__f_file_stream_reopen__fails),
    cmocka_unit_test(test__f_file_stream_reopen__returns_data_not),
    cmocka_unit_test(test__f_file_stream_reopen__works),

    cmocka_unit_test(test__f_file_stream_write__fails),
    cmocka_unit_test(test__f_file_stream_write__returns_file_closed),
    cmocka_unit_test(test__f_file_stream_write__returns_data_not),
    cmocka_unit_test(test__f_file_stream_write__works),

    cmocka_unit_test(test__f_file_stream_write_block__fails),
    cmocka_unit_test(test__f_file_stream_write_block__returns_file_closed),
    cmocka_unit_test(test__f_file_stream_write_block__returns_data_not),
    cmocka_unit_test(test__f_file_stream_write_block__works),

    cmocka_unit_test(test__f_file_stream_write_range__fails),
    cmocka_unit_test(test__f_file_stream_write_range__returns_file_closed),
    cmocka_unit_test(test__f_file_stream_write_range__returns_data_not),
    cmocka_unit_test(test__f_file_stream_write_range__works),

    cmocka_unit_test(test__f_file_stream_write_until__fails),
    cmocka_unit_test(test__f_file_stream_write_until__returns_file_closed),
    cmocka_unit_test(test__f_file_stream_write_until__returns_data_not),
    cmocka_unit_test(test__f_file_stream_write_until__works),

    cmocka_unit_test(test__f_file_touch__fails),
    cmocka_unit_test(test__f_file_touch__returns_data_not),
    cmocka_unit_test(test__f_file_touch__works),

    cmocka_unit_test(test__f_file_touch_at__fails),
    cmocka_unit_test(test__f_file_touch_at__returns_data_not),
    cmocka_unit_test(test__f_file_touch_at__works),

    cmocka_unit_test(test__f_file_type__fails),
    cmocka_unit_test(test__f_file_type__returns_data_not),
    cmocka_unit_test(test__f_file_type__works),

    cmocka_unit_test(test__f_file_type_at__fails),
    cmocka_unit_test(test__f_file_type_at__returns_data_not),
    cmocka_unit_test(test__f_file_type_at__works),

    cmocka_unit_test(test__f_file_umask_get__works),

    cmocka_unit_test(test__f_file_umask_set__works),

    cmocka_unit_test(test__f_file_write__fails),
    cmocka_unit_test(test__f_file_write__returns_file_closed),
    cmocka_unit_test(test__f_file_write__returns_data_not),
    cmocka_unit_test(test__f_file_write__works),

    cmocka_unit_test(test__f_file_write_block__fails),
    cmocka_unit_test(test__f_file_write_block__returns_file_closed),
    cmocka_unit_test(test__f_file_write_block__returns_data_not),
    cmocka_unit_test(test__f_file_write_block__works),

    cmocka_unit_test(test__f_file_write_range__fails),
    cmocka_unit_test(test__f_file_write_range__returns_file_closed),
    cmocka_unit_test(test__f_file_write_range__returns_data_not),
    cmocka_unit_test(test__f_file_write_range__works),

    cmocka_unit_test(test__f_file_write_until__fails),
    cmocka_unit_test(test__f_file_write_until__returns_file_closed),
    cmocka_unit_test(test__f_file_write_until__returns_data_not),
    cmocka_unit_test(test__f_file_write_until__works),

    #ifndef _di_level_0_parameter_checking_
      // f_file_access() doesn't use parameter checking.
      // f_file_access_at() doesn't use parameter checking.
      // f_file_clone() doesn't use parameter checking.
      cmocka_unit_test(test__f_file_close__parameter_checking),
      cmocka_unit_test(test__f_file_close_flush__parameter_checking),
      // f_file_copy() doesn't use parameter checking.
      // f_file_create() doesn't use parameter checking.
      // f_file_create_at() doesn't use parameter checking.
      // f_file_create_device() doesn't use parameter checking.
      // f_file_create_device_at() doesn't use parameter checking.
      // f_file_create_fifo() doesn't use parameter checking.
      // f_file_create_fifo_at() doesn't use parameter checking.
      // f_file_create_node() doesn't use parameter checking.
      // f_file_create_node_at() doesn't use parameter checking.
      cmocka_unit_test(test__f_file_descriptor__parameter_checking),
      // f_file_exists() doesn't use parameter checking.
      // f_file_exists_at() doesn't use parameter checking.
      // f_file_flush() doesn't use parameter checking.
      cmocka_unit_test(test__f_file_group_read__parameter_checking),
      // f_file_is() doesn't use parameter checking.
      // f_file_is_at() doesn't use parameter checking.
      // f_file_link() doesn't use parameter checking.
      // f_file_link_at() doesn't use parameter checking.
      // f_file_link_hard() doesn't use parameter checking.
      // f_file_link_hard_at() doesn't use parameter checking.
      cmocka_unit_test(test__f_file_link_read__parameter_checking),
      cmocka_unit_test(test__f_file_link_read_at__parameter_checking),
      cmocka_unit_test(test__f_file_mode_determine__parameter_checking),
      cmocka_unit_test(test__f_file_mode_from_string__parameter_checking),
      cmocka_unit_test(test__f_file_mode_read__parameter_checking),
      cmocka_unit_test(test__f_file_mode_read_at__parameter_checking),
      // f_file_mode_set() doesn't use parameter checking.
      // f_file_mode_set_at() doesn't use parameter checking.
      cmocka_unit_test(test__f_file_mode_to_mode__parameter_checking),
      cmocka_unit_test(test__f_file_name_base__parameter_checking),
      cmocka_unit_test(test__f_file_name_directory__parameter_checking),
      cmocka_unit_test(test__f_file_open__parameter_checking),
      cmocka_unit_test(test__f_file_open_at__parameter_checking),
      cmocka_unit_test(test__f_file_owner_read__parameter_checking),
      cmocka_unit_test(test__f_file_read__parameter_checking),
      cmocka_unit_test(test__f_file_read_block__parameter_checking),
      cmocka_unit_test(test__f_file_read_until__parameter_checking),
      // f_file_remove() doesn't use parameter checking.
      // f_file_remove_at() doesn't use parameter checking.
      // f_file_rename() doesn't use parameter checking.
      // f_file_rename_at() doesn't use parameter checking.
      // f_file_role_change() doesn't use parameter checking.
      // f_file_role_change_at() doesn't use parameter checking.
      cmocka_unit_test(test__f_file_seek__parameter_checking),
      cmocka_unit_test(test__f_file_size__parameter_checking),
      cmocka_unit_test(test__f_file_size_at__parameter_checking),
      cmocka_unit_test(test__f_file_size_by_id__parameter_checking),
      cmocka_unit_test(test__f_file_stat__parameter_checking),
      cmocka_unit_test(test__f_file_stat_at__parameter_checking),
      cmocka_unit_test(test__f_file_stat_by_id__parameter_checking),
      cmocka_unit_test(test__f_file_stream_close__parameter_checking),
      cmocka_unit_test(test__f_file_stream_open_descriptor__parameter_checking),
      cmocka_unit_test(test__f_file_stream_open__parameter_checking),
      cmocka_unit_test(test__f_file_stream_read__parameter_checking),
      cmocka_unit_test(test__f_file_stream_read_block__parameter_checking),
      cmocka_unit_test(test__f_file_stream_read_until__parameter_checking),
      cmocka_unit_test(test__f_file_stream_reopen__parameter_checking),
      cmocka_unit_test(test__f_file_stream_write__parameter_checking),
      cmocka_unit_test(test__f_file_stream_write_block__parameter_checking),
      cmocka_unit_test(test__f_file_stream_write_until__parameter_checking),
      cmocka_unit_test(test__f_file_stream_write_range__parameter_checking),
      // f_file_touch() doesn't use parameter checking.
      // f_file_touch_at() doesn't use parameter checking.
      cmocka_unit_test(test__f_file_type__parameter_checking),
      cmocka_unit_test(test__f_file_type_at__parameter_checking),
      cmocka_unit_test(test__f_file_umask_get__parameter_checking),
      // f_file_umask_set() doesn't use parameter checking.
      cmocka_unit_test(test__f_file_write__parameter_checking),
      cmocka_unit_test(test__f_file_write_block__parameter_checking),
      cmocka_unit_test(test__f_file_write_until__parameter_checking),
      cmocka_unit_test(test__f_file_write_range__parameter_checking),
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
