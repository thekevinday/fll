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
#include <level_0/status.h>
#include <level_0/string.h>
#include <level_0/type.h>

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
  #define f_fss_delimit_placeholder  f_string_placeholder
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
  typedef f_string_locations f_fss_delimits;

  #define f_fss_delimits_initialize f_string_locations_initialize

  #define f_macro_fss_delimits_clear(delimits) f_macro_memory_structure_clear(delimits)

  #define f_macro_fss_delimits_new(status, delimits)  f_macro_string_locations_new(status, delimits)
  #define f_macro_fss_delimits_delete(status, delimits)  f_macro_string_locations_delete(status, delimits)
  #define f_macro_fss_delimits_destroy(status, delimits) f_macro_string_locations_destroy(status, delimits)

  #define f_macro_fss_delimits_resize(status, delimits, new_length) f_macro_string_locations_resize(status, delimits, new_length)
  #define f_macro_fss_delimits_adjust(status, delimits, new_length) f_macro_string_locations_adjust(status, delimits, new_length)
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

  #define f_macro_fss_headers_delete(status, headers) f_macro_memory_structure_delete(status, headers, f_fss_header)
  #define f_macro_fss_headers_destroy(status, headers) f_macro_memory_structure_destroy(status, headers, f_fss_header)

  #define f_macro_fss_headers_resize(status, headers, new_length) f_macro_memory_structure_resize(status, headers, f_fss_header, new_length)
  #define f_macro_fss_headers_adjust(status, headers, new_length) f_macro_memory_structure_adjust(status, headers, f_fss_header, new_length)
#endif // _di_f_fss_headers_


/**
 * This is a location that represents an object.
 */
#ifndef _di_fss_object_
  typedef f_string_location f_fss_object;

  #define f_fss_object_initialize f_string_location_initialize

  #define f_macro_fss_object_new(status, object, length) status = f_memory_new((void **) & object, sizeof(f_fss_object), length)

  #define f_macro_fss_object_delete(status, object) status = f_memory_delete((void **) & object)
  #define f_macro_fss_object_destroy(status, object, size) status = f_memory_destroy((void **) & object, sizeof(f_fss_object), size)

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

  #define f_macro_fss_objects_delete(status, objects) f_macro_memory_structure_delete(status, objects, f_fss_object)
  #define f_macro_fss_objects_destroy(status, objects) f_macro_memory_structure_destroy(status, objects, f_fss_object)

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
    f_string_location *array;

    f_array_length size;
    f_array_length used;
  } f_fss_content;

  #define f_fss_content_initialize { 0, 0, 0 }

  #define f_macro_fss_content_clear(content) f_macro_memory_structure_new(content)

  #define f_macro_fss_content_new(status, content, length) f_macro_memory_structure_new(status, content, f_string_location, length)

  #define f_macro_fss_content_delete(status, content) f_macro_memory_structure_delete(status, content, f_string_location)
  #define f_macro_fss_content_destroy(status, content) f_macro_memory_structure_destroy(status, content, f_string_location)

  #define f_macro_fss_content_resize(status, content, new_length) f_macro_memory_structure_resize(status, content, f_string_location, new_length)
  #define f_macro_fss_content_adjust(status, content, new_length) f_macro_memory_structure_adjust(status, content, f_string_location, new_length)
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

  #define f_macro_fss_contents_delete(status, contents) f_macro_memory_structures_delete(status, contents, f_fss_content)
  #define f_macro_fss_contents_destroy(status, contents) f_macro_memory_structures_destroy(status, contents, f_fss_content)

  #define f_macro_fss_contents_resize(status, contents, new_length) f_macro_memory_structures_resize(status, contents, f_fss_content, new_length, f_array_length)
  #define f_macro_fss_contents_adjust(status, contents, new_length) f_macro_memory_structures_resize(status, contents, f_fss_content, new_length, f_array_length)
#endif // _di_f_fss_contents_

/**
 * This holds a child content object and its associated content.
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
#ifndef _di_fss_content_child_
  typedef struct {
    f_fss_object   object;
    f_fss_content  content;
    f_array_length parent;
  } f_fss_content_child;

  #define f_fss_content_child_initialize { f_fss_object_initialize, f_fss_content_initialize, f_array_length_initialize }

  /**
   * Reset a fss content child stucture to 0 (clear all values).
   *
   * This does not deallocate memory, be certain that memory is not allocated before calling this to avoid potential memory leaks.
   *
   * content_child: the f_fss_content_child structure to operate on.
   */
  #define f_macro_fss_content_child_clear(content_child) \
    content_child.object.start = 1; \
    content_child.object.stop = 0; \
    f_macro_fss_content_clear(content_child.content); \
    content_child.parent = 0;

  /**
   * Create a new fss content child structure.
   *
   * This does not deallocate memory, be certain that memory is not allocated before calling this to avoid potential memory leaks.
   *
   * status:    the status to return.
   * structure: the structure to operate on.
   * type:      the structure type.
   * length:    the new size of the array.
   */
  #define f_macro_fss_content_child_new(status, content_child, length) \
    content_child.object.start = 1; \
    content_child.object.stop = 0; \
    f_macro_fss_content_new(status, content_child.content, length) \
    content_child.parent = 0;

  /**
   * Delete a fss content child.
   *
   * status:        the status to return.
   * content_child: the f_fss_content_child structure to operate on.
   */
  #define f_macro_fss_content_child_delete(status, content_child) \
    f_macro_fss_content_delete(status, content_child.content) \
    if (status == f_none) { \
      content_child.object.start = 1; \
      content_child.object.stop = 0; \
      content_child.parent = 0; \
    }

  /**
   * Destroy a fss content child.
   *
   * status:        the status to return.
   * content_child: the f_fss_content_child structure to operate on.
   */
  #define f_macro_fss_content_child_destroy(status, content_child) \
    f_macro_fss_content_destroy(status, content_child.content) \
    if (status == f_none) { \
      content_child.object.start = 1; \
      content_child.object.stop = 0; \
      content_child.parent = 0; \
    }

  /**
   * Resize a fss content child.
   *
   * status:        the status to return.
   * content_child: the f_fss_content_child structure to operate on.
   * new_length:    the new size of the array.
   */
  #define f_macro_fss_content_child_resize(status, content_child, new_length) f_macro_fss_content_resize(status, content_child.content, new_length);

  /**
   * Adjust a fss content child.
   *
   * status:        the status to return.
   * content_child: the f_fss_content_child structure to operate on.
   * new_length:    the new size of the array.
   */
  #define f_macro_fss_content_child_adjust(status, content_child, new_length) f_macro_fss_content_adjust(status, content_child.content, new_length);

#endif // _di_fss_content_child_

/**
 * This holds an array of fss_content_child.
 *
 * This is designed to be used as a part of f_fss_content_nest.
 * Range represents the full range of the particular content set.
 * Range can exist before the first child and after the last child to represent unnested data within the content.
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
 * range: A location range representing the full start/stop locations of the entire set.
 * array: The array of objectm their associated content, and their associated parent.
 * size: Total amount of allocated space.
 * used: Total number of allocated spaces used.
 */
#ifndef _di_fss_content_childs_
  typedef struct {
    f_string_location   range;
    f_fss_content_child *array;
    f_array_length      size;
    f_array_length      used;
  } f_fss_content_childs;

  #define f_fss_content_childs_initialize { f_string_location_initialize, 0, 0, 0 }

  /**
   * Reset a fss content childs to 0 (clear all values).
   *
   * This does not deallocate memory, be certain that memory is not allocated before calling this to avoid potential memory leaks.
   *
   * content_childs: the f_fss_content_childs structure to operate on.
   */
  #define f_macro_fss_content_childs_clear(content_childs) \
    content_childs.range.start = 1; \
    content_childs.range_stop = 0; \
    content_childs.array = 0; \
    content_childs.size = 0; \
    content_childs.used = 0;

  /**
   * Create a new fss content childs.
   *
   * This does not deallocate memory, be certain that memory is not allocated before calling this to avoid potential memory leaks.
   *
   * status:         the status to return.
   * content_childs: the f_fss_content_childs structure to operate on.
   * new_length:     the new size of the array.
   */
  #define f_macro_fss_content_childs_new(status, content_childs, length) \
    content_childs.range.start = 1; \
    content_childs.range_stop = 0; \
    content_childs.array = 0; \
    content_childs.size = 0; \
    content_childs.used = 0; \
    status = f_memory_new((void **) & content_childs.array, sizeof(f_fss_content_child), new_length); \
    if (status == f_none) { \
      content_childs.size = new_length; \
      content_childs.used = 0; \
    }

  /**
   * Delete a fss content childs.
   *
   * status:         the status to return.
   * content_childs: the f_fss_content_childs structure to operate on.
   */
  #define f_macro_fss_content_childs_delete(status, content_childs) \
    status = f_none; \
    while (content_childs.size > 0) { \
      f_macro_fss_content_child_delete(status, content_childs.array[content_childs.size - 1]); \
      if (status != f_none) break; \
      content_childs.size--; \
    } \
    if (status == f_none) status = f_memory_delete((void **) & content_childs.array, sizeof(f_fss_content_child), content_childs.size); \
    if (status == f_none) content_childs.used = 0;

  /**
   * Destroy a fss content childs.
   *
   * status:         the status to return.
   * content_childs: the f_fss_content_childs structure to operate on.
   */
  #define f_macro_fss_content_childs_destroy(status, content_childs) \
    status = f_none; \
    while (content_childs.size > 0) { \
      f_macro_fss_content_child_destroy(status, content_childs.array[content_childs.size - 1]); \
      if (status != f_none) break; \
      content_childs.size--; \
    } \
    if (status == f_none) status = f_memory_delete((void **) & content_childs.array, sizeof(f_fss_content_child), content_childs.size); \
    if (status == f_none) content_childs.used = 0;

  /**
   * Resize a fss content childs.
   *
   * status:         the status to return.
   * content_childs: the f_fss_content_childs structure to operate on.
   * new_length:     the new size of the array.
   */
  #define f_macro_fss_content_childs_resize(status, content_childs, new_length) \
    status = f_none; \
    if (new_length < content_childs.size) { \
      f_array_length i = content_childs.size - new_length; \
      for (; i < content_childs.size; i++) { \
        f_macro_fss_content_child_delete(status, content_childs.array[i]); \
        if (status != f_none) break; \
      } \
    } \
    if (status == f_none) status = f_memory_resize((void **) & content_childs.array, sizeof(f_fss_content_child), content_childs.size, new_length); \
    if (status == f_none) { \
      if (new_length > content_childs.size) { \
        f_array_length i = content_childs.size; \
        for (; i < new_length; i++) { \
          memset(&content_childs.array[i], 0, sizeof(f_fss_content_child)); \
        } \
      } \
      content_childs.range.start = 1; \
      content_childs.range.stop = 0; \
      content_childs.size = new_length; \
      if (content_childs.used > content_childs.size) content_childs.used = new_length; \
    }

  /**
   * Adjust a fss content childs.
   *
   * status:         the status to return.
   * content_childs: the f_fss_content_childs structure to operate on.
   * new_length:     the new size of the array.
   */
  #define f_macro_fss_content_childs_adjust(status, content_childs, new_length) \
    status = f_none; \
    if (new_length < content_childs.size) { \
      length_variable i = content_childs.size - new_length; \
      for (; i < content_childs.size; i++) { \
        f_macro_fss_content_child_destroy(status, content_childs.array[i]); \
        if (status != f_none) break; \
      } \
    } \
    if (status == f_none) status = f_memory_adjust((void **) & content_childs.array, sizeof(f_fss_content_child), content_childs.size, new_length); \
    if (status == f_none) { \
      if (new_length > content_childs.size) { \
        length_variable i = content_childs.size; \
        for (; i < new_length; i++) { \
          memset(&content_childs.array[i], 0, sizeof(f_fss_content_child)); \
        } \
      } \
      content_childs.range.start = 1; \
      content_childs.range_stop = 0; \
      content_childs.size = new_length; \
      if (content_childs.used > content_childs.size) content_childs.used = new_length; \
    }
#endif // _di_fss_content_childs_

/**
 * This holds an array of f_fss_content_childs.
 *
 * Each array row represents the nesting depth.
 * The top-level will not have any parent, so "parent" must be ignored on anything at index 0.
 * The parent identifier is expected to reference a position in the nesting depth immediately above it.
 *
 * array: an array of f_fss_content_childs objects.
 * size: Total amount of allocated space.
 * used: Total number of allocated spaces used.
 */
#ifndef _di_fss_content_nest_
  typedef struct {
    f_fss_content_childs *array;
    f_array_length       size;
    f_array_length       used;
  } f_fss_content_nest;

  #define f_fss_content_nest_initialize { 0, 0, 0 }

  /**
   * Reset a fss content nest to 0 (clear all values).
   *
   * This does not deallocate memory, be certain that memory is not allocated before calling this to avoid potential memory leaks.
   *
   * content_nest: the f_fss_content_nest structure to operate on.
   */
  #define f_macro_fss_content_nest_clear(content_nest) \
    content_nest.array = 0; \
    content_nest.size = 0; \
    content_nest.used = 0;

  /**
   * Create a new fss content nest.
   *
   * This does not deallocate memory, be certain that memory is not allocated before calling this to avoid potential memory leaks.
   *
   * status:       the status to return.
   * content_nest: the f_fss_content_nest structure to operate on.
   * new_length:   the new size of the array.
   */
  #define f_macro_fss_content_nest_new(status, content_nest, length) \
    content_nest.array = 0; \
    content_nest.size = 0; \
    content_nest.used = 0; \
    status = f_memory_new((void **) & content_nest.array, sizeof(f_fss_content_childs), new_length); \
    if (status == f_none) { \
      content_nest.size = new_length; \
      content_nest.used = 0; \
    }

  /**
   * Delete a fss content nest.
   *
   * status:       the status to return.
   * content_nest: the f_fss_content_nest structure to operate on.
   */
  #define f_macro_fss_content_nest_delete(status, content_nest) \
    status = f_none; \
    while (content_nest.size > 0) { \
      f_macro_fss_content_childs_delete(status, content_nest.array[content_nest.size - 1]); \
      if (status != f_none) break; \
      content_nest.size--; \
    } \
    if (status == f_none) status = f_memory_delete((void **) & content_nest.array, sizeof(f_fss_content_childs), content_nest.size); \
    if (status == f_none) content_nest.used = 0;

  /**
   * Destroy a fss content nest.
   *
   * status:       the status to return.
   * content_nest: the f_fss_content_nest structure to operate on.
   */
  #define f_macro_fss_content_nest_destroy(status, content_nest) \
    status = f_none; \
    while (content_nest.size > 0) { \
      f_macro_fss_content_childs_destroy(status, content_nest.array[content_nest.size - 1]); \
      if (status != f_none) break; \
      content_nest.size--; \
    } \
    if (status == f_none) status = f_memory_delete((void **) & content_nest.array, sizeof(f_fss_content_childs), content_nest.size); \
    if (status == f_none) content_nest.used = 0;

  /**
   * Resize a fss content nest.
   *
   * status:       the status to return.
   * content_nest: the f_fss_content_nest structure to operate on.
   * new_length:   the new size of the array.
   */
  #define f_macro_fss_content_nest_resize(status, content_nest, new_length) \
    status = f_none; \
    if (new_length < content_nest.size) { \
      f_array_length i = content_nest.size - new_length; \
      for (; i < content_nest.size; i++) { \
        f_macro_fss_content_childs_delete(status, content_nest.array[i]); \
        if (status != f_none) break; \
      } \
    } \
    if (status == f_none) status = f_memory_resize((void **) & content_nest.array, sizeof(f_fss_content_childs), content_nest.size, new_length); \
    if (status == f_none) { \
      if (new_length > content_nest.size) { \
        f_array_length i = content_nest.size; \
        for (; i < new_length; i++) { \
          memset(&content_nest.array[i], 0, sizeof(f_fss_content_childs)); \
        } \
      } \
      content_nest.size = new_length; \
      if (content_nest.used > content_nest.size) content_nest.used = new_length; \
    }

  /**
   * Adjust a fss content nest.
   *
   * status:       the status to return.
   * content_nest: the f_fss_content_nest structure to operate on.
   * new_length:   the new size of the array.
   */
  #define f_macro_fss_content_nest_adjust(status, content_nest, new_length) \
    status = f_none; \
    if (new_length < content_nest.size) { \
      f_array_length i = content_nest.size - new_length; \
      for (; i < content_nest.size; i++) { \
        f_macro_fss_content_childs_destroy(status, content_nest.array[i]); \
        if (status != f_none) break; \
      } \
    } \
    if (status == f_none) status = f_memory_adjust((void **) & content_nest.array, sizeof(f_fss_content_child), content_nest.size, new_length); \
    if (status == f_none) { \
      if (new_length > content_nest.size) { \
        f_array_length i = content_nest.size; \
        for (; i < new_length; i++) { \
          memset(&content_childs.array[i], 0, sizeof(f_fss_content_child)); \
        } \
      } \
      content_nest.size = new_length; \
      if (content_nest.used > content_nest.size) content_nest.used = new_length; \
    }
#endif // _di_fss_content_nest_

/**
 * This holds an array of f_fss_content_nest.
 *
 * array: an array of f_fss_content_nest objects.
 * size: Total amount of allocated space.
 * used: Total number of allocated spaces used.
 */
#ifndef _di_fss_content_nests_
  typedef struct {
    f_fss_content_nest *array;
    f_array_length     size;
    f_array_length     used;
  } f_fss_content_nests;

  #define f_fss_content_nests_initialize { 0, 0, 0 }

  /**
   * Reset a fss content nests to 0 (clear all values).
   *
   * This does not deallocate memory, be certain that memory is not allocated before calling this to avoid potential memory leaks.
   *
   * content_nests: the f_fss_content_nests structure to operate on.
   */
  #define f_macro_fss_content_nests_clear(content_nests) \
    content_nests.array = 0; \
    content_nests.size = 0; \
    content_nests.used = 0;

  /**
   * Create a new fss content nests.
   *
   * This does not deallocate memory, be certain that memory is not allocated before calling this to avoid potential memory leaks.
   *
   * status:        the status to return.
   * content_nests: the f_fss_content_nests structure to operate on.
   * new_length:    the new size of the array.
   */
  #define f_macro_fss_content_nests_new(status, content_nests, length) \
    content_nests.array = 0; \
    content_nests.size = 0; \
    content_nests.used = 0; \
    status = f_memory_new((void **) & content_nests.array, sizeof(f_fss_content_nest), new_length); \
    if (status == f_none) { \
      content_nests.size = new_length; \
      content_nests.used = 0; \
    }

  /**
   * Delete a fss content nests.
   *
   * status:        the status to return.
   * content_nests: the f_fss_content_nests structure to operate on.
   */
  #define f_macro_fss_content_nests_delete(status, content_nests) \
    status = f_none; \
    while (content_nests.size > 0) { \
      f_macro_fss_content_nest_delete(status, content_nests.array[content_nests.size - 1]); \
      if (status != f_none) break; \
      content_nests.size--; \
    } \
    if (status == f_none) status = f_memory_delete((void **) & content_nests.array, sizeof(f_fss_content_nest), content_nests.size); \
    if (status == f_none) content_nests.used = 0;

  /**
   * Destroy a fss content nests.
   *
   * status:        the status to return.
   * content_nests: the f_fss_content_nests structure to operate on.
   */
  #define f_macro_fss_content_nests_destroy(status, content_nests) \
    status = f_none; \
    while (content_nests.size > 0) { \
      f_macro_fss_content_nest_destroy(status, content_nests.array[content_nests.size - 1]); \
      if (status != f_none) break; \
      content_nests.size--; \
    } \
    if (status == f_none) status = f_memory_delete((void **) & content_nests.array, sizeof(f_fss_content_nest), content_nests.size); \
    if (status == f_none) content_nests.used = 0;

  /**
   * Resize a fss content nests.
   *
   * status:        the status to return.
   * content_nests: the f_fss_content_nests structure to operate on.
   * new_length:    the new size of the array.
   */
  #define f_macro_fss_content_nests_resize(status, content_nests, new_length) \
    status = f_none; \
    if (new_length < content_nests.size) { \
      f_array_length i = content_nests.size - new_length; \
      for (; i < content_nests.size; i++) { \
        f_macro_fss_content_nest_delete(status, content_nests.array[i]); \
        if (status != f_none) break; \
      } \
    } \
    if (status == f_none) status = f_memory_resize((void **) & content_nests.array, sizeof(f_fss_content_nest), content_nests.size, new_length); \
    if (status == f_none) { \
      if (new_length > content_nests.size) { \
        f_array_length i = content_nests.size; \
        for (; i < new_length; i++) { \
          memset(&content_nests.array[i], 0, sizeof(f_fss_content_nest)); \
        } \
      } \
      content_nests.size = new_length; \
      if (content_nests.used > content_nests.size) content_nests.used = new_length; \
    }

  /**
   * Adjust a fss content nests.
   *
   * status:        the status to return.
   * content_nests: the f_fss_content_nests structure to operate on.
   * new_length:    the new size of the array.
   */
  #define f_macro_fss_content_nests_adjust(status, content_nests, new_length) \
    status = f_none; \
    if (new_length < content_nests.size) { \
      f_array_length i = content_nests.size - new_length; \
      for (; i < content_nests.size; i++) { \
        f_macro_fss_content_nest_destroy(status, content_nests.array[i]); \
        if (status != f_none) break; \
      } \
    } \
    if (status == f_none) status = f_memory_adjust((void **) & content_nests.array, sizeof(f_fss_content_nest), content_nests.size, new_length); \
    if (status == f_none) { \
      if (new_length > content_nests.size) { \
        f_array_length i = content_nests.size; \
        for (; i < new_length; i++) { \
          memset(&content_nests.array[i], 0, sizeof(f_fss_content_nest)); \
        } \
      } \
      content_nests.size = new_length; \
      if (content_nests.used > content_nests.size) content_nests.used = new_length; \
    }
#endif // _di_fss_content_nests_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_h
