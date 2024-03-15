/**
 * FLL - Level 0
 *
 * Project: UTF
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines map string data.
 *
 * This is auto-included by string.h and should not need to be explicitly included.
 */
#ifndef _F_utf_map_multi_h
#define _F_utf_map_multi_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A string map consisting of a key and multiple values.
 *
 * Properties:
 *   - key:   A string representing the map key.
 *   - value: An array of strings representing the map value.
 */
#ifndef _di_f_utf_string_map_multi_t_
  typedef struct {
    f_utf_string_dynamic_t key;
    f_utf_string_dynamics_t value;
  } f_utf_string_map_multi_t;

  #define f_utf_string_map_multi_t_initialize { f_utf_string_dynamic_t_initialize, f_utf_string_dynamics_t_initialize }

  #define macro_f_utf_string_map_multi_t_initialize_1(key, value) { key, value }

  #define macro_f_utf_string_map_multi_t_clear(map) \
    macro_f_utf_string_dynamic_t_clear(map.key) \
    macro_f_utf_string_dynamics_t_clear(map.value)
#endif // _di_f_utf_string_map_multi_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_utf_map_multi_h
