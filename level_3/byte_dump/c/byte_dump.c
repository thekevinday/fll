#include "byte_dump.h"
#include "private-common.h"
#include "private-byte_dump.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_byte_dump_print_help_
  f_status_t byte_dump_print_help(const f_file_t output, const f_color_context_t context) {

    fll_program_print_help_header(output, context, byte_dump_name_long, byte_dump_version);

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

    fll_program_print_help_option(output, context, byte_dump_short_binary, byte_dump_long_binary, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "     Display binary representation.");
    fll_program_print_help_option(output, context, byte_dump_short_decimal, byte_dump_long_decimal, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Display decimal representation.");
    fll_program_print_help_option(output, context, byte_dump_short_duodecimal, byte_dump_long_duodecimal, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Display duodecimal representation.");
    fll_program_print_help_option(output, context, byte_dump_short_hexidecimal, byte_dump_long_hexidecimal, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Display hexadecimal representation.");
    fll_program_print_help_option(output, context, byte_dump_short_octal, byte_dump_long_octal, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "      Display octal representation.");
    fll_program_print_help_option(output, context, byte_dump_short_unicode, byte_dump_long_unicode, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Display using Unicode representation for valid Unicode (like: U+0000).");

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fll_program_print_help_option(output, context, byte_dump_short_first, byte_dump_long_first, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "      Start reading at this byte offset.");
    fll_program_print_help_option(output, context, byte_dump_short_last, byte_dump_long_last, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "       Stop reading at this (inclusive) byte offset.");
    fll_program_print_help_option(output, context, byte_dump_short_width, byte_dump_long_width, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "      Set number of columns of Bytes to display.");

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fll_program_print_help_option(output, context, byte_dump_short_text, byte_dump_long_text, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "       Include a column of text when displaying the bytes.");
    fll_program_print_help_option(output, context, byte_dump_short_placeholder, byte_dump_long_placeholder, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Use a placeholder character instead of a space for placeholders.");

    fprintf(output.stream, "%c%c", f_string_eol_s[0], f_string_eol_s[0]);

    f_color_print(output.stream, context.set.important, " Special Options: ");

    fll_program_print_help_option_long(output, context, byte_dump_long_normal, f_console_symbol_long_enable_s, " Display UTF-8 symbols for ASCII control codes.");
    fll_program_print_help_option_long(output, context, byte_dump_long_simple, f_console_symbol_long_enable_s, " Display spaces for ASCII control codes.");
    fll_program_print_help_option_long(output, context, byte_dump_long_classic, f_console_symbol_long_enable_s, "Display periods for ASCII control codes.");

    fll_program_print_help_usage(output, context, byte_dump_name, "filename(s)");

    fprintf(output.stream, "  When using the ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, byte_dump_long_text);
    fprintf(output.stream, " option, some UTF-8 characters may be replaced by your instance and cause display alignment issues.");

    fprintf(output.stream, "%c%c", f_string_eol_s[0], f_string_eol_s[0]);

    fprintf(output.stream, "  Special UTF-8 characters and non-spacing UTF-8 characters may be replaced with a space (or a placeholder when the ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, byte_dump_long_placeholder);
    fprintf(output.stream, " option is used).");

    fprintf(output.stream, "%c%c", f_string_eol_s[0], f_string_eol_s[0]);

    fprintf(output.stream, "  UTF-8 \"Combining\" characters might have a space appended to allow a proper display but this may cause copy and paste issues.");

    fprintf(output.stream, "%c%c", f_string_eol_s[0], f_string_eol_s[0]);

    fprintf(output.stream, "  When ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, byte_dump_long_last);
    fprintf(output.stream, " is used, any UTF-8 sequences will still be printed in full should any part is found within the requested range.");

    fprintf(output.stream, "%c%c", f_string_eol_s[0], f_string_eol_s[0]);

    fprintf(output.stream, "  When using the ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, byte_dump_long_unicode);
    fprintf(output.stream, " option, invalid Unicode will fallback to being displayed using one of the other modes.");

    fprintf(output.stream, "%c%c", f_string_eol_s[0], f_string_eol_s[0]);

    return F_none;
  }
#endif // _di_byte_dump_print_help_

#ifndef _di_byte_dump_main_
  f_status_t byte_dump_main(const f_console_arguments_t arguments, byte_dump_main_t *main) {
    f_status_t status = F_none;

    {
      const f_console_parameters_t parameters = macro_f_console_parameters_t_initialize(main->parameters, byte_dump_total_parameters);

      // Identify priority of color parameters.
      {
        f_console_parameter_id_t ids[3] = { byte_dump_parameter_no_color, byte_dump_parameter_light, byte_dump_parameter_dark };
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
          fll_error_print(main->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", F_true);

          byte_dump_main_delete(main);
          return F_status_set_error(status);
        }
      }

      // Identify priority of verbosity related parameters.
      {
        f_console_parameter_id_t ids[4] = { byte_dump_parameter_verbosity_quiet, byte_dump_parameter_verbosity_normal, byte_dump_parameter_verbosity_verbose, byte_dump_parameter_verbosity_debug };
        f_console_parameter_id_t choice = 0;
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 4);

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", F_true);

          byte_dump_main_delete(main);
          return status;
        }

        if (choice == byte_dump_parameter_verbosity_quiet) {
          main->error.verbosity = f_console_verbosity_quiet;
        }
        else if (choice == byte_dump_parameter_verbosity_normal) {
          main->error.verbosity = f_console_verbosity_normal;
        }
        else if (choice == byte_dump_parameter_verbosity_verbose) {
          main->error.verbosity = f_console_verbosity_verbose;
        }
        else if (choice == byte_dump_parameter_verbosity_debug) {
          main->error.verbosity = f_console_verbosity_debug;
        }
      }

      // Identify priority of mode parameters.
      {
        f_console_parameter_id_t ids[5] = { byte_dump_parameter_hexidecimal, byte_dump_parameter_duodecimal, byte_dump_parameter_octal, byte_dump_parameter_binary, byte_dump_parameter_decimal };
        f_console_parameter_id_t choice = byte_dump_parameter_hexidecimal;
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 5);

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", F_true);

          byte_dump_main_delete(main);
          return F_status_set_error(status);
        }

        if (choice == byte_dump_parameter_hexidecimal) {
          main->mode = byte_dump_mode_hexidecimal;
        }
        else if (choice == byte_dump_parameter_duodecimal) {
          main->mode = byte_dump_mode_duodecimal;
        }
        else if (choice == byte_dump_parameter_octal) {
          main->mode = byte_dump_mode_octal;
        }
        else if (choice == byte_dump_parameter_binary) {
          main->mode = byte_dump_mode_binary;
        }
        else if (choice == byte_dump_parameter_decimal) {
          main->mode = byte_dump_mode_decimal;
        }
      }

      // Identify priority of presentation parameters.
      {
        f_console_parameter_id_t ids[3] = { byte_dump_parameter_normal, byte_dump_parameter_simple, byte_dump_parameter_classic };
        f_console_parameter_id_t choice = byte_dump_parameter_normal;
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 3);

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", F_true);

          byte_dump_main_delete(main);
          return F_status_set_error(status);
        }

        if (choice == byte_dump_parameter_normal) {
          main->presentation = byte_dump_presentation_normal;
        }
        else if (choice == byte_dump_parameter_simple) {
          main->presentation = byte_dump_presentation_simple;
        }
        else if (choice == byte_dump_parameter_classic) {
          main->presentation = byte_dump_presentation_classic;
        }
      }

      status = F_none;
    }

    if (main->parameters[byte_dump_parameter_help].result == f_console_result_found) {
      byte_dump_print_help(main->output, main->context);

      byte_dump_main_delete(main);
      return F_none;
    }

    if (main->parameters[byte_dump_parameter_version].result == f_console_result_found) {
      fll_program_print_version(main->output, byte_dump_version);

      byte_dump_main_delete(main);
      return F_none;
    }

    if (main->remaining.used > 0 || main->process_pipe) {
      if (main->parameters[byte_dump_parameter_width].result == f_console_result_found) {
        f_color_print(main->error.to.stream, main->context.set.error, "%sThe parameter '", fll_error_print_error);
        f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, byte_dump_long_width);
        f_color_print(main->error.to.stream, main->context.set.error, "' was specified, but no value was given.%c", f_string_eol_s[0]);

        byte_dump_main_delete(main);
        return F_status_set_error(status);
      }
      else if (main->parameters[byte_dump_parameter_width].result == f_console_result_additional) {
        const f_array_length_t index = main->parameters[byte_dump_parameter_width].values.array[main->parameters[byte_dump_parameter_width].values.used - 1];
        const f_string_range_t range = macro_f_string_range_t_initialize(strlen(arguments.argv[index]));

        f_number_unsigned_t number = 0;

        status = fl_conversion_string_to_number_unsigned(arguments.argv[index], range, &number);

        if (F_status_is_error(status) || number < 1 || number >= 0xfb) {
          f_color_print(main->error.to.stream, main->context.set.error, "%sThe parameter '", fll_error_print_error);
          f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, byte_dump_long_width);
          f_color_print(main->error.to.stream, main->context.set.error, "' value can only be a number between ");
          f_color_print(main->error.to.stream, main->context.set.notable, "0");
          f_color_print(main->error.to.stream, main->context.set.error, " and ");
          f_color_print(main->error.to.stream, main->context.set.notable, "251");
          f_color_print(main->error.to.stream, main->context.set.error, ".%c", f_string_eol_s[0]);

          byte_dump_main_delete(main);
          return F_status_set_error(status);
        }

        main->width = (uint8_t) number;
      }

      if (main->parameters[byte_dump_parameter_first].result == f_console_result_found) {
        f_color_print(main->error.to.stream, main->context.set.error, "%sThe parameter '", fll_error_print_error);
        f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, byte_dump_long_first);
        f_color_print(main->error.to.stream, main->context.set.error, "' was specified, but no value was given.%c", f_string_eol_s[0]);

        byte_dump_main_delete(main);
        return F_status_set_error(status);
      }
      else if (main->parameters[byte_dump_parameter_first].result == f_console_result_additional) {
        const f_array_length_t index = main->parameters[byte_dump_parameter_first].values.array[main->parameters[byte_dump_parameter_first].values.used - 1];
        const f_string_range_t range = macro_f_string_range_t_initialize(strlen(arguments.argv[index]));

        f_number_unsigned_t number = 0;

        status = fl_conversion_string_to_number_unsigned(arguments.argv[index], range, &number);

        if (F_status_is_error(status) || number > f_number_t_size_unsigned) {
          f_color_print(main->error.to.stream, main->context.set.error, "%sThe parameter '", fll_error_print_error);
          f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, byte_dump_long_first);
          f_color_print(main->error.to.stream, main->context.set.error, "' value can only be a number (inclusively) between ");
          f_color_print(main->error.to.stream, main->context.set.notable, "0");
          f_color_print(main->error.to.stream, main->context.set.error, " and ");
          f_color_print(main->error.to.stream, main->context.set.notable, "%llu", f_number_t_size_unsigned);
          f_color_print(main->error.to.stream, main->context.set.error, ".%c", f_string_eol_s[0]);

          byte_dump_main_delete(main);
          return F_status_set_error(status);
        }

        main->first = number;
      }

      if (main->parameters[byte_dump_parameter_last].result == f_console_result_found) {
        f_color_print(main->error.to.stream, main->context.set.error, "%sThe parameter '", fll_error_print_error);
        f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, byte_dump_long_last);
        f_color_print(main->error.to.stream, main->context.set.error, "' was specified, but no value was given.%c", f_string_eol_s[0]);

        byte_dump_main_delete(main);
        return F_status_set_error(status);
      }
      else if (main->parameters[byte_dump_parameter_last].result == f_console_result_additional) {
        const f_array_length_t index = main->parameters[byte_dump_parameter_last].values.array[main->parameters[byte_dump_parameter_last].values.used - 1];
        const f_string_range_t range = macro_f_string_range_t_initialize(strlen(arguments.argv[index]));

        f_number_unsigned_t number = 0;

        status = fl_conversion_string_to_number_unsigned(arguments.argv[index], range, &number);

        if (F_status_is_error(status) || number < 0 || number > f_number_t_size_unsigned) {
          f_color_print(main->error.to.stream, main->context.set.error, "%sThe parameter '", fll_error_print_error);
          f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, byte_dump_long_last);
          f_color_print(main->error.to.stream, main->context.set.error, "' value can only be a number (inclusively) between ");
          f_color_print(main->error.to.stream, main->context.set.notable, "0");
          f_color_print(main->error.to.stream, main->context.set.error, " and ");
          f_color_print(main->error.to.stream, main->context.set.notable, "%llu", f_number_t_size_unsigned);
          f_color_print(main->error.to.stream, main->context.set.error, ".%c", f_string_eol_s[0]);

          byte_dump_main_delete(main);
          return F_status_set_error(status);
        }

        main->last = number;
      }

      if (main->parameters[byte_dump_parameter_first].result == f_console_result_additional && main->parameters[byte_dump_parameter_last].result == f_console_result_additional) {
        if (main->first > main->last) {
          f_color_print(main->error.to.stream, main->context.set.error, "%sThe parameter '", fll_error_print_error);
          f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, byte_dump_long_first);
          f_color_print(main->error.to.stream, main->context.set.error, "' value cannot be greater than the parameter '");
          f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, byte_dump_long_last);
          f_color_print(main->error.to.stream, main->context.set.error, "' value.%c", f_string_eol_s[0]);

          byte_dump_main_delete(main);
          return F_status_set_error(status);
        }

        // store last position as a relative offset from first instead of an absolute position.
        main->last = (main->last - main->first) + 1;
      }

      if (main->process_pipe) {
        f_file_t file = f_file_t_initialize;

        file.id = f_type_descriptor_input;
        file.stream = f_type_input;

        printf("%c", f_string_eol_s[0]);
        f_color_print(main->output.stream, main->context.set.title, "Piped Byte Dump: (in ");

        if (main->mode == byte_dump_mode_hexidecimal) {
          f_color_print(main->output.stream, main->context.set.title, "Hexidecimal");
        }
        else if (main->mode == byte_dump_mode_duodecimal) {
          f_color_print(main->output.stream, main->context.set.title, "Duodecimal");
        }
        else if (main->mode == byte_dump_mode_octal) {
          f_color_print(main->output.stream, main->context.set.title, "Octal");
        }
        else if (main->mode == byte_dump_mode_binary) {
          f_color_print(main->output.stream, main->context.set.title, "Binary");
        }
        else if (main->mode == byte_dump_mode_decimal) {
          f_color_print(main->output.stream, main->context.set.title, "Decimal");
        }

        f_color_print(main->output.stream, main->context.set.title, ")%c", f_string_eol_s[0]);

        status = byte_dump_file(*main, 0, file);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "byte_dump_file", F_true);

          byte_dump_main_delete(main);
          return status;
        }
      }

      if (main->remaining.used > 0) {
        // pre-process remaining arguments to ensure that they all files exist before processing.
        {
          f_status_t missing_files = F_none;

          for (f_array_length_t counter = 0; counter < main->remaining.used; ++counter) {

            status = f_file_exists(arguments.argv[main->remaining.array[counter]]);

            if (status == F_false || F_status_is_error(status)) {
              if (missing_files == F_none) {
                missing_files = status;
              }

              fll_error_file_print(main->error, F_status_set_fine(status), "f_file_exists", F_true, arguments.argv[main->remaining.array[counter]], "find", fll_error_file_type_file);
            }
          } // for

          if (missing_files != F_none) {
            status = F_status_set_error(missing_files);

            byte_dump_main_delete(main);
            return status;
          }
        }

        f_file_t file = f_file_t_initialize;

        for (f_array_length_t counter = 0; counter < main->remaining.used; ++counter) {

          status = f_file_stream_open(arguments.argv[main->remaining.array[counter]], 0, &file);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_open", F_true, arguments.argv[main->remaining.array[counter]], "open", fll_error_file_type_file);

            byte_dump_main_delete(main);
            return status;
          }

          printf("%c", f_string_eol_s[0]);
          f_color_print(main->output.stream, main->context.set.title, "Byte Dump of: ");
          f_color_print(main->output.stream, main->context.set.notable, "%s", arguments.argv[main->remaining.array[counter]]);
          f_color_print(main->output.stream, main->context.set.title, " (in ");

          if (main->mode == byte_dump_mode_hexidecimal) {
            f_color_print(main->output.stream, main->context.set.title, "Hexidecimal");
          }
          else if (main->mode == byte_dump_mode_duodecimal) {
            f_color_print(main->output.stream, main->context.set.title, "Duodecimal");
          }
          else if (main->mode == byte_dump_mode_octal) {
            f_color_print(main->output.stream, main->context.set.title, "Octal");
          }
          else if (main->mode == byte_dump_mode_binary) {
            f_color_print(main->output.stream, main->context.set.title, "Binary");
          }
          else if (main->mode == byte_dump_mode_decimal) {
            f_color_print(main->output.stream, main->context.set.title, "Decimal");
          }

          f_color_print(main->output.stream, main->context.set.title, ")%c", f_string_eol_s[0]);

          status = byte_dump_file(*main, arguments.argv[main->remaining.array[counter]], file);

          f_file_stream_close(F_true, &file);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "byte_dump_file", F_true, arguments.argv[main->remaining.array[counter]], "process", fll_error_file_type_file);

            byte_dump_main_delete(main);
            return status;
          }
        } // for
      }
      else {
        status = F_false;
      }
    }
    else {
      f_color_print(main->error.to.stream, main->context.set.error, "%sYou failed to specify one or more filenames.%c", fll_error_print_error, f_string_eol_s[0]);
      status = F_status_set_error(F_parameter);
    }

    byte_dump_main_delete(main);
    return status;
  }
#endif // _di_byte_dump_main_

#ifndef _di_byte_dump_main_delete_
  f_status_t byte_dump_main_delete(byte_dump_main_t *main) {

    for (f_array_length_t i = 0; i < byte_dump_total_parameters; ++i) {
      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations_sub);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].values);
    } // for

    macro_f_array_lengths_t_delete_simple(main->remaining);

    macro_f_color_context_t_delete_simple(main->context);

    return F_none;
  }
#endif // _di_byte_dump_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif
