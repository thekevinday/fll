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
    f_string_length_t start;
    f_string_length_t total;
  } f_string_quantity_t;

  #define f_string_quantity_t_initialize { 0, 0 }
#endif // _di_f_string_quantity_t_

/**
 * An array of string quantities.
 *
 * array: the array of string quantities.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_string_quantitys_t_
  typedef struct {
    f_string_quantity_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_string_quantitys_t;

  #define f_string_quantitys_t_initialize {0, 0, 0}

  #define f_macro_string_quantitys_t_clear(quantitys) f_macro_memory_structure_clear(quantitys);

  #define f_macro_string_quantitys_t_new(status, quantitys, length) f_macro_memory_structure_new(status, quantitys, f_string_quantity_t, length);

  #define f_macro_string_quantitys_t_resize(status, quantitys, length) f_macro_memory_structure_resize(status, quantitys, f_string_quantity_t, length);
  #define f_macro_string_quantitys_t_adjust(status, quantitys, length) f_macro_memory_structure_adjust(status, quantitys, f_string_quantity_t, length);

  #define f_macro_string_quantitys_t_delete(status, quantitys)  f_macro_memory_structure_delete(status, quantitys, f_string_quantity_t);
  #define f_macro_string_quantitys_t_destroy(status, quantitys) f_macro_memory_structure_destroy(status, quantitys, f_string_quantity_t);

  #define f_macro_string_quantitys_t_delete_simple(quantitys)  f_macro_memory_structure_delete_simple(quantitys, f_string_quantity_t);
  #define f_macro_string_quantitys_t_destroy_simple(quantitys) f_macro_memory_structure_destroy_simple(quantitys, f_string_quantity_t);

  #define f_macro_string_quantitys_t_increase(status, quantitys) f_macro_memory_structure_increase(status, quantitys, f_string_quantity_t);
  #define f_macro_string_quantitys_t_decrease(status, quantitys) f_macro_memory_structure_decrease(status, quantitys, f_string_quantity_t);
  #define f_macro_string_quantitys_t_decimate(status, quantitys) f_macro_memory_structure_decimate(status, quantitys, f_string_quantity_t);

  #define f_macro_string_quantitys_t_increase_by(status, quantitys, amount) f_macro_memory_structure_increase_by(status, quantitys, f_string_quantity_t, amount);
  #define f_macro_string_quantitys_t_decrease_by(status, quantitys, amount) f_macro_memory_structure_decrease_by(status, quantitys, f_string_quantity_t, amount);
  #define f_macro_string_quantitys_t_decimate_by(status, quantitys, amount) f_macro_memory_structure_decimate_by(status, quantitys, f_string_quantity_t, amount);
#endif // _di_f_string_quantitys_t_

/**
 * This holds an array of f_string_quantity_t.
 *
 * array: the array of quantitys arrays.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_string_quantityss_t_
  typedef struct {
    f_string_quantity_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_string_quantityss_t;

  #define f_string_quantityss_t_initialize {0, 0, 0}

  #define f_macro_string_quantityss_t_clear(quantityss) f_macro_memory_structures_clear(quantityss)

  #define f_macro_string_quantityss_t_new(status, quantityss, length) f_macro_memory_structures_new(status, quantityss, f_string_quantity_t, length);

  #define f_macro_string_quantityss_t_resize(status, quantityss, length) f_macro_memory_structures_resize(status, quantityss, f_string_quantity_t, f_string_quantitys_t, length, f_array_length_t);
  #define f_macro_string_quantityss_t_adjust(status, quantityss, length) f_macro_memory_structures_adjust(status, quantityss, f_string_quantity_t, f_string_quantitys_t, length, f_array_length_t);

  #define f_macro_string_quantityss_t_delete(status, quantityss)  f_macro_memory_structures_delete(status, quantityss, f_string_quantity_t, f_string_quantitys_t);
  #define f_macro_string_quantityss_t_destroy(status, quantityss) f_macro_memory_structures_destroy(status, quantityss, f_string_quantity_t, f_string_quantitys_t);

  #define f_macro_string_quantityss_t_delete_simple(quantityss)  f_macro_memory_structures_delete_simple(quantityss, f_string_quantity_t, f_string_quantitys_t);
  #define f_macro_string_quantityss_t_destroy_simple(quantityss) f_macro_memory_structures_destroy_simple(quantityss, f_string_quantity_t, f_string_quantitys_t);
#endif // _di_f_string_quantityss_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_quantity_h
