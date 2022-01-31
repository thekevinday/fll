#include "fake.h"
#include "private-common.h"
#include "private-fake.h"
#include "private-build.h"
#include "private-build-library.h"
#include "private-build-load.h"
#include "private-build-objects.h"
#include "private-build-program.h"
#include "private-build-skeleton.h"
#include "private-make.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_arguments_standard_add_
  void fake_build_arguments_standard_add(fake_main_t * const main, const fake_build_data_t data_build, const bool is_shared, const bool is_library, f_string_dynamics_t *arguments, f_status_t *status) {

    if (F_status_is_error(*status)) return;

    f_array_length_t build_libraries_length = fake_build_parameter_library_link_path_s.used + main->path_build_libraries_shared.used;

    char build_libraries[build_libraries_length + 1];

    memcpy(build_libraries, fake_build_parameter_library_link_path_s.string, fake_build_parameter_library_link_path_s.used);

    if (is_shared) {
      memcpy(build_libraries + fake_build_parameter_library_link_path_s.used, main->path_build_libraries_shared.string, main->path_build_libraries_shared.used);
    }
    else {
      memcpy(build_libraries + fake_build_parameter_library_link_path_s.used, main->path_build_libraries_static.string, main->path_build_libraries_static.used);
    }

    build_libraries[build_libraries_length] = 0;

    f_array_length_t build_includes_length = fake_build_parameter_library_include_s.used + main->path_build_includes.used;

    char build_includes[build_includes_length + 1];

    memcpy(build_includes, fake_build_parameter_library_include_s.string, fake_build_parameter_library_include_s.used);
    memcpy(build_includes + fake_build_parameter_library_include_s.used, main->path_build_includes.string, main->path_build_includes.used);

    const f_string_static_t values[] = {
      macro_f_string_static_t_initialize(build_libraries, 0, build_libraries_length),
      macro_f_string_static_t_initialize(build_includes, 0, build_includes_length),
    };

    for (uint8_t i = 0; i < 2; ++i) {

      if (!values[i].used) continue;

      *status = fll_execute_arguments_add(values[i], arguments);
      if (F_status_is_error(*status)) break;
    } // for

    if (main->path_work.used) {
      f_string_static_t buffer = f_string_static_t_initialize;

      if (F_status_is_error_not(*status)) {
        buffer.used = fake_build_parameter_library_include_s.used + main->path_work_includes.used;

        char buffer_string[buffer.used + 1];

        memcpy(buffer_string, fake_build_parameter_library_include_s.string, fake_build_parameter_library_include_s.used);
        memcpy(buffer_string + fake_build_parameter_library_include_s.used, main->path_work_includes.string, main->path_work_includes.used);

        buffer_string[buffer.used] = 0;

        *status = fll_execute_arguments_add(buffer, arguments);
      }

      if (data_build.setting.search_shared && (is_shared || !data_build.setting.search_exclusive) && F_status_is_error_not(*status)) {
        buffer.used = fake_build_parameter_library_link_path_s.used + main->path_work_libraries_shared.used;

        char buffer_string[buffer.used + 1];

        memcpy(buffer_string, fake_build_parameter_library_link_path_s.string, fake_build_parameter_library_link_path_s.used);
        memcpy(buffer_string + fake_build_parameter_library_link_path_s.used, main->path_work_libraries_shared.string, main->path_work_libraries_shared.used);

        buffer_string[buffer.used] = 0;

        *status = fll_execute_arguments_add(buffer, arguments);
      }

      if (data_build.setting.search_static && (!is_shared || !data_build.setting.search_exclusive) && F_status_is_error_not(*status)) {
        buffer.used = fake_build_parameter_library_link_path_s.used + main->path_work_libraries_static.used;

        char buffer_string[buffer.used + 1];

        memcpy(buffer_string, fake_build_parameter_library_link_path_s.string, fake_build_parameter_library_link_path_s.used);
        memcpy(buffer_string + fake_build_parameter_library_link_path_s.used, main->path_work_libraries_static.string, main->path_work_libraries_static.used);

        buffer_string[buffer.used] = 0;

        *status = fll_execute_arguments_add(buffer, arguments);
      }
    }

    f_array_length_t i = 0;

    for (i = 0; i < data_build.setting.build_libraries.used && F_status_is_error_not(*status); ++i) {

      if (!data_build.setting.build_libraries.array[i].used) continue;

      *status = fll_execute_arguments_add(data_build.setting.build_libraries.array[i], arguments);
    } // for

    if (is_shared) {
      for (i = 0; i < data_build.setting.build_libraries_shared.used && F_status_is_error_not(*status); ++i) {

        if (!data_build.setting.build_libraries_shared.array[i].used) continue;

        *status = fll_execute_arguments_add(data_build.setting.build_libraries_shared.array[i], arguments);
      } // for
    }
    else {
      for (i = 0; i < data_build.setting.build_libraries_static.used && F_status_is_error_not(*status); ++i) {

        if (!data_build.setting.build_libraries_static.array[i].used) continue;

        *status = fll_execute_arguments_add(data_build.setting.build_libraries_static.array[i], arguments);
      } // for
    }

    for (i = 0; i < data_build.setting.flags.used && F_status_is_error_not(*status); ++i) {

      if (!data_build.setting.flags.array[i].used) continue;

      *status = fll_execute_arguments_add(data_build.setting.flags.array[i], arguments);
    } // for

    if (is_shared) {
      for (i = 0; i < data_build.setting.flags_shared.used && F_status_is_error_not(*status); ++i) {

        if (!data_build.setting.flags_shared.array[i].used) continue;

        *status = fll_execute_arguments_add(data_build.setting.flags_shared.array[i], arguments);
      } // for
    }
    else {
      for (i = 0; i < data_build.setting.flags_static.used && F_status_is_error_not(*status); ++i) {

        if (!data_build.setting.flags_static.array[i].used) continue;

        *status = fll_execute_arguments_add(data_build.setting.flags_static.array[i], arguments);
      } // for
    }

    if (is_library) {
      for (i = 0; i < data_build.setting.flags_library.used && F_status_is_error_not(*status); ++i) {

        if (!data_build.setting.flags_library.array[i].used) continue;

        *status = fll_execute_arguments_add(data_build.setting.flags_library.array[i], arguments);
      } // for

      if (is_shared) {
        for (i = 0; i < data_build.setting.flags_library_shared.used && F_status_is_error_not(*status); ++i) {

          if (!data_build.setting.flags_library_shared.array[i].used) continue;

          *status = fll_execute_arguments_add(data_build.setting.flags_library_shared.array[i], arguments);
        } // for
      }
      else {
        for (i = 0; i < data_build.setting.flags_library_static.used && F_status_is_error_not(*status); ++i) {

          if (!data_build.setting.flags_library_static.array[i].used) continue;

          *status = fll_execute_arguments_add(data_build.setting.flags_library_static.array[i], arguments);
        } // for
      }
    }
    else {
      for (i = 0; i < data_build.setting.flags_program.used && F_status_is_error_not(*status); ++i) {

        if (!data_build.setting.flags_program.array[i].used) continue;

        *status = fll_execute_arguments_add(data_build.setting.flags_program.array[i], arguments);
      } // for

      if (is_shared) {
        for (i = 0; i < data_build.setting.flags_program_shared.used && F_status_is_error_not(*status); ++i) {

          if (!data_build.setting.flags_program_shared.array[i].used) continue;

          *status = fll_execute_arguments_add(data_build.setting.flags_program_shared.array[i], arguments);
        } // for
      }
      else {
        for (i = 0; i < data_build.setting.flags_program_static.used && F_status_is_error_not(*status); ++i) {

          if (!data_build.setting.flags_program_static.array[i].used) continue;

          *status = fll_execute_arguments_add(data_build.setting.flags_program_static.array[i], arguments);
        } // for
      }
    }

    for (i = 0; i < data_build.setting.defines.used && F_status_is_error_not(*status); ++i) {

      if (!data_build.setting.defines.array[i].used) continue;

      *status = fll_execute_arguments_add(data_build.setting.defines.array[i], arguments);
    } // for

    if (is_shared) {
      for (i = 0; i < data_build.setting.defines_shared.used && F_status_is_error_not(*status); ++i) {

        if (!data_build.setting.defines_shared.array[i].used) continue;

        *status = fll_execute_arguments_add(data_build.setting.defines_shared.array[i], arguments);
      } // for
    }
    else {
      for (i = 0; i < data_build.setting.defines_static.used && F_status_is_error_not(*status); ++i) {

        if (!data_build.setting.defines_static.array[i].used) continue;

        *status = fll_execute_arguments_add(data_build.setting.defines_static.array[i], arguments);
      } // for
    }

    if (is_library) {
      for (i = 0; i < data_build.setting.defines_library.used && F_status_is_error_not(*status); ++i) {

        if (!data_build.setting.defines_library.array[i].used) continue;

        *status = fll_execute_arguments_add(data_build.setting.defines_library.array[i], arguments);
      } // for

      if (is_shared) {
        for (i = 0; i < data_build.setting.defines_library_shared.used && F_status_is_error_not(*status); ++i) {

          if (!data_build.setting.defines_library_shared.array[i].used) continue;

          *status = fll_execute_arguments_add(data_build.setting.defines_library_shared.array[i], arguments);
        } // for
      }
      else {
        for (i = 0; i < data_build.setting.defines_library_static.used && F_status_is_error_not(*status); ++i) {

          if (!data_build.setting.defines_library_static.array[i].used) continue;

          *status = fll_execute_arguments_add(data_build.setting.defines_library_static.array[i], arguments);
        } // for
      }
    }
    else {
      for (i = 0; i < data_build.setting.defines_program.used && F_status_is_error_not(*status); ++i) {

        if (!data_build.setting.defines_program.array[i].used) continue;

        *status = fll_execute_arguments_add(data_build.setting.defines_program.array[i], arguments);
      } // for

      if (is_shared) {
        for (i = 0; i < data_build.setting.defines_program_shared.used && F_status_is_error_not(*status); ++i) {

          if (!data_build.setting.defines_program_shared.array[i].used) continue;

          *status = fll_execute_arguments_add(data_build.setting.defines_program_shared.array[i], arguments);
        } // for
      }
      else {
        for (i = 0; i < data_build.setting.defines_program_static.used && F_status_is_error_not(*status); ++i) {

          if (!data_build.setting.defines_program_static.array[i].used) continue;

          *status = fll_execute_arguments_add(data_build.setting.defines_program_static.array[i], arguments);
        } // for
      }
    }

    for (i = 0; i < main->define.used && F_status_is_error_not(*status); ++i) {

      if (!main->define.array[i].used) continue;

      *status = fll_execute_arguments_add(main->define.array[i], arguments);
    } // for
  }
#endif // _di_fake_build_arguments_standard_add_

#ifndef _di_fake_build_copy_
  void fake_build_copy(fake_main_t * const main, const f_mode_t mode, const f_string_t label, const f_string_static_t source, const f_string_static_t destination, const f_string_statics_t files, const f_string_static_t file_stage, const f_array_length_t preserve, f_status_t *status) {

    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true || *status == F_child) return;

    if (fake_signal_received(main)) {
      *status = F_status_set_error(F_interrupt);

      return;
    }

    f_directory_statuss_t failures = f_directory_statuss_t_initialize;
    f_string_dynamic_t path_source = f_string_dynamic_t_initialize;
    f_string_dynamic_t destination_file = f_string_dynamic_t_initialize;
    f_string_dynamic_t destination_directory = f_string_dynamic_t_initialize;

    if (main->output.verbosity != f_console_verbosity_quiet_e) {
      fll_print_format("%q%[Copying %S.%]%q", main->output.to.stream, f_string_eol_s, main->context.set.important, label, main->context.set.important, f_string_eol_s);
    }

     macro_f_string_dynamic_t_resize(*status, path_source, source.used);

    if (F_status_is_error(*status)) {
      fll_error_print(main->error, F_status_set_fine(*status), " macro_f_string_dynamic_t_resize", F_true);

      f_string_dynamic_resize(0, &path_source);

      return;
    }

    memcpy(path_source.string, source.string, source.used);

    fl_directory_recurse_t recurse = fl_directory_recurse_t_initialize;

    if (main->error.verbosity == f_console_verbosity_verbose_e) {
      recurse.output.stream = main->output.to.stream;
      recurse.output.id = main->output.to.id;
      recurse.output.flag = main->output.to.flag;
      recurse.output.size_read = main->output.to.size_read;
      recurse.output.size_write = main->output.to.size_write;
      recurse.verbose = fake_verbose_print_copy;
    }

    recurse.failures = &failures;

    for (f_array_length_t i = 0; i < files.used; ++i) {

      if (!(i % fake_signal_check_short_d) && fake_signal_received(main)) {
        *status = F_status_set_error(F_interrupt);
        break;
      }

      if (!files.array[i].used) continue;

      path_source.used = source.used;

      *status = f_string_dynamic_append_nulless(files.array[i], &path_source);

      if (F_status_is_error(*status)) {
        fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_append_nulless", F_true);
        break;
      }

      *status = f_string_dynamic_terminate_after(&path_source);

      if (F_status_is_error(*status)) {
        fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_terminate_after", F_true);
        break;
      }

      *status = f_directory_is(path_source.string);

      if (*status == F_true) {
        destination_directory.used = 0;

        *status = f_string_dynamic_append(destination, &destination_directory);

        if (F_status_is_error(*status)) {
          fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_append", F_true);
          break;
        }

        *status = f_file_name_base(path_source.string, path_source.used, &destination_directory);

        if (F_status_is_error(*status)) {
          fll_error_print(main->error, F_status_set_fine(*status), "f_file_name_base", F_true);
          break;
        }

        *status = f_string_dynamic_terminate_after(&destination_directory);

        if (F_status_is_error(*status)) {
          fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_terminate_after", F_true);
          break;
        }

        *status = fl_directory_copy(path_source.string, destination_directory.string, path_source.used, destination_directory.used, mode, recurse);

        if (F_status_is_error(*status)) {
          if (main->error.verbosity == f_console_verbosity_verbose_e) {
            for (f_array_length_t j = 0; j < failures.used; ++j) {
              fake_print_error_build_operation_file(main, F_status_set_fine(*status), "fl_directory_copy", fake_common_file_directory_copy_s, f_file_operation_to_s, path_source, destination_directory, F_true);
            } // for

            if (F_status_set_fine(*status) != F_failure) {
              fll_error_print(main->error, F_status_set_fine(*status), "fl_directory_copy", F_true);
            }

            break;
          }
          else if (main->error.verbosity != f_console_verbosity_quiet_e) {
            fake_print_error_build_operation_file(main, F_status_set_fine(*status), "fl_directory_copy", fake_common_file_directory_copy_s, f_file_operation_to_s, path_source, destination_directory, F_true);
          }

          break;
        }
      }
      else if (*status == F_false) {
        destination_file.used = 0;
        destination_directory.used = 0;

        *status = f_string_dynamic_append_nulless(destination, &destination_file);

        if (F_status_is_error(*status)) {
          fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_append_nulless", F_true);
          break;
        }

        if (preserve && preserve < path_source.used) {
          *status = f_string_dynamic_append_nulless(destination, &destination_directory);

          if (F_status_is_error(*status)) {
            fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_append_nulless", F_true);
            break;
          }

          *status = f_file_name_directory(path_source.string + preserve, path_source.used - preserve, &destination_directory);

          if (F_status_is_error(*status)) {
            fll_error_print(main->error, F_status_set_fine(*status), "f_file_name_directory", F_true);
            break;
          }

          *status = f_string_dynamic_terminate_after(&destination_directory);

          if (F_status_is_error(*status)) {
            fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_terminate_after", F_true);
            break;
          }

          *status = fl_directory_create(destination_directory.string, destination_directory.used, F_file_mode_all_rwx_d);

          if (F_status_is_error(*status)) {
            fll_error_file_print(main->error, F_status_set_fine(*status), "fl_directory_create", F_true, destination_directory.string, "create", fll_error_file_type_directory_e);
            break;
          }

          *status = f_string_append(path_source.string + preserve, path_source.used - preserve, &destination_file);

          if (F_status_is_error(*status)) {
            fll_error_print(main->error, F_status_set_fine(*status), "f_string_append", F_true);
            break;
          }
        }
        else {
          *status = f_file_name_base(path_source.string, path_source.used, &destination_file);

          if (F_status_is_error(*status)) {
            fll_error_print(main->error, F_status_set_fine(*status), "f_file_name_base", F_true);
            break;
          }
        }

        *status = f_string_dynamic_terminate_after(&destination_file);

        if (F_status_is_error(*status)) {
          fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_terminate_after", F_true);
          break;
        }

        *status = f_file_copy(path_source.string, destination_file.string, mode, F_file_default_read_size_d, F_false);

        if (F_status_is_error(*status)) {
          fake_print_error_build_operation_file(main, F_status_set_fine(*status), "f_file_copy", F_file_operation_copy_s, f_file_operation_to_s, path_source, destination_file, F_true);
          break;
        }

        if (main->error.verbosity == f_console_verbosity_verbose_e) {
          fll_print_format("Copied file '%Q' to '%Q'.%q", main->output.to.stream, path_source, destination_file, f_string_eol_s);
        }
      }
      else if (F_status_is_error(*status)) {
        fll_error_file_print(main->error, F_status_set_fine(*status), "f_directory_is", F_true, path_source, f_file_operation_create_s, fll_error_file_type_file_e);
        break;
      }

      *status = F_none;
    } // for

    macro_f_directory_statuss_t_delete_simple(failures);

    f_string_dynamic_resize(0, &path_source);
    f_string_dynamic_resize(0, &destination_file);
    f_string_dynamic_resize(0, &destination_directory);

    if (F_status_is_error_not(*status)) {
      fake_build_touch(main, file_stage, status);
    }
  }
#endif // _di_fake_build_copy_

#ifndef _di_fake_build_execute_process_script_
  int fake_build_execute_process_script(fake_main_t * const main, const fake_build_data_t data_build, const f_string_static_t process_script, const f_string_static_t file_stage, f_status_t *status) {

    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true || *status == F_child) return main->child;
    if (!process_script.used) return 0;

    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;

    *status = fll_execute_arguments_add(fake_other_operation_build_s, &arguments);

    // Ensure console color mode is passed to the scripts so that they can also react to color mode.
    if (F_status_is_error_not(*status) && main->context.mode != F_color_mode_none_d) {
      f_string_static_t argument = f_string_static_t_initialize;
      argument.used = f_console_symbol_short_disable_s.used + f_console_standard_short_dark_s.used;

      char argument_string[argument.used + 1];
      argument_string[argument.used] = 0;

      memcpy(argument_string, f_console_symbol_short_disable_s.string, f_console_symbol_short_disable_s.used);

      if (main->context.mode == F_color_mode_dark_d) {
        memcpy(argument_string + f_console_symbol_short_disable_s.used, f_console_standard_short_dark_s.string, f_console_standard_short_dark_s.used);
      }
      else if (main->context.mode == F_color_mode_light_d) {
        memcpy(argument_string + f_console_symbol_short_disable_s.used, f_console_standard_short_light_s.string, f_console_standard_short_light_s.used);
      }
      else if (main->context.mode == F_color_mode_no_color_d) {
        memcpy(argument_string + f_console_symbol_short_disable_s.used, f_console_standard_short_no_color_s.string, f_console_standard_short_no_color_s.used);
      }

      *status = fll_execute_arguments_add(argument, &arguments);
    }

    // Ensure verbosity level is passed to the scripts so that they can also react to requested verbosity.
    if (F_status_is_error_not(*status) && main->error.verbosity != f_console_verbosity_normal_e) {
      f_string_static_t argument = f_string_static_t_initialize;
      argument.used = f_console_symbol_short_disable_s.used + f_console_standard_short_quiet_s.used;

      char argument_string[argument.used + 1];
      argument_string[argument.used] = 0;

      memcpy(argument_string, f_console_symbol_short_disable_s.string, f_console_symbol_short_disable_s.used);

      if (main->context.mode == f_console_verbosity_quiet_e) {
        memcpy(argument_string + f_console_symbol_short_disable_s.used, f_console_standard_short_quiet_s.string, f_console_standard_short_quiet_s.used);
      }
      else if (main->context.mode == f_console_verbosity_verbose_e) {
        memcpy(argument_string + f_console_symbol_short_disable_s.used, f_console_standard_short_verbose_s.string, f_console_standard_short_verbose_s.used);
      }
      else if (main->context.mode == f_console_verbosity_debug_e) {
        memcpy(argument_string + f_console_symbol_short_disable_s.used, f_console_standard_short_debug_s.string, f_console_standard_short_debug_s.used);
      }

      *status = fll_execute_arguments_add(argument, &arguments);
    }

    if (F_status_is_error(*status)) {
      fll_error_print(main->error, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);

      f_string_dynamics_resize(0, &arguments);

      return 0;
    }

    {
      f_string_dynamic_t defines = f_string_dynamic_t_initialize;

      if (main->define.used) {
        for (f_array_length_t i = 0; i < main->define.used; ++i) {

          *status = f_string_dynamic_mash(f_string_space_s, main->define.array[i], &defines);
          if (F_status_is_error(*status)) break;
        } // for

        if (F_status_is_error(*status)) {
          fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_mash", F_true);

          f_string_dynamic_resize(0, &defines);
          f_string_dynamics_resize(0, &arguments);

          return 0;
        }

        *status = f_string_dynamic_terminate_after(&defines);

        if (F_status_is_error(*status)) {
          fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_terminate_after", F_true);

          f_string_dynamic_resize(0, &defines);
          f_string_dynamics_resize(0, &arguments);

          return 0;
        }
      }

      const f_string_static_t parameters_prefix[] = {
        f_console_symbol_short_enable_s,
        f_console_symbol_short_enable_s,
        f_console_symbol_short_enable_s,
        f_console_symbol_short_enable_s,
        f_console_symbol_short_enable_s,
        f_console_symbol_short_enable_s,
        f_console_symbol_short_enable_s,
      };

      const f_string_static_t parameters_name[] = {
        fake_short_define_s,
        fake_short_process_s,
        fake_short_settings_s,
        fake_short_path_build_s,
        fake_short_path_data_s,
        fake_short_path_sources_s,
        fake_short_path_work_s,
      };

      const f_string_static_t parameters_value[] = {
        defines,
        main->process,
        main->settings,
        main->path_build,
        main->path_data,
        main->path_sources,
        main->path_work,
      };

      *status = fll_execute_arguments_add_parameter_set(parameters_prefix, parameters_name, parameters_value, 7, &arguments);

      f_string_dynamic_resize(0, &defines);

      if (F_status_is_error(*status)) {
        fll_error_print(main->error, F_status_set_fine(*status), "fll_execute_arguments_add_parameter_set", F_true);

        f_string_dynamics_resize(0, &arguments);

        return 0;
      }
    }

    f_string_dynamic_t path = f_string_dynamic_t_initialize;
    f_string_t function = 0;

    {
      function = "f_string_dynamic_append_nulless";

      if (process_script.string[0] != '/') {
        *status = f_string_dynamic_append_nulless(main->path_data_build, &path);
      }

      if (F_status_is_error_not(*status)) {
        *status = f_string_dynamic_append_nulless(process_script, &path);
      }

      if (F_status_is_error_not(*status)) {
        function = "f_string_dynamic_terminate_after";
        *status = f_string_dynamic_terminate_after(&path);
      }

      if (F_status_is_error(*status)) {
        fll_error_print(main->error, F_status_set_fine(*status), function, F_true);

        f_string_dynamic_resize(0, &path);
        f_string_dynamics_resize(0, &arguments);

        return 0;
      }
    }

    int return_code = 0;

    // Child processes should receive all signals, without blocking.
    f_signal_how_t signals = f_signal_how_t_initialize;
    f_signal_set_empty(&signals.block);
    f_signal_set_fill(&signals.block_not);

    fl_execute_parameter_t parameter = macro_fl_execute_parameter_t_initialize(FL_execute_parameter_option_path_d, 0, &data_build.environment, &signals, 0);

    *status = fll_execute_program(path, arguments, &parameter, 0, (void *) &return_code);

    f_string_dynamics_resize(0, &arguments);

    if (fake_signal_received(main)) {
      *status = F_status_set_error(F_interrupt);
    }
    else if (*status != F_child) {
      if (F_status_is_error(*status)) {
        if (F_status_set_fine(*status) == F_failure) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            flockfile(main->error.to.stream);

            fl_print_format("%q%[%QFailed to execute script: '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, path, main->error.notable);
            fl_print_format("%['.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

            funlockfile(main->error.to.stream);
          }
        }
        else {
          fll_error_print(main->error, F_status_set_fine(*status), "fll_execute_program", F_true);
        }
      }
      else {
        fake_build_touch(main, file_stage, status);
      }
    }

    f_string_dynamic_resize(0, &path);

    return return_code;
  }
#endif // _di_fake_build_execute_process_script_

#ifndef _di_fake_build_get_file_name_without_extension_
  f_status_t fake_build_get_file_name_without_extension(fake_main_t * const main, const f_string_static_t path, f_string_dynamic_t *name) {

    name->used = 0;

    if (!path.used) return F_none;

    f_status_t status = f_file_name_base(path.string, path.used, name);

    if (F_status_is_error(status)) {
      fll_error_print(main->error, F_status_set_fine(status), "f_file_name_base", F_true);

      return status;
    }

    f_array_length_t i = name->used;

    for (; i > 0; --i) {

      if (name->string[i] == f_path_extension_separator_s.string[0]) {
        name->used = i;
        break;
      }
    } // for

    status = f_string_dynamic_terminate_after(name);

    if (F_status_is_error(status)) {
      fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);

      return status;
    }

    return F_none;
  }
#endif // _di_fake_build_get_file_name_without_extension_

#ifndef _di_fake_build_operate_
  f_status_t fake_build_operate(const f_string_static_t setting_file, fake_main_t *main) {

    if (fake_signal_received(main)) {
      return F_status_set_error(F_interrupt);
    }

    f_status_t status = F_none;
    f_mode_t mode = f_mode_t_initialize;

    fake_build_data_t data_build = fake_build_data_t_initialize;
    fake_build_stage_t stage = fake_build_stage_t_initialize;

    macro_f_mode_t_set_default_umask(mode, main->umask);

    fake_build_load_setting(main, setting_file, &data_build.setting, &status);

    if (F_status_is_fine(status)) {
      if (main->output.verbosity != f_console_verbosity_quiet_e) {
        flockfile(main->output.to.stream);

        fl_print_format("%q%[Building project%] ", main->output.to.stream, f_string_eol_s, main->context.set.important, main->context.set.important);
        fl_print_format("%[%Q%]", main->output.to.stream, main->context.set.notable, data_build.setting.project_name, main->context.set.notable);
        fl_print_format("%[.%]%q", main->output.to.stream, main->context.set.important, main->context.set.important, f_string_eol_s);

        funlockfile(main->output.to.stream);
      }
    }

    fake_build_load_stage(main, setting_file, &stage, &status);

    fake_build_load_environment(main, data_build, &data_build.environment, &status);

    fake_build_skeleton(main, data_build, mode.directory, stage.file_skeleton, &status);

    main->child = fake_build_execute_process_script(main, data_build, data_build.setting.process_pre, stage.file_process_pre, &status);

    fake_build_copy(main, mode, "setting files", main->path_data_settings, main->path_build_settings, data_build.setting.build_sources_setting, stage.file_sources_settings, 0, &status);

    if (data_build.setting.build_language == fake_build_language_type_bash_e) {
      fake_build_library_script(main, data_build, mode, stage.file_libraries_script, &status);

      fake_build_program_script(main, data_build, mode, stage.file_programs_script, &status);

      if (data_build.setting.build_script) {
        fake_build_copy(main, mode, "scripts", main->path_sources_script, main->path_build_programs_script, data_build.setting.build_sources_script, stage.file_sources_script, 0, &status);
      }
    }
    else {
      if (data_build.setting.build_sources_headers.used) {
        f_string_static_t path_sources = main->path_sources;

        if (data_build.setting.path_standard) {
          path_sources = main->path_sources_c;

          if (data_build.setting.build_language == fake_build_language_type_cpp_e) {
            path_sources = main->path_sources_cpp;
          }
        }
        else if (main->parameters.array[fake_parameter_path_sources_e].result != f_console_result_additional_e) {
          path_sources = data_build.setting.path_sources;
        }

        const f_array_length_t path_sources_base_length = path_sources.used;

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

        fake_build_copy(main, mode, "header files", path_sources, path_headers, data_build.setting.build_sources_headers, stage.file_sources_headers, data_build.setting.path_headers_preserve ? path_sources_base_length : 0, &status);

        if (data_build.setting.build_shared) {
          fake_build_copy(main, mode, "shared header files", path_sources, path_headers, data_build.setting.build_sources_headers_shared, stage.file_sources_headers, data_build.setting.path_headers_preserve ? path_sources_base_length : 0, &status);
        }

        if (data_build.setting.build_static) {
          fake_build_copy(main, mode, "static header files", path_sources, path_headers, data_build.setting.build_sources_headers_static, stage.file_sources_headers, data_build.setting.path_headers_preserve ? path_sources_base_length : 0, &status);
        }
      }

      if (data_build.setting.build_shared) {
        main->child = fake_build_library_shared(main, data_build, mode, stage.file_libraries_shared, &status);

        main->child = fake_build_program_shared(main, data_build, mode, stage.file_programs_shared, &status);
      }

      if (data_build.setting.build_static) {
        main->child = fake_build_objects_static(main, data_build, mode, stage.file_objects_static, &status);

        main->child = fake_build_library_static(main, data_build, mode, stage.file_libraries_static, &status);

        main->child = fake_build_program_static(main, data_build, mode, stage.file_programs_static, &status);
      }

      if (data_build.setting.build_script) {
        fake_build_copy(main, mode, "scripts", main->path_sources_script, main->path_build_programs_script, data_build.setting.build_sources_script, stage.file_sources_script, 0, &status);
      }
    }

    fake_build_execute_process_script(main, data_build, data_build.setting.process_post, stage.file_process_post, &status);

    macro_fake_build_main_delete_simple(data_build);
    macro_fake_build_stage_t_delete_simple(stage);

    return status;
  }
#endif // _di_fake_build_operate_

#ifndef _di_fake_build_touch_
  void fake_build_touch(fake_main_t * const main, const f_string_dynamic_t file, f_status_t *status) {

    if (F_status_is_error(*status)) return;

    if (fake_signal_received(main)) {
      *status = F_status_set_error(F_interrupt);
      return;
    }

    f_mode_t mode = f_mode_t_initialize;

    macro_f_mode_t_set_default_umask(mode, main->umask);

    *status = f_file_touch(file.string, mode.regular, F_false);

    if (F_status_is_error(*status)) {
      fll_error_file_print(main->error, F_status_set_fine(*status), "f_file_touch", F_true, file.string, "touch", fll_error_file_type_file_e);
    }
  }
#endif // _di_fake_build_touch_

#ifdef __cplusplus
} // extern "C"
#endif
