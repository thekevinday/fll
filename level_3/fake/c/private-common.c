#include "fake.h"
#include "private-common.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_setting_t_
  const f_string_t fake_build_setting_name_build_compiler_s = FAKE_build_setting_name_build_compiler_s;
  const f_string_t fake_build_setting_name_build_language_s = FAKE_build_setting_name_build_language_s;
  const f_string_t fake_build_setting_name_build_libraries_s = FAKE_build_setting_name_build_libraries_s;
  const f_string_t fake_build_setting_name_build_libraries_shared_s = FAKE_build_setting_name_build_libraries_shared_s;
  const f_string_t fake_build_setting_name_build_libraries_static_s = FAKE_build_setting_name_build_libraries_static_s;
  const f_string_t fake_build_setting_name_build_indexer_s = FAKE_build_setting_name_build_indexer_s;
  const f_string_t fake_build_setting_name_build_indexer_arguments_s = FAKE_build_setting_name_build_indexer_arguments_s;
  const f_string_t fake_build_setting_name_build_script_s = FAKE_build_setting_name_build_script_s;
  const f_string_t fake_build_setting_name_build_shared_s = FAKE_build_setting_name_build_shared_s;
  const f_string_t fake_build_setting_name_build_sources_headers_s = FAKE_build_setting_name_build_sources_headers_s;
  const f_string_t fake_build_setting_name_build_sources_headers_shared_s = FAKE_build_setting_name_build_sources_headers_shared_s;
  const f_string_t fake_build_setting_name_build_sources_headers_static_s = FAKE_build_setting_name_build_sources_headers_static_s;
  const f_string_t fake_build_setting_name_build_sources_library_s = FAKE_build_setting_name_build_sources_library_s;
  const f_string_t fake_build_setting_name_build_sources_library_shared_s = FAKE_build_setting_name_build_sources_library_shared_s;
  const f_string_t fake_build_setting_name_build_sources_library_static_s = FAKE_build_setting_name_build_sources_library_static_s;
  const f_string_t fake_build_setting_name_build_sources_program_s = FAKE_build_setting_name_build_sources_program_s;
  const f_string_t fake_build_setting_name_build_sources_program_shared_s = FAKE_build_setting_name_build_sources_program_shared_s;
  const f_string_t fake_build_setting_name_build_sources_program_static_s = FAKE_build_setting_name_build_sources_program_static_s;
  const f_string_t fake_build_setting_name_build_sources_script_s = FAKE_build_setting_name_build_sources_script_s;
  const f_string_t fake_build_setting_name_build_sources_settings_s = FAKE_build_setting_name_build_sources_settings_s;
  const f_string_t fake_build_setting_name_build_static_s = FAKE_build_setting_name_build_static_s;
  const f_string_t fake_build_setting_name_defines_s = FAKE_build_setting_name_defines_s;
  const f_string_t fake_build_setting_name_defines_library_s = FAKE_build_setting_name_defines_library_s;
  const f_string_t fake_build_setting_name_defines_library_shared_s = FAKE_build_setting_name_defines_library_shared_s;
  const f_string_t fake_build_setting_name_defines_library_static_s = FAKE_build_setting_name_defines_library_static_s;
  const f_string_t fake_build_setting_name_defines_program_s = FAKE_build_setting_name_defines_program_s;
  const f_string_t fake_build_setting_name_defines_program_shared_s = FAKE_build_setting_name_defines_program_shared_s;
  const f_string_t fake_build_setting_name_defines_program_static_s = FAKE_build_setting_name_defines_program_static_s;
  const f_string_t fake_build_setting_name_defines_shared_s = FAKE_build_setting_name_defines_shared_s;
  const f_string_t fake_build_setting_name_defines_static_s = FAKE_build_setting_name_defines_static_s;
  const f_string_t fake_build_setting_name_environment_s = FAKE_build_setting_name_environment_s;
  const f_string_t fake_build_setting_name_flags_s = FAKE_build_setting_name_flags_s;
  const f_string_t fake_build_setting_name_flags_library_s = FAKE_build_setting_name_flags_library_s;
  const f_string_t fake_build_setting_name_flags_library_shared_s = FAKE_build_setting_name_flags_library_shared_s;
  const f_string_t fake_build_setting_name_flags_library_static_s = FAKE_build_setting_name_flags_library_static_s;
  const f_string_t fake_build_setting_name_flags_program_s = FAKE_build_setting_name_flags_program_s;
  const f_string_t fake_build_setting_name_flags_program_shared_s = FAKE_build_setting_name_flags_program_shared_s;
  const f_string_t fake_build_setting_name_flags_program_static_s = FAKE_build_setting_name_flags_program_static_s;
  const f_string_t fake_build_setting_name_flags_shared_s = FAKE_build_setting_name_flags_shared_s;
  const f_string_t fake_build_setting_name_flags_static_s = FAKE_build_setting_name_flags_static_s;
  const f_string_t fake_build_setting_name_modes_s = FAKE_build_setting_name_modes_s;
  const f_string_t fake_build_setting_name_modes_default_s = FAKE_build_setting_name_modes_default_s;
  const f_string_t fake_build_setting_name_path_headers_s = FAKE_build_setting_name_path_headers_s;
  const f_string_t fake_build_setting_name_path_headers_preserve_s = FAKE_build_setting_name_path_headers_preserve_s;
  const f_string_t fake_build_setting_name_path_language_s = FAKE_build_setting_name_path_language_s;
  const f_string_t fake_build_setting_name_path_library_script_s = FAKE_build_setting_name_path_library_script_s;
  const f_string_t fake_build_setting_name_path_library_shared_s = FAKE_build_setting_name_path_library_shared_s;
  const f_string_t fake_build_setting_name_path_library_static_s = FAKE_build_setting_name_path_library_static_s;
  const f_string_t fake_build_setting_name_path_program_script_s = FAKE_build_setting_name_path_program_script_s;
  const f_string_t fake_build_setting_name_path_program_shared_s = FAKE_build_setting_name_path_program_shared_s;
  const f_string_t fake_build_setting_name_path_program_static_s = FAKE_build_setting_name_path_program_static_s;
  const f_string_t fake_build_setting_name_path_sources_s = FAKE_build_setting_name_path_sources_s;
  const f_string_t fake_build_setting_name_path_standard_s = FAKE_build_setting_name_path_standard_s;
  const f_string_t fake_build_setting_name_process_post_s = FAKE_build_setting_name_process_post_s;
  const f_string_t fake_build_setting_name_process_pre_s = FAKE_build_setting_name_process_pre_s;
  const f_string_t fake_build_setting_name_project_name_s = FAKE_build_setting_name_project_name_s;
  const f_string_t fake_build_setting_name_search_exclusive_s = FAKE_build_setting_name_search_exclusive_s;
  const f_string_t fake_build_setting_name_search_shared_s = FAKE_build_setting_name_search_shared_s;
  const f_string_t fake_build_setting_name_search_static_s = FAKE_build_setting_name_search_static_s;
  const f_string_t fake_build_setting_name_version_file_s = FAKE_build_setting_name_version_file_s;
  const f_string_t fake_build_setting_name_version_major_s = FAKE_build_setting_name_version_major_s;
  const f_string_t fake_build_setting_name_version_major_prefix_s = FAKE_build_setting_name_version_major_prefix_s;
  const f_string_t fake_build_setting_name_version_micro_s = FAKE_build_setting_name_version_micro_s;
  const f_string_t fake_build_setting_name_version_micro_prefix_s = FAKE_build_setting_name_version_micro_prefix_s;
  const f_string_t fake_build_setting_name_version_minor_s = FAKE_build_setting_name_version_minor_s;
  const f_string_t fake_build_setting_name_version_minor_prefix_s = FAKE_build_setting_name_version_minor_prefix_s;
  const f_string_t fake_build_setting_name_version_nano_s = FAKE_build_setting_name_version_nano_s;
  const f_string_t fake_build_setting_name_version_nano_prefix_s = FAKE_build_setting_name_version_nano_prefix_s;
  const f_string_t fake_build_setting_name_version_target_s = FAKE_build_setting_name_version_target_s;

  const f_string_t fake_build_setting_default_version_s = FAKE_build_setting_default_version_s;
  const f_string_t fake_build_setting_default_version_prefix_s = FAKE_build_setting_default_version_prefix_s;
#endif // _di_fake_build_setting_t_

#ifndef _di_fake_build_stage_t_
  const f_string_t fake_build_stage_built_s = FAKE_build_stage_built_s;
  const f_string_t fake_build_stage_libraries_script_s = FAKE_build_stage_libraries_script_s;
  const f_string_t fake_build_stage_libraries_shared_s = FAKE_build_stage_libraries_shared_s;
  const f_string_t fake_build_stage_libraries_static_s = FAKE_build_stage_libraries_static_s;
  const f_string_t fake_build_stage_objects_static_s = FAKE_build_stage_objects_static_s;
  const f_string_t fake_build_stage_process_post_s = FAKE_build_stage_process_post_s;
  const f_string_t fake_build_stage_process_pre_s = FAKE_build_stage_process_pre_s;
  const f_string_t fake_build_stage_programs_script_s = FAKE_build_stage_programs_script_s;
  const f_string_t fake_build_stage_programs_shared_s = FAKE_build_stage_programs_shared_s;
  const f_string_t fake_build_stage_programs_static_s = FAKE_build_stage_programs_static_s;
  const f_string_t fake_build_stage_separate_s = FAKE_build_stage_separate_s;
  const f_string_t fake_build_stage_skeleton_s = FAKE_build_stage_skeleton_s;
  const f_string_t fake_build_stage_sources_headers_s = FAKE_build_stage_sources_headers_s;
  const f_string_t fake_build_stage_sources_script_s = FAKE_build_stage_sources_script_s;
  const f_string_t fake_build_stage_sources_settings_s = FAKE_build_stage_sources_settings_s;
#endif // _di_fake_build_stage_t_

#ifndef _di_fake_build_parameter_
  const f_string_t fake_build_parameter_library_include_s = FAKE_build_parameter_library_include_s;
  const f_string_t fake_build_parameter_library_link_file_s = FAKE_build_parameter_library_link_file_s;
  const f_string_t fake_build_parameter_library_link_path_s = FAKE_build_parameter_library_link_path_s;
  const f_string_t fake_build_parameter_library_name_prefix_s = FAKE_build_parameter_library_name_prefix_s;
  const f_string_t fake_build_parameter_library_name_suffix_shared_s = FAKE_build_parameter_library_name_suffix_shared_s;
  const f_string_t fake_build_parameter_library_name_suffix_static_s = FAKE_build_parameter_library_name_suffix_static_s;
  const f_string_t fake_build_parameter_library_output_s = FAKE_build_parameter_library_output_s;
  const f_string_t fake_build_parameter_library_shared_s = FAKE_build_parameter_library_shared_s;
  const f_string_t fake_build_parameter_library_static_s = FAKE_build_parameter_library_static_s;
  const f_string_t fake_build_parameter_library_shared_prefix_s = FAKE_build_parameter_library_shared_prefix_s;

  const f_string_t fake_build_parameter_object_compile_s = FAKE_build_parameter_object_compile_s;
  const f_string_t fake_build_parameter_object_name_suffix_s = FAKE_build_parameter_object_name_suffix_s;
  const f_string_t fake_build_parameter_object_output_s = FAKE_build_parameter_object_output_s;
  const f_string_t fake_build_parameter_object_static_s = FAKE_build_parameter_object_static_s;
#endif // _di_fake_build_parameter_

#ifndef _di_fake_common_
  const f_string_t fake_common_setting_bool_yes_s = FAKE_common_setting_bool_yes_s;
  const f_string_t fake_common_setting_bool_no_s = FAKE_common_setting_bool_no_s;
#endif // _di_fake_common_

#ifndef _di_fake_make_section_
  const f_string_t fake_make_section_main_s = FAKE_make_section_main_s;
  const f_string_t fake_make_section_settings_s = FAKE_make_section_settings_s;
#endif // _di_fake_make_section_

#ifndef _di_fake_make_setting_t_
  const f_string_t fake_make_setting_compiler_s = FAKE_make_setting_compiler_s;
  const f_string_t fake_make_setting_define_s = FAKE_make_setting_define_s;
  const f_string_t fake_make_setting_environment_s = FAKE_make_setting_environment_s;
  const f_string_t fake_make_setting_fail_s = FAKE_make_setting_fail_s;
  const f_string_t fake_make_setting_indexer_s = FAKE_make_setting_indexer_s;
  const f_string_t fake_make_setting_indexer_arguments_s = FAKE_make_setting_indexer_arguments_s;
  const f_string_t fake_make_setting_load_build_s = FAKE_make_setting_load_build_s;
  const f_string_t fake_make_setting_parameter_s = FAKE_make_setting_parameter_s;
  const f_string_t fake_make_setting_return_s = FAKE_make_setting_return_s;
#endif // _di_fake_make_setting_t_

#ifndef _di_fake_make_operation_
  const f_string_t fake_make_operation_break_s = FAKE_make_operation_break_s;
  const f_string_t fake_make_operation_build_s = FAKE_make_operation_build_s;
  const f_string_t fake_make_operation_clean_s = FAKE_make_operation_clean_s;
  const f_string_t fake_make_operation_clone_s = FAKE_make_operation_clone_s;
  const f_string_t fake_make_operation_compile_s = FAKE_make_operation_compile_s;
  const f_string_t fake_make_operation_copy_s = FAKE_make_operation_copy_s;
  const f_string_t fake_make_operation_define_s = FAKE_make_operation_define_s;
  const f_string_t fake_make_operation_delete_s = FAKE_make_operation_delete_s;
  const f_string_t fake_make_operation_deletes_s = FAKE_make_operation_deletes_s;
  const f_string_t fake_make_operation_else_s = FAKE_make_operation_else_s;
  const f_string_t fake_make_operation_exit_s = FAKE_make_operation_exit_s;
  const f_string_t fake_make_operation_fail_s = FAKE_make_operation_fail_s;
  const f_string_t fake_make_operation_group_s = FAKE_make_operation_group_s;
  const f_string_t fake_make_operation_groups_s = FAKE_make_operation_groups_s;
  const f_string_t fake_make_operation_if_s = FAKE_make_operation_if_s;
  const f_string_t fake_make_operation_index_s = FAKE_make_operation_index_s;
  const f_string_t fake_make_operation_link_s = FAKE_make_operation_link_s;
  const f_string_t fake_make_operation_mode_s = FAKE_make_operation_mode_s;
  const f_string_t fake_make_operation_modes_s = FAKE_make_operation_modes_s;
  const f_string_t fake_make_operation_move_s = FAKE_make_operation_move_s;
  const f_string_t fake_make_operation_operate_s = FAKE_make_operation_operate_s;
  const f_string_t fake_make_operation_owner_s = FAKE_make_operation_owner_s;
  const f_string_t fake_make_operation_owners_s = FAKE_make_operation_owners_s;
  const f_string_t fake_make_operation_pop_s = FAKE_make_operation_pop_s;
  const f_string_t fake_make_operation_print_s = FAKE_make_operation_print_s;
  const f_string_t fake_make_operation_run_s = FAKE_make_operation_run_s;
  const f_string_t fake_make_operation_shell_s = FAKE_make_operation_shell_s;
  const f_string_t fake_make_operation_skeleton_s = FAKE_make_operation_skeleton_s;
  const f_string_t fake_make_operation_to_s = FAKE_make_operation_to_s;
  const f_string_t fake_make_operation_top_s = FAKE_make_operation_top_s;
  const f_string_t fake_make_operation_touch_s = FAKE_make_operation_touch_s;

  const f_string_t fake_make_operation_argument_environment_s = FAKE_make_operation_argument_environment_s;
  const f_string_t fake_make_operation_argument_failure_s = FAKE_make_operation_argument_failure_s;
  const f_string_t fake_make_operation_argument_file_s = FAKE_make_operation_argument_file_s;
  const f_string_t fake_make_operation_argument_directory_s = FAKE_make_operation_argument_directory_s;
  const f_string_t fake_make_operation_argument_error_s = FAKE_make_operation_argument_error_s;
  const f_string_t fake_make_operation_argument_exit_s = FAKE_make_operation_argument_exit_s;
  const f_string_t fake_make_operation_argument_has_s = FAKE_make_operation_argument_has_s;
  const f_string_t fake_make_operation_argument_ignore_s = FAKE_make_operation_argument_ignore_s;
  const f_string_t fake_make_operation_argument_is_s = FAKE_make_operation_argument_is_s;
  const f_string_t fake_make_operation_argument_parameter_s = FAKE_make_operation_argument_parameter_s;
  const f_string_t fake_make_operation_argument_point_s = FAKE_make_operation_argument_point_s;
  const f_string_t fake_make_operation_argument_recursive_s = FAKE_make_operation_argument_recursive_s;
  const f_string_t fake_make_operation_argument_success_s = FAKE_make_operation_argument_success_s;
  const f_string_t fake_make_operation_argument_target_s = FAKE_make_operation_argument_target_s;
  const f_string_t fake_make_operation_argument_warn_s = FAKE_make_operation_argument_warn_s;

  const f_string_t fake_make_operation_argument_if_defined_s = FAKE_make_operation_argument_if_defined_s;
  const f_string_t fake_make_operation_argument_if_equal_s = FAKE_make_operation_argument_if_equal_s;
  const f_string_t fake_make_operation_argument_if_equal_not_s = FAKE_make_operation_argument_if_equal_not_s;
  const f_string_t fake_make_operation_argument_if_exists_s = FAKE_make_operation_argument_if_exists_s;
  const f_string_t fake_make_operation_argument_if_failure_s = FAKE_make_operation_argument_if_failure_s;
  const f_string_t fake_make_operation_argument_if_greater_s = FAKE_make_operation_argument_if_greater_s;
  const f_string_t fake_make_operation_argument_if_greater_equal_s = FAKE_make_operation_argument_if_greater_equal_s;
  const f_string_t fake_make_operation_argument_if_group_s = FAKE_make_operation_argument_if_group_s;
  const f_string_t fake_make_operation_argument_if_is_s = FAKE_make_operation_argument_if_is_s;
  const f_string_t fake_make_operation_argument_if_is_for_s = FAKE_make_operation_argument_if_is_for_s;
  const f_string_t fake_make_operation_argument_if_less_s = FAKE_make_operation_argument_if_less_s;
  const f_string_t fake_make_operation_argument_if_less_equal_s = FAKE_make_operation_argument_if_less_equal_s;
  const f_string_t fake_make_operation_argument_if_mode_s = FAKE_make_operation_argument_if_mode_s;
  const f_string_t fake_make_operation_argument_if_owner_s = FAKE_make_operation_argument_if_owner_s;
  const f_string_t fake_make_operation_argument_if_success_s = FAKE_make_operation_argument_if_success_s;
#endif // _di_fake_make_operation_

#ifndef _di_fake_make_parameter_t_
  const f_string_t fake_make_parameter_variable_build_s = FAKE_make_parameter_variable_build_s;
  const f_string_t fake_make_parameter_variable_color_s = FAKE_make_parameter_variable_color_s;
  const f_string_t fake_make_parameter_variable_data_s = FAKE_make_parameter_variable_data_s;
  const f_string_t fake_make_parameter_variable_define_s = FAKE_make_parameter_variable_define_s;
  const f_string_t fake_make_parameter_variable_fakefile_s = FAKE_make_parameter_variable_fakefile_s;
  const f_string_t fake_make_parameter_variable_mode_s = FAKE_make_parameter_variable_mode_s;
  const f_string_t fake_make_parameter_variable_process_s = FAKE_make_parameter_variable_process_s;
  const f_string_t fake_make_parameter_variable_return_s = FAKE_make_parameter_variable_return_s;
  const f_string_t fake_make_parameter_variable_settings_s = FAKE_make_parameter_variable_settings_s;
  const f_string_t fake_make_parameter_variable_sources_s = FAKE_make_parameter_variable_sources_s;
  const f_string_t fake_make_parameter_variable_verbosity_s = FAKE_make_parameter_variable_verbosity_s;
  const f_string_t fake_make_parameter_variable_work_s = FAKE_make_parameter_variable_work_s;
#endif // _di_fake_make_parameter_t_

#ifndef _di_fake_skeleton_content_
  const f_string_t fake_make_skeleton_content_defines_s = FAKE_make_skeleton_content_defines_s;
  const f_string_t fake_make_skeleton_content_dependencies_s = FAKE_make_skeleton_content_dependencies_s;
  const f_string_t fake_make_skeleton_content_fakefile_s = FAKE_make_skeleton_content_fakefile_s;
  const f_string_t fake_make_skeleton_content_settings_s = FAKE_make_skeleton_content_settings_s;
#endif // _di_fake_skeleton_content_

#ifndef _di_fake_signal_received_
  f_status_t fake_signal_received(fake_main_t * const main) {

    if (!main->signal.id) {
      return F_false;
    }

    struct signalfd_siginfo information;

    memset(&information, 0, sizeof(struct signalfd_siginfo));

    if (f_signal_read(main->signal, 0, &information) == F_signal) {
      switch (information.ssi_signo) {
        case F_signal_abort:
        case F_signal_broken_pipe:
        case F_signal_hangup:
        case F_signal_interrupt:
        case F_signal_quit:
        case F_signal_termination:
          fake_print_signal_received(main, information.ssi_signo);

          return information.ssi_signo;
      }
    }

    return F_false;
  }
#endif // _di_fake_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif
