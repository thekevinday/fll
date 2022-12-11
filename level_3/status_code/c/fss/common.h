/**
 * FLL - Level 3
 *
 * Project: Status Code
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _status_code_fss_common_h
#define _status_code_fss_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program name.
 */
#ifndef _di_status_code_fss_program_name_s_
  #define STATUS_CODE_fss_program_name_s      "fss_status_code"
  #define STATUS_CODE_fss_program_name_long_s "FSS Status Code"

  #define STATUS_CODE_fss_program_name_s_length      15
  #define STATUS_CODE_fss_program_name_long_s_length 15

  extern const f_string_static_t status_code_fss_program_name_s;
  extern const f_string_static_t status_code_fss_program_name_long_s;
#endif // _di_status_code_program_name_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _status_code_fss_common_h
