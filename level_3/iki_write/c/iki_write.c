#include "iki_write.h"
#include "private-common.h"
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

    f_color_print(output.stream, context.set.important, " Notes:");

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  This program will accept object and content strings to generate an IKI string, such as: ");
    f_color_print(output.stream, context.set.notable, "object:\"content\"");
    fprintf(output.stream, ".%c", f_string_eol_s[0]);

    fprintf(output.stream, "  Each object must have a content (and each content must have an object).%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  When piping main to this program, a single end of line (\\n) must be used to separate each object from each content.%c", f_string_eol_s[0]);
    fprintf(output.stream, "  Furthermore, each object must be followed by a content.%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    return F_none;
  }
#endif // _di_iki_write_print_help_

#ifndef _di_iki_write_main_
  f_status_t iki_write_main(const f_console_arguments_t arguments, iki_write_main_t *main) {

    f_status_t status = F_none;

    {
      const f_console_parameters_t parameters = macro_f_console_parameters_t_initialize(main->parameters, iki_write_total_parameters);

      {
        f_console_parameter_id_t ids[3] = { iki_write_parameter_no_color, iki_write_parameter_light, iki_write_parameter_dark };
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 3);

        status = fll_program_parameter_process(arguments, parameters, choices, F_true, &main->remaining, &main->context);

        if (main->context.set.error.before) {
          main->error.context = main->context.set.error;
          main->error.notable = main->context.set.notable;
        }
        else {
          f_color_set_t *sets[] = { &main->error.context, &main->error.notable, 0 };

          fll_program_parameter_process_empty(&main->context, sets);
        }

        if (F_status_is_error(status)) {
          if (main->error.verbosity != f_console_verbosity_quiet) {
            fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process", F_true);
            fprintf(main->error.to.stream, "%c", f_string_eol_s[0]);
          }

          iki_write_main_delete(main);
          return F_status_set_error(status);
        }
      }

      // Identify priority of verbosity related parameters.
      {
        f_console_parameter_id_t ids[4] = { iki_write_parameter_verbosity_quiet, iki_write_parameter_verbosity_normal, iki_write_parameter_verbosity_verbose, iki_write_parameter_verbosity_debug };
        f_console_parameter_id_t choice = 0;
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 4);

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          iki_write_main_delete(main);

          return status;
        }

        if (choice == iki_write_parameter_verbosity_quiet) {
          main->error.verbosity = f_console_verbosity_quiet;
        }
        else if (choice == iki_write_parameter_verbosity_normal) {
          main->error.verbosity = f_console_verbosity_normal;
        }
        else if (choice == iki_write_parameter_verbosity_verbose) {
          main->error.verbosity = f_console_verbosity_verbose;
        }
        else if (choice == iki_write_parameter_verbosity_debug) {
          main->error.verbosity = f_console_verbosity_debug;
        }
      }

      status = F_none;
    }

    if (main->parameters[iki_write_parameter_help].result == f_console_result_found) {
      iki_write_print_help(main->output, main->context);

      iki_write_main_delete(main);
      return F_none;
    }

    if (main->parameters[iki_write_parameter_version].result == f_console_result_found) {
      fll_program_print_version(main->output, iki_write_version);

      iki_write_main_delete(main);
      return F_none;
    }

    f_file_t output = f_file_t_initialize;

    output.id = f_type_descriptor_output;
    output.stream = f_type_output;
    output.flag = f_file_flag_create | f_file_flag_write_only | f_file_flag_append;

    if (F_status_is_error_not(status)) {
      if (main->parameters[iki_write_parameter_file].result == f_console_result_additional) {
        if (main->parameters[iki_write_parameter_file].values.used > 1) {
          if (main->error.verbosity != f_console_verbosity_quiet) {
            f_color_print(main->error.to.stream, main->context.set.error, "%sThe parameter '", fll_error_print_error);
            f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, iki_write_long_file);
            f_color_print(main->error.to.stream, main->context.set.error, "' may only be specified once.%c", f_string_eol_s[0]);
          }

          status = F_status_set_error(F_parameter);
        }
        else {
          const f_array_length_t location = main->parameters[iki_write_parameter_file].values.array[0];

          output.id = -1;
          output.stream = 0;

          status = f_file_stream_open(arguments.argv[location], 0, &output);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_open", F_true, arguments.argv[location], "open", fll_error_file_type_file);
          }
        }
      }
      else if (main->parameters[iki_write_parameter_file].result == f_console_result_found) {
        if (main->error.verbosity != f_console_verbosity_quiet) {
          f_color_print(main->error.to.stream, main->context.set.error, "%sThe parameter '", fll_error_print_error);
          f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, iki_write_long_file);
          f_color_print(main->error.to.stream, main->context.set.error, "' was specified, but no value was given.%c", f_string_eol_s[0]);
        }

        status = F_status_set_error(F_parameter);
      }
    }

    if (F_status_is_error_not(status) && main->parameters[iki_write_parameter_object].result == f_console_result_found) {
      if (main->error.verbosity != f_console_verbosity_quiet) {
        f_color_print(main->error.to.stream, main->context.set.error, "%sThe parameter '", fll_error_print_error);
        f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, iki_write_long_object);
        f_color_print(main->error.to.stream, main->context.set.error, "' was specified, but no value was given.%c", f_string_eol_s[0]);
      }

      status = F_status_set_error(F_parameter);
    }

    if (F_status_is_error_not(status) && main->parameters[iki_write_parameter_content].result == f_console_result_found) {
      if (main->error.verbosity != f_console_verbosity_quiet) {
        f_color_print(main->error.to.stream, main->context.set.error, "%sThe parameter '", fll_error_print_error);
        f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, iki_write_long_content);
        f_color_print(main->error.to.stream, main->context.set.error, "' was specified, but no value was given.%c", f_string_eol_s[0]);
      }

      status = F_status_set_error(F_parameter);
    }

    if (F_status_is_error_not(status) && !main->process_pipe) {
      if (main->parameters[iki_write_parameter_object].result != f_console_result_additional && main->parameters[iki_write_parameter_content].result != f_console_result_additional) {
        if (main->error.verbosity != f_console_verbosity_quiet) {
          fprintf(main->error.to.stream, "%c", f_string_eol_s[0]);
          f_color_print(main->error.to.stream, main->context.set.error, "%sNo main provided, either pipe the main or use the '", fll_error_print_error);
          f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, iki_write_long_object);
          f_color_print(main->error.to.stream, main->context.set.error, "' and the '");
          f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, iki_write_long_content);
          f_color_print(main->error.to.stream, main->context.set.error, "' parameters.%c", f_string_eol_s[0]);
        }

        status = F_status_set_error(F_parameter);
      }
    }

    if (F_status_is_error_not(status)) {
      if (main->parameters[iki_write_parameter_object].values.used != main->parameters[iki_write_parameter_content].values.used) {
        if (main->error.verbosity != f_console_verbosity_quiet) {
          f_color_print(main->error.to.stream, main->context.set.error, "%sThe parameters '", fll_error_print_error);
          f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, iki_write_long_content);
          f_color_print(main->error.to.stream, main->context.set.error, "' and '");
          f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, iki_write_long_object);
          f_color_print(main->error.to.stream, main->context.set.error, "' must be specified the same number of times.%c", f_string_eol_s[0]);
        }

        status = F_status_set_error(F_parameter);
      }
    }

    uint8_t quote = f_iki_syntax_quote_double;

    if (F_status_is_error_not(status)) {
      if (main->parameters[iki_write_parameter_double].result == f_console_result_found) {
        if (main->parameters[iki_write_parameter_single].result == f_console_result_found) {
          if (main->parameters[iki_write_parameter_double].location < main->parameters[iki_write_parameter_single].location) {
            quote = f_iki_syntax_quote_single;
          }
        }
      }
      else if (main->parameters[iki_write_parameter_single].result == f_console_result_found) {
        quote = f_iki_syntax_quote_single;
      }
    }

    if (F_status_is_error_not(status)) {
      f_string_dynamic_t escaped = f_string_dynamic_t_initialize;

      if (main->process_pipe) {
        f_file_t pipe = f_file_t_initialize;

        pipe.id = f_type_descriptor_input;
        pipe.size_read = 1;

        f_string_dynamic_t buffer = f_string_dynamic_t_initialize;
        f_string_dynamic_t object = f_string_dynamic_t_initialize;
        f_string_dynamic_t content = f_string_dynamic_t_initialize;

        bool object_ended = F_false;

        f_array_length_t previous = 0;
        f_string_range_t range = f_string_range_t_initialize;

        range.start = 0;

        for (f_status_t status_pipe = F_none; ; ) {

          if (status_pipe != F_none_eof) {
            status_pipe = f_file_read(pipe, &buffer);

            if (F_status_is_error(status_pipe)) {
              fll_error_file_print(main->error, F_status_set_fine(status), "f_file_read_to", F_true, "-", "read", fll_error_file_type_pipe);

              status = F_status_set_error(F_pipe);
              break;
            }

            if (!buffer.used) {
              if (main->error.verbosity != f_console_verbosity_quiet) {
                f_color_print(main->error.to.stream, main->context.set.error, "%sThe pipe has no main.%c", fll_error_print_error, f_string_eol_s[0]);
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
            if (main->error.verbosity != f_console_verbosity_quiet) {
              f_color_print(main->error.to.stream, main->context.set.error, "%sThe pipe has incorrectly placed newlines.%c", fll_error_print_error, f_string_eol_s[0]);
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

            status = iki_write_process(*main, output, object, content, quote, &escaped);
            if (F_status_is_error(status)) break;

            fprintf(output.stream, "%c", f_string_eol_s[0]);

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
          if (main->error.verbosity != f_console_verbosity_quiet) {
            f_color_print(main->error.to.stream, main->context.set.error, "%sThe pipe has an object without content.%c", fll_error_print_error, f_string_eol_s[0]);
          }

          status = F_status_set_error(F_parameter);
        }

        macro_f_string_dynamic_t_delete_simple(buffer);
        macro_f_string_dynamic_t_delete_simple(object);
        macro_f_string_dynamic_t_delete_simple(content);
      }

      if (F_status_is_error_not(status)) {
        f_string_static_t object = f_string_static_t_initialize;
        f_string_static_t content = f_string_static_t_initialize;

        for (f_array_length_t i = 0; i < main->parameters[iki_write_parameter_object].values.used; ++i) {

          object.string = arguments.argv[main->parameters[iki_write_parameter_object].values.array[i]];
          object.used = strnlen(object.string, f_console_parameter_size);
          object.size = object.used;

          content.string = arguments.argv[main->parameters[iki_write_parameter_content].values.array[i]];
          content.used = strnlen(content.string, f_console_parameter_size);
          content.size = content.used;

          status = iki_write_process(*main, output, object, content, quote, &escaped);
          if (F_status_is_error(status)) break;

          fprintf(output.stream, "%c", f_string_eol_s[0]);
        } // for

        // ensure there is always a newline at the end, unless in quiet mode.
        if (F_status_is_error_not(status) && main->error.verbosity != f_console_verbosity_quiet && main->parameters[iki_write_parameter_file].result == f_console_result_none) {
          fprintf(main->output.stream, "%c", f_string_eol_s[0]);
        }
      }

      macro_f_string_dynamic_t_delete_simple(escaped);
    }

    if (main->parameters[iki_write_parameter_file].result == f_console_result_additional) {
      if (output.id != -1) {
        f_file_stream_close(F_true, &output);
      }
    }

    // ensure a newline is always put at the end of the program execution, unless in quiet mode.
    if (main->error.verbosity != f_console_verbosity_quiet) {
      if (F_status_is_error(status)) {
        fprintf(main->error.to.stream, "%c", f_string_eol_s[0]);
      }
    }

    iki_write_main_delete(main);
    return status;
  }
#endif // _di_iki_write_main_

#ifndef _di_iki_write_main_delete_
  f_status_t iki_write_main_delete(iki_write_main_t *main) {

    for (f_array_length_t i = 0; i < iki_write_total_parameters; ++i) {
      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations_sub);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].values);
    } // for

    macro_f_array_lengths_t_delete_simple(main->remaining);
    macro_f_string_dynamic_t_delete_simple(main->buffer);

    macro_f_color_context_t_delete_simple(main->context);

    return F_none;
  }
#endif // _di_iki_write_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif
