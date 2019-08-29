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
      if (string[i] != f_eos) {
        if (fputc(string[i], output) == 0) {
          return f_status_set_error(f_output_error);
        }
      }
    }

    return f_none;
  }
#endif // _di_f_print_string_

#ifndef _di_f_print_dynamic_string_
  f_return_status f_print_dynamic_string(FILE *output, const f_dynamic_string buffer) {
    #ifndef _di_level_0_parameter_checking_
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    register f_string_length i = 0;

    for (; i < buffer.used; i++) {
      if (buffer.string[i] != f_eos) {
        if (fputc(buffer.string[i], output) == 0) {
          return f_status_set_error(f_output_error);
        }
      }
    }

    return f_none;
  }
#endif // _di_f_print_dynamic_string_

#ifndef _di_f_print_partial_dynamic_string_
  f_return_status f_print_partial_dynamic_string(FILE *output, const f_dynamic_string buffer, const f_string_location location) {
    #ifndef _di_level_0_parameter_checking_
      if (location.start < 0) return f_status_set_error(f_invalid_parameter);
      if (location.stop < location.start) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (location.start >= buffer.used) return f_status_set_error(f_invalid_parameter);
      if (location.stop >= buffer.used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    register f_string_length i = location.start;

    for (; i <= location.stop; i++) {
      if (buffer.string[i] != f_eos) {
        if (fputc(buffer.string[i], output) == 0) {
          return f_status_set_error(f_output_error);
        }
      }
    }

    return f_none;
  }
#endif // _di_f_print_partial_dynamic_string_

#ifdef __cplusplus
} // extern "C"
#endif
