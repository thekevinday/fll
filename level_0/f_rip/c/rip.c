#include "rip.h"
#include "private-rip.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_rip_
  f_status_t f_rip(const f_string_t source, const f_number_unsigned_t length, f_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not_eos;

    f_number_unsigned_t begin = 0;
    f_number_unsigned_t end = length - 1;

    {
      const f_status_t status = private_f_rip_find_range(source, &begin, &end);
      if (F_status_is_error(status)) return status;
      if (status == F_data_not) return status;
    }

    return f_string_append(source + begin, (end - begin) + 1, destination);
  }
#endif // _di_f_rip_

#ifndef _di_f_rip_dynamic_
  f_status_t f_rip_dynamic(const f_string_static_t source, f_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;

    f_number_unsigned_t begin = 0;
    f_number_unsigned_t end = source.used - 1;

    {
      const f_status_t status = private_f_rip_find_range(source.string, &begin, &end);
      if (F_status_is_error(status)) return status;
      if (status == F_data_not) return status;
    }

    if (begin > end) return F_data_not_stop;

    return f_string_append(source.string + begin, (end - begin) + 1, destination);
  }
#endif // _di_f_rip_dynamic_

#ifndef _di_f_rip_dynamic_nulless_
  f_status_t f_rip_dynamic_nulless(const f_string_static_t source, f_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;

    f_number_unsigned_t begin = 0;
    f_number_unsigned_t end = source.used - 1;

    {
      const f_status_t status = private_f_rip_find_range(source.string, &begin, &end);
      if (F_status_is_error(status)) return status;
      if (status == F_data_not) return status;
    }

    if (begin > end) return F_data_not_stop;

    return f_string_append_nulless(source.string + begin, (end - begin) + 1, destination);
  }
#endif // _di_f_rip_dynamic_nulless_

#ifndef _di_f_rip_nulless_
  f_status_t f_rip_nulless(const f_string_t source, const f_number_unsigned_t length, f_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!length) return F_data_not_eos;

    f_number_unsigned_t begin = 0;
    f_number_unsigned_t end = length - 1;

    {
      const f_status_t status = private_f_rip_find_range(source, &begin, &end);
      if (F_status_is_error(status)) return status;
      if (status == F_data_not) return status;
    }

    return f_string_append_nulless(source + begin, (end - begin) + 1, destination);
  }
#endif // _di_f_rip_nulless_

#ifndef _di_f_rip_dynamic_partial_
  f_status_t f_rip_dynamic_partial(const f_string_static_t source, const f_range_t range, f_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    f_number_unsigned_t begin = range.start;
    f_number_unsigned_t end = range.stop;

    {
      const f_status_t status = private_f_rip_find_range(source.string, &begin, &end);
      if (F_status_is_error(status)) return status;
      if (status == F_data_not) return status;
    }

    if (begin > end) return F_data_not_stop;

    return f_string_append(source.string + begin, (end - begin) + 1, destination);
  }
#endif // _di_f_rip_dynamic_partial_

#ifndef _di_f_rip_dynamic_partial_nulless_
  f_status_t f_rip_dynamic_partial_nulless(const f_string_static_t source, const f_range_t range, f_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;
    if (range.start > range.stop) return F_data_not_stop;

    f_number_unsigned_t begin = range.start;
    f_number_unsigned_t end = range.stop;

    {
      const f_status_t status = private_f_rip_find_range(source.string, &begin, &end);
      if (F_status_is_error(status)) return status;
      if (status == F_data_not) return status;
    }

    if (begin > end) return F_data_not_stop;

    return f_string_append_nulless(source.string + begin, (end - begin) + 1, destination);
  }
#endif // _di_f_rip_dynamic_partial_nulless_

#ifdef __cplusplus
} // extern "C"
#endif
