/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines range string data.
 *
 * This is auto-included by string.h and should not need to be explicitly included.
 */
#ifndef _F_string_range_double_h
#define _F_string_range_double_h

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
#ifndef _di_f_string_range_double_t_
  typedef struct {
    f_number_unsigned_t start_1;
    f_number_unsigned_t stop_1;
    f_number_unsigned_t start_2;
    f_number_unsigned_t stop_2;
  } f_string_range_double_t;

  #define f_string_range_double_t_initialize { 1, 0, 1, 0 }

  #define macro_f_string_range_double_t_initialize_1(start_1, stop_1, start_2, stop_2) { start_1, stop_1, start_2, stop_2 }
  #define macro_f_string_range_double_t_initialize_2(length_1, length_2) { length_1 ? 0 : 1, length_1 ? length_1 - 1 : 0, length_2 ? 0 : 1, length_2 ? length_2 - 1 : 0 }

  #define macro_f_string_range_double_t_clear(range_1, range_2) \
    range_1.start = 1; \
    range_1.stop = 0 \
    range_2.start = 1; \
    range_2.stop = 0;
#endif // _di_f_string_range_double_t_

/**
 * Provide a static empty range.
 *
 * This is intended to represent an empty or disabled range.
 */
#ifndef _di_f_string_range_double_empty_c_
  extern const f_string_range_double_t f_string_range_double_empty_c;
#endif // _di_f_string_range_double_empty_c_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_range_double_h
