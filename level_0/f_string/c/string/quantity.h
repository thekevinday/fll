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
    f_array_length_t start;
    f_array_length_t total;
  } f_string_quantity_t;

  #define f_string_quantity_t_initialize { 0, 0 }

  #define macro_f_string_quantity_t_initialize(start, total) { start, total }

  #define macro_f_string_quantity_t_clear(quantity) \
    quantity.start = 0; \
    quantity.total = 0;
#endif // _di_f_string_quantity_t_

/**
 * An array of string quantitys.
 *
 * array: the array of string quantitys.
 * size:  total amount of allocated space.
 * used:  total number of allocated spaces used.
 */
#ifndef _di_f_string_quantitys_t_
  typedef struct {
    f_string_quantity_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_string_quantitys_t;

  #define f_string_quantitys_t_initialize { 0, 0, 0 }

  #define macro_f_string_quantitys_t_initialize(array, size, used) { array, size, used }
  #define macro_f_string_quantitys_t_initialize2(array, length) { array, length, length }

  #define macro_f_string_quantitys_t_clear(quantitys) macro_f_memory_structure_clear(quantitys)

  #define macro_f_string_quantitys_t_resize(status, quantitys, length) status = f_string_quantitys_resize(length, &quantitys);
  #define macro_f_string_quantitys_t_adjust(status, quantitys, length) status = f_string_quantitys_adjust(length, &quantitys);

  #define macro_f_string_quantitys_t_delete_simple(quantitys)  f_string_quantitys_resize(0, &quantitys);
  #define macro_f_string_quantitys_t_destroy_simple(quantitys) f_string_quantitys_adjust(0, &quantitys);

  #define macro_f_string_quantitys_t_increase(status, step, quantitys)      status = f_string_quantitys_increase(step, &quantitys);
  #define macro_f_string_quantitys_t_increase_by(status, quantitys, amount) status = f_string_quantitys_increase_by(amount, &quantitys);
  #define macro_f_string_quantitys_t_decrease_by(status, quantitys, amount) status = f_string_quantitys_decrease_by(amount, &quantitys);
  #define macro_f_string_quantitys_t_decimate_by(status, quantitys, amount) status = f_string_quantitys_decimate_by(amount, &quantitys);
#endif // _di_f_string_quantitys_t_

/**
 * This holds an array of f_string_quantitys_t.
 *
 * array: The array of quantitys arrays.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_string_quantityss_t_
  typedef struct {
    f_string_quantitys_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_string_quantityss_t;

  #define f_string_quantityss_t_initialize { 0, 0, 0 }

  #define macro_f_string_quantityss_t_initialize(array, size, used) { array, size, used }
  #define macro_f_string_quantityss_t_initialize2(array, length) { array, length, length }

  #define macro_f_string_quantityss_t_clear(quantityss) macro_f_memory_structures_clear(quantityss)

  #define macro_f_string_quantityss_t_resize(status, quantityss, length) status = f_string_quantityss_resize(length, &quantityss);
  #define macro_f_string_quantityss_t_adjust(status, quantityss, length) status = f_string_quantityss_adjust(length, &quantityss);

  #define macro_f_string_quantityss_t_delete_simple(quantityss)  f_string_quantityss_resize(0, &quantityss);
  #define macro_f_string_quantityss_t_destroy_simple(quantityss) f_string_quantityss_adjust(0, &quantityss);

  #define macro_f_string_quantityss_t_increase(status, step, quantityss)      status = f_string_quantityss_increase(step, &quantityss);
  #define macro_f_string_quantityss_t_increase_by(status, quantityss, amount) status = f_string_quantityss_increase_by(amount, &quantityss);
  #define macro_f_string_quantityss_t_decrease_by(status, quantityss, amount) status = f_string_quantityss_decrease_by(amount, &quantityss);
  #define macro_f_string_quantityss_t_decimate_by(status, quantityss, amount) status = f_string_quantityss_decimate_by(amount, &quantityss);
#endif // _di_f_string_quantityss_t_

/**
 * Resize the string quantitys array.
 *
 * @param length
 *   The new size to use.
 * @param quantitys
 *   The string quantitys array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantitys_adjust_
  extern f_status_t f_string_quantitys_adjust(const f_array_length_t length, f_string_quantitys_t * const quantitys);
#endif // _di_f_string_quantitys_adjust_

/**
 * Append the single source quantity onto the destination.
 *
 * @param source
 *   The source quantity to append.
 * @param destination
 *   The destination quantitys the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantitys_append_
  extern f_status_t f_string_quantitys_append(const f_string_quantity_t source, f_string_quantitys_t * const destination);
#endif // _di_f_string_quantitys_append_

/**
 * Append the source quantitys onto the destination.
 *
 * @param source
 *   The source quantitys to append.
 * @param destination
 *   The destination quantitys the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantitys_append_all_
  extern f_status_t f_string_quantitys_append_all(const f_string_quantitys_t source, f_string_quantitys_t * const destination);
#endif // _di_f_string_quantitys_append_all_

/**
 * Resize the string quantitys array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param quantitys
 *   The string quantitys array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantitys_decimate_by_
  extern f_status_t f_string_quantitys_decimate_by(const f_array_length_t amount, f_string_quantitys_t * const quantitys);
#endif // _di_f_string_quantitys_decimate_by_

/**
 * Resize the string quantitys array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param quantitys
 *   The string quantitys array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantitys_decrease_by_
  extern f_status_t f_string_quantitys_decrease_by(const f_array_length_t amount, f_string_quantitys_t * const quantitys);
#endif // _di_f_string_quantitys_decrease_by_

/**
 * Increase the size of the string quantitys array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param quantitys
 *   The string quantitys array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantitys_increase_
  extern f_status_t f_string_quantitys_increase(const f_array_length_t step, f_string_quantitys_t * const quantitys);
#endif // _di_f_string_quantitys_increase_

/**
 * Resize the string quantitys array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param quantitys
 *   The string quantitys array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantitys_increase_by_
  extern f_status_t f_string_quantitys_increase_by(const f_array_length_t amount, f_string_quantitys_t * const quantitys);
#endif // _di_f_string_quantitys_increase_by_

/**
 * Resize the string quantitys array.
 *
 * @param length
 *   The new size to use.
 * @param quantitys
 *   The string quantitys array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantitys_resize_
  extern f_status_t f_string_quantitys_resize(const f_array_length_t length, f_string_quantitys_t * const quantitys);
#endif // _di_f_string_quantitys_resize_

/**
 * Resize the string quantityss array.
 *
 * @param length
 *   The new size to use.
 * @param quantityss
 *   The string quantityss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantityss_adjust_
  extern f_status_t f_string_quantityss_adjust(const f_array_length_t length, f_string_quantityss_t * const quantityss);
#endif // _di_f_string_quantityss_adjust_

/**
 * Append the single source quantitys onto the destination.
 *
 * @param source
 *   The source quantitys to append.
 * @param destination
 *   The destination quantityss the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantityss_append_
  extern f_status_t f_string_quantityss_append(const f_string_quantitys_t source, f_string_quantityss_t * const destination);
#endif // _di_f_string_quantityss_append_

/**
 * Append the source quantityss onto the destination.
 *
 * @param source
 *   The source quantityss to append.
 * @param destination
 *   The destination quantityss the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantityss_append_all_
  extern f_status_t f_string_quantityss_append_all(const f_string_quantityss_t source, f_string_quantityss_t * const destination);
#endif // _di_f_string_quantityss_append_all_

/**
 * Resize the string quantityss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param quantityss
 *   The string quantityss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantityss_decimate_by_
  extern f_status_t f_string_quantityss_decimate_by(const f_array_length_t amount, f_string_quantityss_t * const quantityss);
#endif // _di_f_string_quantityss_decimate_by_

/**
 * Resize the string quantityss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param quantityss
 *   The string quantityss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantityss_decrease_by_
  extern f_status_t f_string_quantityss_decrease_by(const f_array_length_t amount, f_string_quantityss_t * const quantityss);
#endif // _di_f_string_quantityss_decrease_by_

/**
 * Increase the size of the string quantityss array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param quantityss
 *   The string quantityss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantityss_increase_
  extern f_status_t f_string_quantityss_increase(const f_array_length_t step, f_string_quantityss_t * const quantityss);
#endif // _di_f_string_quantityss_increase_

/**
 * Resize the string quantityss array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param quantityss
 *   The string quantityss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantityss_increase_by_
  extern f_status_t f_string_quantityss_increase_by(const f_array_length_t amount, f_string_quantityss_t * const quantityss);
#endif // _di_f_string_quantityss_increase_by_

/**
 * Resize the string quantityss array.
 *
 * @param length
 *   The new size to use.
 * @param quantityss
 *   The string quantityss array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantityss_resize_
  extern f_status_t f_string_quantityss_resize(const f_array_length_t length, f_string_quantityss_t * const quantityss);
#endif // _di_f_string_quantityss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_quantity_h
