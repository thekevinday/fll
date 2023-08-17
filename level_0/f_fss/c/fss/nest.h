/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines nest data to be used for/by project fss.
 *
 * This is auto-included by fss.h and should not need to be explicitly included.
 */
#ifndef _F_fss_nest_h
#define _F_fss_nest_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This holds an array of f_fss_items_t.
 *
 * Each array row represents the nesting depth.
 * The top-level will not have any parent, so "parent" must be ignored on anything at index 0.
 * The parent identifier is expected to reference a position in the nesting depth immediately above it.
 *
 * Properties:
 *   - depth: An array of f_fss_items_t, with each index representing the depth.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fss_nest_t_
  typedef struct {
    f_fss_items_t *depth;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_fss_nest_t;

  #define f_fss_nest_t_initialize { 0, 0, 0 }

  #define macro_f_fss_nest_t_initialize_1(depth, size, used) { depth, size, used }
  #define macro_f_fss_nest_t_initialize_2(depth, length)     { depth, length, length }

  #define macro_f_fss_nest_t_clear(nest) macro_f_memory_structures_clear(nest)
#endif // _di_f_fss_nest_t_

/**
 * This holds an array of f_fss_nest_t.
 *
 * Properties:
 *   - array: An array of f_fss_nest_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fss_nests_t_
  typedef struct {
    f_fss_nest_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_fss_nests_t;

  #define f_fss_nests_t_initialize { 0, 0, 0 }

  #define macro_f_fss_nests_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_fss_nests_t_initialize_2(array, length)     { array, length, length }

  #define macro_f_fss_nests_t_clear(nests) macro_f_memory_structures_clear(nests)
#endif // _di_f_fss_nests_t_

/**
 * This holds an array of an array of f_fss_nests_t.
 *
 * Properties:
 *   - array: An array of an array of f_fss_nests_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fss_nestss_t_
  typedef struct {
    f_fss_nests_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_fss_nestss_t;

  #define f_fss_nestss_t_initialize { 0, 0, 0 }

  #define macro_f_fss_nestss_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_fss_nestss_t_initialize_2(array, length)     { array, length, length }

  #define macro_f_fss_nestss_t_clear(nests) macro_f_memory_structures_clear(nests)
#endif // _di_f_fss_nestss_t_

/**
 * Delete a nest.
 *
 * @param nest
 *   The nest to delete.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_ranges_resize().
 *
 * @see f_string_ranges_resize()
 */
#ifndef _di_f_fss_nest_delete_
  extern f_status_t f_fss_nest_delete(f_fss_nest_t * const nest);
#endif // _di_f_fss_nest_delete_

/**
 * Destroy a nest.
 *
 * @param nest
 *   The nest to destroy.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *   Errors (with error bit) from: f_string_ranges_resize().
 *
 * @see f_memory_array_resize()
 * @see f_string_ranges_resize()
 */
#ifndef _di_f_fss_nest_destroy_
  extern f_status_t f_fss_nest_destroy(f_fss_nest_t * const nest);
#endif // _di_f_fss_nest_destroy_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_nests_t structure.
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
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamics_resize().
 *
 * @see f_string_dynamics_resize()
 */
#ifndef _di_f_fss_nests_delete_callback_
  extern f_status_t f_fss_nests_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_fss_nests_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_nests_t structure.
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
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamics_adjust().
 *
 * @see f_string_dynamics_adjust()
 */
#ifndef _di_f_fss_nests_destroy_callback_
  extern f_status_t f_fss_nests_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_fss_nests_destroy_callback_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_nestss_t structure.
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
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamics_resize().
 *
 * @see f_string_dynamics_resize()
 */
#ifndef _di_f_fss_nestss_delete_callback_
  extern f_status_t f_fss_nestss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_fss_nestss_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_nestss_t structure.
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
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamics_adjust().
 *
 * @see f_string_dynamics_adjust()
 */
#ifndef _di_f_fss_nestss_destroy_callback_
  extern f_status_t f_fss_nestss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_fss_nestss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_nest_h
