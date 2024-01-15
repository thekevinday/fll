/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.7
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
#ifndef _di_f_fss_type_s_
  #define F_fss_brace_close_s    F_string_ascii_brace_close_s
  #define F_fss_brace_open_s     F_string_ascii_brace_open_s
  #define F_fss_colon_s          F_string_ascii_colon_s
  #define F_fss_minus_s          F_string_ascii_minus_s
  #define F_fss_f_s              F_string_ascii_f_s
  #define F_fss_pound_s          F_string_ascii_pound_s
  #define F_fss_quote_double_s   F_string_ascii_quote_double_s
  #define F_fss_quote_grave_s    F_string_ascii_grave_s
  #define F_fss_quote_single_s   F_string_ascii_quote_single_s
  #define F_fss_s_s              F_string_ascii_s_s
  #define F_fss_slash_s          F_string_ascii_slash_backward_s
  #define F_fss_space_s          F_string_ascii_space_s
  #define F_fss_underscore_s     F_string_ascii_underscore_s

  #define F_fss_brace_close_s_length    F_string_ascii_brace_close_s_length
  #define F_fss_brace_open_s_length     F_string_ascii_brace_open_s_length
  #define F_fss_colon_s_length          F_string_ascii_colon_s_length
  #define F_fss_minus_s_length          F_string_ascii_minus_s_length
  #define F_fss_f_s_length              F_string_ascii_f_s_length
  #define F_fss_pound_s_length          F_string_ascii_pound_s_length
  #define F_fss_quote_double_s_length   F_string_ascii_quote_double_s_length
  #define F_fss_quote_grave_s_length    F_string_ascii_grave_s_length
  #define F_fss_quote_single_s_length   F_string_ascii_quote_single_s_length
  #define F_fss_s_s_length              F_string_ascii_s_s_length
  #define F_fss_slash_s_length          F_string_ascii_slash_backward_s_length
  #define F_fss_space_s_length          F_string_ascii_space_s_length
  #define F_fss_underscore_s_length     F_string_ascii_underscore_s_length

  #define f_fss_brace_close_s    f_string_ascii_brace_close_s
  #define f_fss_brace_open_s     f_string_ascii_brace_open_s
  #define f_fss_colon_s          f_string_ascii_colon_s
  #define f_fss_minus_s          f_string_ascii_minus_s
  #define f_fss_f_s              f_string_ascii_f_s
  #define f_fss_pound_s          f_string_ascii_pound_s
  #define f_fss_quote_double_s   f_string_ascii_quote_double_s
  #define f_fss_quote_grave_s    f_string_ascii_grave_s
  #define f_fss_quote_single_s   f_string_ascii_quote_single_s
  #define f_fss_s_s              f_string_ascii_s_s
  #define f_fss_slash_s          f_string_ascii_slash_backward_s
  #define f_fss_space_s          f_string_ascii_space_s
  #define f_fss_underscore_s     f_string_ascii_underscore_s

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
  #define f_fss_payload_header_open_s     f_fss_space_s
  #define f_fss_payload_header_next_s     f_fss_space_s
  #define f_fss_payload_header_close_s    f_string_eol_s
  #define f_fss_payload_list_open_s       f_fss_colon_s
  #define f_fss_payload_list_open_end_s   f_string_eol_s
  #define f_fss_payload_list_close_s      f_string_eol_s
  #define f_fss_type_header_open_s        f_fss_pound_s
  #define f_fss_type_header_part1_s       f_fss_space_s
  #define f_fss_type_header_part2_s       f_fss_f_s
  #define f_fss_type_header_part3_s       f_fss_s_s
  #define f_fss_type_header_part4_s       f_fss_s_s
  #define f_fss_type_header_part5_s       f_fss_minus_s
  #define f_fss_type_header_close_s       f_string_eol_s
#endif // _di_f_fss_type_s_

/**
 * FSS-specific delimiters.
 */
#ifndef _di_f_fss_placeholder_s_
  #define F_fss_placeholder_s F_string_placeholder_s

  #define F_fss_placeholder_s_length F_string_placeholder_s_length

  #define f_fss_placeholder_s f_string_placeholder_s
#endif //_di_f_fss_placeholder_s_

/**
 * Provide strings used by FSS.
 *
 * F_fss_*_s:
 *   - header:  String representing the header Object name.
 *   - payload: String representing the payload Object name.
 */
#ifndef _di_f_fss_s_
  #define F_fss_header_s  "header"
  #define F_fss_payload_s "payload"

  #define F_fss_string_header_s_length  6
  #define F_fss_string_payload_s_length 7

  #ifndef _di_f_fss_header_s_
    extern const f_string_static_t f_fss_header_s;
  #endif // _di_f_fss_header_s_

  #ifndef _di_f_fss_payload_s_
    extern const f_string_static_t f_fss_payload_s;
  #endif // _di_f_fss_payload_s_
#endif // _di_f_fss_s_

/**
 * Codes for every known FSS standard.
 *
 * f_fss_*_e:
 *   - none:                     No type set.
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
 *   - simple_packet:            FSS-000F: Simple Packet.
 *   - encrypted_simple_packet:  FSS-0010: Encrypted Simple Packet.
 */
#ifndef _di_f_fss_e_
  enum {
    f_fss_none_e = 0,
    f_fss_basic_e,
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
    f_fss_simple_packet_e,
    f_fss_encrypted_simple_packet_e,
  }; // enum
#endif // _di_f_fss_e_

/**
 * Codes for FSS completeness.
 *
 * The details on how these work are specific to individual specifications.
 * The notes below provide the intended purpose but be sure to still read the individual function documentation.
 *
 * The "next" and "end" are only meaningful for a Content and will be treated as "none" for an Object.
 *
 * f_fss_complete_*_e:
 *   - none:         Disable completeness.
 *   - end:          Complete as if this is the final piece of a set (such as FSS-0001, adding terminating EOL).
 *   - full:         Complete and add terminating EOL, where applicable.
 *   - full_trim:    Complete and add terminating EOL but remove any leading or trailing whitespace, where applicable.
 *   - next:         Complete as if this is a piece of a set (such as FSS-0001, adding a separating space).
 *   - partial:      Complete, but do not add terminating EOL, where applicable.
 *   - partial_trim: Complete, but do not add terminating EOL and remove any leading or trailing whitespace, where applicable.
 *   - trim:         Only print the Object or Content, trimmed where applicable, without any closing or terminating characters.
 */
#ifndef _di_f_fss_complete_e_
  enum {
    f_fss_complete_none_e = 0,
    f_fss_complete_end_e,
    f_fss_complete_full_e,
    f_fss_complete_full_trim_e,
    f_fss_complete_next_e,
    f_fss_complete_partial_e,
    f_fss_complete_partial_trim_e,
    f_fss_complete_trim_e,
  }; // enum
#endif // _di_f_fss_complete_e_

/**
 * FSS-specific Status codes.
 */
enum {
  F_fss_status_code_first = F_status_code_last + 1,

  #ifndef _di_f_fss_status_error_e_
    F_fss_format,
    F_fss_format_eos,
  #endif // _di_f_fss_status_error_e_

  #ifndef _di_f_fss_status_warning_e_
    F_fss_accepted_invalid,
    F_fss_accepted_invalid_eos,
  #endif // _di_f_fss_status_warning_e_

  #ifndef _di_f_fss_status_success_e_
    F_fss_found_content,
    F_fss_found_object,
    F_fss_found_object_content_not,
    F_fss_found_content_not,
    F_fss_found_object_not,
  #endif // _di_f_fss_status_success_e_

  #ifndef _di_f_fss_status_codes_e_
    F_fss_found_comment,
  #endif // _di_f_fss_status_codes_e_

  F_fss_status_code_last,
}; // enum

/**
 * Default allocation steps.
 *
 * Recommended to be set to at least 4 to be UTF-8 friendlier.
 *
 * F_fss_default_*:
 *   - block_size_huge:   The "huge" size in blocks to process for an FSS related task.
 *   - block_size_normal: The "normal" size in blocks to process for an FSS related task.
 *   - block_size_small:  The "small" size in blocks to process for an FSS related task.
 *   - block_size_tiny:   The "tiny" size in blocks to process for an FSS related task.
 */
#ifndef _di_f_fss_default_d_
  #define F_fss_default_allocation_step_d       F_memory_default_allocation_small_d
  #define F_fss_default_allocation_step_small_d F_memory_default_allocation_small_d
  #define F_fss_default_allocation_step_large_d F_memory_default_allocation_large_d

  #define F_fss_default_block_size_huge_d   65536
  #define F_fss_default_block_size_normal_d 16384
  #define F_fss_default_block_size_small_d  4096
  #define F_fss_default_block_size_tiny_d   512
#endif // _di_f_fss_default_d_

/**
 * State flags associated with FSS functions.
 *
 * These flags are meant to be bitwise for the 32-bit f_state_t flag property.
 *
 * The f_fss_state_flag_none_e is expected to be 0, therefore it must be safe to use 0 directly.
 *
 * f_fss_state_flag_*:
 *   - none:                  No flags are set.
 *   - utf_fail_on_valid_not: Immediately fail on invalid UTF-8 character (including incomplete).
 */
#ifndef _di_f_fss_state_flag_e_
  enum {
    f_fss_state_flag_none_e                  = 0x0,
    f_fss_state_flag_utf_fail_on_valid_not_e = 0x1,
  }; // enum
#endif // _di_f_fss_state_flag_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_common_h
