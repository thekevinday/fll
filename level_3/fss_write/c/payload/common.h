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
  #define FSS_WRITE_payload_s "payload"

  #define FSS_WRITE_payload_standard_s "FSS-000E (Payload)"

  #define FSS_WRITE_payload_program_name_s      "fss_payload_write"
  #define FSS_WRITE_payload_program_name_long_s "FSS Payload Write"

  #define FSS_WRITE_format_code_short_000e_s "000e"
  #define FSS_WRITE_format_code_long_000e_s  "fss-000e"
  #define FSS_WRITE_format_code_human_000e_s "payload"

  #define FSS_WRITE_payload_s_length 7

  #define FSS_WRITE_payload_standard_s_length 18

  #define FSS_WRITE_payload_program_name_s_length      17
  #define FSS_WRITE_payload_program_name_long_s_length 17

  #define FSS_WRITE_format_code_short_000e_s_length 4
  #define FSS_WRITE_format_code_long_000e_s_length  8
  #define FSS_WRITE_format_code_human_000e_s_length 7

  extern const f_string_static_t fss_write_payload_s;

  extern const f_string_static_t fss_write_payload_standard_s;

  extern const f_string_static_t fss_write_payload_program_name_s;
  extern const f_string_static_t fss_write_payload_program_name_long_s;

  extern const f_string_static_t fss_write_format_code_short_000e_s;
  extern const f_string_static_t fss_write_format_code_long_000e_s;
  extern const f_string_static_t fss_write_format_code_human_000e_s;
#endif // _di_fss_write_payload_strings_

/**
 * Perform the payload-specific program setting load process.
 *
 * This prints error messages as appropriate.
 *
 * If either main or setting is NULL, then this immediately retuns without doing anything.
 *
 * @param arguments
 *   The parameters passed to the process (often referred to as command line arguments).
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This alters setting.process_help, setting.process_normal, and setting.process_pipe.
 *
 *   This alters setting.status:
 *     F_none on success.
 *     F_interrupt on (exit) signal received.
 *
 *     F_parameter (with error bit) if main is NULL or setting is NULL.
 *     F_parameter (with error bit) on parameter error.
 *
 *   This alters setting.status:
 *     F_none on success.
 *     F_data_not on success but nothing was provided to operate with.
 *
 * @see fss_write_setting_load()
 */
#ifndef _di_fss_write_payload_setting_load_
  extern void fss_write_payload_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, fss_write_setting_t * const setting);
#endif // _di_fss_write_payload_setting_load_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_write_payload_common_h
