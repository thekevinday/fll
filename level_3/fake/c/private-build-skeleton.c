#include "fake.h"
#include "private-common.h"
#include "private-fake.h"
#include "private-build.h"
#include "private-build-skeleton.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_skeleton_
  void fake_build_skeleton(fake_data_t * const data, fake_build_data_t * const data_build, const mode_t mode, const f_string_static_t file_stage, f_status_t * const status) {

    if (F_status_is_error(*status) || f_file_exists(file_stage, F_true) == F_true || *status == F_child) return;

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

    const f_string_static_t *directorys[] = {
      &data->path_build,
      &data->path_build_documentation,
      &data->path_build_documents,
      &data->path_build_includes,
      &data->path_build_libraries,
      &data->path_build_libraries_script,
      &data->path_build_libraries_shared,
      &data->path_build_libraries_static,
      &data->path_build_objects,
      &data->path_build_objects_script,
      &data->path_build_objects_shared,
      &data->path_build_objects_static,
      &data->path_build_programs,
      &data->path_build_programs_script,
      &data->path_build_programs_shared,
      &data->path_build_programs_static,
      &data->path_build_settings,
      &data->path_build_stage,
      &path_headers,
    };

    if (data->main->output.verbosity != f_console_verbosity_quiet_e && data->main->output.verbosity != f_console_verbosity_error_e) {
      fll_print_format("%r%[Creating base build directories.%]%r", data->main->output.to.stream, f_string_eol_s, data->main->context.set.important, data->main->context.set.important, f_string_eol_s);
    }

    bool created = F_false;
    f_array_length_t j = 0;

    for (uint8_t i = 0; i < 19; ++i) {

      if (!directorys[i]->used) continue;

      created = F_false;

      for (j = 0; j < directorys[i]->used; ++j) {

        if (f_path_separator_s.used && directorys[i]->string[j] != f_path_separator_s.string[0]) continue;

        directorys[i]->string[j] = 0;

        *status = f_directory_exists(*directorys[i]);

        if (F_status_is_error(*status) || *status == F_false) {
          directorys[i]->string[j] = f_path_separator_s.string[0];

          break;
        }

        if (*status == F_file_found_not) {
          *status = f_directory_create(*directorys[i], mode);

          created = F_true;
        }

        directorys[i]->string[j] = f_path_separator_s.string[0];

        if (F_status_is_error(*status)) break;
      } // for

      if (F_status_is_fine(*status) && directorys[i]->used && f_path_separator_s.used && directorys[i]->string[directorys[i]->used - 1] != f_path_separator_s.string[0]) {
        *status = f_directory_exists(*directorys[i]);

        if (F_status_is_error_not(*status)) {
          if (*status == F_false) {
            *status = f_directory_create(*directorys[i], mode);

            created = F_true;
          }
        }
      }

      if (F_status_is_error(*status)) {
        if (F_status_set_fine(*status) == F_file_found) {
          *status = F_none;

          continue;
        }

        fll_error_file_print(data->main->error, F_status_set_fine(*status), "f_directory_create", F_true, *directorys[i], f_file_operation_create_s, fll_error_file_type_directory_e);

        return;
      }

      if (created && data->main->error.verbosity >= f_console_verbosity_verbose_e) {
        fll_print_format("Created directory '%Q'.%r", data->main->output.to.stream, *directorys[i], f_string_eol_s);
      }
    } // for

    fake_build_touch(data, file_stage, status);
  }
#endif // _di_fake_build_skeleton_

#ifdef __cplusplus
} // extern "C"
#endif
