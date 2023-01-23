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
        fll_error_print(data->main->error, F_status_set_fine(*status), "fll_execute_program", F_true);
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
        fll_program_print_signal_received(data->main->warning, data->setting->line_first, data->main->signal_received);

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

#ifndef _di_fake_validate_parameter_paths_
  f_status_t fake_validate_parameter_paths(fake_data_t * const data) {

    if (fll_program_standard_signal_received(data->main)) {
      fll_program_print_signal_received(data->main->warning, data->setting->line_first, data->main->signal_received);

      return F_status_set_error(F_interrupt);
    }

    const f_string_static_t names[] = {
      fake_long_path_build_s,
      fake_long_path_data_s,
      fake_long_path_work_s,
    };

    const f_string_dynamic_t values[] = {
      data->path_build,
      data->path_data,
      data->path_work,
    };

    uint8_t requireds[] = {
      F_false,
      (data->main->pipe & fll_program_data_pipe_input_e) ? F_false : F_true,
      F_false,
    };

    f_status_t status = F_none;

    // Check only expected operations (fake_operation_clean_e and fake_operation_skeleton_e should not call this function).
    if (data->operation == fake_operation_make_e) {
      if (data->main->parameters.array[fake_parameter_fakefile_e].result == f_console_result_none_e) {
        if (data->path_build.used && f_file_exists(data->path_build, F_false) != F_true) {
          if (f_file_exists(fake_default_fakefile_s, F_false) == F_true) {
            requireds[1] = F_false;
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
          requireds[1] = F_none;
        }
        else {
          status = f_file_exists(data->main->parameters.arguments.array[index], F_true);

          if (F_status_is_error_not(status) && status == F_true) {
            requireds[1] = F_none;
          }
        }
      }
    }

    struct stat directory_stat;

    for (uint8_t i = 0; i < 3; ++i) {

      if (requireds[i] != F_none && values[i].used) {
        memset(&directory_stat, 0, sizeof(struct stat));

        status = f_file_stat(values[i], F_true, &directory_stat);

        if (status == F_status_set_error(F_file_found_not)) status = F_status_set_error(F_directory_found_not);

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) != F_directory_found_not || requireds[i]) {
            fll_error_file_print(data->main->error, F_status_set_fine(status), "f_file_stat", F_true, values[i], f_file_operation_access_s, fll_error_file_type_directory_e);

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
