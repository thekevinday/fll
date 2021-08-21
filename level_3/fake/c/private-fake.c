#include "fake.h"
#include "private-common.h"
#include "private-fake.h"
#include "private-build.h"
#include "private-make.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_execute_
  int fake_execute(const fake_main_t main, const f_string_maps_t environment, const f_string_static_t program, const f_string_statics_t arguments, f_status_t *status) {

    if (F_status_is_error(*status)) return 1;

    if (main.error.verbosity == f_console_verbosity_verbose) {
      flockfile(main.output.stream);

      f_print_dynamic(program, main.output.stream);

      for (f_array_length_t i = 0; i < arguments.used; ++i) {

        if (!arguments.array[i].used) continue;

        fl_print_format(" %Q", main.output.stream, arguments.array[i]);
      } // for

      f_print_character(f_string_eol_s[0], main.output.stream);

      funlockfile(main.output.stream);

      // flush to stdout before executing command.
      fflush(main.output.stream);
    }

    if (fake_signal_received(main)) {
      *status = F_status_set_error(F_signal);

      return 0;
    }

    int return_code = 0;

    if (program.used) {

      // child processes should receive all signals, without blocking.
      f_signal_how_t signals = f_signal_how_t_initialize;
      f_signal_set_empty(&signals.block);
      f_signal_set_fill(&signals.block_not);

      fl_execute_parameter_t parameter = macro_fl_execute_parameter_t_initialize(0, 0, &environment, &signals, 0);

      *status = fll_execute_program(program.string, arguments, &parameter, 0, (void *) &return_code);

      if (fake_signal_received(main)) {
        *status = F_status_set_error(F_signal);

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
        if (main.error.verbosity != f_console_verbosity_quiet) {
          flockfile(main.error.to.stream);

          fl_print_format("%c%[%SFailed to find program '%]", main.error.to.stream, f_string_eol_s[0], main.error.context, main.error.prefix, main.error.context);
          fl_print_format("%[%Q%]", main.error.to.stream, main.error.notable, program, main.error.notable);
          fl_print_format("%[' for executing.%]%c", main.error.to.stream, main.error.context, main.error.context, f_string_eol_s[0]);

          funlockfile(main.error.to.stream);
        }
      }
      else {
        fll_error_print(main.error, F_status_set_fine(*status), "fll_execute_program", F_true);
      }
    }

    return return_code;
  }
#endif // _di_fake_execute_

#ifndef _di_fake_file_buffer_
  f_status_t fake_file_buffer(const fake_main_t main, const f_string_t path_file, f_string_dynamic_t *buffer) {

    f_file_t file = f_file_t_initialize;
    f_string_t name_function = "f_file_exists";
    f_status_t status = F_none;

    if (fake_signal_received(main)) {
      return F_status_set_error(F_signal);
    }

    status = f_file_exists(path_file);

    if (status == F_true) {
      {
        f_array_length_t size_file = 0;

        name_function = "f_file_size";
        status = f_file_size(path_file, F_true, &size_file);

        if (F_status_is_error_not(status)) {
          if (size_file > fake_common_initial_buffer_max) {
            size_file = fake_common_initial_buffer_max;
          }

           macro_f_string_dynamic_t_resize((status), (*buffer), size_file);

          if (F_status_is_error(status)) {
            fll_error_file_print(main.error, F_status_set_fine(status), name_function, F_true, path_file, "allocate buffer size for", fll_error_file_type_file);

            macro_f_string_dynamic_t_delete_simple((*buffer));
            return status;
          }
        }

        status = F_true;
      }

      name_function = "f_file_open";
      status = f_file_stream_open(path_file, 0, &file);

      if (fake_signal_received(main)) {
        if (file.id) {
          f_file_stream_close(F_true, &file);
        }

        return F_status_set_error(F_signal);
      }

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
      fll_error_file_print(main.error, F_status_set_fine(status), name_function, F_true, path_file, "read", fll_error_file_type_file);

      macro_f_string_dynamic_t_delete_simple((*buffer));
    }

    return status;
  }
#endif // _di_fake_file_buffer_

#ifndef _di_fake_path_generate_
  f_status_t fake_path_generate(fake_main_t *main) {

    f_status_t status = F_none;
    uint8_t i = 0;

    {
      const f_string_dynamic_t *parameters_source[] = {
        &main->path_build,
        &main->path_data,
        &main->path_sources,
      };

      const uint8_t parameters_length[] = {
        7,
        2,
        4,
      };

      f_string_dynamic_t *parameters_value_0[] = {
        &main->path_build_documents,
        &main->path_build_includes,
        &main->path_build_libraries,
        &main->path_build_objects,
        &main->path_build_programs,
        &main->path_build_settings,
        &main->path_build_stage,
      };

      f_string_dynamic_t *parameters_value_1[] = {
        &main->path_data_build,
        &main->path_data_settings,
      };

      f_string_dynamic_t *parameters_value_2[] = {
        &main->path_sources_bash,
        &main->path_sources_c,
        &main->path_sources_cpp,
        &main->path_sources_script,
      };

      f_string_dynamic_t **const parameters_value[] = {
        parameters_value_0,
        parameters_value_1,
        parameters_value_2,
      };

      for (i = 0; i < 3; ++i) {

        status = fake_path_generate_string_dynamic(main, *parameters_source[i], parameters_value[i], parameters_length[i]);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "fake_path_generate_string_dynamic", F_true);

          return status;
        }
      } // for
    }

    {
      const f_string_t parameters_source[] = {
        fake_path_part_documents,
        fake_path_part_includes,
        fake_path_part_libraries,
        fake_path_part_objects,
        fake_path_part_programs,
        fake_path_part_settings,
        fake_path_part_stage,
        fake_path_part_build,
        fake_path_part_settings,
        fake_path_part_documents,
        fake_path_part_licenses,
        fake_path_part_bash,
        fake_path_part_c,
        fake_path_part_cpp,
        fake_path_part_script,
      };

      const f_array_length_t parameters_length[] = {
        fake_path_part_documents_length,
        fake_path_part_includes_length,
        fake_path_part_libraries_length,
        fake_path_part_objects_length,
        fake_path_part_programs_length,
        fake_path_part_settings_length,
        fake_path_part_stage_length,
        fake_path_part_build_length,
        fake_path_part_settings_length,
        fake_path_part_documents_length,
        fake_path_part_licenses_length,
        fake_path_part_bash_length,
        fake_path_part_c_length,
        fake_path_part_cpp_length,
        fake_path_part_script_length,
      };

      f_string_dynamic_t * const parameters_value[] = {
        &main->path_build_documents,
        &main->path_build_includes,
        &main->path_build_libraries,
        &main->path_build_objects,
        &main->path_build_programs,
        &main->path_build_settings,
        &main->path_build_stage,
        &main->path_data_build,
        &main->path_data_settings,
        &main->path_documents,
        &main->path_licenses,
        &main->path_sources_bash,
        &main->path_sources_c,
        &main->path_sources_cpp,
        &main->path_sources_script,
      };

      for (i = 0; i < 15; ++i) {

        status = f_string_append_nulless(parameters_source[i], parameters_length[i], parameters_value[i]);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "f_string_append_nulless", F_true);

          return status;
        }
      } // for
    }

    {
      const f_string_dynamic_t *parameters_source[] = {
        &main->path_build_libraries,
        &main->path_build_programs,
        &main->path_data_build,
        &main->path_documents,
      };

      const uint8_t parameters_length[] = {
        3,
        3,
        4,
        1,
      };

      f_string_dynamic_t *parameters_value_0[] = {
        &main->path_build_libraries_script,
        &main->path_build_libraries_shared,
        &main->path_build_libraries_static,
      };

      f_string_dynamic_t *parameters_value_1[] = {
        &main->path_build_programs_script,
        &main->path_build_programs_shared,
        &main->path_build_programs_static,
      };

      f_string_dynamic_t *parameters_value_2[] = {
        &main->file_data_build_defines,
        &main->file_data_build_dependencies,
        &main->file_data_build_fakefile,
        &main->file_data_build_settings,
      };

      f_string_dynamic_t *parameters_value_3[] = {
        &main->file_documents_readme,
      };

      f_string_dynamic_t **const parameters_value[] = {
        parameters_value_0,
        parameters_value_1,
        parameters_value_2,
        parameters_value_3,
      };

      for (i = 0; i < 4; ++i) {

        status = fake_path_generate_string_dynamic(main, *parameters_source[i], parameters_value[i], parameters_length[i]);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "fake_path_generate_string_dynamic", F_true);

          return status;
        }
      } // for
    }

    // When custom fakefile or settings are used and they are paths to a file, remove the default path.
    if (f_path_is(main->fakefile.string, main->fakefile.used)) {
      main->file_data_build_fakefile.used = 0;
    }

    if (f_path_is(main->settings.string, main->settings.used)) {
      main->file_data_build_settings.used = 0;
    }

    {
      const f_string_t parameters_source[] = {
        fake_path_part_script,
        fake_path_part_shared,
        fake_path_part_static,
        fake_path_part_script,
        fake_path_part_shared,
        fake_path_part_static,
        fake_file_defines,
        fake_file_dependencies,
        main->fakefile.string,
        main->settings.string,
        fake_file_readme,
      };

      const f_array_length_t parameters_length[] = {
        fake_path_part_script_length,
        fake_path_part_shared_length,
        fake_path_part_static_length,
        fake_path_part_script_length,
        fake_path_part_shared_length,
        fake_path_part_static_length,
        fake_file_defines_length,
        fake_file_dependencies_length,
        main->fakefile.used,
        main->settings.used,
        fake_file_readme_length,
      };

      f_string_dynamic_t * const parameters_value[] = {
        &main->path_build_libraries_script,
        &main->path_build_libraries_shared,
        &main->path_build_libraries_static,
        &main->path_build_programs_script,
        &main->path_build_programs_shared,
        &main->path_build_programs_static,
        &main->file_data_build_defines,
        &main->file_data_build_dependencies,
        &main->file_data_build_fakefile,
        &main->file_data_build_settings,
        &main->file_documents_readme,
      };

      for (i = 0; i < 11; ++i) {

        status = f_string_append_nulless(parameters_source[i], parameters_length[i], parameters_value[i]);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "f_string_append_nulless", F_true);

          return status;
        }
      } // for
    }

    if (main->path_work.used) {
      {
        f_string_dynamic_t * const parameters_value[] = {
          &main->path_work_includes,
          &main->path_work_libraries,
          &main->path_work_programs,
        };

        for (i = 0; i < 3; ++i) {

          status = f_string_dynamic_append_nulless(main->path_work, parameters_value[i]);

          if (F_status_is_error(status)) {
            fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true);

            return status;
          }
        } // for
      }

      {
        const f_string_t parameters_source[] = {
          fake_path_part_includes,
          fake_path_part_libraries,
          fake_path_part_programs,
        };

        const f_array_length_t parameters_length[] = {
          fake_path_part_includes_length,
          fake_path_part_libraries_length,
          fake_path_part_programs_length,
        };

        f_string_dynamic_t * const parameters_value[] = {
          &main->path_work_includes,
          &main->path_work_libraries,
          &main->path_work_programs,
        };

        for (i = 0; i < 3; ++i) {

          status = f_string_append_nulless(parameters_source[i], parameters_length[i], parameters_value[i]);

          if (F_status_is_error(status)) {
            fll_error_print(main->error, F_status_set_fine(status), "f_string_append_nulless", F_true);

            return status;
          }
        } // for
      }

      {
        const f_string_dynamic_t *parameters_source[] = {
          &main->path_work_libraries,
          &main->path_work_programs,
        };

        const uint8_t parameters_length[] = {
          3,
          3,
        };

        f_string_dynamic_t *parameters_value_0[] = {
          &main->path_work_libraries_script,
          &main->path_work_libraries_shared,
          &main->path_work_libraries_static,
        };

        f_string_dynamic_t *parameters_value_1[] = {
          &main->path_work_programs_script,
          &main->path_work_programs_shared,
          &main->path_work_programs_static,
        };

        f_string_dynamic_t **const parameters_value[] = {
          parameters_value_0,
          parameters_value_1,
        };

        for (i = 0; i < 2; ++i) {

          status = fake_path_generate_string_dynamic(main, *parameters_source[i], parameters_value[i], parameters_length[i]);

          if (F_status_is_error(status)) {
            fll_error_print(main->error, F_status_set_fine(status), "fake_path_generate_string_dynamic", F_true);

            return status;
          }
        } // for
      }

      {
        const f_string_t parameters_source[] = {
          fake_path_part_script,
          fake_path_part_shared,
          fake_path_part_static,
          fake_path_part_script,
          fake_path_part_shared,
          fake_path_part_static,
        };

        const f_array_length_t parameters_length[] = {
          fake_path_part_script_length,
          fake_path_part_shared_length,
          fake_path_part_static_length,
          fake_path_part_script_length,
          fake_path_part_shared_length,
          fake_path_part_static_length,
        };

        f_string_dynamic_t * const parameters_value[] = {
          &main->path_work_libraries_script,
          &main->path_work_libraries_shared,
          &main->path_work_libraries_static,
          &main->path_work_programs_script,
          &main->path_work_programs_shared,
          &main->path_work_programs_static,
        };

        for (i = 0; i < 6; ++i) {

          status = f_string_append_nulless(parameters_source[i], parameters_length[i], parameters_value[i]);

          if (F_status_is_error(status)) {
            fll_error_print(main->error, F_status_set_fine(status), "f_string_append_nulless", F_true);

            return status;
          }
        } // for
      }
    }

    {
      f_string_dynamic_t * const parameters_value[] = {
        &main->path_build_documents,
        &main->path_build_includes,
        &main->path_build_libraries,
        &main->path_build_libraries_script,
        &main->path_build_libraries_shared,
        &main->path_build_libraries_static,
        &main->path_build_objects,
        &main->path_build_programs,
        &main->path_build_programs_script,
        &main->path_build_programs_shared,
        &main->path_build_programs_static,
        &main->path_build_settings,
        &main->path_build_stage,
        &main->path_data_build,
        &main->path_data_settings,
        &main->path_licenses,
        &main->path_sources_bash,
        &main->path_sources_c,
        &main->path_sources_cpp,
        &main->path_sources_script,
        &main->path_work_includes,
        &main->path_work_libraries,
        &main->path_work_libraries_script,
        &main->path_work_libraries_shared,
        &main->path_work_libraries_static,
        &main->path_work_programs,
        &main->path_work_programs_script,
        &main->path_work_programs_shared,
        &main->path_work_programs_static,
        &main->file_data_build_defines,
        &main->file_data_build_dependencies,
        &main->file_data_build_fakefile,
        &main->file_data_build_settings,
        &main->file_documents_readme,
      };

      for (i = 0; i < 34; ++i) {

        if (!parameters_value[i]->used) continue;

        status = f_string_dynamic_terminate_after(parameters_value[i]);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);

          return status;
        }
      } // for
    }

    return F_none;
  }
#endif // _di_fake_path_generate_

#ifndef _di_fake_path_generate_string_dynamic_
  f_status_t fake_path_generate_string_dynamic(fake_main_t *main, const f_string_dynamic_t source, f_string_dynamic_t *destination[], const uint8_t length) {

    f_status_t status = F_none;

    for (uint8_t i = 0; i < length; ++i) {

      status = f_string_dynamic_append_nulless(source, destination[i]);
      if (F_status_is_error(status)) return status;
    } // for

    return F_none;
  }
#endif // _di_fake_path_generate_string_dynamic_

#ifndef _di_fake_process_console_parameters_
  f_status_t fake_process_console_parameters(const f_console_arguments_t arguments, fake_main_t *main) {
    f_status_t status = F_none;

    // @todo move as many of the inline error printing code into more general functions where possible to provide more accurate error reporting.

    {
      const uint8_t parameters_id[] = {
        fake_parameter_fakefile,
        fake_parameter_process,
        fake_parameter_settings,
      };

      const f_string_t parameters_name[] = {
        fake_long_fakefile,
        fake_long_process,
        fake_long_settings,
      };

      const f_string_t parameter_defaults[] = {
        fake_default_fakefile,
        fake_default_process,
        fake_default_settings,
      };

      const f_array_length_t parameter_default_lengths[] = {
        fake_default_fakefile_length,
        fake_default_process_length,
        fake_default_settings_length,
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

        if (main->parameters[parameters_id[i]].result == f_console_result_found) {
          fake_print_error_parameter_missing_value(*main, parameters_name[i]);

          return F_status_set_error(F_parameter);
        }
        else if (main->parameters[parameters_id[i]].result == f_console_result_additional) {
          if (main->parameters[parameters_id[i]].locations.used > 1) {
            fake_print_error_parameter_too_many(*main, parameters_name[i]);

            return F_status_set_error(F_parameter);
          }

          f_array_length_t location = main->parameters[parameters_id[i]].values.array[0];
          f_array_length_t length = strnlen(arguments.argv[location], f_console_parameter_size);

          if (length > 0) {
            if (parameters_validate_word[i]) {
              f_array_length_t j = 0;
              f_array_length_t width_max = 0;

              for (j = 0; j < length; ++j) {

                width_max = length - j;

                status = f_utf_is_word_dash_plus(arguments.argv[location] + j, width_max, F_false);

                if (F_status_is_error(status)) {
                  if (fll_error_print(main->error, F_status_set_fine(status), "f_utf_is_word_dash_plus", F_false) == F_known_not && main->error.verbosity != f_console_verbosity_quiet) {
                    flockfile(main->error.to.stream);

                    fl_print_format("%c%[%SFailed to process the parameter '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
                    fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fake_long_process, main->error.notable);
                    fl_print_format("%['.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

                    funlockfile(main->error.to.stream);
                  }

                  return status;
                }

                if (status == F_false) {
                  if (main->error.verbosity != f_console_verbosity_quiet) {
                    flockfile(main->error.to.stream);

                    fl_print_format("%c%[%SThe '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
                    fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fake_long_process, main->error.notable);
                    fl_print_format("%[' parameters value '%]", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);
                    fl_print_format("%[%S%]", main->error.to.stream, main->error.notable, arguments.argv[location], main->error.notable);
                    fl_print_format("%[' contains non-word, non-dash, and non-plus characters.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

                    funlockfile(main->error.to.stream);
                  }

                  return F_status_set_error(F_parameter);
                }
              } // for
            }

            status = f_string_append(arguments.argv[location], length, parameters_value[i]);

            if (F_status_is_error(status)) {
              if (status == F_status_set_error(F_string_too_large)) {
                if (main->error.verbosity != f_console_verbosity_quiet) {
                  flockfile(main->error.to.stream);

                  fl_print_format("%c%[%SThe parameter '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
                  fl_print_format("%[%s%S%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, parameters_name[i], main->error.notable);
                  fl_print_format("%[' is too long.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

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
            if (main->error.verbosity != f_console_verbosity_quiet) {
              flockfile(main->error.to.stream);

              fl_print_format("%c%[%SThe parameter '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
              fl_print_format("%[%s%S%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, parameters_name[i], main->error.notable);
              fl_print_format("%[' must not be empty and must not contain only whitespace.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

              funlockfile(main->error.to.stream);
            }
          }
        }
        else if (parameter_default_lengths[i] > 0) {
          macro_f_string_dynamic_t_resize(status, (*parameters_value[i]), parameter_default_lengths[i]);

          if (F_status_is_error(status)) {
            fll_error_print(main->error, F_status_set_fine(status), "macro_f_string_dynamic_t_resize", F_true);

            return status;
          }

          memcpy(parameters_value[i]->string, parameter_defaults[i], parameter_default_lengths[i]);
          parameters_value[i]->used = parameter_default_lengths[i];
        }
      } // for
    }

    if (main->parameters[fake_parameter_define].result == f_console_result_found) {
      fake_print_error_parameter_missing_value(*main, fake_long_define);

      return F_status_set_error(F_parameter);
    }

    {
      const uint8_t parameters_id[] = {
        fake_parameter_path_build,
        fake_parameter_path_data,
        fake_parameter_path_sources,
        fake_parameter_path_work,
      };

      const f_string_t parameters_name[] = {
        fake_long_path_build,
        fake_long_path_data,
        fake_long_path_sources,
        fake_long_path_work,
      };

      const f_string_t parameter_defaults[] = {
        fake_default_path_build,
        fake_default_path_data,
        fake_default_path_sources,
        fake_default_path_work,
      };

      const f_array_length_t parameter_default_lengths[] = {
        fake_default_path_build_length,
        fake_default_path_data_length,
        fake_default_path_sources_length,
        fake_default_path_work_length,
      };

      f_string_dynamic_t * const parameters_value[] = {
        &main->path_build,
        &main->path_data,
        &main->path_sources,
        &main->path_work,
      };

      for (uint8_t i = 0; i < 4; ++i) {

        if (main->parameters[parameters_id[i]].result == f_console_result_found) {
          fake_print_error_parameter_missing_value(*main, parameters_name[i]);
          return F_status_set_error(F_parameter);
        }
        else if (main->parameters[parameters_id[i]].result == f_console_result_additional) {
          if (main->parameters[parameters_id[i]].values.used > 1) {
            fake_print_error_parameter_too_many(*main, parameters_name[i]);
            return F_status_set_error(F_parameter);
          }

          status = fl_console_parameter_to_string_dynamic_directory(arguments.argv[main->parameters[parameters_id[i]].values.array[0]], parameters_value[i]);

          if (F_status_is_error(status)) {
            if (fll_error_print(main->error, F_status_set_fine(status), "fl_console_parameter_to_string_dynamic_directory", F_false) == F_known_not && main->error.verbosity != f_console_verbosity_quiet) {
              flockfile(main->error.to.stream);

              fl_print_format("%c%[%SFailed to process parameter '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
              fl_print_format("%[%s%S%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, parameters_name[i], main->error.notable);
              fl_print_format("%['.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

              funlockfile(main->error.to.stream);
            }

            return status;
          }
        }
        else if (parameter_default_lengths[i] > 0) {
           macro_f_string_dynamic_t_resize(status, (*parameters_value[i]), parameter_default_lengths[i]);

          if (F_status_is_error(status)) {
            if (fll_error_print(main->error, F_status_set_fine(status), " macro_f_string_dynamic_t_resize", F_false) == F_known_not && main->error.verbosity != f_console_verbosity_quiet) {
              flockfile(main->error.to.stream);

              fl_print_format("%c%[%SFailed to load default for the parameter '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
              fl_print_format("%[%s%S%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, parameters_name[i], main->error.notable);
              fl_print_format("%['.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

              funlockfile(main->error.to.stream);
            }

            return status;
          }

          memcpy(parameters_value[i]->string, parameter_defaults[i], parameter_default_lengths[i]);
          parameters_value[i]->used = parameter_default_lengths[i];
        }
      } // for
    }

    if (main->parameters[fake_parameter_define].result == f_console_result_additional) {
      status = fll_program_parameter_additional_rip(arguments.argv, main->parameters[fake_parameter_define].values, &main->define);

      if (F_status_is_error(status)) {
        if (fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_additional_rip", F_false) == F_known_not && main->error.verbosity != f_console_verbosity_quiet) {
          flockfile(main->error.to.stream);

          fl_print_format("%c%[%SFailed to process the parameter '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fake_long_define, main->error.notable);
          fl_print_format("%['.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

          funlockfile(main->error.to.stream);
        }

        return status;
      }
    }

    if (main->parameters[fake_parameter_mode].result == f_console_result_found) {
      fake_print_error_parameter_missing_value(*main, fake_long_mode);
      return F_status_set_error(F_parameter);
    }
    else if (main->parameters[fake_parameter_mode].result == f_console_result_additional) {
      status = fll_program_parameter_additional_rip(arguments.argv, main->parameters[fake_parameter_mode].values, &main->mode);

      if (F_status_is_error(status)) {
        if (fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_additional_rip", F_false) == F_known_not && main->error.verbosity != f_console_verbosity_quiet) {
          flockfile(main->error.to.stream);

          fl_print_format("%c%[%SFailed to process the parameter '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fake_long_mode, main->error.notable);
          fl_print_format("%['.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

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
            if (fll_error_print(main->error, F_status_set_fine(status), "f_utf_is_word_dash_plus", F_false) == F_known_not && main->error.verbosity != f_console_verbosity_quiet) {
              flockfile(main->error.to.stream);

              fl_print_format("%c%[%SFailed to process the parameter '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
              fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fake_long_mode, main->error.notable);
              fl_print_format("%['.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

              funlockfile(main->error.to.stream);
            }

            return status;
          }

          if (status == F_false) {
            if (main->error.verbosity != f_console_verbosity_quiet) {
              flockfile(main->error.to.stream);

              fl_print_format("%c%[%SThe '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
              fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fake_long_mode, main->error.notable);
              fl_print_format("%[' parameters value '%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fake_long_mode, main->error.notable);
              fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, main->mode.array[i], main->error.notable);
              fl_print_format("%[' contains non-word, non-dash, and non-plus characters.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

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

#ifndef _di_fake_signal_read_
  f_status_t fake_signal_received(const fake_main_t main) {

    if (!main.signal.id) {
      return F_false;
    }

    f_status_t status = F_none;

    struct signalfd_siginfo information;

    memset(&information, 0, sizeof(struct signalfd_siginfo));

    status = f_signal_read(main.signal, &information);

    if (status == F_signal) {
      switch (information.ssi_signo) {
        case F_signal_abort:
        case F_signal_hangup:
        case F_signal_interrupt:
        case F_signal_quit:
        case F_signal_termination:

          if (main.error.verbosity != f_console_verbosity_quiet) {
            fll_print_format("%c%[ALERT: An appropriate exit signal has been received, now aborting.%]%c", main.error.to.stream, f_string_eol_s[0], main.error.context, main.error.context, f_string_eol_s[0]);
          }

          return F_true;
      }
    }

    return F_false;
  }
#endif // _di_fake_signal_read_

#ifndef _di_fake_signal_state_interrupt_fss_
  f_status_t fake_signal_state_interrupt_fss(void *state, void *internal) {

    if (!state) {
      return F_interrupt_not;
    }

    f_state_t *state_ptr = (f_state_t *) state;

    if (!state_ptr->custom) {
      return F_interrupt_not;
    }

    fake_main_t *main = (fake_main_t *) state_ptr->custom;

    if (fake_signal_received(*main)) {
      return F_status_set_error(F_interrupt);
    }

    return F_interrupt_not;
  }
#endif // _di_fake_signal_state_interrupt_fss_

#ifndef _di_fake_signal_state_interrupt_iki_
  f_status_t fake_signal_state_interrupt_iki(void *state, void *internal) {

    if (!state) {
      return F_interrupt_not;
    }

    f_state_t *state_ptr = (f_state_t *) state;

    if (!state_ptr->custom) {
      return F_interrupt_not;
    }

    fake_main_t *main = (fake_main_t *) state_ptr->custom;

    if (fake_signal_received(*main)) {
      return F_status_set_error(F_interrupt);
    }

    return F_interrupt_not;
  }
#endif // _di_fake_signal_state_interrupt_iki_

#ifndef _di_fake_validate_directories_
  f_status_t fake_validate_parameter_directories(const f_console_arguments_t arguments, const fake_main_t main) {

    if (fake_signal_received(main)) {
      return F_signal;
    }

    const f_string_t parameters_name[] = {
      fake_long_path_build,
      fake_long_path_data,
      fake_long_path_work,
    };

    const f_string_t parameter_defaults[] = {
      fake_default_path_build,
      fake_default_path_data,
      fake_default_path_work,
    };

    const f_array_length_t parameter_default_lengths[] = {
      fake_default_path_build_length,
      fake_default_path_data_length,
      fake_default_path_work_length,
    };

    const f_string_dynamic_t *parameters_value[] = {
      &main.path_build,
      &main.path_data,
      &main.path_work,
    };

    const bool parameters_required[] = {
      F_false,
      F_true,
      F_false,
    };

    struct stat directory_stat;
    f_status_t status = F_none;

    for (uint8_t i = 0; i < 3; ++i) {

      if (fake_signal_received(main)) {
        return F_status_set_error(F_signal);
      }

      if (parameters_value[i]->used) {
        memset(&directory_stat, 0, sizeof(struct stat));

        status = f_file_stat(parameters_value[i]->string, F_true, &directory_stat);

        if (status == F_status_set_error(F_file_found_not)) status = F_status_set_error(F_directory_found_not);

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) != F_directory_found_not || parameters_required[i]) {
            fll_error_file_print(main.error, F_status_set_fine(status), "f_file_stat", F_true, parameters_value[i]->string, "access", fll_error_file_type_directory);

            return status;
          }
        }
      }
      else if (parameters_required[i]) {
        flockfile(main.error.to.stream);

        fl_print_format("%c%[%SNo valid path for the (required) directory parameter '%]", main.error.to.stream, f_string_eol_s[0], main.error.context, main.error.prefix, main.error.context);
        fl_print_format("%[%s%s%]", main.error.to.stream, main.error.notable, f_console_symbol_long_enable_s, parameters_name[i], main.error.notable);
        fl_print_format("%[' was found.%]%c", main.error.to.stream, main.error.context, main.error.context, f_string_eol_s[0]);

        funlockfile(main.error.to.stream);

        return F_status_set_error(F_directory_found_not);
      }
    } // for

    return F_none;
  }
#endif // _di_fake_validate_parameter_directories_

#ifndef _di_fake_verbose_print_clone_
  void fake_verbose_print_clone(const f_file_t output, const f_string_t source, const f_string_t destination) {
    fll_print_format("Cloned '%S' to '%S'.%c", output.stream, source, destination, f_string_eol_s[0]);
  }
#endif // _di_fake_verbose_print_clone_

#ifndef _di_fake_verbose_print_copy_
  void fake_verbose_print_copy(const f_file_t output, const f_string_t source, const f_string_t destination) {
    fll_print_format("Copied '%S' to '%S'.%c", output.stream, source, destination, f_string_eol_s[0]);
  }
#endif // _di_fake_verbose_print_copy_

#ifndef _di_fake_verbose_print_move_
  void fake_verbose_print_move(const f_file_t output, const f_string_t source, const f_string_t destination) {
    fll_print_format("Moved '%S' to '%S'.%c", output.stream, source, destination, f_string_eol_s[0]);
  }
#endif // _di_fake_verbose_print_move_

#ifdef __cplusplus
} // extern "C"
#endif
