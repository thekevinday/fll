#include "fss_basic_write.h"
#include "private-common.h"
#include "private-write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_basic_write_main_
  f_status_t fss_basic_write_main(fll_program_data_t * const main, fss_basic_write_setting_t * const setting) {

    f_status_t status = F_none;

    // Load parameters.
    status = f_console_parameter_process(arguments, &main->parameters);
    if (F_status_is_error(status)) return;

    {
      f_array_length_t choice = 0;
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { fss_basic_write_parameter_no_color_e, fss_basic_write_parameter_light_e, fss_basic_write_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        const uint8_t modes[3] = { f_color_mode_color_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        status = fll_program_parameter_process_context(choices, modes, F_true, main);

        if (F_status_is_error(status)) {
          fss_basic_write_print_line_first_locked(setting, main->error);
          fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process_context", F_true);
          fss_basic_write_print_line_last_locked(setting, main->error);

          return;
        }
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { fss_basic_write_parameter_verbosity_quiet_e, fss_basic_write_parameter_verbosity_error_e, fss_basic_write_parameter_verbosity_verbose_e, fss_basic_write_parameter_verbosity_debug_e, fss_basic_write_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, main);

        if (F_status_is_error(status)) {
          fss_basic_write_print_line_first_locked(setting, main->error);
          fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process_verbosity", F_true);
          fss_basic_write_print_line_last_locked(setting, main->error);

          return;
        }
      }
    }

    f_string_static_t * const argv = main->parameters.arguments.array;

    status = F_none;

    if (main->parameters.array[fss_basic_write_parameter_help_e].result & f_console_result_found_e) {
      fss_basic_write_print_help(setting, main->message);

      return status;
    }

    if (main->parameters.array[fss_basic_write_parameter_version_e].result & f_console_result_found_e) {
      fll_program_print_version(main->message, fss_basic_write_program_version_s);

      return status;
    }

    f_file_t output = f_file_t_initialize;

    output.id = F_type_descriptor_output_d;
    output.stream = F_type_output_d;
    output.flag = F_file_flag_create_d | F_file_flag_write_only_d | F_file_flag_append_d;

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[fss_basic_write_parameter_file_e].result & f_console_result_value_e) {
        if (main->parameters.array[fss_basic_write_parameter_file_e].values.used > 1) {
          if (main->error.verbosity > f_console_verbosity_quiet_e) {
            f_file_stream_lock(main->error.to);

            fl_print_format("%r%[%QThe parameter '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, fss_basic_write_long_file_s, main->error.notable);
            fl_print_format("%[' may only be specified once.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

            f_file_stream_unlock(main->error.to);
          }

          status = F_status_set_error(F_parameter);
        }
        else {
          const f_array_length_t index = main->parameters.array[fss_basic_write_parameter_file_e].values.array[0];

          output.id = -1;
          output.stream = 0;
          status = f_file_stream_open(argv[index], f_string_empty_s, &output);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_open", F_true, argv[index], f_file_operation_open_s, fll_error_file_type_file_e);
          }
        }
      }
      else if (main->parameters.array[fss_basic_write_parameter_file_e].result & f_console_result_found_e) {
        fss_basic_write_error_parameter_value_missing_print(main, f_console_symbol_long_normal_s, fss_basic_write_long_file_s);
        status = F_status_set_error(F_parameter);
      }
    }

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[fss_basic_write_parameter_object_e].locations.used || main->parameters.array[fss_basic_write_parameter_content_e].locations.used) {
        if (main->parameters.array[fss_basic_write_parameter_object_e].locations.used) {
          if (main->parameters.array[fss_basic_write_parameter_object_e].locations.used != main->parameters.array[fss_basic_write_parameter_object_e].values.used) {
            fss_basic_write_error_parameter_value_missing_print(main, f_console_symbol_long_normal_s, fss_basic_write_long_object_s);
            status = F_status_set_error(F_parameter);
          }
          else if (main->parameters.array[fss_basic_write_parameter_content_e].locations.used != main->parameters.array[fss_basic_write_parameter_content_e].values.used) {
            fss_basic_write_error_parameter_value_missing_print(main, f_console_symbol_long_normal_s, fss_basic_write_long_content_s);
            status = F_status_set_error(F_parameter);
          }
          else if (main->parameters.array[fss_basic_write_parameter_object_e].locations.used != main->parameters.array[fss_basic_write_parameter_content_e].locations.used && !(main->parameters.array[fss_basic_write_parameter_partial_e].result & f_console_result_found_e)) {
            fss_basic_write_error_parameter_same_times_print(main);
            status = F_status_set_error(F_parameter);
          }
          else if (main->parameters.array[fss_basic_write_parameter_content_e].locations.used && main->parameters.array[fss_basic_write_parameter_partial_e].locations.used) {
            if (main->parameters.array[fss_basic_write_parameter_content_e].result & f_console_result_value_e) {
              if (main->error.verbosity > f_console_verbosity_quiet_e) {
                f_file_stream_lock(main->error.to);

                fl_print_format("%r%[%QThe '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
                fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, fss_basic_write_long_partial_s, main->error.notable);
                fl_print_format("%[' parameter only allows either the '%]", main->error.to, main->error.context, main->error.context);
                fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, fss_basic_write_long_object_s, main->error.notable);
                fl_print_format("%[' parameter or the '%]", main->error.to, main->error.context, main->error.context);
                fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, fss_basic_write_long_content_s, main->error.notable);
                fl_print_format("%[' parameter, but not both.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

                f_file_stream_unlock(main->error.to);
              }

              status = F_status_set_error(F_parameter);
            }
          }

          if (F_status_is_error_not(status)) {
            if (main->parameters.array[fss_basic_write_parameter_content_e].result & f_console_result_value_e) {
              f_array_length_t location_object = 0;
              f_array_length_t location_content = 0;
              f_array_length_t location_sub_object = 0;
              f_array_length_t location_sub_content = 0;

              for (f_array_length_t i = 0; i < main->parameters.array[fss_basic_write_parameter_object_e].locations.used; ++i) {
                location_object = main->parameters.array[fss_basic_write_parameter_object_e].locations.array[i];
                location_content = main->parameters.array[fss_basic_write_parameter_content_e].locations.array[i];
                location_sub_object = main->parameters.array[fss_basic_write_parameter_object_e].locations_sub.array[i];
                location_sub_content = main->parameters.array[fss_basic_write_parameter_content_e].locations_sub.array[i];

                if (location_object > location_content || location_object == location_content && location_sub_object > location_sub_content) {
                  if (main->error.verbosity > f_console_verbosity_quiet_e) {
                    f_file_stream_lock(main->error.to);

                    fl_print_format("%r%[%QEach '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
                    fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, fss_basic_write_long_object_s, main->error.notable);
                    fl_print_format("%[' parameter must be specified before a '%]", main->error.to, main->error.context, main->error.context);
                    fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, fss_basic_write_long_content_s, main->error.notable);
                    fl_print_format("%[' parameter.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

                    f_file_stream_unlock(main->error.to);
                  }

                  status = F_status_set_error(F_parameter);

                  break;
                }
              } // for
            }
          }
        }
        else if (main->parameters.array[fss_basic_write_parameter_content_e].locations.used) {
          if (main->parameters.array[fss_basic_write_parameter_content_e].locations.used != main->parameters.array[fss_basic_write_parameter_content_e].values.used) {
            fss_basic_write_error_parameter_value_missing_print(main, f_console_symbol_long_normal_s, fss_basic_write_long_content_s);
            status = F_status_set_error(F_parameter);
          }
          else if (!main->parameters.array[fss_basic_write_parameter_partial_e].locations.used) {
            fss_basic_write_error_parameter_same_times_print(main);
            status = F_status_set_error(F_parameter);
          }
        }
      }
      else if (!(main->pipe & fll_program_data_pipe_input_e)) {
        if (main->error.verbosity > f_console_verbosity_quiet_e) {
          f_file_stream_lock(main->error.to);

          fl_print_format("%r%[%QThis requires either piped data or the use of the '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, fss_basic_write_long_object_s, main->error.notable);
          fl_print_format("%[' parameter with the '%]", main->error.to, main->error.context, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, fss_basic_write_long_content_s, main->error.notable);
          fl_print_format("%[' parameter.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

          f_file_stream_unlock(main->error.to);
        }

        status = F_status_set_error(F_parameter);
      }

      if (F_status_is_error_not(status) && (main->pipe & fll_program_data_pipe_input_e)) {
        if (main->parameters.array[fss_basic_write_parameter_partial_e].result & f_console_result_found_e) {
          if (main->error.verbosity > f_console_verbosity_quiet_e) {
            f_file_stream_lock(main->error.to);

            fl_print_format("%r%[%QThis '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, fss_basic_write_long_partial_s, main->error.notable);
            fl_print_format("%[' parameter cannot be used when processing a pipe.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

            f_file_stream_unlock(main->error.to);
          }

          status = F_status_set_error(F_parameter);
        }
      }
    }

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[fss_basic_write_parameter_prepend_e].result & f_console_result_found_e) {
        if (main->error.verbosity > f_console_verbosity_quiet_e) {
          f_file_stream_lock(main->error.to);

          fl_print_format("%r%[%QThe parameter '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, fss_basic_write_long_prepend_s, main->error.notable);
          fl_print_format("%[' is specified, but no value is given.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

          f_file_stream_unlock(main->error.to);
        }

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters.array[fss_basic_write_parameter_prepend_e].result & f_console_result_value_e) {
        const f_array_length_t index = main->parameters.array[fss_basic_write_parameter_prepend_e].values.array[main->parameters.array[fss_basic_write_parameter_prepend_e].values.used - 1];

        // Even though this standard does not utilize this parameter, provide the validation for consistency.
        if (argv[index].used) {
          f_string_range_t range = macro_f_string_range_t_initialize2(argv[index].used);
          f_state_t state = f_state_t_initialize;

          for (; range.start < argv[index].used; ++range.start) {

            status = f_fss_is_space(state, argv[index], range);
            if (F_status_is_error(status)) break;

            if (status == F_false) {
              if (main->error.verbosity > f_console_verbosity_quiet_e) {
                f_file_stream_lock(main->error.to);

                fl_print_format("%r%[%QThe value for the parameter '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
                fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, fss_basic_write_long_prepend_s, main->error.notable);
                fl_print_format("%[' must only contain white space.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

                f_file_stream_unlock(main->error.to);
              }

              status = F_status_set_error(F_parameter);

              break;
            }
          } // for
        }
        else {
          if (main->error.verbosity > f_console_verbosity_quiet_e) {
            f_file_stream_lock(main->error.to);

            fl_print_format("%r%[%QThe value for the parameter '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, fss_basic_write_long_prepend_s, main->error.notable);
            fl_print_format("%[' must not be an empty string.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

            f_file_stream_unlock(main->error.to);
          }

          status = F_status_set_error(F_parameter);
        }
      }
    }

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[fss_basic_write_parameter_ignore_e].result & f_console_result_found_e) {
        if (main->error.verbosity > f_console_verbosity_quiet_e) {
          f_file_stream_lock(main->error.to);

          fl_print_format("%r%[%QThe parameter '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, fss_basic_write_long_ignore_s, main->error.notable);
          fl_print_format("%[' was specified, but no values were given.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

          f_file_stream_unlock(main->error.to);
        }

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters.array[fss_basic_write_parameter_ignore_e].result & f_console_result_value_e) {
        const f_array_length_t total_locations = main->parameters.array[fss_basic_write_parameter_ignore_e].locations.used;
        const f_array_length_t total_arguments = main->parameters.array[fss_basic_write_parameter_ignore_e].values.used;

        if (total_locations * 2 > total_arguments) {
          f_file_stream_lock(main->error.to);

          fl_print_format("%r%[%QThe parameter '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, fss_basic_write_long_ignore_s, main->error.notable);
          fl_print_format("%[' requires two values.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

          f_file_stream_unlock(main->error.to);

          status = F_status_set_error(F_parameter);
        }
      }
    }

    uint8_t quote = f_fss_quote_double_s;

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[fss_basic_write_parameter_double_e].result & f_console_result_found_e) {
        if (main->parameters.array[fss_basic_write_parameter_single_e].result & f_console_result_found_e) {
          if (main->parameters.array[fss_basic_write_parameter_double_e].location < main->parameters.array[fss_basic_write_parameter_single_e].location) {
            quote = f_fss_quote_single_s;
          }
        }
      }
      else if (main->parameters.array[fss_basic_write_parameter_single_e].result & f_console_result_found_e) {
        quote = f_fss_quote_single_s;
      }
    }

    f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

    if (F_status_is_error_not(status)) {
      if (main->pipe & fll_program_data_pipe_input_e) {
        status = fss_basic_write_process_pipe(main, output, quote, &buffer);

        if (F_status_is_error(status)) {
          if (main->error.verbosity > f_console_verbosity_quiet_e) {
            f_file_stream_lock(main->error.to);

            fl_print_format("%r%[%QWhile processing the '%]%[input pipe%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context, main->error.notable, main->error.notable);
            fl_print_format("%['.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

            f_file_stream_unlock(main->error.to);
          }
        }
      }

      if (F_status_is_error_not(status)) {
        if (main->parameters.array[fss_basic_write_parameter_partial_e].result & f_console_result_found_e) {
          if (main->parameters.array[fss_basic_write_parameter_object_e].result & f_console_result_value_e) {
            for (f_array_length_t i = 0; i < main->parameters.array[fss_basic_write_parameter_object_e].values.used; ++i) {

              if (!((++main->signal_check) % fss_basic_write_signal_check_d)) {
                if (fll_program_standard_signal_received(main)) {
                  fll_program_print_signal_received(main->warning, setting->line_first, main->signal_received);

                  status = F_status_set_error(F_interrupt);

                  break;
                }

                main->signal_check = 0;
              }

              status = fss_basic_write_process(main, output, quote, &argv[main->parameters.array[fss_basic_write_parameter_object_e].values.array[i]], 0, &buffer);
              if (F_status_is_error(status)) break;
            } // for
          }
          else {
            for (f_array_length_t i = 0; i < main->parameters.array[fss_basic_write_parameter_content_e].values.used; ++i) {

              if (!((++main->signal_check) % fss_basic_write_signal_check_d)) {
                if (fll_program_standard_signal_received(main)) {
                  fll_program_print_signal_received(main->warning, setting->line_first, main->signal_received);

                  status = F_status_set_error(F_interrupt);

                  break;
                }

                main->signal_check = 0;
              }

              status = fss_basic_write_process(main, output, quote, 0, &argv[main->parameters.array[fss_basic_write_parameter_content_e].values.array[i]], &buffer);
              if (F_status_is_error(status)) break;
            } // for
          }
        }
        else {
          for (f_array_length_t i = 0; i < main->parameters.array[fss_basic_write_parameter_object_e].values.used; ++i) {

            if (!((++main->signal_check) % fss_basic_write_signal_check_d)) {
              if (fll_program_standard_signal_received(main)) {
                fll_program_print_signal_received(main->warning, setting->line_first, main->signal_received);

                status = F_status_set_error(F_interrupt);

                break;
              }

              main->signal_check = 0;
            }

            status = fss_basic_write_process(main, output, quote, &argv[main->parameters.array[fss_basic_write_parameter_object_e].values.array[i]], &argv[main->parameters.array[fss_basic_write_parameter_content_e].values.array[i]], &buffer);
            if (F_status_is_error(status)) break;
          } // for
        }

        if (F_status_is_error(status)) {
          if (main->error.verbosity > f_console_verbosity_quiet_e) {
            f_file_stream_lock(main->error.to);

            fl_print_format("%r%[%QWhile processing the '%]%[input arguments%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context, main->error.notable, main->error.notable);
            fl_print_format("%['.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

            f_file_stream_unlock(main->error.to);
          }
        }
        else if (main->error.verbosity > f_console_verbosity_quiet_e && main->error.verbosity != f_console_verbosity_error_e && !(main->parameters.array[fss_basic_write_parameter_file_e].result & f_console_result_found_e)) {

          // Ensure there is always a newline at the end, unless in quiet mode.
          fll_print_dynamic_raw(f_string_eol_s, main->output.to);
        }
      }
    }

    if (main->parameters.array[fss_basic_write_parameter_file_e].result & f_console_result_value_e) {
      f_file_stream_flush(output);
      f_file_stream_close(&output);
    }

    // Ensure a newline is always put at the end of the program execution, unless in quiet mode.
    if (main->error.verbosity > f_console_verbosity_quiet_e) {
      if (F_status_is_error(status)) {
        fll_print_dynamic_raw(f_string_eol_s, main->error.to);
      }
    }

    f_string_dynamic_resize(0, &buffer);

    return status;
  }
#endif // _di_fss_basic_write_main_

#ifdef __cplusplus
} // extern "C"
#endif
