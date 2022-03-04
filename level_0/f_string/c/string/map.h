/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
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

  #define macro_f_string_map_t_initialize(name, value) { name, value }

  #define macro_f_string_map_t_clear(map) \
    macro_f_string_dynamic_t_clear(map.name) \
    macro_f_string_dynamic_t_clear(map.value)

  #define macro_f_string_map_t_delete_simple(map) \
    macro_f_string_dynamic_t_delete_simple(map.name) \
    macro_f_string_dynamic_t_delete_simple(map.value)

  #define macro_f_string_map_t_destroy_simple(map) \
    macro_f_string_dynamic_t_destroy_simple(map.name) \
    macro_f_string_dynamic_t_destroy_simple(map.value)
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

  #define macro_f_string_maps_t_initialize(array, size, used) { array, size, used }
  #define macro_f_string_maps_t_initialize2(array, length) { array, length, length }

  #define macro_f_string_maps_t_clear(maps) macro_f_memory_structure_clear(maps)

  #define macro_f_string_maps_t_resize(status, maps, length) status = f_string_maps_resize(length, &maps);
  #define macro_f_string_maps_t_adjust(status, maps, length) status = f_string_maps_adjust(length, &maps);

  #define macro_f_string_maps_t_delete_simple(maps)  f_string_maps_resize(0, &maps);
  #define macro_f_string_maps_t_destroy_simple(maps) f_string_maps_adjust(0, &maps);

  #define macro_f_string_maps_t_increase(status, step, maps)      status = f_string_maps_increase(step, maps);
  #define macro_f_string_maps_t_increase_by(status, maps, amount) status = f_string_maps_increase_by(amount, maps);
  #define macro_f_string_maps_t_decrease_by(status, maps, amount) status = f_string_maps_decrease_by(amount, maps);
  #define macro_f_string_maps_t_decimate_by(status, maps, amount) status = f_string_maps_decimate_by(amount, maps);
#endif // _di_f_string_maps_t_

/**
 * An array of string maps.
 *
 * array: the array of an array of string maps.
 * size:  total amount of allocated space.
 * used:  total number of allocated spaces used.
 */
#ifndef _di_f_string_mapss_t_
  typedef struct {
    f_string_maps_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_string_mapss_t;

  #define f_string_mapss_t_initialize f_string_statics_t_initialize

  #define macro_f_string_mapss_t_initialize(array, size, used) { array, size, used }
  #define macro_f_string_mapss_t_initialize2(array, length) { array, length, length }

  #define macro_f_string_mapss_t_clear(maps) macro_f_memory_structure_clear(maps)

  #define macro_f_string_mapss_t_resize(status, maps, length) status = f_string_mapss_resize(length, &maps);
  #define macro_f_string_mapss_t_adjust(status, maps, length) status = f_string_mapss_adjust(length, &maps);

  #define macro_f_string_mapss_t_delete_simple(maps)  f_string_mapss_resize(0, &maps);
  #define macro_f_string_mapss_t_destroy_simple(maps) f_string_mapss_adjust(0, &maps);

  #define macro_f_string_mapss_t_increase(status, step, maps)      status = f_string_mapss_increase(step, maps);
  #define macro_f_string_mapss_t_increase_by(status, maps, amount) status = f_string_mapss_increase_by(amount, maps);
  #define macro_f_string_mapss_t_decrease_by(status, maps, amount) status = f_string_mapss_decrease_by(amount, maps);
  #define macro_f_string_mapss_t_decimate_by(status, maps, amount) status = f_string_mapss_decimate_by(amount, maps);
#endif // _di_f_string_mapss_t_

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

  #define macro_f_string_map_t_initialize(name, value) { name, value }

  #define macro_f_string_map_multi_t_clear(map) \
    macro_f_string_dynamic_t_clear(map.name) \
    macro_f_string_dynamics_t_clear(map.value)

  #define macro_f_string_map_multi_t_delete_simple(map) \
    macro_f_string_dynamic_t_delete_simple(map.name) \
    macro_f_string_dynamics_t_delete_simple(map.value)

  #define macro_f_string_map_multi_t_destroy_simple(map) \
    macro_f_string_dynamic_t_destroy_simple(map.name) \
    macro_f_string_dynamics_t_destroy_simple(map.value)
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

  #define macro_f_string_map_multis_t_initialize(array, size, used) { array, size, used }
  #define macro_f_string_map_multis_t_initialize2(array, length) { array, length, length }

  #define macro_f_string_map_multis_t_clear(map_multis) macro_f_memory_structure_clear(map_multis)

  #define macro_f_string_map_multis_t_resize(status, map_multis, length) status = f_string_map_multis_resize(length, &map_multis);
  #define macro_f_string_map_multis_t_adjust(status, map_multis, length) status = f_string_map_multis_adjust(length, &map_multis);

  #define macro_f_string_map_multis_t_delete_simple(map_multis)  f_string_map_multis_resize(0, &map_multis);
  #define macro_f_string_map_multis_t_destroy_simple(map_multis) f_string_map_multis_adjust(0, &map_multis);

  #define macro_f_string_map_multis_t_increase(status, step, map_multis)      status = f_string_map_multis_increase(step, &map_multis);
  #define macro_f_string_map_multis_t_increase_by(status, map_multis, amount) status = f_string_map_multis_increase_by(amount, &map_multis);
  #define macro_f_string_map_multis_t_decrease_by(status, map_multis, amount) status = f_string_map_multis_decrease_by(amount, &map_multis);
  #define macro_f_string_map_multis_t_decimate_by(status, map_multis, amount) status = f_string_map_multis_decimate_by(amount, &map_multis);
#endif // _di_f_string_map_multis_t_

/**
 * An array of string maps.
 *
 * array: the array of an array of string maps.
 * size:  total amount of allocated space.
 * used:  total number of allocated spaces used.
 */
#ifndef _di_f_string_map_multiss_t_
  typedef struct {
    f_string_map_multis_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_string_map_multiss_t;

  #define f_string_map_multiss_t_initialize f_string_statics_t_initialize

  #define macro_f_string_map_multiss_t_initialize(array, size, used) { array, size, used }
  #define macro_f_string_map_multiss_t_initialize2(array, length) { array, length, length }

  #define macro_f_string_map_multiss_t_clear(map_multis) macro_f_memory_structure_clear(map_multis)

  #define macro_f_string_map_multiss_t_resize(status, map_multis, length) status = f_string_map_multiss_resize(length, &map_multis);
  #define macro_f_string_map_multiss_t_adjust(status, map_multis, length) status = f_string_map_multiss_adjust(length, &map_multis);

  #define macro_f_string_map_multiss_t_delete_simple(map_multis)  f_string_map_multiss_resize(0, &map_multis);
  #define macro_f_string_map_multiss_t_destroy_simple(map_multis) f_string_map_multiss_adjust(0, &map_multis);

  #define macro_f_string_map_multiss_t_increase(status, step, map_multis)      status = f_string_map_multiss_increase(step, &map_multis);
  #define macro_f_string_map_multiss_t_increase_by(status, map_multis, amount) status = f_string_map_multiss_increase_by(amount, &map_multis);
  #define macro_f_string_map_multiss_t_decrease_by(status, map_multis, amount) status = f_string_map_multiss_decrease_by(amount, &map_multis);
  #define macro_f_string_map_multiss_t_decimate_by(status, map_multis, amount) status = f_string_map_multiss_decimate_by(amount, &map_multis);
#endif // _di_f_string_map_multiss_t_

/**
 * Resize the map_multis array.
 *
 * @param length
 *   The new size to use.
 * @param map_multis
 *   The map_multis array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_map_multis_adjust_
  extern f_status_t f_string_map_multis_adjust(const f_array_length_t length, f_string_map_multis_t * const map_multis);
#endif // _di_f_string_map_multis_adjust_

/**
 * Append a single source map_multi onto the destination.
 *
 * @param source
 *   The source maps to append.
 * @param destination
 *   The destination maps the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_map_multis_append_
  f_status_t f_string_map_multis_append(const f_string_map_multi_t source, f_string_map_multis_t *destination);
#endif // _di_f_string_map_multis_append_

/**
 * Append the source map_multis onto the destination.
 *
 * @param source
 *   The source maps to append.
 * @param destination
 *   The destination maps the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_map_multis_append_all_
  f_status_t f_string_map_multis_append_all(const f_string_map_multis_t source, f_string_map_multis_t *destination);
#endif // _di_f_string_map_multis_append_all_

/**
 * Resize the map_multis array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param map_multis
 *   The map_multis array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_map_multis_decimate_by_
  extern f_status_t f_string_map_multis_decimate_by(const f_array_length_t amount, f_string_map_multis_t * const map_multis);
#endif // _di_f_string_map_multis_decimate_by_

/**
 * Resize the map_multis array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param map_multis
 *   The map_multis array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_map_multis_decrease_by_
  extern f_status_t f_string_map_multis_decrease_by(const f_array_length_t amount, f_string_map_multis_t * const map_multis);
#endif // _di_f_string_map_multis_decrease_by_

/**
 * Increase the size of the map_multis array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param map_multis
 *   The map_multis array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_map_multis_increase_
  extern f_status_t f_string_map_multis_increase(const f_array_length_t step, f_string_map_multis_t * const map_multis);
#endif // _di_f_string_map_multis_increase_

/**
 * Resize the map_multis array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param map_multis
 *   The map_multis array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_map_multis_increase_by_
  extern f_status_t f_string_map_multis_increase_by(const f_array_length_t amount, f_string_map_multis_t * const map_multis);
#endif // _di_f_string_map_multis_increase_by_

/**
 * Resize the map_multis array.
 *
 * @param length
 *   The new size to use.
 * @param map_multis
 *   The map_multis array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_map_multis_resize_
  extern f_status_t f_string_map_multis_resize(const f_array_length_t length, f_string_map_multis_t * const map_multis);
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
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_maps_adjust_
  extern f_status_t f_string_maps_adjust(const f_array_length_t length, f_string_maps_t * const maps);
#endif // _di_f_string_maps_adjust_

/**
 * Append a single source map onto the destination.
 *
 * @param source
 *   The source maps to append.
 * @param destination
 *   The destination maps the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_maps_append_
  extern f_status_t f_string_maps_append(const f_string_map_t source, f_string_maps_t * const destination);
#endif // _di_f_string_maps_append_

/**
 * Append the source maps onto the destination.
 *
 * @param source
 *   The source maps to append.
 * @param destination
 *   The destination maps the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_maps_append_all_
  extern f_status_t f_string_maps_append_all(const f_string_maps_t source, f_string_maps_t * const destination);
#endif // _di_f_string_maps_append_all_

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
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_maps_decimate_by_
  extern f_status_t f_string_maps_decimate_by(const f_array_length_t amount, f_string_maps_t * const maps);
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
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_maps_decrease_by_
  extern f_status_t f_string_maps_decrease_by(const f_array_length_t amount, f_string_maps_t * const maps);
#endif // _di_f_string_maps_decrease_by_

/**
 * Increase the size of the string maps array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param maps
 *   The string maps array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_maps_increase_
  extern f_status_t f_string_maps_increase(const f_array_length_t step, f_string_maps_t * const maps);
#endif // _di_f_string_maps_increase_

/**
 * Resize the string maps array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
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
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_maps_increase_by_
  extern f_status_t f_string_maps_increase_by(const f_array_length_t amount, f_string_maps_t * const maps);
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
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_maps_resize_
  extern f_status_t f_string_maps_resize(const f_array_length_t length, f_string_maps_t * const maps);
#endif // _di_f_string_maps_resize_

/**
 * Resize the string mapss array.
 *
 * @param length
 *   The new size to use.
 * @param mapss
 *   The string mapss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_mapss_adjust_
  extern f_status_t f_string_mapss_adjust(const f_array_length_t length, f_string_mapss_t * const mapss);
#endif // _di_f_string_mapss_adjust_

/**
 * Append a single source maps onto the destination.
 *
 * @param source
 *   The source mapss to append.
 * @param destination
 *   The destination mapss the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_mapss_append_
  extern f_status_t f_string_mapss_append(const f_string_maps_t source, f_string_mapss_t * const destination);
#endif // _di_f_string_mapss_append_

/**
 * Append the source mapss onto the destination.
 *
 * @param source
 *   The source mapss to append.
 * @param destination
 *   The destination mapss the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_mapss_append_all_
  extern f_status_t f_string_mapss_append_all(const f_string_mapss_t source, f_string_mapss_t * const destination);
#endif // _di_f_string_mapss_append_all_

/**
 * Resize the string mapss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param mapss
 *   The string mapss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_mapss_decimate_by_
  extern f_status_t f_string_mapss_decimate_by(const f_array_length_t amount, f_string_mapss_t * const mapss);
#endif // _di_f_string_mapss_decimate_by_

/**
 * Resize the string mapss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param mapss
 *   The string mapss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_mapss_decrease_by_
  extern f_status_t f_string_mapss_decrease_by(const f_array_length_t amount, f_string_mapss_t * const mapss);
#endif // _di_f_string_mapss_decrease_by_

/**
 * Increase the size of the string mapss array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param mapss
 *   The string mapss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size) (or step is 0).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_mapss_increase_
  extern f_status_t f_string_mapss_increase(const f_array_length_t step, f_string_mapss_t * const mapss);
#endif // _di_f_string_mapss_increase_

/**
 * Resize the string mapss array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param mapss
 *   The string mapss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_mapss_increase_by_
  extern f_status_t f_string_mapss_increase_by(const f_array_length_t amount, f_string_mapss_t * const mapss);
#endif // _di_f_string_mapss_increase_by_

/**
 * Resize the string mapss array.
 *
 * @param length
 *   The new size to use.
 * @param mapss
 *   The string mapss array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_mapss_resize_
  extern f_status_t f_string_mapss_resize(const f_array_length_t length, f_string_mapss_t * const mapss);
#endif // _di_f_string_mapss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_map_h
