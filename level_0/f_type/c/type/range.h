/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines range type data.
 *
 * This is auto-included by type.h and should not need to be explicitly included.
 */
#ifndef _F_range_h
#define _F_range_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A structure designating a start and stop range for some string.
 *
 * In general, this project uses the start and stop position inclusively, meaning that a range of 0 to 1 would include positions 0 and position 1.
 * Therefore, a range from 0 to 0 would be include position 0.
 * Set start to some value larger than stop to designate that there is no range (such as start = 1, stop = 0).
 *
 * Properties:
 *   - start: The start position.
 *   - stop:  The stop position.
 */
#ifndef _di_f_range_t_
  typedef struct {
    f_number_unsigned_t start;
    f_number_unsigned_t stop;
  } f_range_t;

  #define f_range_t_initialize { 1, 0 }

  #define macro_f_range_t_initialize_1(start, stop) { start, stop }
  #define macro_f_range_t_initialize_2(length) { length ? 0 : 1, length ? length - 1 : 0 }

  #define macro_f_range_t_clear(range) \
    range.start = 1; \
    range.stop = 0;
#endif // _di_f_range_t_

/**
 * An array of ranges.
 *
 * Properties:
 *   - array: The array of ranges.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_ranges_t_
  typedef struct {
    f_range_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_ranges_t;

  #define f_ranges_t_initialize { 0, 0, 0 }

  #define macro_f_ranges_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_ranges_t_initialize_2(array, length) { array, length, length }

  #define macro_f_ranges_t_clear(ranges) \
    ranges.array = 0; \
    ranges.size = 0; \
    ranges.used = 0;
#endif // _di_f_ranges_t_

/**
 * This holds an array of f_ranges_t.
 *
 * Properties:
 *   - array: The array of ranges arrays.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_rangess_t_
  typedef struct {
    f_ranges_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_rangess_t;

  #define f_rangess_t_initialize { 0, 0, 0 }

  #define macro_f_rangess_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_rangess_t_initialize_2(array, length) { array, length, length }

  #define macro_f_rangess_t_clear(rangess) \
    rangess.array = 0; \
    rangess.size = 0; \
    rangess.used = 0;
#endif // _di_f_rangess_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_range_h
