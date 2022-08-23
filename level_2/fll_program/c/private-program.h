/**
 * FLL - Level 2
 *
 * Project: Program
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_FLL_program_h
#define _PRIVATE_FLL_program_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of fll_program_standard_signal_received().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   A positive number representing a valid signal on signal received.
 *   0 on no signal received or when main is NULL.
 *
 * @see f_signal_read()
 *
 * @see fll_program_standard_signal_received()
 * @see fll_program_standard_signal_state()
 */
#if !defined(_di_fll_program_standard_signal_received_) || !defined(_di_fll_program_standard_signal_state_)
  f_status_t private_fll_program_standard_signal_received(fll_program_data_t * const main) F_attribute_visibility_internal_d;
#endif // !defined(_di_fll_program_standard_signal_received_) || !defined(_di_fll_program_standard_signal_state_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FLL_program_h
