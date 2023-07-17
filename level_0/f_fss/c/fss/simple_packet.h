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

  #define macro_f_fss_simple_packet_ranges_t_clear(simple_packet_ranges) macro_f_memory_structure_t_clear(simple_packet_range.objects)

  #define macro_f_fss_simple_packet_ranges_t_resize(status, simple_packet_ranges, length) status = f_fss_simple_packet_ranges_resize(length, &simple_packet_ranges);
  #define macro_f_fss_simple_packet_ranges_t_adjust(status, simple_packet_ranges, length) status = f_fss_simple_packet_ranges_adjust(length, &simple_packet_ranges);

  #define macro_f_fss_simple_packet_ranges_t_delete_simple(simple_packet_ranges)  f_fss_simple_packet_ranges_resize(0, &simple_packet_ranges);
  #define macro_f_fss_simple_packet_ranges_t_destroy_simple(simple_packet_ranges) f_fss_simple_packet_ranges_adjust(0, &simple_packet_ranges);

  #define macro_f_fss_simple_packet_ranges_t_increase(status, step, simple_packet_ranges)      status = f_fss_simple_packet_ranges_increase(step, &simple_packet_ranges);
  #define macro_f_fss_simple_packet_ranges_t_increase_by(status, simple_packet_ranges, amount) status = f_fss_simple_packet_ranges_increase_by(amount, &simple_packet_ranges);
  #define macro_f_fss_simple_packet_ranges_t_decrease_by(status, simple_packet_ranges, amount) status = f_fss_simple_packet_ranges_decrease_by(amount, &simple_packet_ranges);
  #define macro_f_fss_simple_packet_ranges_t_decimate_by(status, simple_packet_ranges, amount) status = f_fss_simple_packet_ranges_decimate_by(amount, &simple_packet_ranges);
#endif // _di_f_fss_simple_packet_ranges_t_

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
 *   F_none on success (The end of the Payload Block is assumed to be the remainder of the buffer or F_fss_simple_packet_block_payload_size_d, whichever is smaller).
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
 * Resize the simple_packet_range array.
 *
 * @param length
 *   The new size to use.
 * @param simple_packet_ranges
 *   The simple_packet_ranges array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_simple_packet_ranges_adjust_
  extern f_status_t f_fss_simple_packet_ranges_adjust(const f_number_unsigned_t length, f_fss_simple_packet_ranges_t * const simple_packet_ranges);
#endif // _di_f_fss_simple_packet_ranges_adjust_

/**
 * Resize the simple_packet_range array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param simple_packet_ranges
 *   The simple_packet_ranges array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_simple_packet_ranges_decimate_by_
  extern f_status_t f_fss_simple_packet_ranges_decimate_by(const f_number_unsigned_t amount, f_fss_simple_packet_ranges_t * const simple_packet_ranges);
#endif // _di_f_fss_simple_packet_ranges_decimate_by_

/**
 * Resize the simple_packet_range array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param simple_packet_ranges
 *   The simple_packet_ranges array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_simple_packet_ranges_decrease_by_
  extern f_status_t f_fss_simple_packet_ranges_decrease_by(const f_number_unsigned_t amount, f_fss_simple_packet_ranges_t * const simple_packet_ranges);
#endif // _di_f_fss_simple_packet_ranges_decrease_by_

/**
 * Increase the size of the simple_packet_ranges array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param simple_packet_ranges
 *   The simple_packet_ranges array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_simple_packet_ranges_increase_
  extern f_status_t f_fss_simple_packet_ranges_increase(const f_number_unsigned_t step, f_fss_simple_packet_ranges_t * const simple_packet_ranges);
#endif // _di_f_fss_simple_packet_ranges_increase_

/**
 * Resize the simple_packet_ranges array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param simple_packet_ranges
 *   The simple_packet_ranges array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
 */
#ifndef _di_f_fss_simple_packet_ranges_increase_by_
  extern f_status_t f_fss_simple_packet_ranges_increase_by(const f_number_unsigned_t amount, f_fss_simple_packet_ranges_t * const simple_packet_ranges);
#endif // _di_f_fss_simple_packet_ranges_increase_by_

/**
 * Resize the simple_packet_ranges array.
 *
 * @param length
 *   The new size to use.
 * @param simple_packet_ranges
 *   The simple_packet_ranges array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_simple_packet_ranges_resize_
  extern f_status_t f_fss_simple_packet_ranges_resize(const f_number_unsigned_t length, f_fss_simple_packet_ranges_t * const simple_packet_ranges);
#endif // _di_f_fss_simple_packet_ranges_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_simple_packet_h
