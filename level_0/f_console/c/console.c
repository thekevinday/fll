#include <level_0/console.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_console_identify_
  f_return_status f_console_identify(const f_string input, f_console_id *result) {
    #ifndef _di_level_0_parameter_checking_
      if (result == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    const f_string_length length = strnlen(input, 3);

    if (length == 0) {
      *result = f_console_none;
      return f_no_data;
    }

    if (input[0] == f_console_symbol_enable) {
      if (length > 1) {
        if (input[1] == f_console_symbol_enable) {
          if (length > 2) {
            *result = f_console_long_enable;
          }
          else *result = f_console_empty_long_enable;
        }
        else *result = f_console_short_enable;
      }
      else *result = f_console_empty_short_enable;
    }
    else if (input[0] == f_console_symbol_disable) {
      if (length > 1) {
        if (input[1] == f_console_symbol_disable) {
          if (length > 2) {
            *result = f_console_long_disable;
          }
          else *result = f_console_empty_long_disable;
        }
        else *result = f_console_short_disable;
      }
      else *result = f_console_empty_short_disable;
    }
    else *result = f_console_none;

    return f_none;
  }
#endif // _di_f_console_identify_

#ifdef __cplusplus
} // extern "C"
#endif
