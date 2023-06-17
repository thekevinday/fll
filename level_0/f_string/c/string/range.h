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
 * start: the start position.
 * stop:  the stop position.
 */
#ifndef _di_f_string_range_t_
  typedef struct {
    f_number_unsigned_t start;
    f_number_unsigned_t stop;
  } f_string_range_t;

  #define f_string_range_t_initialize { 1, 0 }

  #define macro_f_string_range_t_initialize_1(start, stop) { start, stop }
  #define macro_f_string_range_t_initialize_2(length) { length ? 0 : 1, length ? length - 1 : 0 }

  #define macro_f_string_range_t_clear(range) \
    range.start = 1; \
    range.stop = 0;
#endif // _di_f_string_range_t_

/**
 * Provide a static empty range.
 *
 * This is intended to represent an empty or disabled range.
 */
#ifndef _di_f_string_range_empty_c_
  extern const f_string_range_t f_string_range_empty_c;
#endif // _di_f_string_range_empty_c_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_range_h
