/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines quantity string data.
 *
 * This is auto-included by string.h and should not need to be explicitly included.
 */
#ifndef _F_string_quantity_h
#define _F_string_quantity_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Store string quantity.
 *
 * Similar to f_string_range_t, except total is relative to start and is not an absolute stop position.
 *
 * Two common uses for when total is 0 is:
 * 1) Exactly that, process a total of 0 strings bytes.
 * 2) Process with no limit, aka infinite.
 *
 * start: The position where the string starts (based on some string/buffer).
 * total: The total number of elements within that string/buffer the quantity represents.
 */
#ifndef _di_f_string_quantity_t_
  typedef struct {
    f_number_unsigned_t start;
    f_number_unsigned_t total;
  } f_string_quantity_t;

  #define f_string_quantity_t_initialize { 0, 0 }

  #define macro_f_string_quantity_t_initialize_1(start, total) { start, total }

  #define macro_f_string_quantity_t_clear(quantity) \
    quantity.start = 0; \
    quantity.total = 0;
#endif // _di_f_string_quantity_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_quantity_h
