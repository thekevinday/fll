/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines quantity type data.
 *
 * This is auto-included by type.h and should not need to be explicitly included.
 */
#ifndef _F_quantity_h
#define _F_quantity_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Store quantity range based on a start position and a total.
 *
 * Similar to f_range_t, except total is relative to start and is not an absolute stop position.
 *
 * Two common uses for when total is 0 is:
 * 1) Exactly that, process a total of 0 strings bytes.
 * 2) Process with no limit, aka infinite.
 *
 * Properties:
 *   - start: The position where the string starts (based on some string/buffer).
 *   - total: The total number of elements within that string/buffer the quantity represents.
 */
#ifndef _di_f_quantity_t_
  typedef struct {
    f_number_unsigned_t start;
    f_number_unsigned_t total;
  } f_quantity_t;

  #define f_quantity_t_initialize { 0, 0 }

  #define macro_f_quantity_t_initialize_1(start, total) { start, total }

  #define macro_f_quantity_t_clear(quantity) \
    quantity.start = 0; \
    quantity.total = 0;
#endif // _di_f_quantity_t_

/**
 * An array of quantitys.
 *
 * Properties:
 *   - array: The array of quantitys.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_quantitys_t_
  typedef struct {
    f_quantity_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_quantitys_t;

  #define f_quantitys_t_initialize { 0, 0, 0 }

  #define macro_f_quantitys_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_quantitys_t_initialize_2(array, length) { array, length, length }

  #define macro_f_quantitys_t_clear(quantitys) \
    quantitys.array = 0; \
    quantitys.size = 0; \
    quantitys.used = 0;
#endif // _di_f_quantitys_t_

/**
 * This holds an array of f_quantitys_t.
 *
 * Properties:
 *   - array: The array of quantitys arrays.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_quantityss_t_
  typedef struct {
    f_quantitys_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_quantityss_t;

  #define f_quantityss_t_initialize { 0, 0, 0 }

  #define macro_f_quantityss_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_quantityss_t_initialize_2(array, length) { array, length, length }

  #define macro_f_quantityss_t_clear(quantityss) \
    quantityss.array = 0; \
    quantityss.size = 0; \
    quantityss.used = 0;
#endif // _di_f_quantityss_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_quantity_h
