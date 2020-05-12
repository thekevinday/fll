#include <level_3/fake.h>
#include "private-fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_path_generate_
  f_return_status fake_path_generate(fake_data *data) {
    f_status status = f_none;
    f_string function = "fl_string_dynamic_append";
    uint8_t i = 0;

    {
      const f_string parameter_strings[] = {
        fake_path_build_documents,
        fake_path_build_includes,
        fake_path_build_libraries,
        fake_path_build_objects,
        fake_path_build_process,
        fake_path_build_programs,
        fake_path_build_settings,
      };

      const f_string_length parameter_strings_lengths[] = {
        fake_path_build_documents_length,
        fake_path_build_includes_length,
        fake_path_build_libraries_length,
        fake_path_build_objects_length,
        fake_path_build_process_length,
        fake_path_build_programs_length,
        fake_path_build_settings_length,
      };

      f_string_dynamic *parameter_values[] = {
        &data->path_build_documents,
        &data->path_build_includes,
        &data->path_build_libraries,
        &data->path_build_objects,
        &data->path_build_process,
        &data->path_build_programs,
        &data->path_build_settings,
      };

      for (i = 0; i < 7; i++) {
        status = fl_string_dynamic_append_nulless(data->path_build, parameter_values[i]);
        if (f_status_is_error(status)) break;

        status = fl_string_append(parameter_strings[i], parameter_strings_lengths[i], parameter_values[i]);
        if (f_status_is_error(status)) break;

        status = fl_string_append_assure("/", 1, parameter_values[i]);
        if (f_status_is_error(status)) {
          function = "fl_string_append_assure";
          break;
        }

        status = fl_string_dynamic_terminate(parameter_values[i]);
        if (f_status_is_error(status)) {
          function = "fl_string_dynamic_terminate";
          break;
        }
      } // for
    }

    if (!f_status_is_error(status)) {
      const f_string parameter_strings[] = {
        fake_path_build_libraries_script,
        fake_path_build_libraries_shared,
        fake_path_build_libraries_static,
      };

      const f_string_length parameter_strings_lengths[] = {
        fake_path_build_libraries_script_length,
        fake_path_build_libraries_shared_length,
        fake_path_build_libraries_static_length,
      };

      f_string_dynamic *parameter_values[] = {
        &data->path_build_libraries_script,
        &data->path_build_libraries_shared,
        &data->path_build_libraries_static,
      };

      for (i = 0; i < 3; i++) {
        status = fl_string_dynamic_append_nulless(data->path_build_libraries, parameter_values[i]);
        if (f_status_is_error(status)) break;

        status = fl_string_append(parameter_strings[i], parameter_strings_lengths[i], parameter_values[i]);
        if (f_status_is_error(status)) break;

        status = fl_string_append_assure("/", 1, parameter_values[i]);
        if (f_status_is_error(status)) {
          function = "fl_string_append_assure";
          break;
        }

        status = fl_string_dynamic_terminate(parameter_values[i]);
        if (f_status_is_error(status)) {
          function = "fl_string_dynamic_terminate";
          break;
        }
      } // for
    }

    {
      const f_string parameter_strings[] = {
        fake_path_build_programs_script,
        fake_path_build_programs_shared,
        fake_path_build_programs_static,
      };

      const f_string_length parameter_strings_lengths[] = {
        fake_path_build_programs_script_length,
        fake_path_build_programs_shared_length,
        fake_path_build_programs_static_length,
      };

      f_string_dynamic *parameter_values[] = {
        &data->path_build_programs_script,
        &data->path_build_programs_shared,
        &data->path_build_programs_static,
      };

      for (i = 0; i < 3; i++) {
        status = fl_string_dynamic_append_nulless(data->path_build_programs, parameter_values[i]);
        if (f_status_is_error(status)) break;

        status = fl_string_append(parameter_strings[i], parameter_strings_lengths[i], parameter_values[i]);
        if (f_status_is_error(status)) break;

        status = fl_string_append_assure("/", 1, parameter_values[i]);
        if (f_status_is_error(status)) {
          function = "fl_string_append_assure";
          break;
        }

        status = fl_string_dynamic_terminate(parameter_values[i]);
        if (f_status_is_error(status)) {
          function = "fl_string_dynamic_terminate";
          break;
        }
      } // for
    }

    if (f_status_is_error(status)) {
      fake_print_error(data->context, data->verbosity, f_status_set_fine(status), function, f_true);
      return status;
    }

    return f_none;
  }
#endif // _di_fake_path_generate_

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
  f_return_status fake_print_error_file(const fl_color_context context, const uint8_t verbosity, const f_status status, const f_string function, const f_string name, const bool is_file, const bool fallback) {
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
        fl_color_print(f_standard_error, context.error, context.reset, "CRITICAL ERROR: Unable to allocate memory, while trying to access %s '", file_or_directory);
        fl_color_print(f_standard_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
      }

      return f_none;
    }

    if (status == f_number_overflow) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_standard_error, "%c", f_string_eol);
        fl_color_print(f_standard_error, context.error, context.reset, "ERROR: Overflow while trying to access %s '", file_or_directory);
        fl_color_print(f_standard_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
      }

      return f_none;
    }

    if (status == f_invalid_directory) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_standard_error, "%c", f_string_eol);
        fl_color_print(f_standard_error, context.error, context.reset, "ERROR: Invalid directory while trying to access %s '", file_or_directory);
        fl_color_print(f_standard_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
      }

      return f_none;
    }

    if (status == f_access_denied) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_standard_error, "%c", f_string_eol);
        fl_color_print(f_standard_error, context.error, context.reset, "ERROR: Access denied while trying to access %s '", file_or_directory);
        fl_color_print(f_standard_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
      }

      return f_none;
    }

    if (status == f_loop) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_standard_error, "%c", f_string_eol);
        fl_color_print(f_standard_error, context.error, context.reset, "ERROR: Loop while trying to access %s '", file_or_directory);
        fl_color_print(f_standard_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
      }

      return f_none;
    }

    if (is_file) {
    }
    else {
      if (status == f_directory_not_found) {
        if (verbosity != fake_verbosity_quiet) {
          fprintf(f_standard_error, "%c", f_string_eol);
          fl_color_print(f_standard_error, context.error, context.reset, "ERROR: failed to find %s '", file_or_directory);
          fl_color_print(f_standard_error, context.notable, context.reset, "%s", name);
          fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
        }

        return f_none;
      }

      if (status == f_no_data) {
        if (verbosity != fake_verbosity_quiet) {
          fprintf(f_standard_error, "%c", f_string_eol);
          fl_color_print(f_standard_error, context.error, context.reset, "ERROR: could not find %s '", file_or_directory);
          fl_color_print(f_standard_error, context.notable, context.reset, "%s", name);
          fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
        }

        return f_none;
      }

      if (status == f_failure) {
        if (verbosity != fake_verbosity_quiet) {
          fprintf(f_standard_error, "%c", f_string_eol);
          fl_color_print(f_standard_error, context.error, context.reset, "ERROR: failed to read the %s '", file_or_directory);
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
      fl_color_print(f_standard_error, context.error, context.reset, ") occurred for %s '", file_or_directory);
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
      const uint8_t parameter_ids[] = {
        fake_parameter_operation_build,
        fake_parameter_operation_clean,
        fake_parameter_operation_make,
        fake_parameter_operation_skeleton,
      };

      const f_string parameter_names[] = {
        fake_other_operation_build,
        fake_other_operation_clean,
        fake_other_operation_make,
        fake_other_operation_skeleton,
      };

      for (uint8_t i = 0; i < 4; i++) {
        if (data->parameters[parameter_ids[i]].total > 1) {
          if (data->verbosity != fake_verbosity_quiet) {
            fprintf(f_standard_error, "%c", f_string_eol);
            fl_color_print(f_standard_error, data->context.error, data->context.reset, "ERROR: the operation '");
            fl_color_print(f_standard_error, data->context.notable, data->context.reset, "%s", parameter_names[i]);
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "' specified too many times.");
          }

          return f_status_set_error(f_invalid_parameter);
        }
      } // for
    }

    {
      const uint8_t parameter_ids[] = {
        fake_parameter_process,
        fake_parameter_settings,
      };

      const f_string parameter_names[] = {
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

      f_string_dynamic *parameter_values[] = {
        &data->process,
        &data->settings,
      };

      for (uint8_t i = 0; i < 2; i++) {
        if (data->parameters[parameter_ids[i]].result == f_console_result_found) {
          fake_print_error_parameter_missing_value(data->context, data->verbosity, parameter_names[i]);
          return f_status_set_error(f_invalid_parameter);
        }
        else if (data->parameters[parameter_ids[i]].result == f_console_result_additional) {
          if (data->parameters[parameter_ids[i]].total > 1) {
            fake_print_error_parameter_too_many(data->context, data->verbosity, parameter_names[i]);
            return f_status_set_error(f_invalid_parameter);
          }

          f_string_length location = data->parameters[parameter_ids[i]].additional.array[0];
          f_string_length length = strnlen(arguments.argv[location], f_console_max_size);

          if (length > 0) {
            status = fl_string_append(arguments.argv[location], length, parameter_values[i]);

            if (f_status_is_error(status)) {
              if (status == f_status_set_error(f_string_too_large)) {
                if (data->verbosity != fake_verbosity_quiet) {
                  fprintf(f_standard_error, "%c", f_string_eol);
                  fl_color_print(f_standard_error, data->context.error, data->context.reset, "ERROR: the parameter '");
                  fl_color_print(f_standard_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, parameter_names[i]);
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
              fl_color_print(f_standard_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, parameter_names[i]);
              fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "' must not be empty and must not contain only whitespace.");
            }
          }
        }
        else if (parameter_default_lengths[i] > 0) {
          f_macro_string_dynamic_resize(status, (*parameter_values[i]), parameter_default_lengths[i]);

          if (f_status_is_error(status)) {
            fake_print_error(data->context, data->verbosity, f_status_set_fine(status), "f_macro_string_dynamic_resize", f_true);
            return status;
          }

          memcpy(parameter_values[i]->string, parameter_defaults[i], parameter_default_lengths[i]);
          parameter_values[i]->used = parameter_default_lengths[i];
        }
      } // for
    }

    if (data->parameters[fake_parameter_defines].result == f_console_result_found) {
      fake_print_error_parameter_missing_value(data->context, data->verbosity, fake_long_defines);
      return f_status_set_error(f_invalid_parameter);
    }

    {
      const uint8_t parameter_ids[] = {
        fake_parameter_path_build,
        fake_parameter_path_source_build,
        fake_parameter_path_source_codes,
        fake_parameter_path_source_common,
        fake_parameter_path_source_data,
        fake_parameter_path_source_documents,
        fake_parameter_path_source_licenses,
        fake_parameter_path_source_settings,
        fake_parameter_path_work,
      };

      const f_string parameter_names[] = {
        fake_long_path_build,
        fake_long_path_source_build,
        fake_long_path_source_codes,
        fake_long_path_source_common,
        fake_long_path_source_data,
        fake_long_path_source_documents,
        fake_long_path_source_licenses,
        fake_long_path_source_settings,
        fake_long_path_work,
      };

      const f_string parameter_defaults[] = {
        fake_default_path_build,
        fake_default_path_source_build,
        fake_default_path_source_codes,
        fake_default_path_source_common,
        fake_default_path_source_data,
        fake_default_path_source_documents,
        fake_default_path_source_licenses,
        fake_default_path_source_settings,
        fake_default_path_work,
      };

      const f_string_length parameter_default_lengths[] = {
        fake_default_path_build_length,
        fake_default_path_source_build_length,
        fake_default_path_source_codes_length,
        fake_default_path_source_common_length,
        fake_default_path_source_data_length,
        fake_default_path_source_documents_length,
        fake_default_path_source_licenses_length,
        fake_default_path_source_settings_length,
        fake_default_path_work_length,
      };

      f_string_dynamic *parameter_values[] = {
        &data->path_build,
        &data->path_source_build,
        &data->path_source_codes,
        &data->path_source_common,
        &data->path_source_data,
        &data->path_source_documents,
        &data->path_source_licenses,
        &data->path_source_settings,
        &data->path_work,
      };

      for (uint8_t i = 0; i < 9; i++) {
        if (data->parameters[parameter_ids[i]].result == f_console_result_found) {
          fake_print_error_parameter_missing_value(data->context, data->verbosity, parameter_names[i]);
          return f_status_set_error(f_invalid_parameter);
        }
        else if (data->parameters[parameter_ids[i]].result == f_console_result_additional) {
          if (data->parameters[parameter_ids[i]].additional.used > 1) {
            fake_print_error_parameter_too_many(data->context, data->verbosity, parameter_names[i]);
            return f_status_set_error(f_invalid_parameter);
          }

          status = fl_console_parameter_to_string_dynamic_directory(arguments.argv[data->parameters[parameter_ids[i]].additional.array[0]], parameter_values[i]);

          if (f_status_is_error(status)) {
            if (fake_print_error(data->context, data->verbosity, f_status_set_fine(status), "fl_console_parameter_to_string_dynamic_directory", f_false) == f_unknown && data->verbosity != fake_verbosity_quiet) {
              fprintf(f_standard_error, "%c", f_string_eol);
              fl_color_print(f_standard_error, data->context.error, data->context.reset, "ERROR: failed to process parameter '");
              fl_color_print(f_standard_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, parameter_names[i]);
              fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "'.");
            }

            return status;
          }
        }
        else if (parameter_default_lengths[i] > 0) {
          f_macro_string_dynamic_new(status, (*parameter_values[i]), parameter_default_lengths[i]);

          if (f_status_is_error(status)) {
            if (fake_print_error(data->context, data->verbosity, f_status_set_fine(status), "f_macro_string_dynamic_new", f_false) == f_unknown && data->verbosity != fake_verbosity_quiet) {
              fprintf(f_standard_error, "%c", f_string_eol);
              fl_color_print(f_standard_error, data->context.error, data->context.reset, "ERROR: failed to load default for the parameter '");
              fl_color_print(f_standard_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, parameter_names[i]);
              fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "'.");
            }

            return status;
          }

          memcpy(parameter_values[i]->string, parameter_defaults[i], parameter_default_lengths[i]);
          parameter_values[i]->used = parameter_default_lengths[i];
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
    const uint8_t parameter_ids[] = {
      fake_parameter_path_build,
      fake_parameter_path_source_build,
      fake_parameter_path_source_codes,
      fake_parameter_path_source_common,
      fake_parameter_path_source_data,
      fake_parameter_path_source_documents,
      fake_parameter_path_source_licenses,
      fake_parameter_path_source_settings,
      fake_parameter_path_work,
    };

    const f_string parameter_names[] = {
      fake_long_path_build,
      fake_long_path_source_build,
      fake_long_path_source_codes,
      fake_long_path_source_common,
      fake_long_path_source_data,
      fake_long_path_source_documents,
      fake_long_path_source_licenses,
      fake_long_path_source_settings,
      fake_long_path_work,
    };

    const f_string parameter_defaults[] = {
      fake_default_path_build,
      fake_default_path_source_build,
      fake_default_path_source_codes,
      fake_default_path_source_common,
      fake_default_path_source_data,
      fake_default_path_source_documents,
      fake_default_path_source_licenses,
      fake_default_path_source_settings,
      fake_default_path_work,
    };

    const f_string_length parameter_default_lengths[] = {
      fake_default_path_build_length,
      fake_default_path_source_build_length,
      fake_default_path_source_codes_length,
      fake_default_path_source_common_length,
      fake_default_path_source_data_length,
      fake_default_path_source_documents_length,
      fake_default_path_source_licenses_length,
      fake_default_path_source_settings_length,
      fake_default_path_work_length,
    };

    const bool parameters_required[] = {
      f_true,
      f_true,
      f_true,
      f_false,
      f_true,
      f_false,
      f_false,
      f_false,
      f_false,
    };

    const f_string_dynamic *parameter_values[] = {
      &data.path_build,
      &data.path_source_build,
      &data.path_source_codes,
      &data.path_source_common,
      &data.path_source_data,
      &data.path_source_documents,
      &data.path_source_licenses,
      &data.path_source_settings,
      &data.path_work,
    };

    struct stat directory_stat;
    f_status status = f_none;

    for (uint8_t i = 0; i < 9; i++) {
      if (parameter_values[i]->used > 0) {
        memset(&directory_stat, 0, sizeof(struct stat));

        status = f_file_stat(parameter_values[i]->string, &directory_stat);

        if (status == f_status_set_error(f_file_not_found)) status = f_status_set_error(f_directory_not_found);

        if (f_status_is_error(status)) {
          if (f_status_set_fine(status) != f_directory_not_found || parameters_required[i]) {
            fake_print_error_file(data.context, data.verbosity, f_status_set_fine(status), "f_file_stat", parameter_values[i]->string, f_false, f_true);
            return status;
          }
        }
      }
      else if (parameters_required[i]) {
        fprintf(f_standard_error, "%c", f_string_eol);
        fl_color_print(f_standard_error, data.context.error, data.context.reset, "ERROR: No valid path for the (required) directory parameter '");
        fl_color_print(f_standard_error, data.context.notable, data.context.reset, "%s%s", f_console_symbol_long_enable, parameter_names[i]);
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
