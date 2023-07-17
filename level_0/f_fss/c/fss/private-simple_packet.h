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
#ifndef _PRIVATE_F_fss_simple_packet_h
#define _PRIVATE_F_fss_simple_packet_h

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
 * @param simple_packet_ranges
 *   The simple_packet_ranges to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: macro_f_string_rangess_t_adjust().
 *   Errors (with error bit) from: macro_f_string_ranges_t_adjust().
 *   Errors (with error bit) from: macro_f_uint8s_t_adjust().
 *   Errors (with error bit) from: macro_f_uint8ss_t_adjust().
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see macro_f_string_rangess_t_adjust()
 * @see macro_f_string_ranges_t_adjust()
 * @see macro_f_uint8s_t_adjust()
 * @see macro_f_uint8ss_t_adjust()
 *
 * @see f_fss_simple_packet_ranges_adjust()
 * @see f_fss_simple_packet_ranges_decimate_by()
 * @see f_memory_adjust()
 */
#if !defined(_di_f_fss_simple_packet_ranges_adjust_) || !defined(_di_f_fss_simple_packet_ranges_decimate_by_)
  extern f_status_t private_f_fss_simple_packet_ranges_adjust(const f_number_unsigned_t length, f_fss_simple_packet_ranges_t * const simple_packet_ranges) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_simple_packet_ranges_adjust_) || !defined(_di_f_fss_simple_packet_ranges_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param simple_packet_ranges
 *   The simple_packet_ranges to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: macro_f_string_rangess_t_resize().
 *   Errors (with error bit) from: macro_f_string_ranges_t_resize().
 *   Errors (with error bit) from: macro_f_uint8s_t_resize().
 *   Errors (with error bit) from: macro_f_uint8ss_t_resize().
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see macro_f_string_rangess_t_resize()
 * @see macro_f_string_ranges_t_resize()
 * @see macro_f_uint8s_t_resize()
 * @see macro_f_uint8ss_t_resize()
 *
 * @see f_fss_simple_packet_ranges_decrease_by()
 * @see f_fss_simple_packet_ranges_increase()
 * @see f_fss_simple_packet_ranges_increase_by()
 * @see f_fss_simple_packet_ranges_resize()
 * @see f_memory_resize()
 */
#if !defined(_di_f_fss_simple_packet_ranges_decrease_by_) || !defined(_di_f_fss_simple_packet_ranges_increase_) || !defined(_di_f_fss_simple_packet_ranges_increase_by_) || !defined(_di_f_fss_simple_packet_ranges_resize_)
  extern f_status_t private_f_fss_simple_packet_ranges_resize(const f_number_unsigned_t length, f_fss_simple_packet_ranges_t * const simple_packet_ranges) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_simple_packet_ranges_decrease_by_) || !defined(_di_f_fss_simple_packet_ranges_increase_) || !defined(_di_f_fss_simple_packet_ranges_increase_by_) || !defined(_di_f_fss_simple_packet_ranges_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_fss_simple_packet_h
