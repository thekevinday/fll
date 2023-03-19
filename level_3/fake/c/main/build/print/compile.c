#include "../../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_print_compile_library_shared_
  f_status_t fake_build_print_compile_library_shared(fake_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_normal_e) return F_output_not;

    fll_print_dynamic_raw(f_string_eol_s, print.to);
    fake_print_context_important_simple(setting, print, "Compiling shared library");

    return F_none;
  }
#endif // _di_fake_build_print_compile_library_shared_

#ifndef _di_fake_build_print_compile_library_static_
  f_status_t fake_build_print_compile_library_static(fake_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_normal_e) return F_output_not;

    fll_print_dynamic_raw(f_string_eol_s, print.to);
    fake_print_context_important_simple(setting, print, "Compiling static library");

    return F_none;
  }
#endif // _di_fake_build_print_compile_library_static_

#ifndef _di_fake_build_print_compile_object_shared_
  f_status_t fake_build_print_compile_object_shared(fake_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_normal_e) return F_output_not;

    fll_print_dynamic_raw(f_string_eol_s, print.to);
    fake_print_context_important_simple(setting, print, "Compiling shared object");

    return F_none;
  }
#endif // _di_fake_build_print_compile_object_shared_

#ifndef _di_fake_build_print_compile_object_static_
  f_status_t fake_build_print_compile_object_static(fake_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_normal_e) return F_output_not;

    fll_print_dynamic_raw(f_string_eol_s, print.to);
    fake_print_context_important_simple(setting, print, "Compiling static object");

    return F_none;
  }
#endif // _di_fake_build_print_compile_object_static_

#ifndef _di_fake_build_print_compile_object_static_library_
  f_status_t fake_build_print_compile_object_static_library(fake_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_normal_e) return F_output_not;

    fll_print_dynamic_raw(f_string_eol_s, print.to);
    fake_print_context_important_simple(setting, print, "Compiling objects for static library");

    return F_none;
  }
#endif // _di_fake_build_print_compile_object_static_library_

#ifndef _di_fake_build_print_compile_program_shared_
  f_status_t fake_build_print_compile_program_shared(fake_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_normal_e) return F_output_not;

    fll_print_dynamic_raw(f_string_eol_s, print.to);
    fake_print_context_important_simple(setting, print, "Compiling shared program");

    return F_none;
  }
#endif // _di_fake_build_print_compile_program_shared_

#ifndef _di_fake_build_print_compile_program_static_
  f_status_t fake_build_print_compile_program_static(fake_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_normal_e) return F_output_not;

    fll_print_dynamic_raw(f_string_eol_s, print.to);
    fake_print_context_important_simple(setting, print, "Compiling static program");

    return F_none;
  }
#endif // _di_fake_build_print_compile_program_static_

#ifdef __cplusplus
} // extern "C"
#endif
