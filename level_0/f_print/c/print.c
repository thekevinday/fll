#include <level_0/print.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_print_string_
  f_return_status f_print_string(FILE *output, const f_string string, const f_string_length length) {
    #ifndef _di_level_0_parameter_checking_
      if (string == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (length == 0) return F_data_not;

    register f_string_length i = 0;

    for (; i < length; i++) {
      if (string[i] != 0) {
        if (fputc(string[i], output) == 0) {
          return F_status_set_error(F_output);
        }
      }
    } // for

    return F_none;
  }
#endif // _di_f_print_string_

#ifndef _di_f_print_string_dynamic_
  f_return_status f_print_string_dynamic(FILE *output, const f_string_static buffer) {
    if (buffer.used == 0) return F_data_not;

    register f_string_length i = 0;

    for (; i < buffer.used; i++) {
      if (buffer.string[i] != 0) {
        if (fputc(buffer.string[i], output) == 0) {
          return F_status_set_error(F_output);
        }
      }
    } // for

    return F_none;
  }
#endif // _di_f_print_string_dynamic_

#ifndef _di_f_print_string_dynamic_partial_
  f_return_status f_print_string_dynamic_partial(FILE *output, const f_string_static buffer, const f_string_range range) {
    #ifndef _di_level_0_parameter_checking_
      if (range.start < 0) return F_status_set_error(F_parameter);
      if (range.start > range.stop) return F_status_set_error(F_parameter);
      if (range.start >= buffer.used) return F_status_set_error(F_parameter);
      if (range.stop >= buffer.used) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (buffer.used == 0) return F_data_not;

    register f_string_length i = range.start;

    for (; i <= range.stop; i++) {
      if (buffer.string[i] != 0) {
        if (fputc(buffer.string[i], output) == 0) {
          return F_status_set_error(F_output);
        }
      }
    } // for

    return F_none;
  }
#endif // _di_f_print_string_dynamic_partial_

#ifdef __cplusplus
} // extern "C"
#endif
