#include "conversion.h"
#include "private-conversion.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_conversion_dynamic_partial_to_signed_
  f_status_t fl_conversion_dynamic_partial_to_signed(const fl_conversion_data_t data, const f_string_static_t buffer, const f_string_range_t range, f_number_signed_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop) {
      return F_data_not;
    }

    if (data.base == 10 || data.base == 16 || data.base == 12 || data.base == 8) {
      return private_fl_conversion_dynamic_to_base_signed(data, buffer.string + range.start, (range.stop - range.start) + 1, number);
    }
    else if (data.base == 2) {
      return private_fl_conversion_dynamic_to_binary_signed(data.flag, buffer.string + range.start, (range.stop - range.start) + 1, number);
    }

    return F_status_set_error(F_base_not);
  }
#endif // _di_fl_conversion_dynamic_partial_to_signed_

#ifndef _di_fl_conversion_dynamic_partial_to_unsigned_
  f_status_t fl_conversion_dynamic_partial_to_unsigned(const fl_conversion_data_t data, const f_string_static_t buffer, const f_string_range_t range, f_number_unsigned_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop) {
      return F_data_not;
    }

    if (data.base == 10 || data.base == 16 || data.base == 12 || data.base == 8) {
      return private_fl_conversion_dynamic_to_base_unsigned(data, buffer.string + range.start, (range.stop - range.start) + 1, number);
    }
    else if (data.base == 2) {
      return private_fl_conversion_dynamic_to_binary_unsigned(data.flag, buffer.string + range.start, (range.stop - range.start) + 1, number);
    }

    return F_status_set_error(F_base_not);
  }
#endif // _di_fl_conversion_dynamic_partial_to_unsigned_

#ifndef _di_fl_conversion_dynamic_partial_to_signed_detect_
  f_status_t fl_conversion_dynamic_partial_to_signed_detect(const fl_conversion_data_t data, const f_string_static_t buffer, const f_string_range_t range, f_number_signed_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop) {
      return F_data_not;
    }

    return private_fl_conversion_dynamic_to_signed_detect(data.flag, buffer.string + range.start, (range.stop - range.start) + 1, number);
  }
#endif // _di_fl_conversion_dynamic_partial_to_signed_detect_

#ifndef _di_fl_conversion_dynamic_partial_to_unsigned_detect_
  f_status_t fl_conversion_dynamic_partial_to_unsigned_detect(const fl_conversion_data_t data, const f_string_static_t buffer, const f_string_range_t range, f_number_unsigned_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used || range.start > range.stop) {
      return F_data_not;
    }

    return private_fl_conversion_dynamic_to_unsigned_detect(data.flag, buffer.string + range.start, (range.stop - range.start) + 1, number);
  }
#endif // _di_fl_conversion_dynamic_partial_to_unsigned_detect_

#ifndef _di_fl_conversion_dynamic_to_signed_
  f_status_t fl_conversion_dynamic_to_signed(const fl_conversion_data_t data, const f_string_static_t buffer, f_number_signed_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    if (data.base == 10 || data.base == 16 || data.base == 12 || data.base == 8) {
      return private_fl_conversion_dynamic_to_base_signed(data, buffer.string, buffer.used, number);
    }
    else if (data.base == 2) {
      return private_fl_conversion_dynamic_to_binary_signed(data.flag, buffer.string, buffer.used, number);
    }

    return F_status_set_error(F_base_not);
  }
#endif // _di_fl_conversion_dynamic_to_signed_

#ifndef _di_fl_conversion_dynamic_to_unsigned_
  f_status_t fl_conversion_dynamic_to_unsigned(const fl_conversion_data_t data, const f_string_static_t buffer, f_number_unsigned_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    if (data.base == 10 || data.base == 16 || data.base == 12 || data.base == 8) {
      return private_fl_conversion_dynamic_to_base_unsigned(data, buffer.string, buffer.used, number);
    }
    else if (data.base == 2) {
      return private_fl_conversion_dynamic_to_binary_unsigned(data.flag, buffer.string, buffer.used, number);
    }

    return F_status_set_error(F_base_not);
  }
#endif // _di_fl_conversion_dynamic_to_unsigned_

#ifndef _di_fl_conversion_dynamic_to_signed_detect_
  f_status_t fl_conversion_dynamic_to_signed_detect(const fl_conversion_data_t data, const f_string_static_t buffer, f_number_signed_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_fl_conversion_dynamic_to_signed_detect(data.flag, buffer.string, buffer.used, number);
  }
#endif // _di_fl_conversion_dynamic_to_signed_detect_

#ifndef _di_fl_conversion_dynamic_to_unsigned_detect_
  f_status_t fl_conversion_dynamic_to_unsigned_detect(const fl_conversion_data_t data, const f_string_static_t buffer, f_number_unsigned_t * const number) {
    #ifndef _di_level_1_parameter_checking_
      if (!number) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) {
      return F_data_not;
    }

    return private_fl_conversion_dynamic_to_unsigned_detect(data.flag, buffer.string, buffer.used, number);
  }
#endif // _di_fl_conversion_dynamic_to_unsigned_detect_
#ifdef __cplusplus
} // extern "C"
#endif
