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
#ifndef _di_f_string_range_t_
  typedef struct {
    f_string_length_t start;
    f_string_length_t stop;
  } f_string_range_t;

  #define f_string_range_initialize { 1, 0 }

  #define f_macro_string_range_initialize(length) { length ? 0 : 1, length ? length - 1 : 0 }

  #define f_macro_string_range_clear(range) \
    range.start = 1; \
    range.stop = 0;
#endif // _di_f_string_range_t_

/**
 * An array of string ranges.
 *
 * array: the array of string ranges.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_string_ranges_t_
  typedef struct {
    f_string_range_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_string_ranges_t;

  #define f_string_ranges_t_initialize {0, 0, 0}

  #define f_macro_string_ranges_t_clear(ranges) f_macro_memory_structure_t_clear(ranges)

  #define f_macro_string_ranges_t_new(status, ranges, length) f_macro_memory_structure_t_new(status, ranges, f_string_range_t, length)

  #define f_macro_string_ranges_t_delete(status, ranges)  f_macro_memory_structure_t_delete(status, ranges, f_string_range_t)
  #define f_macro_string_ranges_t_destroy(status, ranges) f_macro_memory_structure_t_destroy(status, ranges, f_string_range_t)

  #define f_macro_string_ranges_t_delete_simple(ranges)  f_macro_memory_structure_t_delete_simple(ranges, f_string_range_t)
  #define f_macro_string_ranges_t_destroy_simple(ranges) f_macro_memory_structure_t_destroy_simple(ranges, f_string_range_t)

  #define f_macro_string_ranges_t_resize(status, ranges, new_length) f_macro_memory_structure_t_resize(status, ranges, f_string_range_t, new_length)
  #define f_macro_string_ranges_t_adjust(status, ranges, new_length) f_macro_memory_structure_t_adjust(status, ranges, f_string_range_t, new_length)
#endif // _di_f_string_ranges_t_

/**
 * This holds an array of f_string_ranges_t.
 *
 * array: The array of ranges arrays.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_string_rangess_t_
  typedef struct {
    f_string_ranges_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_string_rangess_t;

  #define f_string_rangess_t_initialize { 0, 0, 0 }

  #define f_macro_string_rangess_t_clear(rangess) f_macro_memory_structures_t_clear(rangess)

  #define f_macro_string_rangess_t_new(status, rangess, length) f_macro_memory_structures_t_new(status, rangess, f_string_ranges_t, length)

  #define f_macro_string_rangess_t_delete(status, rangess)  f_macro_memory_structures_t_delete(status, rangess, f_string_range_t, f_string_ranges_t)
  #define f_macro_string_rangess_t_destroy(status, rangess) f_macro_memory_structures_t_destroy(status, rangess, f_string_range_t, f_string_ranges_t)

  #define f_macro_string_rangess_t_delete_simple(rangess)  f_macro_memory_structures_t_delete_simple(rangess, f_string_range_t, f_string_ranges_t)
  #define f_macro_string_rangess_t_destroy_simple(rangess) f_macro_memory_structures_t_destroy_simple(rangess, f_string_range_t, f_string_ranges_t)

  #define f_macro_string_rangess_t_resize(status, rangess, new_length) f_macro_memory_structures_t_resize(status, rangess, f_string_range_t, f_string_ranges_t, new_length, f_array_length_t)
  #define f_macro_string_rangess_t_adjust(status, rangess, new_length) f_macro_memory_structures_t_adjust(status, rangess, f_string_range_t, f_string_ranges_t, new_length, f_array_length_t)
#endif // _di_f_string_rangess_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_range_h
