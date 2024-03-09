/**
 * FLL - Level 0
 *
 * Project: Abstuse
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines abstruse data.
 *
 * This is auto-included by abstruse.h and should not need to be explicitly included.
 */
#ifndef _F_type_abstruse_abstruse_h
#define _F_type_abstruse_abstruse_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * An abstruse a structure that represents different possible types.
 *
 * The type variable is used to designate the type within the f_abstruse_type_t union in use.
 *
 * De-allocation must be performed when swapping between types when the old type contains dynamically allocated data.
 *
 * It may be a good idea to use statically allocated data or dynamically allocated data managed elsewhere with this to avoid potential design complications with de-allocation.
 *
 * properties:
 *   - type: The type in which the "is" property is, represented by f_abstruse_type_e.
 *   - is:   The value, where "is" is chosen as a variable name so that when type is f_abstruse_type_unsigned_e, then accessing this would be done via "is.a_unsigned".
 */
#ifndef _di_f_abstruse_t_
  typedef struct {
    uint8_t type;

    f_abstruse_type_t is;
  } f_abstruse_t;

  #define f_abstruse_t_initialize { 0, f_abstruse_type_t_initialize }

  #define macro_f_abstruse_t_initialize_1(type, is) { type, is }
  #define macro_f_abstruse_t_initialize_2(type) { type, f_abstruse_type_t_initialize }

  #define macro_f_abstruse_t_clear(abstruse) \
    abstruse.type = 0; \
    macro_f_abstruse_type_t_clear(abstruse.is);
#endif // _di_f_abstruse_t_

/**
 * An array of f_abstruse_t.
 *
 * Properties:
 *   - array: The array of f_abstruse_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_abstruses_t_
  typedef struct {
    f_abstruse_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_abstruses_t;

  #define f_abstruses_t_initialize { 0, 0, 0 }

  #define macro_f_abstruses_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_abstruses_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_abstruses_t_

/**
 * This holds an array of f_abstruses_t.
 *
 * Properties:
 *   - array: The array of f_abstruse_t arrays.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_abstrusess_t_
  typedef struct {
    f_abstruses_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_abstrusess_t;

  #define f_abstrusess_t_initialize { 0, 0, 0 }

  #define macro_f_abstrusess_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_abstrusess_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_abstrusess_t_

/**
 * Delete the f_abstruse_t structure.
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
 * @param abstruse
 *   The abstruse to delete.
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
#ifndef _di_f_abstruse_delete_
  extern f_status_t f_abstruse_delete(f_abstruse_t * const abstruse);
#endif // _di_f_abstruse_delete_

/**
 * Destroy the f_abstruse_t structure.
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
 * @param abstruse
 *   The abstruse to destroy.
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
#ifndef _di_f_abstruse_destroy_
  extern f_status_t f_abstruse_destroy(f_abstruse_t * const abstruse);
#endif // _di_f_abstruse_destroy_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_abstruses_t structure.
 *
 * This callback only de-allocates the following:
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
#ifndef _di_f_abstruses_delete_callback_
  extern f_status_t f_abstruses_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_abstruses_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_abstruses_t structure.
 *
 * This callback only de-allocates the following:
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
#ifndef _di_f_abstruses_destroy_callback_
  extern f_status_t f_abstruses_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_abstruses_destroy_callback_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_abstrusess_t structure.
 *
 * This callback only de-allocates the following:
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
#ifndef _di_f_abstrusess_delete_callback_
  extern f_status_t f_abstrusess_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_abstrusess_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_abstrusess_t structure.
 *
 * This callback only de-allocates the following:
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
#ifndef _di_f_abstrusess_destroy_callback_
  extern f_status_t f_abstrusess_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_abstrusess_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_abstruse_abstruse_h
