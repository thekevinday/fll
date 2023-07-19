/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_fss_set_quote_h
#define _PRIVATE_F_fss_set_quote_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param set_quote
 *   The set_quote to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_string_ranges_adjust().
 *   Errors (with error bit) from: f_string_rangess_adjust().
 *   Errors (with error bit) from: f_uint8s_adjust().
 *   Errors (with error bit) from: f_uint8ss_adjust().
 *
 * @see f_string_ranges_adjust()
 * @see f_string_rangess_adjust()
 * @see f_uint8s_adjust()
 * @see f_uint8ss_adjust()
 *
 * @see f_fss_set_quote_adjust()
 * @see f_fss_set_quote_decimate_by()
 */
#if !defined(_di_f_fss_set_quote_adjust_) || !defined(_di_f_fss_set_quote_decimate_by_)
  extern f_status_t private_f_fss_set_quote_adjust(const f_number_unsigned_t length, f_fss_set_quote_t * const set_quote) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_set_quote_adjust_) || !defined(_di_f_fss_set_quote_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param set_quote
 *   The set_quote to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_string_ranges_resize().
 *   Errors (with error bit) from: f_string_rangess_resize().
 *   Errors (with error bit) from: f_uint8s_resize().
 *   Errors (with error bit) from: f_uint8ss_resize().
 *
 * @see f_string_ranges_resize()
 * @see f_string_rangess_resize()
 * @see f_uint8s_resize()
 * @see f_uint8ss_resize()
 *
 * @see f_fss_set_quote_decrease_by()
 * @see f_fss_set_quote_resize()
 */
#if !defined(_di_f_fss_set_quote_decrease_by_) || !defined(_di_f_fss_set_quote_resize_)
  extern f_status_t private_f_fss_set_quote_resize(const f_number_unsigned_t length, f_fss_set_quote_t * const set_quote) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_set_quote_decrease_by_) || !defined(_di_f_fss_set_quote_resize_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param set_quotes
 *   The set_quotes to adjust.
 *
 * @return
 *   Success from f_memory_array_adjust().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *   Errors (with error bit) from: f_string_ranges_adjust().
 *   Errors (with error bit) from: f_string_rangess_adjust().
 *   Errors (with error bit) from: f_uint8s_adjust().
 *   Errors (with error bit) from: f_uint8ss_adjust().
 *
 * @see f_memory_array_adjust()
 * @see f_string_ranges_adjust()
 * @see f_string_rangess_adjust()
 * @see f_uint8s_adjust()
 * @see f_uint8ss_adjust()
 *
 * @see f_fss_set_quotes_decrease_by()
 * @see f_fss_set_quotes_adjust()
 * @see f_memory_adjust()
 */
#if !defined(_di_f_fss_set_quotes_adjust_) || !defined(_di_f_fss_set_quotes_decimate_by_)
  extern f_status_t private_f_fss_set_quotes_adjust(const f_number_unsigned_t length, f_fss_set_quotes_t * const set_quotes) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_set_quotes_adjust_) || !defined(_di_f_fss_set_quotes_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param set_quotes
 *   The set_quotes to resize.
 *
 * @return
 *   Success from f_memory_array_resize().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *   Errors (with error bit) from: f_string_ranges_adjust().
 *   Errors (with error bit) from: f_string_rangess_adjust().
 *   Errors (with error bit) from: f_uint8s_adjust().
 *   Errors (with error bit) from: f_uint8ss_adjust().
 *
 * @see f_memory_array_resize()
 * @see f_string_ranges_adjust()
 * @see f_string_rangess_adjust()
 * @see f_uint8s_adjust()
 * @see f_uint8ss_adjust()
 *
 * @see f_fss_set_quotes_decrease_by()
 * @see f_fss_set_quotes_resize()
 * @see f_memory_resize()
 */
#if !defined(_di_f_fss_set_quotes_decrease_by_) || !defined(_di_f_fss_set_quotes_resize_)
  extern f_status_t private_f_fss_set_quotes_resize(const f_number_unsigned_t length, f_fss_set_quotes_t * const set_quotes) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_set_quotes_decrease_by_) || !defined(_di_f_fss_set_quotes_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_fss_set_quote_h
