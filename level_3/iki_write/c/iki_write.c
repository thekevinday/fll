#include "iki_write.h"
#include "private-common.h"
#include "private-write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_write_program_version_
  const f_string_static_t iki_write_program_version_s = macro_f_string_static_t_initialize(IKI_WRITE_program_version_s, 0, IKI_WRITE_program_version_s_length);
#endif // _di_iki_write_program_version_

#ifndef _di_iki_write_program_name_
  const f_string_static_t iki_write_program_name_s = macro_f_string_static_t_initialize(IKI_WRITE_program_name_s, 0, IKI_WRITE_program_name_s_length);
  const f_string_static_t iki_write_program_name_long_s = macro_f_string_static_t_initialize(IKI_WRITE_program_name_long_s, 0, IKI_WRITE_program_name_long_s_length);
#endif // _di_iki_write_program_name_

#ifndef _di_iki_write_print_help_
  f_status_t iki_write_print_help(const f_file_t file, const f_color_context_t context) {

    flockfile(file.stream);

    fll_program_print_help_header(file, context, iki_write_program_name_long_s, iki_write_program_version_s);

    fll_program_print_help_option(file, context, f_console_standard_short_help_s, f_console_standard_long_help_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Print this help message.");
    fll_program_print_help_option(file, context, f_console_standard_short_dark_s, f_console_standard_long_dark_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_light_s, f_console_standard_long_light_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "Do not file in color.");
    fll_program_print_help_option(file, context, f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Decrease verbosity, silencing most output.");
    fll_program_print_help_option(file, context, f_console_standard_short_normal_s, f_console_standard_long_normal_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "  Set verbosity to normal file.");
    fll_program_print_help_option(file, context, f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_debug_s, f_console_standard_long_debug_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Enable debugging, significantly increasing verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_version_s, f_console_standard_long_version_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Print only the version number.");

    f_print_dynamic_raw(f_string_eol_s, file.stream);

    fll_program_print_help_option(file, context, iki_write_short_file_s, iki_write_long_file_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Specify a file to send data to.");
    fll_program_print_help_option(file, context, iki_write_short_content_s, iki_write_long_content_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "The content to file.");
    fll_program_print_help_option(file, context, iki_write_short_double_s, iki_write_long_double_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Use double quotes (default).");
    fll_program_print_help_option(file, context, iki_write_short_object_s, iki_write_long_object_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " The object to file.");
    fll_program_print_help_option(file, context, iki_write_short_single_s, iki_write_long_single_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Use single quotes.");

    fll_program_print_help_usage(file, context, iki_write_program_name_s, f_string_empty_s);

    fl_print_format(" %[Notes:%]%r", file.stream, context.set.important, context.set.important, f_string_eol_s);
    fl_print_format("  This program will accept object and content strings to generate an IKI string, such as %[object:\"content\"%].%r", file.stream, context.set.notable, context.set.notable, f_string_eol_s);

    fl_print_format("  Each object must have a content (and each content must have an object).%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When piping main to this program, a single end of line (\\n) must be used to separate each object from each content.%r", file.stream, f_string_eol_s);
    fl_print_format("  Furthermore, each object must be followed by a content.%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    funlockfile(file.stream);

    return F_none;
  }
#endif // _di_iki_write_print_help_

#ifndef _di_iki_write_main_
  f_status_t iki_write_main(iki_write_main_t * const main, const f_console_arguments_t *arguments) {

    f_status_t status = F_none;

    f_console_parameter_t parameters[] = iki_write_console_parameter_t_initialize;
    main->parameters.array = parameters;
    main->parameters.used = iki_write_total_parameters_d;

    {
      f_console_parameter_id_t ids[3] = { iki_write_parameter_no_color_e, iki_write_parameter_light_e, iki_write_parameter_dark_e };
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 3);

      status = fll_program_parameter_process(*arguments, &main->parameters, choices, F_true, &main->remaining, &main->context);

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

        iki_write_main_delete(main);

        return F_status_set_error(status);
      }
    }

    // Identify priority of verbosity related parameters.
    {
      f_console_parameter_id_t ids[4] = { iki_write_parameter_verbosity_quiet_e, iki_write_parameter_verbosity_normal_e, iki_write_parameter_verbosity_verbose_e, iki_write_parameter_verbosity_debug_e };
      f_console_parameter_id_t choice = 0;
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 4);

      status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

      if (F_status_is_error(status)) {
        iki_write_main_delete(main);

        return status;
      }

      if (choice == iki_write_parameter_verbosity_quiet_e) {
        main->output.verbosity = f_console_verbosity_quiet_e;
        main->error.verbosity = f_console_verbosity_quiet_e;
        main->warning.verbosity = f_console_verbosity_quiet_e;
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

    f_string_static_t * const argv = main->parameters.arguments.array;

    status = F_none;

    if (main->parameters.array[iki_write_parameter_help_e].result == f_console_result_found_e) {
      iki_write_print_help(main->output.to, main->context);

      iki_write_main_delete(main);

      return F_none;
    }

    if (main->parameters.array[iki_write_parameter_version_e].result == f_console_result_found_e) {
      fll_program_print_version(main->output.to, iki_write_program_version_s);

      iki_write_main_delete(main);

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
          const f_array_length_t location = main->parameters.array[iki_write_parameter_file_e].values.array[0];

          file.id = -1;
          file.stream = 0;

          status = f_file_stream_open(arguments->argv[location], 0, &file);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_open", F_true, arguments->argv[location], f_file_operation_open_s, fll_error_file_type_file_e);
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

    data->quote = f_iki_syntax_quote_double_s.string[0];

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[iki_write_parameter_double_e].result == f_console_result_found_e) {
        if (main->parameters.array[iki_write_parameter_single_e].result == f_console_result_found_e) {
          if (main->parameters.array[iki_write_parameter_double_e].location < main->parameters.array[iki_write_parameter_single_e].location) {
            data->quote = f_iki_syntax_quote_single_s.string[0];
          }
        }
      }
      else if (main->parameters.array[iki_write_parameter_single_e].result == f_console_result_found_e) {
        data->quote = f_iki_syntax_quote_single_s.string[0];
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
        uint16_t signal_check = 0;

        range.start = 0;

        for (f_status_t status_pipe = F_none; ; ) {

          if (!((++signal_check) % iki_write_signal_check_d)) {
            if (iki_write_signal_received(main)) {
              status = F_status_set_error(F_interrupt);

              break;
            }

            signal_check = 0;
          }

          if (status_pipe != F_none_eof) {
            status_pipe = f_file_read(pipe, &buffer);

            if (F_status_is_error(status_pipe)) {
              fll_error_file_print(main->error, F_status_set_fine(status), "f_file_read_to", F_true, f_string_ascii_s, f_file_operation_read_s, fll_error_file_type_pipe_e);

              status = F_status_set_error(F_pipe);

              break;
            }

            if (!buffer.used) {
              if (main->error.verbosity != f_console_verbosity_quiet_e) {
                fll_print_format("%r%[%QThe pipe has no main.%]%r", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context, f_string_eol_s);
              }

              status = F_status_set_error(F_parameter);

              break;
            }

            range.stop = buffer.used - 1;
          }

          previous = range.start;
          status = f_string_dynamic_seek_line(buffer, &range);

          if (F_status_is_error(status)) {
            fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_seek_line", F_true);

            break;
          }

          if (status == F_data_not_stop) {
            status = F_status_set_error(F_parameter);

            fll_error_print(main->error, F_parameter, "f_string_dynamic_seek_line", F_true);

            break;
          }

          if (object_ended && previous == range.start) {
            if (main->error.verbosity != f_console_verbosity_quiet_e) {
              fll_print_format("%r%[%QThe pipe has incorrectly placed newlines.%]%r", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context, f_string_eol_s);
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

            status = iki_write_process(main, file, object, content, &escaped);
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

          // restore the range, positioned after the newline.
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
        f_string_static_t object = f_string_static_t_initialize;
        f_string_static_t content = f_string_static_t_initialize;
        uint16_t signal_check = 0;

        for (f_array_length_t i = 0; i < main->parameters.array[iki_write_parameter_object_e].values.used; ++i) {

          if (!((++signal_check) % iki_write_signal_check_d)) {
            if (iki_write_signal_received(main)) {
              status = F_status_set_error(F_interrupt);
              break;
            }

            signal_check = 0;
          }

          object.string = arguments->argv[main->parameters.array[iki_write_parameter_object_e].values.array[i]];
          object.used = strnlen(object.string, F_console_parameter_size_d);
          object.size = object.used;

          content.string = arguments->argv[main->parameters.array[iki_write_parameter_content_e].values.array[i]];
          content.used = strnlen(content.string, F_console_parameter_size_d);
          content.size = content.used;

          status = iki_write_process(main, file, object, content, &escaped);
          if (F_status_is_error(status)) break;

          fll_print_dynamic_raw(f_string_eol_s, file.stream);
        } // for

        // Ensure there is always a newline at the end, unless in quiet mode.
        if (F_status_is_error_not(status) && main->error.verbosity != f_console_verbosity_quiet_e && main->parameters.array[iki_write_parameter_file_e].result == f_console_result_none_e) {
          fll_print_dynamic_raw(f_string_eol_s, file.stream);
        }
      }

      f_string_dynamic_resize(0, &escaped);
    }

    if (main->parameters.array[iki_write_parameter_file_e].result == f_console_result_additional_e) {
      if (file.id != -1) {
        f_file_stream_close(F_true, &file);
      }
    }

    // Ensure a newline is always put at the end of the program execution, unless in quiet mode.
    if (main->error.verbosity != f_console_verbosity_quiet_e) {
      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_interrupt) {
          fflush(main->output.to.stream);
        }

        fll_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
      }
    }

    iki_write_main_delete(main);

    return status;
  }
#endif // _di_iki_write_main_

#ifndef _di_iki_write_main_delete_
  f_status_t iki_write_main_delete(iki_write_main_t * const main) {

    f_console_parameters_delete(&main->parameters);

    f_type_array_lengths_resize(0, &main->remaining);
    f_string_dynamic_resize(0, &main->buffer);

    macro_f_color_context_t_delete_simple(main->context);

    return F_none;
  }
#endif // _di_iki_write_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif
