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
#ifndef _F_utf_statics_h
#define _F_utf_statics_h

#ifdef __cplusplus
extern "C" {
#endif

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

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_utf_string_statics_t;

  #define f_utf_string_statics_t_initialize { 0, 0, 0 }

  #define macro_f_utf_string_statics_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_utf_string_statics_t_initialize_2(array, length) { array, length, length }

  #define macro_f_utf_string_statics_t_clear(statics) \
    statics.array = 0; \
    statics.size = 0; \
    statics.used = 0;
#endif // _di_f_utf_string_statics_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_utf_statics_h
