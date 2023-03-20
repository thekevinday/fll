#include "../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_path_generate_
  void fake_path_generate(fake_data_t * const data) {

    if (!data || !data->main) return;

    data->main->setting.state.status = F_none;
    uint8_t i = 0;

    {
      uint8_t j = 0;

      const f_string_dynamic_t sources[] = {
        data->main->setting.build,
        data->main->setting.data,
      };

      const uint8_t parameters_size[] = {
        9,
        3,
      };

      f_string_dynamic_t *values_0[] = {
        &data->path_build,
        &data->path_build_documentation,
        &data->path_build_documents,
        &data->path_build_includes,
        &data->path_build_libraries,
        &data->path_build_objects,
        &data->path_build_programs,
        &data->path_build_settings,
        &data->path_build_stage,
      };

      f_string_dynamic_t *values_1[] = {
        &data->path_data_build,
        &data->path_data_documentation,
        &data->path_data_settings,
      };

      f_string_dynamic_t **const values[] = {
        values_0,
        values_1,
      };

      for (i = 0; i < 2; ++i) {

        // Initialize all string lengths to 0.
        for (j = 0; j < parameters_size[i]; ++j) {
          values[i][j]->used = 0;
        } // for

        fake_path_generate_string_dynamic(data, sources[i], values[i], parameters_size[i]);

        if (F_status_is_error(data->main->setting.state.status)) {
          fake_print_error(&data->main->program.error, macro_fake_f(fake_path_generate_string_dynamic));

          return;
        }
      } // for
    }

    {
      const f_string_static_t sources[] = {
        fake_path_part_documentation_s,
        fake_path_part_documents_s,
        fake_path_part_includes_s,
        fake_path_part_libraries_s,
        fake_path_part_objects_s,
        fake_path_part_programs_s,
        fake_path_part_settings_s,
        fake_path_part_stage_s,
        fake_path_part_build_s,
        fake_path_part_documentation_s,
        fake_path_part_settings_s,
        fake_path_part_documents_s,
        fake_path_part_licenses_s,
      };

      f_string_dynamic_t * const values[] = {
        &data->path_build_documentation,
        &data->path_build_documents,
        &data->path_build_includes,
        &data->path_build_libraries,
        &data->path_build_objects,
        &data->path_build_programs,
        &data->path_build_settings,
        &data->path_build_stage,
        &data->path_data_build,
        &data->path_data_documentation,
        &data->path_data_settings,
        &data->path_documents,
        &data->path_licenses,
      };

      for (i = 0; i < 13; ++i) {

        data->main->setting.state.status = f_string_dynamic_append_nulless(sources[i], values[i]);

        if (F_status_is_error(data->main->setting.state.status)) {
          fake_print_error(&data->main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

          return;
        }
      } // for
    }

    {
      const f_string_dynamic_t sources[] = {
        data->path_build_libraries,
        data->path_build_objects,
        data->path_build_programs,
        data->path_data_build,
        data->path_documents,
      };

      const uint8_t parameters_size[] = {
        3,
        3,
        3,
        6,
        1,
      };

      f_string_dynamic_t *values_0[] = {
        &data->path_build_libraries_script,
        &data->path_build_libraries_shared,
        &data->path_build_libraries_static,
      };

      f_string_dynamic_t *values_1[] = {
        &data->path_build_objects_script,
        &data->path_build_objects_shared,
        &data->path_build_objects_static,
      };

      f_string_dynamic_t *parameters_value_2[] = {
        &data->path_build_programs_script,
        &data->path_build_programs_shared,
        &data->path_build_programs_static,
      };

      f_string_dynamic_t *parameters_value_3[] = {
        &data->file_data_build_defines,
        &data->file_data_build_dependencies,
        &data->file_data_build_fakefile,
        &data->file_data_build_process_post,
        &data->file_data_build_process_pre,
        &data->file_data_build_settings,
      };

      f_string_dynamic_t *parameters_value_4[] = {
        &data->file_documents_readme,
      };

      f_string_dynamic_t **const values[] = {
        values_0,
        values_1,
        parameters_value_2,
        parameters_value_3,
        parameters_value_4,
      };

      for (i = 0; i < 5; ++i) {

        fake_path_generate_string_dynamic(data, sources[i], values[i], parameters_size[i]);

        if (F_status_is_error(data->main->setting.state.status)) {
          fake_print_error(&data->main->program.error, macro_fake_f(fake_path_generate_string_dynamic));

          return;
        }
      } // for
    }

    // When custom fakefile or settings are used and they are paths to a file, remove the default path.
    if (f_path_is(data->main->setting.fakefile) == F_true || f_file_exists(data->main->setting.fakefile, F_true) == F_true) {
      data->file_data_build_fakefile.used = 0;
    }

    if (f_path_is(data->main->setting.settings) == F_true || f_file_exists(data->main->setting.settings, F_true) == F_true) {
      data->file_data_build_settings.used = 0;
    }

    {
      const f_string_static_t sources[] = {
        fake_path_part_script_s,
        fake_path_part_shared_s,
        fake_path_part_static_s,
        fake_path_part_script_s,
        fake_path_part_shared_s,
        fake_path_part_static_s,
        fake_path_part_script_s,
        fake_path_part_shared_s,
        fake_path_part_static_s,
        fake_file_defines_s,
        fake_file_dependencies_s,
        fake_file_process_post_s,
        fake_file_process_pre_s,
        data->main->setting.fakefile,
        data->main->setting.settings,
        fake_file_readme_s,
      };

      f_string_dynamic_t * const values[] = {
        &data->path_build_libraries_script,
        &data->path_build_libraries_shared,
        &data->path_build_libraries_static,
        &data->path_build_objects_script,
        &data->path_build_objects_shared,
        &data->path_build_objects_static,
        &data->path_build_programs_script,
        &data->path_build_programs_shared,
        &data->path_build_programs_static,
        &data->file_data_build_defines,
        &data->file_data_build_dependencies,
        &data->file_data_build_process_post,
        &data->file_data_build_process_pre,
        &data->file_data_build_fakefile,
        &data->file_data_build_settings,
        &data->file_documents_readme,
      };

      for (i = 0; i < 16; ++i) {

        data->main->setting.state.status = f_string_dynamic_append_nulless(sources[i], values[i]);

        if (F_status_is_error(data->main->setting.state.status)) {
          fake_print_error(&data->main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

          return;
        }
      } // for
    }

    if (data->main->setting.work.used) {
      {
        f_string_dynamic_t * const values[] = {
          &data->path_work_includes,
          &data->path_work_libraries,
          &data->path_work_programs,
        };

        for (i = 0; i < 3; ++i) {

          values[i]->used = 0;

          data->main->setting.state.status = f_string_dynamic_append_nulless(data->main->setting.work, values[i]);

          if (F_status_is_error(data->main->setting.state.status)) {
            fake_print_error(&data->main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

            return;
          }
        } // for
      }

      {
        const f_string_static_t sources[] = {
          fake_path_part_includes_s,
          fake_path_part_libraries_s,
          fake_path_part_programs_s,
        };

        f_string_dynamic_t * const values[] = {
          &data->path_work_includes,
          &data->path_work_libraries,
          &data->path_work_programs,
        };

        for (i = 0; i < 3; ++i) {

          data->main->setting.state.status = f_string_dynamic_append_nulless(sources[i], values[i]);

          if (F_status_is_error(data->main->setting.state.status)) {
            fake_print_error(&data->main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

            return;
          }
        } // for
      }

      {
        const f_string_dynamic_t sources[] = {
          data->path_work_libraries,
          data->path_work_programs,
        };

        const uint8_t parameters_size[] = {
          3,
          3,
        };

        f_string_dynamic_t *values_0[] = {
          &data->path_work_libraries_script,
          &data->path_work_libraries_shared,
          &data->path_work_libraries_static,
        };

        f_string_dynamic_t *values_1[] = {
          &data->path_work_programs_script,
          &data->path_work_programs_shared,
          &data->path_work_programs_static,
        };

        f_string_dynamic_t **const values[] = {
          values_0,
          values_1,
        };

        for (i = 0; i < 2; ++i) {

          fake_path_generate_string_dynamic(data, sources[i], values[i], parameters_size[i]);

          if (F_status_is_error(data->main->setting.state.status)) {
            fake_print_error(&data->main->program.error, macro_fake_f(fake_path_generate_string_dynamic));

            return;
          }
        } // for
      }

      {
        const f_string_static_t sources[] = {
          fake_path_part_script_s,
          fake_path_part_shared_s,
          fake_path_part_static_s,
          fake_path_part_script_s,
          fake_path_part_shared_s,
          fake_path_part_static_s,
        };

        f_string_dynamic_t * const values[] = {
          &data->path_work_libraries_script,
          &data->path_work_libraries_shared,
          &data->path_work_libraries_static,
          &data->path_work_programs_script,
          &data->path_work_programs_shared,
          &data->path_work_programs_static,
        };

        for (i = 0; i < 6; ++i) {

          data->main->setting.state.status = f_string_dynamic_append_nulless(sources[i], values[i]);

          if (F_status_is_error(data->main->setting.state.status)) {
            fake_print_error(&data->main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

            return;
          }
        } // for
      }
    }

    data->main->setting.state.status = F_none;
  }
#endif // _di_fake_path_generate_

#ifndef _di_fake_path_generate_string_dynamic_
  void fake_path_generate_string_dynamic(fake_data_t * const data, const f_string_dynamic_t source, f_string_dynamic_t *destination[], const uint8_t length) {

    if (!data || !data->main || !destination) return;

    data->main->setting.state.status = F_none;

    for (uint8_t i = 0; i < length; ++i) {

      data->main->setting.state.status = f_string_dynamic_append_nulless(source, destination[i]);
      if (F_status_is_error(data->main->setting.state.status)) break;
    } // for
  }
#endif // _di_fake_path_generate_string_dynamic_

#ifdef __cplusplus
} // extern "C"
#endif
