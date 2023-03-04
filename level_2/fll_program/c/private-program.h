/**
 * FLL - Level 2
 *
 * Project: Program
 * API Version: 0.7
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
 * Print standard help option.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param print
 *   The output structure to print to.
 * @param option_short
 *   The short name of the option.
 * @param option_long
 *   The long name of the option.
 * @param symbol_short
 *   The short symbol of the option.
 * @param symbol_long
 *   The long symbol of the option.
 * @param description
 *   A desciption associated with the option.
 *
 * @return
 *   F_none on success.
 *
 * @see f_print_terminated()
 * @see fl_print_format()
 *
 * @see fll_program_print_help_option()
 * @see fll_program_print_help_option_standard()
 */
#if !defined(_di_fll_program_print_help_option_) || !defined(_di_fll_program_print_help_option_standard_)
  extern f_status_t private_fll_program_print_help_option(const fl_print_t print, const f_string_static_t option_short, const f_string_static_t option_long, const f_string_static_t symbol_short, const f_string_static_t symbol_long, const char *description) F_attribute_visibility_internal_d;
#endif // !defined(_di_fll_program_print_help_option_) || !defined(_di_fll_program_print_help_option_standard_)

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
 * @see fll_program_standard_signal_handle()
 */
#if !defined(_di_fll_program_standard_signal_received_) || !defined(_di_fll_program_standard_signal_handle_)
  uint32_t private_fll_program_standard_signal_received(fll_program_data_t * const main) F_attribute_visibility_internal_d;
#endif // !defined(_di_fll_program_standard_signal_received_) || !defined(_di_fll_program_standard_signal_handle_)

/**
 * Private implementation of fll_program_parameter_process_empty().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param context
 *   The primary color context to assign.
 * @param sets
 *   (optional) A NULL terminated array representing additional sets to assign as empty.
 *   Set to NULL to not use.
 *
 * @see fll_program_parameter_process_context()
 * @see fll_program_parameter_process_empty()
 */
#if !defined(_di_fll_program_parameter_process_context_) || !defined(_di_fll_program_parameter_process_empty_)
  extern void private_fll_program_parameter_process_empty(f_color_context_t * const context, f_color_set_t * const sets[]) F_attribute_visibility_internal_d;
#endif // !defined(_di_fll_program_parameter_process_context_) || !defined(_di_fll_program_parameter_process_empty_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FLL_program_h
