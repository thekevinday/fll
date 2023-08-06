/**
 * FLL - Level 0
 *
 * Project: IKI
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_iki_data_h
#define _PRIVATE_F_iki_data_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation for resizing the iki_datas array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param structure
 *   The iki_datas array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *   Errors (with error bit) from: f_string_ranges_adjust().
 *
 * @see f_memory_array_adjust()
 * @see f_string_ranges_adjust()
 *
 * @see f_iki_datas_adjust()
 * @see f_iki_datas_decimate_by()
 */
#if !defined(_di_f_iki_datas_adjust_) || !defined(_di_f_iki_datas_decimate_by_)
  extern f_status_t private_f_iki_datas_adjust(const f_number_unsigned_t length, f_iki_datas_t *structure) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_iki_datas_adjust_) || !defined(_di_f_iki_datas_decimate_by_)

/**
 * Private implementation for appending the iki_data array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source iki_data to append.
 * @param destination
 *   The iki_datas array the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_array_append_all().
 *   Errors (with error bit) from: f_memory_array_increase().
 *   Errors (with error bit) from: f_string_ranges_append_all().
 *
 * @see f_memory_array_append_all()
 * @see f_memory_array_increase()
 * @see f_string_ranges_append_all()
 *
 * @see f_iki_datas_append()
 * @see f_iki_datass_append()
 */
#if !defined(_di_f_iki_datas_append_) || !defined(_di_f_iki_datass_append_)
  extern f_status_t private_f_iki_datas_append(const f_iki_data_t source, f_iki_datas_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_iki_datas_append_) || !defined(_di_f_iki_datass_append_)

/**
 * Private implementation for appending the iki_data array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source iki_datas to append.
 * @param destination
 *   The iki_datas array the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_array_append_all().
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *   Errors (with error bit) from: f_string_ranges_append_all().
 *
 * @see f_memory_array_append_all()
 * @see f_memory_array_increase_by()
 * @see f_string_ranges_append_all()
 *
 * @see f_iki_datass_append()
 * @see f_iki_datass_append_all()
 */
#if !defined(_di_f_iki_datas_append_) || !defined(_di_f_iki_datas_append_all_) || !defined(_di_f_iki_datass_append_all_)
  extern f_status_t private_f_iki_datas_append_all(const f_iki_datas_t source, f_iki_datas_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_iki_datas_append_) || !defined(_di_f_iki_datas_append_all_) || !defined(_di_f_iki_datass_append_all_)

/**
 * Private implementation for resizing the iki_datas array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param structure
 *   The iki_datas array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *   Errors (with error bit) from: f_string_ranges_resize().
 *
 * @see f_memory_array_resize()
 * @see f_string_ranges_resize()
 *
 * @see f_iki_datas_resize()
 * @see f_iki_datas_append()
 * @see f_iki_datas_decimate_by()
 * @see f_iki_datass_append()
 */
#if !defined(_di_f_iki_datas_resize_) || !defined(_di_f_iki_datas_append_) || !defined(_di_f_iki_datas_decimate_by_) || !defined(_di_f_iki_datass_append_)
  extern f_status_t private_f_iki_datas_resize(const f_number_unsigned_t length, f_iki_datas_t *structure) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_iki_datas_resize_) || !defined(_di_f_iki_datas_append_) || !defined(_di_f_iki_datas_decimate_by_) || !defined(_di_f_iki_datass_append_)

/**
 * Private implementation for resizing the iki_datass array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param iki_datass
 *   The iki_datass array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *   Errors (with error bit) from: f_string_ranges_adjust().
 *
 * @see f_memory_array_adjust()
 * @see f_string_ranges_adjust()
 *
 * @see f_iki_datass_adjust()
 * @see f_iki_datass_decimate_by()
 */
#if !defined(_di_f_iki_datass_adjust_) || !defined(_di_f_iki_datass_decimate_by_)
  extern f_status_t private_f_iki_datass_adjust(const f_number_unsigned_t length, f_iki_datass_t *datass) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_iki_datass_adjust_) || !defined(_di_f_iki_datass_decimate_by_)

/**
 * Private implementation for resizing the iki_datass array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param iki_datass
 *   The iki_datass array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *   Errors (with error bit) from: f_string_ranges_resize().
 *
 * @see f_memory_array_resize()
 * @see f_string_ranges_resize()
 *
 * @see f_iki_datass_decrease_by()
 * @see f_iki_datass_increase()
 * @see f_iki_datass_increase_by()
 * @see f_iki_datass_resize()
 */
#if !defined(_di_f_iki_datass_decrease_by_) || !defined(_di_f_iki_datass_increase_) || !defined(_di_f_iki_datass_increase_by_) || !defined(_di_f_iki_datass_resize_)
  extern f_status_t private_f_iki_datass_resize(const f_number_unsigned_t length, f_iki_datass_t *datass) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_iki_datass_decrease_by_) || !defined(_di_f_iki_datass_increase_) || !defined(_di_f_iki_datass_increase_by_) || !defined(_di_f_iki_datass_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_iki_data_h
