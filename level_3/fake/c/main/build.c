#include "fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_arguments_standard_add_
  void fake_build_arguments_standard_add(fake_data_t * const data, fake_build_data_t * const data_build, const bool is_shared, const uint8_t type, f_string_dynamics_t *arguments) {

    if (!data || !data_build || !arguments) return;
    if (F_status_is_error(data->setting.state.status)) return;

    {
      f_array_length_t build_libraries_length = fake_build_parameter_library_link_path_s.used + data->path_build_libraries_shared.used;

      f_char_t build_libraries[build_libraries_length + 1];
      build_libraries[build_libraries_length] = 0;

      memcpy(build_libraries, fake_build_parameter_library_link_path_s.string, sizeof(f_char_t) * fake_build_parameter_library_link_path_s.used);

      if (is_shared) {
        memcpy(build_libraries + fake_build_parameter_library_link_path_s.used, data->path_build_libraries_shared.string, sizeof(f_char_t) * data->path_build_libraries_shared.used);
      }
      else {
        memcpy(build_libraries + fake_build_parameter_library_link_path_s.used, data->path_build_libraries_static.string, sizeof(f_char_t) * data->path_build_libraries_static.used);
      }

      f_array_length_t build_includes_length = fake_build_parameter_library_include_s.used + data->path_build_includes.used;

      f_char_t build_includes[build_includes_length + 1];
      build_includes[build_includes_length] = 0;

      memcpy(build_includes, fake_build_parameter_library_include_s.string, sizeof(f_char_t) * fake_build_parameter_library_include_s.used);
      memcpy(build_includes + fake_build_parameter_library_include_s.used, data->path_build_includes.string, sizeof(f_char_t) * data->path_build_includes.used);

      const f_string_static_t values[] = {
        macro_f_string_static_t_initialize(build_libraries, 0, build_libraries_length),
        macro_f_string_static_t_initialize(build_includes, 0, build_includes_length),
      };

      for (uint8_t i = 0; i < 2; ++i) {

        if (!values[i].used) continue;

        data->setting.state.status = fll_execute_arguments_add(values[i], arguments);
        if (F_status_is_error(data->setting.state.status)) return;
      } // for
    }

    if (data->setting->work.used) {
      f_string_static_t buffer = f_string_static_t_initialize;

      {
        buffer.used = fake_build_parameter_library_include_s.used + data->path_work_includes.used;

        f_char_t buffer_string[buffer.used + 1];
        buffer.string = buffer_string;
        buffer_string[buffer.used] = 0;

        memcpy(buffer_string, fake_build_parameter_library_include_s.string, sizeof(f_char_t) * fake_build_parameter_library_include_s.used);
        memcpy(buffer_string + fake_build_parameter_library_include_s.used, data->path_work_includes.string, sizeof(f_char_t) * data->path_work_includes.used);

        data->setting.state.status = fll_execute_arguments_add(buffer, arguments);
        if (F_status_is_error(data->setting.state.status)) return;
      }

      if (data_build->setting.search_shared && (is_shared || !data_build->setting.search_exclusive)) {
        buffer.used = fake_build_parameter_library_link_path_s.used + data->path_work_libraries_shared.used;

        f_char_t buffer_string[buffer.used + 1];
        buffer.string = buffer_string;
        buffer_string[buffer.used] = 0;

        memcpy(buffer_string, fake_build_parameter_library_link_path_s.string, sizeof(f_char_t) * fake_build_parameter_library_link_path_s.used);
        memcpy(buffer_string + fake_build_parameter_library_link_path_s.used, data->path_work_libraries_shared.string, sizeof(f_char_t) * data->path_work_libraries_shared.used);

        data->setting.state.status = fll_execute_arguments_add(buffer, arguments);
        if (F_status_is_error(data->setting.state.status)) return;
      }

      if (data_build->setting.search_static && (!is_shared || !data_build->setting.search_exclusive)) {
        buffer.used = fake_build_parameter_library_link_path_s.used + data->path_work_libraries_static.used;

        f_char_t buffer_string[buffer.used + 1];
        buffer.string = buffer_string;
        buffer_string[buffer.used] = 0;

        memcpy(buffer_string, fake_build_parameter_library_link_path_s.string, sizeof(f_char_t) * fake_build_parameter_library_link_path_s.used);
        memcpy(buffer_string + fake_build_parameter_library_link_path_s.used, data->path_work_libraries_static.string, sizeof(f_char_t) * data->path_work_libraries_static.used);

        data->setting.state.status = fll_execute_arguments_add(buffer, arguments);
        if (F_status_is_error(data->setting.state.status)) return;
      }
    }

    {
      f_string_statics_t * const strings[] = {
        &data_build->setting.build_libraries,
        (is_shared) ? &data_build->setting.build_libraries_shared : &data_build->setting.build_libraries_static,
        &data_build->setting.flags,
        (is_shared) ? &data_build->setting.flags_shared : &data_build->setting.flags_static,
        (type == fake_build_type_library_e)
          ? &data_build->setting.flags_library
          : (type == fake_build_type_object_e)
            ? &data_build->setting.flags_object
            : &data_build->setting.flags_program,
        (type == fake_build_type_library_e)
          ? (is_shared)
            ? &data_build->setting.flags_library_shared
            : &data_build->setting.flags_library_static
          : (type == fake_build_type_object_e)
            ? (is_shared)
              ? &data_build->setting.flags_object_shared
              : &data_build->setting.flags_object_static
            : (is_shared)
              ? &data_build->setting.flags_program_shared
              : &data_build->setting.flags_program_static,
        &data_build->setting.defines,
        (is_shared) ? &data_build->setting.defines_shared : &data_build->setting.defines_static,
        &data_build->setting.defines_library,
        (type == fake_build_type_library_e)
          ? &data_build->setting.defines_library
          : (type == fake_build_type_object_e)
            ? &data_build->setting.defines_object
            : &data_build->setting.defines_program,
        (type == fake_build_type_library_e)
          ? (is_shared)
            ? &data_build->setting.defines_library_shared
            : &data_build->setting.defines_library_static
          : (type == fake_build_type_object_e)
            ? (is_shared)
              ? &data_build->setting.defines_object_shared
              : &data_build->setting.defines_object_static
            : (is_shared)
              ? &data_build->setting.defines_program_shared
              : &data_build->setting.defines_program_static,
        &data->setting->defines,
      };

      f_array_length_t i = 0;

      for (uint8_t s = 0; s < 12; ++s) {

        for (i = 0; i < strings[s]->used; ++i) {

          if (!strings[s]->array[i].used) continue;

          data->setting.state.status = fll_execute_arguments_add(strings[s]->array[i], arguments);
          if (F_status_is_error(data->setting.state.status)) return;
        } // for
      } // for
    }

    data->setting.state.status = F_none;
  }
#endif // _di_fake_build_arguments_standard_add_

#ifndef _di_fake_build_copy_
  void fake_build_copy(fake_data_t * const data, const f_mode_t mode, const f_string_static_t label, const f_string_static_t source, const f_string_static_t destination, const f_string_statics_t files, const f_string_static_t file_stage, const f_array_length_t perserve_offset) {

    if (!data) return;
    if (F_status_is_error(data->setting.state.status) || f_file_exists(file_stage, F_true) == F_true || data->setting.state.status == F_child) return;

    if (!((++data->main->signal_check) % fake_signal_check_d)) {
      if (fll_program_standard_signal_received(data->main)) {
        fll_program_print_signal_received(data->main->warning, data->setting->line_first, data->main->signal_received);

        data->setting.state.status = F_status_set_error(F_interrupt);

        return;
      }
    }

    f_directory_statuss_t failures = f_directory_statuss_t_initialize;
    f_string_dynamic_t path_source = f_string_dynamic_t_initialize; // @todo move this to a shared buffer.
    f_string_dynamic_t destination_file = f_string_dynamic_t_initialize;
    f_string_dynamic_t destination_directory = f_string_dynamic_t_initialize;
    f_string_static_t buffer = f_string_static_t_initialize;

    if (data->main->message.verbosity != f_console_verbosity_quiet_e && data->main->message.verbosity != f_console_verbosity_error_e) {
      fll_print_format("%r%[Copying %Q.%]%r", data->main->message.to, f_string_eol_s, data->main->context.set.important, label, data->main->context.set.important, f_string_eol_s);
    }

    data->setting.state.status = f_string_dynamic_resize(source.used, &path_source);

    if (F_status_is_error(data->setting.state.status)) {
      fake_print_error(data->setting, data->main->error, data->setting.state.status, macro_fake_f(f_string_dynamic_resize));

      f_string_dynamic_resize(0, &path_source);

      return;
    }

    memcpy(path_source.string, source.string, sizeof(f_char_t) * source.used);

    f_directory_recurse_t recurse = f_directory_recurse_t_initialize;

    if (data->main->error.verbosity >= f_console_verbosity_verbose_e) {
      recurse.output = data->main->message.to;
      recurse.verbose = fake_print_verbose_copy;
    }

    recurse.failures = &failures;

    for (f_array_length_t i = 0; i < files.used; ++i) {

      if (!((++data->main->signal_check) % fake_signal_check_short_d)) {
        if (fll_program_standard_signal_received(data->main)) {
          fll_program_print_signal_received(data->main->warning, data->setting->line_first, data->main->signal_received);

          data->setting.state.status = F_status_set_error(F_interrupt);

          break;
        }

        data->main->signal_check = 0;
      }

      if (!files.array[i].used) continue;

      path_source.used = source.used;

      data->setting.state.status = f_string_dynamic_append_nulless(files.array[i], &path_source);

      if (F_status_is_error(data->setting.state.status)) {
        fake_print_error(data->setting, data->main->error, data->setting.state.status, macro_fake_f(f_string_dynamic_append_nulless));

        break;
      }

      data->setting.state.status = f_directory_is(path_source);

      if (data->setting.state.status == F_true) {
        destination_directory.used = 0;

        data->setting.state.status = f_string_dynamic_append_nulless(destination, &destination_directory);

        if (F_status_is_error(data->setting.state.status)) {
          fake_print_error(data->setting, data->main->error, data->setting.state.status, macro_fake_f(f_string_dynamic_append_nulless));

          break;
        }

        data->setting.state.status = f_file_name_base(path_source, &destination_directory);

        if (F_status_is_error(data->setting.state.status)) {
          fake_print_error(data->setting, data->main->error, data->setting.state.status, macro_fake_f(f_file_name_base));

          break;
        }

        data->setting.state.status = fl_directory_copy(path_source, destination_directory, mode, recurse);

        if (F_status_is_error(data->setting.state.status)) {
          if (data->main->error.verbosity >= f_console_verbosity_verbose_e) {
            for (f_array_length_t j = 0; j < failures.used; ++j) {

              fake_print_error_build_operation_file(data->setting, data->main->error, macro_fake_f(fl_directory_copy), fake_common_file_directory_copy_s, f_file_operation_to_s, path_source, destination_directory, F_true);
            } // for

            if (F_status_set_fine(data->setting.state.status) != F_failure) {
              fake_print_error(data->setting, data->main->error, data->setting.state.status, macro_fake_f(fl_directory_copy));
            }
          }
          else if (data->main->error.verbosity > f_console_verbosity_quiet_e) {
            fake_print_error_build_operation_file(data->setting, data->main->error, macro_fake_f(fl_directory_copy), fake_common_file_directory_copy_s, f_file_operation_to_s, path_source, destination_directory, F_true);
          }

          break;
        }
      }
      else if (data->setting.state.status == F_false) {
        destination_file.used = 0;
        destination_directory.used = 0;

        data->setting.state.status = f_string_dynamic_append_nulless(destination, &destination_file);

        if (F_status_is_error(data->setting.state.status)) {
          fake_print_error(data->setting, data->main->error, data->setting.state.status, macro_fake_f(f_string_dynamic_append_nulless));

          break;
        }

        if (perserve_offset && perserve_offset < path_source.used) {
          data->setting.state.status = f_string_dynamic_append_nulless(destination, &destination_directory);

          if (F_status_is_error(data->setting.state.status)) {
            fake_print_error(data->setting, data->main->error, data->setting.state.status, macro_fake_f(f_string_dynamic_append_nulless));

            break;
          }

          buffer.string = path_source.string + perserve_offset;
          buffer.used = path_source.used - perserve_offset;

          data->setting.state.status = f_file_name_directory(buffer, &destination_directory);

          if (F_status_is_error(data->setting.state.status)) {
            fake_print_error(data->setting, data->main->error, data->setting.state.status, macro_fake_f(f_file_name_directory));

            break;
          }

          data->setting.state.status = fl_directory_create(destination_directory, F_file_mode_all_rwx_d);

          if (F_status_is_error(data->setting.state.status)) {
            fake_print_error_file(data->setting, data->main->error, data->setting.state.status, macro_fake_f(fl_directory_create), destination_directory, f_file_operation_create_s, fll_error_file_type_directory_e);

            break;
          }

          data->setting.state.status = f_string_append(path_source.string + perserve_offset, path_source.used - perserve_offset, &destination_file);

          if (F_status_is_error(data->setting.state.status)) {
            fake_print_error(data->setting, data->main->error, data->setting.state.status, macro_fake_f(f_string_append));

            break;
          }
        }
        else {
          data->setting.state.status = f_file_name_base(path_source, &destination_file);

          if (F_status_is_error(data->setting.state.status)) {
            fake_print_error(data->setting, data->main->error, data->setting.state.status, macro_fake_f(f_file_name_base));

            break;
          }
        }

        data->setting.state.status = f_file_copy(path_source, destination_file, mode, F_file_default_read_size_d, f_file_stat_flag_reference_e);

        if (F_status_is_error(data->setting.state.status)) {
          fake_print_error_build_operation_file(data->setting, data->main->error, data->setting.state.status, macro_fake_f(f_file_copy), f_file_operation_copy_s, f_file_operation_to_s, path_source, destination_file, F_true);

          break;
        }

        if (data->main->error.verbosity >= f_console_verbosity_verbose_e) {
          fll_print_format("Copied file '%Q' to '%Q'.%r", data->main->message.to, path_source, destination_file, f_string_eol_s);
        }
      }
      else if (F_status_is_error(data->setting.state.status)) {
        fake_print_error_file(data->setting, data->main->error, data->setting.state.status, macro_fake_f(f_directory_is), path_source, f_file_operation_create_s, fll_error_file_type_file_e);

        break;
      }

      data->setting.state.status = F_none;
    } // for

    macro_f_directory_statuss_t_delete_simple(failures);

    f_directory_recurse_delete(&recurse);

    f_string_dynamic_resize(0, &path_source);
    f_string_dynamic_resize(0, &destination_file);
    f_string_dynamic_resize(0, &destination_directory);

    fake_build_touch(data, file_stage);
  }
#endif // _di_fake_build_copy_

#ifndef _di_fake_build_execute_process_script_
  int fake_build_execute_process_script(fake_data_t * const data, fake_build_data_t * const data_build, const f_string_static_t process_script, const f_string_static_t file_stage) {

    if (!data) return;
    if (F_status_is_error(data->setting.state.status) || f_file_exists(file_stage, F_true) == F_true || data->setting.state.status == F_child) return data->main->child;
    if (!process_script.used) return 0;

    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;

    data->setting.state.status = fll_execute_arguments_add(fake_other_operation_build_s, &arguments);

    // Ensure console color mode is passed to the scripts so that they can also react to color mode.
    if (F_status_is_error_not(data->setting.state.status) && data->main->context.mode != f_color_mode_none_e) {
      f_string_static_t argument = f_string_static_t_initialize;
      argument.used = f_console_symbol_short_inverse_s.used + f_console_standard_short_dark_s.used;

      f_char_t argument_string[argument.used + 1];
      argument.string = argument_string;
      argument_string[argument.used] = 0;

      memcpy(argument_string, f_console_symbol_short_inverse_s.string, sizeof(f_char_t) * f_console_symbol_short_inverse_s.used);

      if (data->main->context.mode == f_color_mode_dark_e) {
        memcpy(argument_string + f_console_symbol_short_inverse_s.used, f_console_standard_short_dark_s.string, sizeof(f_char_t) * f_console_standard_short_dark_s.used);
      }
      else if (data->main->context.mode == f_color_mode_light_e) {
        memcpy(argument_string + f_console_symbol_short_inverse_s.used, f_console_standard_short_light_s.string, sizeof(f_char_t) * f_console_standard_short_light_s.used);
      }
      else if (data->main->context.mode == f_color_mode_not_e) {
        memcpy(argument_string + f_console_symbol_short_inverse_s.used, f_console_standard_short_no_color_s.string, sizeof(f_char_t) * f_console_standard_short_no_color_s.used);
      }

      data->setting.state.status = fll_execute_arguments_add(argument, &arguments);
    }

    // Ensure verbosity level is passed to the scripts so that they can also react to requested verbosity.
    if (F_status_is_error_not(data->setting.state.status) && data->main->error.verbosity != f_console_verbosity_normal_e) {
      f_string_static_t argument = f_string_static_t_initialize;
      argument.used = f_console_symbol_short_inverse_s.used + f_console_standard_short_quiet_s.used;

      f_char_t argument_string[argument.used + 1];
      argument.string = argument_string;
      argument_string[argument.used] = 0;

      memcpy(argument_string, f_console_symbol_short_inverse_s.string, sizeof(f_char_t) * f_console_symbol_short_inverse_s.used);

      if (data->main->context.mode == f_console_verbosity_quiet_e) {
        memcpy(argument_string + f_console_symbol_short_inverse_s.used, f_console_standard_short_quiet_s.string, sizeof(f_char_t) * f_console_standard_short_quiet_s.used);
      }
      else if (data->main->context.mode == f_console_verbosity_error_e) {
        memcpy(argument_string + f_console_symbol_short_inverse_s.used, f_console_standard_short_error_s.string, sizeof(f_char_t) * f_console_standard_short_error_s.used);
      }
      else if (data->main->context.mode == f_console_verbosity_verbose_e) {
        memcpy(argument_string + f_console_symbol_short_inverse_s.used, f_console_standard_short_verbose_s.string, sizeof(f_char_t) * f_console_standard_short_verbose_s.used);
      }
      else if (data->main->context.mode == f_console_verbosity_debug_e) {
        memcpy(argument_string + f_console_symbol_short_inverse_s.used, f_console_standard_short_debug_s.string, sizeof(f_char_t) * f_console_standard_short_debug_s.used);
      }

      data->setting.state.status = fll_execute_arguments_add(argument, &arguments);
    }

    if (F_status_is_error(data->setting.state.status)) {
      fake_print_error(data->setting, data->main->error, macro_fake_f(fll_execute_arguments_add));

      f_string_dynamics_resize(0, &arguments);

      return 0;
    }

    {
      f_string_dynamic_t defines = f_string_dynamic_t_initialize;

      if (data->setting->defines.used) {
        for (f_array_length_t i = 0; i < data->setting->defines.used; ++i) {

          data->setting.state.status = f_string_dynamic_mash(f_string_space_s, data->setting->defines.array[i], &defines);
          if (F_status_is_error(data->setting.state.status)) break;
        } // for

        if (F_status_is_error(data->setting.state.status)) {
          fake_print_error(data->setting, data->main->error, macro_fake_f(f_string_dynamic_mash));

          f_string_dynamic_resize(0, &defines);
          f_string_dynamics_resize(0, &arguments);

          return 0;
        }
      }

      const f_string_static_t prefixs[] = {
        f_console_symbol_short_normal_s, // fake_short_build_s
        f_console_symbol_short_normal_s, // fake_short_data_s
        f_console_symbol_short_normal_s, // fake_short_define_s
        f_console_symbol_short_normal_s, // fake_short_documents_s
        f_console_symbol_short_normal_s, // fake_short_licenses_s
        f_console_symbol_short_normal_s, // fake_short_process_s
        f_console_symbol_short_normal_s, // fake_short_settings_s
        f_console_symbol_short_normal_s, // fake_short_sources_s
        f_console_symbol_short_normal_s, // fake_short_work_s
      };

      const f_string_static_t names[] = {
        fake_short_build_s,
        fake_short_data_s,
        fake_short_define_s,
        fake_short_documents_s,
        fake_short_licenses_s,
        fake_short_process_s,
        fake_short_settings_s,
        fake_short_sources_s,
        fake_short_work_s,
      };

      const f_string_static_t values[] = {
        data->setting->build,
        data->setting->data,
        defines,
        data->setting->documents,
        data->setting->licenses,
        data->setting->process,
        data->setting->settings,
        data_build->setting.path_sources,
        data->setting->work,
      };

      data->setting.state.status = fll_execute_arguments_add_parameter_set(prefixs, names, values, 9, &arguments);

      f_string_dynamic_resize(0, &defines);

      if (F_status_is_error(data->setting.state.status)) {
        fake_print_error(data->setting, data->main->error, macro_fake_f(fll_execute_arguments_add_parameter_set));

        f_string_dynamics_resize(0, &arguments);

        return 0;
      }
    }

    f_string_dynamic_t path = f_string_dynamic_t_initialize;

    if (process_script.string[0] != '/') {
      data->setting.state.status = f_string_dynamic_append_nulless(data->path_data_build, &path);
    }

    if (F_status_is_error_not(data->setting.state.status)) {
      data->setting.state.status = f_string_dynamic_append_nulless(process_script, &path);
    }

    if (F_status_is_error(data->setting.state.status)) {
      fake_print_error(data->setting, data->main->error, data->setting.state.status, macro_fake_f(f_string_dynamic_append_nulless));

      f_string_dynamic_resize(0, &path);
      f_string_dynamics_resize(0, &arguments);

      return 0;
    }

    int return_code = 0;

    // Child processes should receive all signals, without blocking.
    f_signal_how_t signals = f_signal_how_t_initialize;
    f_signal_set_empty(&signals.block);
    f_signal_set_fill(&signals.block_not);

    fl_execute_parameter_t parameter = macro_fl_execute_parameter_t_initialize(FL_execute_parameter_option_path_d, 0, &data_build->environment, &signals, 0);

    data->setting.state.status = fll_execute_program(path, arguments, &parameter, 0, (void *) &return_code);

    f_string_dynamics_resize(0, &arguments);

    if (!((++data->main->signal_check) % fake_signal_check_d) && fll_program_standard_signal_received(data->main)) {
      fll_program_print_signal_received(data->main->warning, data->setting->line_first, data->main->signal_received);

      data->setting.state.status = F_status_set_error(F_interrupt);
    }
    else if (data->setting.state.status != F_child) {
      if (F_status_is_error(data->setting.state.status)) {
        if (F_status_set_fine(data->setting.state.status) == F_failure) {
          fake_print_error_failure_script(data->setting, data->main->error, path);
        }
        else {
          fake_print_error(data->setting, data->main->error, macro_fake_f(fll_execute_program));
        }
      }
      else {
        fake_build_touch(data, file_stage);
      }
    }

    f_string_dynamic_resize(0, &path);

    return return_code;
  }
#endif // _di_fake_build_execute_process_script_

#ifndef _di_fake_build_get_file_name_without_extension_
  void fake_build_get_file_name_without_extension(fake_data_t * const data, const f_string_static_t path, f_string_dynamic_t *name) {

    if (!data) return;

    name->used = 0;
    data->setting.state.status = F_none;

    if (!path.used) return;

    data->setting.state.status = f_file_name_base(path, name);

    if (F_status_is_error(data->setting.state.status)) {
      fake_print_error(data->setting, data->main->error, macro_fake_f(f_file_name_base));

      return;
    }

    for (f_array_length_t i = name->used; i > 0; --i) {

      if (name->string[i] == f_path_extension_separator_s.string[0]) {
        name->used = i;

        break;
      }
    } // for

    data->setting.state.status = F_none;
  }
#endif // _di_fake_build_get_file_name_without_extension_

#ifndef _di_fake_build_objects_add_
  void fake_build_objects_add(fake_data_t * const data, fake_build_data_t * const data_build, const f_string_static_t *path, const f_string_statics_t *generic, const f_string_statics_t *specific, f_string_dynamics_t *arguments) {

    if (!data || !data_build || !path || !generic || !specific || !arguments) return;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_string_static_t source = f_string_static_t_initialize;

    const f_string_statics_t *sources[2] = {
      generic,
      specific,
    };

    for (; i < 2; ++i) {

      for (j = 0; j < sources[i]->used; ++j) {

        if (!sources[i]->array[j].used) continue;

        source.used = path->used + sources[i]->array[j].used;

        f_char_t source_string[source.used + 1];
        source.string = source_string;
        source_string[source.used] = 0;

        memcpy(source_string, path->string, sizeof(f_char_t) * path->used);
        memcpy(source_string + path->used, sources[i]->array[j].string, sizeof(f_char_t) * sources[i]->array[j].used);

        data->setting.state.status = fll_execute_arguments_add(source, arguments);
        if (F_status_is_error(data->setting.state.status)) return;
      } // for
    } // for

    data->setting.state.status = F_none;
  }
#endif // _di_fake_build_objects_add_

#ifndef _di_fake_build_operate_
  void fake_build_operate(fake_data_t * const data, const f_string_statics_t * const build_arguments, const bool process_pipe) {

    if (!data) return;

    if (!((++data->main->signal_check) % fake_signal_check_d)) {
      if (fll_program_standard_signal_received(data->main)) {
        fll_program_print_signal_received(data->main->warning, data->setting->line_first, data->main->signal_received);

        data->setting.state.status = F_status_set_error(F_interrupt);

        return;
      }
    }

    data->setting.state.status = F_none;

    f_mode_t mode = f_mode_t_initialize;

    fake_build_data_t data_build = fake_build_data_t_initialize;
    fake_build_stage_t stage = fake_build_stage_t_initialize;

    macro_f_mode_t_set_default_umask(mode, data->main->umask);

    fake_build_load_setting(data, build_arguments, process_pipe, &data_build.setting);

    if (F_status_is_fine(data->setting.state.status)) {
      if (data->main->message.verbosity != f_console_verbosity_quiet_e && data->main->message.verbosity != f_console_verbosity_error_e) {
        f_file_stream_lock(data->main->message.to);

        fl_print_format("%[Building%] ", data->main->message.to, data->main->context.set.important, data->main->context.set.important);
        fl_print_format("%[%Q%]", data->main->message.to, data->main->context.set.notable, data_build.setting.build_name, data->main->context.set.notable);
        fl_print_format("%[ using '%]", data->main->message.to, data->main->context.set.important, data->main->context.set.important);
        fl_print_format("%[%Q%]", data->main->message.to, data->main->context.set.notable, data->setting->settings, data->main->context.set.notable);

        fl_print_format("%[' with modes '%]", data->main->message.to, data->main->context.set.important, data->main->context.set.important);

        f_string_statics_t modes_custom = f_string_statics_t_initialize;
        modes_custom.used = build_arguments && build_arguments->used > 1 ? build_arguments->used - 1 : 0;
        modes_custom.size = 0;

        f_string_static_t modes_custom_array[modes_custom.used];
        modes_custom.array = modes_custom_array;

        for (f_array_length_t i = 0; i < modes_custom.used; ++i) {
          modes_custom.array[i] = build_arguments->array[i + 1];
        } // for

        // Custom modes are always used if provided, otherwise if any mode is specified, the entire defaults is replaced.
        const f_string_statics_t * const modes = modes_custom.used
          ? &modes_custom
          : data->setting->modes.used
            ? &data->setting->modes
            : &data_build.setting.modes_default;

        for (f_array_length_t i = 0; i < modes->used; ) {

          fl_print_format("%[%Q%]", data->main->message.to, data->main->context.set.notable, modes->array[i], data->main->context.set.notable);

          if (++i < modes->used) {
            fl_print_format("%[', '%]", data->main->message.to, data->main->context.set.important, data->main->context.set.important);
          }
        } // for

        fl_print_format("%['.%]%r", data->main->message.to, data->main->context.set.important, data->main->context.set.important, f_string_eol_s);

        f_file_stream_unlock(data->main->message.to);
      }
    }

    fake_build_load_stage(data, build_arguments && build_arguments->array[0].used ? build_arguments->array[0] : f_string_empty_s, &stage);

    fake_build_load_environment(data, &data_build, &data_build.environment);

    fake_build_skeleton(data, &data_build, mode.directory, stage.file_skeleton);

    data->main->child = fake_build_execute_process_script(data, &data_build, data_build.setting.process_pre, stage.file_process_pre);

    fake_build_copy(data, mode, fake_build_documentation_files_s, data->path_data_documentation, data->path_build_documentation, data_build.setting.build_sources_documentation, stage.file_sources_documentation, 0);

    fake_build_copy(data, mode, fake_build_setting_files_s, data->path_data_settings, data->path_build_settings, data_build.setting.build_sources_setting, stage.file_sources_settings, 0);

    if (data_build.setting.build_language == fake_build_language_bash_e) {
      fake_build_object_script(data, &data_build, mode, stage.file_object_script);

      fake_build_library_script(data, &data_build, mode, stage.file_library_script);

      fake_build_program_script(data, &data_build, mode, stage.file_program_script);

      if (data_build.setting.build_script) {
        f_string_static_t source = f_string_static_t_initialize;

        fake_build_path_source_length(data, &data_build, &data_build.setting.path_sources, &source);

        f_char_t source_string[source.used + fake_path_part_script_s.used + 1];
        source.string = source_string;

        fake_build_path_source_string(data, &data_build, &data_build.setting.path_sources, &source);

        memcpy(source_string + source.used, fake_path_part_script_s.string, sizeof(f_char_t) * fake_path_part_script_s.used);
        source.used += fake_path_part_script_s.used;
        source.string[source.used] = 0;

        fake_build_copy(data, mode, fake_build_scripts_s, source, data->path_build_programs_script, data_build.setting.build_sources_script, stage.file_sources_script, 0);
      }
    }
    else {
      if (data_build.setting.build_sources_headers.used) {
        f_string_static_t source = f_string_static_t_initialize;

        fake_build_path_source_length(data, &data_build, &data_build.setting.path_sources, &source);

        f_char_t source_string[source.used + 1];
        source.string = source_string;

        fake_build_path_source_string(data, &data_build, &data_build.setting.path_sources, &source);

        f_string_static_t path_headers = f_string_static_t_initialize;
        path_headers.used = data->path_build_includes.used + data_build.setting.path_headers.used;

        f_char_t path_headers_string[path_headers.used + 1];
        path_headers.string = path_headers_string;

        memcpy(path_headers_string, data->path_build_includes.string, sizeof(f_char_t) * data->path_build_includes.used);

        if (data_build.setting.path_headers.used) {
          memcpy(path_headers_string + data->path_build_includes.used, data_build.setting.path_headers.string, sizeof(f_char_t) * data_build.setting.path_headers.used);
        }

        path_headers_string[path_headers.used] = 0;

        fake_build_copy(data, mode, fake_build_header_files_s, source, path_headers, data_build.setting.build_sources_headers, stage.file_sources_headers, data_build.setting.preserve_path_headers ? source.used : 0);

        if (data_build.setting.build_shared) {
          fake_build_copy(data, mode, fake_build_header_files_shared_s, source, path_headers, data_build.setting.build_sources_headers_shared, stage.file_sources_headers, data_build.setting.preserve_path_headers ? source.used : 0);
        }

        if (data_build.setting.build_static) {
          fake_build_copy(data, mode, fake_build_header_files_static_s, source, path_headers, data_build.setting.build_sources_headers_static, stage.file_sources_headers, data_build.setting.preserve_path_headers ? source.used : 0);
        }
      }

      if (data_build.setting.build_shared) {
        data->main->child = fake_build_object_shared(data, &data_build, mode, stage.file_object_shared);

        data->main->child = fake_build_library_shared(data, &data_build, mode, stage.file_library_shared);

        data->main->child = fake_build_program_shared(data, &data_build, mode, stage.file_program_shared);
      }

      if (data_build.setting.build_static) {
        data->main->child = fake_build_object_static(data, &data_build, mode, stage.file_object_static);

        data->main->child = fake_build_objects_static(data, &data_build, mode, stage.file_objects_static);

        data->main->child = fake_build_library_static(data, &data_build, mode, stage.file_library_static);

        data->main->child = fake_build_program_static(data, &data_build, mode, stage.file_program_static);
      }

      if (data_build.setting.build_script) {
        f_string_static_t source = f_string_static_t_initialize;

        fake_build_path_source_length(data, &data_build, &data_build.setting.path_sources, &source);

        f_char_t source_string[source.used + fake_path_part_script_s.used + 1];
        source.string = source_string;

        fake_build_path_source_string(data, &data_build, &data_build.setting.path_sources, &source);

        memcpy(source_string + source.used, fake_path_part_script_s.string, sizeof(f_char_t) * fake_path_part_script_s.used);
        source.used += fake_path_part_script_s.used;
        source.string[source.used] = 0;

        fake_build_copy(data, mode, fake_build_scripts_s, source, data->path_build_programs_script, data_build.setting.build_sources_script, stage.file_sources_script, 0);
      }
    }

    fake_build_execute_process_script(data, &data_build, data_build.setting.process_post, stage.file_process_post);

    macro_fake_build_main_delete_simple(data_build);
    macro_fake_build_stage_t_delete_simple(stage);
  }
#endif // _di_fake_build_operate_

#ifndef _di_fake_build_path_source_length_
  void fake_build_path_source_length(fake_data_t * const data, fake_build_data_t * const data_build, f_string_static_t * const setting_path_source, f_string_static_t * const source) {

    if (!data || !data_build || !setting_path_source || !source) return;

    source->used = 0;

    if (setting_path_source->used) {
      source->used += setting_path_source->used;
    }

    if (data_build->setting.has_path_standard) {
      if (data_build->setting.build_language == fake_build_language_c_e) {
        source->used += fake_build_language_c_s.used;
      }
      else if (data_build->setting.build_language == fake_build_language_cpp_e) {
        source->used += fake_build_language_cpp_s.used;
      }
      else if (data_build->setting.build_language == fake_build_language_bash_e) {
        source->used += fake_build_language_bash_s.used;
      }

      source->used += f_path_separator_s.used;
    }
  }
#endif // _di_fake_build_path_source_length_

#ifndef _di_fake_build_path_source_string_
  void fake_build_path_source_string(fake_data_t * const data, fake_build_data_t * const data_build, f_string_static_t * const setting_path_source) {

    if (!data || !data_build || !setting_path_source) return;

    source->used = 0;

    memcpy(source->string + source->used, setting_path_source->string, sizeof(f_char_t) * setting_path_source->used);
    source->used += setting_path_source->used;

    if (data_build->setting.has_path_standard) {
      if (data_build->setting.build_language == fake_build_language_c_e) {
        memcpy(source->string + source->used, fake_build_language_c_s.string, sizeof(f_char_t) * fake_build_language_c_s.used);
        source->used += fake_build_language_c_s.used;
      }
      else if (data_build->setting.build_language == fake_build_language_cpp_e) {
        memcpy(source->string + source->used, fake_build_language_cpp_s.string, sizeof(f_char_t) * fake_build_language_cpp_s.used);
        source->used += fake_build_language_cpp_s.used;
      }
      else if (data_build->setting.build_language == fake_build_language_bash_e) {
        memcpy(source->string + source->used, fake_build_language_bash_s.string, sizeof(f_char_t) * fake_build_language_bash_s.used);
        source->used += fake_build_language_bash_s.used;
      }

      memcpy(source->string + source->used, f_path_separator_s.string, sizeof(f_char_t) * f_path_separator_s.used);
      source->used += f_path_separator_s.used;
    }

    source->string[source->used] = 0;
  }
#endif // _di_fake_build_path_source_string_

#ifndef _di_fake_build_sources_add_
  void fake_build_sources_add(fake_data_t * const data, fake_build_data_t * const data_build, const f_string_statics_t *generic, const f_string_statics_t *specific, f_string_dynamics_t *arguments) {

    if (!data || !data_build || !generic || !specific || !arguments) return;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    const f_string_statics_t *sources[2] = {
      generic,
      specific,
    };

    f_string_static_t source = f_string_static_t_initialize;

    for (; i < 2; ++i) {

      for (j = 0; j < sources[i]->used; ++j) {

        if (!sources[i]->array[j].used) continue;

        fake_build_path_source_length(data, data_build, &data_build->setting.path_sources, &source);

        f_char_t source_string[source.used + sources[i]->array[j].used + 1];
        source.string = source_string;

        fake_build_path_source_string(data, data_build, &data_build->setting.path_sources, &source);

        memcpy(source_string + source.used, sources[i]->array[j].string, sizeof(f_char_t) * sources[i]->array[j].used);
        source.used += sources[i]->array[j].used;
        source.string[source.used] = 0;

        data->setting.state.status = fll_execute_arguments_add(source, arguments);
        if (F_status_is_error(data->setting.state.status)) return;
      } // for
    } // for

    data->setting.state.status = F_none;
  }
#endif // _di_fake_build_sources_add_

#ifndef _di_fake_build_sources_object_add_
  void fake_build_sources_object_add(fake_data_t * const data, fake_build_data_t * const data_build, const f_string_static_t *generic, const f_string_static_t *specific, f_string_dynamics_t *arguments) {

    if (!data || !data_build || !generic || !specific || !arguments) return;

    if (!generic->used && !specific->used) {
      data->setting.state.status = F_none;

      return;
    }

    f_string_static_t source = f_string_static_t_initialize;

    fake_build_path_source_length(data, data_build, &data_build->setting.path_sources_object, &source);

    if (specific->used) {
      source.used += specific->used;
    }
    else {
      source.used += generic->used;
    }

    f_char_t source_string[source.used + 1];
    source.string = source_string;

    fake_build_path_source_string(data, data_build, &data_build->setting.path_sources_object, &source);

    if (specific->used) {
      memcpy(source_string + source.used, specific->string, sizeof(f_char_t) * specific->used);
      source.used += specific->used;
    }
    else {
      memcpy(source_string + source.used, generic->string, sizeof(f_char_t) * generic->used);
      source.used += generic->used;
    }

    source_string[source.used] = 0;

    data->setting.state.status = fll_execute_arguments_add(source, arguments);
    if (F_status_is_error(data->setting.state.status)) return;

    data->setting.state.status = F_none;
  }
#endif // _di_fake_build_sources_object_add_

#ifndef _di_fake_build_touch_
  void fake_build_touch(fake_data_t * const data, const f_string_dynamic_t file) {

    if (!data) return;
    if (F_status_is_error(data->setting.state.status)) return;

    if (!((++data->main->signal_check) % fake_signal_check_d)) {
      if (fll_program_standard_signal_received(data->main)) {
        fll_program_print_signal_received(data->main->warning, data->setting->line_first, data->main->signal_received);

        data->setting.state.status = F_status_set_error(F_interrupt);

        return;
      }
    }

    f_mode_t mode = f_mode_t_initialize;

    macro_f_mode_t_set_default_umask(mode, data->main->umask);

    data->setting.state.status = f_file_touch(file, mode.regular, F_false);

    if (F_status_is_error(data->setting.state.status)) {
      fake_print_error_file(data->setting, data->main->error, macro_fake_f(f_file_touch), file, f_file_operation_touch_s, fll_error_file_type_file_e);
    }
    else {
      data->setting.state.status = F_none;
    }
  }
#endif // _di_fake_build_touch_

#ifdef __cplusplus
} // extern "C"
#endif