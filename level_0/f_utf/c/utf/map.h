/**
 * FLL - Level 0
 *
 * Project: UTF
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines map UTF-8 string data.
 *
 * This is auto-included by utf.h and should not need to be explicitly included.
 */
#ifndef _F_utf_map_h
#define _F_utf_map_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A string map consisting of a name and value.
 *
 * name:  A string representing the map name.
 * value: A string representing the map value.
 */
#ifndef _di_f_utf_string_map_t_
  typedef struct {
    f_utf_string_dynamic_t name;
    f_utf_string_dynamic_t value;
  } f_utf_string_map_t;

  #define f_utf_string_map_t_initialize { f_utf_string_dynamic_t_initialize, f_utf_string_dynamic_t_initialize }

  #define macro_f_utf_string_map_t_initialize(name, value) { name, value }

  #define macro_f_utf_string_map_t_clear(map) \
    macro_f_utf_string_dynamic_t_clear(map.name) \
    macro_f_utf_string_dynamic_t_clear(map.value)

  #define macro_f_utf_string_map_t_delete_simple(map) \
    macro_f_utf_string_dynamic_t_delete_simple(map.name) \
    macro_f_utf_string_dynamic_t_delete_simple(map.value)

  #define macro_f_utf_string_map_t_destroy_simple(map) \
    macro_f_utf_string_dynamic_t_destroy_simple(map.name) \
    macro_f_utf_string_dynamic_t_destroy_simple(map.value)
#endif // _di_f_utf_string_map_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_utf_map_h
