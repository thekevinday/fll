/**
 * FLL - Level 0
 *
 * Project: IKI
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines data to be used for/by iki related functionality.
 *
 * This is auto-included by iki.h and should not need to be explicitly included.
 */
#ifndef _F_iki_data_h
#define _F_iki_data_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Delete the IKI data.
 *
 * @param data
 *   The IKI data to delete.
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
#ifndef _di_f_iki_data_delete_
  extern f_status_t f_iki_data_delete(f_iki_data_t *data);
#endif // _di_f_iki_data_delete_

/**
 * Destroy the IKI data.
 *
 * @param data
 *   The IKI data to destroy.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *   Errors (with error bit) from: f_string_ranges_adjust().
 *
 * @see f_memory_array_adjust()
 * @see f_string_ranges_adjust()
 */
#ifndef _di_f_iki_data_destroy_
  extern f_status_t f_iki_data_destroy(f_iki_data_t *data);
#endif // _di_f_iki_data_destroy_

/**
 * Append the single source iki_data onto the destination.
 *
 * @param source
 *   The source iki_data to append.
 * @param destination
 *   The destination iki_datas the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_append().
 *   Errors (with error bit) from: f_memory_array_increase().
 *   Errors (with error bit) from: f_string_ranges_append_all().
 *
 * @see f_memory_array_append()
 * @see f_memory_array_increase()
 * @see f_string_ranges_append_all()
 */
#ifndef _di_f_iki_datas_append_
  extern f_status_t f_iki_datas_append(const f_iki_data_t source, f_iki_datas_t *destination);
#endif // _di_f_iki_datas_append_

/**
 * Append the source iki_datas onto the destination.
 *
 * @param source
 *   The source iki_datas to append.
 * @param destination
 *   The destination iki_datas the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_append().
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *   Errors (with error bit) from: f_string_ranges_append_all().
 *
 * @see f_memory_array_append()
 * @see f_memory_array_increase_by()
 * @see f_string_ranges_append_all()
 */
#ifndef _di_f_iki_datas_append_all_
  extern f_status_t f_iki_datas_append_all(const f_iki_datas_t source, f_iki_datas_t *destination);
#endif // _di_f_iki_datas_append_all_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_iki_datas_t structure.
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
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 * @see f_memory_arrays_resize()
 */
#ifndef _di_f_iki_datas_delete_callback_
  extern f_status_t f_iki_datas_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_iki_datas_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_iki_datas_t structure.
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
 *   Errors (with error bit) from: f_memory_array_adjust().
 *
 * @see f_memory_array_adjust()
 * @see f_memory_arrays_adjust()
 */
#ifndef _di_f_iki_datas_destroy_callback_
  extern f_status_t f_iki_datas_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_iki_datas_destroy_callback_

/**
 * Append the single source iki_datas onto the destination.
 *
 * @param source
 *   The source iki_datas to append.
 * @param destination
 *   The destination ranges the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase().
 *   Errors (with error bit) from: f_memory_array_resize().
 *   Errors (with error bit) from: f_string_ranges_resize().
 *
 * @see f_memory_array_increase()
 * @see f_memory_array_resize()
 * @see f_string_ranges_resize()
 */
#ifndef _di_f_iki_datass_append_
  extern f_status_t f_iki_datass_append(const f_iki_datas_t source, f_iki_datass_t *destination);
#endif // _di_f_iki_datass_append_

/**
 * Append the source iki_datass onto the destination.
 *
 * @param source
 *   The source iki_datass to append.
 * @param destination
 *   The destination ranges the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *   Errors (with error bit) from: f_memory_array_resize().
 *   Errors (with error bit) from: f_string_ranges_resize().
 *
 * @see f_memory_array_increase_by()
 * @see f_memory_array_resize()
 * @see f_string_ranges_resize()
 */
#ifndef _di_f_iki_datass_append_all_
  extern f_status_t f_iki_datass_append_all(const f_iki_datass_t source, f_iki_datass_t *destination);
#endif // _di_f_iki_datass_append_all_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_iki_datass_t structure.
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
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 * @see f_memory_arrays_resize()
 */
#ifndef _di_f_iki_datass_delete_callback_
  extern f_status_t f_iki_datass_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_iki_datass_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_iki_datass_t structure.
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
 *   Errors (with error bit) from: f_memory_array_adjust().
 *
 * @see f_memory_array_adjust()
 * @see f_memory_arrays_adjust()
 */
#ifndef _di_f_iki_datass_destroy_callback_
  extern f_status_t f_iki_datass_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_iki_datass_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_iki_data_h
