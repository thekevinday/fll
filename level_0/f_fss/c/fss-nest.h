/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
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
 * object:  The object.
 * content: The content associated with the object.
 * parent:  A location referencing a parrent object or content that this object content is nested under.
 */
#ifndef _di_fss_item_
  typedef struct {
    f_fss_object   object;
    f_fss_content  content;
    f_array_length parent;
  } f_fss_item;

  #define f_fss_item_initialize { f_fss_object_initialize, f_fss_content_initialize, f_array_length_initialize }

  /**
   * Reset a fss item stucture to 0 (clear all values).
   *
   * This does not deallocate memory, be certain that memory is not allocated before calling this to avoid potential memory leaks.
   *
   * item: the f_fss_item structure to operate on.
   */
  #define f_macro_fss_item_clear(item) \
    item.object.start = 1; \
    item.object.stop = 0; \
    f_macro_fss_content_clear(item.content); \
    item.parent = 0;

  /**
   * Create a new fss item structure.
   *
   * This does not deallocate memory, be certain that memory is not allocated before calling this to avoid potential memory leaks.
   *
   * status:    the status to return.
   * structure: the structure to operate on.
   * type:      the structure type.
   * length:    the new size of the array.
   */
  #define f_macro_fss_item_new(status, item, length) \
    item.object.start = 1; \
    item.object.stop = 0; \
    f_macro_fss_content_new(status, item.content, length) \
    item.parent = 0;

  /**
   * Delete a fss item.
   *
   * status: the status to return.
   * item:   the f_fss_item structure to operate on.
   */
  #define f_macro_fss_item_delete(status, item) \
    f_macro_fss_content_delete(status, item.content) \
    if (status == F_none) { \
      item.object.start = 1; \
      item.object.stop = 0; \
      item.parent = 0; \
    }

  /**
   * Destroy a fss item.
   *
   * status: the status to return.
   * item:  the f_fss_item structure to operate on.
   */
  #define f_macro_fss_item_destroy(status, item) \
    f_macro_fss_content_destroy(status, item.content) \
    if (status == F_none) { \
      item.object.start = 1; \
      item.object.stop = 0; \
      item.parent = 0; \
    }

  /**
   * Delete a fss item.
   *
   * item: the f_fss_item structure to operate on.
   */
  #define f_macro_fss_item_delete_simple(item) \
    f_macro_fss_content_delete_simple(item.content); \
    item.object.start = 1; \
    item.object.stop = 0; \
    item.parent = 0;

  /**
   * Destroy a fss item.
   *
   * item: the f_fss_item structure to operate on.
   */
  #define f_macro_fss_item_destroy_simple(item) \
    f_macro_fss_content_destroy_simple(item.content); \
    item.object.start = 1; \
    item.object.stop = 0; \
    item.parent = 0;

  /**
   * Resize a fss item.
   *
   * status:     the status to return.
   * item:       the f_fss_item structure to operate on.
   * new_length: the new size of the array.
   */
  #define f_macro_fss_item_resize(status, item, new_length) f_macro_fss_content_resize(status, item.content, new_length);

  /**
   * Adjust a fss item.
   *
   * status:     the status to return.
   * item:       the f_fss_item structure to operate on.
   * new_length: the new size of the array.
   */
  #define f_macro_fss_item_adjust(status, item, new_length) f_macro_fss_content_adjust(status, item.content, new_length);

#endif // _di_fss_item_

/**
 * This holds an array of fss_item.
 *
 * This is designed to be used as a part of f_fss_nest.
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
 * size: Total amount of allocated space.
 * used: Total number of allocated spaces used.
 */
#ifndef _di_fss_items_
  typedef struct {
    f_fss_item *array;

    f_array_length size;
    f_array_length used;
  } f_fss_items;

  #define f_fss_items_initialize { 0, 0, 0 }

  /**
   * Reset a fss items to 0 (clear all values).
   *
   * This does not deallocate memory, be certain that memory is not allocated before calling this to avoid potential memory leaks.
   *
   * items: the f_fss_items structure to operate on.
   */
  #define f_macro_fss_items_clear(items) \
    items.array = 0; \
    items.size = 0; \
    items.used = 0;

  /**
   * Create a new fss items.
   *
   * This does not deallocate memory, be certain that memory is not allocated before calling this to avoid potential memory leaks.
   *
   * status:     the status to return.
   * items:      the f_fss_items structure to operate on.
   * new_length: the new size of the array.
   */
  #define f_macro_fss_items_new(status, items, length) \
    items.array = 0; \
    items.size = 0; \
    items.used = 0; \
    status = f_memory_new((void **) & items.array, sizeof(f_fss_item), length); \
    if (status == F_none) { \
      items.size = length; \
      items.used = 0; \
    }

  /**
   * Delete a fss items.
   *
   * status: the status to return.
   * items:  the f_fss_items structure to operate on.
   */
  #define f_macro_fss_items_delete(status, items) \
    status = F_none; \
    items.used = items.size; \
    while (items.used > 0) { \
      items.used--; \
      f_macro_fss_item_delete(status, items.array[items.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_delete((void **) & items.array, sizeof(f_fss_item), items.size); \
    if (status == F_none) items.size = 0;

  /**
   * Destroy a fss items.
   *
   * status: the status to return.
   * items:  the f_fss_items structure to operate on.
   */
  #define f_macro_fss_items_destroy(status, items) \
    status = F_none; \
    items.used = items.size; \
    while (items.used > 0) { \
      items.used--; \
      f_macro_fss_item_destroy(status, items.array[items.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_delete((void **) & items.array, sizeof(f_fss_item), items.size); \
    if (status == F_none) items.size = 0;

  /**
   * Delete a fss items.
   *
   * items: the f_fss_items structure to operate on.
   */
  #define f_macro_fss_items_delete_simple(items) \
    items.used = items.size; \
    while (items.used > 0) { \
      items.used--; \
      f_macro_fss_item_delete_simple(items.array[items.used]); \
      if (items.used == 0) { \
        if (f_memory_delete((void **) & items.array, sizeof(f_fss_item), items.size)) { \
          items.size = 0; \
        } \
      } \
    }

  /**
   * Destroy a fss items.
   *
   * items: the f_fss_items structure to operate on.
   */
  #define f_macro_fss_items_destroy_simple(items) \
    items.used = items.size; \
    while (items.used > 0) { \
      items.used--; \
      f_macro_fss_item_destroy_simple(status, items.array[items.used]); \
      if (items.used == 0) { \
        if (f_memory_destroy((void **) & items.array, sizeof(f_fss_item), items.size)) { \
          items.size = 0; \
        } \
      } \
    }

  /**
   * Resize a fss items.
   *
   * status:     the status to return.
   * items:      the f_fss_items structure to operate on.
   * new_length: the new size of the array.
   */
  #define f_macro_fss_items_resize(status, items, new_length) \
    status = F_none; \
    if (new_length < items.size) { \
      f_array_length i = items.size - new_length; \
      for (; i < items.size; i++) { \
        f_macro_fss_item_delete(status, items.array[i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_resize((void **) & items.array, sizeof(f_fss_item), items.size, new_length); \
    if (status == F_none) { \
      if (new_length > items.size) { \
        f_array_length i = items.size; \
        for (; i < new_length; i++) { \
          memset(&items.array[i], 0, sizeof(f_fss_item)); \
        } \
      } \
      items.size = new_length; \
      if (items.used > items.size) items.used = new_length; \
    }

  /**
   * Adjust a fss items.
   *
   * status:     the status to return.
   * items:      the f_fss_items structure to operate on.
   * new_length: the new size of the array.
   */
  #define f_macro_fss_items_adjust(status, items, new_length) \
    status = F_none; \
    if (new_length < items.size) { \
      length_variable i = items.size - new_length; \
      for (; i < items.size; i++) { \
        f_macro_fss_item_destroy(status, items.array[i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_adjust((void **) & items.array, sizeof(f_fss_item), items.size, new_length); \
    if (status == F_none) { \
      if (new_length > items.size) { \
        length_variable i = items.size; \
        for (; i < new_length; i++) { \
          memset(&items.array[i], 0, sizeof(f_fss_item)); \
        } \
      } \
      items.size = new_length; \
      if (items.used > items.size) items.used = new_length; \
    }
#endif // _di_fss_items_

/**
 * This holds an array of f_fss_items.
 *
 * Each array row represents the nesting depth.
 * The top-level will not have any parent, so "parent" must be ignored on anything at index 0.
 * The parent identifier is expected to reference a position in the nesting depth immediately above it.
 * @todo: consider instead of using a "parent", have setting set to 0 to represent no data.
 *
 * depth: An array of f_fss_items, with each index representing the depth.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_fss_nest_
  typedef struct {
    f_fss_items *depth;

    f_array_length size;
    f_array_length used;
  } f_fss_nest;

  #define f_fss_nest_initialize { 0, 0, 0 }

  /**
   * Reset a fss content nest to 0 (clear all values).
   *
   * This does not deallocate memory, be certain that memory is not allocated before calling this to avoid potential memory leaks.
   *
   * nest: the f_fss_nest structure to operate on.
   */
  #define f_macro_fss_nest_clear(nest) \
    nest.depth = 0; \
    nest.size = 0; \
    nest.used = 0;

  /**
   * Create a new fss content nest.
   *
   * This does not deallocate memory, be certain that memory is not allocated before calling this to avoid potential memory leaks.
   *
   * status:     the status to return.
   * nest:       the f_fss_nest structure to operate on.
   * new_length: the new size of the array.
   */
  #define f_macro_fss_nest_new(status, nest, length) \
    nest.depth = 0; \
    nest.size = 0; \
    nest.used = 0; \
    status = f_memory_new((void **) & nest.depth, sizeof(f_fss_items), length); \
    if (status == F_none) { \
      nest.size = length; \
      nest.used = 0; \
    }

  /**
   * Delete a fss content nest.
   *
   * status: the status to return.
   * nest:   the f_fss_nest structure to operate on.
   */
  #define f_macro_fss_nest_delete(status, nest) \
    status = F_none; \
    nest.used = nest.size; \
    while (nest.used > 0) { \
      nest.used--; \
      f_macro_fss_items_delete(status, nest.depth[nest.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_delete((void **) & nest.depth, sizeof(f_fss_items), nest.size); \
    if (status == F_none) nest.size = 0;

  /**
   * Destroy a fss content nest.
   *
   * status: the status to return.
   * nest:   the f_fss_nest structure to operate on.
   */
  #define f_macro_fss_nest_destroy(status, nest) \
    status = F_none; \
    nest.used = nest.size; \
    while (nest.used > 0) { \
      nest.used--; \
      f_macro_fss_items_destroy(status, nest.depth[nest.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_delete((void **) & nest.depth, sizeof(f_fss_items), nest.size); \
    if (status == F_none) nest.size = 0;

  /**
   * Delete a fss content nest.
   *
   * nest: the f_fss_nest structure to operate on.
   */
  #define f_macro_fss_nest_delete_simple(nest) \
    nest.used = nest.size; \
    while (nest.used > 0) { \
      nest.used--; \
      f_macro_fss_items_delete_simple(nest.depth[nest.used]); \
      if (nest.used == 0) { \
        if (f_memory_delete((void **) & nest.depth, sizeof(f_fss_items), nest.size)) { \
          nest.size = 0; \
        } \
      } \
    }

  /**
   * Destroy a fss content nest.
   *
   * nest: the f_fss_nest structure to operate on.
   */
  #define f_macro_fss_nest_destroy_simple(nest) \
    nest.used = nest.size; \
    while (nest.used > 0) { \
      nest.used--; \
      f_macro_fss_items_destroy_simple(nest.depth[nest.used]); \
      if (nest.used == 0) { \
        if (f_memory_destroy((void **) & nest.depth, sizeof(f_fss_items), nest.size)) { \
          nest.size = 0; \
        } \
      } \
    }

  /**
   * Resize a fss content nest.
   *
   * status:     the status to return.
   * nest:       the f_fss_nest structure to operate on.
   * new_length: the new size of the array.
   */
  #define f_macro_fss_nest_resize(status, nest, new_length) \
    status = F_none; \
    if (new_length < nest.size) { \
      f_array_length i = nest.size - new_length; \
      for (; i < nest.size; i++) { \
        f_macro_fss_items_delete(status, nest.depth[i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_resize((void **) & nest.depth, sizeof(f_fss_items), nest.size, new_length); \
    if (status == F_none) { \
      if (new_length > nest.size) { \
        f_array_length i = nest.size; \
        for (; i < new_length; i++) { \
          memset(&nest.depth[i], 0, sizeof(f_fss_items)); \
        } \
      } \
      nest.size = new_length; \
      if (nest.used > nest.size) nest.used = new_length; \
    }

  /**
   * Adjust a fss content nest.
   *
   * status:     the status to return.
   * nest:       the f_fss_nest structure to operate on.
   * new_length: the new size of the array.
   */
  #define f_macro_fss_nest_adjust(status, nest, new_length) \
    status = F_none; \
    if (new_length < nest.size) { \
      f_array_length i = nest.size - new_length; \
      for (; i < nest.size; i++) { \
        f_macro_fss_items_destroy(status, nest.depth[i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_adjust((void **) & nest.depth, sizeof(f_fss_item), nest.size, new_length); \
    if (status == F_none) { \
      if (new_length > nest.size) { \
        f_array_length i = nest.size; \
        for (; i < new_length; i++) { \
          memset(&items.depth[i], 0, sizeof(f_fss_item)); \
        } \
      } \
      nest.size = new_length; \
      if (nest.used > nest.size) nest.used = new_length; \
    }
#endif // _di_fss_nest_

/**
 * This holds an array of f_fss_nest.
 *
 * array: an array of f_fss_nest.
 * size: Total amount of allocated space.
 * used: Total number of allocated spaces used.
 */
#ifndef _di_fss_nests_
  typedef struct {
    f_fss_nest *array;

    f_array_length size;
    f_array_length used;
  } f_fss_nests;

  #define f_fss_nests_initialize { 0, 0, 0 }

  /**
   * Reset a fss content nests to 0 (clear all values).
   *
   * This does not deallocate memory, be certain that memory is not allocated before calling this to avoid potential memory leaks.
   *
   * nests: the f_fss_nests structure to operate on.
   */
  #define f_macro_fss_nests_clear(nests) \
    nests.array = 0; \
    nests.size = 0; \
    nests.used = 0;

  /**
   * Create a new fss content nests.
   *
   * This does not deallocate memory, be certain that memory is not allocated before calling this to avoid potential memory leaks.
   *
   * status:     the status to return.
   * nests:      the f_fss_nests structure to operate on.
   * new_length: the new size of the array.
   */
  #define f_macro_fss_nests_new(status, nests, length) \
    nests.array = 0; \
    nests.size = 0; \
    nests.used = 0; \
    status = f_memory_new((void **) & nests.array, sizeof(f_fss_nest), length); \
    if (status == F_none) { \
      nests.size = length; \
      nests.used = 0; \
    }

  /**
   * Delete a fss content nests.
   *
   * status: the status to return.
   * nests:  the f_fss_nests structure to operate on.
   */
  #define f_macro_fss_nests_delete(nests) \
    status = F_none; \
    nests.used = nests.size; \
    while (nests.used > 0) { \
      nests.used--; \
      f_macro_fss_nest_delete(status, nests.array[nests.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_delete((void **) & nests.array, sizeof(f_fss_nest), nests.size); \
    if (status == F_none) nests.size = 0;

  /**
   * Destroy a fss content nests.
   *
   * status: the status to return.
   * nests:  the f_fss_nests structure to operate on.
   */
  #define f_macro_fss_nests_destroy(nests) \
    status = F_none; \
    nests.used = nests.size; \
    while (nests.used > 0) { \
      nests.used--; \
      f_macro_fss_nest_destroy(status, nests.array[nests.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_destroy((void **) & nests.array, sizeof(f_fss_nest), nests.size); \
    if (status == F_none) nests.size = 0;

  /**
   * Delete a fss content nests.
   *
   * nests: the f_fss_nests structure to operate on.
   */
  #define f_macro_fss_nests_delete_simple(nests) \
    nests.used = nests.size; \
    while (nests.used > 0) { \
      nests.used--; \
      f_macro_fss_nest_delete_simple(nests.array[nests.used]); \
      if (nests.used == 0) { \
        if (f_memory_delete((void **) & nests.array, sizeof(f_fss_nest), nests.size)) { \
          nests.size = 0; \
        } \
      } \
    }

  /**
   * Destroy a fss content nests.
   *
   * nests: the f_fss_nests structure to operate on.
   */
  #define f_macro_fss_nests_destroy_simple(nests) \
    nests.used = nests.size; \
    while (nests.used > 0) { \
      nests.used--; \
      f_macro_fss_nest_destroy_simple(nests.array[nests.used]); \
      if (nests.used == 0) { \
        if (f_memory_destroy((void **) & nests.array, sizeof(f_fss_nest), nests.size)) { \
          nests.size = 0; \
        } \
      } \
    }

  /**
   * Resize a fss content nests.
   *
   * status:     the status to return.
   * nests:      the f_fss_nests structure to operate on.
   * new_length: the new size of the array.
   */
  #define f_macro_fss_nests_resize(status, nests, new_length) \
    status = F_none; \
    if (new_length < nests.size) { \
      f_array_length i = nests.size - new_length; \
      for (; i < nests.size; i++) { \
        f_macro_fss_nest_delete(status, nests.array[i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_resize((void **) & nests.array, sizeof(f_fss_nest), nests.size, new_length); \
    if (status == F_none) { \
      if (new_length > nests.size) { \
        f_array_length i = nests.size; \
        for (; i < new_length; i++) { \
          memset(&nests.array[i], 0, sizeof(f_fss_nest)); \
        } \
      } \
      nests.size = new_length; \
      if (nests.used > nests.size) nests.used = new_length; \
    }

  /**
   * Adjust a fss content nests.
   *
   * status:     the status to return.
   * nests:      the f_fss_nests structure to operate on.
   * new_length: he new size of the array.
   */
  #define f_macro_fss_nests_adjust(status, nests, new_length) \
    status = F_none; \
    if (new_length < nests.size) { \
      f_array_length i = nests.size - new_length; \
      for (; i < nests.size; i++) { \
        f_macro_fss_nest_destroy(status, nests.array[i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_adjust((void **) & nests.array, sizeof(f_fss_nest), nests.size, new_length); \
    if (status == F_none) { \
      if (new_length > nests.size) { \
        f_array_length i = nests.size; \
        for (; i < new_length; i++) { \
          memset(&nests.array[i], 0, sizeof(f_fss_nest)); \
        } \
      } \
      nests.size = new_length; \
      if (nests.used > nests.size) nests.used = new_length; \
    }
#endif // _di_fss_nests_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_nest_h
