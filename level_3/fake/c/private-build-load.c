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
  void fake_build_load_environment(fake_main_t * const main, fake_build_data_t * const data_build, f_string_maps_t * const environment, f_status_t * const status) {

    if (F_status_is_error(*status)) return;

    // Reset the environment.
    for (f_array_length_t i = 0; i < environment->used; ++i) {
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

        *status = fl_environment_load_name(variables[i], environment);

        if (F_status_is_error(*status)) {
          fll_error_print(main->error, F_status_set_fine(*status), "fl_environment_load_name", F_true);

          return;
        }
      } // for
    }

    if (environment->used + data_build->setting.environment.used > environment->size) {
      if (environment->used + data_build->setting.environment.used > f_environment_max_length) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          flockfile(main->error.to.stream);

          fl_print_format("%r%[%QThe values for the setting '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%]", main->error.to.stream, main->error.notable, fake_build_setting_name_environment_s, main->error.notable);
          fl_print_format("%[' of setting file '%]", main->error.to.stream, main->error.context, main->error.context);
          fl_print_format("%[%r%]", main->error.to.stream, main->error.notable, fake_build_setting_name_environment_s, main->error.notable);
          fl_print_format("%[' is too large.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          flockfile(main->error.to.stream);
        }

        *status = F_status_set_error(F_array_too_large);

        return;
      }
    }

    *status = fl_environment_load_names(data_build->setting.environment, environment);

    if (F_status_is_error(*status)) {
      fll_error_print(main->error, F_status_set_fine(*status), "fl_environment_load_names", F_true);
    }
  }
#endif // _di_fake_build_load_environment_

#ifndef _di_fake_build_load_setting_
  void fake_build_load_setting(fake_main_t * const main, const f_string_static_t setting_file, fake_build_setting_t * const setting, f_status_t * const status) {

    if (F_status_is_error(*status)) return;

    if (fake_signal_received(main)) {
      *status = F_status_set_error(F_interrupt);

      return;
    }

    f_string_static_t path_file = f_string_static_t_initialize;
    path_file.used = main->path_data_build.used + setting_file.used;

    char path_file_string[path_file.used + 1];
    path_file.string = path_file_string;
    path_file_string[path_file.used] = 0;

    {
      f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

      f_fss_objects_t objects = f_fss_objects_t_initialize;
      f_fss_contents_t contents = f_fss_contents_t_initialize;

      if (setting_file.used) {
        memcpy(path_file_string, main->path_data_build.string, main->path_data_build.used);
        memcpy(path_file_string + main->path_data_build.used, setting_file.string, setting_file.used);

        *status = fake_file_buffer(main, path_file, &buffer);
      }
      else {
        *status = fake_file_buffer(main, main->file_data_build_settings, &buffer);
      }

      if (F_status_is_error_not(*status)) {
        f_string_range_t range = macro_f_string_range_t_initialize(buffer.used);
        f_fss_delimits_t delimits = f_fss_delimits_t_initialize;

        {
          f_state_t state = macro_f_state_t_initialize(fake_common_allocation_large_d, fake_common_allocation_small_d, 0, &fake_signal_state_interrupt_fss, 0, (void *) main, 0);

          *status = fll_fss_extended_read(buffer, state, &range, &objects, &contents, 0, 0, &delimits, 0);
        }

        if (F_status_is_error(*status)) {
          fake_print_error_fss(main, F_status_set_fine(*status), "fll_fss_extended_read", main->file_data_build_settings, range, F_true);
        }
        else {
          *status = fl_fss_apply_delimit(delimits, &buffer);

          if (F_status_is_error(*status)) {
            fll_error_print(main->error, F_status_set_fine(*status), "fl_fss_apply_delimit", F_true);
          }
          else {
            fake_build_load_setting_process(main, F_true, setting_file.used ? path_file : main->file_data_build_settings, buffer, objects, contents, setting, status);
          }
        }

        macro_f_fss_delimits_t_delete_simple(delimits);
      }

      f_string_dynamic_resize(0, &buffer);

      macro_f_fss_objects_t_delete_simple(objects);
      macro_f_fss_contents_t_delete_simple(contents);
    }

    // Error when required settings are not specified.
    if (F_status_is_error_not(*status)) {
      bool failed = F_false;

      f_string_static_t * const settings[] = {
        &setting->build_name,
      };

      f_string_static_t names[] = {
        fake_build_setting_name_build_name_s,
      };

      for (uint8_t i = 0; i < 1; ++i) {

        if (!settings[i]->used) {
          flockfile(main->error.to.stream);

          fl_print_format("%r%[%QThe setting '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, names[i], main->error.notable);
          fl_print_format("%[' is required but is not specified in the settings file '%]", main->error.to.stream, main->error.context, main->error.context);
          fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, setting_file.used ? path_file : main->file_data_build_settings, main->error.notable);
          fl_print_format("%['.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          funlockfile(main->error.to.stream);

          failed = F_true;
        }
      } // for

      if (failed) {
        *status = F_status_set_error(F_failure);

        return;
      }
    }

    fake_build_load_setting_override(main, setting, status);
  }
#endif // _di_fake_build_load_setting_

#ifndef _di_fake_build_load_setting_process_
  void fake_build_load_setting_process(fake_main_t * const main, const bool checks, const f_string_static_t path_file, const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, fake_build_setting_t * const setting, f_status_t * const status) {

    if (F_status_is_error(*status) && buffer.used) return;

    if (fake_signal_received(main)) {
      *status = F_status_set_error(F_interrupt);

      return;
    }

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
      fake_build_setting_name_build_sources_settings_s,
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

    *status = fll_fss_snatch_apart(buffer, objects, contents, settings_name, fake_build_setting_total_d, settings_value, settings_matches, 0);

    if (*status == F_none) {
      const int total_build_libraries = setting->build_libraries.used;
      const f_string_dynamics_t *modes = &setting->modes_default;

      f_string_dynamic_t settings_mode_names[fake_build_setting_total_d];

      memset(settings_mode_names, 0, sizeof(f_string_dynamic_t) * fake_build_setting_total_d);

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
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            flockfile(main->error.to.stream);

            fl_print_format("%r%[%QThe specified mode '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, modes->array[i], main->error.notable);
            fl_print_format("%[' is not a valid mode, according to '%]", main->error.to.stream, main->error.context, main->error.context);
            fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, path_file, main->error.notable);
            fl_print_format("%['.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

            funlockfile(main->error.to.stream);
          }

          error_printed = F_true;
          *status = F_status_set_error(F_parameter);

          break;
        }

        for (j = 0; j < fake_build_setting_total_d; ++j) {

          settings_mode_names[j].used = 0;

          *status = f_string_dynamic_increase_by(settings_value[j]->used + f_string_ascii_minus_s.used + modes->array[i].used, &settings_mode_names[j]);

          if (F_status_is_error(*status)) {
            function = "f_string_dynamic_increase_by";

            break;
          }

          *status = f_string_dynamic_append(settings_name[j], &settings_mode_names[j]);

          if (F_status_is_error_not(*status)) {
            *status = f_string_dynamic_append(f_string_ascii_minus_s, &settings_mode_names[j]);
          }

          if (F_status_is_error_not(*status)) {
            *status = f_string_dynamic_append(modes->array[i], &settings_mode_names[j]);
          }

          if (F_status_is_error(*status)) {
            function = "f_string_dynamic_append";

            break;
          }
        } // for

        if (*status == F_none) {
          *status = fll_fss_snatch_apart(buffer, objects, contents, settings_mode_names, fake_build_setting_total_d, settings_value, 0, 0);

          if (F_status_is_error(*status)) {
            function = "fll_fss_snatch_apart";
          }
        }

        if (F_status_is_error(*status)) break;
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

    if (F_status_is_error(*status)) {
      if (*status == F_status_set_error(F_string_too_large)) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          funlockfile(main->error.to.stream);

          fl_print_format("%r%[%QA setting in the file '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, path_file, main->error.notable);
          fl_print_format("%[' is too long.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          funlockfile(main->error.to.stream);
        }
      }
      else if (!error_printed) {
        fll_error_print(main->error, F_status_set_fine(*status), function, F_true);
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
        fake_default_path_sources_s,                 // path_sources
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

      const uint8_t settings_single_version_default[] = {
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
        fake_build_version_type_micro_e,             // version_file
        0,                                           // version_major
        0,                                           // version_major_prefix
        0,                                           // version_micro
        0,                                           // version_micro_prefix
        0,                                           // version_minor
        0,                                           // version_minor_prefix
        0,                                           // version_nano
        0,                                           // version_nano_prefix
        fake_build_version_type_major_e,             // version_target
      };

      const f_string_static_t settings_single_version_default_name[] = {
        f_string_empty_s,                            // build_compiler
        f_string_empty_s,                            // build_indexer
        f_string_empty_s,                            // build_language
        f_string_empty_s,                            // build_name
        f_string_empty_s,                            // build_script
        f_string_empty_s,                            // build_shared
        f_string_empty_s,                            // build_sources_object
        f_string_empty_s,                            // build_sources_object_shared
        f_string_empty_s,                            // build_sources_object_static
        f_string_empty_s,                            // build_static
        f_string_empty_s,                            // has_path_standard
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
        f_string_empty_s,                            // preserve_path_headers
        f_string_empty_s,                            // process_post
        f_string_empty_s,                            // process_pre
        f_string_empty_s,                            // search_exclusive
        f_string_empty_s,                            // search_shared
        f_string_empty_s,                            // search_static
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
      const uint8_t settings_single_type[] = {
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

      for (f_array_length_t i = 0; i < 40; ++i) {

        // Assign the default for literal and path types.
        if (settings_single_string_default[i].used && settings_single_destination[i]) {
          settings_single_destination[i]->used = 0;

          *status = f_string_dynamic_append(settings_single_string_default[i], settings_single_destination[i]);

          if (F_status_is_error(*status)) {
            fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_append", F_true);

            break;
          }
        }

        if (!settings_single_source[i]->used) continue;

        if (settings_single_type[i] == 1) {
          if (fl_string_dynamic_compare_trim(settings_single_source[i]->array[settings_single_source[i]->used - 1], fake_common_setting_bool_yes_s) == F_equal_to) {
            *settings_single_bool[i] = F_true;
          }
          else if (fl_string_dynamic_compare_trim(settings_single_source[i]->array[settings_single_source[i]->used - 1], fake_common_setting_bool_no_s) == F_equal_to) {
            *settings_single_bool[i] = F_false;
          }
          else {
            *settings_single_bool[i] = F_true;

            if (main->warning.verbosity >= f_console_verbosity_verbose_e) {
              flockfile(main->warning.to.stream);

              fl_print_format("%r%[%QThe setting '%]", main->warning.to.stream, f_string_eol_s, main->warning.context, main->warning.prefix, main->warning.context);
              fl_print_format("%[%r%]", main->warning.to.stream, main->warning.notable, settings_single_name[i], main->warning.notable);
              fl_print_format("%[' in the file '%]", main->warning.to.stream, main->warning.context, main->warning.context);
              fl_print_format("%[%Q%]", main->warning.to.stream, main->warning.notable, path_file, main->warning.notable);
              fl_print_format("%[' may be either '%]", main->warning.to.stream, main->warning.context, main->warning.context);
              fl_print_format("%[%r%]", main->warning.to.stream, main->warning.notable, fake_common_setting_bool_yes_s, main->warning.notable);
              fl_print_format("%[' or '%]", main->warning.to.stream, main->warning.context, main->warning.context);
              fl_print_format("%[%r%]", main->warning.to.stream, main->warning.notable, fake_common_setting_bool_no_s, main->warning.notable);
              fl_print_format("%[', defaulting to '%]", main->warning.to.stream, main->warning.context, main->warning.context);
              fl_print_format("%[%r%]", main->warning.to.stream, main->warning.notable, fake_common_setting_bool_yes_s, main->warning.notable);
              fl_print_format("%['.%]%r", main->warning.to.stream, main->warning.context, main->warning.context, f_string_eol_s);

              funlockfile(main->warning.to.stream);
            }
          }
        }
        else if (settings_single_type[i] == 4) {
          if (fl_string_dynamic_compare_trim(settings_single_source[i]->array[settings_single_source[i]->used - 1], fake_build_language_bash_s) == F_equal_to) {
            *settings_single_language[i] = fake_build_language_type_bash_e;
          }
          else if (fl_string_dynamic_compare_trim(settings_single_source[i]->array[settings_single_source[i]->used - 1], fake_build_language_c_s) == F_equal_to) {
            *settings_single_language[i] = fake_build_language_type_c_e;
          }
          else if (fl_string_dynamic_compare_trim(settings_single_source[i]->array[settings_single_source[i]->used - 1], fake_build_language_cpp_s) == F_equal_to) {
            *settings_single_language[i] = fake_build_language_type_cpp_e;
          }
          else {
            *settings_single_language[i] = fake_build_language_type_c_e;

            if (main->warning.verbosity >= f_console_verbosity_verbose_e) {
              flockfile(main->warning.to.stream);

              fl_print_format("%r%[%QThe setting '%]", main->warning.to.stream, f_string_eol_s, main->warning.context, main->warning.prefix, main->warning.context);
              fl_print_format("%[%r%]", main->warning.to.stream, main->warning.notable, settings_single_name[i], main->warning.notable);
              fl_print_format("%[' in the file '%]", main->warning.to.stream, main->warning.context, main->warning.context);
              fl_print_format("%[%Q%]", main->warning.to.stream, main->warning.notable, path_file, main->warning.notable);
              fl_print_format("%[' may only be one of '%]", main->warning.to.stream, main->warning.context, main->warning.context);
              fl_print_format("%[%r%]", main->warning.to.stream, main->warning.notable, fake_build_language_bash_s, main->warning.notable);
              fl_print_format("%[', '%]", main->warning.to.stream, main->warning.context, main->warning.context);
              fl_print_format("%[%r%]", main->warning.to.stream, main->warning.notable, fake_build_language_c_s, main->warning.notable);
              fl_print_format("%[', or '%]", main->warning.to.stream, main->warning.context, main->warning.context);
              fl_print_format("%[%r%]", main->warning.to.stream, main->warning.notable, fake_build_language_cpp_s, main->warning.notable);
              fl_print_format("%[', defaulting to '%]", main->warning.to.stream, main->warning.context, main->warning.context);
              fl_print_format("%[%r%]", main->warning.to.stream, main->warning.notable, fake_build_language_c_s, main->warning.notable);
              fl_print_format("%['.%]%r", main->warning.to.stream, main->warning.context, main->warning.context, f_string_eol_s);

              funlockfile(main->warning.to.stream);
            }
          }
        }
        else if (settings_single_type[i] == 5) {
          if (fl_string_dynamic_compare_trim(settings_single_source[i]->array[settings_single_source[i]->used - 1], fake_build_version_major_s) == F_equal_to) {
            *settings_single_version[i] = fake_build_version_type_major_e;
          }
          else if (fl_string_dynamic_compare_trim(settings_single_source[i]->array[settings_single_source[i]->used - 1], fake_build_version_minor_s) == F_equal_to) {
            *settings_single_version[i] = fake_build_version_type_minor_e;
          }
          else if (fl_string_dynamic_compare_trim(settings_single_source[i]->array[settings_single_source[i]->used - 1], fake_build_version_micro_s) == F_equal_to) {
            *settings_single_version[i] = fake_build_version_type_micro_e;
          }
          else if (fl_string_dynamic_compare_trim(settings_single_source[i]->array[settings_single_source[i]->used - 1], fake_build_version_nano_s) == F_equal_to) {
            *settings_single_version[i] = fake_build_version_type_nano_e;
          }
          else {
            *settings_single_version[i] = settings_single_version_default[i];

            if (main->warning.verbosity >= f_console_verbosity_verbose_e) {
              flockfile(main->warning.to.stream);

              fl_print_format("%r%[%QThe setting '%]", main->warning.to.stream, f_string_eol_s, main->warning.context, main->warning.prefix, main->warning.context);
              fl_print_format("%[%r%]", main->warning.to.stream, main->warning.notable, settings_single_name[i], main->warning.notable);
              fl_print_format("%[' in the file '%]", main->warning.to.stream, main->warning.context, main->warning.context);
              fl_print_format("%[%Q%]", main->warning.to.stream, main->warning.notable, path_file, main->warning.notable);
              fl_print_format("%[' may only be one of '%]", main->warning.to.stream, main->warning.context, main->warning.context);
              fl_print_format("%[%r%]", main->warning.to.stream, main->warning.notable, fake_build_version_major_s, main->warning.notable);
              fl_print_format("%[', '%]", main->warning.to.stream, main->warning.context, main->warning.context);
              fl_print_format("%[%r%]", main->warning.to.stream, main->warning.notable, fake_build_version_minor_s, main->warning.notable);
              fl_print_format("%[', '%]", main->warning.to.stream, main->warning.context, main->warning.context);
              fl_print_format("%[%r%]", main->warning.to.stream, main->warning.notable, fake_build_version_micro_s, main->warning.notable);
              fl_print_format("%[', or '%]", main->warning.to.stream, main->warning.context, main->warning.context);
              fl_print_format("%[%r%]", main->warning.to.stream, main->warning.notable, fake_build_version_nano_s, main->warning.notable);
              fl_print_format("%[', defaulting to '%]", main->warning.to.stream, main->warning.context, main->warning.context);
              fl_print_format("%[%r%]", main->warning.to.stream, main->warning.notable, settings_single_version_default_name[i], main->warning.notable);
              fl_print_format("%['.%]%r", main->warning.to.stream, main->warning.context, main->warning.context, f_string_eol_s);

              funlockfile(main->warning.to.stream);
            }
          }
        }
        else if (settings_single_destination[i]) {

          // Replace any potential existing value.
          settings_single_destination[i]->used = 0;

          if (settings_single_type[i] == 2) {
            *status = f_path_directory_cleanup(settings_single_source[i]->array[settings_single_source[i]->used - 1], settings_single_destination[i]);

            if (F_status_is_error(*status)) {
              fll_error_print(main->error, F_status_set_fine(*status), "f_path_directory_cleanup", F_true);

              break;
            }
          }
          else {
            *status = f_string_dynamic_increase_by(settings_single_source[i]->array[settings_single_source[i]->used - 1].used + 1, settings_single_destination[i]);

            if (F_status_is_error(*status)) {
              fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_increase_by", F_true);

              break;
            }

            *status = f_string_dynamic_append_nulless(settings_single_source[i]->array[settings_single_source[i]->used - 1], settings_single_destination[i]);

            if (F_status_is_error(*status)) {
              fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_append_nulless", F_true);

              break;
            }
          }
        }
      } // for

      if (F_status_is_error_not(*status)) {
        if (checks && !setting->version_file) {
          setting->version_file = fake_build_version_type_micro_e;

          if (main->warning.verbosity >= f_console_verbosity_verbose_e) {
            flockfile(main->warning.to.stream);

            fl_print_format("%r%[%QThe setting '%]", main->warning.to.stream, f_string_eol_s, main->warning.context, main->warning.prefix, main->warning.context);
            fl_print_format("%[%r%]", main->warning.to.stream, main->warning.notable, fake_build_setting_name_version_file_s, main->warning.notable);
            fl_print_format("%[' in the file '%]", main->warning.to.stream, main->warning.context, main->warning.context);
            fl_print_format("%[%Q%]", main->warning.to.stream, main->warning.notable, path_file, main->warning.notable);
            fl_print_format("%[' is required, defaulting to '%]", main->warning.to.stream, main->warning.context, main->warning.context);
            fl_print_format("%[%r%]", main->warning.to.stream, main->warning.notable, fake_build_version_micro_s, main->warning.notable);
            fl_print_format("%['.%]%r", main->warning.to.stream, main->warning.context, main->warning.context, f_string_eol_s);

            funlockfile(main->warning.to.stream);
          }
        }

        if (checks && !setting->version_target) {
          setting->version_target = fake_build_version_type_major_e;

          if (main->warning.verbosity >= f_console_verbosity_verbose_e) {
            flockfile(main->warning.to.stream);

            fl_print_format("%r%[%QThe setting '%]", main->warning.to.stream, f_string_eol_s, main->warning.context, main->warning.prefix, main->warning.context);
            fl_print_format("%[%r%]", main->warning.to.stream, main->warning.notable, fake_build_setting_name_version_target_s, main->warning.notable);
            fl_print_format("%[' in the file '%]", main->warning.to.stream, main->warning.context, main->warning.context);
            fl_print_format("%[%Q%]", main->warning.to.stream, main->warning.notable, path_file, main->warning.notable);
            fl_print_format("%[' is required, defaulting to '%]", main->warning.to.stream, main->warning.context, main->warning.context);
            fl_print_format("%[%r%]", main->warning.to.stream, main->warning.notable, fake_build_version_major_s, main->warning.notable);
            fl_print_format("%['.%]%r", main->warning.to.stream, main->warning.context, main->warning.context, f_string_eol_s);

            funlockfile(main->warning.to.stream);
          }
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
  void fake_build_load_setting_override(fake_main_t * const main, fake_build_setting_t * const setting, f_status_t * const status) {

    if (F_status_is_error(*status)) return;

    if (main->parameters.array[fake_parameter_path_sources_e].result == f_console_result_additional_e && main->path_sources.used) {
      *status = f_string_dynamic_append_assure(f_path_separator_s, &main->path_sources);

      if (F_status_is_error(*status)) {
        fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_append_assure", F_true);

        return;
      }
    }

    if (main->parameters.array[fake_parameter_shared_disabled_e].result == f_console_result_found_e) {
      if (main->parameters.array[fake_parameter_shared_enabled_e].result == f_console_result_found_e) {
        if (main->parameters.array[fake_parameter_shared_enabled_e].location > main->parameters.array[fake_parameter_shared_disabled_e].location) {
          setting->build_shared = F_true;
          setting->search_shared = F_true;
        }
        else {
          setting->build_shared = F_false;
          setting->search_shared = F_false;
        }

        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          flockfile(main->error.to.stream);

          fl_print_format("%r%[%QThe parameters '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fake_long_shared_disabled_s, main->error.notable);
          fl_print_format("%[' and '%]", main->error.to.stream, main->error.context, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fake_long_shared_enabled_s, main->error.notable);
          fl_print_format("%[' contradict, defaulting to '%]", main->error.to.stream, main->error.context, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, setting->build_shared ? fake_long_shared_enabled_s : fake_long_shared_disabled_s, main->error.notable);
          fl_print_format("%['.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          funlockfile(main->error.to.stream);
        }
      }
      else {
        setting->build_shared = F_false;
        setting->search_shared = F_false;
      }
    }
    else if (main->parameters.array[fake_parameter_shared_enabled_e].result == f_console_result_found_e) {
      setting->build_shared = F_true;
      setting->search_shared = F_true;
    }

    if (main->parameters.array[fake_parameter_static_disabled_e].result == f_console_result_found_e) {
      if (main->parameters.array[fake_parameter_static_enabled_e].result == f_console_result_found_e) {
        if (main->parameters.array[fake_parameter_static_enabled_e].location > main->parameters.array[fake_parameter_static_disabled_e].location) {
          setting->build_static = F_true;
          setting->search_static = F_true;
        }
        else {
          setting->build_static = F_false;
          setting->search_static = F_false;
        }

        if (main->error.verbosity >= f_console_verbosity_verbose_e) {
          flockfile(main->error.to.stream);

          fl_print_format("%r%[%QThe parameters '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fake_long_static_disabled_s, main->error.notable);
          fl_print_format("%[' and '%]", main->error.to.stream, main->error.context, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fake_long_static_enabled_s, main->error.notable);
          fl_print_format("%[' contradict, defaulting to '%]", main->error.to.stream, main->error.context, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, setting->build_static ? fake_long_static_enabled_s : fake_long_static_disabled_s, main->error.notable);
          fl_print_format("%['.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          funlockfile(main->error.to.stream);
        }
      }
      else {
        setting->build_static = F_false;
        setting->search_static = F_false;
      }
    }
    else if (main->parameters.array[fake_parameter_static_enabled_e].result == f_console_result_found_e) {
      setting->build_static = F_true;
      setting->search_static = F_true;
    }

    if (setting->build_language == fake_build_language_type_c_e || setting->build_language == fake_build_language_type_cpp_e) {
      if (setting->build_shared == F_false && setting->build_static == F_false) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          flockfile(main->error.to.stream);

          fl_print_format("%r%[%QThe build settings '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%]", main->error.to.stream, main->error.notable, fake_build_setting_name_build_shared_s, main->error.notable);
          fl_print_format("%[' and '%]", main->error.to.stream, main->error.context, main->error.context);
          fl_print_format("%[%r%]", main->error.to.stream, main->error.notable, fake_build_setting_name_build_static_s, main->error.notable);
          fl_print_format("%[' cannot both be false when using the language '%]", main->error.to.stream, main->error.context, main->error.context);
          fl_print_format("%[%r%]", main->error.to.stream, main->error.notable, setting->build_language == fake_build_language_type_c_e ? fake_build_language_c_s : fake_build_language_cpp_s, main->error.notable);
          fl_print_format("%['.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          funlockfile(main->error.to.stream);
        }

        *status = F_status_set_error(F_failure);
      }
    }
  }
#endif // _di_fake_build_load_setting_override_

#ifndef _di_fake_build_load_stage_
  void fake_build_load_stage(fake_main_t * const main, const f_string_static_t settings_file, fake_build_stage_t * const stage, f_status_t * const status) {

    if (F_status_is_error(*status)) return;

    if (fake_signal_received(main)) {
      *status = F_status_set_error(F_interrupt);

      return;
    }

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
      &stage->file_sources_headers,
      &stage->file_sources_script,
      &stage->file_sources_settings,
    };

    *status = F_none;

    f_string_dynamic_t settings_file_base = f_string_dynamic_t_initialize;

    if (settings_file.used) {
      *status = f_file_name_base(settings_file, &settings_file_base);
    }
    else {
      *status = f_file_name_base(main->file_data_build_settings, &settings_file_base);
    }

    if (F_status_is_error(*status)) {
      fll_error_print(main->error, F_status_set_fine(*status), "f_file_name_base", F_true);

      return;
    }

    for (uint8_t i = 0; i < fake_build_stage_total_d; ++i) {

      *status = f_string_dynamic_append_nulless(main->path_build_stage, values[i]);

      if (F_status_is_error_not(*status) && main->process.used) {
        *status = f_string_dynamic_append_nulless(main->process, values[i]);

        *status = f_string_dynamic_append_nulless(fake_build_stage_separate_s, values[i]);
      }

      if (F_status_is_error_not(*status)) {
        *status = f_string_dynamic_append_nulless(names[i], values[i]);
      }

      if (F_status_is_error_not(*status)) {
        *status = f_string_dynamic_append_nulless(fake_build_stage_separate_s, values[i]);
      }

      if (F_status_is_error_not(*status)) {
        *status = f_string_dynamic_append_nulless(settings_file_base, values[i]);
      }

      if (F_status_is_error_not(*status)) {
        *status = f_string_dynamic_append_nulless(fake_build_stage_built_s, values[i]);
      }

      if (F_status_is_error(*status)) {
        fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_append_nulless", F_true);

        break;
      }
    } // for

    f_string_dynamic_resize(0, &settings_file_base);
  }
#endif // _di_fake_build_load_stage_

#ifdef __cplusplus
} // extern "C"
#endif
