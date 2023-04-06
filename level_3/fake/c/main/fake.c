#include "fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_main_
  void fake_main(fake_main_t * const main) {

    if (!main) return;

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & fake_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      return;
    }

    if ((main->setting.flag & fake_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
    }

    main->setting.state.status = F_none;

    if (main->setting.flag & (fake_main_flag_help_e | fake_main_flag_version_e | fake_main_flag_copyright_e)) {
      if (main->setting.flag & fake_main_flag_help_e) {
        fake_print_message_help(&main->program.message);
      }
      else if (main->setting.flag & fake_main_flag_version_e) {
        fll_program_print_version(&main->program.message, fake_program_version_s);
      }
      else if (main->setting.flag & fake_main_flag_copyright_e) {
        fll_program_print_copyright(&main->program.message);
      }

      if ((main->setting.flag & fake_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      return;
    }

    if ((main->setting.flag & fake_main_flag_operation_build_e) && (main->setting.flag & fake_main_flag_operation_make_e)) {
      main->setting.state.status = F_status_set_error(F_parameter);

      fake_print_error_parameter_operation_not_with(&main->program.error, fake_other_operation_build_s, fake_other_operation_make_s);

      if ((main->setting.flag & fake_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      return;
    }

    fake_data_t data = fake_data_t_initialize;
    data.main = main;

    fake_path_generate(&data);

    if (F_status_is_error(main->setting.state.status)) {
      fake_data_delete(&data);

      if ((main->setting.flag & fake_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      return;
    }

    if ((main->program.pipe & fll_program_data_pipe_input_e) && !(main->setting.flag & fake_main_flag_operation_e)) {
      data.file_data_build_fakefile.used = 0;

      main->setting.state.status = f_string_dynamic_append(f_string_ascii_minus_s, &data.file_data_build_fakefile);

      if (F_status_is_error_not(main->setting.state.status)) {
        main->setting.fakefile.used = 0;

        main->setting.state.status = f_string_dynamic_append(f_string_ascii_minus_s, &main->setting.fakefile);
      }

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append));
      }
    }

    if (F_status_is_error_not(main->setting.state.status)) {
      f_array_length_t i = 0;

      // Pre-process and perform validation when "clean" is before a "build" or "make" command as a safety check.
      {
        uint8_t has_clean = F_false;

        for (; i < main->setting.operations.used; ++i) {

          if (main->setting.operations.array[i] == fake_operation_clean_e) {
            has_clean = F_true;
          }
          else if (main->setting.operations.array[i] == fake_operation_build_e || main->setting.operations.array[i] == fake_operation_make_e) {

            // If the first operation is clean and a make or build operation exists, then the clean operation requires the appropriate settings file or fakefile file.
            if (has_clean) {
              data.operation = main->setting.operations.array[i];

              fake_validate_parameter_paths(&data);

              if (F_status_is_error_not(main->setting.state.status) && !(main->program.pipe & fll_program_data_pipe_input_e)) {
                main->setting.state.status = f_file_is(
                  (main->setting.operations.array[i] == fake_operation_build_e)
                    ? data.file_data_build_settings
                    : data.file_data_build_fakefile,
                  F_file_type_regular_d, F_false
                );

                if (main->setting.state.status == F_false) {
                  main->setting.state.status = F_status_set_error(F_file_not);
                }

                if (F_status_is_error(main->setting.state.status)) {
                  fake_print_error_file(
                    &main->program.error,
                    macro_fake_f(f_file_is),
                    (main->setting.operations.array[i] == fake_operation_build_e)
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

          if (fake_signal_check(main)) break;
        } // for
      }

      {
        bool check_paths = F_true;

        for (i = 0; i < main->setting.operations.used; ++i) {

          data.operation = main->setting.operations.array[i];

          if (data.operation == fake_operation_build_e) {
            if (check_paths) {
              fake_validate_parameter_paths(&data);
              check_paths = F_false;
            }

            if (F_status_is_error_not(main->setting.state.status)) {
              if (i && main->program.message.verbosity > f_console_verbosity_error_e) {
                fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
              }

              fake_build_operate(&data, 0, main->program.pipe & fll_program_data_pipe_input_e);
            }
          }
          else if (data.operation == fake_operation_clean_e) {
            if (i && main->program.message.verbosity > f_console_verbosity_error_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
            }

            fake_clean_operate(&data);

            // Reset in case next operation needs files.
            check_paths = F_true;
          }
          else if (data.operation == fake_operation_make_e) {
            if (check_paths) {
              fake_validate_parameter_paths(&data);
              check_paths = F_false;
            }

            if (F_status_is_error_not(main->setting.state.status)) {
              if (i && main->program.message.verbosity > f_console_verbosity_error_e) {
                fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
              }

              fake_make_operate(&data);
              if (main->setting.state.status == F_child) break;
            }
          }
          else if (data.operation == fake_operation_skeleton_e) {
            if (i && main->program.message.verbosity > f_console_verbosity_error_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
            }

            fake_skeleton_operate(&data);

            // Skeleton is supposed to guarantee these.
            check_paths = F_false;
          }

          if (main->setting.state.status == F_child) break;
          if (F_status_set_fine(main->setting.state.status) == F_interrupt || fake_signal_check(main)) break;
          if (F_status_is_error(main->setting.state.status)) break;
        } // for
      }
    }

    if (F_status_is_error(main->setting.state.status)) {
      if (F_status_set_fine(main->setting.state.status) == F_interrupt) {
        fake_print_operation_cancelled(&main->program.message, data.operation);
      }
      else {
        fake_print_error_failure_operation(&main->program.error, data.operation);
      }
    }
    else if (main->setting.state.status != F_child) {
      if (F_status_is_error_not(main->setting.state.status)) {
        main->setting.state.status = F_none;

        fake_print_operation_all_complete(&main->program.message);
      }
    }

    if ((main->setting.flag & fake_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
    }

    fake_data_delete(&data);
  }
#endif // _di_fake_main_

#ifndef _di_fake_execute_
  int fake_execute(fake_data_t * const data, const f_string_maps_t environment, const f_string_static_t program) {

    if (!data || !data->main) return 1;
    if (F_status_is_error(data->main->setting.state.status)) return 1;

    fake_main_t * const main = data->main;

    if (main->program.error.verbosity >= f_console_verbosity_verbose_e) {
      f_file_stream_lock(main->program.message.to);

      f_print_dynamic(program, main->program.message.to);

      for (f_array_length_t i = 0; i < main->cache_arguments.used; ++i) {

        if (!main->cache_arguments.array[i].used) continue;

        fl_print_format(" %Q", main->program.message.to, main->cache_arguments.array[i]);
      } // for

      f_print_dynamic_raw(f_string_eol_s, main->program.message.to);

      f_file_stream_flush(main->program.message.to);
      f_file_stream_unlock(main->program.message.to);
    }

    int return_code = 0;

    if (program.used) {

      // Child processes should receive all signals, without blocking.
      f_signal_how_t signals = f_signal_how_t_initialize;
      f_signal_set_empty(&signals.block);
      f_signal_set_fill(&signals.block_not);

      fl_execute_parameter_t parameter = macro_fl_execute_parameter_t_initialize(0, 0, &environment, &signals, 0);

      main->setting.state.status = fll_execute_program(program, main->cache_arguments, &parameter, 0, (void *) &return_code);
      if (fake_signal_check(data->main)) return return_code;
      if (main->setting.state.status == F_child) return return_code;
    }
    else {
      main->setting.state.status = F_status_set_error(F_file_found_not);
    }

    if (return_code) {
      main->setting.state.status = F_status_set_error(F_failure);
    }
    else if (F_status_is_error(main->setting.state.status)) {
      return_code = 1;

      if (F_status_set_fine(main->setting.state.status) == F_file_found_not) {
        fake_print_error_execute_program_not_found(&main->program.error, program);
      }
      else {
        fake_print_error(&main->program.error, macro_fake_f(fll_execute_program));
      }
    }

    return return_code;
  }
#endif // _di_fake_execute_

#ifndef _di_fake_file_buffer_
  void fake_file_buffer(fake_data_t * const data, const f_string_static_t path_file, const bool required, f_string_dynamic_t * const buffer) {

    if (!data || !data->main || !buffer) return;
    if (fake_signal_check(data->main)) return;

    fake_main_t * const main = data->main;

    main->setting.state.status = f_file_exists(path_file, F_true);

    if (F_status_is_error(main->setting.state.status)) {
      fake_print_error_file(&main->program.error, macro_fake_f(f_file_exists), path_file, f_file_operation_find_s, fll_error_file_type_file_e);

      return;
    }

    if (main->setting.state.status == F_true) {
      {
        off_t size_file = 0;

        main->setting.state.status = f_file_size(path_file, F_true, &size_file);

        if (F_status_is_error(main->setting.state.status)) {
          fake_print_error_file(&main->program.error, macro_fake_f(f_file_size), path_file, f_file_operation_read_s, fll_error_file_type_file_e);

          return;
        }

        if (size_file > fake_max_initial_buffer_d) {
          size_file = fake_max_initial_buffer_d;
        }

        main->setting.state.status = f_string_dynamic_increase_by(size_file, buffer);

        if (F_status_is_error(main->setting.state.status)) {
          const f_string_static_t message = macro_f_string_static_t_initialize("allocate buffer size for", 0, 24);

          fake_print_error_file(&main->program.error, macro_fake_f(f_string_dynamic_increase_by), path_file, message, fll_error_file_type_file_e);

          return;
        }

        main->setting.state.status = F_true;
      }

      f_file_t file = f_file_t_initialize;

      main->setting.state.status = f_file_stream_open(path_file, f_string_empty_s, &file);

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error_file(&main->program.error, macro_fake_f(f_file_stream_open), path_file, f_file_operation_open_s, fll_error_file_type_file_e);

        return;
      }

      main->setting.state.status = f_file_stream_read(file, buffer);

      f_file_stream_flush(file);
      f_file_stream_close(&file);

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error_file(&main->program.error, macro_fake_f(f_file_read), path_file, f_file_operation_read_s, fll_error_file_type_file_e);
      }
      else {
        main->setting.state.status = F_none;
      }
    }
    else {
      if (required) {
        main->setting.state.status = F_status_set_error(F_file_found_not);

        fake_print_error_file(&main->program.error, macro_fake_f(f_file_exists), path_file, f_file_operation_find_s, fll_error_file_type_file_e);
      }
    }
  }
#endif // _di_fake_file_buffer_

#ifndef _di_fake_pipe_buffer_
  void fake_pipe_buffer(fake_data_t * const data, f_string_dynamic_t * const buffer) {

    if (!data || !data->main || !buffer) return;

    fake_main_t * const main = data->main;

    f_file_t file = f_file_t_initialize;

    file.id = F_type_descriptor_input_d;
    file.stream = F_type_input_d;
    file.size_read = fake_allocation_pipe_d;

    main->setting.state.status = f_string_dynamic_increase_by(fake_max_initial_buffer_d, buffer);

    if (F_status_is_error(main->setting.state.status)) {
      const f_string_static_t message = macro_f_string_static_t_initialize("allocate buffer size for", 0, 24);
      fake_print_error_file(&main->program.error, macro_fake_f(f_string_dynamic_increase_by), f_string_ascii_minus_s, message, fll_error_file_type_file_e);

      return;
    }

    // Reset the error state before processing.
    clearerr(F_type_input_d);

    do {
      if (fake_signal_check(main)) return;

      main->setting.state.status = f_file_stream_read_block(file, buffer);

    } while (F_status_is_fine(main->setting.state.status) && main->setting.state.status != F_interrupt && main->setting.state.status != F_none_eof);

    if (F_status_is_error(main->setting.state.status)) {
      fake_print_error_file(&main->program.error, macro_fake_f(f_file_stream_read_block), f_string_ascii_minus_s, f_file_operation_read_s, fll_error_file_type_file_e);
    }
    else {
      main->setting.state.status = F_none;
    }
  }
#endif // _di_fake_pipe_buffer_

#ifndef _di_fake_validate_parameter_paths_
  void fake_validate_parameter_paths(fake_data_t * const data) {

    if (!data || !data->main) return;
    if (fake_signal_check(data->main)) return;

    fake_main_t * const main = data->main;

    const f_string_static_t names[] = {
      fake_long_build_s,
      fake_long_data_s,
      fake_long_documents_s,
      fake_long_licenses_s,
      fake_long_sources_s,
      fake_long_work_s,
    };

    const f_string_dynamic_t values[] = {
      main->setting.build,
      main->setting.data,
      main->setting.documents,
      main->setting.licenses,
      main->setting.sources,
      main->setting.work,
    };

    uint8_t requireds[] = {
      F_false, // fake_long_build_s
      (main->program.pipe & fll_program_data_pipe_input_e) ? F_false : F_true, // fake_long_data_s
      F_false, // fake_long_documents_s
      F_false, // fake_long_licenses_s
      F_false, // fake_long_sources_s
      F_false, // fake_long_work_s
    };

    struct stat directory_stat;

    main->setting.state.status = F_none;

    // Check only expected operations (fake_operation_clean_e and fake_operation_skeleton_e should not call this function).
    if (data->operation == fake_operation_make_e) {
      if (main->program.parameters.array[fake_parameter_fakefile_e].result == f_console_result_none_e) {
        if (main->setting.build.used && f_file_exists(main->setting.build, F_false) != F_true) {
          if (f_file_exists(fake_default_fakefile_s, F_false) == F_true) {
            requireds[1] = F_false; // fake_long_data_s
          }
        }
      }
    }

    // If a custom --data or a custom --fakefile parameter is passed and uses an absolute or relative to current path, then do not check.
    if (data->operation == fake_operation_make_e || data->operation == fake_operation_build_e) {
      f_console_parameter_t * const parameter = &main->program.parameters.array[
        data->operation == fake_operation_make_e
          ? fake_parameter_fakefile_e
          : fake_parameter_settings_e
        ];

      if (parameter->result & f_console_result_value_e) {
        const f_array_length_t index = parameter->values.array[parameter->values.used - 1];

        if (f_path_is_absolute(main->program.parameters.arguments.array[index]) == F_true || f_path_is_relative_current(main->program.parameters.arguments.array[index]) == F_true) {
          requireds[1] = F_none; // fake_long_data_s
        }
        else {
          main->setting.state.status = f_file_exists(main->program.parameters.arguments.array[index], F_true);

          if (F_status_is_error_not(main->setting.state.status) && main->setting.state.status == F_true) {
            requireds[1] = F_none; // fake_long_data_s
          }
        }
      }
    }

    for (uint8_t i = 0; i < 6; ++i) {

      if (requireds[i] != F_none && values[i].used) {
        memset(&directory_stat, 0, sizeof(struct stat));

        main->setting.state.status = f_file_stat(values[i], F_true, &directory_stat);

        if (main->setting.state.status == F_status_set_error(F_file_found_not)) {
          main->setting.state.status = F_status_set_error(F_directory_found_not);
        }

        if (F_status_is_error(main->setting.state.status)) {
          if (F_status_set_fine(main->setting.state.status) != F_directory_found_not || requireds[i]) {
            fake_print_error_file(&main->program.error, macro_fake_f(f_file_stat), values[i], f_file_operation_access_s, fll_error_file_type_directory_e);

            return;
          }
        }
      }
      else if (requireds[i] == F_true) {
        fake_print_error_parameter_directory_not_found_path(&main->program.error, f_console_symbol_long_normal_s, names[i], values[i]);

        main->setting.state.status = F_status_set_error(F_directory_found_not);

        return;
      }
    } // for

    main->setting.state.status = F_none;
  }
#endif // _di_fake_validate_parameter_paths_

#ifdef __cplusplus
} // extern "C"
#endif
