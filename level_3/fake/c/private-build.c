#include <level_3/fake.h>
#include "private-fake.h"
#include "private-build.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_copy_
  void fake_build_copy(const fake_data data, const f_mode mode, const f_string label, const f_string_static source, const f_string_static destination, const f_string_statics files, const f_string_static file_stage, f_status *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true) return;

    f_directory_statuss failures = f_directory_statuss_initialize;
    f_string_dynamic path_source = f_string_dynamic_initialize;
    f_string_dynamic destination_file = f_string_dynamic_initialize;

    if (data.verbosity != fake_verbosity_quiet) {
      printf("%cCopying %s.%c", f_string_eol[0], label, f_string_eol[0]);
    }

    f_macro_string_dynamic_new(*status, path_source, source.used);
    if (F_status_is_error(*status)) {
      fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "f_macro_string_dynamic_new", F_true);

      f_macro_string_dynamic_delete_simple(path_source);
      return;
    }

    memcpy(path_source.string, source.string, source.used);

    for (f_array_length i = 0; i < files.used; i++) {
      if (files.array[i].used == 0) continue;

      if (source.used == 0) {
        path_source.used = 0;
      }
      else {
        path_source.used = source.used - 1;
      }

      *status = fl_string_dynamic_append_nulless(files.array[i], &path_source);
      if (F_status_is_error(*status)) {
        fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_dynamic_append_nulless", F_true);
        break;
      }

      *status = fl_string_dynamic_terminate(&path_source);
      if (F_status_is_error(*status)) {
        fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_dynamic_terminate", F_true);
        break;
      }

      if ((*status = f_directory_is(path_source.string)) == F_true) {
        *status = fl_directory_copy_content(path_source.string, destination.string, path_source.used, destination.used, mode, f_file_default_read_size, F_false, (data.verbosity == fake_verbosity_verbose) ? f_type_output : 0, &failures);

        if (F_status_is_error(*status)) {
          if (data.verbosity == fake_verbosity_verbose) {
            for (f_string_length j = 0; j < failures.used; j++) {
              fake_print_error_operation(data.context, data.verbosity, F_status_set_fine(*status), "fl_directory_copy_content", "copy contents of", "to", path_source.string, destination.string, F_true);
            } // for

            if (F_status_set_fine(*status) != F_failure) {
              fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_directory_copy_content", F_true);
            }

            break;
          }
          else if (data.verbosity != fake_verbosity_quiet) {
            fake_print_error_operation(data.context, data.verbosity, F_status_set_fine(*status), "fl_directory_copy_content", "copy contents of", "to", path_source.string, destination.string, F_true);
          }

          break;
        }
      }
      else if (*status == F_false) {
        destination_file.used = 0;

        *status = fl_string_dynamic_append_nulless(destination, &destination_file);
        if (F_status_is_error(*status)) {
          fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_dynamic_append_nulless", F_true);
          break;
        }

        *status = f_file_name_base(path_source.string, path_source.used, &destination_file);
        if (F_status_is_error(*status)) {
          fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "f_file_name_base", F_true);
          break;
        }

        *status = f_file_copy(path_source.string, destination_file.string, mode, f_file_default_read_size, F_false);

        if (F_status_is_error(*status)) {
          fake_print_error_operation(data.context, data.verbosity, F_status_set_fine(*status), "f_file_copy", "copy", "to", path_source.string, destination_file.string, F_true);
          break;
        }

        if (data.verbosity == fake_verbosity_verbose) {
          printf("Copied file '%s' to '%s'.%c", path_source.string, destination_file.string, f_string_eol[0]);
        }
      }
      else if (F_status_is_error(*status)) {
        fake_print_error_file(data.context, data.verbosity, F_status_set_fine(*status), "f_directory_is", path_source.string, "create", F_false, F_true);
        break;
      }

      *status = F_none;
    } // for

    f_macro_directory_statuss_delete_simple(failures);
    f_macro_string_dynamic_delete_simple(path_source);
    f_macro_string_dynamic_delete_simple(destination_file);

    if (F_status_is_fine(*status)) {
      fake_build_touch(data, file_stage, status);
    }
  }
#endif // _di_fake_build_copy_

#ifndef _di_fake_build_skeleton_
  void fake_build_skeleton(const fake_data data, const fake_build_setting setting, const mode_t mode, const f_string_static file_stage, f_status *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true) return;

    const f_string_static *directorys[] = {
      &data.path_build,
      &data.path_build_documents,
      &data.path_build_includes,
      &data.path_build_libraries,
      &data.path_build_libraries_script,
      &data.path_build_libraries_shared,
      &data.path_build_libraries_static,
      &data.path_build_objects,
      &data.path_build_process,
      &data.path_build_programs,
      &data.path_build_programs_script,
      &data.path_build_programs_shared,
      &data.path_build_programs_static,
      &data.path_build_settings,
      &data.path_build_stage,
    };

    if (data.verbosity != fake_verbosity_quiet) {
      printf("%cCreating base build directories.%c", f_string_eol[0], f_string_eol[0]);
    }

    for (uint8_t i = 0; i < 15; i++) {
      if (directorys[i]->used == 0) continue;

      *status = f_directory_create(directorys[i]->string, mode);

      if (F_status_is_error(*status)) {
        if (F_status_set_fine(*status) == F_file_found) continue;

        fake_print_error_file(data.context, data.verbosity, F_status_set_fine(*status), "f_directory_create", directorys[i]->string, "create", F_false, F_true);
        return;
      }

      if (data.verbosity == fake_verbosity_verbose) {
        printf("Created directory '%s'%c", directorys[i]->string, f_string_eol[0]);
      }
    } // for

    fake_build_touch(data, file_stage, status);
  }
#endif // _di_fake_build_skeleton_

#ifndef _di_fake_build_execute_process_script_
  void fake_build_execute_process_script(const fake_data data, const fake_build_setting setting, const f_string_static process_script, const f_string_static file_stage, f_status *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true) return;
    if (process_script.used == 0) return;

    f_string_dynamics arguments = f_string_dynamics_initialize;

    *status = fll_execute_arguments_add(fake_other_operation_build, fake_other_operation_build_length, &arguments);

    // ensure console color mode is passed to the scripts so that they can also react to color mode.
    if (!F_status_is_error(*status) && data.context.mode != f_color_mode_none) {
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

      *status = fll_execute_arguments_add(argument, 2, &arguments);
    }

    // ensure verbosity level is passed to the scripts so that they can also react to requested verbosity.
    if (!F_status_is_error(*status) && data.verbosity != fake_verbosity_normal) {
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

      *status = fll_execute_arguments_add(argument, 2, &arguments);
    }

    if (F_status_is_error(*status)) {
      fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);

      f_macro_string_dynamics_delete_simple(arguments);
      return;
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

      *status = fll_execute_arguments_add_parameter_set(parameters_prefix, parameters_prefix_length, parameters_name, parameters_name_length, parameters_value, parameters_value_length, 7, &arguments);

      if (F_status_is_error(*status)) {
        fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fll_execute_arguments_add_parameter_set", F_true);

        f_macro_string_dynamics_delete_simple(arguments);
        return;
      }
    }

    f_string_dynamic path = f_string_dynamic_initialize;
    f_string function = 0;

    {
      function = "fl_string_dynamic_append_nulless";

      if (process_script.string[0] != '/') {
        *status = fl_string_dynamic_append_nulless(data.path_data_build, &path);
      }

      if (!F_status_is_error(*status)) {
        *status = fl_string_dynamic_append_nulless(process_script, &path);
      }

      if (!F_status_is_error(*status)) {
        function = "fl_string_dynamic_terminate";
        *status = fl_string_dynamic_terminate(&path);
      }

      if (F_status_is_error(*status)) {
        fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), function, F_true);

        f_macro_string_dynamic_delete_simple(path);
        f_macro_string_dynamics_delete_simple(arguments);
        return;
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

        f_macro_string_dynamics_new(*status, names, 2);
        if (F_status_is_error(*status)) {
          fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "f_macro_string_dynamics_new", F_true);

          f_macro_string_dynamic_delete_simple(path);
          f_macro_string_dynamics_delete_simple(arguments);
          f_macro_string_dynamics_delete_simple(names);
          return;
        }

        f_string_dynamic part = f_string_dynamic_initialize;

        for (uint8_t i = 0; i < 2; i++) {
          *status = fl_string_append(variables_name[i], variables_length[i], &part);
          if (F_status_is_error(*status)) break;

          names.array[names.used].string = part.string;
          names.array[names.used].used = part.used;
          names.array[names.used].size = part.size;
          names.used++;

          f_macro_string_dynamic_clear(part);
        } // for

        if (!F_status_is_error(*status)) {
          if (names.used + setting.environment.used > names.size) {
            if (names.used + setting.environment.used > f_array_length_size) {
              if (data.verbosity != fake_verbosity_quiet) {
                fprintf(f_type_error, "%c", f_string_eol[0]);
                fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: The values for the setting '");
                fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", fake_build_setting_name_environment);
                fl_color_print(f_type_error, data.context.error, data.context.reset, "' of setting file '");
                fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", data.file_data_build_settings.string);
                fl_color_print_line(f_type_error, data.context.error, data.context.reset, "' is too large.");
              }

              f_macro_string_dynamic_delete_simple(part);
              f_macro_string_dynamics_delete_simple(arguments);
              f_macro_string_dynamics_delete_simple(names);
              *status = F_status_set_error(F_buffer_too_large);
              return;
            }

            f_macro_string_dynamics_resize(*status, names, names.used + setting.environment.used);
            if (F_status_is_error(*status)) {
              fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "f_macro_string_dynamics_resize", F_true);

              f_macro_string_dynamic_delete_simple(part);
              f_macro_string_dynamics_delete_simple(arguments);
              f_macro_string_dynamics_delete_simple(names);
              return;
            }
          }

          for (f_string_length i = 0; i < setting.environment.used; i++) {
            *status = fl_string_dynamic_append_nulless(setting.environment.array[i], &part);
            if (F_status_is_error(*status)) break;

            names.array[names.used].string = part.string;
            names.array[names.used].used = part.used;
            names.array[names.used].size = part.size;
            names.used++;

            f_macro_string_dynamic_clear(part);
          } // for
        }

        f_macro_string_dynamic_delete_simple(part);

        if (F_status_is_error(*status)) {
          fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_append", F_true);

          f_macro_string_dynamic_delete_simple(path);
          f_macro_string_dynamics_delete_simple(arguments);
          f_macro_string_dynamics_delete_simple(names);
          return;
        }
      }

      f_string_dynamics environment_names = f_string_dynamics_initialize;
      f_string_dynamics environment_values = f_string_dynamics_initialize;

      f_string_dynamic variable_name = f_string_dynamic_initialize;
      f_string_dynamic variable_value = f_string_dynamic_initialize;

      for (f_string_length i = 0; i < names.used; i++) {
        *status = f_environment_get_dynamic(names.array[i], &variable_value);
        if (F_status_is_error(*status)) {
          if (F_status_set_fine(*status) == F_memory_reallocation) {
            function = "f_macro_string_dynamics_resize";
            break;
          }
        }

        if (environment_names.used + 1 > environment_names.size) {
          f_macro_string_dynamics_resize(*status, environment_names, environment_names.size + f_memory_default_allocation_step);

          if (!F_status_is_error(*status)) {
            f_macro_string_dynamics_resize(*status, environment_values, environment_values.size + f_memory_default_allocation_step);
          }

          if (F_status_is_error(*status)) {
            function = "f_macro_string_dynamics_resize";
            break;
          }
        }

        *status = fl_string_dynamic_append(names.array[i], &variable_name);

        if (F_status_is_error(*status)) {
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

      if (F_status_is_error(*status)) {
        fake_print_error(data.context, data.verbosity, *status, function, F_true);

        f_macro_string_dynamic_delete_simple(variable_name);
        f_macro_string_dynamic_delete_simple(variable_value);
        f_macro_string_dynamics_delete_simple(environment_names);
        f_macro_string_dynamics_delete_simple(environment_values);
        f_macro_string_dynamic_delete_simple(path);
        f_macro_string_dynamics_delete_simple(arguments);
        return;
      }

      int result = 0;

      *status = fll_execute_path_environment(path.string, arguments, environment_names, environment_values, &result);

      f_macro_string_dynamics_delete_simple(environment_names);
      f_macro_string_dynamics_delete_simple(environment_values);
      f_macro_string_dynamics_delete_simple(arguments);
    }

    if (F_status_is_error(*status)) {
      if (F_status_set_fine(*status) == F_failure) {
        if (data.verbosity != fake_verbosity_quiet) {
          fprintf(f_type_error, "%c", f_string_eol[0]);
          fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: Failed to execute script: ");
          fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", path.string);
          fl_color_print_line(f_type_error, data.context.error, data.context.reset, ".");
        }
      }
      else {
        fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fll_execute_path_environment", F_true);
      }
    }
    else {
      fake_build_touch(data, file_stage, status);
    }

    f_macro_string_dynamic_delete_simple(path);
  }
#endif // _di_fake_build_execute_process_script_

#ifndef _di_fake_build_libraries_script_
  void fake_build_libraries_script(const fake_data data, const fake_build_setting setting, const f_mode mode, const f_string_static file_stage, f_status *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true) return;

    // @todo needs to perform some sort of regex replace on the library scripts.

    fake_build_touch(data, file_stage, status);
  }
#endif // _di_fake_build_libraries_script_

#ifndef _di_fake_build_libraries_shared_
  void fake_build_libraries_shared(const fake_data data, const fake_build_setting setting, const f_mode mode, const f_string_static file_stage, f_status *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true) return;

    // needs to strip the prefix and the filename extension '.c', '.cpp', etc.. to get the name." (call f_file_name_base() and then find last '.').

    // $compiler $sources -shared -Wl,-soname,lib$name.so.$major -o ${path_build}libraries/shared/lib$name.so.$major.$minor.$micro $arguments_shared $arguments_include $flags_all $arguments $flags_shared $flags_library
    // ln -vsf lib$name.so.$major.$minor.$micro ${path_build}libraries/shared/lib$name.so.$major
    // ln -vsf lib$name.so.$major ${path_build}libraries/shared/lib$name.so

    fake_build_touch(data, file_stage, status);
  }
#endif // _di_fake_build_libraries_shared_

#ifndef _di_fake_build_libraries_static_
  void fake_build_libraries_static(const fake_data data, const fake_build_setting setting, const f_mode mode, const f_string_static file_stage, f_status *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true) return;

    // needs to strip the prefix and the filename extension '.c', '.cpp', etc.. to get the name." (call f_file_name_base() and then find last '.').

    // $linker rcs ${path_build}libraries/static/lib$name.a $sources

    fake_build_touch(data, file_stage, status);
  }
#endif // _di_fake_build_libraries_static_

#ifndef _di_fake_build_objects_static_
  void fake_build_objects_static(const fake_data data, const fake_build_setting setting, const f_mode mode, const f_string_static file_stage, f_status *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true) return;

    // needs to strip the prefix and the filename extension '.c', '.cpp', etc.. to get the name." (call f_file_name_base() and then find last '.').

    // $compiler $path_c$i -c -static -o ${path_build}objects/$i.o $arguments_static $arguments_include $flags_all $arguments $flags_static $flags_library

    fake_build_touch(data, file_stage, status);
  }
#endif // _di_fake_build_objects_static_

#ifndef _di_fake_build_operate_
  f_return_status fake_build_operate(const fake_data data) {
    if (data.verbosity != fake_verbosity_quiet) {
      printf("%c", f_string_eol[0]);
      fl_color_print_line(f_type_output, data.context.important, data.context.reset, "Building project.");
    }

    f_status status = F_none;
    f_mode mode = f_mode_initialize;

    fake_build_setting setting = fake_build_setting_initialize;
    fake_build_stage stage = fake_build_stage_initialize;

    f_macro_mode_set_default_umask(mode, data.umask);

    fake_build_setting_load(data, &setting, &status);

    fake_build_stage_load(data, &stage, &status);

    fake_build_skeleton(data, setting, mode.directory, stage.file_skeleton, &status);

    fake_build_execute_process_script(data, setting, setting.process_pre, stage.file_process_pre, &status);

    fake_build_copy(data, mode, "setting files", data.path_data_settings, data.path_build_settings, setting.build_sources_setting, stage.file_sources_settings, &status);

    if (setting.build_language == fake_build_language_type_bash) {
      fake_build_libraries_script(data, setting, mode, stage.file_libraries_script, &status);

      fake_build_programs_script(data, setting, mode, stage.file_programs_script, &status);

      if (setting.build_script) {
        fake_build_copy(data, mode, "scripts", data.path_sources_script, data.path_build_programs_script, setting.build_sources_script, stage.file_sources_script, &status);
      }
    }
    else {
      const f_string_dynamic *path_sources = 0;

      if (setting.build_language == fake_build_language_type_c) {
        path_sources = &data.path_sources_c;
      }
      else if (setting.build_language == fake_build_language_type_cpp) {
        path_sources = &data.path_sources_cpp;
      }

      fake_build_copy(data, mode, "header files", *path_sources, data.path_build_includes, setting.build_sources_headers, stage.file_sources_headers, &status);

      if (setting.build_shared) {
        fake_build_libraries_shared(data, setting, mode, stage.file_libraries_shared, &status);

        fake_build_programs_shared(data, setting, mode, stage.file_programs_shared, &status);
      }

      if (setting.build_static) {
        fake_build_objects_static(data, setting, mode, stage.file_objects_static, &status);

        fake_build_libraries_static(data, setting, mode, stage.file_libraries_static, &status);

        fake_build_programs_static(data, setting, mode, stage.file_programs_static, &status);
      }

      if (setting.build_script) {
        fake_build_copy(data, mode, "scripts", data.path_sources_script, data.path_build_programs_script, setting.build_sources_script, stage.file_sources_script, &status);
      }
    }

    fake_build_execute_process_script(data, setting, setting.process_post, stage.file_process_post, &status);

    fake_macro_build_settings_delete_simple(setting);
    fake_macro_build_stage_delete_simple(stage);

    return status;
  }
#endif // _di_fake_build_operate_

#ifndef _di_fake_build_programs_script_
  void fake_build_programs_script(const fake_data data, const fake_build_setting setting, const f_mode mode, const f_string_static file_stage, f_status *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true) return;

    // @todo needs to perform some sort of regex replace on the program scripts.

    fake_build_touch(data, file_stage, status);
  }
#endif // _di_fake_build_programs_script_

#ifndef _di_fake_build_programs_shared_
  void fake_build_programs_shared(const fake_data data, const fake_build_setting setting, const f_mode mode, const f_string_static file_stage, f_status *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true) return;

    // needs to strip the prefix and the filename extension '.c', '.cpp', etc.. to get the name." (call f_file_name_base() and then find last '.').

    // $compiler $sources -o ${path_build}programs/shared/$name $arguments_shared $arguments_include $flags_all $arguments $flags_shared $flags_program

    fake_build_touch(data, file_stage, status);
  }
#endif // _di_fake_build_programs_shared_

#ifndef _di_fake_build_programs_static_
  void fake_build_programs_static(const fake_data data, const fake_build_setting setting, const f_mode mode, const f_string_static file_stage, f_status *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true) return;

    // needs to strip the prefix and the filename extension '.c', '.cpp', etc.. to get the name." (call f_file_name_base() and then find last '.').

    // $compiler -static -o ${path_build}programs/static/$name $sources $arguments_static $arguments_include $flags_all $arguments $flags_static $flags_program

    fake_build_touch(data, file_stage, status);
  }
#endif // _di_fake_build_programs_static_

#ifndef _di_fake_build_setting_load_
  void fake_build_setting_load(const fake_data data, fake_build_setting *setting, f_status *status) {
    if (F_status_is_error(*status)) return;

    f_file file = f_file_initialize;
    f_string_dynamic buffer = f_string_dynamic_initialize;

    *status = F_none;

    {
      f_string name_function = f_string_initialize;

      name_function = "f_file_exists";
      *status = f_file_exists(data.file_data_build_settings.string);

      if (*status == F_true) {
        name_function = "f_file_open";
        *status = f_file_open(data.file_data_build_settings.string, 0, &file);

        if (*status == F_none) {
          name_function = "f_file_read";
          *status = f_file_read(file, &buffer);

          f_file_close(&file.id);
        }
      }
      else if (*status == F_false) {
        *status = F_status_set_error(F_file_found_not);
      }

      if (F_status_is_error(*status)) {
        fake_print_error_file(data.context, data.verbosity, F_status_set_fine(*status), name_function, data.file_data_build_settings.string, "create", F_true, F_true);

        f_macro_string_dynamic_delete_simple(buffer);
        return;
      }
    }

    if (buffer.used > 0) {
      f_fss_objects objects = f_fss_objects_initialize;
      f_fss_contents contents = f_fss_contents_initialize;
      f_string_range range = f_string_range_initialize;
      bool error_printed = F_false;

      range.start = 0;
      range.stop = buffer.used - 1;

      *status = fll_fss_extended_read(&buffer, &range, &objects, &contents);

      if (F_status_is_error(*status)) {
        f_macro_fss_objects_delete_simple(objects);
        f_macro_fss_contents_delete_simple(contents);
        f_macro_string_dynamic_delete_simple(buffer);

        if (*status == F_status_set_error(F_incomplete_utf_stop)) {
          if (data.verbosity != fake_verbosity_quiet) {
            fprintf(f_type_error, "%c", f_string_eol[0]);
            fl_color_print(f_type_error, data.context.error, data.context.reset, "ENCODING ERROR: error occurred on invalid UTF-8 character at stop position (at ");
            fl_color_print(f_type_error, data.context.notable, data.context.reset, "%d", range.start);
            fl_color_print(f_type_error, data.context.error, data.context.reset, " of setting file '");
            fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", data.file_data_build_settings.string);
            fl_color_print_line(f_type_error, data.context.error, data.context.reset, "').");
          }
        }
        else if (*status == F_status_set_error(F_incomplete_utf_stop)) {
          if (data.verbosity != fake_verbosity_quiet) {
            fprintf(f_type_error, "%c", f_string_eol[0]);
            fl_color_print(f_type_error, data.context.error, data.context.reset, "ENCODING ERROR: error occurred on invalid UTF-8 character at end of string (at ");
            fl_color_print(f_type_error, data.context.notable, data.context.reset, "%d", range.start);
            fl_color_print(f_type_error, data.context.error, data.context.reset, " of setting file '");
            fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", data.file_data_build_settings.string);
            fl_color_print_line(f_type_error, data.context.error, data.context.reset, "').");
          }
        }
        else {
          fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fll_fss_extended_read", F_true);
        }

        f_macro_fss_objects_delete_simple(objects);
        f_macro_fss_contents_delete_simple(contents);
        f_macro_string_dynamic_delete_simple(buffer);

        return;
      }

      {
        const f_string settings_name[] = {
          fake_build_setting_name_build_compiler,
          fake_build_setting_name_build_language,
          fake_build_setting_name_build_libraries,
          fake_build_setting_name_build_linker,
          fake_build_setting_name_build_script,
          fake_build_setting_name_build_shared,
          fake_build_setting_name_build_sources_headers,
          fake_build_setting_name_build_sources_library,
          fake_build_setting_name_build_sources_program,
          fake_build_setting_name_build_sources_settings,
          fake_build_setting_name_build_sources_script,
          fake_build_setting_name_build_static,
          fake_build_setting_name_defines_all,
          fake_build_setting_name_defines_shared,
          fake_build_setting_name_defines_static,
          fake_build_setting_name_environment,
          fake_build_setting_name_flags_all,
          fake_build_setting_name_flags_library,
          fake_build_setting_name_flags_program,
          fake_build_setting_name_flags_shared,
          fake_build_setting_name_flags_static,
          fake_build_setting_name_modes,
          fake_build_setting_name_modes_default,
          fake_build_setting_name_path_headers,
          fake_build_setting_name_path_language,
          fake_build_setting_name_path_library_script,
          fake_build_setting_name_path_library_shared,
          fake_build_setting_name_path_library_static,
          fake_build_setting_name_path_program_script,
          fake_build_setting_name_path_program_shared,
          fake_build_setting_name_path_program_static,
          fake_build_setting_name_process_post,
          fake_build_setting_name_process_pre,
          fake_build_setting_name_project_level,
          fake_build_setting_name_project_name,
          fake_build_setting_name_version_major,
          fake_build_setting_name_version_micro,
          fake_build_setting_name_version_minor,
        };

        const f_string_length settings_length[] = {
          fake_build_setting_name_build_compiler_length,
          fake_build_setting_name_build_language_length,
          fake_build_setting_name_build_libraries_length,
          fake_build_setting_name_build_linker_length,
          fake_build_setting_name_build_script_length,
          fake_build_setting_name_build_shared_length,
          fake_build_setting_name_build_sources_headers_length,
          fake_build_setting_name_build_sources_library_length,
          fake_build_setting_name_build_sources_program_length,
          fake_build_setting_name_build_sources_settings_length,
          fake_build_setting_name_build_sources_script_length,
          fake_build_setting_name_build_static_length,
          fake_build_setting_name_defines_all_length,
          fake_build_setting_name_defines_shared_length,
          fake_build_setting_name_defines_static_length,
          fake_build_setting_name_environment_length,
          fake_build_setting_name_flags_all_length,
          fake_build_setting_name_flags_library_length,
          fake_build_setting_name_flags_program_length,
          fake_build_setting_name_flags_shared_length,
          fake_build_setting_name_flags_static_length,
          fake_build_setting_name_modes_length,
          fake_build_setting_name_modes_default_length,
          fake_build_setting_name_path_headers_length,
          fake_build_setting_name_path_language_length,
          fake_build_setting_name_path_library_script_length,
          fake_build_setting_name_path_library_shared_length,
          fake_build_setting_name_path_library_static_length,
          fake_build_setting_name_path_program_script_length,
          fake_build_setting_name_path_program_shared_length,
          fake_build_setting_name_path_program_static_length,
          fake_build_setting_name_process_post_length,
          fake_build_setting_name_process_pre_length,
          fake_build_setting_name_project_level_length,
          fake_build_setting_name_project_name_length,
          fake_build_setting_name_version_major_length,
          fake_build_setting_name_version_micro_length,
          fake_build_setting_name_version_minor_length,
        };

        f_string_dynamics build_language = f_string_dynamics_initialize;
        f_string_dynamics build_script = f_string_dynamics_initialize;
        f_string_dynamics build_shared = f_string_dynamics_initialize;
        f_string_dynamics build_static = f_string_dynamics_initialize;
        f_string_dynamics path_headers = f_string_dynamics_initialize;
        f_string_dynamics path_language = f_string_dynamics_initialize;
        f_string_dynamics path_library_script = f_string_dynamics_initialize;
        f_string_dynamics path_library_shared = f_string_dynamics_initialize;
        f_string_dynamics path_library_static = f_string_dynamics_initialize;
        f_string_dynamics path_program_script = f_string_dynamics_initialize;
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
          &setting->build_compiler,
          &build_language,
          &setting->build_libraries,
          &setting->build_linker,
          &build_script,
          &build_shared,
          &setting->build_sources_headers,
          &setting->build_sources_library,
          &setting->build_sources_program,
          &setting->build_sources_setting,
          &setting->build_sources_script,
          &build_static,
          &setting->defines_all,
          &setting->defines_shared,
          &setting->defines_static,
          &setting->environment,
          &setting->flags_all,
          &setting->flags_library,
          &setting->flags_program,
          &setting->flags_shared,
          &setting->flags_static,
          &setting->modes,
          &setting->modes_default,
          &path_headers,
          &path_language,
          &path_library_script,
          &path_library_shared,
          &path_library_static,
          &path_program_script,
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

        f_string function = "fll_fss_snatch_apart";

        *status = fll_fss_snatch_apart(buffer, objects, contents, settings_name, settings_length, settings_value, fake_build_setting_total);

        if (*status == F_none) {
          f_string_dynamic settings_mode_name_dynamic[fake_build_setting_total];
          f_string settings_mode_names[fake_build_setting_total];
          f_string_length setting_mode_lengths[fake_build_setting_total];

          const f_string_dynamics *modes = &setting->modes_default;
          bool found = F_false;

          f_array_length i = 0;
          f_array_length j = 0;

          // if any mode is specified, the entire defaults is replaced.
          if (data.mode.used > 0) {
            modes = &data.mode;
          }

          for (; i < modes->used; i++) {
            found = F_false;

            for (j = 0; j < setting->modes.used; j++) {
              if (fl_string_dynamic_compare_trim(modes->array[i], setting->modes.array[j]) == F_equal_to) {
                found = F_true;
                break;
              }
            } // for

            if (found == F_false) {
              if (data.verbosity != fake_verbosity_quiet) {
                fprintf(f_type_error, "%c", f_string_eol[0]);
                fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: the specified mode '");
                fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", modes->array[i].string);
                fl_color_print(f_type_error, data.context.error, data.context.reset, "' is not a valid mode, according to '");
                fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", data.file_data_build_settings.string);
                fl_color_print_line(f_type_error, data.context.error, data.context.reset, "'.");
              }

              error_printed = F_true;
              *status = F_status_set_error(F_parameter);
              break;
            }

            memset(&settings_mode_name_dynamic, 0, sizeof(f_string_dynamic) * fake_build_setting_total);
            memset(&settings_mode_names, 0, sizeof(f_string) * fake_build_setting_total);
            memset(&setting_mode_lengths, 0, sizeof(f_string_length) * fake_build_setting_total);

            for (j = 0; j < fake_build_setting_total; j++) {
              setting_mode_lengths[j] = settings_length[j] + 1 + modes->array[i].used;

              f_macro_string_dynamic_new(*status, settings_mode_name_dynamic[j], setting_mode_lengths[j]);
              if (F_status_is_error(*status)) {
                function = "f_macro_string_dynamic_new";
                break;
              }

              memcpy(settings_mode_name_dynamic[j].string, settings_name[j], settings_length[j]);
              memcpy(settings_mode_name_dynamic[j].string + settings_length[j] + 1, modes->array[i].string, modes->array[i].used);
              settings_mode_name_dynamic[j].string[settings_length[j]] = '-';

              settings_mode_names[j] = settings_mode_name_dynamic[j].string;
            } // for

            if (*status == F_none) {
              *status = fll_fss_snatch_apart(buffer, objects, contents, settings_mode_names, setting_mode_lengths, settings_value, fake_build_setting_total);

              if (F_status_is_error(*status)) {
                function = "fll_fss_snatch_apart";
              }
            }

            for (j = 0; j < fake_build_setting_total; j++) {
              f_macro_string_dynamic_delete_simple(settings_mode_name_dynamic[j]);
            } // for

            if (F_status_is_error(*status)) break;
          } // for
        }

        if (F_status_is_error(*status)) {
          if (*status == F_status_set_error(F_string_too_large)) {
            if (data.verbosity != fake_verbosity_quiet) {
              // @todo update FSS functions to return which setting index the problem happened on.
              fprintf(f_type_error, "%c", f_string_eol[0]);
              fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: a setting in the build setting file '");
              fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", data.file_data_build_settings.string);
              fl_color_print_line(f_type_error, data.context.error, data.context.reset, "' is too long.");
            }
          }
          else if (!error_printed) {
            fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), function, F_true);
          }
        }
        else {
          const f_string settings_single_name[] = {
            fake_build_setting_name_build_language,
            fake_build_setting_name_build_script,
            fake_build_setting_name_build_shared,
            fake_build_setting_name_build_static,
            fake_build_setting_name_path_headers,
            fake_build_setting_name_path_language,
            fake_build_setting_name_path_library_script,
            fake_build_setting_name_path_library_shared,
            fake_build_setting_name_path_library_static,
            fake_build_setting_name_path_program_script,
            fake_build_setting_name_path_program_shared,
            fake_build_setting_name_path_program_static,
            fake_build_setting_name_process_post,
            fake_build_setting_name_process_pre,
            fake_build_setting_name_project_level,
            fake_build_setting_name_project_name,
            fake_build_setting_name_version_major,
            fake_build_setting_name_version_micro,
            fake_build_setting_name_version_minor,
          };

          const f_string_statics *settings_single_source[] = {
            &build_language,
            &build_script,
            &build_shared,
            &build_static,
            &path_headers,
            &path_language,
            &path_library_script,
            &path_library_shared,
            &path_library_static,
            &path_program_script,
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

          uint8_t *settings_single_language[] = {
            &setting->build_language,
          };

          bool *settings_single_bool[] = {
            0,
            &setting->build_script,
            &setting->build_shared,
            &setting->build_static,
          };

          f_string_dynamic *settings_single_destination[] = {
            0,
            0,
            0,
            0,
            &setting->path_headers,
            &setting->path_language,
            &setting->path_library_script,
            &setting->path_library_shared,
            &setting->path_library_static,
            &setting->path_program_script,
            &setting->path_program_shared,
            &setting->path_program_static,
            &setting->process_post,
            &setting->process_pre,
            &setting->project_level,
            &setting->project_name,
            &setting->version_major,
            &setting->version_micro,
            &setting->version_minor,
          };

          uint8_t settings_single_type[] = {
            4,
            1,
            1,
            1,
            2,
            2,
            2,
            2,
            2,
            2,
            2,
            2,
            3,
            3,
            3,
            3,
            3,
            3,
            3,
          };

          for (f_array_length i = 0; i < 18; i++) {
            if (settings_single_source[i]->used == 0) continue;

            if (settings_single_source[i]->used > 1) {
              if (data.verbosity != fake_verbosity_quiet) {
                fprintf(f_type_warning, "%c", f_string_eol[0]);
                fl_color_print(f_type_warning, data.context.warning, data.context.reset, "WARNING: the setting '");
                fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s", settings_single_name[i]);
                fl_color_print(f_type_warning, data.context.warning, data.context.reset, "' in the file '");
                fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s", data.file_data_build_settings.string);
                fl_color_print(f_type_warning, data.context.warning, data.context.reset, "' may only have a single property, only using the first: '");
                fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s", settings_single_source[i]->array[0].string);
                fl_color_print_line(f_type_warning, data.context.warning, data.context.reset, "'.");
              }
            }

            if (settings_single_type[i] == 1) {
              if (fl_string_compare_trim(settings_single_source[i]->array[0].string, fake_build_setting_bool_yes, settings_single_source[i]->array[0].used, fake_build_setting_bool_yes_length) == F_equal_to) {
                *settings_single_bool[i] = F_true;
              }
              else if (fl_string_compare_trim(settings_single_source[i]->array[0].string, fake_build_setting_bool_no, settings_single_source[i]->array[0].used, fake_build_setting_bool_no_length) == F_equal_to) {
                *settings_single_bool[i] = F_false;
              }
              else {
                *settings_single_bool[i] = F_true;

                if (data.verbosity != fake_verbosity_quiet) {
                  fprintf(f_type_warning, "%c", f_string_eol[0]);
                  fl_color_print(f_type_warning, data.context.warning, data.context.reset, "WARNING: the setting '");
                  fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s", settings_single_name[i]);
                  fl_color_print(f_type_warning, data.context.warning, data.context.reset, "' in the file '");
                  fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s", data.file_data_build_settings.string);
                  fl_color_print(f_type_warning, data.context.warning, data.context.reset, "' may be either '");
                  fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s", fake_build_setting_bool_yes);
                  fl_color_print(f_type_warning, data.context.warning, data.context.reset, "' or '");
                  fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s", fake_build_setting_bool_no);
                  fl_color_print(f_type_warning, data.context.warning, data.context.reset, "', defaulting to '");
                  fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s", fake_build_setting_bool_yes);
                  fl_color_print_line(f_type_warning, data.context.warning, data.context.reset, "'.");
                }
              }
            }
            else if (settings_single_type[i] == 4) {
              if (fl_string_compare_trim(settings_single_source[i]->array[0].string, fake_build_language_bash, settings_single_source[i]->array[0].used, fake_build_language_bash_length) == F_equal_to) {
                *settings_single_language[i] = fake_build_language_type_bash;
              }
              else if (fl_string_compare_trim(settings_single_source[i]->array[0].string, fake_build_language_c, settings_single_source[i]->array[0].used, fake_build_language_c_length) == F_equal_to) {
                *settings_single_language[i] = fake_build_language_type_c;
              }
              else if (fl_string_compare_trim(settings_single_source[i]->array[0].string, fake_build_language_cpp, settings_single_source[i]->array[0].used, fake_build_language_cpp_length) == F_equal_to) {
                *settings_single_language[i] = fake_build_language_type_cpp;
              }
              else {
                *settings_single_language[i] = fake_build_language_type_c;

                if (data.verbosity != fake_verbosity_quiet) {
                  fprintf(f_type_warning, "%c", f_string_eol[0]);
                  fl_color_print(f_type_warning, data.context.warning, data.context.reset, "WARNING: the setting '");
                  fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s", settings_single_name[i]);
                  fl_color_print(f_type_warning, data.context.warning, data.context.reset, "' in the file '");
                  fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s", data.file_data_build_settings.string);
                  fl_color_print(f_type_warning, data.context.warning, data.context.reset, "' may only be one of '");
                  fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s", fake_build_language_bash);
                  fl_color_print(f_type_warning, data.context.warning, data.context.reset, "', '");
                  fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s", fake_build_language_c);
                  fl_color_print(f_type_warning, data.context.warning, data.context.reset, "', or '");
                  fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s", fake_build_language_cpp);
                  fl_color_print(f_type_warning, data.context.warning, data.context.reset, "', defaulting to '");
                  fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s", fake_build_language_c);
                  fl_color_print_line(f_type_warning, data.context.warning, data.context.reset, "'.");
                }
              }
            }
            else {
              *status = fl_string_dynamic_append_nulless(settings_single_source[i]->array[0], settings_single_destination[i]);
              if (F_status_is_error(*status)) {
                fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_dynamic_append_nulless", F_true);
                break;
              }

              if (settings_single_type[i] == 2) {
                *status = fl_string_append_assure(f_path_separator, f_path_separator_length, settings_single_destination[i]);
                if (F_status_is_error(*status)) {
                  fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_dynamic_append_nulless", F_true);
                  break;
                }
              }

              *status = fl_string_dynamic_terminate(settings_single_destination[i]);
              if (F_status_is_error(*status)) {
                fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_dynamic_terminate", F_true);
                break;
              }
            }
          } // for
        }

        f_macro_string_dynamics_delete_simple(build_language);
        f_macro_string_dynamics_delete_simple(build_script);
        f_macro_string_dynamics_delete_simple(build_shared);
        f_macro_string_dynamics_delete_simple(build_static);
        f_macro_string_dynamics_delete_simple(path_headers);
        f_macro_string_dynamics_delete_simple(path_language);
        f_macro_string_dynamics_delete_simple(path_library_script);
        f_macro_string_dynamics_delete_simple(path_library_shared);
        f_macro_string_dynamics_delete_simple(path_library_static);
        f_macro_string_dynamics_delete_simple(path_program_script);
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
  }
#endif // _di_fake_build_setting_load_

#ifndef _di_fake_build_stage_load_
  void fake_build_stage_load(const fake_data data, fake_build_stage *stage, f_status *status) {
    if (F_status_is_error(*status)) return;

    const f_string names[] = {
      fake_build_stage_libraries_script,
      fake_build_stage_libraries_shared,
      fake_build_stage_libraries_static,
      fake_build_stage_objects_static,
      fake_build_stage_process_post,
      fake_build_stage_process_pre,
      fake_build_stage_programs_script,
      fake_build_stage_programs_shared,
      fake_build_stage_programs_static,
      fake_build_stage_skeleton,
      fake_build_stage_sources_headers,
      fake_build_stage_sources_script,
      fake_build_stage_sources_settings,
    };

    const f_string_length lengths[] = {
      fake_build_stage_libraries_script_length,
      fake_build_stage_libraries_shared_length,
      fake_build_stage_libraries_static_length,
      fake_build_stage_objects_static_length,
      fake_build_stage_process_post_length,
      fake_build_stage_process_pre_length,
      fake_build_stage_programs_script_length,
      fake_build_stage_programs_shared_length,
      fake_build_stage_programs_static_length,
      fake_build_stage_skeleton_length,
      fake_build_stage_sources_headers_length,
      fake_build_stage_sources_script_length,
      fake_build_stage_sources_settings_length,
    };

    f_string_dynamic *values[] = {
      &stage->file_libraries_script,
      &stage->file_libraries_shared,
      &stage->file_libraries_static,
      &stage->file_objects_static,
      &stage->file_process_post,
      &stage->file_process_pre,
      &stage->file_programs_script,
      &stage->file_programs_shared,
      &stage->file_programs_static,
      &stage->file_skeleton,
      &stage->file_sources_headers,
      &stage->file_sources_script,
      &stage->file_sources_settings,
    };

    *status = F_none;

    for (uint8_t i = 0; i < fake_build_stage_total; i++) {
      *status = fl_string_dynamic_append_nulless(data.path_build_stage, values[i]);
      if (F_status_is_error(*status)) {
        fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_dynamic_append_nulless", F_true);
        break;
      }

      *status = fl_string_append_nulless(names[i], lengths[i], values[i]);
      if (F_status_is_error(*status)) {
        fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_dynamic_append_nulless", F_true);
        break;
      }

      *status = fl_string_dynamic_terminate(values[i]);
      if (F_status_is_error(*status)) {
        fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_dynamic_terminate", F_true);
        break;
      }
    } // for
  }
#endif // _di_fake_build_stage_load_

#ifndef _di_fake_build_touch_
  void fake_build_touch(const fake_data data, const f_string_dynamic file, f_status *status) {
    if (F_status_is_error(*status)) return;

    f_mode mode = f_mode_initialize;

    f_macro_mode_set_default_umask(mode, data.umask);

    *status = f_file_touch(file.string, mode.regular, F_false);

    if (F_status_is_error(*status)) {
      fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "f_file_touch", F_true);
    }
  }
#endif // _di_fake_build_touch_

#ifdef __cplusplus
} // extern "C"
#endif
