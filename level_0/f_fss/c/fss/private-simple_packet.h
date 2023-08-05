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
 * Private implementation for appending the range array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source range to append.
 * @param destination
 *   The destination lengths the source is appended onto.
 *
 * @return
 *   Success from f_memory_array_increase().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase().
 *
 * @see f_memory_array_increase()
 *
 * @see f_fss_simple_packet_ranges_append()
 * @see f_fss_simple_packet_rangess_append()
 */
#if !defined(_di_f_fss_simple_packet_ranges_append_) || !defined(_di_f_fss_simple_packet_rangess_append_)
  extern f_status_t private_f_fss_simple_packet_ranges_append(const f_fss_simple_packet_range_t source, f_fss_simple_packet_ranges_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_simple_packet_ranges_append_) || !defined(_di_f_fss_simple_packet_rangess_append_)

/**
 * Private implementation for appending the range array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source ranges to append.
 * @param destination
 *   The destination lengths the source is appended onto.
 *
 * @return
 *   Success from f_memory_array_increase_by().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *
 * @see f_memory_array_increase_by()
 *
 * @see f_fss_simple_packet_ranges_append_all()
 * @see f_fss_simple_packet_rangess_append()
 * @see f_fss_simple_packet_rangess_append_all()
 */
#if !defined(_di_f_fss_simple_packet_ranges_append_) || !defined(_di_f_fss_simple_packet_ranges_append_all_) || !defined(_di_f_fss_simple_packet_rangess_append_all_)
  extern f_status_t private_f_fss_simple_packet_ranges_append_all(const f_fss_simple_packet_ranges_t source, f_fss_simple_packet_ranges_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_simple_packet_ranges_append_) || !defined(_di_f_fss_simple_packet_ranges_append_all_) || !defined(_di_f_fss_simple_packet_rangess_append_all_)

/**
 * Private implementation for resizing the rangess array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param rangess
 *   The rangess array to adjust.
 *
 * @return
 *   Success from f_memory_array_adjust().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *
 * @see f_memory_array_adjust()
 *
 * @see f_fss_simple_packet_rangess_decrease_by()
 * @see f_fss_simple_packet_rangess_adjust()
 */
#if !defined(_di_f_fss_simple_packet_rangess_adjust_) || !defined(_di_f_fss_simple_packet_rangess_decimate_by_)
  extern f_status_t private_f_fss_simple_packet_rangess_adjust(const f_number_unsigned_t length, f_fss_simple_packet_rangess_t *rangess) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_simple_packet_rangess_adjust_) || !defined(_di_f_fss_simple_packet_rangess_decimate_by_)

/**
 * Private implementation for resizing the rangess array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param rangess
 *   The rangess array to resize.
 *
 * @return
 *   Success from f_memory_array_resize().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 *
 * @see f_fss_simple_packet_rangess_decrease_by()
 * @see f_fss_simple_packet_rangess_resize()
 */
#if !defined(_di_f_fss_simple_packet_rangess_decrease_by_) || !defined(_di_f_fss_simple_packet_rangess_resize_)
  extern f_status_t private_f_fss_simple_packet_rangess_resize(const f_number_unsigned_t length, f_fss_simple_packet_rangess_t *rangess) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_simple_packet_rangess_decrease_by_) || !defined(_di_f_fss_simple_packet_rangess_resize_)

/**
 * Private implementation for resizing the simple packet array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param packets
 *   The simple packet array to adjust.
 *
 * @return
 *   Success from f_memory_array_adjust().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *
 * @see f_memory_array_adjust()
 *
 * @see f_fss_simple_packets_decrease_by()
 * @see f_fss_simple_packets_adjust()
 */
#if !defined(_di_f_fss_simple_packets_adjust_) || !defined(_di_f_fss_simple_packets_decimate_by_)
  extern f_status_t private_f_fss_simple_packets_adjust(const f_number_unsigned_t length, f_fss_simple_packets_t *packets) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_simple_packets_adjust_) || !defined(_di_f_fss_simple_packets_decimate_by_)

/**
 * Private implementation for appending the simple packet array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source simple packet to append.
 * @param destination
 *   The destination lengths the source is appended onto.
 *
 * @return
 *   Success from f_memory_array_increase().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase().
 *
 * @see f_memory_array_increase()
 *
 * @see f_fss_simple_packets_append()
 * @see f_fss_simple_packetss_append()
 */
#if !defined(_di_f_fss_simple_packets_append_) || !defined(_di_f_fss_simple_packetss_append_)
  extern f_status_t private_f_fss_simple_packets_append(const f_fss_simple_packet_t source, f_fss_simple_packets_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_simple_packets_append_) || !defined(_di_f_fss_simple_packetss_append_)

/**
 * Private implementation for appending the simple packet array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source simple packets to append.
 * @param destination
 *   The destination lengths the source is appended onto.
 *
 * @return
 *   Success from f_memory_array_increase_by().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *
 * @see f_memory_array_increase_by()
 *
 * @see f_fss_simple_packets_append_all()
 * @see f_fss_simple_packetss_append()
 * @see f_fss_simple_packetss_append_all()
 */
#if !defined(_di_f_fss_simple_packets_append_) || !defined(_di_f_fss_simple_packets_append_all_) || !defined(_di_f_fss_simple_packetss_append_all_)
  extern f_status_t private_f_fss_simple_packets_append_all(const f_fss_simple_packets_t source, f_fss_simple_packets_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_simple_packets_append_) || !defined(_di_f_fss_simple_packets_append_all_) || !defined(_di_f_fss_simple_packetss_append_all_)

/**
 * Private implementation for resizing the simple packet array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param packets
 *   The simple packet array to resize.
 *
 * @return
 *   Success from f_memory_array_resize().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 *
 * @see f_fss_simple_packets_decrease_by()
 * @see f_fss_simple_packets_resize()
 */
#if !defined(_di_f_fss_simple_packets_decrease_by_) || !defined(_di_f_fss_simple_packets_resize_)
  extern f_status_t private_f_fss_simple_packets_resize(const f_number_unsigned_t length, f_fss_simple_packets_t *packets) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_simple_packets_decrease_by_) || !defined(_di_f_fss_simple_packets_resize_)

/**
 * Private implementation for resizing the simple packets array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param packetss
 *   The simple packets array to adjust.
 *
 * @return
 *   Success from f_memory_array_adjust().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *
 * @see f_memory_array_adjust()
 *
 * @see f_fss_simple_packetss_decrease_by()
 * @see f_fss_simple_packetss_adjust()
 */
#if !defined(_di_f_fss_simple_packetss_adjust_) || !defined(_di_f_fss_simple_packetss_decimate_by_)
  extern f_status_t private_f_fss_simple_packetss_adjust(const f_number_unsigned_t length, f_fss_simple_packetss_t *packetss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_simple_packetss_adjust_) || !defined(_di_f_fss_simple_packetss_decimate_by_)

/**
 * Private implementation for resizing the simple packets array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param packetss
 *   The simple packets array to resize.
 *
 * @return
 *   Success from f_memory_array_resize().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 *
 * @see f_fss_simple_packetss_decrease_by()
 * @see f_fss_simple_packetss_resize()
 */
#if !defined(_di_f_fss_simple_packetss_decrease_by_) || !defined(_di_f_fss_simple_packetss_resize_)
  extern f_status_t private_f_fss_simple_packetss_resize(const f_number_unsigned_t length, f_fss_simple_packetss_t *packetss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_simple_packetss_decrease_by_) || !defined(_di_f_fss_simple_packetss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_fss_simple_packet_h
