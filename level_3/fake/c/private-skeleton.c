#include <level_3/fake.h>
#include "private-fake.h"
#include "private-skeleton.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_skeleton_operate_
  f_return_status fake_skeleton_operate(const fake_data data) {
    f_status status = f_none;

    if (data.verbosity != fake_verbosity_quiet) {
      printf("%c", f_string_eol);
      fl_color_print_line(f_standard_output, data.context.important, data.context.reset, "Generating skeleton structure.");
    }

    status = fake_skeleton_operate_directory_create(data, fake_path_documents);
    if (f_status_is_error(status)) return status;

    status = fake_skeleton_operate_directory_create(data, fake_path_data);
    if (f_status_is_error(status)) return status;

    status = fake_skeleton_operate_directory_create(data, fake_path_licenses);
    if (f_status_is_error(status)) return status;

    status = fake_skeleton_operate_directory_create(data, fake_path_sources);
    if (f_status_is_error(status)) return status;

    {
      const f_string_static parameter_strings[] = {
        data.path_build,
        data.path_build_documents,
        data.path_build_includes,
        data.path_build_libraries,
        data.path_build_libraries_script,
        data.path_build_libraries_shared,
        data.path_build_libraries_static,
        data.path_build_objects,
        data.path_build_process,
        data.path_build_programs,
        data.path_build_programs_script,
        data.path_build_programs_shared,
        data.path_build_programs_static,
        data.path_build_settings,
        data.path_work,
        data.path_source_build,
        data.path_source_common,
        data.path_source_data,
        data.path_source_documents,
        data.path_source_codes,
        data.path_source_licenses,
        data.path_source_settings,
      };

      // @todo this needs to create parent directories as well, for some paths.
      for (f_array_length i = 0; i < 22; i++) {
        if (parameter_strings[i].used == 0) continue;

        status = fake_skeleton_operate_directory_create(data, parameter_strings[i].string);
        if (f_status_is_error(status)) return status;
      } // for
    }

    if (data.path_work.used > 0) {
      const f_string parameter_strings[] = {
        fake_path_work_includes,
        fake_path_work_libraries,
        fake_path_work_libraries_script,
        fake_path_work_libraries_shared,
        fake_path_work_libraries_static,
        fake_path_work_programs,
        fake_path_work_programs_script,
        fake_path_work_programs_shared,
        fake_path_work_programs_static,
      };

      const uint8_t parameter_strings_length[] = {
        fake_path_work_includes_length,
        fake_path_work_libraries_length,
        fake_path_work_libraries_script_length,
        fake_path_work_libraries_shared_length,
        fake_path_work_libraries_static_length,
        fake_path_work_programs_length,
        fake_path_work_programs_script_length,
        fake_path_work_programs_shared_length,
        fake_path_work_programs_static_length,
      };

      f_string_dynamic path = f_string_dynamic_initialize;

      status = fl_string_dynamic_append_nulless(data.path_work, &path);
      if (f_status_is_error(status)) {
        f_macro_string_dynamic_delete_simple(path);
        return status;
      }

      for (f_array_length i = 0; i < 9; i++) {
        path.used = data.path_work.used;

        status = fl_string_append_nulless(parameter_strings[i], parameter_strings_length[i], &path);
        if (f_status_is_error(status)) {
          fake_print_error(data.context, data.verbosity, f_status_set_fine(status), "fl_string_dynamic_append_nulless", f_true);
          f_macro_string_dynamic_delete_simple(path);
          return status;
        }

        status = fl_string_dynamic_terminate(&path);
        if (f_status_is_error(status)) {
          fake_print_error(data.context, data.verbosity, f_status_set_fine(status), "fl_string_dynamic_terminate", f_true);
          f_macro_string_dynamic_delete_simple(path);
          return status;
        }

        status = fake_skeleton_operate_directory_create(data, path.string);
        if (f_status_is_error(status)) {
          f_macro_string_dynamic_delete_simple(path);
          return status;
        }
      } // for

      f_macro_string_dynamic_delete_simple(path);
    }

    return f_none;
  }
#endif // _di_fake_skeleton_operate_

#ifndef _di_fake_skeleton_operate_directory_create_
  f_return_status fake_skeleton_operate_directory_create(const fake_data data, const f_string path) {
    f_status status = f_none;

    status = f_directory_is(path);
    if (status == f_true) {
      if (data.verbosity == fake_verbosity_verbose) {
        printf("Directory '%s' already exists.%c", path, f_string_eol);
      }
    }
    else if (status == f_false) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_standard_error, "%c", f_string_eol);
        fl_color_print(f_standard_error, data.context.error, data.context.reset, "ERROR: The path '");
        fl_color_print(f_standard_error, data.context.notable, data.context.reset, "%s", path);
        fl_color_print_line(f_standard_error, data.context.error, data.context.reset, "' exists but is not a directory.");
      }

      return f_status_set_error(f_failure);
    }
    else if (status == f_file_not_found) {
      status = f_directory_create(path, f_file_mode_all_rwx);

      if (f_status_is_error(status)) {
        if (f_status_set_fine(status) == f_file_not_found) {
          fprintf(f_standard_error, "%c", f_string_eol);
          fl_color_print(f_standard_error, data.context.error, data.context.reset, "ERROR: The path '");
          fl_color_print(f_standard_error, data.context.notable, data.context.reset, "%s", path);
          fl_color_print_line(f_standard_error, data.context.error, data.context.reset, "' could not be created, a parent directory does not exist.");
        }
        else {
          fake_print_error(data.context, data.verbosity, f_status_set_fine(status), "f_directory_create", f_true);
        }

        return status;
      }

      if (data.verbosity == fake_verbosity_verbose) {
        printf("Directory '%s' created.%c", path, f_string_eol);
      }
    }
    else if (f_status_is_error(status)) {
      fake_print_error(data.context, data.verbosity, f_status_set_fine(status), "f_directory_is", f_true);
      return status;
    }

    return f_none;
  }
#endif // _di_fake_skeleton_operate_directory_create_

#ifdef __cplusplus
} // extern "C"
#endif
