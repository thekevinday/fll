#include "byte_dump.h"
#include "private-byte_dump.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_byte_dump_print_help_
  f_return_status byte_dump_print_help(const f_file_t file, const f_color_context_t context) {

    fll_program_print_help_header(file, context, byte_dump_name_long, byte_dump_version);

    fll_program_print_help_option(file, context, f_console_standard_short_help, f_console_standard_long_help, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Print this help message.");
    fll_program_print_help_option(file, context, f_console_standard_short_dark, f_console_standard_long_dark, f_console_symbol_short_disable, f_console_symbol_long_disable, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_light, f_console_standard_long_light, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_no_color, f_console_standard_long_no_color, f_console_symbol_short_disable, f_console_symbol_long_disable, "Do not output in color.");
    fll_program_print_help_option(file, context, f_console_standard_short_quiet, f_console_standard_long_quiet, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Decrease verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_normal, f_console_standard_long_normal, f_console_symbol_short_disable, f_console_symbol_long_disable, "  Set verbosity to normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_verbose, f_console_standard_long_verbose, f_console_symbol_short_disable, f_console_symbol_long_disable, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_debug, f_console_standard_long_debug, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Enable debugging, inceasing verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_version, f_console_standard_long_version, f_console_symbol_short_disable, f_console_symbol_long_disable, " Print only the version number.");

    fprintf(file.stream, "%c", f_string_eol[0]);

    fll_program_print_help_option(file, context, byte_dump_short_binary, byte_dump_long_binary, f_console_symbol_short_enable, f_console_symbol_long_enable, "     Display binary representation.");
    fll_program_print_help_option(file, context, byte_dump_short_decimal, byte_dump_long_decimal, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Display decimal representation.");
    fll_program_print_help_option(file, context, byte_dump_short_duodecimal, byte_dump_long_duodecimal, f_console_symbol_short_enable, f_console_symbol_long_enable, " Display duodecimal representation.");
    fll_program_print_help_option(file, context, byte_dump_short_hexidecimal, byte_dump_long_hexidecimal, f_console_symbol_short_enable, f_console_symbol_long_enable, "Display hexadecimal representation.");
    fll_program_print_help_option(file, context, byte_dump_short_octal, byte_dump_long_octal, f_console_symbol_short_enable, f_console_symbol_long_enable, "      Display octal representation.");

    fprintf(file.stream, "%c", f_string_eol[0]);

    fll_program_print_help_option(file, context, byte_dump_short_first, byte_dump_long_first, f_console_symbol_short_enable, f_console_symbol_long_enable, "      Start reading at this byte offset.");
    fll_program_print_help_option(file, context, byte_dump_short_last, byte_dump_long_last, f_console_symbol_short_enable, f_console_symbol_long_enable, "       Stop reading at this (inclusive) byte offset.");
    fll_program_print_help_option(file, context, byte_dump_short_width, byte_dump_long_width, f_console_symbol_short_enable, f_console_symbol_long_enable, "      Set number of columns of Bytes to display.");

    fprintf(file.stream, "%c", f_string_eol[0]);

    fll_program_print_help_option(file, context, byte_dump_short_text, byte_dump_long_text, f_console_symbol_short_enable, f_console_symbol_long_enable, "       Include a column of text when displaying the bytes.");
    fll_program_print_help_option(file, context, byte_dump_short_placeholder, byte_dump_long_placeholder, f_console_symbol_short_enable, f_console_symbol_long_enable, "Use a placeholder character instead of a space for placeholders.");

    fprintf(file.stream, "%c%c", f_string_eol[0], f_string_eol[0]);

    fl_color_print(file.stream, context.set.important, " Special Options: ");

    fll_program_print_help_option_long(file, context, byte_dump_long_normal, f_console_symbol_long_enable, " Display UTF-8 symbols for ASCII control codes.");
    fll_program_print_help_option_long(file, context, byte_dump_long_simple, f_console_symbol_long_enable, " Display spaces for ASCII control codes.");
    fll_program_print_help_option_long(file, context, byte_dump_long_classic, f_console_symbol_long_enable, "Display periods for ASCII control codes.");

    fll_program_print_help_usage(file, context, byte_dump_name, "filename(s)");

    fprintf(file.stream, "  When using the ");
    fl_color_print(file.stream, context.set.notable, "%s%s", f_console_symbol_long_enable, byte_dump_long_text);
    fprintf(file.stream, " option, some UTF-8 characters may be replaced by your instance and cause display alignment issues.");

    fprintf(file.stream, "%c%c", f_string_eol[0], f_string_eol[0]);

    fprintf(file.stream, "  Special UTF-8 characters and non-spacing UTF-8 characters may be replaced with a space (or a placeholder when the ");
    fl_color_print(file.stream, context.set.notable, "%s%s", f_console_symbol_long_enable, byte_dump_long_placeholder);
    fprintf(file.stream, " option is used).");

    fprintf(file.stream, "%c%c", f_string_eol[0], f_string_eol[0]);

    fprintf(file.stream, "  UTF-8 \"Combining\" characters might have a space appended to allow a proper display but this may cause copy and paste issues.");

    fprintf(file.stream, "%c%c", f_string_eol[0], f_string_eol[0]);

    fprintf(file.stream, "  When ");
    fl_color_print(file.stream, context.set.notable, "%s%s", f_console_symbol_long_enable, byte_dump_long_last);
    fprintf(file.stream, " is used, any UTF-8 sequences will still be printed in full should any part is found within the requested range.");

    fprintf(file.stream, "%c%c", f_string_eol[0], f_string_eol[0]);

    return F_none;
  }
#endif // _di_byte_dump_print_help_

#ifndef _di_byte_dump_main_
  f_return_status byte_dump_main(const f_console_arguments_t arguments, byte_dump_data_t *data) {
    f_status_t status = F_none;

    {
      const f_console_parameters_t parameters = f_macro_console_parameters_t_initialize(data->parameters, byte_dump_total_parameters);

      // Identify priority of color parameters.
      {
        f_console_parameter_id_t ids[3] = { byte_dump_parameter_no_color, byte_dump_parameter_light, byte_dump_parameter_dark };
        const f_console_parameter_ids_t choices = f_macro_console_parameter_ids_t_initialize(ids, 3);

        status = fll_program_parameter_process(arguments, parameters, choices, F_true, &data->remaining, &data->context);

        data->error.context = data->context.set.error;
        data->error.notable = data->context.set.notable;

        if (F_status_is_error(status)) {
          fll_error_print(data->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", F_true);

          byte_dump_delete_data(data);
          return F_status_set_error(status);
        }
      }

      // Identify priority of verbosity related parameters.
      {
        f_console_parameter_id_t ids[4] = { byte_dump_parameter_verbosity_quiet, byte_dump_parameter_verbosity_normal, byte_dump_parameter_verbosity_verbose, byte_dump_parameter_verbosity_debug };
        f_console_parameter_id_t choice = 0;
        const f_console_parameter_ids_t choices = f_macro_console_parameter_ids_t_initialize(ids, 4);

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          fll_error_print(data->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", F_true);

          byte_dump_delete_data(data);
          return status;
        }

        if (choice == byte_dump_parameter_verbosity_quiet) {
          data->error.verbosity = f_console_verbosity_quiet;
        }
        else if (choice == byte_dump_parameter_verbosity_normal) {
          data->error.verbosity = f_console_verbosity_normal;
        }
        else if (choice == byte_dump_parameter_verbosity_verbose) {
          data->error.verbosity = f_console_verbosity_verbose;
        }
        else if (choice == byte_dump_parameter_verbosity_debug) {
          data->error.verbosity = f_console_verbosity_debug;
        }
      }

      // Identify priority of mode parameters.
      {
        f_console_parameter_id_t ids[5] = { byte_dump_parameter_hexidecimal, byte_dump_parameter_duodecimal, byte_dump_parameter_octal, byte_dump_parameter_binary, byte_dump_parameter_decimal };
        f_console_parameter_id_t choice = byte_dump_parameter_hexidecimal;
        const f_console_parameter_ids_t choices = f_macro_console_parameter_ids_t_initialize(ids, 5);

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          fll_error_print(data->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", F_true);

          byte_dump_delete_data(data);
          return F_status_set_error(status);
        }

        if (choice == byte_dump_parameter_hexidecimal) {
          data->mode = byte_dump_mode_hexidecimal;
        }
        else if (choice == byte_dump_parameter_duodecimal) {
          data->mode = byte_dump_mode_duodecimal;
        }
        else if (choice == byte_dump_parameter_octal) {
          data->mode = byte_dump_mode_octal;
        }
        else if (choice == byte_dump_parameter_binary) {
          data->mode = byte_dump_mode_binary;
        }
        else if (choice == byte_dump_parameter_decimal) {
          data->mode = byte_dump_mode_decimal;
        }
      }

      // Identify priority of presentation parameters.
      {
        f_console_parameter_id_t ids[3] = { byte_dump_parameter_normal, byte_dump_parameter_simple, byte_dump_parameter_classic };
        f_console_parameter_id_t choice = byte_dump_parameter_normal;
        const f_console_parameter_ids_t choices = f_macro_console_parameter_ids_t_initialize(ids, 3);

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          fll_error_print(data->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", F_true);

          byte_dump_delete_data(data);
          return F_status_set_error(status);
        }

        if (choice == byte_dump_parameter_normal) {
          data->presentation = byte_dump_presentation_normal;
        }
        else if (choice == byte_dump_parameter_simple) {
          data->presentation = byte_dump_presentation_simple;
        }
        else if (choice == byte_dump_parameter_classic) {
          data->presentation = byte_dump_presentation_classic;
        }
      }

      status = F_none;
    }

    if (data->parameters[byte_dump_parameter_help].result == f_console_result_found) {
      byte_dump_print_help(data->output, data->context);

      byte_dump_delete_data(data);
      return F_none;
    }

    if (data->parameters[byte_dump_parameter_version].result == f_console_result_found) {
      fll_program_print_version(data->output, byte_dump_version);

      byte_dump_delete_data(data);
      return F_none;
    }

    if (data->remaining.used > 0 || data->process_pipe) {
      if (data->parameters[byte_dump_parameter_width].result == f_console_result_found) {
        fl_color_print(data->error.to.stream, data->context.set.error, "ERROR: The parameter '");
        fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, byte_dump_long_width);
        fl_color_print(data->error.to.stream, data->context.set.error, "' was specified, but no value was given.%c", f_string_eol[0]);

        byte_dump_delete_data(data);
        return F_status_set_error(status);
      }
      else if (data->parameters[byte_dump_parameter_width].result == f_console_result_additional) {
        const f_string_length_t index = data->parameters[byte_dump_parameter_width].additional.array[data->parameters[byte_dump_parameter_width].additional.used - 1];
        const f_string_range_t range = f_macro_string_range_t_initialize(strlen(arguments.argv[index]));

        f_number_unsigned_t number = 0;

        status = fl_conversion_string_to_number_unsigned(arguments.argv[index], &number, range);

        if (F_status_is_error(status) || number < 1 || number >= 0xfb) {
          fl_color_print(data->error.to.stream, data->context.set.error, "ERROR: The parameter '");
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, byte_dump_long_width);
          fl_color_print(data->error.to.stream, data->context.set.error, "' value can only be a number between ");
          fl_color_print(data->error.to.stream, data->context.set.notable, "0");
          fl_color_print(data->error.to.stream, data->context.set.error, " and ");
          fl_color_print(data->error.to.stream, data->context.set.notable, "251");
          fl_color_print(data->error.to.stream, data->context.set.error, ".%c", f_string_eol[0]);

          byte_dump_delete_data(data);
          return F_status_set_error(status);
        }

        data->width = (uint8_t) number;
      }

      if (data->parameters[byte_dump_parameter_first].result == f_console_result_found) {
        fl_color_print(data->error.to.stream, data->context.set.error, "ERROR: The parameter '");
        fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, byte_dump_long_first);
        fl_color_print(data->error.to.stream, data->context.set.error, "' was specified, but no value was given.%c", f_string_eol[0]);

        byte_dump_delete_data(data);
        return F_status_set_error(status);
      }
      else if (data->parameters[byte_dump_parameter_first].result == f_console_result_additional) {
        const f_string_length_t index = data->parameters[byte_dump_parameter_first].additional.array[data->parameters[byte_dump_parameter_first].additional.used - 1];
        const f_string_range_t range = f_macro_string_range_t_initialize(strlen(arguments.argv[index]));

        f_number_unsigned_t number = 0;

        status = fl_conversion_string_to_number_unsigned(arguments.argv[index], &number, range);

        if (F_status_is_error(status) || number > f_number_t_size_unsigned) {
          fl_color_print(data->error.to.stream, data->context.set.error, "ERROR: The parameter '");
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, byte_dump_long_first);
          fl_color_print(data->error.to.stream, data->context.set.error, "' value can only be a number (inclusively) between ");
          fl_color_print(data->error.to.stream, data->context.set.notable, "0");
          fl_color_print(data->error.to.stream, data->context.set.error, " and ");
          fl_color_print(data->error.to.stream, data->context.set.notable, "%llu", f_number_t_size_unsigned);
          fl_color_print(data->error.to.stream, data->context.set.error, ".%c", f_string_eol[0]);

          byte_dump_delete_data(data);
          return F_status_set_error(status);
        }

        data->first = number;
      }

      if (data->parameters[byte_dump_parameter_last].result == f_console_result_found) {
        fl_color_print(data->error.to.stream, data->context.set.error, "ERROR: The parameter '");
        fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, byte_dump_long_last);
        fl_color_print(data->error.to.stream, data->context.set.error, "' was specified, but no value was given.%c", f_string_eol[0]);

        byte_dump_delete_data(data);
        return F_status_set_error(status);
      }
      else if (data->parameters[byte_dump_parameter_last].result == f_console_result_additional) {
        const f_string_length_t index = data->parameters[byte_dump_parameter_last].additional.array[data->parameters[byte_dump_parameter_last].additional.used - 1];
        const f_string_range_t range = f_macro_string_range_t_initialize(strlen(arguments.argv[index]));

        f_number_unsigned_t number = 0;

        status = fl_conversion_string_to_number_unsigned(arguments.argv[index], &number, range);

        if (F_status_is_error(status) || number < 0 || number > f_number_t_size_unsigned) {
          fl_color_print(data->error.to.stream, data->context.set.error, "ERROR: The parameter '");
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, byte_dump_long_last);
          fl_color_print(data->error.to.stream, data->context.set.error, "' value can only be a number (inclusively) between ");
          fl_color_print(data->error.to.stream, data->context.set.notable, "0");
          fl_color_print(data->error.to.stream, data->context.set.error, " and ");
          fl_color_print(data->error.to.stream, data->context.set.notable, "%llu", f_number_t_size_unsigned);
          fl_color_print(data->error.to.stream, data->context.set.error, ".%c", f_string_eol[0]);

          byte_dump_delete_data(data);
          return F_status_set_error(status);
        }

        data->last = number;
      }

      if (data->parameters[byte_dump_parameter_first].result == f_console_result_additional && data->parameters[byte_dump_parameter_last].result == f_console_result_additional) {
        if (data->first > data->last) {
          fl_color_print(data->error.to.stream, data->context.set.error, "ERROR: The parameter '");
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, byte_dump_long_first);
          fl_color_print(data->error.to.stream, data->context.set.error, "' value cannot be greater than the parameter '");
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, byte_dump_long_last);
          fl_color_print(data->error.to.stream, data->context.set.error, "' value.%c", f_string_eol[0]);

          byte_dump_delete_data(data);
          return F_status_set_error(status);
        }

        // store last position as a relative offset from first instead of an absolute position.
        data->last = (data->last - data->first) + 1;
      }

      if (data->process_pipe) {
        f_file_t file = f_file_t_initialize;

        file.id = f_type_descriptor_input;

        printf("%c", f_string_eol[0]);
        fl_color_print(data->output.stream, data->context.set.title, "Piped Byte Dump: (in ");

        if (data->mode == byte_dump_mode_hexidecimal) {
          fl_color_print(data->output.stream, data->context.set.title, "Hexidecimal");
        }
        else if (data->mode == byte_dump_mode_duodecimal) {
          fl_color_print(data->output.stream, data->context.set.title, "Duodecimal");
        }
        else if (data->mode == byte_dump_mode_octal) {
          fl_color_print(data->output.stream, data->context.set.title, "Octal");
        }
        else if (data->mode == byte_dump_mode_binary) {
          fl_color_print(data->output.stream, data->context.set.title, "Binary");
        }
        else if (data->mode == byte_dump_mode_decimal) {
          fl_color_print(data->output.stream, data->context.set.title, "Decimal");
        }

        fl_color_print(data->output.stream, data->context.set.title, ")%c", f_string_eol[0]);

        status = byte_dump_file(*data, "-", file);

        if (F_status_is_error(status)) {
          fll_error_print(data->error, F_status_set_fine(status), "byte_dump_file", F_true);

          byte_dump_delete_data(data);
          return status;
        }
      }

      if (data->remaining.used > 0) {
        // pre-process remaining arguments to ensure that they all files exist before processing.
        {
          f_status_t missing_files = F_none;

          for (f_array_length_t counter = 0; counter < data->remaining.used; counter++) {

            status = f_file_exists(arguments.argv[data->remaining.array[counter]]);

            if (status == F_false || F_status_is_error(status)) {
              if (missing_files == F_none) {
                missing_files = status;
              }

              fll_error_file_print(data.error, F_status_set_fine(status), "f_file_exists", F_true, arguments.argv[data->remaining.array[counter]], "find", fll_error_file_type_file);
            }
          } // for

          if (missing_files != F_none) {
            status = F_status_set_error(missing_files);

            byte_dump_delete_data(data);
            return status;
          }
        }

        f_file_t file = f_file_t_initialize;

        for (f_array_length_t counter = 0; counter < data->remaining.used; counter++) {
          status = f_file_open(arguments.argv[data->remaining.array[counter]], 0, &file);

          if (F_status_is_error(status)) {
            fll_error_file_print(data.error, F_status_set_fine(status), "f_file_open", F_true, arguments.argv[data->remaining.array[counter]], "open", fll_error_file_type_file);

            byte_dump_delete_data(data);
            return status;
          }

          printf("%c", f_string_eol[0]);
          fl_color_print(data->output.stream, data->context.set.title, "Byte Dump of: ");
          fl_color_print(data->output.stream, data->context.set.notable, "%s", arguments.argv[data->remaining.array[counter]]);
          fl_color_print(data->output.stream, data->context.set.title, " (in ");

          if (data->mode == byte_dump_mode_hexidecimal) {
            fl_color_print(data->output.stream, data->context.set.title, "Hexidecimal");
          }
          else if (data->mode == byte_dump_mode_duodecimal) {
            fl_color_print(data->output.stream, data->context.set.title, "Duodecimal");
          }
          else if (data->mode == byte_dump_mode_octal) {
            fl_color_print(data->output.stream, data->context.set.title, "Octal");
          }
          else if (data->mode == byte_dump_mode_binary) {
            fl_color_print(data->output.stream, data->context.set.title, "Binary");
          }
          else if (data->mode == byte_dump_mode_decimal) {
            fl_color_print(data->output.stream, data->context.set.title, "Decimal");
          }

          fl_color_print(data->output.stream, data->context.set.title, ")%c", f_string_eol[0]);

          status = byte_dump_file(*data, arguments.argv[data->remaining.array[counter]], file);

          f_file_close(&file.id);

          if (F_status_is_error(status)) {
            fll_error_file_print(data.error, F_status_set_fine(status), "byte_dump_file", F_true, arguments.argv[data->remaining.array[counter]], "open", fll_error_file_type_file);

            byte_dump_delete_data(data);
            return status;
          }
        } // for
      }
      else {
        status = F_false;
      }
    }
    else {
      fl_color_print(data->error.to.stream, data->context.set.error, "ERROR: You failed to specify one or more filenames.%c", f_string_eol[0]);
      status = F_status_set_error(F_parameter);
    }

    byte_dump_delete_data(data);
    return status;
  }
#endif // _di_byte_dump_main_

#ifndef _di_byte_dump_delete_data_
  f_return_status byte_dump_delete_data(byte_dump_data_t *data) {

    for (f_string_length_t i = 0; i < byte_dump_total_parameters; i++) {
      f_macro_string_lengths_t_delete_simple(data->parameters[i].locations);
      f_macro_string_lengths_t_delete_simple(data->parameters[i].additional);
    } // for

    f_macro_string_lengths_t_delete_simple(data->remaining);
    f_macro_color_context_t_delete_simple(data->context);

    return F_none;
  }
#endif // _di_byte_dump_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif
