#include "../compare.h"
#include "private-utf.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_compare_utf_
  f_status_t f_compare_utf(const f_utf_string_t string1, const f_utf_string_t string2, const f_array_length_t length1, const f_array_length_t length2) {

    return private_f_compare_utf(string1, string2, 0, 0, length1, length2);
  }
#endif // _di_f_compare_utf_

#ifndef _di_f_compare_utf_dynamic_
  f_status_t f_compare_utf_dynamic(const f_utf_string_static_t string1, const f_utf_string_static_t string2) {

    return private_f_compare_utf(string1.string, string2.string, 0, 0, string1.used, string2.used);
  }
#endif // _di_f_compare_utf_dynamic_

#ifndef _di_f_compare_utf_dynamic_trim_
  f_status_t f_compare_utf_dynamic_trim(const f_utf_string_static_t string1, const f_utf_string_static_t string2) {

    return private_f_compare_utf_trim(string1.string, string2.string, 0, 0, string1.used, string2.used);
  }
#endif // _di_f_compare_utf_dynamic_trim_

#ifndef _di_f_compare_utf_dynamic_partial_
  f_status_t f_compare_utf_dynamic_partial(const f_utf_string_static_t string1, const f_utf_string_static_t string2, const f_string_range_t range1, const f_string_range_t range2) {
    #ifndef _di_level_0_parameter_checking_
      if (string1.used <= range1.stop) return F_status_set_error(F_parameter);
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_compare_utf(string1.string, string2.string, range1.start, range2.start, range1.stop + 1, range2.stop + 1);
  }
#endif // _di_f_compare_utf_dynamic_partial_

#ifndef _di_f_compare_utf_dynamic_partial_trim_
  f_status_t f_compare_utf_dynamic_partial_trim(const f_utf_string_static_t string1, const f_utf_string_static_t string2, const f_string_range_t range1, const f_string_range_t range2) {
    #ifndef _di_level_0_parameter_checking_
      if (string1.used <= range1.stop) return F_status_set_error(F_parameter);
      if (string2.used <= range2.stop) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_compare_utf_trim(string1.string, string2.string, range1.start, range2.start, range1.stop + 1, range2.stop + 1);
  }
#endif // _di_f_compare_utf_dynamic_partial_trim_

#ifndef _di_f_compare_utf_trim_
  f_status_t f_compare_utf_trim(const f_utf_string_t string1, const f_utf_string_t string2, const f_array_length_t length1, const f_array_length_t length2) {

    return private_f_compare_utf_trim(string1, string2, 0, 0, length1, length2);
  }
#endif // _di_f_compare_utf_trim_

#ifdef __cplusplus
} // extern "C"
#endif
