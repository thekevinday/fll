/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides common print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_common_print_h
#define _fake_common_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A special array of strings intended for representing funciton names.
 *
 * These are primarily used for printing errors with the function names.
 *
 * The macro macro_fake_f() is used to reference the array index by the enum name.
 *
 * macro_fake_f():
 *   - name: The name of the function.
 */
#ifndef _di_fake_f_a_
  extern const f_string_t fake_f_a[];

  #define macro_fake_f(name) fake_f_a[fake_f_##name##_e]
#endif // _di_fake_f_a_

/**
 * An enum representing specific indexes within the above array.
 *
 * This is a convenience enum used to make code slightly more readable.
 */
#ifndef _di_fake_f_e_
  enum {
    fake_f_f_account_group_id_by_name_e,
    fake_f_f_account_id_by_name_e,
    fake_f_f_array_lengths_increase_e,
    fake_f_f_console_parameter_prioritize_right_e,
    fake_f_f_console_parameter_process_e,
    fake_f_f_conversion_number_signed_to_string_e,
    fake_f_f_directory_create_e,
    fake_f_f_directory_exists_e,
    fake_f_f_directory_is_e,
    fake_f_f_directory_open_e,
    fake_f_f_directory_remove_e,
    fake_f_f_directory_touch_e,
    fake_f_f_environment_get_all_e,
    fake_f_f_environment_set_e,
    fake_f_f_file_clone_e,
    fake_f_f_file_copy_e,
    fake_f_f_file_create_e,
    fake_f_f_file_exists_e,
    fake_f_f_file_group_read_e,
    fake_f_f_file_is_e,
    fake_f_f_file_link_e,
    fake_f_f_file_mode_determine_e,
    fake_f_f_file_mode_read_e,
    fake_f_f_file_mode_set_e,
    fake_f_f_file_mode_to_mode_e,
    fake_f_f_file_name_base_e,
    fake_f_f_file_name_directory_e,
    fake_f_f_file_open_e,
    fake_f_f_file_owner_read_e,
    fake_f_f_file_read_e,
    fake_f_f_file_remove_e,
    fake_f_f_file_role_change_e,
    fake_f_f_file_size_e,
    fake_f_f_file_stat_e,
    fake_f_f_file_stream_open_e,
    fake_f_f_file_stream_read_block_e,
    fake_f_f_file_stream_write_e,
    fake_f_f_file_touch_e,
    fake_f_f_file_write_e,
    fake_f_f_fss_apply_delimit_e,
    fake_f_f_fss_nameds_resize_e,
    fake_f_f_path_change_e,
    fake_f_f_path_current_e,
    fake_f_f_path_directory_cleanup_e,
    fake_f_f_string_append_e,
    fake_f_f_string_dynamic_append_e,
    fake_f_f_string_dynamic_append_assure_e,
    fake_f_f_string_dynamic_append_nulless_e,
    fake_f_f_string_dynamic_increase_by_e,
    fake_f_f_string_dynamic_mash_e,
    fake_f_f_string_dynamic_partial_append_e,
    fake_f_f_string_dynamic_partial_append_nulless_e,
    fake_f_f_string_dynamic_prepend_e,
    fake_f_f_string_dynamic_resize_e,
    fake_f_f_string_dynamics_increase_e,
    fake_f_f_string_dynamics_increase_by_e,
    fake_f_f_string_dynamics_resize_e,
    fake_f_f_string_map_multis_resize_e,
    fake_f_f_uint8s_increase_e,
    fake_f_f_uint8s_increase_by_e,
    fake_f_f_utf_is_word_dash_plus_e,
    fake_f_fl_conversion_dynamic_to_unsigned_detect_e,
    fake_f_fl_directory_copy_e,
    fake_f_fl_directory_create_e,
    fake_f_fl_environment_load_name_e,
    fake_f_fl_environment_load_names_e,
    fake_f_fl_iki_read_e,
    fake_f_fl_string_dynamic_partial_compare_e,
    fake_f_fll_execute_arguments_add_e,
    fake_f_fll_execute_arguments_add_parameter_set_e,
    fake_f_fll_execute_program_e,
    fake_f_fll_file_mode_set_all_e,
    fake_f_fll_file_move_e,
    fake_f_fll_file_role_change_all_e,
    fake_f_fll_fss_basic_list_read_e,
    fake_f_fll_fss_extended_read_e,
    fake_f_fll_fss_snatch_apart_e,
    fake_f_fll_fss_snatch_map_apart_e,
    fake_f_fll_program_parameter_additional_rip_e,
    fake_f_fll_program_parameter_process_context_e,
    fake_f_fll_program_parameter_process_verbosity_e,
    fake_f_fake_build_arguments_standard_add_e,
    fake_f_fake_build_get_file_name_without_extension_e,
    fake_f_fake_build_load_setting_e,
    fake_f_fake_build_objects_add_e,
    fake_f_fake_build_sources_add_e,
    fake_f_fake_build_sources_object_add_e,
    fake_f_fake_execute_e,
    fake_f_fake_make_assure_inside_project_e,
    fake_f_fake_make_get_id_e,
    fake_f_fake_make_get_id_mode_e,
    fake_f_fake_make_operate_expand_build_e,
    fake_f_fake_make_operate_expand_context_e,
    fake_f_fake_make_operate_expand_environment_e,
    fake_f_fake_make_operate_process_buffer_escape_e,
    fake_f_fake_make_operate_section_e,
    fake_f_fake_make_path_relative_e,
    fake_f_fake_path_generate_string_dynamic_e,
    fake_f_fake_skeleton_operate_directory_create_e,
    fake_f_macro_f_string_map_multis_t_resize_e,
  }; // enum
#endif // _di_fake_f_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_common_print_h
