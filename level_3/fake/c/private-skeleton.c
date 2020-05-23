#include <level_3/fake.h>
#include "private-fake.h"
#include "private-skeleton.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_skeleton_operate_
  f_return_status fake_skeleton_operate(const fake_data data) {
    f_status status = F_none;

    if (data.verbosity != fake_verbosity_quiet) {
      printf("%c", f_string_eol);
      fl_color_print_line(f_type_output, data.context.important, data.context.reset, "Generating skeleton structure.");
    }

    {
      const f_string_dynamic *parameters_value[] = {
        &data.path_build,
        &data.path_data,
        &data.path_data_build,
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

      for (uint8_t i = 0; i < 19; i++) {
        status = fake_skeleton_operate_directory_create(data, *parameters_value[i]);

        if (F_status_is_error(status)) {
          fake_print_error(data.context, data.verbosity, F_status_set_fine(status), "fake_skeleton_operate_directory_create", F_true);
          return status;
        }
      } // for
    }

    f_string_dynamic file_data_build_process_post = f_string_dynamic_initialize;
    f_string_dynamic file_data_build_process_pre = f_string_dynamic_initialize;

    if (!F_status_is_error(status)) {
      status = fake_skeleton_operate_file_create(data, data.file_data_build_defines, F_false);
    }

    if (!F_status_is_error(status)) {
      status = fake_skeleton_operate_file_create(data, data.file_data_build_dependencies, F_false);
    }

    if (!F_status_is_error(status)) {
      status = fake_skeleton_operate_file_create(data, file_data_build_process_post, F_true);
    }

    if (!F_status_is_error(status)) {
      status = fake_skeleton_operate_file_create(data, file_data_build_process_pre, F_true);
    }

    if (!F_status_is_error(status)) {
      status = fake_skeleton_operate_file_create(data, data.file_data_build_settings, F_false);
    }

    if (!F_status_is_error(status)) {
      status = fake_skeleton_operate_file_create(data, data.file_documents_readme, F_false);
    }

    if (F_status_is_error(status)) {
      f_macro_string_dynamic_delete_simple(file_data_build_process_post);
      f_macro_string_dynamic_delete_simple(file_data_build_process_pre);
      return status;
    }

    return F_none;
  }
#endif // _di_fake_skeleton_operate_

#ifndef _di_fake_skeleton_operate_directory_create_
  f_return_status fake_skeleton_operate_directory_create(const fake_data data, const f_string_dynamic path) {
    f_status status = F_none;

    if (path.used == 0) return F_none;

    status = f_directory_exists(path.string);
    if (status == F_true) {
      if (data.verbosity == fake_verbosity_verbose) {
        printf("Directory '%s' already exists.%c", path.string, f_string_eol);
      }

      return F_none;
    }

    if (status == F_false) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol);
        fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: The path '");
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", path.string);
        fl_color_print_line(f_type_error, data.context.error, data.context.reset, "' exists but is not a directory.");
      }

      return F_status_set_warning(F_failure);
    }
    else if (status == F_file_found_not) {
      status = f_directory_create(path.string, f_file_mode_all_rwx);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_file_found_not) {
          fprintf(f_type_error, "%c", f_string_eol);
          fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: The path '");
          fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", path.string);
          fl_color_print_line(f_type_error, data.context.error, data.context.reset, "' could not be created, a parent directory does not exist.");
        }
        else {
          fake_print_error_file(data.context, data.verbosity, F_status_set_fine(status), "f_directory_create", path.string, "create", F_false, F_true);
        }

        return status;
      }

      if (data.verbosity == fake_verbosity_verbose) {
        printf("Directory '%s' created.%c", path.string, f_string_eol);
      }
    }
    else if (F_status_is_error(status)) {
      fake_print_error_file(data.context, data.verbosity, F_status_set_fine(status), "f_directory_exists", path.string, "create", F_false, F_true);
      return status;
    }

    return F_none;
  }
#endif // _di_fake_skeleton_operate_directory_create_

#ifndef _di_fake_skeleton_operate_file_create_
  f_return_status fake_skeleton_operate_file_create(const fake_data data, const f_string_dynamic path, const bool executable) {
    f_status status = F_none;

    if (path.used == 0) return F_none;

    status = f_file_is(path.string, f_file_type_file);
    if (status == F_true) {
      if (data.verbosity == fake_verbosity_verbose) {
        printf("File '%s' already exists.%c", path.string, f_string_eol);
      }

      return F_none;
    }

    // symbolic links might also be fine.
    if (status == F_false) {
      status = f_file_is(path.string, f_file_type_link);

      if (status == F_true) {
        if (data.verbosity == fake_verbosity_verbose) {
          printf("File '%s' already exists (as a symbolic link).%c", path.string, f_string_eol);
        }

        return F_none;
      }
    }

    if (status == F_false) {
      if (data.verbosity == fake_verbosity_verbose) {
        printf("File '%s' already exists but is not a regular file (or symbolic link).%c", path.string, f_string_eol);
      }

      return F_status_set_warning(F_none);
    }
    else if (status == F_file_found_not) {
      mode_t mode = f_file_mode_all_rw;

      if (executable) {
        mode = f_file_mode_all_rwx;
      }

      status = f_file_create(path.string, mode, F_true, F_true);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_file_found_not) {
          fprintf(f_type_error, "%c", f_string_eol);
          fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: The file '");
          fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", path.string);
          fl_color_print_line(f_type_error, data.context.error, data.context.reset, "' could not be created, a parent directory does not exist.");
        }
        else {
          fake_print_error_file(data.context, data.verbosity, F_status_set_fine(status), "f_file_create", path.string, "create", F_true, F_true);
        }

        return status;
      }

      if (data.verbosity == fake_verbosity_verbose) {
        printf("File '%s' created.%c", path.string, f_string_eol);
      }
    }
    else if (F_status_is_error(status)) {
      fake_print_error_file(data.context, data.verbosity, F_status_set_fine(status), "f_file_is", path.string, "create", F_true, F_true);
      return status;
    }

    return F_none;
  }
#endif // _di_fake_skeleton_operate_file_create_

#ifdef __cplusplus
} // extern "C"
#endif
