/**
 * FLL - Level 0
 *
 * Project: String
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
 * A special macro_f_utf_string_static_t_initialize() is provided for the special purpose of easily initialize a static string.
 * A special macro_f_utf_string_static_t_initialize2() is provided for the special purpose of easily initialize a static string with an identical used and size.
 *
 * string: The string.
 * size:   Total amount of space available.
 * used:   Total number of space used.
 */
#ifndef _di_f_utf_string_static_t_
  typedef struct {
    f_utf_string_t string;

    f_array_length_t size;
    f_array_length_t used;
  } f_utf_string_static_t;

  #define f_utf_string_static_t_initialize { 0, 0, 0 }

  #define macro_f_utf_string_static_t_initialize(string, size, used) { string, size, used }
  #define macro_f_utf_string_static_t_initialize2(string, length) { string, length, length }

  #define macro_f_utf_string_static_t_clear(string_static) \
    string_static.string = 0; \
    string_static.size = 0; \
    string_static.used = 0;
#endif // _di_f_utf_string_static_t_

/**
 * An array of static strings.
 *
 * array: The array of static strings.
 * size:  Total amount of space available.
 * used:  Total number of space used.
 */
#ifndef _di_f_utf_string_statics_t_
  typedef struct {
    f_utf_string_static_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_utf_string_statics_t;

  #define f_utf_string_statics_t_initialize { 0, 0, 0 }

  #define macro_f_utf_string_statics_t_initialize(array, size, used) { array, size, used }
  #define macro_f_utf_string_statics_t_initialize2(array, length) { array, length, length }

  #define macro_f_utf_string_statics_t_clear(statics) \
    statics.array = 0; \
    statics.size = 0; \
    statics.used = 0;
#endif // _di_f_utf_string_statics_t_

/**
 * An array of static strings.
 *
 * array: The array of static strings.
 * size:  Total amount of space available.
 * used:  Total number of space used.
 */
#ifndef _di_f_utf_string_staticss_t_
  typedef struct {
    f_utf_string_statics_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_utf_string_staticss_t;

  #define f_utf_string_staticss_t_initialize { 0, 0, 0 }

  #define macro_f_utf_string_staticss_t_initialize(array, size, used) { array, size, used }
  #define macro_f_utf_string_staticss_t_initialize2(array, length) { array, length, length }

  #define macro_f_utf_string_staticss_t_clear(staticss) \
    staticss.array = 0; \
    staticss.size = 0; \
    staticss.used = 0;
#endif // _di_f_utf_string_staticss_t_

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
