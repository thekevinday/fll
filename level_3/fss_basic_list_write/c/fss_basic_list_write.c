#include "fss_basic_list_write.h"
#include "private-fss_basic_list_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_basic_list_write_print_help_
  f_return_status fss_basic_list_write_print_help(const f_file_t file, const f_color_context_t context) {

    fll_program_print_help_header(file, context, fss_basic_list_write_name_long, fss_basic_list_write_version);

    fll_program_print_help_option(file, context, f_console_standard_short_help, f_console_standard_long_help, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Print this help message.");
    fll_program_print_help_option(file, context, f_console_standard_short_dark, f_console_standard_long_dark, f_console_symbol_short_disable, f_console_symbol_long_disable, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_light, f_console_standard_long_light, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_no_color, f_console_standard_long_no_color, f_console_symbol_short_disable, f_console_symbol_long_disable, "Do not output in color.");
    fll_program_print_help_option(file, context, f_console_standard_short_quiet, f_console_standard_long_quiet, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Decrease verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_normal, f_console_standard_long_normal, f_console_symbol_short_disable, f_console_symbol_long_disable, "  Set verbosity to normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_verbose, f_console_standard_long_verbose, f_console_symbol_short_disable, f_console_symbol_long_disable, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_debug, f_console_standard_long_debug, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Enable debugging, inceasing verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_version, f_console_standard_long_version, f_console_symbol_short_disable, f_console_symbol_long_disable, " Print only the version number.");

    printf("%c", f_string_eol[0]);

    fll_program_print_help_option(file, context, fss_basic_list_write_short_file, fss_basic_list_write_long_file, f_console_symbol_short_enable, f_console_symbol_long_enable, "   Specify a file to send output to.");
    fll_program_print_help_option(file, context, fss_basic_list_write_short_content, fss_basic_list_write_long_content, f_console_symbol_short_enable, f_console_symbol_long_enable, " The content to output.");
    fll_program_print_help_option(file, context, fss_basic_list_write_short_double, fss_basic_list_write_long_double, f_console_symbol_short_enable, f_console_symbol_long_enable, " Use double quotes (default).");
    fll_program_print_help_option(file, context, fss_basic_list_write_short_object, fss_basic_list_write_long_object, f_console_symbol_short_enable, f_console_symbol_long_enable, " The object to output.");
    fll_program_print_help_option(file, context, fss_basic_list_write_short_partial, fss_basic_list_write_long_partial, f_console_symbol_short_enable, f_console_symbol_long_enable, "Do not output end of object/content character.");
    fll_program_print_help_option(file, context, fss_basic_list_write_short_single, fss_basic_list_write_long_single, f_console_symbol_short_enable, f_console_symbol_long_enable, " Use single quotes.");

    fll_program_print_help_usage(file, context, fss_basic_list_write_name, "");

    return F_none;
  }
#endif // _di_fss_basic_list_write_print_help_

#ifndef _di_fss_basic_list_write_main_
  f_return_status fss_basic_list_write_main(const f_console_arguments_t arguments, fss_basic_list_write_data_t *data) {
    f_status_t status = F_none;

    {
      const f_console_parameters_t parameters = f_macro_console_parameters_t_initialize(data->parameters, fss_basic_list_write_total_parameters);

      {
        f_console_parameter_id_t ids[3] = { fss_basic_list_write_parameter_no_color, fss_basic_list_write_parameter_light, fss_basic_list_write_parameter_dark };
        const f_console_parameter_ids_t choices = f_macro_console_parameter_ids_t_initialize(ids, 3);

        status = fll_program_parameter_process(arguments, parameters, choices, F_true, &data->remaining, &data->context);

        data->error.context = data->context.set.error;
        data->error.notable = data->context.set.notable;

        if (F_status_is_error(status)) {
          fss_basic_list_write_delete_data(data);
          return F_status_set_error(status);
        }
      }

      // Identify priority of verbosity related parameters.
      {
        f_console_parameter_id_t ids[4] = { fss_basic_list_write_parameter_verbosity_quiet, fss_basic_list_write_parameter_verbosity_normal, fss_basic_list_write_parameter_verbosity_verbose, fss_basic_list_write_parameter_verbosity_debug };
        f_console_parameter_id_t choice = 0;
        const f_console_parameter_ids_t choices = f_macro_console_parameter_ids_t_initialize(ids, 4);

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          fss_basic_list_write_delete_data(data);
          return status;
        }

        if (choice == fss_basic_list_write_parameter_verbosity_quiet) {
          data->error.verbosity = f_console_verbosity_quiet;
        }
        else if (choice == fss_basic_list_write_parameter_verbosity_normal) {
          data->error.verbosity = f_console_verbosity_normal;
        }
        else if (choice == fss_basic_list_write_parameter_verbosity_verbose) {
          data->error.verbosity = f_console_verbosity_verbose;
        }
        else if (choice == fss_basic_list_write_parameter_verbosity_debug) {
          data->error.verbosity = f_console_verbosity_debug;
        }
      }

      status = F_none;
    }

    if (data->parameters[fss_basic_list_write_parameter_help].result == f_console_result_found) {
      fss_basic_list_write_print_help(data->output, data->context);

      fss_basic_list_write_delete_data(data);
      return status;
    }

    if (data->parameters[fss_basic_list_write_parameter_version].result == f_console_result_found) {
      fll_program_print_version(data->output, fss_basic_list_write_version);

      fss_basic_list_write_delete_data(data);
      return status;
    }

    f_file_t output = f_file_t_initialize;

    output.id = f_type_descriptor_output;
    output.stream = f_type_output;
    output.flag = f_file_flag_create | f_file_flag_write_only | f_file_flag_append;

    if (F_status_is_error_not(status)) {
      if (data->parameters[fss_basic_list_write_parameter_file].result == f_console_result_additional) {
        if (data->parameters[fss_basic_list_write_parameter_file].additional.used > 1) {
          if (data->error.verbosity != f_console_verbosity_quiet) {
            fl_color_print(data->error.to.stream, data->context.set.error, "%sThe parameter '", fll_error_print_error);
            fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_list_write_long_file);
            fl_color_print(data->error.to.stream, data->context.set.error, "' may only be specified once.%c", f_string_eol[0]);
          }

          status = F_status_set_error(F_parameter);
        }
        else {
          const f_string_length_t location = data->parameters[fss_basic_list_write_parameter_file].additional.array[0];

          output.id = -1;
          output.stream = 0;
          status = f_file_stream_open(arguments.argv[location], 0, &output);

          if (F_status_is_error(status)) {
            fll_error_file_print(data->error, F_status_set_fine(status), "f_file_stream_open", F_true, arguments.argv[location], "open", fll_error_file_type_file);
          }
        }
      }
      else if (data->parameters[fss_basic_list_write_parameter_file].result == f_console_result_found) {
        fss_basic_list_write_error_parameter_value_missing_print(*data, f_console_symbol_long_enable, fss_basic_list_write_long_file);
        status = F_status_set_error(F_parameter);
      }
    }

    if (F_status_is_error_not(status)) {
      if (data->parameters[fss_basic_list_write_parameter_object].locations.used || data->parameters[fss_basic_list_write_parameter_content].locations.used) {
        if (data->parameters[fss_basic_list_write_parameter_object].locations.used) {
          if (data->parameters[fss_basic_list_write_parameter_object].locations.used != data->parameters[fss_basic_list_write_parameter_object].additional.used) {
            fss_basic_list_write_error_parameter_value_missing_print(*data, f_console_symbol_long_enable, fss_basic_list_write_long_object);
            status = F_status_set_error(F_parameter);
          }
          else if (data->parameters[fss_basic_list_write_parameter_content].locations.used != data->parameters[fss_basic_list_write_parameter_content].additional.used) {
            fss_basic_list_write_error_parameter_value_missing_print(*data, f_console_symbol_long_enable, fss_basic_list_write_long_content);
            status = F_status_set_error(F_parameter);
          }
          else if (data->parameters[fss_basic_list_write_parameter_object].locations.used != data->parameters[fss_basic_list_write_parameter_content].locations.used) {
            fss_basic_list_write_error_parameter_same_times_print(*data);
            status = F_status_set_error(F_parameter);
          }
          else if (data->parameters[fss_basic_list_write_parameter_content].locations.used && data->parameters[fss_basic_list_write_parameter_partial].locations.used) {
            if (data->parameters[fss_basic_list_write_parameter_content].result == f_console_result_additional) {
              if (data->error.verbosity != f_console_verbosity_quiet) {
                fl_color_print(data->error.to.stream, data->context.set.error, "%sThe '", fll_error_print_error);
                fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_list_write_long_partial);
                fl_color_print(data->error.to.stream, data->context.set.error, "' parameter only allows either the '");
                fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_list_write_long_object);
                fl_color_print(data->error.to.stream, data->context.set.error, "' parameter or the '");
                fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_list_write_long_content);
                fl_color_print(data->error.to.stream, data->context.set.error, "' parameter, but not both.%c", f_string_eol[0]);
              }

              status = F_status_set_error(F_parameter);
            }
          }
        }
        else if (data->parameters[fss_basic_list_write_parameter_content].locations.used) {
          if (data->parameters[fss_basic_list_write_parameter_content].locations.used != data->parameters[fss_basic_list_write_parameter_content].additional.used) {
            fss_basic_list_write_error_parameter_value_missing_print(*data, f_console_symbol_long_enable, fss_basic_list_write_long_content);
            status = F_status_set_error(F_parameter);
          }
          else if (!data->parameters[fss_basic_list_write_parameter_partial].locations.used) {
            fss_basic_list_write_error_parameter_same_times_print(*data);
            status = F_status_set_error(F_parameter);
          }
        }
      }
      else if (!data->process_pipe) {
        if (data->error.verbosity != f_console_verbosity_quiet) {
          fl_color_print(data->error.to.stream, data->context.set.error, "%sThis requires either piped data or the use of the '", fll_error_print_error);
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_list_write_long_object);
          fl_color_print(data->error.to.stream, data->context.set.error, "' parameter with the '");
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_list_write_long_content);
          fl_color_print(data->error.to.stream, data->context.set.error, "' parameter.%c", f_string_eol[0]);
        }

        status = F_status_set_error(F_parameter);
      }
    }

    f_fss_quote_t quoted = f_fss_delimit_quote_double;

    if (F_status_is_error_not(status)) {
      if (data->parameters[fss_basic_list_write_parameter_double].result == f_console_result_found) {
        if (data->parameters[fss_basic_list_write_parameter_single].result == f_console_result_found) {
          if (data->parameters[fss_basic_list_write_parameter_double].location < data->parameters[fss_basic_list_write_parameter_single].location) {
            quoted = f_fss_delimit_quote_single;
          }
        }
      }
      else if (data->parameters[fss_basic_list_write_parameter_single].result == f_console_result_found) {
        quoted = f_fss_delimit_quote_single;
      }
    }

    f_string_dynamic_t buffer = f_string_dynamic_t_initialize;
    f_string_dynamic_t object = f_string_dynamic_t_initialize;
    f_string_dynamic_t content = f_string_dynamic_t_initialize;

    if (F_status_is_error_not(status)) {
      f_string_dynamic_t escaped = f_string_dynamic_t_initialize;

      if (data->process_pipe) {
        f_file_t input = f_file_t_initialize;

        input.id = f_type_descriptor_input;
        input.size_read = 1;

        bool object_ended = F_false;

        f_string_length_t previous = 0;
        f_string_range_t range = f_string_range_t_initialize;

        range.start = 0;

        if (data->parameters[fss_basic_list_write_parameter_partial].result == f_console_result_found) {
          for (f_status_t status_pipe = F_none; ; ) {

            if (status_pipe != F_none_eof) {
              status_pipe = f_file_read(input, &buffer);

              if (F_status_is_error(status_pipe)) {
                fll_error_file_print(data->error, F_status_set_fine(status), "f_file_read_to", F_true, "-", "read", fll_error_file_type_pipe);

                status = F_status_set_error(F_pipe);
                break;
              }

              if (!buffer.used) {
                if (data->error.verbosity != f_console_verbosity_quiet) {
                  fl_color_print(data->error.to.stream, data->context.set.error, "%sThe pipe has no data.%c", fll_error_print_error, f_string_eol[0]);
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

            range.stop = range.start - 1;
            range.start = previous;

            if (data->parameters[fss_basic_list_write_parameter_object].result == f_console_result_found) {
              object.used = 0;

              if (buffer.used) {
                status = fl_string_dynamic_partial_append_nulless(buffer, range, &object);

                if (F_status_is_error(status)) {
                  fll_error_print(data->error, F_status_set_fine(status), "fl_string_dynamic_partial_append_nulless", F_true);
                  break;
                }
              }
            }
            else {
              content.used = 0;

              if (buffer.used) {
                status = fl_string_dynamic_partial_append_nulless(buffer, range, &object);

                if (F_status_is_error(status)) {
                  fll_error_print(data->error, F_status_set_fine(status), "fl_string_dynamic_partial_append_nulless", F_true);
                  break;
                }
              }
            }

            status = fss_basic_list_write_process(*data, output, object, content, quoted, &buffer);
            if (F_status_is_error(status)) break;

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
        }
        else {
          for (f_status_t status_pipe = F_none; ; ) {

            if (status_pipe != F_none_eof) {
              status_pipe = f_file_read(input, &buffer);

              if (F_status_is_error(status_pipe)) {
                fll_error_file_print(data->error, F_status_set_fine(status), "f_file_read_to", F_true, "-", "read", fll_error_file_type_pipe);

                status = F_status_set_error(F_pipe);
                break;
              }

              if (!buffer.used) {
                if (data->error.verbosity != f_console_verbosity_quiet) {
                  fl_color_print(data->error.to.stream, data->context.set.error, "%sThe pipe has no data.%c", fll_error_print_error, f_string_eol[0]);
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
                fl_color_print(data->error.to.stream, data->context.set.error, "%sThe pipe has incorrectly placed newlines.%c", fll_error_print_error, f_string_eol[0]);
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
                  fll_error_print(data->error, F_status_set_fine(status), "fl_string_dynamic_partial_append_nulless", F_true);
                  break;
                }
              }

              status = fss_basic_list_write_process(*data, output, object, content, quoted, &buffer);
              if (F_status_is_error(status)) break;

              object_ended = F_false;
            }
            else {
              object.used = 0;

              status = fl_string_dynamic_partial_append_nulless(buffer, range, &object);

              if (F_status_is_error(status)) {
                fll_error_print(data->error, F_status_set_fine(status), "fl_string_dynamic_partial_append_nulless", F_true);
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
              fl_color_print(data->error.to.stream, data->context.set.error, "%sThe pipe has an object without content.%c", fll_error_print_error, f_string_eol[0]);
            }

            status = F_status_set_error(F_parameter);
          }
        }
      }

      if (F_status_is_error_not(status)) {
        if (data->parameters[fss_basic_list_write_parameter_partial].result == f_console_result_found) {
          if (data->parameters[fss_basic_list_write_parameter_object].result == f_console_result_found) {
            content.used = 0;

            for (f_array_length_t i = 0; i < data->parameters[fss_basic_list_write_parameter_object].additional.used; i++) {

              object.string = arguments.argv[data->parameters[fss_basic_list_write_parameter_object].additional.array[i]];
              object.used = strnlen(object.string, f_console_length_size);
              object.size = object.used;

              status = fss_basic_list_write_process(*data, output, object, content, quoted, &buffer);
              if (F_status_is_error(status)) break;
            } // for
          }
          else {
            object.used = 0;

            for (f_array_length_t i = 0; i < data->parameters[fss_basic_list_write_parameter_object].additional.used; i++) {

              content.string = arguments.argv[data->parameters[fss_basic_list_write_parameter_content].additional.array[i]];
              content.used = strnlen(content.string, f_console_length_size);
              content.size = content.used;

              status = fss_basic_list_write_process(*data, output, object, content, quoted, &buffer);
              if (F_status_is_error(status)) break;
            } // for
          }
        }
        else {
          for (f_array_length_t i = 0; i < data->parameters[fss_basic_list_write_parameter_object].additional.used; i++) {

            object.string = arguments.argv[data->parameters[fss_basic_list_write_parameter_object].additional.array[i]];
            object.used = strnlen(object.string, f_console_length_size);
            object.size = object.used;

            content.string = arguments.argv[data->parameters[fss_basic_list_write_parameter_content].additional.array[i]];
            content.used = strnlen(content.string, f_console_length_size);
            content.size = content.used;

            status = fss_basic_list_write_process(*data, output, object, content, quoted, &buffer);
            if (F_status_is_error(status)) break;
          } // for
        }

        // ensure there is always a newline at the end, unless in quiet mode.
        if (F_status_is_error_not(status) && data->error.verbosity != f_console_verbosity_quiet && data->parameters[fss_basic_list_write_parameter_file].result == f_console_result_none) {
          fprintf(f_type_output, "%c", f_string_eol[0]);
        }
      }

      f_macro_string_dynamic_t_delete_simple(escaped);

      // object and content, though being a "dynamic" type, is being used statically, so clear them up to avoid invalid free().
      object.string = 0;
      object.used = 0;
      object.size = 0;

      content.string = 0;
      content.used = 0;
      content.size = 0;
    }

    if (data->parameters[fss_basic_list_write_parameter_file].result == f_console_result_additional) {
      if (output.id != -1) {
        f_file_stream_close(F_true, &output);
      }
    }

    // ensure a newline is always put at the end of the program execution, unless in quiet mode.
    if (data->error.verbosity != f_console_verbosity_quiet) {
      if (F_status_is_error(status)) {
        fprintf(data->error.to.stream, "%c", f_string_eol[0]);
      }
    }

    f_macro_string_dynamic_t_delete_simple(buffer);
    f_macro_string_dynamic_t_delete_simple(object);
    f_macro_string_dynamic_t_delete_simple(content);
    fss_basic_list_write_delete_data(data);
    return status;
  }
#endif // _di_fss_basic_list_write_main_

#ifndef _di_fss_basic_list_write_delete_data_
  f_return_status fss_basic_list_write_delete_data(fss_basic_list_write_data_t *data) {
    f_string_length_t i = 0;

    while (i < fss_basic_list_write_total_parameters) {
      f_macro_string_lengths_t_delete_simple(data->parameters[i].locations);
      f_macro_string_lengths_t_delete_simple(data->parameters[i].additional);
      i++;
    } // while

    f_macro_string_lengths_t_delete_simple(data->remaining);
    f_macro_color_context_t_delete_simple(data->context);

    return F_none;
  }
#endif // _di_fss_basic_list_write_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif
