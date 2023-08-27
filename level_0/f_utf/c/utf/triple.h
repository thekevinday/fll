/**
 * FLL - Level 0
 *
 * Project: UTF
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines 3-tuple of string data called a triple (which is an ordered list of 3 strings).
 *
 * This is auto-included by string.h and should not need to be explicitly included.
 */
#ifndef _F_utf_triple_h
#define _F_utf_triple_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A string triple consisting of a set of three strings.
 *
 * Properties:
 *   - a: A string representing the first string in the triple.
 *   - b: A string representing the second string in the triple.
 *   - c: A string representing the third string in the triple.
 */
#ifndef _di_f_utf_string_triple_t_
  typedef struct {
    f_utf_string_dynamic_t a;
    f_utf_string_dynamic_t b;
    f_utf_string_dynamic_t c;
  } f_utf_string_triple_t;

  #define f_utf_string_triple_t_initialize { f_utf_string_dynamic_t_initialize, f_utf_string_dynamic_t_initialize, f_utf_string_dynamic_t_initialize }

  #define macro_f_utf_string_triple_t_clear(triple) \
    triple.a.array = 0; \
    triple.a.size = 0; \
    triple.a.used = 0; \
    triple.b.array = 0; \
    triple.b.size = 0; \
    triple.b.used = 0; \
    triple.c.array = 0; \
    triple.c.size = 0; \
    triple.c.used = 0;

  #define macro_f_utf_string_triple_t_initialize_1(a, b, c) { a, b, c }
#endif // _di_f_utf_string_triple_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_utf_triple_h
