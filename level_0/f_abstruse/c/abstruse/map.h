/**
 * FLL - Level 0
 *
 * Project: Abstuse
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines abstruse map data.
 *
 * This is auto-included by abstruse.h and should not need to be explicitly included.
 */
#ifndef _F_type_abstruse_map_h
#define _F_type_abstruse_map_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A map of an abstruse as the value and a string as the key.
 *
 * properties:
 *   - key:   The string mapping the abstruse.
 *   - value: The abstruse being mapped by the key.
 */
#ifndef _di_f_abstruse_map_t_
  typedef struct {
    f_string_dynamic_t key;
    f_abstruse_t value;
  } f_abstruse_map_t;

  #define f_abstruse_map_t_initialize { f_string_dynamic_t_initialize, f_abstruse_t_initialize }

  #define macro_f_abstruse_map_t_initialize_1(key, value) { key, value }

  #define macro_f_abstruse_map_t_clear(map) \
    macro_f_string_dynamic_t_clear(map.key); \
    macro_f_abstruse_t_clear(map.value);
#endif // _di_f_abstruse_map_t_

/**
 * An array of f_abstruse_map_t.
 *
 * Properties:
 *   - array: The array of f_abstruse_map_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_abstruse_maps_t_
  typedef struct {
    f_abstruse_map_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_abstruse_maps_t;

  #define f_abstruse_maps_t_initialize { 0, 0, 0 }

  #define macro_f_abstruse_maps_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_abstruse_maps_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_abstruse_maps_t_

/**
 * This holds an array of f_abstruse_map_maps_t.
 *
 * Properties:
 *   - array: The array of f_abstruse_map_t arrays.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_abstruse_mapss_t_
  typedef struct {
    f_abstruse_maps_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_abstruse_mapss_t;

  #define f_abstruse_mapss_t_initialize { 0, 0, 0 }

  #define macro_f_abstruse_mapss_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_abstruse_mapss_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_abstruse_mapss_t_

/**
 * Delete the f_abstruse_map_t structure.
 *
 * This only de-allocates the following:
 *   - a_u8s
 *   - a_u16s
 *   - a_u32s
 *   - a_u64s
 *   - a_i8s
 *   - a_i16s
 *   - a_i32s
 *   - a_i64s
 *   - a_signeds
 *   - a_unsigneds
 *   - a_static (as an f_string_dynamic_t, if size > 0).
 *   - a_statics (as an f_string_dynamics_t, if size > 0).
 *   - a_map
 *   - a_maps
 *   - a_map_multi
 *   - a_map_multis
 *   - a_quantitys
 *   - a_ranges
 *   - a_triple
 *   - a_triples
 *
 * For all other types, the caller must handle de-allocation to avoid memory leaks.
 * Provide and use a custom callback if special handling of deallocation is needed.
 *
 * @param map
 *   The abstruse map to delete.
 *
 * @return
 *   F_okay on success, including when nothing done due to no match against the type.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *   Errors (with error bit) from: f_memory_arrays_resize().
 *
 * @see f_memory_array_resize()
 * @see f_memory_arrays_resize()
 */
#ifndef _di_f_abstruse_map_delete_
  extern f_status_t f_abstruse_map_delete(f_abstruse_map_t * const map);
#endif // _di_f_abstruse_map_delete_

/**
 * Destroy the f_abstruse_map_t structure.
 *
 * This only de-allocates the following:
 *   - a_u8s
 *   - a_u16s
 *   - a_u32s
 *   - a_u64s
 *   - a_i8s
 *   - a_i16s
 *   - a_i32s
 *   - a_i64s
 *   - a_signeds
 *   - a_unsigneds
 *   - a_static (as an f_string_dynamic_t, if size > 0).
 *   - a_statics (as an f_string_dynamics_t, if size > 0).
 *   - a_map
 *   - a_maps
 *   - a_map_multi
 *   - a_map_multis
 *   - a_quantitys
 *   - a_ranges
 *   - a_triple
 *   - a_triples
 *
 * For all other types, the caller must handle de-allocation to avoid memory leaks.
 * Provide and use a custom callback if special handling of deallocation is needed.
 *
 * @param map
 *   The abstruse map to destroy.
 *
 * @return
 *   F_okay on success, including when nothing done due to no match against the type.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *   Errors (with error bit) from: f_memory_arrays_adjust().
 *
 * @see f_memory_array_adjust()
 * @see f_memory_arrays_adjust()
 */
#ifndef _di_f_abstruse_map_destroy_
  extern f_status_t f_abstruse_map_destroy(f_abstruse_map_t * const map);
#endif // _di_f_abstruse_map_destroy_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_abstruse_maps_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success, including when nothing done due to no match against the type.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *   Errors (with error bit) from: f_memory_arrays_resize().
 *
 * @see f_memory_array_resize()
 * @see f_memory_arrays_resize()
 */
#ifndef _di_f_abstruse_maps_delete_callback_
  extern f_status_t f_abstruse_maps_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_abstruse_maps_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_abstruse_maps_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success, including when nothing done due to no match against the type.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *   Errors (with error bit) from: f_memory_arrays_adjust().
 *
 * @see f_memory_array_adjust()
 * @see f_memory_arrays_adjust()
 */
#ifndef _di_f_abstruse_maps_destroy_callback_
  extern f_status_t f_abstruse_maps_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_abstruse_maps_destroy_callback_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_abstruse_mapss_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *   Errors (with error bit) from: f_memory_arrays_resize().
 *
 * @see f_memory_array_resize()
 * @see f_memory_arrays_resize()
 */
#ifndef _di_f_abstruse_mapss_delete_callback_
  extern f_status_t f_abstruse_mapss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_abstruse_mapss_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_abstruse_mapss_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *   Errors (with error bit) from: f_memory_arrays_adjust().
 *
 * @see f_memory_array_adjust()
 * @see f_memory_arrays_adjust()
 */
#ifndef _di_f_abstruse_mapss_destroy_callback_
  extern f_status_t f_abstruse_mapss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_abstruse_mapss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_abstruse_map_h
