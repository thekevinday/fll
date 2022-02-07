/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Defines common string data.
 *
 * This is auto-included by string.h and should not need to be explicitly included.
 */
#ifndef _F_string_common_h
#define _F_string_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * BUG: for whatever reason strnlen is considered not included with -Wall, even with __USE_GNU defined.
 *      therefore this gets defined here.
 */
#ifdef _en_BUG_strnlen_
  extern size_t strnlen (const char *string, size_t max_length);
#endif // _en_BUG_strnlen_

/**
 * Define the basic string type.
 *
 * Dynamic allocation macros are provided, but it is recommended to utilize the f_string_dynamic_t for dynamic allocation.
 *
 *  is provided as a way t have a string max for systems that do not support max string length in 64-bits (when f_array_length_t is set to uint64_t).
 *
 * The ideal length for a string is F_array_length_t_size_d, which generally defaults to 2^64 (unsigned).
 * However, the libc/POSIX appears to limit this to 2^63 (signed).
 * F_string_t_size_d is provided to help safely navigate this.
 */
#ifndef _di_f_string_t_
  typedef char *f_string_t;

  #define f_string_t_initialize 0

  #define macro_f_string_t_clear(string) string = 0;

  #define macro_f_string_t_resize(status, string, length_old, length_new) status = f_memory_resize(length_old, length_new, sizeof(char), (void **) & string);
  #define macro_f_string_t_adjust(status, string, length_old, length_new) status = f_memory_adjust(length_old, length_new, sizeof(char), (void **) & string);

  #define macro_f_string_t_delete_simple(string, length)  f_memory_resize(length, 0, sizeof(char), (void **) & string);
  #define macro_f_string_t_destroy_simple(string, length) f_memory_adjust(length, 0, sizeof(char), (void **) & string);

  #define F_string_t_size_d F_number_t_size_positive_d
#endif // _di_f_string_t_

/**
 * Define the constant string type.
 *
 * This is needed when passing a constant string as a function argument.
 * This cannot be allocated or deallocated.
 * This is provided for compatibility with some projects that return "const char *".
 *
 * GCC errors such as: "warning: assignment discards ‘const’ qualifier from pointer target type [-Wdiscarded-qualifiers]" can be avoided using this.
 *
 * Do not confuse this with "const f_string_static_t".
 * When "const f_string_static_t * xxx" is passed to a function, then "xxx" cannot be changed.
 * When "f_string_constant_t * xxx" is passed to a function, then "xxx" can be changed.
 */
#ifndef _di_f_string_constant_t_
  typedef const char *f_string_constant_t;

  #define f_string_constant_t_initialize 0

  #define macro_f_string_constant_t_clear(string) string = 0;
#endif // _di_f_string_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_common_h
