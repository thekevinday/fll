#include <level_3/fake.h>
#include "private-fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_load_settings_data_
  f_return_status fake_load_settings_data(const fake_data data, fake_settings_data *settings_data) {
    f_status status = f_none;
    f_file file = f_file_initialize;
    f_string_dynamic buffer = f_string_dynamic_initialize;
    f_string_dynamic path = f_string_dynamic_initialize;

    status = fl_string_dynamic_append(data.path_source_settings, &path);

    if (!f_status_is_error(status)) {
      status = fl_string_dynamic_append(data.settings, &path);
    }

    if (f_status_is_error(status)) {
      fake_print_error(data.context, f_status_set_fine(status), "fl_string_dynamic_append", f_true);

      f_macro_string_dynamic_delete_simple(path);
      return status;
    }

    {
      f_string name_function = f_string_initialize;

      name_function = "f_file_exists";
      status = f_file_exists(path.string);

      if (status == f_true) {
        name_function = "f_file_open";
        status = f_file_open(&file, path.string);

        if (status == f_none) {
          name_function = "fl_file_read_position";
          status = fl_file_read(&file, &buffer);

          f_file_close(&file);
        }
      }
      else if (status == f_false) {
        status = f_status_set_error(f_file_not_found);
      }

      if (f_status_is_error(status)) {
        fake_print_error_file(data.context, f_status_set_fine(status), name_function, path.string, "file", f_true);

        f_macro_string_dynamic_delete_simple(buffer);
        f_macro_string_dynamic_delete_simple(path);
        return status;
      }
    }

    if (buffer.used > 0) {
      f_fss_objects objects = f_fss_objects_initialize;
      f_fss_contents contents = f_fss_contents_initialize;
      f_string_location location = f_string_location_initialize;

      location.start = 0;
      location.stop = buffer.used - 1;

      status = fll_fss_basic_read(&buffer, &location, &objects, &contents);

      if (f_status_is_error(status)) {
        f_macro_fss_objects_delete_simple(objects);
        f_macro_fss_contents_delete_simple(contents);
        f_macro_string_dynamic_delete_simple(buffer);

        if (status == f_status_set_error(f_incomplete_utf_on_stop)) {
          fl_color_print(f_standard_error, data.context.error, data.context.reset, "ENCODING ERROR: error occurred on invalid UTF-8 character at stop position (at ");
          fl_color_print(f_standard_error, data.context.notable, data.context.reset, "%d", location.start);
          fl_color_print(f_standard_error, data.context.error, data.context.reset, " of settings file '");
          fl_color_print(f_standard_error, data.context.notable, data.context.reset, "%s", path.string);
          fl_color_print_line(f_standard_error, data.context.error, data.context.reset, "').");
        }
        else if (status == f_status_set_error(f_incomplete_utf_on_stop)) {
          fl_color_print(f_standard_error, data.context.error, data.context.reset, "ENCODING ERROR: error occurred on invalid UTF-8 character at end of string (at ");
          fl_color_print(f_standard_error, data.context.notable, data.context.reset, "%d", location.start);
          fl_color_print(f_standard_error, data.context.error, data.context.reset, " of settings file '");
          fl_color_print(f_standard_error, data.context.notable, data.context.reset, "%s", path.string);
          fl_color_print_line(f_standard_error, data.context.error, data.context.reset, "').");
        }
        else {
          fake_print_error(data.context, f_status_set_fine(status), "fll_fss_basic_read", true);
        }

        f_macro_fss_objects_delete_simple(objects);
        f_macro_fss_contents_delete_simple(contents);
        f_macro_string_dynamic_delete_simple(buffer);
        f_macro_string_dynamic_delete_simple(path);

        return status;
      }

      {
        const f_string setting_names[] = {
          fake_settings_name_build_compiler,
          fake_settings_name_build_libraries,
          fake_settings_name_build_linker,
          fake_settings_name_build_shared,
          fake_settings_name_build_sources_headers,
          fake_settings_name_build_sources_library,
          fake_settings_name_build_sources_program,
          fake_settings_name_build_sources_settings,
          fake_settings_name_build_sources_shell,
          fake_settings_name_build_static,
          fake_settings_name_defines_all,
          fake_settings_name_defines_shared,
          fake_settings_name_defines_static,
          fake_settings_name_flags_all,
          fake_settings_name_flags_library,
          fake_settings_name_flags_program,
          fake_settings_name_flags_shared,
          fake_settings_name_flags_static,
          fake_settings_name_path_language,
          fake_settings_name_process_post,
          fake_settings_name_process_pre,
          fake_settings_name_project_level,
          fake_settings_name_project_name,
          fake_settings_name_version_major,
          fake_settings_name_version_micro,
          fake_settings_name_version_minor,
        };

        const f_string_length setting_lengths[] = {
          fake_settings_name_build_compiler_length,
          fake_settings_name_build_libraries_length,
          fake_settings_name_build_linker_length,
          fake_settings_name_build_shared_length,
          fake_settings_name_build_sources_headers_length,
          fake_settings_name_build_sources_library_length,
          fake_settings_name_build_sources_program_length,
          fake_settings_name_build_sources_settings_length,
          fake_settings_name_build_sources_shell_length,
          fake_settings_name_build_static_length,
          fake_settings_name_defines_all_length,
          fake_settings_name_defines_shared_length,
          fake_settings_name_defines_static_length,
          fake_settings_name_flags_all_length,
          fake_settings_name_flags_library_length,
          fake_settings_name_flags_program_length,
          fake_settings_name_flags_shared_length,
          fake_settings_name_flags_static_length,
          fake_settings_name_path_language_length,
          fake_settings_name_process_post_length,
          fake_settings_name_process_pre_length,
          fake_settings_name_project_level_length,
          fake_settings_name_project_name_length,
          fake_settings_name_version_major_length,
          fake_settings_name_version_micro_length,
          fake_settings_name_version_minor_length,
        };

        f_string_dynamic *setting_values[] = {
          &settings_data->build_compiler,
          &settings_data->build_libraries,
          &settings_data->build_linker,
          &settings_data->build_shared,
          &settings_data->build_sources_headers,
          &settings_data->build_sources_library,
          &settings_data->build_sources_program,
          &settings_data->build_sources_settings,
          &settings_data->build_sources_shell,
          &settings_data->build_static,
          &settings_data->defines_all,
          &settings_data->defines_shared,
          &settings_data->defines_static,
          &settings_data->flags_all,
          &settings_data->flags_library,
          &settings_data->flags_program,
          &settings_data->flags_shared,
          &settings_data->flags_static,
          &settings_data->path_language,
          &settings_data->process_post,
          &settings_data->process_pre,
          &settings_data->project_level,
          &settings_data->project_name,
          &settings_data->version_major,
          &settings_data->version_micro,
          &settings_data->version_minor,
        };

        status = fll_fss_snatch_mash_together(buffer, objects, contents, setting_names, setting_lengths, setting_values, fake_settings_total, " ", 1);

        if (status == f_none) {
          for (f_array_length i = 0; i < data.mode.used; i++) {
            f_string_dynamic settings_mode_name_dynamic[fake_settings_total];
            f_string settings_mode_names[fake_settings_total];
            f_string_length setting_mode_lengths[fake_settings_total];

            memset(&settings_mode_name_dynamic, 0, sizeof(f_string_dynamic) * fake_settings_total);
            memset(&settings_mode_names, 0, sizeof(f_string) * fake_settings_total);

            for (f_string_length j = 0; j < fake_settings_total; j++) {
              setting_mode_lengths[j] = setting_lengths[j] + 1 + data.mode.array[i].used;

              f_macro_string_dynamic_new(status, settings_mode_name_dynamic[j], setting_mode_lengths[j]);
              if (f_status_is_error(status)) break;

              memcpy(settings_mode_name_dynamic[j].string, setting_names[j], setting_lengths[j]);
              memcpy(settings_mode_name_dynamic[j].string + setting_lengths[j] + 1, data.mode.array[i].string, data.mode.array[i].used);
              settings_mode_name_dynamic[j].string[setting_lengths[j]] = '-';

              settings_mode_names[j] = settings_mode_name_dynamic[j].string;
            } // for

            if (status == f_none) {
              status = fll_fss_snatch_mash_together(buffer, objects, contents, settings_mode_names, setting_mode_lengths, setting_values, fake_settings_total, " ", 1);
            }

            for (f_string_length j = 0; j < fake_settings_total; j++) {
              f_macro_string_dynamic_delete_simple(settings_mode_name_dynamic[j]);
            } // for

            if (f_status_is_error(status)) break;
          } // for

          if (f_status_is_error(status)) {
            fake_print_error(data.context, f_status_set_fine(status), "f_macro_string_dynamic_new", f_true);

            f_macro_fss_objects_delete_simple(objects);
            f_macro_fss_contents_delete_simple(contents);
            f_macro_string_dynamic_delete_simple(buffer);
            f_macro_string_dynamic_delete_simple(path);
            return status;
          }
        }

        if (f_status_is_error(status)) {
          if (status == f_status_set_error(f_string_too_large)) {
            fl_color_print(f_standard_error, data.context.error, data.context.reset, "ERROR: a setting in the build settings file '");
            fl_color_print(f_standard_error, data.context.notable, data.context.reset, "%s", path);
            fl_color_print_line(f_standard_error, data.context.error, data.context.reset, "' is too long.");
          }
          else {
            fake_print_error(data.context, f_status_set_fine(status), "fl_string_dynamic_partial_mash", f_true);
          }
        }
      }

      f_macro_fss_objects_delete_simple(objects);
      f_macro_fss_contents_delete_simple(contents);
    }

    f_macro_string_dynamic_delete_simple(buffer);
    f_macro_string_dynamic_delete_simple(path);

    return status;
  }
#endif // _di_fake_load_settings_data_

#ifndef _di_fake_print_error_
  f_return_status fake_print_error(const fl_color_context context, const f_status status, const f_string function, const bool fallback) {

    if (status == f_invalid_parameter) {
      fl_color_print(f_standard_error, context.error, context.reset, "INTERNAL ERROR: Invalid parameter in function ");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", function);
      fl_color_print_line(f_standard_error, context.error, context.reset, "().");
      return f_none;
    }

    if (status == f_error_allocation || status == f_error_reallocation) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: Unable to allocate memory in function ");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", function);
      fl_color_print_line(f_standard_error, context.error, context.reset, "().");
      return f_none;
    }

    if (fallback) {
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
  f_return_status fake_print_error_file(const fl_color_context context, const f_status status, const f_string function, const f_string file_name, const f_string file_or_directory, const bool fallback) {

    if (status == f_file_not_found) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: failed to find file '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
      return f_none;
    }

    if (status == f_directory_not_found) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: failed to find directory '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
      return f_none;
    }

    if (status == f_invalid_parameter) {
      fl_color_print(f_standard_error, context.error, context.reset, "INTERNAL ERROR: Invalid parameter when calling ", function, file_name);
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", function);
      fl_color_print(f_standard_error, context.error, context.reset, "() for the %s '", file_or_directory);
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
      return f_none;
    }

    if (status == f_invalid_name) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: Invalid %s name '", file_or_directory);
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
      return f_none;
    }

    if (status == f_out_of_memory) {
      fl_color_print(f_standard_error, context.error, context.reset, "CRITICAL ERROR: Unable to allocate memory, while trying to access %s '", file_or_directory);
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
      return f_none;
    }

    if (status == f_number_overflow) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: Overflow while trying to access %s '", file_or_directory);
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
      return f_none;
    }

    if (status == f_invalid_directory) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: Invalid directory while trying to access %s '", file_or_directory);
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
      return f_none;
    }

    if (status == f_access_denied) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: Access denied while trying to access %s '", file_or_directory);
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
      return f_none;
    }

    if (status == f_loop) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: Loop while trying to access %s '", file_or_directory);
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
      return f_none;
    }

    if (fake_print_error(context, status, function, f_false) == f_unknown && fallback) {
      fl_color_print(f_standard_error, context.error, context.reset, "UNKNOWN ERROR: (");
      fl_color_print(f_standard_error, context.notable, context.reset, "%d", status);
      fl_color_print(f_standard_error, context.error, context.reset, ") occurred for %s '", file_or_directory);
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
    }

    return f_unknown;
  }
#endif // _di_fake_print_error_file_

#ifndef _di_fake_print_error_parameter_missing_value_
  void fake_print_error_parameter_missing_value(const fl_color_context context, const f_string parameter) {
    fl_color_print(f_standard_error, context.error, context.reset, "ERROR: The parameter '");
    fl_color_print(f_standard_error, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, parameter);
    fl_color_print_line(f_standard_error, context.error, context.reset, "' was specified, but no value was given.");
  }
#endif // _di_fake_print_error_parameter_missing_value_

#ifndef _di_fake_print_error_parameter_too_many_
  void fake_print_error_parameter_too_many(const fl_color_context context, const f_string parameter) {
    fl_color_print(f_standard_error, context.error, context.reset, "ERROR: the parameter '");
    fl_color_print(f_standard_error, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, parameter);
    fl_color_print_line(f_standard_error, context.error, context.reset, "' specified too many times.");
  }
#endif // _di_fake_print_error_parameter_too_many_

#ifndef _di_fake_process_console_parameters_
  f_return_status fake_process_console_parameters(const f_console_arguments arguments, fake_data *data) {
    f_status status = f_none;

    // @todo move as many of the inline error printing code into more general functions where possible to provide more accurate error reporting.

    {
      const uint8_t total = 4;

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

      for (uint8_t i = 0; i < total; i++) {
        if (data->parameters[parameter_ids[i]].total > 1) {
          fl_color_print(f_standard_error, data->context.error, data->context.reset, "ERROR: the operation '");
          fl_color_print(f_standard_error, data->context.notable, data->context.reset, "%s", parameter_names[i]);
          fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "' specified too many times.");

          return f_status_set_error(f_invalid_parameter);
        }
      } // for
    }

    {
      const uint8_t total = 2;

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

      for (uint8_t i = 0; i < total; i++) {
        if (data->parameters[parameter_ids[i]].result == f_console_result_found) {
          fake_print_error_parameter_missing_value(data->context, parameter_names[i]);
          return f_status_set_error(f_invalid_parameter);
        }
        else if (data->parameters[parameter_ids[i]].result == f_console_result_additional) {
          if (data->parameters[parameter_ids[i]].total > 1) {
            fake_print_error_parameter_too_many(data->context, parameter_names[i]);
            return f_status_set_error(f_invalid_parameter);
          }

          f_string_length location = data->parameters[parameter_ids[i]].additional.array[0];
          f_string_length length = strnlen(arguments.argv[location], f_console_max_size);

          if (length > 0) {
            status = fl_string_append(arguments.argv[location], 0, length - 1, parameter_values[i]);

            if (f_status_is_error(status)) {
              if (status == f_status_set_error(f_string_too_large)) {
                fl_color_print(f_standard_error, data->context.error, data->context.reset, "ERROR: the parameter '");
                fl_color_print(f_standard_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, parameter_names[i]);
                fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "' is too long.");
              }
              else {
                fake_print_error(data->context, f_status_set_fine(status), "fl_string_append", f_true);
              }

              return status;
            }
            else {
              status = f_none;
            }
          }

          if (length == 0 || status == f_no_data) {
            fl_color_print(f_standard_error, data->context.error, data->context.reset, "ERROR: the parameter '");
            fl_color_print(f_standard_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, parameter_names[i]);
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "' must not be empty and must not contain only whitespace.");
          }
        }
        else if (parameter_default_lengths[i] > 0) {
          f_macro_string_dynamic_resize(status, (*parameter_values[i]), parameter_default_lengths[i]);

          if (f_status_is_error(status)) {
            fake_print_error(data->context, f_status_set_fine(status), "f_macro_string_dynamic_resize", f_true);
            return status;
          }

          memcpy(parameter_values[i]->string, parameter_defaults[i], parameter_default_lengths[i]);
          parameter_values[i]->used = parameter_default_lengths[i];
        }
      } // for
    }

    if (data->parameters[fake_parameter_defines].result == f_console_result_found) {
      fake_print_error_parameter_missing_value(data->context, fake_long_defines);
      return f_status_set_error(f_invalid_parameter);
    }

    {
      const uint8_t total = 9;

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

      for (uint8_t i = 0; i < total; i++) {
        if (data->parameters[parameter_ids[i]].result == f_console_result_found) {
          fake_print_error_parameter_missing_value(data->context, parameter_names[i]);
          return f_status_set_error(f_invalid_parameter);
        }
        else if (data->parameters[parameter_ids[i]].result == f_console_result_additional) {
          if (data->parameters[parameter_ids[i]].additional.used > 1) {
            fake_print_error_parameter_too_many(data->context, parameter_names[i]);
            return f_status_set_error(f_invalid_parameter);
          }

          status = fl_console_parameter_to_string_dynamic_directory(arguments.argv[data->parameters[parameter_ids[i]].additional.array[0]], parameter_values[i]);

          if (f_status_is_error(status)) {
            if (fake_print_error(data->context, f_status_set_fine(status), "fl_console_parameter_to_string_dynamic_directory", f_false) == f_unknown) {
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
            if (fake_print_error(data->context, f_status_set_fine(status), "f_macro_string_dynamic_new", f_false) == f_unknown) {
              fl_color_print(f_standard_error, data->context.error, data->context.reset, "ERROR: failed to load default for the parameter '");
              fl_color_print(f_standard_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, parameter_names[i]);
              fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "'.");
            }

            return status;
          }

          memcpy(parameter_values[i]->string, parameter_defaults[i], parameter_default_lengths[i]);
          parameter_values[i]->used = parameter_default_lengths[i];
        }

        if (parameter_values[i]->used > 0) {
          struct stat directory_stat;

          memset(&directory_stat, 0, sizeof(struct stat));

          status = f_file_stat(parameter_values[i]->string, &directory_stat);

          if (status == f_status_set_error(f_file_not_found)) status = f_status_set_error(f_directory_not_found);

          if (f_status_is_error(status)) {
            if (f_status_set_fine(status) != f_directory_not_found || parameters_required[i]) {
              fake_print_error_file(data->context, f_status_set_fine(status), "f_file_stat", parameter_values[i]->string, "directory", f_true);
              return status;
            }
          }
        }
        else if (parameters_required[i]) {
          fl_color_print(f_standard_error, data->context.error, data->context.reset, "ERROR: No valid path for the (required) directory parameter '");
          fl_color_print(f_standard_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, parameter_names[i]);
          fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "' was found.");

          return f_status_set_error(f_directory_not_found);
        }
      } // for
    }

    if (data->parameters[fake_parameter_defines].result == f_console_result_additional) {
      status = fll_program_parameter_additional_rip_mash(" ", 1, arguments.argv, data->parameters[fake_parameter_defines].additional, &data->defines);

      if (f_status_is_error(status)) {
        if (status == f_status_set_error(f_string_too_large)) {
          fl_color_print(f_standard_error, data->context.error, data->context.reset, "ERROR: the (combined) parameter '");
          fl_color_print(f_standard_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, fake_long_defines);
          fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "' is too long.");
        }
        else {
          fake_print_error(data->context, f_status_set_fine(status), "fll_program_parameter_additional_rip_mash", f_true);
        }

        return status;
      }
    }

    if (data->parameters[fake_parameter_mode].result == f_console_result_found) {
      fake_print_error_parameter_missing_value(data->context, fake_long_mode);
      return f_status_set_error(f_invalid_parameter);
    }
    else if (data->parameters[fake_parameter_mode].result == f_console_result_additional) {
      status = fll_program_parameter_additional_rip(arguments.argv, data->parameters[fake_parameter_mode].additional, &data->mode);

      if (f_status_is_error(status)) {
        if (fake_print_error(data->context, f_status_set_fine(status), "fll_program_parameter_additional_rip", f_false) == f_unknown) {
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
            if (fake_print_error(data->context, f_status_set_fine(status), "f_utf_is_word_dash_plus", f_false) == f_unknown) {
              fl_color_print(f_standard_error, data->context.error, data->context.reset, "ERROR: failed to process the parameter '");
              fl_color_print(f_standard_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, fake_long_mode);
              fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "'.");
            }

            return status;
          }

          if (status == f_false) {
            fl_color_print(f_standard_error, data->context.error, data->context.reset, "ERROR: the '");
            fl_color_print(f_standard_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, fake_long_mode);
            fl_color_print(f_standard_error, data->context.error, data->context.reset, "' parameters value '");
            fl_color_print(f_standard_error, data->context.notable, data->context.reset, "%s", data->mode.array[i].string);
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "' contains non-word, non-dash, and non-plus characters.");

            return f_status_set_error(f_invalid_parameter);
          }
        } // for
      } // for
    }

    return f_none;
  }
#endif // _di_fake_process_console_parameters_

#ifdef __cplusplus
} // extern "C"
#endif
