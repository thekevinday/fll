/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines range string data.
 *
 * This is auto-included by string.h and should not need to be explicitly included.
 */
#ifndef _F_string_range_h
#define _F_string_range_h

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
 * A special f_macro_string_range_initialize() is provided for the special purpose of easily initialize a static string range.
 *
 * start: the start position.
 * stop: the stop position.
 */
#ifndef _di_f_string_range_
  typedef struct {
    f_string_length start;
    f_string_length stop;
  } f_string_range;

  #define f_string_range_initialize { 1, 0 }

  #define f_macro_string_range_initialize(length) { 0, length - 1 }

  #define f_macro_string_range_clear(range) \
    range.start = 1; \
    range.stop = 0;
#endif // _di_f_string_range_

/**
 * An array of string ranges.
 *
 * array: the array of string ranges.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_string_ranges_
  typedef struct {
    f_string_range *array;

    f_array_length size;
    f_array_length used;
  } f_string_ranges;

  #define f_string_ranges_initialize {0, 0, 0}

  #define f_macro_string_ranges_clear(ranges) f_macro_memory_structure_clear(ranges)

  #define f_macro_string_ranges_new(status, ranges, length) f_macro_memory_structure_new(status, ranges, f_string_range, length)

  #define f_macro_string_ranges_delete(status, ranges)  f_macro_memory_structure_delete(status, ranges, f_string_range)
  #define f_macro_string_ranges_destroy(status, ranges) f_macro_memory_structure_destroy(status, ranges, f_string_range)

  #define f_macro_string_ranges_delete_simple(ranges)  f_macro_memory_structure_delete_simple(ranges, f_string_range)
  #define f_macro_string_ranges_destroy_simple(ranges) f_macro_memory_structure_destroy_simple(ranges, f_string_range)

  #define f_macro_string_ranges_resize(status, ranges, new_length) f_macro_memory_structure_resize(status, ranges, f_string_range, new_length)
  #define f_macro_string_ranges_adjust(status, ranges, new_length) f_macro_memory_structure_adjust(status, ranges, f_string_range, new_length)
#endif // _di_f_string_ranges_

/**
 * This holds an array of f_string_ranges.
 *
 * array: The array of ranges arrays.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_string_rangess_
  typedef struct {
    f_string_ranges *array;

    f_array_length size;
    f_array_length used;
  } f_string_rangess;

  #define f_string_rangess_initialize { 0, 0, 0 }

  #define f_macro_string_rangess_clear(rangess) f_macro_memory_structures_clear(rangess)

  #define f_macro_string_rangess_new(status, rangess, length) f_macro_memory_structures_new(status, rangess, f_string_ranges, length)

  #define f_macro_string_rangess_delete(status, rangess)  f_macro_memory_structures_delete(status, rangess, f_string_range, f_string_ranges)
  #define f_macro_string_rangess_destroy(status, rangess) f_macro_memory_structures_destroy(status, rangess, f_string_range, f_string_ranges)

  #define f_macro_string_rangess_delete_simple(rangess)  f_macro_memory_structures_delete_simple(rangess, f_string_range, f_string_ranges)
  #define f_macro_string_rangess_destroy_simple(rangess) f_macro_memory_structures_destroy_simple(rangess, f_string_range, f_string_ranges)

  #define f_macro_string_rangess_resize(status, rangess, new_length) f_macro_memory_structures_resize(status, rangess, f_string_range, f_string_ranges, new_length, f_array_length)
  #define f_macro_string_rangess_adjust(status, rangess, new_length) f_macro_memory_structures_adjust(status, rangess, f_string_range, f_string_ranges, new_length, f_array_length)
#endif // _di_f_string_rangess_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_range_h
