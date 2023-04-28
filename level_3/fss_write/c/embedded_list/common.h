/**
 * FLL - Level 3
 *
 * Project: FSS Write
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_write_embedded_list_common_h
#define _fss_write_embedded_list_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The FSS-0008 (Embedded List) specific strings.
 */
#ifndef _di_fss_write_embedded_list_s_
  #define FSS_WRITE_embedded_list_standard_s "FSS-0008 (Embedded List)"

  #define FSS_WRITE_embedded_list_program_name_s      "fss_embedded_list_write"
  #define FSS_WRITE_embedded_list_program_name_long_s "FSS Embedded List Write"

  #define FSS_WRITE_format_code_short_0008_s   "0008"
  #define FSS_WRITE_format_code_long_0008_s    "fss-0008"
  #define FSS_WRITE_format_code_human_0008_s   "embedded list"
  #define FSS_WRITE_format_code_machine_0008_s "embedded_list"
  #define FSS_WRITE_format_code_name_0008_s    "Embedded List"

  #define FSS_WRITE_embedded_list_standard_s_length 24

  #define FSS_WRITE_embedded_list_program_name_s_length      23
  #define FSS_WRITE_embedded_list_program_name_long_s_length 23

  #define FSS_WRITE_format_code_short_0008_s_length   4
  #define FSS_WRITE_format_code_long_0008_s_length    8
  #define FSS_WRITE_format_code_human_0008_s_length   13
  #define FSS_WRITE_format_code_machine_0008_s_length 13
  #define FSS_WRITE_format_code_name_0008_s_length 13

  extern const f_string_static_t fss_write_embedded_list_standard_s;

  extern const f_string_static_t fss_write_embedded_list_program_name_s;
  extern const f_string_static_t fss_write_embedded_list_program_name_long_s;

  extern const f_string_static_t fss_write_format_code_short_0008_s;
  extern const f_string_static_t fss_write_format_code_long_0008_s;
  extern const f_string_static_t fss_write_format_code_human_0008_s;
  extern const f_string_static_t fss_write_format_code_machine_0008_s;
  extern const f_string_static_t fss_write_format_code_name_0008_s;
#endif // _di_fss_write_embedded_list_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_write_embedded_list_common_h
