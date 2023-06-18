/**
 * FLL - Level 3
 *
 * Project: FSS Read
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides process normal functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_read_process_normal_h
#define _fss_read_process_normal_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Process normally, reading from the input for the assigned FSS format.
 *
 * @param main
 *   The program and settings data.
 *
 *   Must not be NULL.
 *   Must be of type fss_read_main_t.
 *
 *   This alters main.setting.state.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: main.callback.process_at().
 *     Errors (with error bit) from: main.callback.process_at_line().
 *     Errors (with error bit) from: main.callback.process_columns().
 *     Errors (with error bit) from: main.callback.process_load().
 *     Errors (with error bit) from: main.callback.process_name().
 *     Errors (with error bit) from: main.callback.print_at().
 *     Errors (with error bit) from: main.callback.process_read().
 *     Errors (with error bit) from: main.callback.process_total().
 *
 *     Errors (with error bit) from: fss_read_signal_check().
 *
 * @see fss_read_signal_check()
 */
#ifndef _di_fss_read_process_normal_
  extern void fss_read_process_normal(void * const main);
#endif // _di_fss_read_process_normal_

/**
 * Process buffer according to "at" parameter rules.
 *
 * This handles only a single depth (index 0 of the depth array).
 *
 * @param main
 *   The program and settings data.
 *
 *   Must not be NULL.
 *   Must be of type fss_read_main_t.
 *
 *   This alters main.setting.state.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: fss_read_signal_check().
 * @param names
 *   An array of booleans representing if the name at a given index is enabled.
 *   (If TRUE, then the name is to be used and if FALSE, then the name is not to be used.)
 * @param delimits_object
 *   The delimits array representing a delimited Object.
 *   This represents the positions within the current Object at the "at" position.
 * @param delimits_content
 *   The delimits array representing a delimited Content.
 *   This represents the positions within the current Content at the "at" position.
 *
 * @see fss_read_signal_check()
 */
#ifndef _di_fss_read_process_normal_at_
  extern void fss_read_process_normal_at(void * const main, const bool names[], const f_fss_delimits_t delimits_object, const f_fss_delimits_t delimits_content);
#endif // _di_fss_read_process_normal_at_

/**
 * Process for the given Object index position for processing and ultimately printing a specific line.
 *
 * @param main
 *   The program and settings data.
 *
 *   Must not be NULL.
 *   Must be of type fss_read_main_t.
 *
 *   This alters main.setting.range.
 *
 *   This alters main.setting.state.status:
 *     F_none on success but line not yet found.
 *     F_success on success and line is found and printed.
 *
 *     Errors (with error bit) from: f_string_dynamic_append_assure().
 *
 *     Errors (with error bit) from: fss_read_signal_check().
 * @param at
 *   The Object index position to be processed.
 * @param delimits_object
 *   The delimits array representing a delimited Object.
 *   This represents the positions within the current Object at the "at" position.
 * @param delimits_content
 *   The delimits array representing a delimited Content.
 *   This represents the positions within the current Content at the "at" position.
 * @param line
 *   The current line being processed.
 *   This will be incremented as necessary.
 *
 *   Must not be NULL.
 */
#ifndef _di_fss_read_process_normal_at_line_
  extern void fss_read_process_normal_at_line(void * const main, const f_number_unsigned_t at, const f_number_unsigneds_t delimits_object, const f_number_unsigneds_t delimits_content, f_number_unsigned_t * const line);
#endif // _di_fss_read_process_normal_at_line_

/**
 * Process buffer according to "columns" parameter rules.
 *
 * @param main
 *   The program and settings data.
 *
 *   Must not be NULL.
 *   Must be of type fss_read_main_t.
 *
 *   This alters main.setting.state.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: fss_read_signal_check().
 * @param names
 *   An array of booleans representing if the name at a given index is enabled.
 *   (If TRUE, then the name is to be used and if FALSE, then the name is not to be used.)
 *
 * @see fss_read_signal_check()
 */
#ifndef _di_fss_read_process_normal_columns_
  extern void fss_read_process_normal_columns(void * const main, const bool names[]);
#endif // _di_fss_read_process_normal_columns_

/**
 * Process buffer according to "name" parameter rules.
 *
 * @param main
 *   The program and settings data.
 *
 *   Must not be NULL.
 *   Must be of type fss_read_main_t.
 *
 *   This alters main.setting.state.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: fss_read_signal_check().
 * @param names
 *   An array of booleans representing if the name at a given index is enabled.
 *   (If TRUE, then the name is to be used and if FALSE, then the name is not to be used.)
 *
 * @see fss_read_signal_check()
 */
#ifndef _di_fss_read_process_normal_name_
  extern void fss_read_process_normal_name(void * const main, bool names[]);
#endif // _di_fss_read_process_normal_name_

/**
 * Process buffer according to "total" parameter rules.
 *
 * This processes single line Content only.
 *
 * @param main
 *   The program and settings data.
 *
 *   Must not be NULL.
 *   Must be of type fss_read_main_t.
 *
 *   This alters main.setting.state.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: fss_read_signal_check().
 * @param names
 *   An array of booleans representing if the name at a given index is enabled.
 *   (If TRUE, then the name is to be used and if FALSE, then the name is not to be used.)
 *
 * @see fss_read_signal_check()
 */
#ifndef _di_fss_read_process_normal_total_
  extern void fss_read_process_normal_total(void * const main, const bool names[]);
#endif // _di_fss_read_process_normal_total_

/**
 * Process buffer according to "total" parameter rules.
 *
 * This processes multi-line Content only.
 *
 * @param main
 *   The program and settings data.
 *
 *   Must not be NULL.
 *   Must be of type fss_read_main_t.
 *
 *   This alters main.setting.state.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: fss_read_signal_check().
 * @param names
 *   An array of booleans representing if the name at a given index is enabled.
 *   (If TRUE, then the name is to be used and if FALSE, then the name is not to be used.)
 *
 * @see fss_read_signal_check()
 */
#ifndef _di_fss_read_process_normal_total_multiple_
  extern void fss_read_process_normal_total_multiple(void * const main, const bool names[]);
#endif // _di_fss_read_process_normal_total_multiple_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_read_process_normal_h
