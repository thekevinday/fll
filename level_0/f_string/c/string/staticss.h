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
#ifndef _F_string_staticss_h
#define _F_string_staticss_h

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
#ifndef _di_f_string_staticss_t_
  typedef struct {
    f_string_statics_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_string_staticss_t;

  #define f_string_staticss_t_initialize { 0, 0, 0 }

  #define macro_f_string_staticss_t_initialize(array, size, used) { array, size, used }
  #define macro_f_string_staticss_t_initialize2(array, length) { array, length, length }

  #define macro_f_string_staticss_t_clear(staticss) \
    staticss.array = 0; \
    staticss.size = 0; \
    staticss.used = 0;
#endif // _di_f_string_staticss_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_staticss_h
