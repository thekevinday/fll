#include "print.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_print_
  f_status_t f_print(FILE *output, const f_string_t string, const f_array_length_t length) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!string || !length) {
      return F_data_not;
    }

    return private_f_print(output, string, length);
  }
#endif // _di_f_print_

#ifndef _di_f_print_dynamic_
  f_status_t f_print_dynamic(FILE *output, const f_string_static_t buffer) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_f_print(output, buffer.string, buffer.used);
  }
#endif // _di_f_print_dynamic_

#ifndef _di_f_print_dynamic_partial_
  f_status_t f_print_dynamic_partial(FILE *output, const f_string_static_t buffer, const f_string_range_t range) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_f_print(output, buffer.string + range.start, length);
  }
#endif // _di_f_print_dynamic_partial_

#ifndef _di_f_print_except_
  f_status_t f_print_except(FILE *output, const f_string_t string, const f_array_length_t length, const f_array_lengths_t except) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!string || length == 0) {
      return F_data_not;
    }

    return private_f_print_except(output, string, 0, length, except);
  }
#endif // _di_f_print_except_

#ifndef _di_f_print_except_dynamic_
  f_status_t f_print_except_dynamic(FILE *output, const f_string_static_t buffer, const f_array_lengths_t except) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used) return F_data_not;

    return private_f_print_except(output, buffer.string, 0, buffer.used, except);
  }
#endif // _di_f_print_except_dynamic_

#ifndef _di_f_print_except_dynamic_partial_
  f_status_t f_print_except_dynamic_partial(FILE *output, const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except) {
    #ifndef _di_level_0_parameter_checking_
      if (!output) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_f_print_except(output, buffer.string, range.start, range.start + length, except);
  }
#endif // _di_f_print_except_dynamic_partial_

#ifndef _di_f_print_to_
  f_status_t f_print_to(const int id, const f_string_t string, const f_array_length_t length) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!string || length == 0) {
      return F_data_not;
    }

    return private_f_print_to(id, string, length);
  }
#endif // _di_f_print_to_

#ifndef _di_f_print_to_dynamic_
  f_status_t f_print_to_dynamic(const int id, const f_string_static_t buffer) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_f_print_to(id, buffer.string, buffer.used);
  }
#endif // _di_f_print_to_dynamic_

#ifndef _di_f_print_to_dynamic_partial_
  f_status_t f_print_to_dynamic_partial(const int id, const f_string_static_t buffer, const f_string_range_t range) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_f_print_to(id, buffer.string + range.start, length);
  }
#endif // _di_f_print_to_dynamic_partial_

#ifndef _di_f_print_to_except_
  f_status_t f_print_to_except(const int id, const f_string_t string, const f_array_length_t length, const f_array_lengths_t except) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!string || length == 0) {
      return F_data_not;
    }

    return private_f_print_to_except(id, string, 0, length, except);
  }
#endif // _di_f_print_to_except_

#ifndef _di_f_print_to_except_dynamic_
  f_status_t f_print_to_except_dynamic(const int id, const f_string_static_t buffer, const f_array_lengths_t except) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_f_print_to_except(id, buffer.string, 0, buffer.used, except);
  }
#endif // _di_f_print_to_except_dynamic_

#ifndef _di_f_print_to_except_dynamic_partial_
  f_status_t f_print_to_except_dynamic_partial(const int id, const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except) {
    #ifndef _di_level_0_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t length = (range.stop - range.start) + 1;

    if (length + range.start > buffer.used) {
      length = buffer.used - range.start;
    }

    return private_f_print_to_except(id, buffer.string, range.start, range.start + length, except);
  }
#endif // _di_f_print_to_except_dynamic_partial_

#ifdef __cplusplus
} // extern "C"
#endif
