#include "fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_arguments_standard_add_
  void fake_build_arguments_standard_add(fake_data_t * const data, fake_build_data_t * const data_build, const bool is_shared, const uint8_t type) {

    if (!data || !data->main || !data_build) return;
    if (F_status_is_error(data->main->setting.state.status)) return;

    fake_main_t * const main = data->main;

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

        main->setting.state.status = fll_execute_arguments_add(values[i], &main->cache_arguments);
        if (F_status_is_error(main->setting.state.status)) return;
      } // for
    }

    if (main->setting.work.used) {
      f_string_static_t buffer = f_string_static_t_initialize;

      {
        buffer.used = fake_build_parameter_library_include_s.used + data->path_work_includes.used;

        f_char_t buffer_string[buffer.used + 1];
        buffer.string = buffer_string;
        buffer_string[buffer.used] = 0;

        memcpy(buffer_string, fake_build_parameter_library_include_s.string, sizeof(f_char_t) * fake_build_parameter_library_include_s.used);
        memcpy(buffer_string + fake_build_parameter_library_include_s.used, data->path_work_includes.string, sizeof(f_char_t) * data->path_work_includes.used);

        main->setting.state.status = fll_execute_arguments_add(buffer, &main->cache_arguments);
        if (F_status_is_error(main->setting.state.status)) return;
      }

      if (data_build->setting.search_shared && (is_shared || !data_build->setting.search_exclusive)) {
        buffer.used = fake_build_parameter_library_link_path_s.used + data->path_work_libraries_shared.used;

        f_char_t buffer_string[buffer.used + 1];
        buffer.string = buffer_string;
        buffer_string[buffer.used] = 0;

        memcpy(buffer_string, fake_build_parameter_library_link_path_s.string, sizeof(f_char_t) * fake_build_parameter_library_link_path_s.used);
        memcpy(buffer_string + fake_build_parameter_library_link_path_s.used, data->path_work_libraries_shared.string, sizeof(f_char_t) * data->path_work_libraries_shared.used);

        main->setting.state.status = fll_execute_arguments_add(buffer, &main->cache_arguments);
        if (F_status_is_error(main->setting.state.status)) return;
      }

      if (data_build->setting.search_static && (!is_shared || !data_build->setting.search_exclusive)) {
        buffer.used = fake_build_parameter_library_link_path_s.used + data->path_work_libraries_static.used;

        f_char_t buffer_string[buffer.used + 1];
        buffer.string = buffer_string;
        buffer_string[buffer.used] = 0;

        memcpy(buffer_string, fake_build_parameter_library_link_path_s.string, sizeof(f_char_t) * fake_build_parameter_library_link_path_s.used);
        memcpy(buffer_string + fake_build_parameter_library_link_path_s.used, data->path_work_libraries_static.string, sizeof(f_char_t) * data->path_work_libraries_static.used);

        main->setting.state.status = fll_execute_arguments_add(buffer, &main->cache_arguments);
        if (F_status_is_error(main->setting.state.status)) return;
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
        &main->setting.defines,
      };

      f_array_length_t i = 0;

      for (uint8_t s = 0; s < 12; ++s) {

        for (i = 0; i < strings[s]->used; ++i) {

          if (!strings[s]->array[i].used) continue;

          main->setting.state.status = fll_execute_arguments_add(strings[s]->array[i], &main->cache_arguments);
          if (F_status_is_error(main->setting.state.status)) return;
        } // for
      } // for
    }

    main->setting.state.status = F_none;
  }
#endif // _di_fake_build_arguments_standard_add_

#ifndef _di_fake_build_copy_
  void fake_build_copy(fake_data_t * const data, const f_mode_t mode, const f_string_static_t label, const f_string_static_t source, const f_string_static_t destination, const f_string_statics_t files, const f_string_static_t file_stage, const f_array_length_t perserve_offset) {

    if (!data || !data->main) return;
    if (data->main->setting.state.status == F_child) return;
    if (F_status_is_error(data->main->setting.state.status) || f_file_exists(file_stage, F_true) == F_true) return;
    if (fake_signal_check(data->main)) return;

    fake_main_t * const main = data->main;

    fake_string_dynamic_reset(&main->cache_argument);

    f_string_static_t buffer = f_string_static_t_initialize;
    f_status_t failed = F_none;
    fake_local_t local = macro_fake_local_t_initialize_1(main, &main->cache_map, &failed);

    fake_build_print_message_copying(&main->program.message, label);

    main->setting.state.status = f_string_dynamic_append_nulless(source, &main->cache_argument);

    if (F_status_is_error(main->setting.state.status)) {
      fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

      return;
    }

    f_directory_recurse_do_t recurse = f_directory_recurse_do_t_initialize;
    recurse.action = &fake_build_copy_action;
    recurse.handle = &fake_build_copy_handle;
    recurse.state.custom = (void *) &local;
    recurse.state.code = fake_state_code_local_e;
    recurse.flag = f_directory_recurse_do_flag_top_e & f_directory_recurse_do_flag_before_e & f_directory_recurse_do_flag_after_e;
    recurse.mode = mode;

    for (f_array_length_t i = 0; i < files.used; ++i) {

      if (fake_signal_check(main)) break;
      if (!files.array[i].used) continue;

      main->cache_argument.used = source.used;

      main->setting.state.status = f_string_dynamic_append_nulless(files.array[i], &main->cache_argument);

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

        break;
      }

      main->setting.state.status = f_directory_is(main->cache_argument);

      if (main->setting.state.status == F_true) {
        main->cache_map.name.used = 0;

        main->setting.state.status = f_string_dynamic_append_nulless(destination, &main->cache_map.name);

        if (F_status_is_error(main->setting.state.status)) {
          fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

          break;
        }

        main->setting.state.status = f_file_name_base(main->cache_argument, &main->cache_map.name);

        if (F_status_is_error(main->setting.state.status)) {
          fake_print_error(&main->program.error, macro_fake_f(f_file_name_base));

          break;
        }

        fl_directory_do(main->cache_argument, &recurse);
        if (F_status_is_error(main->setting.state.status)) break;
      }
      else if (main->setting.state.status == F_false) {
        fake_string_dynamic_reset(&main->cache_map.name);
        fake_string_dynamic_reset(&main->cache_map.value);

        main->setting.state.status = f_string_dynamic_append_nulless(destination, &main->cache_map.value);

        if (F_status_is_error(main->setting.state.status)) {
          fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

          break;
        }

        if (perserve_offset && perserve_offset < main->cache_argument.used) {
          main->setting.state.status = f_string_dynamic_append_nulless(destination, &main->cache_map.name);

          if (F_status_is_error(main->setting.state.status)) {
            fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

            break;
          }

          buffer.string = main->cache_argument.string + perserve_offset;
          buffer.used = main->cache_argument.used - perserve_offset;

          main->setting.state.status = f_file_name_directory(buffer, &main->cache_map.name);

          if (F_status_is_error(main->setting.state.status)) {
            fake_print_error(&main->program.error, macro_fake_f(f_file_name_directory));

            break;
          }

          main->setting.state.status = fl_directory_create(main->cache_map.name, F_file_mode_all_rwx_d);

          if (F_status_is_error(main->setting.state.status)) {
            fake_print_error_file(&main->program.error, macro_fake_f(fl_directory_create), main->cache_map.name, f_file_operation_create_s, fll_error_file_type_directory_e);

            break;
          }

          main->setting.state.status = f_string_append(main->cache_argument.string + perserve_offset, main->cache_argument.used - perserve_offset, &main->cache_map.value);

          if (F_status_is_error(main->setting.state.status)) {
            fake_print_error(&main->program.error, macro_fake_f(f_string_append));

            break;
          }
        }
        else {
          main->setting.state.status = f_file_name_base(main->cache_argument, &main->cache_map.value);

          if (F_status_is_error(main->setting.state.status)) {
            fake_print_error(&main->program.error, macro_fake_f(f_file_name_base));

            break;
          }
        }

        fake_build_print_verbose_copying(&main->program.message, main->cache_argument, main->cache_map.value);

        main->setting.state.status = f_file_copy(main->cache_argument, main->cache_map.value, mode, F_file_default_read_size_d, f_file_stat_flag_reference_e);

        if (F_status_is_error(main->setting.state.status)) {
          fake_print_error_build_operation_file(&main->program.error, macro_fake_f(f_file_copy), f_file_operation_copy_s, f_file_operation_to_s, main->cache_argument, main->cache_map.value, F_true);

          break;
        }
      }
      else if (F_status_is_error(main->setting.state.status)) {
        fake_print_error_file(&main->program.error, macro_fake_f(f_directory_is), main->cache_argument, f_file_operation_create_s, fll_error_file_type_file_e);

        break;
      }

      main->setting.state.status = F_none;
    } // for

    if (F_status_is_error(failed)) {
      main->setting.state.status = F_status_set_error(F_failure);
    }

    f_directory_recurse_do_delete(&recurse);

    fake_build_touch(data, file_stage);
  }
#endif // _di_fake_build_copy_

#ifndef _di_fake_build_copy_action_
  void fake_build_copy_action(void * const void_recurse, const f_string_static_t name, const uint16_t flag) {

    if (!void_recurse) return;

    f_directory_recurse_do_t * const recurse = (f_directory_recurse_do_t *) void_recurse;

    if (!recurse->custom) return;

    fake_local_t * const local = (fake_local_t *) recurse->custom;

    if (!local->custom_1) {
      recurse->state.status = F_status_set_error(F_parameter);

      return;
    }

    f_string_map_t * const map_destination = (f_string_map_t *) local->custom_1;

    if (flag & f_directory_recurse_do_flag_top_e) {
      fake_string_dynamic_reset(&map_destination->value);

      recurse->state.status = F_none;

      return;
    }

    if (flag & f_directory_recurse_do_flag_before_e) {

      // Push the name on the path stack (the destination path is expected to be pre-populated).
      recurse->state.status = f_string_dynamic_increase_by(f_path_separator_s.used + name.used + 1, &map_destination->name);

      if (F_status_is_error_not(recurse->state.status)) {
        recurse->state.status = f_string_dynamic_append(f_path_separator_s, &map_destination->name);
      }

      if (F_status_is_error_not(recurse->state.status)) {
        recurse->state.status = f_string_dynamic_append_nulless(name, &map_destination->name);
      }

      // Guaranetee NULL terminated string.
      map_destination->name.string[map_destination->name.used] = 0;

      return;
    }

    if (flag & f_directory_recurse_do_flag_after_e) {

      // Pop the current path off of the path stack.
      map_destination->name.used -= f_path_separator_s.used + name.used;

      recurse->state.status = F_none;

      return;
    }

    fake_string_dynamic_reset(&recurse->path_cache);
    fake_string_dynamic_reset(&map_destination->value);

    recurse->state.status = f_string_dynamic_increase_by(recurse->path.used + f_path_separator_s.used + name.used + 1, &recurse->path_cache);

    if (F_status_is_error_not(recurse->state.status)) {
      recurse->state.status = f_string_dynamic_append_nulless(map_destination->name, &recurse->path_cache);
    }

    if (F_status_is_error_not(recurse->state.status)) {
      recurse->state.status = f_string_dynamic_append(f_path_separator_s, &recurse->path_cache);
    }

    if (F_status_is_error_not(recurse->state.status)) {
      recurse->state.status = f_string_dynamic_append_nulless(name, &recurse->path_cache);
    }

    if (F_status_is_error_not(recurse->state.status)) {
      recurse->state.status = f_string_dynamic_increase_by(map_destination->name.used + f_path_separator_s.used + name.used + 1, &map_destination->value);
    }

    if (F_status_is_error_not(recurse->state.status)) {
      recurse->state.status = f_string_dynamic_append_nulless(map_destination->name, &map_destination->value);
    }

    if (F_status_is_error_not(recurse->state.status)) {
      recurse->state.status = f_string_dynamic_append(f_path_separator_s, &map_destination->value);
    }

    if (F_status_is_error_not(recurse->state.status)) {
      recurse->state.status = f_string_dynamic_append_nulless(name, &map_destination->value);
    }

    // Guaranetee NULL terminated strings.
    recurse->path_cache.string[recurse->path_cache.used] = 0;
    map_destination->value.string[map_destination->value.used] = 0;

    if (F_status_is_error(recurse->state.status)) {
      fake_string_dynamic_reset(&map_destination->value);

      return;
    }

    fake_build_print_verbose_copying(&local->main->program.message, recurse->path_cache, map_destination->value);

    recurse->state.status = f_file_copy(recurse->path_cache, map_destination->value, recurse->mode, F_file_default_read_size_d, f_file_stat_flag_reference_e);
  }
#endif // _di_fake_build_copy_action_

#ifndef _di_fake_build_copy_handle_
  void fake_build_copy_handle(void * const void_recurse, const f_string_static_t name, const uint16_t flag) {

    if (!void_recurse) return;

    f_directory_recurse_do_t * const recurse = (f_directory_recurse_do_t *) void_recurse;

    // Do not print any errors on interrupts.
    if (F_status_set_fine(recurse->state.status) == F_interrupt) return;

    if (!recurse->custom) return;

    fake_local_t * const local = (fake_local_t *) recurse->custom;

    if (!local->main || !local->custom_1 || !local->custom_2) return;

    *((f_status_t *) local->custom_2) = F_status_set_error(F_failure);

    if (flag & f_directory_recurse_do_flag_top_e) {
      local->main->setting.state.status = recurse->state.status;

      if (flag == (f_directory_recurse_do_flag_top_e | f_directory_recurse_do_flag_path_e)) {
        fake_print_error_file(&local->main->program.error, macro_fake_f(fl_directory_do), *recurse->path_top, f_file_operation_copy_s, fll_error_file_type_directory_e);
      }
      else if (flag == (f_directory_recurse_do_flag_top_e | f_directory_recurse_do_flag_before_e | f_directory_recurse_do_flag_path_e)) {
        fake_print_error_file(&local->main->program.error, macro_fake_f(f_directory_exists), *recurse->path_top, f_file_operation_copy_s, fll_error_file_type_directory_e);
      }
      else if (flag == (f_directory_recurse_do_flag_top_e | f_directory_recurse_do_flag_after_e | f_directory_recurse_do_flag_path_e)) {
        fake_print_error_file(&local->main->program.error, macro_fake_f(fl_directory_do), *recurse->path_top, f_file_operation_copy_s, fll_error_file_type_directory_e);
      }

      return;
    }

    f_string_map_t * const map_destination = (f_string_map_t *) local->custom_1;

    if (flag == (flag & f_directory_recurse_do_flag_path_e)) {
      // @todo this is old and may not be correct anymore.
      fake_print_error_build_operation_file_recurse(&local->main->program.error, macro_fake_f(fl_directory_list), f_file_operation_copy_s, f_file_operation_to_s, recurse->path, name, map_destination->name, name, F_true);

      return;
    }

    if (flag & f_directory_recurse_do_flag_directory_e) {
      // @todo

      //fake_print_error_build_operation_file_recurse(&local->main->program.error, macro_fake_f(f_file_copy), f_file_operation_copy_s, f_file_operation_to_s, recurse->path, name, map_destination->name, name, F_true);

      return;
    }

    // The value.used is set to 0 on allocation related failures so that better error messaging can be performed.
    if (map_destination->value.used) {
      fake_print_error_build_operation_file_recurse(&local->main->program.error, macro_fake_f(f_file_copy), f_file_operation_copy_s, f_file_operation_to_s, recurse->path, name, map_destination->name, name, F_true);
    }
    else if (map_destination->name.used) {
      f_char_t destination[map_destination->name.used + f_path_separator_s.used + name.used];

      memcpy(destination, map_destination->name.string, map_destination->name.used);
      memcpy(destination + map_destination->name.used, f_path_separator_s.string, f_path_separator_s.used);
      memcpy(destination + map_destination->name.used + f_path_separator_s.used, name.string, name.used);

      fake_print_error_build_operation_file_recurse(&local->main->program.error, macro_fake_f(f_file_copy), f_file_operation_copy_s, f_file_operation_to_s, recurse->path, name, map_destination->name, name, F_true);
    }
    else {
      fake_print_error_build_operation_file_recurse(&local->main->program.error, macro_fake_f(fl_directory_do), f_file_operation_copy_s, f_file_operation_to_s, recurse->path, name, f_string_empty_s, f_string_empty_s, F_true);
    }
  }
#endif // _di_fake_build_copy_handle_

#ifndef _di_fake_build_execute_process_script_
  int fake_build_execute_process_script(fake_data_t * const data, fake_build_data_t * const data_build, const f_string_static_t process_script, const f_string_static_t file_stage) {

    if (!data || !data->main || !data_build) return 0;
    if (data->main->setting.state.status == F_child) return data->main->program.child;
    if (F_status_is_error(data->main->setting.state.status) || f_file_exists(file_stage, F_true) == F_true) return 0;
    if (!process_script.used) return 0;

    fake_main_t * const main = data->main;

    fake_string_dynamics_reset(&main->cache_arguments);

    main->setting.state.status = fll_execute_arguments_add(fake_other_operation_build_s, &main->cache_arguments);

    // Ensure console color mode is passed to the scripts so that they can also react to color mode.
    if (F_status_is_error_not(main->setting.state.status) && main->program.context.mode != f_color_mode_none_e) {
      fake_string_dynamic_reset(&main->cache_argument);

      main->setting.state.status = f_string_dynamic_append(f_console_symbol_short_inverse_s, &main->cache_argument);

      if (F_status_is_error_not(main->setting.state.status)) {
        if (main->program.context.mode == f_color_mode_dark_e) {
          main->setting.state.status = f_string_dynamic_append(f_console_standard_short_dark_s, &main->cache_argument);
        }
        else if (main->program.context.mode == f_color_mode_light_e) {
          main->setting.state.status = f_string_dynamic_append(f_console_standard_short_light_s, &main->cache_argument);
        }
        else if (main->program.context.mode == f_color_mode_not_e) {
          main->setting.state.status = f_string_dynamic_append(f_console_standard_short_no_color_s, &main->cache_argument);
        }
      }

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append));

        return 0;
      }

      main->setting.state.status = fll_execute_arguments_add(main->cache_argument, &main->cache_arguments);
    }

    // Ensure verbosity level is passed to the scripts so that they can also react to requested verbosity.
    if (F_status_is_error_not(main->setting.state.status) && main->program.error.verbosity != f_console_verbosity_normal_e) {
      fake_string_dynamic_reset(&main->cache_argument);

      main->setting.state.status = f_string_dynamic_append(f_console_symbol_short_inverse_s, &main->cache_argument);

      if (F_status_is_error_not(main->setting.state.status)) {
        if (main->program.context.mode == f_console_verbosity_quiet_e) {
          main->setting.state.status = f_string_dynamic_append(f_console_standard_short_quiet_s, &main->cache_argument);
        }
        else if (main->program.context.mode == f_console_verbosity_error_e) {
          main->setting.state.status = f_string_dynamic_append(f_console_standard_short_error_s, &main->cache_argument);
        }
        else if (main->program.context.mode == f_console_verbosity_verbose_e) {
          main->setting.state.status = f_string_dynamic_append(f_console_standard_short_verbose_s, &main->cache_argument);
        }
        else if (main->program.context.mode == f_console_verbosity_debug_e) {
          main->setting.state.status = f_string_dynamic_append(f_console_standard_short_debug_s, &main->cache_argument);
        }
      }

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append));

        return 0;
      }

      main->setting.state.status = fll_execute_arguments_add(main->cache_argument, &main->cache_arguments);
    }

    if (F_status_is_error(main->setting.state.status)) {
      fake_print_error(&main->program.error, macro_fake_f(fll_execute_arguments_add));

      return 0;
    }

    {
      f_string_dynamic_t defines = f_string_dynamic_t_initialize;

      if (main->setting.defines.used) {
        for (f_array_length_t i = 0; i < main->setting.defines.used; ++i) {

          main->setting.state.status = f_string_dynamic_mash(f_string_space_s, main->setting.defines.array[i], &defines);
          if (F_status_is_error(main->setting.state.status)) break;
        } // for

        if (F_status_is_error(main->setting.state.status)) {
          fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_mash));

          f_string_dynamic_resize(0, &defines);

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
        main->setting.build,
        main->setting.data,
        defines,
        main->setting.documents,
        main->setting.licenses,
        main->setting.process,
        main->setting.settings,
        data_build->setting.path_sources,
        main->setting.work,
      };

      main->setting.state.status = fll_execute_arguments_add_parameter_set(prefixs, names, values, 9, &main->cache_arguments);

      f_string_dynamic_resize(0, &defines);

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error(&main->program.error, macro_fake_f(fll_execute_arguments_add_parameter_set));

        return 0;
      }
    }

    fake_string_dynamic_reset(&main->cache_argument);

    if (process_script.string[0] != f_path_separator_s.string[0]) {
      main->setting.state.status = f_string_dynamic_append_nulless(data->path_data_build, &main->cache_argument);
    }

    if (F_status_is_error_not(main->setting.state.status)) {
      main->setting.state.status = f_string_dynamic_append_nulless(process_script, &main->cache_argument);
    }

    if (F_status_is_error(main->setting.state.status)) {
      fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

      return 0;
    }

    int return_code = 0;

    // Child processes should receive all signals, without blocking.
    f_signal_how_t signals = f_signal_how_t_initialize;
    f_signal_set_empty(&signals.block);
    f_signal_set_fill(&signals.block_not);

    fl_execute_parameter_t parameter = macro_fl_execute_parameter_t_initialize(FL_execute_parameter_option_path_d, 0, &data_build->environment, &signals, 0);

    main->setting.state.status = fll_execute_program(main->cache_argument, main->cache_arguments, &parameter, 0, (void *) &return_code);

    if (fake_signal_check(main)) return return_code;

    if (main->setting.state.status != F_child) {
      if (F_status_is_error(main->setting.state.status)) {
        if (F_status_set_fine(main->setting.state.status) == F_failure) {
          fake_print_error_failure_script(&main->program.error, main->cache_argument);
        }
        else {
          fake_print_error(&main->program.error, macro_fake_f(fll_execute_program));
        }
      }
      else {
        fake_build_touch(data, file_stage);
      }
    }

    return return_code;
  }
#endif // _di_fake_build_execute_process_script_

#ifndef _di_fake_build_get_file_name_without_extension_
  void fake_build_get_file_name_without_extension(fake_data_t * const data, const f_string_static_t path, f_string_dynamic_t *name) {

    if (!data || !data->main) return;
    if (F_status_is_error(data->main->setting.state.status)) return;

    fake_main_t * const main = data->main;

    name->used = 0;
    main->setting.state.status = F_none;

    if (!path.used) return;

    main->setting.state.status = f_file_name_base(path, name);

    if (F_status_is_error(main->setting.state.status)) {
      fake_print_error(&main->program.error, macro_fake_f(f_file_name_base));

      return;
    }

    for (f_array_length_t i = name->used; i > 0; --i) {

      if (name->string[i] == f_path_extension_separator_s.string[0]) {
        name->used = i;

        break;
      }
    } // for

    main->setting.state.status = F_none;
  }
#endif // _di_fake_build_get_file_name_without_extension_

#ifndef _di_fake_build_objects_add_
  void fake_build_objects_add(fake_data_t * const data, fake_build_data_t * const data_build, const f_string_static_t *path, const f_string_statics_t *generic, const f_string_statics_t *specific) {

    if (!data || !data->main || !data_build || !path || !generic || !specific) return;

    fake_main_t * const main = data->main;

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

        main->setting.state.status = fll_execute_arguments_add(source, &main->cache_arguments);
        if (F_status_is_error(main->setting.state.status)) return;
      } // for
    } // for

    main->setting.state.status = F_none;
  }
#endif // _di_fake_build_objects_add_

#ifndef _di_fake_build_operate_
  void fake_build_operate(fake_data_t * const data, const f_string_statics_t * const build_arguments, const bool process_pipe) {

    if (!data || !data->main) return;
    if (fake_signal_check(data->main)) return;

    fake_main_t * const main = data->main;

    main->setting.state.status = F_none;

    f_mode_t mode = f_mode_t_initialize;

    fake_build_data_t data_build = fake_build_data_t_initialize;
    fake_build_stage_t stage = fake_build_stage_t_initialize;

    macro_f_mode_t_set_default_umask(mode, main->program.umask);

    fake_build_load_setting(data, build_arguments, process_pipe, &data_build.setting);

    if (F_status_is_fine(main->setting.state.status)) {
      fake_print_message_building(&main->program.message, build_arguments, &data_build.setting);
    }

    fake_build_load_stage(data, build_arguments && build_arguments->array[0].used ? build_arguments->array[0] : f_string_empty_s, &stage);

    fake_build_load_environment(data, &data_build, &data_build.environment);

    fake_build_skeleton(data, &data_build, mode.directory, stage.file_skeleton);

    main->program.child = fake_build_execute_process_script(data, &data_build, data_build.setting.process_pre, stage.file_process_pre);

    fake_build_copy(data, mode, fake_build_documentation_files_s, data->path_data_documentation, data->path_build_documentation, data_build.setting.build_sources_documentation, stage.file_sources_documentation, 0);

    fake_build_copy(data, mode, fake_build_setting_files_s, data->path_data_settings, data->path_build_settings, data_build.setting.build_sources_setting, stage.file_sources_settings, 0);

    if (data_build.setting.build_language == fake_build_language_bash_e) {
      fake_build_object_script(data, &data_build, mode, stage.file_object_script);

      fake_build_library_script(data, &data_build, mode, stage.file_library_script);

      fake_build_program_script(data, &data_build, mode, stage.file_program_script);

      if (data_build.setting.build_script) {
        fake_build_path_source_string(data, &data_build, &data_build.setting.path_sources, &main->cache_argument);

        if (F_status_is_error_not(main->setting.state.status)) {
          main->setting.state.status = f_string_dynamic_append_nulless(fake_path_part_script_s, &main->cache_argument);

          if (F_status_is_error(main->setting.state.status)) {
            fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append_nulless));
          }
        }

        fake_build_copy(data, mode, fake_build_scripts_s, main->cache_argument, data->path_build_programs_script, data_build.setting.build_sources_script, stage.file_sources_script, 0);
      }
    }
    else {
      if (data_build.setting.build_sources_headers.used) {
        fake_build_path_source_string(data, &data_build, &data_build.setting.path_sources, &main->cache_argument);

        if (F_status_is_error_not(main->setting.state.status)) {
          fake_string_dynamic_reset(&main->cache_1);

          main->setting.state.status = f_string_dynamic_append_nulless(data->path_build_includes, &main->cache_1);

          if (F_status_is_error_not(main->setting.state.status)) {
            main->setting.state.status = f_string_dynamic_append_nulless(data_build.setting.path_headers, &main->cache_1);

            if (F_status_is_error(main->setting.state.status)) {
              fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append_nulless));
            }
          }
        }

        fake_build_copy(data, mode, fake_build_header_files_s, main->cache_argument, main->cache_1, data_build.setting.build_sources_headers, stage.file_sources_headers, data_build.setting.preserve_path_headers ? main->cache_argument.used : 0);

        if (data_build.setting.build_shared) {
          fake_build_copy(data, mode, fake_build_header_files_shared_s, main->cache_argument, main->cache_1, data_build.setting.build_sources_headers_shared, stage.file_sources_headers, data_build.setting.preserve_path_headers ? main->cache_argument.used : 0);
        }

        if (data_build.setting.build_static) {
          fake_build_copy(data, mode, fake_build_header_files_static_s, main->cache_argument, main->cache_1, data_build.setting.build_sources_headers_static, stage.file_sources_headers, data_build.setting.preserve_path_headers ? main->cache_argument.used : 0);
        }
      }

      if (data_build.setting.build_shared) {
        main->program.child = fake_build_object_shared(data, &data_build, mode, stage.file_object_shared);

        main->program.child = fake_build_library_shared(data, &data_build, mode, stage.file_library_shared);

        main->program.child = fake_build_program_shared(data, &data_build, mode, stage.file_program_shared);
      }

      if (data_build.setting.build_static) {
        main->program.child = fake_build_object_static(data, &data_build, mode, stage.file_object_static);

        main->program.child = fake_build_objects_static(data, &data_build, mode, stage.file_objects_static);

        main->program.child = fake_build_library_static(data, &data_build, mode, stage.file_library_static);

        main->program.child = fake_build_program_static(data, &data_build, mode, stage.file_program_static);
      }

      if (data_build.setting.build_script) {
        fake_build_path_source_string(data, &data_build, &data_build.setting.path_sources, &main->cache_argument);

        if (F_status_is_error_not(main->setting.state.status)) {
          main->setting.state.status = f_string_dynamic_append_nulless(fake_path_part_script_s, &main->cache_argument);

          if (F_status_is_error(main->setting.state.status)) {
            fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append_nulless));
          }
          else {
            fake_build_copy(data, mode, fake_build_scripts_s, main->cache_argument, data->path_build_programs_script, data_build.setting.build_sources_script, stage.file_sources_script, 0);
          }
        }
      }
    }

    fake_build_execute_process_script(data, &data_build, data_build.setting.process_post, stage.file_process_post);

    fake_build_data_delete(&data_build);
    fake_build_stage_delete(&stage);
  }
#endif // _di_fake_build_operate_

#ifndef _di_fake_build_path_source_string_
  void fake_build_path_source_string(fake_data_t * const data, fake_build_data_t * const data_build, f_string_static_t * const setting_path_source, f_string_dynamic_t * const source) {

    if (!data || !data->main || !data_build || !setting_path_source || !source) return;
    if (F_status_is_error(data->main->setting.state.status)) return;

    fake_main_t * const main = data->main;

    fake_string_dynamic_reset(source);

    main->setting.state.status = f_string_dynamic_append_nulless(*setting_path_source, source);

    if (F_status_is_error_not(main->setting.state.status) && data_build->setting.has_path_standard) {
      if (data_build->setting.build_language == fake_build_language_c_e) {
        main->setting.state.status = f_string_dynamic_append_nulless(fake_build_language_c_s, source);
      }
      else if (data_build->setting.build_language == fake_build_language_cpp_e) {
        main->setting.state.status = f_string_dynamic_append_nulless(fake_build_language_cpp_s, source);
      }
      else if (data_build->setting.build_language == fake_build_language_bash_e) {
        main->setting.state.status = f_string_dynamic_append_nulless(fake_build_language_bash_s, source);
      }
    }

    if (F_status_is_error_not(main->setting.state.status)) {
      main->setting.state.status = f_string_dynamic_append_assure(f_path_separator_s, source);
    }

    if (F_status_is_error(main->setting.state.status)) {
      fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append_nulless));
    }
  }
#endif // _di_fake_build_path_source_string_

#ifndef _di_fake_build_sources_add_
  void fake_build_sources_add(fake_data_t * const data, fake_build_data_t * const data_build, const f_string_statics_t *generic, const f_string_statics_t *specific) {

    if (!data || !data->main || !data_build || !generic || !specific) return;

    fake_main_t * const main = data->main;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    const f_string_statics_t *sources[2] = {
      generic,
      specific,
    };

    for (; i < 2; ++i) {

      for (j = 0; j < sources[i]->used; ++j) {

        if (!sources[i]->array[j].used) continue;

        fake_build_path_source_string(data, data_build, &data_build->setting.path_sources, &main->cache_argument);
        if (F_status_is_error(main->setting.state.status)) return;

        main->setting.state.status = f_string_dynamic_append_nulless(sources[i]->array[j], &main->cache_argument);

        if (F_status_is_error(main->setting.state.status)) {
          fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

          return;
        }

        main->setting.state.status = fll_execute_arguments_add(main->cache_argument, &main->cache_arguments);
        if (F_status_is_error(main->setting.state.status)) return;
      } // for
    } // for

    main->setting.state.status = F_none;
  }
#endif // _di_fake_build_sources_add_

#ifndef _di_fake_build_sources_object_add_
  void fake_build_sources_object_add(fake_data_t * const data, fake_build_data_t * const data_build, const f_string_static_t *generic, const f_string_static_t *specific) {

    if (!data || !data->main || !data_build || !generic || !specific) return;

    if (!generic->used && !specific->used) {
      data->main->setting.state.status = F_none;

      return;
    }

    fake_main_t * const main = data->main;

    fake_build_path_source_string(data, data_build, &data_build->setting.path_sources_object, &main->cache_argument);
    if (F_status_is_error(main->setting.state.status)) return;

    main->setting.state.status = f_string_dynamic_append_nulless(specific->used ? *specific : *generic, &main->cache_argument);

    if (F_status_is_error(main->setting.state.status)) {
      fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

      return;
    }

    main->setting.state.status = fll_execute_arguments_add(main->cache_argument, &main->cache_arguments);
    if (F_status_is_error(main->setting.state.status)) return;

    main->setting.state.status = F_none;
  }
#endif // _di_fake_build_sources_object_add_

#ifndef _di_fake_build_touch_
  void fake_build_touch(fake_data_t * const data, const f_string_dynamic_t file) {

    if (!data || !data->main) return;
    if (F_status_is_error(data->main->setting.state.status)) return;
    if (fake_signal_check(data->main)) return;

    fake_main_t * const main = data->main;

    f_mode_t mode = f_mode_t_initialize;

    macro_f_mode_t_set_default_umask(mode, main->program.umask);

    main->setting.state.status = f_file_touch(file, mode.regular, F_false);

    if (F_status_is_error(main->setting.state.status)) {
      fake_print_error_file(&main->program.error, macro_fake_f(f_file_touch), file, f_file_operation_touch_s, fll_error_file_type_file_e);
    }
    else {
      main->setting.state.status = F_none;
    }
  }
#endif // _di_fake_build_touch_

#ifdef __cplusplus
} // extern "C"
#endif
