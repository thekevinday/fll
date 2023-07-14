#include "byte_dump.h"
#include "private-common.h"
#include "private-byte_dump.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_byte_dump_main_
  f_status_t byte_dump_main(fll_program_data_t * const main, byte_dump_setting_t * const setting) {

    f_status_t status = F_none;

    setting->state.step_small = byte_dump_allocation_console_d;

    status = f_console_parameter_process(arguments, &main->parameters, &setting->state, 0);

    setting->state.step_small = byte_dump_allocation_small_d;

    if (F_status_is_error(status)) return;

    {
      f_number_unsigned_t choice = 0;
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { byte_dump_parameter_no_color_e, byte_dump_parameter_light_e, byte_dump_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        const uint8_t modes[3] = { f_color_mode_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        status = fll_program_parameter_process_context(choices, modes, F_true, &main->program);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process_context", fll_error_file_flag_fallback_e);

          if (main->error.verbosity > f_console_verbosity_quiet_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->error);
          }

          return;
        }
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { byte_dump_parameter_verbosity_quiet_e, byte_dump_parameter_verbosity_error_e, byte_dump_parameter_verbosity_verbose_e, byte_dump_parameter_verbosity_debug_e, byte_dump_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, &main->program);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process_verbosity", fll_error_file_flag_fallback_e);

          if (main->error.verbosity > f_console_verbosity_quiet_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->error);
          }

          return;
        }
      }
    }

    byte_dump_data_t data = byte_dump_data_t_initialize;
    data.main = main;
    data.argv = main->parameters.arguments.array;

    // Identify priority of mode parameters.
    {
      uint16_t choices_array[5] = { byte_dump_parameter_hexidecimal_e, byte_dump_parameter_duodecimal_e, byte_dump_parameter_octal_e, byte_dump_parameter_binary_e, byte_dump_parameter_decimal_e };
      f_number_unsigned_t choice = 0;
      const f_uint16s_t choices = macro_f_uint16s_t_initialize_1(choices_array, 0, 5);

      status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", fll_error_file_flag_fallback_e);

        return F_status_set_error(status);
      }

      if (choices.array[choice] == byte_dump_parameter_hexidecimal_e) {
        data.mode = byte_dump_mode_hexidecimal_e;
      }
      else if (choices.array[choice] == byte_dump_parameter_duodecimal_e) {
        data.mode = byte_dump_mode_duodecimal_e;
      }
      else if (choices.array[choice] == byte_dump_parameter_octal_e) {
        data.mode = byte_dump_mode_octal_e;
      }
      else if (choices.array[choice] == byte_dump_parameter_binary_e) {
        data.mode = byte_dump_mode_binary_e;
      }
      else if (choices.array[choice] == byte_dump_parameter_decimal_e) {
        data.mode = byte_dump_mode_decimal_e;
      }
    }

    // Identify priority of presentation parameters.
    {
      uint16_t choices_array[3] = { byte_dump_parameter_normal_e, byte_dump_parameter_simple_e, byte_dump_parameter_classic_e };
      f_number_unsigned_t choice = 0;
      const f_uint16s_t choices = macro_f_uint16s_t_initialize_1(choices_array, 0, 3);

      status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", fll_error_file_flag_fallback_e);

        return F_status_set_error(status);
      }

      if (choices.array[choice] == byte_dump_parameter_normal_e) {
        data.presentation = byte_dump_presentation_normal_e;
      }
      else if (choices.array[choice] == byte_dump_parameter_simple_e) {
        data.presentation = byte_dump_presentation_simple_e;
      }
      else if (choices.array[choice] == byte_dump_parameter_classic_e) {
        data.presentation = byte_dump_presentation_classic_e;
      }
    }

    // Identify priority of narrow and wide parameters.
    {
      uint16_t choices_array[2] = { byte_dump_parameter_narrow_e, byte_dump_parameter_wide_e };
      f_number_unsigned_t choice = byte_dump_parameter_wide_e;
      const f_uint16s_t choices = macro_f_uint16s_t_initialize_1(choices_array, 0, 2);

      status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", fll_error_file_flag_fallback_e);

        return F_status_set_error(status);
      }

      if (choices.array[choice] == byte_dump_parameter_narrow_e) {
        if (data.options & byte_dump_option_wide_d) {
          data.options -= byte_dump_option_wide_d;
        }
      }
      else if (choices.array[choice] == byte_dump_parameter_wide_e) {
        data.options |= byte_dump_option_wide_d;
      }
    }

    if (main->parameters.array[byte_dump_parameter_help_e].result & f_console_result_found_e) {
      byte_dump_print_help(setting, main->message);

      return F_none;
    }

    if (main->parameters.array[byte_dump_parameter_version_e].result & f_console_result_found_e) {
      fll_program_print_version(&main->message, byte_dump_program_version_s);

      return F_none;
    }

    if (main->parameters.array[byte_dump_parameter_copyright_e].result & f_console_result_found_e) {
      fll_program_print_copyright(&main->message);

      return F_none;
    }

    status = F_none;

    if (main->parameters.remaining.used || (main->pipe & fll_program_data_pipe_input_e)) {
      if (main->parameters.array[byte_dump_parameter_width_e].result & f_console_result_found_e) {
        f_file_stream_lock(main->error.to);

        fl_print_format("%[%QThe parameter '%]", main->error.to, main->context.set.error, main->error.prefix, main->context.set.error);
        fl_print_format("%[%r%r%]", main->error.to, main->context.set.notable, f_console_symbol_long_normal_s, byte_dump_long_width_s, main->context.set.notable);
        fl_print_format("%[' is specified, but no value is given.%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);

        f_file_stream_unlock(main->error.to);

        return F_status_set_error(F_parameter);
      }

      if (main->parameters.array[byte_dump_parameter_width_e].result & f_console_result_value_e) {
        const f_number_unsigned_t index = main->parameters.array[byte_dump_parameter_width_e].values.array[main->parameters.array[byte_dump_parameter_width_e].values.used - 1];
        f_number_unsigned_t number = 0;

        status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, data.argv[index], &number);

        // Negative numbers are not supported.
        if (status == F_number_negative) {
          status = F_status_set_error(F_number_negative);
        }

        if (F_status_is_error(status) || number < 1 || number >= 0xfb) {
          f_file_stream_lock(main->error.to);

          fl_print_format("%[%QThe parameter '%]", main->error.to, main->context.set.error, main->error.prefix, main->context.set.error);
          fl_print_format("%[%r%r%]", main->error.to, main->context.set.notable, f_console_symbol_long_normal_s, byte_dump_long_width_s, main->context.set.notable);
          fl_print_format("%[' value can only be a number (inclusively) between %]", main->error.to, main->context.set.error, main->context.set.error);
          fl_print_format("%[1%]", main->error.to, main->context.set.notable, main->context.set.notable);
          fl_print_format(" %[and%] ", main->error.to, main->context.set.error, main->context.set.error);
          fl_print_format("%[250%]", main->error.to, main->context.set.notable, main->context.set.notable);
          fl_print_format("%[.%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);

          f_file_stream_unlock(main->error.to);

          if (F_status_is_error(status)) return status;

          return F_status_set_error(F_parameter);
        }

        data.width = (uint8_t) number;
      }

      if (main->parameters.array[byte_dump_parameter_first_e].result & f_console_result_found_e) {
        f_file_stream_lock(main->error.to);

        fl_print_format("%[%QThe parameter '%]", main->error.to, main->context.set.error, main->error.prefix, main->context.set.error);
        fl_print_format("%[%r%r%]", main->error.to, main->context.set.notable, f_console_symbol_long_normal_s, byte_dump_long_first_s, main->context.set.notable);
        fl_print_format("%[' is specified, but no value is given.%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);

        f_file_stream_unlock(main->error.to);

        return F_status_set_error(F_parameter);
      }

      if (main->parameters.array[byte_dump_parameter_first_e].result & f_console_result_value_e) {
        const f_number_unsigned_t index = main->parameters.array[byte_dump_parameter_first_e].values.array[main->parameters.array[byte_dump_parameter_first_e].values.used - 1];
        f_number_unsigned_t number = 0;

        status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, data.argv[index], &number);

        // Negative numbers are not supported.
        if (status == F_number_negative) {
          status = F_status_set_error(F_number_negative);
        }

        if (F_status_is_error(status) || number > F_number_t_size_unsigned_d) {
          f_file_stream_lock(main->error.to);

          fl_print_format("%[%QThe parameter '%]", main->error.to, main->context.set.error, main->error.prefix, main->context.set.error);
          fl_print_format("%[%r%r%]", main->error.to, main->context.set.notable, f_console_symbol_long_normal_s, byte_dump_long_first_s, main->context.set.notable);
          fl_print_format("%[' value can only be a number (inclusively) between %]", main->error.to, main->context.set.error, main->context.set.error);
          fl_print_format("%[0%]", main->error.to, main->context.set.notable, main->context.set.notable);
          fl_print_format(" %[and%] ", main->error.to, main->context.set.error, main->context.set.error);
          fl_print_format("%[%un%]", main->error.to, main->context.set.notable, F_number_t_size_unsigned_d, main->context.set.notable);
          fl_print_format("%[.%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);

          f_file_stream_unlock(main->error.to);

          if (F_status_is_error(status)) return status;

          return F_status_set_error(F_parameter);
        }

        data.first = number;
      }

      if (main->parameters.array[byte_dump_parameter_last_e].result & f_console_result_found_e) {
        f_file_stream_lock(main->error.to);

        fl_print_format("%[%QThe parameter '%]", main->error.to, main->context.set.error, main->error.prefix, main->context.set.error);
        fl_print_format("%[%r%r%]", main->error.to, main->context.set.notable, f_console_symbol_long_normal_s, byte_dump_long_last_s, main->context.set.notable);
        fl_print_format("%[' is specified, but no value is given.%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);

        f_file_stream_unlock(main->error.to);

        return F_status_set_error(F_parameter);
      }

      if (main->parameters.array[byte_dump_parameter_last_e].result & f_console_result_value_e) {
        const f_number_unsigned_t index = main->parameters.array[byte_dump_parameter_last_e].values.array[main->parameters.array[byte_dump_parameter_last_e].values.used - 1];
        f_number_unsigned_t number = 0;

        status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, data.argv[index], &number);

        // Negative numbers are not supported.
        if (status == F_number_negative) {
          status = F_status_set_error(F_number_negative);
        }

        if (F_status_is_error(status) || number < 0 || number > F_number_t_size_unsigned_d) {
          f_file_stream_lock(main->error.to);

          fl_print_format("%[%QThe parameter '%]", main->error.to, main->context.set.error, main->error.prefix, main->context.set.error);
          fl_print_format("%[%r%r%]", main->error.to, main->context.set.notable, f_console_symbol_long_normal_s, byte_dump_long_last_s, main->context.set.notable);
          fl_print_format("%[' value can only be a number (inclusively) between %]", main->error.to, main->context.set.error, main->context.set.error);
          fl_print_format("%[0%]", main->error.to, main->context.set.notable, main->context.set.notable);
          fl_print_format(" %[and%] ", main->error.to, main->context.set.error, main->context.set.error);
          fl_print_format("%[%un%]", main->error.to, main->context.set.notable, F_number_t_size_unsigned_d, main->context.set.notable);
          fl_print_format("%[.%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);

          f_file_stream_unlock(main->error.to);

          if (F_status_is_error(status)) return status;

          return F_status_set_error(F_parameter);
        }

        data.last = number;
      }

      if (main->parameters.array[byte_dump_parameter_first_e].result & f_console_result_value_e && main->parameters.array[byte_dump_parameter_last_e].result & f_console_result_value_e) {
        if (data.first > data.last) {
          f_file_stream_lock(main->error.to);

          fl_print_format("%[%QThe parameter '%]", main->error.to, main->context.set.error, main->error.prefix, main->context.set.error);
          fl_print_format("%[%r%r%]", main->error.to, main->context.set.notable, f_console_symbol_long_normal_s, byte_dump_long_first_s, main->context.set.notable);
          fl_print_format("%[' value cannot be greater than the parameter '%]", main->error.to, main->context.set.error, main->context.set.error);
          fl_print_format("%[%r%r%]", main->error.to, main->context.set.notable, f_console_symbol_long_normal_s, byte_dump_long_last_s, main->context.set.notable);
          fl_print_format("%[' value.%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);

          f_file_stream_unlock(main->error.to);

          return F_status_set_error(F_parameter);
        }

        // Store last position as a relative offset from first instead of an absolute position.
        data.last = (data.last - data.first) + 1;
      }

      if (main->pipe & fll_program_data_pipe_input_e) {
        f_file_t file = f_file_t_initialize;

        file.id = F_type_descriptor_input_d;
        file.stream = F_type_input_d;

        f_file_stream_lock(main->output.to);

        f_print_dynamic_raw(f_string_eol_s, main->output.to);
        fl_print_format("%[Piped " BYTE_DUMP_program_name_long_s ": (in ", main->output.to, main->context.set.title);

        if (data.mode == byte_dump_mode_hexidecimal_e) {
          f_print_dynamic_raw(byte_dump_print_strings_hexidecimal_s, main->output.to);
        }
        else if (data.mode == byte_dump_mode_duodecimal_e) {
          f_print_dynamic_raw(byte_dump_print_strings_duodecimal_s, main->output.to);
        }
        else if (data.mode == byte_dump_mode_octal_e) {
          f_print_dynamic_raw(byte_dump_print_strings_octal_s, main->output.to);
        }
        else if (data.mode == byte_dump_mode_binary_e) {
          f_print_dynamic_raw(byte_dump_print_strings_binary_s, main->output.to);
        }
        else if (data.mode == byte_dump_mode_decimal_e) {
          f_print_dynamic_raw(byte_dump_print_strings_decimal_s, main->output.to);
        }

        fl_print_format(")%]%r", main->output.to, main->context.set.title, f_string_eol_s);

        f_file_stream_unlock(main->output.to);

        status = byte_dump_file(&data, f_string_empty_s, file);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "byte_dump_file", fll_error_file_flag_fallback_e);

          return status;
        }
      }

      if (main->parameters.remaining.used) {

        // Pre-process remaining arguments to ensure that they all files exist before processing.
        {
          f_status_t missing_files = F_none;

          for (f_number_unsigned_t counter = 0; counter < main->parameters.remaining.used; ++counter) {

            status = f_file_exists(data.argv[main->parameters.remaining.array[counter]], F_true);

            if (status == F_false) {
              status = F_status_set_error(F_file_found_not);
            }

            if (F_status_is_error(status)) {
              if (missing_files == F_none) {
                missing_files = status;
              }

              fll_error_file_print(main->error, F_status_set_fine(status), "f_file_exists", fll_error_file_flag_fallback_e, data.argv[main->parameters.remaining.array[counter]], f_file_operation_open_s, fll_error_file_type_file_e);
            }
          } // for

          if (missing_files != F_none) {
            status = F_status_set_error(missing_files);

            return status;
          }
        }

        f_file_t file = f_file_t_initialize;

        for (f_number_unsigned_t counter = 0; counter < main->parameters.remaining.used; ++counter) {

          status = f_file_stream_open(data.argv[main->parameters.remaining.array[counter]], f_string_empty_s, &file);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_open", fll_error_file_flag_fallback_e, data.argv[main->parameters.remaining.array[counter]], f_file_operation_open_s, fll_error_file_type_file_e);

            return status;
          }

          f_file_stream_lock(main->output.to);

          fl_print_format("%r%[" BYTE_DUMP_program_name_long_s " of: %]%[", main->output.to, f_string_eol_s, main->context.set.title, main->context.set.title, main->context.set.notable);
          fl_print_format("%Q%] %[(in ", main->output.to, data.argv[main->parameters.remaining.array[counter]], main->context.set.notable, main->context.set.title);

          if (data.mode == byte_dump_mode_hexidecimal_e) {
            f_print_dynamic_raw(byte_dump_print_strings_hexidecimal_s, main->output.to);
          }
          else if (data.mode == byte_dump_mode_duodecimal_e) {
            f_print_dynamic_raw(byte_dump_print_strings_duodecimal_s, main->output.to);
          }
          else if (data.mode == byte_dump_mode_octal_e) {
            f_print_dynamic_raw(byte_dump_print_strings_octal_s, main->output.to);
          }
          else if (data.mode == byte_dump_mode_binary_e) {
            f_print_dynamic_raw(byte_dump_print_strings_binary_s, main->output.to);
          }
          else if (data.mode == byte_dump_mode_decimal_e) {
            f_print_dynamic_raw(byte_dump_print_strings_decimal_s, main->output.to);
          }

          fl_print_format(")%]%r", main->output.to, main->context.set.title, f_string_eol_s);

          f_file_stream_unlock(main->output.to);

          status = byte_dump_file(&data, data.argv[main->parameters.remaining.array[counter]], file);

          f_file_stream_flush(file);
          f_file_stream_close(&file);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_interrupt) {

              // Ensure a newline is always put at the end of the program execution, unless in quiet mode.
              if (main->output.verbosity != f_console_verbosity_quiet_e) {
                f_file_stream_flush(main->output.to);

                fll_print_dynamic_raw(f_string_eol_s, main->output.to);
              }
            }
            else {
              if (main->error.verbosity > f_console_verbosity_quiet_e) {
                fll_error_file_print(main->error, F_status_set_fine(status), "byte_dump_file", fll_error_file_flag_fallback_e, data.argv[main->parameters.remaining.array[counter]], f_file_operation_process_s, fll_error_file_type_file_e);
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
      fll_print_format("%r%[%QYou failed to specify one or more filenames.%]%r", main->error.to, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error, f_string_eol_s);

      status = F_status_set_error(F_parameter);
    }

    return status;
  }
#endif // _di_byte_dump_main_

#ifdef __cplusplus
} // extern "C"
#endif
