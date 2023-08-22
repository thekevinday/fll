/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines map string data.
 *
 * This is auto-included by string.h and should not need to be explicitly included.
 */
#ifndef _F_string_map_multi_h
#define _F_string_map_multi_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A string map consisting of a name and multiple values.
 *
 * Properties:
 *   - name:  A string representing the map name.
 *   - value: An array of strings representing the map value.
 */
#ifndef _di_f_string_map_multi_t_
  typedef struct {
    f_string_dynamic_t name;
    f_string_dynamics_t value;
  } f_string_map_multi_t;

  #define f_string_map_multi_t_initialize { f_string_dynamic_t_initialize, f_string_dynamics_t_initialize }

  #define macro_f_string_map_multi_t_initialize_1(name, value) { name, value }

  #define macro_f_string_map_multi_t_clear(map) \
    macro_f_string_dynamic_t_clear(map.name) \
    macro_f_string_dynamics_t_clear(map.value)
#endif // _di_f_string_map_multi_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_map_multi_h
