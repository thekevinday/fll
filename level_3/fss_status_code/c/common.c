#include "fss_status_code.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_status_code_program_help_parameters_
  const f_string_static_t fss_status_code_program_help_parameters_s = macro_f_string_static_t_initialize(FSS_STATUS_CODE_program_help_parameters_s, 0, FSS_STATUS_CODE_program_help_parameters_s_length);
#endif // _di_fss_status_code_program_help_parameters_

#ifndef _di_fss_status_code_parameters_
  const f_string_static_t fss_status_code_short_is_fine_s = macro_f_string_static_t_initialize(FSS_STATUS_CODE_short_is_fine_s, 0, FSS_STATUS_CODE_short_is_fine_s_length);
  const f_string_static_t fss_status_code_short_is_warning_s = macro_f_string_static_t_initialize(FSS_STATUS_CODE_short_is_warning_s, 0, FSS_STATUS_CODE_short_is_warning_s_length);
  const f_string_static_t fss_status_code_short_is_error_s = macro_f_string_static_t_initialize(FSS_STATUS_CODE_short_is_error_s, 0, FSS_STATUS_CODE_short_is_error_s_length);
  const f_string_static_t fss_status_code_short_number_s = macro_f_string_static_t_initialize(FSS_STATUS_CODE_short_number_s, 0, FSS_STATUS_CODE_short_number_s_length);

  const f_string_static_t fss_status_code_long_is_fine_s = macro_f_string_static_t_initialize(FSS_STATUS_CODE_long_is_fine_s, 0, FSS_STATUS_CODE_long_is_fine_s_length);
  const f_string_static_t fss_status_code_long_is_warning_s = macro_f_string_static_t_initialize(FSS_STATUS_CODE_long_is_warning_s, 0, FSS_STATUS_CODE_long_is_warning_s_length);
  const f_string_static_t fss_status_code_long_is_error_s = macro_f_string_static_t_initialize(FSS_STATUS_CODE_long_is_error_s, 0, FSS_STATUS_CODE_long_is_error_s_length);
  const f_string_static_t fss_status_code_long_number_s = macro_f_string_static_t_initialize(FSS_STATUS_CODE_long_number_s, 0, FSS_STATUS_CODE_long_number_s_length);
#endif // _di_fss_status_code_parameters_

#ifndef _di_fss_status_code_main_delete_
  f_status_t fss_status_code_main_delete(fll_program_data_t * const main) {

    return fll_program_data_delete(main);
  }
#endif // _di_fss_status_code_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif
