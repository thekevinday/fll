#include "../../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_print_error_cannot_create_due_to_parent_
  f_status_t fake_build_print_error_cannot_create_due_to_parent(fl_print_t * const print, const f_string_static_t path) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_wrapped_variable(print, "The path ", path, " could not be created, a parent directory is invalid or does not exist");

    return F_okay;
  }
#endif // _di_fake_build_print_error_cannot_create_due_to_parent_

#ifndef _di_fake_build_print_error_exist_not_directory_
  f_status_t fake_build_print_error_exist_not_directory(fl_print_t * const print, const f_string_static_t path) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_wrapped_variable(print, "The path ", path, " exists but is not a directory");

    return F_okay;
  }
#endif // _di_fake_build_print_error_exist_not_directory_

#ifndef _di_fake_build_print_error_missing_required_setting_
  f_status_t fake_build_print_error_missing_required_setting(fl_print_t * const print, const f_string_static_t name, const f_string_static_t path) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_wrapped_variables(print, "The setting ", name, " is required but is not specified in the settings file ", path, 0);

    return F_okay;
  }
#endif // _di_fake_build_print_error_missing_required_setting_

#ifndef _di_fake_build_print_error_mode_invalid_
  f_status_t fake_build_print_error_mode_invalid(fl_print_t * const print, const f_string_static_t mode, const f_string_static_t path) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_wrapped_variables(print, "The specified mode ", mode, " in the settings file ", path, " is not a valid mode");

    return F_okay;
  }
#endif // _di_fake_build_print_error_mode_invalid_

#ifndef _di_fake_build_print_error_setting_too_long_
  f_status_t fake_build_print_error_setting_too_long(fl_print_t * const print, const f_string_static_t path) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_wrapped_variable(print, "A setting in the settings file ", path, " is too long");

    return F_okay;
  }
#endif // _di_fake_build_print_error_setting_too_long_

#ifndef _di_fake_build_print_error_setting_value_too_long_
  f_status_t fake_build_print_error_setting_value_too_long(fl_print_t * const print, const f_string_static_t name, const f_string_static_t path) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_wrapped_variables(print, "The values for the setting ", name, " of the setting file ", path, " is too long");

    return F_okay;
  }
#endif // _di_fake_build_print_error_setting_value_too_long_

#ifdef __cplusplus
} // extern "C"
#endif
