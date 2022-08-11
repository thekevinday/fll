#include "iki_write.h"
#include "private-common.h"
#include "private-write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_write_print_help_
  f_status_t iki_write_print_help(const f_file_t file, const f_color_context_t context) {

    flockfile(file.stream);

    fll_program_print_help_header(file, context, iki_write_program_name_long_s, iki_write_program_version_s);

    fll_program_print_help_option(file, context, f_console_standard_short_help_s, f_console_standard_long_help_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Print this help message.");
    fll_program_print_help_option(file, context, f_console_standard_short_dark_s, f_console_standard_long_dark_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_light_s, f_console_standard_long_light_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "Do not print using color.");
    fll_program_print_help_option(file, context, f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Decrease verbosity, silencing most output.");
    fll_program_print_help_option(file, context, f_console_standard_short_error_s, f_console_standard_long_error_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Decrease verbosity, using only error output.");
    fll_program_print_help_option(file, context, f_console_standard_short_normal_s, f_console_standard_long_normal_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "  Set verbosity to normal.");
    fll_program_print_help_option(file, context, f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_debug_s, f_console_standard_long_debug_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Enable debugging, significantly increasing verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_version_s, f_console_standard_long_version_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Print only the version number.");

    f_print_dynamic_raw(f_string_eol_s, file.stream);

    fll_program_print_help_option(file, context, iki_write_short_file_s, iki_write_long_file_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Specify a file to send data to.");
    fll_program_print_help_option(file, context, iki_write_short_content_s, iki_write_long_content_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "The Content to write.");
    fll_program_print_help_option(file, context, iki_write_short_double_s, iki_write_long_double_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Use double quotes (default).");
    fll_program_print_help_option(file, context, iki_write_short_object_s, iki_write_long_object_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " The Object to write.");
    fll_program_print_help_option(file, context, iki_write_short_single_s, iki_write_long_single_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Use single quotes.");

    fll_program_print_help_usage(file, context, iki_write_program_name_s, f_string_empty_s);

    fl_print_format(" %[Notes:%]%r", file.stream, context.set.important, context.set.important, f_string_eol_s);
    fl_print_format("  This program will accept Object and Content strings to generate an IKI string, such as %[object:\"content\"%].%r", file.stream, context.set.notable, context.set.notable, f_string_eol_s);

    fl_print_format("  Each object must have a Content (and each Content must have an Object).%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When piping main to this program, a single form-feed character (\\f) must be used to separate each Object from each Content.%r", file.stream, f_string_eol_s);
    fl_print_format("  Furthermore, each Object must be followed by a Content.%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    funlockfile(file.stream);

    return F_none;
  }
#endif // _di_iki_write_print_help_

#ifndef _di_iki_write_main_
  f_status_t iki_write_main(fll_program_data_t * const main, const f_console_arguments_t *arguments) {

    f_status_t status = F_none;

    {
      f_console_parameter_id_t ids[3] = { iki_write_parameter_no_color_e, iki_write_parameter_light_e, iki_write_parameter_dark_e };
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 3);

      status = fll_program_parameter_process(*arguments, &main->parameters, choices, F_true, &main->context);

      main->output.set = &main->context.set;
      main->error.set = &main->context.set;
      main->warning.set = &main->context.set;

      if (main->context.set.error.before) {
        main->output.context = f_color_set_empty_s;
        main->output.notable = main->context.set.notable;

        main->error.context = main->context.set.error;
        main->error.notable = main->context.set.notable;

        main->warning.context = main->context.set.warning;
        main->warning.notable = main->context.set.notable;
      }
      else {
        f_color_set_t *sets[] = { &main->output.context, &main->output.notable, &main->error.context, &main->error.notable, &main->warning.context, &main->warning.notable, 0 };

        fll_program_parameter_process_empty(&main->context, sets);
      }

      if (F_status_is_error(status)) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process", F_true);
          f_print_dynamic_raw(f_string_eol_s, main->error.to.stream);
        }

        return F_status_set_error(status);
      }
    }

    // Identify priority of verbosity related parameters.
    {
      f_console_parameter_id_t ids[5] = { iki_write_parameter_verbosity_quiet_e, iki_write_parameter_verbosity_error_e, iki_write_parameter_verbosity_normal_e, iki_write_parameter_verbosity_verbose_e, iki_write_parameter_verbosity_debug_e };
      f_console_parameter_id_t choice = 0;
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 5);

      status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", F_true);

        return status;
      }

      if (choice == iki_write_parameter_verbosity_quiet_e) {
        main->output.verbosity = f_console_verbosity_quiet_e;
        main->error.verbosity = f_console_verbosity_quiet_e;
        main->warning.verbosity = f_console_verbosity_quiet_e;
      }
      else if (choice == iki_write_parameter_verbosity_error_e) {
        main->output.verbosity = f_console_verbosity_error_e;
        main->error.verbosity = f_console_verbosity_error_e;
        main->warning.verbosity = f_console_verbosity_error_e;
      }
      else if (choice == iki_write_parameter_verbosity_normal_e) {
        main->output.verbosity = f_console_verbosity_normal_e;
        main->error.verbosity = f_console_verbosity_normal_e;
        main->warning.verbosity = f_console_verbosity_normal_e;
      }
      else if (choice == iki_write_parameter_verbosity_verbose_e) {
        main->output.verbosity = f_console_verbosity_verbose_e;
        main->error.verbosity = f_console_verbosity_verbose_e;
        main->warning.verbosity = f_console_verbosity_verbose_e;
      }
      else if (choice == iki_write_parameter_verbosity_debug_e) {
        main->output.verbosity = f_console_verbosity_debug_e;
        main->error.verbosity = f_console_verbosity_debug_e;
        main->warning.verbosity = f_console_verbosity_debug_e;
      }
    }

    iki_write_data_t data = iki_write_data_t_initialize;
    data.main = main;
    data.argv = main->parameters.arguments.array;

    status = F_none;

    if (main->parameters.array[iki_write_parameter_help_e].result == f_console_result_found_e) {
      iki_write_print_help(main->output.to, main->context);

      iki_write_data_delete(&data);

      return F_none;
    }

    if (main->parameters.array[iki_write_parameter_version_e].result == f_console_result_found_e) {
      fll_program_print_version(main->output.to, iki_write_program_version_s);

      iki_write_data_delete(&data);

      return F_none;
    }

    f_file_t file = f_file_t_initialize;

    file.id = F_type_descriptor_output_d;
    file.stream = F_type_output_d;
    file.flag = F_file_flag_create_d | F_file_flag_write_only_d | F_file_flag_append_d;

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[iki_write_parameter_file_e].result == f_console_result_additional_e) {
        if (main->parameters.array[iki_write_parameter_file_e].values.used > 1) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            flockfile(main->error.to.stream);

            fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_write_long_file_s, main->error.notable);
            fl_print_format("%[' may only be specified once.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

            funlockfile(main->error.to.stream);
          }

          status = F_status_set_error(F_parameter);
        }
        else {
          const f_array_length_t index = main->parameters.array[iki_write_parameter_file_e].values.array[0];

          file.id = -1;
          file.stream = 0;

          status = f_file_stream_open(data.argv[index], f_string_empty_s, &file);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_open", F_true, data.argv[index], f_file_operation_open_s, fll_error_file_type_file_e);
          }
        }
      }
      else if (main->parameters.array[iki_write_parameter_file_e].result == f_console_result_found_e) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          flockfile(main->error.to.stream);

          fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_write_long_file_s, main->error.notable);
          fl_print_format("%[' is specified, but no value is given.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          funlockfile(main->error.to.stream);
        }

        status = F_status_set_error(F_parameter);
      }
    }

    if (F_status_is_error_not(status) && main->parameters.array[iki_write_parameter_object_e].result == f_console_result_found_e) {
      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        flockfile(main->error.to.stream);

        fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_write_long_object_s, main->error.notable);
        fl_print_format("%[' is specified, but no value is given.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

        funlockfile(main->error.to.stream);
      }

      status = F_status_set_error(F_parameter);
    }

    if (F_status_is_error_not(status) && main->parameters.array[iki_write_parameter_content_e].result == f_console_result_found_e) {
      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        flockfile(main->error.to.stream);

        fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_write_long_content_s, main->error.notable);
        fl_print_format("%[' is specified, but no value is given.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

        funlockfile(main->error.to.stream);
      }

      status = F_status_set_error(F_parameter);
    }

    if (F_status_is_error_not(status) && !main->process_pipe) {
      if (main->parameters.array[iki_write_parameter_object_e].result != f_console_result_additional_e && main->parameters.array[iki_write_parameter_content_e].result != f_console_result_additional_e) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          flockfile(main->error.to.stream);

          fl_print_format("%r%[%QNo main provided, either pipe the main or use the '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_write_long_object_s, main->error.notable);
          fl_print_format("%[' and the '%]", main->error.to.stream, main->error.context, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_write_long_content_s, main->error.notable);
          fl_print_format("%[' parameters.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          funlockfile(main->error.to.stream);
        }

        status = F_status_set_error(F_parameter);
      }
    }

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[iki_write_parameter_object_e].values.used != main->parameters.array[iki_write_parameter_content_e].values.used) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          flockfile(main->error.to.stream);

          fl_print_format("%r%[%QThe parameters '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_write_long_content_s, main->error.notable);
          fl_print_format("%[' and '%]", main->error.to.stream, main->error.context, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_write_long_object_s, main->error.notable);
          fl_print_format("%[' must be specified the same number of times.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          funlockfile(main->error.to.stream);
        }

        status = F_status_set_error(F_parameter);
      }
    }

    data.quote = f_iki_syntax_quote_double_s;

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[iki_write_parameter_double_e].result == f_console_result_found_e) {
        if (main->parameters.array[iki_write_parameter_single_e].result == f_console_result_found_e) {
          if (main->parameters.array[iki_write_parameter_double_e].location < main->parameters.array[iki_write_parameter_single_e].location) {
            data.quote = f_iki_syntax_quote_single_s;
          }
        }
      }
      else if (main->parameters.array[iki_write_parameter_single_e].result == f_console_result_found_e) {
        data.quote = f_iki_syntax_quote_single_s;
      }
    }

    if (F_status_is_error_not(status)) {
      f_string_dynamic_t escaped = f_string_dynamic_t_initialize;

      if (main->process_pipe) {
        f_file_t pipe = f_file_t_initialize;

        pipe.id = F_type_descriptor_input_d;
        pipe.size_read = 1;

        f_string_dynamic_t buffer = f_string_dynamic_t_initialize;
        f_string_dynamic_t object = f_string_dynamic_t_initialize;
        f_string_dynamic_t content = f_string_dynamic_t_initialize;

        bool object_ended = F_false;

        f_array_length_t previous = 0;
        f_string_range_t range = f_string_range_t_initialize;

        range.start = 0;

        for (f_status_t status_pipe = F_none; ; ) {

          if (!((++main->signal_check) % iki_write_signal_check_d)) {
            if (fll_program_standard_signal_received(main)) {
              status = F_status_set_error(F_interrupt);

              break;
            }

            main->signal_check = 0;
          }

          if (status_pipe != F_none_eof) {
            status_pipe = f_file_read(pipe, &buffer);

            if (F_status_is_error(status_pipe)) {
              fll_error_file_print(main->error, F_status_set_fine(status), "f_file_read_to", F_true, f_string_ascii_minus_s, f_file_operation_read_s, fll_error_file_type_pipe_e);

              status = F_status_set_error(F_pipe);

              break;
            }

            if (!buffer.used) {
              if (main->error.verbosity != f_console_verbosity_quiet_e) {
                fll_print_format("%r%[%QThe pipe has no content.%]%r", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context, f_string_eol_s);
              }

              status = F_status_set_error(F_parameter);

              break;
            }

            range.stop = buffer.used - 1;
          }

          previous = range.start;
          status = f_string_dynamic_seek_to(buffer, f_string_ascii_feed_form_s.string[0], &range);

          if (F_status_is_error(status)) {
            fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_seek_to", F_true);

            break;
          }

          if (status == F_data_not_stop) {
            status = F_status_set_error(F_parameter);

            fll_error_print(main->error, F_parameter, "f_string_dynamic_seek_line", F_true);

            break;
          }

          if (object_ended && previous == range.start) {
            if (main->error.verbosity != f_console_verbosity_quiet_e) {
              fll_print_format("%r%[%QThe pipe has incorrectly placed form-feed characters (\\f).%]%r", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context, f_string_eol_s);
            }

            status = F_status_set_error(F_parameter);

            break;
          }

          range.stop = range.start - 1;
          range.start = previous;

          if (object_ended) {
            content.used = 0;

            if (buffer.used) {
              status = f_string_dynamic_partial_append_nulless(buffer, range, &content);

              if (F_status_is_error(status)) {
                fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);

                break;
              }
            }

            status = iki_write_process(&data, file, object, content, &escaped);
            if (F_status_is_error(status)) break;

            fll_print_dynamic_raw(f_string_eol_s, file.stream);

            object_ended = F_false;
          }
          else {
            object.used = 0;

            status = f_string_dynamic_partial_append_nulless(buffer, range, &object);

            if (F_status_is_error(status)) {
              fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);

              break;
            }

            object_ended = F_true;
          }

          // Restore the range, positioned after the new line.
          range.start = range.stop + 2;
          range.stop = buffer.used - 1;

          // only clear the buffer and reset the start when the entire buffer has been processed.
          if (range.start > range.stop) {
            range.start = 0;
            buffer.used = 0;
          }

          if (status_pipe == F_none_eof && !buffer.used && !object_ended) break;
        } // for

        if (F_status_is_error_not(status) && object_ended) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            fll_print_format("%r%[%QThe pipe has an object without content.%]%r", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context, f_string_eol_s);
          }

          status = F_status_set_error(F_parameter);
        }

        f_string_dynamic_resize(0, &buffer);
        f_string_dynamic_resize(0, &object);
        f_string_dynamic_resize(0, &content);
      }

      if (F_status_is_error_not(status)) {
        for (f_array_length_t i = 0; i < main->parameters.array[iki_write_parameter_object_e].values.used; ++i) {

          if (!((++main->signal_check) % iki_write_signal_check_d)) {
            if (fll_program_standard_signal_received(main)) {
              status = F_status_set_error(F_interrupt);

              break;
            }

            main->signal_check = 0;
          }

          status = iki_write_process(&data, file, data.argv[main->parameters.array[iki_write_parameter_object_e].values.array[i]], data.argv[main->parameters.array[iki_write_parameter_content_e].values.array[i]], &escaped);
          if (F_status_is_error(status)) break;

          fll_print_dynamic_raw(f_string_eol_s, file.stream);
        } // for

        // Ensure there is always a new line at the end, unless in quiet mode.
        if (F_status_is_error_not(status) && main->error.verbosity != f_console_verbosity_quiet_e && main->error.verbosity != f_console_verbosity_error_e && main->parameters.array[iki_write_parameter_file_e].result == f_console_result_none_e) {
          fll_print_dynamic_raw(f_string_eol_s, file.stream);
        }
      }

      f_string_dynamic_resize(0, &escaped);
    }

    if (main->parameters.array[iki_write_parameter_file_e].result == f_console_result_additional_e) {
      f_file_stream_flush(&file);
      f_file_stream_close(&file);
    }

    // Ensure a new line is always put at the end of the program execution, unless in quiet mode.
    if (main->error.verbosity != f_console_verbosity_quiet_e) {
      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_interrupt) {
          fflush(main->output.to.stream);
        }

        fll_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
      }
    }

    iki_write_data_delete(&data);

    return status;
  }
#endif // _di_iki_write_main_

#ifdef __cplusplus
} // extern "C"
#endif
