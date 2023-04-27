/**
 * FLL - Level 3
 *
 * Project: FSS Read
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_read_basic_list_common_h
#define _fss_read_basic_list_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The FSS-0002 (Basic List) specific strings.
 */
#ifndef _di_fss_read_basic_list_s_
  #define FSS_READ_basic_list_standard_s "FSS-0002 (Basic List)"

  #define FSS_READ_basic_list_program_name_s      "fss_basic_list_read"
  #define FSS_READ_basic_list_program_name_long_s "FSS Basic List Read"

  #define FSS_READ_format_code_short_0002_s   "0002"
  #define FSS_READ_format_code_long_0002_s    "fss-0002"
  #define FSS_READ_format_code_human_0002_s   "basic list"
  #define FSS_READ_format_code_machine_0002_s "basic_list"

  #define FSS_READ_basic_list_standard_s_length 21

  #define FSS_READ_basic_list_program_name_s_length      19
  #define FSS_READ_basic_list_program_name_long_s_length 19

  #define FSS_READ_format_code_short_0002_s_length   4
  #define FSS_READ_format_code_long_0002_s_length    8
  #define FSS_READ_format_code_human_0002_s_length   10
  #define FSS_READ_format_code_machine_0002_s_length 10

  extern const f_string_static_t fss_read_basic_list_standard_s;

  extern const f_string_static_t fss_read_basic_list_program_name_s;
  extern const f_string_static_t fss_read_basic_list_program_name_long_s;

  extern const f_string_static_t fss_read_format_code_short_0002_s;
  extern const f_string_static_t fss_read_format_code_long_0002_s;
  extern const f_string_static_t fss_read_format_code_human_0002_s;
  extern const f_string_static_t fss_read_format_code_machine_0002_s;
#endif // _di_fss_read_basic_list_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_read_basic_list_common_h
