#include "iki_write.h"
#include "private-iki_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_write_print_help_
  f_return_status iki_write_print_help(const fl_color_context_t context) {
    fll_program_print_help_header(context, iki_write_name_long, iki_write_version);

    fll_program_print_help_option(context, f_console_standard_short_help, f_console_standard_long_help, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Print this help message.");
    fll_program_print_help_option(context, f_console_standard_short_dark, f_console_standard_long_dark, f_console_symbol_short_disable, f_console_symbol_long_disable, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(context, f_console_standard_short_light, f_console_standard_long_light, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(context, f_console_standard_short_no_color, f_console_standard_long_no_color, f_console_symbol_short_disable, f_console_symbol_long_disable, "Do not output in color.");
    fll_program_print_help_option(context, f_console_standard_short_quiet, f_console_standard_long_quiet, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Decrease verbosity beyond normal output.");
    fll_program_print_help_option(context, f_console_standard_short_verbose, f_console_standard_long_verbose, f_console_symbol_short_disable, f_console_symbol_long_disable, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(context, f_console_standard_short_version, f_console_standard_long_version, f_console_symbol_short_disable, f_console_symbol_long_disable, " Print only the version number.");

    printf("%c", f_string_eol[0]);

    fll_program_print_help_option(context, iki_write_short_file, iki_write_long_file, f_console_symbol_short_enable, f_console_symbol_long_enable, "   Specify a file to send output to.");
    fll_program_print_help_option(context, iki_write_short_content, iki_write_long_content, f_console_symbol_short_enable, f_console_symbol_long_enable, "The content to write.");
    fll_program_print_help_option(context, iki_write_short_double, iki_write_long_double, f_console_symbol_short_enable, f_console_symbol_long_enable, " Use double quotes (default).");
    fll_program_print_help_option(context, iki_write_short_object, iki_write_long_object, f_console_symbol_short_enable, f_console_symbol_long_enable, " The object to write.");
    fll_program_print_help_option(context, iki_write_short_single, iki_write_long_single, f_console_symbol_short_enable, f_console_symbol_long_enable, " Use single quotes.");

    fll_program_print_help_usage(context, iki_write_name, "filename(s)");

    fl_color_print(f_type_output, context.important, context.reset, " Notes:");

    printf("%c", f_string_eol[0], f_string_eol[0]);

    printf("  This program will accept object and content strings to generate an IKI string, such as: ");
    fl_color_print(f_type_output, context.notable, context.reset, "object:\"content\"");
    printf(".%c", f_string_eol[0]);

    printf("  Each object must have a content (and each content must have an object).%c", f_string_eol[0]);

    printf("%c", f_string_eol[0]);

    printf("  When piping data to this program, a single end of line (\\n) must be used to separate each object from each content.%c", f_string_eol[0]);
    printf("  Furthermore, each object must be followed by a content.%c", f_string_eol[0]);

    printf("%c", f_string_eol[0]);

    return F_none;
  }
#endif // _di_iki_write_print_help_

#ifndef _di_iki_write_main_
  f_return_status iki_write_main(const f_console_arguments_t arguments, iki_write_data_t *data) {
    f_status_t status = F_none;

    {
      f_console_parameter_id_t ids[3] = { iki_write_parameter_no_color, iki_write_parameter_light, iki_write_parameter_dark };
      const f_console_parameters_t parameters = { data->parameters, iki_write_total_parameters };
      const f_console_parameter_ids_t choices = { ids, 3 };

      status = fll_program_parameter_process(arguments, parameters, choices, F_true, &data->remaining, &data->context);
      if (F_status_is_error(status)) {
        iki_write_print_error(data->context, data->verbosity, F_status_set_fine(status), "fll_program_parameter_process", F_true);

        if (data->verbosity == iki_write_verbosity_verbose) {
          fprintf(f_type_error, "%c", f_string_eol[0]);
        }

        iki_write_delete_data(data);
        return F_status_set_error(status);
      }

      status = F_none;
    }

    if (data->parameters[iki_write_parameter_help].result == f_console_result_found) {
      iki_write_print_help(data->context);

      iki_write_delete_data(data);
      return status;
    }
    else if (data->parameters[iki_write_parameter_version].result == f_console_result_found) {
      fll_program_print_version(iki_write_version);

      iki_write_delete_data(data);
      return status;
    }

    if (data->parameters[iki_write_parameter_verbose].result == f_console_result_found) {
      if (data->parameters[iki_write_parameter_quiet].result == f_console_result_found) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data->context.error, data->context.reset, "ERROR: Cannot specify the '");
        fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, f_console_standard_long_verbose);
        fl_color_print(f_type_error, data->context.error, data->context.reset, "' parameter with the '");
        fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, f_console_standard_long_quiet);
        fl_color_print_line(f_type_error, data->context.error, data->context.reset, "' parameter.");

        status = F_status_set_error(F_parameter);
      }

      data->verbosity = iki_write_verbosity_verbose;
    }
    else if (data->parameters[iki_write_parameter_quiet].result == f_console_result_found) {
      data->verbosity = iki_write_verbosity_quiet;
    }
    else {
      data->verbosity = iki_write_verbosity_normal;
    }

    if (!data->process_pipe) {
      if (data->parameters[iki_write_parameter_object].result != f_console_result_additional && data->parameters[iki_write_parameter_content].result != f_console_result_additional) {
        if (data->verbosity != iki_write_verbosity_quiet) {
          fprintf(f_type_error, "%c", f_string_eol[0]);
          fl_color_print(f_type_error, data->context.error, data->context.reset, "ERROR: No data provided, either pipe the data or use the '");
          fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, iki_write_long_object);
          fl_color_print(f_type_error, data->context.error, data->context.reset, "' and the '");
          fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, iki_write_long_content);
          fl_color_print_line(f_type_error, data->context.error, data->context.reset, "' parameters.");
        }

        status = F_status_set_error(F_parameter);
      }
    }

    if (F_status_is_fine(status)) {
      if (data->parameters[iki_write_parameter_object].additional.used != data->parameters[iki_write_parameter_content].additional.used) {
        if (data->verbosity != iki_write_verbosity_quiet) {
          fl_color_print(f_type_error, data->context.error, data->context.reset, "ERROR: The parameters '");
          fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, iki_write_long_content);
          fl_color_print(f_type_error, data->context.error, data->context.reset, "' and '");
          fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, iki_write_long_object);
          fl_color_print_line(f_type_error, data->context.error, data->context.reset, "' must be specified the same number of times.");
        }

        status = F_status_set_error(F_parameter);
      }
    }

    uint8_t quote = f_iki_syntax_quote_double;

    if (F_status_is_fine(status)) {
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

    if (F_status_is_fine(status)) {
      f_string_dynamic_t escaped = f_string_dynamic_t_initialize;

      if (data->process_pipe) {
        f_file_t file = f_file_t_initialize;

        file.id = f_type_descriptor_input;
        file.size_read = 1;

        f_string_dynamic_t buffer = f_string_dynamic_t_initialize;
        f_string_dynamic_t object = f_string_dynamic_t_initialize;
        f_string_dynamic_t content = f_string_dynamic_t_initialize;

        bool object_ended = F_false;

        f_string_length_t previous = 0;
        f_string_range_t range = f_string_range_t_initialize;

        range.start = 0;

        for (f_status_t status_pipe = F_none; ; ) {

          if (status_pipe != F_none_eof) {
            status_pipe = f_file_read(file, &buffer);

            if (F_status_is_error(status_pipe)) {
              iki_write_print_error_file(data->context, data->verbosity, F_status_set_fine(status_pipe), "f_file_read_to", "-", "read", 2, F_true);

              status = F_status_set_error(F_pipe);
              break;
            }

            if (!buffer.used) {
              if (data->verbosity != iki_write_verbosity_quiet) {
                fl_color_print_line(f_type_error, data->context.error, data->context.reset, "ERROR: The pipe has no content.");
              }

              status = F_status_set_error(F_parameter);
              break;
            }

            range.stop = buffer.used - 1;
          }

          previous = range.start;
          status = fl_string_dynamic_seek_line(buffer.string, &range);

          if (F_status_is_error(status)) {
            iki_write_print_error(data->context, data->verbosity, F_status_set_fine(status), "fl_string_dynamic_seek_line", F_true);
            break;
          }

          if (status == F_data_not_stop) {
            status = F_status_set_error(F_parameter);
            iki_write_print_error(data->context, data->verbosity, F_parameter, "fl_string_dynamic_seek_line", F_true);
            break;
          }

          if (object_ended && previous == range.start) {
            if (data->verbosity != iki_write_verbosity_quiet) {
              fl_color_print_line(f_type_error, data->context.error, data->context.reset, "ERROR: The pipe has incorrectly placed newlines.");
            }

            status = F_status_set_error(F_parameter);
            break;
          }

          range.stop = range.start - 1;
          range.start = previous;

          if (object_ended) {
            content.used = 0;

            if (buffer.used) {
              status = fl_string_dynamic_partial_append_nulless(buffer, range, &content);

              if (F_status_is_error(status)) {
                iki_write_print_error(data->context, data->verbosity, F_status_set_fine(status), "fl_string_dynamic_partial_append_nulless", F_true);
                break;
              }
            }

            status = iki_write_process(*data, object, content, quote, f_type_output, &escaped);
            if (F_status_is_error(status)) break;

            fprintf(f_type_output, "%c", f_string_eol[0]);

            object_ended = F_false;
          }
          else {
            object.used = 0;

            status = fl_string_dynamic_partial_append_nulless(buffer, range, &object);

            if (F_status_is_error(status)) {
              iki_write_print_error(data->context, data->verbosity, F_status_set_fine(status), "fl_string_dynamic_partial_append_nulless", F_true);
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

        if (F_status_is_fine(status) && object_ended) {
          if (data->verbosity != iki_write_verbosity_quiet) {
            fl_color_print_line(f_type_error, data->context.error, data->context.reset, "ERROR: The pipe has an object without content.");
          }

          status = F_status_set_error(F_parameter);
        }

        f_macro_string_dynamic_t_delete_simple(buffer);
        f_macro_string_dynamic_t_delete_simple(object);
        f_macro_string_dynamic_t_delete_simple(content);
      }

      if (F_status_is_fine(status)) {
        f_string_static_t object = f_string_static_t_initialize;
        f_string_static_t content = f_string_static_t_initialize;

        for (f_array_length_t i = 0; i < data->parameters[iki_write_parameter_object].additional.used; i++) {

          object.string = arguments.argv[data->parameters[iki_write_parameter_object].additional.array[i]];
          object.used = strnlen(object.string, f_console_length_size);
          object.size = object.used;

          content.string = arguments.argv[data->parameters[iki_write_parameter_content].additional.array[i]];
          content.used = strnlen(content.string, f_console_length_size);
          content.size = content.used;

          status = iki_write_process(*data, object, content, quote, f_type_output, &escaped);
          if (F_status_is_error(status)) break;

          fprintf(f_type_output, "%c", f_string_eol[0]);
        } // for

        // ensure there is always a newline at the end, unless in quiet mode.
        if (F_status_is_fine(status) && data->verbosity != iki_write_verbosity_quiet) {
          fprintf(f_type_output, "%c", f_string_eol[0]);
        }
      }

      f_macro_string_dynamic_t_delete_simple(escaped);
    }

    // ensure a newline is always put at the end of the program execution, unless in quiet mode.
    if (data->verbosity != iki_write_verbosity_quiet) {
      if (F_status_is_error(status)) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
      }
    }

    iki_write_delete_data(data);
    return status;
  }
#endif // _di_iki_write_main_

#ifndef _di_iki_write_delete_data_
  f_return_status iki_write_delete_data(iki_write_data_t *data) {
    f_status_t status = F_none;
    f_string_length_t i = 0;

    while (i < iki_write_total_parameters) {
      f_macro_string_lengths_t_delete_simple(data->parameters[i].locations);
      f_macro_string_lengths_t_delete_simple(data->parameters[i].additional);
      i++;
    } // while

    f_macro_string_lengths_t_delete_simple(data->remaining);
    f_macro_string_dynamic_t_delete_simple(data->buffer);
    fl_macro_color_context_t_delete_simple(data->context);

    return F_none;
  }
#endif // _di_iki_write_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif
