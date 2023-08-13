/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines named set data to be used for/by project fss.
 *
 * This is auto-included by fss.h and should not need to be explicitly included.
 */
#ifndef _F_fss_named_h
#define _F_fss_named_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This holds a named set of fss objects, contents, and quotess.
 *
 * The objects, contents, and quotess should each be of the same used and size.
 * Any deviation to this would require implementing custom equivelents to the standard management macros.
 *
 * Properties:
 *   - name:     The name representing this set.
 *   - objects:  The array of objects.
 *   - contents: The array of contents.
 *   - quotess:  The array of quote for each content.
 */
#ifndef _di_f_fss_named_t_
  typedef struct {
    f_string_range_t name;

    f_string_ranges_t objects;
    f_string_rangess_t contents;
    f_uint8ss_t quotess;
  } f_fss_named_t;

  #define f_fss_named_t_initialize { f_string_range_t_initialize, f_string_ranges_t_initialize, f_string_rangess_t_initialize, f_uint8ss_t_initialize }

  #define macro_f_fss_named_t_initialize_1(name, objects, contents, quotess) macro_f_number_unsigneds_t_initialize_1(name, objects, contents, quotess)

  #define macro_f_fss_named_t_clear(named) \
    macro_f_string_range_t_clear(named.name) \
    macro_f_string_ranges_t_clear(named.objects) \
    macro_f_string_rangess_t_clear(named.contents) \
    macro_f_uint8ss_t_clear(named.quotess)
#endif // _di_f_fss_named_t_

/**
 * This holds an array of f_fss_named_t.
 *
 * Properties:
 *   - array: An array of f_fss_named_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fss_nameds_t_
  typedef struct {
    f_fss_named_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_fss_nameds_t;

  #define f_fss_nameds_t_initialize { 0, 0, 0 }

  #define macro_f_fss_nameds_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_fss_nameds_t_initialize_2(array, length) { array, length, length }

  #define macro_f_fss_nameds_t_clear(nameds) macro_f_memory_structures_clear(nameds)
#endif // _di_f_fss_nameds_t_

/**
 * Delete a named.
 *
 * @param named
 *   The named to delete.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_ranges_resize().
 *   Errors (with error bit) from: f_string_rangess_resize().
 *   Errors (with error bit) from: f_memory_arrays_resize().
 *
 * @see f_string_ranges_resize()
 * @see f_string_rangess_resize()
 * @see f_memory_arrays_resize()
 */
#ifndef _di_f_fss_named_delete_
  extern f_status_t f_fss_named_delete(f_fss_named_t * const named);
#endif // _di_f_fss_named_delete_

/**
 * Destroy a named.
 *
 * @param named
 *   The named to destroy.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_ranges_adjust().
 *   Errors (with error bit) from: f_string_rangess_adjust().
 *   Errors (with error bit) from: f_memory_arrays_adjust().
 *
 * @see f_string_ranges_adjust()
 * @see f_string_rangess_adjust()
 * @see f_memory_arrays_adjust()
 */
#ifndef _di_f_fss_named_destroy_
  extern f_status_t f_fss_named_destroy(f_fss_named_t * const named);
#endif // _di_f_fss_named_destroy_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_nameds_t structure.
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
 *   Errors (with error bit) from: f_string_ranges_resize().
 *   Errors (with error bit) from: f_string_rangess_resize().
 *   Errors (with error bit) from: f_memory_arrays_resize().
 *
 * @see f_string_ranges_resize()
 * @see f_string_rangess_resize()
 * @see f_memory_arrays_resize()
 */
#ifndef _di_f_fss_nameds_delete_callback_
  extern f_status_t f_fss_nameds_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_fss_nameds_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_nameds_t structure.
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
 *   Errors (with error bit) from: f_string_ranges_adjust().
 *   Errors (with error bit) from: f_string_rangess_adjust().
 *   Errors (with error bit) from: f_memory_arrays_adjust().
 *
 * @see f_string_ranges_adjust()
 * @see f_string_rangess_adjust()
 * @see f_memory_arrays_adjust()
 */
#ifndef _di_f_fss_nameds_destroy_callback_
  extern f_status_t f_fss_nameds_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_fss_nameds_destroy_callback_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_namedss_t structure.
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
 *   Errors (with error bit) from: f_string_ranges_resize().
 *   Errors (with error bit) from: f_string_rangess_resize().
 *   Errors (with error bit) from: f_memory_arrays_resize().
 *
 * @see f_string_ranges_resize()
 * @see f_string_rangess_resize()
 * @see f_memory_arrays_resize()
 */
#ifndef _di_f_fss_namedss_delete_callback_
  extern f_status_t f_fss_namedss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_fss_namedss_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_namedss_t structure.
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
 *   Errors (with error bit) from: f_string_ranges_adjust().
 *   Errors (with error bit) from: f_string_rangess_adjust().
 *   Errors (with error bit) from: f_memory_arrays_adjust().
 *
 * @see f_string_ranges_adjust()
 * @see f_string_rangess_adjust()
 * @see f_memory_arrays_adjust()
 */
#ifndef _di_f_fss_namedss_destroy_callback_
  extern f_status_t f_fss_namedss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_fss_namedss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_named_h
