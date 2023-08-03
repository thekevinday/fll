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
 * Private implementation of fll_program_parameter_process_context().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param choices
 *   An array of color modes.
 *   The default, if no mode is specified, will be the last value in the array.
 * @param modes
 *   An array designating the context modes associated with each choice.
 *   This must exactly match the size of the choices array.
 *   No bounds checking is performed.
 * @param right
 *   If TRUE, use the right-most parameter on conflict.
 *   If FALSE, use the left-most parameter on conflict.
 * @param main
 *   The main program data.
 *
 * @return
 *   F_none on success.
 *   F_data_not if "values" parameters were expected but not found.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_console_parameter_prioritize_left().
 *   Errors (with error bit) from: f_console_parameter_prioritize_right().
 *   Errors (with error bit) from: f_color_load_context().
 *
 * @see f_console_parameter_prioritize_left()
 * @see f_console_parameter_prioritize_right()
 * @see f_color_load_context()
 */
#if !defined(_di_fll_program_parameter_process_context_) || !defined(_di_fll_program_parameter_process_context_standard_)
  extern f_status_t private_fll_program_parameter_process_context(const f_uint16s_t choices, const uint8_t modes[], const bool right, fll_program_data_t * const main);
#endif // !defined(_di_fll_program_parameter_process_context_) || !defined(_di_fll_program_parameter_process_context_standard_)

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
  extern f_status_t private_fll_program_print_help_option(fl_print_t * const print, const f_string_static_t option_short, const f_string_static_t option_long, const f_string_static_t symbol_short, const f_string_static_t symbol_long, const char *description) F_attribute_visibility_internal_d;
#endif // !defined(_di_fll_program_print_help_option_) || !defined(_di_fll_program_print_help_option_standard_)

/**
 * Private implementation of fll_program_standard_signal_received().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param program
 *   The program data.
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
  uint32_t private_fll_program_standard_signal_received(fll_program_data_t * const program) F_attribute_visibility_internal_d;
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
 * @see fll_program_parameter_process_context_standard()
 * @see fll_program_parameter_process_empty()
 */
#if !defined(_di_fll_program_parameter_process_context_) || !defined(_di_fll_program_parameter_process_context_standard_) || !defined(_di_fll_program_parameter_process_empty_)
  extern void private_fll_program_parameter_process_empty(f_color_context_t * const context, f_color_set_t * const sets[]) F_attribute_visibility_internal_d;
#endif // !defined(_di_fll_program_parameter_process_context_) || !defined(_di_fll_program_parameter_process_context_standard_) || !defined(_di_fll_program_parameter_process_empty_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FLL_program_h
