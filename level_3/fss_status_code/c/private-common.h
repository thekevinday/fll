/**
 * FLL - Level 3
 *
 * Project: FSS Status Code
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_common_h
#define _PRIVATE_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print a message about a process signal being recieved, such as an interrupt signal.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_fss_status_code_print_signal_received_
  extern void fss_status_code_print_signal_received(fll_program_data_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_status_code_print_signal_received_

/**
 * Print a message about a one parameter not being allowed to be used with another.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_fss_status_code_print_parameter_cannot_be_used_with_
  extern void fss_status_code_print_parameter_cannot_be_used_with(fll_program_data_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_status_code_print_parameter_cannot_be_used_with_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h
