#include "status_code.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_status_code_main_
  void status_code_main(status_code_main_t * const main) {

    if (!main) return;

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & status_code_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      return;
    }

    if ((main->setting.flag & status_code_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
    }

    if (!main->setting.status_string_from || !main->setting.status_string_to) {
      if (!main->setting.status_string_from) {
        status_code_print_error_invalid_callback(&main->program.error, macro_status_code_f(status_string_from));
      }

      if (!main->setting.status_string_to) {
        status_code_print_error_invalid_callback(&main->program.error, macro_status_code_f(status_string_to));
      }

      if ((main->setting.flag & status_code_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      main->setting.state.status = F_status_set_error(F_parameter);

      return;
    }

    main->setting.state.status = F_okay;

    if (main->setting.flag & (status_code_main_flag_help_e | status_code_main_flag_version_e | status_code_main_flag_copyright_e)) {
      if (main->setting.flag & status_code_main_flag_help_e) {
        status_code_print_message_help(&main->program.message);
      }
      else if (main->setting.flag & status_code_main_flag_version_e) {
        fll_program_print_version(&main->program.message, status_code_program_version_s);
      }
      else if (main->setting.flag & status_code_main_flag_copyright_e) {
        fll_program_print_copyright(&main->program.message);
      }

      if ((main->setting.flag & status_code_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      return;
    }

    f_status_t status = F_okay;

    if (main->setting.flag & status_code_main_flag_number_e) {
      if (main->setting.flag & status_code_main_flag_pipe_e) {
        // @todo call status_code_process_number() here for all main from pipe that are space separated.
      }

      if (main->program.parameters.remaining.used) {
        f_file_stream_lock(main->program.output.to);

        for (f_number_unsigned_t i = 0; i < main->program.parameters.remaining.used; ++i) {

          if (!((++main->program.signal_check) % status_code_signal_check_d)) {
            if (fll_program_standard_signal_received(&main->program)) {
              main->setting.state.status = F_status_set_error(F_interrupt);

              break;
            }

            main->program.signal_check = 0;
          }

          status = main->setting.state.status;

          status_code_process_number(main, main->program.parameters.arguments.array[main->program.parameters.remaining.array[i]]);

          if (F_status_is_error_not(main->setting.state.status)) {
            main->setting.state.status = status;
          }
        } // for

        f_file_stream_unlock(main->program.output.to);
      }
    }
    else if ((main->setting.flag & status_code_main_flag_error_e) || (main->setting.flag & status_code_main_flag_warning_e) || (main->setting.flag & status_code_main_flag_fine_e)) {
      if (main->setting.flag & status_code_main_flag_pipe_e) {
        // @todo call status_code_process_check() here for all main from pipe that is space separated.
      }

      if (main->program.parameters.remaining.used) {
        f_file_stream_lock(main->program.output.to);

        for (f_number_unsigned_t i = 0; i < main->program.parameters.remaining.used; ++i) {

          if (!((++main->program.signal_check) % status_code_signal_check_d)) {
            if (fll_program_standard_signal_received(&main->program)) {
              main->setting.state.status = F_status_set_error(F_interrupt);

              break;
            }

            main->program.signal_check = 0;
          }

          status = main->setting.state.status;

          status_code_process_check(main, main->program.parameters.arguments.array[main->program.parameters.remaining.array[i]]);

          if (F_status_is_error_not(main->setting.state.status)) {
            main->setting.state.status = status;
          }
        } // for

        f_file_stream_unlock(main->program.output.to);
      }
    }
    else {
      if (main->setting.flag & status_code_main_flag_pipe_e) {
        // @todo call status_code_process_normal() here for all main from pipe that is space separated.
      }

      if (main->program.parameters.remaining.used) {
        f_file_stream_lock(main->program.output.to);

        for (f_number_unsigned_t i = 0; i < main->program.parameters.remaining.used; ++i) {

          if (!((++main->program.signal_check) % status_code_signal_check_d)) {
            if (fll_program_standard_signal_received(&main->program)) {
              main->setting.state.status = F_status_set_error(F_interrupt);

              break;
            }

            main->program.signal_check = 0;
          }

          status = main->setting.state.status;

          status_code_process_normal(main, main->program.parameters.arguments.array[main->program.parameters.remaining.array[i]]);

          if (F_status_is_error_not(main->setting.state.status)) {
            main->setting.state.status = status;
          }
        } // for

        f_file_stream_unlock(main->program.output.to);
      }
    }

    if (main->setting.state.status == F_status_set_error(F_interrupt)) {
      fll_program_print_signal_received(&main->program.warning, main->program.signal_received);
    }

    if ((main->setting.flag & status_code_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
    }
  }
#endif // _di_status_code_main_

#ifdef __cplusplus
} // extern "C"
#endif
