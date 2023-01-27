#include "byte_dump.h"
#include "private-common.h"
#include "private-byte_dump.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_byte_dump_print_copyright_
  f_status_t byte_dump_print_copyright(const f_file_t file, const bool full) {

    flockfile(file.stream);

    fl_print_format("%rCopyright © 2007-2023 Kevin Day.%r", file.stream, f_string_eol_s, f_string_eol_s);

    #ifndef _di_detailed_copyright_
      if (full) {
        fl_print_format("%rThis program comes with ABSOLUTELY NO WARRANTY.%r", file.stream, f_string_eol_s, f_string_eol_s);
        fl_print_format("This is free software, and you are welcome to modify or redistribute in accordance to the license.%r", file.stream, f_string_eol_s);
      }
    #endif // _di_detailed_copyright_

    fl_print_format("%rSource code license lgpl-2.1-or-later.%r", file.stream, f_string_eol_s, f_string_eol_s);
    fl_print_format("Standard and specification license open-standard-license-1.0.%r", file.stream, f_string_eol_s);
    fl_print_format("Documentation license cc-by-sa-4.0.%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    funlockfile(file.stream);

    return F_none;
  }
#endif // _di_byte_dump_print_copyright_

#ifndef _di_byte_dump_print_help_
  f_status_t byte_dump_print_help(const f_file_t file, const f_color_context_t context) {

    flockfile(file.stream);

    fll_program_print_help_header(file, context, byte_dump_program_name_long_s, byte_dump_program_version_s);

    fll_program_print_help_option(file, context, f_console_standard_short_help_s, f_console_standard_long_help_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "     Print this help message.");
    fll_program_print_help_option(file, context, f_console_standard_short_copyright_s, f_console_standard_long_copyright_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "Print the copyright.");
    fll_program_print_help_option(file, context, f_console_standard_short_dark_s, f_console_standard_long_dark_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "     Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_light_s, f_console_standard_long_light_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Do not print using color.");
    fll_program_print_help_option(file, context, f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Decrease verbosity, silencing most output.");
    fll_program_print_help_option(file, context, f_console_standard_short_error_s, f_console_standard_long_error_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Decrease verbosity, using only error output.");
    fll_program_print_help_option(file, context, f_console_standard_short_normal_s, f_console_standard_long_normal_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Set verbosity to normal.");
    fll_program_print_help_option(file, context, f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "  Increase verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_debug_s, f_console_standard_long_debug_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Enable debugging, significantly increasing verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_version_s, f_console_standard_long_version_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "  Print only the version number.");

    f_print_dynamic_raw(f_string_eol_s, file.stream);

    fll_program_print_help_option(file, context, byte_dump_short_binary_s, byte_dump_long_binary_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "     Display binary representation.");
    fll_program_print_help_option(file, context, byte_dump_short_decimal_s, byte_dump_long_decimal_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Display decimal representation.");
    fll_program_print_help_option(file, context, byte_dump_short_duodecimal_s, byte_dump_long_duodecimal_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Display duodecimal representation.");
    fll_program_print_help_option(file, context, byte_dump_short_hexidecimal_s, byte_dump_long_hexidecimal_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Display hexadecimal representation.");
    fll_program_print_help_option(file, context, byte_dump_short_octal_s, byte_dump_long_octal_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "      Display octal representation.");
    fll_program_print_help_option(file, context, byte_dump_short_unicode_s, byte_dump_long_unicode_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Display using Unicode representation for valid Unicode (like: U+0000).");

    f_print_dynamic_raw(f_string_eol_s, file.stream);

    fll_program_print_help_option(file, context, byte_dump_short_first_s, byte_dump_long_first_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Start reading at this byte offset.");
    fll_program_print_help_option(file, context, byte_dump_short_last_s, byte_dump_long_last_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Stop reading at this (inclusive) byte offset.");

    f_print_dynamic_raw(f_string_eol_s, file.stream);

    fll_program_print_help_option(file, context, byte_dump_short_narrow_s, byte_dump_long_narrow_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "     Use narrow display, resulting in 1*width reducing size of the text columns.");
    fll_program_print_help_option(file, context, byte_dump_short_placeholder_s, byte_dump_long_placeholder_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Use a placeholder character instead of a space for placeholders.");
    fll_program_print_help_option(file, context, byte_dump_short_text_s, byte_dump_long_text_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "       Include a column of text when displaying the bytes.");
    fll_program_print_help_option(file, context, byte_dump_short_wide_s, byte_dump_long_wide_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "       Use wide display, resulting in 2*width allowing for space for wide characters in the text columns.");
    fll_program_print_help_option(file, context, byte_dump_short_width_s, byte_dump_long_width_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "      Set number of columns of Bytes to display.");

    f_print_dynamic_raw(f_string_eol_s, file.stream);
    f_print_dynamic_raw(f_string_eol_s, file.stream);

    fl_print_format(" %[Special Options:%] ", file.stream, context.set.important, context.set.important);

    fll_program_print_help_option_long(file, context, byte_dump_long_normal_s, f_console_symbol_long_enable_s, " Display UTF-8 symbols for ASCII control codes.");
    fll_program_print_help_option_long(file, context, byte_dump_long_simple_s, f_console_symbol_long_enable_s, " Display spaces for ASCII control codes.");
    fll_program_print_help_option_long(file, context, byte_dump_long_classic_s, f_console_symbol_long_enable_s, "Display periods for ASCII control codes.");

    fll_program_print_help_usage(file, context, byte_dump_program_name_s, fll_program_parameter_filenames_s);

    fl_print_format("  When using the %[%r%r%] option, some UTF-8 characters may be replaced by your instance and cause display alignment issues.%r%r", file.stream, context.set.notable, f_console_symbol_long_enable_s, byte_dump_long_text_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  Special UTF-8 characters and non-spacing UTF-8 characters may be replaced with a space (or a placeholder when the %[%r%r%] option is used).%r%r", file.stream, context.set.notable, f_console_symbol_long_enable_s, byte_dump_long_placeholder_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  UTF-8 \"Combining\" characters might have a space appended to allow a proper display but this may cause copy and paste issues.%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When %[%r%r%] is used, any UTF-8 sequences will still be printed in full should any part is found within the requested range.%r%r", file.stream, context.set.notable, f_console_symbol_long_enable_s, byte_dump_long_last_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When using the %[%r%r%] option, invalid Unicode will fallback to being displayed using one of the other modes.%r%r", file.stream, context.set.notable, f_console_symbol_long_enable_s, byte_dump_long_unicode_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    fflush(file.stream);
    funlockfile(file.stream);

    return F_none;
  }
#endif // _di_byte_dump_print_help_

#ifndef _di_byte_dump_main_
  f_status_t byte_dump_main(fll_program_data_t * const main, const f_console_arguments_t *arguments) {

    f_status_t status = F_none;

    // Identify priority of color parameters.
    {
      f_console_parameter_id_t ids[3] = { byte_dump_parameter_no_color_e, byte_dump_parameter_light_e, byte_dump_parameter_dark_e };
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
        fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process", F_true);

        return F_status_set_error(status);
      }
    }

    // Identify priority of verbosity related parameters.
    {
      f_console_parameter_id_t ids[5] = { byte_dump_parameter_verbosity_quiet_e, byte_dump_parameter_verbosity_error_e, byte_dump_parameter_verbosity_normal_e, byte_dump_parameter_verbosity_verbose_e, byte_dump_parameter_verbosity_debug_e };
      f_console_parameter_id_t choice = 0;
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 5);

      status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", F_true);

        return status;
      }

      if (choice == byte_dump_parameter_verbosity_quiet_e) {
        main->output.verbosity = f_console_verbosity_quiet_e;
        main->error.verbosity = f_console_verbosity_quiet_e;
        main->warning.verbosity = f_console_verbosity_quiet_e;
      }
      else if (choice == byte_dump_parameter_verbosity_error_e) {
        main->output.verbosity = f_console_verbosity_error_e;
        main->error.verbosity = f_console_verbosity_error_e;
        main->warning.verbosity = f_console_verbosity_error_e;
      }
      else if (choice == byte_dump_parameter_verbosity_normal_e) {
        main->output.verbosity = f_console_verbosity_normal_e;
        main->error.verbosity = f_console_verbosity_normal_e;
        main->warning.verbosity = f_console_verbosity_normal_e;
      }
      else if (choice == byte_dump_parameter_verbosity_verbose_e) {
        main->output.verbosity = f_console_verbosity_verbose_e;
        main->error.verbosity = f_console_verbosity_verbose_e;
        main->warning.verbosity = f_console_verbosity_verbose_e;
      }
      else if (choice == byte_dump_parameter_verbosity_debug_e) {
        main->output.verbosity = f_console_verbosity_debug_e;
        main->error.verbosity = f_console_verbosity_debug_e;
        main->warning.verbosity = f_console_verbosity_debug_e;
      }
    }

    byte_dump_data_t data = byte_dump_data_t_initialize;
    data.main = main;
    data.argv = main->parameters.arguments.array;

    // Identify priority of mode parameters.
    {
      f_console_parameter_id_t ids[5] = { byte_dump_parameter_hexidecimal_e, byte_dump_parameter_duodecimal_e, byte_dump_parameter_octal_e, byte_dump_parameter_binary_e, byte_dump_parameter_decimal_e };
      f_console_parameter_id_t choice = byte_dump_parameter_hexidecimal_e;
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 5);

      status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", F_true);

        return F_status_set_error(status);
      }

      if (choice == byte_dump_parameter_hexidecimal_e) {
        data.mode = byte_dump_mode_hexidecimal_e;
      }
      else if (choice == byte_dump_parameter_duodecimal_e) {
        data.mode = byte_dump_mode_duodecimal_e;
      }
      else if (choice == byte_dump_parameter_octal_e) {
        data.mode = byte_dump_mode_octal_e;
      }
      else if (choice == byte_dump_parameter_binary_e) {
        data.mode = byte_dump_mode_binary_e;
      }
      else if (choice == byte_dump_parameter_decimal_e) {
        data.mode = byte_dump_mode_decimal_e;
      }
    }

    // Identify priority of presentation parameters.
    {
      f_console_parameter_id_t ids[3] = { byte_dump_parameter_normal_e, byte_dump_parameter_simple_e, byte_dump_parameter_classic_e };
      f_console_parameter_id_t choice = byte_dump_parameter_normal_e;
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 3);

      status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", F_true);

        return F_status_set_error(status);
      }

      if (choice == byte_dump_parameter_normal_e) {
        data.presentation = byte_dump_presentation_normal_e;
      }
      else if (choice == byte_dump_parameter_simple_e) {
        data.presentation = byte_dump_presentation_simple_e;
      }
      else if (choice == byte_dump_parameter_classic_e) {
        data.presentation = byte_dump_presentation_classic_e;
      }
    }

    // Identify priority of narrow and wide parameters.
    {
      f_console_parameter_id_t ids[2] = { byte_dump_parameter_narrow_e, byte_dump_parameter_wide_e };
      f_console_parameter_id_t choice = byte_dump_parameter_wide_e;
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 2);

      status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", F_true);

        return F_status_set_error(status);
      }

      if (choice == byte_dump_parameter_narrow_e) {
        if (data.options & byte_dump_option_wide_d) {
          data.options -= byte_dump_option_wide_d;
        }
      }
      else if (choice == byte_dump_parameter_wide_e) {
        data.options |= byte_dump_option_wide_d;
      }
    }

    if (main->parameters.array[byte_dump_parameter_help_e].result == f_console_result_found_e) {
      byte_dump_print_help(main->output.to, main->context);

      return F_none;
    }

    if (main->parameters.array[byte_dump_parameter_version_e].result == f_console_result_found_e) {
      fll_program_print_version(main->output.to, byte_dump_program_version_s);

      return F_none;
    }

    if (main->parameters.array[byte_dump_parameter_copyright_e].result == f_console_result_found_e) {
      byte_dump_print_copyright(main->output.to, main->output.verbosity > f_console_verbosity_error_e);

      return F_none;
    }

    status = F_none;

    if (main->parameters.remaining.used || main->process_pipe) {
      if (main->parameters.array[byte_dump_parameter_width_e].result == f_console_result_found_e) {
        flockfile(main->error.to.stream);

        fl_print_format("%[%QThe parameter '%]", main->error.to.stream, main->context.set.error, main->error.prefix, main->context.set.error);
        fl_print_format("%[%r%r%]", main->error.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, byte_dump_long_width_s, main->context.set.notable);
        fl_print_format("%[' is specified, but no value is given.%]%r", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

        funlockfile(main->error.to.stream);

        return F_status_set_error(F_parameter);
      }

      if (main->parameters.array[byte_dump_parameter_width_e].result == f_console_result_additional_e) {
        const f_array_length_t index = main->parameters.array[byte_dump_parameter_width_e].values.array[main->parameters.array[byte_dump_parameter_width_e].values.used - 1];
        f_number_unsigned_t number = 0;

        status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, data.argv[index], &number);

        if (F_status_is_error(status) || number < 1 || number >= 0xfb) {
          flockfile(main->error.to.stream);

          fl_print_format("%[%QThe parameter '%]", main->error.to.stream, main->context.set.error, main->error.prefix, main->context.set.error);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, byte_dump_long_width_s, main->context.set.notable);
          fl_print_format("%[' value can only be a number (inclusively) between %]", main->error.to.stream, main->context.set.error, main->context.set.error);
          fl_print_format("%[1%]", main->error.to.stream, main->context.set.notable, main->context.set.notable);
          fl_print_format(" %[and%] ", main->error.to.stream, main->context.set.error, main->context.set.error);
          fl_print_format("%[250%]", main->error.to.stream, main->context.set.notable, main->context.set.notable);
          fl_print_format("%[.%]%r", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

          funlockfile(main->error.to.stream);

          if (F_status_is_error(status)) return status;

          return F_status_set_error(F_parameter);
        }

        data.width = (uint8_t) number;
      }

      if (main->parameters.array[byte_dump_parameter_first_e].result == f_console_result_found_e) {
        flockfile(main->error.to.stream);

        fl_print_format("%[%QThe parameter '%]", main->error.to.stream, main->context.set.error, main->error.prefix, main->context.set.error);
        fl_print_format("%[%r%r%]", main->error.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, byte_dump_long_first_s, main->context.set.notable);
        fl_print_format("%[' is specified, but no value is given.%]%r", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

        funlockfile(main->error.to.stream);

        return F_status_set_error(F_parameter);
      }

      if (main->parameters.array[byte_dump_parameter_first_e].result == f_console_result_additional_e) {
        const f_array_length_t index = main->parameters.array[byte_dump_parameter_first_e].values.array[main->parameters.array[byte_dump_parameter_first_e].values.used - 1];
        f_number_unsigned_t number = 0;

        status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, data.argv[index], &number);

        if (F_status_is_error(status) || number > F_number_t_size_unsigned_d) {
          flockfile(main->error.to.stream);

          fl_print_format("%[%QThe parameter '%]", main->error.to.stream, main->context.set.error, main->error.prefix, main->context.set.error);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, byte_dump_long_first_s, main->context.set.notable);
          fl_print_format("%[' value can only be a number (inclusively) between %]", main->error.to.stream, main->context.set.error, main->context.set.error);
          fl_print_format("%[0%]", main->error.to.stream, main->context.set.notable, main->context.set.notable);
          fl_print_format(" %[and%] ", main->error.to.stream, main->context.set.error, main->context.set.error);
          fl_print_format("%[%un%]", main->error.to.stream, main->context.set.notable, F_number_t_size_unsigned_d, main->context.set.notable);
          fl_print_format("%[.%]%r", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

          funlockfile(main->error.to.stream);

          if (F_status_is_error(status)) return status;

          return F_status_set_error(F_parameter);
        }

        data.first = number;
      }

      if (main->parameters.array[byte_dump_parameter_last_e].result == f_console_result_found_e) {
        flockfile(main->error.to.stream);

        fl_print_format("%[%QThe parameter '%]", main->error.to.stream, main->context.set.error, main->error.prefix, main->context.set.error);
        fl_print_format("%[%r%r%]", main->error.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, byte_dump_long_last_s, main->context.set.notable);
        fl_print_format("%[' is specified, but no value is given.%]%r", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

        funlockfile(main->error.to.stream);

        return F_status_set_error(F_parameter);
      }

      if (main->parameters.array[byte_dump_parameter_last_e].result == f_console_result_additional_e) {
        const f_array_length_t index = main->parameters.array[byte_dump_parameter_last_e].values.array[main->parameters.array[byte_dump_parameter_last_e].values.used - 1];
        f_number_unsigned_t number = 0;

        status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, data.argv[index], &number);

        if (F_status_is_error(status) || number < 0 || number > F_number_t_size_unsigned_d) {
          flockfile(main->error.to.stream);

          fl_print_format("%[%QThe parameter '%]", main->error.to.stream, main->context.set.error, main->error.prefix, main->context.set.error);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, byte_dump_long_last_s, main->context.set.notable);
          fl_print_format("%[' value can only be a number (inclusively) between %]", main->error.to.stream, main->context.set.error, main->context.set.error);
          fl_print_format("%[0%]", main->error.to.stream, main->context.set.notable, main->context.set.notable);
          fl_print_format(" %[and%] ", main->error.to.stream, main->context.set.error, main->context.set.error);
          fl_print_format("%[%un%]", main->error.to.stream, main->context.set.notable, F_number_t_size_unsigned_d, main->context.set.notable);
          fl_print_format("%[.%]%r", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

          funlockfile(main->error.to.stream);

          if (F_status_is_error(status)) return status;

          return F_status_set_error(F_parameter);
        }

        data.last = number;
      }

      if (main->parameters.array[byte_dump_parameter_first_e].result == f_console_result_additional_e && main->parameters.array[byte_dump_parameter_last_e].result == f_console_result_additional_e) {
        if (data.first > data.last) {
          flockfile(main->error.to.stream);

          fl_print_format("%[%QThe parameter '%]", main->error.to.stream, main->context.set.error, main->error.prefix, main->context.set.error);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, byte_dump_long_first_s, main->context.set.notable);
          fl_print_format("%[' value cannot be greater than the parameter '%]", main->error.to.stream, main->context.set.error, main->context.set.error);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, byte_dump_long_last_s, main->context.set.notable);
          fl_print_format("%[' value.%]%r", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

          funlockfile(main->error.to.stream);

          return F_status_set_error(F_parameter);
        }

        // Store last position as a relative offset from first instead of an absolute position.
        data.last = (data.last - data.first) + 1;
      }

      if (main->process_pipe) {
        f_file_t file = f_file_t_initialize;

        file.id = F_type_descriptor_input_d;
        file.stream = F_type_input_d;

        flockfile(main->output.to.stream);

        f_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
        fl_print_format("%[Piped " BYTE_DUMP_program_name_long_s ": (in ", main->output.to.stream, main->context.set.title);

        if (data.mode == byte_dump_mode_hexidecimal_e) {
          f_print_dynamic_raw(byte_dump_print_strings_hexidecimal_s, main->output.to.stream);
        }
        else if (data.mode == byte_dump_mode_duodecimal_e) {
          f_print_dynamic_raw(byte_dump_print_strings_duodecimal_s, main->output.to.stream);
        }
        else if (data.mode == byte_dump_mode_octal_e) {
          f_print_dynamic_raw(byte_dump_print_strings_octal_s, main->output.to.stream);
        }
        else if (data.mode == byte_dump_mode_binary_e) {
          f_print_dynamic_raw(byte_dump_print_strings_binary_s, main->output.to.stream);
        }
        else if (data.mode == byte_dump_mode_decimal_e) {
          f_print_dynamic_raw(byte_dump_print_strings_decimal_s, main->output.to.stream);
        }

        fl_print_format(")%]%r", main->output.to.stream, main->context.set.title, f_string_eol_s);

        funlockfile(main->output.to.stream);

        status = byte_dump_file(&data, f_string_empty_s, file);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "byte_dump_file", F_true);

          return status;
        }
      }

      if (main->parameters.remaining.used) {

        // Pre-process remaining arguments to ensure that they all files exist before processing.
        {
          f_status_t missing_files = F_none;

          for (f_array_length_t counter = 0; counter < main->parameters.remaining.used; ++counter) {

            status = f_file_exists(data.argv[main->parameters.remaining.array[counter]], F_true);

            if (status == F_false) {
              status = F_status_set_error(F_file_found_not);
            }

            if (F_status_is_error(status)) {
              if (missing_files == F_none) {
                missing_files = status;
              }

              fll_error_file_print(main->error, F_status_set_fine(status), "f_file_exists", F_true, data.argv[main->parameters.remaining.array[counter]], f_file_operation_open_s, fll_error_file_type_file_e);
            }
          } // for

          if (missing_files != F_none) {
            status = F_status_set_error(missing_files);

            return status;
          }
        }

        f_file_t file = f_file_t_initialize;

        for (f_array_length_t counter = 0; counter < main->parameters.remaining.used; ++counter) {

          status = f_file_stream_open(data.argv[main->parameters.remaining.array[counter]], f_string_empty_s, &file);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_open", F_true, data.argv[main->parameters.remaining.array[counter]], f_file_operation_open_s, fll_error_file_type_file_e);

            return status;
          }

          flockfile(main->output.to.stream);

          fl_print_format("%r%[" BYTE_DUMP_program_name_long_s " of: %]%[", main->output.to.stream, f_string_eol_s, main->context.set.title, main->context.set.title, main->context.set.notable);
          fl_print_format("%Q%] %[(in ", main->output.to.stream, data.argv[main->parameters.remaining.array[counter]], main->context.set.notable, main->context.set.title);

          if (data.mode == byte_dump_mode_hexidecimal_e) {
            f_print_dynamic_raw(byte_dump_print_strings_hexidecimal_s, main->output.to.stream);
          }
          else if (data.mode == byte_dump_mode_duodecimal_e) {
            f_print_dynamic_raw(byte_dump_print_strings_duodecimal_s, main->output.to.stream);
          }
          else if (data.mode == byte_dump_mode_octal_e) {
            f_print_dynamic_raw(byte_dump_print_strings_octal_s, main->output.to.stream);
          }
          else if (data.mode == byte_dump_mode_binary_e) {
            f_print_dynamic_raw(byte_dump_print_strings_binary_s, main->output.to.stream);
          }
          else if (data.mode == byte_dump_mode_decimal_e) {
            f_print_dynamic_raw(byte_dump_print_strings_decimal_s, main->output.to.stream);
          }

          fl_print_format(")%]%r", main->output.to.stream, main->context.set.title, f_string_eol_s);

          funlockfile(main->output.to.stream);

          status = byte_dump_file(&data, data.argv[main->parameters.remaining.array[counter]], file);

          f_file_stream_close(F_true, &file);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_interrupt) {

              // Ensure a newline is always put at the end of the program execution, unless in quiet mode.
              if (main->output.verbosity != f_console_verbosity_quiet_e) {
                fflush(main->output.to.stream);

                fll_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
              }
            }
            else {
              if (main->error.verbosity != f_console_verbosity_quiet_e) {
                fll_error_file_print(main->error, F_status_set_fine(status), "byte_dump_file", F_true, data.argv[main->parameters.remaining.array[counter]], f_file_operation_process_s, fll_error_file_type_file_e);
              }
            }

            return status;
          }
        } // for
      }
      else {
        status = F_false;
      }
    }
    else {
      fll_print_format("%r%[%QYou failed to specify one or more filenames.%]%r", main->error.to.stream, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error, f_string_eol_s);

      status = F_status_set_error(F_parameter);
    }

    return status;
  }
#endif // _di_byte_dump_main_

#ifdef __cplusplus
} // extern "C"
#endif
