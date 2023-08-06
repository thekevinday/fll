#include "fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_setting_load_
  void fake_setting_load(const f_console_arguments_t arguments, fake_main_t * const main) {

    if (!main) return;

    main->program.output.to.id = F_type_descriptor_output_d;
    main->program.output.to.stream = F_type_output_d;
    main->program.output.to.flag = F_file_flag_create_d | F_file_flag_write_only_d | F_file_flag_append_d;

    {
      const uint16_t step_original = main->setting.state.step_small;
      fake_data_t data = fake_data_t_initialize;
      data.main = main;

      main->setting.state.step_small = 4;

      f_console_parameter_process(arguments, &main->program.parameters, &main->setting.state, (void *) &data);

      main->setting.state.step_small = step_original;
    }

    // Identify and process first/last parameters.
    if (main->program.parameters.array[f_console_standard_parameter_line_first_no_e].result & f_console_result_found_e) {
      main->setting.flag -= main->setting.flag & fake_main_flag_print_first_e;
    }
    else {
      main->setting.flag |= fake_main_flag_print_first_e;
    }

    if (main->program.parameters.array[f_console_standard_parameter_line_last_no_e].result & f_console_result_found_e) {
      main->setting.flag -= main->setting.flag & fake_main_flag_print_last_e;
    }
    else {
      main->setting.flag |= fake_main_flag_print_last_e;
    }

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & fake_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fake_print_error(&main->program.error, macro_fake_f(f_console_parameter_process));

      return;
    }

    main->setting.state.status = fll_program_parameter_process_context_standard(F_true, &main->program);

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & fake_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fake_print_error(&main->program.error, macro_fake_f(fll_program_parameter_process_context_standard));

      return;
    }

    main->setting.state.status = fll_program_parameter_process_verbosity_standard(F_true, &main->program);

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & fake_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fake_print_error(&main->program.error, macro_fake_f(fll_program_parameter_process_verbosity_standard));

      return;
    }

    if (main->program.parameters.array[f_console_standard_parameter_help_e].result & f_console_result_found_e) {
      main->setting.flag |= fake_main_flag_help_e;

      return;
    }

    if (main->program.parameters.array[f_console_standard_parameter_version_e].result & f_console_result_found_e) {
      main->setting.flag |= fake_main_flag_version_e;

      return;
    }

    if (main->program.parameters.array[f_console_standard_parameter_copyright_e].result & f_console_result_found_e) {
      main->setting.flag |= fake_main_flag_copyright_e;

      return;
    }

    f_number_unsigned_t j = 0;
    f_number_unsigned_t index = 0;

    if (main->program.pipe & fll_program_data_pipe_input_e) {
      main->setting.flag |= fake_main_flag_pipe_e;
    }
    else {
      main->setting.flag -= main->setting.flag & fake_main_flag_pipe_e;
    }

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

          if (main->program.parameters.array[enables[i]].result & f_console_result_found_e) {
            if (main->program.parameters.array[disables[i]].result & f_console_result_found_e) {
              if (main->program.parameters.array[enables[i]].location < main->program.parameters.array[disables[i]].location) {
                main->setting.flag -= main->setting.flag & flags[i];
              }
              else {
                main->setting.flag |= flags[i];
              }
            }
            else {
              main->setting.flag |= flags[i];
            }
          }
          else if (main->program.parameters.array[disables[i]].result & f_console_result_found_e) {
            main->setting.flag -= main->setting.flag & flags[i];
          }
        } // for
      }

      {
        const f_number_unsigned_t parameters[] = {
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
          &main->setting.build,
          &main->setting.data,
          &main->setting.documents,
          &main->setting.fakefile,
          &main->setting.licenses,
          &main->setting.process,
          &main->setting.settings,
          &main->setting.sources,
          &main->setting.work,
        };

        main->setting.build.used = 0;
        main->setting.data.used = 0;
        main->setting.documents.used = 0;
        main->setting.fakefile.used = 0;
        main->setting.licenses.used = 0;
        main->setting.process.used = 0;
        main->setting.settings.used = 0;
        main->setting.sources.used = 0;
        main->setting.work.used = 0;

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

          if ((main->program.parameters.array[parameters[i]].result & f_console_result_found_e) && !(main->program.parameters.array[parameters[i]].result & f_console_result_value_e)) {
            main->setting.state.status = F_status_set_error(F_parameter);

            if ((main->setting.flag & fake_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
            }

            if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
              fll_program_print_error_parameter_missing_value(&main->program.error, f_console_symbol_long_normal_s, names[i]);
            }

            return;
          }

          if (main->program.parameters.array[parameters[i]].result & f_console_result_value_e) {
            index = main->program.parameters.array[parameters[i]].values.array[main->program.parameters.array[parameters[i]].values.used - 1];

            if (main->program.parameters.arguments.array[index].used) {
              if (parameters[i] == fake_parameter_process_e) {
                for (j = 0; j < main->program.parameters.arguments.array[index].used; ++j) {

                  main->setting.state.status = f_utf_is_word_dash_plus(main->program.parameters.arguments.array[index].string + j, main->program.parameters.arguments.array[index].used - j, F_false);

                  // @todo fix this to print an error about the actual invalid character so that it can be investigated.

                  if (F_status_is_error(main->setting.state.status)) {
                    if ((main->setting.flag & fake_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
                      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
                    }

                    if (fake_print_error_fallback(&main->program.error, macro_fake_f(f_utf_is_word_dash_plus)) == F_false) {
                      fll_program_print_error_parameter_process(&main->program.error, f_console_symbol_long_normal_s, names[i]);
                    }

                    return;
                  }

                  if (main->setting.state.status == F_false) {
                    main->setting.state.status = F_status_set_error(F_parameter);

                    if ((main->setting.flag & fake_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
                      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
                    }

                    fake_print_error_parameter_not_word(&main->program.error, f_console_symbol_long_normal_s, names[i], main->program.parameters.arguments.array[index]);

                    return;
                  }
                } // for
              }

              if (cleanups[i]) {
                main->setting.state.status = f_path_directory_cleanup(main->program.parameters.arguments.array[index], variable[i]);

                if (F_status_is_error(main->setting.state.status)) {
                  if ((main->setting.flag & fake_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
                    fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
                  }

                  if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
                    if (fake_print_error_fallback(&main->program.error, macro_fake_f(f_path_directory_cleanup)) == F_false) {
                      fll_program_print_error_parameter_process(&main->program.error, f_console_symbol_long_normal_s, names[i]);
                    }
                  }

                  return;
                }
              }
              else {

                // De-allocate memory before replacing it with a statically allocated string.
                if (variable[i]->size) {
                  main->setting.state.status = f_string_dynamic_resize(0, variable[i]);

                  if (F_status_is_error(main->setting.state.status)) {
                    if ((main->setting.flag & fake_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
                      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
                    }

                    fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_resize));

                    return;
                  }
                }

                variable[i]->string = main->program.parameters.arguments.array[index].string;
                variable[i]->used = main->program.parameters.arguments.array[index].used;
                variable[i]->size = 0;
              }

              if (!variable[i]->used) {
                main->setting.state.status = F_status_set_error(F_parameter);

                if ((main->setting.flag & fake_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
                  fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
                }

                fake_print_error_parameter_not_empty(&main->program.error, f_console_symbol_long_normal_s, names[i], main->program.parameters.arguments.array[index]);

                return;
              }

              main->setting.state.status = F_none;
            }
          }
          else {

            // De-allocate memory before replacing it with a statically allocated string.
            if (variable[i]->size) {
              main->setting.state.status = f_string_dynamic_resize(0, variable[i]);

              if (F_status_is_error(main->setting.state.status)) {
                if ((main->setting.flag & fake_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
                  fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
                }

                fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_resize));

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
        const f_number_unsigned_t parameters[] = {
          fake_parameter_define_e,
          fake_parameter_mode_e,
        };

        const f_string_static_t names[] = {
          fake_long_define_s,
          fake_long_mode_s,
        };

        f_string_dynamics_t * const variable[] = {
          &main->setting.defines,
          &main->setting.modes,
        };

        f_number_unsigned_t width_max = 0;

        for (i = 0; i < 2; ++i) {

          if ((main->program.parameters.array[parameters[i]].result & f_console_result_found_e) && !(main->program.parameters.array[parameters[i]].result & f_console_result_value_e)) {
            main->setting.state.status = F_status_set_error(F_parameter);

            if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
              if ((main->setting.flag & fake_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
                fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
              }

              fll_program_print_error_parameter_missing_value(&main->program.error, f_console_symbol_long_normal_s, names[i]);
            }

            return;
          }

          if (main->program.parameters.array[parameters[i]].result & f_console_result_value_e) {
            main->setting.state.status = fll_program_parameter_additional_rip(main->program.parameters.arguments.array, main->program.parameters.array[parameters[i]].values, variable[i]);

            if (F_status_is_error(main->setting.state.status)) {
              if ((main->setting.flag & fake_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
                fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
              }

              if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
                if (fake_print_error_fallback(&main->program.error, macro_fake_f(fll_program_parameter_additional_rip)) == F_false) {
                  fll_program_print_error_parameter_process(&main->program.error, f_console_symbol_long_normal_s, names[i]);
                }
              }

              return;
            }

            if (parameters[i] == fake_parameter_mode_e) {
              for (j = 0; j < main->program.parameters.arguments.array[i].used; ++j) {

                width_max = main->program.parameters.arguments.array[i].used - j;

                main->setting.state.status = f_utf_is_word_dash_plus(main->program.parameters.arguments.array[i].string + j, width_max, F_false);

                if (F_status_is_error(main->setting.state.status)) {
                  if ((main->setting.flag & fake_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
                    fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
                  }

                  // @todo fix this to print an error about the actual invalid character so that it can be investigated.
                  if (fake_print_error_fallback(&main->program.error, macro_fake_f(f_utf_is_word_dash_plus)) == F_false) {
                    fll_program_print_error_parameter_process(&main->program.error, f_console_symbol_long_normal_s, names[i]);
                  }

                  return;
                }

                if (main->setting.state.status == F_false) {
                  main->setting.state.status = F_status_set_error(F_parameter);

                  if ((main->setting.flag & fake_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
                    fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
                  }

                  fake_print_error_parameter_not_word(&main->program.error, f_console_symbol_long_normal_s, names[i], main->program.parameters.arguments.array[i]);

                  return;
                }
              } // for
            }
          }
        } // for
      }
    }

    if (main->setting.operations.used) {
      main->setting.flag |= fake_main_flag_operation_e;
    }
    else {
      main->setting.flag |= fake_main_flag_operation_make_e;
      main->setting.flag -= main->setting.flag & fake_main_flag_operation_e;

      main->setting.state.status = f_memory_array_increase_by(1, sizeof(uint8_t), (void **) &main->setting.operations.array, &main->setting.operations.used, &main->setting.operations.size);

      if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & fake_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

        fake_print_error(&main->program.error, macro_fake_f(f_memory_array_increase_by));

        return;
      }

      main->setting.operations.array[main->setting.operations.used++] = fake_operation_make_e;
    }
  }
#endif // _di_fake_setting_load_

#ifndef _di_fake_setting_load_parameter_callback_
  void fake_setting_load_parameter_callback(const f_console_arguments_t arguments, void * const void_parameters, f_console_parameter_state_t * const parameter_state, void * const void_data) {

    if (!parameter_state || !parameter_state->state) return;

    if (!void_parameters || !void_data || (parameter_state->type != f_console_parameter_state_type_simple_e && parameter_state->type != f_console_parameter_state_type_miss_e)) {
      parameter_state->state->status = F_process;

      return;
    }

    fake_data_t * const data = (fake_data_t * const) void_data;

    if (!data->main) return;

    parameter_state->state->status = f_memory_array_increase(parameter_state->state->step_small, sizeof(uint8_t), (void **) &data->main->setting.operations.array, &data->main->setting.operations.used, &data->main->setting.operations.size);

    if (F_status_is_error(parameter_state->state->status)) {
      fake_print_error(&data->main->program.error, macro_fake_f(f_memory_array_increase));

      return;
    }

    switch (parameter_state->at) {
      case fake_parameter_operation_build_e:
        data->main->setting.operations.array[data->main->setting.operations.used++] = fake_operation_build_e;
        data->main->setting.flag |= fake_main_flag_operation_build_e;

        break;

      case fake_parameter_operation_clean_e:
        data->main->setting.operations.array[data->main->setting.operations.used++] = fake_operation_clean_e;
        data->main->setting.flag |= fake_main_flag_operation_clean_e;

        break;

      case fake_parameter_operation_make_e:
        data->main->setting.operations.array[data->main->setting.operations.used++] = fake_operation_make_e;
        data->main->setting.flag |= fake_main_flag_operation_make_e;

        break;

      case fake_parameter_operation_skeleton_e:
        data->main->setting.operations.array[data->main->setting.operations.used++] = fake_operation_skeleton_e;
        data->main->setting.flag |= fake_main_flag_operation_skeleton_e;

        break;

      default:
        parameter_state->state->status = F_process;

        return;
    }

    parameter_state->state->status = F_none;
  }
#endif // _di_fake_setting_load_parameter_callback_

#ifndef _di_fake_string_dynamic_reset_
  void fake_string_dynamic_reset(f_string_dynamic_t * const dynamic) {

    if (!dynamic) return;

    // Shrink an overly long string.
    if (dynamic->size > fake_max_over_string_d) {
      f_string_dynamic_resize(fake_allocation_large_d, dynamic);
    }

    dynamic->used = 0;
  }
#endif // _di_fake_string_dynamic_reset_

#ifndef _di_fake_string_dynamics_reset_
  void fake_string_dynamics_reset(f_string_dynamics_t * const dynamics) {

    if (!dynamics) return;

    // Shrink an overly long array.
    if (dynamics->size > fake_max_over_array_d) {
      f_string_dynamics_resize(fake_allocation_large_d, dynamics);
    }

    while (dynamics->used) {
      fake_string_dynamic_reset(&dynamics->array[--dynamics->used]);
    } // while
  }
#endif // _di_fake_string_dynamics_reset_

#ifndef _di_fake_iki_data_reset_
  void fake_iki_data_reset(f_iki_data_t * const iki_data) {

    if (!iki_data) return;

    // Shrink an overly long array.
    if (iki_data->content.used > fake_max_over_array_d) {
      f_string_ranges_resize(fake_allocation_large_d, &iki_data->content);
    }

    if (iki_data->delimits.used > fake_max_over_array_d) {
      f_memory_array_resize(fake_allocation_large_d, sizeof(f_number_unsigned_t), (void **) &iki_data->delimits.array, &iki_data->delimits.used, &iki_data->delimits.size);
    }

    if (iki_data->variable.used > fake_max_over_array_d) {
      f_string_ranges_resize(fake_allocation_large_d, &iki_data->variable);
    }

    if (iki_data->vocabulary.used > fake_max_over_array_d) {
      f_string_ranges_resize(fake_allocation_large_d, &iki_data->vocabulary);
    }

    while (iki_data->content.used) {

      iki_data->content.array[--iki_data->content.used].start = 1;
      iki_data->content.array[iki_data->content.used].stop = 0;
    } // while

    while (iki_data->delimits.used) {
      iki_data->delimits.array[--iki_data->delimits.used] = 0;
    } // while

    while (iki_data->variable.used) {

      iki_data->variable.array[--iki_data->variable.used].start = 1;
      iki_data->variable.array[iki_data->variable.used].stop = 0;
    } // while

    while (iki_data->vocabulary.used) {

      iki_data->vocabulary.array[--iki_data->vocabulary.used].start = 1;
      iki_data->vocabulary.array[iki_data->vocabulary.used].stop = 0;
    } // while
  }
#endif // _di_fake_iki_data_reset_

#ifdef __cplusplus
} // extern "C"
#endif
