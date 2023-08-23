#include "console.h"
#include "private-console.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_console_identify_) || !defined(_di_f_console_parameter_process_)
  f_status_t private_f_console_identify(const f_string_t input, f_console_result_t * const result) {

    *result = f_console_result_none_e;

    if (!input) return F_data_not;

    {

      // Only the first three characters need to be scanned.
      const f_number_unsigned_t length = strnlen(input, 3);
      if (!length) return F_data_not;

      if (input[0] == f_console_symbol_short_normal_s.string[0]) {
        *result = f_console_result_found_e | f_console_result_normal_e;

        if (length > 1) {
          if (input[1] == f_console_symbol_short_normal_s.string[0]) {
            *result |= f_console_result_long_e;

            if (length < 3) {
              *result |= f_console_result_alone_e;
            }
          }
          else {
            *result |= f_console_result_short_e;
          }
        }
        else {
          *result |= f_console_result_short_e | f_console_result_alone_e;
        }
      }
      else if (input[0] == f_console_symbol_short_inverse_s.string[0]) {
        *result = f_console_result_found_e | f_console_result_inverse_e;

        if (length > 1) {
          if (input[1] == f_console_symbol_short_inverse_s.string[0]) {
            *result |= f_console_result_long_e;

            if (length < 3) {
              *result |= f_console_result_alone_e;
            }
          }
          else {
            *result |= f_console_result_short_e;
          }
        }
        else {
          *result |= f_console_result_short_e | f_console_result_alone_e;
        }
      }
    }

    return F_okay;
  }
#endif // !defined(_di_f_console_identify_) || !defined(_di_f_console_parameter_process_)

#ifdef __cplusplus
} // extern "C"
#endif
