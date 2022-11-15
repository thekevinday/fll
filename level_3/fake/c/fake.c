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
  f_status_t fake_main(fll_program_data_t * const main, fake_setting_t * const setting) {

    f_status_t status = F_none;

    // Load parameters.
    status = f_console_parameter_process(arguments, &main->parameters);
    if (F_status_is_error(status)) return;

    {
      f_array_length_t choice = 0;
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { fake_parameter_no_color_e, fake_parameter_light_e, fake_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        const uint8_t modes[3] = { f_color_mode_color_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        status = fll_program_parameter_process_context(choices, modes, F_true, main);

        if (F_status_is_error(status)) {
          fake_print_line_first_locked(setting, main->error);
          fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process_context", F_true);
          fake_print_line_last_locked(setting, main->error);

          return;
        }
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { fake_parameter_verbosity_quiet_e, fake_parameter_verbosity_error_e, fake_parameter_verbosity_verbose_e, fake_parameter_verbosity_debug_e, fake_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, main);

        if (F_status_is_error(status)) {
          fake_print_line_first_locked(setting, main->error);
          fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process_verbosity", F_true);
          fake_print_line_last_locked(setting, main->error);

          return;
        }
      }
    }

    if (main->parameters.array[fake_parameter_help_e].result == f_console_result_found_e) {
      fake_print_help(setting, main->message);

      return F_none;
    }

    if (main->parameters.array[fake_parameter_version_e].result == f_console_result_found_e) {
      fll_program_print_version(main->message, fake_program_version_s);

      return F_none;
    }

    status = F_none;

    fake_data_t data = fake_data_t_initialize;
    data.main = main;
    data.argv = main->parameters.arguments.array;

    f_array_length_t operations_length = main->parameters.array[fake_parameter_operation_build_e].locations.used;

    operations_length += main->parameters.array[fake_parameter_operation_clean_e].locations.used;
    operations_length += main->parameters.array[fake_parameter_operation_make_e].locations.used;
    operations_length += main->parameters.array[fake_parameter_operation_skeleton_e].locations.used;

    // Ensure the default operation always exists.
    if (operations_length) {
      data.flag |= fake_data_flag_has_operation_e;
    }
    else {
      operations_length = 1;
    }

    uint8_t operations[operations_length];
    f_string_static_t operations_name = f_string_static_t_initialize;

    if (data.flag & fake_data_flag_has_operation_e) {
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

      if (!(main->pipe & fll_program_data_pipe_input_e) && main->parameters.remaining.used) {
        status = F_status_set_error(F_parameter);

        if (main->error.verbosity > f_console_verbosity_quiet_e) {
          fll_print_format("%r%[%QYou failed to specify a valid operation.%]%r", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context, f_string_eol_s);
        }
      }
    }

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[fake_parameter_operation_build_e].locations.used && main->parameters.array[fake_parameter_operation_make_e].locations.used) {
        status = F_status_set_error(F_parameter);

        if (main->error.verbosity > f_console_verbosity_quiet_e) {
          f_file_stream_lock(main->error.to);

          fl_print_format("%r%[%QThe operation '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%]", main->error.to, main->error.notable, fake_other_operation_build_s, main->error.notable);
          fl_print_format("%[' cannot be specified with the operation '%]", main->error.to, main->error.context, main->error.context);
          fl_print_format("%[%r%]", main->error.to, main->error.notable, fake_other_operation_make_s, main->error.notable);
          fl_print_format("%['.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

          f_file_stream_unlock(main->error.to);
        }
      }
    }

    if (F_status_is_error_not(status)) {
      bool validate_parameter_paths = F_true;

      status = fake_process_console_parameters(&data);

      if (F_status_is_error_not(status)) {
        status = fake_path_generate(&data);
      }

      if (F_status_is_error(status)) {
        fake_data_delete(&data);

        return F_status_set_error(status);
      }

      {
        uint8_t i = 0;

        if ((main->pipe & fll_program_data_pipe_input_e) && !(data.flag & fake_data_flag_has_operation_e)) {
          data.file_data_build_fakefile.used = 0;

          status = f_string_dynamic_append(f_string_ascii_minus_s, &data.file_data_build_fakefile);

          if (F_status_is_error_not(status)) {
            data.fakefile.used = 0;

            status = f_string_dynamic_append(f_string_ascii_minus_s, &data.fakefile);
          }

          if (F_status_is_error(status)) {
            fll_error_print(data.main->error, F_status_set_fine(status), "f_string_dynamic_append", F_true);
          }
        }

        // Pre-process and perform validation when "clean" is before a "build" or "make" command as a safety check.
        if (operations_length > 1) {
          for (uint8_t has_clean = F_false; i < operations_length; ++i) {

            if (operations[i] == fake_operation_clean_e) {
              has_clean = F_true;
            }
            else if (operations[i] == fake_operation_build_e || operations[i] == fake_operation_make_e) {

              // If the first operation is clean and a make or build operation exists, then the clean operation requires the appropriate settings file or fakefile file.
              if (has_clean) {
                operations_name = fake_other_operation_clean_s;
                data.operation = operations[i];

                status = fake_validate_parameter_paths(&data);

                if (F_status_is_error_not(status) && !(main->pipe & fll_program_data_pipe_input_e)) {
                  f_string_static_t *path = 0;

                  if (operations[i] == fake_operation_build_e) {
                    path = &data.file_data_build_settings;
                  }
                  else {
                    path = &data.file_data_build_fakefile;
                  }

                  status = f_file_is(*path, F_file_type_regular_d, F_false);

                  if (status == F_false) {
                    status = F_status_set_error(F_file_not);
                  }

                  if (F_status_is_error(status)) {
                    fll_error_file_print(data.main->error, F_status_set_fine(status), "f_file_is", F_true, *path, fake_common_file_path_access_s, fll_error_file_type_file_e);
                  }
                }
              }

              break;
            }
          } // for
        }

        if (F_status_is_error_not(status)) {
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
                status = fake_validate_parameter_paths(&data);
                validate_parameter_paths = F_false;
              }

              if (F_status_is_error_not(status)) {
                status = fake_build_operate(&data, 0, main->pipe & fll_program_data_pipe_input_e);
              }
            }
            else if (data.operation == fake_operation_clean_e) {
              status = fake_clean_operate(&data);

              // Reset in case next operation needs files.
              validate_parameter_paths = F_true;
            }
            else if (data.operation == fake_operation_make_e) {
              if (validate_parameter_paths) {
                status = fake_validate_parameter_paths(&data);
                validate_parameter_paths = F_false;
              }

              if (F_status_is_error_not(status)) {
                status = fake_make_operate(&data);
                if (status == F_child) break;
              }
            }
            else if (data.operation == fake_operation_skeleton_e) {
              status = fake_skeleton_operate(&data);

              // Skeleton is supposed to guarantee these.
              validate_parameter_paths = F_false;
            }

            if (status == F_child) break;

            if (F_status_set_fine(status) == F_interrupt || !(i % fake_signal_check_short_d)) {
              if (fll_program_standard_signal_received(main)) {
                fll_program_print_signal_received(main->warning, setting->line_first, main->signal_received);

                status = F_status_set_error(F_interrupt);

                break;
              }

              main->signal_check = 0;
            }

            if (F_status_is_error(status)) break;
          } // for
        }

        if (F_status_is_error(status)) {
          if (main->error.verbosity > f_console_verbosity_quiet_e) {
            f_file_stream_lock(main->error.to);

            fl_print_format("%r%[%QThe operation '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%r%]", main->error.to, main->error.notable, operations_name, main->error.notable);
            fl_print_format("%[' failed.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

            f_file_stream_unlock(main->error.to);
          }
        }
      }

      if (main->error.verbosity > f_console_verbosity_error_e) {
        if (F_status_is_error_not(status) && status != F_child) {
          fll_print_format("%rAll operations complete.%r%r", main->output.to, f_string_eol_s, f_string_eol_s, f_string_eol_s);
        }
      }
    }

    if (F_status_is_error(status) && main->error.verbosity > f_console_verbosity_quiet_e) {
      if (F_status_set_fine(status) == F_interrupt) {
        f_file_stream_flush(main->output.to);
      }

      fll_print_dynamic_raw(f_string_eol_s, main->output.to);
    }

    fake_data_delete(&data);

    return status;
  }
#endif // _di_fake_main_

#ifdef __cplusplus
} // extern "C"
#endif
