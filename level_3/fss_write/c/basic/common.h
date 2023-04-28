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
#ifndef _fss_write_basic_common_h
#define _fss_write_basic_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The FSS-0000 (Basic) specific strings.
 */
#ifndef _di_fss_write_basic_s_
  #define FSS_WRITE_basic_standard_s "FSS-0000 (Basic)"

  #define FSS_WRITE_basic_program_name_s      "fss_basic_write"
  #define FSS_WRITE_basic_program_name_long_s "FSS Basic Write"

  #define FSS_WRITE_format_code_short_0000_s   "0000"
  #define FSS_WRITE_format_code_long_0000_s    "fss-0000"
  #define FSS_WRITE_format_code_human_0000_s   "basic"
  #define FSS_WRITE_format_code_machine_0000_s "basic"
  #define FSS_WRITE_format_code_name_0000_s    "Basic"

  #define FSS_WRITE_basic_standard_s_length 16

  #define FSS_WRITE_basic_program_name_s_length      15
  #define FSS_WRITE_basic_program_name_long_s_length 15

  #define FSS_WRITE_format_code_short_0000_s_length   4
  #define FSS_WRITE_format_code_long_0000_s_length    8
  #define FSS_WRITE_format_code_human_0000_s_length   5
  #define FSS_WRITE_format_code_machine_0000_s_length 5
  #define FSS_WRITE_format_code_name_0000_s_length    5

  extern const f_string_static_t fss_write_basic_standard_s;

  extern const f_string_static_t fss_write_basic_program_name_s;
  extern const f_string_static_t fss_write_basic_program_name_long_s;

  extern const f_string_static_t fss_write_format_code_short_0000_s;
  extern const f_string_static_t fss_write_format_code_long_0000_s;
  extern const f_string_static_t fss_write_format_code_human_0000_s;
  extern const f_string_static_t fss_write_format_code_machine_0000_s;
  extern const f_string_static_t fss_write_format_code_name_0000_s;
#endif // _di_fss_write_basic_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_write_basic_common_h
