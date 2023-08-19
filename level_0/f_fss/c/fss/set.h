/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines set data to be used for/by project fss.
 *
 * This is auto-included by fss.h and should not need to be explicitly included.
 */
#ifndef _F_fss_set_h
#define _F_fss_set_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This holds an fss object with a set of fss content.
 *
 * The objects and contents should each be of the same used and size.
 * Any deviation to this would require implementing custom equivelents to the standard management macros.
 *
 * Properties:
 *   - objects:  The array of objects.
 *   - contents: The array of contents.
 */
#ifndef _di_f_fss_set_t_
  typedef struct {
    f_string_ranges_t objects;
    f_string_rangess_t contents;
  } f_fss_set_t;

  #define f_fss_set_t_initialize { f_string_ranges_t_initialize, f_string_rangess_t_initialize }

  #define macro_f_fss_set_t_initialize_1(objects, contents) { objects, contents }

  #define macro_f_fss_set_t_clear(set) \
    macro_f_string_ranges_t_clear(set.objects) \
    macro_f_string_rangess_t_clear(set.contents)
#endif // _di_f_fss_set_t_

/**
 * This holds an array of f_fss_set_t.
 *
 * Properties:
 *   - array: An array of f_fss_set_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fss_sets_t_
  typedef struct {
    f_fss_set_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_fss_sets_t;

  #define f_fss_sets_t_initialize { 0, 0, 0 }

  #define macro_f_fss_sets_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_fss_sets_t_initialize_2(array, length) { array, length, length }

  #define macro_f_fss_sets_t_clear(sets) macro_f_memory_structures_clear(sets)
#endif // _di_f_fss_sets_t_

/**
 * This holds an array of an array of f_fss_sets_t.
 *
 * Properties:
 *   - array: An array of an array of f_fss_sets_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fss_setss_t_
  typedef struct {
    f_fss_sets_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_fss_setss_t;

  #define f_fss_setss_t_initialize { 0, 0, 0 }

  #define macro_f_fss_setss_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_fss_setss_t_initialize_2(array, length) { array, length, length }

  #define macro_f_fss_setss_t_clear(sets) macro_f_memory_structures_clear(sets)
#endif // _di_f_fss_setss_t_

/**
 * Delete a set.
 *
 * @param set
 *   The set to delete.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_ranges_resize().
 *   Errors (with error bit) from: f_string_rangess_resize().
 *
 * @see f_string_ranges_resize()
 * @see f_string_rangess_resize()
 */
#ifndef _di_f_fss_set_delete_
  extern f_status_t f_fss_set_delete(f_fss_set_t * const set);
#endif // _di_f_fss_set_delete_

/**
 * Destroy a set.
 *
 * @param set
 *   The set to destroy.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_ranges_adjust().
 *   Errors (with error bit) from: f_string_rangess_adjust().
 *
 * @see f_string_ranges_adjust
 * @see f_string_rangess_adjust()()
 */
#ifndef _di_f_fss_set_destroy_
  extern f_status_t f_fss_set_destroy(f_fss_set_t * const set);
#endif // _di_f_fss_set_destroy_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_fss_sets_t structure.
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
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamics_resize().
 *
 * @see f_string_dynamics_resize()
 */
#ifndef _di_f_fss_sets_delete_callback_
  extern f_status_t f_fss_sets_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_fss_sets_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_fss_sets_t structure.
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
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamics_adjust().
 *
 * @see f_string_dynamics_adjust()
 */
#ifndef _di_f_fss_sets_destroy_callback_
  extern f_status_t f_fss_sets_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_fss_sets_destroy_callback_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_fss_setss_t structure.
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
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamics_resize().
 *
 * @see f_string_dynamics_resize()
 */
#ifndef _di_f_fss_setss_delete_callback_
  extern f_status_t f_fss_setss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_fss_setss_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_fss_setss_t structure.
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
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamics_adjust().
 *
 * @see f_string_dynamics_adjust()
 */
#ifndef _di_f_fss_setss_destroy_callback_
  extern f_status_t f_fss_setss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_fss_setss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_set_h
