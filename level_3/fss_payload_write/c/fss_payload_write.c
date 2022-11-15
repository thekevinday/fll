#include "fss_payload_write.h"
#include "private-common.h"
#include "private-write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_payload_write_main_
  void fss_payload_write_main(fll_program_data_t * const main, fss_payload_write_setting_t * const setting) {

    if (!main || !setting || F_status_is_error(setting->status)) return;

    setting->status = F_none;

    if (setting->flag & fss_payload_write_main_flag_help_e) {
      fss_payload_write_print_help(setting, main->message);

      return;
    }

    if (setting->flag & fss_payload_write_main_flag_version_e) {
      fll_program_print_version(main->message, fss_payload_write_program_version_s);

      return;
    }

    setting->escaped.used = 0;

    if (main->pipe & fll_program_data_pipe_input_e) {
      bool object_ended = F_false;

      f_array_length_t previous = 0;
      f_string_range_t range = f_string_range_t_initialize;
      f_status_t status = F_none;
      f_file_t pipe = f_file_t_initialize;

      pipe.id = F_type_descriptor_input_d;
      pipe.size_read = 1;

      setting->buffer.used = 0;
      setting->object.used = 0;
      setting->content.used = 0;

      range.start = 0;

      do {
        if (!((++main->signal_check) % fss_payload_write_signal_check_d)) {
          if (fll_program_standard_signal_received(main)) {
            setting->status = F_status_set_error(F_interrupt);

            return;
          }

          main->signal_check = 0;
        }

        if (status != F_none_eof) {
          status = f_file_read(pipe, &setting->buffer);

          if (F_status_is_error(status)) {
            setting->status = F_status_set_error(F_pipe);

            fss_payload_write_print_error_file(setting, main->error, "f_file_read", f_string_ascii_minus_s, f_file_operation_read_s, fll_error_file_type_pipe_e);

            return;
          }

          if (!setting->buffer.used) {
            setting->status = F_status_set_error(F_parameter);

            fss_payload_write_print_line_first_locked(setting, main->error);
            fll_program_print_error_pipe_missing_content(main->error);
            fss_payload_write_print_line_last_locked(setting, main->error);

            return;
          }

          range.stop = setting->buffer.used - 1;
        }

        previous = range.start;
        setting->status = f_string_dynamic_seek_to(setting->buffer, f_string_ascii_feed_form_s.string[0], &range);

        if (setting->status == F_data_not_stop) {
          setting->status = F_status_set_error(F_parameter);
        }

        if (F_status_is_error(setting->status)) {
          fss_payload_write_print_error(setting, main->error, "f_string_dynamic_seek_to");

          return;
        }

        if (object_ended && previous == range.start) {
          setting->status = F_status_set_error(F_parameter);

          fss_payload_write_print_line_first_locked(setting, main->error);
          fll_program_print_error_pipe_invalid_form_feed(main->error);
          fss_payload_write_print_line_last_locked(setting, main->error);

          return;
        }

        range.stop = range.start - 1;
        range.start = previous;

        if (object_ended) {
          setting->content.used = 0;

          if (setting->buffer.used) {
            setting->status = f_string_dynamic_partial_append_nulless(setting->buffer, range, &setting->content);

            if (F_status_is_error(setting->status)) {
              fss_payload_write_print_error(setting, main->error, "f_string_dynamic_partial_append_nulless");

              return;
            }
          }

          setting->status = fss_payload_write_process(main, setting, setting->object, setting->content);
          if (F_status_is_error(setting->status)) return;

          fll_print_dynamic_raw(f_string_eol_s, main->output.to);

          object_ended = F_false;
        }
        else {
          setting->object.used = 0;

          setting->status = f_string_dynamic_partial_append_nulless(setting->buffer, range, &setting->object);

          if (F_status_is_error(setting->status)) {
            fss_payload_write_print_error(setting, main->error, "f_string_dynamic_partial_append_nulless");

            return;
          }

          object_ended = F_true;
        }

        // Restore the range, positioned after the new line.
        range.start = range.stop + 2;
        range.stop = setting->buffer.used - 1;

        // Only clear the buffer and reset the start when the entire buffer has been processed.
        if (range.start > range.stop) {
          range.start = 0;
          setting->buffer.used = 0;
        }

      } while (status != F_none_eof || setting->buffer.used || object_ended);

      if (object_ended) {
        setting->status = F_status_set_error(F_parameter);

        fss_payload_write_print_line_first_locked(setting, main->error);
        fll_program_print_error_pipe_object_without_content(main->error);
        fss_payload_write_print_line_last_locked(setting, main->error);

        return;
      }
    }

    for (f_array_length_t i = 0; i < setting->objects.used; ++i) {

      if (!((++main->signal_check) % fss_payload_write_signal_check_d)) {
        if (fll_program_standard_signal_received(main)) {
          setting->status = F_status_set_error(F_interrupt);

          return;
        }

        main->signal_check = 0;
      }

      setting->status = fss_payload_write_process(main, setting, setting->objects.array[i], setting->contents.array[i]);
      if (F_status_is_error(setting->status)) return;

      fll_print_dynamic_raw(f_string_eol_s, main->output.to);
    } // for

    // Ensure a new line is always put at the end of the program execution, unless in quiet mode.
    fss_payload_write_print_line_last_locked(setting, main->message);


    // xxxxxxxxxxx

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[fss_payload_write_parameter_prepend_e].result == f_console_result_additional_e) {
        const f_array_length_t index = main->parameters.array[fss_payload_write_parameter_prepend_e].values.array[main->parameters.array[fss_payload_write_parameter_prepend_e].values.used - 1];

        if (argv[index].used) {
          f_string_range_t range = macro_f_string_range_t_initialize2(argv[index].used);
          f_state_t state = f_state_t_initialize;

          for (; range.start < argv[index].used; range.start++) {

            status = f_fss_is_space(state, argv[index], range);
            if (F_status_is_error(status)) break;

            if (status == F_false) {
              if (main->error.verbosity > f_console_verbosity_quiet_e) {
                f_file_stream_lock(main->error.to);

                fl_print_format("%r%[%QThe value for the parameter '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
                fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_enable_s, fss_payload_write_long_prepend_s, main->error.notable);
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
            fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_enable_s, fss_payload_write_long_prepend_s, main->error.notable);
            fl_print_format("%[' must not be an empty string.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

            f_file_stream_unlock(main->error.to);
          }

          status = F_status_set_error(F_parameter);
        }
      }
    }

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[fss_payload_write_parameter_ignore_e].result == f_console_result_found_e) {
        if (main->error.verbosity > f_console_verbosity_quiet_e) {
          f_file_stream_lock(main->error.to);

          fl_print_format("%r%[%QThe parameter '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_enable_s, fss_payload_write_long_ignore_s, main->error.notable);
          fl_print_format("%[' was specified, but no values were given.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

          f_file_stream_unlock(main->error.to);
        }

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters.array[fss_payload_write_parameter_ignore_e].result == f_console_result_additional_e) {
        const f_array_length_t total_locations = main->parameters.array[fss_payload_write_parameter_ignore_e].locations.used;
        const f_array_length_t total_arguments = main->parameters.array[fss_payload_write_parameter_ignore_e].values.used;

        if (total_locations * 2 > total_arguments) {
          f_file_stream_lock(main->error.to);

          fl_print_format("%r%[%QThe parameter '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_enable_s, fss_payload_write_long_ignore_s, main->error.notable);
          fl_print_format("%[' requires two values.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

          f_file_stream_unlock(main->error.to);

          status = F_status_set_error(F_parameter);
        }
      }
    }

    f_fss_quote_t quote = f_fss_quote_type_double_e;

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[fss_payload_write_parameter_double_e].result == f_console_result_found_e) {
        if (main->parameters.array[fss_payload_write_parameter_single_e].result == f_console_result_found_e) {
          if (main->parameters.array[fss_payload_write_parameter_double_e].location < main->parameters.array[fss_payload_write_parameter_single_e].location) {
            quote = f_fss_quote_type_single_e;
          }
        }
      }
      else if (main->parameters.array[fss_payload_write_parameter_single_e].result == f_console_result_found_e) {
        quote = f_fss_quote_type_single_e;
      }
    }

    f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

    if (F_status_is_error_not(status)) {
      f_string_dynamic_t escaped = f_string_dynamic_t_initialize;

      if (main->pipe & fll_program_data_pipe_input_e) {
        status = fss_payload_write_process_pipe(main, output, quote, &buffer);

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
        if (main->parameters.array[fss_payload_write_parameter_partial_e].result == f_console_result_found_e) {

          if (main->parameters.array[fss_payload_write_parameter_object_e].result == f_console_result_additional_e) {
            for (f_array_length_t i = 0; i < main->parameters.array[fss_payload_write_parameter_object_e].values.used; ++i) {

              if (!((++main->signal_check) % fss_payload_write_signal_check_d)) {
                if (fll_program_standard_signal_received(main)) {
                  fll_program_print_signal_received(main->warning, setting->line_first, main->signal_received);

                  status = F_status_set_error(F_interrupt);

                  break;
                }

                main->signal_check = 0;
              }

              status = fss_payload_write_process(main, output, quote, &argv[main->parameters.array[fss_payload_write_parameter_object_e].values.array[i]], 0, &buffer);
              if (F_status_is_error(status)) break;
            } // for
          }
          else {
            for (f_array_length_t i = 0; i < main->parameters.array[fss_payload_write_parameter_content_e].values.used; ++i) {

              if (!((++main->signal_check) % fss_payload_write_signal_check_d)) {
                if (fll_program_standard_signal_received(main)) {
                  fll_program_print_signal_received(main->warning, setting->line_first, main->signal_received);

                  status = F_status_set_error(F_interrupt);

                  break;
                }

                main->signal_check = 0;
              }

              status = fss_payload_write_process(main, output, quote, 0, &argv[main->parameters.array[fss_payload_write_parameter_content_e].values.array[i]], &buffer);
              if (F_status_is_error(status)) break;
            } // for
          }
        }
        else {
          for (f_array_length_t i = 0; i < main->parameters.array[fss_payload_write_parameter_object_e].values.used; ++i) {

            if (!((++main->signal_check) % fss_payload_write_signal_check_d)) {
              if (fll_program_standard_signal_received(main)) {
                fll_program_print_signal_received(main->warning, setting->line_first, main->signal_received);

                status = F_status_set_error(F_interrupt);

                break;
              }

              main->signal_check = 0;
            }

            status = fss_payload_write_process(main, output, quote, &argv[main->parameters.array[fss_payload_write_parameter_object_e].values.array[i]], &argv[main->parameters.array[fss_payload_write_parameter_content_e].values.array[i]], &buffer);
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
        else if (main->error.verbosity > f_console_verbosity_quiet_e && main->error.verbosity != f_console_verbosity_error_e && main->parameters.array[fss_payload_write_parameter_file_e].result == f_console_result_none_e) {

          // Ensure there is always a newline at the end, unless in quiet mode.
          fll_print_dynamic_raw(f_string_eol_s, main->output.to);
        }
      }

      f_string_dynamic_resize(0, &escaped);
    }

    if (main->parameters.array[fss_payload_write_parameter_file_e].result == f_console_result_additional_e) {
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
#endif // _di_fss_payload_write_main_

#ifdef __cplusplus
} // extern "C"
#endif
