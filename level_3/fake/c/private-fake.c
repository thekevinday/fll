#include "fake.h"
#include "private-common.h"
#include "private-fake.h"
#include "private-fake-path_generate.h"
#include "private-build.h"
#include "private-make.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_execute_
  int fake_execute(fake_main_t * const main, const f_string_maps_t environment, const f_string_static_t program, const f_string_statics_t arguments, f_status_t *status) {

    if (F_status_is_error(*status)) return 1;

    if (main->error.verbosity == f_console_verbosity_verbose_e) {
      flockfile(main->output.to.stream);

      f_print_dynamic(program, main->output.to.stream);

      for (f_array_length_t i = 0; i < arguments.used; ++i) {

        if (!arguments.array[i].used) continue;

        fl_print_format(" %Q", main->output.to.stream, arguments.array[i]);
      } // for

      f_print_dynamic(f_string_eol_s, main->output.to.stream);

      funlockfile(main->output.to.stream);

      // Flush to stdout before executing command.
      fflush(main->output.to.stream);
    }

    int return_code = 0;

    if (program.used) {

      // Child processes should receive all signals, without blocking.
      f_signal_how_t signals = f_signal_how_t_initialize;
      f_signal_set_empty(&signals.block);
      f_signal_set_fill(&signals.block_not);

      fl_execute_parameter_t parameter = macro_fl_execute_parameter_t_initialize(0, 0, &environment, &signals, 0);

      *status = fll_execute_program(program.string, arguments, &parameter, 0, (void *) &return_code);

      if (fake_signal_received(main)) {
        *status = F_status_set_error(F_interrupt);

        return 0;
      }

      if (*status == F_child) {
        return return_code;
      }
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
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          flockfile(main->error.to.stream);

          fl_print_format("%q%[%QFailed to find program '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, program, main->error.notable);
          fl_print_format("%[' for executing.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          funlockfile(main->error.to.stream);
        }
      }
      else {
        fll_error_print(main->error, F_status_set_fine(*status), "fll_execute_program", F_true);
      }
    }

    return return_code;
  }
#endif // _di_fake_execute_

#ifndef _di_fake_file_buffer_
  f_status_t fake_file_buffer(fake_main_t * const main, const f_string_t path_file, f_string_dynamic_t *buffer) {

    f_file_t file = f_file_t_initialize;
    f_string_t name_function = "f_file_exists";
    f_status_t status = F_none;

    if (fake_signal_received(main)) {
      return F_status_set_error(F_interrupt);
    }

    status = f_file_exists(path_file);

    if (status == F_true) {
      {
        f_array_length_t size_file = 0;

        name_function = "f_file_size";
        status = f_file_size(path_file, F_true, &size_file);

        if (F_status_is_error_not(status)) {
          if (size_file > fake_common_initial_buffer_max_d) {
            size_file = fake_common_initial_buffer_max_d;
          }

           macro_f_string_dynamic_t_resize((status), (*buffer), size_file);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), name_function, F_true, path_file, "allocate buffer size for", fll_error_file_type_file_e);

            f_string_dynamic_resize(0, buffer);

            return status;
          }
        }

        status = F_true;
      }

      name_function = "f_file_open";
      status = f_file_stream_open(path_file, 0, &file);

      if (F_status_is_error_not(status)) {
        name_function = "f_file_read";
        status = f_file_read(file, buffer);

        f_file_stream_close(F_true, &file);
      }
    }
    else if (status == F_false) {
      status = F_status_set_error(F_file_found_not);
    }

    if (F_status_is_error(status)) {
      fll_error_file_print(main->error, F_status_set_fine(status), name_function, F_true, path_file, "read", fll_error_file_type_file_e);

      f_string_dynamic_resize(0, buffer);
    }

    return status;
  }
#endif // _di_fake_file_buffer_

#ifndef _di_fake_process_console_parameters_
  f_status_t fake_process_console_parameters(const f_console_arguments_t *arguments, fake_main_t *main) {

    f_status_t status = F_none;

    // @todo move as many of the inline error printing code into more general functions where possible to provide more accurate error reporting.

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
        &main->fakefile,
        &main->process,
        &main->settings,
      };

      bool parameters_validate_word[] = {
        F_false,
        F_true,
        F_false,
      };

      for (uint8_t i = 0; i < 3; ++i) {

        if (main->parameters[parameters_id[i]].result == f_console_result_found_e) {
          fake_print_error_parameter_missing_value(main, parameters_name[i]);

          return F_status_set_error(F_parameter);
        }
        else if (main->parameters[parameters_id[i]].result == f_console_result_additional_e) {
          if (main->parameters[parameters_id[i]].locations.used > 1) {
            fake_print_error_parameter_too_many(main, parameters_name[i]);

            return F_status_set_error(F_parameter);
          }

          f_array_length_t location = main->parameters[parameters_id[i]].values.array[0];
          f_array_length_t length = strnlen(arguments->argv[location], F_console_parameter_size_d);

          if (length > 0) {
            if (parameters_validate_word[i]) {
              f_array_length_t j = 0;
              f_array_length_t width_max = 0;

              for (j = 0; j < length; ++j) {

                width_max = length - j;

                status = f_utf_is_word_dash_plus(arguments->argv[location] + j, width_max, F_false);

                if (F_status_is_error(status)) {
                  if (fll_error_print(main->error, F_status_set_fine(status), "f_utf_is_word_dash_plus", F_false) == F_known_not && main->error.verbosity != f_console_verbosity_quiet_e) {
                    flockfile(main->error.to.stream);

                    fl_print_format("%q%[%QFailed to process the parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
                    fl_print_format("%[%q%q%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fake_long_process_s, main->error.notable);
                    fl_print_format("%['.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

                    funlockfile(main->error.to.stream);
                  }

                  return status;
                }

                if (status == F_false) {
                  if (main->error.verbosity != f_console_verbosity_quiet_e) {
                    flockfile(main->error.to.stream);

                    fl_print_format("%q%[%QThe '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
                    fl_print_format("%[%q%q%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fake_long_process_s, main->error.notable);
                    fl_print_format("%[' parameters value '%]", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);
                    fl_print_format("%[%S%]", main->error.to.stream, main->error.notable, arguments->argv[location], main->error.notable);
                    fl_print_format("%[' contains non-word, non-dash, and non-plus characters.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

                    funlockfile(main->error.to.stream);
                  }

                  return F_status_set_error(F_parameter);
                }
              } // for
            }

            status = f_string_append(arguments->argv[location], length, parameters_value[i]);

            if (F_status_is_error(status)) {
              if (status == F_status_set_error(F_string_too_large)) {
                if (main->error.verbosity != f_console_verbosity_quiet_e) {
                  flockfile(main->error.to.stream);

                  fl_print_format("%q%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
                  fl_print_format("%[%q%Q%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, parameters_name[i], main->error.notable);
                  fl_print_format("%[' is too long.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

                  funlockfile(main->error.to.stream);
                }
              }
              else {
                fll_error_print(main->error, F_status_set_fine(status), "f_string_append", F_true);
              }

              return status;
            }
            else {
              status = F_none;
            }
          }

          if (length == 0 || status == F_data_not) {
            if (main->error.verbosity != f_console_verbosity_quiet_e) {
              flockfile(main->error.to.stream);

              fl_print_format("%q%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
              fl_print_format("%[%q%q%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, parameters_name[i], main->error.notable);
              fl_print_format("%[' must not be empty and must not contain only whitespace.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

              funlockfile(main->error.to.stream);
            }
          }
        }
        else if (parameter_defaults[i].used) {
          parameters_value[i]->used = 0;

          status = f_string_dynamic_append(parameter_defaults[i], parameters_value[i]);

          if (F_status_is_error(status)) {
            fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_append", F_true);

            return status;
          }
        }
      } // for
    }

    if (main->parameters[fake_parameter_define_e].result == f_console_result_found_e) {
      fake_print_error_parameter_missing_value(main, fake_long_define_s);

      return F_status_set_error(F_parameter);
    }

    {
      const uint8_t parameters_id[] = {
        fake_parameter_path_build_e,
        fake_parameter_path_data_e,
        fake_parameter_path_sources_e,
        fake_parameter_path_work_e,
      };

      const f_string_static_t parameters_name[] = {
        fake_long_path_build_s,
        fake_long_path_data_s,
        fake_long_path_sources_s,
        fake_long_path_work_s,
      };

      const f_string_static_t parameter_defaults[] = {
        fake_default_path_build_s,
        fake_default_path_data_s,
        fake_default_path_sources_s,
        fake_default_path_work_s,
      };

      f_string_dynamic_t * const parameters_value[] = {
        &main->path_build,
        &main->path_data,
        &main->path_sources,
        &main->path_work,
      };

      for (uint8_t i = 0; i < 4; ++i) {

        if (main->parameters[parameters_id[i]].result == f_console_result_found_e) {
          fake_print_error_parameter_missing_value(main, parameters_name[i]);

          return F_status_set_error(F_parameter);
        }
        else if (main->parameters[parameters_id[i]].result == f_console_result_additional_e) {
          if (main->parameters[parameters_id[i]].values.used > 1) {
            fake_print_error_parameter_too_many(main, parameters_name[i]);

            return F_status_set_error(F_parameter);
          }

          status = fl_console_parameter_to_string_dynamic_directory(arguments->argv[main->parameters[parameters_id[i]].values.array[0]], parameters_value[i]);

          if (F_status_is_error(status)) {
            if (fll_error_print(main->error, F_status_set_fine(status), "fl_console_parameter_to_string_dynamic_directory", F_false) == F_known_not && main->error.verbosity != f_console_verbosity_quiet_e) {
              flockfile(main->error.to.stream);

              fl_print_format("%q%[%QFailed to process parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
              fl_print_format("%[%q%q%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, parameters_name[i], main->error.notable);
              fl_print_format("%['.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

              funlockfile(main->error.to.stream);
            }

            return status;
          }
        }
        else if (parameter_defaults[i].used) {
          parameters_value[i]->used = 0;

          status = f_string_dynamic_append(parameter_defaults[i], parameters_value[i]);

          if (F_status_is_error(status)) {
            if (fll_error_print(main->error, F_status_set_fine(status), " f_string_dynamic_append", F_false) == F_known_not && main->error.verbosity != f_console_verbosity_quiet_e) {
              flockfile(main->error.to.stream);

              fl_print_format("%q%[%QFailed to load default for the parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
              fl_print_format("%[%q%q%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, parameters_name[i], main->error.notable);
              fl_print_format("%['.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

              funlockfile(main->error.to.stream);
            }

            return status;
          }
        }
      } // for
    }

    if (main->parameters[fake_parameter_define_e].result == f_console_result_additional_e) {
      status = fll_program_parameter_additional_rip(arguments->argv, main->parameters[fake_parameter_define_e].values, &main->define);

      if (F_status_is_error(status)) {
        if (fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_additional_rip", F_false) == F_known_not && main->error.verbosity != f_console_verbosity_quiet_e) {
          flockfile(main->error.to.stream);

          fl_print_format("%q%[%QFailed to process the parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%q%q%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fake_long_define_s, main->error.notable);
          fl_print_format("%['.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          funlockfile(main->error.to.stream);
        }

        return status;
      }
    }

    if (main->parameters[fake_parameter_mode_e].result == f_console_result_found_e) {
      fake_print_error_parameter_missing_value(main, fake_long_mode_s);
      return F_status_set_error(F_parameter);
    }
    else if (main->parameters[fake_parameter_mode_e].result == f_console_result_additional_e) {
      status = fll_program_parameter_additional_rip(arguments->argv, main->parameters[fake_parameter_mode_e].values, &main->mode);

      if (F_status_is_error(status)) {
        if (fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_additional_rip", F_false) == F_known_not && main->error.verbosity != f_console_verbosity_quiet_e) {
          flockfile(main->error.to.stream);

          fl_print_format("%q%[%SFailed to process the parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%q%q%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fake_long_mode_s, main->error.notable);
          fl_print_format("%['.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          funlockfile(main->error.to.stream);
        }

        return status;
      }

      f_array_length_t i = 0;
      f_array_length_t j = 0;
      f_array_length_t width_max = 0;

      for (; i < main->mode.used; ++i) {

        for (j = 0; j < main->mode.array[i].used; ++j) {

          width_max = main->mode.array[i].used - j;

          status = f_utf_is_word_dash_plus(main->mode.array[i].string + j, width_max, F_false);

          if (F_status_is_error(status)) {
            if (fll_error_print(main->error, F_status_set_fine(status), "f_utf_is_word_dash_plus", F_false) == F_known_not && main->error.verbosity != f_console_verbosity_quiet_e) {
              flockfile(main->error.to.stream);

              fl_print_format("%q%[%QFailed to process the parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
              fl_print_format("%[%q%q%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fake_long_mode_s, main->error.notable);
              fl_print_format("%['.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

              funlockfile(main->error.to.stream);
            }

            return status;
          }

          if (status == F_false) {
            if (main->error.verbosity != f_console_verbosity_quiet_e) {
              flockfile(main->error.to.stream);

              fl_print_format("%q%[%QThe '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
              fl_print_format("%[%q%q%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fake_long_mode_s, main->error.notable);
              fl_print_format("%[' parameters value '%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fake_long_mode_s, main->error.notable);
              fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, main->mode.array[i], main->error.notable);
              fl_print_format("%[' contains non-word, non-dash, and non-plus characters.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

              funlockfile(main->error.to.stream);
            }

            return F_status_set_error(F_parameter);
          }
        } // for
      } // for
    }

    return F_none;
  }
#endif // _di_fake_process_console_parameters_

#ifndef _di_fake_signal_state_interrupt_fss_
  f_status_t fake_signal_state_interrupt_fss(void *state, void *internal) {

    if (!state) {
      return F_interrupt_not;
    }

    f_state_t * const state_ptr = (f_state_t *) state;

    if (!state_ptr->custom) {
      return F_interrupt_not;
    }

    fake_main_t * const main = (fake_main_t *) state_ptr->custom;

    if (!((++main->signal_check) % fake_signal_check_d)) {
      if (fake_signal_received(main)) {
        return F_status_set_error(F_interrupt);
      }

      main->signal_check = 0;
    }

    return F_interrupt_not;
  }
#endif // _di_fake_signal_state_interrupt_fss_

#ifndef _di_fake_signal_state_interrupt_iki_
  f_status_t fake_signal_state_interrupt_iki(void *state, void *internal) {

    if (!state) {
      return F_interrupt_not;
    }

    f_state_t * const state_ptr = (f_state_t *) state;

    if (!state_ptr->custom) {
      return F_interrupt_not;
    }

    fake_main_t * const main = (fake_main_t *) state_ptr->custom;

    if (!((++main->signal_check) % fake_signal_check_d)) {
      if (fake_signal_received(main)) {
        return F_status_set_error(F_interrupt);
      }

      main->signal_check = 0;
    }

    return F_interrupt_not;
  }
#endif // _di_fake_signal_state_interrupt_iki_

#ifndef _di_fake_validate_directories_
  f_status_t fake_validate_parameter_directories(const f_console_arguments_t *arguments, fake_main_t * const main) {

    if (fake_signal_received(main)) {
      return F_status_set_error(F_interrupt);
    }

    const f_string_static_t parameters_name[] = {
      fake_long_path_build_s,
      fake_long_path_data_s,
      fake_long_path_work_s,
    };

    const f_string_dynamic_t *parameters_value[] = {
      &main->path_build,
      &main->path_data,
      &main->path_work,
    };

    const bool parameters_required[] = {
      F_false,
      F_true,
      F_false,
    };

    struct stat directory_stat;
    f_status_t status = F_none;

    for (uint8_t i = 0; i < 3; ++i) {

      if (parameters_value[i]->used) {
        memset(&directory_stat, 0, sizeof(struct stat));

        status = f_file_stat(parameters_value[i]->string, F_true, &directory_stat);

        if (status == F_status_set_error(F_file_found_not)) status = F_status_set_error(F_directory_found_not);

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) != F_directory_found_not || parameters_required[i]) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stat", F_true, parameters_value[i]->string, "access", fll_error_file_type_directory_e);

            return status;
          }
        }
      }
      else if (parameters_required[i]) {
        flockfile(main->error.to.stream);

        fl_print_format("%q%[%QNo valid path for the (required) directory parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%q%q%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, parameters_name[i], main->error.notable);
        fl_print_format("%[' was found.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

        funlockfile(main->error.to.stream);

        return F_status_set_error(F_directory_found_not);
      }
    } // for

    return F_none;
  }
#endif // _di_fake_validate_parameter_directories_

#ifndef _di_fake_verbose_print_clone_
  void fake_verbose_print_clone(const f_file_t output, const f_string_t source, const f_string_t destination) {
    fll_print_format("Cloned '%S' to '%S'.%q", output.stream, source, destination, f_string_eol_s);
  }
#endif // _di_fake_verbose_print_clone_

#ifndef _di_fake_verbose_print_copy_
  void fake_verbose_print_copy(const f_file_t output, const f_string_t source, const f_string_t destination) {
    fll_print_format("Copied '%S' to '%S'.%q", output.stream, source, destination, f_string_eol_s);
  }
#endif // _di_fake_verbose_print_copy_

#ifndef _di_fake_verbose_print_move_
  void fake_verbose_print_move(const f_file_t output, const f_string_t source, const f_string_t destination) {
    fll_print_format("Moved '%S' to '%S'.%q", output.stream, source, destination, f_string_eol_s);
  }
#endif // _di_fake_verbose_print_move_

#ifdef __cplusplus
} // extern "C"
#endif
