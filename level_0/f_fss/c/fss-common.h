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
  extern const f_string_t f_fss_brace_left_s;
  extern const f_string_t f_fss_brace_right_s;
  extern const f_string_t f_fss_colon_s;
  extern const f_string_t f_fss_dash_s;
  extern const f_string_t f_fss_f_s;
  extern const f_string_t f_fss_pound_s;
  extern const f_string_t f_fss_quote_single_s;
  extern const f_string_t f_fss_quote_double_s;
  extern const f_string_t f_fss_s_s;
  extern const f_string_t f_fss_slash_s;
  extern const f_string_t f_fss_space_s;
  extern const f_string_t f_fss_underscore_s;

  #define f_fss_comment                 f_fss_pound_s[0]
  #define f_fss_eol                     f_string_eol_s[0]
  #define f_fss_space                   f_fss_space_s[0]
  #define f_fss_space_holder            f_fss_underscore_s[0]
  #define f_fss_basic_open              f_fss_space_s[0]
  #define f_fss_basic_close             f_string_eol_s[0]
  #define f_fss_extended_open           f_fss_space_s[0]
  #define f_fss_extended_next           f_fss_space_s[0]
  #define f_fss_extended_close          f_string_eol_s[0]
  #define f_fss_basic_list_open         f_fss_colon_s[0]
  #define f_fss_basic_list_open_end     f_string_eol_s[0]
  #define f_fss_basic_list_close        f_string_eol_s[0]
  #define f_fss_extended_list_open      f_fss_brace_left_s[0]
  #define f_fss_extended_list_open_end  f_string_eol_s[0]
  #define f_fss_extended_list_close     f_fss_brace_right_s[0]
  #define f_fss_extended_list_close_end f_string_eol_s[0]
  #define f_fss_embedded_list_open      f_fss_brace_left_s[0]
  #define f_fss_embedded_list_open_end  f_string_eol_s[0]
  #define f_fss_embedded_list_close     f_fss_brace_right_s[0]
  #define f_fss_embedded_list_close_end f_string_eol_s[0]
  #define f_fss_type_header_open        f_fss_pound_s[0]
  #define f_fss_type_header_part1       f_fss_space_s[0]
  #define f_fss_type_header_part2       f_fss_f_s[0]
  #define f_fss_type_header_part3       f_fss_s_s[0]
  #define f_fss_type_header_part4       f_fss_s_s[0]
  #define f_fss_type_header_part5       f_fss_dash_s[0]
  #define f_fss_type_header_close       f_string_eol_s[0]

  typedef uint64_t f_fss_id_t;
#endif // _di_f_fss_types_t_

/**
 * FSS-specific delimiters.
 */
#ifndef _di_f_fss_delimiters_
  #define f_fss_delimit_placeholder  f_string_placeholder[0]
  #define f_fss_delimit_quote_single f_fss_quote_single_s[0]
  #define f_fss_delimit_quote_double f_fss_quote_double_s[0]
  #define f_fss_delimit_slash        f_fss_slash_s[0]
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
    f_fss_simple_list,
    f_fss_iki_text,
    f_fss_basic_rule,
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
 * none:         Disable completeness.
 * end:          Complete as if this is the final piece of a set (such as FSS-0001, adding terminating EOL).
 * full:         Complete and add terminating EOL, where applicable.
 * full_trim:    Complete and add terminating EOL but remove any leading or trailing whitespace, where applicable.
 * next:         Complete as if this is a piece of a set (such as FSS-0001, adding a separating space).
 * partial:      Complete, but do not add terminating EOL, where applicable.
 * partial_trim: Complete, but do not add terminating EOL and remove any leading or trailing whitespace, where applicable.
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
 *
 * Recommended to be set to at least 4 to be UTF-8 friendlier.
 */
#ifndef _di_f_fss_default_allocation_step_
  #define f_fss_default_allocation_step f_memory_default_allocation_small
#endif // _di_f_fss_default_allocation_step_

/**
 * Stores information about a particular fss file, otherwise known as its header.
 *
 * @todo change this to use a range instead if a length to support multiple sub-headers.
 *
 * type:   The kind of fss file is this.
 * length: Total length of the header.
 */
#ifndef _di_f_fss_header_t_
  typedef struct {
    f_fss_id_t type;

    f_array_length_t length;
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

    f_array_length_t size;
    f_array_length_t used;
  } f_fss_headers_t;

  #define f_fss_headers_t_initialize { 0, 0, 0 }

  #define macro_f_fss_headers_t_clear(headers) macro_f_memory_structure_clear(headers)

  #define macro_f_fss_headers_t_resize(status, headers, length) macro_f_memory_structure_resize(status, headers, f_fss_header_t, length)
  #define macro_f_fss_headers_t_adjust(status, headers, length) macro_f_memory_structure_adjust(status, headers, f_fss_header_t, length)

  #define macro_f_fss_headers_t_delete_simple(headers)  macro_f_memory_structure_delete_simple(headers, f_fss_header_t)
  #define macro_f_fss_headers_t_destroy_simple(headers) macro_f_memory_structure_destroy_simple(headers, f_fss_header_t)

  #define macro_f_fss_headers_t_increase(status, step, headers)      macro_f_memory_structure_increase(status, step, headers, f_fss_header_t)
  #define macro_f_fss_headers_t_increase_by(status, headers, amount) macro_f_memory_structure_increase_by(status, headers, f_fss_header_t, amount)
  #define macro_f_fss_headers_t_decrease_by(status, headers, amount) macro_f_memory_structure_decrease_by(status, headers, f_fss_header_t, amount)
  #define macro_f_fss_headers_t_decimate_by(status, headers, amount) macro_f_memory_structure_decimate_by(status, headers, f_fss_header_t, amount)
#endif // _di_f_fss_headers_t_

/**
 * This is a range that represents an object.
 */
#ifndef _di_fss_object_t_
  typedef f_string_range_t f_fss_object_t;

  #define f_fss_object_t_initialize f_string_range_t_initialize

  #define macro_f_fss_object_t_clear(object) macro_f_string_range_t_clear(object)
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

  #define macro_f_fss_objects_t_clear(objects) macro_f_string_ranges_t_clear(objects)

  #define macro_f_fss_objects_t_resize(status, objects, length) macro_f_string_ranges_t_resize(status, objects, length)
  #define macro_f_fss_objects_t_adjust(status, objects, length) macro_f_string_ranges_t_adjust(status, objects, length)

  #define macro_f_fss_objects_t_delete_simple(objects)  macro_f_string_ranges_t_delete_simple(objects)
  #define macro_f_fss_objects_t_destroy_simple(objects) macro_f_string_ranges_t_destroy_simple(objects)

  #define macro_f_fss_objects_t_increase(status, step, objects)      macro_f_string_ranges_t_increase(status, step, objects)
  #define macro_f_fss_objects_t_increase_by(status, objects, amount) macro_f_string_ranges_t_increase_by(status, objects, amount)
  #define macro_f_fss_objects_t_decrease_by(status, objects, amount) macro_f_string_ranges_t_decrease_by(status, objects, amount)
  #define macro_f_fss_objects_t_decimate_by(status, objects, amount) macro_f_string_ranges_t_decimate_by(status, objects, amount)
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

  #define macro_f_fss_content_t_clear(content) macro_f_string_ranges_t_clear(content)

  #define macro_f_fss_content_t_resize(status, content, length) macro_f_string_ranges_t_resize(status, content, length)
  #define macro_f_fss_content_t_adjust(status, content, length) macro_f_string_ranges_t_adjust(status, content, length)

  #define macro_f_fss_content_t_delete_simple(content)  macro_f_string_ranges_t_delete_simple(content)
  #define macro_f_fss_content_t_destroy_simple(content) macro_f_string_ranges_t_destroy_simple(content)

  #define macro_f_fss_content_t_increase(status, step, content)      macro_f_string_ranges_t_increase(status, step, content)
  #define macro_f_fss_content_t_increase_by(status, content, amount) macro_f_string_ranges_t_increase_by(status, content, amount)
  #define macro_f_fss_content_t_decrease_by(status, content, amount) macro_f_string_ranges_t_decrease_by(status, content, amount)
  #define macro_f_fss_content_t_decimate_by(status, content, amount) macro_f_string_ranges_t_decimate_by(status, content, amount)
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

  #define macro_f_fss_contents_t_clear(contents) macro_f_string_rangess_t_clear(contents)

  #define macro_f_fss_contents_t_resize(status, contents, length) macro_f_string_rangess_t_resize(status, contents, length)
  #define macro_f_fss_contents_t_adjust(status, contents, length) macro_f_string_rangess_t_adjust(status, contents, length)

  #define macro_f_fss_contents_t_delete_simple(contents)  macro_f_string_rangess_t_delete_simple(contents)
  #define macro_f_fss_contents_t_destroy_simple(contents) macro_f_string_rangess_t_destroy_simple(contents)

  #define macro_f_fss_contents_t_increase(status, step, contents)            macro_f_string_rangess_t_increase(status, step, contents)
  #define macro_f_fss_contents_t_increase_by(status, contents, amount) macro_f_string_rangess_t_increase_by(status, contents, amount)
  #define macro_f_fss_contents_t_decrease_by(status, contents, amount) macro_f_string_rangess_t_decrease_by(status, contents, amount)
  #define macro_f_fss_contents_t_decimate_by(status, contents, amount) macro_f_string_rangess_t_decimate_by(status, contents, amount)
#endif // _di_f_fss_contents_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_common_h
