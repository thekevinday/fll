/**
 * FLL - Level 1
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides generic functionality shared between and used by different fss processing functions.
 */
#ifndef _PRIVATE_FL_fss_macro_h
#define _PRIVATE_FL_fss_macro_h

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_macro_fl_fss_object_return_on_overflow_
  #define private_macro_fl_fss_object_return_on_overflow(buffer, range, found, delimits, delimits_used, eos_status, stop_status) \
    if (range.start >= buffer.used) { \
      delimits.used = delimits_used; \
      found.stop = buffer.used - 1; \
      return eos_status; \
    } \
    else if (range.start > range.stop) { \
      delimits.used = delimits_used; \
      found.stop = range.stop; \
      return stop_status; \
    }
#endif // _di_macro_fl_fss_object_return_on_overflow_

#ifndef _di_macro_fl_fss_object_return_on_overflow_delimited_
  #define private_macro_fl_fss_object_return_on_overflow_delimited(buffer, range, found, eos_status, stop_status) \
    if (range.start >= buffer.used) { \
      found.stop = buffer.used - 1; \
      return eos_status; \
    } \
    else if (range.start > range.stop) { \
      found.stop = range.stop; \
      return stop_status; \
    }
#endif // _di_macro_fl_fss_object_return_on_overflow_delimited_

#ifndef _di_macro_fl_fss_content_with_comments_return_on_overflow_
  #define private_macro_fl_fss_content_with_comments_return_on_overflow(buffer, range, found, delimits, delimits_used, comments, comments_used, eos_status, stop_status) \
    if (range.start >= buffer.used) { \
      delimits.used = delimits_used; \
      comments.used = comments_used; \
      found.array[found.used].stop = buffer.used - 1; \
      return eos_status; \
    } \
    else if (range.start > range.stop) { \
      delimits.used = delimits_used; \
      comments.used = comments_used; \
      found.array[found.used].stop = range.stop; \
      return stop_status; \
    }
#endif // _di_macro_fl_fss_content_with_comments_return_on_overflow_

#ifndef _di_macro_fl_fss_nest_return_on_overflow_
  #define private_macro_fl_fss_nest_return_on_overflow(buffer, range, found, delimits, delimits_used, comments, comments_used, positions, objects, slashes, eos_status, stop_status) \
    if (range.start >= buffer.used) { \
      delimits.used = delimits_used; \
      comments.used = comments_used; \
      macro_f_array_lengths_t_delete_simple(positions); \
      macro_f_fss_objects_t_delete_simple(objects); \
      macro_f_array_lengths_t_delete_simple(slashes); \
      return eos_status; \
    } \
    else if (range.start > range.stop) { \
      delimits.used = delimits_used; \
      comments.used = comments_used; \
      macro_f_array_lengths_t_delete_simple(positions); \
      macro_f_fss_objects_t_delete_simple(objects); \
      macro_f_array_lengths_t_delete_simple(slashes); \
      return stop_status; \
    }
#endif // _di_macro_fl_fss_nest_return_on_overflow_

#ifndef _di_macro_fl_fss_nest_return_on_overflow_delimited_
  #define private_macro_fl_fss_nest_return_on_overflow_delimited(buffer, range, found, positions, objects, slashes, eos_status, stop_status) \
    if (range.start >= buffer.used) { \
      macro_f_array_lengths_t_delete_simple(positions); \
      macro_f_fss_objects_t_delete_simple(objects); \
      macro_f_array_lengths_t_delete_simple(slashes); \
      return eos_status; \
    } \
    else if (range.start > range.stop) { \
      macro_f_array_lengths_t_delete_simple(positions); \
      macro_f_fss_objects_t_delete_simple(objects); \
      macro_f_array_lengths_t_delete_simple(slashes); \
      return stop_status; \
    }
#endif // _di_macro_fl_fss_nest_return_on_overflow_delimited_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FL_fss_macro_h
