#include "conversion.h"
#include "private-conversion.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_conversion_dynamic_partial_to_binary_signed_
  f_status_t fl_conversion_dynamic_partial_to_binary_signed(const f_string_static_t buffer, const f_string_range_t range, const bool negative, f_number_signed_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop) {
      return F_data_not;
    }

    return private_fl_conversion_dynamic_to_binary_signed(buffer.string + range.start, (range.stop - range.start) + 1, negative, number);
  }
#endif // _di_fl_conversion_dynamic_partial_to_binary_signed_

#ifndef _di_fl_conversion_dynamic_partial_to_binary_unsigned_
  f_status_t fl_conversion_dynamic_partial_to_binary_unsigned(const f_string_static_t buffer, const f_string_range_t range, f_number_unsigned_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop) {
      return F_data_not;
    }

    return private_fl_conversion_dynamic_to_binary_unsigned(buffer.string + range.start, (range.stop - range.start) + 1, number);
  }
#endif // _di_fl_conversion_dynamic_partial_to_binary_unsigned_

#ifndef _di_fl_conversion_dynamic_partial_to_decimal_signed_
  f_status_t fl_conversion_dynamic_partial_to_decimal_signed(const f_string_static_t buffer, const f_string_range_t range, const bool negative, f_number_signed_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop) {
      return F_data_not;
    }

    return private_fl_conversion_dynamic_to_decimal_signed(buffer.string + range.start, (range.stop - range.start) + 1, negative, number);
  }
#endif // _di_fl_conversion_dynamic_partial_to_decimal_signed_

#ifndef _di_fl_conversion_dynamic_partial_to_decimal_unsigned_
  f_status_t fl_conversion_dynamic_partial_to_decimal_unsigned(const f_string_static_t buffer, const f_string_range_t range, f_number_unsigned_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop) {
      return F_data_not;
    }

    return private_fl_conversion_dynamic_to_decimal_unsigned(buffer.string + range.start, (range.stop - range.start) + 1, number);
  }
#endif // _di_fl_conversion_dynamic_partial_to_decimal_unsigned_

#ifndef _di_fl_conversion_dynamic_partial_to_duodecimal_signed_
  f_status_t fl_conversion_dynamic_partial_to_duodecimal_signed(const f_string_static_t buffer, const f_string_range_t range, const bool negative, f_number_signed_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop) {
      return F_data_not;
    }

    return private_fl_conversion_dynamic_to_duodecimal_signed(buffer.string + range.start, (range.stop - range.start) + 1, negative, number);
  }
#endif // _di_fl_conversion_dynamic_partial_to_duodecimal_signed_

#ifndef _di_fl_conversion_dynamic_partial_to_duodecimal_unsigned_
  f_status_t fl_conversion_dynamic_partial_to_duodecimal_unsigned(const f_string_static_t buffer, const f_string_range_t range, f_number_unsigned_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop) {
      return F_data_not;
    }

    return private_fl_conversion_dynamic_to_duodecimal_unsigned(buffer.string + range.start, (range.stop - range.start) + 1, number);
  }
#endif // _di_fl_conversion_dynamic_partial_to_duodecimal_unsigned_

#ifndef _di_fl_conversion_dynamic_partial_to_hexidecimal_signed_
  f_status_t fl_conversion_dynamic_partial_to_hexidecimal_signed(const f_string_static_t buffer, const f_string_range_t range, const bool negative, f_number_signed_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop) {
      return F_data_not;
    }

    return private_fl_conversion_dynamic_to_hexidecimal_signed(buffer.string + range.start, (range.stop - range.start) + 1, negative, number);
  }
#endif // _di_fl_conversion_dynamic_partial_to_hexidecimal_signed_

#ifndef _di_fl_conversion_dynamic_partial_to_hexidecimal_unsigned_
  f_status_t fl_conversion_dynamic_partial_to_hexidecimal_unsigned(const f_string_static_t buffer, const f_string_range_t range, f_number_unsigned_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop) {
      return F_data_not;
    }

    return private_fl_conversion_dynamic_to_hexidecimal_unsigned(buffer.string + range.start, (range.stop - range.start) + 1, number);
  }
#endif // _di_fl_conversion_dynamic_partial_to_hexidecimal_unsigned_

#ifndef _di_fl_conversion_dynamic_partial_to_octal_signed_
  f_status_t fl_conversion_dynamic_partial_to_octal_signed(const f_string_static_t buffer, const f_string_range_t range, const bool negative, f_number_signed_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop) {
      return F_data_not;
    }

    return private_fl_conversion_dynamic_to_octal_signed(buffer.string + range.start, (range.stop - range.start) + 1, negative, number);
  }
#endif // _di_fl_conversion_dynamic_partial_to_octal_signed_

#ifndef _di_fl_conversion_dynamic_partial_to_octal_unsigned_
  f_status_t fl_conversion_dynamic_partial_to_octal_unsigned(const f_string_static_t buffer, const f_string_range_t range, f_number_unsigned_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop) {
      return F_data_not;
    }

    return private_fl_conversion_dynamic_to_octal_unsigned(buffer.string + range.start, (range.stop - range.start) + 1, number);
  }
#endif // _di_fl_conversion_dynamic_partial_to_octal_unsigned_

#ifndef _di_fl_conversion_dynamic_partial_to_number_signed_
  f_status_t fl_conversion_dynamic_partial_to_number_signed(const f_string_static_t buffer, const f_string_range_t range, f_number_signed_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop) {
      return F_data_not;
    }

    return private_fl_conversion_dynamic_to_number_signed(buffer.string + range.start, (range.stop - range.start) + 1, number);
  }
#endif // _di_fl_conversion_dynamic_partial_to_number_signed_

#ifndef _di_fl_conversion_dynamic_partial_to_number_unsigned_
  f_status_t fl_conversion_dynamic_partial_to_number_unsigned(const f_string_static_t buffer, const f_string_range_t range, f_number_unsigned_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop) {
      return F_data_not;
    }

    return private_fl_conversion_dynamic_to_number_unsigned(buffer.string + range.start, (range.stop - range.start) + 1, number);
  }
#endif // _di_fl_conversion_dynamic_partial_to_number_unsigned_

#ifndef _di_fl_conversion_dynamic_to_binary_signed_
  f_status_t fl_conversion_dynamic_to_binary_signed(const f_string_static_t buffer, const bool negative, f_number_signed_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_fl_conversion_dynamic_to_binary_signed(buffer.string, buffer.used, negative, number);
  }
#endif // _di_fl_conversion_dynamic_to_binary_signed_

#ifndef _di_fl_conversion_dynamic_to_binary_unsigned_
  f_status_t fl_conversion_dynamic_to_binary_unsigned(const f_string_static_t buffer, f_number_unsigned_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_fl_conversion_dynamic_to_binary_unsigned(buffer.string, buffer.used, number);
  }
#endif // _di_fl_conversion_dynamic_to_binary_unsigned_

#ifndef _di_fl_conversion_dynamic_to_decimal_signed_
  f_status_t fl_conversion_dynamic_to_decimal_signed(const f_string_static_t buffer, const bool negative, f_number_signed_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_fl_conversion_dynamic_to_decimal_signed(buffer.string, buffer.used, negative, number);
  }
#endif // _di_fl_conversion_dynamic_to_decimal_signed_

#ifndef _di_fl_conversion_dynamic_to_decimal_unsigned_
  f_status_t fl_conversion_dynamic_to_decimal_unsigned(const f_string_static_t buffer, f_number_unsigned_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_fl_conversion_dynamic_to_decimal_unsigned(buffer.string, buffer.used, number);
  }
#endif // _di_fl_conversion_dynamic_to_decimal_unsigned_

#ifndef _di_fl_conversion_dynamic_to_duodecimal_signed_
  f_status_t fl_conversion_dynamic_to_duodecimal_signed(const f_string_static_t buffer, const bool negative, f_number_signed_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_fl_conversion_dynamic_to_duodecimal_signed(buffer.string, buffer.used, negative, number);
  }
#endif // _di_fl_conversion_dynamic_to_duodecimal_signed_

#ifndef _di_fl_conversion_dynamic_to_duodecimal_unsigned_
  f_status_t fl_conversion_dynamic_to_duodecimal_unsigned(const f_string_static_t buffer, f_number_unsigned_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_fl_conversion_dynamic_to_duodecimal_unsigned(buffer.string, buffer.used, number);
  }
#endif // _di_fl_conversion_dynamic_to_duodecimal_unsigned_

#ifndef _di_fl_conversion_dynamic_to_hexidecimal_signed_
  f_status_t fl_conversion_dynamic_to_hexidecimal_signed(const f_string_static_t buffer, const bool negative, f_number_signed_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_fl_conversion_dynamic_to_hexidecimal_signed(buffer.string, buffer.used, negative, number);
  }
#endif // _di_fl_conversion_dynamic_to_hexidecimal_signed_

#ifndef _di_fl_conversion_dynamic_to_hexidecimal_unsigned_
  f_status_t fl_conversion_dynamic_to_hexidecimal_unsigned(const f_string_static_t buffer, f_number_unsigned_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_fl_conversion_dynamic_to_hexidecimal_unsigned(buffer.string, buffer.used, number);
  }
#endif // _di_fl_conversion_dynamic_to_hexidecimal_unsigned_

#ifndef _di_fl_conversion_dynamic_to_octal_signed_
  f_status_t fl_conversion_dynamic_to_octal_signed(const f_string_static_t buffer, const bool negative, f_number_signed_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_fl_conversion_dynamic_to_octal_signed(buffer.string, buffer.used, negative, number);
  }
#endif // _di_fl_conversion_dynamic_to_octal_signed_

#ifndef _di_fl_conversion_dynamic_to_octal_unsigned_
  f_status_t fl_conversion_dynamic_to_octal_unsigned(const f_string_static_t buffer, f_number_unsigned_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_fl_conversion_dynamic_to_octal_unsigned(buffer.string, buffer.used, number);
  }
#endif // _di_fl_conversion_dynamic_to_octal_unsigned_

#ifndef _di_fl_conversion_dynamic_to_number_signed_
  f_status_t fl_conversion_dynamic_to_number_signed(const f_string_static_t buffer, f_number_signed_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_fl_conversion_dynamic_to_number_signed(buffer.string, buffer.used, number);
  }
#endif // _di_fl_conversion_dynamic_to_number_signed_

#ifndef _di_fl_conversion_dynamic_to_number_unsigned_
  f_status_t fl_conversion_dynamic_to_number_unsigned(const f_string_static_t buffer, f_number_unsigned_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_fl_conversion_dynamic_to_number_unsigned(buffer.string, buffer.used, number);
  }
#endif // _di_fl_conversion_dynamic_to_number_unsigned_
#ifdef __cplusplus
} // extern "C"
#endif
