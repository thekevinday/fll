/**
 * FLL - Level 1
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides generic functionality shared between and used by different fss processing functions.
 */
#ifndef _PRIVATE_FL_fss_macro_h
#define _PRIVATE_FL_fss_macro_h

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_macro_fss_object_return_on_overflow_
  #define private_fl_macro_fss_object_return_on_overflow(buffer, range, found, delimits, delimits_used, eos_status, stop_status) \
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
#endif // _di_fl_macro_fss_object_return_on_overflow_

#ifndef _di_fl_macro_fss_object_return_on_overflow_delimited_
  #define private_fl_macro_fss_object_return_on_overflow_delimited(buffer, range, found, eos_status, stop_status) \
    if (range.start >= buffer.used) { \
      found.stop = buffer.used - 1; \
      return eos_status; \
    } \
    else if (range.start > range.stop) { \
      found.stop = range.stop; \
      return stop_status; \
    }
#endif // _di_fl_macro_fss_object_return_on_overflow_delimited_

#ifndef _di_fl_macro_fss_content_return_on_overflow_
  #define private_fl_macro_fss_content_return_on_overflow(buffer, range, found, delimits, delimits_used, eos_status, stop_status) \
    if (range.start >= buffer.used) { \
      delimits.used = delimits_used; \
      found.array[found.used].stop = buffer.used - 1; \
      return eos_status; \
    } \
    else if (range.start > range.stop) { \
      delimits.used = delimits_used; \
      found.array[found.used].stop = range.stop; \
      return stop_status; \
    }
#endif // _di_fl_macro_fss_content_return_on_overflow_

#ifndef _di_fl_macro_fss_content_with_comments_return_on_overflow_
  #define private_fl_macro_fss_content_with_comments_return_on_overflow(buffer, range, found, delimits, delimits_used, comments, comments_used, eos_status, stop_status) \
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
#endif // _di_fl_macro_fss_content_with_comments_return_on_overflow_

#ifndef _di_fl_macro_fss_content_return_on_overflow_delimited_
  #define private_fl_macro_fss_content_return_on_overflow_delimited(buffer, range, found, eos_status, stop_status) \
    if (range.start >= buffer.used) { \
      found.array[found.used].stop = buffer.used - 1; \
      return eos_status; \
    } \
    else if (range.start > range.stop) { \
      found.array[found.used].stop = range.stop; \
      return stop_status; \
    }
#endif // _di_fl_macro_fss_content_return_on_overflow_delimited_

#ifndef _di_fl_macro_fss_nest_return_on_overflow_
  #define private_fl_macro_fss_nest_return_on_overflow(buffer, range, found, delimits, delimits_used, comments, comments_used, positions, objects, eos_status, stop_status) \
    if (range.start >= buffer.used) { \
      delimits.used = delimits_used; \
      comments.used = comments_used; \
      f_macro_string_lengths_t_delete_simple(positions); \
      private_fl_fss_objects_delete(&objects); \
      return eos_status; \
    } \
    else if (range.start > range.stop) { \
      delimits.used = delimits_used; \
      comments.used = comments_used; \
      f_macro_string_lengths_t_delete_simple(positions); \
      private_fl_fss_objects_delete(&objects); \
      return stop_status; \
    }
#endif // _di_fl_macro_fss_nest_return_on_overflow_

#ifndef _di_fl_macro_fss_nest_return_on_overflow_delimited_
  #define private_fl_macro_fss_nest_return_on_overflow_delimited(buffer, range, found, positions, objects, eos_status, stop_status) \
    if (range.start >= buffer.used) { \
      f_macro_string_lengths_t_delete_simple(positions); \
      private_fl_fss_objects_delete(&objects); \
      return eos_status; \
    } \
    else if (range.start > range.stop) { \
      f_macro_string_lengths_t_delete_simple(positions); \
      private_fl_fss_objects_delete(&objects); \
      return stop_status; \
    }
#endif // _di_fl_macro_fss_nest_return_on_overflow_delimited_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FL_fss_macro_h
