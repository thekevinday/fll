/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_type_array_cell_h
#define _PRIVATE_F_type_array_cell_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation for resizing the fll_ids array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param fll_ids
 *   The fll_ids array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_fll_ids_adjust()
 * @see f_fll_ids_decimate_by()
 */
#if !defined(_di_f_fll_ids_adjust_) || !defined(_di_f_fll_ids_decimate_by_)
  extern f_status_t private_f_fll_ids_adjust(const f_array_length_t length, f_fll_ids_t *fll_ids) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fll_ids_adjust_) || !defined(_di_f_fll_ids_decimate_by_)

/**
 * Private implementation for appending the fll_id array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source fll_id to append.
 * @param destination
 *   The destination lengths the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_fll_ids_append()
 * @see f_fll_idss_append()
 */
#if !defined(_di_f_fll_ids_append_) || !defined(_di_f_fll_idss_append_)
  extern f_status_t private_f_fll_ids_append(const f_fll_id_t source, f_fll_ids_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fll_ids_append_) || !defined(_di_f_fll_idss_append_)

/**
 * Private implementation for appending the fll_id array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source fll_ids to append.
 * @param destination
 *   The destination lengths the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_fll_ids_append_all()
 * @see f_fll_idss_append()
 * @see f_fll_idss_append_all()
 */
#if !defined(_di_f_fll_ids_append_) || !defined(_di_f_fll_ids_append_all_) || !defined(_di_f_fll_idss_append_all_)
  extern f_status_t private_f_fll_ids_append_all(const f_fll_ids_t source, f_fll_ids_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fll_ids_append_) || !defined(_di_f_fll_ids_append_all_) || !defined(_di_f_fll_idss_append_all_)

/**
 * Private implementation for resizing the fll_ids array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param fll_ids
 *   The fll_ids array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_fll_ids_resize()
 * @see f_fll_ids_append()
 * @see f_fll_ids_decimate_by()
 * @see f_fll_idss_append()
 */
#if !defined(_di_f_fll_ids_resize_) || !defined(_di_f_fll_ids_append_) || !defined(_di_f_fll_ids_decimate_by_) || !defined(_di_f_fll_idss_append_)
  extern f_status_t private_f_fll_ids_resize(const f_array_length_t length, f_fll_ids_t *fll_ids) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fll_ids_resize_) || !defined(_di_f_fll_ids_append_) || !defined(_di_f_fll_ids_decimate_by_) || !defined(_di_f_fll_idss_append_)

/**
 * Private implementation for resizing the fll_idss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param fll_idss
 *   The fll_idss array to adjust.
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
 * @see f_fll_idss_adjust()
 * @see f_fll_idss_decimate_by()
 */
#if !defined(_di_f_fll_idss_adjust_) || !defined(_di_f_fll_idss_decimate_by_)
  extern f_status_t private_f_fll_idss_adjust(const f_array_length_t length, f_fll_idss_t *fll_idss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fll_idss_adjust_) || !defined(_di_f_fll_idss_decimate_by_)

/**
 * Private implementation for resizing the fll_idss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param fll_idss
 *   The fll_idss array to resize.
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
 * @see f_fll_idss_decrease_by()
 * @see f_fll_idss_increase()
 * @see f_fll_idss_increase_by()
 * @see f_fll_idss_resize()
 */
#if !defined(_di_f_fll_idss_decrease_by_) || !defined(_di_f_fll_idss_increase_) || !defined(_di_f_fll_idss_increase_by_) || !defined(_di_f_fll_idss_resize_)
  extern f_status_t private_f_fll_idss_resize(const f_array_length_t length, f_fll_idss_t *fll_idss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fll_idss_decrease_by_) || !defined(_di_f_fll_idss_increase_) || !defined(_di_f_fll_idss_increase_by_) || !defined(_di_f_fll_idss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_type_array_cell_h
