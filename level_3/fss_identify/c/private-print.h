/**
 * FLL - Level 3
 *
 * Project: FSS Identify
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_print_h
#define _PRIVATE_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print the given FLL Identifier.
 *
 * @param main
 *   The main program data.
 * @param id
 *   The Identifier to print.
 */
#ifndef _di_fss_identify_print_
  extern void fss_identify_print(fss_identify_main_t * const main, f_fll_id_t id) F_attribute_visibility_internal_d;
#endif // _di_fss_identify_print_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_print_h
