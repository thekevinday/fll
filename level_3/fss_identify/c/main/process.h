/**
 * FLL - Level 3
 *
 * Project: FSS Identify
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides process functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_identify_process_h
#define _fss_identify_process_h


/**
 * Process a given pipe or file.
 *
 * @param main
 *   The main program and settings data.
 *
 *   This alters main.program.signal_received, setting it to a received signal.
 *
 *   This alters setting.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: fll_fss_identify().
 * @param name
 *   The name of the file.
 *   file_name.used to 0 to designate that this is a pipe.
 *
 * @see fll_fss_identify()
 */
#ifndef _di_fss_identify_process_
  extern void fss_identify_process(fss_identify_main_t * const main, const f_string_static_t name);
#endif // _di_fss_identify_process_

/**
 * Determine if the given FLL ID matches the requested range.
 *
 * @param main
 *   The main program and settings data.
 *
 *   This alters main.program.signal_received, setting it to a received signal.
 *
 *   This alters setting.status:
 *     Errors (with error bit) from: f_compare_dynamic_partial_string().
 *     Errors (with error bit) from: f_compare_dynamic_string().
 *     Errors (with error bit) from: fl_conversion_dynamic_partial_to_hexidecimal_unsigned().
 * @param id
 *   The identifier to compare against.
 * @param mode
 *   An array of modes specifying how to compare:
 *     0 = Compare against just the ID Name (such as "fss" in "fss-0001").
 *     1 = Compare against just the ID Type (such as "0001" in "fss-0001").
 *     2 = Compare against the full name (such as "fss-0001" in "fss-0001").
 *
 *   The array size must exactly match main.setting.names.used.
 *
 * @return
 *   F_equal_to on match.
 *   F_equal_to_not on no match or on error.
 *
 * @see fl_conversion_dynamic_partial_to_hexidecimal_unsigned()
 * @see f_compare_dynamic_string()
 */
#ifndef _di_fss_identify_process_name_compare_
  extern f_status_t fss_identify_process_name_compare(fss_identify_main_t * const main, const f_fll_id_t id, const uint8_t modes[]);
#endif // _di_fss_identify_process_name_compare_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_identify_process_h
