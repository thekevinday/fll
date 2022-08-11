#include "utf8.h"
#include "private-common.h"
#include "private-print.h"
#include "private-utf8.h"
#include "private-utf8_bytesequence.h"
#include "private-utf8_codepoint.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_print_help_
  f_status_t utf8_print_help(const f_file_t file, const f_color_context_t context) {

    flockfile(file.stream);

    fll_program_print_help_header(file, context, utf8_program_name_long_s, utf8_program_version_s);

    fll_program_print_help_option(file, context, f_console_standard_short_help_s, f_console_standard_long_help_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Print this help message.");
    fll_program_print_help_option(file, context, f_console_standard_short_dark_s, f_console_standard_long_dark_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_light_s, f_console_standard_long_light_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "Do not print using color.");
    fll_program_print_help_option(file, context, f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Decrease verbosity, silencing most output.");
    fll_program_print_help_option(file, context, f_console_standard_short_error_s, f_console_standard_long_error_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Decrease verbosity, using only error output.");
    fll_program_print_help_option(file, context, f_console_standard_short_normal_s, f_console_standard_long_normal_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "  Set verbosity to normal.");
    fll_program_print_help_option(file, context, f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_debug_s, f_console_standard_long_debug_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Enable debugging, significantly increasing verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_version_s, f_console_standard_long_version_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Print only the version number.");

    f_print_dynamic_raw(f_string_eol_s, file.stream);

    fll_program_print_help_option(file, context, utf8_short_from_bytesequence_s, utf8_long_from_bytesequence_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "The expected input format is byte sequence (character data).");
    fll_program_print_help_option(file, context, utf8_short_from_codepoint_s, utf8_long_from_codepoint_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   The expected input format is codepoint (such as U+0000).");
    fll_program_print_help_option(file, context, utf8_short_from_file_s, utf8_long_from_file_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "        Use the given file as the input source.");

    f_print_dynamic_raw(f_string_eol_s, file.stream);

    fll_program_print_help_option(file, context, utf8_short_to_bytesequence_s, utf8_long_to_bytesequence_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "The output format is byte sequence (character data).");
    fll_program_print_help_option(file, context, utf8_short_to_codepoint_s, utf8_long_to_codepoint_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   The output format is codepoint (such as U+0000).");
    fll_program_print_help_option(file, context, utf8_short_to_combining_s, utf8_long_to_combining_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   The output format is to print whether or not character is combining or not.");
    fll_program_print_help_option(file, context, utf8_short_to_file_s, utf8_long_to_file_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "        Use the given file as the output destination.");
    fll_program_print_help_option(file, context, utf8_short_to_width_s, utf8_long_to_width_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "       The output format is to print the width of a character (either 0, 1, or 2).");

    f_print_dynamic_raw(f_string_eol_s, file.stream);

    fll_program_print_help_option(file, context, utf8_short_headers_s, utf8_long_headers_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "      Print headers for each section (pipe, file, or parameter).");
    fll_program_print_help_option(file, context, utf8_short_separate_s, utf8_long_separate_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "     Separate characters by newlines (implied when printing headers).");
    fll_program_print_help_option(file, context, utf8_short_strip_invalid_s, utf8_long_strip_invalid_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Strip invalid Unicode characters (do not print invalid sequences).");
    fll_program_print_help_option(file, context, utf8_short_verify_s, utf8_long_verify_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "       Only perform verification of valid sequences.");

    fll_program_print_help_usage(file, context, utf8_program_name_s, utf8_program_help_parameters_s);

    fl_print_format("  The default behavior is to assume the expected input is byte sequence from the command line to be output to the screen as codepoints.%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    fl_print_format("  Multiple input sources are allowed but only a single output destination is allowed.%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When using the parameter '%[%r%r%]', no data is printed and 0 is returned if valid or 1 is returned if invalid.%r%r", file.stream, context.set.notable, f_console_symbol_long_enable_s, utf8_long_verify_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When using the parameter '%[%r%r%]' with the parameter ", file.stream, context.set.notable, f_console_symbol_long_enable_s, utf8_long_to_combining_s, context.set.notable);
    fl_print_format("'%[%r%r%]', the ", file.stream, context.set.notable, f_console_symbol_long_enable_s, utf8_long_to_width_s, context.set.notable);
    fl_print_format("'%[%r%]' character is printed to represent the combining and the digits are used to represent widths.%r", file.stream, context.set.notable, utf8_string_combining_is_s, context.set.notable, f_string_eol_s);
    fl_print_format("  The combining characters should be considered 1-width by themselves or 0-width when combined.%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    funlockfile(file.stream);

    return F_none;
  }
#endif // _di_utf8_print_help_

#ifndef _di_utf8_main_
  f_status_t utf8_main(fll_program_data_t * const main, utf8_main_setting_t * const setting) {

    if (!main || !setting) {
      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        fll_error_print(main->error, F_status_set_fine(status), "utf8_main", F_true);
        fll_print_dynamic_raw(f_string_eol_s, main->message.to.stream);
      }

      return F_status_set_error(F_paremeter);
    }

    utf8_data_t data = utf8_data_t_initialize;
    data.main = main;
    data.setting = setting;
    data.argv = main->parameters.arguments.array;
    f_status_t status = F_none;

    if (main->parameters.array[utf8_parameter_help_e].result == f_console_result_found_e) {
      utf8_print_help(main->message.to, main->context);

      utf8_data_delete(&data);

      return F_none;
    }

    if (main->parameters.array[utf8_parameter_version_e].result == f_console_result_found_e) {
      fll_program_print_version(main->message.to, utf8_program_version_s);

      utf8_data_delete(&data);

      return F_none;
    }

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[utf8_parameter_from_file_e].result == f_console_result_additional_e) {
        f_array_length_t i = 0;
        f_array_length_t index = 0;

        for (; i < main->parameters.array[utf8_parameter_from_file_e].values.used; ++i) {

          index = main->parameters.array[utf8_parameter_from_file_e].values.array[i];

          if (data.argv[index].used) {
            if (f_file_exists(data.argv[index], F_true) != F_true) {
              utf8_print_error_parameter_file_not_found(&data, F_true, data.argv[index]);

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
          if (data.argv[main->parameters.array[utf8_parameter_to_file_e].values.array[0]].used) {
            status = f_file_stream_open(data.argv[main->parameters.array[utf8_parameter_to_file_e].values.array[0]], f_file_open_mode_append_s, &data.file);

            if (F_status_is_error(status)) {
              fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_open", F_true, data.argv[main->parameters.array[utf8_parameter_to_file_e].values.array[0]], f_file_operation_open_s, fll_error_file_type_file_e);
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
        data.file = main->message.to;
      }
    }

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[utf8_parameter_from_file_e].result == f_console_result_none_e && !(main->process_pipe || main->parameters.remaining.used)) {
        utf8_print_error_no_from(&data);

        status = F_status_set_error(F_parameter);
      }

      if (!(data.mode & utf8_mode_to_bytesequence_d)) {
        if (main->parameters.array[utf8_parameter_separate_e].result == f_console_result_found_e || main->parameters.array[utf8_parameter_headers_e].result == f_console_result_found_e) {
          data.prepend = utf8_string_prepend_padding_s;
          data.append = f_string_eol_s;
        }
        else {
          data.prepend = f_string_space_s;
        }
      }

      data.valid_not = main->message.set->error;
    }

    if (F_status_is_error_not(status)) {
      status = F_none;

      if (main->process_pipe) {
        f_file_t file = macro_f_file_t_initialize(0, -1, F_file_flag_read_only_d, 32768, F_file_default_write_size_d);

        file.id = F_type_descriptor_input_d;
        file.stream = F_type_input_d;

        utf8_print_section_header_pipe(&data);

        if (data.mode & utf8_mode_from_bytesequence_d) {
          status = utf8_process_file_bytesequence(&data, file);
        }
        else {
          status = utf8_process_file_codepoint(&data, file);
        }

        if (F_status_is_error(status) && F_status_set_fine(status) != F_utf_fragment && F_status_set_fine(status) != F_complete_not_utf) {
          fll_error_file_print(main->error, F_status_set_fine(status), data.mode & utf8_mode_from_bytesequence_d ? "utf8_process_file_bytesequence" : "utf8_process_file_codepoint", F_true, f_string_empty_s, f_file_operation_process_s, fll_error_file_type_pipe_e);
        }
      }

      if (F_status_is_error_not(status) && status != F_interrupt && main->parameters.array[utf8_parameter_from_file_e].result == f_console_result_additional_e) {
        f_array_length_t i = 0;
        f_array_length_t index = 0;

        f_file_t file = macro_f_file_t_initialize(0, -1, F_file_flag_read_only_d, 32768, F_file_default_write_size_d);

        for (; i < main->parameters.array[utf8_parameter_from_file_e].values.used && status != F_interrupt; ++i) {

          if (!((++main->signal_check) % utf8_signal_check_d)) {
            if (fll_program_standard_signal_received(main)) {
              status = F_status_set_error(F_interrupt);

              break;
            }

            main->signal_check = 0;
          }

          index = main->parameters.array[utf8_parameter_from_file_e].values.array[i];

          utf8_print_section_header_file(&data, data.argv[index]);

          status = f_file_stream_open(data.argv[index], f_string_empty_s, &file);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_open", F_true, data.argv[index], f_file_operation_open_s, fll_error_file_type_file_e);

            break;
          }

          if (data.mode & utf8_mode_from_bytesequence_d) {
            status = utf8_process_file_bytesequence(&data, file);
          }
          else {
            status = utf8_process_file_codepoint(&data, file);
          }

          f_file_stream_flush(&file);
          f_file_stream_close(&file);

          if (main->parameters.array[utf8_parameter_verify_e].result == f_console_result_found_e) {
            if (status == F_false) {
              valid = F_false;
            }
          }

          if (F_status_is_error(status) && F_status_set_fine(status) != F_utf_fragment && F_status_set_fine(status) != F_complete_not_utf) {
            fll_error_file_print(main->error, F_status_set_fine(status), data.mode & utf8_mode_from_bytesequence_d ? "utf8_process_file_bytesequence" : "utf8_process_file_codepoint", F_true, data.argv[index], f_file_operation_process_s, fll_error_file_type_file_e);

            break;
          }
        } // for
      }

      if (F_status_is_error_not(status) && status != F_interrupt && main->parameters.remaining.used) {
        for (f_array_length_t i = 0; F_status_is_error_not(status) && i < main->parameters.remaining.used; ++i) {

          if (!((++main->signal_check) % utf8_signal_check_d)) {
            if (fll_program_standard_signal_received(main)) {
              status = F_status_set_error(F_interrupt);

              break;
            }

            main->signal_check = 0;
          }

          utf8_print_section_header_parameter(&data, main->parameters.remaining.array[i]);

          status = utf8_process_text(&data, data.argv[main->parameters.remaining.array[i]]);

          if (main->parameters.array[utf8_parameter_verify_e].result == f_console_result_found_e) {
            if (status == F_false) {
              valid = F_false;
            }
          }
        } // for
      }
    }

    if (main->message.verbosity != f_console_verbosity_quiet_e && main->parameters.array[utf8_parameter_verify_e].result == f_console_result_none_e) {
      if (status == F_interrupt) {
        fflush(data.file.stream);

        if (data.file.stream != main->message.to.stream) {
          fflush(main->message.to.stream);
        }
      }

      fll_print_dynamic_raw(f_string_eol_s, main->message.to.stream);
    }

    utf8_data_delete(&data);

    if (F_status_is_error(status) || status == F_interrupt) return status;

    return valid;
  }
#endif // _di_utf8_main_

#ifndef _di_utf8_main_setting_delete_
  f_status_t utf8_main_setting_delete(utf8_main_setting_t * const setting) {

    return F_none;
  }
#endif // _di_utf8_main_setting_delete_

#ifndef _di_utf8_main_setting_load_
  f_status_t utf8_main_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, utf8_main_setting_t * const setting) {

    f_status_t status = F_none;

    // Identify priority of color parameters.
    {
      f_console_parameter_id_t ids[3] = { utf8_parameter_no_color_e, utf8_parameter_light_e, utf8_parameter_dark_e };
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 3);

      status = fll_program_parameter_process(arguments, choices, F_true, main);

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process", F_true);

        return status;
      }
    }

    {
      const verbosity[5] = { utf8_parameter_verbosity_quiet_e, utf8_parameter_verbosity_error_e, f_console_verbosity_normal_e, utf8_parameter_verbosity_verbose_e, utf8_parameter_verbosity_debug_e };
      f_console_parameter_id_t ids[5] = { utf8_parameter_verbosity_quiet_e, utf8_parameter_verbosity_error_e, utf8_parameter_verbosity_normal_e, utf8_parameter_verbosity_verbose_e, utf8_parameter_verbosity_debug_e };
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 5);

      status = fll_program_parameter_process_verbosity(choices, F_true, verbosity, main);

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process_verbosity", F_true);

        return status;
      }
    }

    // Identify and prioritize from mode parameters.
    {
      f_console_parameter_id_t ids[2] = { utf8_parameter_from_bytesequence_e, utf8_parameter_from_codepoint_e };
      f_console_parameter_id_t choice = 0;
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 2);

      status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", F_true);

        return status;
      }

      if (choice == utf8_parameter_from_bytesequence_e) {
        if (data.mode & utf8_mode_from_codepoint_d) {
          data.mode -= utf8_mode_from_codepoint_d;
        }

        data.mode |= utf8_mode_from_bytesequence_d;
      }
      else if (choice == utf8_parameter_from_codepoint_e) {
        if (data.mode & utf8_mode_from_bytesequence_d) {
          data.mode -= utf8_mode_from_bytesequence_d;
        }

        data.mode |= utf8_mode_from_codepoint_d;
      }
    }

    // Identify and prioritize to mode parameters.
    {
      f_console_parameter_id_t ids[5] = { utf8_parameter_to_bytesequence_e, utf8_parameter_to_codepoint_e, utf8_parameter_to_combining_e, utf8_parameter_to_width_e };
      f_console_parameter_id_t choice = 0;
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 5);

      status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", F_true);

        return status;
      }

      if (choice == utf8_parameter_to_bytesequence_e) {
        if (data.mode & utf8_mode_to_codepoint_d) {
          data.mode -= utf8_mode_to_codepoint_d;
        }

        if (data.mode & utf8_mode_to_combining_d) {
          data.mode -= utf8_mode_to_combining_d;
        }

        if (data.mode & utf8_mode_to_width_d) {
          data.mode -= utf8_mode_to_width_d;
        }

        data.mode |= utf8_mode_to_bytesequence_d;
      }
      else if (choice == utf8_parameter_to_codepoint_e) {
        if (data.mode & utf8_mode_to_bytesequence_d) {
          data.mode -= utf8_mode_to_bytesequence_d;
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
        if (data.mode & utf8_mode_to_bytesequence_d) {
          data.mode -= utf8_mode_to_bytesequence_d;
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
        if (data.mode & utf8_mode_to_bytesequence_d) {
          data.mode -= utf8_mode_to_bytesequence_d;
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

    return F_none;
  }
#endif // _di_utf8_main_setting_load_

#ifndef _di_utf8_main_setting_unload_
  f_status_t utf8_main_setting_unload(fll_program_data_t * const main, utf8_main_setting_t * const setting) {

    if (data->file.stream) {
      if (data->file.stream != main->message.stream && data->file.stream != main->output.stream && data->file.stream != main->error.stream && data->file.stream != main->warning.stream && data->file.stream != main->debug.stream) {
        f_file_stream_flush(&data->file);
        f_file_stream_close(&data->file);
      }
    }
    else if (data->file.id != -1) {
      if (data->file.id != main->message.id && data->file.id != main->output.id && data->file.id != main->error.id && data->file.id != main->warning.id && data->file.id != main->debug.id) {
        f_file_flush(&data->file);
        f_file_close(&data->file);
      }
    }
  }
#endif // _di_utf8_main_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif
