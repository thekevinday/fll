#include <level_3/fake.h>
#include "private-fake.h"
#include "private-build.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_arguments_standard_add_
  void fake_build_arguments_standard_add(const fake_data data, const fake_build_data data_build, const bool is_shared, const bool is_library, f_string_dynamics *arguments, f_status *status) {
    if (F_status_is_error(*status)) return;

    f_string_length build_libraries_length = fake_build_parameter_library_link_path_length + data.path_build_libraries_shared.used;

    char build_libraries[build_libraries_length + 1];

    memcpy(build_libraries, fake_build_parameter_library_link_path, fake_build_parameter_library_link_path_length);

    if (is_shared) {
      memcpy(build_libraries + fake_build_parameter_library_link_path_length, data.path_build_libraries_shared.string, data.path_build_libraries_shared.used);
    }
    else {
      memcpy(build_libraries + fake_build_parameter_library_link_path_length, data.path_build_libraries_static.string, data.path_build_libraries_static.used);
    }

    f_string_length build_includes_length = fake_build_parameter_library_include_length + data.path_build_includes.used;

    char build_includes[build_includes_length + 1];

    memcpy(build_includes, fake_build_parameter_library_include, fake_build_parameter_library_include_length);
    memcpy(build_includes + fake_build_parameter_library_include_length, data.path_build_includes.string, data.path_build_includes.used);

    const f_string values[] = {
      build_libraries,
      build_includes,
    };

    const f_string_length lengths[] = {
      build_libraries_length,
      build_includes_length,
    };

    for (uint8_t i = 0; i < 2; i++) {
      *status = fll_execute_arguments_add(values[i], lengths[i], arguments);
      if (F_status_is_error(*status)) break;
    } // for

    if (data.path_work.used > 0) {
      f_string_length length = 0;

      if (F_status_is_fine(*status)) {
        length = fake_build_parameter_library_include_length + data.path_work_includes.used;

        char string[length + 1];

        memcpy(string, fake_build_parameter_library_include, fake_build_parameter_library_include_length);
        memcpy(string + fake_build_parameter_library_include_length, data.path_work_includes.string, data.path_work_includes.used);

        string[length] = 0;

        *status = fll_execute_arguments_add(string, length, arguments);
      }

      if (data_build.setting.search_shared && (is_shared || !data_build.setting.search_exclusive) && F_status_is_fine(*status)) {
        length = fake_build_parameter_library_link_path_length + data.path_work_libraries_shared.used;

        char string[length + 1];

        memcpy(string, fake_build_parameter_library_link_path, fake_build_parameter_library_link_path_length);
        memcpy(string + fake_build_parameter_library_link_path_length, data.path_work_libraries_shared.string, data.path_work_libraries_shared.used);

        string[length] = 0;

        *status = fll_execute_arguments_add(string, length, arguments);
      }

      if (data_build.setting.search_static && (!is_shared || !data_build.setting.search_exclusive) && F_status_is_fine(*status)) {
        length = fake_build_parameter_library_link_path_length + data.path_work_libraries_static.used;

        char string[length + 1];

        memcpy(string, fake_build_parameter_library_link_path, fake_build_parameter_library_link_path_length);
        memcpy(string + fake_build_parameter_library_link_path_length, data.path_work_libraries_static.string, data.path_work_libraries_static.used);

        string[length] = 0;

        *status = fll_execute_arguments_add(string, length, arguments);
      }
    }

    if (F_status_is_fine(*status)) {
      for (f_array_length i = 0; i < data_build.setting.build_libraries.used; i++) {
        *status = fll_execute_arguments_add(data_build.setting.build_libraries.array[i].string, data_build.setting.build_libraries.array[i].used, arguments);
        if (F_status_is_error(*status)) break;
      } // for
    }

    for (f_array_length i = 0; i < data_build.setting.flags_all.used && F_status_is_fine(*status); i++) {
      *status = fll_execute_arguments_add(data_build.setting.flags_all.array[i].string, data_build.setting.flags_all.array[i].used, arguments);
      if (F_status_is_error(*status)) break;
    } // for

    for (f_array_length i = 0; i < data_build.setting.flags_shared.used && F_status_is_fine(*status); i++) {
      *status = fll_execute_arguments_add(data_build.setting.flags_shared.array[i].string, data_build.setting.flags_shared.array[i].used, arguments);
      if (F_status_is_error(*status)) break;
    } // for

    if (is_library) {
      for (f_array_length j = 0; j < data_build.setting.flags_library.used && F_status_is_fine(*status); j++) {
        *status = fll_execute_arguments_add(data_build.setting.flags_library.array[j].string, data_build.setting.flags_library.array[j].used, arguments);
        if (F_status_is_error(*status)) break;
      } // for
    }
    else {
      for (f_array_length i = 0; i < data_build.setting.flags_program.used && F_status_is_fine(*status); i++) {
        *status = fll_execute_arguments_add(data_build.setting.flags_program.array[i].string, data_build.setting.flags_program.array[i].used, arguments);
        if (F_status_is_error(*status)) break;
      } // for
    }
  }
#endif // _di_fake_build_arguments_standard_add_

#ifndef _di_fake_build_copy_
  void fake_build_copy(const fake_data data, const f_mode mode, const f_string label, const f_string_static source, const f_string_static destination, const f_string_statics files, const f_string_static file_stage, f_status *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true) return;

    f_directory_statuss failures = f_directory_statuss_initialize;
    f_string_dynamic path_source = f_string_dynamic_initialize;
    f_string_dynamic destination_file = f_string_dynamic_initialize;

    if (data.verbosity != fake_verbosity_quiet) {
      printf("%c", f_string_eol[0]);
      fl_color_print_line(f_type_output, data.context.important, data.context.reset, "Copying %s.", label);
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

      path_source.used = source.used;

      *status = fl_string_dynamic_append_nulless(files.array[i], &path_source);
      if (F_status_is_error(*status)) {
        fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_dynamic_append_nulless", F_true);
        break;
      }

      *status = fl_string_dynamic_terminate_after(&path_source);
      if (F_status_is_error(*status)) {
        fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_dynamic_terminate_after", F_true);
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

#ifndef _di_fake_build_execute_
  void fake_build_execute(const fake_data data, const fake_build_data data_build, const f_string_static program, const f_string_dynamics arguments, f_status *status) {
    if (F_status_is_error(*status)) return;

    if (data.verbosity == fake_verbosity_verbose) {
      printf("%s", program.string);

      for (f_array_length i = 0; i < arguments.used; i++) {
        if (arguments.array[i].used == 0) continue;

        printf(" %s", arguments.array[i].string);
      } // for

      printf("%c", f_string_eol[0]);

      // flush to stdout before executing command.
      fflush(f_type_output);
    }

    {
      int result = 0;

      *status = fll_execute_program_environment(program.string, arguments, data_build.environment.names, data_build.environment.values, &result);

      if (result != 0) {
        *status = F_status_set_error(F_failure);
      }
      else if (F_status_is_error(*status)) {
        if (F_status_set_fine(*status) == F_file_found_not) {
          if (data.verbosity != fake_verbosity_quiet) {
            fprintf(f_type_error, "%c", f_string_eol[0]);
            fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: failed to find program '");
            fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", program.string);
            fl_color_print_line(f_type_error, data.context.error, data.context.reset, "' for executing.");
          }
        }
        else {
          fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fll_execute_program_environment", F_true);
        }
      }
    }
  }
#endif // _di_fake_build_execute_

#ifndef _di_fake_build_skeleton_
  void fake_build_skeleton(const fake_data data, const fake_build_data data_build, const mode_t mode, const f_string_static file_stage, f_status *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true) return;

    f_string_static path_headers = f_string_static_initialize;
    f_string_length directory_headers_length = data.path_build_includes.used + data_build.setting.path_headers.used;

    char directory_headers[directory_headers_length + 1];

    if (data_build.setting.path_headers.used > 0) {
      memcpy(directory_headers, data.path_build_includes.string, data.path_build_includes.used);
      memcpy(directory_headers + data.path_build_includes.used, data_build.setting.path_headers.string, data_build.setting.path_headers.used);

      directory_headers[directory_headers_length] = 0;

      path_headers.string = directory_headers;
      path_headers.used = directory_headers_length;
      path_headers.size = directory_headers_length + 1;
    }
    else {
      directory_headers[0] = 0;

      path_headers.string = directory_headers;
      path_headers.used = 0;
      path_headers.size = directory_headers_length + 1;
    }

    const f_string_static *directorys[] = {
      &data.path_build,
      &data.path_build_documents,
      &data.path_build_includes,
      &data.path_build_libraries,
      &data.path_build_libraries_script,
      &data.path_build_libraries_shared,
      &data.path_build_libraries_static,
      &data.path_build_objects,
      &data.path_build_programs,
      &data.path_build_programs_script,
      &data.path_build_programs_shared,
      &data.path_build_programs_static,
      &data.path_build_settings,
      &data.path_build_stage,
      &path_headers,
    };

    if (data.verbosity != fake_verbosity_quiet) {
      printf("%c", f_string_eol[0]);
      fl_color_print_line(f_type_output, data.context.important, data.context.reset, "Creating base build directories.");
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
        printf("Created directory '%s'.%c", directorys[i]->string, f_string_eol[0]);
      }
    } // for

    fake_build_touch(data, file_stage, status);
  }
#endif // _di_fake_build_skeleton_

#ifndef _di_fake_build_execute_process_script_
  void fake_build_execute_process_script(const fake_data data, const fake_build_data data_build, const f_string_static process_script, const f_string_static file_stage, f_status *status) {
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
        function = "fl_string_dynamic_terminate_after";
        *status = fl_string_dynamic_terminate_after(&path);
      }

      if (F_status_is_error(*status)) {
        fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), function, F_true);

        f_macro_string_dynamic_delete_simple(path);
        f_macro_string_dynamics_delete_simple(arguments);
        return;
      }
    }

    {
      int result = 0;

      *status = fll_execute_path_environment(path.string, arguments, data_build.environment.names, data_build.environment.values, &result);

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

#ifndef _di_fake_build_get_file_name_without_extension_
  f_return_status fake_build_get_file_name_without_extension(const fake_data data, const f_string_static path, f_string_dynamic *name) {
    name->used = 0;

    if (path.used == 0) return F_none;

    f_status status = f_file_name_base(path.string, path.used, name);
    if (F_status_is_error(status)) {
      fake_print_error(data.context, data.verbosity, F_status_set_fine(status), "f_file_name_base", F_true);
      return status;
    }

    f_string_length i = name->used;

    for (; i > 0; i--) {
      if (name->string[i] == f_path_extension_separator[0]) {
        name->used = i;
        break;
      }
    } // for

    status = fl_string_dynamic_terminate_after(name);
    if (F_status_is_error(status)) {
      fake_print_error(data.context, data.verbosity, F_status_set_fine(status), "fl_string_dynamic_terminate_after", F_true);
      return status;
    }

    return F_none;
  }
#endif // _di_fake_build_get_file_name_without_extension_

#ifndef _di_fake_build_libraries_script_
  void fake_build_libraries_script(const fake_data data, const fake_build_data data_build, const f_mode mode, const f_string_static file_stage, f_status *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true) return;

    // @todo needs to perform some sort of regex replace on the library scripts.

    fake_build_touch(data, file_stage, status);
  }
#endif // _di_fake_build_libraries_script_

#ifndef _di_fake_build_libraries_shared_
  void fake_build_libraries_shared(const fake_data data, const fake_build_data data_build, const f_mode mode, const f_string_static file_stage, f_status *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true) return;
    if (!data_build.setting.build_sources_library.used) return;

    if (data.verbosity != fake_verbosity_quiet) {
      printf("%c", f_string_eol[0]);
      fl_color_print_line(f_type_output, data.context.important, data.context.reset, "Compiling shared library.");
    }

    f_string_dynamics arguments = f_string_dynamics_initialize;

    {
      const f_string_static *path_sources = &data.path_sources_c;

      if (data_build.setting.build_language == fake_build_language_type_cpp) {
        path_sources = &data.path_sources_cpp;
      }

      f_string_length source_length = 0;

      for (f_array_length i = 0; i < data_build.setting.build_sources_library.used; i++) {
        source_length = path_sources->used + data_build.setting.build_sources_library.array[i].used;

        char source[source_length + 1];

        memcpy(source, path_sources->string, path_sources->used);
        memcpy(source + path_sources->used, data_build.setting.build_sources_library.array[i].string, data_build.setting.build_sources_library.array[i].used);
        source[source_length] = 0;

        *status = fll_execute_arguments_add(source, source_length, &arguments);
        if (F_status_is_error(*status)) break;
      } // for

      if (F_status_is_error(*status)) {
        fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);

        f_macro_string_dynamics_delete_simple(arguments);
        return;
      }
    }

    f_string_length parameter_file_name_major_length = fake_build_parameter_library_name_prefix_length;
    f_string_length parameter_file_name_minor_length = fake_build_parameter_library_name_prefix_length;
    f_string_length parameter_file_name_micro_length = fake_build_parameter_library_name_prefix_length;

    parameter_file_name_micro_length += data_build.setting.project_name.used + fake_build_parameter_library_name_suffix_shared_length;
    parameter_file_name_micro_length += data_build.setting.version_major.used + fake_build_parameter_library_separator_length;
    parameter_file_name_major_length = parameter_file_name_micro_length;

    parameter_file_name_micro_length += data_build.setting.version_minor.used + fake_build_parameter_library_separator_length;
    parameter_file_name_minor_length = parameter_file_name_micro_length;

    parameter_file_name_micro_length += data_build.setting.version_micro.used;

    char parameter_file_name_major[parameter_file_name_major_length + 1];
    char parameter_file_name_minor[parameter_file_name_minor_length + 1];
    char parameter_file_name_micro[parameter_file_name_micro_length + 1];

    parameter_file_name_micro_length = 0;

    memcpy(parameter_file_name_major, fake_build_parameter_library_name_prefix, fake_build_parameter_library_name_prefix_length);
    memcpy(parameter_file_name_minor, fake_build_parameter_library_name_prefix, fake_build_parameter_library_name_prefix_length);
    memcpy(parameter_file_name_micro, fake_build_parameter_library_name_prefix, fake_build_parameter_library_name_prefix_length);
    parameter_file_name_micro_length += fake_build_parameter_library_name_prefix_length;

    memcpy(parameter_file_name_major + parameter_file_name_micro_length, data_build.setting.project_name.string, data_build.setting.project_name.used);
    memcpy(parameter_file_name_minor + parameter_file_name_micro_length, data_build.setting.project_name.string, data_build.setting.project_name.used);
    memcpy(parameter_file_name_micro + parameter_file_name_micro_length, data_build.setting.project_name.string, data_build.setting.project_name.used);
    parameter_file_name_micro_length += data_build.setting.project_name.used;

    memcpy(parameter_file_name_major + parameter_file_name_micro_length, fake_build_parameter_library_name_suffix_shared, fake_build_parameter_library_name_suffix_shared_length);
    memcpy(parameter_file_name_minor + parameter_file_name_micro_length, fake_build_parameter_library_name_suffix_shared, fake_build_parameter_library_name_suffix_shared_length);
    memcpy(parameter_file_name_micro + parameter_file_name_micro_length, fake_build_parameter_library_name_suffix_shared, fake_build_parameter_library_name_suffix_shared_length);
    parameter_file_name_micro_length += fake_build_parameter_library_name_suffix_shared_length;

    memcpy(parameter_file_name_major + parameter_file_name_micro_length, data_build.setting.version_major.string, data_build.setting.version_major.used);
    memcpy(parameter_file_name_minor + parameter_file_name_micro_length, data_build.setting.version_major.string, data_build.setting.version_major.used);
    memcpy(parameter_file_name_micro + parameter_file_name_micro_length, data_build.setting.version_major.string, data_build.setting.version_major.used);
    parameter_file_name_micro_length += data_build.setting.version_major.used;
    parameter_file_name_major_length = parameter_file_name_micro_length;

    memcpy(parameter_file_name_minor + parameter_file_name_micro_length, fake_build_parameter_library_separator, fake_build_parameter_library_separator_length);
    memcpy(parameter_file_name_micro + parameter_file_name_micro_length, fake_build_parameter_library_separator, fake_build_parameter_library_separator_length);
    parameter_file_name_micro_length += fake_build_parameter_library_separator_length;

    memcpy(parameter_file_name_minor + parameter_file_name_micro_length, data_build.setting.version_minor.string, data_build.setting.version_minor.used);
    memcpy(parameter_file_name_micro + parameter_file_name_micro_length, data_build.setting.version_minor.string, data_build.setting.version_minor.used);
    parameter_file_name_micro_length += data_build.setting.version_minor.used;
    parameter_file_name_minor_length = parameter_file_name_micro_length;

    memcpy(parameter_file_name_micro + parameter_file_name_micro_length, fake_build_parameter_library_separator, fake_build_parameter_library_separator_length);
    parameter_file_name_micro_length += fake_build_parameter_library_separator_length;

    memcpy(parameter_file_name_micro + parameter_file_name_micro_length, data_build.setting.version_micro.string, data_build.setting.version_micro.used);
    parameter_file_name_micro_length += data_build.setting.version_micro.used;

    parameter_file_name_major[parameter_file_name_major_length] = 0;
    parameter_file_name_minor[parameter_file_name_minor_length] = 0;
    parameter_file_name_micro[parameter_file_name_micro_length] = 0;

    {
      f_string_length parameter_file_path_length = data.path_build_libraries_shared.used + parameter_file_name_micro_length;

      char parameter_file_path[parameter_file_path_length + 1];

      memcpy(parameter_file_path, data.path_build_libraries_shared.string, data.path_build_libraries_shared.used);

      memcpy(parameter_file_path + data.path_build_libraries_shared.used, parameter_file_name_micro, parameter_file_name_micro_length);

      parameter_file_path[parameter_file_path_length] = 0;

      f_string_length parameter_linker_length = fake_build_parameter_library_shared_prefix_length + parameter_file_name_micro_length;

      char parameter_linker[parameter_linker_length + 1];

      memcpy(parameter_linker, fake_build_parameter_library_shared_prefix, fake_build_parameter_library_shared_prefix_length);

      memcpy(parameter_linker + fake_build_parameter_library_shared_prefix_length, parameter_file_name_micro, parameter_file_name_micro_length);

      parameter_linker[parameter_linker_length] = 0;

      const f_string values[] = {
        fake_build_parameter_library_shared,
        parameter_linker,
        fake_build_parameter_library_output,
        parameter_file_path,
      };

      const f_string_length lengths[] = {
        fake_build_parameter_library_shared_length,
        parameter_linker_length,
        fake_build_parameter_library_output_length,
        parameter_file_path_length,
      };

      for (uint8_t i = 0; i < 4; i++) {
        *status = fll_execute_arguments_add(values[i], lengths[i], &arguments);
        if (F_status_is_error(*status)) break;
      } // for

      fake_build_arguments_standard_add(data, data_build, F_true, F_true, &arguments, status);

      if (F_status_is_error(*status)) {
        fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);

        f_macro_string_dynamics_delete_simple(arguments);
        return;
      }
    }

    fake_build_execute(data, data_build, data_build.setting.build_compiler, arguments, status);

    f_macro_string_dynamics_delete_simple(arguments);

    if (F_status_is_error(*status)) return;

    {
      f_string_length parameter_file_path_length = data.path_build_libraries_shared.used + parameter_file_name_minor_length;

      char parameter_file_path[parameter_file_path_length + 1];

      memcpy(parameter_file_path, data.path_build_libraries_shared.string, data.path_build_libraries_shared.used);

      memcpy(parameter_file_path + data.path_build_libraries_shared.used, parameter_file_name_minor, parameter_file_name_minor_length);

      parameter_file_path[parameter_file_path_length] = 0;

      *status = f_file_link(parameter_file_name_micro, parameter_file_path);

      if (F_status_is_fine(*status) && data.verbosity == fake_verbosity_verbose) {
        printf("Linked file '%s' to '%s'.%c", parameter_file_path, parameter_file_name_micro, f_string_eol[0]);
      }
    }

    if (F_status_is_fine(*status)) {
      f_string_length parameter_file_path_length = data.path_build_libraries_shared.used + parameter_file_name_major_length;

      char parameter_file_path[parameter_file_path_length + 1];

      memcpy(parameter_file_path, data.path_build_libraries_shared.string, data.path_build_libraries_shared.used);

      memcpy(parameter_file_path + data.path_build_libraries_shared.used, parameter_file_name_major, parameter_file_name_major_length);

      parameter_file_path[parameter_file_path_length] = 0;

      *status = f_file_link(parameter_file_name_minor, parameter_file_path);

      if (F_status_is_fine(*status) && data.verbosity == fake_verbosity_verbose) {
        printf("Linked file '%s' to '%s'.%c", parameter_file_path, parameter_file_name_minor, f_string_eol[0]);
      }
    }

    if (F_status_is_error(*status)) {
      fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "f_file_link", F_true);
      return;
    }

    fake_build_touch(data, file_stage, status);
  }
#endif // _di_fake_build_libraries_shared_

#ifndef _di_fake_build_libraries_static_
  void fake_build_libraries_static(const fake_data data, const fake_build_data data_build, const f_mode mode, const f_string_static file_stage, f_status *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true) return;
    if (!data_build.setting.build_sources_library.used) return;

    if (data.verbosity != fake_verbosity_quiet) {
      printf("%c", f_string_eol[0]);
      fl_color_print_line(f_type_output, data.context.important, data.context.reset, "Compiling static library.");
    }

    f_string_dynamic file_name = f_string_dynamic_initialize;
    f_string_dynamic source_path = f_string_dynamic_initialize;
    f_string_dynamics arguments = f_string_dynamics_initialize;

    *status = fll_execute_arguments_add(fake_build_parameter_object_link_arguments, fake_build_parameter_object_link_arguments_length, &arguments);

    if (F_status_is_fine(*status)) {
      f_string_length destination_length = data.path_build_libraries_static.used + fake_build_parameter_library_name_prefix_length;
      destination_length += data_build.setting.project_name.used + fake_build_parameter_library_name_suffix_static_length;

      char destination[destination_length + 1];

      destination_length = 0;

      memcpy(destination, data.path_build_libraries_static.string, data.path_build_libraries_static.used);
      destination_length += data.path_build_libraries_static.used;

      memcpy(destination + destination_length, fake_build_parameter_library_name_prefix, fake_build_parameter_library_name_prefix_length);
      destination_length += fake_build_parameter_library_name_prefix_length;

      memcpy(destination + destination_length, data_build.setting.project_name.string, data_build.setting.project_name.used);
      destination_length += data_build.setting.project_name.used;

      memcpy(destination + destination_length, fake_build_parameter_library_name_suffix_static, fake_build_parameter_library_name_suffix_static_length);
      destination_length += fake_build_parameter_library_name_suffix_static_length;

      destination[destination_length] = 0;

      *status = fll_execute_arguments_add(destination, destination_length, &arguments);
    }

    if (F_status_is_fine(*status)) {
      f_string_length source_length = 0;

      for (f_array_length i = 0; i < data_build.setting.build_sources_library.used; i++) {
        source_path.used = 0;

        *status = fake_build_get_file_name_without_extension(data, data_build.setting.build_sources_library.array[i], &file_name);
        if (F_status_is_error(*status)) {
          fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fake_build_get_file_name_without_extension", F_true);

          f_macro_string_dynamic_delete_simple(file_name);
          f_macro_string_dynamic_delete_simple(source_path);
          f_macro_string_dynamics_delete_simple(arguments);
          return;
        }

        *status = f_file_name_directory(data_build.setting.build_sources_library.array[i].string, data_build.setting.build_sources_library.array[i].used, &source_path);
        if (F_status_is_error(*status)) {
          fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "f_file_name_directory", F_true);
          break;
        }

        if (source_path.used) {
          *status = fl_string_dynamic_prepend(data.path_build_objects, &source_path);
          if (F_status_is_error(*status)) {
            fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_dynamic_prepend", F_true);
            break;
          }

          *status = fl_string_append_assure(f_path_separator, f_path_separator_length, &source_path);
          if (F_status_is_error(*status)) {
            fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_append_assure", F_true);
            break;
          }

          *status = fl_string_dynamic_terminate_after(&source_path);
          if (F_status_is_error(*status)) {
            fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_dynamic_terminate_after", F_true);
            break;
          }

          source_length = source_path.used + file_name.used + fake_build_parameter_object_name_suffix_length;
        }
        else {
          source_length = data.path_build_objects.used + file_name.used + fake_build_parameter_object_name_suffix_length;
        }

        char source[source_length + 1];

        if (source_path.used) {
          memcpy(source, source_path.string, source_path.used);
          memcpy(source + source_path.used, file_name.string, file_name.used);
          memcpy(source + source_path.used + file_name.used, fake_build_parameter_object_name_suffix, fake_build_parameter_object_name_suffix_length);
        }
        else {
          memcpy(source, data.path_build_objects.string, data.path_build_objects.used);
          memcpy(source + data.path_build_objects.used, file_name.string, file_name.used);
          memcpy(source + data.path_build_objects.used + file_name.used, fake_build_parameter_object_name_suffix, fake_build_parameter_object_name_suffix_length);
        }

        source[source_length] = 0;

        *status = fll_execute_arguments_add(source, source_length, &arguments);
        if (F_status_is_error(*status)) break;
      } // for

      if (F_status_is_error(*status)) {
        fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);

        f_macro_string_dynamic_delete_simple(file_name);
        f_macro_string_dynamic_delete_simple(source_path);
        f_macro_string_dynamics_delete_simple(arguments);
        return;
      }
    }

    fake_build_execute(data, data_build, data_build.setting.build_linker, arguments, status);

    f_macro_string_dynamic_delete_simple(file_name);
    f_macro_string_dynamic_delete_simple(source_path);
    f_macro_string_dynamics_delete_simple(arguments);

    if (F_status_is_fine(*status)) {
      fake_build_touch(data, file_stage, status);
    }
  }
#endif // _di_fake_build_libraries_static_

#ifndef _di_fake_build_load_environment_
  void fake_build_load_environment(const fake_data data, const fake_build_data data_build, fake_build_environment *environment, f_status *status) {
    if (F_status_is_error(*status)) return;

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
        if (names.used + data_build.setting.environment.used > names.size) {
          if (names.used + data_build.setting.environment.used > f_array_length_size) {
            if (data.verbosity != fake_verbosity_quiet) {
              fprintf(f_type_error, "%c", f_string_eol[0]);
              fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: The values for the setting '");
              fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", fake_build_setting_name_environment);
              fl_color_print(f_type_error, data.context.error, data.context.reset, "' of setting file '");
              fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", data.file_data_build_settings.string);
              fl_color_print_line(f_type_error, data.context.error, data.context.reset, "' is too large.");
            }

            f_macro_string_dynamic_delete_simple(part);
            f_macro_string_dynamics_delete_simple(names);
            *status = F_status_set_error(F_buffer_too_large);
            return;
          }

          f_macro_string_dynamics_resize(*status, names, names.used + data_build.setting.environment.used);
          if (F_status_is_error(*status)) {
            fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "f_macro_string_dynamics_resize", F_true);

            f_macro_string_dynamic_delete_simple(part);
            f_macro_string_dynamics_delete_simple(names);
            return;
          }
        }

        for (f_string_length i = 0; i < data_build.setting.environment.used; i++) {
          *status = fl_string_dynamic_append_nulless(data_build.setting.environment.array[i], &part);
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

        f_macro_string_dynamics_delete_simple(names);
        return;
      }
    }

    f_string function = f_string_initialize;
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

      if (environment->names.used + 1 > environment->names.size) {
        f_macro_string_dynamics_resize(*status, environment->names, environment->names.size + f_memory_default_allocation_step);

        if (!F_status_is_error(*status)) {
          f_macro_string_dynamics_resize(*status, environment->values, environment->values.size + f_memory_default_allocation_step);
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

      environment->names.array[environment->names.used].string = variable_name.string;
      environment->names.array[environment->names.used].used = variable_name.used;
      environment->names.array[environment->names.used].size = variable_name.size;
      environment->names.used++;

      environment->values.array[environment->values.used].string = variable_value.string;
      environment->values.array[environment->values.used].used = variable_value.used;
      environment->values.array[environment->values.used].size = variable_value.size;
      environment->values.used++;

      f_macro_string_dynamic_clear(variable_name);
      f_macro_string_dynamic_clear(variable_value);
    } // for

    f_macro_string_dynamics_delete_simple(names);
    f_macro_string_dynamic_delete_simple(variable_name);
    f_macro_string_dynamic_delete_simple(variable_value);

    if (F_status_is_error(*status)) {
      fake_print_error(data.context, data.verbosity, *status, function, F_true);
    }
  }
#endif // _di_fake_build_load_environment_

#ifndef _di_fake_build_load_setting_
  void fake_build_load_setting(const fake_data data, fake_build_setting *setting, f_status *status) {
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
          fake_build_setting_name_search_exclusive,
          fake_build_setting_name_search_shared,
          fake_build_setting_name_search_static,
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
          fake_build_setting_name_search_exclusive_length,
          fake_build_setting_name_search_shared_length,
          fake_build_setting_name_search_static_length,
          fake_build_setting_name_version_major_length,
          fake_build_setting_name_version_micro_length,
          fake_build_setting_name_version_minor_length,
        };

        f_string_dynamics build_compiler = f_string_dynamics_initialize;
        f_string_dynamics build_language = f_string_dynamics_initialize;
        f_string_dynamics build_linker = f_string_dynamics_initialize;
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
        f_string_dynamics search_exclusive = f_string_dynamics_initialize;
        f_string_dynamics search_shared = f_string_dynamics_initialize;
        f_string_dynamics search_static = f_string_dynamics_initialize;
        f_string_dynamics version_major = f_string_dynamics_initialize;
        f_string_dynamics version_micro = f_string_dynamics_initialize;
        f_string_dynamics version_minor = f_string_dynamics_initialize;

        f_string_dynamics *settings_value[] = {
          &build_compiler,
          &build_language,
          &setting->build_libraries,
          &build_linker,
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
          &search_exclusive,
          &search_shared,
          &search_static,
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
            fake_build_setting_name_search_exclusive,
            fake_build_setting_name_search_shared,
            fake_build_setting_name_search_static,
            fake_build_setting_name_version_major,
            fake_build_setting_name_version_micro,
            fake_build_setting_name_version_minor,
          };

          const f_string_statics *settings_single_source[] = {
            &build_compiler,
            &build_language,
            &build_linker,
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
            &search_exclusive,
            &search_shared,
            &search_static,
            &version_major,
            &version_micro,
            &version_minor,
          };

          uint8_t *settings_single_language[] = {
            0,
            &setting->build_language,
          };

          bool *settings_single_bool[] = {
            0,
            0,
            0,
            &setting->build_script,
            &setting->build_shared,
            &setting->build_static,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            &setting->search_exclusive,
            &setting->search_shared,
            &setting->search_static,
          };

          f_string_dynamic *settings_single_destination[] = {
            &setting->build_compiler,
            0,
            &setting->build_linker,
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
            0,
            0,
            0,
            &setting->version_major,
            &setting->version_micro,
            &setting->version_minor,
          };

          // 1 = "yes" or "no", 2 = path/, 3 = literal, 4 = "bash", "c", or "c++".
          uint8_t settings_single_type[] = {
            3,
            4,
            3,
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
            1,
            1,
            1,
            3,
            3,
            3,
          };

          for (f_array_length i = 0; i < 24; i++) {
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
                  fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_append_assure", F_true);
                  break;
                }
              }

              *status = fl_string_dynamic_terminate_after(settings_single_destination[i]);
              if (F_status_is_error(*status)) {
                fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_dynamic_terminate_after", F_true);
                break;
              }
            }
          } // for
        }

        f_macro_string_dynamics_delete_simple(build_compiler);
        f_macro_string_dynamics_delete_simple(build_language);
        f_macro_string_dynamics_delete_simple(build_linker);
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
        f_macro_string_dynamics_delete_simple(search_exclusive);
        f_macro_string_dynamics_delete_simple(search_shared);
        f_macro_string_dynamics_delete_simple(search_static);
        f_macro_string_dynamics_delete_simple(version_major);
        f_macro_string_dynamics_delete_simple(version_micro);
        f_macro_string_dynamics_delete_simple(version_minor);
      }

      f_macro_fss_objects_delete_simple(objects);
      f_macro_fss_contents_delete_simple(contents);
    }

    f_macro_string_dynamic_delete_simple(buffer);

    if (F_status_is_error(*status)) return;

    // error when required settings are not specified.
    {
      bool failed = F_false;

      f_string_static *settings[] = {
        &setting->project_name,
      };

      f_string names[] = {
        fake_build_setting_name_project_name,
      };

      for (uint8_t i = 0; i < 1; i++) {
        if (settings[i]->used == 0) {
          fprintf(f_type_error, "%c", f_string_eol[0]);
          fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: the setting '");
          fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", names[i]);
          fl_color_print(f_type_error, data.context.error, data.context.reset, "' is required but is not specified in the settings file '");
          fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", data.file_data_build_settings.string);
          fl_color_print_line(f_type_error, data.context.error, data.context.reset, "'.");

          failed = F_true;
        }
      } // for

      if (failed) {
        *status = F_status_set_error(F_failure);
        return;
      }
    }

    // provide some defaults.
    {
      f_string sources[] = {
        fake_build_setting_default_version,
        fake_build_setting_default_version,
        fake_build_setting_default_version,
      };

      f_string_length lengths[] = {
        fake_build_setting_default_version_length,
        fake_build_setting_default_version_length,
        fake_build_setting_default_version_length,
      };

      f_string_dynamic *destinations[] = {
        &setting->version_major,
        &setting->version_minor,
        &setting->version_micro,
      };

      for (uint8_t i = 0; i < 3; i++) {
        if (destinations[i]->used > 0) continue;

        *status = fl_string_append_assure(sources[i], lengths[i], destinations[i]);
        if (F_status_is_error(*status)) {
          fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_append_assure", F_true);
          break;
        }

        *status = fl_string_dynamic_terminate_after(destinations[i]);
        if (F_status_is_error(*status)) {
          fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_dynamic_terminate_after", F_true);
          break;
        }
      } // for
    }

    // Override setting file when any of these are specified in the command line.
    if (F_status_is_fine(*status)) {
      if (data.parameters[fake_parameter_shared_disabled].result == f_console_result_found) {
        if (data.parameters[fake_parameter_shared_enabled].result == f_console_result_found) {
          if (data.parameters[fake_parameter_shared_enabled].location > data.parameters[fake_parameter_shared_disabled].location) {
            setting->build_shared = F_true;
            setting->search_shared = F_true;
          }
          else {
            setting->build_shared = F_false;
            setting->search_shared = F_false;
          }

          if (data.verbosity == fake_verbosity_verbose) {
            fprintf(f_type_warning, "%c", f_string_eol[0]);
            fl_color_print(f_type_warning, data.context.error, data.context.reset, "WARNING: the parameters '");
            fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s%s", f_console_symbol_long_enable, fake_long_shared_disabled);
            fl_color_print(f_type_warning, data.context.error, data.context.reset, "' and '");
            fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s%s", f_console_symbol_long_enable, fake_long_shared_enabled);
            fl_color_print(f_type_warning, data.context.error, data.context.reset, "' contradict, defaulting to '");

            if (setting->build_shared) {
              fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s%s", f_console_symbol_long_enable, fake_long_shared_enabled);
            }
            else {
              fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s%s", f_console_symbol_long_enable, fake_long_shared_disabled);
            }

            fl_color_print_line(f_type_warning, data.context.error, data.context.reset, "'.");
          }
        }
        else {
          setting->build_shared = F_false;
          setting->search_shared = F_false;
        }
      }
      else if (data.parameters[fake_parameter_shared_enabled].result == f_console_result_found) {
        setting->build_shared = F_true;
        setting->search_shared = F_true;
      }

      if (data.parameters[fake_parameter_static_disabled].result == f_console_result_found) {
        if (data.parameters[fake_parameter_static_enabled].result == f_console_result_found) {
          if (data.parameters[fake_parameter_static_enabled].location > data.parameters[fake_parameter_static_disabled].location) {
            setting->build_static = F_true;
            setting->search_static = F_true;
          }
          else {
            setting->build_static = F_false;
            setting->search_static = F_false;
          }

          if (data.verbosity == fake_verbosity_verbose) {
            fprintf(f_type_warning, "%c", f_string_eol[0]);
            fl_color_print(f_type_warning, data.context.error, data.context.reset, "WARNING: the parameters '");
            fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s%s", f_console_symbol_long_enable, fake_long_static_disabled);
            fl_color_print(f_type_warning, data.context.error, data.context.reset, "' and '");
            fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s%s", f_console_symbol_long_enable, fake_long_static_enabled);
            fl_color_print(f_type_warning, data.context.error, data.context.reset, "' contradict, defaulting to '");

            if (setting->build_static) {
              fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s%s", f_console_symbol_long_enable, fake_long_static_enabled);
            }
            else {
              fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s%s", f_console_symbol_long_enable, fake_long_static_disabled);
            }

            fl_color_print_line(f_type_warning, data.context.error, data.context.reset, "'.");
          }
        }
        else {
          setting->build_static = F_false;
          setting->search_static = F_false;
        }
      }
      else if (data.parameters[fake_parameter_static_enabled].result == f_console_result_found) {
        setting->build_static = F_true;
        setting->search_static = F_true;
      }

      if (setting->build_language == fake_build_language_type_c || setting->build_language == fake_build_language_type_cpp) {
        if (setting->build_shared == F_false && setting->build_static == F_false) {
          if (data.verbosity != fake_verbosity_quiet) {
            fprintf(f_type_error, "%c", f_string_eol[0]);
            fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: the build settings '");
            fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", fake_build_setting_name_build_shared);
            fl_color_print(f_type_error, data.context.error, data.context.reset, "' and '");
            fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", fake_build_setting_name_build_static);
            fl_color_print(f_type_error, data.context.error, data.context.reset, "' cannot both be false when using the language '");

            if (setting->build_language == fake_build_language_type_c) {
              fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", fake_build_language_c);
            }
            else {
              fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", fake_build_language_cpp);
            }

            fl_color_print_line(f_type_error, data.context.error, data.context.reset, "'.");
          }

          *status = F_status_set_error(F_failure);
        }
      }
    }
  }
#endif // _di_fake_build_load_setting_

#ifndef _di_fake_build_load_stage_
  void fake_build_load_stage(const fake_data data, fake_build_stage *stage, f_status *status) {
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

      *status = fl_string_dynamic_terminate_after(values[i]);
      if (F_status_is_error(*status)) {
        fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_dynamic_terminate_after", F_true);
        break;
      }
    } // for
  }
#endif // _di_fake_build_load_stage_

#ifndef _di_fake_build_objects_static_
  void fake_build_objects_static(const fake_data data, const fake_build_data data_build, const f_mode mode, const f_string_static file_stage, f_status *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true) return;
    if (!data_build.setting.build_sources_library.used) return;

    if (data.verbosity != fake_verbosity_quiet) {
      printf("%c", f_string_eol[0]);
      fl_color_print_line(f_type_output, data.context.important, data.context.reset, "Compiling static objects.");
    }

    f_string_dynamic file_name = f_string_dynamic_initialize;
    f_string_dynamic destination_path = f_string_dynamic_initialize;
    f_string_dynamics arguments = f_string_dynamics_initialize;
    f_string_length source_length = 0;
    f_string_length destination_length = 0;

    const f_string_static *path_sources = &data.path_sources_c;

    if (data_build.setting.build_language == fake_build_language_type_cpp) {
      path_sources = &data.path_sources_cpp;
    }

    for (f_array_length i = 0; i < data_build.setting.build_sources_library.used; i++) {
      file_name.used = 0;
      destination_path.used = 0;

      source_length = path_sources->used + data_build.setting.build_sources_library.array[i].used;

      char source[source_length + 1];

      memcpy(source, path_sources->string, path_sources->used);
      memcpy(source + path_sources->used, data_build.setting.build_sources_library.array[i].string, data_build.setting.build_sources_library.array[i].used);
      source[source_length] = 0;

      *status = fake_build_get_file_name_without_extension(data, data_build.setting.build_sources_library.array[i], &file_name);
      if (F_status_is_error(*status)) {
        fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fake_build_get_file_name_without_extension", F_true);

        f_macro_string_dynamic_delete_simple(file_name);
        f_macro_string_dynamic_delete_simple(destination_path);
        f_macro_string_dynamics_delete_simple(arguments);
        return;
      }

      *status = f_file_name_directory(data_build.setting.build_sources_library.array[i].string, data_build.setting.build_sources_library.array[i].used, &destination_path);
      if (F_status_is_error(*status)) {
        fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "f_file_name_directory", F_true);
        break;
      }

      if (destination_path.used) {
        *status = fl_string_dynamic_prepend(data.path_build_objects, &destination_path);
        if (F_status_is_error(*status)) {
          fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_dynamic_prepend", F_true);
          break;
        }

        *status = fl_string_append_assure(f_path_separator, f_path_separator_length, &destination_path);
        if (F_status_is_error(*status)) {
          fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_append_assure", F_true);
          break;
        }

        *status = fl_string_dynamic_terminate_after(&destination_path);
        if (F_status_is_error(*status)) {
          fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_dynamic_terminate_after", F_true);
          break;
        }

        *status = f_directory_exists(destination_path.string);

        if (*status == F_false) {
          if (data.verbosity != fake_verbosity_quiet) {
            fprintf(f_type_error, "%c", f_string_eol[0]);
            fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: The path '");
            fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", destination_path.string);
            fl_color_print_line(f_type_error, data.context.error, data.context.reset, "' exists but is not a directory.");
          }

          *status = F_status_set_error(F_failure);
          break;
        }
        else if (*status == F_file_found_not) {
          *status = f_directory_create(destination_path.string, mode.directory);

          if (F_status_is_error(*status)) {
            if (F_status_set_fine(*status) == F_file_found_not) {
              fprintf(f_type_error, "%c", f_string_eol[0]);
              fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: The path '");
              fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", destination_path.string);
              fl_color_print_line(f_type_error, data.context.error, data.context.reset, "' could not be created, a parent directory does not exist.");
            }
            else {
              fake_print_error_file(data.context, data.verbosity, F_status_set_fine(*status), "f_directory_create", destination_path.string, "create", F_false, F_true);
            }

            break;
          }

          if (data.verbosity == fake_verbosity_verbose) {
            printf("Directory '%s' created.%c", destination_path.string, f_string_eol[0]);
          }
        }
        else if (F_status_is_error(*status)) {
          fake_print_error_file(data.context, data.verbosity, F_status_set_fine(*status), "f_directory_exists", destination_path.string, "create", F_false, F_true);
          break;
        }

        destination_length = destination_path.used + file_name.used + fake_build_parameter_object_name_suffix_length;
      }
      else {
        destination_length = data.path_build_objects.used + file_name.used + fake_build_parameter_object_name_suffix_length;
      }

      char destination[destination_length + 1];

      if (destination_path.used) {
        memcpy(destination, destination_path.string, destination_path.used);
        memcpy(destination + destination_path.used, file_name.string, file_name.used);
        memcpy(destination + destination_path.used + file_name.used, fake_build_parameter_object_name_suffix, fake_build_parameter_object_name_suffix_length);
      }
      else {
        memcpy(destination, data.path_build_objects.string, data.path_build_objects.used);
        memcpy(destination + data.path_build_objects.used, file_name.string, file_name.used);
        memcpy(destination + data.path_build_objects.used + file_name.used, fake_build_parameter_object_name_suffix, fake_build_parameter_object_name_suffix_length);
      }

      destination[destination_length] = 0;

      const f_string values[] = {
        source,
        fake_build_parameter_object_compile,
        fake_build_parameter_object_static,
        fake_build_parameter_object_output,
        destination,
      };

      const f_string_length lengths[] = {
        source_length,
        fake_build_parameter_object_compile_length,
        fake_build_parameter_object_static_length,
        fake_build_parameter_object_output_length,
        destination_length,
      };

      for (uint8_t j = 0; j < 5; j++) {
        *status = fll_execute_arguments_add(values[j], lengths[j], &arguments);
        if (F_status_is_error(*status)) break;
      } // for

      fake_build_arguments_standard_add(data, data_build, F_false, F_true, &arguments, status);

      if (F_status_is_error(*status)) {
        fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);
        break;
      }

      fake_build_execute(data, data_build, data_build.setting.build_compiler, arguments, status);
      if (F_status_is_error(*status)) break;

      f_macro_string_dynamics_delete_simple(arguments);
    } // for

    f_macro_string_dynamic_delete_simple(file_name);
    f_macro_string_dynamic_delete_simple(destination_path);
    f_macro_string_dynamics_delete_simple(arguments);

    if (F_status_is_fine(*status)) {
      fake_build_touch(data, file_stage, status);
    }
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

    fake_build_data data_build = fake_build_data_initialize;
    fake_build_stage stage = fake_build_stage_initialize;

    f_macro_mode_set_default_umask(mode, data.umask);

    fake_build_load_setting(data, &data_build.setting, &status);

    fake_build_load_stage(data, &stage, &status);

    fake_build_load_environment(data, data_build, &data_build.environment, &status);

    fake_build_skeleton(data, data_build, mode.directory, stage.file_skeleton, &status);

    fake_build_execute_process_script(data, data_build, data_build.setting.process_pre, stage.file_process_pre, &status);

    fake_build_copy(data, mode, "setting files", data.path_data_settings, data.path_build_settings, data_build.setting.build_sources_setting, stage.file_sources_settings, &status);

    if (data_build.setting.build_language == fake_build_language_type_bash) {
      fake_build_libraries_script(data, data_build, mode, stage.file_libraries_script, &status);

      fake_build_programs_script(data, data_build, mode, stage.file_programs_script, &status);

      if (data_build.setting.build_script) {
        fake_build_copy(data, mode, "scripts", data.path_sources_script, data.path_build_programs_script, data_build.setting.build_sources_script, stage.file_sources_script, &status);
      }
    }
    else {
      if (data_build.setting.build_sources_headers.used) {
        const f_string_static *path_sources = &data.path_sources_c;

        if (data_build.setting.build_language == fake_build_language_type_cpp) {
          path_sources = &data.path_sources_cpp;
        }

        f_string_static path_headers = f_string_static_initialize;
        f_string_length directory_headers_length = data.path_build_includes.used + data_build.setting.path_headers.used;

        char directory_headers[directory_headers_length + 1];

        if (data_build.setting.path_headers.used > 0) {
          memcpy(directory_headers, data.path_build_includes.string, data.path_build_includes.used);
          memcpy(directory_headers + data.path_build_includes.used, data_build.setting.path_headers.string, data_build.setting.path_headers.used);

          directory_headers[directory_headers_length] = 0;

          path_headers.string = directory_headers;
          path_headers.used = directory_headers_length;
          path_headers.size = directory_headers_length + 1;
        }
        else {
          memcpy(directory_headers, data.path_build_includes.string, data.path_build_includes.used);

          directory_headers[directory_headers_length] = 0;

          path_headers.string = directory_headers;
          path_headers.used = directory_headers_length;
          path_headers.size = directory_headers_length + 1;
        }

        fake_build_copy(data, mode, "header files", *path_sources, path_headers, data_build.setting.build_sources_headers, stage.file_sources_headers, &status);
      }

      if (data_build.setting.build_shared) {
        fake_build_libraries_shared(data, data_build, mode, stage.file_libraries_shared, &status);

        fake_build_programs_shared(data, data_build, mode, stage.file_programs_shared, &status);
      }

      if (data_build.setting.build_static) {
        fake_build_objects_static(data, data_build, mode, stage.file_objects_static, &status);

        fake_build_libraries_static(data, data_build, mode, stage.file_libraries_static, &status);

        fake_build_programs_static(data, data_build, mode, stage.file_programs_static, &status);
      }

      if (data_build.setting.build_script) {
        fake_build_copy(data, mode, "scripts", data.path_sources_script, data.path_build_programs_script, data_build.setting.build_sources_script, stage.file_sources_script, &status);
      }
    }

    fake_build_execute_process_script(data, data_build, data_build.setting.process_post, stage.file_process_post, &status);

    fake_macro_build_data_delete_simple(data_build);
    fake_macro_build_stage_delete_simple(stage);

    return status;
  }
#endif // _di_fake_build_operate_

#ifndef _di_fake_build_programs_script_
  void fake_build_programs_script(const fake_data data, const fake_build_data data_build, const f_mode mode, const f_string_static file_stage, f_status *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true) return;

    // @todo needs to perform some sort of regex replace on the program scripts.

    fake_build_touch(data, file_stage, status);
  }
#endif // _di_fake_build_programs_script_

#ifndef _di_fake_build_programs_shared_
  void fake_build_programs_shared(const fake_data data, const fake_build_data data_build, const f_mode mode, const f_string_static file_stage, f_status *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true) return;
    if (!data_build.setting.build_sources_program.used) return;

    if (data.verbosity != fake_verbosity_quiet) {
      printf("%c", f_string_eol[0]);
      fl_color_print_line(f_type_output, data.context.important, data.context.reset, "Compiling shared program.");
    }

    f_string_dynamics arguments = f_string_dynamics_initialize;

    {
      const f_string_static *path_sources = &data.path_sources_c;

      if (data_build.setting.build_language == fake_build_language_type_cpp) {
        path_sources = &data.path_sources_cpp;
      }

      f_string_length source_length = 0;

      for (f_array_length i = 0; i < data_build.setting.build_sources_program.used; i++) {
        source_length = path_sources->used + data_build.setting.build_sources_program.array[i].used;

        char source[source_length + 1];

        memcpy(source, path_sources->string, path_sources->used);
        memcpy(source + path_sources->used, data_build.setting.build_sources_program.array[i].string, data_build.setting.build_sources_program.array[i].used);
        source[source_length] = 0;

        *status = fll_execute_arguments_add(source, source_length, &arguments);
        if (F_status_is_error(*status)) break;
      } // for
    }

    if (F_status_is_fine(*status)) {
      f_string_length parameter_file_name_path_length = data.path_build_programs_shared.used + data_build.setting.project_name.used;

      char parameter_file_name_path[parameter_file_name_path_length + 1];

      memcpy(parameter_file_name_path, data.path_build_programs_shared.string, data.path_build_programs_shared.used);
      memcpy(parameter_file_name_path + data.path_build_programs_shared.used, data_build.setting.project_name.string, data_build.setting.project_name.used);
      parameter_file_name_path[parameter_file_name_path_length] = 0;

      const f_string values[] = {
        fake_build_parameter_library_output,
        parameter_file_name_path,
      };

      const f_string_length lengths[] = {
        fake_build_parameter_library_output_length,
        parameter_file_name_path_length,
      };

      for (uint8_t i = 0; i < 2; i++) {
        *status = fll_execute_arguments_add(values[i], lengths[i], &arguments);
        if (F_status_is_error(*status)) break;
      } // for
    }

    // if project-specific library sources exist, then the -lproject_name needs to be added to the arguments.
    if (F_status_is_fine(*status) && data_build.setting.build_sources_library.used > 0) {
      f_string_length link_project_library_length = fake_build_parameter_library_link_file_length + data_build.setting.project_name.used;

      char link_project_library[link_project_library_length + 1];

      memcpy(link_project_library, fake_build_parameter_library_link_file, fake_build_parameter_library_link_file_length);
      memcpy(link_project_library + fake_build_parameter_library_link_file_length, data_build.setting.project_name.string, data_build.setting.project_name.used);
      link_project_library[link_project_library_length] = 0;

      *status = fll_execute_arguments_add(link_project_library, link_project_library_length, &arguments);
    }

    fake_build_arguments_standard_add(data, data_build, F_true, F_false, &arguments, status);

    if (F_status_is_error(*status)) {
      fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);

      f_macro_string_dynamics_delete_simple(arguments);
      return;
    }

    fake_build_execute(data, data_build, data_build.setting.build_compiler, arguments, status);

    f_macro_string_dynamics_delete_simple(arguments);

    if (F_status_is_fine(*status)) {
      fake_build_touch(data, file_stage, status);
    }
  }
#endif // _di_fake_build_programs_shared_

#ifndef _di_fake_build_programs_static_
  void fake_build_programs_static(const fake_data data, const fake_build_data data_build, const f_mode mode, const f_string_static file_stage, f_status *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true) return;
    if (!data_build.setting.build_sources_program.used) return;

    if (data.verbosity != fake_verbosity_quiet) {
      printf("%c", f_string_eol[0]);
      fl_color_print_line(f_type_output, data.context.important, data.context.reset, "Compiling static program.");
    }

    f_string_dynamics arguments = f_string_dynamics_initialize;

    {
      const f_string_static *path_sources = &data.path_sources_c;

      if (data_build.setting.build_language == fake_build_language_type_cpp) {
        path_sources = &data.path_sources_cpp;
      }

      f_string_length source_length = 0;

      for (f_array_length i = 0; i < data_build.setting.build_sources_program.used; i++) {
        if (!data_build.setting.build_sources_program.array[i].used) continue;

        source_length = path_sources->used + data_build.setting.build_sources_program.array[i].used;

        char source[source_length + 1];

        memcpy(source, path_sources->string, path_sources->used);
        memcpy(source + path_sources->used, data_build.setting.build_sources_program.array[i].string, data_build.setting.build_sources_program.array[i].used);
        source[source_length] = 0;

        *status = fll_execute_arguments_add(source, source_length, &arguments);
        if (F_status_is_error(*status)) break;
      } // for
    }

    if (F_status_is_fine(*status)) {
      f_string_length source_library_length = data.path_build_libraries_static.used + fake_build_parameter_library_name_prefix_length + data_build.setting.project_name.used + fake_build_parameter_library_name_suffix_static_length;

      char source_library[source_library_length + 1];

      source_library_length = 0;

      memcpy(source_library, data.path_build_libraries_static.string, data.path_build_libraries_static.used);
      source_library_length += data.path_build_libraries_static.used;

      memcpy(source_library + source_library_length, fake_build_parameter_library_name_prefix, fake_build_parameter_library_name_prefix_length);
      source_library_length += fake_build_parameter_library_name_prefix_length;

      memcpy(source_library + source_library_length, data_build.setting.project_name.string, data_build.setting.project_name.used);
      source_library_length += data_build.setting.project_name.used;

      memcpy(source_library + source_library_length, fake_build_parameter_library_name_suffix_static, fake_build_parameter_library_name_suffix_static_length);
      source_library_length += fake_build_parameter_library_name_suffix_static_length;

      source_library[source_library_length] = 0;

      f_string_length parameter_file_name_path_length = data.path_build_programs_static.used + data_build.setting.project_name.used;

      char parameter_file_name_path[parameter_file_name_path_length + 1];

      memcpy(parameter_file_name_path, data.path_build_programs_static.string, data.path_build_programs_static.used);
      memcpy(parameter_file_name_path + data.path_build_programs_static.used, data_build.setting.project_name.string, data_build.setting.project_name.used);
      parameter_file_name_path[parameter_file_name_path_length] = 0;

      const f_string values[] = {
        source_library,
        fake_build_parameter_library_static,
        fake_build_parameter_library_output,
        parameter_file_name_path,
      };

      const f_string_length lengths[] = {
        source_library_length,
        fake_build_parameter_library_static_length,
        fake_build_parameter_library_output_length,
        parameter_file_name_path_length,
      };

      for (uint8_t i = 0; i < 4; i++) {
        *status = fll_execute_arguments_add(values[i], lengths[i], &arguments);
        if (F_status_is_error(*status)) break;
      } // for
    }

    fake_build_arguments_standard_add(data, data_build, F_false, F_false, &arguments, status);

    if (F_status_is_error(*status)) {
      fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);

      f_macro_string_dynamics_delete_simple(arguments);
      return;
    }

    fake_build_execute(data, data_build, data_build.setting.build_compiler, arguments, status);

    f_macro_string_dynamics_delete_simple(arguments);

    if (F_status_is_fine(*status)) {
      fake_build_touch(data, file_stage, status);
    }
  }
#endif // _di_fake_build_programs_static_

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
