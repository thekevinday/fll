#include "fss_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_write_payload_strings_
  const f_string_static_t fss_write_payload_s = macro_f_string_static_t_initialize(FSS_WRITE_payload_s, 0, FSS_WRITE_payload_s_length);

  const f_string_static_t fss_write_payload_standard_s = macro_f_string_static_t_initialize(FSS_WRITE_payload_standard_s, 0, FSS_WRITE_payload_standard_s_length);

  const f_string_static_t fss_write_payload_program_name_s = macro_f_string_static_t_initialize(FSS_WRITE_payload_program_name_s, 0, FSS_WRITE_payload_program_name_s_length);
  const f_string_static_t fss_write_payload_program_name_long_s = macro_f_string_static_t_initialize(FSS_WRITE_payload_program_name_long_s, 0, FSS_WRITE_payload_program_name_long_s_length);

  const f_string_static_t fss_write_format_code_short_000e_s = macro_f_string_static_t_initialize(FSS_WRITE_format_code_short_000e_s, 0, FSS_WRITE_format_code_short_000e_s_length);
  const f_string_static_t fss_write_format_code_long_000e_s = macro_f_string_static_t_initialize(FSS_WRITE_format_code_long_000e_s, 0, FSS_WRITE_format_code_long_000e_s_length);
  const f_string_static_t fss_write_format_code_human_000e_s = macro_f_string_static_t_initialize(FSS_WRITE_format_code_human_000e_s, 0, FSS_WRITE_format_code_human_000e_s_length);
#endif // _di_fss_write_payload_strings_

#ifndef _di_fss_write_payload_setting_load_
  void fss_write_payload_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, fss_write_setting_t * const setting) {

    if (!main || !setting) return;

    f_array_lengths_t * const values = &main->parameters.array[fss_write_parameter_object_e].values;
    f_string_static_t * const argv = main->parameters.arguments.array;

    if ((main->parameters.array[fss_write_parameter_object_e].result & f_console_result_value_e) && values->used) {

      for (f_array_length_t i = 0; i < values->used; ++i) {

        if (fl_string_dynamic_compare(argv[values->array[i]], fss_write_payload_s) == F_equal_to && i + 1 < values->used) {
          setting->status = F_status_set_error(F_parameter);

          fss_write_payload_print_error_payload_not_last(setting, main->error);

          return;
        }
      } // for
    }
  }
#endif // _di_fss_write_payload_setting_load_

#ifdef __cplusplus
} // extern "C"
#endif
