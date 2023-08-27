#include "../compare.h"
#include "private-utf.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_compare_utf_
  f_status_t f_compare_utf(const f_utf_string_t string1, const f_utf_string_t string2, const f_number_unsigned_t length1, const f_number_unsigned_t length2) {

    return private_f_compare_utf(string1, string2, 0, 0, length1, length2);
  }
#endif // _di_f_compare_utf_

#ifndef _di_f_compare_utf_dynamic_
  f_status_t f_compare_utf_dynamic(const f_utf_string_static_t string1, const f_utf_string_static_t string2) {

    return private_f_compare_utf(string1.string, string2.string, 0, 0, string1.used, string2.used);
  }
#endif // _di_f_compare_utf_dynamic_

#ifndef _di_f_compare_utf_dynamic_except_
  f_status_t f_compare_utf_dynamic_except(const f_utf_string_static_t string1, const f_utf_string_static_t string2, const f_number_unsigneds_t except1, const f_number_unsigneds_t except2) {

    return private_f_compare_utf_except(string1.string, string2.string, 0, 0, string1.used, string2.used, except1, except2);
  }
#endif // _di_f_compare_utf_dynamic_except_

#ifndef _di_f_compare_utf_dynamic_except_string_
  f_status_t f_compare_utf_dynamic_except_string(const f_utf_string_t string1, const f_utf_string_static_t string2, const f_number_unsigned_t length1, const f_number_unsigneds_t except1, const f_number_unsigneds_t except2) {

    return private_f_compare_utf_except(string1, string2.string, 0, 0, length1, string2.used, except1, except2);
  }
#endif // _di_f_compare_utf_dynamic_except_string_

#ifndef _di_f_compare_utf_dynamic_except_trim_
  f_status_t f_compare_utf_dynamic_except_trim(const f_utf_string_static_t string1, const f_utf_string_static_t string2, const f_number_unsigneds_t except1, const f_number_unsigneds_t except2) {

    return private_f_compare_utf_except_trim(string1.string, string2.string, 0, 0, string1.used, string2.used, except1, except2);
  }
#endif // _di_f_compare_utf_dynamic_except_trim_

#ifndef _di_f_compare_utf_dynamic_except_trim_string_
  f_status_t f_compare_utf_dynamic_except_trim_string(const f_utf_string_t string1, const f_utf_string_static_t string2, const f_number_unsigned_t length1, const f_number_unsigneds_t except1, const f_number_unsigneds_t except2) {

    return private_f_compare_utf_except_trim(string1, string2.string, 0, 0, length1, string2.used, except1, except2);
  }
#endif // _di_f_compare_utf_dynamic_except_trim_string_

#ifndef _di_f_compare_utf_dynamic_string_
  f_status_t f_compare_utf_dynamic_string(const f_utf_string_t string1, const f_utf_string_static_t string2, const f_number_unsigned_t length1) {

    return private_f_compare_utf(string1, string2.string, 0, 0, length1, string2.used);
  }
#endif // _di_f_compare_utf_dynamic_string_

#ifndef _di_f_compare_utf_dynamic_trim_
  f_status_t f_compare_utf_dynamic_trim(const f_utf_string_static_t string1, const f_utf_string_static_t string2) {

    return private_f_compare_utf_trim(string1.string, string2.string, 0, 0, string1.used, string2.used);
  }
#endif // _di_f_compare_utf_dynamic_trim_

#ifndef _di_f_compare_utf_dynamic_trim_string_
  f_status_t f_compare_utf_dynamic_trim_string(const f_utf_string_t string1, const f_utf_string_static_t string2, const f_number_unsigned_t length1) {

    return private_f_compare_utf_trim(string1, string2.string, 0, 0, length1, string2.used);
  }
#endif // _di_f_compare_utf_dynamic_trim_string_

#ifndef _di_f_compare_utf_dynamic_partial_
  f_status_t f_compare_utf_dynamic_partial(const f_utf_string_static_t string1, const f_utf_string_static_t string2, const f_string_range_t range1, const f_string_range_t range2) {

    return private_f_compare_utf(
      string1.string,
      string2.string,
      range1.start,
      range2.start,
      string1.used <= range1.stop
        ? string1.used
        : range1.stop + 1,
      string2.used <= range2.stop
        ? string2.used
        : range2.stop + 1
    );
  }
#endif // _di_f_compare_utf_dynamic_partial_

#ifndef _di_f_compare_utf_dynamic_partial_dynamic_
  f_status_t f_compare_utf_dynamic_partial_dynamic(const f_utf_string_static_t string1, const f_utf_string_static_t string2, const f_string_range_t range2) {

    return private_f_compare_utf(
      string1.string,
      string2.string,
      0,
      range2.start,
      string1.used,
      string2.used <= range2.stop
        ? string2.used
        : range2.stop + 1
    );
  }
#endif // _di_f_compare_utf_dynamic_partial_dynamic_

#ifndef _di_f_compare_utf_dynamic_partial_string_
  f_status_t f_compare_utf_dynamic_partial_string(const f_utf_string_t string1, const f_utf_string_static_t string2, const f_number_unsigned_t length1, const f_string_range_t range2) {

    return private_f_compare_utf(
      string1,
      string2.string,
      0,
      range2.start,
      length1,
      string2.used < range2.stop
        ? string2.used
        : range2.stop + 1
    );
  }
#endif // _di_f_compare_utf_dynamic_partial_string_

#ifndef _di_f_compare_utf_dynamic_partial_except_
  f_status_t f_compare_utf_dynamic_partial_except(const f_utf_string_static_t string1, const f_utf_string_static_t string2, const f_string_range_t range1, const f_string_range_t range2, const f_number_unsigneds_t except1, const f_number_unsigneds_t except2) {

    return private_f_compare_utf_except(
      string1.string,
      string2.string,
      range1.start,
      range2.start,
      string1.used < range1.stop
        ? string1.used
        : range1.stop + 1,
      string2.used <= range2.stop
        ? string2.used
        : range2.stop + 1,
      except1,
      except2
    );
  }
#endif // _di_f_compare_utf_dynamic_partial_except_

#ifndef _di_f_compare_utf_dynamic_partial_except_dynamic_
  f_status_t f_compare_utf_dynamic_partial_except_dynamic(const f_utf_string_static_t string1, const f_utf_string_static_t string2, const f_string_range_t range2, const f_number_unsigneds_t except1, const f_number_unsigneds_t except2) {

    return private_f_compare_utf_except(
      string1.string,
      string2.string,
      0,
      range2.start,
      string1.used,
      string2.used <= range2.stop
        ? string2.used
        : range2.stop + 1,
      except1,
      except2
    );
  }
#endif // _di_f_compare_utf_dynamic_partial_except_dynamic_

#ifndef _di_f_compare_utf_dynamic_partial_except_string_
  f_status_t f_compare_utf_dynamic_partial_except_string(const f_utf_string_t string1, const f_utf_string_static_t string2, const f_number_unsigned_t length1, const f_string_range_t range2, const f_number_unsigneds_t except1, const f_number_unsigneds_t except2) {

    return private_f_compare_utf_except(
      string1,
      string2.string,
      0,
      range2.start,
      length1,
      string2.used <= range2.stop
        ? string2.used
        : range2.stop + 1,
      except1,
      except2
    );
  }
#endif // _di_f_compare_utf_dynamic_partial_except_string_

#ifndef _di_f_compare_utf_dynamic_partial_except_trim_
  f_status_t f_compare_utf_dynamic_partial_except_trim(const f_utf_string_static_t string1, const f_utf_string_static_t string2, const f_string_range_t range1, const f_string_range_t range2, const f_number_unsigneds_t except1, const f_number_unsigneds_t except2) {

    return private_f_compare_utf_except_trim(
      string1.string,
      string2.string,
      range1.start,
      range2.start,
      string1.used <= range1.stop
        ? string1.used
        : range1.stop + 1,
      string2.used <= range2.stop
        ? string2.used
        : range2.stop + 1,
      except1,
      except2
    );
  }
#endif // _di_f_compare_utf_dynamic_partial_except_trim_

#ifndef _di_f_compare_utf_dynamic_partial_except_trim_dynamic_
  f_status_t f_compare_utf_dynamic_partial_except_trim_dynamic(const f_utf_string_static_t string1, const f_utf_string_static_t string2, const f_string_range_t range2, const f_number_unsigneds_t except1, const f_number_unsigneds_t except2) {

    return private_f_compare_utf_except_trim(
      string1.string,
      string2.string,
      0,
      range2.start,
      string1.used,
      string2.used <= range2.stop
        ? string2.used
        : range2.stop + 1,
      except1,
      except2
    );
  }
#endif // _di_f_compare_utf_dynamic_partial_except_trim_dynamic_

#ifndef _di_f_compare_utf_dynamic_partial_except_trim_string_
  f_status_t f_compare_utf_dynamic_partial_except_trim_string(const f_utf_string_t string1, const f_utf_string_static_t string2, const f_number_unsigned_t length1, const f_string_range_t range2, const f_number_unsigneds_t except1, const f_number_unsigneds_t except2) {

    return private_f_compare_utf_except_trim(
      string1,
      string2.string,
      0,
      range2.start,
      length1,
      string2.used <= range2.stop
        ? string2.used
        : range2.stop + 1,
      except1,
      except2
    );
  }
#endif // _di_f_compare_utf_dynamic_partial_except_trim_string_

#ifndef _di_f_compare_utf_dynamic_partial_trim_
  f_status_t f_compare_utf_dynamic_partial_trim(const f_utf_string_static_t string1, const f_utf_string_static_t string2, const f_string_range_t range1, const f_string_range_t range2) {

    return private_f_compare_utf_trim(
      string1.string,
      string2.string,
      range1.start,
      range2.start,
      string1.used <= range1.stop
        ? string1.used
        : range1.stop + 1,
      string2.used <= range2.stop
        ? string2.used
        : range2.stop + 1
      );
  }
#endif // _di_f_compare_utf_utf_string_dynamic_partial_trim_

#ifndef _di_f_compare_utf_dynamic_partial_trim_dynamic_
  f_status_t f_compare_utf_dynamic_partial_trim_dynamic(const f_utf_string_static_t string1, const f_utf_string_static_t string2, const f_string_range_t range2) {

    return private_f_compare_utf_trim(
      string1.string,
      string2.string,
      0,
      range2.start,
      string1.used,
      string2.used <= range2.stop
        ? string2.used
        : range2.stop + 1
    );
  }
#endif // _di_f_compare_utf_dynamic_partial_trim_dynamic_

#ifndef _di_f_compare_utf_dynamic_partial_trim_string_
  f_status_t f_compare_utf_dynamic_partial_trim_string(const f_utf_string_t string1, const f_utf_string_static_t string2, const f_number_unsigned_t length1, const f_string_range_t range2) {

    return private_f_compare_utf_trim(
      string1,
      string2.string,
      0,
      range2.start,
      length1,
      string2.used <= range2.stop
        ? string2.used
        : range2.stop + 1
    );
  }
#endif // _di_f_compare_utf_dynamic_partial_trim_string_

#ifndef _di_f_compare_utf_except_
  f_status_t f_compare_utf_except(const f_utf_string_t string1, const f_utf_string_t string2, const f_number_unsigned_t length1, const f_number_unsigned_t length2, const f_number_unsigneds_t except1, const f_number_unsigneds_t except2) {

    return private_f_compare_utf_except(string1, string2, 0, 0, length1, length2, except1, except2);
  }
#endif // _di_f_compare_utf_except_

#ifndef _di_f_compare_utf_except_trim_
  f_status_t f_compare_utf_except_trim(const f_utf_string_t string1, const f_utf_string_t string2, const f_number_unsigned_t length1, const f_number_unsigned_t length2, const f_number_unsigneds_t except1, const f_number_unsigneds_t except2) {

    return private_f_compare_utf_except_trim(string1, string2, 0, 0, length1, length2, except1, except2);
  }
#endif // _di_f_compare_utf_except_trim_

#ifndef _di_f_compare_utf_trim_
  f_status_t f_compare_utf_trim(const f_utf_string_t string1, const f_utf_string_t string2, const f_number_unsigned_t length1, const f_number_unsigned_t length2) {

    return private_f_compare_utf_trim(string1, string2, 0, 0, length1, length2);
  }
#endif // _di_f_compare_utf_trim_

#ifdef __cplusplus
} // extern "C"
#endif
