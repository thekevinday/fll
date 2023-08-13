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
#endif // _di_f_fss_items_t_

/**
 * Delete an item.
 *
 * @param item
 *   The item to delete.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_ranges_resize().
 *
 * @see f_string_ranges_resize()
 */
#ifndef _di_f_fss_item_delete_
  extern f_status_t f_fss_item_delete(f_fss_item_t * const item);
#endif // _di_f_fss_item_delete_

/**
 * Destroy an item.
 *
 * @param item
 *   The item to destroy.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_ranges_adjust().
 *
 * @see f_string_ranges_adjust()
 */
#ifndef _di_f_fss_item_destroy_
  extern f_status_t f_fss_item_destroy(f_fss_item_t * const item);
#endif // _di_f_fss_item_destroy_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_items_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *   Must not be NULL.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_ranges_resize().
 *
 * @see f_string_ranges_resize()
 */
#ifndef _di_f_fss_items_delete_callback_
  extern f_status_t f_fss_items_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_fss_items_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_items_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *   Must not be NULL.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_ranges_adjust().
 *
 * @see f_string_ranges_adjust()
 */
#ifndef _di_f_fss_items_destroy_callback_
  extern f_status_t f_fss_items_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_fss_items_destroy_callback_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_itemss_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *   Must not be NULL.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_ranges_resize().
 *
 * @see f_string_ranges_resize()
 */
#ifndef _di_f_fss_itemss_delete_callback_
  extern f_status_t f_fss_itemss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_fss_itemss_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_itemss_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *   Must not be NULL.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_ranges_adjust().
 *
 * @see f_string_ranges_adjust()
 */
#ifndef _di_f_fss_itemss_destroy_callback_
  extern f_status_t f_fss_itemss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_fss_itemss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_item_h
