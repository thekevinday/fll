/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines set data to be used for/by project fss.
 *
 * This is auto-included by fss.h and should not need to be explicitly included.
 */
#ifndef _F_fss_simple_packet_h
#define _F_fss_simple_packet_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * FSS-000F (Simple Packet) specific defines.
 *
 * F_fss_simple_packet_*_d:
 *   - endian:             The endian bit for a 8-bit type, generally a character, that when set to 1 is big endian and when set to 0 is little endian.
 *   - block_control_size: The size of the Control Block in bytes.
 *   - block_size_size:    The size of the Size Block in bytes.
 *   - block_header_size:  The size of both the Control Block and the Size Block in bytes.
 *   - block_payload_size: The maximum block size of the Payload Block in bytes, which is (2^32)-6.
 */
#ifndef _di_f_fss_simple_packet_d_
  #define F_fss_simple_packet_endian_d 0x80

  #define F_fss_simple_packet_block_control_size_d 1
  #define F_fss_simple_packet_block_size_size_d    4
  #define F_fss_simple_packet_block_header_size_d  5
  #define F_fss_simple_packet_block_payload_size_d 4294967290
#endif // _di_f_fss_simple_packet_d_

/**
 * A structure representing the Simple Packet.
 *
 * Properties:
 *   - control: The Control Block, which is 1 byte long.
 *   - size:    The Size Block, which is 4 bytes long.
 *   - payload: The Payload Block, which is inclusively between 0 and (2^32)-6 bytes long.
 */
#ifndef _di_f_fss_simple_packet_t_
  typedef struct {
    uint8_t control;
    uint32_t size;
    f_string_dynamic_t payload;
  } f_fss_simple_packet_t;

  #define f_fss_simple_packet_t_initialize { \
    0, \
    0, \
    f_string_dynamic_t_initialize, \
  }

  #define macro_f_fss_simple_packet_t_initialize_1(control, size, payload) { \
    control, \
    size, \
    payload, \
  }

  #define macro_f_fss_simple_packet_t_initialize_2(payload) { \
    0, \
    0, \
    payload, \
  }
#endif // _di_f_fss_simple_packet_t_

/**
 * This holds an array of f_fss_simple_packet_t.
 *
 * Properties:
 *   - array: An array of f_fss_simple_packet_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fss_simple_packets_t_
  typedef struct {
    f_fss_simple_packet_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_fss_simple_packets_t;

  #define f_fss_simple_packets_t_initialize { 0, 0, 0 }

  #define macro_f_fss_simple_packets_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_fss_simple_packets_t_initialize_2(array, length) { array, length, length }

  #define macro_f_fss_simple_packets_t_clear(simple_packets) macro_f_memory_structures_clear(simple_packets)
#endif // _di_f_fss_simple_packets_t_

/**
 * This holds an array of f_fss_simple_packets_t.
 *
 * Properties:
 *   - array: An array of f_fss_simple_packets_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fss_simple_packetss_t_
  typedef struct {
    f_fss_simple_packets_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_fss_simple_packetss_t;

  #define f_fss_simple_packetss_t_initialize { 0, 0, 0 }

  #define macro_f_fss_simple_packetss_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_fss_simple_packetss_t_initialize_2(array, length) { array, length, length }

  #define macro_f_fss_simple_packetss_t_clear(simple_packetss) macro_f_memory_structures_clear(simple_packetss)
#endif // _di_f_fss_simple_packetss_t_
/**
 * A set of string ranges intending to designate the different ranges for a Simple Packet representing each Block.
 *
 * Properties:
 *   - control: The Control Block, which is 1 byte long.
 *   - size:    The Size Block, which is 4 bytes long.
 *   - payload: The Payload Block, which is inclusively between 0 and (2^32)-6 bytes long.
 */
#ifndef _di_f_fss_simple_packet_range_t_
  typedef struct {
    f_string_range_t control;
    f_string_range_t size;
    f_string_range_t payload;
  } f_fss_simple_packet_range_t;

  #define f_fss_simple_packet_range_t_initialize { \
    f_string_range_t_initialize, \
    f_string_range_t_initialize, \
    f_string_range_t_initialize, \
  }

  #define macro_f_fss_simple_packet_range_t_initialize_1(control, size, payload) { \
    control, \
    size, \
    payload, \
  }
#endif // _di_f_fss_simple_packet_range_t_

/**
 * This holds an array of f_fss_simple_packet_range_t.
 *
 * Properties:
 *   - array: An array of f_fss_simple_packet_range_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fss_simple_packet_ranges_t_
  typedef struct {
    f_fss_simple_packet_range_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_fss_simple_packet_ranges_t;

  #define f_fss_simple_packet_ranges_t_initialize { 0, 0, 0 }

  #define macro_f_fss_simple_packet_ranges_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_fss_simple_packet_ranges_t_initialize_2(array, length) { array, length, length }

  #define macro_f_fss_simple_packet_ranges_t_clear(simple_packet_ranges) macro_f_memory_structures_clear(simple_packet_ranges)
#endif // _di_f_fss_simple_packet_ranges_t_

/**
 * This holds an array of an array of f_fss_simple_packet_range_t.
 *
 * Properties:
 *   - array: An array of an array of f_fss_simple_packet_range_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fss_simple_packet_rangess_t_
  typedef struct {
    f_fss_simple_packet_ranges_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_fss_simple_packet_rangess_t;

  #define f_fss_simple_packet_rangess_t_initialize { 0, 0, 0 }

  #define macro_f_fss_simple_packet_rangess_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_fss_simple_packet_rangess_t_initialize_2(array, length) { array, length, length }

  #define macro_f_fss_simple_packet_rangess_t_clear(simple_packet_rangess) macro_f_memory_structures_clear(simple_packet_rangess)
#endif // _di_f_fss_simple_packet_rangess_t_

/**
 * Delete a simple packet.
 *
 * @param packet
 *   The simple packet to delete.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_string_dynamic_resize()
 */
#ifndef _di_f_fss_simple_packet_delete_
  extern f_status_t f_fss_simple_packet_delete(f_fss_simple_packet_t * const packet);
#endif // _di_f_fss_simple_packet_delete_

/**
 * Destroy a simple packet.
 *
 * @param packet
 *   The simple packet to destroy.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamic_adjust().
 *
 * @see f_string_dynamic_adjust()
 */
#ifndef _di_f_fss_simple_packet_destroy_
  extern f_status_t f_fss_simple_packet_destroy(f_fss_simple_packet_t * const packet);
#endif // _di_f_fss_simple_packet_destroy_

/**
 * Identify the ranges representing the different parts of the FSS-000F (Simple Packet).
 *
 * @param buffer
 *   The string buffer to identify the packet ranges of.
 *   This buffer is considered binary data and so any NULL found within is treated as a valid part of the buffer.
 * @param range
 *   The set of blocks, each representing a range within the buffer.
 *   If the buffer is too small (including when F_data_not is returned), then the ranges are all set to the out of range values as appropriate.
 *
 * @return
 *   F_okay on success (The end of the Payload Block is assumed to be the remainder of the buffer or F_fss_simple_packet_block_payload_size_d, whichever is smaller).
 *   F_partial on success but not all blocks are identified.
 *   F_data_not if buffer.used is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_valid_not (with error bit) if the data is invalid, which generally only happens when the value of the Size block is less than 5 (and when not returning F_partial).
 */
#ifndef _di_f_fss_simple_packet_identify_
  extern f_status_t f_fss_simple_packet_identify(const f_string_static_t buffer, f_fss_simple_packet_range_t * const range);
#endif // _di_f_fss_simple_packet_identify_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_fss_simple_packets_t structure.
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
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_string_dynamic_resize()
 */
#ifndef _di_f_fss_simple_packets_delete_callback_
  extern f_status_t f_fss_simple_packets_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_fss_simple_packets_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_fss_simple_packets_t structure.
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
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamic_adjust().
 *
 * @see f_string_dynamic_adjust()
 */
#ifndef _di_f_fss_simple_packets_destroy_callback_
  extern f_status_t f_fss_simple_packets_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_fss_simple_packets_destroy_callback_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_fss_simple_packetss_t structure.
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
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_string_dynamic_resize()
 */
#ifndef _di_f_fss_simple_packetss_delete_callback_
  extern f_status_t f_fss_simple_packetss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_fss_simple_packetss_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_fss_simple_packetss_t structure.
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
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamic_adjust().
 *
 * @see f_string_dynamic_adjust()
 */
#ifndef _di_f_fss_simple_packetss_destroy_callback_
  extern f_status_t f_fss_simple_packetss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_fss_simple_packetss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_simple_packet_h
