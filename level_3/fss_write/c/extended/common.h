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
#ifndef _fss_write_extended_common_h
#define _fss_write_extended_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The FSS-0001 (Extended) specific strings.
 */
#ifndef _di_fss_write_extended_s_
  #define FSS_WRITE_extended_standard_s "FSS-0001 (Extended)"

  #define FSS_WRITE_extended_program_name_s      "fss_extended_write"
  #define FSS_WRITE_extended_program_name_long_s "FSS Extended Write"

  #define FSS_WRITE_format_code_short_0001_s   "0001"
  #define FSS_WRITE_format_code_long_0001_s    "fss-0001"
  #define FSS_WRITE_format_code_human_0001_s   "extended"
  #define FSS_WRITE_format_code_machine_0001_s "extended"
  #define FSS_WRITE_format_code_name_0001_s    "Extended"

  #define FSS_WRITE_extended_standard_s_length 19

  #define FSS_WRITE_extended_program_name_s_length      18
  #define FSS_WRITE_extended_program_name_long_s_length 18

  #define FSS_WRITE_format_code_short_0001_s_length   4
  #define FSS_WRITE_format_code_long_0001_s_length    8
  #define FSS_WRITE_format_code_human_0001_s_length   8
  #define FSS_WRITE_format_code_machine_0001_s_length 8
  #define FSS_WRITE_format_code_name_0001_s_length    8

  extern const f_string_static_t fss_write_extended_standard_s;

  extern const f_string_static_t fss_write_extended_program_name_s;
  extern const f_string_static_t fss_write_extended_program_name_long_s;

  extern const f_string_static_t fss_write_format_code_short_0001_s;
  extern const f_string_static_t fss_write_format_code_long_0001_s;
  extern const f_string_static_t fss_write_format_code_human_0001_s;
  extern const f_string_static_t fss_write_format_code_machine_0001_s;
  extern const f_string_static_t fss_write_format_code_name_0001_s;
#endif // _di_fss_write_extended_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_write_extended_common_h
