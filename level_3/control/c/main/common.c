#include "control.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_control_setting_load_
  void control_setting_load(const f_console_arguments_t arguments, control_main_t * const main) {

    if (!main) return;

    main->setting.state.step_small = control_allocation_console_d;

    f_console_parameter_process(arguments, &main->program.parameters, &main->setting.state, 0);

    main->setting.state.step_small = control_allocation_small_d;

    // Identify and process first/last parameters.
    if (main->program.parameters.array[f_console_standard_parameter_line_first_no_e].result & f_console_result_found_e) {
      main->setting.flag &= ~control_main_flag_print_first_e;
    }
    else {
      main->setting.flag |= control_main_flag_print_first_e;
    }

    if (main->program.parameters.array[f_console_standard_parameter_line_last_no_e].result & f_console_result_found_e) {
      main->setting.flag &= ~control_main_flag_print_last_e;
    }
    else {
      main->setting.flag |= control_main_flag_print_last_e;
    }

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & control_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      control_print_error(&main->program.error, macro_control_f(f_console_parameter_process));

      return;
    }

    main->setting.state.status = fll_program_parameter_process_context_standard(F_true, &main->program);

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & control_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      control_print_error(&main->program.error, macro_control_f(fll_program_parameter_process_context_standard));

      return;
    }

    main->setting.state.status = fll_program_parameter_process_verbosity_standard(F_true, &main->program);

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & control_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      control_print_error(&main->program.error, macro_control_f(fll_program_parameter_process_verbosity_standard));

      return;
    }

    if (main->program.parameters.array[f_console_standard_parameter_help_e].result & f_console_result_found_e) {
      main->setting.flag |= control_main_flag_help_e;

      return;
    }

    if (main->program.parameters.array[f_console_standard_parameter_version_e].result & f_console_result_found_e) {
      main->setting.flag |= control_main_flag_version_e;

      return;
    }

    if (main->program.parameters.array[f_console_standard_parameter_copyright_e].result & f_console_result_found_e) {
      main->setting.flag |= control_main_flag_copyright_e;

      return;
    }

    if (main->program.parameters.array[control_parameter_return_e].result & f_console_result_found_e) {
      main->setting.flag |= control_main_flag_return_e;

      return;
    }

    f_number_unsigned_t index = 0;

    if (main->program.pipe & fll_program_data_pipe_input_e) {
      main->setting.flag |= control_main_flag_pipe_e;
    }
    else {
      main->setting.flag &= ~control_main_flag_pipe_e;
    }

    // The settings path is statically allocated.
    if (main->program.parameters.array[control_parameter_settings_e].result & f_console_result_value_e) {
      index = main->program.parameters.array[control_parameter_settings_e].values.array[main->program.parameters.array[control_parameter_settings_e].values.used - 1];

      main->setting.path_settings.string = main->program.parameters.arguments.array[index].string;
      main->setting.path_settings.used = main->program.parameters.arguments.array[index].used;
      main->setting.path_settings.size = 0;
    }
    else {
      main->setting.path_settings.string = control_path_settings_s.string;
      main->setting.path_settings.used = control_path_settings_s.used;
      main->setting.path_settings.size = 0;
    }

    {
      f_file_t file = f_file_t_initialize;

      main->setting.state.status = f_file_stream_open(main->setting.path_settings, f_file_open_mode_read_s, &file);

      if (F_status_is_error(main->setting.state.status)) {
        if ((main->setting.flag & control_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        control_print_error_file(&main->program.error, macro_control_f(f_file_stream_open), main->setting.path_settings, f_file_operation_open_s, fll_error_file_type_file_e);

        return;
      }

      main->setting.state.status = f_file_stream_read(file, &main->cache.large);

      f_file_stream_flush(file);
      f_file_stream_close(&file);

      if (F_status_is_error(main->setting.state.status)) {
        if ((main->setting.flag & control_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        control_print_error_file(&main->program.error, macro_control_f(f_file_stream_read), main->setting.path_settings, f_file_operation_read_s, fll_error_file_type_file_e);

        return;
      }
    }

    if (main->cache.large.used) {
      main->setting.range.start = 0;
      main->setting.range.stop = main->cache.large.used - 1;
    }
    else {
      main->setting.range.start = 1;
      main->setting.range.stop = 0;
    }

    fll_fss_extended_read(main->cache.large, &main->setting.range, &main->cache.objects, &main->cache.contents, 0, 0, &main->cache.delimits, 0, &main->setting.state);

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & control_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      control_print_error_file(&main->program.error, macro_control_f(fll_fss_extended_read), main->setting.path_settings, f_file_operation_process_s, fll_error_file_type_file_e);

      return;
    }

    f_fss_apply_delimit(main->cache.delimits, &main->cache.large, &main->setting.state);

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & control_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      control_print_error_file(&main->program.error, macro_control_f(f_fss_apply_delimit), main->setting.path_settings, f_file_operation_process_s, fll_error_file_type_file_e);

      return;
    }

    uint8_t i = 0;
    uint8_t parameter_hass[] = { 0, 0, 0, 0 };
    f_number_unsigned_t parameter_ats[] = { 0, 0, 0, 0 };

    {
      const f_string_static_t parameter_names[] = {
        control_name_socket_s,
        control_path_socket_s,
        control_path_socket_prefix_s,
        control_path_socket_suffix_s,
      };

      f_number_unsigned_t j = 0;
      uint8_t k = 0;

      for (; j < main->cache.objects.used; ++j) {

        for (k = 0; k < 4; ++k) {

          if (!parameter_names[k].used) continue;

          main->setting.range.start = 0;
          main->setting.range.stop = parameter_names[k].used - 1;

          if (f_compare_dynamic_partial(parameter_names[k], main->cache.large, main->setting.range, main->cache.objects.array[j]) == F_equal_to) {
            parameter_hass[k] = F_true;
            parameter_ats[k] = j;

            break;
          }
        } // for
      } // for
    }

    // The settings path is statically allocated, except when read from the settings file.
    if (main->program.parameters.array[control_parameter_socket_e].result & f_console_result_value_e) {
      index = main->program.parameters.array[control_parameter_settings_e].values.array[main->program.parameters.array[control_parameter_settings_e].values.used - 1];

      main->setting.path_socket.string = main->program.parameters.arguments.array[index].string;
      main->setting.path_socket.used = main->program.parameters.arguments.array[index].used;
      main->setting.path_socket.size = 0;
    }
    else if (parameter_hass[1]) {
      main->setting.state.status = f_string_dynamic_partial_append_nulless(main->cache.large, main->cache.objects.array[parameter_ats[1]], &main->setting.path_socket);

      if (F_status_is_error(main->setting.state.status)) {
        if ((main->setting.flag & control_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        control_print_error_file(&main->program.error, macro_control_f(f_string_dynamic_partial_append_nulless), main->setting.path_socket, f_file_operation_process_s, fll_error_file_type_file_e);

        return;
      }
    }
    else {
      main->setting.path_socket.string = controller_path_socket_s.string;
      main->setting.path_socket.used = controller_path_socket_s.used;
      main->setting.path_socket.size = 0;
    }

    main->setting.state.status = f_file_exists(main->setting.path_socket, F_true);

    if (F_status_is_error(main->setting.state.status) || main->setting.state.status == F_false) {
      if ((main->setting.flag & control_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      if (F_status_is_error(main->setting.state.status)) {
        control_print_error_file(&main->program.error, macro_control_f(f_file_exists), main->setting.path_socket, f_file_operation_find_s, fll_error_file_type_directory_e);

        if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.error.to);
        }
      }

      main->setting.state.status = F_status_set_error(F_socket_not);

      control_print_error_socket_file_missing(&main->program.error, main->setting.path_socket);

      return;
    }

    // Construct the file name when the socket path is a directory.
    if (f_file_is(main->setting.path_socket, F_file_type_directory_d, F_true) == F_true) {
      main->setting.state.status = f_string_dynamic_append_assure(f_path_separator_s, &main->setting.path_socket);

      if (F_status_is_error(main->setting.state.status)) {
        if ((main->setting.flag & control_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        control_print_error(&main->program.error, macro_control_f(f_string_dynamic_append_assure));

        return;
      }

      {
        const uint8_t append_ids[] = {
          0,
          control_parameter_name_e,
          0,
        };

        const uint8_t append_hass[] = {
          parameter_hass[2],
          parameter_hass[0],
          parameter_hass[3],
        };

        const f_string_static_t append_defaults[] = {
          controller_path_socket_prefix_s,
          controller_name_socket_s,
          controller_path_socket_suffix_s,
        };

        for (i = 0; i < 3; ++i) {

          if (append_ids[i] && main->program.parameters.array[append_ids[i]].result & f_console_result_value_e) {
            index = main->program.parameters.array[append_ids[i]].values.array[main->program.parameters.array[append_ids[i]].values.used - 1];

            main->setting.state.status = f_string_dynamic_append(main->program.parameters.arguments.array[index], &main->setting.path_socket);
          }
          else if (append_hass[i]) {
            main->setting.state.status = f_string_dynamic_partial_append_nulless(main->cache.large, main->cache.objects.array[append_hass[i]], &main->setting.path_socket);
          }
          else {
            main->setting.state.status = f_string_dynamic_append_nulless(append_defaults[i], &main->setting.path_socket);
          }

          if (F_status_is_error(main->setting.state.status)) {
            if ((main->setting.flag & control_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
            }

            control_print_error(
              &main->program.error,
              ((append_ids[i] && main->program.parameters.array[append_ids[i]].result & f_console_result_value_e) || !append_hass[i])
                ? macro_control_f(f_string_dynamic_append)
                : macro_control_f(f_string_dynamic_partial_append_nulless)
            );

            return;
          }
        } // for

        main->setting.state.status = f_file_exists(main->setting.path_socket, F_true);

        if (F_status_is_error(main->setting.state.status) || main->setting.state.status == F_false) {
          if ((main->setting.flag & control_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          if (F_status_is_error(main->setting.state.status)) {
            control_print_error_file(&main->program.error, macro_control_f(f_file_exists), main->setting.path_socket, f_file_operation_find_s, fll_error_file_type_directory_e);

            if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.error.to);
            }
          }

          main->setting.state.status = F_status_set_error(F_socket_not);

          control_print_error_socket_file_missing(&main->program.error, main->setting.path_socket);

          return;
        }
      }
    }

    if (f_file_is(main->setting.path_socket, F_file_type_socket_d, F_true) == F_false) {
      main->setting.state.status = F_status_set_error(F_socket_not);

      if ((main->setting.flag & control_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      control_print_error_socket_file_not(&main->program.error, main->setting.path_socket);

      return;
    }

    main->setting.state.status = f_socket_create(&main->setting.socket);

    if (F_status_is_error(main->setting.state.status)) {
      control_print_error(&main->program.error, macro_control_f(f_socket_create));

      if ((main->setting.flag & control_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      control_print_error_socket_file_failed(&main->program.error, main->setting.path_socket);

      return;
    }

    main->setting.state.status = f_socket_connect(&main->setting.socket);

    if (F_status_is_error(main->setting.state.status)) {
      control_print_error(&main->program.error, macro_control_f(f_socket_connect));

      if ((main->setting.flag & control_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      control_print_error_socket_file_failed(&main->program.error, main->setting.path_socket);

      return;
    }

    f_memory_array_resize(0, sizeof(f_range_t), (void **) &main->cache.objects.array, &main->cache.objects.used, &main->cache.objects.size);
    f_memory_arrays_resize(0, sizeof(f_ranges_t), (void **) &main->cache.contents.array, &main->cache.contents.used, &main->cache.contents.size, &f_rangess_delete_callback);
    f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &main->cache.delimits.array, &main->cache.delimits.used, &main->cache.delimits.size);

    {
      const uint8_t ids[] = {
        control_parameter_name_e,
        control_parameter_settings_e,
        control_parameter_socket_e
      };

      const f_string_static_t names[] = {
        control_long_name_s,
        control_long_settings_s,
        control_long_socket_s
      };

      f_status_t error_printed_not = F_false;

      for (i = 0; i < 3; ++i) {

        if (main->program.parameters.array[ids[i]].result & f_console_result_found_e) {
          main->setting.state.status = F_status_set_error(F_parameter);

          if (error_printed_not) {
            error_printed_not = F_true;

            if ((main->setting.flag & control_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
            }
          }

          control_print_error_parameter_value_not(&main->program.error, names[i]);
        }
        else if (main->program.parameters.array[ids[i]].result & f_console_result_value_e) {
          index = main->program.parameters.array[ids[i]].values.array[main->program.parameters.array[ids[i]].values.used - 1];

          if (!main->program.parameters.arguments.array[index].used) {
            main->setting.state.status = F_status_set_error(F_parameter);

            if (error_printed_not) {
              error_printed_not = F_true;

              if ((main->setting.flag & control_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
                fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
              }
            }

            control_print_error_parameter_value_empty(&main->program.error, names[i]);
          }
        }
      } // for
    }

    main->cache.large.used = 0;

    if (main->cache.large.size > control_default_buffer_limit_soft_large_d) {
      main->setting.state.status = f_memory_array_resize(control_default_buffer_limit_soft_large_d, sizeof(f_char_t), (void **) &main->cache.large.string, &main->cache.large.used, &main->cache.large.size);

      if (F_status_is_error(main->setting.state.status)) {
        if ((main->setting.flag & control_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        control_print_error(&main->program.error, macro_control_f(f_memory_array_resize));

        return;
      }
    }

    if (main->program.parameters.remaining.used) {
      main->setting.state.status = f_memory_array_increase_by(main->program.parameters.remaining.used, sizeof(f_string_dynamic_t), (void **) &main->setting.actions.array, &main->setting.actions.used, &main->setting.actions.size);

      if (F_status_is_error(main->setting.state.status)) {
        if ((main->setting.flag & control_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        control_print_error(&main->program.error, macro_control_f(f_memory_array_increase_by));

        return;
      }

      index = 0;

      for (f_number_unsigned_t number = 0; index < main->program.parameters.remaining.used; ++index) {

        if (control_signal_check(main)) return;

        number = main->program.parameters.remaining.array[index];

        // Statically allocate the inner strings.
        main->setting.actions.array[main->setting.actions.used].string = main->program.parameters.arguments.array[number].string;
        main->setting.actions.array[main->setting.actions.used].used = main->program.parameters.arguments.array[number].used;
        main->setting.actions.array[main->setting.actions.used++].size = 0;
      } // for
    }

    main->setting.state.status = F_okay;
  }
#endif // _di_control_setting_load_

#ifdef __cplusplus
} // extern "C"
#endif
