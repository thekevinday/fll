#include "../fake.h"
#include "print-warning.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_make_print_warning_cannot_change_back_
  f_status_t fake_make_print_warning_cannot_change_back(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path, const f_status_t status) {

    if (print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%QFailed change back to original path '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, path, print.notable);
    fl_print_format("%[', status code =%] ", print.to, print.context, print.context);
    fl_print_format("%[%ui%]", print.to, print.notable, F_status_set_fine(status), print.notable);
    fl_print_format("%['.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_warning_cannot_change_back_

#ifndef _di_fake_make_print_warning_environment_name_already_added_
  f_status_t fake_make_print_warning_environment_name_already_added(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t name) {

    return fake_make_print_warning_simple_variable(setting, print, "The environment name", name, "is already added, replacing previous value");
  }
#endif // _di_fake_make_print_warning_environment_name_already_added_

#ifndef _di_fake_make_print_warning_environment_name_invalid_
  f_status_t fake_make_print_warning_environment_name_invalid(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t name) {

    return fake_make_print_warning_simple_variable(setting, print, "The environment name", name, "is invalid, ignoring");
  }
#endif // _di_fake_make_print_warning_environment_name_invalid_

#ifndef _di_fake_make_print_warning_fakefile_empty_
  f_status_t fake_make_print_warning_fakefile_empty(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t fakefile) {

    return fake_make_print_warning_simple_variable(setting, print, "The fakefile", fakefile, "is empty");
  }
#endif // _di_fake_make_print_warning_fakefile_empty_

#ifndef _di_fake_make_print_warning_file_not_found_
  f_status_t fake_make_print_warning_file_not_found(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t file) {

    return fake_make_print_warning_simple_variable(setting, print, "The file", file, "cannot be found");
  }
#endif // _di_fake_make_print_warning_file_not_found_

#ifndef _di_fake_make_print_warning_settings_content_empty_
  f_status_t fake_make_print_warning_settings_content_empty(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t fakefile, const f_string_dynamic_t buffer, const f_string_range_t range, const f_string_static_t name) {

    if (print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%QThe fakefile '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, fakefile, print.notable);
    fl_print_format("%[' has empty content for the '%]", print.to, print.context, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, name, print.notable);
    fl_print_format("%[' object '%]", print.to, print.context, print.context);
    fl_print_format("%[%/Q%]", print.to, print.notable, buffer, range, print.notable);
    fl_print_format("%['.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_warning_settings_content_empty_

#ifndef _di_fake_make_print_warning_settings_content_invalid_
  f_status_t fake_make_print_warning_settings_content_invalid(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t fakefile, const f_string_dynamic_t buffer, const f_string_range_t object, const f_string_range_t content, const f_string_static_t name) {

    if (print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%QThe fakefile '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, fakefile, print.notable);
    fl_print_format("%[' has invalid content '%]", print.to, print.context, print.context);
    fl_print_format("%[%/Q%]", print.to, print.notable, buffer, content, print.notable);
    fl_print_format("%[' for the '%]", print.to, print.context, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, name, print.notable);
    fl_print_format("%[' object '%]", print.to, print.context, print.context);
    fl_print_format("%[%/Q%]", print.to, print.notable, buffer, object, print.notable);
    fl_print_format("%['.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_warning_settings_content_invalid_

#ifndef _di_fake_make_print_warning_settings_content_multiple_
  f_status_t fake_make_print_warning_settings_content_multiple(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t fakefile, const f_string_static_t name) {

    return fake_make_print_warning_simple_variables(setting, print, "The fakefile", fakefile, "may only have a single content for the object", name, ", only using the first");
  }
#endif // _di_fake_make_print_warning_settings_content_multiple_

#ifndef _di_fake_make_print_warning_settings_object_multiple_
  f_status_t fake_make_print_warning_settings_object_multiple(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t fakefile, const f_string_static_t name) {

    return fake_make_print_warning_simple_variables(setting, print, "The object", name, "in the fakefile", fakefile, "may only be specified once, only using the first");
  }
#endif // _di_fake_make_print_warning_settings_object_multiple_

#ifndef _di_fake_make_print_warning_simple_variable_
  f_status_t fake_make_print_warning_simple_variable(fake_setting_t * const setting, const fl_print_t print, const f_string_t before, const f_string_static_t variable, const f_string_t after) {

    if (print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%Q%S '%]", print.to, print.context, print.prefix, before, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, variable, print.notable);
    fl_print_format("%['%S.%]%r", print.to, print.context, after, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_warning_simple_variable_

#ifndef _di_fake_make_print_warning_simple_variables_
  f_status_t fake_make_print_warning_simple_variables(fake_setting_t * const setting, const fl_print_t print, const f_string_t before, const f_string_static_t first, const f_string_t between, const f_string_static_t second, const f_string_t after) {

    if (print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%Q%S '%]", print.to, print.context, print.prefix, before, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, first, print.notable);
    fl_print_format("%[' %S '%]", print.to, print.context, between, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, second, print.notable);
    fl_print_format("%['%S.%]%r", print.to, print.context, after, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_warning_simple_variables_

#ifdef __cplusplus
} // extern "C"
#endif
