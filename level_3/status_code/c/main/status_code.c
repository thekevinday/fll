#include "status_code.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_status_code_main_
  void status_code_main(fll_program_data_t * const main, status_code_setting_t * const setting) {

    if (!main || !setting) return;

    if (F_status_is_error(setting->state.status)) {
      if ((setting->flag & status_code_main_flag_print_last_e) && main->message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->message.to);
      }

      return;
    }

    if ((setting->flag & status_code_main_flag_print_first_e) && main->message.verbosity > f_console_verbosity_error_e) {
      fll_print_dynamic_raw(f_string_eol_s, main->message.to);
    }

    if (!setting->status_string_from || !setting->status_string_to) {
      if (!setting->status_string_from) {
        status_code_print_error_invalid_callback(setting, main->error, macro_status_code_f(status_string_from));
      }

      if (!setting->status_string_to) {
        status_code_print_error_invalid_callback(setting, main->error, macro_status_code_f(status_string_to));
      }

      if ((setting->flag & status_code_main_flag_print_last_e) && main->message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->message.to);
      }

      setting->state.status = F_status_set_error(F_parameter);

      return;
    }

    setting->state.status = F_none;

    if (setting->flag & status_code_main_flag_help_e) {
      status_code_print_help(setting, main->message);

      if ((setting->flag & status_code_main_flag_print_last_e) && main->message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->message.to);
      }

      return;
    }

    if (setting->flag & status_code_main_flag_version_e) {
      fll_program_print_version(main->message, status_code_program_version_s);

      if ((setting->flag & status_code_main_flag_print_last_e) && main->message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->message.to);
      }

      return;
    }

    if (setting->flag & status_code_main_flag_copyright_e) {
      fll_program_print_copyright(main->message);

      if ((setting->flag & status_code_main_flag_print_last_e) && main->message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->message.to);
      }

      return;
    }

    f_status_t status = F_none;

    if (setting->flag & status_code_main_flag_number_e) {
      if (main->pipe & fll_program_data_pipe_input_e) {
        // @todo call status_code_process_number() here for all main from pipe that are space separated.
      }

      if (main->parameters.remaining.used) {
        f_file_stream_lock(main->output.to);

        for (f_array_length_t i = 0; i < main->parameters.remaining.used; ++i) {

          if (!((++main->signal_check) % status_code_signal_check_d)) {
            if (fll_program_standard_signal_received(main)) {
              setting->state.status = F_status_set_error(F_interrupt);

              break;
            }

            main->signal_check = 0;
          }

          status = setting->state.status;

          status_code_process_number(main, setting, main->parameters.arguments.array[main->parameters.remaining.array[i]]);

          if (F_status_is_error_not(setting->state.status)) {
            setting->state.status = status;
          }
        } // for

        f_file_stream_unlock(main->output.to);
      }
    }
    else if ((setting->flag & status_code_main_flag_error_e) || (setting->flag & status_code_main_flag_warning_e) || (setting->flag & status_code_main_flag_fine_e)) {
      if (main->pipe & fll_program_data_pipe_input_e) {
        // @todo call status_code_process_check() here for all main from pipe that is space separated.
      }

      if (main->parameters.remaining.used) {
        f_file_stream_lock(main->output.to);

        for (f_array_length_t i = 0; i < main->parameters.remaining.used; ++i) {

          if (!((++main->signal_check) % status_code_signal_check_d)) {
            if (fll_program_standard_signal_received(main)) {
              setting->state.status = F_status_set_error(F_interrupt);

              break;
            }

            main->signal_check = 0;
          }

          status = setting->state.status;

          status_code_process_check(main, setting, main->parameters.arguments.array[main->parameters.remaining.array[i]]);

          if (F_status_is_error_not(setting->state.status)) {
            setting->state.status = status;
          }
        } // for

        f_file_stream_unlock(main->output.to);
      }
    }
    else {
      if (main->pipe & fll_program_data_pipe_input_e) {
        // @todo call status_code_process_normal() here for all main from pipe that is space separated.
      }

      if (main->parameters.remaining.used) {
        f_file_stream_lock(main->output.to);

        for (f_array_length_t i = 0; i < main->parameters.remaining.used; ++i) {

          if (!((++main->signal_check) % status_code_signal_check_d)) {
            if (fll_program_standard_signal_received(main)) {
              setting->state.status = F_status_set_error(F_interrupt);

              break;
            }

            main->signal_check = 0;
          }

          status = setting->state.status;

          status_code_process_normal(main, setting, main->parameters.arguments.array[main->parameters.remaining.array[i]]);

          if (F_status_is_error_not(setting->state.status)) {
            setting->state.status = status;
          }
        } // for

        f_file_stream_unlock(main->output.to);
      }
    }

    if (setting->state.status == F_status_set_error(F_interrupt)) {
      fll_program_print_signal_received(main->warning, main->signal_received);
    }

    if ((setting->flag & status_code_main_flag_print_last_e) && main->message.verbosity > f_console_verbosity_error_e) {
      fll_print_dynamic_raw(f_string_eol_s, main->message.to);
    }
  }
#endif // _di_status_code_main_

#ifdef __cplusplus
} // extern "C"
#endif
