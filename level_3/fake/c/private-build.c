#include "fake.h"
#include "private-fake.h"
#include "private-build.h"
#include "private-make.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_arguments_standard_add_
  void fake_build_arguments_standard_add(const fake_data_t data, const fake_build_data_t data_build, const bool is_shared, const bool is_library, f_string_dynamics_t *arguments, f_status_t *status) {
    if (F_status_is_error(*status)) return;

    f_string_length_t build_libraries_length = fake_build_parameter_library_link_path_length + data.path_build_libraries_shared.used;

    char build_libraries[build_libraries_length + 1];

    memcpy(build_libraries, fake_build_parameter_library_link_path, fake_build_parameter_library_link_path_length);

    if (is_shared) {
      memcpy(build_libraries + fake_build_parameter_library_link_path_length, data.path_build_libraries_shared.string, data.path_build_libraries_shared.used);
    }
    else {
      memcpy(build_libraries + fake_build_parameter_library_link_path_length, data.path_build_libraries_static.string, data.path_build_libraries_static.used);
    }

    f_string_length_t build_includes_length = fake_build_parameter_library_include_length + data.path_build_includes.used;

    char build_includes[build_includes_length + 1];

    memcpy(build_includes, fake_build_parameter_library_include, fake_build_parameter_library_include_length);
    memcpy(build_includes + fake_build_parameter_library_include_length, data.path_build_includes.string, data.path_build_includes.used);

    const f_string_t values[] = {
      build_libraries,
      build_includes,
    };

    const f_string_length_t lengths[] = {
      build_libraries_length,
      build_includes_length,
    };

    for (uint8_t i = 0; i < 2; i++) {
      *status = fll_execute_arguments_add(values[i], lengths[i], arguments);
      if (F_status_is_error(*status)) break;
    } // for

    if (data.path_work.used > 0) {
      f_string_length_t length = 0;

      if (F_status_is_error_not(*status)) {
        length = fake_build_parameter_library_include_length + data.path_work_includes.used;

        char string[length + 1];

        memcpy(string, fake_build_parameter_library_include, fake_build_parameter_library_include_length);
        memcpy(string + fake_build_parameter_library_include_length, data.path_work_includes.string, data.path_work_includes.used);

        string[length] = 0;

        *status = fll_execute_arguments_add(string, length, arguments);
      }

      if (data_build.setting.search_shared && (is_shared || !data_build.setting.search_exclusive) && F_status_is_error_not(*status)) {
        length = fake_build_parameter_library_link_path_length + data.path_work_libraries_shared.used;

        char string[length + 1];

        memcpy(string, fake_build_parameter_library_link_path, fake_build_parameter_library_link_path_length);
        memcpy(string + fake_build_parameter_library_link_path_length, data.path_work_libraries_shared.string, data.path_work_libraries_shared.used);

        string[length] = 0;

        *status = fll_execute_arguments_add(string, length, arguments);
      }

      if (data_build.setting.search_static && (!is_shared || !data_build.setting.search_exclusive) && F_status_is_error_not(*status)) {
        length = fake_build_parameter_library_link_path_length + data.path_work_libraries_static.used;

        char string[length + 1];

        memcpy(string, fake_build_parameter_library_link_path, fake_build_parameter_library_link_path_length);
        memcpy(string + fake_build_parameter_library_link_path_length, data.path_work_libraries_static.string, data.path_work_libraries_static.used);

        string[length] = 0;

        *status = fll_execute_arguments_add(string, length, arguments);
      }
    }

    if (F_status_is_error_not(*status)) {
      for (f_array_length_t i = 0; i < data_build.setting.build_libraries.used; i++) {

        *status = fll_execute_arguments_add(data_build.setting.build_libraries.array[i].string, data_build.setting.build_libraries.array[i].used, arguments);
        if (F_status_is_error(*status)) break;
      } // for
    }

    for (f_array_length_t i = 0; i < data_build.setting.flags_all.used && F_status_is_error_not(*status); i++) {

      *status = fll_execute_arguments_add(data_build.setting.flags_all.array[i].string, data_build.setting.flags_all.array[i].used, arguments);
      if (F_status_is_error(*status)) break;
    } // for

    for (f_array_length_t i = 0; i < data_build.setting.flags_shared.used && F_status_is_error_not(*status); i++) {

      *status = fll_execute_arguments_add(data_build.setting.flags_shared.array[i].string, data_build.setting.flags_shared.array[i].used, arguments);
      if (F_status_is_error(*status)) break;
    } // for

    if (is_library) {
      for (f_array_length_t j = 0; j < data_build.setting.flags_library.used && F_status_is_error_not(*status); j++) {

        *status = fll_execute_arguments_add(data_build.setting.flags_library.array[j].string, data_build.setting.flags_library.array[j].used, arguments);
        if (F_status_is_error(*status)) break;
      } // for
    }
    else {
      for (f_array_length_t i = 0; i < data_build.setting.flags_program.used && F_status_is_error_not(*status); i++) {

        *status = fll_execute_arguments_add(data_build.setting.flags_program.array[i].string, data_build.setting.flags_program.array[i].used, arguments);
        if (F_status_is_error(*status)) break;
      } // for
    }

    if (data.define.used) {
      f_string_length_t length = 0;
      f_array_length_t i = 0;

      for (; i < data.define.used && F_status_is_error_not(*status); i++) {

        *status = fll_execute_arguments_add(data.define.array[i].string, data.define.array[i].used, arguments);
        if (F_status_is_error(*status)) break;
      } // for
    }
    else {
      f_string_length_t length = 0;
      f_array_length_t i = 0;

      for (; i < data_build.setting.defines_all.used && F_status_is_error_not(*status); i++) {

        *status = fll_execute_arguments_add(data_build.setting.defines_all.array[i].string, data_build.setting.defines_all.array[i].used, arguments);
        if (F_status_is_error(*status)) break;
      } // for

      if (is_shared) {
        for (i = 0; i < data_build.setting.defines_shared.used && F_status_is_error_not(*status); i++) {

          *status = fll_execute_arguments_add(data_build.setting.defines_shared.array[i].string, data_build.setting.defines_shared.array[i].used, arguments);
          if (F_status_is_error(*status)) break;
        } // for
      }
      else {
        for (i = 0; i < data_build.setting.defines_static.used && F_status_is_error_not(*status); i++) {

          *status = fll_execute_arguments_add(data_build.setting.defines_static.array[i].string, data_build.setting.defines_static.array[i].used, arguments);
          if (F_status_is_error(*status)) break;
        } // for
      }
    }
  }
#endif // _di_fake_build_arguments_standard_add_

#ifndef _di_fake_build_copy_
  void fake_build_copy(const fake_data_t data, const f_mode_t mode, const f_string_t label, const f_string_static_t source, const f_string_static_t destination, const f_string_statics_t files, const f_string_static_t file_stage, const f_string_length_t preserve, f_status_t *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true || *status == F_child) return;

    if (fake_signal_received(data)) {
      *status = F_status_set_error(F_signal);
      return;
    }

    f_directory_statuss_t failures = f_directory_statuss_t_initialize;
    f_string_dynamic_t path_source = f_string_dynamic_t_initialize;
    f_string_dynamic_t destination_file = f_string_dynamic_t_initialize;
    f_string_dynamic_t destination_directory = f_string_dynamic_t_initialize;

    if (data.error.verbosity != f_console_verbosity_quiet) {
      fprintf(data.output.stream, "%c", f_string_eol[0]);
      fl_color_print(data.output.stream, data.context.set.important, "Copying %s.", label);
      fprintf(data.output.stream, "%c", f_string_eol[0]);
    }

    f_macro_string_dynamic_t_new(*status, path_source, source.used);

    if (F_status_is_error(*status)) {
      fll_error_print(data.error, F_status_set_fine(*status), "f_macro_string_dynamic_t_new", F_true);

      fl_string_dynamic_delete(&path_source);
      return;
    }

    memcpy(path_source.string, source.string, source.used);

    fl_directory_recurse_t recurse = fl_directory_recurse_t_initialize;

    if (data.error.verbosity == f_console_verbosity_verbose) {
      recurse.output = data.output;
      recurse.verbose = fake_verbose_print_copy;
    }

    recurse.failures = &failures;

    for (f_array_length_t i = 0; i < files.used; i++) {
      if (!files.array[i].used) continue;

      path_source.used = source.used;

      *status = fl_string_dynamic_append_nulless(files.array[i], &path_source);

      if (F_status_is_error(*status)) {
        fll_error_print(data.error, F_status_set_fine(*status), "fl_string_dynamic_append_nulless", F_true);
        break;
      }

      *status = fl_string_dynamic_terminate_after(&path_source);

      if (F_status_is_error(*status)) {
        fll_error_print(data.error, F_status_set_fine(*status), "fl_string_dynamic_terminate_after", F_true);
        break;
      }

      if (fake_signal_received(data)) {
        *status = F_status_set_error(F_signal);
        break;
      }

      *status = f_directory_is(path_source.string);

      if (fake_signal_received(data)) {
        *status = F_status_set_error(F_signal);
        break;
      }

      if (*status == F_true) {
        destination_directory.used = 0;

        *status = fl_string_dynamic_append(destination, &destination_directory);

        if (F_status_is_error(*status)) {
          fll_error_print(data.error, F_status_set_fine(*status), "fl_string_dynamic_append", F_true);
          break;
        }

        *status = f_file_name_base(path_source.string, path_source.used, &destination_directory);

        if (F_status_is_error(*status)) {
          fll_error_print(data.error, F_status_set_fine(*status), "f_file_name_base", F_true);
          break;
        }

        *status = fl_string_dynamic_terminate_after(&destination_directory);

        if (F_status_is_error(*status)) {
          fll_error_print(data.error, F_status_set_fine(*status), "fl_string_dynamic_terminate_after", F_true);
          break;
        }

        *status = fl_directory_copy(path_source.string, destination_directory.string, path_source.used, destination_directory.used, mode, recurse);

        if (F_status_is_error(*status)) {
          if (data.error.verbosity == f_console_verbosity_verbose) {
            for (f_string_length_t j = 0; j < failures.used; j++) {
              fake_print_error_build_operation_file(data, F_status_set_fine(*status), "fl_directory_copy", "copy directory", "to", path_source.string, destination_directory.string, F_true);
            } // for

            if (F_status_set_fine(*status) != F_failure) {
              fll_error_print(data.error, F_status_set_fine(*status), "fl_directory_copy", F_true);
            }

            break;
          }
          else if (data.error.verbosity != f_console_verbosity_quiet) {
            fake_print_error_build_operation_file(data, F_status_set_fine(*status), "fl_directory_copy", "copy directory", "to", path_source.string, destination_directory.string, F_true);
          }

          break;
        }
      }
      else if (*status == F_false) {
        destination_file.used = 0;
        destination_directory.used = 0;

        *status = fl_string_dynamic_append_nulless(destination, &destination_file);

        if (F_status_is_error(*status)) {
          fll_error_print(data.error, F_status_set_fine(*status), "fl_string_dynamic_append_nulless", F_true);
          break;
        }

        if (preserve && preserve < path_source.used) {
          *status = fl_string_dynamic_append_nulless(destination, &destination_directory);

          if (F_status_is_error(*status)) {
            fll_error_print(data.error, F_status_set_fine(*status), "fl_string_dynamic_append_nulless", F_true);
            break;
          }

          *status = f_file_name_directory(path_source.string + preserve, path_source.used - preserve, &destination_directory);

          if (F_status_is_error(*status)) {
            fll_error_print(data.error, F_status_set_fine(*status), "f_file_name_directory", F_true);
            break;
          }

          *status = fl_string_dynamic_terminate_after(&destination_directory);

          if (F_status_is_error(*status)) {
            fll_error_print(data.error, F_status_set_fine(*status), "fl_string_dynamic_terminate_after", F_true);
            break;
          }

          *status = fl_directory_create(destination_directory.string, destination_directory.used, f_file_mode_all_rwx);

          if (F_status_is_error(*status)) {
            fll_error_file_print(data.error, F_status_set_fine(*status), "fl_directory_create", F_true, destination_directory.string, "create", fll_error_file_type_directory);
            break;
          }

          *status = fl_string_append(path_source.string + preserve, path_source.used - preserve, &destination_file);

          if (F_status_is_error(*status)) {
            fll_error_print(data.error, F_status_set_fine(*status), "fl_string_append", F_true);
            break;
          }
        }
        else {
          *status = f_file_name_base(path_source.string, path_source.used, &destination_file);

          if (F_status_is_error(*status)) {
            fll_error_print(data.error, F_status_set_fine(*status), "f_file_name_base", F_true);
            break;
          }
        }

        *status = fl_string_dynamic_terminate_after(&destination_file);

        if (F_status_is_error(*status)) {
          fll_error_print(data.error, F_status_set_fine(*status), "fl_string_dynamic_terminate_after", F_true);
          break;
        }

        if (fake_signal_received(data)) {
          *status = F_status_set_error(F_signal);
          break;
        }

        *status = f_file_copy(path_source.string, destination_file.string, mode, f_file_default_read_size, F_false);

        if (F_status_is_error(*status)) {
          fake_print_error_build_operation_file(data, F_status_set_fine(*status), "f_file_copy", "copy", "to", path_source.string, destination_file.string, F_true);
          break;
        }

        if (data.error.verbosity == f_console_verbosity_verbose) {
          fprintf(data.output.stream, "Copied file '%s' to '%s'.%c", path_source.string, destination_file.string, f_string_eol[0]);
        }
      }
      else if (F_status_is_error(*status)) {
        fll_error_file_print(data.error, F_status_set_fine(*status), "f_directory_is", F_true, path_source.string, "create", fll_error_file_type_file);
        break;
      }

      *status = F_none;
    } // for

    f_macro_directory_statuss_t_delete_simple(failures);
    fl_string_dynamic_delete(&path_source);
    fl_string_dynamic_delete(&destination_file);
    fl_string_dynamic_delete(&destination_directory);

    if (F_status_is_error_not(*status)) {
      fake_build_touch(data, file_stage, status);
    }
  }
#endif // _di_fake_build_copy_

#ifndef _di_fake_build_skeleton_
  void fake_build_skeleton(const fake_data_t data, const fake_build_data_t data_build, const mode_t mode, const f_string_static_t file_stage, f_status_t *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true || *status == F_child) return;

    if (fake_signal_received(data)) {
      *status = F_status_set_error(F_signal);
      return;
    }

    f_string_static_t path_headers = f_string_static_t_initialize;
    f_string_length_t directory_headers_length = data.path_build_includes.used + data_build.setting.path_headers.used;

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

    const f_string_static_t *directorys[] = {
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

    if (data.error.verbosity != f_console_verbosity_quiet) {
      fprintf(data.output.stream, "%c", f_string_eol[0]);
      fl_color_print(data.output.stream, data.context.set.important, "Creating base build directories.");
      fprintf(data.output.stream, "%c", f_string_eol[0]);
    }

    for (uint8_t i = 0; i < 15; i++) {

      if (!directorys[i]->used) continue;

      if (fake_signal_received(data)) {
        *status = F_status_set_error(F_signal);
        return;
      }

      *status = f_directory_create(directorys[i]->string, mode);

      if (F_status_is_error(*status)) {
        if (F_status_set_fine(*status) == F_file_found) {
          *status = F_none;
          continue;
        }

        fll_error_file_print(data.error, F_status_set_fine(*status), "f_directory_create", F_true, directorys[i]->string, "create", fll_error_file_type_directory);
        return;
      }

      if (data.error.verbosity == f_console_verbosity_verbose) {
        fprintf(data.output.stream, "Created directory '%s'.%c", directorys[i]->string, f_string_eol[0]);
      }
    } // for

    fake_build_touch(data, file_stage, status);
  }
#endif // _di_fake_build_skeleton_

#ifndef _di_fake_build_execute_process_script_
  int fake_build_execute_process_script(const fake_data_t data, const fake_build_data_t data_build, const f_string_static_t process_script, const f_string_static_t file_stage, f_status_t *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true || *status == F_child) return data.child;
    if (!process_script.used) return 0;

    if (fake_signal_received(data)) {
      *status = F_status_set_error(F_signal);
      return 0;
    }

    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;

    *status = fll_execute_arguments_add(fake_other_operation_build, fake_other_operation_build_length, &arguments);

    // ensure console color mode is passed to the scripts so that they can also react to color mode.
    if (F_status_is_error_not(*status) && data.context.mode != f_color_mode_none) {
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
    if (F_status_is_error_not(*status) && data.error.verbosity != f_console_verbosity_normal) {
      char argument[3] = { f_console_symbol_disable, 0, 0 };

      if (data.error.verbosity == f_console_verbosity_quiet) {
        argument[1] = f_console_standard_short_quiet[0];
      }
      else if (data.error.verbosity == f_console_verbosity_verbose) {
        argument[1] = f_console_standard_short_verbose[0];
      }
      else if (data.error.verbosity == f_console_verbosity_debug) {
        argument[1] = f_console_standard_short_debug[0];
      }

      *status = fll_execute_arguments_add(argument, 2, &arguments);
    }

    if (F_status_is_error(*status)) {
      fll_error_print(data.error, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);

      fl_string_dynamics_delete(&arguments);
      return 0;
    }

    {
      f_string_dynamic_t defines = f_string_dynamic_t_initialize;

      if (data.define.used) {
        for (f_array_length_t i = 0; i < data.define.used; i++) {

          *status = fl_string_dynamic_mash(" ", 1, data.define.array[i], &defines);

          if (F_status_is_error(*status)) {
            break;
          }
        } // for

        if (F_status_is_error(*status)) {
          fll_error_print(data.error, F_status_set_fine(*status), "fl_string_dynamic_mash", F_true);

          fl_string_dynamic_delete(&defines);
          fl_string_dynamics_delete(&arguments);
          return 0;
        }

        *status = fl_string_dynamic_terminate_after(&defines);

        if (F_status_is_error(*status)) {
          fll_error_print(data.error, F_status_set_fine(*status), "fl_string_dynamic_terminate_after", F_true);

          fl_string_dynamic_delete(&defines);
          fl_string_dynamics_delete(&arguments);
          return 0;
        }
      }

      const f_string_t parameters_prefix[] = {
        f_console_symbol_short_enable,
        f_console_symbol_short_enable,
        f_console_symbol_short_enable,
        f_console_symbol_short_enable,
        f_console_symbol_short_enable,
        f_console_symbol_short_enable,
        f_console_symbol_short_enable,
      };

      const f_string_length_t parameters_prefix_length[] = {
         f_console_symbol_short_enable_length,
         f_console_symbol_short_enable_length,
         f_console_symbol_short_enable_length,
         f_console_symbol_short_enable_length,
         f_console_symbol_short_enable_length,
         f_console_symbol_short_enable_length,
         f_console_symbol_short_enable_length,
      };

      const f_string_t parameters_name[] = {
        fake_short_define,
        fake_short_process,
        fake_short_settings,
        fake_short_path_build,
        fake_short_path_data,
        fake_short_path_sources,
        fake_short_path_work,
      };

      const f_string_length_t parameters_name_length[] = {
         fake_short_define_length,
         fake_short_process_length,
         fake_short_settings_length,
         fake_short_path_build_length,
         fake_short_path_data_length,
         fake_short_path_sources_length,
         fake_short_path_work_length,
      };

      const f_string_t parameters_value[] = {
        defines.string,
        data.process.string,
        data.settings.string,
        data.path_build.string,
        data.path_data.string,
        data.path_sources.string,
        data.path_work.string,
      };

      const f_string_length_t parameters_value_length[] = {
        defines.used,
        data.process.used,
        data.settings.used,
        data.path_build.used,
        data.path_data.used,
        data.path_sources.used,
        data.path_work.used,
      };

      *status = fll_execute_arguments_add_parameter_set(parameters_prefix, parameters_prefix_length, parameters_name, parameters_name_length, parameters_value, parameters_value_length, 7, &arguments);

      fl_string_dynamic_delete(&defines);

      if (F_status_is_error(*status)) {
        fll_error_print(data.error, F_status_set_fine(*status), "fll_execute_arguments_add_parameter_set", F_true);

        fl_string_dynamics_delete(&arguments);
        return 0;
      }
    }

    f_string_dynamic_t path = f_string_dynamic_t_initialize;
    f_string_t function = 0;

    {
      function = "fl_string_dynamic_append_nulless";

      if (process_script.string[0] != '/') {
        *status = fl_string_dynamic_append_nulless(data.path_data_build, &path);
      }

      if (F_status_is_error_not(*status)) {
        *status = fl_string_dynamic_append_nulless(process_script, &path);
      }

      if (F_status_is_error_not(*status)) {
        function = "fl_string_dynamic_terminate_after";
        *status = fl_string_dynamic_terminate_after(&path);
      }

      if (F_status_is_error(*status)) {
        fll_error_print(data.error, F_status_set_fine(*status), function, F_true);

        fl_string_dynamic_delete(&path);
        fl_string_dynamics_delete(&arguments);
        return 0;
      }
    }

    int return_code = 0;

    if (fake_signal_received(data)) {
      *status = F_status_set_error(F_signal);

      fl_string_dynamic_delete(&path);
      fl_string_dynamics_delete(&arguments);
    }
    else {
      // child processes should receive all signals, without blocking.
      f_signal_how_t signals = f_signal_how_t_initialize;
      f_signal_set_empty(&signals.block);
      f_signal_set_fill(&signals.block_not);

      fl_execute_parameter_t parameter = fl_macro_execute_parameter_t_initialize(fl_execute_parameter_option_path, &data_build.environment.names, &data_build.environment.values, &signals, 0);

      *status = fll_execute_program(path.string, arguments, &parameter, &return_code);

      fl_string_dynamics_delete(&arguments);

      if (fake_signal_received(data)) {
        *status = F_status_set_error(F_signal);
      }
      else if (*status != F_child) {
        if (F_status_is_error(*status)) {
          if (F_status_set_fine(*status) == F_failure) {
            if (data.error.verbosity != f_console_verbosity_quiet) {
              fprintf(data.error.to.stream, "%c", f_string_eol[0]);
              fl_color_print(data.error.to.stream, data.error.context, "%sFailed to execute script: ", data.error.prefix);
              fl_color_print(data.error.to.stream, data.error.notable, "%s", path.string);
              fl_color_print(data.error.to.stream, data.error.context, ".");
              fprintf(data.error.to.stream, "%c", f_string_eol[0]);
            }
          }
          else {
            fll_error_print(data.error, F_status_set_fine(*status), "fll_execute_program", F_true);
          }
        }
        else {
          fake_build_touch(data, file_stage, status);
        }
      }
    }

    fl_string_dynamic_delete(&path);

    return return_code;
  }
#endif // _di_fake_build_execute_process_script_

#ifndef _di_fake_build_get_file_name_without_extension_
  f_return_status fake_build_get_file_name_without_extension(const fake_data_t data, const f_string_static_t path, f_string_dynamic_t *name) {
    name->used = 0;

    if (!path.used) return F_none;

    f_status_t status = f_file_name_base(path.string, path.used, name);

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "f_file_name_base", F_true);
      return status;
    }

    f_string_length_t i = name->used;

    for (; i > 0; i--) {
      if (name->string[i] == f_path_extension_separator[0]) {
        name->used = i;
        break;
      }
    } // for

    status = fl_string_dynamic_terminate_after(name);

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_terminate_after", F_true);
      return status;
    }

    return F_none;
  }
#endif // _di_fake_build_get_file_name_without_extension_

#ifndef _di_fake_build_libraries_script_
  int fake_build_libraries_script(const fake_data_t data, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true || *status == F_child) return data.child;

    // @todo needs to perform some sort of regex replace on the library scripts.

    fake_build_touch(data, file_stage, status);

    return 0;
  }
#endif // _di_fake_build_libraries_script_

#ifndef _di_fake_build_library_shared_
  int fake_build_library_shared(const fake_data_t data, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true || *status == F_child) return data.child;
    if (!data_build.setting.build_sources_library.used) return 0;

    if (data.error.verbosity != f_console_verbosity_quiet) {
      fprintf(data.output.stream, "%c", f_string_eol[0]);
      fl_color_print(data.output.stream, data.context.set.important, "Compiling shared library.");
      fprintf(data.output.stream, "%c", f_string_eol[0]);
    }

    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;

    {
      const f_string_static_t *path_sources = &data.path_sources;

      if (data_build.setting.path_standard) {
        path_sources = &data.path_sources_c;

        if (data_build.setting.build_language == fake_build_language_type_cpp) {
          path_sources = &data.path_sources_cpp;
        }
      }
      else if (data.parameters[fake_parameter_path_sources].result != f_console_result_additional) {
        path_sources = &data_build.setting.path_sources;
      }

      f_string_length_t source_length = 0;

      for (f_array_length_t i = 0; i < data_build.setting.build_sources_library.used; i++) {

        source_length = path_sources->used + data_build.setting.build_sources_library.array[i].used;

        char source[source_length + 1];

        memcpy(source, path_sources->string, path_sources->used);
        memcpy(source + path_sources->used, data_build.setting.build_sources_library.array[i].string, data_build.setting.build_sources_library.array[i].used);
        source[source_length] = 0;

        *status = fll_execute_arguments_add(source, source_length, &arguments);
        if (F_status_is_error(*status)) break;
      } // for

      if (F_status_is_error(*status)) {
        fll_error_print(data.error, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);

        fl_string_dynamics_delete(&arguments);
        return 0;
      }
    }

    f_string_length_t parameter_file_name_length = fake_build_parameter_library_name_prefix_length;
    f_string_length_t parameter_file_name_major_length = fake_build_parameter_library_name_prefix_length;
    f_string_length_t parameter_file_name_minor_length = fake_build_parameter_library_name_prefix_length;
    f_string_length_t parameter_file_name_micro_length = fake_build_parameter_library_name_prefix_length;

    parameter_file_name_micro_length += data_build.setting.project_name.used + fake_build_parameter_library_name_suffix_shared_length;
    parameter_file_name_length = parameter_file_name_micro_length;

    parameter_file_name_micro_length += fake_build_parameter_library_separator_length + data_build.setting.version_major.used;
    parameter_file_name_major_length = parameter_file_name_micro_length;

    parameter_file_name_micro_length += fake_build_parameter_library_separator_length + data_build.setting.version_minor.used;
    parameter_file_name_minor_length = parameter_file_name_micro_length;

    parameter_file_name_micro_length += fake_build_parameter_library_separator_length + data_build.setting.version_micro.used;

    char parameter_file_name[parameter_file_name_length + 1];
    char parameter_file_name_major[parameter_file_name_major_length + 1];
    char parameter_file_name_minor[parameter_file_name_minor_length + 1];
    char parameter_file_name_micro[parameter_file_name_micro_length + 1];

    parameter_file_name_micro_length = 0;

    memcpy(parameter_file_name, fake_build_parameter_library_name_prefix, fake_build_parameter_library_name_prefix_length);
    memcpy(parameter_file_name_major, fake_build_parameter_library_name_prefix, fake_build_parameter_library_name_prefix_length);
    memcpy(parameter_file_name_minor, fake_build_parameter_library_name_prefix, fake_build_parameter_library_name_prefix_length);
    memcpy(parameter_file_name_micro, fake_build_parameter_library_name_prefix, fake_build_parameter_library_name_prefix_length);
    parameter_file_name_micro_length += fake_build_parameter_library_name_prefix_length;

    memcpy(parameter_file_name + parameter_file_name_micro_length, data_build.setting.project_name.string, data_build.setting.project_name.used);
    memcpy(parameter_file_name_major + parameter_file_name_micro_length, data_build.setting.project_name.string, data_build.setting.project_name.used);
    memcpy(parameter_file_name_minor + parameter_file_name_micro_length, data_build.setting.project_name.string, data_build.setting.project_name.used);
    memcpy(parameter_file_name_micro + parameter_file_name_micro_length, data_build.setting.project_name.string, data_build.setting.project_name.used);
    parameter_file_name_micro_length += data_build.setting.project_name.used;

    memcpy(parameter_file_name + parameter_file_name_micro_length, fake_build_parameter_library_name_suffix_shared, fake_build_parameter_library_name_suffix_shared_length);
    memcpy(parameter_file_name_major + parameter_file_name_micro_length, fake_build_parameter_library_name_suffix_shared, fake_build_parameter_library_name_suffix_shared_length);
    memcpy(parameter_file_name_minor + parameter_file_name_micro_length, fake_build_parameter_library_name_suffix_shared, fake_build_parameter_library_name_suffix_shared_length);
    memcpy(parameter_file_name_micro + parameter_file_name_micro_length, fake_build_parameter_library_name_suffix_shared, fake_build_parameter_library_name_suffix_shared_length);
    parameter_file_name_micro_length += fake_build_parameter_library_name_suffix_shared_length;

    memcpy(parameter_file_name_major + parameter_file_name_micro_length, fake_build_parameter_library_separator, fake_build_parameter_library_separator_length);
    memcpy(parameter_file_name_minor + parameter_file_name_micro_length, fake_build_parameter_library_separator, fake_build_parameter_library_separator_length);
    memcpy(parameter_file_name_micro + parameter_file_name_micro_length, fake_build_parameter_library_separator, fake_build_parameter_library_separator_length);
    parameter_file_name_micro_length += fake_build_parameter_library_separator_length;

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

    parameter_file_name[parameter_file_name_length] = 0;
    parameter_file_name_major[parameter_file_name_major_length] = 0;
    parameter_file_name_minor[parameter_file_name_minor_length] = 0;
    parameter_file_name_micro[parameter_file_name_micro_length] = 0;

    {
      f_string_length_t parameter_file_path_length = data.path_build_libraries_shared.used + parameter_file_name_micro_length;

      char parameter_file_path[parameter_file_path_length + 1];

      memcpy(parameter_file_path, data.path_build_libraries_shared.string, data.path_build_libraries_shared.used);
      memcpy(parameter_file_path + data.path_build_libraries_shared.used, parameter_file_name_micro, parameter_file_name_micro_length);

      parameter_file_path[parameter_file_path_length] = 0;

      f_string_length_t parameter_linker_length = fake_build_parameter_library_shared_prefix_length;

      if (data_build.setting.version_target == fake_build_version_type_major) {
        parameter_linker_length += parameter_file_name_major_length;
      }
      else if (data_build.setting.version_target == fake_build_version_type_minor) {
        parameter_linker_length += parameter_file_name_minor_length;
      }
      else if (data_build.setting.version_target == fake_build_version_type_micro) {
        parameter_linker_length += parameter_file_name_micro_length;
      }

      char parameter_linker[parameter_linker_length + 1];

      memcpy(parameter_linker, fake_build_parameter_library_shared_prefix, fake_build_parameter_library_shared_prefix_length);

      if (data_build.setting.version_target == fake_build_version_type_major) {
        memcpy(parameter_linker + fake_build_parameter_library_shared_prefix_length, parameter_file_name_major, parameter_file_name_major_length);
      }
      else if (data_build.setting.version_target == fake_build_version_type_minor) {
        memcpy(parameter_linker + fake_build_parameter_library_shared_prefix_length, parameter_file_name_minor, parameter_file_name_minor_length);
      }
      else if (data_build.setting.version_target == fake_build_version_type_micro) {
        memcpy(parameter_linker + fake_build_parameter_library_shared_prefix_length, parameter_file_name_micro, parameter_file_name_micro_length);
      }

      parameter_linker[parameter_linker_length] = 0;

      const f_string_t values[] = {
        fake_build_parameter_library_shared,
        parameter_linker,
        fake_build_parameter_library_output,
        parameter_file_path,
      };

      const f_string_length_t lengths[] = {
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
        fll_error_print(data.error, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);

        fl_string_dynamics_delete(&arguments);
        return 0;
      }
    }

    {
      const int result = fake_execute(data, data_build.environment, data_build.setting.build_compiler, arguments, status);

      fl_string_dynamics_delete(&arguments);

      if (F_status_is_error(*status)) {
        return 0;
      }

      if (*status == F_child) {
        return result;
      }
    }

    if (data_build.setting.version_target != fake_build_version_type_micro) {
      f_string_length_t parameter_file_path_length = data.path_build_libraries_shared.used;

      if (data_build.setting.version_target == fake_build_version_type_major) {
        parameter_file_path_length += parameter_file_name_major_length;
      }
      else {
        parameter_file_path_length += parameter_file_name_minor_length;
      }

      char parameter_file_path[parameter_file_path_length + 1];

      memcpy(parameter_file_path, data.path_build_libraries_shared.string, data.path_build_libraries_shared.used);

      if (data_build.setting.version_target == fake_build_version_type_major) {
        memcpy(parameter_file_path + data.path_build_libraries_shared.used, parameter_file_name_major, parameter_file_name_major_length);
      }
      else {
        memcpy(parameter_file_path + data.path_build_libraries_shared.used, parameter_file_name_minor, parameter_file_name_minor_length);
      }

      parameter_file_path[parameter_file_path_length] = 0;


      if (fake_signal_received(data)) {
        *status = F_status_set_error(F_signal);
        return 0;
      }

      *status = f_file_link(parameter_file_name_micro, parameter_file_path);

      if (F_status_is_error_not(*status) && data.error.verbosity == f_console_verbosity_verbose) {
        fprintf(data.output.stream, "Linked file '%s' to '%s'.%c", parameter_file_path, parameter_file_name_micro, f_string_eol[0]);
      }
      else if (F_status_is_error(*status)) {
        if (F_status_set_fine(*status) == F_file_found) {
          fll_error_file_print(data.error, F_status_set_fine(*status), "f_file_link", F_true, parameter_file_path, "link", fll_error_file_type_file);
          return 0;
        }

        fll_error_file_print(data.error, F_status_set_fine(*status), "f_file_link", F_true, parameter_file_name_micro, "link", fll_error_file_type_file);
        return 0;
      }
    }

    if (F_status_is_error_not(*status)) {
      f_string_length_t parameter_file_path_length = data.path_build_libraries_shared.used + parameter_file_name_length;

      char parameter_file_path[parameter_file_path_length + 1];

      memcpy(parameter_file_path, data.path_build_libraries_shared.string, data.path_build_libraries_shared.used);

      memcpy(parameter_file_path + data.path_build_libraries_shared.used, parameter_file_name, parameter_file_name_length);

      parameter_file_path[parameter_file_path_length] = 0;

      if (fake_signal_received(data)) {
        *status = F_status_set_error(F_signal);
        return 0;
      }

      if (data_build.setting.version_target == fake_build_version_type_major) {
        *status = f_file_link(parameter_file_name_major, parameter_file_path);
      }
      else if (data_build.setting.version_target == fake_build_version_type_minor) {
        *status = f_file_link(parameter_file_name_minor, parameter_file_path);
      }
      else if (data_build.setting.version_target == fake_build_version_type_micro) {
        *status = f_file_link(parameter_file_name_micro, parameter_file_path);
      }

      if (F_status_is_error_not(*status) && data.error.verbosity == f_console_verbosity_verbose) {
        fprintf(data.output.stream, "Linked file '%s' to '", parameter_file_path);

        if (data_build.setting.version_target == fake_build_version_type_major) {
          fprintf(data.output.stream, "%s", parameter_file_name_major);
        }
        else if (data_build.setting.version_target == fake_build_version_type_minor) {
          fprintf(data.output.stream, "%s", parameter_file_name_minor);
        }
        else if (data_build.setting.version_target == fake_build_version_type_micro) {
          fprintf(data.output.stream, "%s", parameter_file_name_micro);
        }

        fprintf(data.output.stream, "'.%c", f_string_eol[0]);
      }
      else if (F_status_is_error(*status)) {
        if (F_status_set_fine(*status) == F_file_found) {
          fll_error_file_print(data.error, F_status_set_fine(*status), "f_file_link", F_true, parameter_file_path, "link", fll_error_file_type_file);

          return 0;
        }

        if (data_build.setting.version_target == fake_build_version_type_major) {
          fll_error_file_print(data.error, F_status_set_fine(*status), "f_file_link", F_true, parameter_file_name_major, "link", fll_error_file_type_file);
        }
        else if (data_build.setting.version_target == fake_build_version_type_minor) {
          fll_error_file_print(data.error, F_status_set_fine(*status), "f_file_link", F_true, parameter_file_name_minor, "link", fll_error_file_type_file);
        }
        else if (data_build.setting.version_target == fake_build_version_type_micro) {
          fll_error_file_print(data.error, F_status_set_fine(*status), "f_file_link", F_true, parameter_file_name_micro, "link", fll_error_file_type_file);
        }

        return 0;
      }
    }

    fake_build_touch(data, file_stage, status);

    return 0;
  }
#endif // _di_fake_build_library_shared_

#ifndef _di_fake_build_library_static_
  int fake_build_library_static(const fake_data_t data, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true || *status == F_child) return data.child;
    if (!data_build.setting.build_sources_library.used) return 0;

    if (data.error.verbosity != f_console_verbosity_quiet) {
      fprintf(data.output.stream, "%c", f_string_eol[0]);
      fl_color_print(data.output.stream, data.context.set.important, "Compiling static library.");
      fprintf(data.output.stream, "%c", f_string_eol[0]);
    }

    f_string_dynamic_t file_name = f_string_dynamic_t_initialize;
    f_string_dynamic_t source_path = f_string_dynamic_t_initialize;
    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;

    *status = fll_execute_arguments_add(fake_build_parameter_object_link_arguments, fake_build_parameter_object_link_arguments_length, &arguments);

    if (F_status_is_error_not(*status)) {
      f_string_length_t destination_length = data.path_build_libraries_static.used + fake_build_parameter_library_name_prefix_length;
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

    if (F_status_is_error_not(*status)) {
      f_string_length_t source_length = 0;

      for (f_array_length_t i = 0; i < data_build.setting.build_sources_library.used; i++) {
        source_path.used = 0;

        *status = fake_build_get_file_name_without_extension(data, data_build.setting.build_sources_library.array[i], &file_name);

        if (F_status_is_error(*status)) {
          fll_error_print(data.error, F_status_set_fine(*status), "fake_build_get_file_name_without_extension", F_true);
          break;
        }

        if (fake_signal_received(data)) {
          *status = F_status_set_error(F_signal);
          break;
        }

        *status = f_file_name_directory(data_build.setting.build_sources_library.array[i].string, data_build.setting.build_sources_library.array[i].used, &source_path);

        if (F_status_is_error(*status)) {
          fll_error_print(data.error, F_status_set_fine(*status), "f_file_name_directory", F_true);
          break;
        }

        if (source_path.used) {
          *status = fl_string_dynamic_prepend(data.path_build_objects, &source_path);

          if (F_status_is_error(*status)) {
            fll_error_print(data.error, F_status_set_fine(*status), "fl_string_dynamic_prepend", F_true);
            break;
          }

          *status = fl_string_append_assure(f_path_separator_s, f_path_separator_length, &source_path);

          if (F_status_is_error(*status)) {
            fll_error_print(data.error, F_status_set_fine(*status), "fl_string_append_assure", F_true);
            break;
          }

          *status = fl_string_dynamic_terminate_after(&source_path);

          if (F_status_is_error(*status)) {
            fll_error_print(data.error, F_status_set_fine(*status), "fl_string_dynamic_terminate_after", F_true);
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

        if (F_status_is_error(*status)) {
          fll_error_print(data.error, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);
          break;
        }
      } // for
    }

    int result = data.child;

    if (F_status_is_error_not(*status)) {
      result = fake_execute(data, data_build.environment, data_build.setting.build_indexer, arguments, status);
    }

    fl_string_dynamic_delete(&file_name);
    fl_string_dynamic_delete(&source_path);
    fl_string_dynamics_delete(&arguments);

    if (F_status_is_error_not(*status) && *status != F_child) {
      fake_build_touch(data, file_stage, status);
    }

    return result;
  }
#endif // _di_fake_build_library_static_

#ifndef _di_fake_build_load_environment_
  void fake_build_load_environment(const fake_data_t data, const fake_build_data_t data_build, fake_environment_t *environment, f_status_t *status) {
    if (F_status_is_error(*status)) return;

    f_string_dynamics_t names = f_string_dynamics_t_initialize;

    {
      // add the guaranteed environment variables.
      const f_string_t variables_name[] = {
        f_path_environment_s,
        f_path_present_working_s
      };

      const f_string_length_t variables_length[] = {
        f_path_environment_length,
        f_path_present_working_length
      };

      f_macro_string_dynamics_new(*status, names, 2);

      if (F_status_is_error(*status)) {
        fll_error_print(data.error, F_status_set_fine(*status), "f_macro_string_dynamics_new", F_true);

        fl_string_dynamics_delete(&names);
        return;
      }

      f_string_dynamic_t part = f_string_dynamic_t_initialize;

      for (uint8_t i = 0; i < 2; i++) {

        *status = fl_string_append(variables_name[i], variables_length[i], &part);
        if (F_status_is_error(*status)) break;

        names.array[names.used].string = part.string;
        names.array[names.used].used = part.used;
        names.array[names.used].size = part.size;
        names.used++;

        f_macro_string_dynamic_t_clear(part);
      } // for

      if (F_status_is_error_not(*status)) {
        if (names.used + data_build.setting.environment.used > names.size) {
          if (names.used + data_build.setting.environment.used > f_array_length_t_size) {
            if (data.error.verbosity != f_console_verbosity_quiet) {
              fprintf(data.error.to.stream, "%c", f_string_eol[0]);
              fl_color_print(data.error.to.stream, data.context.set.error, "%sThe values for the setting '", fll_error_print_error);
              fl_color_print(data.error.to.stream, data.context.set.notable, "%s", fake_build_setting_name_environment);
              fl_color_print(data.error.to.stream, data.context.set.error, "' of setting file '");
              fl_color_print(data.error.to.stream, data.context.set.notable, "%s", data.file_data_build_settings.string);
              fl_color_print(data.error.to.stream, data.context.set.error, "' is too large.");
              fprintf(data.error.to.stream, "%c", f_string_eol[0]);
            }

            fl_string_dynamic_delete(&part);
            fl_string_dynamics_delete(&names);
            *status = F_status_set_error(F_array_too_large);
            return;
          }

          f_macro_string_dynamics_t_resize(*status, names, names.used + data_build.setting.environment.used);

          if (F_status_is_error(*status)) {
            fll_error_print(data.error, F_status_set_fine(*status), "f_macro_string_dynamics_t_resize", F_true);

            fl_string_dynamic_delete(&part);
            fl_string_dynamics_delete(&names);
            return;
          }
        }

        for (f_string_length_t i = 0; i < data_build.setting.environment.used; i++) {

          *status = fl_string_dynamic_append_nulless(data_build.setting.environment.array[i], &part);
          if (F_status_is_error(*status)) break;

          names.array[names.used].string = part.string;
          names.array[names.used].used = part.used;
          names.array[names.used].size = part.size;
          names.used++;

          f_macro_string_dynamic_t_clear(part);
        } // for
      }

      fl_string_dynamic_delete(&part);

      if (F_status_is_error(*status)) {
        fll_error_print(data.error, F_status_set_fine(*status), "fl_string_append", F_true);

        fl_string_dynamics_delete(&names);
        return;
      }
    }

    f_string_t function = f_string_t_initialize;
    f_string_dynamic_t variable_name = f_string_dynamic_t_initialize;
    f_string_dynamic_t variable_value = f_string_dynamic_t_initialize;

    for (f_string_length_t i = 0; i < names.used; i++) {

      if (fake_signal_received(data)) {
        *status = F_status_set_error(F_signal);
        break;
      }

      *status = f_environment_get_dynamic(names.array[i], &variable_value);

      if (F_status_is_error(*status)) {
        if (F_status_set_fine(*status) == F_memory_reallocation) {
          function = "f_macro_string_dynamics_t_resize";
          break;
        }
      }

      if (F_status_is_error_not(*status) && environment->names.used + 1 > environment->names.size) {
        if (environment->names.size + f_memory_default_allocation_step > f_array_length_t_size) {
          if (environment->names.size + 1 > f_array_length_t_size) {
            *status = F_status_set_error(F_array_too_large);
          }
          else {
            f_macro_string_dynamics_t_resize(*status, environment->names, environment->names.size + 1);
          }
        }
        else {
          f_macro_string_dynamics_t_resize(*status, environment->names, environment->names.size + f_memory_default_allocation_step);
        }

        if (F_status_is_error(*status)) {
          function = "f_macro_string_dynamics_t_resize";
          break;
        }

        f_macro_string_dynamics_t_resize(*status, environment->values, environment->names.size);
        if (F_status_is_error(*status)) {
          function = "f_macro_string_dynamics_t_resize";
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

      f_macro_string_dynamic_t_clear(variable_name);
      f_macro_string_dynamic_t_clear(variable_value);
    } // for

    fl_string_dynamics_delete(&names);
    fl_string_dynamic_delete(&variable_name);
    fl_string_dynamic_delete(&variable_value);

    if (F_status_is_error(*status) && F_status_set_fine(*status) != F_signal) {
      fll_error_print(data.error, *status, function, F_true);
    }
  }
#endif // _di_fake_build_load_environment_

#ifndef _di_fake_build_load_setting_
  void fake_build_load_setting(const fake_data_t data, const f_string_static_t setting_file, fake_build_setting_t *setting, f_status_t *status) {
    if (F_status_is_error(*status)) return;

    if (fake_signal_received(data)) {
      *status = F_status_set_error(F_signal);
      return;
    }

    char path_file[data.path_data_build.used + setting_file.used + 1];

    {
      f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

      f_fss_objects_t objects = f_fss_objects_t_initialize;
      f_fss_contents_t contents = f_fss_contents_t_initialize;

      if (setting_file.used) {
        memcpy(path_file, data.path_data_build.string, data.path_data_build.used);
        memcpy(path_file + data.path_data_build.used, setting_file.string, setting_file.used);

        path_file[data.path_data_build.used + setting_file.used] = 0;

        *status = fake_file_buffer(data, path_file, &buffer);
      }
      else {
        *status = fake_file_buffer(data, data.file_data_build_settings.string, &buffer);
      }

      if (fake_signal_received(data)) {
        *status = F_status_set_error(F_signal);
      }
      else if (F_status_is_error_not(*status)) {
        f_string_range_t range = f_macro_string_range_t_initialize(buffer.used);
        f_fss_delimits_t delimits = f_fss_delimits_t_initialize;

        *status = fll_fss_extended_read(buffer, &range, &objects, &contents, 0, 0, &delimits, 0);

        if (F_status_is_error(*status)) {
          fake_print_error_fss(data, F_status_set_fine(*status), "fll_fss_extended_read", data.file_data_build_settings.string, range, F_true);
        }
        else {
          *status = fl_fss_apply_delimit(delimits, &buffer);

          if (F_status_is_error(*status)) {
            fll_error_print(data.error, F_status_set_fine(*status), "fl_fss_apply_delimit", F_true);
          }
          else {
            fake_build_load_setting_process(data, setting_file.used ? path_file : data.file_data_build_settings.string, buffer, objects, contents, setting, status);
          }
        }

        f_macro_fss_delimits_t_delete_simple(delimits);
      }

      fl_string_dynamic_delete(&buffer);
      f_macro_fss_objects_t_delete_simple(objects);
      f_macro_fss_contents_t_delete_simple(contents);
    }

    // error when required settings are not specified.
    if (F_status_is_error_not(*status)) {
      bool failed = F_false;

      f_string_static_t * const settings[] = {
        &setting->project_name,
      };

      f_string_t names[] = {
        fake_build_setting_name_project_name,
      };

      for (uint8_t i = 0; i < 1; i++) {

        if (!settings[i]->used) {
          fprintf(data.error.to.stream, "%c", f_string_eol[0]);
          fl_color_print(data.error.to.stream, data.context.set.error, "%sThe setting '", fll_error_print_error);
          fl_color_print(data.error.to.stream, data.context.set.notable, "%s", names[i]);
          fl_color_print(data.error.to.stream, data.context.set.error, "' is required but is not specified in the settings file '");
          fl_color_print(data.error.to.stream, data.context.set.notable, "%s", setting_file.used ? path_file : data.file_data_build_settings.string);
          fl_color_print(data.error.to.stream, data.context.set.error, "'.");
          fprintf(data.error.to.stream, "%c", f_string_eol[0]);

          failed = F_true;
        }
      } // for

      if (failed) {
        *status = F_status_set_error(F_failure);
        return;
      }
    }

    fake_build_load_setting_defaults(data, setting, status);
  }
#endif // _di_fake_build_load_setting_

#ifndef _di_fake_build_load_setting_process_
  void fake_build_load_setting_process(const fake_data_t data, const f_string_t path_file, const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, fake_build_setting_t *setting, f_status_t *status) {
    if (F_status_is_error(*status) && buffer.used) return;

    if (fake_signal_received(data)) {
      *status = F_status_set_error(F_signal);
      return;
    }

    bool error_printed = F_false;

    const f_string_t settings_name[] = {
      fake_build_setting_name_build_compiler,
      fake_build_setting_name_build_indexer,
      fake_build_setting_name_build_language,
      fake_build_setting_name_build_libraries,
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
      fake_build_setting_name_path_headers_preserve,
      fake_build_setting_name_path_language,
      fake_build_setting_name_path_library_script,
      fake_build_setting_name_path_library_shared,
      fake_build_setting_name_path_library_static,
      fake_build_setting_name_path_program_script,
      fake_build_setting_name_path_program_shared,
      fake_build_setting_name_path_program_static,
      fake_build_setting_name_path_sources,
      fake_build_setting_name_path_standard,
      fake_build_setting_name_process_post,
      fake_build_setting_name_process_pre,
      fake_build_setting_name_project_name,
      fake_build_setting_name_search_exclusive,
      fake_build_setting_name_search_shared,
      fake_build_setting_name_search_static,
      fake_build_setting_name_version_major,
      fake_build_setting_name_version_micro,
      fake_build_setting_name_version_minor,
      fake_build_setting_name_version_target,
    };

    const f_string_length_t settings_length[] = {
      fake_build_setting_name_build_compiler_length,
      fake_build_setting_name_build_indexer_length,
      fake_build_setting_name_build_language_length,
      fake_build_setting_name_build_libraries_length,
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
      fake_build_setting_name_path_headers_preserve_length,
      fake_build_setting_name_path_language_length,
      fake_build_setting_name_path_library_script_length,
      fake_build_setting_name_path_library_shared_length,
      fake_build_setting_name_path_library_static_length,
      fake_build_setting_name_path_program_script_length,
      fake_build_setting_name_path_program_shared_length,
      fake_build_setting_name_path_program_static_length,
      fake_build_setting_name_path_sources_length,
      fake_build_setting_name_path_standard_length,
      fake_build_setting_name_process_post_length,
      fake_build_setting_name_process_pre_length,
      fake_build_setting_name_project_name_length,
      fake_build_setting_name_search_exclusive_length,
      fake_build_setting_name_search_shared_length,
      fake_build_setting_name_search_static_length,
      fake_build_setting_name_version_major_length,
      fake_build_setting_name_version_micro_length,
      fake_build_setting_name_version_minor_length,
      fake_build_setting_name_version_target_length,
    };

    f_string_dynamics_t build_compiler = f_string_dynamics_t_initialize;
    f_string_dynamics_t build_indexer = f_string_dynamics_t_initialize;
    f_string_dynamics_t build_language = f_string_dynamics_t_initialize;
    f_string_dynamics_t build_script = f_string_dynamics_t_initialize;
    f_string_dynamics_t build_shared = f_string_dynamics_t_initialize;
    f_string_dynamics_t build_static = f_string_dynamics_t_initialize;
    f_string_dynamics_t path_headers = f_string_dynamics_t_initialize;
    f_string_dynamics_t path_headers_preserve = f_string_dynamics_t_initialize;
    f_string_dynamics_t path_language = f_string_dynamics_t_initialize;
    f_string_dynamics_t path_library_script = f_string_dynamics_t_initialize;
    f_string_dynamics_t path_library_shared = f_string_dynamics_t_initialize;
    f_string_dynamics_t path_library_static = f_string_dynamics_t_initialize;
    f_string_dynamics_t path_program_script = f_string_dynamics_t_initialize;
    f_string_dynamics_t path_program_shared = f_string_dynamics_t_initialize;
    f_string_dynamics_t path_program_static = f_string_dynamics_t_initialize;
    f_string_dynamics_t path_sources = f_string_dynamics_t_initialize;
    f_string_dynamics_t path_standard = f_string_dynamics_t_initialize;
    f_string_dynamics_t process_post = f_string_dynamics_t_initialize;
    f_string_dynamics_t process_pre = f_string_dynamics_t_initialize;
    f_string_dynamics_t project_name = f_string_dynamics_t_initialize;
    f_string_dynamics_t search_exclusive = f_string_dynamics_t_initialize;
    f_string_dynamics_t search_shared = f_string_dynamics_t_initialize;
    f_string_dynamics_t search_static = f_string_dynamics_t_initialize;
    f_string_dynamics_t version_major = f_string_dynamics_t_initialize;
    f_string_dynamics_t version_micro = f_string_dynamics_t_initialize;
    f_string_dynamics_t version_minor = f_string_dynamics_t_initialize;
    f_string_dynamics_t version_target = f_string_dynamics_t_initialize;

    f_string_dynamics_t *settings_value[] = {
      &build_compiler,
      &build_indexer,
      &build_language,
      &setting->build_libraries,
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
      &path_headers_preserve,
      &path_language,
      &path_library_script,
      &path_library_shared,
      &path_library_static,
      &path_program_script,
      &path_program_shared,
      &path_program_static,
      &path_sources,
      &path_standard,
      &process_post,
      &process_pre,
      &project_name,
      &search_exclusive,
      &search_shared,
      &search_static,
      &version_major,
      &version_micro,
      &version_minor,
      &version_target,
    };

    f_string_t function = "fll_fss_snatch_apart";

    *status = fll_fss_snatch_apart(buffer, objects, contents, settings_name, settings_length, fake_build_setting_total, settings_value, 0);

    if (*status == F_none) {
      f_string_dynamic_t settings_mode_name_dynamic[fake_build_setting_total];
      f_string_t settings_mode_names[fake_build_setting_total];
      f_string_length_t setting_mode_lengths[fake_build_setting_total];

      const f_string_dynamics_t *modes = &setting->modes_default;
      bool found = F_false;

      f_array_length_t i = 0;
      f_array_length_t j = 0;

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
          if (data.error.verbosity != f_console_verbosity_quiet) {
            fprintf(data.error.to.stream, "%c", f_string_eol[0]);
            fl_color_print(data.error.to.stream, data.context.set.error, "%sThe specified mode '", fll_error_print_error);
            fl_color_print(data.error.to.stream, data.context.set.notable, "%s", modes->array[i].string);
            fl_color_print(data.error.to.stream, data.context.set.error, "' is not a valid mode, according to '");
            fl_color_print(data.error.to.stream, data.context.set.notable, "%s", path_file);
            fl_color_print(data.error.to.stream, data.context.set.error, "'.");
            fprintf(data.error.to.stream, "%c", f_string_eol[0]);
          }

          error_printed = F_true;
          *status = F_status_set_error(F_parameter);
          break;
        }

        memset(&settings_mode_name_dynamic, 0, sizeof(f_string_dynamic_t) * fake_build_setting_total);
        memset(&settings_mode_names, 0, sizeof(f_string_t) * fake_build_setting_total);
        memset(&setting_mode_lengths, 0, sizeof(f_string_length_t) * fake_build_setting_total);

        for (j = 0; j < fake_build_setting_total; j++) {

          setting_mode_lengths[j] = settings_length[j] + 1 + modes->array[i].used;

          f_macro_string_dynamic_t_new(*status, settings_mode_name_dynamic[j], setting_mode_lengths[j]);

          if (F_status_is_error(*status)) {
            function = "f_macro_string_dynamic_t_new";
            break;
          }

          memcpy(settings_mode_name_dynamic[j].string, settings_name[j], settings_length[j]);
          memcpy(settings_mode_name_dynamic[j].string + settings_length[j] + 1, modes->array[i].string, modes->array[i].used);
          settings_mode_name_dynamic[j].string[settings_length[j]] = '-';

          settings_mode_names[j] = settings_mode_name_dynamic[j].string;
        } // for

        if (*status == F_none) {
          *status = fll_fss_snatch_apart(buffer, objects, contents, settings_mode_names, setting_mode_lengths, fake_build_setting_total, settings_value, 0);

          if (F_status_is_error(*status)) {
            function = "fll_fss_snatch_apart";
          }
        }

        for (j = 0; j < fake_build_setting_total; j++) {
          fl_string_dynamic_delete(&settings_mode_name_dynamic[j]);
        } // for

        if (F_status_is_error(*status)) break;
      } // for
    }

    if (F_status_is_error(*status)) {
      if (*status == F_status_set_error(F_string_too_large)) {
        if (data.error.verbosity != f_console_verbosity_quiet) {
          // @todo update FSS functions to return which setting index the problem happened on.
          fprintf(data.error.to.stream, "%c", f_string_eol[0]);
          fl_color_print(data.error.to.stream, data.context.set.error, "%sA setting in the build setting file '", fll_error_print_error);
          fl_color_print(data.error.to.stream, data.context.set.notable, "%s", path_file);
          fl_color_print(data.error.to.stream, data.context.set.error, "' is too long.");
          fprintf(data.error.to.stream, "%c", f_string_eol[0]);
        }
      }
      else if (!error_printed) {
        fll_error_print(data.error, F_status_set_fine(*status), function, F_true);
      }
    }
    else if (!fake_signal_received(data)) {
      const f_string_t settings_single_name[] = {
        fake_build_setting_name_build_compiler,
        fake_build_setting_name_build_indexer,
        fake_build_setting_name_build_language,
        fake_build_setting_name_build_script,
        fake_build_setting_name_build_shared,
        fake_build_setting_name_build_static,
        fake_build_setting_name_path_headers,
        fake_build_setting_name_path_headers_preserve,
        fake_build_setting_name_path_language,
        fake_build_setting_name_path_library_script,
        fake_build_setting_name_path_library_shared,
        fake_build_setting_name_path_library_static,
        fake_build_setting_name_path_program_script,
        fake_build_setting_name_path_program_shared,
        fake_build_setting_name_path_program_static,
        fake_build_setting_name_path_sources,
        fake_build_setting_name_path_standard,
        fake_build_setting_name_process_post,
        fake_build_setting_name_process_pre,
        fake_build_setting_name_project_name,
        fake_build_setting_name_search_exclusive,
        fake_build_setting_name_search_shared,
        fake_build_setting_name_search_static,
        fake_build_setting_name_version_major,
        fake_build_setting_name_version_micro,
        fake_build_setting_name_version_minor,
        fake_build_setting_name_version_target,
      };

      const f_string_statics_t *settings_single_source[] = {
        &build_compiler,
        &build_indexer,
        &build_language,
        &build_script,
        &build_shared,
        &build_static,
        &path_headers,
        &path_headers_preserve,
        &path_language,
        &path_library_script,
        &path_library_shared,
        &path_library_static,
        &path_program_script,
        &path_program_shared,
        &path_program_static,
        &path_sources,
        &path_standard,
        &process_post,
        &process_pre,
        &project_name,
        &search_exclusive,
        &search_shared,
        &search_static,
        &version_major,
        &version_micro,
        &version_minor,
        &version_target,
      };

      bool * const settings_single_bool[] = {
        0,
        0,
        0,
        &setting->build_script,
        &setting->build_shared,
        &setting->build_static,
        0,
        &setting->path_headers_preserve,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        &setting->path_standard,
        0,
        0,
        0,
        &setting->search_exclusive,
        &setting->search_shared,
        &setting->search_static,
      };

      f_string_dynamic_t * const settings_single_destination[] = {
        &setting->build_compiler,
        &setting->build_indexer,
        0,
        0,
        0,
        0,
        &setting->path_headers,
        0,
        &setting->path_language,
        &setting->path_library_script,
        &setting->path_library_shared,
        &setting->path_library_static,
        &setting->path_program_script,
        &setting->path_program_shared,
        &setting->path_program_static,
        &setting->path_sources,
        0,
        &setting->process_post,
        &setting->process_pre,
        &setting->project_name,
        0,
        0,
        0,
        &setting->version_major,
        &setting->version_micro,
        &setting->version_minor,
      };

      uint8_t * const settings_single_language[] = {
        0,
        0,
        &setting->build_language,
      };

      uint8_t * const settings_single_version[] = {
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
        0,
        0,
        &setting->version_target,
      };

      // 1 = "yes" or "no", 2 = path/, 3 = literal, 4 = "bash", "c", or "c++", 5 = "major", "minor", or "micro".
      const uint8_t settings_single_type[] = {
        3,
        3,
        4,
        1,
        1,
        1,
        2,
        1,
        2,
        2,
        2,
        2,
        2,
        2,
        2,
        2,
        1,
        3,
        3,
        3,
        1,
        1,
        1,
        3,
        3,
        3,
        5,
      };

      for (f_array_length_t i = 0; i < 27; i++) {
        if (!settings_single_source[i]->used) continue;

        if (settings_single_source[i]->used > 1) {
          if (data.error.verbosity == f_console_verbosity_verbose) {
            fprintf(data.output.stream, "%c", f_string_eol[0]);
            fl_color_print(data.output.stream, data.context.set.warning, "%sthe setting '", fll_error_print_warning);
            fl_color_print(data.output.stream, data.context.set.notable, "%s", settings_single_name[i]);
            fl_color_print(data.output.stream, data.context.set.warning, "' in the file '");
            fl_color_print(data.output.stream, data.context.set.notable, "%s", path_file);
            fl_color_print(data.output.stream, data.context.set.warning, "' may only have a single property, only using the first: '");
            fl_color_print(data.output.stream, data.context.set.notable, "%s", settings_single_source[i]->array[0].string);
            fl_color_print(data.output.stream, data.context.set.warning, "'.");
            fprintf(data.output.stream, "%c", f_string_eol[0]);
          }
        }

        if (settings_single_type[i] == 1) {
          if (fl_string_compare_trim(settings_single_source[i]->array[0].string, fake_common_setting_bool_yes, settings_single_source[i]->array[0].used, fake_common_setting_bool_yes_length) == F_equal_to) {
            *settings_single_bool[i] = F_true;
          }
          else if (fl_string_compare_trim(settings_single_source[i]->array[0].string, fake_common_setting_bool_no, settings_single_source[i]->array[0].used, fake_common_setting_bool_no_length) == F_equal_to) {
            *settings_single_bool[i] = F_false;
          }
          else {
            *settings_single_bool[i] = F_true;

            if (data.error.verbosity == f_console_verbosity_verbose) {
              fprintf(data.output.stream, "%c", f_string_eol[0]);
              fl_color_print(data.output.stream, data.context.set.warning, "%sthe setting '", fll_error_print_warning);
              fl_color_print(data.output.stream, data.context.set.notable, "%s", settings_single_name[i]);
              fl_color_print(data.output.stream, data.context.set.warning, "' in the file '");
              fl_color_print(data.output.stream, data.context.set.notable, "%s", path_file);
              fl_color_print(data.output.stream, data.context.set.warning, "' may be either '");
              fl_color_print(data.output.stream, data.context.set.notable, "%s", fake_common_setting_bool_yes);
              fl_color_print(data.output.stream, data.context.set.warning, "' or '");
              fl_color_print(data.output.stream, data.context.set.notable, "%s", fake_common_setting_bool_no);
              fl_color_print(data.output.stream, data.context.set.warning, "', defaulting to '");
              fl_color_print(data.output.stream, data.context.set.notable, "%s", fake_common_setting_bool_yes);
              fl_color_print(data.output.stream, data.context.set.warning, "'.");
              fprintf(data.output.stream, "%c", f_string_eol[0]);
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

            if (data.error.verbosity == f_console_verbosity_verbose) {
              fprintf(data.output.stream, "%c", f_string_eol[0]);
              fl_color_print(data.output.stream, data.context.set.warning, "%sthe setting '", fll_error_print_warning);
              fl_color_print(data.output.stream, data.context.set.notable, "%s", settings_single_name[i]);
              fl_color_print(data.output.stream, data.context.set.warning, "' in the file '");
              fl_color_print(data.output.stream, data.context.set.notable, "%s", path_file);
              fl_color_print(data.output.stream, data.context.set.warning, "' may only be one of '");
              fl_color_print(data.output.stream, data.context.set.notable, "%s", fake_build_language_bash);
              fl_color_print(data.output.stream, data.context.set.warning, "', '");
              fl_color_print(data.output.stream, data.context.set.notable, "%s", fake_build_language_c);
              fl_color_print(data.output.stream, data.context.set.warning, "', or '");
              fl_color_print(data.output.stream, data.context.set.notable, "%s", fake_build_language_cpp);
              fl_color_print(data.output.stream, data.context.set.warning, "', defaulting to '");
              fl_color_print(data.output.stream, data.context.set.notable, "%s", fake_build_language_c);
              fl_color_print(data.output.stream, data.context.set.warning, "'.");
              fprintf(data.output.stream, "%c", f_string_eol[0]);
            }
          }
        }
        else if (settings_single_type[i] == 5) {
          if (fl_string_compare_trim(settings_single_source[i]->array[0].string, fake_build_version_major, settings_single_source[i]->array[0].used, fake_build_version_major_length) == F_equal_to) {
            *settings_single_version[i] = fake_build_version_type_major;
          }
          else if (fl_string_compare_trim(settings_single_source[i]->array[0].string, fake_build_version_micro, settings_single_source[i]->array[0].used, fake_build_version_micro_length) == F_equal_to) {
            *settings_single_version[i] = fake_build_version_type_micro;
          }
          else if (fl_string_compare_trim(settings_single_source[i]->array[0].string, fake_build_version_minor, settings_single_source[i]->array[0].used, fake_build_version_minor_length) == F_equal_to) {
            *settings_single_version[i] = fake_build_version_type_minor;
          }
          else {
            *settings_single_version[i] = fake_build_version_type_major;

            if (data.error.verbosity == f_console_verbosity_verbose) {
              fprintf(data.output.stream, "%c", f_string_eol[0]);
              fl_color_print(data.output.stream, data.context.set.warning, "%sthe setting '", fll_error_print_warning);
              fl_color_print(data.output.stream, data.context.set.notable, "%s", settings_single_name[i]);
              fl_color_print(data.output.stream, data.context.set.warning, "' in the file '");
              fl_color_print(data.output.stream, data.context.set.notable, "%s", path_file);
              fl_color_print(data.output.stream, data.context.set.warning, "' may only be one of '");
              fl_color_print(data.output.stream, data.context.set.notable, "%s", fake_build_version_major);
              fl_color_print(data.output.stream, data.context.set.warning, "', '");
              fl_color_print(data.output.stream, data.context.set.notable, "%s", fake_build_version_minor);
              fl_color_print(data.output.stream, data.context.set.warning, "', or '");
              fl_color_print(data.output.stream, data.context.set.notable, "%s", fake_build_version_micro);
              fl_color_print(data.output.stream, data.context.set.warning, "', defaulting to '");
              fl_color_print(data.output.stream, data.context.set.notable, "%s", fake_build_version_major);
              fl_color_print(data.output.stream, data.context.set.warning, "'.");
              fprintf(data.output.stream, "%c", f_string_eol[0]);
            }
          }
        }
        else {
          // replace any potential existing value.
          settings_single_destination[i]->used = 0;

          *status = fl_string_dynamic_append_nulless(settings_single_source[i]->array[0], settings_single_destination[i]);
          if (F_status_is_error(*status)) {
            fll_error_print(data.error, F_status_set_fine(*status), "fl_string_dynamic_append_nulless", F_true);
            break;
          }

          if (settings_single_type[i] == 2) {
            *status = fl_string_append_assure(f_path_separator_s, f_path_separator_length, settings_single_destination[i]);
            if (F_status_is_error(*status)) {
              fll_error_print(data.error, F_status_set_fine(*status), "fl_string_append_assure", F_true);
              break;
            }
          }

          *status = fl_string_dynamic_terminate_after(settings_single_destination[i]);
          if (F_status_is_error(*status)) {
            fll_error_print(data.error, F_status_set_fine(*status), "fl_string_dynamic_terminate_after", F_true);
            break;
          }
        }
      } // for
    }

    fl_string_dynamics_delete(&build_compiler);
    fl_string_dynamics_delete(&build_indexer);
    fl_string_dynamics_delete(&build_language);
    fl_string_dynamics_delete(&build_script);
    fl_string_dynamics_delete(&build_shared);
    fl_string_dynamics_delete(&build_static);
    fl_string_dynamics_delete(&path_headers);
    fl_string_dynamics_delete(&path_headers_preserve);
    fl_string_dynamics_delete(&path_language);
    fl_string_dynamics_delete(&path_library_script);
    fl_string_dynamics_delete(&path_library_shared);
    fl_string_dynamics_delete(&path_library_static);
    fl_string_dynamics_delete(&path_program_script);
    fl_string_dynamics_delete(&path_program_shared);
    fl_string_dynamics_delete(&path_program_static);
    fl_string_dynamics_delete(&path_sources);
    fl_string_dynamics_delete(&path_standard);
    fl_string_dynamics_delete(&process_post);
    fl_string_dynamics_delete(&process_pre);
    fl_string_dynamics_delete(&project_name);
    fl_string_dynamics_delete(&search_exclusive);
    fl_string_dynamics_delete(&search_shared);
    fl_string_dynamics_delete(&search_static);
    fl_string_dynamics_delete(&version_major);
    fl_string_dynamics_delete(&version_micro);
    fl_string_dynamics_delete(&version_minor);
    fl_string_dynamics_delete(&version_target);
  }
#endif // _di_fake_build_load_setting_process_

#ifndef _di_fake_build_load_setting_defaults_
  void fake_build_load_setting_defaults(const fake_data_t data, fake_build_setting_t *setting, f_status_t *status) {
    if (F_status_is_error(*status)) return;

    if (fake_signal_received(data)) {
      *status = F_status_set_error(F_signal);
      return;
    }

    {
      const f_string_t sources[] = {
        fake_build_setting_default_version,
        fake_build_setting_default_version,
        fake_build_setting_default_version,
      };

      const f_string_length_t lengths[] = {
        fake_build_setting_default_version_length,
        fake_build_setting_default_version_length,
        fake_build_setting_default_version_length,
      };

      f_string_dynamic_t * const destinations[] = {
        &setting->version_major,
        &setting->version_minor,
        &setting->version_micro,
      };

      for (uint8_t i = 0; i < 3; i++) {
        if (destinations[i]->used > 0) continue;

        *status = fl_string_append_assure(sources[i], lengths[i], destinations[i]);

        if (F_status_is_error(*status)) {
          fll_error_print(data.error, F_status_set_fine(*status), "fl_string_append_assure", F_true);
          break;
        }

        *status = fl_string_dynamic_terminate_after(destinations[i]);

        if (F_status_is_error(*status)) {
          fll_error_print(data.error, F_status_set_fine(*status), "fl_string_dynamic_terminate_after", F_true);
          break;
        }
      } // for
    }

    if (F_status_is_error(*status)) return;

    // Override setting file when any of these are specified in the command line.
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

        if (data.error.verbosity == f_console_verbosity_verbose) {
          fprintf(data.output.stream, "%c", f_string_eol[0]);
          fl_color_print(data.output.stream, data.context.set.error, "%sthe parameters '", fll_error_print_warning);
          fl_color_print(data.output.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable, fake_long_shared_disabled);
          fl_color_print(data.output.stream, data.context.set.error, "' and '");
          fl_color_print(data.output.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable, fake_long_shared_enabled);
          fl_color_print(data.output.stream, data.context.set.error, "' contradict, defaulting to '");

          if (setting->build_shared) {
            fl_color_print(data.output.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable, fake_long_shared_enabled);
          }
          else {
            fl_color_print(data.output.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable, fake_long_shared_disabled);
          }

          fl_color_print(data.output.stream, data.context.set.error, "'.");
          fprintf(data.output.stream, "%c", f_string_eol[0]);
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

        if (data.error.verbosity == f_console_verbosity_verbose) {
          fprintf(data.output.stream, "%c", f_string_eol[0]);
          fl_color_print(data.output.stream, data.context.set.error, "%sthe parameters '", fll_error_print_warning);
          fl_color_print(data.output.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable, fake_long_static_disabled);
          fl_color_print(data.output.stream, data.context.set.error, "' and '");
          fl_color_print(data.output.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable, fake_long_static_enabled);
          fl_color_print(data.output.stream, data.context.set.error, "' contradict, defaulting to '");

          if (setting->build_static) {
            fl_color_print(data.output.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable, fake_long_static_enabled);
          }
          else {
            fl_color_print(data.output.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable, fake_long_static_disabled);
          }

          fl_color_print(data.output.stream, data.context.set.error, "'.");
          fprintf(data.output.stream, "%c", f_string_eol[0]);
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
        if (data.error.verbosity != f_console_verbosity_quiet) {
          fprintf(data.error.to.stream, "%c", f_string_eol[0]);
          fl_color_print(data.error.to.stream, data.context.set.error, "%sThe build settings '", fll_error_print_error);
          fl_color_print(data.error.to.stream, data.context.set.notable, "%s", fake_build_setting_name_build_shared);
          fl_color_print(data.error.to.stream, data.context.set.error, "' and '");
          fl_color_print(data.error.to.stream, data.context.set.notable, "%s", fake_build_setting_name_build_static);
          fl_color_print(data.error.to.stream, data.context.set.error, "' cannot both be false when using the language '");

          if (setting->build_language == fake_build_language_type_c) {
            fl_color_print(data.error.to.stream, data.context.set.notable, "%s", fake_build_language_c);
          }
          else {
            fl_color_print(data.error.to.stream, data.context.set.notable, "%s", fake_build_language_cpp);
          }

          fl_color_print(data.error.to.stream, data.context.set.error, "'.");
          fprintf(data.error.to.stream, "%c", f_string_eol[0]);
        }

        *status = F_status_set_error(F_failure);
      }
    }

    if (fake_signal_received(data)) {
      *status = F_status_set_error(F_signal);
    }
  }
#endif // _di_fake_build_load_setting_defaults_

#ifndef _di_fake_build_load_stage_
  void fake_build_load_stage(const fake_data_t data, const f_string_static_t settings_file, fake_build_stage_t *stage, f_status_t *status) {
    if (F_status_is_error(*status)) return;

    if (fake_signal_received(data)) {
      *status = F_status_set_error(F_signal);
    }

    const f_string_t names[] = {
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

    const f_string_length_t lengths[] = {
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

    f_string_dynamic_t * const values[] = {
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

    f_string_dynamic_t settings_file_base = f_string_dynamic_t_initialize;

    if (settings_file.used) {
      *status = f_file_name_base(settings_file.string, settings_file.used, &settings_file_base);
    }
    else {
      *status = f_file_name_base(data.file_data_build_settings.string, data.file_data_build_settings.used, &settings_file_base);
    }

    if (F_status_is_error(*status)) {
      fll_error_print(data.error, F_status_set_fine(*status), "f_file_name_base", F_true);
      return;
    }

    for (uint8_t i = 0; i < fake_build_stage_total; i++) {

      *status = fl_string_dynamic_append_nulless(data.path_build_stage, values[i]);

      if (F_status_is_error(*status)) {
        fll_error_print(data.error, F_status_set_fine(*status), "fl_string_dynamic_append_nulless", F_true);
        break;
      }

      if (data.process.used) {
        *status = fl_string_append(data.process.string, data.process.used, values[i]);

        if (F_status_is_error(*status)) {
          fll_error_print(data.error, F_status_set_fine(*status), "fl_string_append", F_true);
          break;
        }

        *status = fl_string_append(fake_build_stage_separate, fake_build_stage_separate_length, values[i]);

        if (F_status_is_error(*status)) {
          fll_error_print(data.error, F_status_set_fine(*status), "fl_string_append", F_true);
          break;
        }
      }

      *status = fl_string_append_nulless(names[i], lengths[i], values[i]);

      if (F_status_is_error(*status)) {
        fll_error_print(data.error, F_status_set_fine(*status), "fl_string_dynamic_append_nulless", F_true);
        break;
      }

      *status = fl_string_append(fake_build_stage_separate, fake_build_stage_separate_length, values[i]);

      if (F_status_is_error(*status)) {
        fll_error_print(data.error, F_status_set_fine(*status), "fl_string_append", F_true);
        break;
      }

      *status = fl_string_dynamic_append(settings_file_base, values[i]);

      if (F_status_is_error(*status)) {
        fll_error_print(data.error, F_status_set_fine(*status), "fl_string_dynamic_append", F_true);
        break;
      }

      *status = fl_string_append(fake_build_stage_built, fake_build_stage_built_length, values[i]);

      if (F_status_is_error(*status)) {
        fll_error_print(data.error, F_status_set_fine(*status), "fl_string_append", F_true);
        break;
      }

      *status = fl_string_dynamic_terminate_after(values[i]);

      if (F_status_is_error(*status)) {
        fll_error_print(data.error, F_status_set_fine(*status), "fl_string_dynamic_terminate_after", F_true);
        break;
      }
    } // for

    fl_string_dynamic_delete(&settings_file_base);
  }
#endif // _di_fake_build_load_stage_

#ifndef _di_fake_build_objects_static_
  int fake_build_objects_static(const fake_data_t data, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true || *status == F_child) return data.child;
    if (!data_build.setting.build_sources_library.used) return 0;

    if (data.error.verbosity != f_console_verbosity_quiet) {
      fprintf(data.output.stream, "%c", f_string_eol[0]);
      fl_color_print(data.output.stream, data.context.set.important, "Compiling static objects.");
      fprintf(data.output.stream, "%c", f_string_eol[0]);
    }

    f_string_dynamic_t file_name = f_string_dynamic_t_initialize;
    f_string_dynamic_t destination_path = f_string_dynamic_t_initialize;
    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;
    f_string_length_t source_length = 0;
    f_string_length_t destination_length = 0;

    const f_string_static_t *path_sources = &data.path_sources;

    int result = data.child;

    if (data_build.setting.path_standard) {
      path_sources = &data.path_sources_c;

      if (data_build.setting.build_language == fake_build_language_type_cpp) {
        path_sources = &data.path_sources_cpp;
      }
    }
    else if (data.parameters[fake_parameter_path_sources].result != f_console_result_additional) {
      path_sources = &data_build.setting.path_sources;
    }

    for (f_array_length_t i = 0; i < data_build.setting.build_sources_library.used; i++) {
      file_name.used = 0;
      destination_path.used = 0;

      source_length = path_sources->used + data_build.setting.build_sources_library.array[i].used;

      char source[source_length + 1];

      memcpy(source, path_sources->string, path_sources->used);
      memcpy(source + path_sources->used, data_build.setting.build_sources_library.array[i].string, data_build.setting.build_sources_library.array[i].used);
      source[source_length] = 0;

      *status = fake_build_get_file_name_without_extension(data, data_build.setting.build_sources_library.array[i], &file_name);

      if (F_status_is_error(*status)) {
        fll_error_print(data.error, F_status_set_fine(*status), "fake_build_get_file_name_without_extension", F_true);
        break;
      }

      if (fake_signal_received(data)) {
        *status = F_status_set_error(F_signal);
        break;
      }

      *status = f_file_name_directory(data_build.setting.build_sources_library.array[i].string, data_build.setting.build_sources_library.array[i].used, &destination_path);

      if (F_status_is_error(*status)) {
        fll_error_print(data.error, F_status_set_fine(*status), "f_file_name_directory", F_true);
        break;
      }

      if (destination_path.used) {
        *status = fl_string_dynamic_prepend(data.path_build_objects, &destination_path);

        if (F_status_is_error(*status)) {
          fll_error_print(data.error, F_status_set_fine(*status), "fl_string_dynamic_prepend", F_true);
          break;
        }

        *status = fl_string_append_assure(f_path_separator_s, f_path_separator_length, &destination_path);

        if (F_status_is_error(*status)) {
          fll_error_print(data.error, F_status_set_fine(*status), "fl_string_append_assure", F_true);
          break;
        }

        *status = fl_string_dynamic_terminate_after(&destination_path);

        if (F_status_is_error(*status)) {
          fll_error_print(data.error, F_status_set_fine(*status), "fl_string_dynamic_terminate_after", F_true);
          break;
        }

        if (fake_signal_received(data)) {
          *status = F_status_set_error(F_signal);
          break;
        }

        *status = f_directory_exists(destination_path.string);

        if (*status == F_false) {
          if (data.error.verbosity != f_console_verbosity_quiet) {
            fprintf(data.error.to.stream, "%c", f_string_eol[0]);
            fl_color_print(data.error.to.stream, data.context.set.error, "%sThe path '", fll_error_print_error);
            fl_color_print(data.error.to.stream, data.context.set.notable, "%s", destination_path.string);
            fl_color_print(data.error.to.stream, data.context.set.error, "' exists but is not a directory.");
            fprintf(data.error.to.stream, "%c", f_string_eol[0]);
          }

          *status = F_status_set_error(F_failure);
          break;
        }
        else if (*status == F_file_found_not) {
          *status = f_directory_create(destination_path.string, mode.directory);

          if (F_status_is_error(*status)) {
            if (F_status_set_fine(*status) == F_file_found_not) {
              fprintf(data.error.to.stream, "%c", f_string_eol[0]);
              fl_color_print(data.error.to.stream, data.context.set.error, "%sThe path '", fll_error_print_error);
              fl_color_print(data.error.to.stream, data.context.set.notable, "%s", destination_path.string);
              fl_color_print(data.error.to.stream, data.context.set.error, "' could not be created, a parent directory does not exist.");
              fprintf(data.error.to.stream, "%c", f_string_eol[0]);
            }
            else {
              fll_error_file_print(data.error, F_status_set_fine(*status), "f_directory_create", F_true, destination_path.string, "create", fll_error_file_type_directory);
            }

            break;
          }

          if (data.error.verbosity == f_console_verbosity_verbose) {
            fprintf(data.output.stream, "Directory '%s' created.%c", destination_path.string, f_string_eol[0]);
          }
        }
        else if (F_status_is_error(*status)) {
          fll_error_file_print(data.error, F_status_set_fine(*status), "f_directory_exists", F_true, destination_path.string, "create", fll_error_file_type_directory);
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

      const f_string_t values[] = {
        source,
        fake_build_parameter_object_compile,
        fake_build_parameter_object_static,
        fake_build_parameter_object_output,
        destination,
      };

      const f_string_length_t lengths[] = {
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
        fll_error_print(data.error, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);
        break;
      }

      result = fake_execute(data, data_build.environment, data_build.setting.build_compiler, arguments, status);

      fl_string_dynamics_delete(&arguments);

      if (F_status_is_error(*status) || *status == F_child) break;
    } // for

    fl_string_dynamic_delete(&file_name);
    fl_string_dynamic_delete(&destination_path);
    fl_string_dynamics_delete(&arguments);

    if (F_status_is_error_not(*status) && *status != F_child) {
      fake_build_touch(data, file_stage, status);
    }

    return result;
  }
#endif // _di_fake_build_objects_static_

#ifndef _di_fake_build_operate_
  f_return_status fake_build_operate(const f_string_static_t setting_file, fake_data_t *data) {

    if (fake_signal_received(*data)) {
      return F_signal;
    }

    f_status_t status = F_none;
    f_mode_t mode = f_mode_t_initialize;

    fake_build_data_t data_build = fake_build_data_t_initialize;
    fake_build_stage_t stage = fake_build_stage_t_initialize;

    f_macro_mode_t_set_default_umask(mode, data->umask);

    fake_build_load_setting(*data, setting_file, &data_build.setting, &status);

    if (F_status_is_fine(status)) {
      if (data->error.verbosity != f_console_verbosity_quiet) {
        fprintf(data->output.stream, "%c", f_string_eol[0]);
        fl_color_print(data->output.stream, data->context.set.important, "Building project%c", data_build.setting.project_name.used ? ' ' : 0);

        if (data_build.setting.project_name.used) {
          fl_color_print_code(data->output.stream, data->context.notable);
          f_print_dynamic(data->output.stream, data_build.setting.project_name);
          fl_color_print_code(data->output.stream, data->context.reset);
        }

        fl_color_print(data->output.stream, data->context.set.important, ".");
        fprintf(data->output.stream, "%c", f_string_eol[0]);
      }
    }

    fake_build_load_stage(*data, setting_file, &stage, &status);

    fake_build_load_environment(*data, data_build, &data_build.environment, &status);

    fake_build_skeleton(*data, data_build, mode.directory, stage.file_skeleton, &status);

    data->child = fake_build_execute_process_script(*data, data_build, data_build.setting.process_pre, stage.file_process_pre, &status);

    fake_build_copy(*data, mode, "setting files", data->path_data_settings, data->path_build_settings, data_build.setting.build_sources_setting, stage.file_sources_settings, 0, &status);

    if (data_build.setting.build_language == fake_build_language_type_bash) {
      fake_build_libraries_script(*data, data_build, mode, stage.file_libraries_script, &status);

      fake_build_programs_script(*data, data_build, mode, stage.file_programs_script, &status);

      if (data_build.setting.build_script) {
        fake_build_copy(*data, mode, "scripts", data->path_sources_script, data->path_build_programs_script, data_build.setting.build_sources_script, stage.file_sources_script, 0, &status);
      }
    }
    else {
      if (data_build.setting.build_sources_headers.used) {
        const f_string_static_t *path_sources = &data->path_sources;

        if (data_build.setting.path_standard) {
          path_sources = &data->path_sources_c;

          if (data_build.setting.build_language == fake_build_language_type_cpp) {
            path_sources = &data->path_sources_cpp;
          }
        }
        else if (data->parameters[fake_parameter_path_sources].result != f_console_result_additional) {
          path_sources = &data_build.setting.path_sources;
        }

        const f_string_length_t path_sources_base_length = path_sources->used;

        f_string_static_t path_headers = f_string_static_t_initialize;
        f_string_length_t directory_headers_length = data->path_build_includes.used + data_build.setting.path_headers.used;

        char directory_headers[directory_headers_length + 1];

        if (data_build.setting.path_headers.used > 0) {
          memcpy(directory_headers, data->path_build_includes.string, data->path_build_includes.used);
          memcpy(directory_headers + data->path_build_includes.used, data_build.setting.path_headers.string, data_build.setting.path_headers.used);

          directory_headers[directory_headers_length] = 0;

          path_headers.string = directory_headers;
          path_headers.used = directory_headers_length;
          path_headers.size = directory_headers_length + 1;
        }
        else {
          memcpy(directory_headers, data->path_build_includes.string, data->path_build_includes.used);

          directory_headers[directory_headers_length] = 0;

          path_headers.string = directory_headers;
          path_headers.used = directory_headers_length;
          path_headers.size = directory_headers_length + 1;
        }

        fake_build_copy(*data, mode, "header files", *path_sources, path_headers, data_build.setting.build_sources_headers, stage.file_sources_headers, data_build.setting.path_headers_preserve ? path_sources_base_length : 0, &status);
      }

      if (data_build.setting.build_shared) {
        data->child = fake_build_library_shared(*data, data_build, mode, stage.file_libraries_shared, &status);

        data->child = fake_build_program_shared(*data, data_build, mode, stage.file_programs_shared, &status);
      }

      if (data_build.setting.build_static) {
        data->child = fake_build_objects_static(*data, data_build, mode, stage.file_objects_static, &status);

        data->child = fake_build_library_static(*data, data_build, mode, stage.file_libraries_static, &status);

        data->child = fake_build_program_static(*data, data_build, mode, stage.file_programs_static, &status);
      }

      if (data_build.setting.build_script) {
        fake_build_copy(*data, mode, "scripts", data->path_sources_script, data->path_build_programs_script, data_build.setting.build_sources_script, stage.file_sources_script, 0, &status);
      }
    }

    fake_build_execute_process_script(*data, data_build, data_build.setting.process_post, stage.file_process_post, &status);

    fake_macro_build_data_delete_simple(data_build);
    fake_macro_build_stage_t_delete_simple(stage);

    // signal is set with error code only to prevent further execution above, return without the error bit set.
    if (status == F_status_set_error(F_signal)) {
      return F_signal;
    }

    return status;
  }
#endif // _di_fake_build_operate_

#ifndef _di_fake_build_programs_script_
  int fake_build_programs_script(const fake_data_t data, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true || *status == F_child) return data.child;

    // @todo needs to perform some sort of regex replace on the program scripts.

    fake_build_touch(data, file_stage, status);

    return 0;
  }
#endif // _di_fake_build_programs_script_

#ifndef _di_fake_build_program_shared_
  int fake_build_program_shared(const fake_data_t data, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true || *status == F_child) return data.child;
    if (!data_build.setting.build_sources_program.used) return 0;

    if (data.error.verbosity != f_console_verbosity_quiet) {
      fprintf(data.output.stream, "%c", f_string_eol[0]);
      fl_color_print(data.output.stream, data.context.set.important, "Compiling shared program.");
      fprintf(data.output.stream, "%c", f_string_eol[0]);
    }

    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;

    {
      const f_string_static_t *path_sources = &data.path_sources;

      if (data_build.setting.path_standard) {
        path_sources = &data.path_sources_c;

        if (data_build.setting.build_language == fake_build_language_type_cpp) {
          path_sources = &data.path_sources_cpp;
        }
      }
      else if (data.parameters[fake_parameter_path_sources].result != f_console_result_additional) {
        path_sources = &data_build.setting.path_sources;
      }

      f_string_length_t source_length = 0;

      for (f_array_length_t i = 0; i < data_build.setting.build_sources_program.used; i++) {
        source_length = path_sources->used + data_build.setting.build_sources_program.array[i].used;

        char source[source_length + 1];

        memcpy(source, path_sources->string, path_sources->used);
        memcpy(source + path_sources->used, data_build.setting.build_sources_program.array[i].string, data_build.setting.build_sources_program.array[i].used);
        source[source_length] = 0;

        *status = fll_execute_arguments_add(source, source_length, &arguments);
        if (F_status_is_error(*status)) break;
      } // for
    }

    if (F_status_is_error_not(*status)) {
      f_string_length_t parameter_file_name_path_length = data.path_build_programs_shared.used + data_build.setting.project_name.used;

      char parameter_file_name_path[parameter_file_name_path_length + 1];

      memcpy(parameter_file_name_path, data.path_build_programs_shared.string, data.path_build_programs_shared.used);
      memcpy(parameter_file_name_path + data.path_build_programs_shared.used, data_build.setting.project_name.string, data_build.setting.project_name.used);
      parameter_file_name_path[parameter_file_name_path_length] = 0;

      const f_string_t values[] = {
        fake_build_parameter_library_output,
        parameter_file_name_path,
      };

      const f_string_length_t lengths[] = {
        fake_build_parameter_library_output_length,
        parameter_file_name_path_length,
      };

      for (uint8_t i = 0; i < 2; i++) {
        *status = fll_execute_arguments_add(values[i], lengths[i], &arguments);
        if (F_status_is_error(*status)) break;
      } // for
    }

    // if project-specific library sources exist, then the -lproject_name needs to be added to the arguments.
    if (F_status_is_error_not(*status) && data_build.setting.build_sources_library.used > 0) {
      f_string_length_t link_project_library_length = fake_build_parameter_library_link_file_length + data_build.setting.project_name.used;

      char link_project_library[link_project_library_length + 1];

      memcpy(link_project_library, fake_build_parameter_library_link_file, fake_build_parameter_library_link_file_length);
      memcpy(link_project_library + fake_build_parameter_library_link_file_length, data_build.setting.project_name.string, data_build.setting.project_name.used);
      link_project_library[link_project_library_length] = 0;

      *status = fll_execute_arguments_add(link_project_library, link_project_library_length, &arguments);
    }

    fake_build_arguments_standard_add(data, data_build, F_true, F_false, &arguments, status);

    if (F_status_is_error(*status)) {
      fll_error_print(data.error, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);

      fl_string_dynamics_delete(&arguments);
      return 0;
    }

    int result = fake_execute(data, data_build.environment, data_build.setting.build_compiler, arguments, status);

    fl_string_dynamics_delete(&arguments);

    if (F_status_is_error_not(*status) && *status != F_child) {
      fake_build_touch(data, file_stage, status);
    }

    return result;
  }
#endif // _di_fake_build_program_shared_

#ifndef _di_fake_build_program_static_
  int fake_build_program_static(const fake_data_t data, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true || *status == F_child) return data.child;
    if (!data_build.setting.build_sources_program.used) return 0;

    if (data.error.verbosity != f_console_verbosity_quiet) {
      fprintf(data.output.stream, "%c", f_string_eol[0]);
      fl_color_print(data.output.stream, data.context.set.important, "Compiling static program.");
      fprintf(data.output.stream, "%c", f_string_eol[0]);
    }

    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;

    {
      const f_string_static_t *path_sources = &data.path_sources;

      if (data_build.setting.path_standard) {
        path_sources = &data.path_sources_c;

        if (data_build.setting.build_language == fake_build_language_type_cpp) {
          path_sources = &data.path_sources_cpp;
        }
      }
      else if (data.parameters[fake_parameter_path_sources].result != f_console_result_additional) {
        path_sources = &data_build.setting.path_sources;
      }

      f_string_length_t source_length = 0;

      for (f_array_length_t i = 0; i < data_build.setting.build_sources_program.used; i++) {
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

    if (F_status_is_error_not(*status)) {
      f_string_length_t source_library_length = data.path_build_libraries_static.used + fake_build_parameter_library_name_prefix_length + data_build.setting.project_name.used + fake_build_parameter_library_name_suffix_static_length;

      char source_library[source_library_length + 1];

      source_library_length = 0;

      // only include the library if there are sources that would result in it being built.
      if (data_build.setting.build_sources_library.used) {
        memcpy(source_library, data.path_build_libraries_static.string, data.path_build_libraries_static.used);
        source_library_length += data.path_build_libraries_static.used;

        memcpy(source_library + source_library_length, fake_build_parameter_library_name_prefix, fake_build_parameter_library_name_prefix_length);
        source_library_length += fake_build_parameter_library_name_prefix_length;

        memcpy(source_library + source_library_length, data_build.setting.project_name.string, data_build.setting.project_name.used);
        source_library_length += data_build.setting.project_name.used;

        memcpy(source_library + source_library_length, fake_build_parameter_library_name_suffix_static, fake_build_parameter_library_name_suffix_static_length);
        source_library_length += fake_build_parameter_library_name_suffix_static_length;
      }

      source_library[source_library_length] = 0;

      f_string_length_t parameter_file_name_path_length = data.path_build_programs_static.used + data_build.setting.project_name.used;

      char parameter_file_name_path[parameter_file_name_path_length + 1];

      memcpy(parameter_file_name_path, data.path_build_programs_static.string, data.path_build_programs_static.used);
      memcpy(parameter_file_name_path + data.path_build_programs_static.used, data_build.setting.project_name.string, data_build.setting.project_name.used);
      parameter_file_name_path[parameter_file_name_path_length] = 0;

      const f_string_t values[] = {
        source_library,
        fake_build_parameter_library_static,
        fake_build_parameter_library_output,
        parameter_file_name_path,
      };

      const f_string_length_t lengths[] = {
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
      fll_error_print(data.error, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);

      fl_string_dynamics_delete(&arguments);
      return 0;
    }

    int result = fake_execute(data, data_build.environment, data_build.setting.build_compiler, arguments, status);

    fl_string_dynamics_delete(&arguments);

    if (F_status_is_error_not(*status) && *status != F_child) {
      fake_build_touch(data, file_stage, status);
    }

    return result;
  }
#endif // _di_fake_build_program_static_

#ifndef _di_fake_build_touch_
  void fake_build_touch(const fake_data_t data, const f_string_dynamic_t file, f_status_t *status) {
    if (F_status_is_error(*status)) return;

    f_mode_t mode = f_mode_t_initialize;

    f_macro_mode_t_set_default_umask(mode, data.umask);

    if (fake_signal_received(data)) {
      *status = F_status_set_error(F_signal);
      return;
    }

    *status = f_file_touch(file.string, mode.regular, F_false);

    if (F_status_is_error(*status)) {
      fll_error_file_print(data.error, F_status_set_fine(*status), "f_file_touch", F_true, file.string, "touch", fll_error_file_type_file);
    }
  }
#endif // _di_fake_build_touch_

#ifdef __cplusplus
} // extern "C"
#endif
