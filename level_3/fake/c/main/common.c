#include "fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_program_version_s_
  const f_string_static_t fake_program_version_s = macro_f_string_static_t_initialize(FAKE_program_version_s, 0, FAKE_program_version_s_length);
#endif // _di_fake_program_version_s_

#ifndef _di_fake_program_name_s_
  const f_string_static_t fake_program_name_s = macro_f_string_static_t_initialize(FAKE_program_name_s, 0, FAKE_program_name_s_length);
  const f_string_static_t fake_program_name_long_s = macro_f_string_static_t_initialize(FAKE_program_name_long_s, 0, FAKE_program_name_long_s_length);
#endif // _di_fake_program_name_s_

#ifndef _di_fake_program_help_parameter_s_
  const f_string_static_t fake_program_help_parameters_s = macro_f_string_static_t_initialize(FAKE_program_help_parameters_s, 0, FAKE_program_help_parameters_s_length);
#endif // _di_fake_program_help_parameter_s_

#ifndef _di_fake_path_s_
  const f_string_static_t fake_path_part_build_s = macro_f_string_static_t_initialize(FAKE_path_part_build_s, 0, FAKE_path_part_build_s_length);
  const f_string_static_t fake_path_part_c_s = macro_f_string_static_t_initialize(FAKE_path_part_c_s, 0, FAKE_path_part_c_s_length);
  const f_string_static_t fake_path_part_cpp_s = macro_f_string_static_t_initialize(FAKE_path_part_cpp_s, 0, FAKE_path_part_cpp_s_length);
  const f_string_static_t fake_path_part_data_s = macro_f_string_static_t_initialize(FAKE_path_part_data_s, 0, FAKE_path_part_data_s_length);
  const f_string_static_t fake_path_part_documentation_s = macro_f_string_static_t_initialize(FAKE_path_part_documentation_s, 0, FAKE_path_part_documentation_s_length);
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
  const f_string_static_t fake_path_part_shell_s = macro_f_string_static_t_initialize(FAKE_path_part_shell_s, 0, FAKE_path_part_shell_s_length);
  const f_string_static_t fake_path_part_specifications_s = macro_f_string_static_t_initialize(FAKE_path_part_specifications_s, 0, FAKE_path_part_specifications_s_length);
  const f_string_static_t fake_path_part_stage_s = macro_f_string_static_t_initialize(FAKE_path_part_stage_s, 0, FAKE_path_part_stage_s_length);
  const f_string_static_t fake_path_part_static_s = macro_f_string_static_t_initialize(FAKE_path_part_static_s, 0, FAKE_path_part_static_s_length);
#endif // _di_fake_path_s_

#ifndef _di_fake_file_s_
  const f_string_static_t fake_file_defines_s = macro_f_string_static_t_initialize(FAKE_file_defines_s, 0, FAKE_file_defines_s_length);
  const f_string_static_t fake_file_dependencies_s = macro_f_string_static_t_initialize(FAKE_file_dependencies_s, 0, FAKE_file_dependencies_s_length);
  const f_string_static_t fake_file_process_pre_s = macro_f_string_static_t_initialize(FAKE_file_process_pre_s, 0, FAKE_file_process_pre_s_length);
  const f_string_static_t fake_file_process_post_s = macro_f_string_static_t_initialize(FAKE_file_process_post_s, 0, FAKE_file_process_post_s_length);
  const f_string_static_t fake_file_readme_s = macro_f_string_static_t_initialize(FAKE_file_readme_s, 0, FAKE_file_readme_s_length);
#endif // _di_fake_file_s_

/**
 * Provide default settings.
 */
#ifndef _di_fake_default_s_
  const f_string_static_t fake_default_path_build_s = macro_f_string_static_t_initialize(FAKE_default_path_build_s, 0, FAKE_default_path_build_s_length);
  const f_string_static_t fake_default_path_data_s = macro_f_string_static_t_initialize(FAKE_default_path_data_s, 0, FAKE_default_path_data_s_length);
  const f_string_static_t fake_default_path_sources_s = macro_f_string_static_t_initialize(FAKE_default_path_sources_s, 0, FAKE_default_path_sources_s_length);
  const f_string_static_t fake_default_path_work_s = macro_f_string_static_t_initialize(FAKE_default_path_work_s, 0, FAKE_default_path_work_s_length);

  const f_string_static_t fake_default_fakefile_s = macro_f_string_static_t_initialize(FAKE_default_fakefile_s, 0, FAKE_default_fakefile_s_length);
  const f_string_static_t fake_default_process_s = macro_f_string_static_t_initialize(FAKE_default_process_s, 0, FAKE_default_process_s_length);
  const f_string_static_t fake_default_settings_s = macro_f_string_static_t_initialize(FAKE_default_settings_s, 0, FAKE_default_settings_s_length);
#endif // _di_fake_default_s_

#ifndef _di_fake_build_language_s_
  const f_string_static_t fake_build_language_bash_s = macro_f_string_static_t_initialize(FAKE_build_language_bash_s, 0, FAKE_build_language_bash_s_length);
  const f_string_static_t fake_build_language_c_s = macro_f_string_static_t_initialize(FAKE_build_language_c_s, 0, FAKE_build_language_c_s_length);
  const f_string_static_t fake_build_language_cpp_s = macro_f_string_static_t_initialize(FAKE_build_language_cpp_s, 0, FAKE_build_language_cpp_s_length);
  const f_string_static_t fake_build_language_zsh_s = macro_f_string_static_t_initialize(FAKE_build_language_zsh_s, 0, FAKE_build_language_zsh_s_length);
#endif // _di_fake_build_language_s_

#ifndef _di_fake_build_version_s_
  const f_string_static_t fake_build_version_major_s = macro_f_string_static_t_initialize(FAKE_build_version_major_s, 0, FAKE_build_version_major_s_length);
  const f_string_static_t fake_build_version_minor_s = macro_f_string_static_t_initialize(FAKE_build_version_minor_s, 0, FAKE_build_version_minor_s_length);
  const f_string_static_t fake_build_version_micro_s = macro_f_string_static_t_initialize(FAKE_build_version_micro_s, 0, FAKE_build_version_micro_s_length);
  const f_string_static_t fake_build_version_nano_s = macro_f_string_static_t_initialize(FAKE_build_version_nano_s, 0, FAKE_build_version_nano_s_length);
#endif // _di_fake_build_version_s_

#ifndef _di_fake_parameter_d_
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
#endif // _di_fake_parameter_d_

#ifndef _di_fake_setting_delete_
  f_status_t fake_setting_delete(fake_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    f_string_dynamic_resize(0, &setting->build);
    f_string_dynamic_resize(0, &setting->data);
    f_string_dynamic_resize(0, &setting->fakefile);
    f_string_dynamic_resize(0, &setting->process);
    f_string_dynamic_resize(0, &setting->settings);
    f_string_dynamic_resize(0, &setting->sources);
    f_string_dynamic_resize(0, &setting->work);
    f_string_dynamic_resize(0, &setting->path_build);
    f_string_dynamic_resize(0, &setting->path_build_documentation);
    f_string_dynamic_resize(0, &setting->path_build_documents);
    f_string_dynamic_resize(0, &setting->path_build_includes);
    f_string_dynamic_resize(0, &setting->path_build_libraries);
    f_string_dynamic_resize(0, &setting->path_build_libraries_script);
    f_string_dynamic_resize(0, &setting->path_build_libraries_shared);
    f_string_dynamic_resize(0, &setting->path_build_libraries_static);
    f_string_dynamic_resize(0, &setting->path_build_objects);
    f_string_dynamic_resize(0, &setting->path_build_objects_script);
    f_string_dynamic_resize(0, &setting->path_build_objects_shared);
    f_string_dynamic_resize(0, &setting->path_build_objects_static);
    f_string_dynamic_resize(0, &setting->path_build_programs);
    f_string_dynamic_resize(0, &setting->path_build_programs_script);
    f_string_dynamic_resize(0, &setting->path_build_programs_shared);
    f_string_dynamic_resize(0, &setting->path_build_programs_static);
    f_string_dynamic_resize(0, &setting->path_build_settings);
    f_string_dynamic_resize(0, &setting->path_build_stage);
    f_string_dynamic_resize(0, &setting->path_data);
    f_string_dynamic_resize(0, &setting->path_data_build);
    f_string_dynamic_resize(0, &setting->path_data_documentation);
    f_string_dynamic_resize(0, &setting->path_data_settings);
    f_string_dynamic_resize(0, &setting->path_documents);
    f_string_dynamic_resize(0, &setting->path_licenses);
    f_string_dynamic_resize(0, &setting->path_sources);
    f_string_dynamic_resize(0, &setting->path_work);
    f_string_dynamic_resize(0, &setting->path_work_includes);
    f_string_dynamic_resize(0, &setting->path_work_libraries);
    f_string_dynamic_resize(0, &setting->path_work_libraries_script);
    f_string_dynamic_resize(0, &setting->path_work_libraries_shared);
    f_string_dynamic_resize(0, &setting->path_work_libraries_static);
    f_string_dynamic_resize(0, &setting->path_work_programs);
    f_string_dynamic_resize(0, &setting->path_work_programs_script);
    f_string_dynamic_resize(0, &setting->path_work_programs_shared);
    f_string_dynamic_resize(0, &setting->path_work_programs_static);
    f_string_dynamic_resize(0, &setting->file_data_build_defines);
    f_string_dynamic_resize(0, &setting->file_data_build_dependencies);
    f_string_dynamic_resize(0, &setting->file_data_build_fakefile);
    f_string_dynamic_resize(0, &setting->file_data_build_process_post);
    f_string_dynamic_resize(0, &setting->file_data_build_process_pre);
    f_string_dynamic_resize(0, &setting->file_data_build_settings);
    f_string_dynamic_resize(0, &setting->file_documents_readme);

    f_string_dynamics_resize(0, &setting->defines);
    f_string_dynamics_resize(0, &setting->modes);

    f_uint8s_resize(0, &setting->operations);

    return F_none;
  }
#endif // _di_fake_setting_delete_

#ifndef _di_fake_setting_load_
  void fake_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, fake_setting_t * const setting) {

    if (!main || !setting) return;

    setting->flag = 0;

    // Load parameters.
    setting->status = f_console_parameter_process(arguments, &main->parameters, (void *) setting);

    if (F_status_is_error(setting->status)) {
      fake_print_error(setting, F_status_set_fine(setting->status), macro_fake_f(f_console_parameter_process));

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

        const uint8_t modes[3] = { f_color_mode_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        setting->status = fll_program_parameter_process_context(choices, modes, F_true, main);

        if (F_status_is_error(setting->status)) {
          fake_print_error(setting, F_status_set_fine(setting->status), macro_fake_f(fll_program_parameter_process_context));

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
          fake_print_error(setting, F_status_set_fine(setting->status), macro_fake_f(fll_program_parameter_process_verbosity));

          return;
        }
      }
    }

    main->output.to.id = F_type_descriptor_output_d;
    main->output.to.stream = F_type_output_d;
    main->output.to.flag = F_file_flag_create_d | F_file_flag_write_only_d | F_file_flag_append_d;

    if (main->parameters.array[fake_parameter_help_e].result & f_console_result_found_e) {
      setting->flag |= fake_main_flag_help_e;

      return;
    }

    if (main->parameters.array[fake_parameter_version_e].result & f_console_result_found_e) {
      setting->flag |= fake_main_flag_version_e;

      return;
    }

    f_array_length_t j = 0;
    f_array_length_t index = 0;

    {
      uint8_t i = 0;

      {
        const uint8_t enables[] = {
          fake_parameter_documents_enable_e,
          fake_parameter_shared_enable_e,
          fake_parameter_static_enable_e,
        };

        const uint8_t disables[] = {
          fake_parameter_documents_enable_e,
          fake_parameter_shared_enable_e,
          fake_parameter_static_enable_e,
        };

        const uint16_t flags[] = {
          fake_main_flag_enable_documents_e,
          fake_main_flag_enable_shared_e,
          fake_main_flag_enable_static_e,
        };

        for (; i < 3; ++i) {

          if (main->parameters.array[enables[i]].result & f_console_result_found_e) {
            if (main->parameters.array[disables[i]].result & f_console_result_found_e) {
              if (main->parameters.array[enables[i]].location < main->parameters.array[disables[i]].location) {
                setting->flag -= setting->flag & flags[i];
              }
              else {
                setting->flag |= flags[i];
              }
            }
            else {
              setting->flag |= flags[i];
            }
          }
          else if (main->parameters.array[disables[i]].result & f_console_result_found_e) {
            setting->flag -= setting->flag & flags[i];
          }
        } // for
      }

      {
        const f_array_length_t parameters[] = {
          fake_parameter_fakefile_e,
          fake_parameter_path_build_e,
          fake_parameter_path_data_e,
          fake_parameter_path_sources_e,
          fake_parameter_path_work_e,
          fake_parameter_process_e,
          fake_parameter_settings_e,
          fake_parameter_sources_e,
        };

        const f_string_static_t names[] = {
          fake_long_fakefile_s,
          fake_long_path_build_s,
          fake_long_path_data_s,
          fake_long_path_sources_s,
          fake_long_path_work_s,
          fake_long_process_s,
          fake_long_settings_s,
          fake_long_sources_s,
        };

        f_string_dynamic_t * const variable[] = {
          &setting->fakefile,
          &setting->path_build,
          &setting->path_data,
          &setting->path_sources,
          &setting->path_work,
          &setting->process,
          &setting->settings,
          &setting->sources,
        };

        f_string_static_t * const defaults[] = {
          &fake_default_fakefile_s, // fake_parameter_fakefile_e
          0,                        // fake_parameter_path_build_e
          0,                        // fake_parameter_path_data_e
          0,                        // fake_parameter_path_sources_e
          0,                        // fake_parameter_path_work_e
          &fake_default_process_s,  // fake_parameter_process_e
          &fake_default_settings_s, // fake_parameter_settings_e
          0,                        // fake_parameter_sources_e
        };

        for (i = 0; i < 8; ++i) {

          if (main->parameters.array[parameters[i]].result & f_console_result_found_e) {
            setting->status = F_status_set_error(F_parameter);

            fake_print_line_first_locked(setting, main->error);

            fll_program_print_error_parameter_missing_value(main->error, f_console_symbol_long_normal_s, names[i]);

            return;
          }

          if (main->parameters.array[parameters[i]].result & f_console_result_additional_e) {
            index = data->main->parameters.array[parameters[i]].values.array[data->main->parameters.array[parameters[i]].values.used - 1];

            if (data->main->parameters.arguments.array[index].used) {
              if (parameters[i] == fake_parameter_process_e) {
                for (j = 0; j < data->main->parameters.arguments.array[index].used; ++j) {

                  setting->status = f_utf_is_word_dash_plus(data->main->parameters.arguments.array[index].string + j, data->main->parameters.arguments.array[index].used - j, F_false);

                  if (F_status_is_error(setting->status)) {
                    if (print.verbosity > f_console_verbosity_quiet_e) {
                      fake_print_line_first_locked(setting, print);

                      if (fll_error_print(data->main->error, F_status_set_fine(setting->status), macro_fake_f(f_utf_is_word_dash_plus), F_false) == F_false) {
                        fll_program_print_error_parameter_process(data->main->error, F_status_set_fine(setting->status), f_console_symbol_long_normal_s, names[i]);
                      }
                    }

                    return;
                  }

                  if (setting->status == F_false) {
                    setting->status = F_status_set_error(F_parameter);

                    fake_print_error_parameter_not_word(setting, data->main->error, f_console_symbol_long_normal_s, names[i], data->main->parameters.arguments.array[index]);

                    return;
                  }
                } // for
              }

              // De-allocate memory before replacing it with a statically allocated string.
              if (variable[i]->size) {
                setting->status = f_string_dynamic_resize(0, variable[i]);

                if (F_status_is_error(setting->status)) {
                  fake_print_error(setting, F_status_set_fine(setting->status), macro_fake_f(f_string_dynamic_resize));

                  return;
                }
              }

              variable[i]->string = data->main->parameters.arguments.array[index].string;
              variable[i]->used = data->main->parameters.arguments.array[index].used;
              variable[i]->size = 0;

              setting->status = F_none;
            }
          }
          else if (defaults[i]) {

            // De-allocate memory before replacing it with a statically allocated string.
            if (variable[i]->size) {
              setting->status = f_string_dynamic_resize(0, variable[i]);

              if (F_status_is_error(setting->status)) {
                fake_print_error(setting, F_status_set_fine(setting->status), macro_fake_f(f_string_dynamic_resize));

                return;
              }
            }

            variable[i]->string = defaults[i]->string;
            variable[i]->used = defaults[i]->used;
            variable[i]->size = 0;
          }
        } // for
      }

      {
        const f_array_length_t parameters[] = {
          fake_parameter_define_e,
          fake_parameter_mode_e,
        };

        const f_string_static_t names[] = {
          fake_long_define_s,
          fake_long_mode_s,
        };

        f_string_dynamics_t * const variable[] = {
          &setting->define,
          &setting->mode,
        };

        for (i = 0; i < 2; ++i) {

          if (main->parameters.array[parameters[i]].result & f_console_result_found_e) {
            setting->status = F_status_set_error(F_parameter);

            fake_print_line_first_locked(setting, main->error);

            fll_program_print_error_parameter_missing_value(main->error, f_console_symbol_long_normal_s, names[i]);

            return;
          }

          if (main->parameters.array[parameters[i]].result & f_console_result_additional_e) {
            variable[i]->used = 0;

            setting->status = f_string_dynamics_increase_by(data->main->parameters.array[parameters[i]].values.used, variable[i]);

            if (F_status_is_error(setting->status)) {
              fake_print_error(setting, main->error, macro_fake_f(f_string_dynamics_increase_by));

              return;
            }

            for (; variable[i]->used < data->main->parameters.array[parameters[i]].values.used; ) {

              // De-allocate memory before replacing it with a statically allocated string.
              if (variable[i]->size) {
                setting->status = f_string_dynamic_resize(0, variable[i]);

                if (F_status_is_error(setting->status)) {
                  fake_print_error(setting, F_status_set_fine(setting->status), macro_fake_f(f_string_dynamic_resize));

                  return;
                }
              }

              index = data->main->parameters.array[parameters[i]].values.array[variable[i]->used];

              variable[i]->array[variable[i]->used].string = main->parameters.arguments.array[index].string;
              variable[i]->array[variable[i]->used].used = main->parameters.arguments.array[index].used;
              variable[i]->array[variable[i]->used++].size = 0;
            } // for
          }
        } // for
      }
    }

    {
      f_array_length_t locations = main->parameters.array[fake_parameter_operation_build_e].locations.used;
      locations += main->parameters.array[fake_parameter_operation_clean_e].locations.used;
      locations += main->parameters.array[fake_parameter_operation_make_e].locations.used;
      locations += main->parameters.array[fake_parameter_operation_skeleton_e].locations.used;

      setting->operations.used = 0;

      setting->status = f_uint8s_increase_by(locations ? locations : 1, &setting->operations);

      if (F_status_is_error(setting->status)) {
        fake_print_error(setting, main->error, macro_fake_f(f_uint8s_increase_by));

        return;
      }

      if (locations) {
        data.flag |= fake_data_flag_operation_e;

        f_array_length_t i = 0;

        //f_string_static_t * const args = main->parameters.arguments.array;

        /*
          fake_process_console_parameters
          fake_parameter_operation_build_e,
          fake_parameter_operation_clean_e,
          fake_parameter_operation_make_e,
          fake_parameter_operation_skeleton_e,
        */
        /*
        f_array_length_t locations[operations_length];
        f_array_length_t locations_length = 0;
        f_array_length_t i = 0;
        f_array_length_t j = 0;
        f_array_length_t k = 0;

        for (; i < main->parameters.array[fake_parameter_operation_build_e].locations.used; ++i, ++locations_length) {

          operations[locations_length] = fake_operation_build_e;
          locations[locations_length] = main->parameters.array[fake_parameter_operation_build_e].locations.array[i];
        } // for

        for (i = 0; i < main->parameters.array[fake_parameter_operation_clean_e].locations.used; ++i) {

          for (j = 0; j < locations_length; ++j) {

            if (main->parameters.array[fake_parameter_operation_clean_e].locations.array[i] < locations[j]) {
              for (k = locations_length; k > j; --k) {
                locations[k] = locations[k - 1];
                operations[k] = operations[k - 1];
              } // for

              break;
            }
          } // for

          locations[j] = main->parameters.array[fake_parameter_operation_clean_e].locations.array[i];
          operations[j] = fake_operation_clean_e;
          ++locations_length;
        } // for

        for (i = 0; i < main->parameters.array[fake_parameter_operation_make_e].locations.used; ++i) {

          for (j = 0; j < locations_length; ++j) {

            if (main->parameters.array[fake_parameter_operation_make_e].locations.array[i] < locations[j]) {
              for (k = locations_length; k > j; --k) {
                locations[k] = locations[k - 1];
                operations[k] = operations[k - 1];
              } // for

              break;
            }
          } // for

          locations[j] = main->parameters.array[fake_parameter_operation_make_e].locations.array[i];
          operations[j] = fake_operation_make_e;
          ++locations_length;
        } // for

        for (i = 0; i < main->parameters.array[fake_parameter_operation_skeleton_e].locations.used; ++i) {

          for (j = 0; j < locations_length; ++j) {

            if (main->parameters.array[fake_parameter_operation_skeleton_e].locations.array[i] < locations[j]) {
              for (k = locations_length; k > j; --k) {

                locations[k] = locations[k - 1];
                operations[k] = operations[k - 1];
              } // for

              break;
            }
          } // for

          locations[j] = main->parameters.array[fake_parameter_operation_skeleton_e].locations.array[i];
          operations[j] = fake_operation_skeleton_e;
          ++locations_length;
        } // for
        */
      }
      else {
        setting->operations.array[setting->operations.used++] = fake_parameter_operation_make_e;
      }
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
