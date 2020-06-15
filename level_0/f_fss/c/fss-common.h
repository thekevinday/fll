/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines common data to be used for/by project fss.
 *
 * This is auto-included by fss.h and should not need to be explicitly included.
 */
#ifndef _F_fss_common_h
#define _F_fss_common_h

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

  #define f_macro_fss_object_clear(object) f_macro_string_range_clear(object)
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

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_common_h
