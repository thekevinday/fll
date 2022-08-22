#include "fss_status_code.h"
#include "private-common.h"
#include "private-fss_status_code.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_status_code_print_help_
  f_status_t fss_status_code_print_help(const f_file_t file, const f_color_context_t context) {

    flockfile(file.stream);

    //if (!(setting->flag & XXX_main_flag_line_first_no_e)) {
      f_print_dynamic_raw(f_string_eol_s, file.stream);
    //}

    fll_program_print_help_header(file, context, fss_status_code_program_name_long_s, fss_status_code_program_version_s);

    fll_program_print_help_option_standard(file, context);

    f_print_dynamic_raw(f_string_eol_s, file.stream);

    fll_program_print_help_option(file, context, fss_status_code_short_fine_s, fss_status_code_long_fine_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Print F_true or F_false if status code is neither an error nor a warning or print number with neither the error code nor the warning code bits set.");
    fll_program_print_help_option(file, context, fss_status_code_short_warning_s, fss_status_code_long_warning_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Print F_true or F_false if status code is a warning or print number with warning code bit set.");
    fll_program_print_help_option(file, context, fss_status_code_short_error_s, fss_status_code_long_error_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Print F_true or F_false if status code is an error or print number with error code bit set.");
    fll_program_print_help_option(file, context, fss_status_code_short_number_s, fss_status_code_long_number_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Convert status code name to number.");

    fll_program_print_help_usage(file, context, fss_status_code_program_name_s, fss_status_code_program_help_parameters_s);

    //if (!(setting->flag & XXX_main_flag_line_last_no_e)) {
      f_print_dynamic_raw(f_string_eol_s, file.stream);
    //}

    f_file_stream_flush(file);
    funlockfile(file.stream);

    return F_none;
  }
#endif // _di_fss_status_code_print_help_

#ifndef _di_fss_status_code_main_
  f_status_t fss_status_code_main(fll_program_data_t * const main, const f_console_arguments_t arguments) {

    f_status_t status = F_none;

    // Load parameters.
    status = f_console_parameter_process(arguments, &main->parameters);
    if (F_status_is_error(status)) return;

    {
      f_array_length_t choice = 0;
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { fss_status_code_parameter_no_color_e, fss_status_code_parameter_light_e, fss_status_code_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        const uint8_t modes[3] = { f_color_mode_color_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        status = fll_program_parameter_process_context(choices, modes, F_true, main);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process_context", F_true);

          return;
        }
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { fss_status_code_parameter_verbosity_quiet_e, fss_status_code_parameter_verbosity_error_e, fss_status_code_parameter_verbosity_verbose_e, fss_status_code_parameter_verbosity_debug_e, fss_status_code_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, main);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process_verbosity", F_true);

          return;
        }
      }
    }

    f_string_static_t * const argv = main->parameters.arguments.array;

    status = F_none;

    if (main->parameters.array[fss_status_code_parameter_help_e].result == f_console_result_found_e) {
      fss_status_code_print_help(main->output.to, main->context);

      return F_none;
    }

    if (main->parameters.array[fss_status_code_parameter_version_e].result == f_console_result_found_e) {
      fll_program_print_version(main->output.to, fss_status_code_program_version_s);

      return F_none;
    }

    if (main->parameters.array[fss_status_code_parameter_error_e].result == f_console_result_found_e) {
      if (main->parameters.array[fss_status_code_parameter_warning_e].result == f_console_result_found_e) {
        if (main->parameters.array[fss_status_code_parameter_number_e].result == f_console_result_none_e) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            flockfile(main->error.to.stream);

            fl_print_format("%r%[%QCannot specify the '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_status_code_long_error_s, main->error.notable);
            fl_print_format("%[' parameter with the '%]", main->error.to.stream, main->error.context, main->error.context);
            fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_status_code_long_warning_s, main->error.notable);
            fl_print_format("%[' parameter when not also specifying the '%]", main->error.to.stream, main->error.context, main->error.context);
            fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_status_code_long_number_s, main->error.notable);
            fl_print_format("%[' parameter.%]%r%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s, f_string_eol_s);

            funlockfile(main->error.to.stream);
          }

          return F_status_set_error(status);
        }
      }

      if (main->parameters.array[fss_status_code_parameter_fine_e].result == f_console_result_found_e) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          fll_program_parameter_long_print_cannot_use_with(main->error, fss_status_code_long_error_s, fss_status_code_long_fine_s);
          fll_print_dynamic_raw(f_string_eol_s, main->error.to.stream);
        }

        return F_status_set_error(status);
      }
    }
    else if (main->parameters.array[fss_status_code_parameter_warning_e].result == f_console_result_found_e && main->parameters.array[fss_status_code_parameter_fine_e].result == f_console_result_found_e) {
      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        fll_program_parameter_long_print_cannot_use_with(main->error, fss_status_code_long_warning_s, fss_status_code_long_fine_s);
        fll_print_dynamic_raw(f_string_eol_s, main->error.to.stream);
      }

      return F_status_set_error(status);
    }

    if (main->parameters.remaining.used == 0 && !(main->pipe & fll_program_data_pipe_input_e)) {
      fll_print_format("%[You failed to specify an error code.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

      return F_status_set_error(F_parameter);
    }

    f_status_t status2 = F_none;

    if (main->parameters.array[fss_status_code_parameter_number_e].result == f_console_result_found_e) {
      if (main->pipe & fll_program_data_pipe_input_e) {
        // @todo call fss_status_code_process_number() here for all main from pipe that is space separated.
      }

      if (main->parameters.remaining.used) {
        flockfile(main->output.to.stream);

        for (f_array_length_t i = 0; i < main->parameters.remaining.used; ++i) {

          if (!((++main->signal_check) % fss_status_code_signal_check_d)) {
            if (fll_program_standard_signal_received(main)) {
              fss_status_code_print_signal_received(main);

              status = F_status_set_error(F_interrupt);

              break;
            }

            main->signal_check = 0;
          }

          status2 = fss_status_code_process_number(main, argv[main->parameters.remaining.array[i]]);

          if (F_status_is_error(status2) && status == F_none) {
            status = status2;
          }
        } // for

        funlockfile(main->output.to.stream);
      }
    }
    else if (main->parameters.array[fss_status_code_parameter_error_e].result == f_console_result_found_e || main->parameters.array[fss_status_code_parameter_warning_e].result == f_console_result_found_e || main->parameters.array[fss_status_code_parameter_fine_e].result == f_console_result_found_e) {
      if (main->pipe & fll_program_data_pipe_input_e) {
        // @todo call fss_status_code_process_check() here for all main from pipe that is space separated.
      }

      if (main->parameters.remaining.used) {
        flockfile(main->output.to.stream);

        for (f_array_length_t i = 0; i < main->parameters.remaining.used; ++i) {

          if (!((++main->signal_check) % fss_status_code_signal_check_d)) {
            if (fll_program_standard_signal_received(main)) {
              fss_status_code_print_signal_received(main);

              status = F_status_set_error(F_interrupt);

              break;
            }

            main->signal_check = 0;
          }

          status2 = fss_status_code_process_check(main, argv[main->parameters.remaining.array[i]]);

          if (F_status_is_error(status2) && status == F_none) {
            status = status2;
          }
        } // for

        funlockfile(main->output.to.stream);
      }
    }
    else {
      if (main->pipe & fll_program_data_pipe_input_e) {
        // @todo call fss_status_code_process_normal() here for all main from pipe that is space separated.
      }

      if (main->parameters.remaining.used) {
        flockfile(main->output.to.stream);

        for (f_array_length_t i = 0; i < main->parameters.remaining.used; ++i) {

          if (!((++main->signal_check) % fss_status_code_signal_check_d)) {
            if (fll_program_standard_signal_received(main)) {
              fss_status_code_print_signal_received(main);

              status = F_status_set_error(F_interrupt);

              break;
            }

            main->signal_check = 0;
          }

          status2 = fss_status_code_process_normal(main, argv[main->parameters.remaining.array[i]]);

          if (F_status_is_error(status2) && status == F_none) {
            status = status2;
          }
        } // for

        funlockfile(main->output.to.stream);
      }
    }

    if (F_status_set_fine(status) == F_interrupt) {
      if (main->output.verbosity != f_console_verbosity_quiet_e) {
        fflush(main->output.to.stream);

        fll_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
      }
    }

    return status;
  }
#endif // _di_fss_status_code_main_

#ifdef __cplusplus
} // extern "C"
#endif
