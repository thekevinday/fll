/**
 * FLL - Level 3
 *
 * Project: IKI
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_write_h
#define _PRIVATE_write_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Process a given object and content, printing the IKI if valid or an error if invalid.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 * @param object
 *   The object to validate and print.
 * @param content
 *   The content to escape and print.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) for any othe failure.
 */
#ifndef _di_iki_write_process_
  extern f_status_t iki_write_process(fll_program_data_t * const main, iki_write_setting_t * const setting, const f_string_static_t object, const f_string_static_t content) F_attribute_visibility_internal_d;
#endif // _di_iki_write_process_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_write_h
