#include "print.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_print_
  f_return_status f_print(FILE *output, const f_string_t string, const f_string_length_t length) {
    #ifndef _di_level_0_parameter_checking_
      if (output == 0) return F_status_set_error(F_parameter);
      if (string == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_print(output, string, length);
  }
#endif // _di_f_print_

#ifndef _di_f_print_dynamic_
  f_return_status f_print_dynamic(FILE *output, const f_string_static_t buffer) {
    #ifndef _di_level_0_parameter_checking_
      if (output == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_print(output, buffer.string, buffer.used);
  }
#endif // _di_f_print_dynamic_

#ifndef _di_f_print_dynamic_partial_
  f_return_status f_print_dynamic_partial(FILE *output, const f_string_static_t buffer, const f_string_range_t range) {
    #ifndef _di_level_0_parameter_checking_
      if (output == 0) return F_status_set_error(F_parameter);
      if (range.start < 0) return F_status_set_error(F_parameter);
      if (range.start > range.stop) return F_status_set_error(F_parameter);
      if (range.start >= buffer.used) return F_status_set_error(F_parameter);
      if (range.stop >= buffer.used) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const f_string_length_t length = (range.stop - range.start) + 1;

    return private_f_print(output, buffer.string + range.start, length);
  }
#endif // _di_f_print_dynamic_partial_

#ifndef _di_f_print_to_
  f_return_status f_print_to(const int id, const f_string_t string, const f_string_length_t length) {
    #ifndef _di_level_0_parameter_checking_
      if (string == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_print_to(id, string, length);
  }
#endif // _di_f_print_to_

#ifndef _di_f_print_to_dynamic_
  f_return_status f_print_to_dynamic(const int id, const f_string_static_t buffer) {
    return private_f_print_to(id, buffer.string, buffer.used);
  }
#endif // _di_f_print_to_dynamic_

#ifndef _di_f_print_to_dynamic_partial_
  f_return_status f_print_to_dynamic_partial(const int id, const f_string_static_t buffer, const f_string_range_t range) {
    #ifndef _di_level_0_parameter_checking_
      if (range.start < 0) return F_status_set_error(F_parameter);
      if (range.start > range.stop) return F_status_set_error(F_parameter);
      if (range.start >= buffer.used) return F_status_set_error(F_parameter);
      if (range.stop >= buffer.used) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const f_string_length_t length = (range.stop - range.start) + 1;

    return private_f_print_to(id, buffer.string + range.start, length);
  }
#endif // _di_f_print_to_dynamic_partial_

#ifdef __cplusplus
} // extern "C"
#endif
