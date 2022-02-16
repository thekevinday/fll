/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
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
  #define F_fss_brace_close_s  F_string_ascii_brace_close_s
  #define F_fss_brace_open_s   F_string_ascii_brace_open_s
  #define F_fss_colon_s        F_string_ascii_colon_s
  #define F_fss_minus_s        F_string_ascii_minus_s
  #define F_fss_f_s            F_string_ascii_f_s
  #define F_fss_pound_s        F_string_ascii_pound_s
  #define F_fss_quote_double_s F_string_ascii_quote_double_s
  #define F_fss_quote_single_s F_string_ascii_quote_single_s
  #define F_fss_s_s            F_string_ascii_s_s
  #define F_fss_slash_s        F_string_ascii_slash_backward_s
  #define F_fss_space_s        F_string_ascii_space_s
  #define F_fss_underscore_s   F_string_ascii_underscore_s

  #define F_fss_brace_close_s_length  F_string_ascii_brace_close_s_length
  #define F_fss_brace_open_s_length   F_string_ascii_brace_open_s_length
  #define F_fss_colon_s_length        F_string_ascii_colon_s_length
  #define F_fss_minus_s_length        F_string_ascii_minus_s_length
  #define F_fss_f_s_length            F_string_ascii_f_s_length
  #define F_fss_pound_s_length        F_string_ascii_pound_s_length
  #define F_fss_quote_double_s_length F_string_ascii_quote_double_s_length
  #define F_fss_quote_single_s_length F_string_ascii_quote_single_s_length
  #define F_fss_s_s_length            F_string_ascii_s_s_length
  #define F_fss_slash_s_length        F_string_ascii_slash_backward_s_length
  #define F_fss_space_s_length        F_string_ascii_space_s_length
  #define F_fss_underscore_s_length   F_string_ascii_underscore_s_length

  #define f_fss_brace_close_s  f_string_ascii_brace_close_s
  #define f_fss_brace_open_s   f_string_ascii_brace_open_s
  #define f_fss_colon_s        f_string_ascii_colon_s
  #define f_fss_minus_s        f_string_ascii_minus_s
  #define f_fss_f_s            f_string_ascii_f_s
  #define f_fss_pound_s        f_string_ascii_pound_s
  #define f_fss_quote_double_s f_string_ascii_quote_double_s
  #define f_fss_quote_single_s f_string_ascii_quote_single_s
  #define f_fss_s_s            f_string_ascii_s_s
  #define f_fss_slash_s        f_string_ascii_slash_backward_s
  #define f_fss_space_s        f_string_ascii_space_s
  #define f_fss_underscore_s   f_string_ascii_underscore_s

  #define f_fss_comment_s                 f_fss_pound_s
  #define f_fss_eol_s                     f_string_eol_s
  #define f_fss_space_holder_s            f_fss_underscore_s
  #define f_fss_basic_open_s              f_fss_space_s
  #define f_fss_basic_close_s             f_string_eol_s
  #define f_fss_extended_open_s           f_fss_space_s
  #define f_fss_extended_next_s           f_fss_space_s
  #define f_fss_extended_close_s          f_string_eol_s
  #define f_fss_basic_list_open_s         f_fss_colon_s
  #define f_fss_basic_list_open_end_s     f_string_eol_s
  #define f_fss_basic_list_close_s        f_string_eol_s
  #define f_fss_extended_list_open_s      f_fss_brace_open_s
  #define f_fss_extended_list_open_end_s  f_string_eol_s
  #define f_fss_extended_list_close_s     f_fss_brace_close_s
  #define f_fss_extended_list_close_end_s f_string_eol_s
  #define f_fss_embedded_list_open_s      f_fss_brace_open_s
  #define f_fss_embedded_list_open_end_s  f_string_eol_s
  #define f_fss_embedded_list_close_s     f_fss_brace_close_s
  #define f_fss_embedded_list_close_end_s f_string_eol_s
  #define f_fss_type_header_open_s        f_fss_pound_s
  #define f_fss_type_header_part1_s       f_fss_space_s
  #define f_fss_type_header_part2_s       f_fss_f_s
  #define f_fss_type_header_part3_s       f_fss_s_s
  #define f_fss_type_header_part4_s       f_fss_s_s
  #define f_fss_type_header_part5_s       f_fss_minus_s
  #define f_fss_type_header_close_s       f_string_eol_s
#endif // _di_f_fss_types_t_

/**
 * FSS-specific delimiters.
 */
#ifndef _di_f_fss_delimiters_
  #define F_fss_delimit_placeholder_s  F_string_placeholder_s
  #define F_fss_delimit_quote_single_s F_fss_quote_single_s
  #define F_fss_delimit_quote_double_s F_fss_quote_double_s
  #define F_fss_delimit_slash_s        F_fss_slash_s

  #define F_fss_delimit_placeholder_s_length  F_string_placeholder_s_length
  #define F_fss_delimit_quote_single_s_length F_fss_quote_single_s_length
  #define F_fss_delimit_quote_double_s_length F_fss_quote_double_s_length
  #define F_fss_delimit_slash_s_length        F_fss_slash_s_length

  #define f_fss_delimit_placeholder_s  f_string_placeholder_s
  #define f_fss_delimit_quote_single_s f_fss_quote_single_s
  #define f_fss_delimit_quote_double_s f_fss_quote_double_s
  #define f_fss_delimit_slash_s        f_fss_slash_s
#endif //_di_f_fss_delimiters_

/**
 * Provide strings used by FSS.
 *
 * F_fss_string_*:
 *   - header:  String representing the header Object name.
 *   - payload: String representing the payload Object name.
 */
#ifndef _di_f_fss_strings_
  #define F_fss_string_header_s  "header"
  #define F_fss_string_payload_s "payload"

  #define F_fss_string_header_s_length  6
  #define F_fss_string_payload_s_length 7

  extern const f_string_static_t f_fss_string_header_s;
  extern const f_string_static_t f_fss_string_payload_s;
#endif // _di_f_fss_strings_

/**
 * Codes for every known FSS standard.
 *
 * f_fss_*:
 *   - basic:                    FSS-0000: Basic.
 *   - extended:                 FSS-0001: Extended.
 *   - basic_list:               FSS-0002: Basic List.
 *   - extended_list:            FSS-0003: Extended List.
 *   - very_basic_list:          FSS-0004: Very Basic List.
 *   - somewhat_basic_list:      FSS-0005: Somewhat Basic List.
 *   - somewhat_extended_list:   FSS-0006: Somewhat Extended List.
 *   - very_extended_list:       FSS-0007: Very Extended List.
 *   - embedded_list:            FSS-0008: Embedded List.
 *   - reverse_mapping:          FSS-0009: Reverse Mapping.
 *   - extended_reverse_mapping: FSS-000A: Extended Reverse Mapping.
 *   - simple_list:              FSS-000B: Simple List.
 *   - iki_text:                 FSS-000C: IKI Text.
 *   - basic_rule:               FSS-000D: Basic Rule.
 *   - payload:                  FSS-000E: Payload.
 */
#ifndef _di_f_fss_codes_
  enum {
    f_fss_basic_e = 1,
    f_fss_extended_e,
    f_fss_basic_list_e,
    f_fss_extended_list_e,
    f_fss_very_basic_list_e,
    f_fss_somewhat_basic_list_e,
    f_fss_somewhat_extended_list_e,
    f_fss_very_extended_list_e,
    f_fss_embedded_list_e,
    f_fss_reverse_mapping_e,
    f_fss_extended_reverse_mapping_e,
    f_fss_simple_list_e,
    f_fss_iki_text_e,
    f_fss_basic_rule_e,
    f_fss_payload_e,
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
 * f_fss_complete_*:
 *   - none:         Disable completeness.
 *   - end:          Complete as if this is the final piece of a set (such as FSS-0001, adding terminating EOL).
 *   - full:         Complete and add terminating EOL, where applicable.
 *   - full_trim:    Complete and add terminating EOL but remove any leading or trailing whitespace, where applicable.
 *   - next:         Complete as if this is a piece of a set (such as FSS-0001, adding a separating space).
 *   - partial:      Complete, but do not add terminating EOL, where applicable.
 *   - partial_trim: Complete, but do not add terminating EOL and remove any leading or trailing whitespace, where applicable.
 */
#ifndef _di_f_fss_complete_
  enum {
    f_fss_complete_none_e = 1,
    f_fss_complete_end_e,
    f_fss_complete_full_e,
    f_fss_complete_full_trim_e,
    f_fss_complete_next_e,
    f_fss_complete_partial_e,
    f_fss_complete_partial_trim_e,
  };
#endif // _di_f_fss_complete_

/**
 * FSS-specific Status codes.
 */
enum {
  F_fss_status_code_first = F_status_code_last + 1,

  #ifndef _di_F_fss_status_error_
    F_fss_format,
    F_fss_format_eos,
  #endif // _di_F_fss_status_error_

  #ifndef _di_F_fss_status_warning_
    F_fss_accepted_invalid,
    F_fss_accepted_invalid_eos,
  #endif // _di_F_fss_status_warning_

  #ifndef _di_F_fss_status_success_
    F_fss_found_content,
    F_fss_found_object,
    F_fss_found_object_content_not,
    F_fss_found_content_not,
    F_fss_found_object_not,
  #endif // _di_F_fss_status_success_

  #ifndef _di_F_fss_status_codes_
    F_fss_found_comment,
  #endif // _di_F_fss_status_codes_

  F_fss_status_code_last,
}; // enum

/**
 * Default allocation steps.
 *
 * Recommended to be set to at least 4 to be UTF-8 friendlier.
 */
#ifndef _di_f_fss_default_allocation_step_
  #define F_fss_default_allocation_step_d       F_memory_default_allocation_small_d
  #define F_fss_default_allocation_step_small_d F_memory_default_allocation_small_d
  #define F_fss_default_allocation_step_large_d F_memory_default_allocation_large_d
#endif // _di_f_fss_default_allocation_step_

/**
 * Common FSS defaults.
 *
 * F_fss_default_*:
 *   - block_size_huge:   The "huge" size in blocks to process for an FSS related task.
 *   - block_size_normal: The "normal" size in blocks to process for an FSS related task.
 *   - block_size_small:  The "small" size in blocks to process for an FSS related task.
 *   - block_size_tiny:   The "tiny" size in blocks to process for an FSS related task.
 */
#ifndef _di_f_fss_defaults_
  #define F_fss_default_block_size_huge_d   65536
  #define F_fss_default_block_size_normal_d 16384
  #define F_fss_default_block_size_small_d  4096
  #define F_fss_default_block_size_tiny_d   512
#endif // _di_f_fss_defaults_

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
