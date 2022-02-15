#include "control.h"
#include "private-common.h"
#include "private-control.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_control_command_identify_
  f_status_t control_command_identify(fll_program_data_t * const main, control_data_t * const data, const f_string_static_t command) {

    if (fl_string_dynamic_compare(command, control_freeze_s) == F_equal_to) {
      data->command = control_command_type_freeze_e;

      return F_found;
    }

    if (fl_string_dynamic_compare(command, control_kill_s) == F_equal_to) {
      data->command = control_command_type_kill_e;

      return F_found;
    }

    if (fl_string_dynamic_compare(command, control_pause_s) == F_equal_to) {
      data->command = control_command_type_pause_e;

      return F_found;
    }

    if (fl_string_dynamic_compare(command, control_reboot_s) == F_equal_to) {
      data->command = control_command_type_reboot_e;

      return F_found;
    }

    if (fl_string_dynamic_compare(command, control_reload_s) == F_equal_to) {
      data->command = control_command_type_reload_e;

      return F_found;
    }

    if (fl_string_dynamic_compare(command, control_rerun_s) == F_equal_to) {
      data->command = control_command_type_rerun_e;

      return F_found;
    }

    if (fl_string_dynamic_compare(command, control_restart_s) == F_equal_to) {
      data->command = control_command_type_restart_e;

      return F_found;
    }

    if (fl_string_dynamic_compare(command, control_resume_s) == F_equal_to) {
      data->command = control_command_type_resume_e;

      return F_found;
    }

    if (fl_string_dynamic_compare(command, control_shutdown_s) == F_equal_to) {
      data->command = control_command_type_shutdown_e;

      return F_found;
    }

    if (fl_string_dynamic_compare(command, control_start_s) == F_equal_to) {
      data->command = control_command_type_start_e;

      return F_found;
    }

    if (fl_string_dynamic_compare(command, control_stop_s) == F_equal_to) {
      data->command = control_command_type_stop_e;

      return F_found;
    }

    if (fl_string_dynamic_compare(command, control_thaw_s) == F_equal_to) {
      data->command = control_command_type_thaw_e;

      return F_found;
    }

    return F_found_not;
  }
#endif // _di_control_command_identify_

#ifndef _di_control_command_verify_
  f_status_t control_command_verify(fll_program_data_t * const main, control_data_t * const data) {

    switch (data->command) {
      case control_command_type_freeze_e:
      case control_command_type_kill_e:
      case control_command_type_pause_e:
      case control_command_type_reload_e:
      case control_command_type_rerun_e:
      case control_command_type_restart_e:
      case control_command_type_resume_e:
      case control_command_type_start_e:
      case control_command_type_stop_e:
      case control_command_type_thaw_e:
        if (main->parameters.remaining.used < 2) {
          control_print_error_parameter_command_rule_not(main, data->argv[main->parameters.remaining.array[0]]);

          return F_status_set_error(F_parameter);
        }
        else if (main->parameters.remaining.used > 3) {
          control_print_error_parameter_command_rule_too_many(main, data->argv[main->parameters.remaining.array[0]]);

          return F_status_set_error(F_parameter);
        }

        if (!data->argv[main->parameters.remaining.array[1]].used) {
          if (main->parameters.remaining.used == 2) {
            control_print_error_parameter_command_rule_empty(main, data->argv[main->parameters.remaining.array[0]]);
          }
          else {
            control_print_error_parameter_command_rule_directory_empty(main, data->argv[main->parameters.remaining.array[0]]);
          }

          return F_status_set_error(F_parameter);
        }

        if (main->parameters.remaining.used == 3) {
          if (!data->argv[main->parameters.remaining.array[2]].used) {
            control_print_error_parameter_command_rule_basename_empty(main, data->argv[main->parameters.remaining.array[0]]);

            return F_status_set_error(F_parameter);
          }
        }

        return F_none;
    }

    if (data->command == control_command_type_reboot_e) {
      // @todo
    }

    if (data->command == control_command_type_shutdown_e) {
      // @todo
    }

    return F_none;
  }
#endif // _di_control_command_verify_

#ifndef _di_control_settings_load_
  f_status_t control_settings_load(fll_program_data_t * const main, control_data_t * const data) {

    f_status_t status = F_none;

    data->cache.buffer_small.used = 0;

    if (main->parameters.array[control_parameter_socket_e].result == f_console_result_additional_e) {
      const f_array_length_t index = main->parameters.array[control_parameter_settings_e].values.array[main->parameters.array[control_parameter_settings_e].values.used - 1];

      status = f_string_dynamic_append(data->argv[index], &data->cache.buffer_small);
    }
    else {
      status = f_string_dynamic_append(control_path_settings_s, &data->cache.buffer_small);
    }

    if (F_status_is_error(status)) {
      fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_append", F_true);

      return status;
    }

    {
      f_file_t file = f_file_t_initialize;

      status = f_file_stream_open(data->cache.buffer_small, f_file_open_mode_read_s, &file);

      if (F_status_is_error(status)) {
        fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_open", F_true, data->cache.buffer_small, f_file_operation_open_s, fll_error_file_type_file_e);

        return status;
      }

      status = f_file_stream_read(file, &data->cache.buffer_large);

      f_file_stream_close(F_true, &file);

      if (F_status_is_error(status)) {
        fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_read", F_true, data->cache.buffer_small, f_file_operation_read_s, fll_error_file_type_file_e);

        return status;
      }
    }

    f_state_t state = f_state_t_initialize;
    f_string_range_t range = f_string_range_t_initialize;
    f_fss_objects_t objects = f_fss_objects_t_initialize;
    f_fss_contents_t contents = f_fss_contents_t_initialize;
    f_fss_delimits_t delimits = f_fss_delimits_t_initialize;

    status = fll_fss_extended_read(data->cache.buffer_large, state, &range, &objects, &contents, 0, 0, &delimits, 0);

    if (F_status_is_error(status)) {
      fll_error_file_print(main->error, F_status_set_fine(status), "fll_fss_extended_read", F_true, data->cache.buffer_small, f_file_operation_process_s, fll_error_file_type_file_e);
    }
    else {
      status = fl_fss_apply_delimit(delimits, &data->cache.buffer_large);

      if (F_status_is_error(status)) {
        fll_error_file_print(main->error, F_status_set_fine(status), "fl_fss_apply_delimit", F_true, data->cache.buffer_small, f_file_operation_process_s, fll_error_file_type_file_e);
      }
    }

    if (F_status_is_error_not(status)) {
      uint8_t parameter_hass[] = { 0, 0, 0, 0 };

      f_array_length_t parameter_ats[] = { 0, 0, 0, 0 };

      {
        const f_string_static_t parameter_names[] = {
          control_name_socket_s,
          control_path_socket_s,
          control_path_socket_prefix_s,
          control_path_socket_suffix_s,
        };

        f_array_length_t i = 0;
        uint8_t j = 0;
        f_string_range_t range = f_string_range_t_initialize;

        for (; i < objects.used; ++i) {

          for (j = 0; j < 4; ++j) {

            range.stop = parameter_names[j].used - 1;

            if (fl_string_dynamic_partial_compare(parameter_names[j], data->cache.buffer_large, range, objects.array[i]) == F_equal_to) {
              parameter_hass[j] = F_true;
              parameter_ats[j] = i;

              break;
            }
          } // for
        } // for
      }

      data->cache.buffer_small.used = 0;

      if (main->parameters.array[control_parameter_socket_e].result == f_console_result_additional_e) {
        const f_array_length_t index = main->parameters.array[control_parameter_socket_e].values.array[main->parameters.array[control_parameter_socket_e].values.used - 1];

        status = f_string_dynamic_append(data->argv[index], &data->cache.buffer_small);
      }
      else if (parameter_hass[1]) {
        status = f_string_dynamic_partial_append_nulless(data->cache.buffer_large, objects.array[parameter_ats[1]], &data->cache.buffer_small);
      }
      else {
        status = f_string_dynamic_append(controller_path_socket_s, &data->cache.buffer_small);
      }

      if (F_status_is_error(status)) {
        if (main->parameters.array[control_parameter_socket_e].result == f_console_result_additional_e || !parameter_hass[1]) {
          fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_append", F_true);
        }
        else {
          fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);
        }
      }
      else {
        status = f_string_dynamic_terminate_after(&data->cache.buffer_small);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);
        }
      }

      status = f_file_exists(data->cache.buffer_small);

      if (F_status_is_error(status) || status == F_false) {
        if (F_status_is_error(status)) {
          fll_error_file_print(main->error, F_status_set_fine(status), "f_file_exists", F_true, data->cache.buffer_small, f_file_operation_find_s, fll_error_file_type_directory_e);

          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->error.to.stream);
          }
        }

        control_print_error_socket_file_missing(main, data->cache.buffer_small);

        status = F_status_set_error(F_socket_not);
      }

      // Construct the file name when the socket path is a directory.
      else if (f_file_is(data->cache.buffer_small, F_file_type_directory_d, F_true) == F_true) {
        status = f_string_dynamic_append_assure(f_path_separator_s, &data->cache.buffer_small);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_append_assure", F_true);
        }
        else {
          uint8_t append_ids[] = {
            0,
            control_parameter_name_e,
            0,
          };

          uint8_t append_hass[] = {
            parameter_hass[2],
            parameter_hass[0],
            parameter_hass[3],
          };

          const f_string_static_t append_defaults[] = {
            controller_path_socket_prefix_s,
            controller_name_socket_s,
            controller_path_socket_suffix_s,
          };

          for (uint8_t i = 0; i < 3; ++i) {

            if (append_ids[i] && main->parameters.array[append_ids[i]].result == f_console_result_additional_e) {
              const f_array_length_t index = main->parameters.array[append_ids[i]].values.array[main->parameters.array[append_ids[i]].values.used - 1];

              status = f_string_dynamic_append(data->argv[index], &data->cache.buffer_small);
            }
            else if (append_hass[i]) {
              status = f_string_dynamic_partial_append_nulless(data->cache.buffer_large, objects.array[append_hass[i]], &data->cache.buffer_small);
            }
            else {
              status = f_string_dynamic_append_nulless(append_defaults[i], &data->cache.buffer_small);
            }

            if (F_status_is_error(status)) {
              if (append_ids[i] && main->parameters.array[append_ids[i]].result == f_console_result_additional_e || !append_hass[i]) {
                fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_append", F_true);
              }
              else {
                fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);
              }

              break;
            }
          } // for

          if (F_status_is_error_not(status)) {
            status = f_string_dynamic_terminate_after(&data->cache.buffer_small);

            if (F_status_is_error(status)) {
              fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);
            }
          }

          if (F_status_is_error_not(status)) {
            status = f_file_exists(data->cache.buffer_small);

            if (F_status_is_error(status) || status == F_false) {
              if (F_status_is_error(status)) {
                fll_error_file_print(main->error, F_status_set_fine(status), "f_file_exists", F_true, data->cache.buffer_small, f_file_operation_find_s, fll_error_file_type_directory_e);

                if (main->error.verbosity != f_console_verbosity_quiet_e) {
                  fll_print_dynamic_raw(f_string_eol_s, main->error.to.stream);
                }
              }

              control_print_error_socket_file_missing(main, data->cache.buffer_small);

              status = F_status_set_error(F_socket_not);
            }
          }

          if (F_status_is_error_not(status)) {
            if (f_file_is(data->cache.buffer_small, F_file_type_socket_d, F_true) == F_false) {
              control_print_error_socket_file_not(main, data->cache.buffer_small);

              status = F_status_set_error(F_socket_not);
            }
          }

          if (F_status_is_error_not(status)) {
            status = f_socket_create(&data->socket);

            if (F_status_is_error(status)) {
              fll_error_print(main->error, F_status_set_fine(status), "f_socket_create", F_true);

              if (main->error.verbosity != f_console_verbosity_quiet_e) {
                fll_print_dynamic_raw(f_string_eol_s, main->error.to.stream);
              }

              control_print_error_socket_file_failed(main, data->cache.buffer_small);
            }
          }

          if (F_status_is_error_not(status)) {
            status = f_socket_connect(data->socket);

            if (F_status_is_error(status)) {
              fll_error_print(main->error, F_status_set_fine(status), "f_socket_connect", F_true);

              if (main->error.verbosity != f_console_verbosity_quiet_e) {
                fll_print_dynamic_raw(f_string_eol_s, main->error.to.stream);
              }

              control_print_error_socket_file_failed(main, data->cache.buffer_small);
            }
          }
        }
      }
    }

    f_string_ranges_resize(0, &objects);
    f_string_rangess_resize(0, &contents);
    f_array_lengths_resize(0, &delimits);

    data->cache.buffer_large.used = 0;
    data->cache.buffer_small.used = 0;

    if (F_status_is_error_not(status)) {
      if (data->cache.buffer_large.size > control_default_buffer_limit_soft_large_d) {
        status = f_string_dynamic_resize(control_default_buffer_limit_soft_large_d, &data->cache.buffer_large);
      }

      if (F_status_is_error_not(status)) {
        if (data->cache.buffer_small.size > control_default_buffer_limit_soft_small_d) {
          status = f_string_dynamic_resize(control_default_buffer_limit_soft_small_d, &data->cache.buffer_small);
        }
      }
    }

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_control_settings_load_

#ifdef __cplusplus
} // extern "C"
#endif
