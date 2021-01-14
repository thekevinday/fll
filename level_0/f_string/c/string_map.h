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
 * name:  A string representing the map name.
 * value: A string representing the map value.
 */
#ifndef _di_f_string_map_t_
  typedef struct {
    f_string_dynamic_t name;
    f_string_dynamic_t value;
  } f_string_map_t;

  #define f_string_map_t_initialize { f_string_dynamic_t_initialize, f_string_dynamic_t_initialize }

  #define f_macro_string_map_t_clear(map) \
    f_macro_string_dynamic_t_clear(map.name) \
    f_macro_string_dynamic_t_clear(map.value)

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
 * size:  total amount of allocated space.
 * used:  total number of allocated spaces used.
 */
#ifndef _di_f_string_maps_t_
  typedef struct {
    f_string_map_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_string_maps_t;

  #define f_string_maps_t_initialize f_string_statics_t_initialize

  #define f_macro_string_maps_t_clear(maps) f_macro_memory_structure_clear(maps)

  #define f_macro_string_maps_t_resize(status, maps, length) status = f_string_maps_resize(length, &maps);
  #define f_macro_string_maps_t_adjust(status, maps, length) status = f_string_maps_adjust(length, &maps);

  #define f_macro_string_maps_t_delete_simple(maps)  f_string_maps_resize(0, &maps);
  #define f_macro_string_maps_t_destroy_simple(maps) f_string_maps_adjust(0, &maps);

  #define f_macro_string_maps_t_increase(status, maps)            status = f_string_maps_increase(maps);
  #define f_macro_string_maps_t_increase_by(status, maps, amount) status = f_string_maps_increase_by(amount, maps);
  #define f_macro_string_maps_t_decrease_by(status, maps, amount) status = f_string_maps_decrease_by(amount, maps);
  #define f_macro_string_maps_t_decimate_by(status, maps, amount) status = f_string_maps_decimate_by(amount, maps);
#endif // _di_f_string_maps_t_

/**
 * A string map consisting of a name and multiple values.
 *
 * name:  A string representing the map name.
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
 * size:  total amount of allocated space.
 * used:  total number of allocated spaces used.
 */
#ifndef _di_f_string_map_multis_t_
  typedef struct {
    f_string_map_multi_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_string_map_multis_t;

  #define f_string_map_multis_t_initialize f_string_statics_t_initialize

  #define f_macro_string_map_multis_t_clear(map_multis) f_macro_memory_structure_clear(map_multis)

  #define f_macro_string_map_multis_t_resize(status, map_multis, length) status = f_string_map_multis_resize(length, &map_multis);
  #define f_macro_string_map_multis_t_adjust(status, map_multis, length) status = f_string_map_multis_adjust(length, &map_multis);

  #define f_macro_string_map_multis_t_delete_simple(map_multis)  f_string_map_multis_resize(0, &map_multis);
  #define f_macro_string_map_multis_t_destroy_simple(map_multis) f_string_map_multis_adjust(0, &map_multis);

  #define f_macro_string_map_multis_t_increase(status, map_multis)            status = f_string_map_multis_increase(&map_multis);
  #define f_macro_string_map_multis_t_increase_by(status, map_multis, amount) status = f_string_map_multis_increase_by(amount, &map_multis);
  #define f_macro_string_map_multis_t_decrease_by(status, map_multis, amount) status = f_string_map_multis_decrease_by(amount, &map_multis);
  #define f_macro_string_map_multis_t_decimate_by(status, map_multis, amount) status = f_string_map_multis_decimate_by(amount, &map_multis);
#endif // _di_f_string_map_multis_t_

/**
 * Resize the string map_multis array.
 *
 * @param length
 *   The new size to use.
 * @param map_multis
 *   The string map_multis array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_map_multis_adjust_
  extern f_status_t f_string_map_multis_adjust(const f_array_length_t length, f_string_map_multis_t *map_multis);
#endif // _di_f_string_map_multis_adjust_

/**
 * Resize the string map_multis array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param map_multis
 *   The string map_multis array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_map_multis_decimate_by_
  extern f_status_t f_string_map_multis_decimate_by(const f_array_length_t amount, f_string_map_multis_t *map_multis);
#endif // _di_f_string_map_multis_decimate_by_

/**
 * Resize the string map_multis array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param map_multis
 *   The string map_multis array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_map_multis_decrease_by_
  extern f_status_t f_string_map_multis_decrease_by(const f_array_length_t amount, f_string_map_multis_t *map_multis);
#endif // _di_f_string_map_multis_decrease_by_

/**
 * Increase the size of the string map_multis array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param map_multis
 *   The string map_multis array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_map_multis_increase_
  extern f_status_t f_string_map_multis_increase(f_string_map_multis_t *map_multis);
#endif // _di_f_string_map_multis_increase_

/**
 * Resize the string map_multis array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param map_multis
 *   The string map_multis array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
 */
#ifndef _di_f_string_map_multis_increase_by_
  extern f_status_t f_string_map_multis_increase_by(const f_array_length_t amount, f_string_map_multis_t *map_multis);
#endif // _di_f_string_map_multis_increase_by_

/**
 * Resize the string map_multis array.
 *
 * @param length
 *   The new size to use.
 * @param map_multis
 *   The string map_multis array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_map_multis_resize_
  extern f_status_t f_string_map_multis_resize(const f_array_length_t length, f_string_map_multis_t *map_multis);
#endif // _di_f_string_map_multis_resize_

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
 *
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
 *
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
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_maps_decrease_by_
  extern f_status_t f_string_maps_decrease_by(const f_array_length_t amount, f_string_maps_t *maps);
#endif // _di_f_string_maps_decrease_by_

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
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
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
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
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
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_maps_resize_
  extern f_status_t f_string_maps_resize(const f_array_length_t length, f_string_maps_t *maps);
#endif // _di_f_string_maps_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_map_h
