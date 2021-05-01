#include "fake.h"
#include "private-fake.h"
#include "private-build.h"
#include "private-make.h"
#include "private-print.h"
#include "private-skeleton.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_skeleton_operate_
  f_status_t fake_skeleton_operate(const fake_main_t main) {

    if (fake_signal_received(main)) {
      return F_signal;
    }

    f_status_t status = F_none;

    if (main.error.verbosity != f_console_verbosity_quiet) {
      fprintf(main.output.stream, "%c", f_string_eol_s[0]);
      f_color_print(main.output.stream, main.context.set.important, "Generating skeleton structure.%c", f_string_eol_s[0]);
    }

    {
      const f_string_dynamic_t *parameters_value[] = {
        &main.path_build,
        &main.path_data,
        &main.path_data_build,
        &main.path_data_settings,
        &main.path_documents,
        &main.path_licenses,
        &main.path_sources,
        &main.path_sources_bash,
        &main.path_sources_c,
        &main.path_sources_cpp,
        &main.path_work,
        &main.path_work_includes,
        &main.path_work_libraries,
        &main.path_work_libraries_script,
        &main.path_work_libraries_shared,
        &main.path_work_libraries_static,
        &main.path_work_programs,
        &main.path_work_programs_script,
        &main.path_work_programs_shared,
        &main.path_work_programs_static,
      };

      for (uint8_t i = 0; i < 20; i++) {

        if (fake_signal_received(main)) {
          return F_status_set_error(F_signal);
        }

        status = fake_skeleton_operate_directory_create(main, *parameters_value[i]);

        if (F_status_is_error(status)) {
          fll_error_print(main.error, F_status_set_fine(status), "fake_skeleton_operate_directory_create", F_true);
          return status;
        }
      } // for
    }

    f_string_dynamic_t file_data_build_process_post = f_string_dynamic_t_initialize;
    f_string_dynamic_t file_data_build_process_pre = f_string_dynamic_t_initialize;
    f_string_dynamic_t content = f_string_dynamic_t_initialize;

    if (fake_signal_received(main)) {
      status = F_status_set_error(F_signal);
    }

    if (F_status_is_error_not(status)) {
      content.string = fake_make_skeleton_content_defines;
      content.used = fake_make_skeleton_content_defines_length;
      content.size = content.used;

      status = fake_skeleton_operate_file_create(main, main.file_data_build_defines, F_false, content);

      content.used = 0;
    }

    if (F_status_is_error_not(status)) {
      content.string = fake_make_skeleton_content_dependencies;
      content.used = fake_make_skeleton_content_dependencies_length;
      content.size = content.used;

      status = fake_skeleton_operate_file_create(main, main.file_data_build_dependencies, F_false, content);

      content.used = 0;

      if (fake_signal_received(main)) {
        status = F_status_set_error(F_signal);
      }
    }

    if (F_status_is_error_not(status)) {
      status = fake_skeleton_operate_file_create(main, file_data_build_process_post, F_true, content);

      if (fake_signal_received(main)) {
        status = F_status_set_error(F_signal);
      }
    }

    if (F_status_is_error_not(status)) {
      status = fake_skeleton_operate_file_create(main, file_data_build_process_pre, F_true, content);

      if (fake_signal_received(main)) {
        status = F_status_set_error(F_signal);
      }
    }

    if (F_status_is_error_not(status)) {
      content.string = fake_make_skeleton_content_settings;
      content.used = fake_make_skeleton_content_settings_length;
      content.size = content.used;

      status = fake_skeleton_operate_file_create(main, main.file_data_build_settings, F_false, content);

      content.used = 0;

      if (fake_signal_received(main)) {
        status = F_status_set_error(F_signal);
      }
    }

    if (F_status_is_error_not(status)) {
      status = fake_skeleton_operate_file_create(main, main.file_documents_readme, F_false, content);

      if (fake_signal_received(main)) {
        status = F_status_set_error(F_signal);
      }
    }

    if (F_status_is_error_not(status)) {
      content.string = fake_make_skeleton_content_fakefile;
      content.used = fake_make_skeleton_content_fakefile_length;
      content.size = content.used;

      status = fake_skeleton_operate_file_create(main, main.file_data_build_fakefile, F_false, content);

      content.used = 0;

      if (fake_signal_received(main)) {
        status = F_status_set_error(F_signal);
      }
    }

    if (F_status_is_error(status)) {
      f_macro_string_dynamic_t_delete_simple(file_data_build_process_post);
      f_macro_string_dynamic_t_delete_simple(file_data_build_process_pre);
      return status;
    }

    return F_none;
  }
#endif // _di_fake_skeleton_operate_

#ifndef _di_fake_skeleton_operate_directory_create_
  f_status_t fake_skeleton_operate_directory_create(const fake_main_t main, const f_string_dynamic_t path) {
    f_status_t status = F_none;

    if (!path.used) return F_none;

    status = f_directory_exists(path.string);

    if (status == F_true) {
      if (main.error.verbosity == f_console_verbosity_verbose) {
        fprintf(main.output.stream, "Directory '%s' already exists.%c", path.string, f_string_eol_s[0]);
      }

      return F_none;
    }

    if (status == F_false) {
      if (main.error.verbosity != f_console_verbosity_quiet) {
        fprintf(main.error.to.stream, "%c", f_string_eol_s[0]);
        f_color_print(main.error.to.stream, main.context.set.error, "%sThe path '", fll_error_print_error);
        f_color_print(main.error.to.stream, main.context.set.notable, "%s", path.string);
        f_color_print(main.error.to.stream, main.context.set.error, "' exists but is not a directory.%c", f_string_eol_s[0]);
      }

      return F_status_set_warning(F_failure);
    }
    else if (status == F_file_found_not) {
      status = f_directory_create(path.string, f_file_mode_all_rwx);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_file_found_not) {
          fprintf(main.error.to.stream, "%c", f_string_eol_s[0]);
          f_color_print(main.error.to.stream, main.context.set.error, "%sThe path '", fll_error_print_error);
          f_color_print(main.error.to.stream, main.context.set.notable, "%s", path.string);
          f_color_print(main.error.to.stream, main.context.set.error, "' could not be created, a parent directory does not exist.%c", f_string_eol_s[0]);
        }
        else {
          fll_error_file_print(main.error, F_status_set_fine(status), "f_directory_create", F_true, path.string, "create", fll_error_file_type_directory);
        }

        return status;
      }

      if (main.error.verbosity == f_console_verbosity_verbose) {
        fprintf(main.output.stream, "Directory '%s' created.%c", path.string, f_string_eol_s[0]);
      }
    }
    else if (F_status_is_error(status)) {
      fll_error_file_print(main.error, F_status_set_fine(status), "f_directory_exists", F_true, path.string, "create", fll_error_file_type_directory);
      return status;
    }

    return F_none;
  }
#endif // _di_fake_skeleton_operate_directory_create_

#ifndef _di_fake_skeleton_operate_file_create_
  f_status_t fake_skeleton_operate_file_create(const fake_main_t main, const f_string_dynamic_t path, const bool executable, const f_string_static_t content) {
    f_status_t status = F_none;

    if (!path.used) return F_none;

    status = f_file_is(path.string, f_file_type_regular, F_false);

    if (status == F_true) {
      if (main.error.verbosity == f_console_verbosity_verbose) {
        fprintf(main.output.stream, "File '%s' already exists.%c", path.string, f_string_eol_s[0]);
      }

      return F_none;
    }

    // symbolic links might also be fine.
    if (status == F_false) {
      status = f_file_is(path.string, f_file_type_link, F_false);

      if (status == F_true) {
        if (main.error.verbosity == f_console_verbosity_verbose) {
          fprintf(main.output.stream, "File '%s' already exists (as a symbolic link).%c", path.string, f_string_eol_s[0]);
        }

        return F_none;
      }
    }

    if (status == F_false) {
      if (main.error.verbosity == f_console_verbosity_verbose) {
        fprintf(main.output.stream, "File '%s' already exists but is not a regular file (or symbolic link).%c", path.string, f_string_eol_s[0]);
      }

      return F_status_set_warning(F_none);
    }
    else if (status == F_file_found_not) {
      mode_t mode = f_file_mode_all_rw;

      if (executable) {
        mode = f_file_mode_all_rwx;
      }

      status = f_file_create(path.string, mode, F_true);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_file_found_not) {
          fprintf(main.error.to.stream, "%c", f_string_eol_s[0]);
          f_color_print(main.error.to.stream, main.context.set.error, "%sThe file '", fll_error_print_error);
          f_color_print(main.error.to.stream, main.context.set.notable, "%s", path.string);
          f_color_print(main.error.to.stream, main.context.set.error, "' could not be created, a parent directory does not exist.%c", f_string_eol_s[0]);
        }
        else {
          fll_error_file_print(main.error, F_status_set_fine(status), "f_file_create", F_true, path.string, "create", fll_error_file_type_file);
        }

        return status;
      }

      if (main.error.verbosity == f_console_verbosity_verbose) {
        fprintf(main.output.stream, "File '%s' created.%c", path.string, f_string_eol_s[0]);
      }

      if (content.used) {
        f_file_t file = f_file_t_initialize;

        file.flag = f_file_flag_append_wo;
        file.size_write = content.used;

        status = f_file_open(path.string, 0, &file);

        if (F_status_is_error(status)) {
          fll_error_file_print(main.error, F_status_set_fine(status), "f_file_open", F_true, path.string, "pre-populate", fll_error_file_type_file);

          return status;
        }

        status = f_file_write(file, content, 0);

        if (F_status_is_error(status)) {
          fll_error_file_print(main.error, F_status_set_fine(status), "f_file_write", F_true, path.string, "pre-populate", fll_error_file_type_file);

          f_file_stream_close(F_true, &file);
          return status;
        }

        if (main.error.verbosity == f_console_verbosity_verbose) {
          fprintf(main.output.stream, "File '%s' pre-populated.%c", path.string, f_string_eol_s[0]);
        }

        f_file_stream_close(F_true, &file);
      }
    }
    else if (F_status_is_error(status)) {
      fll_error_file_print(main.error, F_status_set_fine(status), "f_file_is", F_true, path.string, "create", fll_error_file_type_file);

      return status;
    }

    return F_none;
  }
#endif // _di_fake_skeleton_operate_file_create_

#ifdef __cplusplus
} // extern "C"
#endif
