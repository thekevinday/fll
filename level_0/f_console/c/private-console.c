#include "console.h"
#include "private-console.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_console_identify_) || !defined(_di_f_console_parameter_process_)
  f_status_t private_f_console_identify(const f_string_t input, f_console_id_t * const result) {
    #ifndef _di_level_0_parameter_checking_
      if (!result) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_f

    if (!input) {
      *result = f_console_none_e;

      return F_data_not;
    }

    const f_array_length_t length = strnlen(input, 3);

    if (!length) {
      *result = f_console_none_e;

      return F_data_not;
    }

    if (input[0] == f_console_symbol_short_enable_s.string[0]) {
      if (length > 1) {
        if (input[1] == f_console_symbol_short_enable_s.string[0]) {
          if (length > 2) {
            *result = f_console_long_enable_e;
          }
          else *result = f_console_empty_long_enable_e;
        }
        else *result = f_console_short_enable_e;
      }
      else *result = f_console_empty_short_enable_e;
    }
    else if (input[0] == f_console_symbol_short_disable_s.string[0]) {
      if (length > 1) {
        if (input[1] == f_console_symbol_short_disable_s.string[0]) {
          if (length > 2) {
            *result = f_console_long_disable_e;
          }
          else *result = f_console_empty_long_disable_e;
        }
        else *result = f_console_short_disable_e;
      }
      else *result = f_console_empty_short_disable_e;
    }
    else *result = f_console_none_e;

    return F_none;
  }
#endif // !defined(_di_f_console_identify_) || !defined(_di_f_console_parameter_process_)

#ifdef __cplusplus
} // extern "C"
#endif
