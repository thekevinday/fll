#include "iki_write.h"
#include "private-iki_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_write_print_help_
  f_status_t iki_write_print_help(const f_file_t output, const f_color_context_t context) {

    fll_program_print_help_header(output, context, iki_write_name_long, iki_write_version);

    fll_program_print_help_option(output, context, f_console_standard_short_help_s, f_console_standard_long_help_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Print this help message.");
    fll_program_print_help_option(output, context, f_console_standard_short_dark_s, f_console_standard_long_dark_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(output, context, f_console_standard_short_light_s, f_console_standard_long_light_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(output, context, f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "Do not output in color.");
    fll_program_print_help_option(output, context, f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Decrease verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_normal_s, f_console_standard_long_normal_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "  Set verbosity to normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_debug_s, f_console_standard_long_debug_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Enable debugging, inceasing verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_version_s, f_console_standard_long_version_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Print only the version number.");

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fll_program_print_help_option(output, context, iki_write_short_file, iki_write_long_file, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Specify a file to send output to.");
    fll_program_print_help_option(output, context, iki_write_short_content, iki_write_long_content, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "The content to output.");
    fll_program_print_help_option(output, context, iki_write_short_double, iki_write_long_double, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Use double quotes (default).");
    fll_program_print_help_option(output, context, iki_write_short_object, iki_write_long_object, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " The object to output.");
    fll_program_print_help_option(output, context, iki_write_short_single, iki_write_long_single, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Use single quotes.");

    fll_program_print_help_usage(output, context, iki_write_name, f_string_empty_s);

    fl_color_print(output.stream, context.set.important, " Notes:");

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  This program will accept object and content strings to generate an IKI string, such as: ");
    fl_color_print(output.stream, context.set.notable, "object:\"content\"");
    fprintf(output.stream, ".%c", f_string_eol_s[0]);

    fprintf(output.stream, "  Each object must have a content (and each content must have an object).%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  When piping data to this program, a single end of line (\\n) must be used to separate each object from each content.%c", f_string_eol_s[0]);
    fprintf(output.stream, "  Furthermore, each object must be followed by a content.%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    return F_none;
  }
#endif // _di_iki_write_print_help_

#ifndef _di_iki_write_main_
  f_status_t iki_write_main(const f_console_arguments_t arguments, iki_write_data_t *data) {
    f_status_t status = F_none;

    {
      const f_console_parameters_t parameters = f_macro_console_parameters_t_initialize(data->parameters, iki_write_total_parameters);

      {
        f_console_parameter_id_t ids[3] = { iki_write_parameter_no_color, iki_write_parameter_light, iki_write_parameter_dark };
        const f_console_parameter_ids_t choices = f_macro_console_parameter_ids_t_initialize(ids, 3);

        status = fll_program_parameter_process(arguments, parameters, choices, F_true, &data->remaining, &data->context);

        if (data->context.set.error.before) {
          data->error.context = data->context.set.error;
          data->error.notable = data->context.set.notable;
        }
        else {
          data->context.set.warning = f_color_set_empty_s;
          data->context.set.error = f_color_set_empty_s;
          data->context.set.title = f_color_set_empty_s;
          data->context.set.notable = f_color_set_empty_s;
          data->context.set.important = f_color_set_empty_s;
          data->context.set.standout = f_color_set_empty_s;
          data->context.set.normal = f_color_set_empty_s;
          data->context.set.normal_reset = f_color_set_empty_s;

          data->error.context = f_color_set_empty_s;
          data->error.notable = f_color_set_empty_s;
        }

        if (F_status_is_error(status)) {
          if (data->error.verbosity != f_console_verbosity_quiet) {
            fll_error_print(data->error, F_status_set_fine(status), "fll_program_parameter_process", F_true);
            fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
          }

          iki_write_delete_data(data);
          return F_status_set_error(status);
        }
      }

      // Identify priority of verbosity related parameters.
      {
        f_console_parameter_id_t ids[4] = { iki_write_parameter_verbosity_quiet, iki_write_parameter_verbosity_normal, iki_write_parameter_verbosity_verbose, iki_write_parameter_verbosity_debug };
        f_console_parameter_id_t choice = 0;
        const f_console_parameter_ids_t choices = f_macro_console_parameter_ids_t_initialize(ids, 4);

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          iki_write_delete_data(data);
          return status;
        }

        if (choice == iki_write_parameter_verbosity_quiet) {
          data->error.verbosity = f_console_verbosity_quiet;
        }
        else if (choice == iki_write_parameter_verbosity_normal) {
          data->error.verbosity = f_console_verbosity_normal;
        }
        else if (choice == iki_write_parameter_verbosity_verbose) {
          data->error.verbosity = f_console_verbosity_verbose;
        }
        else if (choice == iki_write_parameter_verbosity_debug) {
          data->error.verbosity = f_console_verbosity_debug;
        }
      }

      status = F_none;
    }

    if (data->parameters[iki_write_parameter_help].result == f_console_result_found) {
      iki_write_print_help(data->output, data->context);

      iki_write_delete_data(data);
      return F_none;
    }

    if (data->parameters[iki_write_parameter_version].result == f_console_result_found) {
      fll_program_print_version(data->output, iki_write_version);

      iki_write_delete_data(data);
      return F_none;
    }

    f_file_t output = f_file_t_initialize;

    output.id = f_type_descriptor_output;
    output.stream = f_type_output;
    output.flag = f_file_flag_create | f_file_flag_write_only | f_file_flag_append;

    if (F_status_is_error_not(status)) {
      if (data->parameters[iki_write_parameter_file].result == f_console_result_additional) {
        if (data->parameters[iki_write_parameter_file].values.used > 1) {
          if (data->error.verbosity != f_console_verbosity_quiet) {
            fl_color_print(data->error.to.stream, data->context.set.error, "%sThe parameter '", fll_error_print_error);
            fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable_s, iki_write_long_file);
            fl_color_print(data->error.to.stream, data->context.set.error, "' may only be specified once.%c", f_string_eol_s[0]);
          }

          status = F_status_set_error(F_parameter);
        }
        else {
          const f_string_length_t location = data->parameters[iki_write_parameter_file].values.array[0];

          output.id = -1;
          output.stream = 0;

          status = f_file_stream_open(arguments.argv[location], 0, &output);

          if (F_status_is_error(status)) {
            fll_error_file_print(data->error, F_status_set_fine(status), "f_file_stream_open", F_true, arguments.argv[location], "open", fll_error_file_type_file);
          }
        }
      }
      else if (data->parameters[iki_write_parameter_file].result == f_console_result_found) {
        if (data->error.verbosity != f_console_verbosity_quiet) {
          fl_color_print(data->error.to.stream, data->context.set.error, "%sThe parameter '", fll_error_print_error);
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable_s, iki_write_long_file);
          fl_color_print(data->error.to.stream, data->context.set.error, "' was specified, but no value was given.%c", f_string_eol_s[0]);
        }

        status = F_status_set_error(F_parameter);
      }
    }

    if (F_status_is_error_not(status) && data->parameters[iki_write_parameter_object].result == f_console_result_found) {
      if (data->error.verbosity != f_console_verbosity_quiet) {
        fl_color_print(data->error.to.stream, data->context.set.error, "%sThe parameter '", fll_error_print_error);
        fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable_s, iki_write_long_object);
        fl_color_print(data->error.to.stream, data->context.set.error, "' was specified, but no value was given.%c", f_string_eol_s[0]);
      }

      status = F_status_set_error(F_parameter);
    }

    if (F_status_is_error_not(status) && data->parameters[iki_write_parameter_content].result == f_console_result_found) {
      if (data->error.verbosity != f_console_verbosity_quiet) {
        fl_color_print(data->error.to.stream, data->context.set.error, "%sThe parameter '", fll_error_print_error);
        fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable_s, iki_write_long_content);
        fl_color_print(data->error.to.stream, data->context.set.error, "' was specified, but no value was given.%c", f_string_eol_s[0]);
      }

      status = F_status_set_error(F_parameter);
    }

    if (F_status_is_error_not(status) && !data->process_pipe) {
      if (data->parameters[iki_write_parameter_object].result != f_console_result_additional && data->parameters[iki_write_parameter_content].result != f_console_result_additional) {
        if (data->error.verbosity != f_console_verbosity_quiet) {
          fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
          fl_color_print(data->error.to.stream, data->context.set.error, "%sNo data provided, either pipe the data or use the '", fll_error_print_error);
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable_s, iki_write_long_object);
          fl_color_print(data->error.to.stream, data->context.set.error, "' and the '");
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable_s, iki_write_long_content);
          fl_color_print(data->error.to.stream, data->context.set.error, "' parameters.%c", f_string_eol_s[0]);
        }

        status = F_status_set_error(F_parameter);
      }
    }

    if (F_status_is_error_not(status)) {
      if (data->parameters[iki_write_parameter_object].values.used != data->parameters[iki_write_parameter_content].values.used) {
        if (data->error.verbosity != f_console_verbosity_quiet) {
          fl_color_print(data->error.to.stream, data->context.set.error, "%sThe parameters '", fll_error_print_error);
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable_s, iki_write_long_content);
          fl_color_print(data->error.to.stream, data->context.set.error, "' and '");
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable_s, iki_write_long_object);
          fl_color_print(data->error.to.stream, data->context.set.error, "' must be specified the same number of times.%c", f_string_eol_s[0]);
        }

        status = F_status_set_error(F_parameter);
      }
    }

    uint8_t quote = f_iki_syntax_quote_double;

    if (F_status_is_error_not(status)) {
      if (data->parameters[iki_write_parameter_double].result == f_console_result_found) {
        if (data->parameters[iki_write_parameter_single].result == f_console_result_found) {
          if (data->parameters[iki_write_parameter_double].location < data->parameters[iki_write_parameter_single].location) {
            quote = f_iki_syntax_quote_single;
          }
        }
      }
      else if (data->parameters[iki_write_parameter_single].result == f_console_result_found) {
        quote = f_iki_syntax_quote_single;
      }
    }

    if (F_status_is_error_not(status)) {
      f_string_dynamic_t escaped = f_string_dynamic_t_initialize;

      if (data->process_pipe) {
        f_file_t pipe = f_file_t_initialize;

        pipe.id = f_type_descriptor_input;
        pipe.size_read = 1;

        f_string_dynamic_t buffer = f_string_dynamic_t_initialize;
        f_string_dynamic_t object = f_string_dynamic_t_initialize;
        f_string_dynamic_t content = f_string_dynamic_t_initialize;

        bool object_ended = F_false;

        f_string_length_t previous = 0;
        f_string_range_t range = f_string_range_t_initialize;

        range.start = 0;

        for (f_status_t status_pipe = F_none; ; ) {

          if (status_pipe != F_none_eof) {
            status_pipe = f_file_read(pipe, &buffer);

            if (F_status_is_error(status_pipe)) {
              fll_error_file_print(data->error, F_status_set_fine(status), "f_file_read_to", F_true, "-", "read", fll_error_file_type_pipe);

              status = F_status_set_error(F_pipe);
              break;
            }

            if (!buffer.used) {
              if (data->error.verbosity != f_console_verbosity_quiet) {
                fl_color_print(data->error.to.stream, data->context.set.error, "%sThe pipe has no data.%c", fll_error_print_error, f_string_eol_s[0]);
              }

              status = F_status_set_error(F_parameter);
              break;
            }

            range.stop = buffer.used - 1;
          }

          previous = range.start;
          status = fl_string_dynamic_seek_line(buffer.string, &range);

          if (F_status_is_error(status)) {
            fll_error_print(data->error, F_status_set_fine(status), "fl_string_dynamic_seek_line", F_true);
            break;
          }

          if (status == F_data_not_stop) {
            status = F_status_set_error(F_parameter);

            fll_error_print(data->error, F_parameter, "fl_string_dynamic_seek_line", F_true);
            break;
          }

          if (object_ended && previous == range.start) {
            if (data->error.verbosity != f_console_verbosity_quiet) {
              fl_color_print(data->error.to.stream, data->context.set.error, "%sThe pipe has incorrectly placed newlines.%c", fll_error_print_error, f_string_eol_s[0]);
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
                fll_error_print(data->error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);
                break;
              }
            }

            status = iki_write_process(*data, output, object, content, quote, &escaped);
            if (F_status_is_error(status)) break;

            fprintf(output.stream, "%c", f_string_eol_s[0]);

            object_ended = F_false;
          }
          else {
            object.used = 0;

            status = f_string_dynamic_partial_append_nulless(buffer, range, &object);

            if (F_status_is_error(status)) {
              fll_error_print(data->error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);
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
          if (data->error.verbosity != f_console_verbosity_quiet) {
            fl_color_print(data->error.to.stream, data->context.set.error, "%sThe pipe has an object without content.%c", fll_error_print_error, f_string_eol_s[0]);
          }

          status = F_status_set_error(F_parameter);
        }

        f_macro_string_dynamic_t_delete_simple(buffer);
        f_macro_string_dynamic_t_delete_simple(object);
        f_macro_string_dynamic_t_delete_simple(content);
      }

      if (F_status_is_error_not(status)) {
        f_string_static_t object = f_string_static_t_initialize;
        f_string_static_t content = f_string_static_t_initialize;

        for (f_array_length_t i = 0; i < data->parameters[iki_write_parameter_object].values.used; i++) {

          object.string = arguments.argv[data->parameters[iki_write_parameter_object].values.array[i]];
          object.used = strnlen(object.string, f_console_length_size);
          object.size = object.used;

          content.string = arguments.argv[data->parameters[iki_write_parameter_content].values.array[i]];
          content.used = strnlen(content.string, f_console_length_size);
          content.size = content.used;

          status = iki_write_process(*data, output, object, content, quote, &escaped);
          if (F_status_is_error(status)) break;

          fprintf(output.stream, "%c", f_string_eol_s[0]);
        } // for

        // ensure there is always a newline at the end, unless in quiet mode.
        if (F_status_is_error_not(status) && data->error.verbosity != f_console_verbosity_quiet && data->parameters[iki_write_parameter_file].result == f_console_result_none) {
          fprintf(data->output.stream, "%c", f_string_eol_s[0]);
        }
      }

      f_macro_string_dynamic_t_delete_simple(escaped);
    }

    if (data->parameters[iki_write_parameter_file].result == f_console_result_additional) {
      if (output.id != -1) {
        f_file_stream_close(F_true, &output);
      }
    }

    // ensure a newline is always put at the end of the program execution, unless in quiet mode.
    if (data->error.verbosity != f_console_verbosity_quiet) {
      if (F_status_is_error(status)) {
        fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
      }
    }

    iki_write_delete_data(data);
    return status;
  }
#endif // _di_iki_write_main_

#ifndef _di_iki_write_delete_data_
  f_status_t iki_write_delete_data(iki_write_data_t *data) {

    for (f_string_length_t i = 0; i < iki_write_total_parameters; i++) {
      f_macro_string_lengths_t_delete_simple(data->parameters[i].locations);
      f_macro_string_lengths_t_delete_simple(data->parameters[i].locations_sub);
      f_macro_string_lengths_t_delete_simple(data->parameters[i].values);
    } // for

    f_macro_string_lengths_t_delete_simple(data->remaining);
    f_macro_string_dynamic_t_delete_simple(data->buffer);

    f_macro_color_context_t_delete_simple(data->context);

    return F_none;
  }
#endif // _di_iki_write_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif
