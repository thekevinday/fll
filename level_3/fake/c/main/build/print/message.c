#include "../../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_print_message_copying_
  f_status_t fake_build_print_message_copying(fl_print_t * const print, const f_string_static_t path) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_normal_e) return F_output_not;

    fll_print_dynamic_raw(f_string_eol_s, print->to);
    fake_print_context_important_simple_variable(print, "Copying ", path, 0);

    return F_okay;
  }
#endif // _di_fake_build_print_message_copying_

#ifndef _di_fake_build_print_message_skeleton_build_base_
  f_status_t fake_build_print_message_skeleton_build_base(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_normal_e) return F_output_not;

    fll_print_dynamic_raw(f_string_eol_s, print->to);
    fake_print_context_important_simple(print, "Creating base build directories");

    return F_okay;
  }
#endif // _di_fake_build_print_message_skeleton_build_base_

#ifdef __cplusplus
} // extern "C"
#endif
