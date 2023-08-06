#include "../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_load_environment_
  void fake_build_load_environment(fake_data_t * const data, fake_build_data_t * const data_build, f_string_maps_t * const environment) {

    if (!data || !data->main || !data_build || !environment) return;
    if (F_status_is_error(data->main->setting.state.status)) return;

    fake_main_t * const main = data->main;

    // Reset the environment.
    for (f_number_unsigned_t i = 0; i < environment->used; ++i) {

      environment->array[i].name.used = 0;
      environment->array[i].value.used = 0;
    } // for

    environment->used = 0;

    {
      // Add the guaranteed environment variables.
      const f_string_static_t variables[] = {
        f_path_environment_s,
        f_path_present_working_s
      };

      for (uint8_t i = 0; i < 2; ++i) {

        main->setting.state.status = fl_environment_load_name(variables[i], environment);

        if (F_status_is_error(main->setting.state.status)) {
          fake_print_error(&main->program.error, macro_fake_f(fl_environment_load_name));

          return;
        }
      } // for
    }

    if (environment->used + data_build->setting.environment.used > environment->size) {
      if (environment->used + data_build->setting.environment.used > f_environment_max_length_d) {
        fake_build_print_error_setting_value_too_long(&main->program.error, fake_build_setting_name_environment_s, data->file_data_build_settings);

        main->setting.state.status = F_status_set_error(F_array_too_large);

        return;
      }
    }

    main->setting.state.status = fl_environment_load_names(data_build->setting.environment, environment);

    if (F_status_is_error(main->setting.state.status)) {
      fake_print_error(&main->program.error, macro_fake_f(fl_environment_load_names));
    }
    else {
      main->setting.state.status = F_none;
    }
  }
#endif // _di_fake_build_load_environment_

#ifndef _di_fake_build_load_setting_
  void fake_build_load_setting(fake_data_t * const data, const f_string_statics_t * const build_arguments, const bool process_pipe, fake_build_setting_t * const setting) {

    if (!data || !data->main || !setting) return;
    if (F_status_is_error(data->main->setting.state.status)) return;
    if (fake_signal_check(data->main)) return;

    fake_main_t * const main = data->main;

    // Strip the build settings name from the build arguments to generate a list of modes.
    f_string_statics_t modes_custom = f_string_statics_t_initialize;

    if (build_arguments) {
      if (build_arguments->used > 1) {
        modes_custom.used = build_arguments->used - 1;
      }
      else if (main->setting.modes.used) {
        modes_custom.used = main->setting.modes.used;
      }
    }

    f_string_static_t modes_custom_array[modes_custom.used];
    modes_custom.array = modes_custom_array;

    if (build_arguments) {
      f_number_unsigned_t i = 0;

      if (build_arguments->used > 1) {
        for (; i < modes_custom.used; ++i) {
          modes_custom.array[i] = build_arguments->array[i + 1];
        } // for
      }
      else if (main->setting.modes.used) {
        for (; i < main->setting.modes.used; ++i) {
          modes_custom.array[i] = main->setting.modes.array[i];
        } // for
      }
    }

    f_string_static_t path_file = f_string_static_t_initialize;

    if (build_arguments && build_arguments->used) {
      path_file.used = data->path_data_build.used + build_arguments->array[0].used;
    }
    else if (!process_pipe || (main->setting.flag & fake_main_flag_operation_e)) {
      path_file.used = data->file_data_build_settings.used;
    }
    else {
      path_file.used = f_string_ascii_minus_s.used;
    }

    f_char_t path_file_string[path_file.used + 1];
    path_file.string = path_file_string;
    path_file_string[path_file.used] = 0;

    if (build_arguments && build_arguments->used) {
      memcpy(path_file_string, data->path_data_build.string, sizeof(f_char_t) * data->path_data_build.used);
      memcpy(path_file_string + data->path_data_build.used, build_arguments->array[0].string, sizeof(f_char_t) * build_arguments->array[0].used);
    }
    else if (!process_pipe || (main->setting.flag & fake_main_flag_operation_e)) {
      memcpy(path_file_string, data->file_data_build_settings.string, sizeof(f_char_t) * data->file_data_build_settings.used);
    }
    else {
      memcpy(path_file_string, f_string_ascii_minus_s.string, sizeof(f_char_t) * f_string_ascii_minus_s.used);
    }

    {
      f_string_dynamic_t buffer = f_string_dynamic_t_initialize;
      f_string_ranges_t objects = f_string_ranges_t_initialize;
      f_string_rangess_t contents = f_string_rangess_t_initialize;

      if (process_pipe) {
        fake_pipe_buffer(data, &buffer);

        if (F_status_is_error(main->setting.state.status)) {
          buffer.used = 0;
        }
        else {
          main->setting.state.status = f_string_dynamic_append_assure(f_string_eol_s, &buffer);
        }
      }

      if (F_status_is_error_not(main->setting.state.status)) {
        if (build_arguments && build_arguments->used || !process_pipe || (main->setting.flag & fake_main_flag_operation_e)) {
          fake_file_buffer(data, path_file, process_pipe ? F_false : F_true, &buffer);
        }
      }

      if (F_status_is_error_not(main->setting.state.status)) {
        f_string_range_t range = macro_f_string_range_t_initialize_2(buffer.used);
        f_number_unsigneds_t delimits = f_number_unsigneds_t_initialize;

        fll_fss_extended_read(buffer, &range, &objects, &contents, 0, 0, &delimits, 0, &main->setting.state);

        if (F_status_is_error(main->setting.state.status)) {
          fake_print_error_fss(&main->program.error, macro_fake_f(fll_fss_extended_read), data->file_data_build_settings, range, F_true);
        }
        else {
          f_fss_apply_delimit(delimits, &buffer, &main->setting.state);

          if (F_status_is_error(main->setting.state.status)) {
            fake_print_error(&main->program.error, macro_fake_f(f_fss_apply_delimit));
          }
          else {
            fake_build_load_setting_process(data, F_true, path_file, modes_custom.used ? &modes_custom : 0, buffer, objects, contents, setting);
          }
        }

        f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &delimits.array, &delimits.used, &delimits.size);
      }

      f_string_dynamic_resize(0, &buffer);

      macro_f_string_ranges_t_delete_simple(objects);
      macro_f_string_rangess_t_delete_simple(contents);
    }

    // Error when required settings are not specified.
    if (F_status_is_error_not(main->setting.state.status)) {
      bool failed = F_false;

      f_string_static_t * const settings[] = {
        &setting->build_name,
      };

      f_string_static_t names[] = {
        fake_build_setting_name_build_name_s,
      };

      for (uint8_t i = 0; i < 1; ++i) {

        if (!settings[i]->used) {
          fake_build_print_error_missing_required_setting(&main->program.warning, names[i], path_file);

          failed = F_true;
        }
      } // for

      if (failed) {
        main->setting.state.status = F_status_set_error(F_failure);

        return;
      }

      main->setting.state.status = F_none;
    }

    fake_build_load_setting_override(data, setting);
  }
#endif // _di_fake_build_load_setting_

#ifndef _di_fake_build_load_setting_process_
  void fake_build_load_setting_process(fake_data_t * const data, const bool checks, const f_string_static_t path_file, const f_string_statics_t * const modes_custom, const f_string_static_t buffer, const f_string_ranges_t objects, const f_string_rangess_t contents, fake_build_setting_t * const setting) {

    if (!data || !data->main || !setting) return;
    if (F_status_is_error(data->main->setting.state.status) && buffer.used) return;
    if (fake_signal_check(data->main)) return;

    fake_main_t * const main = data->main;

    bool error_printed = F_false;

    f_string_dynamics_t build_compiler = f_string_dynamics_t_initialize;
    f_string_dynamics_t build_indexer = f_string_dynamics_t_initialize;
    f_string_dynamics_t build_language = f_string_dynamics_t_initialize;
    f_string_dynamics_t build_name = f_string_dynamics_t_initialize;
    f_string_dynamics_t build_script = f_string_dynamics_t_initialize;
    f_string_dynamics_t build_shared = f_string_dynamics_t_initialize;
    f_string_dynamics_t build_sources_object = f_string_dynamics_t_initialize;
    f_string_dynamics_t build_sources_object_shared = f_string_dynamics_t_initialize;
    f_string_dynamics_t build_sources_object_static = f_string_dynamics_t_initialize;
    f_string_dynamics_t build_static = f_string_dynamics_t_initialize;
    f_string_dynamics_t has_path_standard = f_string_dynamics_t_initialize;
    f_string_dynamics_t path_headers = f_string_dynamics_t_initialize;
    f_string_dynamics_t path_language = f_string_dynamics_t_initialize;
    f_string_dynamics_t path_library_script = f_string_dynamics_t_initialize;
    f_string_dynamics_t path_library_shared = f_string_dynamics_t_initialize;
    f_string_dynamics_t path_library_static = f_string_dynamics_t_initialize;
    f_string_dynamics_t path_object_script = f_string_dynamics_t_initialize;
    f_string_dynamics_t path_object_shared = f_string_dynamics_t_initialize;
    f_string_dynamics_t path_object_static = f_string_dynamics_t_initialize;
    f_string_dynamics_t path_program_script = f_string_dynamics_t_initialize;
    f_string_dynamics_t path_program_shared = f_string_dynamics_t_initialize;
    f_string_dynamics_t path_program_static = f_string_dynamics_t_initialize;
    f_string_dynamics_t path_sources = f_string_dynamics_t_initialize;
    f_string_dynamics_t path_sources_object = f_string_dynamics_t_initialize;
    f_string_dynamics_t preserve_path_headers = f_string_dynamics_t_initialize;
    f_string_dynamics_t process_post = f_string_dynamics_t_initialize;
    f_string_dynamics_t process_pre = f_string_dynamics_t_initialize;
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

    const f_string_static_t settings_name[] = {
      fake_build_setting_name_build_compiler_s,
      fake_build_setting_name_build_indexer_s,
      fake_build_setting_name_build_indexer_arguments_s,
      fake_build_setting_name_build_language_s,
      fake_build_setting_name_build_libraries_s,
      fake_build_setting_name_build_libraries_shared_s,
      fake_build_setting_name_build_libraries_static_s,
      fake_build_setting_name_build_name_s,
      fake_build_setting_name_build_objects_library_s,
      fake_build_setting_name_build_objects_library_shared_s,
      fake_build_setting_name_build_objects_library_static_s,
      fake_build_setting_name_build_objects_program_s,
      fake_build_setting_name_build_objects_program_shared_s,
      fake_build_setting_name_build_objects_program_static_s,
      fake_build_setting_name_build_script_s,
      fake_build_setting_name_build_shared_s,
      fake_build_setting_name_build_sources_documentation_s,
      fake_build_setting_name_build_sources_headers_s,
      fake_build_setting_name_build_sources_headers_shared_s,
      fake_build_setting_name_build_sources_headers_static_s,
      fake_build_setting_name_build_sources_library_s,
      fake_build_setting_name_build_sources_library_shared_s,
      fake_build_setting_name_build_sources_library_static_s,
      fake_build_setting_name_build_sources_object_s,
      fake_build_setting_name_build_sources_object_shared_s,
      fake_build_setting_name_build_sources_object_static_s,
      fake_build_setting_name_build_sources_program_s,
      fake_build_setting_name_build_sources_program_shared_s,
      fake_build_setting_name_build_sources_program_static_s,
      fake_build_setting_name_build_sources_script_s,
      fake_build_setting_name_build_sources_setting_s,
      fake_build_setting_name_build_static_s,
      fake_build_setting_name_defines_s,
      fake_build_setting_name_defines_library_s,
      fake_build_setting_name_defines_library_shared_s,
      fake_build_setting_name_defines_library_static_s,
      fake_build_setting_name_defines_object_s,
      fake_build_setting_name_defines_object_shared_s,
      fake_build_setting_name_defines_object_static_s,
      fake_build_setting_name_defines_program_s,
      fake_build_setting_name_defines_program_shared_s,
      fake_build_setting_name_defines_program_static_s,
      fake_build_setting_name_defines_shared_s,
      fake_build_setting_name_defines_static_s,
      fake_build_setting_name_environment_s,
      fake_build_setting_name_flags_s,
      fake_build_setting_name_flags_library_s,
      fake_build_setting_name_flags_library_shared_s,
      fake_build_setting_name_flags_library_static_s,
      fake_build_setting_name_flags_object_s,
      fake_build_setting_name_flags_object_shared_s,
      fake_build_setting_name_flags_object_static_s,
      fake_build_setting_name_flags_program_s,
      fake_build_setting_name_flags_program_shared_s,
      fake_build_setting_name_flags_program_static_s,
      fake_build_setting_name_flags_shared_s,
      fake_build_setting_name_flags_static_s,
      fake_build_setting_name_has_path_standard_s,
      fake_build_setting_name_modes_s,
      fake_build_setting_name_modes_default_s,
      fake_build_setting_name_path_headers_s,
      fake_build_setting_name_path_language_s,
      fake_build_setting_name_path_library_script_s,
      fake_build_setting_name_path_library_shared_s,
      fake_build_setting_name_path_library_static_s,
      fake_build_setting_name_path_object_script_s,
      fake_build_setting_name_path_object_shared_s,
      fake_build_setting_name_path_object_static_s,
      fake_build_setting_name_path_program_script_s,
      fake_build_setting_name_path_program_shared_s,
      fake_build_setting_name_path_program_static_s,
      fake_build_setting_name_path_sources_s,
      fake_build_setting_name_path_sources_object_s,
      fake_build_setting_name_preserve_path_headers_s,
      fake_build_setting_name_process_post_s,
      fake_build_setting_name_process_pre_s,
      fake_build_setting_name_search_exclusive_s,
      fake_build_setting_name_search_shared_s,
      fake_build_setting_name_search_static_s,
      fake_build_setting_name_version_file_s,
      fake_build_setting_name_version_major_s,
      fake_build_setting_name_version_major_prefix_s,
      fake_build_setting_name_version_micro_s,
      fake_build_setting_name_version_micro_prefix_s,
      fake_build_setting_name_version_minor_s,
      fake_build_setting_name_version_minor_prefix_s,
      fake_build_setting_name_version_nano_s,
      fake_build_setting_name_version_nano_prefix_s,
      fake_build_setting_name_version_target_s,
    };

    f_string_dynamics_t *settings_value[] = {
      &build_compiler,
      &build_indexer,
      &setting->build_indexer_arguments,
      &build_language,
      &setting->build_libraries,
      &setting->build_libraries_shared,
      &setting->build_libraries_static,
      &build_name,
      &setting->build_objects_library,
      &setting->build_objects_library_shared,
      &setting->build_objects_library_static,
      &setting->build_objects_program,
      &setting->build_objects_program_shared,
      &setting->build_objects_program_static,
      &build_script,
      &build_shared,
      &setting->build_sources_documentation,
      &setting->build_sources_headers,
      &setting->build_sources_headers_shared,
      &setting->build_sources_headers_static,
      &setting->build_sources_library,
      &setting->build_sources_library_shared,
      &setting->build_sources_library_static,
      &build_sources_object,
      &build_sources_object_shared,
      &build_sources_object_static,
      &setting->build_sources_program,
      &setting->build_sources_program_shared,
      &setting->build_sources_program_static,
      &setting->build_sources_script,
      &setting->build_sources_setting,
      &build_static,
      &setting->defines,
      &setting->defines_library,
      &setting->defines_library_shared,
      &setting->defines_library_static,
      &setting->defines_object,
      &setting->defines_object_shared,
      &setting->defines_object_static,
      &setting->defines_program,
      &setting->defines_program_shared,
      &setting->defines_program_static,
      &setting->defines_shared,
      &setting->defines_static,
      &setting->environment,
      &setting->flags,
      &setting->flags_library,
      &setting->flags_library_shared,
      &setting->flags_library_static,
      &setting->flags_object,
      &setting->flags_object_shared,
      &setting->flags_object_static,
      &setting->flags_program,
      &setting->flags_program_shared,
      &setting->flags_program_static,
      &setting->flags_shared,
      &setting->flags_static,
      &has_path_standard,
      &setting->modes,
      &setting->modes_default,
      &path_headers,
      &path_language,
      &path_library_script,
      &path_library_shared,
      &path_library_static,
      &path_object_script,
      &path_object_shared,
      &path_object_static,
      &path_program_script,
      &path_program_shared,
      &path_program_static,
      &path_sources,
      &path_sources_object,
      &preserve_path_headers,
      &process_post,
      &process_pre,
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
      F_false, // build_compiler
      F_false, // build_indexer
      F_false, // setting->build_indexer_arguments
      F_false, // build_language
      F_false, // setting->build_libraries
      F_false, // setting->build_libraries_shared
      F_false, // setting->build_libraries_static
      F_false, // build_name
      F_false, // setting->build_objects_library
      F_false, // setting->build_objects_library_shar
      F_false, // setting->build_objects_library_stat
      F_false, // setting->build_objects_program
      F_false, // setting->build_objects_program_shar
      F_false, // setting->build_objects_program_stat
      F_false, // build_script
      F_false, // build_shared
      F_false, // setting->build_sources_documentation
      F_false, // setting->build_sources_headers
      F_false, // setting->build_sources_headers_shar
      F_false, // setting->build_sources_headers_stat
      F_false, // setting->build_sources_library
      F_false, // setting->build_sources_library_shar
      F_false, // setting->build_sources_library_stat
      F_false, // build_sources_object
      F_false, // build_sources_object_shared
      F_false, // build_sources_object_static
      F_false, // setting->build_sources_program
      F_false, // setting->build_sources_program_shar
      F_false, // setting->build_sources_program_stat
      F_false, // setting->build_sources_script
      F_false, // setting->build_sources_setting
      F_false, // build_static
      F_false, // setting->defines
      F_false, // setting->defines_library
      F_false, // setting->defines_library_shared
      F_false, // setting->defines_library_static
      F_false, // setting->defines_object
      F_false, // setting->defines_object_shared
      F_false, // setting->defines_object_static
      F_false, // setting->defines_program
      F_false, // setting->defines_program_shared
      F_false, // setting->defines_program_static
      F_false, // setting->defines_shared
      F_false, // setting->defines_static
      F_false, // setting->environment
      F_false, // setting->flags
      F_false, // setting->flags_library
      F_false, // setting->flags_library_shared
      F_false, // setting->flags_library_static
      F_false, // setting->flags_object
      F_false, // setting->flags_object_shared
      F_false, // setting->flags_object_static
      F_false, // setting->flags_program
      F_false, // setting->flags_program_shared
      F_false, // setting->flags_program_static
      F_false, // setting->flags_shared
      F_false, // setting->flags_static
      F_false, // has_path_standard
      F_false, // setting->modes
      F_false, // setting->modes_default
      F_false, // path_headers
      F_false, // path_language
      F_false, // path_library_script
      F_false, // path_library_shared
      F_false, // path_library_static
      F_false, // path_object_script
      F_false, // path_object_shared
      F_false, // path_object_static
      F_false, // path_program_script
      F_false, // path_program_shared
      F_false, // path_program_static
      F_false, // path_sources
      F_false, // path_sources_object
      F_false, // preserve_path_headers
      F_false, // process_post
      F_false, // process_pre
      F_false, // search_exclusive
      F_false, // search_shared
      F_false, // search_static
      F_false, // version_file
      F_false, // version_major
      F_false, // version_major_prefix
      F_false, // version_micro
      F_false, // version_micro_prefix
      F_false, // version_minor
      F_false, // version_minor_prefix
      F_false, // version_nano
      F_false, // version_nano_prefix
      F_false, // version_target
    };

    f_string_t function = macro_fake_f(fll_fss_snatch_apart);

    main->setting.state.status = fll_fss_snatch_apart(buffer, objects, contents, settings_name, fake_build_setting_total_d, settings_value, settings_matches, 0);

    if (main->setting.state.status == F_none) {
      const int total_build_libraries = setting->build_libraries.used;

      // Custom modes are always used if provided, otherwise if any mode is specified, the entire defaults is replaced.
      const f_string_statics_t * const modes = modes_custom && modes_custom->used
        ? modes_custom
        : main->setting.modes.used
          ? &main->setting.modes
          : &setting->modes_default;

      f_string_dynamic_t settings_mode_names[fake_build_setting_total_d];

      memset(settings_mode_names, 0, sizeof(f_string_statics_t) * fake_build_setting_total_d);

      bool found = F_false;

      f_number_unsigned_t i = 0;
      f_number_unsigned_t j = 0;

      for (; i < modes->used; ++i) {

        // Skip empty modes.
        if (!modes->array[i].used) continue;

        for (j = 0; j < setting->modes.used; ++j) {

          if (f_compare_dynamic_trim(modes->array[i], setting->modes.array[j]) == F_equal_to) {
            found = F_true;

            break;
          }
        } // for

        if (found == F_false) {
          fake_build_print_error_mode_invalid(&main->program.warning, modes->array[i], path_file);

          error_printed = F_true;
          main->setting.state.status = F_status_set_error(F_parameter);

          break;
        }

        for (j = 0; j < fake_build_setting_total_d; ++j) {

          settings_mode_names[j].used = 0;

          main->setting.state.status = f_string_dynamic_increase_by(settings_value[j]->used + f_string_ascii_minus_s.used + modes->array[i].used, &settings_mode_names[j]);

          if (F_status_is_error(main->setting.state.status)) {
            function = macro_fake_f(f_string_dynamic_increase_by);

            break;
          }

          main->setting.state.status = f_string_dynamic_append_nulless(settings_name[j], &settings_mode_names[j]);

          if (F_status_is_error_not(main->setting.state.status)) {
            main->setting.state.status = f_string_dynamic_append_nulless(f_string_ascii_minus_s, &settings_mode_names[j]);
          }

          if (F_status_is_error_not(main->setting.state.status)) {
            main->setting.state.status = f_string_dynamic_append_nulless(modes->array[i], &settings_mode_names[j]);
          }

          if (F_status_is_error(main->setting.state.status)) {
            function = macro_fake_f(f_string_dynamic_append);

            break;
          }
        } // for

        if (main->setting.state.status == F_none) {
          main->setting.state.status = fll_fss_snatch_apart(buffer, objects, contents, settings_mode_names, fake_build_setting_total_d, settings_value, 0, 0);

          if (F_status_is_error(main->setting.state.status)) {
            function = macro_fake_f(fll_fss_snatch_apart);
          }
        }

        if (F_status_is_error(main->setting.state.status)) break;
      } // for

      for (j = 0; j < fake_build_setting_total_d; ++j) {
        f_string_dynamic_resize(0, &settings_mode_names[j]);
      } // for

      // The string "build_libraries" is appended after all modes to help assist with static linker file issues.
      if (total_build_libraries) {
        f_string_static_t temporary[total_build_libraries];

        // Move the original "build_libraries" into a temporary location.
        for (i = 0; i < total_build_libraries; ++i) {

          temporary[i].string = setting->build_libraries.array[i].string;
          temporary[i].used = setting->build_libraries.array[i].used;
          temporary[i].size = setting->build_libraries.array[i].size;
        } // for

        // Move all of the other build library settings to the front of the array.
        for (i = 0, j = total_build_libraries; j < setting->build_libraries.used; ++i, ++j) {

          setting->build_libraries.array[i].string = setting->build_libraries.array[j].string;
          setting->build_libraries.array[i].used = setting->build_libraries.array[j].used;
          setting->build_libraries.array[i].size = setting->build_libraries.array[j].size;
        } // for

        // Move back the original "build_libraries" back, but at the end of the array.
        for (i = setting->build_libraries.used - total_build_libraries, j = 0; j < total_build_libraries; ++i, ++j) {

          setting->build_libraries.array[i].string = temporary[j].string;
          setting->build_libraries.array[i].used = temporary[j].used;
          setting->build_libraries.array[i].size = temporary[j].size;
        } // for
      }
    }

    if (F_status_is_error(main->setting.state.status)) {
      if (main->setting.state.status == F_status_set_error(F_string_too_large)) {
        fake_build_print_error_setting_too_long(&main->program.warning, path_file);
      }
      else if (!error_printed) {
        fake_print_error(&main->program.error, function);
      }
    }
    else {
      const f_string_static_t settings_single_name[] = {
        fake_build_setting_name_build_compiler_s,
        fake_build_setting_name_build_indexer_s,
        fake_build_setting_name_build_language_s,
        fake_build_setting_name_build_name_s,
        fake_build_setting_name_build_script_s,
        fake_build_setting_name_build_shared_s,
        fake_build_setting_name_build_sources_object_s,
        fake_build_setting_name_build_sources_object_shared_s,
        fake_build_setting_name_build_sources_object_static_s,
        fake_build_setting_name_build_static_s,
        fake_build_setting_name_has_path_standard_s,
        fake_build_setting_name_path_headers_s,
        fake_build_setting_name_path_language_s,
        fake_build_setting_name_path_library_script_s,
        fake_build_setting_name_path_library_shared_s,
        fake_build_setting_name_path_library_static_s,
        fake_build_setting_name_path_object_script_s,
        fake_build_setting_name_path_object_shared_s,
        fake_build_setting_name_path_object_static_s,
        fake_build_setting_name_path_program_script_s,
        fake_build_setting_name_path_program_shared_s,
        fake_build_setting_name_path_program_static_s,
        fake_build_setting_name_path_sources_s,
        fake_build_setting_name_path_sources_object_s,
        fake_build_setting_name_preserve_path_headers_s,
        fake_build_setting_name_process_post_s,
        fake_build_setting_name_process_pre_s,
        fake_build_setting_name_search_exclusive_s,
        fake_build_setting_name_search_shared_s,
        fake_build_setting_name_search_static_s,
        fake_build_setting_name_version_file_s,
        fake_build_setting_name_version_major_s,
        fake_build_setting_name_version_major_prefix_s,
        fake_build_setting_name_version_micro_s,
        fake_build_setting_name_version_micro_prefix_s,
        fake_build_setting_name_version_minor_s,
        fake_build_setting_name_version_minor_prefix_s,
        fake_build_setting_name_version_nano_s,
        fake_build_setting_name_version_nano_prefix_s,
        fake_build_setting_name_version_target_s,
      };

      const f_string_statics_t *settings_single_source[] = {
        &build_compiler,
        &build_indexer,
        &build_language,
        &build_name,
        &build_script,
        &build_shared,
        &build_sources_object,
        &build_sources_object_shared,
        &build_sources_object_static,
        &build_static,
        &has_path_standard,
        &path_headers,
        &path_language,
        &path_library_script,
        &path_library_shared,
        &path_library_static,
        &path_object_script,
        &path_object_shared,
        &path_object_static,
        &path_program_script,
        &path_program_shared,
        &path_program_static,
        &path_sources,
        &path_sources_object,
        &preserve_path_headers,
        &process_post,
        &process_pre,
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

      bool *settings_single_bool[] = {
        0,                                           // build_compiler
        0,                                           // build_indexer
        0,                                           // build_language
        0,                                           // build_name
        &setting->build_script,                      // build_script
        &setting->build_shared,                      // build_shared
        0,                                           // build_sources_object
        0,                                           // build_sources_object_shared
        0,                                           // build_sources_object_static
        &setting->build_static,                      // build_static
        &setting->has_path_standard,                 // has_path_standard
        0,                                           // path_headers
        0,                                           // path_language
        0,                                           // path_library_script
        0,                                           // path_library_shared
        0,                                           // path_library_static
        0,                                           // path_object_script
        0,                                           // path_object_shared
        0,                                           // path_object_static
        0,                                           // path_program_script
        0,                                           // path_program_shared
        0,                                           // path_program_static
        0,                                           // path_sources
        0,                                           // path_sources_object
        &setting->preserve_path_headers,             // preserve_path_headers
        0,                                           // process_post
        0,                                           // process_pre
        &setting->search_exclusive,                  // search_exclusive
        &setting->search_shared,                     // search_shared
        &setting->search_static,                     // search_static
      };

      f_string_dynamic_t *settings_single_destination[] = {
        &setting->build_compiler,                    // build_compiler
        &setting->build_indexer,                     // build_indexer
        0,                                           // build_language
        &setting->build_name,                        // build_name
        0,                                           // build_script
        0,                                           // build_shared
        &setting->build_sources_object,              // build_sources_object
        &setting->build_sources_object_shared,       // build_sources_object_shared
        &setting->build_sources_object_static,       // build_sources_object_static
        0,                                           // build_static
        0,                                           // has_path_standard
        &setting->path_headers,                      // path_headers
        &setting->path_language,                     // path_language
        &setting->path_library_script,               // path_library_script
        &setting->path_library_shared,               // path_library_shared
        &setting->path_library_static,               // path_library_static
        &setting->path_object_script,                // path_object_script
        &setting->path_object_shared,                // path_object_shared
        &setting->path_object_static,                // path_object_static
        &setting->path_program_script,               // path_program_script
        &setting->path_program_shared,               // path_program_shared
        &setting->path_program_static,               // path_program_static
        &setting->path_sources,                      // path_sources
        &setting->path_sources_object,               // path_sources_object
        0,                                           // preserve_path_headers
        &setting->process_post,                      // process_post
        &setting->process_pre,                       // process_pre
        0,                                           // search_exclusive
        0,                                           // search_shared
        0,                                           // search_static
        0,                                           // version_file
        &setting->version_major,                     // version_major
        &setting->version_major_prefix,              // version_major_prefix
        &setting->version_micro,                     // version_micro
        &setting->version_micro_prefix,              // version_micro_prefix
        &setting->version_minor,                     // version_minor
        &setting->version_minor_prefix,              // version_minor_prefix
        &setting->version_nano,                      // version_nano
        &setting->version_nano_prefix,               // version_nano_prefix
        0,                                           // version_target
      };

      const bool settings_single_matches[] = {
        settings_matches[0],  // build_compiler
        settings_matches[1],  // build_indexer
        settings_matches[3],  // build_language
        settings_matches[7],  // build_name
        settings_matches[14], // build_script
        settings_matches[15], // build_shared
        settings_matches[23], // build_sources_object
        settings_matches[24], // build_sources_object_shared
        settings_matches[25], // build_sources_object_static
        settings_matches[31], // build_static
        settings_matches[57], // has_path_standard
        settings_matches[60], // path_headers
        settings_matches[61], // path_language
        settings_matches[62], // path_library_script
        settings_matches[63], // path_library_shared
        settings_matches[64], // path_library_static
        settings_matches[65], // path_object_script
        settings_matches[66], // path_object_shared
        settings_matches[67], // path_object_static
        settings_matches[68], // path_program_script
        settings_matches[69], // path_program_shared
        settings_matches[70], // path_program_static
        settings_matches[71], // path_sources
        settings_matches[72], // path_sources_object
        settings_matches[73], // preserve_path_headers
        settings_matches[74], // process_post
        settings_matches[75], // process_pre
        settings_matches[76], // search_exclusive
        settings_matches[77], // search_shared
        settings_matches[78], // search_static
        settings_matches[79], // version_file
        settings_matches[80], // version_major
        settings_matches[81], // version_major_prefix
        settings_matches[82], // version_micro
        settings_matches[83], // version_micro_prefix
        settings_matches[84], // version_minor
        settings_matches[85], // version_minor_prefix
        settings_matches[86], // version_nano
        settings_matches[87], // version_nano_prefix
        settings_matches[88], // version_target
      };

      const f_string_static_t settings_single_string_default[] = {
        fake_build_setting_default_gcc_s,            // build_compiler
        fake_build_setting_default_ar_s,             // build_indexer
        f_string_empty_s,                            // build_language
        f_string_empty_s,                            // build_name
        f_string_empty_s,                            // build_script
        f_string_empty_s,                            // build_shared
        f_string_empty_s,                            // build_sources_object
        f_string_empty_s,                            // build_sources_object_shared
        f_string_empty_s,                            // build_sources_object_static
        f_string_empty_s,                            // build_static
        fake_build_setting_default_yes_s,            // has_path_standard
        f_string_empty_s,                            // path_headers
        f_string_empty_s,                            // path_language
        fake_path_part_script_s,                     // path_library_script
        fake_path_part_shared_s,                     // path_library_shared
        fake_path_part_static_s,                     // path_library_static
        fake_path_part_script_s,                     // path_object_script
        fake_path_part_shared_s,                     // path_object_shared
        fake_path_part_static_s,                     // path_object_static
        fake_path_part_script_s,                     // path_program_script
        fake_path_part_shared_s,                     // path_program_shared
        fake_path_part_static_s,                     // path_program_static
        main->setting.sources,                      // path_sources
        f_string_empty_s,                            // path_sources_object
        f_string_empty_s,                            // preserve_path_headers
        f_string_empty_s,                            // process_post
        f_string_empty_s,                            // process_pre
        fake_build_setting_default_yes_s,            // search_exclusive
        f_string_empty_s,                            // search_shared
        f_string_empty_s,                            // search_static
        f_string_empty_s,                            // version_file
        f_string_empty_s,                            // version_major
        fake_build_setting_default_version_prefix_s, // version_major_prefix
        f_string_empty_s,                            // version_micro
        fake_build_setting_default_version_prefix_s, // version_micro_prefix
        f_string_empty_s,                            // version_minor
        fake_build_setting_default_version_prefix_s, // version_minor_prefix
        f_string_empty_s,                            // version_nano
        fake_build_setting_default_version_prefix_s, // version_nano_prefix
        f_string_empty_s,                            // version_target
      };

      uint8_t *settings_single_language[] = {
        0,                                           // build_compiler
        0,                                           // build_indexer
        &setting->build_language,                    // build_language
      };

      uint8_t *settings_single_version[] = {
        0,                                           // build_compiler
        0,                                           // build_indexer
        0,                                           // build_language
        0,                                           // build_name
        0,                                           // build_script
        0,                                           // build_shared
        0,                                           // build_sources_object
        0,                                           // build_sources_object_shared
        0,                                           // build_sources_object_static
        0,                                           // build_static
        0,                                           // has_path_standard
        0,                                           // path_headers
        0,                                           // path_language
        0,                                           // path_library_script
        0,                                           // path_library_shared
        0,                                           // path_library_static
        0,                                           // path_object_script
        0,                                           // path_object_shared
        0,                                           // path_object_static
        0,                                           // path_program_script
        0,                                           // path_program_shared
        0,                                           // path_program_static
        0,                                           // path_sources
        0,                                           // path_sources_object
        0,                                           // preserve_path_headers
        0,                                           // process_post
        0,                                           // process_pre
        0,                                           // search_exclusive
        0,                                           // search_shared
        0,                                           // search_static
        &setting->version_file,                      // version_file
        0,                                           // version_major
        0,                                           // version_major_prefix
        0,                                           // version_micro
        0,                                           // version_micro_prefix
        0,                                           // version_minor
        0,                                           // version_minor_prefix
        0,                                           // version_nano
        0,                                           // version_nano_prefix
        &setting->version_target,                    // version_target
      };

      static const uint8_t settings_single_version_default[] = {
        0,                                           // build_compiler
        0,                                           // build_indexer
        0,                                           // build_language
        0,                                           // build_name
        0,                                           // build_script
        0,                                           // build_shared
        0,                                           // build_sources_object
        0,                                           // build_sources_object_shared
        0,                                           // build_sources_object_static
        0,                                           // build_static
        0,                                           // has_path_standard
        0,                                           // path_headers
        0,                                           // path_language
        0,                                           // path_library_script
        0,                                           // path_library_shared
        0,                                           // path_library_static
        0,                                           // path_object_script
        0,                                           // path_object_shared
        0,                                           // path_object_static
        0,                                           // path_program_script
        0,                                           // path_program_shared
        0,                                           // path_program_static
        0,                                           // path_sources
        0,                                           // path_sources_object
        0,                                           // preserve_path_headers
        0,                                           // process_post
        0,                                           // process_pre
        0,                                           // search_exclusive
        0,                                           // search_shared
        0,                                           // search_static
        fake_build_version_micro_e,                  // version_file
        0,                                           // version_major
        0,                                           // version_major_prefix
        0,                                           // version_micro
        0,                                           // version_micro_prefix
        0,                                           // version_minor
        0,                                           // version_minor_prefix
        0,                                           // version_nano
        0,                                           // version_nano_prefix
        fake_build_version_major_e,                  // version_target
      };

      const f_string_static_t settings_single_version_default_name[] = {
        f_string_empty_s,                            // build_compiler
        f_string_empty_s,                            // build_indexer
        f_string_empty_s,                            // build_language
        f_string_empty_s,                            // build_name
        fake_common_setting_bool_yes_s,              // build_script
        fake_common_setting_bool_yes_s,              // build_shared
        f_string_empty_s,                            // build_sources_object
        f_string_empty_s,                            // build_sources_object_shared
        f_string_empty_s,                            // build_sources_object_static
        fake_common_setting_bool_yes_s,              // build_static
        fake_common_setting_bool_yes_s,              // has_path_standard
        f_string_empty_s,                            // path_headers
        f_string_empty_s,                            // path_language
        f_string_empty_s,                            // path_library_script
        f_string_empty_s,                            // path_library_shared
        f_string_empty_s,                            // path_library_static
        f_string_empty_s,                            // path_object_script
        f_string_empty_s,                            // path_object_shared
        f_string_empty_s,                            // path_object_static
        f_string_empty_s,                            // path_program_script
        f_string_empty_s,                            // path_program_shared
        f_string_empty_s,                            // path_program_static
        f_string_empty_s,                            // path_sources
        f_string_empty_s,                            // path_sources_object
        fake_common_setting_bool_yes_s,              // preserve_path_headers
        f_string_empty_s,                            // process_post
        f_string_empty_s,                            // process_pre
        fake_common_setting_bool_yes_s,              // search_exclusive
        fake_common_setting_bool_yes_s,              // search_shared
        fake_common_setting_bool_yes_s,              // search_static
        fake_build_version_micro_s,                  // version_file
        f_string_empty_s,                            // version_major
        f_string_empty_s,                            // version_major_prefix
        f_string_empty_s,                            // version_micro
        f_string_empty_s,                            // version_micro_prefix
        f_string_empty_s,                            // version_minor
        f_string_empty_s,                            // version_minor_prefix
        f_string_empty_s,                            // version_nano
        f_string_empty_s,                            // version_nano_prefix
        fake_build_version_major_s,                  // version_target
      };

      // 1 = "yes" or "no", 2 = path/, 3 = literal, 4 = "bash", "c", or "c++", 5 = "major", "minor", "micro", or "nano".
      static const uint8_t settings_single_type[] = {
        3,                                           // build_compiler
        3,                                           // build_indexer
        4,                                           // build_language
        3,                                           // build_name
        1,                                           // build_script
        1,                                           // build_shared
        3,                                           // build_sources_object
        3,                                           // build_sources_object_shared
        3,                                           // build_sources_object_static
        1,                                           // build_static
        1,                                           // has_path_standard
        2,                                           // path_headers
        2,                                           // path_language
        2,                                           // path_library_script
        2,                                           // path_library_shared
        2,                                           // path_library_static
        2,                                           // path_object_script
        2,                                           // path_object_shared
        2,                                           // path_object_static
        2,                                           // path_program_script
        2,                                           // path_program_shared
        2,                                           // path_program_static
        2,                                           // path_sources
        2,                                           // path_sources_object
        1,                                           // preserve_path_headers
        3,                                           // process_post
        3,                                           // process_pre
        1,                                           // search_exclusive
        1,                                           // search_shared
        1,                                           // search_static
        5,                                           // version_file
        3,                                           // version_major
        3,                                           // version_major_prefix
        3,                                           // version_micro
        3,                                           // version_micro_prefix
        3,                                           // version_minor
        3,                                           // version_minor_prefix
        3,                                           // version_nano
        3,                                           // version_nano_prefix
        5,                                           // version_target
      };

      for (f_number_unsigned_t i = 0; i < 40; ++i) {

        // Assign the default for literal and path types.
        if (!settings_single_matches[i] && settings_single_destination[i]) {
          settings_single_destination[i]->used = 0;

          main->setting.state.status = f_string_dynamic_append(settings_single_string_default[i], settings_single_destination[i]);

          if (F_status_is_error(main->setting.state.status)) {
            fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append));

            break;
          }
        }

        if (!settings_single_source[i]->used) continue;

        if (settings_single_type[i] == 1) {
          if (f_compare_dynamic_trim(settings_single_source[i]->array[settings_single_source[i]->used - 1], fake_common_setting_bool_yes_s) == F_equal_to) {
            *settings_single_bool[i] = F_true;
          }
          else if (f_compare_dynamic_trim(settings_single_source[i]->array[settings_single_source[i]->used - 1], fake_common_setting_bool_no_s) == F_equal_to) {
            *settings_single_bool[i] = F_false;
          }
          else {
            *settings_single_bool[i] = F_true;

            fake_build_print_warning_setting_boolean_may_only_be(&main->program.warning, settings_single_name[i], path_file, settings_single_version_default_name[i]);
          }
        }
        else if (settings_single_type[i] == 4) {
          if (f_compare_dynamic_trim(settings_single_source[i]->array[settings_single_source[i]->used - 1], fake_build_language_bash_s) == F_equal_to) {
            *settings_single_language[i] = fake_build_language_bash_e;
          }
          else if (f_compare_dynamic_trim(settings_single_source[i]->array[settings_single_source[i]->used - 1], fake_build_language_c_s) == F_equal_to) {
            *settings_single_language[i] = fake_build_language_c_e;
          }
          else if (f_compare_dynamic_trim(settings_single_source[i]->array[settings_single_source[i]->used - 1], fake_build_language_cpp_s) == F_equal_to) {
            *settings_single_language[i] = fake_build_language_cpp_e;
          }
          else {
            *settings_single_language[i] = fake_build_language_c_e;

            fake_build_print_warning_setting_language_may_only_be(&main->program.warning, settings_single_name[i], path_file, fake_build_language_c_s);
          }
        }
        else if (settings_single_type[i] == 5) {
          if (f_compare_dynamic_trim(settings_single_source[i]->array[settings_single_source[i]->used - 1], fake_build_version_major_s) == F_equal_to) {
            *settings_single_version[i] = fake_build_version_major_e;
          }
          else if (f_compare_dynamic_trim(settings_single_source[i]->array[settings_single_source[i]->used - 1], fake_build_version_minor_s) == F_equal_to) {
            *settings_single_version[i] = fake_build_version_minor_e;
          }
          else if (f_compare_dynamic_trim(settings_single_source[i]->array[settings_single_source[i]->used - 1], fake_build_version_micro_s) == F_equal_to) {
            *settings_single_version[i] = fake_build_version_micro_e;
          }
          else if (f_compare_dynamic_trim(settings_single_source[i]->array[settings_single_source[i]->used - 1], fake_build_version_nano_s) == F_equal_to) {
            *settings_single_version[i] = fake_build_version_nano_e;
          }
          else {
            *settings_single_version[i] = settings_single_version_default[i];

            fake_build_print_warning_setting_version_may_only_be(&main->program.warning, settings_single_name[i], path_file, settings_single_version_default_name[i]);
          }
        }
        else if (settings_single_destination[i]) {

          // Replace any potential existing value.
          settings_single_destination[i]->used = 0;

          if (settings_single_type[i] == 2) {
            main->setting.state.status = f_path_directory_cleanup(settings_single_source[i]->array[settings_single_source[i]->used - 1], settings_single_destination[i]);

            if (F_status_is_error(main->setting.state.status)) {
              fake_print_error(&main->program.error, macro_fake_f(f_path_directory_cleanup));

              break;
            }
          }
          else {
            main->setting.state.status = f_string_dynamic_increase_by(settings_single_source[i]->array[settings_single_source[i]->used - 1].used + 1, settings_single_destination[i]);

            if (F_status_is_error(main->setting.state.status)) {
              fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_increase_by));

              break;
            }

            main->setting.state.status = f_string_dynamic_append_nulless(settings_single_source[i]->array[settings_single_source[i]->used - 1], settings_single_destination[i]);

            if (F_status_is_error(main->setting.state.status)) {
              fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

              break;
            }
          }
        }
      } // for

      if (F_status_is_error_not(main->setting.state.status)) {
        if (checks && !setting->version_file) {
          setting->version_file = fake_build_version_micro_e;

          fake_build_print_warning_setting_required_default_to(&main->program.warning, fake_build_setting_name_version_file_s, path_file, fake_build_version_micro_s);
        }

        if (checks && !setting->version_target) {
          setting->version_target = fake_build_version_major_e;

          fake_build_print_warning_setting_required_default_to(&main->program.warning, fake_build_setting_name_version_target_s, path_file, fake_build_version_major_s);
        }
      }
    }

    f_string_dynamics_resize(0, &build_compiler);
    f_string_dynamics_resize(0, &build_indexer);
    f_string_dynamics_resize(0, &build_language);
    f_string_dynamics_resize(0, &build_name);
    f_string_dynamics_resize(0, &build_script);
    f_string_dynamics_resize(0, &build_shared);
    f_string_dynamics_resize(0, &build_sources_object);
    f_string_dynamics_resize(0, &build_sources_object_shared);
    f_string_dynamics_resize(0, &build_sources_object_static);
    f_string_dynamics_resize(0, &build_static);
    f_string_dynamics_resize(0, &has_path_standard);
    f_string_dynamics_resize(0, &path_headers);
    f_string_dynamics_resize(0, &path_language);
    f_string_dynamics_resize(0, &path_library_script);
    f_string_dynamics_resize(0, &path_library_shared);
    f_string_dynamics_resize(0, &path_library_static);
    f_string_dynamics_resize(0, &path_object_script);
    f_string_dynamics_resize(0, &path_object_shared);
    f_string_dynamics_resize(0, &path_object_static);
    f_string_dynamics_resize(0, &path_program_script);
    f_string_dynamics_resize(0, &path_program_shared);
    f_string_dynamics_resize(0, &path_program_static);
    f_string_dynamics_resize(0, &path_sources);
    f_string_dynamics_resize(0, &path_sources_object);
    f_string_dynamics_resize(0, &preserve_path_headers);
    f_string_dynamics_resize(0, &process_post);
    f_string_dynamics_resize(0, &process_pre);
    f_string_dynamics_resize(0, &search_exclusive);
    f_string_dynamics_resize(0, &search_shared);
    f_string_dynamics_resize(0, &search_static);
    f_string_dynamics_resize(0, &version_file);
    f_string_dynamics_resize(0, &version_major);
    f_string_dynamics_resize(0, &version_major_prefix);
    f_string_dynamics_resize(0, &version_micro);
    f_string_dynamics_resize(0, &version_micro_prefix);
    f_string_dynamics_resize(0, &version_minor);
    f_string_dynamics_resize(0, &version_minor_prefix);
    f_string_dynamics_resize(0, &version_nano);
    f_string_dynamics_resize(0, &version_nano_prefix);
    f_string_dynamics_resize(0, &version_target);
  }
#endif // _di_fake_build_load_setting_process_

#ifndef _di_fake_build_load_setting_override_
  void fake_build_load_setting_override(fake_data_t * const data, fake_build_setting_t * const setting) {

    if (!data || !data->main || !setting) return;
    if (F_status_is_error(data->main->setting.state.status)) return;

    fake_main_t * const main = data->main;

    if (main->program.parameters.array[fake_parameter_sources_e].result & f_console_result_value_e && setting->path_sources.used) {
      main->setting.state.status = f_string_dynamic_append_assure(f_path_separator_s, &setting->path_sources);

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append_assure));

        return;
      }
    }

    if (main->program.parameters.array[fake_parameter_shared_disable_e].result & f_console_result_found_e) {
      if (main->program.parameters.array[fake_parameter_shared_enable_e].result & f_console_result_found_e) {
        if (main->program.parameters.array[fake_parameter_shared_enable_e].location > main->program.parameters.array[fake_parameter_shared_disable_e].location) {
          setting->build_shared = F_true;
          setting->search_shared = F_true;
        }
        else {
          setting->build_shared = F_false;
          setting->search_shared = F_false;
        }

        fake_build_print_warning_parameters_contradict(&main->program.warning, f_console_symbol_long_normal_s, fake_long_shared_disabled_s, f_console_symbol_long_normal_s, fake_long_shared_enabled_s, f_console_symbol_long_normal_s, setting->build_shared ? fake_long_shared_enabled_s : fake_long_shared_disabled_s);
      }
      else {
        setting->build_shared = F_false;
        setting->search_shared = F_false;
      }
    }
    else if (main->program.parameters.array[fake_parameter_shared_enable_e].result & f_console_result_found_e) {
      setting->build_shared = F_true;
      setting->search_shared = F_true;
    }

    if (main->program.parameters.array[fake_parameter_static_disable_e].result & f_console_result_found_e) {
      if (main->program.parameters.array[fake_parameter_static_enable_e].result & f_console_result_found_e) {
        if (main->program.parameters.array[fake_parameter_static_enable_e].location > main->program.parameters.array[fake_parameter_static_disable_e].location) {
          setting->build_static = F_true;
          setting->search_static = F_true;
        }
        else {
          setting->build_static = F_false;
          setting->search_static = F_false;
        }

        fake_build_print_warning_parameters_contradict(&main->program.warning, f_console_symbol_long_normal_s, fake_long_static_disabled_s, f_console_symbol_long_normal_s, fake_long_static_enabled_s, f_console_symbol_long_normal_s, setting->build_static ? fake_long_static_enabled_s : fake_long_static_disabled_s);
      }
      else {
        setting->build_static = F_false;
        setting->search_static = F_false;
      }
    }
    else if (main->program.parameters.array[fake_parameter_static_enable_e].result & f_console_result_found_e) {
      setting->build_static = F_true;
      setting->search_static = F_true;
    }

    if (setting->build_language == fake_build_language_c_e || setting->build_language == fake_build_language_cpp_e) {
      if (setting->build_shared == F_false && setting->build_static == F_false) {
        fake_build_print_warning_setting_both_cannot_when_language(&main->program.warning, fake_build_setting_name_build_shared_s, fake_build_setting_name_build_static_s, setting->build_language == fake_build_language_c_e ? fake_build_language_c_s : fake_build_language_cpp_s);

        main->setting.state.status = F_status_set_error(F_failure);
      }
    }
  }
#endif // _di_fake_build_load_setting_override_

#ifndef _di_fake_build_load_stage_
  void fake_build_load_stage(fake_data_t * const data, const f_string_static_t settings_file, fake_build_stage_t * const stage) {

    if (!data || !data->main || !stage) return;
    if (F_status_is_error(data->main->setting.state.status)) return;
    if (fake_signal_check(data->main)) return;

    fake_main_t * const main = data->main;

    const f_string_static_t names[] = {
      fake_build_stage_library_script_s,
      fake_build_stage_library_shared_s,
      fake_build_stage_library_static_s,
      fake_build_stage_object_script_s,
      fake_build_stage_object_shared_s,
      fake_build_stage_object_static_s,
      fake_build_stage_objects_static_s,
      fake_build_stage_process_post_s,
      fake_build_stage_process_pre_s,
      fake_build_stage_program_script_s,
      fake_build_stage_program_shared_s,
      fake_build_stage_program_static_s,
      fake_build_stage_skeleton_s,
      fake_build_stage_sources_documentation_s,
      fake_build_stage_sources_headers_s,
      fake_build_stage_sources_script_s,
      fake_build_stage_sources_settings_s,
    };

    f_string_dynamic_t * const values[] = {
      &stage->file_library_script,
      &stage->file_library_shared,
      &stage->file_library_static,
      &stage->file_object_script,
      &stage->file_object_shared,
      &stage->file_object_static,
      &stage->file_objects_static,
      &stage->file_process_post,
      &stage->file_process_pre,
      &stage->file_program_script,
      &stage->file_program_shared,
      &stage->file_program_static,
      &stage->file_skeleton,
      &stage->file_sources_documentation,
      &stage->file_sources_headers,
      &stage->file_sources_script,
      &stage->file_sources_settings,
    };

    main->setting.state.status = F_none;

    f_string_dynamic_t settings_file_base = f_string_dynamic_t_initialize;

    if (settings_file.used) {
      main->setting.state.status = f_file_name_base(settings_file, &settings_file_base);
    }
    else {
      main->setting.state.status = f_file_name_base(data->file_data_build_settings, &settings_file_base);
    }

    if (F_status_is_error(main->setting.state.status)) {
      fake_print_error(&main->program.error, macro_fake_f(f_file_name_base));

      return;
    }

    for (uint8_t i = 0; i < fake_build_stage_total_d; ++i) {

      values[i]->used = 0;

      main->setting.state.status = f_string_dynamic_append_nulless(data->path_build_stage, values[i]);

      if (F_status_is_error_not(main->setting.state.status) && main->setting.process.used) {
        main->setting.state.status = f_string_dynamic_append_nulless(main->setting.process, values[i]);

        if (F_status_is_error_not(main->setting.state.status)) {
          main->setting.state.status = f_string_dynamic_append_nulless(fake_build_stage_separate_s, values[i]);
        }
      }

      if (F_status_is_error_not(main->setting.state.status) && names[i].used) {
        main->setting.state.status = f_string_dynamic_append_nulless(names[i], values[i]);

        if (F_status_is_error_not(main->setting.state.status)) {
          main->setting.state.status = f_string_dynamic_append_nulless(fake_build_stage_separate_s, values[i]);
        }
      }

      if (F_status_is_error_not(main->setting.state.status)) {
        main->setting.state.status = f_string_dynamic_append_nulless(settings_file_base, values[i]);
      }

      if (F_status_is_error_not(main->setting.state.status)) {
        main->setting.state.status = f_string_dynamic_append_nulless(fake_build_stage_built_s, values[i]);
      }

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

        break;
      }
    } // for

    f_string_dynamic_resize(0, &settings_file_base);
  }
#endif // _di_fake_build_load_stage_

#ifdef __cplusplus
} // extern "C"
#endif
