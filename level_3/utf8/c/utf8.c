#include "utf8.h"
#include "private-common.h"
#include "private-utf8.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_print_help_
  f_status_t utf8_print_help(const f_file_t file, const f_color_context_t context) {

    flockfile(file.stream);

    fll_program_print_help_header(file, context, utf8_program_name_long_s, utf8_version_s);

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

    fll_program_print_help_option(file, context, utf8_short_from_binary_s, utf8_long_from_binary_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   The expected input format is binary (character data).");
    fll_program_print_help_option(file, context, utf8_short_from_codepoint_s, utf8_long_from_codepoint_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "The expected input format is codepoint (such as U+0000).");
    fll_program_print_help_option(file, context, utf8_short_from_file_s, utf8_long_from_file_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "     Use the given file as the input source.");

    f_print_character(f_string_eol_s[0], file.stream);

    fll_program_print_help_option(file, context, utf8_short_to_binary_s, utf8_long_to_binary_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   The output format is binary (character data).");
    fll_program_print_help_option(file, context, utf8_short_to_codepoint_s, utf8_long_to_codepoint_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "The output format is codepoint (such as U+0000).");
    fll_program_print_help_option(file, context, utf8_short_to_file_s, utf8_long_to_file_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "     Use the given file as the output destination.");

    f_print_character(f_string_eol_s[0], file.stream);

    fll_program_print_help_option(file, context, utf8_short_headers_s, utf8_long_headers_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "      Print headers for each section (pipe, file, or parameter).");
    fll_program_print_help_option(file, context, utf8_short_strip_invalid_s, utf8_long_strip_invalid_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Strip invalid Unicode characters.");
    fll_program_print_help_option(file, context, utf8_short_verify_s, utf8_long_verify_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "       Only perform verification of valid sequences.");

    f_print_character(f_string_eol_s[0], file.stream);
    f_print_character(f_string_eol_s[0], file.stream);

    fll_program_print_help_usage(file, context, utf8_program_name_s, "filename(s)");

    fl_print_format("  The default behavior is to assume the expected input is binary from the command line to be output to the screen as codepoints.%c%c", file.stream, f_string_eol_s[0], f_string_eol_s[0]);

    fl_print_format("  Multiple input sources are allowed but only a single output destination is allowed.%c%c", file.stream, f_string_eol_s[0], f_string_eol_s[0]);

    fl_print_format("  When using the parameter '%[%s%s%]', only invalid data is printed and 0 is returned if valid or 1 is returned if invalid.%c", file.stream, context.set.notable, f_console_symbol_long_enable_s, utf8_long_verify_s, context.set.notable, f_string_eol_s[0]);

    funlockfile(file.stream);

    return F_none;
  }
#endif // _di_utf8_print_help_

#ifndef _di_utf8_main_
  f_status_t utf8_main(utf8_main_t * const main, const f_console_arguments_t *arguments) {

    f_status_t status = F_none;

    {
      const f_console_parameters_t parameters = macro_f_console_parameters_t_initialize(main->parameters, utf8_total_parameters_d);

      // Identify priority of color parameters.
      {
        f_console_parameter_id_t ids[3] = { utf8_parameter_no_color, utf8_parameter_light, utf8_parameter_dark };
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

          utf8_main_delete(main);

          return F_status_set_error(status);
        }
      }

      // Identify priority of verbosity related parameters.
      {
        f_console_parameter_id_t ids[4] = { utf8_parameter_verbosity_quiet, utf8_parameter_verbosity_normal, utf8_parameter_verbosity_verbose, utf8_parameter_verbosity_debug };
        f_console_parameter_id_t choice = 0;
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 4);

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", F_true);

          utf8_main_delete(main);

          return status;
        }

        if (choice == utf8_parameter_verbosity_quiet) {
          main->output.verbosity = f_console_verbosity_quiet;
          main->error.verbosity = f_console_verbosity_quiet;
          main->warning.verbosity = f_console_verbosity_quiet;
        }
        else if (choice == utf8_parameter_verbosity_normal) {
          main->output.verbosity = f_console_verbosity_normal;
          main->error.verbosity = f_console_verbosity_normal;
          main->warning.verbosity = f_console_verbosity_normal;
        }
        else if (choice == utf8_parameter_verbosity_verbose) {
          main->output.verbosity = f_console_verbosity_verbose;
          main->error.verbosity = f_console_verbosity_verbose;
          main->warning.verbosity = f_console_verbosity_verbose;
        }
        else if (choice == utf8_parameter_verbosity_debug) {
          main->output.verbosity = f_console_verbosity_debug;
          main->error.verbosity = f_console_verbosity_debug;
          main->warning.verbosity = f_console_verbosity_debug;
        }
      }

      // Identify and prioritize from mode parameters.
      {
        f_console_parameter_id_t ids[4] = { utf8_parameter_from_binary, utf8_parameter_from_codepoint };
        f_console_parameter_id_t choice = 0;
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 2);

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", F_true);

          utf8_main_delete(main);

          return status;
        }

        if (choice == utf8_parameter_from_binary) {
          if (main->mode & utf8_mode_from_codepoint_d) {
            main->mode -= utf8_mode_from_codepoint_d;
          }

          main->mode |= utf8_mode_from_binary_d;
        }
        else if (choice == utf8_parameter_from_codepoint) {
          if (main->mode & utf8_mode_from_binary_d) {
            main->mode -= utf8_mode_from_binary_d;
          }

          main->mode |= utf8_mode_from_codepoint_d;
        }
      }

      // Identify and prioritize to mode parameters.
      {
        f_console_parameter_id_t ids[4] = { utf8_parameter_to_binary, utf8_parameter_to_codepoint };
        f_console_parameter_id_t choice = 0;
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 2);

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", F_true);

          utf8_main_delete(main);

          return status;
        }

        if (choice == utf8_parameter_to_binary) {
          if (main->mode & utf8_mode_to_codepoint_d) {
            main->mode -= utf8_mode_to_codepoint_d;
          }

          main->mode |= utf8_mode_to_binary_d;
        }
        else if (choice == utf8_parameter_to_codepoint) {
          if (main->mode & utf8_mode_to_binary_d) {
            main->mode -= utf8_mode_to_binary_d;
          }

          main->mode |= utf8_mode_to_codepoint_d;
        }
      }

      status = F_none;
    }

    if (main->parameters[utf8_parameter_help].result == f_console_result_found) {
      utf8_print_help(main->output.to, main->context);

      utf8_main_delete(main);
      return F_none;
    }

    if (main->parameters[utf8_parameter_version].result == f_console_result_found) {
      fll_program_print_version(main->output.to, utf8_version_s);

      utf8_main_delete(main);
      return F_none;
    }

    if (main->parameters[utf8_parameter_from_binary].result == f_console_result_found) {
      if (main->parameters[utf8_parameter_from_codepoint].result == f_console_result_found) {
        utf8_print_error_parameter_conflict(main, utf8_long_from_binary_s, utf8_long_from_codepoint_s);

        status = F_status_set_error(F_parameter);
      }
    }

    if (F_status_is_error_not(status) && main->parameters[utf8_parameter_to_binary].result == f_console_result_found) {
      if (main->parameters[utf8_parameter_to_codepoint].result == f_console_result_found) {
        utf8_print_error_parameter_conflict(main, utf8_long_to_binary_s, utf8_long_to_codepoint_s);

        status = F_status_set_error(F_parameter);
      }
    }

    if (main->parameters[utf8_parameter_verify].result == f_console_result_found) {
      if (main->parameters[utf8_parameter_strip_invalid].result == f_console_result_found) {
        utf8_print_error_parameter_conflict(main, utf8_long_verify_s, utf8_long_strip_invalid_s);

        status = F_status_set_error(F_parameter);
      }
    }

    if (F_status_is_error_not(status)) {
      if (main->parameters[utf8_parameter_from_file].result == f_console_result_additional) {
        f_array_length_t i = 0;
        f_array_length_t index = 0;

        for (; i < main->parameters[utf8_parameter_from_file].values.used; ++i) {

          index = main->parameters[utf8_parameter_from_file].values.array[i];

          if (arguments->argv[index][0]) {
            if (!f_file_exists(arguments->argv[index])) {
              utf8_print_error_parameter_file_not_found(main, F_true, arguments->argv[index]);

              if (F_status_is_error_not(status)) {
                status = F_status_set_error(F_file_found_not);
              }
            }
          }
          else {
            utf8_print_error_parameter_file_name_empty(main, index);

            if (F_status_is_error_not(status)) {
              status = F_status_set_error(F_parameter);
            }
          }
        } // for
      }
      else if (main->parameters[utf8_parameter_from_file].result == f_console_result_found) {
        utf8_print_error_no_value(main, utf8_long_from_file_s);

        status = F_status_set_error(F_parameter);
      }
    }

    bool valid = F_true;

    if (F_status_is_error_not(status)) {
      if (main->parameters[utf8_parameter_to_file].result == f_console_result_additional) {
        if (main->parameters[utf8_parameter_to_file].values.used > 1) {
          utf8_print_error_parameter_file_to_too_many(main);

          status = F_status_set_error(F_parameter);
        }
        else {
          const f_array_length_t index = main->parameters[utf8_parameter_to_file].values.array[0];

          if (arguments->argv[index][0]) {
            if (!f_file_exists(arguments->argv[index])) {
              utf8_print_error_parameter_file_not_found(main, F_false, arguments->argv[index]);

              status = F_status_set_error(F_file_found_not);
            }
          }
          else {
            utf8_print_error_parameter_file_name_empty(main, index);

            status = F_status_set_error(F_parameter);
          }
        }
      }
      else if (main->parameters[utf8_parameter_to_file].result == f_console_result_found) {
        utf8_print_error_no_value(main, utf8_long_to_file_s);

        status = F_status_set_error(F_parameter);
      }
      else {
        main->destination = main->output.to;
      }
    }

    if (F_status_is_error_not(status)) {
      if (main->parameters[utf8_parameter_from_file].result == f_console_result_none && !(main->process_pipe || main->remaining.used)) {
        utf8_print_error_no_from(main);

        status = F_status_set_error(F_parameter);
      }
    }

    if (F_status_is_error_not(status)) {
      status = F_none;

      if (main->process_pipe) {
        f_file_t file = f_file_t_initialize;

        file.id = F_type_descriptor_input_d;
        file.stream = F_type_input_d;

        utf8_print_section_header_pipe(main);

        if (main->mode & utf8_mode_from_binary_d) {
          status = utf8_process_file_binary(main, file);
        }
        else {
          status = utf8_process_file_codepoint(main, file);
        }

        if (F_status_is_error(status)) {
          fll_error_file_print(main->error, F_status_set_fine(status), main->mode & utf8_mode_from_binary_d ? "utf8_process_file_binary" : "utf8_process_file_codepoint", F_true, 0, utf8_string_process_s, fll_error_file_type_pipe);
        }
      }

      if (F_status_is_error_not(status) && status != F_signal && main->parameters[utf8_parameter_from_file].result == f_console_result_additional) {
        f_array_length_t i = 0;
        f_array_length_t index = 0;

        f_file_t file = f_file_t_initialize;
        file.size_read = 32768;

        for (; i < main->parameters[utf8_parameter_from_file].values.used && status != F_signal; ++i) {

          if (utf8_signal_received(main)) {
            status = F_status_set_error(F_signal);
            break;
          }

          index = main->parameters[utf8_parameter_from_file].values.array[i];

          utf8_print_section_header_file(main, arguments->argv[index]);

          status = f_file_stream_open(arguments->argv[index], 0, &file);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_open", F_true, arguments->argv[index], utf8_string_open_s, fll_error_file_type_file);

            break;
          }

          if (main->mode & utf8_mode_from_binary_d) {
            status = utf8_process_file_binary(main, file);
          }
          else {
            status = utf8_process_file_codepoint(main, file);
          }

          f_file_stream_close(F_true, &file);

          if (main->parameters[utf8_parameter_verify].result == f_console_result_found) {
            if (status == F_false) {
              valid = F_false;
            }
          }

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), main->mode & utf8_mode_from_binary_d ? "utf8_process_file_binary" : "utf8_process_file_codepoint", F_true, arguments->argv[index], utf8_string_process_s, fll_error_file_type_file);

            break;
          }
        } // for
      }

      if (F_status_is_error_not(status) && status != F_signal && main->remaining.used) {
        f_array_length_t i = 0;
        f_array_length_t index = 0;

        for (; F_status_is_error_not(status) && i < main->remaining.used; ++i) {

          if (utf8_signal_received(main)) {
            status = F_status_set_error(F_signal);
            break;
          }

          index = main->remaining.array[i];

          utf8_print_section_header_parameter(main, index);

          status = utf8_process_text(main, arguments->argv[index]);

          if (main->parameters[utf8_parameter_verify].result == f_console_result_found) {
            if (status == F_false) {
              valid = F_false;
            }
          }
        } // for
      }
    }

    if (main->output.verbosity != f_console_verbosity_quiet) {
      if (F_status_set_fine(status) == F_interrupt) {
        fflush(main->output.to.stream);
      }

      fll_print_terminated(f_string_eol_s, main->output.to.stream);
    }

    utf8_main_delete(main);

    if (F_status_is_error(status)) {
      return status;
    }

    return valid;
  }
#endif // _di_utf8_main_

#ifndef _di_utf8_main_delete_
  f_status_t utf8_main_delete(utf8_main_t *main) {

    for (f_array_length_t i = 0; i < utf8_total_parameters_d; ++i) {

      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations_sub);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].values);
    } // for

    macro_f_string_dynamic_t_delete_simple(main->buffer);
    macro_f_string_dynamic_t_delete_simple(main->file_input);
    macro_f_string_dynamic_t_delete_simple(main->file_output);
    macro_f_string_dynamic_t_delete_simple(main->text);

    macro_f_string_dynamic_t_delete_simple(main->separate_character);
    macro_f_string_dynamic_t_delete_simple(main->separate_source);

    macro_f_array_lengths_t_delete_simple(main->remaining);

    macro_f_color_context_t_delete_simple(main->context);

    return F_none;
  }
#endif // _di_utf8_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif
