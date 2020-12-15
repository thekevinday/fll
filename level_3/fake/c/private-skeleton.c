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
  f_return_status fake_skeleton_operate(const fake_data_t data) {

    if (fake_signal_received(data)) {
      return F_signal;
    }

    f_status_t status = F_none;

    if (data.error.verbosity != f_console_verbosity_quiet) {
      fprintf(data.output.stream, "%c", f_string_eol[0]);
      fl_color_print(data.output.stream, data.context.set.important, "Generating skeleton structure.%c", f_string_eol[0]);
    }

    {
      const f_string_dynamic_t *parameters_value[] = {
        &data.path_build,
        &data.path_data,
        &data.path_data_build,
        &data.path_data_settings,
        &data.path_documents,
        &data.path_licenses,
        &data.path_sources,
        &data.path_sources_bash,
        &data.path_sources_c,
        &data.path_sources_cpp,
        &data.path_work,
        &data.path_work_includes,
        &data.path_work_libraries,
        &data.path_work_libraries_script,
        &data.path_work_libraries_shared,
        &data.path_work_libraries_static,
        &data.path_work_programs,
        &data.path_work_programs_script,
        &data.path_work_programs_shared,
        &data.path_work_programs_static,
      };

      for (uint8_t i = 0; i < 20; i++) {

        if (fake_signal_received(data)) {
          return F_status_set_error(F_signal);
        }

        status = fake_skeleton_operate_directory_create(data, *parameters_value[i]);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fake_skeleton_operate_directory_create", F_true);
          return status;
        }
      } // for
    }

    f_string_dynamic_t file_data_build_process_post = f_string_dynamic_t_initialize;
    f_string_dynamic_t file_data_build_process_pre = f_string_dynamic_t_initialize;
    f_string_dynamic_t content = f_string_dynamic_t_initialize;

    if (fake_signal_received(data)) {
      status = F_status_set_error(F_signal);
    }

    if (F_status_is_error_not(status)) {
      content.string = fake_make_skeleton_content_defines;
      content.used = fake_make_skeleton_content_defines_length;
      content.size = content.used;

      status = fake_skeleton_operate_file_create(data, data.file_data_build_defines, F_false, content);

      content.used = 0;
    }

    if (F_status_is_error_not(status)) {
      content.string = fake_make_skeleton_content_dependencies;
      content.used = fake_make_skeleton_content_dependencies_length;
      content.size = content.used;

      status = fake_skeleton_operate_file_create(data, data.file_data_build_dependencies, F_false, content);

      content.used = 0;

      if (fake_signal_received(data)) {
        status = F_status_set_error(F_signal);
      }
    }

    if (F_status_is_error_not(status)) {
      status = fake_skeleton_operate_file_create(data, file_data_build_process_post, F_true, content);

      if (fake_signal_received(data)) {
        status = F_status_set_error(F_signal);
      }
    }

    if (F_status_is_error_not(status)) {
      status = fake_skeleton_operate_file_create(data, file_data_build_process_pre, F_true, content);

      if (fake_signal_received(data)) {
        status = F_status_set_error(F_signal);
      }
    }

    if (F_status_is_error_not(status)) {
      content.string = fake_make_skeleton_content_settings;
      content.used = fake_make_skeleton_content_settings_length;
      content.size = content.used;

      status = fake_skeleton_operate_file_create(data, data.file_data_build_settings, F_false, content);

      content.used = 0;

      if (fake_signal_received(data)) {
        status = F_status_set_error(F_signal);
      }
    }

    if (F_status_is_error_not(status)) {
      status = fake_skeleton_operate_file_create(data, data.file_documents_readme, F_false, content);

      if (fake_signal_received(data)) {
        status = F_status_set_error(F_signal);
      }
    }

    if (F_status_is_error_not(status)) {
      content.string = fake_make_skeleton_content_fakefile;
      content.used = fake_make_skeleton_content_fakefile_length;
      content.size = content.used;

      status = fake_skeleton_operate_file_create(data, data.file_data_build_fakefile, F_false, content);

      content.used = 0;

      if (fake_signal_received(data)) {
        status = F_status_set_error(F_signal);
      }
    }

    if (F_status_is_error(status)) {
      fl_string_dynamic_delete(&file_data_build_process_post);
      fl_string_dynamic_delete(&file_data_build_process_pre);
      return status;
    }

    return F_none;
  }
#endif // _di_fake_skeleton_operate_

#ifndef _di_fake_skeleton_operate_directory_create_
  f_return_status fake_skeleton_operate_directory_create(const fake_data_t data, const f_string_dynamic_t path) {
    f_status_t status = F_none;

    if (!path.used) return F_none;

    status = f_directory_exists(path.string);

    if (status == F_true) {
      if (data.error.verbosity == f_console_verbosity_verbose) {
        fprintf(data.output.stream, "Directory '%s' already exists.%c", path.string, f_string_eol[0]);
      }

      return F_none;
    }

    if (status == F_false) {
      if (data.error.verbosity != f_console_verbosity_quiet) {
        fprintf(data.error.to.stream, "%c", f_string_eol[0]);
        fl_color_print(data.error.to.stream, data.context.set.error, "%sThe path '", fll_error_print_error);
        fl_color_print(data.error.to.stream, data.context.set.notable, "%s", path.string);
        fl_color_print(data.error.to.stream, data.context.set.error, "' exists but is not a directory.%c", f_string_eol[0]);
      }

      return F_status_set_warning(F_failure);
    }
    else if (status == F_file_found_not) {
      status = f_directory_create(path.string, f_file_mode_all_rwx);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_file_found_not) {
          fprintf(data.error.to.stream, "%c", f_string_eol[0]);
          fl_color_print(data.error.to.stream, data.context.set.error, "%sThe path '", fll_error_print_error);
          fl_color_print(data.error.to.stream, data.context.set.notable, "%s", path.string);
          fl_color_print(data.error.to.stream, data.context.set.error, "' could not be created, a parent directory does not exist.%c", f_string_eol[0]);
        }
        else {
          fll_error_file_print(data.error, F_status_set_fine(status), "f_directory_create", F_true, path.string, "create", fll_error_file_type_directory);
        }

        return status;
      }

      if (data.error.verbosity == f_console_verbosity_verbose) {
        fprintf(data.output.stream, "Directory '%s' created.%c", path.string, f_string_eol[0]);
      }
    }
    else if (F_status_is_error(status)) {
      fll_error_file_print(data.error, F_status_set_fine(status), "f_directory_exists", F_true, path.string, "create", fll_error_file_type_directory);
      return status;
    }

    return F_none;
  }
#endif // _di_fake_skeleton_operate_directory_create_

#ifndef _di_fake_skeleton_operate_file_create_
  f_return_status fake_skeleton_operate_file_create(const fake_data_t data, const f_string_dynamic_t path, const bool executable, const f_string_static_t content) {
    f_status_t status = F_none;

    if (!path.used) return F_none;

    status = f_file_is(path.string, f_file_type_regular, F_false);

    if (status == F_true) {
      if (data.error.verbosity == f_console_verbosity_verbose) {
        fprintf(data.output.stream, "File '%s' already exists.%c", path.string, f_string_eol[0]);
      }

      return F_none;
    }

    // symbolic links might also be fine.
    if (status == F_false) {
      status = f_file_is(path.string, f_file_type_link, F_false);

      if (status == F_true) {
        if (data.error.verbosity == f_console_verbosity_verbose) {
          fprintf(data.output.stream, "File '%s' already exists (as a symbolic link).%c", path.string, f_string_eol[0]);
        }

        return F_none;
      }
    }

    if (status == F_false) {
      if (data.error.verbosity == f_console_verbosity_verbose) {
        fprintf(data.output.stream, "File '%s' already exists but is not a regular file (or symbolic link).%c", path.string, f_string_eol[0]);
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
          fprintf(data.error.to.stream, "%c", f_string_eol[0]);
          fl_color_print(data.error.to.stream, data.context.set.error, "%sThe file '", fll_error_print_error);
          fl_color_print(data.error.to.stream, data.context.set.notable, "%s", path.string);
          fl_color_print(data.error.to.stream, data.context.set.error, "' could not be created, a parent directory does not exist.%c", f_string_eol[0]);
        }
        else {
          fll_error_file_print(data.error, F_status_set_fine(status), "f_file_create", F_true, path.string, "create", fll_error_file_type_file);
        }

        return status;
      }

      if (data.error.verbosity == f_console_verbosity_verbose) {
        fprintf(data.output.stream, "File '%s' created.%c", path.string, f_string_eol[0]);
      }

      if (content.used) {
        f_file_t file = f_file_t_initialize;

        file.flag = f_file_flag_append_wo;
        file.size_write = content.used;

        status = f_file_open(path.string, 0, &file);

        if (F_status_is_error(status)) {
          fll_error_file_print(data.error, F_status_set_fine(status), "f_file_open", F_true, path.string, "pre-populate", fll_error_file_type_file);

          return status;
        }

        status = f_file_write(file, content, 0);

        if (F_status_is_error(status)) {
          fll_error_file_print(data.error, F_status_set_fine(status), "f_file_write", F_true, path.string, "pre-populate", fll_error_file_type_file);

          f_file_stream_close(F_true, &file);
          return status;
        }

        if (data.error.verbosity == f_console_verbosity_verbose) {
          fprintf(data.output.stream, "File '%s' pre-populated.%c", path.string, f_string_eol[0]);
        }

        f_file_stream_close(F_true, &file);
      }
    }
    else if (F_status_is_error(status)) {
      fll_error_file_print(data.error, F_status_set_fine(status), "f_file_is", F_true, path.string, "create", fll_error_file_type_file);

      return status;
    }

    return F_none;
  }
#endif // _di_fake_skeleton_operate_file_create_

#ifdef __cplusplus
} // extern "C"
#endif
