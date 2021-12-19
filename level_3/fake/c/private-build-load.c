#include "fake.h"
#include "private-common.h"
#include "private-fake.h"
#include "private-build.h"
#include "private-build-load.h"
#include "private-make.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_load_environment_
  void fake_build_load_environment(fake_main_t * const main, const fake_build_data_t data_build, f_string_maps_t *environment, f_status_t *status) {

    if (F_status_is_error(*status)) return;

    // Reset the environment.
    for (f_array_length_t i = 0; i < environment->used; ++i) {
      environment->array[i].name.used = 0;
      environment->array[i].value.used = 0;
    } // for

    environment->used = 0;

    {
      // Add the guaranteed environment variables.
      const f_string_t variables_name[] = {
        f_path_environment_s,
        f_path_present_working_s
      };

      const f_array_length_t variables_length[] = {
        F_path_environment_s_length,
        F_path_present_working_s_length
      };

      for (uint8_t i = 0; i < 2; ++i) {

        *status = fl_environment_load_name(variables_name[i], variables_length[i], environment);

        if (F_status_is_error(*status)) {
          fll_error_print(main->error, F_status_set_fine(*status), "fl_environment_load_name", F_true);
          break;
        }
      } // for

      if (F_status_is_error(*status)) {
        return;
      }
    }

    if (environment->used + data_build.setting.environment.used > environment->size) {
      if (environment->used + data_build.setting.environment.used > f_environment_max_length) {
        if (main->error.verbosity != f_console_verbosity_quiet) {
          flockfile(main->error.to.stream);

          fl_print_format("%c%[%SThe values for the setting '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%s%]", main->error.to.stream, main->error.notable, fake_build_setting_name_environment_s, main->error.notable);
          fl_print_format("%[' of setting file '%]", main->error.to.stream, main->error.context, main->error.context);
          fl_print_format("%[%s%]", main->error.to.stream, main->error.notable, fake_build_setting_name_environment_s, main->error.notable);
          fl_print_format("%[' is too large.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

          flockfile(main->error.to.stream);
        }

        *status = F_status_set_error(F_array_too_large);

        return;
      }
    }

    *status = fl_environment_load_names(data_build.setting.environment, environment);

    if (F_status_is_error(*status)) {
      fll_error_print(main->error, F_status_set_fine(*status), "fl_environment_load_names", F_true);
    }
  }
#endif // _di_fake_build_load_environment_

#ifndef _di_fake_build_load_setting_
  void fake_build_load_setting(fake_main_t * const main, const f_string_static_t setting_file, fake_build_setting_t *setting, f_status_t *status) {

    if (F_status_is_error(*status)) return;

    if (fake_signal_received(main)) {
      *status = F_status_set_error(F_interrupt);

      return;
    }

    char path_file[main->path_data_build.used + setting_file.used + 1];

    {
      f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

      f_fss_objects_t objects = f_fss_objects_t_initialize;
      f_fss_contents_t contents = f_fss_contents_t_initialize;

      if (setting_file.used) {
        memcpy(path_file, main->path_data_build.string, main->path_data_build.used);
        memcpy(path_file + main->path_data_build.used, setting_file.string, setting_file.used);

        path_file[main->path_data_build.used + setting_file.used] = 0;

        *status = fake_file_buffer(main, path_file, &buffer);
      }
      else {
        *status = fake_file_buffer(main, main->file_data_build_settings.string, &buffer);
      }

      if (F_status_is_error_not(*status)) {
        f_string_range_t range = macro_f_string_range_t_initialize(buffer.used);
        f_fss_delimits_t delimits = f_fss_delimits_t_initialize;

        {
          f_state_t state = macro_f_state_t_initialize(fake_common_allocation_large_d, fake_common_allocation_small_d, 0, &fake_signal_state_interrupt_fss, 0, (void *) &main, 0);

          *status = fll_fss_extended_read(buffer, state, &range, &objects, &contents, 0, 0, &delimits, 0);
        }

        if (F_status_is_error(*status)) {
          fake_print_error_fss(main, F_status_set_fine(*status), "fll_fss_extended_read", main->file_data_build_settings.string, range, F_true);
        }
        else {
          *status = fl_fss_apply_delimit(delimits, &buffer);

          if (F_status_is_error(*status)) {
            fll_error_print(main->error, F_status_set_fine(*status), "fl_fss_apply_delimit", F_true);
          }
          else {
            fake_build_load_setting_process(main, F_true, setting_file.used ? path_file : main->file_data_build_settings.string, buffer, objects, contents, setting, status);
          }
        }

        macro_f_fss_delimits_t_delete_simple(delimits);
      }

      macro_f_string_dynamic_t_delete_simple(buffer);
      macro_f_fss_objects_t_delete_simple(objects);
      macro_f_fss_contents_t_delete_simple(contents);
    }

    // Error when required settings are not specified.
    if (F_status_is_error_not(*status)) {
      bool failed = F_false;

      f_string_static_t * const settings[] = {
        &setting->project_name,
      };

      f_string_t names[] = {
        fake_build_setting_name_project_name_s,
      };

      for (uint8_t i = 0; i < 1; ++i) {

        if (!settings[i]->used) {
          flockfile(main->error.to.stream);

          fl_print_format("%c%[%SThe setting '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%S%]", main->error.to.stream, main->error.notable, names[i], main->error.notable);
          fl_print_format("%[' is required but is not specified in the settings file '%]", main->error.to.stream, main->error.context, main->error.context);
          fl_print_format("%[%S%]", main->error.to.stream, main->error.notable, setting_file.used ? path_file : main->file_data_build_settings.string, main->error.notable);
          fl_print_format("%['.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

          funlockfile(main->error.to.stream);

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
  void fake_build_load_setting_process(fake_main_t * const main, const bool checks, const f_string_t path_file, const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, fake_build_setting_t *setting, f_status_t *status) {

    if (F_status_is_error(*status) && buffer.used) return;

    if (fake_signal_received(main)) {
      *status = F_status_set_error(F_interrupt);

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
      fake_build_setting_name_build_compiler_s,
      fake_build_setting_name_build_indexer_s,
      fake_build_setting_name_build_indexer_arguments_s,
      fake_build_setting_name_build_language_s,
      fake_build_setting_name_build_libraries_s,
      fake_build_setting_name_build_libraries_shared_s,
      fake_build_setting_name_build_libraries_static_s,
      fake_build_setting_name_build_script_s,
      fake_build_setting_name_build_shared_s,
      fake_build_setting_name_build_sources_headers_s,
      fake_build_setting_name_build_sources_headers_shared_s,
      fake_build_setting_name_build_sources_headers_static_s,
      fake_build_setting_name_build_sources_library_s,
      fake_build_setting_name_build_sources_library_shared_s,
      fake_build_setting_name_build_sources_library_static_s,
      fake_build_setting_name_build_sources_program_s,
      fake_build_setting_name_build_sources_program_shared_s,
      fake_build_setting_name_build_sources_program_static_s,
      fake_build_setting_name_build_sources_script_s,
      fake_build_setting_name_build_sources_settings_s,
      fake_build_setting_name_build_static_s,
      fake_build_setting_name_defines_s,
      fake_build_setting_name_defines_library_s,
      fake_build_setting_name_defines_library_shared_s,
      fake_build_setting_name_defines_library_static_s,
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
      fake_build_setting_name_flags_program_s,
      fake_build_setting_name_flags_program_shared_s,
      fake_build_setting_name_flags_program_static_s,
      fake_build_setting_name_flags_shared_s,
      fake_build_setting_name_flags_static_s,
      fake_build_setting_name_modes_s,
      fake_build_setting_name_modes_default_s,
      fake_build_setting_name_path_headers_s,
      fake_build_setting_name_path_headers_preserve_s,
      fake_build_setting_name_path_language_s,
      fake_build_setting_name_path_library_script_s,
      fake_build_setting_name_path_library_shared_s,
      fake_build_setting_name_path_library_static_s,
      fake_build_setting_name_path_program_script_s,
      fake_build_setting_name_path_program_shared_s,
      fake_build_setting_name_path_program_static_s,
      fake_build_setting_name_path_sources_s,
      fake_build_setting_name_path_standard_s,
      fake_build_setting_name_process_post_s,
      fake_build_setting_name_process_pre_s,
      fake_build_setting_name_project_name_s,
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

    const f_array_length_t settings_length[] = {
      fake_build_setting_name_build_compiler_s_length,
      fake_build_setting_name_build_indexer_s_length,
      fake_build_setting_name_build_indexer_arguments_s_length,
      fake_build_setting_name_build_language_s_length,
      fake_build_setting_name_build_libraries_s_length,
      fake_build_setting_name_build_libraries_shared_s_length,
      fake_build_setting_name_build_libraries_static_s_length,
      fake_build_setting_name_build_script_s_length,
      fake_build_setting_name_build_shared_s_length,
      fake_build_setting_name_build_sources_headers_s_length,
      fake_build_setting_name_build_sources_headers_shared_s_length,
      fake_build_setting_name_build_sources_headers_static_s_length,
      fake_build_setting_name_build_sources_library_s_length,
      fake_build_setting_name_build_sources_library_shared_s_length,
      fake_build_setting_name_build_sources_library_static_s_length,
      fake_build_setting_name_build_sources_program_s_length,
      fake_build_setting_name_build_sources_program_shared_s_length,
      fake_build_setting_name_build_sources_program_static_s_length,
      fake_build_setting_name_build_sources_script_s_length,
      fake_build_setting_name_build_sources_settings_s_length,
      fake_build_setting_name_build_static_s_length,
      fake_build_setting_name_defines_s_length,
      fake_build_setting_name_defines_library_s_length,
      fake_build_setting_name_defines_library_shared_s_length,
      fake_build_setting_name_defines_library_static_s_length,
      fake_build_setting_name_defines_program_s_length,
      fake_build_setting_name_defines_program_shared_s_length,
      fake_build_setting_name_defines_program_static_s_length,
      fake_build_setting_name_defines_shared_s_length,
      fake_build_setting_name_defines_static_s_length,
      fake_build_setting_name_environment_length_s,
      fake_build_setting_name_flags_s_length,
      fake_build_setting_name_flags_library_s_length,
      fake_build_setting_name_flags_library_shared_s_length,
      fake_build_setting_name_flags_library_static_s_length,
      fake_build_setting_name_flags_program_s_length,
      fake_build_setting_name_flags_program_shared_s_length,
      fake_build_setting_name_flags_program_static_s_length,
      fake_build_setting_name_flags_shared_s_length,
      fake_build_setting_name_flags_static_s_length,
      fake_build_setting_name_modes_s_length,
      fake_build_setting_name_modes_default_s_length,
      fake_build_setting_name_path_headers_s_length,
      fake_build_setting_name_path_headers_preserve_s_length,
      fake_build_setting_name_path_language_s_length,
      fake_build_setting_name_path_library_script_s_length,
      fake_build_setting_name_path_library_shared_s_length,
      fake_build_setting_name_path_library_static_s_length,
      fake_build_setting_name_path_program_script_s_length,
      fake_build_setting_name_path_program_shared_s_length,
      fake_build_setting_name_path_program_static_s_length,
      fake_build_setting_name_path_sources_s_length,
      fake_build_setting_name_path_standard_s_length,
      fake_build_setting_name_process_post_s_length,
      fake_build_setting_name_process_pre_s_length,
      fake_build_setting_name_project_name_s_length,
      fake_build_setting_name_search_exclusive_s_length,
      fake_build_setting_name_search_shared_s_length,
      fake_build_setting_name_search_static_s_length,
      fake_build_setting_name_version_file_s_length,
      fake_build_setting_name_version_major_s_length,
      fake_build_setting_name_version_major_prefix_s_length,
      fake_build_setting_name_version_micro_s_length,
      fake_build_setting_name_version_micro_prefix_s_length,
      fake_build_setting_name_version_minor_s_length,
      fake_build_setting_name_version_minor_prefix_s_length,
      fake_build_setting_name_version_nano_s_length,
      fake_build_setting_name_version_nano_prefix_s_length,
      fake_build_setting_name_version_target_s_length,
    };

    f_string_dynamics_t *settings_value[] = {
      &build_compiler,
      &build_indexer,
      &setting->build_indexer_arguments,
      &build_language,
      &setting->build_libraries,
      &setting->build_libraries_shared,
      &setting->build_libraries_static,
      &build_script,
      &build_shared,
      &setting->build_sources_headers,
      &setting->build_sources_headers_shared,
      &setting->build_sources_headers_static,
      &setting->build_sources_library,
      &setting->build_sources_library_shared,
      &setting->build_sources_library_static,
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
      &setting->flags_program,
      &setting->flags_program_shared,
      &setting->flags_program_static,
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

    *status = fll_fss_snatch_apart(buffer, objects, contents, settings_name, settings_length, fake_build_setting_total_d, settings_value, settings_matches, 0);

    if (*status == F_none) {
      const int total_build_libraries = setting->build_libraries.used;
      const f_string_dynamics_t *modes = &setting->modes_default;

      f_string_dynamic_t settings_mode_name_dynamic[fake_build_setting_total_d];
      f_string_t settings_mode_names[fake_build_setting_total_d];
      f_array_length_t setting_mode_lengths[fake_build_setting_total_d];

      bool found = F_false;

      f_array_length_t i = 0;
      f_array_length_t j = 0;

      // If any mode is specified, the entire defaults is replaced.
      if (main->mode.used) {
        modes = &main->mode;
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
          if (main->error.verbosity != f_console_verbosity_quiet) {
            flockfile(main->error.to.stream);

            fl_print_format("%c%[%SThe specified mode '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, modes->array[i], main->error.notable);
            fl_print_format("%[' is not a valid mode, according to '%]", main->error.to.stream, main->error.context, main->error.context);
            fl_print_format("%[%S%]", main->error.to.stream, main->error.notable, path_file, main->error.notable);
            fl_print_format("%['.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

            funlockfile(main->error.to.stream);
          }

          error_printed = F_true;
          *status = F_status_set_error(F_parameter);

          break;
        }

        memset(&settings_mode_name_dynamic, 0, sizeof(f_string_dynamic_t) * fake_build_setting_total_d);
        memset(&settings_mode_names, 0, sizeof(f_string_t) * fake_build_setting_total_d);
        memset(&setting_mode_lengths, 0, sizeof(f_array_length_t) * fake_build_setting_total_d);

        for (j = 0; j < fake_build_setting_total_d; ++j) {

          setting_mode_lengths[j] = settings_length[j] + 1 + modes->array[i].used;

          *status = f_string_dynamic_resize(setting_mode_lengths[j], &settings_mode_name_dynamic[j]);

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
          *status = fll_fss_snatch_apart(buffer, objects, contents, settings_mode_names, setting_mode_lengths, fake_build_setting_total_d, settings_value, 0, 0);

          if (F_status_is_error(*status)) {
            function = "fll_fss_snatch_apart";
          }
        }

        for (j = 0; j < fake_build_setting_total_d; ++j) {
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
        if (main->error.verbosity != f_console_verbosity_quiet) {
          funlockfile(main->error.to.stream);

          fl_print_format("%c%[%SA setting in the file '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%S%]", main->error.to.stream, main->error.notable, path_file, main->error.notable);
          fl_print_format("%[' is too long.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

          funlockfile(main->error.to.stream);
        }
      }
      else if (!error_printed) {
        fll_error_print(main->error, F_status_set_fine(*status), function, F_true);
      }
    }
    else {
      const f_string_t settings_single_name[] = {
        fake_build_setting_name_build_compiler_s,
        fake_build_setting_name_build_indexer_s,
        fake_build_setting_name_build_language_s,
        fake_build_setting_name_build_script_s,
        fake_build_setting_name_build_shared_s,
        fake_build_setting_name_build_static_s,
        fake_build_setting_name_path_headers_s,
        fake_build_setting_name_path_headers_preserve_s,
        fake_build_setting_name_path_language_s,
        fake_build_setting_name_path_library_script_s,
        fake_build_setting_name_path_library_shared_s,
        fake_build_setting_name_path_library_static_s,
        fake_build_setting_name_path_program_script_s,
        fake_build_setting_name_path_program_shared_s,
        fake_build_setting_name_path_program_static_s,
        fake_build_setting_name_path_sources_s,
        fake_build_setting_name_path_standard_s,
        fake_build_setting_name_process_post_s,
        fake_build_setting_name_process_pre_s,
        fake_build_setting_name_project_name_s,
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
        0,                               // build_compiler
        0,                               // build_indexer
        0,                               // build_language
        &setting->build_script,          // build_script
        &setting->build_shared,          // build_shared
        &setting->build_static,          // build_static
        0,                               // path_headers
        &setting->path_headers_preserve, // path_headers_preserve
        0,                               // path_language
        0,                               // path_library_script
        0,                               // path_library_shared
        0,                               // path_library_static
        0,                               // path_program_script
        0,                               // path_program_shared
        0,                               // path_program_static
        0,                               // path_sources
        &setting->path_standard,         // path_standard
        0,                               // process_post
        0,                               // process_pre
        0,                               // project_name
        &setting->search_exclusive,      // search_exclusive
        &setting->search_shared,         // search_shared
        &setting->search_static,         // search_static
      };

      f_string_dynamic_t * const settings_single_destination[] = {
        &setting->build_compiler,        // build_compiler
        &setting->build_indexer,         // build_indexer
        0,                               // build_language
        0,                               // build_script
        0,                               // build_shared
        0,                               // build_static
        &setting->path_headers,          // path_headers
        0,                               // path_headers_preserve
        &setting->path_language,         // path_language
        &setting->path_library_script,   // path_library_script
        &setting->path_library_shared,   // path_library_shared
        &setting->path_library_static,   // path_library_static
        &setting->path_program_script,   // path_program_script
        &setting->path_program_shared,   // path_program_shared
        &setting->path_program_static,   // path_program_static
        &setting->path_sources,          // path_sources
        0,                               // path_standard
        &setting->process_post,          // process_post
        &setting->process_pre,           // process_pre
        &setting->project_name,          // project_name
        0,                               // search_exclusive
        0,                               // search_shared
        0,                               // search_static
        0,                               // version_file
        &setting->version_major,         // version_major
        &setting->version_major_prefix,  // version_major_prefix
        &setting->version_micro,         // version_micro
        &setting->version_micro_prefix,  // version_micro_prefix
        &setting->version_minor,         // version_minor
        &setting->version_minor_prefix,  // version_minor_prefix
        &setting->version_nano,          // version_nano
        &setting->version_nano_prefix,   // version_nano_prefix
      };

      uint8_t * const settings_single_language[] = {
        0,                               // build_compiler
        0,                               // build_indexer
        &setting->build_language,        // build_language
      };

      uint8_t * const settings_single_version[] = {
        0,                               // build_compiler
        0,                               // build_indexer
        0,                               // build_language
        0,                               // build_script
        0,                               // build_shared
        0,                               // build_static
        0,                               // path_headers
        0,                               // path_headers_preserve
        0,                               // path_language
        0,                               // path_library_script
        0,                               // path_library_shared
        0,                               // path_library_static
        0,                               // path_program_script
        0,                               // path_program_shared
        0,                               // path_program_static
        0,                               // path_sources
        0,                               // path_standard
        0,                               // process_post
        0,                               // process_pre
        0,                               // project_name
        0,                               // search_exclusive
        0,                               // search_shared
        0,                               // search_static
        &setting->version_file,          // version_file
        0,                               // version_major
        0,                               // version_major_prefix
        0,                               // version_micro
        0,                               // version_micro_prefix
        0,                               // version_minor
        0,                               // version_minor_prefix
        0,                               // version_nano
        0,                               // version_nano_prefix
        &setting->version_target,        // version_target
      };

      const uint8_t settings_single_version_default[] = {
        0,                               // build_compiler
        0,                               // build_indexer
        0,                               // build_language
        0,                               // build_script
        0,                               // build_shared
        0,                               // build_static
        0,                               // path_headers
        0,                               // path_headers_preserve
        0,                               // path_language
        0,                               // path_library_script
        0,                               // path_library_shared
        0,                               // path_library_static
        0,                               // path_program_script
        0,                               // path_program_shared
        0,                               // path_program_static
        0,                               // path_sources
        0,                               // path_standard
        0,                               // process_post
        0,                               // process_pre
        0,                               // project_name
        0,                               // search_exclusive
        0,                               // search_shared
        0,                               // search_static
        fake_build_version_type_micro,   // version_file
        0,                               // version_major
        0,                               // version_major_prefix
        0,                               // version_micro
        0,                               // version_micro_prefix
        0,                               // version_minor
        0,                               // version_minor_prefix
        0,                               // version_nano
        0,                               // version_nano_prefix
        fake_build_version_type_major,   // version_target
      };

      const char *settings_single_version_default_name[] = {
        0,                               // build_compiler
        0,                               // build_indexer
        0,                               // build_language
        0,                               // build_script
        0,                               // build_shared
        0,                               // build_static
        0,                               // path_headers
        0,                               // path_headers_preserve
        0,                               // path_language
        0,                               // path_library_script
        0,                               // path_library_shared
        0,                               // path_library_static
        0,                               // path_program_script
        0,                               // path_program_shared
        0,                               // path_program_static
        0,                               // path_sources
        0,                               // path_standard
        0,                               // process_post
        0,                               // process_pre
        0,                               // project_name
        0,                               // search_exclusive
        0,                               // search_shared
        0,                               // search_static
        fake_build_version_micro_s,      // version_file
        0,                               // version_major
        0,                               // version_major_prefix
        0,                               // version_micro
        0,                               // version_micro_prefix
        0,                               // version_minor
        0,                               // version_minor_prefix
        0,                               // version_nano
        0,                               // version_nano_prefix
        fake_build_version_major_s,      // version_target
      };

      // 1 = "yes" or "no", 2 = path/, 3 = literal, 4 = "bash", "c", or "c++", 5 = "major", "minor", "micro", or "nano".
      const uint8_t settings_single_type[] = {
        3,                               // build_compiler
        3,                               // build_indexer
        4,                               // build_language
        1,                               // build_script
        1,                               // build_shared
        1,                               // build_static
        2,                               // path_headers
        1,                               // path_headers_preserve
        2,                               // path_language
        2,                               // path_library_script
        2,                               // path_library_shared
        2,                               // path_library_static
        2,                               // path_program_script
        2,                               // path_program_shared
        2,                               // path_program_static
        2,                               // path_sources
        1,                               // path_standard
        3,                               // process_post
        3,                               // process_pre
        3,                               // project_name
        1,                               // search_exclusive
        1,                               // search_shared
        1,                               // search_static
        5,                               // version_file
        3,                               // version_major
        3,                               // version_major_prefix
        3,                               // version_micro
        3,                               // version_micro_prefix
        3,                               // version_minor
        3,                               // version_minor_prefix
        3,                               // version_nano
        3,                               // version_nano_prefix
        5,                               // version_target
      };

      for (f_array_length_t i = 0; i < 33; ++i) {

        if (!settings_single_source[i]->used) continue;

        if (settings_single_source[i]->used > 1) {
          if (main->warning.verbosity == f_console_verbosity_verbose) {
            flockfile(main->warning.to.stream);

            fl_print_format("%c%[%SThe setting '%]", main->warning.to.stream, f_string_eol_s[0], main->warning.context, main->warning.prefix, main->warning.context);
            fl_print_format("%[%S%]", main->warning.to.stream, main->warning.notable, settings_single_name[i], main->warning.notable);
            fl_print_format("%[' in the file '%]", main->warning.to.stream, main->warning.context, main->warning.context);
            fl_print_format("%[%S%]", main->warning.to.stream, main->warning.notable, path_file, main->warning.notable);
            fl_print_format("%[' may only have a single property, only using the first: '%]", main->warning.to.stream, main->warning.context, main->warning.context);
            fl_print_format("%[%Q%]", main->warning.to.stream, main->warning.notable, settings_single_source[i]->array[0], main->warning.notable);
            fl_print_format("%['.%]%c", main->warning.to.stream, main->warning.context, main->warning.context, f_string_eol_s[0]);

            funlockfile(main->warning.to.stream);
          }
        }

        if (settings_single_type[i] == 1) {
          if (fl_string_compare_trim(settings_single_source[i]->array[0].string, fake_common_setting_bool_yes_s, settings_single_source[i]->array[0].used, fake_common_setting_bool_yes_s_length) == F_equal_to) {
            *settings_single_bool[i] = F_true;
          }
          else if (fl_string_compare_trim(settings_single_source[i]->array[0].string, fake_common_setting_bool_no_s, settings_single_source[i]->array[0].used, fake_common_setting_bool_no_s_length) == F_equal_to) {
            *settings_single_bool[i] = F_false;
          }
          else {
            *settings_single_bool[i] = F_true;

            if (main->warning.verbosity == f_console_verbosity_verbose) {
              flockfile(main->warning.to.stream);

              fl_print_format("%c%[%SThe setting '%]", main->warning.to.stream, f_string_eol_s[0], main->warning.context, main->warning.prefix, main->warning.context);
              fl_print_format("%[%S%]", main->warning.to.stream, main->warning.notable, settings_single_name[i], main->warning.notable);
              fl_print_format("%[' in the file '%]", main->warning.to.stream, main->warning.context, main->warning.context);
              fl_print_format("%[%S%]", main->warning.to.stream, main->warning.notable, path_file, main->warning.notable);
              fl_print_format("%[' may be either '%]", main->warning.to.stream, main->warning.context, main->warning.context);
              fl_print_format("%[%s%]", main->warning.to.stream, main->warning.notable, fake_common_setting_bool_yes_s, main->warning.notable);
              fl_print_format("%[' or '%]", main->warning.to.stream, main->warning.context, main->warning.context);
              fl_print_format("%[%s%]", main->warning.to.stream, main->warning.notable, fake_common_setting_bool_no_s, main->warning.notable);
              fl_print_format("%[', defaulting to '%]", main->warning.to.stream, main->warning.context, main->warning.context);
              fl_print_format("%[%s%]", main->warning.to.stream, main->warning.notable, fake_common_setting_bool_yes_s, main->warning.notable);
              fl_print_format("%['.%]%c", main->warning.to.stream, main->warning.context, main->warning.context, f_string_eol_s[0]);

              funlockfile(main->warning.to.stream);
            }
          }
        }
        else if (settings_single_type[i] == 4) {
          if (fl_string_compare_trim(settings_single_source[i]->array[0].string, fake_build_language_bash_s, settings_single_source[i]->array[0].used, fake_build_language_bash_s_length) == F_equal_to) {
            *settings_single_language[i] = fake_build_language_type_bash;
          }
          else if (fl_string_compare_trim(settings_single_source[i]->array[0].string, fake_build_language_c_s, settings_single_source[i]->array[0].used, fake_build_language_c_s_length) == F_equal_to) {
            *settings_single_language[i] = fake_build_language_type_c;
          }
          else if (fl_string_compare_trim(settings_single_source[i]->array[0].string, fake_build_language_cpp_s, settings_single_source[i]->array[0].used, fake_build_language_cpp_s_length) == F_equal_to) {
            *settings_single_language[i] = fake_build_language_type_cpp;
          }
          else {
            *settings_single_language[i] = fake_build_language_type_c;

            if (main->warning.verbosity == f_console_verbosity_verbose) {
              flockfile(main->warning.to.stream);

              fl_print_format("%c%[%SThe setting '%]", main->warning.to.stream, f_string_eol_s[0], main->warning.context, main->warning.prefix, main->warning.context);
              fl_print_format("%[%S%]", main->warning.to.stream, main->warning.notable, settings_single_name[i], main->warning.notable);
              fl_print_format("%[' in the file '%]", main->warning.to.stream, main->warning.context, main->warning.context);
              fl_print_format("%[%S%]", main->warning.to.stream, main->warning.notable, path_file, main->warning.notable);
              fl_print_format("%[' may only be one of '%]", main->warning.to.stream, main->warning.context, main->warning.context);
              fl_print_format("%[%s%]", main->warning.to.stream, main->warning.notable, fake_build_language_bash_s, main->warning.notable);
              fl_print_format("%[', '%]", main->warning.to.stream, main->warning.context, main->warning.context);
              fl_print_format("%[%s%]", main->warning.to.stream, main->warning.notable, fake_build_language_c_s, main->warning.notable);
              fl_print_format("%[', or '%]", main->warning.to.stream, main->warning.context, main->warning.context);
              fl_print_format("%[%s%]", main->warning.to.stream, main->warning.notable, fake_build_language_cpp_s, main->warning.notable);
              fl_print_format("%[', defaulting to '%]", main->warning.to.stream, main->warning.context, main->warning.context);
              fl_print_format("%[%s%]", main->warning.to.stream, main->warning.notable, fake_build_language_c_s, main->warning.notable);
              fl_print_format("%['.%]%c", main->warning.to.stream, main->warning.context, main->warning.context, f_string_eol_s[0]);

              funlockfile(main->warning.to.stream);
            }
          }
        }
        else if (settings_single_type[i] == 5) {
          if (fl_string_compare_trim(settings_single_source[i]->array[0].string, fake_build_version_major_s, settings_single_source[i]->array[0].used, fake_build_version_major_s_length) == F_equal_to) {
            *settings_single_version[i] = fake_build_version_type_major;
          }
          else if (fl_string_compare_trim(settings_single_source[i]->array[0].string, fake_build_version_minor_s, settings_single_source[i]->array[0].used, fake_build_version_minor_s_length) == F_equal_to) {
            *settings_single_version[i] = fake_build_version_type_minor;
          }
          else if (fl_string_compare_trim(settings_single_source[i]->array[0].string, fake_build_version_micro_s, settings_single_source[i]->array[0].used, fake_build_version_micro_s_length) == F_equal_to) {
            *settings_single_version[i] = fake_build_version_type_micro;
          }
          else if (fl_string_compare_trim(settings_single_source[i]->array[0].string, fake_build_version_nano_s, settings_single_source[i]->array[0].used, fake_build_version_nano_s_length) == F_equal_to) {
            *settings_single_version[i] = fake_build_version_type_nano;
          }
          else {
            *settings_single_version[i] = settings_single_version_default[i];

            if (main->warning.verbosity == f_console_verbosity_verbose) {
              flockfile(main->warning.to.stream);

              fl_print_format("%c%[%SThe setting '%]", main->warning.to.stream, f_string_eol_s[0], main->warning.context, main->warning.prefix, main->warning.context);
              fl_print_format("%[%S%]", main->warning.to.stream, main->warning.notable, settings_single_name[i], main->warning.notable);
              fl_print_format("%[' in the file '%]", main->warning.to.stream, main->warning.context, main->warning.context);
              fl_print_format("%[%S%]", main->warning.to.stream, main->warning.notable, path_file, main->warning.notable);
              fl_print_format("%[' may only be one of '%]", main->warning.to.stream, main->warning.context, main->warning.context);
              fl_print_format("%[%s%]", main->warning.to.stream, main->warning.notable, fake_build_version_major_s, main->warning.notable);
              fl_print_format("%[', '%]", main->warning.to.stream, main->warning.context, main->warning.context);
              fl_print_format("%[%s%]", main->warning.to.stream, main->warning.notable, fake_build_version_minor_s, main->warning.notable);
              fl_print_format("%[', '%]", main->warning.to.stream, main->warning.context, main->warning.context);
              fl_print_format("%[%s%]", main->warning.to.stream, main->warning.notable, fake_build_version_micro_s, main->warning.notable);
              fl_print_format("%[', or '%]", main->warning.to.stream, main->warning.context, main->warning.context);
              fl_print_format("%[%s%]", main->warning.to.stream, main->warning.notable, fake_build_version_nano_s, main->warning.notable);
              fl_print_format("%[', defaulting to '%]", main->warning.to.stream, main->warning.context, main->warning.context);
              fl_print_format("%[%s%]", main->warning.to.stream, main->warning.notable, settings_single_version_default_name[i], main->warning.notable);
              fl_print_format("%['.%]%c", main->warning.to.stream, main->warning.context, main->warning.context, f_string_eol_s[0]);

              funlockfile(main->warning.to.stream);
            }
          }
        }
        else {

          // Replace any potential existing value.
          settings_single_destination[i]->used = 0;

          *status = f_string_dynamic_append_nulless(settings_single_source[i]->array[0], settings_single_destination[i]);

          if (F_status_is_error(*status)) {
            fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_append_nulless", F_true);

            break;
          }

          if (settings_single_type[i] == 2) {
            *status = f_string_append_assure(f_path_separator_s, F_path_separator_s_length, settings_single_destination[i]);

            if (F_status_is_error(*status)) {
              fll_error_print(main->error, F_status_set_fine(*status), "f_string_append_assure", F_true);

              break;
            }
          }

          *status = f_string_dynamic_terminate_after(settings_single_destination[i]);
          if (F_status_is_error(*status)) {
            fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_terminate_after", F_true);

            break;
          }
        }
      } // for

      if (F_status_is_error_not(*status)) {
        if (checks && !setting->version_file) {
          setting->version_file = fake_build_version_type_micro;

          if (main->warning.verbosity == f_console_verbosity_verbose) {
            flockfile(main->warning.to.stream);

            fl_print_format("%c%[%SThe setting '%]", main->warning.to.stream, f_string_eol_s[0], main->warning.context, main->warning.prefix, main->warning.context);
            fl_print_format("%[%S%]", main->warning.to.stream, main->warning.notable, fake_build_setting_name_version_file_s, main->warning.notable);
            fl_print_format("%[' in the file '%]", main->warning.to.stream, main->warning.context, main->warning.context);
            fl_print_format("%[%S%]", main->warning.to.stream, main->warning.notable, path_file, main->warning.notable);
            fl_print_format("%[' is required, defaulting to '%]", main->warning.to.stream, main->warning.context, main->warning.context);
            fl_print_format("%[%s%]", main->warning.to.stream, main->warning.notable, fake_build_version_micro_s, main->warning.notable);
            fl_print_format("%['.%]%c", main->warning.to.stream, main->warning.context, main->warning.context, f_string_eol_s[0]);

            funlockfile(main->warning.to.stream);
          }
        }

        if (checks && !setting->version_target) {
          setting->version_target = fake_build_version_type_major;

          if (main->warning.verbosity == f_console_verbosity_verbose) {
            flockfile(main->warning.to.stream);

            fl_print_format("%c%[%SThe setting '%]", main->warning.to.stream, f_string_eol_s[0], main->warning.context, main->warning.prefix, main->warning.context);
            fl_print_format("%[%S%]", main->warning.to.stream, main->warning.notable, fake_build_setting_name_version_target_s, main->warning.notable);
            fl_print_format("%[' in the file '%]", main->warning.to.stream, main->warning.context, main->warning.context);
            fl_print_format("%[%S%]", main->warning.to.stream, main->warning.notable, path_file, main->warning.notable);
            fl_print_format("%[' is required, defaulting to '%]", main->warning.to.stream, main->warning.context, main->warning.context);
            fl_print_format("%[%s%]", main->warning.to.stream, main->warning.notable, fake_build_version_major_s, main->warning.notable);
            fl_print_format("%['.%]%c", main->warning.to.stream, main->warning.context, main->warning.context, f_string_eol_s[0]);

            funlockfile(main->warning.to.stream);
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
          settings_matches[61], // version_major_prefix
          settings_matches[63], // version_minor_prefix
          settings_matches[65], // version_micro_prefix
          settings_matches[67], // version_nano_prefix
        };

        const char *name_target[] = {
          fake_build_version_major_s,
          fake_build_version_minor_s,
          fake_build_version_micro_s,
          fake_build_version_nano_s,
        };

        const char *name_object[] = {
          fake_build_setting_name_version_major_s,
          fake_build_setting_name_version_minor_s,
          fake_build_setting_name_version_micro_s,
          fake_build_setting_name_version_nano_s,
        };

        const char *setting_name[] = {
          fake_build_setting_name_version_file_s,
          fake_build_setting_name_version_target_s,
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

              *status = f_string_append(fake_build_setting_default_version_prefix_s, fake_build_setting_default_version_prefix_s_length, prefix[i]);

              if (F_status_is_error(*status)) {
                fll_error_print(main->error, F_status_set_fine(*status), "f_string_append", F_true);
                break;
              }
            }
          }
          else if (checks) {
            prefix[i]->used = 0;

            for (j = 0; j < 2; ++j) {

              if (setting_target[j] && i + 1 <= setting_target[j]) {
                if (main->error.verbosity != f_console_verbosity_quiet) {
                  flockfile(main->error.to.stream);

                  fl_print_format("%c%[%SWhen the '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
                  fl_print_format("%[%S%]", main->error.to.stream, main->error.notable, setting_name[j], main->error.notable);
                  fl_print_format("%[' is set to '%]", main->error.to.stream, main->error.context, main->error.context);
                  fl_print_format("%[%S%]", main->error.to.stream, main->error.notable, name_target[setting_target[j] - 1], main->error.notable);
                  fl_print_format("%[' then the '%]", main->error.to.stream, main->error.context, main->error.context);
                  fl_print_format("%[%S%]", main->error.to.stream, main->error.notable, name_object[i], main->error.notable);
                  fl_print_format("%[' Object must have Content.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

                  funlockfile(main->error.to.stream);
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
  void fake_build_load_setting_defaults(fake_main_t * const main, fake_build_setting_t *setting, f_status_t *status) {

    if (F_status_is_error(*status)) return;

    if (fake_signal_received(main)) {
      *status = F_status_set_error(F_interrupt);

      return;
    }

    {
      const f_string_t sources[] = {
        fake_build_setting_default_version_s,
        fake_build_setting_default_version_s,
        fake_build_setting_default_version_s,
      };

      const f_array_length_t lengths[] = {
        fake_build_setting_default_version_s_length,
        fake_build_setting_default_version_s_length,
        fake_build_setting_default_version_s_length,
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
          fll_error_print(main->error, F_status_set_fine(*status), "f_string_append_assure", F_true);
          break;
        }

        *status = f_string_dynamic_terminate_after(destinations[i]);

        if (F_status_is_error(*status)) {
          fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_terminate_after", F_true);
          break;
        }
      } // for
    }

    if (F_status_is_error(*status)) return;

    // Override setting file when any of these are specified in the command line.
    if (main->parameters[fake_parameter_shared_disabled].result == f_console_result_found) {
      if (main->parameters[fake_parameter_shared_enabled].result == f_console_result_found) {
        if (main->parameters[fake_parameter_shared_enabled].location > main->parameters[fake_parameter_shared_disabled].location) {
          setting->build_shared = F_true;
          setting->search_shared = F_true;
        }
        else {
          setting->build_shared = F_false;
          setting->search_shared = F_false;
        }

        if (main->error.verbosity != f_console_verbosity_quiet) {
          flockfile(main->error.to.stream);

          fl_print_format("%c%[%SThe parameters '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fake_long_shared_disabled_s, main->error.notable);
          fl_print_format("%[' and '%]", main->error.to.stream, main->error.context, main->error.context);
          fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fake_long_shared_enabled_s, main->error.notable);
          fl_print_format("%[' contradict, defaulting to '%]", main->error.to.stream, main->error.context, main->error.context);
          fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, setting->build_shared ? fake_long_shared_enabled_s : fake_long_shared_disabled_s, main->error.notable);
          fl_print_format("%['.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

          funlockfile(main->error.to.stream);
        }
      }
      else {
        setting->build_shared = F_false;
        setting->search_shared = F_false;
      }
    }
    else if (main->parameters[fake_parameter_shared_enabled].result == f_console_result_found) {
      setting->build_shared = F_true;
      setting->search_shared = F_true;
    }

    if (main->parameters[fake_parameter_static_disabled].result == f_console_result_found) {
      if (main->parameters[fake_parameter_static_enabled].result == f_console_result_found) {
        if (main->parameters[fake_parameter_static_enabled].location > main->parameters[fake_parameter_static_disabled].location) {
          setting->build_static = F_true;
          setting->search_static = F_true;
        }
        else {
          setting->build_static = F_false;
          setting->search_static = F_false;
        }

        if (main->error.verbosity == f_console_verbosity_verbose) {
          flockfile(main->error.to.stream);

          fl_print_format("%c%[%SThe parameters '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fake_long_static_disabled_s, main->error.notable);
          fl_print_format("%[' and '%]", main->error.to.stream, main->error.context, main->error.context);
          fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fake_long_static_enabled_s, main->error.notable);
          fl_print_format("%[' contradict, defaulting to '%]", main->error.to.stream, main->error.context, main->error.context);
          fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, setting->build_static ? fake_long_static_enabled_s : fake_long_static_disabled_s, main->error.notable);
          fl_print_format("%['.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

          funlockfile(main->error.to.stream);
        }
      }
      else {
        setting->build_static = F_false;
        setting->search_static = F_false;
      }
    }
    else if (main->parameters[fake_parameter_static_enabled].result == f_console_result_found) {
      setting->build_static = F_true;
      setting->search_static = F_true;
    }

    if (setting->build_language == fake_build_language_type_c || setting->build_language == fake_build_language_type_cpp) {
      if (setting->build_shared == F_false && setting->build_static == F_false) {
        if (main->error.verbosity != f_console_verbosity_quiet) {
          flockfile(main->error.to.stream);

          fl_print_format("%c%[%SThe build settings '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%s%]", main->error.to.stream, main->error.notable, fake_build_setting_name_build_shared_s, main->error.notable);
          fl_print_format("%[' and '%]", main->error.to.stream, main->error.context, main->error.context);
          fl_print_format("%[%s%]", main->error.to.stream, main->error.notable, fake_build_setting_name_build_static_s, main->error.notable);
          fl_print_format("%[' cannot both be false when using the language '%]", main->error.to.stream, main->error.context, main->error.context);
          fl_print_format("%[%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, setting->build_language == fake_build_language_type_c ? fake_build_language_c_s : fake_build_language_cpp_s, main->error.notable);
          fl_print_format("%['.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

          funlockfile(main->error.to.stream);
        }

        *status = F_status_set_error(F_failure);
      }
    }
  }
#endif // _di_fake_build_load_setting_defaults_

#ifndef _di_fake_build_load_stage_
  void fake_build_load_stage(fake_main_t * const main, const f_string_static_t settings_file, fake_build_stage_t *stage, f_status_t *status) {

    if (F_status_is_error(*status)) return;

    if (fake_signal_received(main)) {
      *status = F_status_set_error(F_interrupt);

      return;
    }

    const f_string_t names[] = {
      fake_build_stage_libraries_script_s,
      fake_build_stage_libraries_shared_s,
      fake_build_stage_libraries_static_s,
      fake_build_stage_objects_static_s,
      fake_build_stage_process_post_s,
      fake_build_stage_process_pre_s,
      fake_build_stage_programs_script_s,
      fake_build_stage_programs_shared_s,
      fake_build_stage_programs_static_s,
      fake_build_stage_skeleton_s,
      fake_build_stage_sources_headers_s,
      fake_build_stage_sources_script_s,
      fake_build_stage_sources_settings_s,
    };

    const f_array_length_t lengths[] = {
      fake_build_stage_libraries_script_s_length,
      fake_build_stage_libraries_shared_s_length,
      fake_build_stage_libraries_static_s_length,
      fake_build_stage_objects_static_s_length,
      fake_build_stage_process_post_s_length,
      fake_build_stage_process_pre_s_length,
      fake_build_stage_programs_script_s_length,
      fake_build_stage_programs_shared_s_length,
      fake_build_stage_programs_static_s_length,
      fake_build_stage_skeleton_s_length,
      fake_build_stage_sources_headers_s_length,
      fake_build_stage_sources_script_s_length,
      fake_build_stage_sources_settings_s_length,
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
      *status = f_file_name_base(main->file_data_build_settings.string, main->file_data_build_settings.used, &settings_file_base);
    }

    if (F_status_is_error(*status)) {
      fll_error_print(main->error, F_status_set_fine(*status), "f_file_name_base", F_true);

      return;
    }

    for (uint8_t i = 0; i < fake_build_stage_total_d; ++i) {

      *status = f_string_dynamic_append_nulless(main->path_build_stage, values[i]);

      if (F_status_is_error(*status)) {
        fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_append_nulless", F_true);

        break;
      }

      if (main->process.used) {
        *status = f_string_append(main->process.string, main->process.used, values[i]);

        if (F_status_is_error(*status)) {
          fll_error_print(main->error, F_status_set_fine(*status), "f_string_append", F_true);

          break;
        }

        *status = f_string_append(fake_build_stage_separate_s, fake_build_stage_separate_s_length, values[i]);

        if (F_status_is_error(*status)) {
          fll_error_print(main->error, F_status_set_fine(*status), "f_string_append", F_true);

          break;
        }
      }

      *status = f_string_append_nulless(names[i], lengths[i], values[i]);

      if (F_status_is_error(*status)) {
        fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_append_nulless", F_true);

        break;
      }

      *status = f_string_append(fake_build_stage_separate_s, fake_build_stage_separate_s_length, values[i]);

      if (F_status_is_error(*status)) {
        fll_error_print(main->error, F_status_set_fine(*status), "f_string_append", F_true);

        break;
      }

      *status = f_string_dynamic_append(settings_file_base, values[i]);

      if (F_status_is_error(*status)) {
        fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_append", F_true);

        break;
      }

      *status = f_string_append(fake_build_stage_built_s, fake_build_stage_built_s_length, values[i]);

      if (F_status_is_error(*status)) {
        fll_error_print(main->error, F_status_set_fine(*status), "f_string_append", F_true);

        break;
      }

      *status = f_string_dynamic_terminate_after(values[i]);

      if (F_status_is_error(*status)) {
        fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_terminate_after", F_true);

        break;
      }
    } // for

    macro_f_string_dynamic_t_delete_simple(settings_file_base);
  }
#endif // _di_fake_build_load_stage_

#ifdef __cplusplus
} // extern "C"
#endif
