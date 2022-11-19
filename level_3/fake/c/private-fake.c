#include "fake.h"
#include "private-common.h"
#include "private-fake.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_execute_
  int fake_execute(fake_data_t * const data, const f_string_maps_t environment, const f_string_static_t program, const f_string_statics_t arguments, f_status_t * const status) {

    if (F_status_is_error(*status)) return 1;

    if (data->main->error.verbosity >= f_console_verbosity_verbose_e) {
      f_file_stream_lock(data->main->output);

      f_print_dynamic(program, data->main->output.to);

      for (f_array_length_t i = 0; i < arguments.used; ++i) {

        if (!arguments.array[i].used) continue;

        fl_print_format(" %Q", data->main->output.to, arguments.array[i]);
      } // for

      f_print_dynamic_raw(f_string_eol_s, data->main->output.to);

      f_file_stream_unlock(data->main->output);

      // Flush to stdout before executing command.
      f_file_stream_flush(data->main->output.to);
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
        fll_program_print_signal_received(main->warning, setting->line_first, main->signal_received);

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
          f_file_stream_lock(data->main->error);

          fl_print_format("%r%[%QFailed to find program '%]", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
          fl_print_format("%[%Q%]", data->main->error.to, data->main->error.notable, program, data->main->error.notable);
          fl_print_format("%[' for executing.%]%r", data->main->error.to, data->main->error.context, data->main->error.context, f_string_eol_s);

          f_file_stream_unlock(data->main->error);
        }
      }
      else {
        fll_error_print(data->main->error, F_status_set_fine(*status), "fll_execute_program", F_true);
      }
    }

    return return_code;
  }
#endif // _di_fake_execute_

#ifndef _di_fake_file_buffer_
  f_status_t fake_file_buffer(fake_data_t * const data, const f_string_static_t path_file, const bool required, f_string_dynamic_t * const buffer) {

    if (fll_program_standard_signal_received(data->main)) {
      fll_program_print_signal_received(main->warning, setting->line_first, main->signal_received);

      return F_status_set_error(F_interrupt);
    }

    f_file_t file = f_file_t_initialize;
    char *name_function = "f_file_exists";

    f_status_t status = f_file_exists(path_file, F_true);

    if (status == F_true) {
      {
        off_t size_file = 0;

        name_function = "f_file_size";
        status = f_file_size(path_file, F_true, &size_file);

        if (F_status_is_error_not(status)) {
          if (size_file > fake_common_initial_buffer_max_d) {
            size_file = fake_common_initial_buffer_max_d;
          }

          status = f_string_dynamic_increase_by(size_file, buffer);

          if (F_status_is_error(status)) {
            const f_string_static_t message = macro_f_string_static_t_initialize("allocate buffer size for", 0, 24);
            fll_error_file_print(data->main->error, F_status_set_fine(status), name_function, F_true, path_file, message, fll_error_file_type_file_e);

            return status;
          }
        }

        status = F_true;
      }

      name_function = "f_file_open";
      status = f_file_stream_open(path_file, f_string_empty_s, &file);

      if (F_status_is_error_not(status)) {
        name_function = "f_file_read";
        status = f_file_read(file, buffer);

        f_file_stream_flush(file);
        f_file_stream_close(&file);
      }
    }
    else if (status == F_false) {
      if (required) {
        status = F_status_set_error(F_file_found_not);
      }
    }

    if (F_status_is_error(status)) {
      fll_error_file_print(data->main->error, F_status_set_fine(status), name_function, F_true, path_file, f_file_operation_read_s, fll_error_file_type_file_e);
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

    status = f_string_dynamic_increase_by(fake_common_initial_buffer_max_d, buffer);

    if (F_status_is_error(status)) {
      const f_string_static_t message = macro_f_string_static_t_initialize("allocate buffer size for", 0, 24);
      fll_error_file_print(data->main->error, F_status_set_fine(status), "f_string_dynamic_increase_by", F_true, f_string_ascii_minus_s, message, fll_error_file_type_file_e);

      return status;
    }

    // Reset the error state before processing.
    clearerr(F_type_input_d);

    do {
      if (fll_program_standard_signal_received(data->main)) {
        fll_program_print_signal_received(main->warning, setting->line_first, main->signal_received);

        return F_status_set_error(F_interrupt);
      }

      status = f_file_stream_read_block(file, buffer);

    } while (F_status_is_fine(status) && status != F_interrupt && status != F_none_eof);

    if (F_status_is_error(status)) {
      fll_error_file_print(data->main->error, F_status_set_fine(status), "f_file_stream_read_block", F_true, f_string_ascii_minus_s, f_file_operation_read_s, fll_error_file_type_file_e);
    }

    return status;
  }
#endif // _di_fake_pipe_buffer_

#ifndef _di_fake_process_console_parameters_
  f_status_t fake_process_console_parameters(fake_data_t * const data) {

    f_status_t status = F_none;

    {
      const uint8_t parameters_id[] = {
        fake_parameter_fakefile_e,
        fake_parameter_process_e,
        fake_parameter_settings_e,
      };

      const f_string_static_t parameters_name[] = {
        fake_long_fakefile_s,
        fake_long_process_s,
        fake_long_settings_s,
      };

      const f_string_static_t parameter_defaults[] = {
        fake_default_fakefile_s,
        fake_default_process_s,
        fake_default_settings_s,
      };

      f_string_dynamic_t * const parameters_value[] = {
        &data->fakefile,
        &data->process,
        &data->settings,
      };

      bool parameters_validate_word[] = {
        F_false,
        F_true,
        F_false,
      };

      for (uint8_t i = 0; i < 3; ++i) {

        if (data->main->parameters.array[parameters_id[i]].result & f_console_result_found_e) {
          fake_print_error_parameter_missing_value(data, parameters_name[i]);

          return F_status_set_error(F_parameter);
        }

        if (data->main->parameters.array[parameters_id[i]].result & f_console_result_value_e) {
          if (data->main->parameters.array[parameters_id[i]].locations.used > 1) {
            fake_print_error_parameter_too_many(data, parameters_name[i]);

            return F_status_set_error(F_parameter);
          }

          f_array_length_t index = data->main->parameters.array[parameters_id[i]].values.array[0];

          if (data->main->parameters.arguments.array[index].used) {
            if (parameters_validate_word[i]) {
              f_array_length_t j = 0;
              f_array_length_t width_max = 0;

              for (j = 0; j < data->main->parameters.arguments.array[index].used; ++j) {

                width_max = data->main->parameters.arguments.array[index].used - j;

                status = f_utf_is_word_dash_plus(data->main->parameters.arguments.array[index].string + j, width_max, F_false);

                if (F_status_is_error(status)) {
                  if (fll_error_print(data->main->error, F_status_set_fine(status), "f_utf_is_word_dash_plus", F_false) == F_known_not && data->main->error.verbosity > f_console_verbosity_quiet_e) {
                    f_file_stream_lock(data->main->error);

                    fl_print_format("%r%[%QFailed to process the parameter '%]", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
                    fl_print_format("%[%r%r%]", data->main->error.to, data->main->error.notable, f_console_symbol_long_normal_s, fake_long_process_s, data->main->error.notable);
                    fl_print_format("%['.%]%r", data->main->error.to, data->main->error.context, data->main->error.context, f_string_eol_s);

                    f_file_stream_unlock(data->main->error);
                  }

                  return status;
                }

                if (status == F_false) {
                  if (data->main->error.verbosity > f_console_verbosity_quiet_e) {
                    f_file_stream_lock(data->main->error);

                    fl_print_format("%r%[%QThe '%]", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
                    fl_print_format("%[%r%r%]", data->main->error.to, data->main->error.notable, f_console_symbol_long_normal_s, fake_long_process_s, data->main->error.notable);
                    fl_print_format("%[' parameters value '%]", data->main->error.to, data->main->error.context, data->main->error.context, f_string_eol_s);
                    fl_print_format("%[%Q%]", data->main->error.to, data->main->error.notable, data->main->parameters.arguments.array[index], data->main->error.notable);
                    fl_print_format("%[' contains non-word, non-dash, and non-plus characters.%]%r", data->main->error.to, data->main->error.context, data->main->error.context, f_string_eol_s);

                    f_file_stream_unlock(data->main->error);
                  }

                  return F_status_set_error(F_parameter);
                }
              } // for
            }

            status = f_string_dynamic_increase_by(data->main->parameters.arguments.array[index].used + 1, parameters_value[i]);

            if (F_status_is_error(status)) {
              fll_error_print(data->main->error, F_status_set_fine(status), "f_string_dynamic_increase_by", F_true);

              return status;
            }

            status = f_string_dynamic_append(data->main->parameters.arguments.array[index], parameters_value[i]);

            if (F_status_is_error(status)) {
              if (status == F_status_set_error(F_string_too_large)) {
                if (data->main->error.verbosity > f_console_verbosity_quiet_e) {
                  f_file_stream_lock(data->main->error);

                  fl_print_format("%r%[%QThe parameter '%]", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
                  fl_print_format("%[%r%Q%]", data->main->error.to, data->main->error.notable, f_console_symbol_long_normal_s, parameters_name[i], data->main->error.notable);
                  fl_print_format("%[' is too long.%]%r", data->main->error.to, data->main->error.context, data->main->error.context, f_string_eol_s);

                  f_file_stream_unlock(data->main->error);
                }
              }
              else {
                fll_error_print(data->main->error, F_status_set_fine(status), "f_string_append", F_true);
              }

              return status;
            }

            status = F_none;
          }

          if (!data->main->parameters.arguments.array[index].used || status == F_data_not) {
            if (data->main->error.verbosity > f_console_verbosity_quiet_e) {
              f_file_stream_lock(data->main->error);

              fl_print_format("%r%[%QThe parameter '%]", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
              fl_print_format("%[%r%r%]", data->main->error.to, data->main->error.notable, f_console_symbol_long_normal_s, parameters_name[i], data->main->error.notable);
              fl_print_format("%[' must not be empty and must not contain only white space.%]%r", data->main->error.to, data->main->error.context, data->main->error.context, f_string_eol_s);

              f_file_stream_unlock(data->main->error);
            }
          }
        }
        else if (parameter_defaults[i].used) {
          parameters_value[i]->used = 0;

          status = f_string_dynamic_increase_by(parameter_defaults[i].used + 1, parameters_value[i]);

          if (F_status_is_error(status)) {
            fll_error_print(data->main->error, F_status_set_fine(status), "f_string_dynamic_increase_by", F_true);

            return status;
          }

          status = f_string_dynamic_append(parameter_defaults[i], parameters_value[i]);

          if (F_status_is_error(status)) {
            fll_error_print(data->main->error, F_status_set_fine(status), "f_string_dynamic_append", F_true);

            return status;
          }
        }
      } // for
    }

    if (data->main->parameters.array[fake_parameter_define_e].result & f_console_result_found_e) {
      fake_print_error_parameter_missing_value(data, fake_long_define_s);

      return F_status_set_error(F_parameter);
    }

    {
      const uint8_t parameters_id[] = {
        fake_parameter_path_build_e,
        fake_parameter_path_data_e,
        fake_parameter_path_work_e,
      };

      const f_string_static_t parameters_name[] = {
        fake_long_path_build_s,
        fake_long_path_data_s,
        fake_long_path_work_s,
      };

      const f_string_static_t parameter_defaults[] = {
        fake_default_path_build_s,
        fake_default_path_data_s,
        fake_default_path_work_s,
      };

      f_string_dynamic_t * const parameters_value[] = {
        &data->path_build,
        &data->path_data,
        &data->path_work,
      };

      for (uint8_t i = 0; i < 3; ++i) {

        if (data->main->parameters.array[parameters_id[i]].result & f_console_result_found_e) {
          fake_print_error_parameter_missing_value(data, parameters_name[i]);

          return F_status_set_error(F_parameter);
        }

        if (data->main->parameters.array[parameters_id[i]].result & f_console_result_value_e) {
          if (data->main->parameters.array[parameters_id[i]].values.used > 1) {
            fake_print_error_parameter_too_many(data, parameters_name[i]);

            return F_status_set_error(F_parameter);
          }

          const f_array_length_t index = data->main->parameters.array[parameters_id[i]].values.array[data->main->parameters.array[parameters_id[i]].values.used - 1];

          parameters_value[i]->used = 0;

          status = f_string_dynamic_increase_by(data->main->parameters.arguments.array[index].used + 1, parameters_value[i]);

          if (F_status_is_error(status)) {
            fll_error_print(data->main->error, F_status_set_fine(status), "f_string_dynamic_increase_by", F_true);

            return status;
          }

          status = f_path_directory_cleanup(data->main->parameters.arguments.array[index], parameters_value[i]);

          if (F_status_is_error(status)) {
            if (fll_error_print(data->main->error, F_status_set_fine(status), "f_path_directory_cleanup", F_false) == F_known_not && data->main->error.verbosity > f_console_verbosity_quiet_e) {
              f_file_stream_lock(data->main->error);

              fl_print_format("%r%[%QFailed to process parameter '%]", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
              fl_print_format("%[%r%r%]", data->main->error.to, data->main->error.notable, f_console_symbol_long_normal_s, parameters_name[i], data->main->error.notable);
              fl_print_format("%['.%]%r", data->main->error.to, data->main->error.context, data->main->error.context, f_string_eol_s);

              f_file_stream_unlock(data->main->error);
            }

            return status;
          }
        }
        else if (parameter_defaults[i].used) {
          parameters_value[i]->used = 0;

          status = f_string_dynamic_increase_by(parameter_defaults[i].used + 1, parameters_value[i]);

          if (F_status_is_error(status)) {
            fll_error_print(data->main->error, F_status_set_fine(status), "f_string_dynamic_increase_by", F_true);

            return status;
          }

          status = f_string_dynamic_append(parameter_defaults[i], parameters_value[i]);

          if (F_status_is_error(status)) {
            if (fll_error_print(data->main->error, F_status_set_fine(status), " f_string_dynamic_append", F_false) == F_known_not && data->main->error.verbosity > f_console_verbosity_quiet_e) {
              f_file_stream_lock(data->main->error);

              fl_print_format("%r%[%QFailed to load default for the parameter '%]", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
              fl_print_format("%[%r%r%]", data->main->error.to, data->main->error.notable, f_console_symbol_long_normal_s, parameters_name[i], data->main->error.notable);
              fl_print_format("%['.%]%r", data->main->error.to, data->main->error.context, data->main->error.context, f_string_eol_s);

              f_file_stream_unlock(data->main->error);
            }

            return status;
          }
        }
      } // for
    }

    if (data->main->parameters.array[fake_parameter_define_e].result & f_console_result_value_e) {
      status = fll_program_parameter_additional_rip(data->main->parameters.arguments.array, data->main->parameters.array[fake_parameter_define_e].values, &data->define);

      if (F_status_is_error(status)) {
        if (fll_error_print(data->main->error, F_status_set_fine(status), "fll_program_parameter_additional_rip", F_false) == F_known_not && data->main->error.verbosity > f_console_verbosity_quiet_e) {
          f_file_stream_lock(data->main->error);

          fl_print_format("%r%[%QFailed to process the parameter '%]", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
          fl_print_format("%[%r%r%]", data->main->error.to, data->main->error.notable, f_console_symbol_long_normal_s, fake_long_define_s, data->main->error.notable);
          fl_print_format("%['.%]%r", data->main->error.to, data->main->error.context, data->main->error.context, f_string_eol_s);

          f_file_stream_unlock(data->main->error);
        }

        return status;
      }
    }

    if (data->main->parameters.array[fake_parameter_mode_e].result & f_console_result_found_e) {
      fake_print_error_parameter_missing_value(data, fake_long_mode_s);

      return F_status_set_error(F_parameter);
    }

    if (data->main->parameters.array[fake_parameter_mode_e].result & f_console_result_value_e) {
      status = fll_program_parameter_additional_rip(data->main->parameters.arguments.array, data->main->parameters.array[fake_parameter_mode_e].values, &data->mode);

      if (F_status_is_error(status)) {
        if (fll_error_print(data->main->error, F_status_set_fine(status), "fll_program_parameter_additional_rip", F_false) == F_known_not && data->main->error.verbosity > f_console_verbosity_quiet_e) {
          f_file_stream_lock(data->main->error);

          fl_print_format("%r%[%QFailed to process the parameter '%]", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
          fl_print_format("%[%r%r%]", data->main->error.to, data->main->error.notable, f_console_symbol_long_normal_s, fake_long_mode_s, data->main->error.notable);
          fl_print_format("%['.%]%r", data->main->error.to, data->main->error.context, data->main->error.context, f_string_eol_s);

          f_file_stream_unlock(data->main->error);
        }

        return status;
      }

      f_array_length_t i = 0;
      f_array_length_t j = 0;
      f_array_length_t width_max = 0;

      for (; i < data->mode.used; ++i) {

        for (j = 0; j < data->mode.array[i].used; ++j) {

          width_max = data->mode.array[i].used - j;

          status = f_utf_is_word_dash_plus(data->mode.array[i].string + j, width_max, F_false);

          if (F_status_is_error(status)) {
            if (fll_error_print(data->main->error, F_status_set_fine(status), "f_utf_is_word_dash_plus", F_false) == F_known_not && data->main->error.verbosity > f_console_verbosity_quiet_e) {
              f_file_stream_lock(data->main->error);

              fl_print_format("%r%[%QFailed to process the parameter '%]", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
              fl_print_format("%[%r%r%]", data->main->error.to, data->main->error.notable, f_console_symbol_long_normal_s, fake_long_mode_s, data->main->error.notable);
              fl_print_format("%['.%]%r", data->main->error.to, data->main->error.context, data->main->error.context, f_string_eol_s);

              f_file_stream_unlock(data->main->error);
            }

            return status;
          }

          if (status == F_false) {
            if (data->main->error.verbosity > f_console_verbosity_quiet_e) {
              f_file_stream_lock(data->main->error);

              fl_print_format("%r%[%QThe '%]", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
              fl_print_format("%[%r%r%]", data->main->error.to, data->main->error.notable, f_console_symbol_long_normal_s, fake_long_mode_s, data->main->error.notable);
              fl_print_format("%[' parameters value '%]", data->main->error.to, data->main->error.notable, f_console_symbol_long_normal_s, fake_long_mode_s, data->main->error.notable);
              fl_print_format("%[%Q%]", data->main->error.to, data->main->error.notable, data->mode.array[i], data->main->error.notable);
              fl_print_format("%[' contains non-word, non-dash, and non-plus characters.%]%r", data->main->error.to, data->main->error.context, data->main->error.context, f_string_eol_s);

              f_file_stream_unlock(data->main->error);
            }

            return F_status_set_error(F_parameter);
          }
        } // for
      } // for
    }

    return F_none;
  }
#endif // _di_fake_process_console_parameters_

#ifndef _di_fake_validate_parameter_paths_
  f_status_t fake_validate_parameter_paths(fake_data_t * const data) {

    if (fll_program_standard_signal_received(data->main)) {
      fll_program_print_signal_received(main->warning, setting->line_first, main->signal_received);

      return F_status_set_error(F_interrupt);
    }

    const f_string_static_t parameters_name[] = {
      fake_long_path_build_s,
      fake_long_path_data_s,
      fake_long_path_work_s,
    };

    const f_string_dynamic_t parameters_value[] = {
      data->path_build,
      data->path_data,
      data->path_work,
    };

    uint8_t parameters_required[] = {
      F_false,
      (data->main->pipe & fll_program_data_pipe_input_e) ? F_false : F_true,
      F_false,
    };

    f_status_t status = F_none;

    // Check only expected operations (fake_operation_clean_e and fake_operation_skeleton_e should not call this function).
    if (data->operation == fake_operation_make_e) {

      // If a custom --data or a custom --fakefile parameter is passed and uses an absolute or relative to current path, then do not check.
      if (data->main->parameters.array[fake_parameter_fakefile_e].result & f_console_result_value_e) {
        const f_array_length_t index = data->main->parameters.array[fake_parameter_fakefile_e].values.array[data->main->parameters.array[fake_parameter_fakefile_e].values.used - 1];

        if (f_path_is_absolute(data->main->parameters.arguments.array[index]) == F_true || f_path_is_relative_current(data->main->parameters.arguments.array[index]) == F_true) {
          parameters_required[1] = F_none;
        }
        else {
          status = f_file_exists(data->main->parameters.arguments.array[index], F_true);

          if (F_status_is_error_not(status) && status == F_true) {
            parameters_required[1] = F_none;
          }
        }
      }
    }
    else if (data->operation == fake_operation_build_e) {

      // If a custom --data or a custom --settings parameter is passed and uses an absolute or relative to current path, then do not check.
      if (data->main->parameters.array[fake_parameter_settings_e].result & f_console_result_value_e) {
        const f_array_length_t index = data->main->parameters.array[fake_parameter_settings_e].values.array[data->main->parameters.array[fake_parameter_settings_e].values.used - 1];

        if (f_path_is_absolute(data->main->parameters.arguments.array[index]) == F_true || f_path_is_relative_current(data->main->parameters.arguments.array[index]) == F_true) {
          parameters_required[1] = F_none;
        }
        else {
          status = f_file_exists(data->main->parameters.arguments.array[index], F_true);

          if (F_status_is_error_not(status) && status == F_true) {
            parameters_required[1] = F_none;
          }
        }
      }
    }

    struct stat directory_stat;

    for (uint8_t i = 0; i < 3; ++i) {

      if (parameters_required[i] != F_none && parameters_value[i].used) {
        memset(&directory_stat, 0, sizeof(struct stat));

        status = f_file_stat(parameters_value[i], F_true, &directory_stat);

        if (status == F_status_set_error(F_file_found_not)) status = F_status_set_error(F_directory_found_not);

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) != F_directory_found_not || parameters_required[i]) {
            fll_error_file_print(data->main->error, F_status_set_fine(status), "f_file_stat", F_true, parameters_value[i], f_file_operation_access_s, fll_error_file_type_directory_e);

            return status;
          }
        }
      }
      else if (parameters_required[i] == F_true) {
        f_file_stream_lock(data->main->error);

        fl_print_format("%r%[%QNo valid path for the (required) directory parameter '%]", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
        fl_print_format("%[%r%r%]", data->main->error.to, data->main->error.notable, f_console_symbol_long_normal_s, parameters_name[i], data->main->error.notable);
        fl_print_format("%[' was found.%]%r", data->main->error.to, data->main->error.context, data->main->error.context, f_string_eol_s);

        f_file_stream_unlock(data->main->error);

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
