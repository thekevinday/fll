#include "error.h"
#include "private-error.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_error_file_type_
  const f_string_t fll_error_file_type_directory_s = FLL_error_file_type_directory_s;
  const f_string_t fll_error_file_type_file_s = FLL_error_file_type_file_s;
  const f_string_t fll_error_file_type_pipe_s = FLL_error_file_type_pipe_s;
#endif // _di_fll_error_file_type_

#ifdef __cplusplus
} // extern "C"
#endif
