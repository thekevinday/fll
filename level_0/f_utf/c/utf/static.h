/**
 * FLL - Level 0
 *
 * Project: UTF
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines static string data.
 *
 * This is auto-included by string.h and should not need to be explicitly included.
 */
#ifndef _F_utf_static_h
#define _F_utf_static_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A string that is analogous to f_utf_string_dynamic_t but intended for static-only uses.
 *
 * The f_utf_string_static_t type should never be directly allocated or deallocated.
 *
 * A special macro_f_utf_string_static_t_initialize_1() is provided for the special purpose of easily initialize a static string.
 * A special macro_f_utf_string_static_t_initialize_2() is provided for the special purpose of easily initialize a static string with an identical used and size.
 *
 * Properties:
 *   - string: The string.
 *   - size:   Total amount of space available.
 *   - used:   Total number of space used.
 */
#ifndef _di_f_utf_string_static_t_
  typedef struct {
    f_utf_string_t string;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_utf_string_static_t;

  #define f_utf_string_static_t_initialize { 0, 0, 0 }

  #define macro_f_utf_string_static_t_initialize_1(string, size, used) { string, size, used }
  #define macro_f_utf_string_static_t_initialize_2(string, length) { string, length, length }

  #define macro_f_utf_string_static_t_clear(string_static) \
    string_static.string = 0; \
    string_static.size = 0; \
    string_static.used = 0;
#endif // _di_f_utf_string_static_t_

/**
 * Provide a static empty string.
 *
 * This is intended to represent an empty string.
 */
#ifndef _di_f_utf_string_empty_s_
  extern const f_utf_string_static_t f_utf_string_empty_s;
#endif // _di_f_utf_string_empty_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_utf_static_h
