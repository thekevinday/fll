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
      fll_program_print_version(main->message, fake_program_version_s);

      return;
    }

    fake_data_t data = fake_data_t_initialize;
    data.main = main;
    data.setting = setting;
    data.argv = main->parameters.arguments.array;

    // @todo move operations processing into the common settings loader.
    f_array_length_t operations_length = main->parameters.array[fake_parameter_operation_build_e].locations.used;

    operations_length += main->parameters.array[fake_parameter_operation_clean_e].locations.used;
    operations_length += main->parameters.array[fake_parameter_operation_make_e].locations.used;
    operations_length += main->parameters.array[fake_parameter_operation_skeleton_e].locations.used;

    // Ensure the default operation always exists.
    if (operations_length) {
      data.flag |= fake_data_flag_operation_e;
    }
    else {
      operations_length = 1;
    }

    uint8_t operations[operations_length];
    f_string_static_t operations_name = f_string_static_t_initialize;

    if (data.flag & fake_data_flag_operation_e) {
      f_array_length_t locations[operations_length];
      f_array_length_t locations_length = 0;
      f_array_length_t i = 0;
      f_array_length_t j = 0;
      f_array_length_t k = 0;

      for (; i < main->parameters.array[fake_parameter_operation_build_e].locations.used; ++i, ++locations_length) {

        operations[locations_length] = fake_operation_build_e;
        locations[locations_length] = main->parameters.array[fake_parameter_operation_build_e].locations.array[i];
      } // for

      for (i = 0; i < main->parameters.array[fake_parameter_operation_clean_e].locations.used; ++i) {

        for (j = 0; j < locations_length; ++j) {

          if (main->parameters.array[fake_parameter_operation_clean_e].locations.array[i] < locations[j]) {
            for (k = locations_length; k > j; --k) {
              locations[k] = locations[k - 1];
              operations[k] = operations[k - 1];
            } // for

            break;
          }
        } // for

        locations[j] = main->parameters.array[fake_parameter_operation_clean_e].locations.array[i];
        operations[j] = fake_operation_clean_e;
        ++locations_length;
      } // for

      for (i = 0; i < main->parameters.array[fake_parameter_operation_make_e].locations.used; ++i) {

        for (j = 0; j < locations_length; ++j) {

          if (main->parameters.array[fake_parameter_operation_make_e].locations.array[i] < locations[j]) {
            for (k = locations_length; k > j; --k) {
              locations[k] = locations[k - 1];
              operations[k] = operations[k - 1];
            } // for

            break;
          }
        } // for

        locations[j] = main->parameters.array[fake_parameter_operation_make_e].locations.array[i];
        operations[j] = fake_operation_make_e;
        ++locations_length;
      } // for

      for (i = 0; i < main->parameters.array[fake_parameter_operation_skeleton_e].locations.used; ++i) {

        for (j = 0; j < locations_length; ++j) {

          if (main->parameters.array[fake_parameter_operation_skeleton_e].locations.array[i] < locations[j]) {
            for (k = locations_length; k > j; --k) {

              locations[k] = locations[k - 1];
              operations[k] = operations[k - 1];
            } // for

            break;
          }
        } // for

        locations[j] = main->parameters.array[fake_parameter_operation_skeleton_e].locations.array[i];
        operations[j] = fake_operation_skeleton_e;
        ++locations_length;
      } // for
    }
    else {
      operations[0] = fake_operation_make_e;
    }

    if (F_status_is_error_not(setting->status)) {
      if (main->parameters.array[fake_parameter_operation_build_e].locations.used && main->parameters.array[fake_parameter_operation_make_e].locations.used) {
        setting->status = F_status_set_error(F_parameter);

        fake_print_error_parameter_operation_not_with(setting, main->error, fake_other_operation_build_s, fake_other_operation_make_s);
      }
    }

    if (F_status_is_error_not(setting->status)) {
      bool validate_parameter_paths = F_true;

      setting->status = fake_process_console_parameters(&data);

      if (F_status_is_error_not(setting->status)) {
        setting->status = fake_path_generate(&data);
      }

      if (F_status_is_error(setting->status)) {
        fake_data_delete(&data);

        return;
      }

      {
        uint8_t i = 0;

        if ((main->pipe & fll_program_data_pipe_input_e) && !(data.flag & fake_data_flag_operation_e)) {
          data.file_data_build_fakefile.used = 0;

          setting->status = f_string_dynamic_append(f_string_ascii_minus_s, &data.file_data_build_fakefile);

          if (F_status_is_error(setting->status)) {
            fake_print_error(setting, setting->status, main->error, macro_fake_f(f_string_dynamic_append));
          }
          else {
            data.fakefile.used = 0;

            setting->status = f_string_dynamic_append(f_string_ascii_minus_s, &data.fakefile);
          }
        }

        // Pre-process and perform validation when "clean" is before a "build" or "make" command as a safety check.
        if (operations_length) {
          for (uint8_t has_clean = F_false; i < operations_length; ++i) {

            if (operations[i] == fake_operation_clean_e) {
              has_clean = F_true;
            }
            else if (operations[i] == fake_operation_build_e || operations[i] == fake_operation_make_e) {

              // If the first operation is clean and a make or build operation exists, then the clean operation requires the appropriate settings file or fakefile file.
              if (has_clean) {
                operations_name = fake_other_operation_clean_s;
                data.operation = operations[i];

                setting->status = fake_validate_parameter_paths(&data);

                if (F_status_is_error_not(setting->status) && !(main->pipe & fll_program_data_pipe_input_e)) {
                  f_string_static_t *path = 0;

                  if (operations[i] == fake_operation_build_e) {
                    path = &data.file_data_build_settings;
                  }
                  else {
                    path = &data.file_data_build_fakefile;
                  }

                  setting->status = f_file_is(*path, F_file_type_regular_d, F_false);

                  if (setting->status == F_false) {
                    setting->status = F_status_set_error(F_file_not);
                  }

                  if (F_status_is_error(setting->status)) {
                    fll_error_file_print(data.main->error, F_status_set_fine(setting->status), "f_file_is", F_true, *path, fake_common_file_path_access_s, fll_error_file_type_file_e);
                  }
                }
              }

              break;
            }
          } // for
        }

        if (F_status_is_error_not(setting->status)) {
          for (i = 0; i < operations_length; ++i) {

            data.operation = operations[i];

            if (data.operation == fake_operation_build_e) {
              operations_name = fake_other_operation_build_s;
            }
            else if (data.operation == fake_operation_clean_e) {
              operations_name = fake_other_operation_clean_s;
            }
            else if (data.operation == fake_operation_make_e) {
              operations_name = fake_other_operation_make_s;
            }
            else if (data.operation == fake_operation_skeleton_e) {
              operations_name = fake_other_operation_skeleton_s;
            }

            if (data.operation == fake_operation_build_e) {
              if (validate_parameter_paths) {
                setting->status = fake_validate_parameter_paths(&data);
                validate_parameter_paths = F_false;
              }

              if (F_status_is_error_not(setting->status)) {
                setting->status = fake_build_operate(&data, 0, main->pipe & fll_program_data_pipe_input_e);
              }
            }
            else if (data.operation == fake_operation_clean_e) {
              setting->status = fake_clean_operate(&data);

              // Reset in case next operation needs files.
              validate_parameter_paths = F_true;
            }
            else if (data.operation == fake_operation_make_e) {
              if (validate_parameter_paths) {
                setting->status = fake_validate_parameter_paths(&data);
                validate_parameter_paths = F_false;
              }

              if (F_status_is_error_not(setting->status)) {
                setting->status = fake_make_operate(&data);
                if (setting->status == F_child) break;
              }
            }
            else if (data.operation == fake_operation_skeleton_e) {
              setting->status = fake_skeleton_operate(&data);

              // Skeleton is supposed to guarantee these.
              validate_parameter_paths = F_false;
            }

            if (setting->status == F_child) break;

            if (F_status_set_fine(setting->status) == F_interrupt || !(i % fake_signal_check_short_d)) {
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

        if (F_status_is_error(setting->status)) {
          fake_print_error_failure_operation(setting, main->error, operations_name);
        }
      }

      if (setting->status != F_child) {
        fake_print_operation_all_complete(setting, main->message);
      }
    }

    if (F_status_is_error(setting->status)) {
      fake_print_line_last_locked(setting, main->error);
    }
    else if (setting->status != F_interrupt && setting->status != F_child) {
      fake_print_line_last_locked(setting, main->message);
    }

    fake_data_delete(&data);
  }
#endif // _di_fake_main_

#ifdef __cplusplus
} // extern "C"
#endif
