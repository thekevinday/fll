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
  { \
    f_status allocation_status = f_none; \
    \
    f_string_length i = 0; \
    \
    while (i < delimits.used) { \
      buffer.string[delimits.array[i]] = f_fss_delimit_placeholder; \
      i++; \
    } \
    \
    f_macro_strings_string_lengths_delete(allocation_status, delimits); \
  }
#endif // _di_fl_macro_fss_apply_delimit_placeholders_

#ifndef _di_fl_macro_fss_skip_past_delimit_placeholders_
  #define fl_macro_fss_skip_past_delimit_placeholders(buffer, input) \
    while (buffer.string[input.start] == f_fss_delimit_placeholder) { \
      ++input.start;\
      \
      if (input.start >= buffer.used) break; \
      if (input.start  > input.stop) break; \
    } // while
#endif // _di_fl_macro_fss_skip_past_delimit_placeholders_

#ifndef _di_fl_macro_fss_object_return_on_overflow_
  #define fl_macro_fss_object_return_on_overflow(buffer, input, found, delimits, eos_status, stop_status) \
    if (input.start >= buffer.used) { \
      f_status allocation_status = f_none; \
      f_macro_strings_string_lengths_delete(allocation_status, delimits); \
      \
      found.stop = buffer.used - 1; \
      return eos_status; \
    } \
    else if (input.start > input.stop) { \
      f_status allocation_status = f_none; \
      f_macro_strings_string_lengths_delete(allocation_status, delimits); \
      \
      found.stop = input.stop; \
      return stop_status; \
    }
#endif // _di_fl_macro_fss_object_return_on_overflow_

#ifndef _di_fl_macro_fss_object_delimited_return_on_overflow_
  #define fl_macro_fss_object_delimited_return_on_overflow(buffer, input, found, delimits, eos_status, stop_status) \
    if (input.start >= buffer.used) { \
      f_status allocation_status = f_none; \
      f_string_length i = 0; \
      \
      while (i < delimits.used) { \
        buffer.string[delimits.array[i]] = f_fss_delimit_placeholder; \
        i++; \
      } \
      f_macro_strings_string_lengths_delete(allocation_status, delimits); \
      \
      found.stop = buffer.used - 1; \
      return eos_status; \
    } \
    else if (input.start > input.stop) { \
      f_status allocation_status = f_none; \
      f_string_length i = 0; \
      \
      while (i < delimits.used) { \
        buffer.string[delimits.array[i]] = f_fss_delimit_placeholder; \
        i++; \
      } \
      f_macro_strings_string_lengths_delete(allocation_status, delimits); \
      \
      found.stop = input.stop; \
      return stop_status; \
    }
#endif // _di_fl_macro_fss_object_delimited_return_on_overflow_

#ifndef _di_fl_macro_fss_content_return_on_overflow_
  #define fl_macro_fss_content_return_on_overflow(buffer, input, found, delimits, eos_status, stop_status) \
    if (input.start >= buffer.used) { \
      f_status allocation_status = f_none; \
      f_macro_strings_string_lengths_delete(allocation_status, delimits); \
      \
      found.array[found.used].stop = buffer.used - 1; \
      return eos_status; \
    } \
    else if (input.start > input.stop) { \
      f_status allocation_status = f_none; \
      f_macro_strings_string_lengths_delete(allocation_status, delimits); \
      \
      found.array[found.used].stop = input.stop; \
      return stop_status; \
    }
#endif // _di_fl_macro_fss_content_return_on_overflow_

#ifndef _di_fl_macro_fss_content_delimited_return_on_overflow_
  #define fl_macro_fss_content_delimited_return_on_overflow(buffer, input, found, delimits, eos_status, stop_status) \
    if (input.start >= buffer.used) { \
      f_status allocation_status = f_none; \
      f_string_length i = 0; \
      \
      while (i < delimits.used) { \
        buffer.string[delimits.array[i]] = f_fss_delimit_placeholder; \
        i++; \
      } \
      f_macro_strings_string_lengths_delete(allocation_status, delimits); \
      \
      found.array[found.used].stop = buffer.used - 1; \
      return eos_status; \
    } \
    else if (input.start > input.stop) { \
      f_status allocation_status = f_none; \
      f_string_length i = 0; \
      \
      while (i < delimits.used) { \
        buffer.string[delimits.array[i]] = f_fss_delimit_placeholder; \
        i++; \
      } \
      f_macro_strings_string_lengths_delete(allocation_status, delimits); \
      \
      found.array[found.used].stop = input.stop; \
      return stop_status; \
    }
#endif // _di_fl_macro_fss_content_delimited_return_on_overflow_

#ifndef _di_fl_macro_fss_content_return_on_overflow_reset_
  #define fl_macro_fss_content_return_on_overflow_reset(buffer, input, found, delimits, eos_status, stop_status, set_stop) \
    if (input.start >= buffer.used) { \
      f_status allocation_status = f_none; \
      f_macro_strings_string_lengths_delete(allocation_status, delimits); \
      \
      input.start = set_stop; \
      found.array[found.used].stop = set_stop; \
      return eos_status; \
    } \
    else if (input.start > input.stop) { \
      f_status allocation_status = f_none; \
      f_macro_strings_string_lengths_delete(allocation_status, delimits); \
      \
      input.start = set_stop; \
      found.array[found.used].stop = set_stop; \
      return stop_status; \
    }
#endif // _di_fl_macro_fss_content_return_on_overflow_reset_

#ifndef _di_fl_macro_fss_content_delimited_return_on_overflow_reset_
  #define fl_macro_fss_content_delimited_return_on_overflow_reset(buffer, input, found, delimits, eos_status, stop_status, set_stop) \
    if (input.start >= buffer.used) { \
      f_status allocation_status = f_none; \
      f_string_length i = 0; \
      \
      while (i < delimits.used) { \
        buffer.string[delimits.array[i]] = f_fss_delimit_placeholder; \
        i++; \
      } \
      f_macro_strings_string_lengths_delete(allocation_status, delimits); \
      \
      input.start = set_stop; \
      found.array[found.used].stop = set_stop; \
      return eos_status; \
    } \
    else if (input.start > input.stop) { \
      f_status allocation_status = f_none; \
      f_string_length i = 0; \
      \
      while (i < delimits.used) { \
        buffer.string[delimits.array[i]] = f_fss_delimit_placeholder; \
        i++; \
      } \
      f_macro_strings_string_lengths_delete(allocation_status, delimits); \
      \
      input.start = set_stop; \
      found.array[found.used].stop = set_stop; \
      return stop_status; \
    }
#endif // _di_fl_macro_fss_content_delimited_return_on_overflow_reset_

#ifndef _di_fl_macro_fss_allocate_content_if_necessary_
  #define fl_macro_fss_allocate_content_if_necessary(content, delimits) \
    if (content.used >= content.size) { \
      f_status status = f_none; \
      \
      f_macro_fss_content_resize(status, content, content.size + f_fss_default_allocation_step); \
      if (f_status_is_error(status)) { \
        f_status allocation_status = f_none; \
        f_macro_strings_string_lengths_delete(allocation_status, delimits); \
        \
        return status; \
      } \
    }
#endif // _di_fl_macro_fss_allocate_content_if_necessary_

#ifndef _di_fl_macro_fss_object_seek_till_newline_
  #define fl_macro_fss_object_seek_till_newline(buffer, input, delimits, eos_status, stop_status) \
    while (buffer.string[input.start] != f_eol) { \
      ++input.start; \
      if (input.start >= buffer.used) { \
        f_status allocation_status = f_none; \
        f_macro_strings_string_lengths_delete(allocation_status, delimits); \
        \
        return eos_status; \
      } \
      if (input.start > input.stop) { \
        f_status allocation_status = f_none; \
        f_macro_strings_string_lengths_delete(allocation_status, delimits); \
        \
        return stop_status; \
      } \
    } // while
#endif // _di_fl_macro_fss_object_seek_till_newline_

#ifndef _di_fl_macro_fss_object_delimited_seek_till_newline_
  #define fl_macro_fss_object_delimited_seek_till_newline(buffer, input, delimits, eos_status, stop_status) \
    while (buffer.string[input.start] != f_eol) { \
      ++input.start; \
      if (input.start >= buffer.used) { \
        f_status allocation_status = f_none; \
        f_string_length i = 0; \
        \
        while (i < delimits.used) { \
          buffer.string[delimits.array[i]] = f_fss_delimit_placeholder; \
          i++; \
        } \
        f_macro_strings_string_lengths_delete(allocation_status, delimits); \
        \
        return eos_status; \
      } \
      if (input.start > input.stop) { \
        f_status allocation_status = f_none; \
        f_string_length i = 0; \
        \
        while (i < delimits.used) { \
          buffer.string[delimits.array[i]] = f_fss_delimit_placeholder; \
          i++; \
        } \
        f_macro_strings_string_lengths_delete(allocation_status, delimits); \
        \
        return stop_status; \
      } \
    } // while
#endif // _di_fl_macro_fss_object_delimited_seek_till_newline_

#ifndef _di_fl_macro_fss_content_seek_till_newline_
  #define fl_macro_fss_content_seek_till_newline(buffer, input, found, delimits, eos_status, stop_status) \
    while (buffer.string[input.start] != f_eol) { \
      ++input.start; \
      if (input.start >= buffer.used) { \
        f_status allocation_status = f_none; \
        f_macro_strings_string_lengths_delete(allocation_status, delimits); \
        \
        found.array[found.used].stop = input.stop; \
        return eos_status; \
      } \
      if (input.start > input.stop) { \
        f_status allocation_status = f_none; \
        f_macro_strings_string_lengths_delete(allocation_status, delimits); \
        \
        found.array[found.used].stop = input.stop; \
        return stop_status; \
      } \
    } // while
#endif // _di_fl_macro_fss_content_seek_till_newline_

#ifndef _di_fl_macro_fss_content_delimited_seek_till_newline_
  #define fl_macro_fss_content_delimited_seek_till_newline(buffer, input, found, delimits, eos_status, stop_status) \
    while (buffer.string[input.start] != f_eol) { \
      ++input.start; \
      if (input.start >= buffer.used) { \
        f_status allocation_status = f_none; \
        f_string_length i = 0; \
        \
        while (i < delimits.used) { \
          buffer.string[delimits.array[i]] = f_fss_delimit_placeholder; \
          i++; \
        } \
        f_macro_strings_string_lengths_delete(allocation_status, delimits); \
        \
        found.array[found.used].stop = input.stop; \
        return eos_status; \
      } \
      if (input.start > input.stop) { \
        f_status allocation_status = f_none; \
        f_string_length i = 0; \
        \
        while (i < delimits.used) { \
          buffer.string[delimits.array[i]] = f_fss_delimit_placeholder; \
          i++; \
        } \
        f_macro_strings_string_lengths_delete(allocation_status, delimits); \
        \
        found.array[found.used].stop = input.stop; \
        return stop_status; \
      } \
    } // while
#endif // _di_fl_macro_fss_content_delimited_seek_till_newline_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_fss_macro_h
