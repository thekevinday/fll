#include <level_3/fake.h>
#include "private-fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_path_generate_
  f_return_status fake_path_generate(fake_data *data) {
    f_status status = f_none;
    uint8_t i = 0;

    {
      const f_string_dynamic *parameters_source[] = {
        &data->path_build,
        &data->path_data,
        &data->path_sources,
      };

      const uint8_t parameters_length[] = {
        7,
        1,
        3,
      };

      f_string_dynamic *parameters_value_0[] = {
        &data->path_build_documents,
        &data->path_build_includes,
        &data->path_build_libraries,
        &data->path_build_objects,
        &data->path_build_process,
        &data->path_build_programs,
        &data->path_build_settings,
      };

      f_string_dynamic *parameters_value_1[] = {
        &data->path_data_build,
      };

      f_string_dynamic *parameters_value_2[] = {
        &data->path_sources_bash,
        &data->path_sources_c,
        &data->path_sources_cpp,
      };

      f_string_dynamic **parameters_value[] = {
        parameters_value_0,
        parameters_value_1,
        parameters_value_2,
      };

      for (i = 0; i < 3; i++) {
        status = fake_path_generate_string_dynamic(data, *parameters_source[i], parameters_value[i], parameters_length[i]);

        if (f_status_is_error(status)) {
          fake_print_error(data->context, data->verbosity, f_status_set_fine(status), "fake_path_generate_string_dynamic", f_true);
          return status;
        }
      } // for
    }

    {
      const f_string parameters_source[] = {
        fake_path_part_documents,
        fake_path_part_includes,
        fake_path_part_libraries,
        fake_path_part_objects,
        fake_path_part_process,
        fake_path_part_programs,
        fake_path_part_settings,
        fake_path_part_build,
        fake_path_part_documents,
        fake_path_part_licenses,
        fake_path_part_bash,
        fake_path_part_c,
        fake_path_part_cpp,
      };

      const f_string_length parameters_length[] = {
        fake_path_part_documents_length,
        fake_path_part_includes_length,
        fake_path_part_libraries_length,
        fake_path_part_objects_length,
        fake_path_part_process_length,
        fake_path_part_programs_length,
        fake_path_part_settings_length,
        fake_path_part_build_length,
        fake_path_part_documents_length,
        fake_path_part_licenses_length,
        fake_path_part_bash_length,
        fake_path_part_c_length,
        fake_path_part_cpp_length,
      };

      f_string_dynamic *parameters_value[] = {
        &data->path_build_documents,
        &data->path_build_includes,
        &data->path_build_libraries,
        &data->path_build_objects,
        &data->path_build_process,
        &data->path_build_programs,
        &data->path_build_settings,
        &data->path_data_build,
        &data->path_documents,
        &data->path_licenses,
        &data->path_sources_bash,
        &data->path_sources_c,
        &data->path_sources_cpp,
      };

      for (i = 0; i < 13; i++) {
        status = fl_string_append_nulless(parameters_source[i], parameters_length[i], parameters_value[i]);

        if (f_status_is_error(status)) {
          fake_print_error(data->context, data->verbosity, f_status_set_fine(status), "fl_string_append_nulless", f_true);
          return status;
        }
      } // for
    }

    {
      const f_string_dynamic *parameters_source[] = {
        &data->path_build_libraries,
        &data->path_build_programs,
        &data->path_data_build,
        &data->path_documents,
      };

      const uint8_t parameters_length[] = {
        3,
        3,
        2,
        1,
      };

      f_string_dynamic *parameters_value_0[] = {
        &data->path_build_libraries_script,
        &data->path_build_libraries_shared,
        &data->path_build_libraries_static,
      };

      f_string_dynamic *parameters_value_1[] = {
        &data->path_build_programs_script,
        &data->path_build_programs_shared,
        &data->path_build_programs_static,
      };

      f_string_dynamic *parameters_value_2[] = {
        &data->file_data_build_dependencies,
        &data->file_data_build_settings,
      };

      f_string_dynamic *parameters_value_3[] = {
        &data->file_documents_readme,
      };

      f_string_dynamic **parameters_value[] = {
        parameters_value_0,
        parameters_value_1,
        parameters_value_2,
        parameters_value_3,
      };

      for (i = 0; i < 4; i++) {
        status = fake_path_generate_string_dynamic(data, *parameters_source[i], parameters_value[i], parameters_length[i]);

        if (f_status_is_error(status)) {
          fake_print_error(data->context, data->verbosity, f_status_set_fine(status), "fake_path_generate_string_dynamic", f_true);
          return status;
        }
      } // for
    }

    {
      const f_string parameters_source[] = {
        fake_path_part_script,
        fake_path_part_shared,
        fake_path_part_static,
        fake_path_part_script,
        fake_path_part_shared,
        fake_path_part_static,
        fake_file_dependencies,
        fake_file_settings,
        fake_file_readme,
      };

      const f_string_length parameters_length[] = {
        fake_path_part_script_length,
        fake_path_part_shared_length,
        fake_path_part_static_length,
        fake_path_part_script_length,
        fake_path_part_shared_length,
        fake_path_part_static_length,
        fake_file_dependencies_length,
        fake_file_settings_length,
        fake_file_readme_length,
      };

      f_string_dynamic *parameters_value[] = {
        &data->path_build_libraries_script,
        &data->path_build_libraries_shared,
        &data->path_build_libraries_static,
        &data->path_build_programs_script,
        &data->path_build_programs_shared,
        &data->path_build_programs_static,
        &data->file_data_build_dependencies,
        &data->file_data_build_settings,
        &data->file_documents_readme,
      };

      for (i = 0; i < 9; i++) {
        status = fl_string_append_nulless(parameters_source[i], parameters_length[i], parameters_value[i]);

        if (f_status_is_error(status)) {
          fake_print_error(data->context, data->verbosity, f_status_set_fine(status), "fl_string_append_nulless", f_true);
          return status;
        }
      } // for
    }

    if (data->path_work.used > 0) {
      {
        f_string_dynamic *parameters_value[] = {
          &data->path_work_includes,
          &data->path_work_libraries,
          &data->path_work_programs,
        };

        for (i = 0; i < 3; i++) {
          status = fl_string_dynamic_append_nulless(data->path_work, parameters_value[i]);

          if (f_status_is_error(status)) {
            fake_print_error(data->context, data->verbosity, f_status_set_fine(status), "fl_string_dynamic_append_nulless", f_true);
            return status;
          }
        } // for
      }

      {
        const f_string parameters_source[] = {
          fake_path_part_includes,
          fake_path_part_libraries,
          fake_path_part_programs,
        };

        const f_string_length parameters_length[] = {
          fake_path_part_includes_length,
          fake_path_part_libraries_length,
          fake_path_part_programs_length,
        };

        f_string_dynamic *parameters_value[] = {
          &data->path_work_includes,
          &data->path_work_libraries,
          &data->path_work_programs,
        };

        for (i = 0; i < 3; i++) {
          status = fl_string_append_nulless(parameters_source[i], parameters_length[i], parameters_value[i]);

          if (f_status_is_error(status)) {
            fake_print_error(data->context, data->verbosity, f_status_set_fine(status), "fl_string_append_nulless", f_true);
            return status;
          }
        } // for
      }

      {
        const f_string_dynamic *parameters_source[] = {
          &data->path_work_libraries,
          &data->path_work_programs,
        };

        const uint8_t parameters_length[] = {
          3,
          3,
        };

        f_string_dynamic *parameters_value_0[] = {
          &data->path_work_libraries_script,
          &data->path_work_libraries_shared,
          &data->path_work_libraries_static,
        };

        f_string_dynamic *parameters_value_1[] = {
          &data->path_work_programs_script,
          &data->path_work_programs_shared,
          &data->path_work_programs_static,
        };

        f_string_dynamic **parameters_value[] = {
          parameters_value_0,
          parameters_value_1,
        };

        for (i = 0; i < 2; i++) {
          status = fake_path_generate_string_dynamic(data, *parameters_source[i], parameters_value[i], parameters_length[i]);

          if (f_status_is_error(status)) {
            fake_print_error(data->context, data->verbosity, f_status_set_fine(status), "fake_path_generate_string_dynamic", f_true);
            return status;
          }
        } // for
      }

      {
        const f_string parameters_source[] = {
          fake_path_part_script,
          fake_path_part_shared,
          fake_path_part_static,
          fake_path_part_script,
          fake_path_part_shared,
          fake_path_part_static,
        };

        const f_string_length parameters_length[] = {
          fake_path_part_script_length,
          fake_path_part_shared_length,
          fake_path_part_static_length,
          fake_path_part_script_length,
          fake_path_part_shared_length,
          fake_path_part_static_length,
        };

        f_string_dynamic *parameters_value[] = {
          &data->path_work_libraries_script,
          &data->path_work_libraries_shared,
          &data->path_work_libraries_static,
          &data->path_work_programs_script,
          &data->path_work_programs_shared,
          &data->path_work_programs_static,
        };

        for (i = 0; i < 6; i++) {
          status = fl_string_append_nulless(parameters_source[i], parameters_length[i], parameters_value[i]);

          if (f_status_is_error(status)) {
            fake_print_error(data->context, data->verbosity, f_status_set_fine(status), "fl_string_append_nulless", f_true);
            return status;
          }
        } // for
      }
    }

    {
      f_string_dynamic *parameters_value[] = {
        &data->path_build_documents,
        &data->path_build_includes,
        &data->path_build_libraries,
        &data->path_build_libraries_script,
        &data->path_build_libraries_shared,
        &data->path_build_libraries_static,
        &data->path_build_objects,
        &data->path_build_process,
        &data->path_build_programs,
        &data->path_build_programs_script,
        &data->path_build_programs_shared,
        &data->path_build_programs_static,
        &data->path_build_settings,
        &data->path_data_build,
        &data->path_licenses,
        &data->path_sources_bash,
        &data->path_sources_c,
        &data->path_sources_cpp,
        &data->path_work_includes,
        &data->path_work_libraries,
        &data->path_work_libraries_script,
        &data->path_work_libraries_shared,
        &data->path_work_libraries_static,
        &data->path_work_programs,
        &data->path_work_programs_script,
        &data->path_work_programs_shared,
        &data->path_work_programs_static,
        &data->file_data_build_dependencies,
        &data->file_data_build_settings,
        &data->file_documents_readme,
      };

      for (i = 0; i < 30; i++) {
        if (parameters_value[i]->used == 0) continue;

        status = fl_string_dynamic_terminate(parameters_value[i]);

        if (f_status_is_error(status)) {
          fake_print_error(data->context, data->verbosity, f_status_set_fine(status), "fl_string_dynamic_terminate", f_true);
          return status;
        }
      } // for
    }

    return f_none;
  }
#endif // _di_fake_path_generate_

#ifndef _di_fake_path_generate_string_dynamic_
  f_return_status fake_path_generate_string_dynamic(fake_data *data, const f_string_dynamic source, f_string_dynamic *value[], const uint8_t length) {
    f_status status = f_none;

    for (uint8_t i = 0; i < length; i++) {
      status = fl_string_dynamic_append_nulless(source, value[i]);
      if (f_status_is_error(status)) return status;
    } // for

    return f_none;
  }
#endif // _di_fake_path_generate_string_dynamic_

#ifndef _di_fake_print_error_
  f_return_status fake_print_error(const fl_color_context context, const uint8_t verbosity, const f_status status, const f_string function, const bool fallback) {

    if (status == f_invalid_parameter) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_standard_error, "%c", f_string_eol);
        fl_color_print(f_standard_error, context.error, context.reset, "INTERNAL ERROR: Invalid parameter in function ");
        fl_color_print(f_standard_error, context.notable, context.reset, "%s", function);
        fl_color_print_line(f_standard_error, context.error, context.reset, "().");
      }

      return f_none;
    }

    if (status == f_error_allocation || status == f_error_reallocation) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_standard_error, "%c", f_string_eol);
        fl_color_print(f_standard_error, context.error, context.reset, "ERROR: Unable to allocate memory in function ");
        fl_color_print(f_standard_error, context.notable, context.reset, "%s", function);
        fl_color_print_line(f_standard_error, context.error, context.reset, "().");
      }

      return f_none;
    }

    if (fallback && verbosity != fake_verbosity_quiet) {
      fprintf(f_standard_error, "%c", f_string_eol);
      fl_color_print(f_standard_error, context.error, context.reset, "UNKNOWN ERROR: (");
      fl_color_print(f_standard_error, context.notable, context.reset, "%d", status);
      fl_color_print(f_standard_error, context.error, context.reset, ") in function ");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", function);
      fl_color_print_line(f_standard_error, context.error, context.reset, "().");
    }

    return f_unknown;
  }
#endif // _di_fake_print_error_

#ifndef _di_fake_print_error_file_
  f_return_status fake_print_error_file(const fl_color_context context, const uint8_t verbosity, const f_status status, const f_string function, const f_string name, const f_string operation, const bool is_file, const bool fallback) {
    f_string file_or_directory = 0;

    if (is_file) file_or_directory = "file";
    else file_or_directory = "directory";

    if (status == f_file_not_found) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_standard_error, "%c", f_string_eol);
        fl_color_print(f_standard_error, context.error, context.reset, "ERROR: failed to find %s '", file_or_directory);
        fl_color_print(f_standard_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
      }

      return f_none;
    }

    if (status == f_invalid_parameter) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_standard_error, "%c", f_string_eol);
        fl_color_print(f_standard_error, context.error, context.reset, "INTERNAL ERROR: Invalid parameter when calling ", function, name);
        fl_color_print(f_standard_error, context.notable, context.reset, "%s", function);
        fl_color_print(f_standard_error, context.error, context.reset, "() for the %s '", file_or_directory);
        fl_color_print(f_standard_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
      }

      return f_none;
    }

    if (status == f_invalid_name) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_standard_error, "%c", f_string_eol);
        fl_color_print(f_standard_error, context.error, context.reset, "ERROR: Invalid %s name '", file_or_directory);
        fl_color_print(f_standard_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
      }

      return f_none;
    }

    if (status == f_out_of_memory) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_standard_error, "%c", f_string_eol);
        fl_color_print(f_standard_error, context.error, context.reset, "CRITICAL ERROR: Unable to allocate memory, while trying to %s %s '", operation, file_or_directory);
        fl_color_print(f_standard_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
      }

      return f_none;
    }

    if (status == f_number_overflow) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_standard_error, "%c", f_string_eol);
        fl_color_print(f_standard_error, context.error, context.reset, "ERROR: Overflow while trying to %s %s '", operation, file_or_directory);
        fl_color_print(f_standard_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
      }

      return f_none;
    }

    if (status == f_invalid_directory) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_standard_error, "%c", f_string_eol);
        fl_color_print(f_standard_error, context.error, context.reset, "ERROR: Invalid directory while trying to %s %s '", operation, file_or_directory);
        fl_color_print(f_standard_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
      }

      return f_none;
    }

    if (status == f_access_denied) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_standard_error, "%c", f_string_eol);
        fl_color_print(f_standard_error, context.error, context.reset, "ERROR: Access denied while trying to %s %s '", operation, file_or_directory);
        fl_color_print(f_standard_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
      }

      return f_none;
    }

    if (status == f_loop) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_standard_error, "%c", f_string_eol);
        fl_color_print(f_standard_error, context.error, context.reset, "ERROR: Loop while trying to %s %s '", operation, file_or_directory);
        fl_color_print(f_standard_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
      }

      return f_none;
    }

    if (is_file) {
      if (status == f_directory_not_found) {
        if (verbosity != fake_verbosity_quiet) {
          fprintf(f_standard_error, "%c", f_string_eol);
          fl_color_print(f_standard_error, context.error, context.reset, "ERROR: failed to %s %s '", operation, file_or_directory);
          fl_color_print(f_standard_error, context.notable, context.reset, "%s", name);
          fl_color_print_line(f_standard_error, context.error, context.reset, "' due to an invalid directory in the path.");
        }

        return f_none;
      }
    }
    else {
      if (status == f_directory_not_found) {
        if (verbosity != fake_verbosity_quiet) {
          fprintf(f_standard_error, "%c", f_string_eol);
          fl_color_print(f_standard_error, context.error, context.reset, "ERROR: failed to %s %s '", operation, file_or_directory);
          fl_color_print(f_standard_error, context.notable, context.reset, "%s", name);
          fl_color_print_line(f_standard_error, context.error, context.reset, "' due to an invalid directory in the path.");
        }

        return f_none;
      }

      if (status == f_failure) {
        if (verbosity != fake_verbosity_quiet) {
          fprintf(f_standard_error, "%c", f_string_eol);
          fl_color_print(f_standard_error, context.error, context.reset, "ERROR: failed to %s %s '", operation, file_or_directory);
          fl_color_print(f_standard_error, context.notable, context.reset, "%s", name);
          fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
        }

        return f_none;
      }
    }

    if (fake_print_error(context, verbosity, status, function, f_false) == f_unknown && fallback && verbosity != fake_verbosity_quiet) {
      fprintf(f_standard_error, "%c", f_string_eol);
      fl_color_print(f_standard_error, context.error, context.reset, "UNKNOWN ERROR: (");
      fl_color_print(f_standard_error, context.notable, context.reset, "%d", status);
      fl_color_print(f_standard_error, context.error, context.reset, ") occurred while trying to %s %s '", operation, file_or_directory);
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
    }

    return f_unknown;
  }
#endif // _di_fake_print_error_file_

#ifndef _di_fake_print_error_parameter_missing_value_
  void fake_print_error_parameter_missing_value(const fl_color_context context, const uint8_t verbosity, const f_string parameter) {
    if (verbosity != fake_verbosity_quiet) {
      fprintf(f_standard_error, "%c", f_string_eol);
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: The parameter '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, parameter);
      fl_color_print_line(f_standard_error, context.error, context.reset, "' was specified, but no value was given.");
    }
  }
#endif // _di_fake_print_error_parameter_missing_value_

#ifndef _di_fake_print_error_parameter_too_many_
  void fake_print_error_parameter_too_many(const fl_color_context context, const uint8_t verbosity, const f_string parameter) {
    if (verbosity != fake_verbosity_quiet) {
      fprintf(f_standard_error, "%c", f_string_eol);
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: the parameter '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, parameter);
      fl_color_print_line(f_standard_error, context.error, context.reset, "' specified too many times.");
    }
  }
#endif // _di_fake_print_error_parameter_too_many_

#ifndef _di_fake_process_console_parameters_
  f_return_status fake_process_console_parameters(const f_console_arguments arguments, fake_data *data) {
    f_status status = f_none;

    // @todo move as many of the inline error printing code into more general functions where possible to provide more accurate error reporting.

    {
      const uint8_t parameters_id[] = {
        fake_parameter_operation_build,
        fake_parameter_operation_clean,
        fake_parameter_operation_make,
        fake_parameter_operation_skeleton,
      };

      const f_string parameters_name[] = {
        fake_other_operation_build,
        fake_other_operation_clean,
        fake_other_operation_make,
        fake_other_operation_skeleton,
      };

      for (uint8_t i = 0; i < 4; i++) {
        if (data->parameters[parameters_id[i]].total > 1) {
          if (data->verbosity != fake_verbosity_quiet) {
            fprintf(f_standard_error, "%c", f_string_eol);
            fl_color_print(f_standard_error, data->context.error, data->context.reset, "ERROR: the operation '");
            fl_color_print(f_standard_error, data->context.notable, data->context.reset, "%s", parameters_name[i]);
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "' specified too many times.");
          }

          return f_status_set_error(f_invalid_parameter);
        }
      } // for
    }

    {
      const uint8_t parameters_id[] = {
        fake_parameter_process,
        fake_parameter_settings,
      };

      const f_string parameters_name[] = {
        fake_long_process,
        fake_long_settings,
      };

      const f_string parameter_defaults[] = {
        fake_default_process,
        fake_default_settings,
      };

      const f_string_length parameter_default_lengths[] = {
        fake_default_process_length,
        fake_default_settings_length,
      };

      f_string_dynamic *parameters_value[] = {
        &data->process,
        &data->settings,
      };

      for (uint8_t i = 0; i < 2; i++) {
        if (data->parameters[parameters_id[i]].result == f_console_result_found) {
          fake_print_error_parameter_missing_value(data->context, data->verbosity, parameters_name[i]);
          return f_status_set_error(f_invalid_parameter);
        }
        else if (data->parameters[parameters_id[i]].result == f_console_result_additional) {
          if (data->parameters[parameters_id[i]].total > 1) {
            fake_print_error_parameter_too_many(data->context, data->verbosity, parameters_name[i]);
            return f_status_set_error(f_invalid_parameter);
          }

          f_string_length location = data->parameters[parameters_id[i]].additional.array[0];
          f_string_length length = strnlen(arguments.argv[location], f_console_max_size);

          if (length > 0) {
            status = fl_string_append(arguments.argv[location], length, parameters_value[i]);

            if (f_status_is_error(status)) {
              if (status == f_status_set_error(f_string_too_large)) {
                if (data->verbosity != fake_verbosity_quiet) {
                  fprintf(f_standard_error, "%c", f_string_eol);
                  fl_color_print(f_standard_error, data->context.error, data->context.reset, "ERROR: the parameter '");
                  fl_color_print(f_standard_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, parameters_name[i]);
                  fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "' is too long.");
                }
              }
              else {
                fake_print_error(data->context, data->verbosity, f_status_set_fine(status), "fl_string_append", f_true);
              }

              return status;
            }
            else {
              status = f_none;
            }
          }

          if (length == 0 || status == f_no_data) {
            if (data->verbosity != fake_verbosity_quiet) {
              fprintf(f_standard_error, "%c", f_string_eol);
              fl_color_print(f_standard_error, data->context.error, data->context.reset, "ERROR: the parameter '");
              fl_color_print(f_standard_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, parameters_name[i]);
              fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "' must not be empty and must not contain only whitespace.");
            }
          }
        }
        else if (parameter_default_lengths[i] > 0) {
          f_macro_string_dynamic_resize(status, (*parameters_value[i]), parameter_default_lengths[i]);

          if (f_status_is_error(status)) {
            fake_print_error(data->context, data->verbosity, f_status_set_fine(status), "f_macro_string_dynamic_resize", f_true);
            return status;
          }

          memcpy(parameters_value[i]->string, parameter_defaults[i], parameter_default_lengths[i]);
          parameters_value[i]->used = parameter_default_lengths[i];
        }
      } // for
    }

    if (data->parameters[fake_parameter_defines].result == f_console_result_found) {
      fake_print_error_parameter_missing_value(data->context, data->verbosity, fake_long_defines);
      return f_status_set_error(f_invalid_parameter);
    }

    {
      const uint8_t parameters_id[] = {
        fake_parameter_path_build,
        fake_parameter_path_data,
        fake_parameter_path_sources,
        fake_parameter_path_work,
      };

      const f_string parameters_name[] = {
        fake_long_path_build,
        fake_long_path_data,
        fake_long_path_sources,
        fake_long_path_work,
      };

      const f_string parameter_defaults[] = {
        fake_default_path_build,
        fake_default_path_data,
        fake_default_path_sources,
        fake_default_path_work,
      };

      const f_string_length parameter_default_lengths[] = {
        fake_default_path_build_length,
        fake_default_path_data_length,
        fake_default_path_sources_length,
        fake_default_path_work_length,
      };

      f_string_dynamic *parameters_value[] = {
        &data->path_build,
        &data->path_data,
        &data->path_sources,
        &data->path_work,
      };

      for (uint8_t i = 0; i < 4; i++) {
        if (data->parameters[parameters_id[i]].result == f_console_result_found) {
          fake_print_error_parameter_missing_value(data->context, data->verbosity, parameters_name[i]);
          return f_status_set_error(f_invalid_parameter);
        }
        else if (data->parameters[parameters_id[i]].result == f_console_result_additional) {
          if (data->parameters[parameters_id[i]].additional.used > 1) {
            fake_print_error_parameter_too_many(data->context, data->verbosity, parameters_name[i]);
            return f_status_set_error(f_invalid_parameter);
          }

          status = fl_console_parameter_to_string_dynamic_directory(arguments.argv[data->parameters[parameters_id[i]].additional.array[0]], parameters_value[i]);

          if (f_status_is_error(status)) {
            if (fake_print_error(data->context, data->verbosity, f_status_set_fine(status), "fl_console_parameter_to_string_dynamic_directory", f_false) == f_unknown && data->verbosity != fake_verbosity_quiet) {
              fprintf(f_standard_error, "%c", f_string_eol);
              fl_color_print(f_standard_error, data->context.error, data->context.reset, "ERROR: failed to process parameter '");
              fl_color_print(f_standard_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, parameters_name[i]);
              fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "'.");
            }

            return status;
          }
        }
        else if (parameter_default_lengths[i] > 0) {
          f_macro_string_dynamic_new(status, (*parameters_value[i]), parameter_default_lengths[i]);

          if (f_status_is_error(status)) {
            if (fake_print_error(data->context, data->verbosity, f_status_set_fine(status), "f_macro_string_dynamic_new", f_false) == f_unknown && data->verbosity != fake_verbosity_quiet) {
              fprintf(f_standard_error, "%c", f_string_eol);
              fl_color_print(f_standard_error, data->context.error, data->context.reset, "ERROR: failed to load default for the parameter '");
              fl_color_print(f_standard_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, parameters_name[i]);
              fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "'.");
            }

            return status;
          }

          memcpy(parameters_value[i]->string, parameter_defaults[i], parameter_default_lengths[i]);
          parameters_value[i]->used = parameter_default_lengths[i];
        }
      } // for
    }

    if (data->parameters[fake_parameter_defines].result == f_console_result_additional) {
      status = fll_program_parameter_additional_rip_mash(" ", 1, arguments.argv, data->parameters[fake_parameter_defines].additional, &data->defines);

      if (f_status_is_error(status)) {
        if (status == f_status_set_error(f_string_too_large)) {
          if (data->verbosity != fake_verbosity_quiet) {
            fprintf(f_standard_error, "%c", f_string_eol);
            fl_color_print(f_standard_error, data->context.error, data->context.reset, "ERROR: the (combined) parameter '");
            fl_color_print(f_standard_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, fake_long_defines);
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "' is too long.");
          }
        }
        else {
          fake_print_error(data->context, data->verbosity, f_status_set_fine(status), "fll_program_parameter_additional_rip_mash", f_true);
        }

        return status;
      }
    }

    if (data->parameters[fake_parameter_mode].result == f_console_result_found) {
      fake_print_error_parameter_missing_value(data->context, data->verbosity, fake_long_mode);
      return f_status_set_error(f_invalid_parameter);
    }
    else if (data->parameters[fake_parameter_mode].result == f_console_result_additional) {
      status = fll_program_parameter_additional_rip(arguments.argv, data->parameters[fake_parameter_mode].additional, &data->mode);

      if (f_status_is_error(status)) {
        if (fake_print_error(data->context, data->verbosity, f_status_set_fine(status), "fll_program_parameter_additional_rip", f_false) == f_unknown && data->verbosity != fake_verbosity_quiet) {
          fprintf(f_standard_error, "%c", f_string_eol);
          fl_color_print(f_standard_error, data->context.error, data->context.reset, "ERROR: failed to process the parameter '");
          fl_color_print(f_standard_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, fake_long_mode);
          fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "'.");
        }

        return status;
      }

      f_array_length i = 0;
      f_string_length j = 0;
      f_string_length width_max = 0;

      for (; i < data->mode.used; i++) {
        for (j = 0; j < data->mode.array[i].used; j++) {
          width_max = data->mode.array[i].used - j;

          status = f_utf_is_word_dash_plus(data->mode.array[i].string + j, width_max);

          if (f_status_is_error(status)) {
            if (fake_print_error(data->context, data->verbosity, f_status_set_fine(status), "f_utf_is_word_dash_plus", f_false) == f_unknown && data->verbosity != fake_verbosity_quiet) {
              fprintf(f_standard_error, "%c", f_string_eol);
              fl_color_print(f_standard_error, data->context.error, data->context.reset, "ERROR: failed to process the parameter '");
              fl_color_print(f_standard_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, fake_long_mode);
              fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "'.");
            }

            return status;
          }

          if (status == f_false) {
            if (data->verbosity != fake_verbosity_quiet) {
              fprintf(f_standard_error, "%c", f_string_eol);
              fl_color_print(f_standard_error, data->context.error, data->context.reset, "ERROR: the '");
              fl_color_print(f_standard_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, fake_long_mode);
              fl_color_print(f_standard_error, data->context.error, data->context.reset, "' parameters value '");
              fl_color_print(f_standard_error, data->context.notable, data->context.reset, "%s", data->mode.array[i].string);
              fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "' contains non-word, non-dash, and non-plus characters.");
            }

            return f_status_set_error(f_invalid_parameter);
          }
        } // for
      } // for
    }

    return f_none;
  }
#endif // _di_fake_process_console_parameters_

#ifndef _di_fake_validate_directories_
  f_return_status fake_validate_parameter_directories(const f_console_arguments arguments, const fake_data data) {
    const f_string parameters_name[] = {
      fake_long_path_build,
      fake_long_path_data,
      fake_long_path_sources,
      fake_long_path_work,
    };

    const f_string parameter_defaults[] = {
      fake_default_path_build,
      fake_default_path_data,
      fake_default_path_sources,
      fake_default_path_work,
    };

    const f_string_length parameter_default_lengths[] = {
      fake_default_path_build_length,
      fake_default_path_data_length,
      fake_default_path_sources_length,
      fake_default_path_work_length,
    };

    const f_string_dynamic *parameters_value[] = {
      &data.path_build,
      &data.path_data,
      &data.path_sources,
      &data.path_work,
    };

    const bool parameters_required[] = {
      f_true,
      f_true,
      f_true,
      f_false,
    };

    struct stat directory_stat;
    f_status status = f_none;

    for (uint8_t i = 0; i < 4; i++) {
      if (parameters_value[i]->used > 0) {
        memset(&directory_stat, 0, sizeof(struct stat));

        status = f_file_stat(parameters_value[i]->string, &directory_stat);

        if (status == f_status_set_error(f_file_not_found)) status = f_status_set_error(f_directory_not_found);

        if (f_status_is_error(status)) {
          if (f_status_set_fine(status) != f_directory_not_found || parameters_required[i]) {
            fake_print_error_file(data.context, data.verbosity, f_status_set_fine(status), "f_file_stat", parameters_value[i]->string, "access", f_false, f_true);
            return status;
          }
        }
      }
      else if (parameters_required[i]) {
        fprintf(f_standard_error, "%c", f_string_eol);
        fl_color_print(f_standard_error, data.context.error, data.context.reset, "ERROR: No valid path for the (required) directory parameter '");
        fl_color_print(f_standard_error, data.context.notable, data.context.reset, "%s%s", f_console_symbol_long_enable, parameters_name[i]);
        fl_color_print_line(f_standard_error, data.context.error, data.context.reset, "' was found.");

        return f_status_set_error(f_directory_not_found);
      }
    } // for

    return f_none;
  }
#endif // _di_fake_validate_parameter_directories_

#ifdef __cplusplus
} // extern "C"
#endif
