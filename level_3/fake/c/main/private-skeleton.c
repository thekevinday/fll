#include "fake.h"
#include "private-common.h"
#include "private-skeleton.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_skeleton_operate_
  f_status_t fake_skeleton_operate(fake_data_t * const data) {

    f_status_t status = F_none;

    if (data->main->message.verbosity != f_console_verbosity_quiet_e && data->main->message.verbosity != f_console_verbosity_error_e) {
      fll_print_format("%rGenerating skeleton structure.%r", data->main->message.to, f_string_eol_s, f_string_eol_s);

      if (data->main->message.verbosity >= f_console_verbosity_verbose_e) {
        fll_print_dynamic(f_string_eol_s, data->main->message.to);
      }
    }

    {
      f_string_static_t sources = f_string_static_t_initialize;
      f_string_static_t sources_bash = f_string_static_t_initialize;
      f_string_static_t sources_c = f_string_static_t_initialize;
      f_string_static_t sources_cpp = f_string_static_t_initialize;
      f_string_static_t sources_script = f_string_static_t_initialize;

      fake_skeleton_path_source_length(data, &f_string_empty_s, &sources);
      fake_skeleton_path_source_length(data, &fake_path_part_c_s, &sources_c);
      fake_skeleton_path_source_length(data, &fake_path_part_cpp_s, &sources_cpp);
      fake_skeleton_path_source_length(data, &fake_path_part_script_s, &sources_script);
      fake_skeleton_path_source_length(data, &fake_path_part_shell_s, &sources_bash);

      f_char_t sources_string[sources.used + 1];
      f_char_t sources_bash_string[sources_bash.used + 1];
      f_char_t sources_c_string[sources_c.used + 1];
      f_char_t sources_cpp_string[sources_cpp.used + 1];
      f_char_t sources_script_string[sources_script.used + 1];

      sources.string = sources_string;
      sources_bash.string = sources_bash_string;
      sources_c.string = sources_c_string;
      sources_cpp.string = sources_cpp_string;
      sources_script.string = sources_script_string;

      fake_skeleton_path_source_string(data, &f_string_empty_s, &sources);
      fake_skeleton_path_source_string(data, &fake_path_part_c_s, &sources_c);
      fake_skeleton_path_source_string(data, &fake_path_part_cpp_s, &sources_cpp);
      fake_skeleton_path_source_string(data, &fake_path_part_script_s, &sources_script);
      fake_skeleton_path_source_string(data, &fake_path_part_shell_s, &sources_bash);

      const f_string_static_t path[] = {
        data->setting->build,
        data->setting->data,
        data->path_data_build,
        data->path_data_documentation,
        data->path_data_settings,
        data->path_documents,
        data->path_licenses,
        data->setting->sources,
        sources,
        sources_bash,
        sources_c,
        sources_cpp,
        sources_script,
        data->setting->work,
        data->path_work_includes,
        data->path_work_libraries,
        data->path_work_libraries_script,
        data->path_work_libraries_shared,
        data->path_work_libraries_static,
        data->path_work_programs,
        data->path_work_programs_script,
        data->path_work_programs_shared,
        data->path_work_programs_static,
        fake_path_part_specifications_s,
      };

      for (uint8_t i = 0; i < 24; ++i) {

        status = fake_skeleton_operate_directory_create(data, path[i]);

        if (F_status_is_error(status)) {
          fake_print_error(data->setting, status, data->main->error, macro_fake_f(fake_skeleton_operate_directory_create));

          return status;
        }
      } // for

      if (data->main->message.verbosity >= f_console_verbosity_verbose_e) {
        fll_print_dynamic(f_string_eol_s, data->main->message.to);
      }
    }

    if (F_status_is_error_not(status)) {
      status = fake_skeleton_operate_file_create(data, data->file_data_build_defines, F_false, fake_make_skeleton_content_defines_s);
    }

    if (F_status_is_error_not(status)) {
      status = fake_skeleton_operate_file_create(data, data->file_data_build_dependencies, F_false, fake_make_skeleton_content_dependencies_s);
    }

    if (F_status_is_error_not(status)) {
      status = fake_skeleton_operate_file_create(data, data->file_data_build_process_post, F_true, fake_make_skeleton_content_process_post_s);
    }

    if (F_status_is_error_not(status)) {
      status = fake_skeleton_operate_file_create(data, data->file_data_build_process_pre, F_true, fake_make_skeleton_content_process_pre_s);
    }

    if (F_status_is_error_not(status)) {
      status = fake_skeleton_operate_file_create(data, data->file_data_build_settings, F_false, fake_make_skeleton_content_settings_s);
    }

    if (F_status_is_error_not(status)) {
      status = fake_skeleton_operate_file_create(data, data->file_documents_readme, F_false, f_string_empty_s);
    }

    if (F_status_is_error_not(status)) {
      status = fake_skeleton_operate_file_create(data, data->file_data_build_fakefile, F_false, fake_make_skeleton_content_fakefile_s);
    }

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fake_skeleton_operate_

#ifndef _di_fake_skeleton_operate_directory_create_
  f_status_t fake_skeleton_operate_directory_create(fake_data_t * const data, const f_string_static_t path) {

    if (!path.used) return F_none;

    f_status_t status = f_directory_exists(path);

    if (status == F_true) {
      if (data->main->error.verbosity >= f_console_verbosity_verbose_e) {
        fll_print_format("Directory '%Q' already exists.%r", data->main->message.to, path, f_string_eol_s);
      }

      return F_none;
    }

    if (status == F_false) {
      if (data->main->error.verbosity > f_console_verbosity_quiet_e) {
        f_file_stream_lock(data->main->error.to);

        fl_print_format("%r%[%QThe path '%]", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
        fl_print_format("%[%Q%]", data->main->error.to, data->main->error.notable, path, data->main->error.notable);
        fl_print_format("%[' exists but is not a directory.%]%r", data->main->error.to, data->main->error.context, data->main->error.context, f_string_eol_s);

        f_file_stream_unlock(data->main->error.to);
      }

      return F_status_set_warning(F_failure);
    }
    else if (status == F_file_found_not) {
      status = f_directory_create(path, F_file_mode_all_rwx_d);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_file_found_not) {
          f_file_stream_lock(data->main->error.to);

          fl_print_format("%r%[%QThe path '%]", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
          fl_print_format("%[%Q%]", data->main->error.to, data->main->error.notable, path, data->main->error.notable);
          fl_print_format("%[' could not be created, a parent directory does not exist.%]%r", data->main->error.to, data->main->error.context, data->main->error.context, f_string_eol_s);

          f_file_stream_unlock(data->main->error.to);
        }
        else {
          fake_print_error_file(data->setting, status, data->main->error, macro_fake_f(f_directory_create), path, f_file_operation_create_s, fll_error_file_type_directory_e);
        }

        return status;
      }

      if (data->main->error.verbosity >= f_console_verbosity_verbose_e) {
        fll_print_format("Directory '%Q' created.%r", data->main->message.to, path, f_string_eol_s);
      }
    }
    else if (F_status_is_error(status)) {
      fake_print_error_file(data->setting, status, data->main->error, macro_fake_f(f_directory_exists), path, f_file_operation_create_s, fll_error_file_type_directory_e);

      return status;
    }

    return F_none;
  }
#endif // _di_fake_skeleton_operate_directory_create_

#ifndef _di_fake_skeleton_operate_file_create_
  f_status_t fake_skeleton_operate_file_create(fake_data_t * const data, const f_string_static_t path, const bool executable, const f_string_static_t content) {

    f_status_t status = F_none;

    if (!path.used) return F_none;

    status = f_file_is(path, F_file_type_regular_d, F_false);

    if (status == F_true) {
      if (data->main->error.verbosity >= f_console_verbosity_verbose_e) {
        fll_print_format("File '%Q' already exists.%r", data->main->message.to, path, f_string_eol_s);
      }

      return F_none;
    }

    // symbolic links might also be fine.
    if (status == F_false) {
      status = f_file_is(path, F_file_type_link_d, F_false);

      if (status == F_true) {
        if (data->main->error.verbosity >= f_console_verbosity_verbose_e) {
          fll_print_format("File '%Q' already exists (as a symbolic link).%r", data->main->message.to, path, f_string_eol_s);
        }

        return F_none;
      }
    }

    if (status == F_false) {
      if (data->main->error.verbosity >= f_console_verbosity_verbose_e) {
        fll_print_format("File '%Q' already exists but is not a regular file (or symbolic link).%r", data->main->message.to, path, f_string_eol_s);
      }

      return F_status_set_warning(F_none);
    }
    else if (F_status_set_fine(status) == F_file_found_not) {
      mode_t mode = F_file_mode_all_rw_d;

      if (executable) {
        mode = F_file_mode_all_rwx_d;
      }

      status = f_file_create(path, mode, F_true);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_file_found_not) {
          f_file_stream_lock(data->main->error.to);

          fl_print_format("%r%[%QThe file '%]", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
          fl_print_format("%[%Q%]", data->main->error.to, data->main->error.notable, path, data->main->error.notable);
          fl_print_format("%[' could not be created, a parent directory does not exist.%]%r", data->main->error.to, data->main->error.context, data->main->error.context, f_string_eol_s);

          f_file_stream_unlock(data->main->error.to);
        }
        else {
          fake_print_error_file(data->setting, status, data->main->error, macro_fake_f(f_file_create), path, f_file_operation_create_s, fll_error_file_type_file_e);
        }

        return status;
      }

      if (data->main->error.verbosity >= f_console_verbosity_verbose_e) {
        fll_print_format("File '%Q' created.%r", data->main->message.to, path, f_string_eol_s);
      }

      if (content.used) {
        f_file_t file = f_file_t_initialize;

        file.flag = F_file_flag_append_wo_d;
        file.size_write = content.used;

        status = f_file_open(path, 0, &file);

        if (F_status_is_error(status)) {
          fake_print_error_file(data->setting, status, data->main->error, macro_fake_f(f_file_open), path, fake_common_file_populate_pre_s, fll_error_file_type_file_e);

          return status;
        }

        status = f_file_write(file, content, 0);

        if (F_status_is_error(status)) {
          fake_print_error_file(data->setting, status, data->main->error, macro_fake_f(f_file_write), path, fake_common_file_populate_pre_s, fll_error_file_type_file_e);

          f_file_stream_flush(file);
          f_file_stream_close(&file);

          return status;
        }

        if (data->main->error.verbosity >= f_console_verbosity_verbose_e) {
          fll_print_format("File '%Q' pre-populated.%r", data->main->message.to, path, f_string_eol_s);
        }

        f_file_stream_flush(file);
        f_file_stream_close(&file);
      }
    }
    else if (F_status_is_error(status)) {
      fake_print_error_file(data->setting, status, data->main->error, macro_fake_f(f_file_is), path, f_file_operation_create_s, fll_error_file_type_file_e);

      return status;
    }

    return F_none;
  }
#endif // _di_fake_skeleton_operate_file_create_

#ifndef _di_fake_skeleton_path_source_length_
  void fake_skeleton_path_source_length(fake_data_t * const data, const f_string_static_t *partial, f_string_static_t * const source) {

    source->used = data->setting->sources.used + partial->used;
  }
#endif // _di_fake_skeleton_path_source_length_

#ifndef _di_fake_skeleton_path_source_string_
  void fake_skeleton_path_source_string(fake_data_t * const data, const f_string_static_t *partial, f_string_static_t * const source) {

    source->used = 0;

    memcpy(source->string, data->setting->sources.string, sizeof(f_char_t) * data->setting->sources.used);
    source->used += data->setting->sources.used;

    memcpy(source->string + source->used, partial->string, sizeof(f_char_t) * partial->used);
    source->used += partial->used;

    source->string[source->used] = 0;
  }
#endif // _di_fake_skeleton_path_source_string_

#ifdef __cplusplus
} // extern "C"
#endif
