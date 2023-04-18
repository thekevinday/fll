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
#ifndef _fss_write_extended_list_common_h
#define _fss_write_extended_list_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The FSS-0001 (Extended List) specific strings.
 */
#ifndef _di_fss_write_extended_list_s_
  #define FSS_WRITE_extended_list_standard_s "FSS-0003 (Extended List)"

  #define FSS_WRITE_extended_list_program_name_s      "fss_extended_list_write"
  #define FSS_WRITE_extended_list_program_name_long_s "FSS Extended List Write"

  #define FSS_WRITE_format_code_short_0003_s   "0003"
  #define FSS_WRITE_format_code_long_0003_s    "fss-0003"
  #define FSS_WRITE_format_code_human_0003_s   "extended list"
  #define FSS_WRITE_format_code_machine_0003_s "extended_list"

  #define FSS_WRITE_extended_list_standard_s_length 24

  #define FSS_WRITE_extended_list_program_name_s_length      23
  #define FSS_WRITE_extended_list_program_name_long_s_length 23

  #define FSS_WRITE_format_code_short_0003_s_length   4
  #define FSS_WRITE_format_code_long_0003_s_length    8
  #define FSS_WRITE_format_code_human_0003_s_length   13
  #define FSS_WRITE_format_code_machine_0003_s_length 13

  extern const f_string_static_t fss_write_extended_list_standard_s;

  extern const f_string_static_t fss_write_extended_list_program_name_s;
  extern const f_string_static_t fss_write_extended_list_program_name_long_s;

  extern const f_string_static_t fss_write_format_code_short_0003_s;
  extern const f_string_static_t fss_write_format_code_long_0003_s;
  extern const f_string_static_t fss_write_format_code_human_0003_s;
  extern const f_string_static_t fss_write_format_code_machine_0003_s;
#endif // _di_fss_write_extended_list_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_write_extended_list_common_h
