/**
 * FLL - Level 0
 *
 * Project: Console
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_console_h
#define _PRIVATE_F_console_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of f_console_identify().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param input
 *   The input parameter to process.
 * @param result
 *   The flag with the console type bits determined by this function.
 *
 * @return
 *   F_none on success.
 *   F_data_not the input string is empty.
 *
 *
 * @see f_console_identify()
 * @see f_console_parameter_process()
 */
#if !defined(_di_f_console_identify_) || !defined(_di_f_console_parameter_process_)
  extern f_status_t private_f_console_identify(const f_string_t input, f_console_result_t * const result) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_console_identify_) || !defined(_di_f_console_parameter_process_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_console_h
