#include <level_0/print.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_print_string_
  f_return_status f_print_string(FILE *output, const f_string string, const f_string_length length) {
    #ifndef _di_level_0_parameter_checking_
      if (string == 0) return f_status_set_error(f_invalid_parameter);
      if (length < 1) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    register f_string_length i = 0;

    for (; i < length; i++) {
      if (string[i] != f_string_eos) {
        if (fputc(string[i], output) == 0) {
          return f_status_set_error(f_error_output);
        }
      }
    } // for

    return f_none;
  }
#endif // _di_f_print_string_

#ifndef _di_f_print_string_dynamic_
  f_return_status f_print_string_dynamic(FILE *output, const f_string_static buffer) {
    #ifndef _di_level_0_parameter_checking_
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    register f_string_length i = 0;

    for (; i < buffer.used; i++) {
      if (buffer.string[i] != f_string_eos) {
        if (fputc(buffer.string[i], output) == 0) {
          return f_status_set_error(f_error_output);
        }
      }
    } // for

    return f_none;
  }
#endif // _di_f_print_string_dynamic_

#ifndef _di_f_print_string_dynamic_partial_
  f_return_status f_print_string_dynamic_partial(FILE *output, const f_string_static buffer, const f_string_range range) {
    #ifndef _di_level_0_parameter_checking_
      if (range.start < 0) return f_status_set_error(f_invalid_parameter);
      if (range.stop < range.start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (range.start >= buffer.used) return f_status_set_error(f_invalid_parameter);
      if (range.stop >= buffer.used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    register f_string_length i = range.start;

    for (; i <= range.stop; i++) {
      if (buffer.string[i] != f_string_eos) {
        if (fputc(buffer.string[i], output) == 0) {
          return f_status_set_error(f_error_output);
        }
      }
    } // for

    return f_none;
  }
#endif // _di_f_print_string_dynamic_partial_

#ifdef __cplusplus
} // extern "C"
#endif
