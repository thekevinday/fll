#include "fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_setting_delete_
  f_status_t fake_setting_delete(fake_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    f_string_dynamic_resize(0, &setting->build);
    f_string_dynamic_resize(0, &setting->data);
    f_string_dynamic_resize(0, &setting->documents);
    f_string_dynamic_resize(0, &setting->fakefile);
    f_string_dynamic_resize(0, &setting->licenses);
    f_string_dynamic_resize(0, &setting->process);
    f_string_dynamic_resize(0, &setting->settings);
    f_string_dynamic_resize(0, &setting->sources);
    f_string_dynamic_resize(0, &setting->work);

    f_string_dynamics_resize(0, &setting->defines);
    f_string_dynamics_resize(0, &setting->modes);

    f_uint8s_resize(0, &setting->operations);

    return F_none;
  }
#endif // _di_fake_setting_delete_

#ifndef _di_fake_setting_load_
  void fake_setting_load(const f_console_arguments_t arguments, f_state_t state, fll_program_data_t * const main, fake_setting_t * const setting) {

    if (!main || !setting) return;

    main->output.to.id = F_type_descriptor_output_d;
    main->output.to.stream = F_type_output_d;
    main->output.to.flag = F_file_flag_create_d | F_file_flag_write_only_d | F_file_flag_append_d;

    {
      fake_data_t data = fake_data_t_initialize;
      data.main = main;
      data.setting = setting;

      // Load parameters.
      setting->status = f_console_parameter_process(state, arguments, &main->parameters, (void *) &data);
    }

    if (F_status_is_error(setting->status)) {
      fake_print_error(setting, setting->status, main->error, macro_fake_f(f_console_parameter_process));

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
          fake_print_error(setting, setting->status, main->error, macro_fake_f(fll_program_parameter_process_context));

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
          fake_print_error(setting, setting->status, main->error, macro_fake_f(fll_program_parameter_process_verbosity));

          return;
        }
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

    if (main->parameters.array[fake_parameter_copyright_e].result & f_console_result_found_e) {
      setting->flag |= fake_main_flag_copyright_e;

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
          fake_parameter_build_e,
          fake_parameter_data_e,
          fake_parameter_documents_e,
          fake_parameter_fakefile_e,
          fake_parameter_licenses_e,
          fake_parameter_process_e,
          fake_parameter_settings_e,
          fake_parameter_sources_e,
          fake_parameter_work_e,
        };

        const f_string_static_t names[] = {
          fake_long_build_s,
          fake_long_data_s,
          fake_long_fakefile_s,
          fake_long_documents_s,
          fake_long_licenses_s,
          fake_long_process_s,
          fake_long_settings_s,
          fake_long_sources_s,
          fake_long_work_s,
        };

        f_string_dynamic_t * const variable[] = {
          &setting->build,
          &setting->data,
          &setting->documents,
          &setting->fakefile,
          &setting->licenses,
          &setting->process,
          &setting->settings,
          &setting->sources,
          &setting->work,
        };

        setting->build.used = 0;
        setting->data.used = 0;
        setting->documents.used = 0;
        setting->fakefile.used = 0;
        setting->licenses.used = 0;
        setting->process.used = 0;
        setting->settings.used = 0;
        setting->sources.used = 0;
        setting->work.used = 0;

        const f_string_static_t defaults[] = {
          fake_default_build_s,
          fake_default_data_s,
          fake_default_documents_s,
          fake_default_fakefile_s,
          fake_default_licenses_s,
          fake_default_process_s,
          fake_default_settings_s,
          fake_default_sources_s,
          fake_default_work_s,
        };

        const bool cleanups[] = {
          F_true,  // fake_parameter_build_e
          F_true,  // fake_parameter_data_e
          F_true,  // fake_parameter_documents_e
          F_false, // fake_parameter_fakefile_e
          F_true,  // fake_parameter_licenses_e
          F_false, // fake_parameter_process_e
          F_false, // fake_parameter_settings_e
          F_false, // fake_parameter_sources_e
          F_true,  // fake_parameter_work_e
        };

        for (i = 0; i < 9; ++i) {

          if (main->parameters.array[parameters[i]].result & f_console_result_found_e) {
            setting->status = F_status_set_error(F_parameter);

            fake_print_line_first_locked(setting, main->error);

            fll_program_print_error_parameter_missing_value(main->error, f_console_symbol_long_normal_s, names[i]);

            return;
          }

          if (main->parameters.array[parameters[i]].result & f_console_result_value_e) {
            index = main->parameters.array[parameters[i]].values.array[main->parameters.array[parameters[i]].values.used - 1];

            if (main->parameters.arguments.array[index].used) {
              if (parameters[i] == fake_parameter_process_e) {
                for (j = 0; j < main->parameters.arguments.array[index].used; ++j) {

                  setting->status = f_utf_is_word_dash_plus(main->parameters.arguments.array[index].string + j, main->parameters.arguments.array[index].used - j, F_false);

                  if (F_status_is_error(setting->status)) {
                    if (main->error.verbosity > f_console_verbosity_quiet_e) {
                      fake_print_line_first_locked(setting, main->error);

                      if (fake_print_error_fallback(setting, setting->status, main->error, macro_fake_f(f_utf_is_word_dash_plus)) == F_false) {
                        fll_program_print_error_parameter_process(main->error, f_console_symbol_long_normal_s, names[i]);
                      }
                    }

                    return;
                  }

                  if (setting->status == F_false) {
                    setting->status = F_status_set_error(F_parameter);

                    fake_print_error_parameter_not_word(setting, main->error, f_console_symbol_long_normal_s, names[i], main->parameters.arguments.array[index]);

                    return;
                  }
                } // for
              }

              if (cleanups[i]) {
                setting->status = f_path_directory_cleanup(main->parameters.arguments.array[index], variable[i]);

                if (F_status_is_error(setting->status)) {
                  if (main->error.verbosity > f_console_verbosity_quiet_e) {
                    fake_print_line_first_locked(setting, main->error);

                    if (fake_print_error_fallback(setting, setting->status, main->error, macro_fake_f(f_path_directory_cleanup)) == F_false) {
                      fll_program_print_error_parameter_process(main->error, f_console_symbol_long_normal_s, names[i]);
                    }
                  }

                  return;
                }
              }
              else {

                // De-allocate memory before replacing it with a statically allocated string.
                if (variable[i]->size) {
                  setting->status = f_string_dynamic_resize(0, variable[i]);

                  if (F_status_is_error(setting->status)) {
                    fake_print_error(setting, setting->status, main->error, macro_fake_f(f_string_dynamic_resize));

                    return;
                  }
                }

                variable[i]->string = main->parameters.arguments.array[index].string;
                variable[i]->used = main->parameters.arguments.array[index].used;
                variable[i]->size = 0;
              }

              if (!variable[i]->used) {
                setting->status = F_status_set_error(F_parameter);

                fake_print_error_parameter_not_empty(setting, main->error, f_console_symbol_long_normal_s, names[i], main->parameters.arguments.array[index]);

                return;
              }

              setting->status = F_none;
            }
          }
          else {

            // De-allocate memory before replacing it with a statically allocated string.
            if (variable[i]->size) {
              setting->status = f_string_dynamic_resize(0, variable[i]);

              if (F_status_is_error(setting->status)) {
                fake_print_error(setting, setting->status, main->error, macro_fake_f(f_string_dynamic_resize));

                return;
              }
            }

            variable[i]->string = defaults[i].string;
            variable[i]->used = defaults[i].used;
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
          &setting->defines,
          &setting->modes,
        };

        for (i = 0; i < 2; ++i) {

          if (main->parameters.array[parameters[i]].result & f_console_result_found_e) {
            setting->status = F_status_set_error(F_parameter);

            fake_print_line_first_locked(setting, main->error);

            fll_program_print_error_parameter_missing_value(main->error, f_console_symbol_long_normal_s, names[i]);

            return;
          }

          if (main->parameters.array[parameters[i]].result & f_console_result_value_e) {
            setting->status = fll_program_parameter_additional_rip(main->parameters.arguments.array, main->parameters.array[parameters[i]].values, variable[i]);

            if (F_status_is_error(setting->status)) {
              if (main->error.verbosity > f_console_verbosity_quiet_e) {
                fake_print_line_first_locked(setting, main->error);

                if (fake_print_error_fallback(setting, setting->status, main->error, macro_fake_f(fll_program_parameter_additional_rip)) == F_false) {
                  fll_program_print_error_parameter_process(main->error, f_console_symbol_long_normal_s, names[i]);
                }
              }

              return;
            }

            if (parameters[i] == fake_parameter_mode_e) {
              f_array_length_t i = 0;
              f_array_length_t j = 0;
              f_array_length_t width_max = 0;

              for (; i < setting->modes.used; ++i) {

                for (j = 0; j < setting->modes.array[i].used; ++j) {

                  width_max = setting->modes.array[i].used - j;

                  setting->status = f_utf_is_word_dash_plus(main->parameters.arguments.array[i].string + j, main->parameters.arguments.array[i].used - j, F_false);

                  if (F_status_is_error(setting->status)) {
                    if (main->error.verbosity > f_console_verbosity_quiet_e) {
                      fake_print_line_first_locked(setting, main->error);

                      if (fake_print_error_fallback(setting, setting->status, main->error, macro_fake_f(f_utf_is_word_dash_plus)) == F_false) {
                        fll_program_print_error_parameter_process(main->error, f_console_symbol_long_normal_s, names[i]);
                      }
                    }

                    return;
                  }

                  if (setting->status == F_false) {
                    setting->status = F_status_set_error(F_parameter);

                    fake_print_error_parameter_not_word(setting, main->error, f_console_symbol_long_normal_s, names[i], main->parameters.arguments.array[index]);

                    return;
                  }
                } // for
              } // for
            }
          }
        } // for
      }
    }

    if (setting->operations.used) {
      setting->flag |= fake_main_flag_operation_e;
    }
    else {
      setting->flag |= fake_main_flag_operation_make_e;
      setting->flag -= setting->flag & fake_main_flag_operation_e;

      setting->status = f_uint8s_increase_by(1, &setting->operations);

      if (F_status_is_error(setting->status)) {
        fake_print_error(setting, setting->status, main->error, macro_fake_f(f_uint8s_increase_by));

        return;
      }

      setting->operations.array[setting->operations.used++] = fake_operation_make_e;
    }
  }
#endif // _di_fake_setting_load_

#ifndef _di_fake_setting_load_parameter_callback_
  void fake_setting_load_parameter_callback(const f_console_arguments_t arguments, void * const void_parameters, f_console_parameter_state_t * const state, void * const void_data) {

    if (!state) return;

    if (!void_parameters || !void_data || (state->type != f_console_parameter_state_type_simple_e && state->type != f_console_parameter_state_type_miss_e)) {
      state->status = F_process;

      return;
    }

    f_console_parameters_t * const parameters = (f_console_parameters_t * const) void_parameters;
    fake_data_t * const data = (fake_data_t * const) void_data;

    state->status = f_uint8s_increase(fake_default_allocation_small_d, &data->setting->operations);

    if (F_status_is_error(state->status)) {
      fake_print_error(data->setting, state->status, data->main->error, macro_fake_f(f_uint8s_increase));

      return;
    }

    switch (state->at) {
      case fake_parameter_operation_build_e:
        data->setting->operations.array[data->setting->operations.used++] = fake_operation_build_e;
        data->setting->flag |= fake_main_flag_operation_build_e;

        break;

      case fake_parameter_operation_clean_e:
        data->setting->operations.array[data->setting->operations.used++] = fake_operation_clean_e;
        data->setting->flag |= fake_main_flag_operation_clean_e;

        break;

      case fake_parameter_operation_make_e:
        data->setting->operations.array[data->setting->operations.used++] = fake_operation_make_e;
        data->setting->flag |= fake_main_flag_operation_make_e;

        break;

      case fake_parameter_operation_skeleton_e:
        data->setting->operations.array[data->setting->operations.used++] = fake_operation_skeleton_e;
        data->setting->flag |= fake_main_flag_operation_skeleton_e;

        break;

      default:
        state->status = F_process;

        return;
    }

    state->status = F_none;
  }
#endif // _di_fake_setting_load_parameter_callback_

#ifndef _di_fake_setting_unload_
  f_status_t fake_setting_unload(fll_program_data_t * const main, fake_setting_t * const setting) {

    if (!main || !setting) return F_status_set_error(F_parameter);

    fake_setting_delete(setting);

    return F_none;
  }
#endif // _di_fake_setting_unload_

#ifndef _di_fake_data_delete_
  f_status_t fake_data_delete(fake_data_t * const data) {

    f_string_dynamic_resize(0, &data->path_build);
    f_string_dynamic_resize(0, &data->path_build_documentation);
    f_string_dynamic_resize(0, &data->path_build_documents);
    f_string_dynamic_resize(0, &data->path_build_includes);
    f_string_dynamic_resize(0, &data->path_build_libraries);
    f_string_dynamic_resize(0, &data->path_build_libraries_script);
    f_string_dynamic_resize(0, &data->path_build_libraries_shared);
    f_string_dynamic_resize(0, &data->path_build_libraries_static);
    f_string_dynamic_resize(0, &data->path_build_objects);
    f_string_dynamic_resize(0, &data->path_build_objects_script);
    f_string_dynamic_resize(0, &data->path_build_objects_shared);
    f_string_dynamic_resize(0, &data->path_build_objects_static);
    f_string_dynamic_resize(0, &data->path_build_programs);
    f_string_dynamic_resize(0, &data->path_build_programs_script);
    f_string_dynamic_resize(0, &data->path_build_programs_shared);
    f_string_dynamic_resize(0, &data->path_build_programs_static);
    f_string_dynamic_resize(0, &data->path_build_settings);
    f_string_dynamic_resize(0, &data->path_build_stage);

    f_string_dynamic_resize(0, &data->path_data_build);
    f_string_dynamic_resize(0, &data->path_data_documentation);
    f_string_dynamic_resize(0, &data->path_data_settings);

    f_string_dynamic_resize(0, &data->path_documents);

    f_string_dynamic_resize(0, &data->path_licenses);

    f_string_dynamic_resize(0, &data->path_work_includes);
    f_string_dynamic_resize(0, &data->path_work_libraries);
    f_string_dynamic_resize(0, &data->path_work_libraries_script);
    f_string_dynamic_resize(0, &data->path_work_libraries_shared);
    f_string_dynamic_resize(0, &data->path_work_libraries_static);
    f_string_dynamic_resize(0, &data->path_work_programs);
    f_string_dynamic_resize(0, &data->path_work_programs_script);
    f_string_dynamic_resize(0, &data->path_work_programs_shared);
    f_string_dynamic_resize(0, &data->path_work_programs_static);

    f_string_dynamic_resize(0, &data->file_data_build_defines);
    f_string_dynamic_resize(0, &data->file_data_build_dependencies);
    f_string_dynamic_resize(0, &data->file_data_build_process_post);
    f_string_dynamic_resize(0, &data->file_data_build_process_pre);
    f_string_dynamic_resize(0, &data->file_data_build_fakefile);
    f_string_dynamic_resize(0, &data->file_data_build_settings);

    f_string_dynamic_resize(0, &data->file_documents_readme);

    return F_none;
  }
#endif // _di_fake_data_delete_

#ifndef _di_fake_make_data_delete_
  f_status_t fake_make_data_delete(fake_make_data_t * const data) {

    macro_fake_build_setting_t_delete_simple(data->setting_build);
    macro_fake_make_setting_t_delete_simple(data->setting_make);

    f_string_maps_resize(0, &data->environment);

    macro_fake_make_parameter_delete_simple(data->parameter);
    macro_fake_make_parameter_delete_simple(data->parameter_option);
    macro_fake_make_parameter_delete_simple(data->parameter_value);
    macro_fake_make_path_delete_simple(data->path);

    f_fss_nameds_resize(0, &data->fakefile);

    f_string_dynamic_resize(0, &data->buffer);
    f_string_dynamic_resize(0, &data->cache_1);
    f_string_dynamic_resize(0, &data->cache_2);
    f_string_dynamic_resize(0, &data->cache_path);

    f_string_dynamics_resize(0, &data->cache_arguments);

    f_iki_data_delete(&data->cache_iki);

    return F_none;
  }
#endif // _di_fake_make_data_delete_

#ifdef __cplusplus
} // extern "C"
#endif
