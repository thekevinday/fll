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
#ifndef _PRIVATE_F_type_array_h
#define _PRIVATE_F_type_array_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation for resizing the statuss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param statuss
 *   The statuss array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_type_statuss_adjust()
 * @see f_type_statuss_decimate_by()
 */
#if !defined(_di_f_type_statuss_adjust_) || !defined(_di_f_type_statuss_decimate_by_)
  extern f_status_t private_f_type_statuss_adjust(const f_array_length_t length, f_statuss_t *statuss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_statuss_adjust_) || !defined(_di_f_type_statuss_decimate_by_)

/**
 * Private implementation for appending the status array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source statuss to append.
 * @param destination
 *   The destination statuss the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_statuss_append()
 * @see f_type_statusss_append()
 */
#if !defined(_di_f_type_statuss_append_) || !defined(_di_f_type_statusss_append_)
  extern f_status_t private_f_type_statuss_append(const f_statuss_t source, f_statuss_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_statuss_append_) || !defined(_di_f_type_statusss_append_)

/**
 * Private implementation for resizing the statuss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param statuss
 *   The statuss array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_statuss_resize()
 * @see f_type_statuss_append()
 * @see f_type_statuss_decimate_by()
 * @see f_type_statusss_append()
 */
#if !defined(_di_f_type_statuss_resize_) || !defined(_di_f_type_statuss_append_) || !defined(_di_f_type_statuss_decimate_by_) || !defined(_di_f_type_statusss_append_)
  extern f_status_t private_f_type_statuss_resize(const f_array_length_t length, f_statuss_t *statuss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_statuss_resize_) || !defined(_di_f_type_statuss_append_) || !defined(_di_f_type_statuss_decimate_by_) || !defined(_di_f_type_statusss_append_)

/**
 * Private implementation for resizing the statusss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param statusss
 *   The statusss array to adjust.
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
 * @see f_type_statusss_adjust()
 * @see f_type_statusss_decimate_by()
 */
#if !defined(_di_f_type_statusss_adjust_) || !defined(_di_f_type_statusss_decimate_by_)
  extern f_status_t private_f_type_statusss_adjust(const f_array_length_t length, f_statusss_t *statusss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_statusss_adjust_) || !defined(_di_f_type_statusss_decimate_by_)

/**
 * Private implementation for resizing the statusss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param statusss
 *   The statusss array to resize.
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
 * @see f_type_statusss_decrease_by()
 * @see f_type_statusss_increase()
 * @see f_type_statusss_increase_by()
 * @see f_type_statusss_resize()
 */
#if !defined(_di_f_type_statusss_decrease_by_) || !defined(_di_f_type_statusss_increase_) || !defined(_di_f_type_statusss_increase_by_) || !defined(_di_f_type_statusss_resize_)
  extern f_status_t private_f_type_statusss_resize(const f_array_length_t length, f_statusss_t *statusss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_statusss_decrease_by_) || !defined(_di_f_type_statusss_increase_) || !defined(_di_f_type_statusss_increase_by_) || !defined(_di_f_type_statusss_resize_)

/**
 * Private implementation for resizing the states array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param states
 *   The states array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_type_states_adjust()
 * @see f_type_states_decimate_by()
 */
#if !defined(_di_f_type_states_adjust_) || !defined(_di_f_type_states_decimate_by_)
  extern f_status_t private_f_type_states_adjust(const f_array_length_t length, f_states_t *states) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_states_adjust_) || !defined(_di_f_type_states_decimate_by_)

/**
 * Private implementation for appending the state array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source states to append.
 * @param destination
 *   The destination states the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_states_append()
 * @see f_type_statess_append()
 */
#if !defined(_di_f_type_states_append_) || !defined(_di_f_type_statess_append_)
  extern f_status_t private_f_type_states_append(const f_states_t source, f_states_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_states_append_) || !defined(_di_f_type_statess_append_)

/**
 * Private implementation for resizing the states array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param states
 *   The states array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_states_resize()
 * @see f_type_states_append()
 * @see f_type_states_decimate_by()
 * @see f_type_statess_append()
 */
#if !defined(_di_f_type_states_resize_) || !defined(_di_f_type_states_append_) || !defined(_di_f_type_states_decimate_by_) || !defined(_di_f_type_statess_append_)
  extern f_status_t private_f_type_states_resize(const f_array_length_t length, f_states_t *states) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_states_resize_) || !defined(_di_f_type_states_append_) || !defined(_di_f_type_states_decimate_by_) || !defined(_di_f_type_statess_append_)

/**
 * Private implementation for resizing the statess array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param statess
 *   The statess array to adjust.
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
 * @see f_type_statess_adjust()
 * @see f_type_statess_decimate_by()
 */
#if !defined(_di_f_type_statess_adjust_) || !defined(_di_f_type_statess_decimate_by_)
  extern f_status_t private_f_type_statess_adjust(const f_array_length_t length, f_statess_t *statess) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_statess_adjust_) || !defined(_di_f_type_statess_decimate_by_)

/**
 * Private implementation for resizing the statess array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param statess
 *   The statess array to resize.
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
 * @see f_type_statess_decrease_by()
 * @see f_type_statess_increase()
 * @see f_type_statess_increase_by()
 * @see f_type_statess_resize()
 */
#if !defined(_di_f_type_statess_decrease_by_) || !defined(_di_f_type_statess_increase_) || !defined(_di_f_type_statess_increase_by_) || !defined(_di_f_type_statess_resize_)
  extern f_status_t private_f_type_statess_resize(const f_array_length_t length, f_statess_t *statess) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_statess_decrease_by_) || !defined(_di_f_type_statess_increase_) || !defined(_di_f_type_statess_increase_by_) || !defined(_di_f_type_statess_resize_)

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
 * @see f_type_cells_adjust()
 * @see f_type_cells_decimate_by()
 */
#if !defined(_di_f_type_cells_adjust_) || !defined(_di_f_type_cells_decimate_by_)
  extern f_status_t private_f_type_cells_adjust(const f_array_length_t length, f_cells_t *cells) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_cells_adjust_) || !defined(_di_f_type_cells_decimate_by_)

/**
 * Private implementation for appending the cell array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source cells to append.
 * @param destination
 *   The destination cells the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_cells_append()
 * @see f_type_cellss_append()
 */
#if !defined(_di_f_type_cells_append_) || !defined(_di_f_type_cellss_append_)
  extern f_status_t private_f_type_cells_append(const f_cells_t source, f_cells_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_cells_append_) || !defined(_di_f_type_cellss_append_)

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
 * @see f_type_cells_resize()
 * @see f_type_cells_append()
 * @see f_type_cells_decimate_by()
 * @see f_type_cellss_append()
 */
#if !defined(_di_f_type_cells_resize_) || !defined(_di_f_type_cells_append_) || !defined(_di_f_type_cells_decimate_by_) || !defined(_di_f_type_cellss_append_)
  extern f_status_t private_f_type_cells_resize(const f_array_length_t length, f_cells_t *cells) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_cells_resize_) || !defined(_di_f_type_cells_append_) || !defined(_di_f_type_cells_decimate_by_) || !defined(_di_f_type_cellss_append_)

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
 * @see f_type_cellss_adjust()
 * @see f_type_cellss_decimate_by()
 */
#if !defined(_di_f_type_cellss_adjust_) || !defined(_di_f_type_cellss_decimate_by_)
  extern f_status_t private_f_type_cellss_adjust(const f_array_length_t length, f_cellss_t *cellss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_cellss_adjust_) || !defined(_di_f_type_cellss_decimate_by_)

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
 * @see f_type_cellss_decrease_by()
 * @see f_type_cellss_increase()
 * @see f_type_cellss_increase_by()
 * @see f_type_cellss_resize()
 */
#if !defined(_di_f_type_cellss_decrease_by_) || !defined(_di_f_type_cellss_increase_) || !defined(_di_f_type_cellss_increase_by_) || !defined(_di_f_type_cellss_resize_)
  extern f_status_t private_f_type_cellss_resize(const f_array_length_t length, f_cellss_t *cellss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_cellss_decrease_by_) || !defined(_di_f_type_cellss_increase_) || !defined(_di_f_type_cellss_increase_by_) || !defined(_di_f_type_cellss_resize_)

/**
 * Private implementation for resizing the ids array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param ids
 *   The ids array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_type_fll_ids_adjust()
 * @see f_type_fll_ids_decimate_by()
 */
#if !defined(_di_f_type_fll_ids_adjust_) || !defined(_di_f_type_fll_ids_decimate_by_)
  extern f_status_t private_f_type_fll_ids_adjust(const f_array_length_t length, f_fll_ids_t *ids) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_fll_ids_adjust_) || !defined(_di_f_type_fll_ids_decimate_by_)

/**
 * Private implementation for appending the fll_id array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source ids to append.
 * @param destination
 *   The destination ids the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_fll_ids_append()
 * @see f_type_fll_idss_append()
 */
#if !defined(_di_f_type_fll_ids_append_) || !defined(_di_f_type_fll_idss_append_)
  extern f_status_t private_f_type_fll_ids_append(const f_fll_ids_t source, f_fll_ids_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_fll_ids_append_) || !defined(_di_f_type_fll_idss_append_)

/**
 * Private implementation for resizing the ids array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param ids
 *   The ids array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_fll_ids_resize()
 * @see f_type_fll_ids_append()
 * @see f_type_fll_ids_decimate_by()
 * @see f_type_fll_idss_append()
 */
#if !defined(_di_f_type_fll_ids_resize_) || !defined(_di_f_type_fll_ids_append_) || !defined(_di_f_type_fll_ids_decimate_by_) || !defined(_di_f_type_fll_idss_append_)
  extern f_status_t private_f_type_fll_ids_resize(const f_array_length_t length, f_fll_ids_t *ids) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_fll_ids_resize_) || !defined(_di_f_type_fll_ids_append_) || !defined(_di_f_type_fll_ids_decimate_by_) || !defined(_di_f_type_fll_idss_append_)

/**
 * Private implementation for resizing the idss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param idss
 *   The idss array to adjust.
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
 * @see f_type_fll_idss_adjust()
 * @see f_type_fll_idss_decimate_by()
 */
#if !defined(_di_f_type_fll_idss_adjust_) || !defined(_di_f_type_fll_idss_decimate_by_)
  extern f_status_t private_f_type_fll_idss_adjust(const f_array_length_t length, f_fll_idss_t *idss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_fll_idss_adjust_) || !defined(_di_f_type_fll_idss_decimate_by_)

/**
 * Private implementation for resizing the idss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param idss
 *   The idss array to resize.
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
 * @see f_type_fll_idss_decrease_by()
 * @see f_type_fll_idss_increase()
 * @see f_type_fll_idss_increase_by()
 * @see f_type_fll_idss_resize()
 */
#if !defined(_di_f_type_fll_idss_decrease_by_) || !defined(_di_f_type_fll_idss_increase_) || !defined(_di_f_type_fll_idss_increase_by_) || !defined(_di_f_type_fll_idss_resize_)
  extern f_status_t private_f_type_fll_idss_resize(const f_array_length_t length, f_fll_idss_t *idss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_fll_idss_decrease_by_) || !defined(_di_f_type_fll_idss_increase_) || !defined(_di_f_type_fll_idss_increase_by_) || !defined(_di_f_type_fll_idss_resize_)
/**
 * Private implementation for resizing the array_lengths array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param lengths
 *   The lengths array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_type_array_lengths_adjust()
 * @see f_type_array_lengths_decimate_by()
 */
#if !defined(_di_f_type_array_lengths_adjust_) || !defined(_di_f_type_array_lengths_decimate_by_)
  extern f_status_t private_f_type_array_lengths_adjust(const f_array_length_t length, f_array_lengths_t *lengths) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_array_lengths_adjust_) || !defined(_di_f_type_array_lengths_decimate_by_)

/**
 * Private implementation for appending the array_length array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source array_lengths to append.
 * @param destination
 *   The destination lengths the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_array_lengths_append()
 * @see f_type_array_lengthss_append()
 */
#if !defined(_di_f_type_array_lengths_append_) || !defined(_di_f_type_array_lengthss_append_)
  extern f_status_t private_f_type_array_lengths_append(const f_array_lengths_t source, f_array_lengths_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_array_lengths_append_) || !defined(_di_f_type_array_lengthss_append_)

/**
 * Private implementation for resizing the array_lengths array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param lengths
 *   The lengths array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_array_lengths_resize()
 * @see f_type_array_lengths_append()
 * @see f_type_array_lengths_decimate_by()
 * @see f_type_array_lengthss_append()
 */
#if !defined(_di_f_type_array_lengths_resize_) || !defined(_di_f_type_array_lengths_append_) || !defined(_di_f_type_array_lengths_decimate_by_) || !defined(_di_f_type_array_lengthss_append_)
  extern f_status_t private_f_type_array_lengths_resize(const f_array_length_t length, f_array_lengths_t *lengths) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_array_lengths_resize_) || !defined(_di_f_type_array_lengths_append_) || !defined(_di_f_type_array_lengths_decimate_by_) || !defined(_di_f_type_array_lengthss_append_)

/**
 * Private implementation for resizing the lengthss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param lengthss
 *   The lengthss array to adjust.
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
 * @see f_type_array_lengthss_adjust()
 * @see f_type_array_lengthss_decimate_by()
 */
#if !defined(_di_f_type_array_lengthss_adjust_) || !defined(_di_f_type_array_lengthss_decimate_by_)
  extern f_status_t private_f_type_array_lengthss_adjust(const f_array_length_t length, f_array_lengthss_t *lengthss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_array_lengthss_adjust_) || !defined(_di_f_type_array_lengthss_decimate_by_)

/**
 * Private implementation for resizing the lengthss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param lengthss
 *   The lengthss array to resize.
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
 * @see f_type_array_lengthss_decrease_by()
 * @see f_type_array_lengthss_increase()
 * @see f_type_array_lengthss_increase_by()
 * @see f_type_array_lengthss_resize()
 */
#if !defined(_di_f_type_array_lengthss_decrease_by_) || !defined(_di_f_type_array_lengthss_increase_) || !defined(_di_f_type_array_lengthss_increase_by_) || !defined(_di_f_type_array_lengthss_resize_)
  extern f_status_t private_f_type_array_lengthss_resize(const f_array_length_t length, f_array_lengthss_t *lengthss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_array_lengthss_decrease_by_) || !defined(_di_f_type_array_lengthss_increase_) || !defined(_di_f_type_array_lengthss_increase_by_) || !defined(_di_f_type_array_lengthss_resize_)

/**
 * Private implementation for resizing the int8s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param int8s
 *   The int8s array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_type_int8s_adjust()
 * @see f_type_int8s_decimate_by()
 */
#if !defined(_di_f_type_int8s_adjust_) || !defined(_di_f_type_int8s_decimate_by_)
  extern f_status_t private_f_type_int8s_adjust(const f_array_length_t length, f_int8s_t *int8s) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_int8s_adjust_) || !defined(_di_f_type_int8s_decimate_by_)

/**
 * Private implementation for appending the int8 array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source int8s to append.
 * @param destination
 *   The destination int8s the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_int8s_append()
 * @see f_type_int8ss_append()
 */
#if !defined(_di_f_type_int8s_append_) || !defined(_di_f_type_int8ss_append_)
  extern f_status_t private_f_type_int8s_append(const f_int8s_t source, f_int8s_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_int8s_append_) || !defined(_di_f_type_int8ss_append_)

/**
 * Private implementation for resizing the int8s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param int8s
 *   The int8s array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_int8s_resize()
 * @see f_type_int8s_append()
 * @see f_type_int8s_decimate_by()
 * @see f_type_int8ss_append()
 */
#if !defined(_di_f_type_int8s_resize_) || !defined(_di_f_type_int8s_append_) || !defined(_di_f_type_int8s_decimate_by_) || !defined(_di_f_type_int8ss_append_)
  extern f_status_t private_f_type_int8s_resize(const f_array_length_t length, f_int8s_t *int8s) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_int8s_resize_) || !defined(_di_f_type_int8s_append_) || !defined(_di_f_type_int8s_decimate_by_) || !defined(_di_f_type_int8ss_append_)

/**
 * Private implementation for resizing the int8ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param int8ss
 *   The int8ss array to adjust.
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
 * @see f_type_int8ss_adjust()
 * @see f_type_int8ss_decimate_by()
 */
#if !defined(_di_f_type_int8ss_adjust_) || !defined(_di_f_type_int8ss_decimate_by_)
  extern f_status_t private_f_type_int8ss_adjust(const f_array_length_t length, f_int8ss_t *int8ss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_int8ss_adjust_) || !defined(_di_f_type_int8ss_decimate_by_)

/**
 * Private implementation for resizing the int8ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param int8ss
 *   The int8ss array to resize.
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
 * @see f_type_int8ss_decrease_by()
 * @see f_type_int8ss_increase()
 * @see f_type_int8ss_increase_by()
 * @see f_type_int8ss_resize()
 */
#if !defined(_di_f_type_int8ss_decrease_by_) || !defined(_di_f_type_int8ss_increase_) || !defined(_di_f_type_int8ss_increase_by_) || !defined(_di_f_type_int8ss_resize_)
  extern f_status_t private_f_type_int8ss_resize(const f_array_length_t length, f_int8ss_t *int8ss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_int8ss_decrease_by_) || !defined(_di_f_type_int8ss_increase_) || !defined(_di_f_type_int8ss_increase_by_) || !defined(_di_f_type_int8ss_resize_)

/**
 * Private implementation for resizing the uint8s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param uint8s
 *   The uint8s array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_type_uint8s_adjust()
 * @see f_type_uint8s_decimate_by()
 */
#if !defined(_di_f_type_uint8s_adjust_) || !defined(_di_f_type_uint8s_decimate_by_)
  extern f_status_t private_f_type_uint8s_adjust(const f_array_length_t length, f_uint8s_t *uint8s) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_uint8s_adjust_) || !defined(_di_f_type_uint8s_decimate_by_)

/**
 * Private implementation for appending the uint8 array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source uint8s to append.
 * @param destination
 *   The destination uint8s the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_uint8s_append()
 * @see f_type_uint8ss_append()
 */
#if !defined(_di_f_type_uint8s_append_) || !defined(_di_f_type_uint8ss_append_)
  extern f_status_t private_f_type_uint8s_append(const f_uint8s_t source, f_uint8s_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_uint8s_append_) || !defined(_di_f_type_uint8ss_append_)

/**
 * Private implementation for resizing the uint8s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param uint8s
 *   The uint8s array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_uint8s_resize()
 * @see f_type_uint8s_append()
 * @see f_type_uint8s_decimate_by()
 * @see f_type_uint8ss_append()
 */
#if !defined(_di_f_type_uint8s_resize_) || !defined(_di_f_type_uint8s_append_) || !defined(_di_f_type_uint8s_decimate_by_) || !defined(_di_f_type_uint8ss_append_)
  extern f_status_t private_f_type_uint8s_resize(const f_array_length_t length, f_uint8s_t *uint8s) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_uint8s_resize_) || !defined(_di_f_type_uint8s_append_) || !defined(_di_f_type_uint8s_decimate_by_) || !defined(_di_f_type_uint8ss_append_)

/**
 * Private implementation for resizing the uint8ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param uint8ss
 *   The uint8ss array to adjust.
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
 * @see f_type_uint8ss_adjust()
 * @see f_type_uint8ss_decimate_by()
 */
#if !defined(_di_f_type_uint8ss_adjust_) || !defined(_di_f_type_uint8ss_decimate_by_)
  extern f_status_t private_f_type_uint8ss_adjust(const f_array_length_t length, f_uint8ss_t *uint8ss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_uint8ss_adjust_) || !defined(_di_f_type_uint8ss_decimate_by_)

/**
 * Private implementation for resizing the uint8ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param uint8ss
 *   The uint8ss array to resize.
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
 * @see f_type_uint8ss_decrease_by()
 * @see f_type_uint8ss_increase()
 * @see f_type_uint8ss_increase_by()
 * @see f_type_uint8ss_resize()
 */
#if !defined(_di_f_type_uint8ss_decrease_by_) || !defined(_di_f_type_uint8ss_increase_) || !defined(_di_f_type_uint8ss_increase_by_) || !defined(_di_f_type_uint8ss_resize_)
  extern f_status_t private_f_type_uint8ss_resize(const f_array_length_t length, f_uint8ss_t *uint8ss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_uint8ss_decrease_by_) || !defined(_di_f_type_uint8ss_increase_) || !defined(_di_f_type_uint8ss_increase_by_) || !defined(_di_f_type_uint8ss_resize_)

/**
 * Private implementation for resizing the int16s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param int16s
 *   The int16s array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_type_int16s_adjust()
 * @see f_type_int16s_decimate_by()
 */
#if !defined(_di_f_type_int16s_adjust_) || !defined(_di_f_type_int16s_decimate_by_)
  extern f_status_t private_f_type_int16s_adjust(const f_array_length_t length, f_int16s_t *int16s) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_int16s_adjust_) || !defined(_di_f_type_int16s_decimate_by_)

/**
 * Private implementation for appending the int16 array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source int16s to append.
 * @param destination
 *   The destination int16s the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_int16s_append()
 * @see f_type_int16ss_append()
 */
#if !defined(_di_f_type_int16s_append_) || !defined(_di_f_type_int16ss_append_)
  extern f_status_t private_f_type_int16s_append(const f_int16s_t source, f_int16s_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_int16s_append_) || !defined(_di_f_type_int16ss_append_)

/**
 * Private implementation for resizing the int16s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param int16s
 *   The int16s array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_int16s_resize()
 * @see f_type_int16s_append()
 * @see f_type_int16s_decimate_by()
 * @see f_type_int16ss_append()
 */
#if !defined(_di_f_type_int16s_resize_) || !defined(_di_f_type_int16s_append_) || !defined(_di_f_type_int16s_decimate_by_) || !defined(_di_f_type_int16ss_append_)
  extern f_status_t private_f_type_int16s_resize(const f_array_length_t length, f_int16s_t *int16s) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_int16s_resize_) || !defined(_di_f_type_int16s_append_) || !defined(_di_f_type_int16s_decimate_by_) || !defined(_di_f_type_int16ss_append_)

/**
 * Private implementation for resizing the int16ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param int16ss
 *   The int16ss array to adjust.
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
 * @see f_type_int16ss_adjust()
 * @see f_type_int16ss_decimate_by()
 */
#if !defined(_di_f_type_int16ss_adjust_) || !defined(_di_f_type_int16ss_decimate_by_)
  extern f_status_t private_f_type_int16ss_adjust(const f_array_length_t length, f_int16ss_t *int16ss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_int16ss_adjust_) || !defined(_di_f_type_int16ss_decimate_by_)

/**
 * Private implementation for resizing the int16ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param int16ss
 *   The int16ss array to resize.
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
 * @see f_type_int16ss_decrease_by()
 * @see f_type_int16ss_increase()
 * @see f_type_int16ss_increase_by()
 * @see f_type_int16ss_resize()
 */
#if !defined(_di_f_type_int16ss_decrease_by_) || !defined(_di_f_type_int16ss_increase_) || !defined(_di_f_type_int16ss_increase_by_) || !defined(_di_f_type_int16ss_resize_)
  extern f_status_t private_f_type_int16ss_resize(const f_array_length_t length, f_int16ss_t *int16ss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_int16ss_decrease_by_) || !defined(_di_f_type_int16ss_increase_) || !defined(_di_f_type_int16ss_increase_by_) || !defined(_di_f_type_int16ss_resize_)

/**
 * Private implementation for resizing the uint16s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param uint16s
 *   The uint16s array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_type_uint16s_adjust()
 * @see f_type_uint16s_decimate_by()
 */
#if !defined(_di_f_type_uint16s_adjust_) || !defined(_di_f_type_uint16s_decimate_by_)
  extern f_status_t private_f_type_uint16s_adjust(const f_array_length_t length, f_uint16s_t *uint16s) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_uint16s_adjust_) || !defined(_di_f_type_uint16s_decimate_by_)

/**
 * Private implementation for appending the uint16 array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source uint16s to append.
 * @param destination
 *   The destination uint16s the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_uint16s_append()
 * @see f_type_uint16ss_append()
 */
#if !defined(_di_f_type_uint16s_append_) || !defined(_di_f_type_uint16ss_append_)
  extern f_status_t private_f_type_uint16s_append(const f_uint16s_t source, f_uint16s_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_uint16s_append_) || !defined(_di_f_type_uint16ss_append_)

/**
 * Private implementation for resizing the uint16s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param uint16s
 *   The uint16s array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_uint16s_resize()
 * @see f_type_uint16s_append()
 * @see f_type_uint16s_decimate_by()
 * @see f_type_uint16ss_append()
 */
#if !defined(_di_f_type_uint16s_resize_) || !defined(_di_f_type_uint16s_append_) || !defined(_di_f_type_uint16s_decimate_by_) || !defined(_di_f_type_uint16ss_append_)
  extern f_status_t private_f_type_uint16s_resize(const f_array_length_t length, f_uint16s_t *uint16s) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_uint16s_resize_) || !defined(_di_f_type_uint16s_append_) || !defined(_di_f_type_uint16s_decimate_by_) || !defined(_di_f_type_uint16ss_append_)

/**
 * Private implementation for resizing the uint16ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param uint16ss
 *   The uint16ss array to adjust.
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
 * @see f_type_uint16ss_adjust()
 * @see f_type_uint16ss_decimate_by()
 */
#if !defined(_di_f_type_uint16ss_adjust_) || !defined(_di_f_type_uint16ss_decimate_by_)
  extern f_status_t private_f_type_uint16ss_adjust(const f_array_length_t length, f_uint16ss_t *uint16ss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_uint16ss_adjust_) || !defined(_di_f_type_uint16ss_decimate_by_)

/**
 * Private implementation for resizing the uint16ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param uint16ss
 *   The uint16ss array to resize.
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
 * @see f_type_uint16ss_decrease_by()
 * @see f_type_uint16ss_increase()
 * @see f_type_uint16ss_increase_by()
 * @see f_type_uint16ss_resize()
 */
#if !defined(_di_f_type_uint16ss_decrease_by_) || !defined(_di_f_type_uint16ss_increase_) || !defined(_di_f_type_uint16ss_increase_by_) || !defined(_di_f_type_uint16ss_resize_)
  extern f_status_t private_f_type_uint16ss_resize(const f_array_length_t length, f_uint16ss_t *uint16ss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_uint16ss_decrease_by_) || !defined(_di_f_type_uint16ss_increase_) || !defined(_di_f_type_uint16ss_increase_by_) || !defined(_di_f_type_uint16ss_resize_)

/**
 * Private implementation for resizing the int32s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param int32s
 *   The int32s array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_type_int32s_adjust()
 * @see f_type_int32s_decimate_by()
 */
#if !defined(_di_f_type_int32s_adjust_) || !defined(_di_f_type_int32s_decimate_by_)
  extern f_status_t private_f_type_int32s_adjust(const f_array_length_t length, f_int32s_t *int32s) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_int32s_adjust_) || !defined(_di_f_type_int32s_decimate_by_)

/**
 * Private implementation for appending the int32 array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source int32s to append.
 * @param destination
 *   The destination int32s the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_int32s_append()
 * @see f_type_int32ss_append()
 */
#if !defined(_di_f_type_int32s_append_) || !defined(_di_f_type_int32ss_append_)
  extern f_status_t private_f_type_int32s_append(const f_int32s_t source, f_int32s_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_int32s_append_) || !defined(_di_f_type_int32ss_append_)

/**
 * Private implementation for resizing the int32s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param int32s
 *   The int32s array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_int32s_resize()
 * @see f_type_int32s_append()
 * @see f_type_int32s_decimate_by()
 * @see f_type_int32ss_append()
 */
#if !defined(_di_f_type_int32s_resize_) || !defined(_di_f_type_int32s_append_) || !defined(_di_f_type_int32s_decimate_by_) || !defined(_di_f_type_int32ss_append_)
  extern f_status_t private_f_type_int32s_resize(const f_array_length_t length, f_int32s_t *int32s) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_int32s_resize_) || !defined(_di_f_type_int32s_append_) || !defined(_di_f_type_int32s_decimate_by_) || !defined(_di_f_type_int32ss_append_)

/**
 * Private implementation for resizing the int32ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param int32ss
 *   The int32ss array to adjust.
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
 * @see f_type_int32ss_adjust()
 * @see f_type_int32ss_decimate_by()
 */
#if !defined(_di_f_type_int32ss_adjust_) || !defined(_di_f_type_int32ss_decimate_by_)
  extern f_status_t private_f_type_int32ss_adjust(const f_array_length_t length, f_int32ss_t *int32ss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_int32ss_adjust_) || !defined(_di_f_type_int32ss_decimate_by_)

/**
 * Private implementation for resizing the int32ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param int32ss
 *   The int32ss array to resize.
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
 * @see f_type_int32ss_decrease_by()
 * @see f_type_int32ss_increase()
 * @see f_type_int32ss_increase_by()
 * @see f_type_int32ss_resize()
 */
#if !defined(_di_f_type_int32ss_decrease_by_) || !defined(_di_f_type_int32ss_increase_) || !defined(_di_f_type_int32ss_increase_by_) || !defined(_di_f_type_int32ss_resize_)
  extern f_status_t private_f_type_int32ss_resize(const f_array_length_t length, f_int32ss_t *int32ss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_int32ss_decrease_by_) || !defined(_di_f_type_int32ss_increase_) || !defined(_di_f_type_int32ss_increase_by_) || !defined(_di_f_type_int32ss_resize_)

/**
 * Private implementation for resizing the uint32s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param uint32s
 *   The uint32s array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_type_uint32s_adjust()
 * @see f_type_uint32s_decimate_by()
 */
#if !defined(_di_f_type_uint32s_adjust_) || !defined(_di_f_type_uint32s_decimate_by_)
  extern f_status_t private_f_type_uint32s_adjust(const f_array_length_t length, f_uint32s_t *uint32s) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_uint32s_adjust_) || !defined(_di_f_type_uint32s_decimate_by_)

/**
 * Private implementation for appending the uint32 array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source uint32s to append.
 * @param destination
 *   The destination uint32s the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_uint32s_append()
 * @see f_type_uint32ss_append()
 */
#if !defined(_di_f_type_uint32s_append_) || !defined(_di_f_type_uint32ss_append_)
  extern f_status_t private_f_type_uint32s_append(const f_uint32s_t source, f_uint32s_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_uint32s_append_) || !defined(_di_f_type_uint32ss_append_)

/**
 * Private implementation for resizing the uint32s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param uint32s
 *   The uint32s array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_uint32s_resize()
 * @see f_type_uint32s_append()
 * @see f_type_uint32s_decimate_by()
 * @see f_type_uint32ss_append()
 */
#if !defined(_di_f_type_uint32s_resize_) || !defined(_di_f_type_uint32s_append_) || !defined(_di_f_type_uint32s_decimate_by_) || !defined(_di_f_type_uint32ss_append_)
  extern f_status_t private_f_type_uint32s_resize(const f_array_length_t length, f_uint32s_t *uint32s) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_uint32s_resize_) || !defined(_di_f_type_uint32s_append_) || !defined(_di_f_type_uint32s_decimate_by_) || !defined(_di_f_type_uint32ss_append_)

/**
 * Private implementation for resizing the uint32ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param uint32ss
 *   The uint32ss array to adjust.
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
 * @see f_type_uint32ss_adjust()
 * @see f_type_uint32ss_decimate_by()
 */
#if !defined(_di_f_type_uint32ss_adjust_) || !defined(_di_f_type_uint32ss_decimate_by_)
  extern f_status_t private_f_type_uint32ss_adjust(const f_array_length_t length, f_uint32ss_t *uint32ss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_uint32ss_adjust_) || !defined(_di_f_type_uint32ss_decimate_by_)

/**
 * Private implementation for resizing the uint32ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param uint32ss
 *   The uint32ss array to resize.
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
 * @see f_type_uint32ss_decrease_by()
 * @see f_type_uint32ss_increase()
 * @see f_type_uint32ss_increase_by()
 * @see f_type_uint32ss_resize()
 */
#if !defined(_di_f_type_uint32ss_decrease_by_) || !defined(_di_f_type_uint32ss_increase_) || !defined(_di_f_type_uint32ss_increase_by_) || !defined(_di_f_type_uint32ss_resize_)
  extern f_status_t private_f_type_uint32ss_resize(const f_array_length_t length, f_uint32ss_t *uint32ss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_uint32ss_decrease_by_) || !defined(_di_f_type_uint32ss_increase_) || !defined(_di_f_type_uint32ss_increase_by_) || !defined(_di_f_type_uint32ss_resize_)

/**
 * Private implementation for resizing the int64s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param int64s
 *   The int64s array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_type_int64s_adjust()
 * @see f_type_int64s_decimate_by()
 */
#if !defined(_di_f_type_int64s_adjust_) || !defined(_di_f_type_int64s_decimate_by_)
  extern f_status_t private_f_type_int64s_adjust(const f_array_length_t length, f_int64s_t *int64s) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_int64s_adjust_) || !defined(_di_f_type_int64s_decimate_by_)

/**
 * Private implementation for appending the int64 array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source int64s to append.
 * @param destination
 *   The destination int64s the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_int64s_append()
 * @see f_type_int64ss_append()
 */
#if !defined(_di_f_type_int64s_append_) || !defined(_di_f_type_int64ss_append_)
  extern f_status_t private_f_type_int64s_append(const f_int64s_t source, f_int64s_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_int64s_append_) || !defined(_di_f_type_int64ss_append_)

/**
 * Private implementation for resizing the int64s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param int64s
 *   The int64s array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_int64s_resize()
 * @see f_type_int64s_append()
 * @see f_type_int64s_decimate_by()
 * @see f_type_int64ss_append()
 */
#if !defined(_di_f_type_int64s_resize_) || !defined(_di_f_type_int64s_append_) || !defined(_di_f_type_int64s_decimate_by_) || !defined(_di_f_type_int64ss_append_)
  extern f_status_t private_f_type_int64s_resize(const f_array_length_t length, f_int64s_t *int64s) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_int64s_resize_) || !defined(_di_f_type_int64s_append_) || !defined(_di_f_type_int64s_decimate_by_) || !defined(_di_f_type_int64ss_append_)

/**
 * Private implementation for resizing the int64ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param int64ss
 *   The int64ss array to adjust.
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
 * @see f_type_int64ss_adjust()
 * @see f_type_int64ss_decimate_by()
 */
#if !defined(_di_f_type_int64ss_adjust_) || !defined(_di_f_type_int64ss_decimate_by_)
  extern f_status_t private_f_type_int64ss_adjust(const f_array_length_t length, f_int64ss_t *int64ss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_int64ss_adjust_) || !defined(_di_f_type_int64ss_decimate_by_)

/**
 * Private implementation for resizing the int64ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param int64ss
 *   The int64ss array to resize.
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
 * @see f_type_int64ss_decrease_by()
 * @see f_type_int64ss_increase()
 * @see f_type_int64ss_increase_by()
 * @see f_type_int64ss_resize()
 */
#if !defined(_di_f_type_int64ss_decrease_by_) || !defined(_di_f_type_int64ss_increase_) || !defined(_di_f_type_int64ss_increase_by_) || !defined(_di_f_type_int64ss_resize_)
  extern f_status_t private_f_type_int64ss_resize(const f_array_length_t length, f_int64ss_t *int64ss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_int64ss_decrease_by_) || !defined(_di_f_type_int64ss_increase_) || !defined(_di_f_type_int64ss_increase_by_) || !defined(_di_f_type_int64ss_resize_)

/**
 * Private implementation for resizing the uint64s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param uint64s
 *   The uint64s array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_type_uint64s_adjust()
 * @see f_type_uint64s_decimate_by()
 */
#if !defined(_di_f_type_uint64s_adjust_) || !defined(_di_f_type_uint64s_decimate_by_)
  extern f_status_t private_f_type_uint64s_adjust(const f_array_length_t length, f_uint64s_t *uint64s) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_uint64s_adjust_) || !defined(_di_f_type_uint64s_decimate_by_)

/**
 * Private implementation for appending the uint64 array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source uint64s to append.
 * @param destination
 *   The destination uint64s the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_uint64s_append()
 * @see f_type_uint64ss_append()
 */
#if !defined(_di_f_type_uint64s_append_) || !defined(_di_f_type_uint64ss_append_)
  extern f_status_t private_f_type_uint64s_append(const f_uint64s_t source, f_uint64s_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_uint64s_append_) || !defined(_di_f_type_uint64ss_append_)

/**
 * Private implementation for resizing the uint64s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param uint64s
 *   The uint64s array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_uint64s_resize()
 * @see f_type_uint64s_append()
 * @see f_type_uint64s_decimate_by()
 * @see f_type_uint64ss_append()
 */
#if !defined(_di_f_type_uint64s_resize_) || !defined(_di_f_type_uint64s_append_) || !defined(_di_f_type_uint64s_decimate_by_) || !defined(_di_f_type_uint64ss_append_)
  extern f_status_t private_f_type_uint64s_resize(const f_array_length_t length, f_uint64s_t *uint64s) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_uint64s_resize_) || !defined(_di_f_type_uint64s_append_) || !defined(_di_f_type_uint64s_decimate_by_) || !defined(_di_f_type_uint64ss_append_)

/**
 * Private implementation for resizing the uint64ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param uint64ss
 *   The uint64ss array to adjust.
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
 * @see f_type_uint64ss_adjust()
 * @see f_type_uint64ss_decimate_by()
 */
#if !defined(_di_f_type_uint64ss_adjust_) || !defined(_di_f_type_uint64ss_decimate_by_)
  extern f_status_t private_f_type_uint64ss_adjust(const f_array_length_t length, f_uint64ss_t *uint64ss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_uint64ss_adjust_) || !defined(_di_f_type_uint64ss_decimate_by_)

/**
 * Private implementation for resizing the uint64ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param uint64ss
 *   The uint64ss array to resize.
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
 * @see f_type_uint64ss_decrease_by()
 * @see f_type_uint64ss_increase()
 * @see f_type_uint64ss_increase_by()
 * @see f_type_uint64ss_resize()
 */
#if !defined(_di_f_type_uint64ss_decrease_by_) || !defined(_di_f_type_uint64ss_increase_) || !defined(_di_f_type_uint64ss_increase_by_) || !defined(_di_f_type_uint64ss_resize_)
  extern f_status_t private_f_type_uint64ss_resize(const f_array_length_t length, f_uint64ss_t *uint64ss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_uint64ss_decrease_by_) || !defined(_di_f_type_uint64ss_increase_) || !defined(_di_f_type_uint64ss_increase_by_) || !defined(_di_f_type_uint64ss_resize_)

/**
 * Private implementation for resizing the int128s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param int128s
 *   The int128s array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_type_int128s_adjust()
 * @see f_type_int128s_decimate_by()
 */
#if !defined(_di_f_type_int128s_adjust_) || !defined(_di_f_type_int128s_decimate_by_)
  extern f_status_t private_f_type_int128s_adjust(const f_array_length_t length, f_int128s_t *int128s) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_int128s_adjust_) || !defined(_di_f_type_int128s_decimate_by_)

/**
 * Private implementation for appending the int128 array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source int128s to append.
 * @param destination
 *   The destination int128s the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_int128s_append()
 * @see f_type_int128ss_append()
 */
#if !defined(_di_f_type_int128s_append_) || !defined(_di_f_type_int128ss_append_)
  extern f_status_t private_f_type_int128s_append(const f_int128s_t source, f_int128s_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_int128s_append_) || !defined(_di_f_type_int128ss_append_)

/**
 * Private implementation for resizing the int128s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param int128s
 *   The int128s array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_int128s_resize()
 * @see f_type_int128s_append()
 * @see f_type_int128s_decimate_by()
 * @see f_type_int128ss_append()
 */
#if !defined(_di_f_type_int128s_resize_) || !defined(_di_f_type_int128s_append_) || !defined(_di_f_type_int128s_decimate_by_) || !defined(_di_f_type_int128ss_append_)
  extern f_status_t private_f_type_int128s_resize(const f_array_length_t length, f_int128s_t *int128s) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_int128s_resize_) || !defined(_di_f_type_int128s_append_) || !defined(_di_f_type_int128s_decimate_by_) || !defined(_di_f_type_int128ss_append_)

/**
 * Private implementation for resizing the int128ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param int128ss
 *   The int128ss array to adjust.
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
 * @see f_type_int128ss_adjust()
 * @see f_type_int128ss_decimate_by()
 */
#if !defined(_di_f_type_int128ss_adjust_) || !defined(_di_f_type_int128ss_decimate_by_)
  extern f_status_t private_f_type_int128ss_adjust(const f_array_length_t length, f_int128ss_t *int128ss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_int128ss_adjust_) || !defined(_di_f_type_int128ss_decimate_by_)

/**
 * Private implementation for resizing the int128ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param int128ss
 *   The int128ss array to resize.
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
 * @see f_type_int128ss_decrease_by()
 * @see f_type_int128ss_increase()
 * @see f_type_int128ss_increase_by()
 * @see f_type_int128ss_resize()
 */
#if !defined(_di_f_type_int128ss_decrease_by_) || !defined(_di_f_type_int128ss_increase_) || !defined(_di_f_type_int128ss_increase_by_) || !defined(_di_f_type_int128ss_resize_)
  extern f_status_t private_f_type_int128ss_resize(const f_array_length_t length, f_int128ss_t *int128ss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_int128ss_decrease_by_) || !defined(_di_f_type_int128ss_increase_) || !defined(_di_f_type_int128ss_increase_by_) || !defined(_di_f_type_int128ss_resize_)

/**
 * Private implementation for resizing the uint128s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param uint128s
 *   The uint128s array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_type_uint128s_adjust()
 * @see f_type_uint128s_decimate_by()
 */
#if !defined(_di_f_type_uint128s_adjust_) || !defined(_di_f_type_uint128s_decimate_by_)
  extern f_status_t private_f_type_uint128s_adjust(const f_array_length_t length, f_uint128s_t *uint128s) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_uint128s_adjust_) || !defined(_di_f_type_uint128s_decimate_by_)

/**
 * Private implementation for appending the uint128 array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source uint128s to append.
 * @param destination
 *   The destination uint128s the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_uint128s_append()
 * @see f_type_uint128ss_append()
 */
#if !defined(_di_f_type_uint128s_append_) || !defined(_di_f_type_uint128ss_append_)
  extern f_status_t private_f_type_uint128s_append(const f_uint128s_t source, f_uint128s_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_uint128s_append_) || !defined(_di_f_type_uint128ss_append_)

/**
 * Private implementation for resizing the uint128s array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param uint128s
 *   The uint128s array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_uint128s_resize()
 * @see f_type_uint128s_append()
 * @see f_type_uint128s_decimate_by()
 * @see f_type_uint128ss_append()
 */
#if !defined(_di_f_type_uint128s_resize_) || !defined(_di_f_type_uint128s_append_) || !defined(_di_f_type_uint128s_decimate_by_) || !defined(_di_f_type_uint128ss_append_)
  extern f_status_t private_f_type_uint128s_resize(const f_array_length_t length, f_uint128s_t *uint128s) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_uint128s_resize_) || !defined(_di_f_type_uint128s_append_) || !defined(_di_f_type_uint128s_decimate_by_) || !defined(_di_f_type_uint128ss_append_)

/**
 * Private implementation for resizing the uint128ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param uint128ss
 *   The uint128ss array to adjust.
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
 * @see f_type_uint128ss_adjust()
 * @see f_type_uint128ss_decimate_by()
 */
#if !defined(_di_f_type_uint128ss_adjust_) || !defined(_di_f_type_uint128ss_decimate_by_)
  extern f_status_t private_f_type_uint128ss_adjust(const f_array_length_t length, f_uint128ss_t *uint128ss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_uint128ss_adjust_) || !defined(_di_f_type_uint128ss_decimate_by_)

/**
 * Private implementation for resizing the uint128ss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param uint128ss
 *   The uint128ss array to resize.
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
 * @see f_type_uint128ss_decrease_by()
 * @see f_type_uint128ss_increase()
 * @see f_type_uint128ss_increase_by()
 * @see f_type_uint128ss_resize()
 */
#if !defined(_di_f_type_uint128ss_decrease_by_) || !defined(_di_f_type_uint128ss_increase_) || !defined(_di_f_type_uint128ss_increase_by_) || !defined(_di_f_type_uint128ss_resize_)
  extern f_status_t private_f_type_uint128ss_resize(const f_array_length_t length, f_uint128ss_t *uint128ss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_uint128ss_decrease_by_) || !defined(_di_f_type_uint128ss_increase_) || !defined(_di_f_type_uint128ss_increase_by_) || !defined(_di_f_type_uint128ss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_type_array_h
