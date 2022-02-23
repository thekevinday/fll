/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Defines nest data to be used for/by project fss.
 *
 * This is auto-included by fss.h and should not need to be explicitly included.
 */
#ifndef _F_fss_nest_h
#define _F_fss_nest_h

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
 * object:  The object.
 * content: The content associated with the object.
 * parent:  A location referencing a parrent object or content that this object content is nested under.
 */
#ifndef _di_f_fss_item_t_
  typedef struct {
    f_fss_object_t object;
    f_fss_content_t content;

    f_array_length_t parent;
  } f_fss_item_t;

  #define f_fss_item_t_initialize { f_fss_object_t_initialize, f_fss_content_t_initialize, 0 }

  #define macro_f_fss_item_t_clear(item) \
    macro_f_fss_object_t_clear(item.object); \
    macro_f_fss_content_t_clear(item.content); \
    item.parent = 0;

  #define macro_f_fss_item_t_resize(status, item, length) macro_f_fss_content_t_resize(status, item.content, length)
  #define macro_f_fss_item_t_adjust(status, item, length) macro_f_fss_content_t_adjust(status, item.content, length)

  #define macro_f_fss_item_t_delete_simple(item)  macro_f_fss_content_t_delete_simple(item.content)
  #define macro_f_fss_item_t_destroy_simple(item) macro_f_fss_content_t_destroy_simple(item.content)

  #define macro_f_fss_item_t_increase(status, step, item)      macro_f_fss_content_t_increase(status, step, item.content)
  #define macro_f_fss_item_t_increase_by(status, item, amount) macro_f_fss_content_t_increase_by(status, item.content, amount)
  #define macro_f_fss_item_t_decrease_by(status, item, amount) macro_f_fss_content_t_decrease_by(status, item.content, amount)
  #define macro_f_fss_item_t_decimate_by(status, item, amount) macro_f_fss_content_t_decimate_by(status, item.content, amount)
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
 * array: The array of object, their associated content, and their associated parent.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fss_items_t_
  typedef struct {
    f_fss_item_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_fss_items_t;

  #define f_fss_items_t_initialize { 0, 0, 0 }

  #define macro_f_fss_items_t_clear(items) macro_f_memory_structure_clear(items)

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
 * This holds an array of f_fss_items_t.
 *
 * Each array row represents the nesting depth.
 * The top-level will not have any parent, so "parent" must be ignored on anything at index 0.
 * The parent identifier is expected to reference a position in the nesting depth immediately above it.
 * @todo consider instead of using a "parent", have setting set to 0 to represent no data.
 *
 * depth: An array of f_fss_items_t, with each index representing the depth.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fss_nest_t_
  typedef struct {
    f_fss_items_t *depth;

    f_array_length_t size;
    f_array_length_t used;
  } f_fss_nest_t;

  #define f_fss_nest_t_initialize { 0, 0, 0 }

  #define macro_f_fss_nest_t_clear(nest) macro_f_memory_structures_clear(nest)

  #define macro_f_fss_nest_t_resize(status, nest, length) status = f_fss_nest_resize(length, &nest);
  #define macro_f_fss_nest_t_adjust(status, nest, length) status = f_fss_nest_adjust(length, &nest);

  #define macro_f_fss_nest_t_delete_simple(nest)  f_fss_nest_resize(0, &nest);
  #define macro_f_fss_nest_t_destroy_simple(nest) f_fss_nest_adjust(0, &nest);

  #define macro_f_fss_nest_t_increase(status, step, nest)      status = f_fss_nest_increase(step, &nest);
  #define macro_f_fss_nest_t_increase_by(status, nest, amount) status = f_fss_nest_increase_by(amount, &nest);
  #define macro_f_fss_nest_t_decrease_by(status, nest, amount) status = f_fss_nest_decrease_by(amount, &nest);
  #define macro_f_fss_nest_t_decimate_by(status, nest, amount) status = f_fss_nest_decimate_by(amount, &nest);
#endif // _di_f_fss_nest_t_

/**
 * This holds an array of f_fss_nest_t.
 *
 * array: an array of f_fss_nest_t.
 * size: Total amount of allocated space.
 * used: Total number of allocated spaces used.
 */
#ifndef _di_f_fss_nests_t_
  typedef struct {
    f_fss_nest_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_fss_nests_t;

  #define f_fss_nests_t_initialize { 0, 0, 0 }

  #define macro_f_fss_nests_t_clear(nests) macro_f_memory_structures_clear(nests)

  #define macro_f_fss_nests_t_resize(status, nests, length) status = f_fss_nests_resize(length, &nests);
  #define macro_f_fss_nests_t_adjust(status, nests, length) status = f_fss_nests_adjust(length, &nests);

  #define macro_f_fss_nests_t_delete_simple(nests)  f_fss_nests_resize(0, &nests);
  #define macro_f_fss_nests_t_destroy_simple(nests) f_fss_nests_adjust(0, &nests);

  #define macro_f_fss_nests_t_increase(status, step, nests)      status = f_fss_nests_increase(step, &nests);
  #define macro_f_fss_nests_t_increase_by(status, nests, amount) status = f_fss_nests_increase_by(amount, &nests);
  #define macro_f_fss_nests_t_decrease_by(status, nests, amount) status = f_fss_nests_decrease_by(amount, &nests);
  #define macro_f_fss_nests_t_decimate_by(status, nests, amount) status = f_fss_nests_decimate_by(amount, &nests);
#endif // _di_f_fss_nests_t_

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
  extern f_status_t f_fss_items_adjust(const f_array_length_t length, f_fss_items_t * const items);
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
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_items_decimate_by_
  extern f_status_t f_fss_items_decimate_by(const f_array_length_t amount, f_fss_items_t * const items);
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
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_items_decrease_by_
  extern f_status_t f_fss_items_decrease_by(const f_array_length_t amount, f_fss_items_t * const items);
#endif // _di_f_fss_items_decrease_by_

/**
 * Increase the size of the items array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param items
 *   The items array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_items_increase_
  extern f_status_t f_fss_items_increase(const f_array_length_t step, f_fss_items_t * const items);
#endif // _di_f_fss_items_increase_

/**
 * Resize the items array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param items
 *   The items array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
 */
#ifndef _di_f_fss_items_increase_by_
  extern f_status_t f_fss_items_increase_by(const f_array_length_t amount, f_fss_items_t * const items);
#endif // _di_f_fss_items_increase_by_

/**
 * Resize the items array.
 *
 * @param length
 *   The new size to use.
 * @param items
 *   The items array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_items_resize_
  extern f_status_t f_fss_items_resize(const f_array_length_t length, f_fss_items_t * const items);
#endif // _di_f_fss_items_resize_

/**
 * Resize the nest array.
 *
 * @param length
 *   The new size to use.
 * @param nest
 *   The nest array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_nest_adjust_
  extern f_status_t f_fss_nest_adjust(const f_array_length_t length, f_fss_nest_t * const nest);
#endif // _di_f_fss_nest_adjust_

/**
 * Resize the nest array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param nest
 *   The nest array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_nest_decimate_by_
  extern f_status_t f_fss_nest_decimate_by(const f_array_length_t amount, f_fss_nest_t * const nest);
#endif // _di_f_fss_nest_decimate_by_

/**
 * Resize the nest array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param nest
 *   The nest array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_nest_decrease_by_
  extern f_status_t f_fss_nest_decrease_by(const f_array_length_t amount, f_fss_nest_t * const nest);
#endif // _di_f_fss_nest_decrease_by_

/**
 * Increase the size of the nest array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param nest
 *   The nest array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_nest_increase_
  extern f_status_t f_fss_nest_increase(const f_array_length_t step, f_fss_nest_t * const nest);
#endif // _di_f_fss_nest_increase_

/**
 * Resize the nest array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param nest
 *   The nest array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
 */
#ifndef _di_f_fss_nest_increase_by_
  extern f_status_t f_fss_nest_increase_by(const f_array_length_t amount, f_fss_nest_t * const nest);
#endif // _di_f_fss_nest_increase_by_

/**
 * Resize the nest array.
 *
 * @param length
 *   The new size to use.
 * @param nest
 *   The nest array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_nest_resize_
  extern f_status_t f_fss_nest_resize(const f_array_length_t length, f_fss_nest_t * const nest);
#endif // _di_f_fss_nest_resize_

/**
 * Resize the nest array.
 *
 * @param length
 *   The new size to use.
 * @param nests
 *   The nests array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_nests_adjust_
  extern f_status_t f_fss_nests_adjust(const f_array_length_t length, f_fss_nests_t * const nests);
#endif // _di_f_fss_nests_adjust_

/**
 * Resize the nest array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param nests
 *   The nests array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_nests_decimate_by_
  extern f_status_t f_fss_nests_decimate_by(const f_array_length_t amount, f_fss_nests_t * const nests);
#endif // _di_f_fss_nests_decimate_by_

/**
 * Resize the nest array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param nests
 *   The nests array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_nests_decrease_by_
  extern f_status_t f_fss_nests_decrease_by(const f_array_length_t amount, f_fss_nests_t * const nests);
#endif // _di_f_fss_nests_decrease_by_

/**
 * Increase the size of the nests array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param nests
 *   The nests array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_nests_increase_
  extern f_status_t f_fss_nests_increase(const f_array_length_t step, f_fss_nests_t * const nests);
#endif // _di_f_fss_nests_increase_

/**
 * Resize the nests array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param nests
 *   The nests array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
 */
#ifndef _di_f_fss_nests_increase_by_
  extern f_status_t f_fss_nests_increase_by(const f_array_length_t amount, f_fss_nests_t * const nests);
#endif // _di_f_fss_nests_increase_by_

/**
 * Resize the nests array.
 *
 * @param length
 *   The new size to use.
 * @param nests
 *   The nests array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_nests_resize_
  extern f_status_t f_fss_nests_resize(const f_array_length_t length, f_fss_nests_t * const nests);
#endif // _di_f_fss_nests_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_nest_h
