/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines nest data to be used for/by project fss.
 *
 * This is auto-included by fss.h and should not need to be explicitly included.
 */
#ifndef _F_fss_item_h
#define _F_fss_item_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This holds a item object and its associated content.
 *
 * Child content represents content nested within some other content and never represents the top-most content.
 *
 * To designate that either object or content is non-existent, set start position greater than stop position.
 * In particular, set start to 1 and stop to 0.
 *
 * This does not have resize/adjust macros due to multiple things to potentially resize.
 * Any resizing must be manually performed on each applicable property.
 *
 * Properties:
 *   - object:  The object.
 *   - content: The content associated with the object.
 *   - parent:  A location referencing a parrent object or content that this object content is nested under.
 */
#ifndef _di_f_fss_item_t_
  typedef struct {
    f_string_range_t object;
    f_string_ranges_t content;

    f_number_unsigned_t parent;
  } f_fss_item_t;

  #define f_fss_item_t_initialize { f_string_range_t_initialize, f_string_ranges_t_initialize, 0 }

  #define macro_f_fss_item_t_initialize_1(object, content, parent) macro_f_number_unsigneds_t_initialize_1(object, content, parent)

  #define macro_f_fss_item_t_clear(item) \
    macro_f_string_range_t_clear(item.object); \
    macro_f_string_ranges_t_clear(item.content); \
    item.parent = 0;

  #define macro_f_fss_item_t_resize(status, item, length) macro_f_string_ranges_t_resize(status, item.content, length)
  #define macro_f_fss_item_t_adjust(status, item, length) macro_f_string_ranges_t_adjust(status, item.content, length)

  #define macro_f_fss_item_t_delete_simple(item)  macro_f_string_ranges_t_delete_simple(item.content)
  #define macro_f_fss_item_t_destroy_simple(item) macro_f_string_ranges_t_destroy_simple(item.content)

  #define macro_f_fss_item_t_increase(status, step, item)      macro_f_string_ranges_t_increase(status, step, item.content)
  #define macro_f_fss_item_t_increase_by(status, item, amount) macro_f_string_ranges_t_increase_by(status, item.content, amount)
  #define macro_f_fss_item_t_decrease_by(status, item, amount) macro_f_string_ranges_t_decrease_by(status, item.content, amount)
  #define macro_f_fss_item_t_decimate_by(status, item, amount) macro_f_string_ranges_t_decimate_by(status, item.content, amount)
#endif // _di_f_fss_item_t_

/**
 * This holds an array of fss_item.
 *
 * This is designed to be used as a part of f_fss_nest_t.
 *
 * For example:
 *   object {
 *     fss_basic_content before nested content.
 *     nested_1 {
 *        Nested content one.
 *     }
 *
 *     More content in between.
 *
 *     nested_2 {
 *        Nested content two.
 *        nested_3 {
 *          Nested content three.
 *        }
 *     }
 *
 *     More content after.
 *   }
 *
 * Properties:
 *   - array: The array of object, their associated content, and their associated parent.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fss_items_t_
  typedef struct {
    f_fss_item_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_fss_items_t;

  #define f_fss_items_t_initialize { 0, 0, 0 }

  #define macro_f_fss_items_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_fss_items_t_initialize_2(array, length)     { array, length, length }

  #define macro_f_fss_items_t_resize(status, items, length) status = f_fss_items_resize(length, &items);
  #define macro_f_fss_items_t_adjust(status, items, length) status = f_fss_items_adjust(length, &items);

  #define macro_f_fss_items_t_delete_simple(items)  f_fss_items_resize(0, &items);
  #define macro_f_fss_items_t_destroy_simple(items) f_fss_items_adjust(0, &items);

  #define macro_f_fss_items_t_increase(status, step, items)      status = f_fss_items_increase(step, &items);
  #define macro_f_fss_items_t_increase_by(status, items, amount) status = f_fss_items_increase_by(amount, &items);
  #define macro_f_fss_items_t_decrease_by(status, items, amount) status = f_fss_items_decrease_by(amount, &items);
  #define macro_f_fss_items_t_decimate_by(status, items, amount) status = f_fss_items_decimate_by(amount, &items);
#endif // _di_f_fss_items_t_

/**
 * Resize the nest array.
 *
 * @param length
 *   The new size to use.
 * @param items
 *   The items array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_items_adjust_
  extern f_status_t f_fss_items_adjust(const f_number_unsigned_t length, f_fss_items_t * const items);
#endif // _di_f_fss_items_adjust_

/**
 * Resize the nest array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param items
 *   The items array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_items_decimate_by_
  extern f_status_t f_fss_items_decimate_by(const f_number_unsigned_t amount, f_fss_items_t * const items);
#endif // _di_f_fss_items_decimate_by_

/**
 * Resize the nest array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param items
 *   The items array to resize.
 *
 * @return
 *   Success from f_memory_array_adjust().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *   Errors (with error bit) from: f_string_dynamic_adjust().
 *
 * @see f_memory_array_adjust()
 * @see f_string_dynamic_adjust()
 */
#ifndef _di_f_fss_items_decrease_by_
  extern f_status_t f_fss_items_decrease_by(const f_number_unsigned_t amount, f_fss_items_t * const items);
#endif // _di_f_fss_items_decrease_by_

/**
 * Increase the size of the items array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param items
 *   The items array to resize.
 *
 * @return
 *   Success from f_memory_array_increase().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase().
 *
 * @see f_memory_array_increase()
 */
#ifndef _di_f_fss_items_increase_
  extern f_status_t f_fss_items_increase(const f_number_unsigned_t step, f_fss_items_t * const items);
#endif // _di_f_fss_items_increase_

/**
 * Resize the items array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param items
 *   The items array to resize.
 *
 * @return
 *   Success from f_memory_array_increase_by().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *
 * @see f_memory_array_increase_by()
 */
#ifndef _di_f_fss_items_increase_by_
  extern f_status_t f_fss_items_increase_by(const f_number_unsigned_t amount, f_fss_items_t * const items);
#endif // _di_f_fss_items_increase_by_

/**
 * Resize the items array.
 *
 * @param length
 *   The new size to use.
 * @param items
 *   The items array to resize.
 *
 * @return
 *   Success from f_memory_array_resize().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_memory_array_resize()
 * @see f_string_dynamic_resize()
 */
#ifndef _di_f_fss_items_resize_
  extern f_status_t f_fss_items_resize(const f_number_unsigned_t length, f_fss_items_t * const items);
#endif // _di_f_fss_items_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_item_h
