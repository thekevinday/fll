#include "status_code.h"
#include "private-common.h"
#include "private-status_code.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_status_code_main_
  void status_code_main(fll_program_data_t * const main, status_code_setting_t * const setting) {

    if (!main || !setting || F_status_is_error(setting->status)) return;

    if (!setting->status_string_from || !setting->status_string_to) {

      if (!setting->status_string_from) {
        status_code_print_error_invalid_callback(setting, main->error, "status_string_from");
      }

      if (!setting->status_string_to) {
        status_code_print_error_invalid_callback(setting, main->error, "status_string_to");
      }

      setting->status = F_status_set_error(F_parameter);

      return;
    }

    setting->status = F_none;

    if (setting->flag & status_code_main_flag_help_e) {
      status_code_print_help(setting, main->message);

      return;
    }

    if (setting->flag & status_code_main_flag_version_e) {
      fll_program_print_version(main->message, status_code_program_version_s);

      return;
    }

    f_status_t status2 = F_none;

    if (setting->flag & status_code_main_flag_number_e) {
      if (main->pipe & fll_program_data_pipe_input_e) {
        // @todo call status_code_process_number() here for all main from pipe that are space separated.
      }

      if (main->parameters.remaining.used) {
        f_file_stream_lock(main->output.to);

        for (f_array_length_t i = 0; i < main->parameters.remaining.used; ++i) {

          if (!((++main->signal_check) % status_code_signal_check_d)) {
            if (fll_program_standard_signal_received(main)) {
              f_file_stream_unlock(main->output.to);

              fll_program_print_signal_received(main->warning, setting->line_first, main->signal_received);

              setting->status = F_status_set_error(F_interrupt);

              return;
            }

            main->signal_check = 0;
          }

          status2 = status_code_process_number(main, setting, main->parameters.arguments.array[main->parameters.remaining.array[i]]);

          if (F_status_is_error(status2) && setting->status == F_none) {
            setting->status = status2;
          }
        } // for

        f_file_stream_unlock(main->output.to);
      }
    }
    else if (setting->flag & status_code_main_flag_error_e || setting->flag & status_code_main_flag_warning_e || setting->flag & status_code_main_flag_fine_e) {
      if (main->pipe & fll_program_data_pipe_input_e) {
        // @todo call status_code_process_check() here for all main from pipe that is space separated.
      }

      if (main->parameters.remaining.used) {
        f_file_stream_lock(main->output.to);

        for (f_array_length_t i = 0; i < main->parameters.remaining.used; ++i) {

          if (!((++main->signal_check) % status_code_signal_check_d)) {
            if (fll_program_standard_signal_received(main)) {
              f_file_stream_unlock(main->output.to);

              fll_program_print_signal_received(main->warning, setting->line_first, main->signal_received);

              setting->status = F_status_set_error(F_interrupt);

              return;
            }

            main->signal_check = 0;
          }

          status2 = status_code_process_check(main, setting, main->parameters.arguments.array[main->parameters.remaining.array[i]]);

          if (F_status_is_error(status2) && setting->status == F_none) {
            setting->status = status2;
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
              f_file_stream_unlock(main->output.to);

              fll_program_print_signal_received(main->warning, setting->line_first, main->signal_received);

              setting->status = F_status_set_error(F_interrupt);

              return;
            }

            main->signal_check = 0;
          }

          status2 = status_code_process_normal(main, setting, main->parameters.arguments.array[main->parameters.remaining.array[i]]);

          if (F_status_is_error(status2) && setting->status == F_none) {
            setting->status = status2;
          }
        } // for

        f_file_stream_unlock(main->output.to);
      }
    }

    if (F_status_is_error(setting->status)) {
      status_code_print_line_last_locked(setting, main->error);
    }
    else if (setting->status != F_interrupt) {
      status_code_print_line_last_locked(setting, main->message);
    }
  }
#endif // _di_status_code_main_

#ifdef __cplusplus
} // extern "C"
#endif
