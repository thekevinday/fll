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
#ifndef _fss_write_payload_common_h
#define _fss_write_payload_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The FSS-000E (Payload) specific strings.
 */
#ifndef _di_fss_write_payload_strings_
  #define FSS_WRITE_payload_standard_s "FSS-000E (Payload)"

  #define FSS_WRITE_format_code_short_000e_s "000e"
  #define FSS_WRITE_format_code_long_000e_s  "fss-000e"
  #define FSS_WRITE_format_code_human_000e_s "payload"

  #define FSS_WRITE_payload_standard_s_length 18

  #define FSS_WRITE_format_code_short_000e_s_length 4
  #define FSS_WRITE_format_code_long_000e_s_length  8
  #define FSS_WRITE_format_code_human_000e_s_length 7

  extern const f_string_static_t fss_write_payload_standard_s;

  extern const f_string_static_t fss_write_format_code_short_000e_s;
  extern const f_string_static_t fss_write_format_code_long_000e_s;
  extern const f_string_static_t fss_write_format_code_human_000e_s;
#endif // _di_fss_write_payload_strings_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_write_payload_common_h
