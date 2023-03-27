#include "../rip.h"
#include "private-utf.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_rip_utf_
  f_status_t f_rip_utf(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!length) return F_data_not;

    f_array_length_t begin = 0;
    f_array_length_t end = length - 1;

    f_status_t status = private_f_rip_utf_find_range(source, &begin, &end);

    if (F_status_is_error(status)) {
      return status;
    }

    if (status == F_data_not) {
      return status;
    }

    return f_utf_string_append(source + begin, (end - begin) + 1, destination);
  }
#endif // _di_f_rip_utf_

#ifndef _di_f_rip_utf_dynamic_
  f_status_t f_rip_utf_dynamic(const f_utf_string_static_t source, const f_string_range_t range, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.start) return F_status_set_error(F_parameter);
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not;
    if (range.start > range.stop) return F_data_not_stop;

    return f_utf_string_append(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_rip_utf_dynamic_

#ifndef _di_f_rip_utf_dynamic_nulless_
  f_status_t f_rip_utf_dynamic_nulless(const f_utf_string_static_t source, const f_string_range_t range, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_1_parameter_checking_
      if (source.used <= range.start) return F_status_set_error(F_parameter);
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not;
    if (range.start > range.stop) return F_data_not_stop;

    return f_utf_string_append_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_rip_utf_dynamic_nulless_

#ifndef _di_f_rip_utf_nulless_
  f_status_t f_rip_utf_nulless(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t * const destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!length) return F_data_not;

    f_array_length_t begin = 0;
    f_array_length_t end = length - 1;

    f_status_t status = private_f_rip_utf_find_range(source, &begin, &end);

    if (F_status_is_error(status)) {
      return status;
    }

    if (status == F_data_not) {
      return status;
    }

    return f_utf_string_append_nulless(source + begin, (end - begin) + 1, destination);
  }
#endif // _di_f_rip_utf_nulless_

#ifdef __cplusplus
} // extern "C"
#endif
