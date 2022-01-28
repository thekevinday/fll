#include "error.h"
#include "private-error.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_error_file_type_
  const f_string_static_t fll_error_file_type_directory_s = macro_f_string_static_t_initialize2(FLL_error_file_type_directory_s, 0, FLL_error_file_type_directory_s_length);
  const f_string_static_t fll_error_file_type_file_s = macro_f_string_static_t_initialize2(FLL_error_file_type_file_s, 0, FLL_error_file_type_file_s_length);
  const f_string_static_t fll_error_file_type_path_s = macro_f_string_static_t_initialize2(FLL_error_file_type_path_s, 0, FLL_error_file_type_path_s_length);
  const f_string_static_t fll_error_file_type_pipe_s = macro_f_string_static_t_initialize2(FLL_error_file_type_pipe_s, 0, FLL_error_file_type_pipe_s_length);
#endif // _di_fll_error_file_type_

#ifdef __cplusplus
} // extern "C"
#endif
