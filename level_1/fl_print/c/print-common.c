#include "print.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_print_t_
  const f_string_static_t fl_print_debug_s = macro_f_string_static_t_initialize(FL_print_debug_s, 0, FL_print_debug_s_length);
  const f_string_static_t fl_print_error_s = macro_f_string_static_t_initialize(FL_print_error_s, 0, FL_print_error_s_length);
  const f_string_static_t fl_print_warning_s = macro_f_string_static_t_initialize(FL_print_warning_s, 0, FL_print_warning_s_length);
#endif // _di_fl_print_t_

#ifdef __cplusplus
} // extern "C"
#endif
