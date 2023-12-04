/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines data to be used for/by type (array) related functionality.
 *
 * This is auto-included by type_array.h and should not need to be explicitly included.
 */
#ifndef _F_range_double_h
#define _F_range_double_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A structure designating two start and stop ranges for some string(s).
 *
 * In general, this project uses the start and stop position inclusively, meaning that a range of 0 to 1 would include positions 0 and position 1.
 * Therefore, a range from 0 to 0 would be include position 0.
 * Set start to some value larger than stop to designate that there is no range (such as start = 1, stop = 0).
 *
 * Properties:
 *   - start_1: The first start position.
 *   - stop_1:  The first stop position.
 *   - start_2: The second start position.
 *   - stop_2:  The second stop position.
 */
#ifndef _di_f_range_double_t_
  typedef struct {
    f_number_unsigned_t start_1;
    f_number_unsigned_t stop_1;
    f_number_unsigned_t start_2;
    f_number_unsigned_t stop_2;
  } f_range_double_t;

  #define f_range_double_t_initialize { 1, 0, 1, 0 }

  #define macro_f_range_double_t_initialize_1(start_1, stop_1, start_2, stop_2) { start_1, stop_1, start_2, stop_2 }
  #define macro_f_range_double_t_initialize_2(length_1, length_2) { length_1 ? 0 : 1, length_1 ? length_1 - 1 : 0, length_2 ? 0 : 1, length_2 ? length_2 - 1 : 0 }

  #define macro_f_range_double_t_clear(range_1, range_2) \
    range_1.start = 1; \
    range_1.stop = 0 \
    range_2.start = 1; \
    range_2.stop = 0;
#endif // _di_f_range_double_t_

/**
 * An array of ranges.
 *
 * Properties:
 *   - array: The array of ranges.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_range_doubles_t_
  typedef struct {
    f_range_double_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_range_doubles_t;

  #define f_range_doubles_t_initialize { 0, 0, 0 }

  #define macro_f_range_doubles_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_range_doubles_t_initialize_2(array, length) { array, length, length }

  #define macro_f_range_doubles_t_clear(ranges) \
    ranges.array = 0; \
    ranges.size = 0; \
    ranges.used = 0;
#endif // _di_f_range_doubles_t_

/**
 * This holds an array of f_range_doubles_t.
 *
 * Properties:
 *   - array: The array of ranges arrays.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_range_doubless_t_
  typedef struct {
    f_range_doubles_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_range_doubless_t;

  #define f_range_doubless_t_initialize { 0, 0, 0 }

  #define macro_f_range_doubless_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_range_doubless_t_initialize_2(array, length) { array, length, length }

  #define macro_f_range_doubless_t_clear(rangess) \
    rangess.array = 0; \
    rangess.size = 0; \
    rangess.used = 0;
#endif // _di_f_range_doubless_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_range_double_h
