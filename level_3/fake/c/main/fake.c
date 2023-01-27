#include "fake.h"
#include "private-common.h"
#include "private-fake.h"
#include "private-fake-path_generate.h"
#include "private-build.h"
#include "private-clean.h"
#include "private-make.h"
#include "private-make-operate.h"
#include "private-print.h"
#include "private-skeleton.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_main_
  void fake_main(fll_program_data_t * const main, fake_setting_t * const setting) {

    if (!main || !setting) return;

    if (F_status_is_error(setting->status)) {
      fake_print_line_last_locked(setting, main->error);

      return;
    }

    setting->status = F_none;

    if (setting->flag & fake_main_flag_help_e) {
      fake_print_help(setting, main->message);

      return;
    }

    if (setting->flag & fake_main_flag_version_e) {
      fll_program_print_version(main->message, (setting->line_first.used ? 0x1 : 0x0) | (setting->line_last.used ? 0x2 : 0x0), fake_program_version_s);

      return;
    }

    if (setting->flag & fake_main_flag_copyright_e) {
      fll_program_print_copyright(main->message, (setting->line_first.used ? 0x1 : 0x0) | (setting->line_last.used ? 0x2 : 0x0));

      return;
    }

    if ((setting->flag & fake_data_flag_operation_build_e) && (setting->flag & fake_data_flag_operation_make_e)) {
      setting->status = F_status_set_error(F_parameter);

      fake_print_error_parameter_operation_not_with(setting, main->error, fake_other_operation_build_s, fake_other_operation_make_s);

      return;
    }

    fake_data_t data = fake_data_t_initialize;
    data.main = main;
    data.setting = setting;

    setting->status = fake_path_generate(&data); // @todo needs to be updated regarding the new data structure.

    if (F_status_is_error(setting->status)) {
      fake_data_delete(&data);

      return;
    }

    if ((main->pipe & fll_program_data_pipe_input_e) && !(data.setting->flag & fake_data_flag_operation_e)) {
      data.file_data_build_fakefile.used = 0;

      setting->status = f_string_dynamic_append(f_string_ascii_minus_s, &data.file_data_build_fakefile);

      if (F_status_is_error(setting->status)) {
        fake_print_error(setting, setting->status, main->error, macro_fake_f(f_string_dynamic_append));
      }
      else {
        setting->fakefile.used = 0;

        setting->status = f_string_dynamic_append(f_string_ascii_minus_s, &setting->fakefile);
      }
    }

    {
      f_array_length_t i = 0;

      // Pre-process and perform validation when "clean" is before a "build" or "make" command as a safety check.
      {
        uint8_t has_clean = F_false;

        for (; i < setting->operations.used; ++i) {

          if (setting->operations.array[i] == fake_operation_clean_e) {
            has_clean = F_true;
          }
          else if (setting->operations.array[i] == fake_operation_build_e || setting->operations.array[i] == fake_operation_make_e) {

            // If the first operation is clean and a make or build operation exists, then the clean operation requires the appropriate settings file or fakefile file.
            if (has_clean) {
              data.operation = setting->operations.array[i];

              setting->status = fake_validate_parameter_paths(&data);

              if (F_status_is_error_not(setting->status) && !(main->pipe & fll_program_data_pipe_input_e)) {
                setting->status = f_file_is(
                  setting->operations.array[i] == fake_operation_build_e
                    ? data.file_data_build_settings
                    : data.file_data_build_fakefile,
                  F_file_type_regular_d, F_false
                );

                if (setting->status == F_false) {
                  setting->status = F_status_set_error(F_file_not);
                }

                if (F_status_is_error(setting->status)) {
                  fake_print_error_file(
                    setting,
                    F_status_set_fine(setting->status),
                    main->error,
                    macro_fake_f(f_file_is),
                    setting->operations.array[i] == fake_operation_build_e
                      ? data.file_data_build_settings
                      : data.file_data_build_fakefile,
                    fake_common_file_path_access_s,
                    fll_error_file_type_file_e
                  );
                }
              }
            }

            break;
          }

          if (!((++main->signal_check) % fake_signal_check_short_d)) {
            if (fll_program_standard_signal_received(main)) {
              fll_program_print_signal_received(main->warning, setting->line_first, main->signal_received);

              setting->status = F_status_set_error(F_interrupt);

              break;
            }

            main->signal_check = 0;
          }
        } // for
      }

      {
        bool check_paths = F_true;

        for (i = 0; i < setting->operations.used; ++i) {

          data.operation = setting->operations.array[i];

          if (data.operation == fake_operation_build_e) {
            if (check_paths) {
              setting->status = fake_validate_parameter_paths(&data);
              check_paths = F_false;
            }

            if (F_status_is_error_not(setting->status)) {
              setting->status = fake_build_operate(&data, 0, main->pipe & fll_program_data_pipe_input_e);
            }
          }
          else if (data.operation == fake_operation_clean_e) {
            setting->status = fake_clean_operate(&data);

            // Reset in case next operation needs files.
            check_paths = F_true;
          }
          else if (data.operation == fake_operation_make_e) {
            if (check_paths) {
              setting->status = fake_validate_parameter_paths(&data);
              check_paths = F_false;
            }

            if (F_status_is_error_not(setting->status)) {
              setting->status = fake_make_operate(&data);
              if (setting->status == F_child) break;
            }
          }
          else if (data.operation == fake_operation_skeleton_e) {
            setting->status = fake_skeleton_operate(&data);

            // Skeleton is supposed to guarantee these.
            check_paths = F_false;
          }

          if (setting->status == F_child) break;

          if (!((++main->signal_check) % fake_signal_check_short_d)) {
            if (fll_program_standard_signal_received(main)) {
              fll_program_print_signal_received(main->warning, setting->line_first, main->signal_received);

              setting->status = F_status_set_error(F_interrupt);

              break;
            }

            main->signal_check = 0;
          }

          if (F_status_is_error(setting->status)) break;
        } // for
      }
    }

    if (F_status_is_error(setting->status)) {
      fake_print_error_failure_operation(setting, main->error, data.operation);
      fake_print_line_last_locked(setting, main->error);
    }
    else if (setting->status != F_child) {
      fake_print_operation_all_complete(setting, main->message);

      if (setting->status != F_interrupt) {
        fake_print_line_last_locked(setting, main->message);
      }
    }

    fake_data_delete(&data);
  }
#endif // _di_fake_main_

#ifdef __cplusplus
} // extern "C"
#endif
