#include "fake.h"
#include "private-fake.h"
#include "private-build.h"
#include "private-make.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_execute_
  int fake_execute(const fake_data_t data, const f_string_maps_t environment, const f_string_static_t program, const f_string_statics_t arguments, f_status_t *status) {
    if (F_status_is_error(*status)) return 1;

    if (data.error.verbosity == f_console_verbosity_verbose) {
      fprintf(data.output.stream, "%s", program.string);

      for (f_array_length_t i = 0; i < arguments.used; i++) {
        if (!arguments.array[i].used) continue;

        fprintf(data.output.stream, " %s", arguments.array[i].string);
      } // for

      fprintf(data.output.stream, "%c", f_string_eol[0]);

      // flush to stdout before executing command.
      fflush(data.output.stream);
    }

    if (fake_signal_received(data)) {
      *status = F_status_set_error(F_signal);
      return 0;
    }

    int return_code = 0;

    if (program.used) {

      // child processes should receive all signals, without blocking.
      f_signal_how_t signals = f_signal_how_t_initialize;
      f_signal_set_empty(&signals.block);
      f_signal_set_fill(&signals.block_not);

      fl_execute_parameter_t parameter = fl_macro_execute_parameter_t_initialize(0, &environment, &signals, 0);

      *status = fll_execute_program(program.string, arguments, &parameter, &return_code);

      if (fake_signal_received(data)) {
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
        if (data.error.verbosity != f_console_verbosity_quiet) {
          fprintf(data.error.to.stream, "%c", f_string_eol[0]);
          fl_color_print(data.error.to.stream, data.context.set.error, "%sFailed to find program '", fll_error_print_error);
          fl_color_print(data.error.to.stream, data.context.set.notable, "%s", program.used ? program.string : f_string_empty_s);
          fl_color_print(data.error.to.stream, data.context.set.error, "' for executing.%c", f_string_eol[0]);
        }
      }
      else {
        fll_error_print(data.error, F_status_set_fine(*status), "fll_execute_program_environment", F_true);
      }
    }

    return return_code;
  }
#endif // _di_fake_execute_

#ifndef _di_fake_file_buffer_
  f_return_status fake_file_buffer(const fake_data_t data, const f_string_t path_file, f_string_dynamic_t *buffer) {
    f_file_t file = f_file_t_initialize;
    f_string_t name_function = "f_file_exists";
    f_status_t status = F_none;

    if (fake_signal_received(data)) {
      return F_status_set_error(F_signal);
    }

    status = f_file_exists(path_file);

    if (status == F_true) {
      {
        f_string_length_t size_file = 0;

        name_function = "f_file_size";
        status = f_file_size(path_file, F_true, &size_file);

        if (F_status_is_error_not(status)) {
          if (size_file > fake_common_initial_buffer_max) {
            size_file = fake_common_initial_buffer_max;
          }

          f_macro_string_dynamic_t_new((status), (*buffer), size_file);

          if (F_status_is_error(status)) {
            fll_error_file_print(data.error, F_status_set_fine(status), name_function, F_true, path_file, "allocate buffer size for", fll_error_file_type_file);

            fl_string_dynamic_delete(&(*buffer));
            return status;
          }
        }

        status = F_true;
      }

      name_function = "f_file_open";
      status = f_file_stream_open(path_file, 0, &file);

      if (fake_signal_received(data)) {
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
      fll_error_file_print(data.error, F_status_set_fine(status), name_function, F_true, path_file, "read", fll_error_file_type_file);

      fl_string_dynamic_delete(&(*buffer));
    }

    return status;
  }
#endif // _di_fake_file_buffer_

#ifndef _di_fake_path_generate_
  f_return_status fake_path_generate(fake_data_t *data) {
    f_status_t status = F_none;
    uint8_t i = 0;

    {
      const f_string_dynamic_t *parameters_source[] = {
        &data->path_build,
        &data->path_data,
        &data->path_sources,
      };

      const uint8_t parameters_length[] = {
        7,
        2,
        4,
      };

      f_string_dynamic_t *parameters_value_0[] = {
        &data->path_build_documents,
        &data->path_build_includes,
        &data->path_build_libraries,
        &data->path_build_objects,
        &data->path_build_programs,
        &data->path_build_settings,
        &data->path_build_stage,
      };

      f_string_dynamic_t *parameters_value_1[] = {
        &data->path_data_build,
        &data->path_data_settings,
      };

      f_string_dynamic_t *parameters_value_2[] = {
        &data->path_sources_bash,
        &data->path_sources_c,
        &data->path_sources_cpp,
        &data->path_sources_script,
      };

      f_string_dynamic_t **const parameters_value[] = {
        parameters_value_0,
        parameters_value_1,
        parameters_value_2,
      };

      for (i = 0; i < 3; i++) {
        status = fake_path_generate_string_dynamic(data, *parameters_source[i], parameters_value[i], parameters_length[i]);

        if (F_status_is_error(status)) {
          fll_error_print(data->error, F_status_set_fine(status), "fake_path_generate_string_dynamic", F_true);
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

      const f_string_length_t parameters_length[] = {
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
        &data->path_build_documents,
        &data->path_build_includes,
        &data->path_build_libraries,
        &data->path_build_objects,
        &data->path_build_programs,
        &data->path_build_settings,
        &data->path_build_stage,
        &data->path_data_build,
        &data->path_data_settings,
        &data->path_documents,
        &data->path_licenses,
        &data->path_sources_bash,
        &data->path_sources_c,
        &data->path_sources_cpp,
        &data->path_sources_script,
      };

      for (i = 0; i < 15; i++) {
        status = fl_string_append_nulless(parameters_source[i], parameters_length[i], parameters_value[i]);

        if (F_status_is_error(status)) {
          fll_error_print(data->error, F_status_set_fine(status), "fl_string_append_nulless", F_true);
          return status;
        }
      } // for
    }

    {
      const f_string_dynamic_t *parameters_source[] = {
        &data->path_build_libraries,
        &data->path_build_programs,
        &data->path_data_build,
        &data->path_documents,
      };

      const uint8_t parameters_length[] = {
        3,
        3,
        4,
        1,
      };

      f_string_dynamic_t *parameters_value_0[] = {
        &data->path_build_libraries_script,
        &data->path_build_libraries_shared,
        &data->path_build_libraries_static,
      };

      f_string_dynamic_t *parameters_value_1[] = {
        &data->path_build_programs_script,
        &data->path_build_programs_shared,
        &data->path_build_programs_static,
      };

      f_string_dynamic_t *parameters_value_2[] = {
        &data->file_data_build_defines,
        &data->file_data_build_dependencies,
        &data->file_data_build_fakefile,
        &data->file_data_build_settings,
      };

      f_string_dynamic_t *parameters_value_3[] = {
        &data->file_documents_readme,
      };

      f_string_dynamic_t **const parameters_value[] = {
        parameters_value_0,
        parameters_value_1,
        parameters_value_2,
        parameters_value_3,
      };

      for (i = 0; i < 4; i++) {
        status = fake_path_generate_string_dynamic(data, *parameters_source[i], parameters_value[i], parameters_length[i]);

        if (F_status_is_error(status)) {
          fll_error_print(data->error, F_status_set_fine(status), "fake_path_generate_string_dynamic", F_true);
          return status;
        }
      } // for
    }

    // When custom fakefile or settings are used and they are paths to a file, remove the default path.
    if (f_path_is(data->fakefile.string, data->fakefile.used)) {
      data->file_data_build_fakefile.used = 0;
    }

    if (f_path_is(data->settings.string, data->settings.used)) {
      data->file_data_build_settings.used = 0;
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
        data->fakefile.string,
        data->settings.string,
        fake_file_readme,
      };

      const f_string_length_t parameters_length[] = {
        fake_path_part_script_length,
        fake_path_part_shared_length,
        fake_path_part_static_length,
        fake_path_part_script_length,
        fake_path_part_shared_length,
        fake_path_part_static_length,
        fake_file_defines_length,
        fake_file_dependencies_length,
        data->fakefile.used,
        data->settings.used,
        fake_file_readme_length,
      };

      f_string_dynamic_t * const parameters_value[] = {
        &data->path_build_libraries_script,
        &data->path_build_libraries_shared,
        &data->path_build_libraries_static,
        &data->path_build_programs_script,
        &data->path_build_programs_shared,
        &data->path_build_programs_static,
        &data->file_data_build_defines,
        &data->file_data_build_dependencies,
        &data->file_data_build_fakefile,
        &data->file_data_build_settings,
        &data->file_documents_readme,
      };

      for (i = 0; i < 11; i++) {
        status = fl_string_append_nulless(parameters_source[i], parameters_length[i], parameters_value[i]);

        if (F_status_is_error(status)) {
          fll_error_print(data->error, F_status_set_fine(status), "fl_string_append_nulless", F_true);
          return status;
        }
      } // for
    }

    if (data->path_work.used > 0) {
      {
        f_string_dynamic_t * const parameters_value[] = {
          &data->path_work_includes,
          &data->path_work_libraries,
          &data->path_work_programs,
        };

        for (i = 0; i < 3; i++) {
          status = fl_string_dynamic_append_nulless(data->path_work, parameters_value[i]);

          if (F_status_is_error(status)) {
            fll_error_print(data->error, F_status_set_fine(status), "fl_string_dynamic_append_nulless", F_true);
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

        const f_string_length_t parameters_length[] = {
          fake_path_part_includes_length,
          fake_path_part_libraries_length,
          fake_path_part_programs_length,
        };

        f_string_dynamic_t * const parameters_value[] = {
          &data->path_work_includes,
          &data->path_work_libraries,
          &data->path_work_programs,
        };

        for (i = 0; i < 3; i++) {
          status = fl_string_append_nulless(parameters_source[i], parameters_length[i], parameters_value[i]);

          if (F_status_is_error(status)) {
            fll_error_print(data->error, F_status_set_fine(status), "fl_string_append_nulless", F_true);
            return status;
          }
        } // for
      }

      {
        const f_string_dynamic_t *parameters_source[] = {
          &data->path_work_libraries,
          &data->path_work_programs,
        };

        const uint8_t parameters_length[] = {
          3,
          3,
        };

        f_string_dynamic_t *parameters_value_0[] = {
          &data->path_work_libraries_script,
          &data->path_work_libraries_shared,
          &data->path_work_libraries_static,
        };

        f_string_dynamic_t *parameters_value_1[] = {
          &data->path_work_programs_script,
          &data->path_work_programs_shared,
          &data->path_work_programs_static,
        };

        f_string_dynamic_t **const parameters_value[] = {
          parameters_value_0,
          parameters_value_1,
        };

        for (i = 0; i < 2; i++) {
          status = fake_path_generate_string_dynamic(data, *parameters_source[i], parameters_value[i], parameters_length[i]);

          if (F_status_is_error(status)) {
            fll_error_print(data->error, F_status_set_fine(status), "fake_path_generate_string_dynamic", F_true);
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

        const f_string_length_t parameters_length[] = {
          fake_path_part_script_length,
          fake_path_part_shared_length,
          fake_path_part_static_length,
          fake_path_part_script_length,
          fake_path_part_shared_length,
          fake_path_part_static_length,
        };

        f_string_dynamic_t * const parameters_value[] = {
          &data->path_work_libraries_script,
          &data->path_work_libraries_shared,
          &data->path_work_libraries_static,
          &data->path_work_programs_script,
          &data->path_work_programs_shared,
          &data->path_work_programs_static,
        };

        for (i = 0; i < 6; i++) {
          status = fl_string_append_nulless(parameters_source[i], parameters_length[i], parameters_value[i]);

          if (F_status_is_error(status)) {
            fll_error_print(data->error, F_status_set_fine(status), "fl_string_append_nulless", F_true);
            return status;
          }
        } // for
      }
    }

    {
      f_string_dynamic_t * const parameters_value[] = {
        &data->path_build_documents,
        &data->path_build_includes,
        &data->path_build_libraries,
        &data->path_build_libraries_script,
        &data->path_build_libraries_shared,
        &data->path_build_libraries_static,
        &data->path_build_objects,
        &data->path_build_programs,
        &data->path_build_programs_script,
        &data->path_build_programs_shared,
        &data->path_build_programs_static,
        &data->path_build_settings,
        &data->path_build_stage,
        &data->path_data_build,
        &data->path_data_settings,
        &data->path_licenses,
        &data->path_sources_bash,
        &data->path_sources_c,
        &data->path_sources_cpp,
        &data->path_sources_script,
        &data->path_work_includes,
        &data->path_work_libraries,
        &data->path_work_libraries_script,
        &data->path_work_libraries_shared,
        &data->path_work_libraries_static,
        &data->path_work_programs,
        &data->path_work_programs_script,
        &data->path_work_programs_shared,
        &data->path_work_programs_static,
        &data->file_data_build_defines,
        &data->file_data_build_dependencies,
        &data->file_data_build_fakefile,
        &data->file_data_build_settings,
        &data->file_documents_readme,
      };

      for (i = 0; i < 34; i++) {
        if (!parameters_value[i]->used) continue;

        status = fl_string_dynamic_terminate_after(parameters_value[i]);

        if (F_status_is_error(status)) {
          fll_error_print(data->error, F_status_set_fine(status), "fl_string_dynamic_terminate_after", F_true);
          return status;
        }
      } // for
    }

    return F_none;
  }
#endif // _di_fake_path_generate_

#ifndef _di_fake_path_generate_string_dynamic_
  f_return_status fake_path_generate_string_dynamic(fake_data_t *data, const f_string_dynamic_t source, f_string_dynamic_t *destination[], const uint8_t length) {
    f_status_t status = F_none;

    for (uint8_t i = 0; i < length; i++) {
      status = fl_string_dynamic_append_nulless(source, destination[i]);
      if (F_status_is_error(status)) return status;
    } // for

    return F_none;
  }
#endif // _di_fake_path_generate_string_dynamic_

#ifndef _di_fake_process_console_parameters_
  f_return_status fake_process_console_parameters(const f_console_arguments_t arguments, fake_data_t *data) {
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

      const f_string_length_t parameter_default_lengths[] = {
        fake_default_fakefile_length,
        fake_default_process_length,
        fake_default_settings_length,
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

      for (uint8_t i = 0; i < 3; i++) {

        if (data->parameters[parameters_id[i]].result == f_console_result_found) {
          fake_print_error_parameter_missing_value(*data, parameters_name[i]);
          return F_status_set_error(F_parameter);
        }
        else if (data->parameters[parameters_id[i]].result == f_console_result_additional) {
          if (data->parameters[parameters_id[i]].locations.used > 1) {
            fake_print_error_parameter_too_many(*data, parameters_name[i]);
            return F_status_set_error(F_parameter);
          }

          f_string_length_t location = data->parameters[parameters_id[i]].values.array[0];
          f_string_length_t length = strnlen(arguments.argv[location], f_console_length_size);

          if (length > 0) {
            if (parameters_validate_word[i]) {
              f_string_length_t j = 0;
              f_string_length_t width_max = 0;

              for (j = 0; j < length; j++) {
                width_max = length - j;

                status = f_utf_is_word_dash_plus(arguments.argv[location] + j, width_max, F_false);

                if (F_status_is_error(status)) {
                  if (fll_error_print(data->error, F_status_set_fine(status), "f_utf_is_word_dash_plus", F_false) == F_known_not && data->error.verbosity != f_console_verbosity_quiet) {
                    fprintf(data->error.to.stream, "%c", f_string_eol[0]);
                    fl_color_print(data->error.to.stream, data->context.set.error, "%sFailed to process the parameter '", fll_error_print_error);
                    fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fake_long_process);
                    fl_color_print(data->error.to.stream, data->context.set.error, "'.%c", f_string_eol[0]);
                  }

                  return status;
                }

                if (status == F_false) {
                  if (data->error.verbosity != f_console_verbosity_quiet) {
                    fprintf(data->error.to.stream, "%c", f_string_eol[0]);
                    fl_color_print(data->error.to.stream, data->context.set.error, "%sThe '", fll_error_print_error);
                    fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fake_long_process);
                    fl_color_print(data->error.to.stream, data->context.set.error, "' parameters value '");
                    fl_color_print(data->error.to.stream, data->context.set.notable, "%s", arguments.argv[location]);
                    fl_color_print(data->error.to.stream, data->context.set.error, "' contains non-word, non-dash, and non-plus characters.%c", f_string_eol[0]);
                  }

                  return F_status_set_error(F_parameter);
                }
              } // for
            }

            status = fl_string_append(arguments.argv[location], length, parameters_value[i]);

            if (F_status_is_error(status)) {
              if (status == F_status_set_error(F_string_too_large)) {
                if (data->error.verbosity != f_console_verbosity_quiet) {
                  fprintf(data->error.to.stream, "%c", f_string_eol[0]);
                  fl_color_print(data->error.to.stream, data->context.set.error, "%sThe parameter '", fll_error_print_error);
                  fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, parameters_name[i]);
                  fl_color_print(data->error.to.stream, data->context.set.error, "' is too long.%c", f_string_eol[0]);
                }
              }
              else {
                fll_error_print(data->error, F_status_set_fine(status), "fl_string_append", F_true);
              }

              return status;
            }
            else {
              status = F_none;
            }
          }

          if (length == 0 || status == F_data_not) {
            if (data->error.verbosity != f_console_verbosity_quiet) {
              fprintf(data->error.to.stream, "%c", f_string_eol[0]);
              fl_color_print(data->error.to.stream, data->context.set.error, "%sThe parameter '", fll_error_print_error);
              fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, parameters_name[i]);
              fl_color_print(data->error.to.stream, data->context.set.error, "' must not be empty and must not contain only whitespace.%c", f_string_eol[0]);
            }
          }
        }
        else if (parameter_default_lengths[i] > 0) {
          f_macro_string_dynamic_t_resize(status, (*parameters_value[i]), parameter_default_lengths[i]);

          if (F_status_is_error(status)) {
            fll_error_print(data->error, F_status_set_fine(status), "f_macro_string_dynamic_t_resize", F_true);
            return status;
          }

          memcpy(parameters_value[i]->string, parameter_defaults[i], parameter_default_lengths[i]);
          parameters_value[i]->used = parameter_default_lengths[i];
        }
      } // for
    }

    if (data->parameters[fake_parameter_define].result == f_console_result_found) {
      fake_print_error_parameter_missing_value(*data, fake_long_define);
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

      const f_string_length_t parameter_default_lengths[] = {
        fake_default_path_build_length,
        fake_default_path_data_length,
        fake_default_path_sources_length,
        fake_default_path_work_length,
      };

      f_string_dynamic_t * const parameters_value[] = {
        &data->path_build,
        &data->path_data,
        &data->path_sources,
        &data->path_work,
      };

      for (uint8_t i = 0; i < 4; i++) {

        if (data->parameters[parameters_id[i]].result == f_console_result_found) {
          fake_print_error_parameter_missing_value(*data, parameters_name[i]);
          return F_status_set_error(F_parameter);
        }
        else if (data->parameters[parameters_id[i]].result == f_console_result_additional) {
          if (data->parameters[parameters_id[i]].values.used > 1) {
            fake_print_error_parameter_too_many(*data, parameters_name[i]);
            return F_status_set_error(F_parameter);
          }

          status = fl_console_parameter_to_string_dynamic_directory(arguments.argv[data->parameters[parameters_id[i]].values.array[0]], parameters_value[i]);

          if (F_status_is_error(status)) {
            if (fll_error_print(data->error, F_status_set_fine(status), "fl_console_parameter_to_string_dynamic_directory", F_false) == F_known_not && data->error.verbosity != f_console_verbosity_quiet) {
              fprintf(data->error.to.stream, "%c", f_string_eol[0]);
              fl_color_print(data->error.to.stream, data->context.set.error, "%sFailed to process parameter '", fll_error_print_error);
              fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, parameters_name[i]);
              fl_color_print(data->error.to.stream, data->context.set.error, "'.%c", f_string_eol[0]);
            }

            return status;
          }
        }
        else if (parameter_default_lengths[i] > 0) {
          f_macro_string_dynamic_t_new(status, (*parameters_value[i]), parameter_default_lengths[i]);

          if (F_status_is_error(status)) {
            if (fll_error_print(data->error, F_status_set_fine(status), "f_macro_string_dynamic_t_new", F_false) == F_known_not && data->error.verbosity != f_console_verbosity_quiet) {
              fprintf(data->error.to.stream, "%c", f_string_eol[0]);
              fl_color_print(data->error.to.stream, data->context.set.error, "%sFailed to load default for the parameter '", fll_error_print_error);
              fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, parameters_name[i]);
              fl_color_print(data->error.to.stream, data->context.set.error, "'.%c", f_string_eol[0]);
            }

            return status;
          }

          memcpy(parameters_value[i]->string, parameter_defaults[i], parameter_default_lengths[i]);
          parameters_value[i]->used = parameter_default_lengths[i];
        }
      } // for
    }

    if (data->parameters[fake_parameter_define].result == f_console_result_additional) {
      status = fll_program_parameter_additional_rip(arguments.argv, data->parameters[fake_parameter_define].values, &data->define);

      if (F_status_is_error(status)) {
        if (fll_error_print(data->error, F_status_set_fine(status), "fll_program_parameter_additional_rip", F_false) == F_known_not && data->error.verbosity != f_console_verbosity_quiet) {
          fprintf(data->error.to.stream, "%c", f_string_eol[0]);
          fl_color_print(data->error.to.stream, data->context.set.error, "%sFailed to process the parameter '", fll_error_print_error);
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fake_long_define);
          fl_color_print(data->error.to.stream, data->context.set.error, "'.%c", f_string_eol[0]);
        }

        return status;
      }

      f_array_length_t i = 0;
      f_string_length_t j = 0;
      f_string_length_t width_max = 0;

      for (; i < data->define.used; i++) {

        for (j = 0; j < data->define.array[i].used; j++) {

          width_max = data->define.array[i].used - j;

          status = f_utf_is_word(data->define.array[i].string + j, width_max, F_false);

          if (F_status_is_error(status)) {
            if (fll_error_print(data->error, F_status_set_fine(status), "f_utf_is_word", F_false) == F_known_not && data->error.verbosity != f_console_verbosity_quiet) {
              fprintf(data->error.to.stream, "%c", f_string_eol[0]);
              fl_color_print(data->error.to.stream, data->context.set.error, "%sFailed to process the parameter '", fll_error_print_error);
              fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fake_long_define);
              fl_color_print(data->error.to.stream, data->context.set.error, "'.%c", f_string_eol[0]);
            }

            return status;
          }

          if (status == F_false) {
            if (data->error.verbosity != f_console_verbosity_quiet) {
              fprintf(data->error.to.stream, "%c", f_string_eol[0]);
              fl_color_print(data->error.to.stream, data->context.set.error, "%sThe '", fll_error_print_error);
              fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fake_long_define);
              fl_color_print(data->error.to.stream, data->context.set.error, "' parameters value '");
              fl_color_print(data->error.to.stream, data->context.set.notable, "%s", data->define.array[i].string);
              fl_color_print(data->error.to.stream, data->context.set.error, "' contains non-word characters.%c", f_string_eol[0]);
            }

            return F_status_set_error(F_parameter);
          }
        } // for
      } // for
    }

    if (data->parameters[fake_parameter_mode].result == f_console_result_found) {
      fake_print_error_parameter_missing_value(*data, fake_long_mode);
      return F_status_set_error(F_parameter);
    }
    else if (data->parameters[fake_parameter_mode].result == f_console_result_additional) {
      status = fll_program_parameter_additional_rip(arguments.argv, data->parameters[fake_parameter_mode].values, &data->mode);

      if (F_status_is_error(status)) {
        if (fll_error_print(data->error, F_status_set_fine(status), "fll_program_parameter_additional_rip", F_false) == F_known_not && data->error.verbosity != f_console_verbosity_quiet) {
          fprintf(data->error.to.stream, "%c", f_string_eol[0]);
          fl_color_print(data->error.to.stream, data->context.set.error, "%sFailed to process the parameter '", fll_error_print_error);
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fake_long_mode);
          fl_color_print(data->error.to.stream, data->context.set.error, "'.%c", f_string_eol[0]);
        }

        return status;
      }

      f_array_length_t i = 0;
      f_string_length_t j = 0;
      f_string_length_t width_max = 0;

      for (; i < data->mode.used; i++) {

        for (j = 0; j < data->mode.array[i].used; j++) {

          width_max = data->mode.array[i].used - j;

          status = f_utf_is_word_dash_plus(data->mode.array[i].string + j, width_max, F_false);

          if (F_status_is_error(status)) {
            if (fll_error_print(data->error, F_status_set_fine(status), "f_utf_is_word_dash_plus", F_false) == F_known_not && data->error.verbosity != f_console_verbosity_quiet) {
              fprintf(data->error.to.stream, "%c", f_string_eol[0]);
              fl_color_print(data->error.to.stream, data->context.set.error, "%sFailed to process the parameter '", fll_error_print_error);
              fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fake_long_mode);
              fl_color_print(data->error.to.stream, data->context.set.error, "'.%c", f_string_eol[0]);
            }

            return status;
          }

          if (status == F_false) {
            if (data->error.verbosity != f_console_verbosity_quiet) {
              fprintf(data->error.to.stream, "%c", f_string_eol[0]);
              fl_color_print(data->error.to.stream, data->context.set.error, "%sThe '", fll_error_print_error);
              fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fake_long_mode);
              fl_color_print(data->error.to.stream, data->context.set.error, "' parameters value '");
              fl_color_print(data->error.to.stream, data->context.set.notable, "%s", data->mode.array[i].string);
              fl_color_print(data->error.to.stream, data->context.set.error, "' contains non-word, non-dash, and non-plus characters.%c", f_string_eol[0]);
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
  f_return_status fake_signal_received(const fake_data_t data) {

    if (!data.signal.id) {
      return F_false;
    }

    f_status_t status = F_none;

    struct signalfd_siginfo information;

    memset(&information, 0, sizeof(struct signalfd_siginfo));

    status = f_signal_read(data.signal, &information);

    if (status == F_signal) {
      switch (information.ssi_signo) {
        case F_signal_abort:
        case F_signal_hangup:
        case F_signal_interrupt:
        case F_signal_quit:
        case F_signal_termination:

          if (data.error.verbosity != f_console_verbosity_quiet) {
            fprintf(data.error.to.stream, "%c", f_string_eol[0]);
            fl_color_print(data.error.to.stream, data.context.set.error, "ALERT: An appropriate exit signal has been received, now aborting.");
            fprintf(data.error.to.stream, "%c", f_string_eol[0]);
          }

          return F_true;
      }
    }

    return F_false;
  }
#endif // _di_fake_signal_read_

#ifndef _di_fake_validate_directories_
  f_return_status fake_validate_parameter_directories(const f_console_arguments_t arguments, const fake_data_t data) {

    if (fake_signal_received(data)) {
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

    const f_string_length_t parameter_default_lengths[] = {
      fake_default_path_build_length,
      fake_default_path_data_length,
      fake_default_path_work_length,
    };

    const f_string_dynamic_t *parameters_value[] = {
      &data.path_build,
      &data.path_data,
      &data.path_work,
    };

    const bool parameters_required[] = {
      F_false,
      F_true,
      F_false,
    };

    struct stat directory_stat;
    f_status_t status = F_none;

    for (uint8_t i = 0; i < 3; i++) {

      if (fake_signal_received(data)) {
        return F_status_set_error(F_signal);
      }

      if (parameters_value[i]->used > 0) {
        memset(&directory_stat, 0, sizeof(struct stat));

        status = f_file_stat(parameters_value[i]->string, F_true, &directory_stat);

        if (status == F_status_set_error(F_file_found_not)) status = F_status_set_error(F_directory_found_not);

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) != F_directory_found_not || parameters_required[i]) {
            fll_error_file_print(data.error, F_status_set_fine(status), "f_file_stat", F_true, parameters_value[i]->string, "access", fll_error_file_type_directory);

            return status;
          }
        }
      }
      else if (parameters_required[i]) {
        fprintf(data.error.to.stream, "%c", f_string_eol[0]);
        fl_color_print(data.error.to.stream, data.context.set.error, "%sNo valid path for the (required) directory parameter '", fll_error_print_error);
        fl_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable, parameters_name[i]);
        fl_color_print(data.error.to.stream, data.context.set.error, "' was found.%c", f_string_eol[0]);

        return F_status_set_error(F_directory_found_not);
      }
    } // for

    return F_none;
  }
#endif // _di_fake_validate_parameter_directories_

#ifndef _di_fake_verbose_print_clone_
  void fake_verbose_print_clone(const f_file_t output, const f_string_t source, const f_string_t destination) {
    fprintf(output.stream, "Cloned '%s' to '%s'.%c", source, destination, f_string_eol[0]);
  }
#endif // _di_fake_verbose_print_clone_

#ifndef _di_fake_verbose_print_copy_
  void fake_verbose_print_copy(const f_file_t output, const f_string_t source, const f_string_t destination) {
    fprintf(output.stream, "Copied '%s' to '%s'.%c", source, destination, f_string_eol[0]);
  }
#endif // _di_fake_verbose_print_copy_

#ifndef _di_fake_verbose_print_move_
  void fake_verbose_print_move(const f_file_t output, const f_string_t source, const f_string_t destination) {
    fprintf(output.stream, "Moved '%s' to '%s'.%c", source, destination, f_string_eol[0]);
  }
#endif // _di_fake_verbose_print_move_

#ifdef __cplusplus
} // extern "C"
#endif
