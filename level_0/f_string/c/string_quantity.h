/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.5
 * Licenses: lgplv2.1
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
 * Similar to f_string_range, except total is relative to start and is not an absolute stop position.
 *
 * Two common uses for when total is 0 is:
 * 1) Exactly that, process a total of 0 strings bytes.
 * 2) Process with no limit, aka infinite.
 *
 * start: The position where the string starts (based on some string/buffer).
 * total: The total number of elements within that string/buffer the quantity represents.
 */
#ifndef _di_f_string_quantity_
  typedef struct {
    f_string_length start;
    f_string_length total;
  } f_string_quantity;

  #define f_string_quantity_initialize { 0, 0 }
#endif // _di_f_string_quantity_

/**
 * An array of string quantities.
 *
 * array: the array of string quantities.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_string_quantitys_
  typedef struct {
    f_string_quantity *array;

    f_array_length size;
    f_array_length used;
  } f_string_quantitys;

  #define f_string_quantitys_initialize {0, 0, 0}

  #define f_macro_string_quantitys_clear(quantitys) f_macro_memory_structure_clear(quantitys)

  #define f_macro_string_quantitys_new(status, quantitys, length) f_macro_memory_structure_new(status, quantitys, f_string_quantity, length)

  #define f_macro_string_quantitys_delete(status, quantitys)  f_macro_memory_structure_delete(status, quantitys, f_string_quantity)
  #define f_macro_string_quantitys_destroy(status, quantitys) f_macro_memory_structure_destroy(status, quantitys, f_string_quantity)

  #define f_macro_string_quantitys_delete_simple(quantitys)  f_macro_memory_structure_delete_simple(quantitys, f_string_quantity)
  #define f_macro_string_quantitys_destroy_simple(quantitys) f_macro_memory_structure_destroy_simple(quantitys, f_string_quantity)

  #define f_macro_string_quantitys_resize(status, quantitys, new_length) f_macro_memory_structure_resize(status, quantitys, f_string_quantity, new_length)
  #define f_macro_string_quantitys_adjust(status, quantitys, new_length) f_macro_memory_structure_adjust(status, quantitys, f_string_quantity, new_length)
#endif // _di_f_string_quantitys_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_quantity_h
