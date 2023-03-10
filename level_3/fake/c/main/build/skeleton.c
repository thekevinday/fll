#include "../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_skeleton_
  void fake_build_skeleton(fake_data_t * const data, fake_build_data_t * const data_build, const mode_t mode, const f_string_static_t file_stage) {

    if (!data || !data_build) return;
    if (F_status_is_error(data->setting->state.status) || data->setting->state.status == F_child) return;
    if (f_file_exists(file_stage, F_true) == F_true) return;

    f_string_static_t path_headers = f_string_static_t_initialize;
    path_headers.used = data->path_build_includes.used + data_build->setting.path_headers.used;

    f_char_t path_headers_string[path_headers.used + 1];
    path_headers.string = path_headers_string;

    if (data_build->setting.path_headers.used) {
      memcpy(path_headers_string, data->path_build_includes.string, sizeof(f_char_t) * data->path_build_includes.used);
      memcpy(path_headers_string + data->path_build_includes.used, data_build->setting.path_headers.string, sizeof(f_char_t) * data_build->setting.path_headers.used);
    }
    else {
      path_headers.used = 0;
    }

    path_headers_string[path_headers.used] = 0;

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
      path_headers,
    };

    fake_build_print_skeleton_build_base(data->setting, data->main->message);

    bool created = F_false;
    f_array_length_t j = 0;

    for (uint8_t i = 0; i < 19; ++i) {

      if (!directorys[i].used) continue;

      created = F_false;

      for (j = 0; j < directorys[i].used; ++j) {

        if (f_path_separator_s.used && directorys[i].string[j] != f_path_separator_s.string[0]) continue;

        if (!((++main->signal_check) % fake_signal_check_d)) {
          if (fll_program_standard_signal_received(data->main)) {
            fll_program_print_signal_received(data->main->warning, data->setting->line_first, data->main->signal_received);

            data->setting->state.status = F_status_set_error(F_interrupt);

            return;
          }
        }

        directorys[i].string[j] = 0; // @fixme this is an error because static strings might be in use.

        data->setting->state.status = f_directory_exists(directorys[i]);

        if (F_status_is_error(data->setting->state.status) || data->setting->state.status == F_false) {
          directorys[i].string[j] = f_path_separator_s.string[0];

          break;
        }

        if (data->setting->state.status == F_file_found_not) {
          data->setting->state.status = f_directory_create(directorys[i], mode);

          created = F_true;
        }

        directorys[i].string[j] = f_path_separator_s.string[0];

        if (F_status_is_error(data->setting->state.status)) break;
      } // for

      if (F_status_is_fine(data->setting->state.status) && directorys[i].used && f_path_separator_s.used && directorys[i].string[directorys[i].used - 1] != f_path_separator_s.string[0]) {
        data->setting->state.status = f_directory_exists(directorys[i]);

        if (F_status_is_error_not(data->setting->state.status)) {
          if (data->setting->state.status == F_false) {
            data->setting->state.status = f_directory_create(directorys[i], mode);

            created = F_true;
          }
        }
      }

      if (F_status_is_error(setting->state.status)) {
        if (F_status_set_fine(data->setting->state.status) == F_file_found) {
          data->setting->state.status = F_none;

          continue;
        }

        fake_print_error_file(data->setting, data->main->error, macro_fake_f(f_directory_create), directorys[i], f_file_operation_create_s, fll_error_file_type_directory_e);

        return;
      }

      if (created) {
        fake_build_print_verbose_create_directory(data->setting, data->main->message, directorys[i]);
      }
    } // for

    fake_build_touch(data, file_stage);

    if (F_status_is_error_not(data->setting->state.status)) {
      data->setting->state.status = F_none;
    }
  }
#endif // _di_fake_build_skeleton_

#ifdef __cplusplus
} // extern "C"
#endif
