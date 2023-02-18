#include "fake.h"
#include "fake/path_generate.h"
#include "build.h"
#include "clean.h"
#include "make.h"
#include "make/operate.h"
#include "print.h"
#include "skeleton.h"

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

    if ((setting->flag & fake_main_flag_operation_build_e) && (setting->flag & fake_main_flag_operation_make_e)) {
      setting->status = F_status_set_error(F_parameter);

      fake_print_error_parameter_operation_not_with(setting, main->error, fake_other_operation_build_s, fake_other_operation_make_s);

      return;
    }

    fake_data_t data = fake_data_t_initialize;
    data.main = main;
    data.setting = setting;

    setting->status = fake_path_generate(&data);

    if (F_status_is_error(setting->status)) {
      fake_data_delete(&data);

      return;
    }

    if ((main->pipe & fll_program_data_pipe_input_e) && !(data.setting->flag & fake_main_flag_operation_e)) {
      data.file_data_build_fakefile.used = 0;

      setting->status = f_string_dynamic_append(f_string_ascii_minus_s, &data.file_data_build_fakefile);

      if (F_status_is_error(setting->status)) {
        fake_print_error(setting, main->error, setting->status, macro_fake_f(f_string_dynamic_append));
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
                    main->error,
                    F_status_set_fine(setting->status),
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
      if (F_status_set_fine(setting->status) == F_interrupt) {
        fake_print_operation_cancelled(setting, main->message, data.operation);
      }
      else {
        fake_print_error_failure_operation(setting, main->error, data.operation);
      }

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

#ifndef _di_fake_execute_
  int fake_execute(fake_data_t * const data, const f_string_maps_t environment, const f_string_static_t program, const f_string_statics_t arguments, f_status_t * const status) {

    if (F_status_is_error(*status)) return 1;

    if (data->main->error.verbosity >= f_console_verbosity_verbose_e) {
      f_file_stream_lock(data->main->message.to);

      f_print_dynamic(program, data->main->message.to);

      for (f_array_length_t i = 0; i < arguments.used; ++i) {

        if (!arguments.array[i].used) continue;

        fl_print_format(" %Q", data->main->message.to, arguments.array[i]);
      } // for

      f_print_dynamic_raw(f_string_eol_s, data->main->message.to);

      f_file_stream_flush(data->main->message.to);
      f_file_stream_unlock(data->main->message.to);
    }

    int return_code = 0;

    if (program.used) {

      // Child processes should receive all signals, without blocking.
      f_signal_how_t signals = f_signal_how_t_initialize;
      f_signal_set_empty(&signals.block);
      f_signal_set_fill(&signals.block_not);

      fl_execute_parameter_t parameter = macro_fl_execute_parameter_t_initialize(0, 0, &environment, &signals, 0);

      *status = fll_execute_program(program, arguments, &parameter, 0, (void *) &return_code);

      if (fll_program_standard_signal_received(data->main)) {
        fll_program_print_signal_received(data->main->warning, data->setting->line_first, data->main->signal_received);

        *status = F_status_set_error(F_interrupt);

        return 0;
      }

      if (*status == F_child) return return_code;
    }
    else {
      *status = F_status_set_error(F_file_found_not);
    }

    if (return_code != 0) {
      *status = F_status_set_error(F_failure);
    }
    else if (F_status_is_error(*status)) {
      return_code = 1;

      if (F_status_set_fine(*status) == F_file_found_not) {
        if (data->main->error.verbosity > f_console_verbosity_quiet_e) {
          f_file_stream_lock(data->main->error.to);

          fl_print_format("%r%[%QFailed to find program '%]", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
          fl_print_format("%[%Q%]", data->main->error.to, data->main->error.notable, program, data->main->error.notable);
          fl_print_format("%[' for executing.%]%r", data->main->error.to, data->main->error.context, data->main->error.context, f_string_eol_s);

          f_file_stream_unlock(data->main->error.to);
        }
      }
      else {
        fake_print_error(data->setting, data->main->error, *status, macro_fake_f(fll_execute_program));
      }
    }

    return return_code;
  }
#endif // _di_fake_execute_

#ifndef _di_fake_file_buffer_
  f_status_t fake_file_buffer(fake_data_t * const data, const f_string_static_t path_file, const bool required, f_string_dynamic_t * const buffer) {

    if (fll_program_standard_signal_received(data->main)) {
      fll_program_print_signal_received(data->main->warning, data->setting->line_first, data->main->signal_received);

      return F_status_set_error(F_interrupt);
    }

    f_status_t status = f_file_exists(path_file, F_true);

    if (F_status_is_error(status)) {
      fake_print_error_file(data->setting, data->main->error, status, macro_fake_f(f_file_exists), path_file, f_file_operation_find_s, fll_error_file_type_file_e);

      return status;
    }

    if (status == F_true) {
      {
        off_t size_file = 0;

        status = f_file_size(path_file, F_true, &size_file);

        if (F_status_is_error(status)) {
          fake_print_error_file(data->setting, data->main->error, status, macro_fake_f(f_file_size), path_file, f_file_operation_read_s, fll_error_file_type_file_e);

          return status;
        }

        if (size_file > fake_common_max_initial_buffer_d) {
          size_file = fake_common_max_initial_buffer_d;
        }

        status = f_string_dynamic_increase_by(size_file, buffer);

        if (F_status_is_error(status)) {
          const f_string_static_t message = macro_f_string_static_t_initialize("allocate buffer size for", 0, 24);

          fake_print_error_file(data->setting, data->main->error, status, macro_fake_f(f_string_dynamic_increase_by), path_file, message, fll_error_file_type_file_e);

          return status;
        }

        status = F_true;
      }

      f_file_t file = f_file_t_initialize;

      status = f_file_stream_open(path_file, f_string_empty_s, &file);

      if (F_status_is_error(status)) {
        fake_print_error_file(data->setting, data->main->error, status, macro_fake_f(f_file_stream_open), path_file, f_file_operation_open_s, fll_error_file_type_file_e);

        return status;
      }

      status = f_file_stream_read(file, buffer);

      f_file_stream_flush(file);
      f_file_stream_close(&file);

      if (F_status_is_error(status)) {
        fake_print_error_file(data->setting, data->main->error, status, macro_fake_f(f_file_read), path_file, f_file_operation_read_s, fll_error_file_type_file_e);
      }
    }
    else {
      if (required) {
        status = F_status_set_error(F_file_found_not);

        fake_print_error_file(data->setting, data->main->error, status, macro_fake_f(f_file_exists), path_file, f_file_operation_find_s, fll_error_file_type_file_e);
      }
    }

    return status;
  }
#endif // _di_fake_file_buffer_

#ifndef _di_fake_pipe_buffer_
  f_status_t fake_pipe_buffer(fake_data_t * const data, f_string_dynamic_t * const buffer) {

    f_status_t status = F_none;
    f_file_t file = f_file_t_initialize;

    file.id = F_type_descriptor_input_d;
    file.stream = F_type_input_d;
    file.size_read = fake_default_allocation_pipe_d;

    status = f_string_dynamic_increase_by(fake_common_max_initial_buffer_d, buffer);

    if (F_status_is_error(status)) {
      const f_string_static_t message = macro_f_string_static_t_initialize("allocate buffer size for", 0, 24);
      fake_print_error_file(data->setting, data->main->error, status, macro_fake_f(f_string_dynamic_increase_by), f_string_ascii_minus_s, message, fll_error_file_type_file_e);

      return status;
    }

    // Reset the error state before processing.
    clearerr(F_type_input_d);

    do {
      if (fll_program_standard_signal_received(data->main)) {
        fll_program_print_signal_received(data->main->warning, data->setting->line_first, data->main->signal_received);

        return F_status_set_error(F_interrupt);
      }

      status = f_file_stream_read_block(file, buffer);

    } while (F_status_is_fine(status) && status != F_interrupt && status != F_none_eof);

    if (F_status_is_error(status)) {
      fake_print_error_file(data->setting, data->main->error, status, macro_fake_f(f_file_stream_read_block), f_string_ascii_minus_s, f_file_operation_read_s, fll_error_file_type_file_e);
    }

    return status;
  }
#endif // _di_fake_pipe_buffer_

#ifndef _di_fake_validate_parameter_paths_
  f_status_t fake_validate_parameter_paths(fake_data_t * const data) {

    if (fll_program_standard_signal_received(data->main)) {
      fll_program_print_signal_received(data->main->warning, data->setting->line_first, data->main->signal_received);

      return F_status_set_error(F_interrupt);
    }

    const f_string_static_t names[] = {
      fake_long_build_s,
      fake_long_data_s,
      fake_long_documents_s,
      fake_long_licenses_s,
      fake_long_sources_s,
      fake_long_work_s,
    };

    const f_string_dynamic_t values[] = {
      data->setting->build,
      data->setting->data,
      data->setting->documents,
      data->setting->licenses,
      data->setting->sources,
      data->setting->work,
    };

    uint8_t requireds[] = {
      F_false, // fake_long_build_s
      (data->main->pipe & fll_program_data_pipe_input_e) ? F_false : F_true, // fake_long_data_s
      F_false, // fake_long_documents_s
      F_false, // fake_long_licenses_s
      F_false, // fake_long_sources_s
      F_false, // fake_long_work_s
    };

    struct stat directory_stat;

    f_status_t status = F_none;

    // Check only expected operations (fake_operation_clean_e and fake_operation_skeleton_e should not call this function).
    if (data->operation == fake_operation_make_e) {
      if (data->main->parameters.array[fake_parameter_fakefile_e].result == f_console_result_none_e) {
        if (data->setting->build.used && f_file_exists(data->setting->build, F_false) != F_true) {
          if (f_file_exists(fake_default_fakefile_s, F_false) == F_true) {
            requireds[1] = F_false; // fake_long_data_s
          }
        }
      }
    }

    // If a custom --data or a custom --fakefile parameter is passed and uses an absolute or relative to current path, then do not check.
    if (data->operation == fake_operation_make_e || data->operation == fake_operation_build_e) {
      f_console_parameter_t * const parameter = &data->main->parameters.array[
        data->operation == fake_operation_make_e
          ? fake_parameter_fakefile_e
          : fake_parameter_settings_e
        ];

      if (parameter->result & f_console_result_value_e) {
        const f_array_length_t index = parameter->values.array[parameter->values.used - 1];

        if (f_path_is_absolute(data->main->parameters.arguments.array[index]) == F_true || f_path_is_relative_current(data->main->parameters.arguments.array[index]) == F_true) {
          requireds[1] = F_none; // fake_long_data_s
        }
        else {
          status = f_file_exists(data->main->parameters.arguments.array[index], F_true);

          if (F_status_is_error_not(status) && status == F_true) {
            requireds[1] = F_none; // fake_long_data_s
          }
        }
      }
    }

    for (uint8_t i = 0; i < 6; ++i) {

      if (requireds[i] != F_none && values[i].used) {
        memset(&directory_stat, 0, sizeof(struct stat));

        status = f_file_stat(values[i], F_true, &directory_stat);

        if (status == F_status_set_error(F_file_found_not)) status = F_status_set_error(F_directory_found_not);

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) != F_directory_found_not || requireds[i]) {
            fake_print_error_file(data->setting, data->main->error, status, macro_fake_f(f_file_stat), values[i], f_file_operation_access_s, fll_error_file_type_directory_e);

            return status;
          }
        }
      }
      else if (requireds[i] == F_true) {
        f_file_stream_lock(data->main->error.to);

        fl_print_format("%r%[%QNo valid path for the (required) directory parameter '%]", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
        fl_print_format("%[%r%r%]", data->main->error.to, data->main->error.notable, f_console_symbol_long_normal_s, names[i], data->main->error.notable);
        fl_print_format("%[' was found.%]%r", data->main->error.to, data->main->error.context, data->main->error.context, f_string_eol_s);

        f_file_stream_unlock(data->main->error.to);

        return F_status_set_error(F_directory_found_not);
      }
    } // for

    return F_none;
  }
#endif // _di_fake_validate_parameter_paths_

#ifndef _di_fake_verbose_print_clone_
  void fake_verbose_print_clone(const f_file_t output, const f_string_static_t source, const f_string_static_t destination) {
    fll_print_format("Cloned '%Q' to '%Q'.%r", output, source, destination, f_string_eol_s);
  }
#endif // _di_fake_verbose_print_clone_

#ifndef _di_fake_verbose_print_copy_
  void fake_verbose_print_copy(const f_file_t output, const f_string_static_t source, const f_string_static_t destination) {
    fll_print_format("Copied '%Q' to '%Q'.%r", output, source, destination, f_string_eol_s);
  }
#endif // _di_fake_verbose_print_copy_

#ifndef _di_fake_verbose_print_move_
  void fake_verbose_print_move(const f_file_t output, const f_string_static_t source, const f_string_static_t destination) {
    fll_print_format("Moved '%Q' to '%Q'.%r", output, source, destination, f_string_eol_s);
  }
#endif // _di_fake_verbose_print_move_

#ifdef __cplusplus
} // extern "C"
#endif
