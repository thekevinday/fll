#include "error.h"
#include "private-error.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_error_file_type_
  const f_string_t fll_error_file_type_string_directory_s = fll_error_file_type_string_directory;
  const f_string_t fll_error_file_type_string_file_s = fll_error_file_type_string_file;
  const f_string_t fll_error_file_type_string_pipe_s = fll_error_file_type_string_pipe;
#endif // _di_fll_error_file_type_

#ifndef _di_fll_error_print_t_
  const f_string_t fll_error_print_debug_s = fll_error_print_debug;
  const f_string_t fll_error_print_error_s = fll_error_print_error;
  const f_string_t fll_error_print_warning_s = fll_error_print_warning;
#endif // _di_fll_error_print_t_

#ifdef __cplusplus
} // extern "C"
#endif
