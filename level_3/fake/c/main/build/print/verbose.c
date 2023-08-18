#include "../../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_print_verbose_create_directory_
  f_status_t fake_build_print_verbose_create_directory(fl_print_t * const print, const f_string_static_t directory) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_common_simple_variable(print, "Created directory ", directory);

    return F_okay;
  }
#endif // _di_fake_build_print_verbose_create_directory_

#ifndef _di_fake_build_print_verbose_linked_file_
  f_status_t fake_build_print_verbose_linked_file(fl_print_t * const print, const f_string_static_t from, const f_string_static_t to) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_common_wrapped_variables(print, "Linked file ", from, " to ", to, 0);

    return F_okay;
  }
#endif // _di_fake_build_print_verbose_linked_file_

#ifdef __cplusplus
} // extern "C"
#endif
