#include "../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_print_common_simple_
  void fake_print_common_simple(fl_print_t * const print, const f_string_t message) {

    if (!print) return;

    fll_print_format("%S.%r", print->to, message, f_string_eol_s);
  }
#endif // _di_fake_print_common_simple_

#ifndef _di_fake_print_common_simple_variable_
  void fake_print_common_simple_variable(fl_print_t * const print, const f_string_t message, const f_string_static_t variable) {

    if (!print) return;

    fll_print_format("%S'%[%Q%]'.%r", print->to, message, print->set->notable, variable, print->set->notable, f_string_eol_s);
  }
#endif // _di_fake_print_common_simple_variable_

#ifndef _di_fake_print_common_wrapped_variable_
  void fake_print_common_wrapped_variable(fl_print_t * const print, const f_string_t before, const f_string_static_t variable, const f_string_t after) {

    if (!print) return;

    fll_print_format("%S'%[%Q%]'%S.%r", print->to, before, print->set->notable, variable, print->set->notable, after, f_string_eol_s);
  }
#endif // _di_fake_print_common_wrapped_variable_

#ifndef _di_fake_print_common_wrapped_variables_
  void fake_print_common_wrapped_variables(fl_print_t * const print, const f_string_t before, const f_string_static_t first, const f_string_t between, const f_string_static_t second, const f_string_t after) {

    if (!print) return;

    f_file_stream_lock(print->to);

    fl_print_format("%S'", print->to, before);
    fl_print_format("%[%Q%]", print->to, print->notable, first, print->notable);
    fl_print_format("'%S'", print->to, between);
    fl_print_format("%[%Q%]", print->to, print->notable, second, print->notable);
    fl_print_format("'%S.%r", print->to, after, f_string_eol_s);

    f_file_stream_unlock(print->to);
  }
#endif // _di_fake_print_common_wrapped_variables_

#ifdef __cplusplus
} // extern "C"
#endif
