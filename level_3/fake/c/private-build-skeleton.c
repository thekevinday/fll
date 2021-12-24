#include "fake.h"
#include "private-common.h"
#include "private-fake.h"
#include "private-build.h"
#include "private-build-skeleton.h"
#include "private-make.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_skeleton_
  void fake_build_skeleton(fake_main_t * const main, const fake_build_data_t data_build, const mode_t mode, const f_string_static_t file_stage, f_status_t *status) {

    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true || *status == F_child) return;

    f_string_static_t path_headers = f_string_static_t_initialize;
    f_array_length_t directory_headers_length = main->path_build_includes.used + data_build.setting.path_headers.used;

    char directory_headers[directory_headers_length + 1];

    if (data_build.setting.path_headers.used) {
      memcpy(directory_headers, main->path_build_includes.string, main->path_build_includes.used);
      memcpy(directory_headers + main->path_build_includes.used, data_build.setting.path_headers.string, data_build.setting.path_headers.used);

      directory_headers[directory_headers_length] = 0;

      path_headers.string = directory_headers;
      path_headers.used = directory_headers_length;
      path_headers.size = directory_headers_length + 1;
    }
    else {
      directory_headers[0] = 0;

      path_headers.string = directory_headers;
      path_headers.used = 0;
      path_headers.size = directory_headers_length + 1;
    }

    const f_string_static_t *directorys[] = {
      &main->path_build,
      &main->path_build_documents,
      &main->path_build_includes,
      &main->path_build_libraries,
      &main->path_build_libraries_script,
      &main->path_build_libraries_shared,
      &main->path_build_libraries_static,
      &main->path_build_objects,
      &main->path_build_programs,
      &main->path_build_programs_script,
      &main->path_build_programs_shared,
      &main->path_build_programs_static,
      &main->path_build_settings,
      &main->path_build_stage,
      &path_headers,
    };

    if (main->output.verbosity != f_console_verbosity_quiet_e) {
      fll_print_format("%c%[Creating base build directories.%]%c", main->output.to.stream, f_string_eol_s[0], main->context.set.important, main->context.set.important, f_string_eol_s[0]);
    }

    for (uint8_t i = 0; i < 15; ++i) {

      if (!directorys[i]->used) continue;

      // @todo implement this in a common function and use across project for creating parent directories.
      for (f_array_length_t j = 0; j < directorys[i]->used; ++j) {

        if (directorys[i]->string[j] != f_path_separator_s[0]) continue;

        directorys[i]->string[j] = 0;

        *status = f_directory_exists(directorys[i]->string);

        if (F_status_is_error(*status) || *status == F_false) {
          directorys[i]->string[j] = f_path_separator_s[0];

          break;
        }

        if (*status == F_file_found_not) {
          *status = f_directory_create(directorys[i]->string, mode);
        }

        directorys[i]->string[j] = f_path_separator_s[0];

        if (F_status_is_error(*status)) break;
      } // for

      if (F_status_is_fine(*status)) {
        *status = f_directory_create(directorys[i]->string, mode);
      }

      if (F_status_is_error(*status)) {
        if (F_status_set_fine(*status) == F_file_found) {
          *status = F_none;
          continue;
        }

        fll_error_file_print(main->error, F_status_set_fine(*status), "f_directory_create", F_true, directorys[i]->string, "create", fll_error_file_type_directory_e);
        return;
      }

      if (main->error.verbosity == f_console_verbosity_verbose_e) {
        fll_print_format("Created directory '%Q'.%c", main->output.to.stream, directorys[i], f_string_eol_s[0]);
      }
    } // for

    fake_build_touch(main, file_stage, status);
  }
#endif // _di_fake_build_skeleton_

#ifdef __cplusplus
} // extern "C"
#endif
