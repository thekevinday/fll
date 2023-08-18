#include "../program.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_program_parameter_s_
  #ifndef _di_fll_program_parameter_filename_s_
    const f_string_static_t fll_program_parameter_filename_s = macro_f_string_static_t_initialize_1(FLL_program_parameter_filename_s, 0, FLL_program_parameter_filename_s_length);
  #endif // _di_fll_program_parameter_filename_s_

  #ifndef _di_fll_program_parameter_filenames_s_
    const f_string_static_t fll_program_parameter_filenames_s = macro_f_string_static_t_initialize_1(FLL_program_parameter_filenames_s, 0, FLL_program_parameter_filenames_s_length);
  #endif // _di_fll_program_parameter_filenames_s_
#endif // _di_fll_program_parameter_s_

#ifndef _di_fll_program_data_delete_
  f_status_t fll_program_data_delete(fll_program_data_t * const data) {
    #ifndef _di_level_2_parameter_checking_
      if (!data) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_okay;

    status = f_console_parameters_delete(&data->parameters);
    if (F_status_is_error(status)) return status;

    status = f_color_context_delete(&data->context);
    if (F_status_is_error(status)) return status;

    return F_okay;
  }
#endif // _di_fll_program_data_delete_

#ifndef _di_fll_program_data_destroy_
  f_status_t fll_program_data_destroy(fll_program_data_t * const data) {
    #ifndef _di_level_2_parameter_checking_
      if (!data) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_okay;

    status = f_console_parameters_destroy(&data->parameters);
    if (F_status_is_error(status)) return status;

    status = f_color_context_destroy(&data->context);
    if (F_status_is_error(status)) return status;

    return F_okay;
  }
#endif // _di_fll_program_data_destroy_

#ifdef __cplusplus
} // extern "C"
#endif
