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
    map.name.array = 0; \
    map.name.size = 0; \
    map.name.used = 0; \
    map.value.array = 0; \
    map.value.size = 0; \
    map.value.used = 0;

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

  #define f_macro_string_maps_t_resize(status, maps, length) \
    status = F_none; \
    if (length < maps.size) { \
      for (register f_array_length_t _macro__i = maps.size - length; _macro__i < maps.size; ++_macro__i) { \
        f_macro_string_map_t_delete(status, maps.array[_macro__i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_resize((void **) & maps.array, sizeof(f_string_map_t), maps.size, length); \
    if (status == F_none) { \
      maps.size = length; \
      if (maps.used > maps.size) maps.used = length; \
    }

  #define f_macro_string_maps_t_adjust(status, maps, length) \
    status = F_none; \
    if (length < maps.size) { \
      for (register f_array_length_t _macro__i = maps.size - length; _macro__i < maps.size; ++_macro__i) { \
        f_macro_string_map_t_destroy(status, maps.array[_macro__i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_adjust((void **) & maps.array, sizeof(f_string_map_t), maps.size, length); \
    if (status == F_none) { \
      maps.size = length; \
      if (maps.used > maps.size) maps.used = length; \
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
#endif // _di_f_string_maps_t_

// @todo increase, decrease, decimate, increase_by, decrease_by, decimate_by

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
    f_macro_string_dynamics_t_clear(map.value)

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

  #define f_macro_string_map_multis_t_resize(status, maps, length) \
    status = F_none; \
    if (length < maps.size) { \
      for (register f_array_length_t _macro__i = maps.size - length; _macro__i < maps.size; ++_macro__i) { \
        f_macro_string_map_multi_t_delete(status, maps.array[_macro__i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_resize((void **) & maps.array, sizeof(f_string_map_multi_t), maps.size, length); \
    if (status == F_none) { \
      maps.size = length; \
      if (maps.used > maps.size) maps.used = length; \
    }

  #define f_macro_string_map_multis_t_adjust(status, maps, length) \
    status = F_none; \
    if (length < maps.size) { \
      for (register f_array_length_t _macro__i = maps.size - length; _macro__i < maps.size; ++_macro__i) { \
        f_macro_string_map_multi_t_destroy(status, maps.array[_macro__i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_adjust((void **) & maps.array, sizeof(f_string_map_multi_t), maps.size, length); \
    if (status == F_none) { \
      maps.size = length; \
      if (maps.used > maps.size) maps.used = length; \
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
#endif // _di_f_string_map_multis_t_

// @todo increase, decrease, decimate, increase_by, decrease_by, decimate_by

/**
 * Resize the string maps array.
 *
 * @param length
 *   The new size to use.
 * @param maps
 *   The string maps array to resize.
 *
 * @return
 *   F_none on success.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_maps_adjust_
  extern f_status_t f_string_maps_adjust(const f_array_length_t length, f_string_maps_t *maps);
#endif // _di_f_string_maps_adjust_

/**
 * Resize the string maps array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param maps
 *   The string maps array to resize.
 *
 * @return
 *   F_none on success.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_maps_decimate_by_
  extern f_status_t f_string_maps_decimate_by(const f_array_length_t amount, f_string_maps_t *maps);
#endif // _di_f_string_maps_decimate_by_

/**
 * Resize the string maps array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param maps
 *   The string maps array to resize.
 *
 * @return
 *   F_none on success.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_maps_decrease_by_
  extern f_status_t f_string_maps_decrease_by(const f_array_length_t amount, f_string_maps_t *maps);
#endif // _di_f_string_maps_decrease_by_

/**
 * Delete the array of string maps.
 *
 * @param maps
 *   The maps to delete.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_maps_delete_
  extern f_status_t f_string_maps_delete(f_string_maps_t *maps);
#endif // _di_f_string_maps_delete_

/**
 * Delete the array of string maps.
 *
 * @param maps
 *   The maps to destroy.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_maps_destroy_
  extern f_status_t f_string_maps_destroy(f_string_maps_t *maps);
#endif // _di_f_string_maps_destroy_

/**
 * Increase the size of the string maps array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param maps
 *   The string maps array to resize.
 *
 * @return
 *   F_none on success.
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_maps_increase_
  extern f_status_t f_string_maps_increase(f_string_maps_t *maps);
#endif // _di_f_string_maps_increase_

/**
 * Resize the string maps array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param maps
 *   The string maps array to resize.
 *
 * @return
 *   F_none on success.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
 */
#ifndef _di_f_string_maps_increase_by_
  extern f_status_t f_string_maps_increase_by(const f_array_length_t amount, f_string_maps_t *maps);
#endif // _di_f_string_maps_increase_by_

/**
 * Resize the string maps array.
 *
 * @param length
 *   The new size to use.
 * @param maps
 *   The string maps array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_maps_adjust_
  extern f_status_t f_string_maps_adjust(const f_array_length_t length, f_string_maps_t *maps);
#endif // _di_f_string_maps_adjust_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_map_h
