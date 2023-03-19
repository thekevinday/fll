#include "../../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_print_verbose_copied_file_
  f_status_t fake_build_print_verbose_copied_file(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t source, const f_string_static_t destination) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_wrapped_variables(setting, print, "Copied file ", source, " to ", destination, f_string_empty_s.string);

    return F_none;
  }
#endif // _di_fake_build_print_verbose_copied_file_

#ifndef _di_fake_build_print_verbose_create_directory_
  f_status_t fake_build_print_verbose_create_directory(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t directory) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_simple_variable(setting, print, "Created directory ", directory);

    return F_none;
  }
#endif // _di_fake_build_print_verbose_create_directory_

#ifdef __cplusplus
} // extern "C"
#endif
