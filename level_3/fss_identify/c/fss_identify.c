#include "fss_identify.h"
#include "private-common.h"
#include "private-identify.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_identify_main_
  f_status_t fss_identify_main(fll_program_data_t * const main, fss_identify_setting_t * const setting) {

    f_status_t status = F_none;

    setting->state.step_small = fss_identify_allocation_console_d;

    status = f_console_parameter_process(arguments, &main->parameters, &setting->state, 0);

    setting->state.step_small = fss_identify_allocation_small_d;

    if (F_status_is_error(status)) return;

    {
      f_number_unsigned_t choice = 0;
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { fss_identify_parameter_no_color_e, fss_identify_parameter_light_e, fss_identify_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        static const uint8_t modes[3] = { f_color_mode_not_e, f_color_mode_light_e, f_color_mode_dark_e };

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
        uint16_t choices_array[5] = { fss_identify_parameter_verbosity_quiet_e, fss_identify_parameter_verbosity_error_e, fss_identify_parameter_verbosity_verbose_e, fss_identify_parameter_verbosity_debug_e, fss_identify_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        static const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

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

    if (main->parameters.array[fss_identify_parameter_help_e].result & f_console_result_found_e) {
      fss_identify_print_help(setting, main->message);

      return F_none;
    }

    if (main->parameters.array[fss_identify_parameter_version_e].result & f_console_result_found_e) {
      fll_program_print_version(&main->message, fss_identify_program_version_s);

      return F_none;
    }

    if (main->parameters.array[fss_identify_parameter_copyright_e].result & f_console_result_found_e) {
      fll_program_print_copyright(&main->message);

      return F_none;
    }

    status = F_none;

    fss_identify_data_t data = fss_identify_data_t_initialize;

    data.argv = main->parameters.arguments.array;

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[fss_identify_parameter_line_e].result & f_console_result_found_e) {
        f_file_stream_lock(main->error.to);

        fl_print_format("%r%[%QThe parameter '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, fss_identify_long_line_s, main->error.notable);
        fl_print_format("%[' requires a positive number.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

        f_file_stream_unlock(main->error.to);

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters.array[fss_identify_parameter_line_e].result & f_console_result_value_e) {
        const f_number_unsigned_t index = main->parameters.array[fss_identify_parameter_line_e].values.array[main->parameters.array[fss_identify_parameter_line_e].values.used - 1];

        status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, data.argv[index], &data.line);

        if (F_status_is_error(status)) {
          fll_error_parameter_integer_print(main->error, F_status_set_fine(status), "fl_conversion_dynamic_to_unsigned_detect", F_true, fss_identify_long_line_s, data.argv[index]);
        }
      }
    }

    if (F_status_is_error_not(status) && (main->parameters.array[fss_identify_parameter_total_e].result & f_console_result_found_e)) {
      if (main->parameters.array[fss_identify_parameter_object_e].result & f_console_result_found_e) {
        if (main->error.verbosity > f_console_verbosity_quiet_e) {
          fll_program_print_error_parameter_cannot_use_with(&main->error, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, fss_identify_long_object_s, fss_identify_long_total_s);
        }

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters.array[fss_identify_parameter_content_e].result & f_console_result_found_e) {
        if (main->error.verbosity > f_console_verbosity_quiet_e) {
          fll_program_print_error_parameter_cannot_use_with(&main->error, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, fss_identify_long_content_s, fss_identify_long_total_s);
        }

        status = F_status_set_error(F_parameter);
      }
    }

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[fss_identify_parameter_name_e].result & f_console_result_found_e) {
        f_file_stream_lock(main->error.to);

        fl_print_format("%r%[%QThe parameter '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, fss_identify_long_name_s, main->error.notable);
        fl_print_format("%[' requires a string.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

        f_file_stream_unlock(main->error.to);

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters.array[fss_identify_parameter_name_e].result & f_console_result_value_e) {
        const f_number_unsigned_t index = main->parameters.array[fss_identify_parameter_name_e].values.array[main->parameters.array[fss_identify_parameter_name_e].values.used - 1];
        const f_number_unsigned_t length = data.argv[index].used;
        const f_string_range_t range = macro_f_string_range_t_initialize_2(length);

        if (length == 0) {
          f_file_stream_lock(main->error.to);

          fl_print_format("%r%[%QThe parameter '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, fss_identify_long_name_s, main->error.notable);
          fl_print_format("%[' does not allow zero length strings.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

          f_file_stream_unlock(main->error.to);

          status = F_status_set_error(F_parameter);
        }
        else {
          status = f_string_dynamic_resize(length, &data.name);

          if (F_status_is_error(status)) {
            fll_error_print(main->error, F_status_set_fine(status), "f_utf_is_word", fll_error_file_flag_fallback_e);
          }
        }

        if (F_status_is_error_not(status)) {

          for (f_number_unsigned_t i = range.start; i <= range.stop; ++i) {

            status = f_utf_is_word_dash(data.argv[index].string + i, length, F_true);

            if (F_status_is_error(status)) {
              fll_error_print(main->error, F_status_set_fine(status), "f_utf_is_word_dash", fll_error_file_flag_fallback_e);

              break;
            }
            else if (status == F_false) {
              f_file_stream_lock(main->error.to);

              fl_print_format("%r%[%QThe value '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
              fl_print_format("%[%Q%]", main->error.to, main->error.notable, data.argv[index], main->error.notable);
              fl_print_format("%[' for the parameter '%]", main->error.to, main->error.context, main->error.context);
              fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, fss_identify_long_name_s, main->error.notable);
              fl_print_format("%[' may only contain word characters or the dash (minus)y character.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

              f_file_stream_unlock(main->error.to);

              status = F_status_set_error(F_parameter);

              break;
            }

            data.name.string[data.name.used++] = data.argv[index].string[i];
          } // for
        }
      }
    }

    f_string_range_t range = f_string_range_t_initialize;
    f_string_dynamic_t buffer = f_string_dynamic_t_initialize;
    f_file_t file = f_file_t_initialize;

    if (F_status_is_error_not(status) && (main->pipe & fll_program_data_pipe_input_e)) {
      file.id = F_type_descriptor_input_d;
      file.stream = F_type_input_d;
      file.size_read = 512;

      status = fss_identify_load_line(main, file, f_string_empty_s, &buffer, &range);

      if (F_status_is_error_not(status)) {
        status = fss_identify_process(main, &data, f_string_ascii_minus_s, buffer, &range);
      }
    }

    if (F_status_is_error_not(status)) {
      for (f_number_unsigned_t i = 0; i < main->parameters.remaining.used; ++i) {

        if (!((++main->signal_check) % fss_identify_signal_check_d)) {
          if (fll_program_standard_signal_received(&main->program)) {
            fll_program_print_signal_received(&main->warning, main->signal_received);

            status = F_status_set_error(F_interrupt);

            break;
          }

          main->signal_check = 0;
        }

        if (main->parameters.array[fss_identify_parameter_line_e].result & f_console_result_value_e) {
          if (data.current > data.line) break;
        }

        macro_f_file_t_reset(file);

        file.size_read = 512;

        status = f_file_stream_open(data.argv[main->parameters.remaining.array[i]], f_string_empty_s, &file);

        if (F_status_is_error(status)) {
          fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_open", fll_error_file_flag_fallback_e, data.argv[main->parameters.remaining.array[i]], f_file_operation_open_s, fll_error_file_type_file_e);
        }
        else {
          status = fss_identify_load_line(main, file, data.argv[main->parameters.remaining.array[i]], &buffer, &range);

          if (F_status_is_error_not(status)) {
            status = fss_identify_process(main, &data, data.argv[main->parameters.remaining.array[i]], buffer, &range);
          }
        }

        f_file_stream_flush(file);
        f_file_stream_close(&file);

        if (F_status_is_error(status)) break;
      } // for
    }

    f_string_dynamic_resize(0, &buffer);

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[fss_identify_parameter_total_e].result & f_console_result_found_e) {
        fll_print_format("%ul%r", main->output.to, data.total, f_string_eol_s);
      }
    }

    // Ensure a newline is always put at the end of the program execution, unless in quiet mode.
    if (main->error.verbosity > f_console_verbosity_quiet_e) {
      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_interrupt) {
          f_file_stream_flush(main->output.to);
        }

        fll_print_dynamic_raw(f_string_eol_s, main->output.to);
      }
    }

    fss_identify_data_delete(&data);

    return status;
  }
#endif // _di_fss_identify_main_

#ifdef __cplusplus
} // extern "C"
#endif
