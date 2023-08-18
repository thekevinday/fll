#include "../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_print_warning_build_directory_not_directory_
  f_status_t fake_print_warning_build_directory_not_directory(fl_print_t * const print, f_string_static_t path) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_context_wrapped_variable(print, "The build directory ", path, " exists but is not a directory");

    return F_okay;
  }
#endif // _di_fake_print_warning_build_directory_not_directory_

#ifndef _di_fake_print_warning_path_exists_not_directory_
  f_status_t fake_print_warning_path_exists_not_directory(fl_print_t * const print, const f_string_static_t path) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_context_wrapped_variable(print, "The path ", path, " exists but is not a directory");

    return F_okay;
  }
#endif // _di_fake_print_warning_path_exists_not_directory_

#ifdef __cplusplus
} // extern "C"
#endif
