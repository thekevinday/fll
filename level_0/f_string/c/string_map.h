/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines map string data.
 *
 * This is auto-included by string.h and should not need to be explicitly included.
 */
#ifndef _F_string_map_h
#define _F_string_map_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A string map consisting of a name and value.
 *
 * name: A string representing the map name.
 * value: A string representing the map value.
 */
#ifndef _di_f_string_map_t_
  typedef struct {
    f_string_dynamic_t name;
    f_string_dynamic_t value;
  } f_string_map_t;

  #define f_string_map_t_initialize { f_string_dynamic_t_initialize, f_string_dynamic_t_initialize }

  #define f_macro_string_map_t_clear(map) \
    map.array = 0; \
    map.size = 0; \
    map.used = 0;

  #define f_macro_string_map_t_delete(status, map) \
    f_macro_string_dynamic_t_delete(status, map.name) \
    if (status == F_none) { \
      f_macro_string_dynamic_t_delete(status, map.value) \
    }

  #define f_macro_string_map_t_destroy(status, map) \
    f_macro_string_dynamic_t_destroy(status, map.name) \
    if (status == F_none) { \
      f_macro_string_dynamic_t_destroy(status, map.value) \
    }

  #define f_macro_string_map_t_delete_simple(map) \
    f_macro_string_dynamic_t_delete_simple(map.name) \
    f_macro_string_dynamic_t_delete_simple(map.value)

  #define f_macro_string_map_t_destroy_simple(map) \
    f_macro_string_dynamic_t_destroy_simple(map.name) \
    f_macro_string_dynamic_t_destroy_simple(map.value)
#endif // _di_f_string_map_t_

/**
 * An array of string maps.
 *
 * array: the array of string maps.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_string_maps_t_
  typedef struct {
    f_string_map_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_string_maps_t;

  #define f_string_maps_t_initialize f_string_statics_t_initialize

  #define f_macro_string_maps_t_clear(maps) \
    maps.array = 0; \
    maps.size = 0; \
    maps.used = 0;

  #define f_macro_string_maps_t_new(status, maps, length) \
    f_macro_string_maps_t_clear(maps) \
    status = f_memory_new((void **) & maps.array, sizeof(f_string_map_t), length); \
    if (status == F_none) { \
      maps.size = length; \
      maps.used = 0; \
    }

  #define f_macro_string_maps_t_delete(status, maps) \
    status = F_none; \
    maps.used = maps.size; \
    while (maps.used) { \
      maps.used--; \
      f_macro_string_map_t_delete(status, maps.array[maps.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_delete((void **) & maps.array, sizeof(f_string_map_t), maps.size); \
    if (status == F_none) maps.size = 0;

  #define f_macro_string_maps_t_destroy(status, maps) \
    status = F_none; \
    maps.used = maps.size; \
    while (maps.used) { \
      maps.used--; \
      f_macro_string_map_t_destroy(status, maps.array[maps.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_destroy((void **) & maps.array, sizeof(f_string_map_t), maps.size); \
    if (status == F_none) maps.size = 0;

  #define f_macro_string_maps_t_delete_simple(maps) \
    maps.used = maps.size; \
    while (maps.used) { \
      maps.used--; \
      f_macro_string_map_t_delete_simple(maps.array[maps.used]); \
    } \
    f_memory_delete((void **) & maps.array, sizeof(f_string_map_t), maps.size); \
    maps.size = 0;

  #define f_macro_string_maps_t_destroy_simple(maps) \
    maps.used = maps.size; \
    while (maps.used) { \
      maps.used--; \
      f_macro_string_map_t_destroy_simple(maps.array[maps.used]); \
    } \
    f_memory_destroy((void **) & maps.array, sizeof(f_string_map_t), maps.size); \
    maps.size = 0;

  #define f_macro_string_maps_t_resize(status, maps, new_length) \
    status = F_none; \
    if (new_length < maps.size) { \
      for (f_array_length_t _macro__i = maps.size - new_length; _macro__i < maps.size; _macro__i++) { \
        f_macro_string_map_t_delete(status, maps.array[_macro__i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_resize((void **) & maps.array, sizeof(f_string_map_t), maps.size, new_length); \
    if (status == F_none) { \
      if (new_length > maps.size) { \
        for (f_array_length_t _macro__i = maps.size; _macro__i < new_length; _macro__i++) { \
          memset(&maps.array[_macro__i], 0, sizeof(f_string_map_t)); \
        } \
      } \
      maps.size = new_length; \
      if (maps.used > maps.size) maps.used = new_length; \
    }

  #define f_macro_string_maps_t_adjust(status, maps, new_length) \
    status = F_none; \
    if (new_length < maps.size) { \
      for (f_array_length_t _macro__i = maps.size - new_length; _macro__i < maps.size; _macro__i++) { \
        f_macro_string_map_t_destroy(status, maps.array[_macro__i], f_string_map_t); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_adjust((void **) & maps.array, sizeof(f_string_map_t), maps.size, new_length); \
    if (status == F_none) { \
      if (new_length > maps.size) { \
        for (f_array_length_t _macro__i = maps.size; _macro__i < new_length; _macro__i++) { \
          memset(&maps.array[_macro__i], 0, sizeof(f_string_map_t)); \
        } \
      } \
      maps.size = new_length; \
      if (maps.used > maps.size) maps.used = new_length; \
    }
#endif // _di_f_string_maps_t_

/**
 * A string map consisting of a name and multiple values.
 *
 * name: A string representing the map name.
 * value: An array of strings representing the map value.
 */
#ifndef _di_f_string_map_multi_t_
  typedef struct {
    f_string_dynamic_t name;
    f_string_dynamics_t value;
  } f_string_map_multi_t;

  #define f_string_map_multi_t_initialize { f_string_dynamic_t_initialize, f_string_dynamics_t_initialize }

  #define f_macro_string_map_multi_t_clear(map) \
    f_macro_string_dynamic_t_clear(map.name) \
    f_macro_string_dynamics_clear(map.value)

  #define f_macro_string_map_multi_t_delete(status, map) \
    f_macro_string_dynamic_t_delete(status, map.name) \
    if (status == F_none) { \
      f_macro_string_dynamics_t_delete(status, map.value) \
    }

  #define f_macro_string_map_multi_t_destroy(status, map) \
    f_macro_string_dynamic_t_destroy(status, map.name) \
    if (status == F_none) { \
      f_macro_string_dynamics_t_destroy(status, map.value) \
    }

  #define f_macro_string_map_multi_t_delete_simple(map) \
    f_macro_string_dynamic_t_delete_simple(map.name) \
    f_macro_string_dynamics_t_delete_simple(map.value)

  #define f_macro_string_map_multi_t_destroy_simple(map) \
    f_macro_string_dynamic_t_destroy_simple(map.name) \
    f_macro_string_dynamics_t_destroy_simple(map.value)
#endif // _di_f_string_map_multi_t_

/**
 * An array of string maps.
 *
 * array: the array of string maps.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_string_map_multis_t_
  typedef struct {
    f_string_map_multi_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_string_map_multis_t;

  #define f_string_map_multis_t_initialize f_string_statics_t_initialize

  #define f_macro_string_map_multis_t_clear(maps) f_macro_string_statics_t_clear(maps)

  #define f_macro_string_map_multis_t_new(status, maps, length) \
    f_macro_string_map_multis_t_clear(maps) \
    status = f_memory_new((void **) & maps.array, sizeof(f_string_map_multi_t), length); \
    if (status == F_none) { \
      maps.size = length; \
      maps.used = 0; \
    }

  #define f_macro_string_map_multis_t_delete(status, maps) \
    status = F_none; \
    maps.used = maps.size; \
    while (maps.used) { \
      maps.used--; \
      f_macro_string_map_multi_t_delete(status, maps.array[maps.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_delete((void **) & maps.array, sizeof(f_string_map_multi_t), maps.size); \
    if (status == F_none) maps.size = 0;

  #define f_macro_string_map_multis_t_destroy(status, maps) \
    status = F_none; \
    maps.used = maps.size; \
    while (maps.used) { \
      maps.used--; \
      f_macro_string_map_multi_t_destroy(status, maps.array[maps.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_destroy((void **) & maps.array, sizeof(f_string_map_multi_t), maps.size); \
    if (status == F_none) maps.size = 0;

  #define f_macro_string_map_multis_t_delete_simple(maps) \
    maps.used = maps.size; \
    while (maps.used) { \
      maps.used--; \
      f_macro_string_map_multi_t_delete_simple(maps.array[maps.used]); \
    } \
    f_memory_delete((void **) & maps.array, sizeof(f_string_map_multi_t), maps.size); \
    maps.size = 0;

  #define f_macro_string_map_multis_t_destroy_simple(maps) \
    maps.used = maps.size; \
    while (maps.used) { \
      maps.used--; \
      f_macro_string_map_multi_t_destroy_simple(maps.array[maps.used]); \
    } \
    f_memory_destroy((void **) & maps.array, sizeof(f_string_map_multi_t), maps.size); \
    maps.size = 0;

  #define f_macro_string_map_multis_t_resize(status, maps, new_length) \
    status = F_none; \
    if (new_length < maps.size) { \
      for (f_array_length_t _macro__i = maps.size - new_length; _macro__i < maps.size; _macro__i++) { \
        f_macro_string_map_multi_t_delete(status, maps.array[_macro__i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_resize((void **) & maps.array, sizeof(f_string_map_multi_t), maps.size, new_length); \
    if (status == F_none) { \
      if (new_length > maps.size) { \
        for (f_array_length_t _macro__i = maps.size; _macro__i < new_length; _macro__i++) { \
          memset(&maps.array[_macro__i], 0, sizeof(f_string_map_multi_t)); \
        } \
      } \
      maps.size = new_length; \
      if (maps.used > maps.size) maps.used = new_length; \
    }

  #define f_macro_string_map_multis_t_adjust(status, maps, new_length) \
    status = F_none; \
    if (new_length < maps.size) { \
      for (f_array_length_t _macro__i = maps.size - new_length; _macro__i < maps.size; _macro__i++) { \
        f_macro_string_map_multi_t_destroy(status, maps.array[_macro__i], f_string_map_multi_t); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_adjust((void **) & maps.array, sizeof(f_string_map_multi_t), maps.size, new_length); \
    if (status == F_none) { \
      if (new_length > maps.size) { \
        for (f_array_length_t _macro__i = maps.size; _macro__i < new_length; _macro__i++) { \
          memset(&maps.array[_macro__i], 0, sizeof(f_string_map_multi_t)); \
        } \
      } \
      maps.size = new_length; \
      if (maps.used > maps.size) maps.used = new_length; \
    }
#endif // _di_f_string_map_multis_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_map_h
