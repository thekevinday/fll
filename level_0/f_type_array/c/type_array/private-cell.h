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
#ifndef _PRIVATE_F_type_array_cell_h
#define _PRIVATE_F_type_array_cell_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation for resizing the cells array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param cells
 *   The cells array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_cells_adjust()
 * @see f_cells_decimate_by()
 */
#if !defined(_di_f_cells_adjust_) || !defined(_di_f_cells_decimate_by_)
  extern f_status_t private_f_cells_adjust(const f_number_unsigned_t length, f_cells_t * const cells) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_cells_adjust_) || !defined(_di_f_cells_decimate_by_)

/**
 * Private implementation for appending the cell array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source cell to append.
 * @param destination
 *   The destination lengths the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_cells_append()
 * @see f_cellss_append()
 */
#if !defined(_di_f_cells_append_) || !defined(_di_f_cellss_append_)
  extern f_status_t private_f_cells_append(const f_cell_t source, f_cells_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_cells_append_) || !defined(_di_f_cellss_append_)

/**
 * Private implementation for appending the cell array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source cells to append.
 * @param destination
 *   The destination lengths the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_cells_append_all()
 * @see f_cellss_append()
 * @see f_cellss_append_all()
 */
#if !defined(_di_f_cells_append_) || !defined(_di_f_cells_append_all_) || !defined(_di_f_cellss_append_all_)
  extern f_status_t private_f_cells_append_all(const f_cells_t source, f_cells_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_cells_append_) || !defined(_di_f_cells_append_all_) || !defined(_di_f_cellss_append_all_)

/**
 * Private implementation for resizing the cells array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param cells
 *   The cells array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_cells_resize()
 * @see f_cells_append()
 * @see f_cells_decrease_by()
 * @see f_cellss_append()
 */
#if !defined(_di_f_cells_resize_) || !defined(_di_f_cells_append_) || !defined(_di_f_cells_decrease_by_) || !defined(_di_f_cellss_append_)
  extern f_status_t private_f_cells_resize(const f_number_unsigned_t length, f_cells_t * const cells) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_cells_resize_) || !defined(_di_f_cells_append_) || !defined(_di_f_cells_decrease_by_) || !defined(_di_f_cellss_append_)

/**
 * Private implementation for resizing the cellss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param cellss
 *   The cellss array to adjust.
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
 * @see f_cellss_adjust()
 * @see f_cellss_decimate_by()
 */
#if !defined(_di_f_cellss_adjust_) || !defined(_di_f_cellss_decimate_by_)
  extern f_status_t private_f_cellss_adjust(const f_number_unsigned_t length, f_cellss_t * const cellss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_cellss_adjust_) || !defined(_di_f_cellss_decimate_by_)

/**
 * Private implementation for resizing the cellss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param cellss
 *   The cellss array to resize.
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
 * @see f_cellss_decrease_by()
 * @see f_cellss_increase()
 * @see f_cellss_increase_by()
 * @see f_cellss_resize()
 */
#if !defined(_di_f_cellss_decrease_by_) || !defined(_di_f_cellss_increase_) || !defined(_di_f_cellss_increase_by_) || !defined(_di_f_cellss_resize_)
  extern f_status_t private_f_cellss_resize(const f_number_unsigned_t length, f_cellss_t * const cellss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_cellss_decrease_by_) || !defined(_di_f_cellss_increase_) || !defined(_di_f_cellss_increase_by_) || !defined(_di_f_cellss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_type_array_cell_h
