#include "fake.h"
#include "private-common.h"
#include "private-fake.h"
#include "private-build.h"
#include "private-make.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_arguments_standard_add_
  void fake_build_arguments_standard_add(const fake_main_t main, const fake_build_data_t data_build, const bool is_shared, const bool is_library, f_string_dynamics_t *arguments, f_status_t *status) {

    if (F_status_is_error(*status)) return;

    f_array_length_t build_libraries_length = fake_build_parameter_library_link_path_length + main.path_build_libraries_shared.used;

    char build_libraries[build_libraries_length + 1];

    memcpy(build_libraries, fake_build_parameter_library_link_path, fake_build_parameter_library_link_path_length);

    if (is_shared) {
      memcpy(build_libraries + fake_build_parameter_library_link_path_length, main.path_build_libraries_shared.string, main.path_build_libraries_shared.used);
    }
    else {
      memcpy(build_libraries + fake_build_parameter_library_link_path_length, main.path_build_libraries_static.string, main.path_build_libraries_static.used);
    }

    build_libraries[build_libraries_length] = 0;

    f_array_length_t build_includes_length = fake_build_parameter_library_include_length + main.path_build_includes.used;

    char build_includes[build_includes_length + 1];

    memcpy(build_includes, fake_build_parameter_library_include, fake_build_parameter_library_include_length);
    memcpy(build_includes + fake_build_parameter_library_include_length, main.path_build_includes.string, main.path_build_includes.used);

    const f_string_t values[] = {
      build_libraries,
      build_includes,
    };

    const f_array_length_t lengths[] = {
      build_libraries_length,
      build_includes_length,
    };

    for (uint8_t i = 0; i < 2; ++i) {

      *status = fll_execute_arguments_add(values[i], lengths[i], arguments);
      if (F_status_is_error(*status)) break;
    } // for

    if (main.path_work.used) {
      f_array_length_t length = 0;

      if (F_status_is_error_not(*status)) {
        length = fake_build_parameter_library_include_length + main.path_work_includes.used;

        char string[length + 1];

        memcpy(string, fake_build_parameter_library_include, fake_build_parameter_library_include_length);
        memcpy(string + fake_build_parameter_library_include_length, main.path_work_includes.string, main.path_work_includes.used);

        string[length] = 0;

        *status = fll_execute_arguments_add(string, length, arguments);
      }

      if (data_build.setting.search_shared && (is_shared || !data_build.setting.search_exclusive) && F_status_is_error_not(*status)) {
        length = fake_build_parameter_library_link_path_length + main.path_work_libraries_shared.used;

        char string[length + 1];

        memcpy(string, fake_build_parameter_library_link_path, fake_build_parameter_library_link_path_length);
        memcpy(string + fake_build_parameter_library_link_path_length, main.path_work_libraries_shared.string, main.path_work_libraries_shared.used);

        string[length] = 0;

        *status = fll_execute_arguments_add(string, length, arguments);
      }

      if (data_build.setting.search_static && (!is_shared || !data_build.setting.search_exclusive) && F_status_is_error_not(*status)) {
        length = fake_build_parameter_library_link_path_length + main.path_work_libraries_static.used;

        char string[length + 1];

        memcpy(string, fake_build_parameter_library_link_path, fake_build_parameter_library_link_path_length);
        memcpy(string + fake_build_parameter_library_link_path_length, main.path_work_libraries_static.string, main.path_work_libraries_static.used);

        string[length] = 0;

        *status = fll_execute_arguments_add(string, length, arguments);
      }
    }

    f_array_length_t i = 0;

    for (i = 0; i < data_build.setting.build_libraries.used && F_status_is_error_not(*status); ++i) {
      *status = fll_execute_arguments_add(data_build.setting.build_libraries.array[i].string, data_build.setting.build_libraries.array[i].used, arguments);
    } // for

    for (i = 0; i < data_build.setting.flags_all.used && F_status_is_error_not(*status); ++i) {
      *status = fll_execute_arguments_add(data_build.setting.flags_all.array[i].string, data_build.setting.flags_all.array[i].used, arguments);
    } // for

    for (i = 0; i < data_build.setting.flags_shared.used && F_status_is_error_not(*status); ++i) {
      *status = fll_execute_arguments_add(data_build.setting.flags_shared.array[i].string, data_build.setting.flags_shared.array[i].used, arguments);
    } // for

    if (is_library) {
      for (i = 0; i < data_build.setting.flags_library.used && F_status_is_error_not(*status); ++i) {
        *status = fll_execute_arguments_add(data_build.setting.flags_library.array[i].string, data_build.setting.flags_library.array[i].used, arguments);
      } // for
    }
    else {
      for (i = 0; i < data_build.setting.flags_program.used && F_status_is_error_not(*status); ++i) {
        *status = fll_execute_arguments_add(data_build.setting.flags_program.array[i].string, data_build.setting.flags_program.array[i].used, arguments);
      } // for
    }

    for (i = 0; i < data_build.setting.defines_all.used && F_status_is_error_not(*status); ++i) {
      *status = fll_execute_arguments_add(data_build.setting.defines_all.array[i].string, data_build.setting.defines_all.array[i].used, arguments);
    } // for

    if (is_shared) {
      for (i = 0; i < data_build.setting.defines_shared.used && F_status_is_error_not(*status); ++i) {
        *status = fll_execute_arguments_add(data_build.setting.defines_shared.array[i].string, data_build.setting.defines_shared.array[i].used, arguments);
      } // for
    }
    else {
      for (i = 0; i < data_build.setting.defines_static.used && F_status_is_error_not(*status); ++i) {
        *status = fll_execute_arguments_add(data_build.setting.defines_static.array[i].string, data_build.setting.defines_static.array[i].used, arguments);
      } // for
    }

    if (is_library) {
      for (i = 0; i < data_build.setting.defines_library.used && F_status_is_error_not(*status); ++i) {
        *status = fll_execute_arguments_add(data_build.setting.defines_library.array[i].string, data_build.setting.defines_library.array[i].used, arguments);
      } // for
    }
    else {
      for (i = 0; i < data_build.setting.defines_program.used && F_status_is_error_not(*status); ++i) {
        *status = fll_execute_arguments_add(data_build.setting.defines_program.array[i].string, data_build.setting.defines_program.array[i].used, arguments);
      } // for
    }

    for (i = 0; i < main.define.used && F_status_is_error_not(*status); ++i) {
      *status = fll_execute_arguments_add(main.define.array[i].string, main.define.array[i].used, arguments);
    } // for
  }
#endif // _di_fake_build_arguments_standard_add_

#ifndef _di_fake_build_copy_
  void fake_build_copy(const fake_main_t main, const f_mode_t mode, const f_string_t label, const f_string_static_t source, const f_string_static_t destination, const f_string_statics_t files, const f_string_static_t file_stage, const f_array_length_t preserve, f_status_t *status) {

    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true || *status == F_child) return;

    if (fake_signal_received(main)) {
      *status = F_status_set_error(F_signal);

      return;
    }

    f_directory_statuss_t failures = f_directory_statuss_t_initialize;
    f_string_dynamic_t path_source = f_string_dynamic_t_initialize;
    f_string_dynamic_t destination_file = f_string_dynamic_t_initialize;
    f_string_dynamic_t destination_directory = f_string_dynamic_t_initialize;

    if (main.output.verbosity != f_console_verbosity_quiet) {
      fll_print_format("%c%[Copying %S.%]%c", main.output.to.stream, f_string_eol_s[0], main.context.set.important, label, main.context.set.important, f_string_eol_s[0]);
    }

     macro_f_string_dynamic_t_resize(*status, path_source, source.used);

    if (F_status_is_error(*status)) {
      fll_error_print(main.error, F_status_set_fine(*status), " macro_f_string_dynamic_t_resize", F_true);

      macro_f_string_dynamic_t_delete_simple(path_source);
      return;
    }

    memcpy(path_source.string, source.string, source.used);

    fl_directory_recurse_t recurse = fl_directory_recurse_t_initialize;

    if (main.error.verbosity == f_console_verbosity_verbose) {
      recurse.output.stream = main.output.to.stream;
      recurse.output.id = main.output.to.id;
      recurse.output.flag = main.output.to.flag;
      recurse.output.size_read = main.output.to.size_read;
      recurse.output.size_write = main.output.to.size_write;
      recurse.verbose = fake_verbose_print_copy;
    }

    recurse.failures = &failures;

    for (f_array_length_t i = 0; i < files.used; ++i) {

      if (!files.array[i].used) continue;

      path_source.used = source.used;

      *status = f_string_dynamic_append_nulless(files.array[i], &path_source);

      if (F_status_is_error(*status)) {
        fll_error_print(main.error, F_status_set_fine(*status), "f_string_dynamic_append_nulless", F_true);
        break;
      }

      *status = f_string_dynamic_terminate_after(&path_source);

      if (F_status_is_error(*status)) {
        fll_error_print(main.error, F_status_set_fine(*status), "f_string_dynamic_terminate_after", F_true);
        break;
      }

      if (fake_signal_received(main)) {
        *status = F_status_set_error(F_signal);
        break;
      }

      *status = f_directory_is(path_source.string);

      if (fake_signal_received(main)) {
        *status = F_status_set_error(F_signal);
        break;
      }

      if (*status == F_true) {
        destination_directory.used = 0;

        *status = f_string_dynamic_append(destination, &destination_directory);

        if (F_status_is_error(*status)) {
          fll_error_print(main.error, F_status_set_fine(*status), "f_string_dynamic_append", F_true);
          break;
        }

        *status = f_file_name_base(path_source.string, path_source.used, &destination_directory);

        if (F_status_is_error(*status)) {
          fll_error_print(main.error, F_status_set_fine(*status), "f_file_name_base", F_true);
          break;
        }

        *status = f_string_dynamic_terminate_after(&destination_directory);

        if (F_status_is_error(*status)) {
          fll_error_print(main.error, F_status_set_fine(*status), "f_string_dynamic_terminate_after", F_true);
          break;
        }

        *status = fl_directory_copy(path_source.string, destination_directory.string, path_source.used, destination_directory.used, mode, recurse);

        if (F_status_is_error(*status)) {
          if (main.error.verbosity == f_console_verbosity_verbose) {
            for (f_array_length_t j = 0; j < failures.used; ++j) {
              fake_print_error_build_operation_file(main, F_status_set_fine(*status), "fl_directory_copy", "copy directory", "to", path_source.string, destination_directory.string, F_true);
            } // for

            if (F_status_set_fine(*status) != F_failure) {
              fll_error_print(main.error, F_status_set_fine(*status), "fl_directory_copy", F_true);
            }

            break;
          }
          else if (main.error.verbosity != f_console_verbosity_quiet) {
            fake_print_error_build_operation_file(main, F_status_set_fine(*status), "fl_directory_copy", "copy directory", "to", path_source.string, destination_directory.string, F_true);
          }

          break;
        }
      }
      else if (*status == F_false) {
        destination_file.used = 0;
        destination_directory.used = 0;

        *status = f_string_dynamic_append_nulless(destination, &destination_file);

        if (F_status_is_error(*status)) {
          fll_error_print(main.error, F_status_set_fine(*status), "f_string_dynamic_append_nulless", F_true);
          break;
        }

        if (preserve && preserve < path_source.used) {
          *status = f_string_dynamic_append_nulless(destination, &destination_directory);

          if (F_status_is_error(*status)) {
            fll_error_print(main.error, F_status_set_fine(*status), "f_string_dynamic_append_nulless", F_true);
            break;
          }

          *status = f_file_name_directory(path_source.string + preserve, path_source.used - preserve, &destination_directory);

          if (F_status_is_error(*status)) {
            fll_error_print(main.error, F_status_set_fine(*status), "f_file_name_directory", F_true);
            break;
          }

          *status = f_string_dynamic_terminate_after(&destination_directory);

          if (F_status_is_error(*status)) {
            fll_error_print(main.error, F_status_set_fine(*status), "f_string_dynamic_terminate_after", F_true);
            break;
          }

          *status = fl_directory_create(destination_directory.string, destination_directory.used, f_file_mode_all_rwx);

          if (F_status_is_error(*status)) {
            fll_error_file_print(main.error, F_status_set_fine(*status), "fl_directory_create", F_true, destination_directory.string, "create", fll_error_file_type_directory);
            break;
          }

          *status = f_string_append(path_source.string + preserve, path_source.used - preserve, &destination_file);

          if (F_status_is_error(*status)) {
            fll_error_print(main.error, F_status_set_fine(*status), "f_string_append", F_true);
            break;
          }
        }
        else {
          *status = f_file_name_base(path_source.string, path_source.used, &destination_file);

          if (F_status_is_error(*status)) {
            fll_error_print(main.error, F_status_set_fine(*status), "f_file_name_base", F_true);
            break;
          }
        }

        *status = f_string_dynamic_terminate_after(&destination_file);

        if (F_status_is_error(*status)) {
          fll_error_print(main.error, F_status_set_fine(*status), "f_string_dynamic_terminate_after", F_true);
          break;
        }

        if (fake_signal_received(main)) {
          *status = F_status_set_error(F_signal);
          break;
        }

        *status = f_file_copy(path_source.string, destination_file.string, mode, f_file_default_read_size, F_false);

        if (F_status_is_error(*status)) {
          fake_print_error_build_operation_file(main, F_status_set_fine(*status), "f_file_copy", "copy", "to", path_source.string, destination_file.string, F_true);
          break;
        }

        if (main.error.verbosity == f_console_verbosity_verbose) {
          fll_print_format("Copied file '%Q' to '%Q'.%c", main.output.to.stream, path_source, destination_file, f_string_eol_s[0]);
        }
      }
      else if (F_status_is_error(*status)) {
        fll_error_file_print(main.error, F_status_set_fine(*status), "f_directory_is", F_true, path_source.string, "create", fll_error_file_type_file);
        break;
      }

      *status = F_none;
    } // for

    macro_f_directory_statuss_t_delete_simple(failures);
    macro_f_string_dynamic_t_delete_simple(path_source);
    macro_f_string_dynamic_t_delete_simple(destination_file);
    macro_f_string_dynamic_t_delete_simple(destination_directory);

    if (F_status_is_error_not(*status)) {
      fake_build_touch(main, file_stage, status);
    }
  }
#endif // _di_fake_build_copy_

#ifndef _di_fake_build_skeleton_
  void fake_build_skeleton(const fake_main_t main, const fake_build_data_t data_build, const mode_t mode, const f_string_static_t file_stage, f_status_t *status) {

    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true || *status == F_child) return;

    if (fake_signal_received(main)) {
      *status = F_status_set_error(F_signal);
      return;
    }

    f_string_static_t path_headers = f_string_static_t_initialize;
    f_array_length_t directory_headers_length = main.path_build_includes.used + data_build.setting.path_headers.used;

    char directory_headers[directory_headers_length + 1];

    if (data_build.setting.path_headers.used) {
      memcpy(directory_headers, main.path_build_includes.string, main.path_build_includes.used);
      memcpy(directory_headers + main.path_build_includes.used, data_build.setting.path_headers.string, data_build.setting.path_headers.used);

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
      &main.path_build,
      &main.path_build_documents,
      &main.path_build_includes,
      &main.path_build_libraries,
      &main.path_build_libraries_script,
      &main.path_build_libraries_shared,
      &main.path_build_libraries_static,
      &main.path_build_objects,
      &main.path_build_programs,
      &main.path_build_programs_script,
      &main.path_build_programs_shared,
      &main.path_build_programs_static,
      &main.path_build_settings,
      &main.path_build_stage,
      &path_headers,
    };

    if (main.output.verbosity != f_console_verbosity_quiet) {
      fll_print_format("%c%[Creating base build directories.%]%c", main.output.to.stream, f_string_eol_s[0], main.context.set.important, main.context.set.important, f_string_eol_s[0]);
    }

    for (uint8_t i = 0; i < 15; ++i) {

      if (!directorys[i]->used) continue;

      if (fake_signal_received(main)) {
        *status = F_status_set_error(F_signal);

        return;
      }

      // @todo implement this in a common function and use across project for creating parent directories.
      for (f_array_length_t j = 0; j < directorys[i]->used; ++j) {

        if (directorys[i]->string[j] != f_path_separator_s[0]) continue;

        directorys[i]->string[j] = 0;

        *status = f_directory_exists(directorys[i]->string);

        if (F_status_is_error(*status) || *status == F_false) {
          directorys[i]->string[j] = f_path_separator_s[0];

          break;
        }

        if (*status == F_file_found_not) {
          *status = f_directory_create(directorys[i]->string, mode);
        }

        directorys[i]->string[j] = f_path_separator_s[0];

        if (F_status_is_error(*status)) break;
      } // for

      if (F_status_is_fine(*status)) {
        *status = f_directory_create(directorys[i]->string, mode);
      }

      if (F_status_is_error(*status)) {
        if (F_status_set_fine(*status) == F_file_found) {
          *status = F_none;
          continue;
        }

        fll_error_file_print(main.error, F_status_set_fine(*status), "f_directory_create", F_true, directorys[i]->string, "create", fll_error_file_type_directory);
        return;
      }

      if (main.error.verbosity == f_console_verbosity_verbose) {
        fll_print_format("Created directory '%Q'.%c", main.output.to.stream, directorys[i], f_string_eol_s[0]);
      }
    } // for

    fake_build_touch(main, file_stage, status);
  }
#endif // _di_fake_build_skeleton_

#ifndef _di_fake_build_execute_process_script_
  int fake_build_execute_process_script(const fake_main_t main, const fake_build_data_t data_build, const f_string_static_t process_script, const f_string_static_t file_stage, f_status_t *status) {

    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true || *status == F_child) return main.child;
    if (!process_script.used) return 0;

    if (fake_signal_received(main)) {
      *status = F_status_set_error(F_signal);

      return 0;
    }

    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;

    *status = fll_execute_arguments_add(fake_other_operation_build, fake_other_operation_build_length, &arguments);

    // ensure console color mode is passed to the scripts so that they can also react to color mode.
    if (F_status_is_error_not(*status) && main.context.mode != f_color_mode_none) {
      char argument[3] = { f_console_symbol_short_disable_s[0], 0, 0 };

      if (main.context.mode == f_color_mode_dark) {
        argument[1] = f_console_standard_short_dark_s[0];
      }
      else if (main.context.mode == f_color_mode_light) {
        argument[1] = f_console_standard_short_light_s[0];
      }
      else if (main.context.mode == f_color_mode_no_color) {
        argument[1] = f_console_standard_short_no_color_s[0];
      }

      *status = fll_execute_arguments_add(argument, 2, &arguments);
    }

    // ensure verbosity level is passed to the scripts so that they can also react to requested verbosity.
    if (F_status_is_error_not(*status) && main.error.verbosity != f_console_verbosity_normal) {
      char argument[3] = { f_console_symbol_short_disable_s[0], 0, 0 };

      if (main.error.verbosity == f_console_verbosity_quiet) {
        argument[1] = f_console_standard_short_quiet_s[0];
      }
      else if (main.error.verbosity == f_console_verbosity_verbose) {
        argument[1] = f_console_standard_short_verbose_s[0];
      }
      else if (main.error.verbosity == f_console_verbosity_debug) {
        argument[1] = f_console_standard_short_debug_s[0];
      }

      *status = fll_execute_arguments_add(argument, 2, &arguments);
    }

    if (F_status_is_error(*status)) {
      fll_error_print(main.error, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);

      macro_f_string_dynamics_t_delete_simple(arguments);
      return 0;
    }

    {
      f_string_dynamic_t defines = f_string_dynamic_t_initialize;

      if (main.define.used) {
        for (f_array_length_t i = 0; i < main.define.used; ++i) {

          *status = f_string_dynamic_mash(f_string_space_s, 1, main.define.array[i], &defines);

          if (F_status_is_error(*status)) {
            break;
          }
        } // for

        if (F_status_is_error(*status)) {
          fll_error_print(main.error, F_status_set_fine(*status), "f_string_dynamic_mash", F_true);

          macro_f_string_dynamic_t_delete_simple(defines);
          macro_f_string_dynamics_t_delete_simple(arguments);
          return 0;
        }

        *status = f_string_dynamic_terminate_after(&defines);

        if (F_status_is_error(*status)) {
          fll_error_print(main.error, F_status_set_fine(*status), "f_string_dynamic_terminate_after", F_true);

          macro_f_string_dynamic_t_delete_simple(defines);
          macro_f_string_dynamics_t_delete_simple(arguments);
          return 0;
        }
      }

      const f_string_t parameters_prefix[] = {
        f_console_symbol_short_enable_s,
        f_console_symbol_short_enable_s,
        f_console_symbol_short_enable_s,
        f_console_symbol_short_enable_s,
        f_console_symbol_short_enable_s,
        f_console_symbol_short_enable_s,
        f_console_symbol_short_enable_s,
      };

      const f_array_length_t parameters_prefix_length[] = {
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

      const f_array_length_t parameters_name_length[] = {
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
        main.process.string,
        main.settings.string,
        main.path_build.string,
        main.path_data.string,
        main.path_sources.string,
        main.path_work.string,
      };

      const f_array_length_t parameters_value_length[] = {
        defines.used,
        main.process.used,
        main.settings.used,
        main.path_build.used,
        main.path_data.used,
        main.path_sources.used,
        main.path_work.used,
      };

      *status = fll_execute_arguments_add_parameter_set(parameters_prefix, parameters_prefix_length, parameters_name, parameters_name_length, parameters_value, parameters_value_length, 7, &arguments);

      macro_f_string_dynamic_t_delete_simple(defines);

      if (F_status_is_error(*status)) {
        fll_error_print(main.error, F_status_set_fine(*status), "fll_execute_arguments_add_parameter_set", F_true);

        macro_f_string_dynamics_t_delete_simple(arguments);
        return 0;
      }
    }

    f_string_dynamic_t path = f_string_dynamic_t_initialize;
    f_string_t function = 0;

    {
      function = "f_string_dynamic_append_nulless";

      if (process_script.string[0] != '/') {
        *status = f_string_dynamic_append_nulless(main.path_data_build, &path);
      }

      if (F_status_is_error_not(*status)) {
        *status = f_string_dynamic_append_nulless(process_script, &path);
      }

      if (F_status_is_error_not(*status)) {
        function = "f_string_dynamic_terminate_after";
        *status = f_string_dynamic_terminate_after(&path);
      }

      if (F_status_is_error(*status)) {
        fll_error_print(main.error, F_status_set_fine(*status), function, F_true);

        macro_f_string_dynamic_t_delete_simple(path);
        macro_f_string_dynamics_t_delete_simple(arguments);
        return 0;
      }
    }

    int return_code = 0;

    if (fake_signal_received(main)) {
      *status = F_status_set_error(F_signal);

      macro_f_string_dynamic_t_delete_simple(path);
      macro_f_string_dynamics_t_delete_simple(arguments);
    }
    else {
      // child processes should receive all signals, without blocking.
      f_signal_how_t signals = f_signal_how_t_initialize;
      f_signal_set_empty(&signals.block);
      f_signal_set_fill(&signals.block_not);

      fl_execute_parameter_t parameter = macro_fl_execute_parameter_t_initialize(fl_execute_parameter_option_path, 0, &data_build.environment, &signals, 0);

      *status = fll_execute_program(path.string, arguments, &parameter, 0, (void *) &return_code);

      macro_f_string_dynamics_t_delete_simple(arguments);

      if (fake_signal_received(main)) {
        *status = F_status_set_error(F_signal);
      }
      else if (*status != F_child) {
        if (F_status_is_error(*status)) {
          if (F_status_set_fine(*status) == F_failure) {
            if (main.error.verbosity != f_console_verbosity_quiet) {
              flockfile(main.error.to.stream);

              fl_print_format("%c%[%SFailed to execute script: '%]", main.error.to.stream, f_string_eol_s[0], main.error.context, main.error.prefix, main.error.context);
              fl_print_format("%[%Q%]", main.error.to.stream, main.error.notable, path, main.error.notable);
              fl_print_format("%['.%]%c", main.error.to.stream, main.error.context, main.error.context, f_string_eol_s[0]);

              funlockfile(main.error.to.stream);
            }
          }
          else {
            fll_error_print(main.error, F_status_set_fine(*status), "fll_execute_program", F_true);
          }
        }
        else {
          fake_build_touch(main, file_stage, status);
        }
      }
    }

    macro_f_string_dynamic_t_delete_simple(path);

    return return_code;
  }
#endif // _di_fake_build_execute_process_script_

#ifndef _di_fake_build_get_file_name_without_extension_
  f_status_t fake_build_get_file_name_without_extension(const fake_main_t main, const f_string_static_t path, f_string_dynamic_t *name) {

    name->used = 0;

    if (!path.used) return F_none;

    f_status_t status = f_file_name_base(path.string, path.used, name);

    if (F_status_is_error(status)) {
      fll_error_print(main.error, F_status_set_fine(status), "f_file_name_base", F_true);

      return status;
    }

    f_array_length_t i = name->used;

    for (; i > 0; --i) {

      if (name->string[i] == f_path_extension_separator[0]) {
        name->used = i;
        break;
      }
    } // for

    status = f_string_dynamic_terminate_after(name);

    if (F_status_is_error(status)) {
      fll_error_print(main.error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);

      return status;
    }

    return F_none;
  }
#endif // _di_fake_build_get_file_name_without_extension_

#ifndef _di_fake_build_libraries_script_
  int fake_build_libraries_script(const fake_main_t main, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true || *status == F_child) return main.child;

    // @todo needs to perform some sort of regex replace on the library scripts.

    fake_build_touch(main, file_stage, status);

    return 0;
  }
#endif // _di_fake_build_libraries_script_

#ifndef _di_fake_build_library_shared_
  int fake_build_library_shared(const fake_main_t main, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) {

    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true || *status == F_child) return main.child;
    if (!data_build.setting.build_sources_library.used) return 0;

    if (main.output.verbosity != f_console_verbosity_quiet) {
      fll_print_format("%c%[Compiling shared library.%]%c", main.output.to.stream, f_string_eol_s[0], main.context.set.important, main.context.set.important, f_string_eol_s[0]);
    }

    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;

    {
      const f_string_static_t *path_sources = &main.path_sources;

      if (data_build.setting.path_standard) {
        path_sources = &main.path_sources_c;

        if (data_build.setting.build_language == fake_build_language_type_cpp) {
          path_sources = &main.path_sources_cpp;
        }
      }
      else if (main.parameters[fake_parameter_path_sources].result != f_console_result_additional) {
        path_sources = &data_build.setting.path_sources;
      }

      f_array_length_t source_length = 0;

      for (f_array_length_t i = 0; i < data_build.setting.build_sources_library.used; ++i) {

        source_length = path_sources->used + data_build.setting.build_sources_library.array[i].used;

        char source[source_length + 1];

        memcpy(source, path_sources->string, path_sources->used);
        memcpy(source + path_sources->used, data_build.setting.build_sources_library.array[i].string, data_build.setting.build_sources_library.array[i].used);
        source[source_length] = 0;

        *status = fll_execute_arguments_add(source, source_length, &arguments);
        if (F_status_is_error(*status)) break;
      } // for

      if (F_status_is_error(*status)) {
        fll_error_print(main.error, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);

        macro_f_string_dynamics_t_delete_simple(arguments);
        return 0;
      }
    }

    const f_array_length_t parameter_file_name_length = fake_build_parameter_library_name_prefix_length + data_build.setting.project_name.used + fake_build_parameter_library_name_suffix_shared_length;
    const f_array_length_t parameter_file_name_major_length = data_build.setting.version_major.used ? parameter_file_name_length + data_build.setting.version_major_prefix.used + data_build.setting.version_major.used : 0;
    const f_array_length_t parameter_file_name_minor_length = data_build.setting.version_minor.used ? parameter_file_name_major_length + data_build.setting.version_minor_prefix.used + data_build.setting.version_minor.used : 0;
    const f_array_length_t parameter_file_name_micro_length = data_build.setting.version_micro.used ? parameter_file_name_minor_length + data_build.setting.version_micro_prefix.used + data_build.setting.version_micro.used : 0;
    const f_array_length_t parameter_file_name_nano_length = data_build.setting.version_nano.used ? parameter_file_name_micro_length + data_build.setting.version_nano_prefix.used + data_build.setting.version_nano.used : 0;

    char parameter_file_name[parameter_file_name_length + 1];
    char parameter_file_name_major[parameter_file_name_major_length + 1];
    char parameter_file_name_minor[parameter_file_name_minor_length + 1];
    char parameter_file_name_micro[parameter_file_name_micro_length + 1];
    char parameter_file_name_nano[parameter_file_name_nano_length + 1];

    parameter_file_name[parameter_file_name_length] = 0;
    parameter_file_name_major[parameter_file_name_major_length] = 0;
    parameter_file_name_minor[parameter_file_name_minor_length] = 0;
    parameter_file_name_micro[parameter_file_name_micro_length] = 0;
    parameter_file_name_nano[parameter_file_name_nano_length] = 0;

    memcpy(parameter_file_name, fake_build_parameter_library_name_prefix, fake_build_parameter_library_name_prefix_length);

    if (parameter_file_name_major_length) {
      memcpy(parameter_file_name_major, fake_build_parameter_library_name_prefix, fake_build_parameter_library_name_prefix_length);

      if (parameter_file_name_minor_length) {
        memcpy(parameter_file_name_minor, fake_build_parameter_library_name_prefix, fake_build_parameter_library_name_prefix_length);

        if (parameter_file_name_micro_length) {
          memcpy(parameter_file_name_micro, fake_build_parameter_library_name_prefix, fake_build_parameter_library_name_prefix_length);

          if (parameter_file_name_nano_length) {
            memcpy(parameter_file_name_nano, fake_build_parameter_library_name_prefix, fake_build_parameter_library_name_prefix_length);
          }
        }
      }
    }

    f_array_length_t count = fake_build_parameter_library_name_prefix_length;

    memcpy(parameter_file_name + count, data_build.setting.project_name.string, data_build.setting.project_name.used);

    if (parameter_file_name_major_length) {
      memcpy(parameter_file_name_major + count, data_build.setting.project_name.string, data_build.setting.project_name.used);

      if (parameter_file_name_minor_length) {
        memcpy(parameter_file_name_minor + count, data_build.setting.project_name.string, data_build.setting.project_name.used);

        if (parameter_file_name_micro_length) {
          memcpy(parameter_file_name_micro + count, data_build.setting.project_name.string, data_build.setting.project_name.used);

          if (parameter_file_name_nano_length) {
            memcpy(parameter_file_name_nano + count, data_build.setting.project_name.string, data_build.setting.project_name.used);
          }
        }
      }
    }

    count += data_build.setting.project_name.used;

    memcpy(parameter_file_name + count, fake_build_parameter_library_name_suffix_shared, fake_build_parameter_library_name_suffix_shared_length);

    if (parameter_file_name_major_length) {
      memcpy(parameter_file_name_major + count, fake_build_parameter_library_name_suffix_shared, fake_build_parameter_library_name_suffix_shared_length);

      if (parameter_file_name_minor_length) {
        memcpy(parameter_file_name_minor + count, fake_build_parameter_library_name_suffix_shared, fake_build_parameter_library_name_suffix_shared_length);

        if (parameter_file_name_micro_length) {
          memcpy(parameter_file_name_micro + count, fake_build_parameter_library_name_suffix_shared, fake_build_parameter_library_name_suffix_shared_length);

          if (parameter_file_name_nano_length) {
            memcpy(parameter_file_name_nano + count, fake_build_parameter_library_name_suffix_shared, fake_build_parameter_library_name_suffix_shared_length);
          }
        }
      }
    }

    if (parameter_file_name_major_length) {
      count += fake_build_parameter_library_name_suffix_shared_length;

      if (data_build.setting.version_major_prefix.used) {
        memcpy(parameter_file_name_major + count, data_build.setting.version_major_prefix.string, data_build.setting.version_major_prefix.used);

        if (parameter_file_name_minor_length) {
          memcpy(parameter_file_name_minor + count, data_build.setting.version_major_prefix.string, data_build.setting.version_major_prefix.used);

          if (parameter_file_name_micro_length) {
            memcpy(parameter_file_name_micro + count, data_build.setting.version_major_prefix.string, data_build.setting.version_major_prefix.used);

            if (parameter_file_name_nano_length) {
              memcpy(parameter_file_name_nano + count, data_build.setting.version_major_prefix.string, data_build.setting.version_major_prefix.used);
            }
          }
        }

        count += data_build.setting.version_major_prefix.used;
      }

      memcpy(parameter_file_name_major + count, data_build.setting.version_major.string, data_build.setting.version_major.used);

      if (parameter_file_name_minor_length) {
        memcpy(parameter_file_name_minor + count, data_build.setting.version_major.string, data_build.setting.version_major.used);

        if (parameter_file_name_micro_length) {
          memcpy(parameter_file_name_micro + count, data_build.setting.version_major.string, data_build.setting.version_major.used);

          if (parameter_file_name_nano_length) {
            memcpy(parameter_file_name_nano + count, data_build.setting.version_major.string, data_build.setting.version_major.used);
          }
        }
      }

      if (parameter_file_name_minor_length) {
        count += data_build.setting.version_major.used;

        if (data_build.setting.version_minor_prefix.used) {
          memcpy(parameter_file_name_minor + count, data_build.setting.version_minor_prefix.string, data_build.setting.version_minor_prefix.used);

          if (parameter_file_name_micro_length) {
            memcpy(parameter_file_name_micro + count, data_build.setting.version_minor_prefix.string, data_build.setting.version_minor_prefix.used);

            if (parameter_file_name_nano_length) {
              memcpy(parameter_file_name_nano + count, data_build.setting.version_minor_prefix.string, data_build.setting.version_minor_prefix.used);
            }
          }

          count += data_build.setting.version_minor_prefix.used;
        }

        memcpy(parameter_file_name_minor + count, data_build.setting.version_minor.string, data_build.setting.version_minor.used);

        if (parameter_file_name_micro_length) {
          memcpy(parameter_file_name_micro + count, data_build.setting.version_minor.string, data_build.setting.version_minor.used);

          if (parameter_file_name_nano_length) {
            memcpy(parameter_file_name_nano + count, data_build.setting.version_minor.string, data_build.setting.version_minor.used);
          }
        }

        if (parameter_file_name_micro_length) {
          count += data_build.setting.version_minor.used;

          if (data_build.setting.version_micro_prefix.used) {
            memcpy(parameter_file_name_micro + count, data_build.setting.version_micro_prefix.string, data_build.setting.version_micro_prefix.used);

            if (parameter_file_name_nano_length) {
              memcpy(parameter_file_name_nano + count, data_build.setting.version_micro_prefix.string, data_build.setting.version_micro_prefix.used);
            }

            count += data_build.setting.version_micro_prefix.used;
          }

          memcpy(parameter_file_name_micro + count, data_build.setting.version_micro.string, data_build.setting.version_micro.used);

          if (parameter_file_name_nano_length) {
            memcpy(parameter_file_name_nano + count, data_build.setting.version_micro.string, data_build.setting.version_micro.used);

            count += data_build.setting.version_micro.used;

            if (data_build.setting.version_nano_prefix.used) {
              memcpy(parameter_file_name_nano + count, data_build.setting.version_nano_prefix.string, data_build.setting.version_nano_prefix.used);
              count += data_build.setting.version_nano_prefix.used;
            }

            memcpy(parameter_file_name_nano + count, data_build.setting.version_nano.string, data_build.setting.version_nano.used);
          }
        }
      }
    }

    {
      f_array_length_t parameter_linker_length = fake_build_parameter_library_shared_prefix_length;
      f_array_length_t parameter_file_path_length = main.path_build_libraries_shared.used;

      if (data_build.setting.version_file == fake_build_version_type_major) {
        parameter_file_path_length += parameter_file_name_major_length;
      }
      else if (data_build.setting.version_file == fake_build_version_type_minor) {
        parameter_file_path_length += parameter_file_name_minor_length;
      }
      else if (data_build.setting.version_file == fake_build_version_type_micro) {
        parameter_file_path_length += parameter_file_name_micro_length;
      }
      else if (data_build.setting.version_file == fake_build_version_type_nano) {
        parameter_file_path_length += parameter_file_name_nano_length;
      }

      if (data_build.setting.version_target == fake_build_version_type_major) {
        parameter_linker_length += parameter_file_name_major_length;
      }
      else if (data_build.setting.version_target == fake_build_version_type_minor) {
        parameter_linker_length += parameter_file_name_minor_length;
      }
      else if (data_build.setting.version_target == fake_build_version_type_micro) {
        parameter_linker_length += parameter_file_name_micro_length;
      }
      else if (data_build.setting.version_target == fake_build_version_type_nano) {
        parameter_linker_length += parameter_file_name_nano_length;
      }

      char parameter_linker[parameter_linker_length + 1];
      char parameter_file_path[parameter_file_path_length + 1];

      memcpy(parameter_linker, fake_build_parameter_library_shared_prefix, fake_build_parameter_library_shared_prefix_length);
      memcpy(parameter_file_path, main.path_build_libraries_shared.string, main.path_build_libraries_shared.used);

      if (data_build.setting.version_file == fake_build_version_type_major) {
        memcpy(parameter_file_path + main.path_build_libraries_shared.used, parameter_file_name_major, parameter_file_name_major_length);
      }
      else if (data_build.setting.version_file == fake_build_version_type_minor) {
        memcpy(parameter_file_path + main.path_build_libraries_shared.used, parameter_file_name_minor, parameter_file_name_minor_length);
      }
      else if (data_build.setting.version_file == fake_build_version_type_micro) {
        memcpy(parameter_file_path + main.path_build_libraries_shared.used, parameter_file_name_micro, parameter_file_name_micro_length);
      }
      else if (data_build.setting.version_file == fake_build_version_type_nano) {
        memcpy(parameter_file_path + main.path_build_libraries_shared.used, parameter_file_name_nano, parameter_file_name_nano_length);
      }

      if (data_build.setting.version_target == fake_build_version_type_major) {
        memcpy(parameter_linker + fake_build_parameter_library_shared_prefix_length, parameter_file_name_major, parameter_file_name_major_length);
      }
      else if (data_build.setting.version_target == fake_build_version_type_minor) {
        memcpy(parameter_linker + fake_build_parameter_library_shared_prefix_length, parameter_file_name_minor, parameter_file_name_minor_length);
      }
      else if (data_build.setting.version_target == fake_build_version_type_micro) {
        memcpy(parameter_linker + fake_build_parameter_library_shared_prefix_length, parameter_file_name_micro, parameter_file_name_micro_length);
      }
      else if (data_build.setting.version_target == fake_build_version_type_nano) {
        memcpy(parameter_linker + fake_build_parameter_library_shared_prefix_length, parameter_file_name_nano, parameter_file_name_nano_length);
      }

      parameter_linker[parameter_linker_length] = 0;
      parameter_file_path[parameter_file_path_length] = 0;

      const f_string_t values[] = {
        fake_build_parameter_library_shared,
        parameter_linker,
        fake_build_parameter_library_output,
        parameter_file_path,
      };

      const f_array_length_t lengths[] = {
        fake_build_parameter_library_shared_length,
        parameter_linker_length,
        fake_build_parameter_library_output_length,
        parameter_file_path_length,
      };

      for (uint8_t i = 0; i < 4; ++i) {

        *status = fll_execute_arguments_add(values[i], lengths[i], &arguments);
        if (F_status_is_error(*status)) break;
      } // for

      fake_build_arguments_standard_add(main, data_build, F_true, F_true, &arguments, status);

      if (F_status_is_error(*status)) {
        fll_error_print(main.error, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);

        macro_f_string_dynamics_t_delete_simple(arguments);

        return 0;
      }
    }

    {
      const int result = fake_execute(main, data_build.environment, data_build.setting.build_compiler, arguments, status);

      macro_f_string_dynamics_t_delete_simple(arguments);

      if (F_status_is_error(*status)) {
        return 0;
      }

      if (*status == F_child) {
        return result;
      }
    }

    if (parameter_file_name_major_length) {

      f_array_length_t parameter_file_path_length = main.path_build_libraries_shared.used + parameter_file_name_length;

      char parameter_file_path[parameter_file_path_length + 1];

      memcpy(parameter_file_path, main.path_build_libraries_shared.string, main.path_build_libraries_shared.used);
      memcpy(parameter_file_path + main.path_build_libraries_shared.used, parameter_file_name, parameter_file_name_length);

      parameter_file_path[parameter_file_path_length] = 0;

      if (fake_signal_received(main)) {
        *status = F_status_set_error(F_signal);

        return 0;
      }

      *status = f_file_link(parameter_file_name_major, parameter_file_path);

      if (F_status_is_error_not(*status) && main.error.verbosity == f_console_verbosity_verbose) {
        fll_print_format("Linked file '%S' to '%S'.%c", main.output.to.stream, parameter_file_path, parameter_file_name_major, f_string_eol_s[0]);
      }
      else if (F_status_is_error(*status)) {
        if (F_status_set_fine(*status) == F_file_found) {
          fll_error_file_print(main.error, F_status_set_fine(*status), "f_file_link", F_true, parameter_file_path, "link", fll_error_file_type_file);

          return 0;
        }

        fll_error_file_print(main.error, F_status_set_fine(*status), "f_file_link", F_true, parameter_file_name_major, "link", fll_error_file_type_file);

        return 0;
      }
    }

    if (data_build.setting.version_file != fake_build_version_type_major && parameter_file_name_major_length) {

      f_array_length_t parameter_file_path_length = main.path_build_libraries_shared.used + parameter_file_name_major_length;

      char parameter_file_path[parameter_file_path_length + 1];

      memcpy(parameter_file_path, main.path_build_libraries_shared.string, main.path_build_libraries_shared.used);
      memcpy(parameter_file_path + main.path_build_libraries_shared.used, parameter_file_name_major, parameter_file_name_major_length);

      parameter_file_path[parameter_file_path_length] = 0;

      if (fake_signal_received(main)) {
        *status = F_status_set_error(F_signal);

        return 0;
      }

      *status = f_file_link(parameter_file_name_minor, parameter_file_path);

      if (F_status_is_error_not(*status) && main.error.verbosity == f_console_verbosity_verbose) {
        fll_print_format("Linked file '%S' to '%S'.%c", main.output.to.stream, parameter_file_path, parameter_file_name_minor, f_string_eol_s[0]);
      }
      else if (F_status_is_error(*status)) {
        if (F_status_set_fine(*status) == F_file_found) {
          fll_error_file_print(main.error, F_status_set_fine(*status), "f_file_link", F_true, parameter_file_path, "link", fll_error_file_type_file);

          return 0;
        }

        fll_error_file_print(main.error, F_status_set_fine(*status), "f_file_link", F_true, parameter_file_name_minor, "link", fll_error_file_type_file);

        return 0;
      }

      if (data_build.setting.version_file != fake_build_version_type_minor && parameter_file_name_minor_length) {

        f_array_length_t parameter_file_path_length = main.path_build_libraries_shared.used + parameter_file_name_minor_length;

        char parameter_file_path[parameter_file_path_length + 1];

        memcpy(parameter_file_path, main.path_build_libraries_shared.string, main.path_build_libraries_shared.used);
        memcpy(parameter_file_path + main.path_build_libraries_shared.used, parameter_file_name_minor, parameter_file_name_minor_length);

        parameter_file_path[parameter_file_path_length] = 0;

        if (fake_signal_received(main)) {
          *status = F_status_set_error(F_signal);

          return 0;
        }

        *status = f_file_link(parameter_file_name_micro, parameter_file_path);

        if (F_status_is_error_not(*status) && main.error.verbosity == f_console_verbosity_verbose) {
          fll_print_format("Linked file '%S' to '%S'.%c", main.output.to.stream, parameter_file_path, parameter_file_name_micro, f_string_eol_s[0]);
        }
        else if (F_status_is_error(*status)) {
          if (F_status_set_fine(*status) == F_file_found) {
            fll_error_file_print(main.error, F_status_set_fine(*status), "f_file_link", F_true, parameter_file_path, "link", fll_error_file_type_file);

            return 0;
          }

          fll_error_file_print(main.error, F_status_set_fine(*status), "f_file_link", F_true, parameter_file_name_micro, "link", fll_error_file_type_file);

          return 0;
        }

        if (data_build.setting.version_file != fake_build_version_type_micro && parameter_file_name_micro_length) {

          f_array_length_t parameter_file_path_length = main.path_build_libraries_shared.used + parameter_file_name_micro_length;

          char parameter_file_path[parameter_file_path_length + 1];

          memcpy(parameter_file_path, main.path_build_libraries_shared.string, main.path_build_libraries_shared.used);
          memcpy(parameter_file_path + main.path_build_libraries_shared.used, parameter_file_name_micro, parameter_file_name_micro_length);

          parameter_file_path[parameter_file_path_length] = 0;

          if (fake_signal_received(main)) {
            *status = F_status_set_error(F_signal);

            return 0;
          }

          *status = f_file_link(parameter_file_name_nano, parameter_file_path);

          if (F_status_is_error_not(*status) && main.error.verbosity == f_console_verbosity_verbose) {
            fll_print_format("Linked file '%S' to '%S'.%c", main.output.to.stream, parameter_file_path, parameter_file_name_nano, f_string_eol_s[0]);
          }
          else if (F_status_is_error(*status)) {
            if (F_status_set_fine(*status) == F_file_found) {
              fll_error_file_print(main.error, F_status_set_fine(*status), "f_file_link", F_true, parameter_file_path, "link", fll_error_file_type_file);

              return 0;
            }

            fll_error_file_print(main.error, F_status_set_fine(*status), "f_file_link", F_true, parameter_file_name_nano, "link", fll_error_file_type_file);

            return 0;
          }
        }
      }
    }

    fake_build_touch(main, file_stage, status);

    return 0;
  }
#endif // _di_fake_build_library_shared_

#ifndef _di_fake_build_library_static_
  int fake_build_library_static(const fake_main_t main, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) {

    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true || *status == F_child) return main.child;
    if (!data_build.setting.build_sources_library.used) return 0;

    if (main.output.verbosity != f_console_verbosity_quiet) {
      fll_print_format("%c%[Compiling static library.%]%c", main.output.to.stream, f_string_eol_s[0], main.context.set.important, main.context.set.important, f_string_eol_s[0]);
    }

    f_string_dynamic_t file_name = f_string_dynamic_t_initialize;
    f_string_dynamic_t source_path = f_string_dynamic_t_initialize;
    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;

    *status = fll_execute_arguments_add(fake_build_parameter_object_link_arguments, fake_build_parameter_object_link_arguments_length, &arguments);

    if (F_status_is_error_not(*status)) {
      f_array_length_t destination_length = main.path_build_libraries_static.used + fake_build_parameter_library_name_prefix_length;
      destination_length += data_build.setting.project_name.used + fake_build_parameter_library_name_suffix_static_length;

      char destination[destination_length + 1];

      destination_length = 0;

      memcpy(destination, main.path_build_libraries_static.string, main.path_build_libraries_static.used);
      destination_length += main.path_build_libraries_static.used;

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
      f_array_length_t source_length = 0;

      for (f_array_length_t i = 0; i < data_build.setting.build_sources_library.used; ++i) {

        source_path.used = 0;

        *status = fake_build_get_file_name_without_extension(main, data_build.setting.build_sources_library.array[i], &file_name);

        if (F_status_is_error(*status)) {
          fll_error_print(main.error, F_status_set_fine(*status), "fake_build_get_file_name_without_extension", F_true);
          break;
        }

        if (fake_signal_received(main)) {
          *status = F_status_set_error(F_signal);
          break;
        }

        *status = f_file_name_directory(data_build.setting.build_sources_library.array[i].string, data_build.setting.build_sources_library.array[i].used, &source_path);

        if (F_status_is_error(*status)) {
          fll_error_print(main.error, F_status_set_fine(*status), "f_file_name_directory", F_true);
          break;
        }

        if (source_path.used) {
          *status = f_string_dynamic_prepend(main.path_build_objects, &source_path);

          if (F_status_is_error(*status)) {
            fll_error_print(main.error, F_status_set_fine(*status), "f_string_dynamic_prepend", F_true);
            break;
          }

          *status = f_string_append_assure(f_path_separator_s, f_path_separator_length, &source_path);

          if (F_status_is_error(*status)) {
            fll_error_print(main.error, F_status_set_fine(*status), "f_string_append_assure", F_true);
            break;
          }

          *status = f_string_dynamic_terminate_after(&source_path);

          if (F_status_is_error(*status)) {
            fll_error_print(main.error, F_status_set_fine(*status), "f_string_dynamic_terminate_after", F_true);
            break;
          }

          source_length = source_path.used + file_name.used + fake_build_parameter_object_name_suffix_length;
        }
        else {
          source_length = main.path_build_objects.used + file_name.used + fake_build_parameter_object_name_suffix_length;
        }

        char source[source_length + 1];

        if (source_path.used) {
          memcpy(source, source_path.string, source_path.used);
          memcpy(source + source_path.used, file_name.string, file_name.used);
          memcpy(source + source_path.used + file_name.used, fake_build_parameter_object_name_suffix, fake_build_parameter_object_name_suffix_length);
        }
        else {
          memcpy(source, main.path_build_objects.string, main.path_build_objects.used);
          memcpy(source + main.path_build_objects.used, file_name.string, file_name.used);
          memcpy(source + main.path_build_objects.used + file_name.used, fake_build_parameter_object_name_suffix, fake_build_parameter_object_name_suffix_length);
        }

        source[source_length] = 0;

        *status = fll_execute_arguments_add(source, source_length, &arguments);

        if (F_status_is_error(*status)) {
          fll_error_print(main.error, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);
          break;
        }
      } // for
    }

    int result = main.child;

    if (F_status_is_error_not(*status)) {
      result = fake_execute(main, data_build.environment, data_build.setting.build_indexer, arguments, status);
    }

    macro_f_string_dynamic_t_delete_simple(file_name);
    macro_f_string_dynamic_t_delete_simple(source_path);
    macro_f_string_dynamics_t_delete_simple(arguments);

    if (F_status_is_error_not(*status) && *status != F_child) {
      fake_build_touch(main, file_stage, status);
    }

    return result;
  }
#endif // _di_fake_build_library_static_

#ifndef _di_fake_build_load_environment_
  void fake_build_load_environment(const fake_main_t main, const fake_build_data_t data_build, f_string_maps_t *environment, f_status_t *status) {

    if (F_status_is_error(*status)) return;

    // reset the environment.
    for (f_array_length_t i = 0; i < environment->used; ++i) {
      environment->array[i].name.used = 0;
      environment->array[i].value.used = 0;
    } // for

    environment->used = 0;

    {
      // add the guaranteed environment variables.
      const f_string_t variables_name[] = {
        f_path_environment_s,
        f_path_present_working_s
      };

      const f_array_length_t variables_length[] = {
        f_path_environment_length,
        f_path_present_working_length
      };

      for (uint8_t i = 0; i < 2; ++i) {

        *status = fl_environment_load_name(variables_name[i], variables_length[i], environment);

        if (F_status_is_error(*status)) {
          fll_error_print(main.error, F_status_set_fine(*status), "fl_environment_load_name", F_true);
          break;
        }
      } // for

      if (F_status_is_error(*status)) {
        return;
      }
    }

    if (environment->used + data_build.setting.environment.used > environment->size) {
      if (environment->used + data_build.setting.environment.used > f_environment_max_length) {
        if (main.error.verbosity != f_console_verbosity_quiet) {
          flockfile(main.error.to.stream);

          fl_print_format("%c%[%SThe values for the setting '%]", main.error.to.stream, f_string_eol_s[0], main.error.context, main.error.prefix, main.error.context);
          fl_print_format("%[%s%]", main.error.to.stream, main.error.notable, fake_build_setting_name_environment, main.error.notable);
          fl_print_format("%[' of setting file '%]", main.error.to.stream, main.error.context, main.error.context);
          fl_print_format("%[%s%]", main.error.to.stream, main.error.notable, fake_build_setting_name_environment, main.error.notable);
          fl_print_format("%[' is too large.%]%c", main.error.to.stream, main.error.context, main.error.context, f_string_eol_s[0]);

          flockfile(main.error.to.stream);
        }

        *status = F_status_set_error(F_array_too_large);
        return;
      }
    }

    *status = fl_environment_load_names(data_build.setting.environment, environment);

    if (F_status_is_error(*status)) {
      fll_error_print(main.error, F_status_set_fine(*status), "fl_environment_load_names", F_true);
    }
  }
#endif // _di_fake_build_load_environment_

#ifndef _di_fake_build_load_setting_
  void fake_build_load_setting(const fake_main_t main, const f_string_static_t setting_file, fake_build_setting_t *setting, f_status_t *status) {

    if (F_status_is_error(*status)) return;

    if (fake_signal_received(main)) {
      *status = F_status_set_error(F_signal);
      return;
    }

    char path_file[main.path_data_build.used + setting_file.used + 1];

    {
      f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

      f_fss_objects_t objects = f_fss_objects_t_initialize;
      f_fss_contents_t contents = f_fss_contents_t_initialize;

      if (setting_file.used) {
        memcpy(path_file, main.path_data_build.string, main.path_data_build.used);
        memcpy(path_file + main.path_data_build.used, setting_file.string, setting_file.used);

        path_file[main.path_data_build.used + setting_file.used] = 0;

        *status = fake_file_buffer(main, path_file, &buffer);
      }
      else {
        *status = fake_file_buffer(main, main.file_data_build_settings.string, &buffer);
      }

      if (fake_signal_received(main)) {
        *status = F_status_set_error(F_signal);
      }
      else if (F_status_is_error_not(*status)) {
        f_string_range_t range = macro_f_string_range_t_initialize(buffer.used);
        f_fss_delimits_t delimits = f_fss_delimits_t_initialize;

        {
          f_state_t state = macro_f_state_t_initialize(fake_common_allocation_large, fake_common_allocation_small, 0, &fake_signal_state_interrupt_fss, 0, (void *) &main, 0);

          *status = fll_fss_extended_read(buffer, state, &range, &objects, &contents, 0, 0, &delimits, 0);
        }

        if (F_status_is_error(*status)) {
          fake_print_error_fss(main, F_status_set_fine(*status), "fll_fss_extended_read", main.file_data_build_settings.string, range, F_true);
        }
        else {
          *status = fl_fss_apply_delimit(delimits, &buffer);

          if (F_status_is_error(*status)) {
            fll_error_print(main.error, F_status_set_fine(*status), "fl_fss_apply_delimit", F_true);
          }
          else {
            fake_build_load_setting_process(main, setting_file.used ? path_file : main.file_data_build_settings.string, buffer, objects, contents, setting, status);
          }
        }

        macro_f_fss_delimits_t_delete_simple(delimits);
      }

      macro_f_string_dynamic_t_delete_simple(buffer);
      macro_f_fss_objects_t_delete_simple(objects);
      macro_f_fss_contents_t_delete_simple(contents);
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

      for (uint8_t i = 0; i < 1; ++i) {

        if (!settings[i]->used) {
          flockfile(main.error.to.stream);

          fl_print_format("%c%[%SThe setting '%]", main.error.to.stream, f_string_eol_s[0], main.error.context, main.error.prefix, main.error.context);
          fl_print_format("%[%S%]", main.error.to.stream, main.error.notable, names[i], main.error.notable);
          fl_print_format("%[' is required but is not specified in the settings file '%]", main.error.to.stream, main.error.context, main.error.context);
          fl_print_format("%[%S%]", main.error.to.stream, main.error.notable, setting_file.used ? path_file : main.file_data_build_settings.string, main.error.notable);
          fl_print_format("%['.%]%c", main.error.to.stream, main.error.context, main.error.context, f_string_eol_s[0]);

          funlockfile(main.error.to.stream);

          failed = F_true;
        }
      } // for

      if (failed) {
        *status = F_status_set_error(F_failure);

        return;
      }
    }

    fake_build_load_setting_defaults(main, setting, status);
  }
#endif // _di_fake_build_load_setting_

#ifndef _di_fake_build_load_setting_process_
  void fake_build_load_setting_process(const fake_main_t main, const f_string_t path_file, const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, fake_build_setting_t *setting, f_status_t *status) {

    if (F_status_is_error(*status) && buffer.used) return;

    if (fake_signal_received(main)) {
      *status = F_status_set_error(F_signal);

      return;
    }

    bool error_printed = F_false;

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
    f_string_dynamics_t version_file = f_string_dynamics_t_initialize;
    f_string_dynamics_t version_major = f_string_dynamics_t_initialize;
    f_string_dynamics_t version_major_prefix = f_string_dynamics_t_initialize;
    f_string_dynamics_t version_micro = f_string_dynamics_t_initialize;
    f_string_dynamics_t version_micro_prefix = f_string_dynamics_t_initialize;
    f_string_dynamics_t version_minor = f_string_dynamics_t_initialize;
    f_string_dynamics_t version_minor_prefix = f_string_dynamics_t_initialize;
    f_string_dynamics_t version_nano = f_string_dynamics_t_initialize;
    f_string_dynamics_t version_nano_prefix = f_string_dynamics_t_initialize;
    f_string_dynamics_t version_target = f_string_dynamics_t_initialize;

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
      fake_build_setting_name_build_sources_script,
      fake_build_setting_name_build_sources_settings,
      fake_build_setting_name_build_static,
      fake_build_setting_name_defines_all,
      fake_build_setting_name_defines_library,
      fake_build_setting_name_defines_program,
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
      fake_build_setting_name_version_file,
      fake_build_setting_name_version_major,
      fake_build_setting_name_version_major_prefix,
      fake_build_setting_name_version_micro,
      fake_build_setting_name_version_micro_prefix,
      fake_build_setting_name_version_minor,
      fake_build_setting_name_version_minor_prefix,
      fake_build_setting_name_version_nano,
      fake_build_setting_name_version_nano_prefix,
      fake_build_setting_name_version_target,
    };

    const f_array_length_t settings_length[] = {
      fake_build_setting_name_build_compiler_length,
      fake_build_setting_name_build_indexer_length,
      fake_build_setting_name_build_language_length,
      fake_build_setting_name_build_libraries_length,
      fake_build_setting_name_build_script_length,
      fake_build_setting_name_build_shared_length,
      fake_build_setting_name_build_sources_headers_length,
      fake_build_setting_name_build_sources_library_length,
      fake_build_setting_name_build_sources_program_length,
      fake_build_setting_name_build_sources_script_length,
      fake_build_setting_name_build_sources_settings_length,
      fake_build_setting_name_build_static_length,
      fake_build_setting_name_defines_all_length,
      fake_build_setting_name_defines_library_length,
      fake_build_setting_name_defines_program_length,
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
      fake_build_setting_name_version_file_length,
      fake_build_setting_name_version_major_length,
      fake_build_setting_name_version_major_prefix_length,
      fake_build_setting_name_version_micro_length,
      fake_build_setting_name_version_micro_prefix_length,
      fake_build_setting_name_version_minor_length,
      fake_build_setting_name_version_minor_prefix_length,
      fake_build_setting_name_version_nano_length,
      fake_build_setting_name_version_nano_prefix_length,
      fake_build_setting_name_version_target_length,
    };

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
      &setting->build_sources_script,
      &setting->build_sources_setting,
      &build_static,
      &setting->defines_all,
      &setting->defines_library,
      &setting->defines_program,
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
      &version_file,
      &version_major,
      &version_major_prefix,
      &version_micro,
      &version_micro_prefix,
      &version_minor,
      &version_minor_prefix,
      &version_nano,
      &version_nano_prefix,
      &version_target,
    };

    bool settings_matches[] = {
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
      F_false,
    };

    f_string_t function = "fll_fss_snatch_apart";

    *status = fll_fss_snatch_apart(buffer, objects, contents, settings_name, settings_length, fake_build_setting_total, settings_value, settings_matches, 0);

    if (*status == F_none) {
      const int total_build_libraries = setting->build_libraries.used;

      f_string_dynamic_t settings_mode_name_dynamic[fake_build_setting_total];
      f_string_t settings_mode_names[fake_build_setting_total];
      f_array_length_t setting_mode_lengths[fake_build_setting_total];

      const f_string_dynamics_t *modes = &setting->modes_default;
      bool found = F_false;

      f_array_length_t i = 0;
      f_array_length_t j = 0;

      // if any mode is specified, the entire defaults is replaced.
      if (main.mode.used) {
        modes = &main.mode;
      }

      for (; i < modes->used; ++i) {

        found = F_false;

        for (j = 0; j < setting->modes.used; ++j) {

          if (fl_string_dynamic_compare_trim(modes->array[i], setting->modes.array[j]) == F_equal_to) {
            found = F_true;
            break;
          }
        } // for

        if (found == F_false) {
          if (main.error.verbosity != f_console_verbosity_quiet) {
            flockfile(main.error.to.stream);

            fl_print_format("%c%[%SThe specified mode '%]", main.error.to.stream, f_string_eol_s[0], main.error.context, main.error.prefix, main.error.context);
            fl_print_format("%[%Q%]", main.error.to.stream, main.error.notable, modes->array[i], main.error.notable);
            fl_print_format("%[' is not a valid mode, according to '%]", main.error.to.stream, main.error.context, main.error.context);
            fl_print_format("%[%S%]", main.error.to.stream, main.error.notable, path_file, main.error.notable);
            fl_print_format("%['.%]%c", main.error.to.stream, main.error.context, main.error.context, f_string_eol_s[0]);

            funlockfile(main.error.to.stream);
          }

          error_printed = F_true;
          *status = F_status_set_error(F_parameter);
          break;
        }

        memset(&settings_mode_name_dynamic, 0, sizeof(f_string_dynamic_t) * fake_build_setting_total);
        memset(&settings_mode_names, 0, sizeof(f_string_t) * fake_build_setting_total);
        memset(&setting_mode_lengths, 0, sizeof(f_array_length_t) * fake_build_setting_total);

        for (j = 0; j < fake_build_setting_total; ++j) {

          setting_mode_lengths[j] = settings_length[j] + 1 + modes->array[i].used;

          macro_f_string_dynamic_t_resize(*status, settings_mode_name_dynamic[j], setting_mode_lengths[j]);

          if (F_status_is_error(*status)) {
            function = "macro_f_string_dynamic_t_resize";
            break;
          }

          memcpy(settings_mode_name_dynamic[j].string, settings_name[j], settings_length[j]);
          memcpy(settings_mode_name_dynamic[j].string + settings_length[j] + 1, modes->array[i].string, modes->array[i].used);
          settings_mode_name_dynamic[j].string[settings_length[j]] = '-';

          settings_mode_names[j] = settings_mode_name_dynamic[j].string;
        } // for

        if (*status == F_none) {
          *status = fll_fss_snatch_apart(buffer, objects, contents, settings_mode_names, setting_mode_lengths, fake_build_setting_total, settings_value, 0, 0);

          if (F_status_is_error(*status)) {
            function = "fll_fss_snatch_apart";
          }
        }

        for (j = 0; j < fake_build_setting_total; ++j) {
          macro_f_string_dynamic_t_delete_simple(settings_mode_name_dynamic[j]);
        } // for

        if (F_status_is_error(*status)) break;
      } // for

      // "build_libraries" is appended after all modes to help assist with static linker file issues (@todo there should likely be more options to have a postfix linker parameter that can be added here instead, such as "build_libraries_last").
      if (total_build_libraries) {
        f_string_dynamic_t temporary[total_build_libraries];

        for (i = 0; i < total_build_libraries; ++i) {

          temporary[i].string = setting->build_libraries.array[i].string;
          temporary[i].used = setting->build_libraries.array[i].used;
          temporary[i].size = setting->build_libraries.array[i].size;
        } // for

        for (i = 0, j = total_build_libraries; j < setting->build_libraries.used; ++i, ++j) {

          setting->build_libraries.array[i].string = setting->build_libraries.array[j].string;
          setting->build_libraries.array[i].used = setting->build_libraries.array[j].used;
          setting->build_libraries.array[i].size = setting->build_libraries.array[j].size;
        } // for

        for (i = setting->build_libraries.used - total_build_libraries, j = 0; j < total_build_libraries; ++i, ++j) {

          setting->build_libraries.array[i].string = temporary[j].string;
          setting->build_libraries.array[i].used = temporary[j].used;
          setting->build_libraries.array[i].size = temporary[j].size;
        } // for
      }
    }

    if (F_status_is_error(*status)) {
      if (*status == F_status_set_error(F_string_too_large)) {
        if (main.error.verbosity != f_console_verbosity_quiet) {
          funlockfile(main.error.to.stream);

          // @todo update FSS functions to return which setting index the problem happened on.
          fl_print_format("%c%[%SA setting in the build setting file '%]", main.error.to.stream, f_string_eol_s[0], main.error.context, main.error.prefix, main.error.context);
          fl_print_format("%[%S%]", main.error.to.stream, main.error.notable, path_file, main.error.notable);
          fl_print_format("%[' is too long.%]%c", main.error.to.stream, main.error.context, main.error.context, f_string_eol_s[0]);

          funlockfile(main.error.to.stream);
        }
      }
      else if (!error_printed) {
        fll_error_print(main.error, F_status_set_fine(*status), function, F_true);
      }
    }
    else if (!fake_signal_received(main)) {
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
        fake_build_setting_name_version_file,
        fake_build_setting_name_version_major,
        fake_build_setting_name_version_major_prefix,
        fake_build_setting_name_version_micro,
        fake_build_setting_name_version_micro_prefix,
        fake_build_setting_name_version_minor,
        fake_build_setting_name_version_minor_prefix,
        fake_build_setting_name_version_nano,
        fake_build_setting_name_version_nano_prefix,
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
        &version_file,
        &version_major,
        &version_major_prefix,
        &version_micro,
        &version_micro_prefix,
        &version_minor,
        &version_minor_prefix,
        &version_nano,
        &version_nano_prefix,
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
        0,
        &setting->version_major,
        &setting->version_major_prefix,
        &setting->version_micro,
        &setting->version_micro_prefix,
        &setting->version_minor,
        &setting->version_minor_prefix,
        &setting->version_nano,
        &setting->version_nano_prefix,
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
        &setting->version_file,
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

      const uint8_t settings_single_version_default[] = {
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
        fake_build_version_type_micro,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        fake_build_version_type_major,
      };

      const char *settings_single_version_default_name[] = {
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
        fake_build_version_micro,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        fake_build_version_major,
      };

      // 1 = "yes" or "no", 2 = path/, 3 = literal, 4 = "bash", "c", or "c++", 5 = "major", "minor", "micro", or "nano".
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
        5,
        3,
        3,
        3,
        3,
        3,
        3,
        3,
        3,
        5,
      };

      for (f_array_length_t i = 0; i < 33; ++i) {

        if (!settings_single_source[i]->used) continue;

        if (settings_single_source[i]->used > 1) {
          if (main.warning.verbosity == f_console_verbosity_verbose) {
            flockfile(main.warning.to.stream);

            fl_print_format("%c%[%SThe setting '%]", main.warning.to.stream, f_string_eol_s[0], main.warning.context, main.warning.prefix, main.warning.context);
            fl_print_format("%[%S%]", main.warning.to.stream, main.warning.notable, settings_single_name[i], main.warning.notable);
            fl_print_format("%[' in the file '%]", main.warning.to.stream, main.warning.context, main.warning.context);
            fl_print_format("%[%S%]", main.warning.to.stream, main.warning.notable, path_file, main.warning.notable);
            fl_print_format("%[' may only have a single property, only using the first: '%]", main.warning.to.stream, main.warning.context, main.warning.context);
            fl_print_format("%[%Q%]", main.warning.to.stream, main.warning.notable, settings_single_source[i]->array[0], main.warning.notable);
            fl_print_format("%['.%]%c", main.warning.to.stream, main.warning.context, main.warning.context, f_string_eol_s[0]);

            funlockfile(main.warning.to.stream);
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

            if (main.warning.verbosity == f_console_verbosity_verbose) {
              flockfile(main.warning.to.stream);

              fl_print_format("%c%[%SThe setting '%]", main.warning.to.stream, f_string_eol_s[0], main.warning.context, main.warning.prefix, main.warning.context);
              fl_print_format("%[%S%]", main.warning.to.stream, main.warning.notable, settings_single_name[i], main.warning.notable);
              fl_print_format("%[' in the file '%]", main.warning.to.stream, main.warning.context, main.warning.context);
              fl_print_format("%[%S%]", main.warning.to.stream, main.warning.notable, path_file, main.warning.notable);
              fl_print_format("%[' may be either '%]", main.warning.to.stream, main.warning.context, main.warning.context);
              fl_print_format("%[%s%]", main.warning.to.stream, main.warning.notable, fake_common_setting_bool_yes, main.warning.notable);
              fl_print_format("%[' or '%]", main.warning.to.stream, main.warning.context, main.warning.context);
              fl_print_format("%[%s%]", main.warning.to.stream, main.warning.notable, fake_common_setting_bool_no, main.warning.notable);
              fl_print_format("%[', defaulting to '%]", main.warning.to.stream, main.warning.context, main.warning.context);
              fl_print_format("%[%s%]", main.warning.to.stream, main.warning.notable, fake_common_setting_bool_yes, main.warning.notable);
              fl_print_format("%['.%]%c", main.warning.to.stream, main.warning.context, main.warning.context, f_string_eol_s[0]);

              funlockfile(main.warning.to.stream);
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

            if (main.warning.verbosity == f_console_verbosity_verbose) {
              flockfile(main.warning.to.stream);

              fl_print_format("%c%[%SThe setting '%]", main.warning.to.stream, f_string_eol_s[0], main.warning.context, main.warning.prefix, main.warning.context);
              fl_print_format("%[%S%]", main.warning.to.stream, main.warning.notable, settings_single_name[i], main.warning.notable);
              fl_print_format("%[' in the file '%]", main.warning.to.stream, main.warning.context, main.warning.context);
              fl_print_format("%[%S%]", main.warning.to.stream, main.warning.notable, path_file, main.warning.notable);
              fl_print_format("%[' may only be one of '%]", main.warning.to.stream, main.warning.context, main.warning.context);
              fl_print_format("%[%s%]", main.warning.to.stream, main.warning.notable, fake_build_language_bash, main.warning.notable);
              fl_print_format("%[', '%]", main.warning.to.stream, main.warning.context, main.warning.context);
              fl_print_format("%[%s%]", main.warning.to.stream, main.warning.notable, fake_build_language_c, main.warning.notable);
              fl_print_format("%[', or '%]", main.warning.to.stream, main.warning.context, main.warning.context);
              fl_print_format("%[%s%]", main.warning.to.stream, main.warning.notable, fake_build_language_cpp, main.warning.notable);
              fl_print_format("%[', defaulting to '%]", main.warning.to.stream, main.warning.context, main.warning.context);
              fl_print_format("%[%s%]", main.warning.to.stream, main.warning.notable, fake_build_language_c, main.warning.notable);
              fl_print_format("%['.%]%c", main.warning.to.stream, main.warning.context, main.warning.context, f_string_eol_s[0]);

              funlockfile(main.warning.to.stream);
            }
          }
        }
        else if (settings_single_type[i] == 5) {
          if (fl_string_compare_trim(settings_single_source[i]->array[0].string, fake_build_version_major, settings_single_source[i]->array[0].used, fake_build_version_major_length) == F_equal_to) {
            *settings_single_version[i] = fake_build_version_type_major;
          }
          else if (fl_string_compare_trim(settings_single_source[i]->array[0].string, fake_build_version_minor, settings_single_source[i]->array[0].used, fake_build_version_minor_length) == F_equal_to) {
            *settings_single_version[i] = fake_build_version_type_minor;
          }
          else if (fl_string_compare_trim(settings_single_source[i]->array[0].string, fake_build_version_micro, settings_single_source[i]->array[0].used, fake_build_version_micro_length) == F_equal_to) {
            *settings_single_version[i] = fake_build_version_type_micro;
          }
          else if (fl_string_compare_trim(settings_single_source[i]->array[0].string, fake_build_version_nano, settings_single_source[i]->array[0].used, fake_build_version_nano_length) == F_equal_to) {
            *settings_single_version[i] = fake_build_version_type_nano;
          }
          else {
            *settings_single_version[i] = settings_single_version_default[i];

            if (main.warning.verbosity == f_console_verbosity_verbose) {
              flockfile(main.warning.to.stream);

              fl_print_format("%c%[%SThe setting '%]", main.warning.to.stream, f_string_eol_s[0], main.warning.context, main.warning.prefix, main.warning.context);
              fl_print_format("%[%S%]", main.warning.to.stream, main.warning.notable, settings_single_name[i], main.warning.notable);
              fl_print_format("%[' in the file '%]", main.warning.to.stream, main.warning.context, main.warning.context);
              fl_print_format("%[%S%]", main.warning.to.stream, main.warning.notable, path_file, main.warning.notable);
              fl_print_format("%[' may only be one of '%]", main.warning.to.stream, main.warning.context, main.warning.context);
              fl_print_format("%[%s%]", main.warning.to.stream, main.warning.notable, fake_build_version_major, main.warning.notable);
              fl_print_format("%[', '%]", main.warning.to.stream, main.warning.context, main.warning.context);
              fl_print_format("%[%s%]", main.warning.to.stream, main.warning.notable, fake_build_version_minor, main.warning.notable);
              fl_print_format("%[', '%]", main.warning.to.stream, main.warning.context, main.warning.context);
              fl_print_format("%[%s%]", main.warning.to.stream, main.warning.notable, fake_build_version_micro, main.warning.notable);
              fl_print_format("%[', or '%]", main.warning.to.stream, main.warning.context, main.warning.context);
              fl_print_format("%[%s%]", main.warning.to.stream, main.warning.notable, fake_build_version_nano, main.warning.notable);
              fl_print_format("%[', defaulting to '%]", main.warning.to.stream, main.warning.context, main.warning.context);
              fl_print_format("%[%s%]", main.warning.to.stream, main.warning.notable, settings_single_version_default_name[i], main.warning.notable);
              fl_print_format("%['.%]%c", main.warning.to.stream, main.warning.context, main.warning.context, f_string_eol_s[0]);

              funlockfile(main.warning.to.stream);
            }
          }
        }
        else {

          // replace any potential existing value.
          settings_single_destination[i]->used = 0;

          *status = f_string_dynamic_append_nulless(settings_single_source[i]->array[0], settings_single_destination[i]);

          if (F_status_is_error(*status)) {
            fll_error_print(main.error, F_status_set_fine(*status), "f_string_dynamic_append_nulless", F_true);
            break;
          }

          if (settings_single_type[i] == 2) {
            *status = f_string_append_assure(f_path_separator_s, f_path_separator_length, settings_single_destination[i]);

            if (F_status_is_error(*status)) {
              fll_error_print(main.error, F_status_set_fine(*status), "f_string_append_assure", F_true);
              break;
            }
          }

          *status = f_string_dynamic_terminate_after(settings_single_destination[i]);
          if (F_status_is_error(*status)) {
            fll_error_print(main.error, F_status_set_fine(*status), "f_string_dynamic_terminate_after", F_true);
            break;
          }
        }
      } // for

      if (F_status_is_error_not(*status)) {
        if (!setting->version_file) {
          setting->version_file = fake_build_version_type_micro;

          if (main.warning.verbosity == f_console_verbosity_verbose) {
            flockfile(main.warning.to.stream);

            fl_print_format("%c%[%SThe setting '%]", main.warning.to.stream, f_string_eol_s[0], main.warning.context, main.warning.prefix, main.warning.context);
            fl_print_format("%[%S%]", main.warning.to.stream, main.warning.notable, fake_build_setting_name_version_file, main.warning.notable);
            fl_print_format("%[' in the file '%]", main.warning.to.stream, main.warning.context, main.warning.context);
            fl_print_format("%[%S%]", main.warning.to.stream, main.warning.notable, path_file, main.warning.notable);
            fl_print_format("%[' is required, defaulting to '%]", main.warning.to.stream, main.warning.context, main.warning.context);
            fl_print_format("%[%s%]", main.warning.to.stream, main.warning.notable, fake_build_version_micro, main.warning.notable);
            fl_print_format("%['.%]%c", main.warning.to.stream, main.warning.context, main.warning.context, f_string_eol_s[0]);

            funlockfile(main.warning.to.stream);
          }
        }

        if (!setting->version_target) {
          setting->version_target = fake_build_version_type_major;

          if (main.warning.verbosity == f_console_verbosity_verbose) {
            flockfile(main.warning.to.stream);

            fl_print_format("%c%[%SThe setting '%]", main.warning.to.stream, f_string_eol_s[0], main.warning.context, main.warning.prefix, main.warning.context);
            fl_print_format("%[%S%]", main.warning.to.stream, main.warning.notable, fake_build_setting_name_version_target, main.warning.notable);
            fl_print_format("%[' in the file '%]", main.warning.to.stream, main.warning.context, main.warning.context);
            fl_print_format("%[%S%]", main.warning.to.stream, main.warning.notable, path_file, main.warning.notable);
            fl_print_format("%[' is required, defaulting to '%]", main.warning.to.stream, main.warning.context, main.warning.context);
            fl_print_format("%[%s%]", main.warning.to.stream, main.warning.notable, fake_build_version_major, main.warning.notable);
            fl_print_format("%['.%]%c", main.warning.to.stream, main.warning.context, main.warning.context, f_string_eol_s[0]);

            funlockfile(main.warning.to.stream);
          }
        }
      }

      // Provide these defaults only if the Object is not defined (this allows for empty Content to exist if the Object is defined).
      // In the case of the version prefixes, if the associated version is empty, then instead clear the associated version prefix.
      if (F_status_is_error_not(*status)) {
        f_string_dynamic_t *prefix[] = {
          &setting->version_major_prefix,
          &setting->version_minor_prefix,
          &setting->version_micro_prefix,
          &setting->version_nano_prefix,
        };

        f_string_dynamic_t *version[] = {
          &setting->version_major,
          &setting->version_minor,
          &setting->version_micro,
          &setting->version_nano,
        };

        bool has_prefix_object[] = {
          settings_matches[44], // version_major_prefix
          settings_matches[46], // version_minor_prefix
          settings_matches[48], // version_micro_prefix
          settings_matches[50], // version_nano_prefix
        };

        const char *name_target[] = {
          fake_build_version_major,
          fake_build_version_minor,
          fake_build_version_micro,
          fake_build_version_nano,
        };

        const char *name_object[] = {
          fake_build_setting_name_version_major,
          fake_build_setting_name_version_minor,
          fake_build_setting_name_version_micro,
          fake_build_setting_name_version_nano,
        };

        const char *setting_name[] = {
          fake_build_setting_name_version_file,
          fake_build_setting_name_version_target,
        };

        const uint8_t setting_target[] = {
          setting->version_file,
          setting->version_target,
        };

        f_array_length_t i = 0;
        f_array_length_t j = 0;

        for (; i < 4; ++i) {

          if (version[i]->used) {
            if (!has_prefix_object[i]) {
              prefix[i]->used = 0;

              *status = f_string_append(fake_build_setting_default_version_prefix, fake_build_setting_default_version_prefix_length, prefix[i]);

              if (F_status_is_error(*status)) {
                fll_error_print(main.error, F_status_set_fine(*status), "f_string_append", F_true);
                break;
              }
            }
          }
          else {
            prefix[i]->used = 0;

            for (j = 0; j < 2; ++j) {

              if (setting_target[j] && i + 1 <= setting_target[j]) {
                if (main.error.verbosity != f_console_verbosity_quiet) {
                  flockfile(main.error.to.stream);

                  fl_print_format("%c%[%SWhen the '%]", main.error.to.stream, f_string_eol_s[0], main.error.context, main.error.prefix, main.error.context);
                  fl_print_format("%[%S%]", main.error.to.stream, main.error.notable, setting_name[j], main.error.notable);
                  fl_print_format("%[' is set to '%]", main.error.to.stream, main.error.context, main.error.context);
                  fl_print_format("%[%S%]", main.error.to.stream, main.error.notable, name_target[setting_target[j] - 1], main.error.notable);
                  fl_print_format("%[' then the '%]", main.error.to.stream, main.error.context, main.error.context);
                  fl_print_format("%[%S%]", main.error.to.stream, main.error.notable, name_object[i], main.error.notable);
                  fl_print_format("%[' Object must have Content.%]%c", main.error.to.stream, main.error.context, main.error.context, f_string_eol_s[0]);

                  funlockfile(main.error.to.stream);
                }

                *status = F_status_set_error(F_failure);
                break;
              }
            } // for

            if (F_status_is_error(*status)) break;
          }
        } // for
      }
    }

    macro_f_string_dynamics_t_delete_simple(build_compiler);
    macro_f_string_dynamics_t_delete_simple(build_indexer);
    macro_f_string_dynamics_t_delete_simple(build_language);
    macro_f_string_dynamics_t_delete_simple(build_script);
    macro_f_string_dynamics_t_delete_simple(build_shared);
    macro_f_string_dynamics_t_delete_simple(build_static);
    macro_f_string_dynamics_t_delete_simple(path_headers);
    macro_f_string_dynamics_t_delete_simple(path_headers_preserve);
    macro_f_string_dynamics_t_delete_simple(path_language);
    macro_f_string_dynamics_t_delete_simple(path_library_script);
    macro_f_string_dynamics_t_delete_simple(path_library_shared);
    macro_f_string_dynamics_t_delete_simple(path_library_static);
    macro_f_string_dynamics_t_delete_simple(path_program_script);
    macro_f_string_dynamics_t_delete_simple(path_program_shared);
    macro_f_string_dynamics_t_delete_simple(path_program_static);
    macro_f_string_dynamics_t_delete_simple(path_sources);
    macro_f_string_dynamics_t_delete_simple(path_standard);
    macro_f_string_dynamics_t_delete_simple(process_post);
    macro_f_string_dynamics_t_delete_simple(process_pre);
    macro_f_string_dynamics_t_delete_simple(project_name);
    macro_f_string_dynamics_t_delete_simple(search_exclusive);
    macro_f_string_dynamics_t_delete_simple(search_shared);
    macro_f_string_dynamics_t_delete_simple(search_static);
    macro_f_string_dynamics_t_delete_simple(version_file);
    macro_f_string_dynamics_t_delete_simple(version_major);
    macro_f_string_dynamics_t_delete_simple(version_major_prefix);
    macro_f_string_dynamics_t_delete_simple(version_micro);
    macro_f_string_dynamics_t_delete_simple(version_micro_prefix);
    macro_f_string_dynamics_t_delete_simple(version_minor);
    macro_f_string_dynamics_t_delete_simple(version_minor_prefix);
    macro_f_string_dynamics_t_delete_simple(version_nano);
    macro_f_string_dynamics_t_delete_simple(version_nano_prefix);
    macro_f_string_dynamics_t_delete_simple(version_target);
  }
#endif // _di_fake_build_load_setting_process_

#ifndef _di_fake_build_load_setting_defaults_
  void fake_build_load_setting_defaults(const fake_main_t main, fake_build_setting_t *setting, f_status_t *status) {

    if (F_status_is_error(*status)) return;

    if (fake_signal_received(main)) {
      *status = F_status_set_error(F_signal);

      return;
    }

    {
      const f_string_t sources[] = {
        fake_build_setting_default_version,
        fake_build_setting_default_version,
        fake_build_setting_default_version,
      };

      const f_array_length_t lengths[] = {
        fake_build_setting_default_version_length,
        fake_build_setting_default_version_length,
        fake_build_setting_default_version_length,
      };

      f_string_dynamic_t * const destinations[] = {
        &setting->version_major,
        &setting->version_minor,
        &setting->version_micro,
      };

      for (uint8_t i = 0; i < 3; ++i) {

        if (destinations[i]->used) continue;

        *status = f_string_append_assure(sources[i], lengths[i], destinations[i]);

        if (F_status_is_error(*status)) {
          fll_error_print(main.error, F_status_set_fine(*status), "f_string_append_assure", F_true);
          break;
        }

        *status = f_string_dynamic_terminate_after(destinations[i]);

        if (F_status_is_error(*status)) {
          fll_error_print(main.error, F_status_set_fine(*status), "f_string_dynamic_terminate_after", F_true);
          break;
        }
      } // for
    }

    if (F_status_is_error(*status)) return;

    // Override setting file when any of these are specified in the command line.
    if (main.parameters[fake_parameter_shared_disabled].result == f_console_result_found) {
      if (main.parameters[fake_parameter_shared_enabled].result == f_console_result_found) {
        if (main.parameters[fake_parameter_shared_enabled].location > main.parameters[fake_parameter_shared_disabled].location) {
          setting->build_shared = F_true;
          setting->search_shared = F_true;
        }
        else {
          setting->build_shared = F_false;
          setting->search_shared = F_false;
        }

        if (main.error.verbosity != f_console_verbosity_quiet) {
          flockfile(main.error.to.stream);

          fl_print_format("%c%[%SThe parameters '%]", main.error.to.stream, f_string_eol_s[0], main.error.context, main.error.prefix, main.error.context);
          fl_print_format("%[%s%s%]", main.error.to.stream, main.error.notable, f_console_symbol_long_enable_s, fake_long_shared_disabled, main.error.notable);
          fl_print_format("%[' and '%]", main.error.to.stream, main.error.context, main.error.context);
          fl_print_format("%[%s%s%]", main.error.to.stream, main.error.notable, f_console_symbol_long_enable_s, fake_long_shared_enabled, main.error.notable);
          fl_print_format("%[' contradict, defaulting to '%]", main.error.to.stream, main.error.context, main.error.context);
          fl_print_format("%[%s%s%]", main.error.to.stream, main.error.notable, f_console_symbol_long_enable_s, setting->build_shared ? fake_long_shared_enabled : fake_long_shared_disabled, main.error.notable);
          fl_print_format("%['.%]%c", main.error.to.stream, main.error.context, main.error.context, f_string_eol_s[0]);

          funlockfile(main.error.to.stream);
        }
      }
      else {
        setting->build_shared = F_false;
        setting->search_shared = F_false;
      }
    }
    else if (main.parameters[fake_parameter_shared_enabled].result == f_console_result_found) {
      setting->build_shared = F_true;
      setting->search_shared = F_true;
    }

    if (main.parameters[fake_parameter_static_disabled].result == f_console_result_found) {
      if (main.parameters[fake_parameter_static_enabled].result == f_console_result_found) {
        if (main.parameters[fake_parameter_static_enabled].location > main.parameters[fake_parameter_static_disabled].location) {
          setting->build_static = F_true;
          setting->search_static = F_true;
        }
        else {
          setting->build_static = F_false;
          setting->search_static = F_false;
        }

        if (main.error.verbosity == f_console_verbosity_verbose) {
          flockfile(main.error.to.stream);

          fl_print_format("%c%[%SThe parameters '%]", main.error.to.stream, f_string_eol_s[0], main.error.context, main.error.prefix, main.error.context);
          fl_print_format("%[%s%s%]", main.error.to.stream, main.error.notable, f_console_symbol_long_enable_s, fake_long_static_disabled, main.error.notable);
          fl_print_format("%[' and '%]", main.error.to.stream, main.error.context, main.error.context);
          fl_print_format("%[%s%s%]", main.error.to.stream, main.error.notable, f_console_symbol_long_enable_s, fake_long_static_enabled, main.error.notable);
          fl_print_format("%[' contradict, defaulting to '%]", main.error.to.stream, main.error.context, main.error.context);
          fl_print_format("%[%s%s%]", main.error.to.stream, main.error.notable, f_console_symbol_long_enable_s, setting->build_static ? fake_long_static_enabled : fake_long_static_disabled, main.error.notable);
          fl_print_format("%['.%]%c", main.error.to.stream, main.error.context, main.error.context, f_string_eol_s[0]);

          funlockfile(main.error.to.stream);
        }
      }
      else {
        setting->build_static = F_false;
        setting->search_static = F_false;
      }
    }
    else if (main.parameters[fake_parameter_static_enabled].result == f_console_result_found) {
      setting->build_static = F_true;
      setting->search_static = F_true;
    }

    if (setting->build_language == fake_build_language_type_c || setting->build_language == fake_build_language_type_cpp) {
      if (setting->build_shared == F_false && setting->build_static == F_false) {
        if (main.error.verbosity != f_console_verbosity_quiet) {
          flockfile(main.error.to.stream);

          fl_print_format("%c%[%SThe build settings '%]", main.error.to.stream, f_string_eol_s[0], main.error.context, main.error.prefix, main.error.context);
          fl_print_format("%[%s%]", main.error.to.stream, main.error.notable, fake_build_setting_name_build_shared, main.error.notable);
          fl_print_format("%[' and '%]", main.error.to.stream, main.error.context, main.error.context);
          fl_print_format("%[%s%]", main.error.to.stream, main.error.notable, fake_build_setting_name_build_static, main.error.notable);
          fl_print_format("%[' cannot both be false when using the language '%]", main.error.to.stream, main.error.context, main.error.context);
          fl_print_format("%[%s%]", main.error.to.stream, main.error.notable, f_console_symbol_long_enable_s, setting->build_language == fake_build_language_type_c ? fake_build_language_c : fake_build_language_cpp, main.error.notable);
          fl_print_format("%['.%]%c", main.error.to.stream, main.error.context, main.error.context, f_string_eol_s[0]);

          funlockfile(main.error.to.stream);
        }

        *status = F_status_set_error(F_failure);
      }
    }

    if (fake_signal_received(main)) {
      *status = F_status_set_error(F_signal);
    }
  }
#endif // _di_fake_build_load_setting_defaults_

#ifndef _di_fake_build_load_stage_
  void fake_build_load_stage(const fake_main_t main, const f_string_static_t settings_file, fake_build_stage_t *stage, f_status_t *status) {

    if (F_status_is_error(*status)) return;

    if (fake_signal_received(main)) {
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

    const f_array_length_t lengths[] = {
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
      *status = f_file_name_base(main.file_data_build_settings.string, main.file_data_build_settings.used, &settings_file_base);
    }

    if (F_status_is_error(*status)) {
      fll_error_print(main.error, F_status_set_fine(*status), "f_file_name_base", F_true);

      return;
    }

    for (uint8_t i = 0; i < fake_build_stage_total; ++i) {

      *status = f_string_dynamic_append_nulless(main.path_build_stage, values[i]);

      if (F_status_is_error(*status)) {
        fll_error_print(main.error, F_status_set_fine(*status), "f_string_dynamic_append_nulless", F_true);
        break;
      }

      if (main.process.used) {
        *status = f_string_append(main.process.string, main.process.used, values[i]);

        if (F_status_is_error(*status)) {
          fll_error_print(main.error, F_status_set_fine(*status), "f_string_append", F_true);
          break;
        }

        *status = f_string_append(fake_build_stage_separate, fake_build_stage_separate_length, values[i]);

        if (F_status_is_error(*status)) {
          fll_error_print(main.error, F_status_set_fine(*status), "f_string_append", F_true);
          break;
        }
      }

      *status = f_string_append_nulless(names[i], lengths[i], values[i]);

      if (F_status_is_error(*status)) {
        fll_error_print(main.error, F_status_set_fine(*status), "f_string_dynamic_append_nulless", F_true);
        break;
      }

      *status = f_string_append(fake_build_stage_separate, fake_build_stage_separate_length, values[i]);

      if (F_status_is_error(*status)) {
        fll_error_print(main.error, F_status_set_fine(*status), "f_string_append", F_true);
        break;
      }

      *status = f_string_dynamic_append(settings_file_base, values[i]);

      if (F_status_is_error(*status)) {
        fll_error_print(main.error, F_status_set_fine(*status), "f_string_dynamic_append", F_true);
        break;
      }

      *status = f_string_append(fake_build_stage_built, fake_build_stage_built_length, values[i]);

      if (F_status_is_error(*status)) {
        fll_error_print(main.error, F_status_set_fine(*status), "f_string_append", F_true);
        break;
      }

      *status = f_string_dynamic_terminate_after(values[i]);

      if (F_status_is_error(*status)) {
        fll_error_print(main.error, F_status_set_fine(*status), "f_string_dynamic_terminate_after", F_true);
        break;
      }
    } // for

    macro_f_string_dynamic_t_delete_simple(settings_file_base);
  }
#endif // _di_fake_build_load_stage_

#ifndef _di_fake_build_objects_static_
  int fake_build_objects_static(const fake_main_t main, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) {

    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true || *status == F_child) return main.child;
    if (!data_build.setting.build_sources_library.used) return 0;

    if (main.output.verbosity != f_console_verbosity_quiet) {
      fll_print_format("%c%[Compiling static objects.%]%c", main.output.to.stream, f_string_eol_s[0], main.context.set.important, main.context.set.important, f_string_eol_s[0]);
    }

    f_string_dynamic_t file_name = f_string_dynamic_t_initialize;
    f_string_dynamic_t destination_path = f_string_dynamic_t_initialize;
    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;
    f_array_length_t source_length = 0;
    f_array_length_t destination_length = 0;

    const f_string_static_t *path_sources = &main.path_sources;

    int result = main.child;

    if (data_build.setting.path_standard) {
      path_sources = &main.path_sources_c;

      if (data_build.setting.build_language == fake_build_language_type_cpp) {
        path_sources = &main.path_sources_cpp;
      }
    }
    else if (main.parameters[fake_parameter_path_sources].result != f_console_result_additional) {
      path_sources = &data_build.setting.path_sources;
    }

    for (f_array_length_t i = 0; i < data_build.setting.build_sources_library.used; ++i) {

      file_name.used = 0;
      destination_path.used = 0;

      source_length = path_sources->used + data_build.setting.build_sources_library.array[i].used;

      char source[source_length + 1];

      memcpy(source, path_sources->string, path_sources->used);
      memcpy(source + path_sources->used, data_build.setting.build_sources_library.array[i].string, data_build.setting.build_sources_library.array[i].used);
      source[source_length] = 0;

      *status = fake_build_get_file_name_without_extension(main, data_build.setting.build_sources_library.array[i], &file_name);

      if (F_status_is_error(*status)) {
        fll_error_print(main.error, F_status_set_fine(*status), "fake_build_get_file_name_without_extension", F_true);
        break;
      }

      if (fake_signal_received(main)) {
        *status = F_status_set_error(F_signal);
        break;
      }

      *status = f_file_name_directory(data_build.setting.build_sources_library.array[i].string, data_build.setting.build_sources_library.array[i].used, &destination_path);

      if (F_status_is_error(*status)) {
        fll_error_print(main.error, F_status_set_fine(*status), "f_file_name_directory", F_true);
        break;
      }

      if (destination_path.used) {
        *status = f_string_dynamic_prepend(main.path_build_objects, &destination_path);

        if (F_status_is_error(*status)) {
          fll_error_print(main.error, F_status_set_fine(*status), "f_string_dynamic_prepend", F_true);
          break;
        }

        *status = f_string_append_assure(f_path_separator_s, f_path_separator_length, &destination_path);

        if (F_status_is_error(*status)) {
          fll_error_print(main.error, F_status_set_fine(*status), "f_string_append_assure", F_true);
          break;
        }

        *status = f_string_dynamic_terminate_after(&destination_path);

        if (F_status_is_error(*status)) {
          fll_error_print(main.error, F_status_set_fine(*status), "f_string_dynamic_terminate_after", F_true);
          break;
        }

        if (fake_signal_received(main)) {
          *status = F_status_set_error(F_signal);
          break;
        }

        *status = f_directory_exists(destination_path.string);

        if (*status == F_false) {
          if (main.error.verbosity != f_console_verbosity_quiet) {
            flockfile(main.error.to.stream);

            fl_print_format("%c%[%SThe path '%]", main.error.to.stream, f_string_eol_s[0], main.error.context, main.error.prefix, main.error.context);
            fl_print_format("%[%Q%]", main.error.to.stream, main.error.notable, destination_path, main.error.notable);
            fl_print_format("%[' exists but is not a directory.%]%c", main.error.to.stream, main.error.context, main.error.context, f_string_eol_s[0]);

            funlockfile(main.error.to.stream);
          }

          *status = F_status_set_error(F_failure);
          break;
        }
        else if (*status == F_file_found_not) {
          *status = f_directory_create(destination_path.string, mode.directory);

          if (F_status_is_error(*status)) {
            if (F_status_set_fine(*status) == F_file_found_not) {
              flockfile(main.error.to.stream);

              fl_print_format("%c%[%SThe path '%]", main.error.to.stream, f_string_eol_s[0], main.error.context, main.error.prefix, main.error.context);
              fl_print_format("%[%Q%]", main.error.to.stream, main.error.notable, destination_path, main.error.notable);
              fl_print_format("%[' could not be created, a parent directory does not exist.%]%c", main.error.to.stream, main.error.context, main.error.context, f_string_eol_s[0]);

              funlockfile(main.error.to.stream);
            }
            else {
              fll_error_file_print(main.error, F_status_set_fine(*status), "f_directory_create", F_true, destination_path.string, "create", fll_error_file_type_directory);
            }

            break;
          }

          if (main.error.verbosity == f_console_verbosity_verbose) {
            fll_print_format("Directory '%Q' created.%c", main.output.to.stream, destination_path, f_string_eol_s[0]);
          }
        }
        else if (F_status_is_error(*status)) {
          fll_error_file_print(main.error, F_status_set_fine(*status), "f_directory_exists", F_true, destination_path.string, "create", fll_error_file_type_directory);
          break;
        }

        destination_length = destination_path.used + file_name.used + fake_build_parameter_object_name_suffix_length;
      }
      else {
        destination_length = main.path_build_objects.used + file_name.used + fake_build_parameter_object_name_suffix_length;
      }

      char destination[destination_length + 1];

      if (destination_path.used) {
        memcpy(destination, destination_path.string, destination_path.used);
        memcpy(destination + destination_path.used, file_name.string, file_name.used);
        memcpy(destination + destination_path.used + file_name.used, fake_build_parameter_object_name_suffix, fake_build_parameter_object_name_suffix_length);
      }
      else {
        memcpy(destination, main.path_build_objects.string, main.path_build_objects.used);
        memcpy(destination + main.path_build_objects.used, file_name.string, file_name.used);
        memcpy(destination + main.path_build_objects.used + file_name.used, fake_build_parameter_object_name_suffix, fake_build_parameter_object_name_suffix_length);
      }

      destination[destination_length] = 0;

      const f_string_t values[] = {
        source,
        fake_build_parameter_object_compile,
        fake_build_parameter_object_static,
        fake_build_parameter_object_output,
        destination,
      };

      const f_array_length_t lengths[] = {
        source_length,
        fake_build_parameter_object_compile_length,
        fake_build_parameter_object_static_length,
        fake_build_parameter_object_output_length,
        destination_length,
      };

      for (uint8_t j = 0; j < 5; ++j) {

        *status = fll_execute_arguments_add(values[j], lengths[j], &arguments);
        if (F_status_is_error(*status)) break;
      } // for

      fake_build_arguments_standard_add(main, data_build, F_false, F_true, &arguments, status);

      if (F_status_is_error(*status)) {
        fll_error_print(main.error, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);
        break;
      }

      result = fake_execute(main, data_build.environment, data_build.setting.build_compiler, arguments, status);

      macro_f_string_dynamics_t_delete_simple(arguments);

      if (F_status_is_error(*status) || *status == F_child) break;
    } // for

    macro_f_string_dynamic_t_delete_simple(file_name);
    macro_f_string_dynamic_t_delete_simple(destination_path);
    macro_f_string_dynamics_t_delete_simple(arguments);

    if (F_status_is_error_not(*status) && *status != F_child) {
      fake_build_touch(main, file_stage, status);
    }

    return result;
  }
#endif // _di_fake_build_objects_static_

#ifndef _di_fake_build_operate_
  f_status_t fake_build_operate(const f_string_static_t setting_file, fake_main_t *main) {

    if (fake_signal_received(*main)) {
      return F_signal;
    }

    f_status_t status = F_none;
    f_mode_t mode = f_mode_t_initialize;

    fake_build_data_t data_build = fake_build_data_t_initialize;
    fake_build_stage_t stage = fake_build_stage_t_initialize;

    macro_f_mode_t_set_default_umask(mode, main->umask);

    fake_build_load_setting(*main, setting_file, &data_build.setting, &status);

    if (F_status_is_fine(status)) {
      if (main->output.verbosity != f_console_verbosity_quiet) {
        flockfile(main->output.to.stream);

        fl_print_format("%c%[Building project%] ", main->output.to.stream, f_string_eol_s[0], main->context.set.important, main->context.set.important);
        fl_print_format("%[%Q%]", main->output.to.stream, main->context.set.notable, data_build.setting.project_name, main->context.set.notable);
        fl_print_format("%[.%]%c", main->output.to.stream, main->context.set.important, main->context.set.important, f_string_eol_s[0]);

        funlockfile(main->output.to.stream);
      }
    }

    fake_build_load_stage(*main, setting_file, &stage, &status);

    fake_build_load_environment(*main, data_build, &data_build.environment, &status);

    fake_build_skeleton(*main, data_build, mode.directory, stage.file_skeleton, &status);

    main->child = fake_build_execute_process_script(*main, data_build, data_build.setting.process_pre, stage.file_process_pre, &status);

    fake_build_copy(*main, mode, "setting files", main->path_data_settings, main->path_build_settings, data_build.setting.build_sources_setting, stage.file_sources_settings, 0, &status);

    if (data_build.setting.build_language == fake_build_language_type_bash) {
      fake_build_libraries_script(*main, data_build, mode, stage.file_libraries_script, &status);

      fake_build_programs_script(*main, data_build, mode, stage.file_programs_script, &status);

      if (data_build.setting.build_script) {
        fake_build_copy(*main, mode, "scripts", main->path_sources_script, main->path_build_programs_script, data_build.setting.build_sources_script, stage.file_sources_script, 0, &status);
      }
    }
    else {
      if (data_build.setting.build_sources_headers.used) {
        const f_string_static_t *path_sources = &main->path_sources;

        if (data_build.setting.path_standard) {
          path_sources = &main->path_sources_c;

          if (data_build.setting.build_language == fake_build_language_type_cpp) {
            path_sources = &main->path_sources_cpp;
          }
        }
        else if (main->parameters[fake_parameter_path_sources].result != f_console_result_additional) {
          path_sources = &data_build.setting.path_sources;
        }

        const f_array_length_t path_sources_base_length = path_sources->used;

        f_string_static_t path_headers = f_string_static_t_initialize;
        f_array_length_t directory_headers_length = main->path_build_includes.used + data_build.setting.path_headers.used;

        char directory_headers[directory_headers_length + 1];

        memcpy(directory_headers, main->path_build_includes.string, main->path_build_includes.used);

        if (data_build.setting.path_headers.used) {
          memcpy(directory_headers + main->path_build_includes.used, data_build.setting.path_headers.string, data_build.setting.path_headers.used);
        }

        directory_headers[directory_headers_length] = 0;

        path_headers.string = directory_headers;
        path_headers.used = directory_headers_length;
        path_headers.size = directory_headers_length + 1;

        fake_build_copy(*main, mode, "header files", *path_sources, path_headers, data_build.setting.build_sources_headers, stage.file_sources_headers, data_build.setting.path_headers_preserve ? path_sources_base_length : 0, &status);
      }

      if (data_build.setting.build_shared) {
        main->child = fake_build_library_shared(*main, data_build, mode, stage.file_libraries_shared, &status);

        main->child = fake_build_program_shared(*main, data_build, mode, stage.file_programs_shared, &status);
      }

      if (data_build.setting.build_static) {
        main->child = fake_build_objects_static(*main, data_build, mode, stage.file_objects_static, &status);

        main->child = fake_build_library_static(*main, data_build, mode, stage.file_libraries_static, &status);

        main->child = fake_build_program_static(*main, data_build, mode, stage.file_programs_static, &status);
      }

      if (data_build.setting.build_script) {
        fake_build_copy(*main, mode, "scripts", main->path_sources_script, main->path_build_programs_script, data_build.setting.build_sources_script, stage.file_sources_script, 0, &status);
      }
    }

    fake_build_execute_process_script(*main, data_build, data_build.setting.process_post, stage.file_process_post, &status);

    macro_fake_build_main_delete_simple(data_build);
    macro_fake_build_stage_t_delete_simple(stage);

    // signal is set with error code only to prevent further execution above, return without the error bit set.
    if (status == F_status_set_error(F_signal)) {
      return F_signal;
    }

    return status;
  }
#endif // _di_fake_build_operate_

#ifndef _di_fake_build_programs_script_
  int fake_build_programs_script(const fake_main_t main, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) {
    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true || *status == F_child) return main.child;

    // @todo needs to perform some sort of regex replace on the program scripts.

    fake_build_touch(main, file_stage, status);

    return 0;
  }
#endif // _di_fake_build_programs_script_

#ifndef _di_fake_build_program_shared_
  int fake_build_program_shared(const fake_main_t main, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) {

    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true || *status == F_child) return main.child;
    if (!data_build.setting.build_sources_program.used) return 0;

    if (main.output.verbosity != f_console_verbosity_quiet) {
      fll_print_format("%c%[Compiling shared program.%]%c", main.output.to.stream, f_string_eol_s[0], main.context.set.important, main.context.set.important, f_string_eol_s[0]);
    }

    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;

    {
      const f_string_static_t *path_sources = &main.path_sources;

      if (data_build.setting.path_standard) {
        path_sources = &main.path_sources_c;

        if (data_build.setting.build_language == fake_build_language_type_cpp) {
          path_sources = &main.path_sources_cpp;
        }
      }
      else if (main.parameters[fake_parameter_path_sources].result != f_console_result_additional) {
        path_sources = &data_build.setting.path_sources;
      }

      f_array_length_t source_length = 0;

      for (f_array_length_t i = 0; i < data_build.setting.build_sources_program.used; ++i) {

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
      f_array_length_t parameter_file_name_path_length = main.path_build_programs_shared.used + data_build.setting.project_name.used;

      char parameter_file_name_path[parameter_file_name_path_length + 1];

      memcpy(parameter_file_name_path, main.path_build_programs_shared.string, main.path_build_programs_shared.used);
      memcpy(parameter_file_name_path + main.path_build_programs_shared.used, data_build.setting.project_name.string, data_build.setting.project_name.used);
      parameter_file_name_path[parameter_file_name_path_length] = 0;

      const f_string_t values[] = {
        fake_build_parameter_library_output,
        parameter_file_name_path,
      };

      const f_array_length_t lengths[] = {
        fake_build_parameter_library_output_length,
        parameter_file_name_path_length,
      };

      for (uint8_t i = 0; i < 2; ++i) {

        *status = fll_execute_arguments_add(values[i], lengths[i], &arguments);
        if (F_status_is_error(*status)) break;
      } // for
    }

    // if project-specific library sources exist, then the -lproject_name needs to be added to the arguments.
    if (F_status_is_error_not(*status) && data_build.setting.build_sources_library.used) {
      f_array_length_t link_project_library_length = fake_build_parameter_library_link_file_length + data_build.setting.project_name.used;

      char link_project_library[link_project_library_length + 1];

      memcpy(link_project_library, fake_build_parameter_library_link_file, fake_build_parameter_library_link_file_length);
      memcpy(link_project_library + fake_build_parameter_library_link_file_length, data_build.setting.project_name.string, data_build.setting.project_name.used);
      link_project_library[link_project_library_length] = 0;

      *status = fll_execute_arguments_add(link_project_library, link_project_library_length, &arguments);
    }

    fake_build_arguments_standard_add(main, data_build, F_true, F_false, &arguments, status);

    if (F_status_is_error(*status)) {
      fll_error_print(main.error, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);

      macro_f_string_dynamics_t_delete_simple(arguments);
      return 0;
    }

    int result = fake_execute(main, data_build.environment, data_build.setting.build_compiler, arguments, status);

    macro_f_string_dynamics_t_delete_simple(arguments);

    if (F_status_is_error_not(*status) && *status != F_child) {
      fake_build_touch(main, file_stage, status);
    }

    return result;
  }
#endif // _di_fake_build_program_shared_

#ifndef _di_fake_build_program_static_
  int fake_build_program_static(const fake_main_t main, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) {

    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true || *status == F_child) return main.child;
    if (!data_build.setting.build_sources_program.used) return 0;

    if (main.output.verbosity != f_console_verbosity_quiet) {
      fll_print_format("%c%[Compiling static program.%]%c", main.output.to.stream, f_string_eol_s[0], main.context.set.important, main.context.set.important, f_string_eol_s[0]);
    }

    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;

    {
      const f_string_static_t *path_sources = &main.path_sources;

      if (data_build.setting.path_standard) {
        path_sources = &main.path_sources_c;

        if (data_build.setting.build_language == fake_build_language_type_cpp) {
          path_sources = &main.path_sources_cpp;
        }
      }
      else if (main.parameters[fake_parameter_path_sources].result != f_console_result_additional) {
        path_sources = &data_build.setting.path_sources;
      }

      f_array_length_t source_length = 0;

      for (f_array_length_t i = 0; i < data_build.setting.build_sources_program.used; ++i) {

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
      f_array_length_t source_library_length = main.path_build_libraries_static.used + fake_build_parameter_library_name_prefix_length + data_build.setting.project_name.used + fake_build_parameter_library_name_suffix_static_length;

      char source_library[source_library_length + 1];

      source_library_length = 0;

      // only include the library if there are sources that would result in it being built.
      if (data_build.setting.build_sources_library.used) {
        memcpy(source_library, main.path_build_libraries_static.string, main.path_build_libraries_static.used);
        source_library_length += main.path_build_libraries_static.used;

        memcpy(source_library + source_library_length, fake_build_parameter_library_name_prefix, fake_build_parameter_library_name_prefix_length);
        source_library_length += fake_build_parameter_library_name_prefix_length;

        memcpy(source_library + source_library_length, data_build.setting.project_name.string, data_build.setting.project_name.used);
        source_library_length += data_build.setting.project_name.used;

        memcpy(source_library + source_library_length, fake_build_parameter_library_name_suffix_static, fake_build_parameter_library_name_suffix_static_length);
        source_library_length += fake_build_parameter_library_name_suffix_static_length;
      }

      source_library[source_library_length] = 0;

      f_array_length_t parameter_file_name_path_length = main.path_build_programs_static.used + data_build.setting.project_name.used;

      char parameter_file_name_path[parameter_file_name_path_length + 1];

      memcpy(parameter_file_name_path, main.path_build_programs_static.string, main.path_build_programs_static.used);
      memcpy(parameter_file_name_path + main.path_build_programs_static.used, data_build.setting.project_name.string, data_build.setting.project_name.used);
      parameter_file_name_path[parameter_file_name_path_length] = 0;

      const f_string_t values[] = {
        source_library,
        fake_build_parameter_library_static,
        fake_build_parameter_library_output,
        parameter_file_name_path,
      };

      const f_array_length_t lengths[] = {
        source_library_length,
        fake_build_parameter_library_static_length,
        fake_build_parameter_library_output_length,
        parameter_file_name_path_length,
      };

      for (uint8_t i = 0; i < 4; ++i) {

        *status = fll_execute_arguments_add(values[i], lengths[i], &arguments);
        if (F_status_is_error(*status)) break;
      } // for
    }

    fake_build_arguments_standard_add(main, data_build, F_false, F_false, &arguments, status);

    if (F_status_is_error(*status)) {
      fll_error_print(main.error, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);

      macro_f_string_dynamics_t_delete_simple(arguments);
      return 0;
    }

    int result = fake_execute(main, data_build.environment, data_build.setting.build_compiler, arguments, status);

    macro_f_string_dynamics_t_delete_simple(arguments);

    if (F_status_is_error_not(*status) && *status != F_child) {
      fake_build_touch(main, file_stage, status);
    }

    return result;
  }
#endif // _di_fake_build_program_static_

#ifndef _di_fake_build_touch_
  void fake_build_touch(const fake_main_t main, const f_string_dynamic_t file, f_status_t *status) {

    if (F_status_is_error(*status)) return;

    f_mode_t mode = f_mode_t_initialize;

    macro_f_mode_t_set_default_umask(mode, main.umask);

    if (fake_signal_received(main)) {
      *status = F_status_set_error(F_signal);

      return;
    }

    *status = f_file_touch(file.string, mode.regular, F_false);

    if (F_status_is_error(*status)) {
      fll_error_file_print(main.error, F_status_set_fine(*status), "f_file_touch", F_true, file.string, "touch", fll_error_file_type_file);
    }
  }
#endif // _di_fake_build_touch_

#ifdef __cplusplus
} // extern "C"
#endif
