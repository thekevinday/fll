#include "fake.h"
#include "private-common.h"
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

    if (main.output.verbosity != f_console_verbosity_quiet) {
      fll_print_format("%cGenerating skeleton structure.%c", main.output.to.stream, f_string_eol_s[0], f_string_eol_s[0]);
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

      for (uint8_t i = 0; i < 20; ++i) {

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
      macro_f_string_dynamic_t_delete_simple(file_data_build_process_post);
      macro_f_string_dynamic_t_delete_simple(file_data_build_process_pre);
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
        fll_print_format("Directory '%Q' already exists.%c", main.output.to.stream, path, f_string_eol_s[0]);
      }

      return F_none;
    }

    if (status == F_false) {
      if (main.error.verbosity != f_console_verbosity_quiet) {
        flockfile(main.error.to.stream);

        fl_print_format("%c%[%SThe path '%]", main.error.to.stream, f_string_eol_s[0], main.error.context, main.error.prefix, main.error.context);
        fl_print_format("%[%Q%]", main.error.to.stream, main.error.notable, path, main.error.notable);
        fl_print_format("%[' exists but is not a directory.%]%c", main.error.to.stream, main.error.context, main.error.context, f_string_eol_s[0]);

        funlockfile(main.error.to.stream);
      }

      return F_status_set_warning(F_failure);
    }
    else if (status == F_file_found_not) {
      status = f_directory_create(path.string, f_file_mode_all_rwx);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_file_found_not) {
          flockfile(main.error.to.stream);

          fl_print_format("%c%[%SThe path '%]", main.error.to.stream, f_string_eol_s[0], main.error.context, main.error.prefix, main.error.context);
          fl_print_format("%[%Q%]", main.error.to.stream, main.error.notable, path, main.error.notable);
          fl_print_format("%[' could not be created, a parent directory does not exist.%]%c", main.error.to.stream, main.error.context, main.error.context, f_string_eol_s[0]);

          funlockfile(main.error.to.stream);
        }
        else {
          fll_error_file_print(main.error, F_status_set_fine(status), "f_directory_create", F_true, path.string, "create", fll_error_file_type_directory);
        }

        return status;
      }

      if (main.error.verbosity == f_console_verbosity_verbose) {
        fll_print_format("Directory '%Q' created.%c", main.output.to.stream, path, f_string_eol_s[0]);
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
        fll_print_format("File '%Q' already exists.%c", main.output.to.stream, path, f_string_eol_s[0]);
      }

      return F_none;
    }

    // symbolic links might also be fine.
    if (status == F_false) {
      status = f_file_is(path.string, f_file_type_link, F_false);

      if (status == F_true) {
        if (main.error.verbosity == f_console_verbosity_verbose) {
          fll_print_format("File '%Q' already exists (as a symbolic link).%c", main.output.to.stream, path, f_string_eol_s[0]);
        }

        return F_none;
      }
    }

    if (status == F_false) {
      if (main.error.verbosity == f_console_verbosity_verbose) {
        fll_print_format("File '%Q' already exists but is not a regular file (or symbolic link).%c", main.output.to.stream, path, f_string_eol_s[0]);
      }

      return F_status_set_warning(F_none);
    }
    else if (F_status_set_fine(status) == F_file_found_not) {
      mode_t mode = f_file_mode_all_rw;

      if (executable) {
        mode = f_file_mode_all_rwx;
      }

      status = f_file_create(path.string, mode, F_true);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_file_found_not) {
          flockfile(main.error.to.stream);

          fl_print_format("%c%[%SThe file '%]", main.error.to.stream, f_string_eol_s[0], main.error.context, main.error.prefix, main.error.context);
          fl_print_format("%[%Q%]", main.error.to.stream, main.error.notable, path, main.error.notable);
          fl_print_format("%[' could not be created, a parent directory does not exist.%]%c", main.error.to.stream, main.error.context, main.error.context, f_string_eol_s[0]);

          funlockfile(main.error.to.stream);
        }
        else {
          fll_error_file_print(main.error, F_status_set_fine(status), "f_file_create", F_true, path.string, "create", fll_error_file_type_file);
        }

        return status;
      }

      if (main.error.verbosity == f_console_verbosity_verbose) {
        fll_print_format("File '%Q' created.%c", main.output.to.stream, path, f_string_eol_s[0]);
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
          fll_print_format("File '%Q' pre-populated.%c", main.output.to.stream, path, f_string_eol_s[0]);
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
