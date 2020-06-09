/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines all datatypes to be used for/by project fss.
 *
 * The purpose of compression is not to compression the entire file's contents but only and individual objects content, so the file is still partially readable.
 * NOTE: all start/stop locations must be defined as a (start < stop) and not (start <= stop), therefore if (start == stop) then stop.
 */
#ifndef _F_fss_h
#define _F_fss_h

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/utf.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * FSS-specific types.
 */
#ifndef _di_f_fss_types_
  #define f_fss_comment             '#'
  #define f_fss_space               ' '
  #define f_fss_space_holder        '_'
  #define f_fss_basic_open          ' '
  #define f_fss_basic_close         '\n'
  #define f_fss_extended_open       ' '
  #define f_fss_extended_close      '\n'
  #define f_fss_list_terminator     '\n'
  #define f_fss_basic_list_open     ':'
  #define f_fss_basic_list_close    '\0'
  #define f_fss_extended_list_open  '{'
  #define f_fss_extended_list_close '}'
  #define f_fss_type_header_open    '#'
  #define f_fss_type_header_part1   ' '
  #define f_fss_type_header_part2   'f'
  #define f_fss_type_header_part3   's'
  #define f_fss_type_header_part4   's'
  #define f_fss_type_header_part5   '-'
  #define f_fss_type_header_close   '\n'

  typedef unsigned long f_fss_id;
#endif // _di_f_fss_types_

/**
 * FSS-specific delimiters.
 */
#ifndef _di_f_fss_delimiters_
  #define f_fss_delimit_slash        '\\'
  #define f_fss_delimit_single_quote '\''
  #define f_fss_delimit_double_quote '"'
  #define f_fss_delimit_placeholder  f_string_placeholder[0]
#endif //_di_f_fss_delimiters_

/**
 * Codes for every FSS standard.
 */
#ifndef _di_f_fss_codes_
  enum {
    f_fss_basic = 1,
    f_fss_extended,
    f_fss_basic_list,
    f_fss_extended_list,
    f_fss_very_basic_list,
    f_fss_somewhat_basic_list,
    f_fss_somewhat_extended_list,
    f_fss_very_extended_list,
    f_fss_embeded_list,
    f_fss_reverse_mapping,
    f_fss_extended_reverse_mapping,
    f_fss_simple_json,
    f_fss_simple_list,
  };
#endif // _di_f_fss_codes_

/**
 * Max size of a FSS header.
 *
 * The standard FSS character header is: "# fss-0000\n\0", which is 10 characters + newline + EOS = 12.
 *
 * The UTF-8 BOM is not supported because it is not an actual thing (only a suggestion according to rfc3629).
 * The UTF-8 BOM sequence is actually a different character called "zero-width non-breaking space".
 * Because it already has a use, this project considers the existence of UTF-8 BOM bad practice in all cases.
 * After all, if your file begins with a "zero-width non breaking space", you may want to actually use a space and not a "BOM".
 */
#ifndef _di_f_fss_max_header_length_
  #define f_fss_max_header_length 12
#endif // _di_f_fss_max_header_length_

/**
 * Default allocation steps.
 */
#ifndef _di_f_fss_default_allocation_step_
  #define f_fss_default_allocation_step f_memory_default_allocation_step

  // set to 4 to be UTF-8 friendlier.
  #define f_fss_default_allocation_step_string 4
#endif // _di_f_fss_default_allocation_step_

/**
 * An array of string locations representing where a delimit was applied or is to be applied with respect to some string.
 */
#ifndef _di_f_fss_delimits_
  typedef f_string_ranges f_fss_delimits;

  #define f_fss_delimits_initialize f_string_ranges_initialize

  #define f_macro_fss_delimits_clear(delimits) f_macro_memory_structure_clear(delimits)

  #define f_macro_fss_delimits_new(status, delimits)     f_macro_string_ranges_new(status, delimits)
  #define f_macro_fss_delimits_delete(status, delimits)  f_macro_string_ranges_delete(status, delimits)
  #define f_macro_fss_delimits_destroy(status, delimits) f_macro_string_ranges_destroy(status, delimits)

  #define f_macro_fss_delimits_delete_simple(delimits)  f_macro_string_ranges_delete_simple(delimits)
  #define f_macro_fss_delimits_destroy_simple(delimits) f_macro_string_ranges_destroy_simple(delimits)

  #define f_macro_fss_delimits_resize(status, delimits, new_length) f_macro_string_ranges_resize(status, delimits, new_length)
  #define f_macro_fss_delimits_adjust(status, delimits, new_length) f_macro_string_ranges_adjust(status, delimits, new_length)
#endif // _di_f_fss_delimits_

/**
 * Stores information about a particular fss file, otherwise known as its header.
 *
 * type:   the kind of fss file is this.
 * length: Total length of the header.
 */
#ifndef _di_f_fss_header_
  typedef struct {
    f_fss_id type;

    f_string_length length;
  } f_fss_header;

  #define f_fss_header_initialize { 0, 0 }
#endif // _di_f_fss_header_

/**
 * This holds an array of fss_headers.
 *
 * array: The array of headers.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fss_headers_
  typedef struct {
    f_fss_header *array;

    f_string_length size;
    f_string_length used;
  } f_fss_headers;

  #define f_fss_headers_initialize { 0, 0, 0 }

  #define f_macro_fss_headers_clear(headers) f_macro_memory_structure_clear(headers)

  #define f_macro_fss_headers_new(status, headers, length) f_macro_memory_structure_new(status, headers, f_fss_header, length)

  #define f_macro_fss_headers_delete(status, headers)  f_macro_memory_structure_delete(status, headers, f_fss_header)
  #define f_macro_fss_headers_destroy(status, headers) f_macro_memory_structure_destroy(status, headers, f_fss_header)

  #define f_macro_fss_headers_delete_simple(headers)  f_macro_memory_structure_delete_simple(headers, f_fss_header)
  #define f_macro_fss_headers_destroy_simple(headers) f_macro_memory_structure_destroy_simple(headers, f_fss_header)

  #define f_macro_fss_headers_resize(status, headers, new_length) f_macro_memory_structure_resize(status, headers, f_fss_header, new_length)
  #define f_macro_fss_headers_adjust(status, headers, new_length) f_macro_memory_structure_adjust(status, headers, f_fss_header, new_length)
#endif // _di_f_fss_headers_


/**
 * This is a location that represents an object.
 */
#ifndef _di_fss_object_
  typedef f_string_range f_fss_object;

  #define f_fss_object_initialize f_string_range_initialize

  #define f_macro_fss_object_new(status, object, length) status = f_memory_new((void **) & object, sizeof(f_fss_object), length)

  #define f_macro_fss_object_delete(status, object)          status = f_memory_delete((void **) & object)
  #define f_macro_fss_object_destroy(status, object, length) status = f_memory_destroy((void **) & object, sizeof(f_fss_object), length)

  #define f_macro_fss_object_delete_simple(object)          f_memory_delete((void **) & object)
  #define f_macro_fss_object_destroy_simple(object, length) f_memory_destroy((void **) & object, sizeof(f_fss_object), length)

  #define f_macro_fss_object_resize(status, object, old_length, new_length) status = f_memory_resize((void **) & object, sizeof(f_fss_object), old_length, new_length)

  #define f_macro_fss_object_adjust(status, object, old_length, new_length) status = f_memory_adjust((void **) & object, sizeof(f_fss_object), old_length, new_length)
#endif // _di_fss_object_

/**
 * This holds an array of fss_object.
 *
 * array: The array of objects.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_fss_objects_
  typedef struct {
    f_fss_object *array;

    f_string_length size;
    f_string_length used;
  } f_fss_objects;

  #define f_fss_objects_initialize { 0, 0, 0 }

  #define f_macro_fss_objects_clear(objects) f_macro_memory_structure_clear(objects)

  #define f_macro_fss_objects_new(status, objects, length) f_macro_memory_structure_new(status, objects, f_fss_object, length)

  #define f_macro_fss_objects_delete(status, objects)  f_macro_memory_structure_delete(status, objects, f_fss_object)
  #define f_macro_fss_objects_destroy(status, objects) f_macro_memory_structure_destroy(status, objects, f_fss_object)

  #define f_macro_fss_objects_delete_simple(objects)  f_macro_memory_structure_delete_simple(objects, f_fss_object)
  #define f_macro_fss_objects_destroy_simple(objects) f_macro_memory_structure_destroy_simple(objects, f_fss_object)

  #define f_macro_fss_objects_resize(status, objects, new_length) f_macro_memory_structure_resize(status, objects, f_fss_object, new_length)
  #define f_macro_fss_objects_adjust(status, objects, new_length) f_macro_memory_structure_destroy(status, objects, f_fss_object, new_length)
#endif // _di_fss_objects_

/**
 * This holds an array of string locations that represent the content.
 *
 * The very first string location will represent the outermost content.
 * All of the following string locations will represent the first level of nesting of all sub-content.
 * There will be no nesting beyond the first level recorded in this structure.
 *
 * array: The array of content.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_fss_content_
  typedef struct {
    f_string_range *array;

    f_array_length size;
    f_array_length used;
  } f_fss_content;

  #define f_fss_content_initialize { 0, 0, 0 }

  #define f_macro_fss_content_clear(content) f_macro_memory_structure_new(content)

  #define f_macro_fss_content_new(status, content, length) f_macro_memory_structure_new(status, content, f_string_range, length)

  #define f_macro_fss_content_delete(status, content)  f_macro_memory_structure_delete(status, content, f_string_range)
  #define f_macro_fss_content_destroy(status, content) f_macro_memory_structure_destroy(status, content, f_string_range)

  #define f_macro_fss_content_delete_simple(content)  f_macro_memory_structure_delete_simple(content, f_string_range)
  #define f_macro_fss_content_destroy_simple(content) f_macro_memory_structure_destroy_simple(content, f_string_range)

  #define f_macro_fss_content_resize(status, content, new_length) f_macro_memory_structure_resize(status, content, f_string_range, new_length)
  #define f_macro_fss_content_adjust(status, content, new_length) f_macro_memory_structure_adjust(status, content, f_string_range, new_length)
#endif // _di_fss_content_

/**
 * This holds an array of fss_content.
 *
 * array: The array of content arrays.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fss_contents_
  typedef struct {
    f_fss_content *array;

    f_array_length size;
    f_array_length used;
  } f_fss_contents;

  #define f_fss_contents_initialize { 0, 0, 0 }

  #define f_macro_fss_contents_clear(contents) f_macro_memory_structures_clear(contents)

  #define f_macro_fss_contents_new(status, contents, length) f_macro_memory_structures_delete(status, contents, f_fss_content, length)

  #define f_macro_fss_contents_delete(status, contents)  f_macro_memory_structures_delete(status, contents, f_fss_content)
  #define f_macro_fss_contents_destroy(status, contents) f_macro_memory_structures_destroy(status, contents, f_fss_content)

  #define f_macro_fss_contents_delete_simple(contents)  f_macro_memory_structures_delete_simple(contents, f_fss_content)
  #define f_macro_fss_contents_destroy_simple(contents) f_macro_memory_structures_destroy_simple(contents, f_fss_content)

  #define f_macro_fss_contents_resize(status, contents, new_length) f_macro_memory_structures_resize(status, contents, f_fss_content, new_length, f_array_length)
  #define f_macro_fss_contents_adjust(status, contents, new_length) f_macro_memory_structures_resize(status, contents, f_fss_content, new_length, f_array_length)
#endif // _di_f_fss_contents_

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
    status = f_memory_new((void **) & items.array, sizeof(f_fss_item), new_length); \
    if (status == F_none) { \
      items.size = new_length; \
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
    status = f_memory_new((void **) & nest.depth, sizeof(f_fss_items), new_length); \
    if (status == F_none) { \
      nest.size = new_length; \
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
    status = f_memory_new((void **) & nests.array, sizeof(f_fss_nest), new_length); \
    if (status == F_none) { \
      nests.size = new_length; \
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

/**
 * Continue to the previous character, based on step and character width.
 *
 * The start position must be at the start of a valid UTF-8 block.
 *
 * @param buffer
 *   The string to process.
 * @param range
 *   The start and stop positions to be incremented.
 *   The start position will be incremented by step.
 * @param step
 *   The number of steps to decrement the start position.
 *   The steps refer to characters and not integers.
 *   Essentially this number is considered against the width of every character found.
 *   (For ASCII each step would be (sizeof(int8_t), which is 1).
 *   (For UTF-8 character of width 3, each step would be (3 * sizeof(int8_t)).
 *
 * @return
 *   F_none on success.
 *   F_none_stop if the stop range is reached before all steps are completed.
 *   F_none_eos if the end of buffer is reached before all steps are completed.
 *   F_incomplete_utf_eos (with error bit) if the end of buffer is reached before the complete UTF-8 character can be processed.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_decrement_buffer_
  extern f_return_status f_fss_decrement_buffer(const f_string_static buffer, f_string_range *range, const f_string_length step);
#endif // _di_f_fss_decrement_buffer_

/**
 * Continue to the next character, based on step and character width.
 *
 * The start position must be at the start of a valid UTF-8 block.
 *
 * @param buffer
 *   The string to process.
 * @param range
 *   The start and stop positions to be incremented.
 *   The start position will be incremented by step.
 * @param step
 *   The number of steps to increment the start position.
 *   The steps refer to characters and not integers.
 *   Essentially this number is considered against the width of every character found.
 *   (For ASCII each step would be (sizeof(int8_t), which is 1).
 *   (For UTF-8 character of width 3, each step would be (3 * sizeof(int8_t)).
 *
 * @return
 *   F_none on success.
 *   F_none_stop if the stop range is reached before all steps are completed.
 *   F_none_eos if the end of buffer is reached before all steps are completed.
 *   F_incomplete_utf_stop (with error bit) if the stop range is reached before the complete UTF-8 character can be processed.
 *   F_incomplete_utf_eos (with error bit) if the end of buffer is reached before the complete UTF-8 character can be processed.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_increment_buffer_
  extern f_return_status f_fss_increment_buffer(const f_string_static buffer, f_string_range *range, const f_string_length step);
#endif // _di_f_fss_increment_buffer_

/**
 * Identify whether or not a character in the buffer is a graph (ASCII or UTF-8) character.
 *
 * @param buffer
 *   The string to process.
 * @param range
 *   The character at the start position will be checked against the graph.
 * @param header
 *   The header data to populate with results of this function.
 *
 * @return
 *   F_true if the character in the buffer is a graph character.
 *   F_false if the character in the buffer is not a graph character.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors from (with error bit): f_utf_is_graph().
 *
 * @see f_utf_is_graph()
 */
#ifndef _di_f_fss_is_graph_
  extern f_return_status f_fss_is_graph(const f_string_static buffer, const f_string_range range);
#endif // _di_f_fss_is_graph_

/**
 * Identify whether or not a character in the buffer is a space (ASCII or UTF-8) character.
 *
 * @param buffer
 *   The string to process.
 * @param range
 *   The character at the start position will be checked against the graph.
 * @param header
 *   The header data to populate with results of this function.
 *
 * @return
 *   F_true if the character in the buffer is a space character.
 *   F_false if the character in the buffer is not a space character.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors from (with error bit): f_utf_is_space().
 *
 * @see f_utf_is_space()
 */
#ifndef _di_f_fss_is_space_
  extern f_return_status f_fss_is_space(const f_string_static buffer, const f_string_range range);
#endif // _di_f_fss_is_space_

/**
 * Shift all of the delimiters to the end of the used buffer.
 *
 * This allows one to do a printf on the dynamic string without the delimiters arbitrarily stopping the output.
 * No reallocations are performed, this will only shift characters.
 *
 * @param buffer
 *   The string to process.
 *   This gets updated.
 * @param range
 *   A restriction on where within the buffer the shifting happens.
 *
 * @return
 *   F_none on success.
 *   F_utf (with error bit) if UTF-8 cannot be fully processed (buffer or range range not long enough).
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_shift_delimiters_
  extern f_return_status f_fss_shift_delimiters(f_string_dynamic *buffer, const f_string_range range);
#endif // _di_f_fss_shift_delimiters_

/**
 * Skip past all whitespace and control characters, except newline.
 *
 * Zero-width characters are not skipped because they might be part of a graph character, such as combining characters.
 * @todo needs consideration on how to handle zero-width before space/control vs zero-width before graph.
 *
 * @param buffer
 *   The string to process.
 * @param range
 *   The start and stop positions in the buffer being processed.
 *   This increments range->start.
 *
 * @return
 *   F_none on success.
 *   F_none_eol on success and EOL was reached.
 *   F_none_eos on success and EOS was reached.
 *   F_none_stop on success and stop point was reached.
 *   F_incomplete_utf (with error bit) if an incomplete UTF-8 fragment was found.
 *   F_incomplete_utf_eos (with error bit) if unable to get entire UTF-8 sequence due to EOS.
 *   F_incomplete_utf_stop (with error bit) if unable to get entire UTF-8 sequence due to stop point reached.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors from (with error bit): f_utf_is_control().
 *   Errors from (with error bit): f_utf_is_whitespace().
 *   Errors from (with error bit): f_utf_is_zero_width().
 *
 * @see f_utf_is_control()
 * @see f_utf_is_whitespace()
 * @see f_utf_is_zero_width()
 */
#ifndef _di_f_fss_skip_past_space_
  extern f_return_status f_fss_skip_past_space(const f_string_static buffer, f_string_range *range);
#endif // _di_f_fss_skip_past_space_

/**
 * Skip past all non-graph and non-zero-width characters (whitespace and control characters).
 *
 * Zero-width characters are not skipped because they might be part of a graph character, such as combining characters.
 * @todo needs consideration on how to handle zero-width before space/control vs zero-width before graph.
 *
 * @param buffer
 *   The string to process.
 * @param range
 *   The start and stop positions in the buffer being processed.
 *   This increments range->start.
 *
 * @return
 *   F_none on success.
 *   F_none_eol on success and EOL was reached.
 *   F_none_eos on success and EOS was reached.
 *   F_none_stop on success and stop point was reached.
 *   F_incomplete_utf (with error bit) if an incomplete UTF-8 fragment was found.
 *   F_incomplete_utf_eos (with error bit) if unable to get entire UTF-8 sequence due to EOS.
 *   F_incomplete_utf_stop (with error bit) if unable to get entire UTF-8 sequence due to stop point reached.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors from (with error bit): f_utf_is_graph().
 *   Errors from (with error bit): f_utf_is_zero_width().
 *
 * @see f_utf_is_graph()
 * @see f_utf_is_zero_width()
 */
#ifndef _di_f_fss_skip_past_non_graph_
  extern f_return_status f_fss_skip_past_non_graph(const f_string_static buffer, f_string_range *range);
#endif // _di_f_fss_skip_past_non_graph_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_h
