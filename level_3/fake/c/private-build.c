#include <level_3/fake.h>
#include "private-fake.h"
#include "private-build.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_load_settings_
  f_return_status fake_build_load_settings(const fake_data data, fake_build_settings *settings) {
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
      f_string_range range = f_string_range_initialize;

      range.start = 0;
      range.stop = buffer.used - 1;

      status = fll_fss_extended_read(&buffer, &range, &objects, &contents);

      if (f_status_is_error(status)) {
        f_macro_fss_objects_delete_simple(objects);
        f_macro_fss_contents_delete_simple(contents);
        f_macro_string_dynamic_delete_simple(buffer);

        if (status == f_status_set_error(f_incomplete_utf_on_stop)) {
          fl_color_print(f_standard_error, data.context.error, data.context.reset, "ENCODING ERROR: error occurred on invalid UTF-8 character at stop position (at ");
          fl_color_print(f_standard_error, data.context.notable, data.context.reset, "%d", range.start);
          fl_color_print(f_standard_error, data.context.error, data.context.reset, " of settings file '");
          fl_color_print(f_standard_error, data.context.notable, data.context.reset, "%s", path.string);
          fl_color_print_line(f_standard_error, data.context.error, data.context.reset, "').");
        }
        else if (status == f_status_set_error(f_incomplete_utf_on_stop)) {
          fl_color_print(f_standard_error, data.context.error, data.context.reset, "ENCODING ERROR: error occurred on invalid UTF-8 character at end of string (at ");
          fl_color_print(f_standard_error, data.context.notable, data.context.reset, "%d", range.start);
          fl_color_print(f_standard_error, data.context.error, data.context.reset, " of settings file '");
          fl_color_print(f_standard_error, data.context.notable, data.context.reset, "%s", path.string);
          fl_color_print_line(f_standard_error, data.context.error, data.context.reset, "').");
        }
        else {
          fake_print_error(data.context, f_status_set_fine(status), "fll_fss_extended_read", true);
        }

        f_macro_fss_objects_delete_simple(objects);
        f_macro_fss_contents_delete_simple(contents);
        f_macro_string_dynamic_delete_simple(buffer);
        f_macro_string_dynamic_delete_simple(path);

        return status;
      }

      {
        const f_string setting_names[] = {
          fake_build_settings_name_build_compiler,
          fake_build_settings_name_build_libraries,
          fake_build_settings_name_build_linker,
          fake_build_settings_name_build_shared,
          fake_build_settings_name_build_sources_headers,
          fake_build_settings_name_build_sources_library,
          fake_build_settings_name_build_sources_program,
          fake_build_settings_name_build_sources_settings,
          fake_build_settings_name_build_sources_shell,
          fake_build_settings_name_build_static,
          fake_build_settings_name_defines_all,
          fake_build_settings_name_defines_shared,
          fake_build_settings_name_defines_static,
          fake_build_settings_name_flags_all,
          fake_build_settings_name_flags_library,
          fake_build_settings_name_flags_program,
          fake_build_settings_name_flags_shared,
          fake_build_settings_name_flags_static,
          fake_build_settings_name_path_language,
          fake_build_settings_name_path_headers,
          fake_build_settings_name_path_library_shared,
          fake_build_settings_name_path_library_static,
          fake_build_settings_name_path_program_shared,
          fake_build_settings_name_path_program_static,
          fake_build_settings_name_process_post,
          fake_build_settings_name_process_pre,
          fake_build_settings_name_project_level,
          fake_build_settings_name_project_name,
          fake_build_settings_name_version_major,
          fake_build_settings_name_version_micro,
          fake_build_settings_name_version_minor,
        };

        const f_string_length setting_lengths[] = {
          fake_build_settings_name_build_compiler_length,
          fake_build_settings_name_build_libraries_length,
          fake_build_settings_name_build_linker_length,
          fake_build_settings_name_build_shared_length,
          fake_build_settings_name_build_sources_headers_length,
          fake_build_settings_name_build_sources_library_length,
          fake_build_settings_name_build_sources_program_length,
          fake_build_settings_name_build_sources_settings_length,
          fake_build_settings_name_build_sources_shell_length,
          fake_build_settings_name_build_static_length,
          fake_build_settings_name_defines_all_length,
          fake_build_settings_name_defines_shared_length,
          fake_build_settings_name_defines_static_length,
          fake_build_settings_name_flags_all_length,
          fake_build_settings_name_flags_library_length,
          fake_build_settings_name_flags_program_length,
          fake_build_settings_name_flags_shared_length,
          fake_build_settings_name_flags_static_length,
          fake_build_settings_name_path_language_length,
          fake_build_settings_name_path_headers_length,
          fake_build_settings_name_path_library_shared_length,
          fake_build_settings_name_path_library_static_length,
          fake_build_settings_name_path_program_shared_length,
          fake_build_settings_name_path_program_static_length,
          fake_build_settings_name_process_post_length,
          fake_build_settings_name_process_pre_length,
          fake_build_settings_name_project_level_length,
          fake_build_settings_name_project_name_length,
          fake_build_settings_name_version_major_length,
          fake_build_settings_name_version_micro_length,
          fake_build_settings_name_version_minor_length,
        };

        f_string_dynamic *setting_values[] = {
          &settings->build_compiler,
          &settings->build_libraries,
          &settings->build_linker,
          &settings->build_shared,
          &settings->build_sources_headers,
          &settings->build_sources_library,
          &settings->build_sources_program,
          &settings->build_sources_setting,
          &settings->build_sources_shell,
          &settings->build_static,
          &settings->defines_all,
          &settings->defines_shared,
          &settings->defines_static,
          &settings->flags_all,
          &settings->flags_library,
          &settings->flags_program,
          &settings->flags_shared,
          &settings->flags_static,
          &settings->path_language,
          &settings->path_headers,
          &settings->path_library_shared,
          &settings->path_library_static,
          &settings->path_program_shared,
          &settings->path_program_static,
          &settings->process_post,
          &settings->process_pre,
          &settings->project_level,
          &settings->project_name,
          &settings->version_major,
          &settings->version_micro,
          &settings->version_minor,
        };

        // @todo change this to use fll_fss_snatch_apart() so that each string can be a distinct argument for fll_execute functions.
        status = fll_fss_snatch_mash_together(buffer, objects, contents, setting_names, setting_lengths, setting_values, fake_build_settings_total, " ", 1);

        if (status == f_none) {
          for (f_array_length i = 0; i < data.mode.used; i++) {
            f_string_dynamic settings_mode_name_dynamic[fake_build_settings_total];
            f_string settings_mode_names[fake_build_settings_total];
            f_string_length setting_mode_lengths[fake_build_settings_total];

            memset(&settings_mode_name_dynamic, 0, sizeof(f_string_dynamic) * fake_build_settings_total);
            memset(&settings_mode_names, 0, sizeof(f_string) * fake_build_settings_total);

            for (f_string_length j = 0; j < fake_build_settings_total; j++) {
              setting_mode_lengths[j] = setting_lengths[j] + 1 + data.mode.array[i].used;

              f_macro_string_dynamic_new(status, settings_mode_name_dynamic[j], setting_mode_lengths[j]);
              if (f_status_is_error(status)) break;

              memcpy(settings_mode_name_dynamic[j].string, setting_names[j], setting_lengths[j]);
              memcpy(settings_mode_name_dynamic[j].string + setting_lengths[j] + 1, data.mode.array[i].string, data.mode.array[i].used);
              settings_mode_name_dynamic[j].string[setting_lengths[j]] = '-';

              settings_mode_names[j] = settings_mode_name_dynamic[j].string;
            } // for

            if (status == f_none) {
              status = fll_fss_snatch_mash_together(buffer, objects, contents, settings_mode_names, setting_mode_lengths, setting_values, fake_build_settings_total, " ", 1);
            }

            for (f_string_length j = 0; j < fake_build_settings_total; j++) {
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

    // @todo: perform validation of values, such as "shared" and "static", at least one must be "yes".

    return status;
  }
#endif // _di_fake_build_load_settings_

#ifndef _di_fake_build_operate_
  f_return_status fake_build_operate(const fake_data data) {
    f_status status = f_none;
    fake_build_settings settings = fake_build_settings_initialize;

    status = fake_build_load_settings(data, &settings);

    if (f_status_is_error(status)) {
      fake_macro_build_settings_delete_simple(settings);
      return f_status_set_error(status);
    }

    status = fake_build_execute_process_script(data, settings, settings.process_pre);
    if (f_status_is_error(status)) {
      // @todo handle errors.
    }

    // @todo: may have to process all data intended to be used in parameters, exploding them into console parameters.
    // Steps:
    // 1) copy sources settings to build settings
    // 2) copy sources headers to build headers
    // 3) if shared=yes and library sources exist, compile shared libraries and make links.
    // 4) if shared=yes and program sources exist, compile shared programs.
    // 5) if static=yes and library sources exist, compile static objects.
    // 6) if static=yes and library sources exist, link static objects into static library (appending objects to path for static programs to compile against).
    // 7) if static=yes and program sources exist, compile static programs (include any static objects).
    // 8) touch build file designating that build fully completed.

    status = fake_build_execute_process_script(data, settings, settings.process_post);
    if (f_status_is_error(status)) {
      // @todo handle errors.
    }

    fake_macro_build_settings_delete_simple(settings);

    return status;
  }
#endif // _di_fake_build_operate_

#ifndef _di_fake_build_execute_process_script_
  f_return_status fake_build_execute_process_script(const fake_data data, const fake_build_settings settings, const f_string_dynamic process_script) {
    if (process_script.used == 0) return f_none;

    f_status status = f_none;

    const f_string parameter_prefixs[] = {
      f_console_symbol_short_enable,
      f_console_symbol_short_enable,
      f_console_symbol_short_enable,
      f_console_symbol_short_enable,
      f_console_symbol_short_enable,
      f_console_symbol_short_enable,
      f_console_symbol_short_enable,
      f_console_symbol_short_enable,
      f_console_symbol_short_enable,
      f_console_symbol_short_enable,
      f_console_symbol_short_enable,
      f_console_symbol_short_enable,
    };

    const f_string_length parameter_prefixs_length[] = {
       f_console_symbol_short_enable_length,
       f_console_symbol_short_enable_length,
       f_console_symbol_short_enable_length,
       f_console_symbol_short_enable_length,
       f_console_symbol_short_enable_length,
       f_console_symbol_short_enable_length,
       f_console_symbol_short_enable_length,
       f_console_symbol_short_enable_length,
       f_console_symbol_short_enable_length,
       f_console_symbol_short_enable_length,
       f_console_symbol_short_enable_length,
       f_console_symbol_short_enable_length,
    };

    const f_string parameter_names[] = {
      fake_short_defines,
      fake_short_process,
      fake_short_settings,
      fake_short_path_build,
      fake_short_path_work,
      fake_short_path_source_build,
      fake_short_path_source_common,
      fake_short_path_source_data,
      fake_short_path_source_documents,
      fake_short_path_source_codes,
      fake_short_path_source_licenses,
      fake_short_path_source_settings,
    };

    const f_string_length parameter_names_length[] = {
       fake_short_defines_length,
       fake_short_process_length,
       fake_short_settings_length,
       fake_short_path_build_length,
       fake_short_path_work_length,
       fake_short_path_source_build_length,
       fake_short_path_source_common_length,
       fake_short_path_source_data_length,
       fake_short_path_source_documents_length,
       fake_short_path_source_codes_length,
       fake_short_path_source_licenses_length,
       fake_short_path_source_settings_length,
    };

    const f_string parameter_values[] = {
      data.defines.string,
      data.process.string,
      data.settings.string,
      data.path_build.string,
      data.path_work.string,
      data.path_source_build.string,
      data.path_source_common.string,
      data.path_source_data.string,
      data.path_source_documents.string,
      data.path_source_codes.string,
      data.path_source_licenses.string,
      data.path_source_settings.string,
    };

    const f_string_length parameter_values_length[] = {
      data.defines.used,
      data.process.used,
      data.settings.used,
      data.path_build.used,
      data.path_work.used,
      data.path_source_build.used,
      data.path_source_common.used,
      data.path_source_data.used,
      data.path_source_documents.used,
      data.path_source_codes.used,
      data.path_source_licenses.used,
      data.path_source_settings.used,
    };

    const uint8_t parameters_total = 12;

    f_string_dynamics arguments = f_string_dynamics_initialize;

    status = fll_execute_arguments_add(fake_other_operation_build, fake_other_operation_build_length, &arguments);

    if (f_status_is_error(status)) {
      fake_print_error(data.context, f_status_set_fine(status), "fll_execute_arguments_add", f_true);

      f_macro_string_dynamics_delete_simple(arguments);
      return status;
    }

    status = fll_execute_arguments_add_parameter_set(parameter_prefixs, parameter_prefixs_length, parameter_names, parameter_names_length, parameter_values, parameter_values_length, parameters_total, &arguments);

    if (f_status_is_error(status)) {
      fake_print_error(data.context, f_status_set_fine(status), "fll_execute_arguments_add_parameter_set", f_true);

      f_macro_string_dynamics_delete_simple(arguments);
      return status;
    }

    f_string_dynamic path = f_string_dynamic_initialize;

    if (process_script.string[0] != '/') {
      status = fl_string_dynamic_append(data.path_source_settings, &path);
    }

    if (!f_status_is_error(status)) {
      status = fl_string_dynamic_append(process_script, &path);
    }

    if (f_status_is_error(status)) {
      fake_print_error(data.context, f_status_set_fine(status), "fl_string_dynamic_append", f_true);

      f_macro_string_dynamic_delete_simple(path);
      return status;
    }

    int results = 0;

    status = fll_execute_path(path.string, arguments, &results);

    if (f_status_is_error(status)) {
      if (f_status_set_fine(status) == f_failure) {
        fl_color_print(f_standard_error, data.context.error, data.context.reset, "ERROR: Failed to execute script: ");
        fl_color_print(f_standard_error, data.context.notable, data.context.reset, "%s", path.string);
        fl_color_print_line(f_standard_error, data.context.error, data.context.reset, ".");
      }
      else {
        fake_print_error(data.context, f_status_set_fine(status), "fll_execute_path", f_true);
      }
    }

    f_macro_string_dynamic_delete_simple(path);
    f_macro_string_dynamics_delete_simple(arguments);

    return status;
  }
#endif // _di_fake_execute_process_pre_

#ifdef __cplusplus
} // extern "C"
#endif
