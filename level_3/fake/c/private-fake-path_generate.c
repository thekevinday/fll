#include "fake.h"
#include "private-common.h"
#include "private-fake-path_generate.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_path_generate_
  f_status_t fake_path_generate(fake_data_t * const data) {

    f_status_t status = F_none;
    uint8_t i = 0;

    {
      uint8_t j = 0;

      const f_string_dynamic_t *parameters_source[] = {
        &data->path_build,
        &data->path_data,
      };

      const uint8_t parameters_size[] = {
        8,
        3,
      };

      f_string_dynamic_t *parameters_value_0[] = {
        &data->path_build_documentation,
        &data->path_build_documents,
        &data->path_build_includes,
        &data->path_build_libraries,
        &data->path_build_objects,
        &data->path_build_programs,
        &data->path_build_settings,
        &data->path_build_stage,
      };

      f_string_dynamic_t *parameters_value_1[] = {
        &data->path_data_build,
        &data->path_data_documentation,
        &data->path_data_settings,
      };

      f_string_dynamic_t **const parameters_value[] = {
        parameters_value_0,
        parameters_value_1,
      };

      for (i = 0; i < 2; ++i) {

        // Initialize all string lengths to 0.
        for (j = 0; j < parameters_size[i]; ++j) {
          parameters_value[i][j]->used = 0;
        } // for

        status = fake_path_generate_string_dynamic(data, *parameters_source[i], parameters_value[i], parameters_size[i]);

        if (F_status_is_error(status)) {
          fll_error_print(data->main->error, F_status_set_fine(status), "fake_path_generate_string_dynamic", F_true);

          return status;
        }
      } // for
    }

    {
      const f_string_static_t parameters_source[] = {
        fake_path_part_documentation_s,
        fake_path_part_documents_s,
        fake_path_part_includes_s,
        fake_path_part_libraries_s,
        fake_path_part_objects_s,
        fake_path_part_programs_s,
        fake_path_part_settings_s,
        fake_path_part_stage_s,
        data->path_under,
        fake_path_part_documentation_s,
        fake_path_part_settings_s,
        fake_path_part_documents_s,
        fake_path_part_licenses_s,
      };

      f_string_dynamic_t * const parameters_value[] = {
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

        status = f_string_dynamic_append_nulless(parameters_source[i], parameters_value[i]);

        if (F_status_is_error(status)) {
          fll_error_print(data->main->error, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true);

          return status;
        }
      } // for
    }

    {
      const f_string_dynamic_t *parameters_source[] = {
        &data->path_build_libraries,
        &data->path_build_objects,
        &data->path_build_programs,
        &data->path_data_build,
        &data->path_documents,
      };

      const uint8_t parameters_size[] = {
        3,
        3,
        3,
        6,
        1,
      };

      f_string_dynamic_t *parameters_value_0[] = {
        &data->path_build_libraries_script,
        &data->path_build_libraries_shared,
        &data->path_build_libraries_static,
      };

      f_string_dynamic_t *parameters_value_1[] = {
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

      f_string_dynamic_t **const parameters_value[] = {
        parameters_value_0,
        parameters_value_1,
        parameters_value_2,
        parameters_value_3,
        parameters_value_4,
      };

      for (i = 0; i < 5; ++i) {

        status = fake_path_generate_string_dynamic(data, *parameters_source[i], parameters_value[i], parameters_size[i]);

        if (F_status_is_error(status)) {
          fll_error_print(data->main->error, F_status_set_fine(status), "fake_path_generate_string_dynamic", F_true);

          return status;
        }
      } // for
    }

    // When custom fakefile or settings are used and they are paths to a file, remove the default path.
    if (f_path_is(data->fakefile) == F_true || f_file_exists(data->fakefile, F_true) == F_true) {
      data->file_data_build_fakefile.used = 0;
    }

    if (f_path_is(data->settings) == F_true || f_file_exists(data->settings, F_true) == F_true) {
      data->file_data_build_settings.used = 0;
    }

    {
      const f_string_static_t parameters_source[] = {
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
        data->fakefile,
        data->settings,
        fake_file_readme_s,
      };

      f_string_dynamic_t * const parameters_value[] = {
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

        status = f_string_dynamic_append_nulless(parameters_source[i], parameters_value[i]);

        if (F_status_is_error(status)) {
          fll_error_print(data->main->error, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true);

          return status;
        }
      } // for
    }

    if (data->path_work.used) {
      {
        f_string_dynamic_t * const parameters_value[] = {
          &data->path_work_includes,
          &data->path_work_libraries,
          &data->path_work_programs,
        };

        for (i = 0; i < 3; ++i) {

          parameters_value[i]->used = 0;

          status = f_string_dynamic_append_nulless(data->path_work, parameters_value[i]);

          if (F_status_is_error(status)) {
            fll_error_print(data->main->error, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true);

            return status;
          }
        } // for
      }

      {
        const f_string_static_t parameters_source[] = {
          fake_path_part_includes_s,
          fake_path_part_libraries_s,
          fake_path_part_programs_s,
        };

        f_string_dynamic_t * const parameters_value[] = {
          &data->path_work_includes,
          &data->path_work_libraries,
          &data->path_work_programs,
        };

        for (i = 0; i < 3; ++i) {

          status = f_string_dynamic_append_nulless(parameters_source[i], parameters_value[i]);

          if (F_status_is_error(status)) {
            fll_error_print(data->main->error, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true);

            return status;
          }
        } // for
      }

      {
        const f_string_dynamic_t *parameters_source[] = {
          &data->path_work_libraries,
          &data->path_work_programs,
        };

        const uint8_t parameters_size[] = {
          3,
          3,
        };

        f_string_dynamic_t *parameters_value_0[] = {
          &data->path_work_libraries_script,
          &data->path_work_libraries_shared,
          &data->path_work_libraries_static,
        };

        f_string_dynamic_t *parameters_value_1[] = {
          &data->path_work_programs_script,
          &data->path_work_programs_shared,
          &data->path_work_programs_static,
        };

        f_string_dynamic_t **const parameters_value[] = {
          parameters_value_0,
          parameters_value_1,
        };

        for (i = 0; i < 2; ++i) {

          status = fake_path_generate_string_dynamic(data, *parameters_source[i], parameters_value[i], parameters_size[i]);

          if (F_status_is_error(status)) {
            fll_error_print(data->main->error, F_status_set_fine(status), "fake_path_generate_string_dynamic", F_true);

            return status;
          }
        } // for
      }

      {
        const f_string_static_t parameters_source[] = {
          fake_path_part_script_s,
          fake_path_part_shared_s,
          fake_path_part_static_s,
          fake_path_part_script_s,
          fake_path_part_shared_s,
          fake_path_part_static_s,
        };

        f_string_dynamic_t * const parameters_value[] = {
          &data->path_work_libraries_script,
          &data->path_work_libraries_shared,
          &data->path_work_libraries_static,
          &data->path_work_programs_script,
          &data->path_work_programs_shared,
          &data->path_work_programs_static,
        };

        for (i = 0; i < 6; ++i) {

          status = f_string_dynamic_append_nulless(parameters_source[i], parameters_value[i]);

          if (F_status_is_error(status)) {
            fll_error_print(data->main->error, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true);

            return status;
          }
        } // for
      }
    }

    return F_none;
  }
#endif // _di_fake_path_generate_

#ifndef _di_fake_path_generate_string_dynamic_
  f_status_t fake_path_generate_string_dynamic(fake_data_t * const data, const f_string_dynamic_t source, f_string_dynamic_t *destination[], const uint8_t length) {

    f_status_t status = F_none;

    for (uint8_t i = 0; i < length; ++i) {

      status = f_string_dynamic_append_nulless(source, destination[i]);
      if (F_status_is_error(status)) return status;
    } // for

    return F_none;
  }
#endif // _di_fake_path_generate_string_dynamic_

#ifdef __cplusplus
} // extern "C"
#endif
