#include "fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_program_version_
  const f_string_static_t fake_program_version_s = macro_f_string_static_t_initialize(FAKE_program_version_s, 0, FAKE_program_version_s_length);
#endif // _di_fake_program_version_

#ifndef _di_fake_program_name_
  const f_string_static_t fake_program_name_s = macro_f_string_static_t_initialize(FAKE_program_name_s, 0, FAKE_program_name_s_length);
  const f_string_static_t fake_program_name_long_s = macro_f_string_static_t_initialize(FAKE_program_name_long_s, 0, FAKE_program_name_long_s_length);
#endif // _di_fake_program_name_

#ifndef _di_fake_program_help_parameters_
  const f_string_static_t fake_program_help_parameters_s = macro_f_string_static_t_initialize(FAKE_program_help_parameters_s, 0, FAKE_program_help_parameters_s_length);
#endif // _di_fake_program_help_parameters_

/**
 * The build operation utilizes pre-defined path structures.
 * These structures are hard-coded by their individual pieces to be constructed later on.
 */
#ifndef _di_fake_path_
  const f_string_static_t fake_path_part_bash_s = macro_f_string_static_t_initialize(FAKE_path_part_bash_s, 0, FAKE_path_part_bash_s_length);
  const f_string_static_t fake_path_part_build_s = macro_f_string_static_t_initialize(FAKE_path_part_build_s, 0, FAKE_path_part_build_s_length);
  const f_string_static_t fake_path_part_c_s = macro_f_string_static_t_initialize(FAKE_path_part_c_s, 0, FAKE_path_part_c_s_length);
  const f_string_static_t fake_path_part_cpp_s = macro_f_string_static_t_initialize(FAKE_path_part_cpp_s, 0, FAKE_path_part_cpp_s_length);
  const f_string_static_t fake_path_part_data_s = macro_f_string_static_t_initialize(FAKE_path_part_data_s, 0, FAKE_path_part_data_s_length);
  const f_string_static_t fake_path_part_documents_s = macro_f_string_static_t_initialize(FAKE_path_part_documents_s, 0, FAKE_path_part_documents_s_length);
  const f_string_static_t fake_path_part_includes_s = macro_f_string_static_t_initialize(FAKE_path_part_includes_s, 0, FAKE_path_part_includes_s_length);
  const f_string_static_t fake_path_part_libraries_s = macro_f_string_static_t_initialize(FAKE_path_part_libraries_s, 0, FAKE_path_part_libraries_s_length);
  const f_string_static_t fake_path_part_licenses_s = macro_f_string_static_t_initialize(FAKE_path_part_licenses_s, 0, FAKE_path_part_licenses_s_length);
  const f_string_static_t fake_path_part_objects_s = macro_f_string_static_t_initialize(FAKE_path_part_objects_s, 0, FAKE_path_part_objects_s_length);
  const f_string_static_t fake_path_part_process_s = macro_f_string_static_t_initialize(FAKE_path_part_process_s, 0, FAKE_path_part_process_s_length);
  const f_string_static_t fake_path_part_programs_s = macro_f_string_static_t_initialize(FAKE_path_part_programs_s, 0, FAKE_path_part_programs_s_length);
  const f_string_static_t fake_path_part_script_s = macro_f_string_static_t_initialize(FAKE_path_part_script_s, 0, FAKE_path_part_script_s_length);
  const f_string_static_t fake_path_part_settings_s = macro_f_string_static_t_initialize(FAKE_path_part_settings_s, 0, FAKE_path_part_settings_s_length);
  const f_string_static_t fake_path_part_shared_s = macro_f_string_static_t_initialize(FAKE_path_part_shared_s, 0, FAKE_path_part_shared_s_length);
  const f_string_static_t fake_path_part_specifications_s = macro_f_string_static_t_initialize(FAKE_path_part_specifications_s, 0, FAKE_path_part_specifications_s_length);
  const f_string_static_t fake_path_part_stage_s = macro_f_string_static_t_initialize(FAKE_path_part_stage_s, 0, FAKE_path_part_stage_s_length);
  const f_string_static_t fake_path_part_static_s = macro_f_string_static_t_initialize(FAKE_path_part_static_s, 0, FAKE_path_part_static_s_length);
#endif // _di_fake_path_

#ifndef _di_fake_file_
  const f_string_static_t fake_file_defines_s = macro_f_string_static_t_initialize(FAKE_file_defines_s, 0, FAKE_file_defines_s_length);
  const f_string_static_t fake_file_dependencies_s = macro_f_string_static_t_initialize(FAKE_file_dependencies_s, 0, FAKE_file_dependencies_s_length);
  const f_string_static_t fake_file_process_pre_s = macro_f_string_static_t_initialize(FAKE_file_process_pre_s, 0, FAKE_file_process_pre_s_length);
  const f_string_static_t fake_file_process_post_s = macro_f_string_static_t_initialize(FAKE_file_process_post_s, 0, FAKE_file_process_post_s_length);
  const f_string_static_t fake_file_readme_s = macro_f_string_static_t_initialize(FAKE_file_readme_s, 0, FAKE_file_readme_s_length);
#endif // _di_fake_file_

/**
 * Provide default settings.
 */
#ifndef _di_fake_defaults_
  const f_string_static_t fake_default_path_build_s = macro_f_string_static_t_initialize(FAKE_default_path_build_s, 0, FAKE_default_path_build_s_length);
  const f_string_static_t fake_default_path_data_s = macro_f_string_static_t_initialize(FAKE_default_path_data_s, 0, FAKE_default_path_data_s_length);
  const f_string_static_t fake_default_path_sources_s = macro_f_string_static_t_initialize(FAKE_default_path_sources_s, 0, FAKE_default_path_sources_s_length);
  const f_string_static_t fake_default_path_work_s = macro_f_string_static_t_initialize(FAKE_default_path_work_s, 0, FAKE_default_path_work_s_length);

  const f_string_static_t fake_default_define_s = macro_f_string_static_t_initialize(FAKE_default_define_s, 0, FAKE_default_define_s_length);
  const f_string_static_t fake_default_fakefile_s = macro_f_string_static_t_initialize(FAKE_default_fakefile_s, 0, FAKE_default_fakefile_s_length);
  const f_string_static_t fake_default_mode_s = macro_f_string_static_t_initialize(FAKE_default_mode_s, 0, FAKE_default_mode_s_length);
  const f_string_static_t fake_default_process_s = macro_f_string_static_t_initialize(FAKE_default_process_s, 0, FAKE_default_process_s_length);
  const f_string_static_t fake_default_settings_s = macro_f_string_static_t_initialize(FAKE_default_settings_s, 0, FAKE_default_settings_s_length);
#endif // _di_fake_defaults_

#ifndef _di_fake_build_language_
  const f_string_static_t fake_build_language_bash_s = macro_f_string_static_t_initialize(FAKE_build_language_bash_s, 0, FAKE_build_language_bash_s_length);
  const f_string_static_t fake_build_language_c_s = macro_f_string_static_t_initialize(FAKE_build_language_c_s, 0, FAKE_build_language_c_s_length);
  const f_string_static_t fake_build_language_cpp_s = macro_f_string_static_t_initialize(FAKE_build_language_cpp_s, 0, FAKE_build_language_cpp_s_length);
#endif // _di_fake_build_language_

#ifndef _di_fake_build_version_
  const f_string_static_t fake_build_version_major_s = macro_f_string_static_t_initialize(FAKE_build_version_major_s, 0, FAKE_build_version_major_s_length);
  const f_string_static_t fake_build_version_minor_s = macro_f_string_static_t_initialize(FAKE_build_version_minor_s, 0, FAKE_build_version_minor_s_length);
  const f_string_static_t fake_build_version_micro_s = macro_f_string_static_t_initialize(FAKE_build_version_micro_s, 0, FAKE_build_version_micro_s_length);
  const f_string_static_t fake_build_version_nano_s = macro_f_string_static_t_initialize(FAKE_build_version_nano_s, 0, FAKE_build_version_nano_s_length);
#endif // _di_fake_build_version_

#ifndef _di_fake_parameters_
  const f_string_static_t fake_short_define_s = macro_f_string_static_t_initialize(FAKE_short_define_s, 0, FAKE_short_define_s_length);
  const f_string_static_t fake_short_fakefile_s = macro_f_string_static_t_initialize(FAKE_short_fakefile_s, 0, FAKE_short_fakefile_s_length);
  const f_string_static_t fake_short_mode_s = macro_f_string_static_t_initialize(FAKE_short_mode_s, 0, FAKE_short_mode_s_length);
  const f_string_static_t fake_short_process_s = macro_f_string_static_t_initialize(FAKE_short_process_s, 0, FAKE_short_process_s_length);
  const f_string_static_t fake_short_settings_s = macro_f_string_static_t_initialize(FAKE_short_settings_s, 0, FAKE_short_settings_s_length);

  const f_string_static_t fake_short_path_build_s = macro_f_string_static_t_initialize(FAKE_short_path_build_s, 0, FAKE_short_path_build_s_length);
  const f_string_static_t fake_short_path_data_s = macro_f_string_static_t_initialize(FAKE_short_path_data_s, 0, FAKE_short_path_data_s_length);
  const f_string_static_t fake_short_path_sources_s = macro_f_string_static_t_initialize(FAKE_short_path_sources_s, 0, FAKE_short_path_sources_s_length);
  const f_string_static_t fake_short_path_work_s = macro_f_string_static_t_initialize(FAKE_short_path_work_s, 0, FAKE_short_path_work_s_length);

  const f_string_static_t fake_long_define_s = macro_f_string_static_t_initialize(FAKE_long_define_s, 0, FAKE_long_define_s_length);
  const f_string_static_t fake_long_fakefile_s = macro_f_string_static_t_initialize(FAKE_long_fakefile_s, 0, FAKE_long_fakefile_s_length);
  const f_string_static_t fake_long_mode_s = macro_f_string_static_t_initialize(FAKE_long_mode_s, 0, FAKE_long_mode_s_length);
  const f_string_static_t fake_long_process_s = macro_f_string_static_t_initialize(FAKE_long_process_s, 0, FAKE_long_process_s_length);
  const f_string_static_t fake_long_settings_s = macro_f_string_static_t_initialize(FAKE_long_settings_s, 0, FAKE_long_settings_s_length);

  const f_string_static_t fake_long_path_build_s = macro_f_string_static_t_initialize(FAKE_long_path_build_s, 0, FAKE_long_path_build_s_length);
  const f_string_static_t fake_long_path_data_s = macro_f_string_static_t_initialize(FAKE_long_path_data_s, 0, FAKE_long_path_data_s_length);
  const f_string_static_t fake_long_path_sources_s = macro_f_string_static_t_initialize(FAKE_long_path_sources_s, 0, FAKE_long_path_sources_s_length);
  const f_string_static_t fake_long_path_work_s = macro_f_string_static_t_initialize(FAKE_long_path_work_s, 0, FAKE_long_path_work_s_length);

  const f_string_static_t fake_long_documents_disabled_s = macro_f_string_static_t_initialize(FAKE_long_documents_disabled_s, 0, FAKE_long_documents_disabled_s_length);
  const f_string_static_t fake_long_documents_enabled_s = macro_f_string_static_t_initialize(FAKE_long_documents_enabled_s, 0, FAKE_long_documents_enabled_s_length);
  const f_string_static_t fake_long_shared_disabled_s = macro_f_string_static_t_initialize(FAKE_long_shared_disabled_s, 0, FAKE_long_shared_disabled_s_length);
  const f_string_static_t fake_long_shared_enabled_s = macro_f_string_static_t_initialize(FAKE_long_shared_enabled_s, 0, FAKE_long_shared_enabled_s_length);
  const f_string_static_t fake_long_static_disabled_s = macro_f_string_static_t_initialize(FAKE_long_static_disabled_s, 0, FAKE_long_static_disabled_s_length);
  const f_string_static_t fake_long_static_enabled_s = macro_f_string_static_t_initialize(FAKE_long_static_enabled_s, 0, FAKE_long_static_enabled_s_length);

  const f_string_static_t fake_other_operation_build_s = macro_f_string_static_t_initialize(FAKE_other_operation_build_s, 0, FAKE_other_operation_build_s_length);
  const f_string_static_t fake_other_operation_clean_s = macro_f_string_static_t_initialize(FAKE_other_operation_clean_s, 0, FAKE_other_operation_clean_s_length);
  const f_string_static_t fake_other_operation_make_s = macro_f_string_static_t_initialize(FAKE_other_operation_make_s, 0, FAKE_other_operation_make_s_length);
  const f_string_static_t fake_other_operation_skeleton_s = macro_f_string_static_t_initialize(FAKE_other_operation_skeleton_s, 0, FAKE_other_operation_skeleton_s_length);
#endif // _di_fake_parameters_

#ifndef _di_fake_setting_delete_
  f_status_t fake_setting_delete(fake_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    return F_none;
  }
#endif // _di_fake_setting_delete_

#ifndef _di_fake_setting_load_
  void fake_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, fake_setting_t * const setting) {

    if (!main || !setting) return;

    setting->flag = 0;

    // Load parameters.
    setting->status = f_console_parameter_process(arguments, &main->parameters);

    if (F_status_is_error(setting->status)) {
      fake_print_line_first_locked(setting, main->error);
      fll_error_print(main->error, F_status_set_fine(setting->status), "f_console_parameter_process", F_true);
      fake_print_line_last_locked(setting, main->error);

      return;
    }

    {
      f_array_length_t choice = 0;
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { fake_parameter_no_color_e, fake_parameter_light_e, fake_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        const uint8_t modes[3] = { f_color_mode_color_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        setting->status = fll_program_parameter_process_context(choices, modes, F_true, main);

        if (F_status_is_error(setting->status)) {
          fake_print_line_first_locked(setting, main->error);
          fll_error_print(main->error, F_status_set_fine(setting->status), "fll_program_parameter_process_context", F_true);
          fake_print_line_last_locked(setting, main->error);

          return;
        }
      }

      if (main->parameters.array[fake_parameter_line_first_no_e].result & f_console_result_found_e) {
        setting->line_first = f_string_empty_s;
      }
      else {
        setting->line_first = f_string_eol_s;
      }

      if (main->parameters.array[fake_parameter_line_last_no_e].result & f_console_result_found_e) {
        setting->line_last = f_string_empty_s;
      }
      else {
        setting->line_last = f_string_eol_s;
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { fake_parameter_verbosity_quiet_e, fake_parameter_verbosity_error_e, fake_parameter_verbosity_verbose_e, fake_parameter_verbosity_debug_e, fake_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        setting->status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, main);

        if (F_status_is_error(setting->status)) {
          fake_print_line_first_locked(setting, main->error);
          fll_error_print(main->error, F_status_set_fine(setting->status), "fll_program_parameter_process_verbosity", F_true);
          fake_print_line_last_locked(setting, main->error);

          return;
        }
      }

      if (main->parameters.array[fake_parameter_help_e].result & f_console_result_found_e) {
        setting->flag |= fake_main_flag_help_e;

        return;
      }

      if (main->parameters.array[fake_parameter_version_e].result & f_console_result_found_e) {
        setting->flag |= fake_main_flag_version_e;

        return;
      }
    }

    main->output.to.id = F_type_descriptor_output_d;
    main->output.to.stream = F_type_output_d;
    main->output.to.flag = F_file_flag_create_d | F_file_flag_write_only_d | F_file_flag_append_d;

    f_string_static_t * const args = main->parameters.arguments.array;

    if (main->parameters.array[fake_parameter_strip_invalid_e].result & f_console_result_found_e) {
      setting->flag |= fake_main_flag_strip_invalid_e;
    }
  }
#endif // _di_fake_setting_load_

#ifndef _di_fake_setting_unload_
  f_status_t fake_setting_unload(fll_program_data_t * const main, fake_setting_t * const setting) {

    if (!main || !setting) return F_status_set_error(F_parameter);

    fake_setting_delete(setting);

    return F_none;
  }
#endif // _di_fake_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif
