/**
 * FLL - Level 3
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_write_h
#define _PRIVATE_write_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Process a given object and content, printing the FSS if valid or an error if invalid.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This alters setting.status:
 *     F_none on success.
 *     F_interrupt on (exit) signal received.
 *
 *     F_parameter (with error bit) if main is NULL or setting is NULL.
 * @param object
 *   The object to validate and print.
 *   Set pointer address to 0 to not use.
 * @param content
 *   The content to escape and print.
 *   Set pointer address to 0 to not use.
 *
 * @return
 *   F_none on success.
 *   F_failure (with error bit) for any other failure.
 */
#ifndef _di_fss_payload_write_process_
  extern void fss_payload_write_process(fll_program_data_t * const main, fss_payload_write_setting_t * const setting, const f_string_static_t *object, const f_string_static_t *content) F_attribute_visibility_internal_d;
#endif // _di_fss_payload_write_process_

/**
 * Process the pipe, reading from the pipe and writing to the output.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This alters setting.status:
 *     F_none on success.
 *     F_data_not on success but pipe contained no relevant data.
 *     F_payload on success and the payload has been printed.
 *     F_interrupt on (exit) signal received.
 *
 *     F_parameter (with error bit) if main is NULL or setting is NULL.
 *
 * @return
 *   F_none on success.
 *   F_failure (with error bit) for any other failure.
 */
#ifndef _di_fss_payload_write_process_pipe_
  extern void fss_payload_write_process_pipe(fll_program_data_t * const main, fss_payload_write_setting_t * const setting) F_attribute_visibility_internal_d;
#endif // _di_fss_payload_write_process_pipe_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_write_h
