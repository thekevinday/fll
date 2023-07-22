/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_type_array_file_h
#define _PRIVATE_F_type_array_file_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation for resizing the files array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param structure
 *   The files array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_array_increase().
 *
 * @see f_memory_array_increase()
 *
 * @see f_files_adjust()
 * @see f_files_decimate_by()
 */
#if !defined(_di_f_files_adjust_) || !defined(_di_f_files_decimate_by_)
  extern f_status_t private_f_files_adjust(const f_number_unsigned_t length, f_files_t * const structure) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_files_adjust_) || !defined(_di_f_files_decimate_by_)

/**
 * Private implementation for appending the file array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source file to append.
 * @param destination
 *   The destination lengths the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_array_increase().
 *
 * @see f_memory_array_increase()
 *
 * @see f_files_append()
 * @see f_filess_append()
 */
#if !defined(_di_f_files_append_) || !defined(_di_f_filess_append_)
  extern f_status_t private_f_files_append(const f_file_t source, f_files_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_files_append_) || !defined(_di_f_filess_append_)

/**
 * Private implementation for appending the file array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source files to append.
 * @param destination
 *   The destination lengths the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_files_append_all()
 * @see f_filess_append()
 * @see f_filess_append_all()
 */
#if !defined(_di_f_files_append_) || !defined(_di_f_files_append_all_) || !defined(_di_f_filess_append_all_)
  extern f_status_t private_f_files_append_all(const f_files_t source, f_files_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_files_append_) || !defined(_di_f_files_append_all_) || !defined(_di_f_filess_append_all_)

/**
 * Private implementation for resizing the files array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param structure
 *   The files array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_files_append()
 * @see f_files_append_all()
 * @see f_files_decrease_by()
 * @see f_files_increase()
 * @see f_files_increase_by()
 * @see f_files_resize()
 * @see f_filess_append()
 * @see f_filess_append_all()
 *
 */
#if !defined(_di_f_files_append_) || !defined(_di_f_files_append_all_) || !defined(_di_f_files_decrease_by_) || !defined(_di_f_files_increase_) || !defined(_di_f_files_increase_by_) || !defined(_di_f_files_resize_) || !defined(_di_f_filess_append_) || !defined(_di_f_filess_append_all_)
  extern f_status_t private_f_files_resize(const f_number_unsigned_t length, f_files_t * const structure) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_files_append_) || !defined(_di_f_files_append_all_) || !defined(_di_f_files_decrease_by_) || !defined(_di_f_files_increase_) || !defined(_di_f_files_increase_by_) || !defined(_di_f_files_resize_) || !defined(_di_f_filess_append_) || !defined(_di_f_filess_append_all_)

/**
 * Private implementation for resizing the filess array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param structure
 *   The filess array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 *
 * @see f_filess_adjust()
 * @see f_filess_decimate_by()
 */
#if !defined(_di_f_filess_adjust_) || !defined(_di_f_filess_decimate_by_)
  extern f_status_t private_f_filess_adjust(const f_number_unsigned_t length, f_filess_t * const structure) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_filess_adjust_) || !defined(_di_f_filess_decimate_by_)

/**
 * Private implementation for resizing the filess array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param structure
 *   The filess array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_filess_decrease_by()
 * @see f_filess_increase()
 * @see f_filess_increase_by()
 * @see f_filess_resize()
 */
#if !defined(_di_f_filess_decrease_by_) || !defined(_di_f_filess_increase_) || !defined(_di_f_filess_increase_by_) || !defined(_di_f_filess_resize_)
  extern f_status_t private_f_filess_resize(const f_number_unsigned_t length, f_filess_t * const structure) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_filess_decrease_by_) || !defined(_di_f_filess_increase_) || !defined(_di_f_filess_increase_by_) || !defined(_di_f_filess_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_type_array_file_h
