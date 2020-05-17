#include <level_3/fake.h>
#include "private-fake.h"
#include "private-build.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_execute_process_script_
  f_return_status fake_build_execute_process_script(const fake_data data, const fake_build_settings settings, const f_string_static process_script) {
    if (process_script.used == 0) return f_none;

    f_status status = f_none;
    f_string_dynamics arguments = f_string_dynamics_initialize;

    status = fll_execute_arguments_add(fake_other_operation_build, fake_other_operation_build_length, &arguments);

    // ensure console color mode is passed to the scripts so that they can also react to color mode.
    if (!f_status_is_error(status) && data.context.mode != f_color_mode_none) {
      char argument[3] = { f_console_symbol_disable, 0, 0 };

      if (data.context.mode == f_color_mode_dark) {
        argument[1] = f_console_standard_short_dark[0];
      }
      else if (data.context.mode == f_color_mode_light) {
        argument[1] = f_console_standard_short_light[0];
      }
      else if (data.context.mode == f_color_mode_no_color) {
        argument[1] = f_console_standard_short_no_color[0];
      }

      status = fll_execute_arguments_add(argument, 2, &arguments);
    }

    // ensure verbosity level is passed to the scripts so that they can also react to requested verbosity.
    if (!f_status_is_error(status) && data.verbosity != fake_verbosity_normal) {
      char argument[3] = { f_console_symbol_disable, 0, 0 };

      if (data.verbosity == fake_verbosity_quiet) {
        argument[1] = f_console_standard_short_quiet[0];
      }
      else if (data.verbosity == fake_verbosity_verbose) {
        argument[1] = f_console_standard_short_verbose[0];
      }
      else if (data.verbosity == fake_verbosity_debug) {
        argument[1] = f_console_standard_short_debug[0];
      }

      status = fll_execute_arguments_add(argument, 2, &arguments);
    }

    if (f_status_is_error(status)) {
      fake_print_error(data.context, data.verbosity, f_status_set_fine(status), "fll_execute_arguments_add", f_true);

      f_macro_string_dynamics_delete_simple(arguments);
      return status;
    }

    {
      const f_string parameters_prefix[] = {
        f_console_symbol_short_enable,
        f_console_symbol_short_enable,
        f_console_symbol_short_enable,
        f_console_symbol_short_enable,
        f_console_symbol_short_enable,
        f_console_symbol_short_enable,
        f_console_symbol_short_enable,
      };

      const f_string_length parameters_prefix_length[] = {
         f_console_symbol_short_enable_length,
         f_console_symbol_short_enable_length,
         f_console_symbol_short_enable_length,
         f_console_symbol_short_enable_length,
         f_console_symbol_short_enable_length,
         f_console_symbol_short_enable_length,
         f_console_symbol_short_enable_length,
      };

      const f_string parameters_name[] = {
        fake_short_defines,
        fake_short_process,
        fake_short_settings,
        fake_short_path_build,
        fake_short_path_data,
        fake_short_path_sources,
        fake_short_path_work,
      };

      const f_string_length parameters_name_length[] = {
         fake_short_defines_length,
         fake_short_process_length,
         fake_short_settings_length,
         fake_short_path_build_length,
         fake_short_path_data_length,
         fake_short_path_sources_length,
         fake_short_path_work_length,
      };

      const f_string parameters_value[] = {
        data.defines.string,
        data.process.string,
        data.settings.string,
        data.path_build.string,
        data.path_data.string,
        data.path_sources.string,
        data.path_work.string,
      };

      const f_string_length parameters_value_length[] = {
        data.defines.used,
        data.process.used,
        data.settings.used,
        data.path_build.used,
        data.path_data.used,
        data.path_sources.used,
        data.path_work.used,
      };

      status = fll_execute_arguments_add_parameter_set(parameters_prefix, parameters_prefix_length, parameters_name, parameters_name_length, parameters_value, parameters_value_length, 7, &arguments);

      if (f_status_is_error(status)) {
        fake_print_error(data.context, data.verbosity, f_status_set_fine(status), "fll_execute_arguments_add_parameter_set", f_true);

        f_macro_string_dynamics_delete_simple(arguments);
        return status;
      }
    }

    f_string_dynamic path = f_string_dynamic_initialize;
    f_string function = 0;

    {
      function = "fl_string_dynamic_append_nulless";

      if (process_script.string[0] != '/') {
        status = fl_string_dynamic_append_nulless(data.path_data_build, &path);
      }

      if (!f_status_is_error(status)) {
        status = fl_string_dynamic_append_nulless(process_script, &path);
      }

      if (!f_status_is_error(status)) {
        function = "fl_string_dynamic_terminate";
        status = fl_string_dynamic_terminate(&path);
      }

      if (f_status_is_error(status)) {
        fake_print_error(data.context, data.verbosity, f_status_set_fine(status), function, f_true);

        f_macro_string_dynamic_delete_simple(path);
        f_macro_string_dynamics_delete_simple(arguments);
        return status;
      }
    }

    {
      // @todo: create an implode function that merges f_string [] (and an f_string_dynamic [] equivalent) into a f_string_dynamics.
      f_string_dynamics names = f_string_dynamics_initialize;

      {
        // add the guaranteed environment variables.
        const f_string variables_name[] = {
          f_path_environment,
          f_path_present_working
        };

        const f_string_length variables_length[] = {
          f_path_environment_length,
          f_path_present_working_length
        };

        f_macro_string_dynamics_new(status, names, 2);
        if (f_status_is_error(status)) {
          fake_print_error(data.context, data.verbosity, f_status_set_fine(status), "f_macro_string_dynamics_new", f_true);

          f_macro_string_dynamic_delete_simple(path);
          f_macro_string_dynamics_delete_simple(arguments);
          f_macro_string_dynamics_delete_simple(names);
          return status;
        }

        f_string_dynamic part = f_string_dynamic_initialize;

        for (uint8_t i = 0; i < 2; i++) {
          status = fl_string_append(variables_name[i], variables_length[i], &part);
          if (f_status_is_error(status)) break;

          names.array[names.used].string = part.string;
          names.array[names.used].used = part.used;
          names.array[names.used].size = part.size;
          names.used++;

          f_macro_string_dynamic_clear(part);
        } // for

        if (!f_status_is_error(status)) {
          if (names.used + settings.environment.used > names.size) {
            if (names.used + settings.environment.used > f_array_length_size) {
              if (data.verbosity != fake_verbosity_quiet) {
                fprintf(f_standard_error, "%c", f_string_eol);
                fl_color_print(f_standard_error, data.context.error, data.context.reset, "ERROR: The values for the settings '");
                fl_color_print(f_standard_error, data.context.notable, data.context.reset, "%s", fake_build_settings_name_environment);
                fl_color_print(f_standard_error, data.context.error, data.context.reset, "' of settings file '");
                fl_color_print(f_standard_error, data.context.notable, data.context.reset, "%s", data.file_data_build_settings.string);
                fl_color_print_line(f_standard_error, data.context.error, data.context.reset, "' is too large.");
              }

              f_macro_string_dynamic_delete_simple(part);
              f_macro_string_dynamics_delete_simple(arguments);
              f_macro_string_dynamics_delete_simple(names);
              return f_status_set_error(f_buffer_too_large);
            }

            f_macro_string_dynamics_resize(status, names, names.used + settings.environment.used);
            if (f_status_is_error(status)) {
              fake_print_error(data.context, data.verbosity, f_status_set_fine(status), "f_macro_string_dynamics_resize", f_true);

              f_macro_string_dynamic_delete_simple(part);
              f_macro_string_dynamics_delete_simple(arguments);
              f_macro_string_dynamics_delete_simple(names);
              return status;
            }
          }

          for (f_string_length i = 0; i < settings.environment.used; i++) {
            status = fl_string_dynamic_append_nulless(settings.environment.array[i], &part);
            if (f_status_is_error(status)) break;

            names.array[names.used].string = part.string;
            names.array[names.used].used = part.used;
            names.array[names.used].size = part.size;
            names.used++;

            f_macro_string_dynamic_clear(part);
          } // for
        }

        f_macro_string_dynamic_delete_simple(part);

        if (f_status_is_error(status)) {
          fake_print_error(data.context, data.verbosity, f_status_set_fine(status), "fl_string_append", f_true);

          f_macro_string_dynamic_delete_simple(path);
          f_macro_string_dynamics_delete_simple(arguments);
          f_macro_string_dynamics_delete_simple(names);
          return status;
        }
      }

      f_string_dynamics environment_names = f_string_dynamics_initialize;
      f_string_dynamics environment_values = f_string_dynamics_initialize;

      f_string_dynamic variable_name = f_string_dynamic_initialize;
      f_string_dynamic variable_value = f_string_dynamic_initialize;

      for (f_string_length i = 0; i < names.used; i++) {
        status = f_environment_get_dynamic(names.array[i], &variable_value);
        if (f_status_is_error(status)) {
          status = f_status_set_fine(status);

          if (status == f_error_reallocation) {
            function = "f_macro_string_dynamics_resize";
            break;
          }
        }

        if (environment_names.used + 1 > environment_names.size) {
          f_macro_string_dynamics_resize(status, environment_names, environment_names.size + f_memory_default_allocation_step);

          if (!f_status_is_error(status)) {
            f_macro_string_dynamics_resize(status, environment_values, environment_values.size + f_memory_default_allocation_step);
          }

          if (f_status_is_error(status)) {
            function = "f_macro_string_dynamics_resize";
            break;
          }
        }

        status = fl_string_dynamic_append(names.array[i], &variable_name);

        if (f_status_is_error(status)) {
          function = "fl_string_append";
          break;
        }

        environment_names.array[environment_names.used].string = variable_name.string;
        environment_names.array[environment_names.used].used = variable_name.used;
        environment_names.array[environment_names.used].size = variable_name.size;
        environment_names.used++;

        environment_values.array[environment_values.used].string = variable_value.string;
        environment_values.array[environment_values.used].used = variable_value.used;
        environment_values.array[environment_values.used].size = variable_value.size;
        environment_values.used++;

        f_macro_string_dynamic_clear(variable_name);
        f_macro_string_dynamic_clear(variable_value);
      } // for

      f_macro_string_dynamics_delete_simple(names);

      if (f_status_is_error(status)) {
        fake_print_error(data.context, data.verbosity, status, function, f_true);

        f_macro_string_dynamic_delete_simple(variable_name);
        f_macro_string_dynamic_delete_simple(variable_value);
        f_macro_string_dynamics_delete_simple(environment_names);
        f_macro_string_dynamics_delete_simple(environment_values);
        f_macro_string_dynamic_delete_simple(path);
        f_macro_string_dynamics_delete_simple(arguments);
        return status;
      }

      int result = 0;

      status = fll_execute_path_environment(path.string, arguments, environment_names, environment_values, &result);

      f_macro_string_dynamics_delete_simple(environment_names);
      f_macro_string_dynamics_delete_simple(environment_values);
      f_macro_string_dynamics_delete_simple(arguments);
    }

    if (f_status_is_error(status)) {
      if (f_status_set_fine(status) == f_failure) {
        if (data.verbosity != fake_verbosity_quiet) {
          fprintf(f_standard_error, "%c", f_string_eol);
          fl_color_print(f_standard_error, data.context.error, data.context.reset, "ERROR: Failed to execute script: ");
          fl_color_print(f_standard_error, data.context.notable, data.context.reset, "%s", path.string);
          fl_color_print_line(f_standard_error, data.context.error, data.context.reset, ".");
        }
      }
      else {
        fake_print_error(data.context, data.verbosity, f_status_set_fine(status), "fll_execute_path_environment", f_true);
      }
    }

    f_macro_string_dynamic_delete_simple(path);

    return status;
  }
#endif // _di_fake_build_execute_process_script_

#ifndef _di_fake_build_operate_
  f_return_status fake_build_operate(const fake_data data) {
    if (data.verbosity != fake_verbosity_quiet) {
      printf("%c", f_string_eol);
      fl_color_print_line(f_standard_output, data.context.important, data.context.reset, "Building project.");
    }

    f_status status = f_none;
    fake_build_settings settings = fake_build_settings_initialize;

    status = fake_build_settings_load(data, &settings);

    if (f_status_is_error(status)) {
      fake_macro_build_settings_delete_simple(settings);
      return status;
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

#ifndef _di_fake_build_settings_load_
  f_return_status fake_build_settings_load(const fake_data data, fake_build_settings *settings) {
    f_status status = f_none;
    f_file file = f_file_initialize;
    f_string_dynamic buffer = f_string_dynamic_initialize;

    {
      f_string name_function = f_string_initialize;

      name_function = "f_file_exists";
      status = f_file_exists(data.file_data_build_settings.string);

      if (status == f_true) {
        name_function = "f_file_open";
        status = f_file_open(&file, data.file_data_build_settings.string);

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
        fake_print_error_file(data.context, data.verbosity, f_status_set_fine(status), name_function, data.file_data_build_settings.string, "create", f_true, f_true);

        f_macro_string_dynamic_delete_simple(buffer);
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
          if (data.verbosity != fake_verbosity_quiet) {
            fprintf(f_standard_error, "%c", f_string_eol);
            fl_color_print(f_standard_error, data.context.error, data.context.reset, "ENCODING ERROR: error occurred on invalid UTF-8 character at stop position (at ");
            fl_color_print(f_standard_error, data.context.notable, data.context.reset, "%d", range.start);
            fl_color_print(f_standard_error, data.context.error, data.context.reset, " of settings file '");
            fl_color_print(f_standard_error, data.context.notable, data.context.reset, "%s", data.file_data_build_settings.string);
            fl_color_print_line(f_standard_error, data.context.error, data.context.reset, "').");
          }
        }
        else if (status == f_status_set_error(f_incomplete_utf_on_stop)) {
          if (data.verbosity != fake_verbosity_quiet) {
            fprintf(f_standard_error, "%c", f_string_eol);
            fl_color_print(f_standard_error, data.context.error, data.context.reset, "ENCODING ERROR: error occurred on invalid UTF-8 character at end of string (at ");
            fl_color_print(f_standard_error, data.context.notable, data.context.reset, "%d", range.start);
            fl_color_print(f_standard_error, data.context.error, data.context.reset, " of settings file '");
            fl_color_print(f_standard_error, data.context.notable, data.context.reset, "%s", data.file_data_build_settings.string);
            fl_color_print_line(f_standard_error, data.context.error, data.context.reset, "').");
          }
        }
        else {
          fake_print_error(data.context, data.verbosity, f_status_set_fine(status), "fll_fss_extended_read", true);
        }

        f_macro_fss_objects_delete_simple(objects);
        f_macro_fss_contents_delete_simple(contents);
        f_macro_string_dynamic_delete_simple(buffer);

        return status;
      }

      {
        const f_string settings_name[] = {
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
          fake_build_settings_name_environment,
          fake_build_settings_name_flags_all,
          fake_build_settings_name_flags_library,
          fake_build_settings_name_flags_program,
          fake_build_settings_name_flags_shared,
          fake_build_settings_name_flags_static,
          fake_build_settings_name_path_headers,
          fake_build_settings_name_path_language,
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

        const f_string_length settings_length[] = {
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
          fake_build_settings_name_environment_length,
          fake_build_settings_name_flags_all_length,
          fake_build_settings_name_flags_library_length,
          fake_build_settings_name_flags_program_length,
          fake_build_settings_name_flags_shared_length,
          fake_build_settings_name_flags_static_length,
          fake_build_settings_name_path_headers_length,
          fake_build_settings_name_path_language_length,
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

        f_string_dynamics build_shared = f_string_dynamics_initialize;
        f_string_dynamics build_static = f_string_dynamics_initialize;
        f_string_dynamics path_headers = f_string_dynamics_initialize;
        f_string_dynamics path_language = f_string_dynamics_initialize;
        f_string_dynamics path_library_shared = f_string_dynamics_initialize;
        f_string_dynamics path_library_static = f_string_dynamics_initialize;
        f_string_dynamics path_program_shared = f_string_dynamics_initialize;
        f_string_dynamics path_program_static = f_string_dynamics_initialize;
        f_string_dynamics process_post = f_string_dynamics_initialize;
        f_string_dynamics process_pre = f_string_dynamics_initialize;
        f_string_dynamics project_level = f_string_dynamics_initialize;
        f_string_dynamics project_name = f_string_dynamics_initialize;
        f_string_dynamics version_major = f_string_dynamics_initialize;
        f_string_dynamics version_micro = f_string_dynamics_initialize;
        f_string_dynamics version_minor = f_string_dynamics_initialize;

        f_string_dynamics *settings_value[] = {
          &settings->build_compiler,
          &settings->build_libraries,
          &settings->build_linker,
          &build_shared,
          &settings->build_sources_headers,
          &settings->build_sources_library,
          &settings->build_sources_program,
          &settings->build_sources_setting,
          &settings->build_sources_shell,
          &build_static,
          &settings->defines_all,
          &settings->defines_shared,
          &settings->defines_static,
          &settings->environment,
          &settings->flags_all,
          &settings->flags_library,
          &settings->flags_program,
          &settings->flags_shared,
          &settings->flags_static,
          &path_headers,
          &path_language,
          &path_library_shared,
          &path_library_static,
          &path_program_shared,
          &path_program_static,
          &process_post,
          &process_pre,
          &project_level,
          &project_name,
          &version_major,
          &version_micro,
          &version_minor,
        };

        status = fll_fss_snatch_apart(buffer, objects, contents, settings_name, settings_length, settings_value, fake_build_settings_total);

        if (status == f_none) {
          for (f_array_length i = 0; i < data.mode.used; i++) {
            f_string_dynamic settings_mode_name_dynamic[fake_build_settings_total];
            f_string settings_mode_names[fake_build_settings_total];
            f_string_length setting_mode_lengths[fake_build_settings_total];

            memset(&settings_mode_name_dynamic, 0, sizeof(f_string_dynamic) * fake_build_settings_total);
            memset(&settings_mode_names, 0, sizeof(f_string) * fake_build_settings_total);

            for (f_string_length j = 0; j < fake_build_settings_total; j++) {
              setting_mode_lengths[j] = settings_length[j] + 1 + data.mode.array[i].used;

              f_macro_string_dynamic_new(status, settings_mode_name_dynamic[j], setting_mode_lengths[j]);
              if (f_status_is_error(status)) break;

              memcpy(settings_mode_name_dynamic[j].string, settings_name[j], settings_length[j]);
              memcpy(settings_mode_name_dynamic[j].string + settings_length[j] + 1, data.mode.array[i].string, data.mode.array[i].used);
              settings_mode_name_dynamic[j].string[settings_length[j]] = '-';

              settings_mode_names[j] = settings_mode_name_dynamic[j].string;
            } // for

            if (status == f_none) {
              status = fll_fss_snatch_apart(buffer, objects, contents, settings_mode_names, setting_mode_lengths, settings_value, fake_build_settings_total);
            }

            for (f_string_length j = 0; j < fake_build_settings_total; j++) {
              f_macro_string_dynamic_delete_simple(settings_mode_name_dynamic[j]);
            } // for

            if (f_status_is_error(status)) break;
          } // for

          if (f_status_is_error(status)) {
            fake_print_error(data.context, data.verbosity, f_status_set_fine(status), "f_macro_string_dynamic_new", f_true);

            f_macro_string_dynamics_delete_simple(build_shared);
            f_macro_string_dynamics_delete_simple(build_static);
            f_macro_string_dynamics_delete_simple(path_headers);
            f_macro_string_dynamics_delete_simple(path_language);
            f_macro_string_dynamics_delete_simple(path_library_shared);
            f_macro_string_dynamics_delete_simple(path_library_static);
            f_macro_string_dynamics_delete_simple(path_program_shared);
            f_macro_string_dynamics_delete_simple(path_program_static);
            f_macro_string_dynamics_delete_simple(process_post);
            f_macro_string_dynamics_delete_simple(process_pre);
            f_macro_string_dynamics_delete_simple(project_level);
            f_macro_string_dynamics_delete_simple(project_name);
            f_macro_string_dynamics_delete_simple(version_major);
            f_macro_string_dynamics_delete_simple(version_micro);
            f_macro_string_dynamics_delete_simple(version_minor);

            f_macro_fss_objects_delete_simple(objects);
            f_macro_fss_contents_delete_simple(contents);
            f_macro_string_dynamic_delete_simple(buffer);
            return status;
          }
        }

        if (f_status_is_error(status)) {
          if (status == f_status_set_error(f_string_too_large)) {
            if (data.verbosity != fake_verbosity_quiet) {
              // @todo update FSS functions to return which setting index the problem happened on.
              fprintf(f_standard_error, "%c", f_string_eol);
              fl_color_print(f_standard_error, data.context.error, data.context.reset, "ERROR: a setting in the build settings file '");
              fl_color_print(f_standard_error, data.context.notable, data.context.reset, "%s", data.file_data_build_settings.string);
              fl_color_print_line(f_standard_error, data.context.error, data.context.reset, "' is too long.");
            }
          }
          else {
            fake_print_error(data.context, data.verbosity, f_status_set_fine(status), "fl_string_dynamic_partial_mash", f_true);
          }
        }

        const f_string settings_single_name[] = {
          fake_build_settings_name_build_shared,
          fake_build_settings_name_build_static,
          fake_build_settings_name_path_headers,
          fake_build_settings_name_path_language,
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

        const f_string_statics *settings_single_source[] = {
          &build_shared,
          &build_static,
          &path_headers,
          &path_language,
          &path_library_shared,
          &path_library_static,
          &path_program_shared,
          &path_program_static,
          &process_post,
          &process_pre,
          &project_level,
          &project_name,
          &version_major,
          &version_micro,
          &version_minor,
        };

        bool *settings_single_bool[] = {
          &settings->build_shared,
          &settings->build_static,
        };

        f_string_dynamic *settings_single_destination[] = {
          0,
          0,
          &settings->path_headers,
          &settings->path_language,
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

        uint8_t settings_single_type[] = {
          1, // yes/no
          1,
          2, // path
          2,
          2,
          2,
          2,
          2,
          3, // just a string
          3,
          3,
          3,
          3,
          3,
          3,
        };

        for (f_array_length i = 0; i < 15; i++) {
          if (settings_single_source[i]->used == 0) continue;

          if (settings_single_source[i]->used > 1) {
            if (data.verbosity != fake_verbosity_quiet) {
              fprintf(f_standard_warning, "%c", f_string_eol);
              fl_color_print(f_standard_warning, data.context.warning, data.context.reset, "WARNING: the setting '");
              fl_color_print(f_standard_warning, data.context.notable, data.context.reset, "%s", settings_single_name[i]);
              fl_color_print(f_standard_warning, data.context.warning, data.context.reset, "' in the file '");
              fl_color_print(f_standard_warning, data.context.notable, data.context.reset, "%s", data.file_data_build_settings.string);
              fl_color_print(f_standard_warning, data.context.warning, data.context.reset, "' may only have a single property, only using the first: '");
              fl_color_print(f_standard_warning, data.context.notable, data.context.reset, "%s", settings_single_source[i]->array[0].string);
              fl_color_print_line(f_standard_warning, data.context.warning, data.context.reset, "'.");
            }
          }

          if (settings_single_type[i] == 1) {
            if (fl_string_compare_trim(settings_single_source[i]->array[0].string, fake_build_settings_bool_yes, settings_single_source[i]->array[0].used, fake_build_settings_bool_yes_length) == f_equal_to) {
              *settings_single_bool[i] = f_true;
            }
            else if (fl_string_compare_trim(settings_single_source[i]->array[0].string, fake_build_settings_bool_no, settings_single_source[i]->array[0].used, fake_build_settings_bool_no_length) == f_equal_to) {
              *settings_single_bool[i] = f_false;
            }
            else {
              *settings_single_bool[i] = f_true;

              if (data.verbosity != fake_verbosity_quiet) {
                fprintf(f_standard_warning, "%c", f_string_eol);
                fl_color_print(f_standard_warning, data.context.warning, data.context.reset, "WARNING: the setting '");
                fl_color_print(f_standard_warning, data.context.notable, data.context.reset, "%s", settings_single_name[i]);
                fl_color_print(f_standard_warning, data.context.warning, data.context.reset, "' in the file '");
                fl_color_print(f_standard_warning, data.context.notable, data.context.reset, "%s", data.file_data_build_settings.string);
                fl_color_print(f_standard_warning, data.context.warning, data.context.reset, "' may be either '");
                fl_color_print(f_standard_warning, data.context.notable, data.context.reset, "%s", fake_build_settings_bool_yes);
                fl_color_print(f_standard_warning, data.context.warning, data.context.reset, "' or '");
                fl_color_print(f_standard_warning, data.context.notable, data.context.reset, "%s", fake_build_settings_bool_no);
                fl_color_print(f_standard_warning, data.context.warning, data.context.reset, "', defaulting to '");
                fl_color_print(f_standard_warning, data.context.notable, data.context.reset, "%s", fake_build_settings_bool_yes);
                fl_color_print_line(f_standard_warning, data.context.warning, data.context.reset, "'.");
              }
            }
          }
          else {
            status = fl_string_dynamic_append_nulless(settings_single_source[i]->array[0], settings_single_destination[i]);
            if (f_status_is_error(status)) {
              fake_print_error(data.context, data.verbosity, f_status_set_fine(status), "fl_string_dynamic_append_nulless", f_true);
              break;
            }

            if (settings_single_type[i] == 2) {
              status = fl_string_append_assure(f_path_separator, f_path_separator_length, settings_single_destination[i]);
              if (f_status_is_error(status)) {
                fake_print_error(data.context, data.verbosity, f_status_set_fine(status), "fl_string_dynamic_append_nulless", f_true);
                break;
              }
            }

            status = fl_string_dynamic_terminate(settings_single_destination[i]);
            if (f_status_is_error(status)) {
              fake_print_error(data.context, data.verbosity, f_status_set_fine(status), "fl_string_dynamic_terminate", f_true);
              break;
            }
          }
        } // for

        f_macro_string_dynamics_delete_simple(build_shared);
        f_macro_string_dynamics_delete_simple(build_static);
        f_macro_string_dynamics_delete_simple(path_headers);
        f_macro_string_dynamics_delete_simple(path_language);
        f_macro_string_dynamics_delete_simple(path_library_shared);
        f_macro_string_dynamics_delete_simple(path_library_static);
        f_macro_string_dynamics_delete_simple(path_program_shared);
        f_macro_string_dynamics_delete_simple(path_program_static);
        f_macro_string_dynamics_delete_simple(process_post);
        f_macro_string_dynamics_delete_simple(process_pre);
        f_macro_string_dynamics_delete_simple(project_level);
        f_macro_string_dynamics_delete_simple(project_name);
        f_macro_string_dynamics_delete_simple(version_major);
        f_macro_string_dynamics_delete_simple(version_micro);
        f_macro_string_dynamics_delete_simple(version_minor);
      }

      f_macro_fss_objects_delete_simple(objects);
      f_macro_fss_contents_delete_simple(contents);
    }

    f_macro_string_dynamic_delete_simple(buffer);

    // @todo: perform validation of values, such as "shared" and "static", at least one must be "yes".

    return status;
  }
#endif // _di_fake_build_settings_load_

#ifdef __cplusplus
} // extern "C"
#endif
