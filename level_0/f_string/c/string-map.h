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
#ifndef _di_f_string_map_
  typedef struct {
    f_string_dynamic name;
    f_string_dynamic value;
  } f_string_map;

  #define f_string_map_initialize { f_string_dynamic_initialize, f_string_dynamic_initialize }

  #define f_macro_string_map_clear(map) \
    map.array = 0; \
    map.size = 0; \
    map.used = 0;

  #define f_macro_string_map_delete(status, map) \
    f_macro_string_dynamic_delete(status, map.name) \
    if (status == F_none) { \
      f_macro_string_dynamic_delete(status, map.value) \
    }

  #define f_macro_string_map_destroy(status, map) \
    f_macro_string_dynamic_destroy(status, map.name) \
    if (status == F_none) { \
      f_macro_string_dynamic_destroy(status, map.value) \
    }

  #define f_macro_string_map_delete_simple(map) \
    f_macro_string_dynamic_delete_simple(map.name) \
    f_macro_string_dynamic_delete_simple(map.value)

  #define f_macro_string_map_destroy_simple(map) \
    f_macro_string_dynamic_destroy_simple(map.name) \
    f_macro_string_dynamic_destroy_simple(map.value)
#endif // _di_f_string_map_

/**
 * An array of string maps.
 *
 * array: the array of string maps.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_string_maps_
  typedef struct {
    f_string_map *array;

    f_array_length size;
    f_array_length used;
  } f_string_maps;

  #define f_string_maps_initialize f_string_statics_initialize

  #define f_macro_string_maps_clear(maps) \
    maps.array = 0; \
    maps.size = 0; \
    maps.used = 0;

  #define f_macro_string_maps_new(status, maps, length) \
    f_macro_string_maps_clear(maps) \
    status = f_memory_new((void **) & maps.array, sizeof(f_string_map), length); \
    if (status == F_none) { \
      maps.size = length; \
      maps.used = 0; \
    }

  #define f_macro_string_maps_delete(status, maps) \
    status = F_none; \
    maps.used = maps.size; \
    while (maps.used > 0) { \
      maps.used--; \
      f_macro_string_map_delete(status, maps.array[maps.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_delete((void **) & maps.array, sizeof(f_string_map), maps.size); \
    if (status == F_none) maps.size = 0;

  #define f_macro_string_maps_destroy(status, maps) \
    status = F_none; \
    maps.used = maps.size; \
    while (maps.used > 0) { \
      maps.used--; \
      f_macro_string_map_destroy(status, maps.array[maps.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_destroy((void **) & maps.array, sizeof(f_string_map), maps.size); \
    if (status == F_none) maps.size = 0;

  #define f_macro_string_maps_delete_simple(maps) \
    maps.used = maps.size; \
    while (maps.used > 0) { \
      maps.used--; \
      f_macro_string_map_delete_simple(maps.array[maps.used]); \
      if (maps.used == 0) { \
        if (f_memory_delete((void **) & maps.array, sizeof(f_string_map), maps.size)) { \
          maps.size = 0; \
        } \
      } \
    }

  #define f_macro_string_maps_destroy_simple(maps) \
    maps.used = maps.size; \
    while (maps.used > 0) { \
      maps.used--; \
      f_macro_string_map_destroy_simple(maps.array[maps.used]); \
      if (maps.used == 0) { \
        if (f_memory_destroy((void **) & maps.array, sizeof(f_string_map), maps.size)) { \
          maps.size = 0; \
        } \
      } \
    }

  #define f_macro_string_maps_resize(status, maps, new_length) \
    status = F_none; \
    if (new_length < maps.size) { \
      f_array_length i = maps.size - new_length; \
      for (; i < maps.size; i++) { \
        f_macro_string_map_delete(status, maps.array[i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_resize((void **) & maps.array, sizeof(f_string_map), maps.size, new_length); \
    if (status == F_none) { \
      if (new_length > maps.size) { \
        f_array_length i = maps.size; \
        for (; i < new_length; i++) { \
          memset(&maps.array[i], 0, sizeof(f_string_map)); \
        } \
      } \
      maps.size = new_length; \
      if (maps.used > maps.size) maps.used = new_length; \
    }

  #define f_macro_string_maps_adjust(status, maps, new_length) \
    status = F_none; \
    if (new_length < maps.size) { \
      f_array_length i = maps.size - new_length; \
      for (; i < maps.size; i++) { \
        f_macro_string_map_destroy(status, maps.array[i], f_string_map); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_adjust((void **) & maps.array, sizeof(f_string_map), maps.size, new_length); \
    if (status == F_none) { \
      if (new_length > maps.size) { \
        f_array_length i = maps.size; \
        for (; i < new_length; i++) { \
          memset(&maps.array[i], 0, sizeof(f_string_map)); \
        } \
      } \
      maps.size = new_length; \
      if (maps.used > maps.size) maps.used = new_length; \
    }
#endif // _di_f_string_maps_

/**
 * A string map consisting of a name and multiple values.
 *
 * name: A string representing the map name.
 * value: An array of strings representing the map value.
 */
#ifndef _di_f_string_map_multi_
  typedef struct {
    f_string_dynamic name;
    f_string_dynamics value;
  } f_string_map_multi;

  #define f_string_map_multi_initialize { f_string_dynamic_initialize, f_string_dynamics_initialize }

  #define f_macro_string_map_multi_clear(map) \
    f_macro_string_dynamic_clear(map.name) \
    f_macro_string_dynamics_clear(map.value)

  #define f_macro_string_map_multi_delete(status, map) \
    f_macro_string_dynamic_delete(status, map.name) \
    if (status == F_none) { \
      f_macro_string_dynamics_delete(status, map.value) \
    }

  #define f_macro_string_map_multi_destroy(status, map) \
    f_macro_string_dynamic_destroy(status, map.name) \
    if (status == F_none) { \
      f_macro_string_dynamics_destroy(status, map.value) \
    }

  #define f_macro_string_map_multi_delete_simple(map) \
    f_macro_string_dynamic_delete_simple(map.name) \
    f_macro_string_dynamics_delete_simple(map.value)

  #define f_macro_string_map_multi_destroy_simple(map) \
    f_macro_string_dynamic_destroy_simple(map.name) \
    f_macro_string_dynamics_destroy_simple(map.value)
#endif // _di_f_string_map_multi_

/**
 * An array of string maps.
 *
 * array: the array of string maps.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_string_map_multis_
  typedef struct {
    f_string_map_multi *array;

    f_array_length size;
    f_array_length used;
  } f_string_map_multis;

  #define f_string_map_multis_initialize f_string_statics_initialize

  #define f_macro_string_map_multis_clear(maps) f_macro_string_statics_clear(maps)

  #define f_macro_string_map_multis_new(status, maps, length) \
    f_macro_string_map_multis_clear(maps) \
    status = f_memory_new((void **) & maps.array, sizeof(f_string_map_multi), length); \
    if (status == F_none) { \
      maps.size = length; \
      maps.used = 0; \
    }

  #define f_macro_string_map_multis_delete(status, maps) \
    status = F_none; \
    maps.used = maps.size; \
    while (maps.used > 0) { \
      maps.used--; \
      f_macro_string_map_multi_delete(status, maps.array[maps.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_delete((void **) & maps.array, sizeof(f_string_map_multi), maps.size); \
    if (status == F_none) maps.size = 0;

  #define f_macro_string_map_multis_destroy(status, maps) \
    status = F_none; \
    maps.used = maps.size; \
    while (maps.used > 0) { \
      maps.used--; \
      f_macro_string_map_multi_destroy(status, maps.array[maps.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_destroy((void **) & maps.array, sizeof(f_string_map_multi), maps.size); \
    if (status == F_none) maps.size = 0;

  #define f_macro_string_map_multis_delete_simple(maps) \
    maps.used = maps.size; \
    while (maps.used > 0) { \
      maps.used--; \
      f_macro_string_map_multi_delete_simple(maps.array[maps.used]); \
      if (maps.used == 0) { \
        if (f_memory_delete((void **) & maps.array, sizeof(f_string_map_multi), maps.size)) { \
          maps.size = 0; \
        } \
      } \
    }

  #define f_macro_string_map_multis_destroy_simple(maps) \
    maps.used = maps.size; \
    while (maps.used > 0) { \
      maps.used--; \
      f_macro_string_map_multi_destroy_simple(maps.array[maps.used]); \
      if (maps.used == 0) { \
        if (f_memory_destroy((void **) & maps.array, sizeof(f_string_map_multi), maps.size)) { \
          maps.size = 0; \
        } \
      } \
    }

  #define f_macro_string_map_multis_resize(status, maps, new_length) \
    status = F_none; \
    if (new_length < maps.size) { \
      f_array_length i = maps.size - new_length; \
      for (; i < maps.size; i++) { \
        f_macro_string_map_multi_delete(status, maps.array[i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_resize((void **) & maps.array, sizeof(f_string_map_multi), maps.size, new_length); \
    if (status == F_none) { \
      if (new_length > maps.size) { \
        f_array_length i = maps.size; \
        for (; i < new_length; i++) { \
          memset(&maps.array[i], 0, sizeof(f_string_map_multi)); \
        } \
      } \
      maps.size = new_length; \
      if (maps.used > maps.size) maps.used = new_length; \
    }

  #define f_macro_string_map_multis_adjust(status, maps, new_length) \
    status = F_none; \
    if (new_length < maps.size) { \
      f_array_length i = maps.size - new_length; \
      for (; i < maps.size; i++) { \
        f_macro_string_map_multi_destroy(status, maps.array[i], f_string_map_multi); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_adjust((void **) & maps.array, sizeof(f_string_map_multi), maps.size, new_length); \
    if (status == F_none) { \
      if (new_length > maps.size) { \
        f_array_length i = maps.size; \
        for (; i < new_length; i++) { \
          memset(&maps.array[i], 0, sizeof(f_string_map_multi)); \
        } \
      } \
      maps.size = new_length; \
      if (maps.used > maps.size) maps.used = new_length; \
    }
#endif // _di_f_string_map_multis_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_map_h
