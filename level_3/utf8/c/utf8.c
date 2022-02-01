#include "utf8.h"
#include "private-common.h"
#include "private-print.h"
#include "private-utf8.h"
#include "private-utf8_binary.h"
#include "private-utf8_codepoint.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_program_version_
  const f_string_static_t utf8_program_version_s = macro_f_string_static_t_initialize(UTF8_program_version_s, 0, UTF8_program_version_s_length);
#endif // _di_utf8_program_version_

#ifndef _di_utf8_program_name_
  const f_string_static_t utf8_program_name_s = macro_f_string_static_t_initialize(UTF8_program_name_s, 0, UTF8_program_name_s_length);
  const f_string_static_t utf8_program_name_long_s = macro_f_string_static_t_initialize(UTF8_program_name_long_s, 0, UTF8_program_name_s_long_length);
#endif // _di_utf8_program_name_

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

    f_print_dynamic_raw(f_string_eol_s, file.stream);

    fll_program_print_help_option(file, context, utf8_short_from_binary_s, utf8_long_from_binary_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   The expected input format is binary (character data).");
    fll_program_print_help_option(file, context, utf8_short_from_codepoint_s, utf8_long_from_codepoint_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "The expected input format is codepoint (such as U+0000).");
    fll_program_print_help_option(file, context, utf8_short_from_file_s, utf8_long_from_file_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "     Use the given file as the input source.");

    f_print_dynamic_raw(f_string_eol_s, file.stream);

    fll_program_print_help_option(file, context, utf8_short_to_binary_s, utf8_long_to_binary_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   The output format is binary (character data).");
    fll_program_print_help_option(file, context, utf8_short_to_codepoint_s, utf8_long_to_codepoint_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "The output format is codepoint (such as U+0000).");
    fll_program_print_help_option(file, context, utf8_short_to_combining_s, utf8_long_to_combining_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "The output format is to print whether or not character is combining or not.");
    fll_program_print_help_option(file, context, utf8_short_to_file_s, utf8_long_to_file_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "     Use the given file as the output destination.");
    fll_program_print_help_option(file, context, utf8_short_to_width_s, utf8_long_to_width_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    The output format is to print the width of a character (either 0, 1, or 2).");

    f_print_dynamic_raw(f_string_eol_s, file.stream);

    fll_program_print_help_option(file, context, utf8_short_headers_s, utf8_long_headers_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "      Print headers for each section (pipe, file, or parameter).");
    fll_program_print_help_option(file, context, utf8_short_separate_s, utf8_long_separate_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "     Separate characters by newlines (implied when printing headers).");
    fll_program_print_help_option(file, context, utf8_short_strip_invalid_s, utf8_long_strip_invalid_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Strip invalid Unicode characters (do not print invalid sequences).");
    fll_program_print_help_option(file, context, utf8_short_verify_s, utf8_long_verify_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "       Only perform verification of valid sequences.");

    fll_program_print_help_usage(file, context, utf8_program_name_s, "filename(s)");

    fl_print_format("  The default behavior is to assume the expected input is binary from the command line to be output to the screen as codepoints.%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    fl_print_format("  Multiple input sources are allowed but only a single output destination is allowed.%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When using the parameter '%[%r%s%]', no data is printed and 0 is returned if valid or 1 is returned if invalid.%r%r", file.stream, context.set.notable, f_console_symbol_long_enable_s, utf8_long_verify_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When using the parameter '%[%r%s%]' with the parameter ", file.stream, context.set.notable, f_console_symbol_long_enable_s, utf8_long_to_combining_s, context.set.notable);
    fl_print_format("'%[%r%s%]', the ", file.stream, context.set.notable, f_console_symbol_long_enable_s, utf8_long_to_width_s, context.set.notable);
    fl_print_format("'%[%s%]' character is printed to represent the combining and the digits are used to represent widths.%r", file.stream, context.set.notable, utf8_string_combining_is_s, context.set.notable, f_string_eol_s);
    fl_print_format("  The combining characters should be considered 1-width by themselves or 0-width when combined.%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    funlockfile(file.stream);

    return F_none;
  }
#endif // _di_utf8_print_help_

#ifndef _di_utf8_main_
  f_status_t utf8_main(utf8_main_t * const main, const f_console_arguments_t *arguments) {

    f_status_t status = F_none;

    utf8_data_t data = utf8_data_t_initialize;
    data.main = main;

    f_console_parameter_t parameters[] = utf8_console_parameter_t_initialize;
    main->parameters.array = parameters;
    main->parameters.used = utf8_total_parameters_d;

    // Identify priority of color parameters.
    {
      f_console_parameter_id_t ids[3] = { utf8_parameter_no_color_e, utf8_parameter_light_e, utf8_parameter_dark_e };
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
        fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process", F_true);

        utf8_data_delete(&data);
        utf8_main_delete(main);

        return F_status_set_error(status);
      }
    }

    // Identify priority of verbosity related parameters.
    {
      f_console_parameter_id_t ids[4] = { utf8_parameter_verbosity_quiet_e, utf8_parameter_verbosity_normal_e, utf8_parameter_verbosity_verbose_e, utf8_parameter_verbosity_debug_e };
      f_console_parameter_id_t choice = 0;
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 4);

      status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", F_true);

        utf8_main_delete(main);
        utf8_data_delete(&data);

        return status;
      }

      if (choice == utf8_parameter_verbosity_quiet_e) {
        main->output.verbosity = f_console_verbosity_quiet_e;
        main->error.verbosity = f_console_verbosity_quiet_e;
        main->warning.verbosity = f_console_verbosity_quiet_e;
      }
      else if (choice == utf8_parameter_verbosity_normal_e) {
        main->output.verbosity = f_console_verbosity_normal_e;
        main->error.verbosity = f_console_verbosity_normal_e;
        main->warning.verbosity = f_console_verbosity_normal_e;
      }
      else if (choice == utf8_parameter_verbosity_verbose_e) {
        main->output.verbosity = f_console_verbosity_verbose_e;
        main->error.verbosity = f_console_verbosity_verbose_e;
        main->warning.verbosity = f_console_verbosity_verbose_e;
      }
      else if (choice == utf8_parameter_verbosity_debug_e) {
        main->output.verbosity = f_console_verbosity_debug_e;
        main->error.verbosity = f_console_verbosity_debug_e;
        main->warning.verbosity = f_console_verbosity_debug_e;
      }
    }

    // Identify and prioritize from mode parameters.
    {
      f_console_parameter_id_t ids[2] = { utf8_parameter_from_binary_e, utf8_parameter_from_codepoint_e };
      f_console_parameter_id_t choice = 0;
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 2);

      status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", F_true);

        utf8_data_delete(&data);
        utf8_main_delete(main);

        return status;
      }

      if (choice == utf8_parameter_from_binary_e) {
        if (data.mode & utf8_mode_from_codepoint_d) {
          data.mode -= utf8_mode_from_codepoint_d;
        }

        data.mode |= utf8_mode_from_binary_d;
      }
      else if (choice == utf8_parameter_from_codepoint_e) {
        if (data.mode & utf8_mode_from_binary_d) {
          data.mode -= utf8_mode_from_binary_d;
        }

        data.mode |= utf8_mode_from_codepoint_d;
      }
    }

    // Identify and prioritize to mode parameters.
    {
      f_console_parameter_id_t ids[4] = { utf8_parameter_to_binary_e, utf8_parameter_to_codepoint_e, utf8_parameter_to_combining_e, utf8_parameter_to_width_e };
      f_console_parameter_id_t choice = 0;
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 4);

      status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", F_true);

        utf8_data_delete(&data);
        utf8_main_delete(main);

        return status;
      }

      if (choice == utf8_parameter_to_binary_e) {
        if (data.mode & utf8_mode_to_codepoint_d) {
          data.mode -= utf8_mode_to_codepoint_d;
        }

        if (data.mode & utf8_mode_to_combining_d) {
          data.mode -= utf8_mode_to_combining_d;
        }

        if (data.mode & utf8_mode_to_width_d) {
          data.mode -= utf8_mode_to_width_d;
        }

        data.mode |= utf8_mode_to_binary_d;
      }
      else if (choice == utf8_parameter_to_codepoint_e) {
        if (data.mode & utf8_mode_to_binary_d) {
          data.mode -= utf8_mode_to_binary_d;
        }

        if (data.mode & utf8_mode_to_combining_d) {
          data.mode -= utf8_mode_to_combining_d;
        }

        if (data.mode & utf8_mode_to_width_d) {
          data.mode -= utf8_mode_to_width_d;
        }

        data.mode |= utf8_mode_to_codepoint_d;
      }
      else if (choice == utf8_parameter_to_combining_e) {
        if (data.mode & utf8_mode_to_binary_d) {
          data.mode -= utf8_mode_to_binary_d;
        }

        if (data.mode & utf8_mode_to_codepoint_d) {
          data.mode -= utf8_mode_to_codepoint_d;
        }

        // --to_width may be specified with --to_combining.
        if (main->parameters.array[utf8_parameter_to_width_e].result == f_console_result_found_e) {
          data.mode |= utf8_mode_to_width_d;
        }

        data.mode |= utf8_mode_to_combining_d;
      }
      else if (choice == utf8_parameter_to_width_e) {
        if (data.mode & utf8_mode_to_binary_d) {
          data.mode -= utf8_mode_to_binary_d;
        }

        if (data.mode & utf8_mode_to_codepoint_d) {
          data.mode -= utf8_mode_to_codepoint_d;
        }

        // --to_width may be specified with --to_combining.
        if (main->parameters.array[utf8_parameter_to_combining_e].result == f_console_result_found_e) {
          data.mode |= utf8_mode_to_combining_d;
        }

        data.mode |= utf8_mode_to_width_d;
      }
    }

    data.argv = main->parameters.arguments.array;
    status = F_none;

    if (main->parameters.array[utf8_parameter_help_e].result == f_console_result_found_e) {
      utf8_print_help(main->output.to, main->context);

      utf8_data_delete(&data);
      utf8_main_delete(main);

      return F_none;
    }

    if (main->parameters.array[utf8_parameter_version_e].result == f_console_result_found_e) {
      fll_program_print_version(main->output.to, utf8_version_s);

      utf8_data_delete(&data);
      utf8_main_delete(main);

      return F_none;
    }

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[utf8_parameter_from_file_e].result == f_console_result_additional_e) {
        f_array_length_t i = 0;
        f_array_length_t index = 0;

        for (; i < main->parameters.array[utf8_parameter_from_file_e].values.used; ++i) {

          index = main->parameters.array[utf8_parameter_from_file_e].values.array[i];

          if (arguments->argv[index][0]) {
            if (!f_file_exists(arguments->argv[index])) {
              utf8_print_error_parameter_file_not_found(&data, F_true, arguments->argv[index]);

              if (F_status_is_error_not(status)) {
                status = F_status_set_error(F_file_found_not);
              }
            }
          }
          else {
            utf8_print_error_parameter_file_name_empty(&data, index);

            if (F_status_is_error_not(status)) {
              status = F_status_set_error(F_parameter);
            }
          }
        } // for
      }
      else if (main->parameters.array[utf8_parameter_from_file_e].result == f_console_result_found_e) {
        utf8_print_error_no_value(&data, utf8_long_from_file_s);

        status = F_status_set_error(F_parameter);
      }
    }

    bool valid = F_true;

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[utf8_parameter_to_file_e].result == f_console_result_additional_e) {
        if (main->parameters.array[utf8_parameter_to_file_e].values.used > 1) {
          utf8_print_error_parameter_file_to_too_many(&data);

          status = F_status_set_error(F_parameter);
        }
        else {
          data.file_name.string = arguments->argv[main->parameters.array[utf8_parameter_to_file_e].values.array[0]];
          data.file_name.used = strnlen(data.file_name.string, PATH_MAX);

          if (data.file_name.used) {
            status = f_file_stream_open(data.file_name.string, "a", &data.file);

            if (F_status_is_error(status)) {
              fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_open", F_true, data.file_name.string, f_file_operation_open_s, fll_error_file_type_file_e);
            }
          }
          else {
            utf8_print_error_parameter_file_name_empty(&data, main->parameters.array[utf8_parameter_to_file_e].values.array[0]);

            status = F_status_set_error(F_parameter);
          }
        }
      }
      else if (main->parameters.array[utf8_parameter_to_file_e].result == f_console_result_found_e) {
        utf8_print_error_no_value(&data, utf8_long_to_file_s);

        status = F_status_set_error(F_parameter);
      }
      else {
        data.file = main->output.to;
      }
    }

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[utf8_parameter_from_file_e].result == f_console_result_none_e && !(main->process_pipe || main->remaining.used)) {
        utf8_print_error_no_from(&data);

        status = F_status_set_error(F_parameter);
      }

      if (!(data.mode & utf8_mode_to_binary_d)) {
        if (main->parameters.array[utf8_parameter_separate_e].result == f_console_result_found_e || main->parameters.array[utf8_parameter_headers_e].result == f_console_result_found_e) {
          data.prepend = "  ";
          data.append = f_string_eol_s;
        }
        else {
          data.prepend = f_string_space_s;
        }
      }

      data.valid_not = main->output.set->error;
    }

    if (F_status_is_error_not(status)) {
      status = F_none;

      if (main->process_pipe) {
        f_file_t file = macro_f_file_t_initialize(0, -1, F_file_flag_read_only_d, 32768, F_file_default_write_size_d);

        file.id = F_type_descriptor_input_d;
        file.stream = F_type_input_d;

        utf8_print_section_header_pipe(&data);

        if (data.mode & utf8_mode_from_binary_d) {
          status = utf8_process_file_binary(&data, file);
        }
        else {
          status = utf8_process_file_codepoint(&data, file);
        }

        if (F_status_is_error(status) && F_status_set_fine(status) != F_utf_fragment) {
          fll_error_file_print(main->error, F_status_set_fine(status), data.mode & utf8_mode_from_binary_d ? "utf8_process_file_binary" : "utf8_process_file_codepoint", F_true, 0, f_file_operation_process_s, fll_error_file_type_pipe_e);
        }
      }

      if (F_status_is_error_not(status) && status != F_signal && main->parameters.array[utf8_parameter_from_file_e].result == f_console_result_additional_e) {
        f_array_length_t i = 0;
        f_array_length_t index = 0;

        f_file_t file = macro_f_file_t_initialize(0, -1, F_file_flag_read_only_d, 32768, F_file_default_write_size_d);

        for (uint16_t signal_check = 0; i < main->parameters.array[utf8_parameter_from_file_e].values.used && status != F_signal; ++i) {

          if (!((++signal_check) % utf8_signal_check_d)) {
            if (utf8_signal_received(&data)) {
              status = F_status_set_error(F_signal);
              break;
            }

            signal_check = 0;
          }

          index = main->parameters.array[utf8_parameter_from_file_e].values.array[i];

          utf8_print_section_header_file(&data, arguments->argv[index]);

          status = f_file_stream_open(arguments->argv[index], 0, &file);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_open", F_true, arguments->argv[index], f_file_operation_open_s, fll_error_file_type_file_e);

            break;
          }

          if (data.mode & utf8_mode_from_binary_d) {
            status = utf8_process_file_binary(&data, file);
          }
          else {
            status = utf8_process_file_codepoint(&data, file);
          }

          f_file_stream_close(F_true, &file);

          if (main->parameters.array[utf8_parameter_verify_e].result == f_console_result_found_e) {
            if (status == F_false) {
              valid = F_false;
            }
          }

          if (F_status_is_error(status) && F_status_set_fine(status) != F_utf_fragment) {
            fll_error_file_print(main->error, F_status_set_fine(status), data.mode & utf8_mode_from_binary_d ? "utf8_process_file_binary" : "utf8_process_file_codepoint", F_true, arguments->argv[index], f_file_operation_process_s, fll_error_file_type_file_e);

            break;
          }
        } // for
      }

      if (F_status_is_error_not(status) && status != F_signal && main->remaining.used) {
        f_array_length_t i = 0;
        f_array_length_t index = 0;

        for (uint16_t signal_check = 0; F_status_is_error_not(status) && i < main->remaining.used; ++i) {

          if (!((++signal_check) % utf8_signal_check_d)) {
            if (utf8_signal_received(&data)) {
              status = F_status_set_error(F_signal);
              break;
            }

            signal_check = 0;
          }

          index = main->remaining.array[i];

          utf8_print_section_header_parameter(&data, index);

          status = utf8_process_text(&data, arguments->argv[index]);

          if (main->parameters.array[utf8_parameter_verify_e].result == f_console_result_found_e) {
            if (status == F_false) {
              valid = F_false;
            }
          }
        } // for
      }
    }

    if (main->output.verbosity != f_console_verbosity_quiet_e && main->parameters.array[utf8_parameter_verify_e].result == f_console_result_none_e) {
      if (status == F_signal) {
        fflush(data.file.stream);

        if (data.file.stream != main->output.to.stream) {
          fflush(main->output.to.stream);
        }
      }

      fll_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
    }

    utf8_data_delete(&data);
    utf8_main_delete(main);

    if (F_status_is_error(status) || status == F_signal) {
      return status;
    }

    return valid;
  }
#endif // _di_utf8_main_

#ifndef _di_utf8_main_delete_
  f_status_t utf8_main_delete(utf8_main_t *main) {

    f_console_parameters_delete(&main->parameters);

    f_type_array_lengths_resize(0, &main->remaining);

    macro_f_color_context_t_delete_simple(main->context);

    return F_none;
  }
#endif // _di_utf8_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif
