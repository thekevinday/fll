#include "../fake.h"
#include "print-verbose.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_print_error_cannot_create_due_to_parent_
  f_status_t fake_build_print_error_cannot_create_due_to_parent(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path) {

    if (!setting || print.verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_wrapped_variable(setting, print, "The path ", path, " could not be created, a parent directory is invalid or does not exist");

    return F_none;
  }
#endif // _di_fake_build_print_error_cannot_create_due_to_parent_

#ifndef _di_fake_build_print_error_exist_not_directory_
  f_status_t fake_build_print_error_exist_not_directory(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path) {

    if (!setting || print.verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_wrapped_variable(setting, print, "The path ", path, " exists but is not a directory");

    return F_none;
  }
#endif // _di_fake_build_print_error_exist_not_directory_

#ifdef __cplusplus
} // extern "C"
#endif
