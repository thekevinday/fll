#include "../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_skeleton_
  void fake_build_skeleton(fake_data_t * const data, fake_build_data_t * const data_build, const mode_t mode, const f_string_static_t file_stage) {

    if (!data || !data->main || !data_build) return;
    if (F_status_is_error(data->main->setting.state.status) || data->main->setting.state.status == F_child) return;
    if (f_file_exists(file_stage, F_true) == F_true) return;

    fake_main_t * const main = data->main;

    fake_string_dynamic_reset(&main->cache_argument);

    if (data_build->setting.path_headers.used) {
        main->setting.state.status = f_string_dynamic_append_nulless(data->path_build_includes, &main->cache_argument);

      if (F_status_is_error_not(main->setting.state.status)) {
        main->setting.state.status = f_string_dynamic_append_nulless(data_build->setting.path_headers, &main->cache_argument);
      }

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

        return;
      }
    }

    const f_string_static_t directorys[] = {
      data->path_build,
      data->path_build_documentation,
      data->path_build_documents,
      data->path_build_includes,
      data->path_build_libraries,
      data->path_build_libraries_script,
      data->path_build_libraries_shared,
      data->path_build_libraries_static,
      data->path_build_objects,
      data->path_build_objects_script,
      data->path_build_objects_shared,
      data->path_build_objects_static,
      data->path_build_programs,
      data->path_build_programs_script,
      data->path_build_programs_shared,
      data->path_build_programs_static,
      data->path_build_settings,
      data->path_build_stage,
      main->cache_argument,
    };

    fake_build_print_message_skeleton_build_base(&main->program.message);

    bool created = F_false;
    f_number_unsigned_t j = 0;

    for (uint8_t i = 0; i < 19; ++i) {

      if (!directorys[i].used) continue;

      created = F_false;

      for (j = 0; j < directorys[i].used; ++j) {

        if (f_path_separator_s.used && directorys[i].string[j] != f_path_separator_s.string[0]) continue;
        if (fake_signal_check(data->main)) return;

        directorys[i].string[j] = 0;

        main->setting.state.status = f_directory_exists(directorys[i]);

        if (F_status_is_error(main->setting.state.status) || main->setting.state.status == F_false) {
          directorys[i].string[j] = f_path_separator_s.string[0];

          break;
        }

        if (main->setting.state.status == F_file_found_not) {
          main->setting.state.status = f_directory_create(directorys[i], mode);

          created = F_true;
        }

        directorys[i].string[j] = f_path_separator_s.string[0];

        if (F_status_is_error(main->setting.state.status)) break;
      } // for

      if (F_status_is_fine(main->setting.state.status) && directorys[i].used && f_path_separator_s.used && directorys[i].string[directorys[i].used - 1] != f_path_separator_s.string[0]) {
        main->setting.state.status = f_directory_exists(directorys[i]);

        if (F_status_is_error_not(main->setting.state.status)) {
          if (main->setting.state.status == F_false) {
            main->setting.state.status = f_directory_create(directorys[i], mode);

            created = F_true;
          }
        }
      }

      if (F_status_is_error(main->setting.state.status)) {
        if (F_status_set_fine(main->setting.state.status) == F_file_found) {
          main->setting.state.status = F_none;

          continue;
        }

        fake_print_error_file(&main->program.error, macro_fake_f(f_directory_create), directorys[i], f_file_operation_create_s, fll_error_file_type_directory_e);

        return;
      }

      if (created) {
        fake_build_print_verbose_create_directory(&main->program.message, directorys[i]);
      }
    } // for

    fake_build_touch(data, file_stage);

    if (F_status_is_error_not(main->setting.state.status)) {
      main->setting.state.status = F_none;
    }
  }
#endif // _di_fake_build_skeleton_

#ifdef __cplusplus
} // extern "C"
#endif
