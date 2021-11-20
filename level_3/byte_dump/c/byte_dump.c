#include "byte_dump.h"
#include "private-common.h"
#include "private-byte_dump.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_byte_dump_print_help_
  f_status_t byte_dump_print_help(const f_file_t file, const f_color_context_t context) {

    flockfile(file.stream);

    fll_program_print_help_header(file, context, byte_dump_program_name_long_s, byte_dump_version_s);

    fll_program_print_help_option(file, context, f_console_standard_short_help_s, f_console_standard_long_help_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Print this help message.");
    fll_program_print_help_option(file, context, f_console_standard_short_dark_s, f_console_standard_long_dark_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_light_s, f_console_standard_long_light_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "Do not file in color.");
    fll_program_print_help_option(file, context, f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Decrease verbosity, silencing most output.");
    fll_program_print_help_option(file, context, f_console_standard_short_normal_s, f_console_standard_long_normal_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "  Set verbosity to normal file.");
    fll_program_print_help_option(file, context, f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_debug_s, f_console_standard_long_debug_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Enable debugging, significantly increasing verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_version_s, f_console_standard_long_version_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Print only the version number.");

    f_print_character(f_string_eol_s[0], file.stream);

    fll_program_print_help_option(file, context, byte_dump_short_binary_s, byte_dump_long_binary_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "     Display binary representation.");
    fll_program_print_help_option(file, context, byte_dump_short_decimal_s, byte_dump_long_decimal_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Display decimal representation.");
    fll_program_print_help_option(file, context, byte_dump_short_duodecimal_s, byte_dump_long_duodecimal_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Display duodecimal representation.");
    fll_program_print_help_option(file, context, byte_dump_short_hexidecimal_s, byte_dump_long_hexidecimal_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Display hexadecimal representation.");
    fll_program_print_help_option(file, context, byte_dump_short_octal_s, byte_dump_long_octal_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "      Display octal representation.");
    fll_program_print_help_option(file, context, byte_dump_short_unicode_s, byte_dump_long_unicode_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Display using Unicode representation for valid Unicode (like: U+0000).");

    f_print_character(f_string_eol_s[0], file.stream);

    fll_program_print_help_option(file, context, byte_dump_short_first_s, byte_dump_long_first_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Start reading at this byte offset.");
    fll_program_print_help_option(file, context, byte_dump_short_last_s, byte_dump_long_last_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Stop reading at this (inclusive) byte offset.");

    f_print_character(f_string_eol_s[0], file.stream);

    fll_program_print_help_option(file, context, byte_dump_short_narrow_s, byte_dump_long_narrow_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "      Use narrow display, resulting in 1*width reducing size of the text columns.");
    fll_program_print_help_option(file, context, byte_dump_short_placeholder_s, byte_dump_long_placeholder_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Use a placeholder character instead of a space for placeholders.");
    fll_program_print_help_option(file, context, byte_dump_short_text_s, byte_dump_long_text_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "       Include a column of text when displaying the bytes.");
    fll_program_print_help_option(file, context, byte_dump_short_wide_s, byte_dump_long_wide_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "      Use wide display, resulting in 2*width allowing for space for wide characters in the text columns.");
    fll_program_print_help_option(file, context, byte_dump_short_width_s, byte_dump_long_width_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "      Set number of columns of Bytes to display.");

    f_print_character(f_string_eol_s[0], file.stream);
    f_print_character(f_string_eol_s[0], file.stream);

    fl_print_format(" %[Special Options:%] ", file.stream, context.set.important, context.set.important);

    fll_program_print_help_option_long(file, context, byte_dump_long_normal_s, f_console_symbol_long_enable_s, " Display UTF-8 symbols for ASCII control codes.");
    fll_program_print_help_option_long(file, context, byte_dump_long_simple_s, f_console_symbol_long_enable_s, " Display spaces for ASCII control codes.");
    fll_program_print_help_option_long(file, context, byte_dump_long_classic_s, f_console_symbol_long_enable_s, "Display periods for ASCII control codes.");

    fll_program_print_help_usage(file, context, byte_dump_program_name_s, "filename(s)");

    fl_print_format("  When using the %[%s%s%] option, some UTF-8 characters may be replaced by your instance and cause display alignment issues.%c%c", file.stream, context.set.notable, f_console_symbol_long_enable_s, byte_dump_long_text_s, context.set.notable, f_string_eol_s[0], f_string_eol_s[0]);

    fl_print_format("  Special UTF-8 characters and non-spacing UTF-8 characters may be replaced with a space (or a placeholder when the %[%s%s%] option is used).%c%c", file.stream, context.set.notable, f_console_symbol_long_enable_s, byte_dump_long_placeholder_s, context.set.notable, f_string_eol_s[0], f_string_eol_s[0]);

    fl_print_format("  UTF-8 \"Combining\" characters might have a space appended to allow a proper display but this may cause copy and paste issues.%c%c", file.stream, f_string_eol_s[0], f_string_eol_s[0]);

    fl_print_format("  When %[%s%s%] is used, any UTF-8 sequences will still be printed in full should any part is found within the requested range.%c%c", file.stream, context.set.notable, f_console_symbol_long_enable_s, byte_dump_long_last_s, context.set.notable, f_string_eol_s[0], f_string_eol_s[0]);

    fl_print_format("  When using the %[%s%s%] option, invalid Unicode will fallback to being displayed using one of the other modes.%c%c", file.stream, context.set.notable, f_console_symbol_long_enable_s, byte_dump_long_unicode_s, context.set.notable, f_string_eol_s[0], f_string_eol_s[0]);

    funlockfile(file.stream);

    return F_none;
  }
#endif // _di_byte_dump_print_help_

#ifndef _di_byte_dump_main_
  f_status_t byte_dump_main(byte_dump_main_t * const main, const f_console_arguments_t *arguments) {

    f_status_t status = F_none;

    {
      const f_console_parameters_t parameters = macro_f_console_parameters_t_initialize(main->parameters, byte_dump_total_parameters_d);

      // Identify priority of color parameters.
      {
        f_console_parameter_id_t ids[3] = { byte_dump_parameter_no_color, byte_dump_parameter_light, byte_dump_parameter_dark };
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 3);

        status = fll_program_parameter_process(*arguments, parameters, choices, F_true, &main->remaining, &main->context);

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
          fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process", F_true);

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
          main->output.verbosity = f_console_verbosity_quiet;
          main->error.verbosity = f_console_verbosity_quiet;
          main->warning.verbosity = f_console_verbosity_quiet;
        }
        else if (choice == byte_dump_parameter_verbosity_normal) {
          main->output.verbosity = f_console_verbosity_normal;
          main->error.verbosity = f_console_verbosity_normal;
          main->warning.verbosity = f_console_verbosity_normal;
        }
        else if (choice == byte_dump_parameter_verbosity_verbose) {
          main->output.verbosity = f_console_verbosity_verbose;
          main->error.verbosity = f_console_verbosity_verbose;
          main->warning.verbosity = f_console_verbosity_verbose;
        }
        else if (choice == byte_dump_parameter_verbosity_debug) {
          main->output.verbosity = f_console_verbosity_debug;
          main->error.verbosity = f_console_verbosity_debug;
          main->warning.verbosity = f_console_verbosity_debug;
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
      byte_dump_print_help(main->output.to, main->context);

      byte_dump_main_delete(main);

      return F_none;
    }

    if (main->parameters[byte_dump_parameter_version].result == f_console_result_found) {
      fll_program_print_version(main->output.to, byte_dump_version_s);

      byte_dump_main_delete(main);

      return F_none;
    }

    if (main->remaining.used > 0 || main->process_pipe) {
      if (main->parameters[byte_dump_parameter_width].result == f_console_result_found) {
        flockfile(main->error.to.stream);

        fl_print_format("%[%SThe parameter '%]", main->error.to.stream, main->context.set.error, main->error.prefix, main->context.set.error);
        fl_print_format("%[%s%s%]", main->error.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, byte_dump_long_width_s, main->context.set.notable);
        fl_print_format("%[' is specified, but no value is given.%]%c", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s[0]);

        funlockfile(main->error.to.stream);

        byte_dump_main_delete(main);
        return F_status_set_error(status);
      }
      else if (main->parameters[byte_dump_parameter_width].result == f_console_result_additional) {
        const f_array_length_t index = main->parameters[byte_dump_parameter_width].values.array[main->parameters[byte_dump_parameter_width].values.used - 1];
        const f_string_range_t range = macro_f_string_range_t_initialize(strlen(arguments->argv[index]));

        f_number_unsigned_t number = 0;

        status = fl_conversion_string_to_number_unsigned(arguments->argv[index], range, &number);

        if (F_status_is_error(status) || number < 1 || number >= 0xfb) {
          flockfile(main->error.to.stream);

          fl_print_format("%[%SThe parameter '%]", main->error.to.stream, main->context.set.error, main->error.prefix, main->context.set.error);
          fl_print_format("%[%s%s%]", main->error.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, byte_dump_long_width_s, main->context.set.notable);
          fl_print_format("%[' value can only be a number (inclusively) between %]", main->error.to.stream, main->context.set.error, main->context.set.error);
          fl_print_format("%[1%]", main->error.to.stream, main->context.set.notable, main->context.set.notable);
          fl_print_format(" %[and%] ", main->error.to.stream, main->context.set.error, main->context.set.error);
          fl_print_format("%[250%]", main->error.to.stream, main->context.set.notable, main->context.set.notable);
          fl_print_format("%[.%]%c", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s[0]);

          funlockfile(main->error.to.stream);

          byte_dump_main_delete(main);
          return F_status_set_error(status);
        }

        main->width = (uint8_t) number;
      }

      if (main->parameters[byte_dump_parameter_first].result == f_console_result_found) {
        flockfile(main->error.to.stream);

        fl_print_format("%[%SThe parameter '%]", main->error.to.stream, main->context.set.error, main->error.prefix, main->context.set.error);
        fl_print_format("%[%s%s%]", main->error.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, byte_dump_long_first_s, main->context.set.notable);
        fl_print_format("%[' is specified, but no value is given.%]%c", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s[0]);

        funlockfile(main->error.to.stream);

        byte_dump_main_delete(main);

        return F_status_set_error(status);
      }
      else if (main->parameters[byte_dump_parameter_first].result == f_console_result_additional) {
        const f_array_length_t index = main->parameters[byte_dump_parameter_first].values.array[main->parameters[byte_dump_parameter_first].values.used - 1];
        const f_string_range_t range = macro_f_string_range_t_initialize(strlen(arguments->argv[index]));

        f_number_unsigned_t number = 0;

        status = fl_conversion_string_to_number_unsigned(arguments->argv[index], range, &number);

        if (F_status_is_error(status) || number > F_number_t_size_unsigned_d) {
          flockfile(main->error.to.stream);

          fl_print_format("%[%SThe parameter '%]", main->error.to.stream, main->context.set.error, main->error.prefix, main->context.set.error);
          fl_print_format("%[%s%s%]", main->error.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, byte_dump_long_first_s, main->context.set.notable);
          fl_print_format("%[' value can only be a number (inclusively) between %]", main->error.to.stream, main->context.set.error, main->context.set.error);
          fl_print_format("%[0%]", main->error.to.stream, main->context.set.notable, main->context.set.notable);
          fl_print_format(" %[and%] ", main->error.to.stream, main->context.set.error, main->context.set.error);
          fl_print_format("%[%un%]", main->error.to.stream, main->context.set.notable, F_number_t_size_unsigned_d, main->context.set.notable);
          fl_print_format("%[.%]%c", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s[0]);

          funlockfile(main->error.to.stream);

          byte_dump_main_delete(main);

          return F_status_set_error(status);
        }

        main->first = number;
      }

      if (main->parameters[byte_dump_parameter_last].result == f_console_result_found) {
        flockfile(main->error.to.stream);

        fl_print_format("%[%SThe parameter '%]", main->error.to.stream, main->context.set.error, main->error.prefix, main->context.set.error);
        fl_print_format("%[%s%s%]", main->error.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, byte_dump_long_last_s, main->context.set.notable);
        fl_print_format("%[' is specified, but no value is given.%]%c", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s[0]);

        funlockfile(main->error.to.stream);

        byte_dump_main_delete(main);

        return F_status_set_error(status);
      }
      else if (main->parameters[byte_dump_parameter_last].result == f_console_result_additional) {
        const f_array_length_t index = main->parameters[byte_dump_parameter_last].values.array[main->parameters[byte_dump_parameter_last].values.used - 1];
        const f_string_range_t range = macro_f_string_range_t_initialize(strlen(arguments->argv[index]));

        f_number_unsigned_t number = 0;

        status = fl_conversion_string_to_number_unsigned(arguments->argv[index], range, &number);

        if (F_status_is_error(status) || number < 0 || number > F_number_t_size_unsigned_d) {
          flockfile(main->error.to.stream);

          fl_print_format("%[%SThe parameter '%]", main->error.to.stream, main->context.set.error, main->error.prefix, main->context.set.error);
          fl_print_format("%[%s%s%]", main->error.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, byte_dump_long_last_s, main->context.set.notable);
          fl_print_format("%[' value can only be a number (inclusively) between %]", main->error.to.stream, main->context.set.error, main->context.set.error);
          fl_print_format("%[0%]", main->error.to.stream, main->context.set.notable, main->context.set.notable);
          fl_print_format(" %[and%] ", main->error.to.stream, main->context.set.error, main->context.set.error);
          fl_print_format("%[%un%]", main->error.to.stream, main->context.set.notable, F_number_t_size_unsigned_d, main->context.set.notable);
          fl_print_format("%[.%]%c", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s[0]);

          funlockfile(main->error.to.stream);

          byte_dump_main_delete(main);

          return F_status_set_error(status);
        }

        main->last = number;
      }

      if (main->parameters[byte_dump_parameter_first].result == f_console_result_additional && main->parameters[byte_dump_parameter_last].result == f_console_result_additional) {
        if (main->first > main->last) {
          flockfile(main->error.to.stream);

          fl_print_format("%[%SThe parameter '%]", main->error.to.stream, main->context.set.error, main->error.prefix, main->context.set.error);
          fl_print_format("%[%s%s%]", main->error.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, byte_dump_long_first_s, main->context.set.notable);
          fl_print_format("%[' value cannot be greater than the parameter '%]", main->error.to.stream, main->context.set.error, main->context.set.error);
          fl_print_format("%[%s%s%]", main->error.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, byte_dump_long_last_s, main->context.set.notable);
          fl_print_format("%[' value.%]%c", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s[0]);

          funlockfile(main->error.to.stream);

          byte_dump_main_delete(main);

          return F_status_set_error(status);
        }

        // store last position as a relative offset from first instead of an absolute position.
        main->last = (main->last - main->first) + 1;
      }

      if (main->process_pipe) {
        f_file_t file = f_file_t_initialize;

        file.id = F_type_descriptor_input_d;
        file.stream = F_type_input_d;

        flockfile(main->output.to.stream);

        f_print_terminated(f_string_eol_s, main->output.to.stream);
        fl_print_format("%[Piped Byte Dump: (in ", main->output.to.stream, main->context.set.title);

        if (main->mode == byte_dump_mode_hexidecimal) {
          f_print_terminated("Hexidecimal", main->output.to.stream);
        }
        else if (main->mode == byte_dump_mode_duodecimal) {
          f_print_terminated("Duodecimal", main->output.to.stream);
        }
        else if (main->mode == byte_dump_mode_octal) {
          f_print_terminated("Octal", main->output.to.stream);
        }
        else if (main->mode == byte_dump_mode_binary) {
          f_print_terminated("Binary", main->output.to.stream);
        }
        else if (main->mode == byte_dump_mode_decimal) {
          f_print_terminated("Decimal", main->output.to.stream);
        }

        fl_print_format(")%]%c", main->output.to.stream, main->context.set.title, f_string_eol_s[0]);

        funlockfile(main->output.to.stream);

        status = byte_dump_file(main, 0, file);

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

            status = f_file_exists(arguments->argv[main->remaining.array[counter]]);

            if (status == F_false) {
              status = F_status_set_error(F_file_found_not);
            }

            if (F_status_is_error(status)) {
              if (missing_files == F_none) {
                missing_files = status;
              }

              fll_error_file_print(main->error, F_status_set_fine(status), "f_file_exists", F_true, arguments->argv[main->remaining.array[counter]], "open", fll_error_file_type_file);
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

          status = f_file_stream_open(arguments->argv[main->remaining.array[counter]], 0, &file);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_open", F_true, arguments->argv[main->remaining.array[counter]], "open", fll_error_file_type_file);

            byte_dump_main_delete(main);

            return status;
          }

          flockfile(main->output.to.stream);

          f_print_terminated(f_string_eol_s, main->output.to.stream);
          fl_print_format("%[Byte Dump of: %]%[", main->output.to.stream, main->context.set.title, main->context.set.title, main->context.set.notable);
          fl_print_format("%S%] %[(in ", main->output.to.stream, arguments->argv[main->remaining.array[counter]], main->context.set.notable, main->context.set.title);

          if (main->mode == byte_dump_mode_hexidecimal) {
            f_print_terminated("Hexidecimal", main->output.to.stream);
          }
          else if (main->mode == byte_dump_mode_duodecimal) {
            f_print_terminated("Duodecimal", main->output.to.stream);
          }
          else if (main->mode == byte_dump_mode_octal) {
            f_print_terminated("Octal", main->output.to.stream);
          }
          else if (main->mode == byte_dump_mode_binary) {
            f_print_terminated("Binary", main->output.to.stream);
          }
          else if (main->mode == byte_dump_mode_decimal) {
            f_print_terminated("Decimal", main->output.to.stream);
          }

          fl_print_format(")%]%c", main->output.to.stream, main->context.set.title, f_string_eol_s[0]);

          funlockfile(main->output.to.stream);

          status = byte_dump_file(main, arguments->argv[main->remaining.array[counter]], file);

          f_file_stream_close(F_true, &file);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_interrupt) {

              // Ensure a newline is always put at the end of the program execution, unless in quiet mode.
              if (main->output.verbosity != f_console_verbosity_quiet) {
                fflush(main->output.to.stream);

                fll_print_terminated(f_string_eol_s, main->output.to.stream);
              }
            }
            else {
              if (main->error.verbosity != f_console_verbosity_quiet) {
                fll_error_file_print(main->error, F_status_set_fine(status), "byte_dump_file", F_true, arguments->argv[main->remaining.array[counter]], "process", fll_error_file_type_file);
              }
            }

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
      fll_print_format("%[%SYou failed to specify one or more filenames.%]%c", main->error.to.stream, main->context.set.error, main->error.prefix, main->context.set.error, f_string_eol_s[0]);
      status = F_status_set_error(F_parameter);
    }

    byte_dump_main_delete(main);

    return status;
  }
#endif // _di_byte_dump_main_

#ifndef _di_byte_dump_main_delete_
  f_status_t byte_dump_main_delete(byte_dump_main_t * const main) {

    for (f_array_length_t i = 0; i < byte_dump_total_parameters_d; ++i) {

      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations_sub);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].values);
    } // for

    macro_f_array_lengths_t_delete_simple(main->remaining);

    macro_f_color_context_t_delete_simple(main->context);
    macro_f_color_context_t_clear(main->context)

    return F_none;
  }
#endif // _di_byte_dump_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif
