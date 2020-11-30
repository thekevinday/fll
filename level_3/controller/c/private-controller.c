#include "controller.h"
#include "private-control.h"
#include "private-entry.h"
#include "private-rule.h"
#include "private-controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_file_load_
  f_return_status controller_file_load(const controller_data_t data, const controller_setting_t setting, const f_string_t path_prefix, const f_string_static_t path_name, const f_string_t path_suffix, const f_string_length_t path_prefix_length, const f_string_length_t path_suffix_length, f_string_dynamic_t *path_file, f_string_dynamic_t *buffer) {
    f_status_t status = F_none;
    f_file_t file = f_file_t_initialize;

    status = fl_string_append(path_prefix, path_prefix_length, path_file);

    if (F_status_is_error_not(status)) {
      status = fl_string_append(f_path_separator, f_path_separator_length, path_file);
    }

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "fl_string_append", F_true);
      return status;
    }

    status = fl_string_dynamic_append(path_name, path_file);

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_append", F_true);
      return status;
    }

    status = fl_string_append(f_path_extension_separator, f_path_extension_separator_length, path_file);

    if (F_status_is_error_not(status)) {
      status = fl_string_append(path_suffix, path_suffix_length, path_file);
    }

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "fl_string_append", F_true);
      return status;
    }

    status = fl_string_dynamic_terminate_after(path_file);

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_terminate_after", F_true);
      return status;
    }

    const f_string_length_t path_length = setting.path_setting.used ? setting.path_setting.used + f_path_separator_length + path_file->used : path_file->used;
    char path[path_length + 1];

    if (setting.path_setting.used) {
      memcpy(path, setting.path_setting.string, setting.path_setting.used);
      memcpy(path + setting.path_setting.used + f_path_separator_length, path_file->string, path_file->used);

      path[setting.path_setting.used] = f_path_separator[0];
    }

    path[path_length] = 0;

    status = f_file_stream_open(path, 0, &file);

    if (F_status_is_error(status)) {
      fll_error_file_print(data.error, F_status_set_fine(status), "f_file_stream_open", F_true, path, "open", fll_error_file_type_file);
    }
    else {
      status = f_file_stream_read(file, 1, buffer);

      if (F_status_is_error(status)) {
        fll_error_file_print(data.error, F_status_set_fine(status), "f_file_stream_read", F_true, path, "read", fll_error_file_type_file);
      }
    }

    f_file_stream_close(F_true, &file);

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_controller_file_load_

#ifndef _di_controller_status_simplify_
  f_return_status controller_status_simplify(const f_status_t status) {

    if (status == F_memory_not || status == F_memory_allocation || status == F_memory_reallocation) {
      return F_status_set_error(F_memory);
    }

    if (status == F_file_open_max || status == F_space_not || status == F_busy) {
      return F_status_set_error(F_resource);
    }

    if (status == F_access_denied || status == F_filesystem_quota_block || status == F_prohibited || status == F_input_output) {
      return F_status_set_error(F_access);
    }

    if (status == F_incomplete_utf || status == F_incomplete_utf_block || status == F_incomplete_utf_eof || status == F_incomplete_utf_eol || status == F_incomplete_utf_eos || status == F_incomplete_utf_stop) {
      return F_status_set_error(F_encoding);
    }

    if (status == F_number || status == F_number_negative || status == F_number_positive || status == F_number_overflow) {
      return F_status_set_error(F_number);
    }

    if (status == F_parameter || status == F_found_not || status == F_interrupted) {
      return F_status_set_error(status);
    }

    return F_status_set_error(F_invalid);
  }
#endif // _di_controller_status_simplify_

#ifndef _di_controller_validate_define_name_
  f_return_status controller_validate_environment_name(const f_string_static_t name) {

    if (!name.used) return F_none;

    f_status_t status = F_none;

    if (name.string[0] != '_') {
      status = f_utf_is_alpha(name.string, name.used);

      if (F_status_is_error(status)) return status;
      if (status == F_false) return F_false;
    }

    for (f_string_length_t i = f_macro_utf_byte_width(name.string[0]); i < name.used; i += f_macro_utf_byte_width(name.string[i])) {

      if (name.string[i] == '_') continue;

      status = f_utf_is_alpha_digit(name.string, name.used);

      if (F_status_is_error(status)) return status;
      if (status == F_false) return F_false;
    } // for

    return F_true;
  }
#endif // _di_controller_validate_define_name_

#ifndef _di_controller_validate_has_graph_
  f_return_status controller_validate_has_graph(const f_string_static_t name) {

    if (!name.used) return F_none;

    f_status_t status = F_none;

    for (f_string_length_t i = 0; i < name.used; i += f_macro_utf_byte_width(name.string[i])) {

      status = f_utf_is_graph(name.string, name.used);

      if (F_status_is_error(status)) return status;
      if (status == F_true) return F_true;
    } // for

    return F_false;
  }
#endif // _di_controller_validate_has_graph_

#ifdef __cplusplus
} // extern "C"
#endif
