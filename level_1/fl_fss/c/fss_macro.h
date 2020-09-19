/**
 * FLL - Level 1
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides generic functionality shared between and used by different fss processing functions.
 */
#ifndef _FL_fss_macro_h
#define _FL_fss_macro_h

#ifdef __cplusplus
extern "C" {
#endif

// TODO: check if character to be replaced is UTF and apply placeholder to entire width.
#ifndef _di_fl_macro_fss_apply_delimit_placeholders_
  #define fl_macro_fss_apply_delimit_placeholders(buffer, delimits) \
    for (f_array_length_t _macro__i = 0; _macro__i < delimits.used; _macro__i++) { \
      buffer.string[delimits.array[_macro__i]] = f_fss_delimit_placeholder; \
    } \
    \
    f_macro_string_lengths_t_delete_simple(delimits);
#endif // _di_fl_macro_fss_apply_delimit_placeholders_

#ifndef _di_fl_macro_fss_skip_past_delimit_placeholders_
  #define fl_macro_fss_skip_past_delimit_placeholders(buffer, range) \
    while (buffer.string[range.start] == f_fss_delimit_placeholder) { \
      range.start++;\
      \
      if (range.start >= buffer.used) break; \
      if (range.start  > range.stop) break; \
    } // while
#endif // _di_fl_macro_fss_skip_past_delimit_placeholders_

#ifndef _di_fl_macro_fss_object_return_on_overflow_
  #define fl_macro_fss_object_return_on_overflow(buffer, range, found, delimits, eos_status, stop_status) \
    if (range.start >= buffer.used) { \
      f_macro_string_lengths_t_delete_simple(delimits); \
      \
      found.stop = buffer.used - 1; \
      return eos_status; \
    } \
    else if (range.start > range.stop) { \
      f_macro_string_lengths_t_delete_simple(delimits); \
      \
      found.stop = range.stop; \
      return stop_status; \
    }
#endif // _di_fl_macro_fss_object_return_on_overflow_

#ifndef _di_fl_macro_fss_object_delimited_return_on_overflow_
  #define fl_macro_fss_object_delimited_return_on_overflow(buffer, range, found, delimits, eos_status, stop_status) \
    if (range.start >= buffer.used) { \
      for (f_array_length_t _macro__i = 0; _macro__i < delimits.used; _macro__i++) { \
        buffer.string[delimits.array[_macro__i]] = f_fss_delimit_placeholder; \
      } \
      f_macro_string_lengths_t_delete_simple(delimits); \
      \
      found.stop = buffer.used - 1; \
      return eos_status; \
    } \
    else if (range.start > range.stop) { \
      for (f_array_length_t _macro__i = 0; _macro__i < delimits.used; _macro__i++) { \
        buffer.string[delimits.array[_macro__i]] = f_fss_delimit_placeholder; \
        _macro__i++; \
      } \
      f_macro_string_lengths_t_delete_simple(delimits); \
      \
      found.stop = range.stop; \
      return stop_status; \
    }
#endif // _di_fl_macro_fss_object_delimited_return_on_overflow_

#ifndef _di_fl_macro_fss_content_return_on_overflow_
  #define fl_macro_fss_content_return_on_overflow(buffer, range, found, delimits, eos_status, stop_status) \
    if (range.start >= buffer.used) { \
      f_macro_string_lengths_t_delete_simple(delimits); \
      \
      found.array[found.used].stop = buffer.used - 1; \
      return eos_status; \
    } \
    else if (range.start > range.stop) { \
      f_macro_string_lengths_t_delete_simple(delimits); \
      \
      found.array[found.used].stop = range.stop; \
      return stop_status; \
    }
#endif // _di_fl_macro_fss_content_return_on_overflow_

#ifndef _di_fl_macro_fss_content_delimited_return_on_overflow_
  #define fl_macro_fss_content_delimited_return_on_overflow(buffer, range, found, delimits, eos_status, stop_status) \
    if (range.start >= buffer.used) { \
      for (f_array_length_t _macro__i = 0; _macro__i < delimits.used; _macro__i++) { \
        buffer.string[delimits.array[_macro__i]] = f_fss_delimit_placeholder; \
      } \
      f_macro_string_lengths_t_delete_simple(delimits); \
      \
      found.array[found.used].stop = buffer.used - 1; \
      return eos_status; \
    } \
    else if (range.start > range.stop) { \
      for (f_array_length_t _macro__i = 0; _macro__i < delimits.used; _macro__i++) { \
        buffer.string[delimits.array[_macro__i]] = f_fss_delimit_placeholder; \
      } \
      f_macro_string_lengths_t_delete_simple(delimits); \
      \
      found.array[found.used].stop = range.stop; \
      return stop_status; \
    }
#endif // _di_fl_macro_fss_content_delimited_return_on_overflow_

#ifndef _di_fl_macro_fss_allocate_content_if_necessary_
  #define fl_macro_fss_allocate_content_if_necessary(content, delimits) \
    if (content.used == content.size) { \
      f_status_t status = F_none; \
      \
      f_macro_fss_content_t_resize(status, content, content.size + f_fss_default_allocation_step); \
      if (F_status_is_error(status)) { \
        f_macro_string_lengths_t_delete_simple(delimits); \
        \
        return status; \
      } \
    }
#endif // _di_fl_macro_fss_allocate_content_if_necessary_

#ifndef _di_fl_macro_fss_nest_return_on_overflow_
  #define fl_macro_fss_nest_return_on_overflow(buffer, range, found, delimits, positions, objects, eos_status, stop_status) \
    if (range.start >= buffer.used) { \
      f_macro_string_lengths_t_delete_simple(delimits); \
      f_macro_string_lengths_t_delete_simple(positions); \
      f_macro_fss_objects_t_delete_simple(objects); \
      \
      return eos_status; \
    } \
    else if (range.start > range.stop) { \
      f_macro_string_lengths_t_delete_simple(delimits); \
      f_macro_string_lengths_t_delete_simple(positions); \
      f_macro_fss_objects_t_delete_simple(objects); \
      \
      return stop_status; \
    }
#endif // _di_fl_macro_fss_nest_return_on_overflow_

#ifndef _di_fl_macro_fss_nest_delimited_return_on_overflow_
  #define fl_macro_fss_nest_delimited_return_on_overflow(buffer, range, found, delimits, positions, objects, eos_status, stop_status) \
    if (range.start >= buffer.used) { \
      for (f_array_length_t _macro__i = 0; _macro__i < delimits.used; _macro__i++) { \
        buffer.string[delimits.array[_macro__i]] = f_fss_delimit_placeholder; \
      } \
      f_macro_string_lengths_t_delete_simple(delimits); \
      f_macro_string_lengths_t_delete_simple(positions); \
      f_macro_fss_objects_t_delete_simple(objects); \
      \
      return eos_status; \
    } \
    else if (range.start > range.stop) { \
      for (f_array_length_t _macro__i = 0; _macro__i < delimits.used; _macro__i++) { \
        buffer.string[delimits.array[_macro__i]] = f_fss_delimit_placeholder; \
      } \
      f_macro_string_lengths_t_delete_simple(delimits); \
      f_macro_string_lengths_t_delete_simple(positions); \
      f_macro_fss_objects_t_delete_simple(objects); \
      \
      return stop_status; \
    }
#endif // _di_fl_macro_fss_nest_delimited_return_on_overflow_

#ifndef _di_fl_macro_fss_object_seek_till_newline_
  #define fl_macro_fss_object_seek_till_newline(buffer, range, delimits, eos_status, stop_status) \
    while (buffer.string[range.start] != f_string_eol[0]) { \
      range.start++; \
      if (range.start >= buffer.used) { \
        f_macro_string_lengths_t_delete_simple(delimits); \
        \
        return eos_status; \
      } \
      if (range.start > range.stop) { \
        f_macro_string_lengths_t_delete_simple(delimits); \
        \
        return stop_status; \
      } \
    } // while
#endif // _di_fl_macro_fss_object_seek_till_newline_

#ifndef _di_fl_macro_fss_object_delimited_seek_till_newline_
  #define fl_macro_fss_object_delimited_seek_till_newline(buffer, range, delimits, eos_status, stop_status) \
    while (buffer.string[range.start] != f_string_eol[0]) { \
      range.start++; \
      if (range.start >= buffer.used) { \
        for (f_array_length_t _macro__i = 0; _macro__i < delimits.used; _macro__i++) { \
          buffer.string[delimits.array[_macro__i]] = f_fss_delimit_placeholder; \
        } \
        f_macro_string_lengths_t_delete_simple(delimits); \
        \
        return eos_status; \
      } \
      if (range.start > range.stop) { \
        for (f_array_length_t _macro__i = 0; _macro__i < delimits.used; _macro__i++) { \
          buffer.string[delimits.array[_macro__i]] = f_fss_delimit_placeholder; \
        } \
        f_macro_string_lengths_t_delete_simple(delimits); \
        \
        return stop_status; \
      } \
    } // while
#endif // _di_fl_macro_fss_object_delimited_seek_till_newline_

#ifndef _di_fl_macro_fss_content_seek_till_newline_
  #define fl_macro_fss_content_seek_till_newline(buffer, range, found, delimits, eos_status, stop_status) \
    while (buffer.string[range.start] != f_string_eol[0]) { \
      range.start++; \
      if (range.start >= buffer.used) { \
        f_macro_string_lengths_t_delete_simple(delimits); \
        \
        found.array[found.used].stop = range.stop; \
        return eos_status; \
      } \
      if (range.start > range.stop) { \
        f_macro_string_lengths_t_delete_simple(delimits); \
        \
        found.array[found.used].stop = range.stop; \
        return stop_status; \
      } \
    } // while
#endif // _di_fl_macro_fss_content_seek_till_newline_

#ifndef _di_fl_macro_fss_content_delimited_seek_till_newline_
  #define fl_macro_fss_content_delimited_seek_till_newline(buffer, range, found, delimits, eos_status, stop_status) \
    while (buffer.string[range.start] != f_string_eol[0]) { \
      range.start++; \
      if (range.start >= buffer.used) { \
        for (f_array_length_t _macro__i = 0; _macro__i < delimits.used; _macro__i++) { \
          buffer.string[delimits.array[_macro__i]] = f_fss_delimit_placeholder; \
        } \
        f_macro_string_lengths_t_delete_simple(delimits); \
        \
        found.array[found.used].stop = range.stop; \
        return eos_status; \
      } \
      if (range.start > range.stop) { \
        for (f_array_length_t _macro__i = 0; _macro__i < delimits.used; _macro__i++) { \
          buffer.string[delimits.array[_macro__i]] = f_fss_delimit_placeholder; \
        } \
        f_macro_string_lengths_t_delete_simple(delimits); \
        \
        found.array[found.used].stop = range.stop; \
        return stop_status; \
      } \
    } // while
#endif // _di_fl_macro_fss_content_delimited_seek_till_newline_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_fss_macro_h
