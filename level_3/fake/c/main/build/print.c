#include "../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_print_linked_file_
  f_status_t fake_build_print_linked_file(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t from, const f_string_static_t to) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_verbose_e) return F_output_not; // @fixme this function needs to be a "verbose" function rather than a "normal" print function.

    fake_print_wrapped_variables(setting, print, "Linked file ", from, " to ", to, 0);

    return F_none;
  }
#endif // _di_fake_build_print_linked_file_

#ifndef _di_fake_build_print_skeleton_build_base_
  f_status_t fake_build_print_skeleton_build_base(fake_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_normal_e) return F_output_not;

    fll_print_dynamic_raw(f_string_eol_s, print.to);
    fake_print_context_important_simple(setting, print, "Creating base build directories");

    return F_none;
  }
#endif // _di_fake_build_print_skeleton_build_base_

#ifdef __cplusplus
} // extern "C"
#endif
