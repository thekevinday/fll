#include "fss_status_code.h"
#include "private-common.h"
#include "private-fss_status_code.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_status_code_main_
  void fss_status_code_main(fll_program_data_t * const main, fss_status_code_setting_t * const setting) {

    if (!main || !setting || F_status_is_error(setting->status)) return;

    setting->status = F_none;

    if (setting->flag & fss_status_code_main_flag_help_e) {
      fss_status_code_print_help(setting, main->message);

      return;
    }

    if (setting->flag & fss_status_code_main_flag_version_e) {
      fll_program_print_version(main->message, fss_status_code_program_version_s);

      return;
    }

    f_status_t status2 = F_none;

    if (setting->flag & fss_status_code_main_flag_number_e) {
      if (main->pipe & fll_program_data_pipe_input_e) {
        // @todo call fss_status_code_process_number() here for all main from pipe that is space separated.
      }

      if (main->parameters.remaining.used) {
        f_file_stream_lock(main->output.to);

        for (f_array_length_t i = 0; i < main->parameters.remaining.used; ++i) {

          if (!((++main->signal_check) % fss_status_code_signal_check_d)) {
            if (fll_program_standard_signal_received(main)) {
              fll_program_print_signal_received(main->warning, setting->line_first, main->signal_received);

              setting->status = F_status_set_error(F_signal);

              break;
            }

            main->signal_check = 0;
          }

          status2 = fss_status_code_process_number(main, setting, main->parameters.arguments.array[main->parameters.remaining.array[i]]);

          if (F_status_is_error(status2) && setting->status == F_none) {
            setting->status = status2;
          }
        } // for

        f_file_stream_unlock(main->output.to);
      }
    }
    else if (setting->flag & fss_status_code_main_flag_error_e || setting->flag & fss_status_code_main_flag_warning_e || setting->flag & fss_status_code_main_flag_fine_e) {
      if (main->pipe & fll_program_data_pipe_input_e) {
        // @todo call fss_status_code_process_check() here for all main from pipe that is space separated.
      }

      if (main->parameters.remaining.used) {
        f_file_stream_lock(main->output.to);

        for (f_array_length_t i = 0; i < main->parameters.remaining.used; ++i) {

          if (!((++main->signal_check) % fss_status_code_signal_check_d)) {
            if (fll_program_standard_signal_received(main)) {
              fll_program_print_signal_received(main->warning, setting->line_first, main->signal_received);

              setting->status = F_status_set_error(F_signal);

              break;
            }

            main->signal_check = 0;
          }

          status2 = fss_status_code_process_check(main, setting, main->parameters.arguments.array[main->parameters.remaining.array[i]]);

          if (F_status_is_error(status2) && setting->status == F_none) {
            setting->status = status2;
          }
        } // for

        f_file_stream_unlock(main->output.to);
      }
    }
    else {
      if (main->pipe & fll_program_data_pipe_input_e) {
        // @todo call fss_status_code_process_normal() here for all main from pipe that is space separated.
      }

      if (main->parameters.remaining.used) {
        f_file_stream_lock(main->output.to);

        for (f_array_length_t i = 0; i < main->parameters.remaining.used; ++i) {

          if (!((++main->signal_check) % fss_status_code_signal_check_d)) {
            if (fll_program_standard_signal_received(main)) {
              fll_program_print_signal_received(main->warning, setting->line_first, main->signal_received);

              setting->status = F_status_set_error(F_signal);

              break;
            }

            main->signal_check = 0;
          }

          status2 = fss_status_code_process_normal(main, setting, main->parameters.arguments.array[main->parameters.remaining.array[i]]);

          if (F_status_is_error(status2) && setting->status == F_none) {
            setting->status = status2;
          }
        } // for

        f_file_stream_unlock(main->output.to);
      }
    }

    if (F_status_is_error(setting->status)) {
      fss_status_code_print_line_last(setting, main->error, F_true);
    }
    else if (setting->status != F_interrupt) {
      fss_status_code_print_line_last(setting, main->message, F_true);
    }
  }
#endif // _di_fss_status_code_main_

#ifdef __cplusplus
} // extern "C"
#endif
