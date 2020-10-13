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
#ifndef _di_f_fss_types_t_
  #define f_fss_comment                 '#'
  #define f_fss_eol                     f_string_eol[0]
  #define f_fss_space                   ' '
  #define f_fss_space_holder            '_'
  #define f_fss_basic_open              ' '
  #define f_fss_basic_close             f_string_eol[0]
  #define f_fss_extended_open           ' '
  #define f_fss_extended_next           ' '
  #define f_fss_extended_close          f_string_eol[0]
  #define f_fss_basic_list_open         ':'
  #define f_fss_basic_list_open_end     f_string_eol[0]
  #define f_fss_basic_list_close        f_string_eol[0]
  #define f_fss_extended_list_open      '{'
  #define f_fss_extended_list_open_end  f_string_eol[0]
  #define f_fss_extended_list_close     '}'
  #define f_fss_extended_list_close_end f_string_eol[0]
  #define f_fss_type_header_open        '#'
  #define f_fss_type_header_part1       ' '
  #define f_fss_type_header_part2       'f'
  #define f_fss_type_header_part3       's'
  #define f_fss_type_header_part4       's'
  #define f_fss_type_header_part5       '-'
  #define f_fss_type_header_close       f_string_eol[0]

  typedef unsigned long f_fss_id_t;
#endif // _di_f_fss_types_t_

/**
 * FSS-specific delimiters.
 */
#ifndef _di_f_fss_delimiters_
  #define f_fss_delimit_placeholder  f_string_placeholder[0]
  #define f_fss_delimit_quote_single '\''
  #define f_fss_delimit_quote_double '"'
  #define f_fss_delimit_slash        '\\'
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
 * Codes for FSS completeness.
 *
 * The details on how these work are specific to individual specifications.
 * The notes below provide the intended purpose but be sure to still read the individual function documentation.
 *
 * Only "next" and "end" are only meaningful for a Content and will be treated as "none" for an Object.
 *
 * none:         disable completeness.
 * end:          complete as if this is the final piece of a set (such as FSS-0001, adding terminating EOL).
 * full:         complete and add terminating EOL, where applicable.
 * full_trim:    complete and add terminating EOL but remove any leading or trailing whitespace, where applicable.
 * next:         complete as if this is a piece of a set (such as FSS-0001, adding a separating space).
 * partial:      complete, but do not add terminating EOL, where applicable.
 * partial_trim: complete, but do not add terminating EOL and remove any leading or trailing whitespace, where applicable.
 */
#ifndef _di_f_fss_complete_
  enum {
    f_fss_complete_none = 1,
    f_fss_complete_end,
    f_fss_complete_full,
    f_fss_complete_full_trim,
    f_fss_complete_next,
    f_fss_complete_partial,
    f_fss_complete_partial_trim,
  };
#endif // _di_f_fss_complete_

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
  // recommended to be set to at least 4 to be UTF-8 friendlier.
  #define f_fss_default_allocation_step f_memory_default_allocation_step
#endif // _di_f_fss_default_allocation_step_

/**
 * An array of string locations representing where a delimit was applied or is to be applied with respect to some string.
 */
#ifndef _di_f_fss_delimits_t_
  typedef f_string_ranges_t f_fss_delimits_t;

  #define f_fss_delimits_initialize f_string_ranges_t_initialize

  #define f_macro_fss_delimits_clear(delimits) f_macro_memory_structure_t_clear(delimits)

  #define f_macro_fss_delimits_new(status, delimits)     f_macro_string_ranges_t_new(status, delimits)
  #define f_macro_fss_delimits_delete(status, delimits)  f_macro_string_ranges_t_delete(status, delimits)
  #define f_macro_fss_delimits_destroy(status, delimits) f_macro_string_ranges_t_destroy(status, delimits)

  #define f_macro_fss_delimits_delete_simple(delimits)  f_macro_string_ranges_t_delete_simple(delimits)
  #define f_macro_fss_delimits_destroy_simple(delimits) f_macro_string_ranges_t_destroy_simple(delimits)

  #define f_macro_fss_delimits_resize(status, delimits, new_length) f_macro_string_ranges_t_resize(status, delimits, new_length)
  #define f_macro_fss_delimits_adjust(status, delimits, new_length) f_macro_string_ranges_t_adjust(status, delimits, new_length)
#endif // _di_f_fss_delimits_t_

/**
 * Stores information about a particular fss file, otherwise known as its header.
 *
 * @todo change this to use a range instead if a length to support multiple sub-headers.
 *
 * type:   the kind of fss file is this.
 * length: Total length of the header.
 */
#ifndef _di_f_fss_header_t_
  typedef struct {
    f_fss_id_t type;

    f_string_length_t length;
  } f_fss_header_t;

  #define f_fss_header_initialize { 0, 0 }
#endif // _di_f_fss_header_t_

/**
 * This holds an array of fss_headers.
 *
 * array: The array of headers.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fss_headers_t_
  typedef struct {
    f_fss_header_t *array;

    f_string_length_t size;
    f_string_length_t used;
  } f_fss_headers_t;

  #define f_fss_headers_initialize { 0, 0, 0 }

  #define f_macro_fss_headers_clear(headers) f_macro_memory_structure_t_clear(headers)

  #define f_macro_fss_headers_new(status, headers, length) f_macro_memory_structure_t_new(status, headers, f_fss_header_t, length)

  #define f_macro_fss_headers_delete(status, headers)  f_macro_memory_structure_t_delete(status, headers, f_fss_header_t)
  #define f_macro_fss_headers_destroy(status, headers) f_macro_memory_structure_t_destroy(status, headers, f_fss_header_t)

  #define f_macro_fss_headers_delete_simple(headers)  f_macro_memory_structure_t_delete_simple(headers, f_fss_header_t)
  #define f_macro_fss_headers_destroy_simple(headers) f_macro_memory_structure_t_destroy_simple(headers, f_fss_header_t)

  #define f_macro_fss_headers_resize(status, headers, new_length) f_macro_memory_structure_t_resize(status, headers, f_fss_header_t, new_length)
  #define f_macro_fss_headers_adjust(status, headers, new_length) f_macro_memory_structure_t_adjust(status, headers, f_fss_header_t, new_length)
#endif // _di_f_fss_headers_t_

/**
 * This is a range that represents an object.
 */
#ifndef _di_fss_object_t_
  typedef f_string_range_t f_fss_object_t;

  #define f_fss_object_t_initialize f_string_range_t_initialize

  #define f_macro_fss_object_t_clear(object) f_macro_string_range_t_clear(object)
#endif // _di_fss_object_t_

/**
 * This holds an array of fss_object.
 *
 * array: The array of objects.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_fss_objects_t_
  typedef f_string_ranges_t f_fss_objects_t;

  #define f_fss_objects_t_initialize f_string_ranges_t_initialize

  #define f_macro_fss_objects_t_clear(objects) f_macro_string_ranges_t_clear(objects)

  #define f_macro_fss_objects_t_new(status, objects, length) f_macro_string_ranges_t_new(status, objects, length)

  #define f_macro_fss_objects_t_delete(status, objects)  f_macro_string_ranges_t_delete(status, objects)
  #define f_macro_fss_objects_t_destroy(status, objects) f_macro_string_ranges_t_destroy(status, objects)

  #define f_macro_fss_objects_t_delete_simple(objects)  f_macro_string_ranges_t_delete_simple(objects)
  #define f_macro_fss_objects_t_destroy_simple(objects) f_macro_string_ranges_t_destroy_simple(objects)

  #define f_macro_fss_objects_t_resize(status, objects, new_length) f_macro_string_ranges_t_resize(status, objects, new_length)
  #define f_macro_fss_objects_t_adjust(status, objects, new_length) f_macro_string_ranges_t_destroy(status, objects, new_length)
#endif // _di_fss_objects_t_

/**
 * This holds an array of string ranges that represent the content.
 *
 * The very first string range will represent the first content found.
 *
 * array: The array of content.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_fss_content_
  typedef f_string_ranges_t f_fss_content_t;

  #define f_fss_content_t_initialize f_string_ranges_t_initialize

  #define f_macro_fss_content_t_clear(content) f_macro_string_ranges_t_clear(content)

  #define f_macro_fss_content_t_new(status, content, length) f_macro_string_ranges_t_new(status, content, length)

  #define f_macro_fss_content_t_delete(status, content)  f_macro_string_ranges_t_delete(status, content)
  #define f_macro_fss_content_t_destroy(status, content) f_macro_string_ranges_t_destroy(status, content)

  #define f_macro_fss_content_t_delete_simple(content)  f_macro_string_ranges_t_delete_simple(content)
  #define f_macro_fss_content_t_destroy_simple(content) f_macro_string_ranges_t_destroy_simple(content)

  #define f_macro_fss_content_t_resize(status, content, new_length) f_macro_string_ranges_t_resize(status, content, new_length)
  #define f_macro_fss_content_t_adjust(status, content, new_length) f_macro_string_ranges_t_adjust(status, content, new_length)
#endif // _di_fss_content_

/**
 * This holds an array of fss_content.
 *
 * array: The array of content arrays.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fss_contents_t_
  typedef f_string_rangess_t f_fss_contents_t;

  #define f_fss_contents_t_initialize f_string_rangess_t_initialize

  #define f_macro_fss_contents_t_clear(contents) f_macro_string_rangess_t_clear(contents)

  #define f_macro_fss_contents_t_new(status, contents, length) f_macro_string_rangess_t_new(status, contents, length)

  #define f_macro_fss_contents_t_delete(status, contents)  f_macro_string_rangess_t_delete(status, contents)
  #define f_macro_fss_contents_t_destroy(status, contents) f_macro_string_rangess_t_destroy(status, contents)

  #define f_macro_fss_contents_t_delete_simple(contents)  f_macro_string_rangess_t_delete_simple(contents)
  #define f_macro_fss_contents_t_destroy_simple(contents) f_macro_string_rangess_t_destroy_simple(contents)

  #define f_macro_fss_contents_t_resize(status, contents, new_length) f_macro_string_rangess_t_resize(status, contents, new_length)
  #define f_macro_fss_contents_t_adjust(status, contents, new_length) f_macro_string_rangess_t_adjust(status, contents, new_length)
#endif // _di_f_fss_contents_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_common_h
