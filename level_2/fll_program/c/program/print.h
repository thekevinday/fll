/**
 * FLL - Level 2
 *
 * Project: Program
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines common data to be used for/by project program.
 *
 * This is auto-included by program.h and should not need to be explicitly included.
 */
#ifndef _FLL_program_print_h
#define _FLL_program_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print standard help header.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param print
 *   The output structure to print to.
 *   This requires print.set to be non-NULL.
 * @param name
 *   The name of the program.
 * @param version
 *   The version number of the program.
 *
 * @return
 *   F_none on success.
 *
 * @see f_print_terminated()
 * @see fl_print_format()
 */
#ifndef _di_fll_program_print_help_header_
  extern f_status_t fll_program_print_help_header(const fl_print_t print, const f_string_static_t name, const f_string_static_t version);
#endif // _di_fll_program_print_help_header_

/**
 * Print standard help option.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param print
 *   The output structure to print to.
 *   This requires print.set to be non-NULL.
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
 */
#ifndef _di_fll_program_print_help_option_
  extern f_status_t fll_program_print_help_option(const fl_print_t print, const f_string_static_t option_short, const f_string_static_t option_long, const f_string_static_t symbol_short, const f_string_static_t symbol_long, const char *description);
#endif // _di_fll_program_print_help_option_

/**
 * Print standard help option (long option only).
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param print
 *   The output structure to print to.
 *   This requires print.set to be non-NULL.
 * @param option_long
 *   The long name of the option.
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
 */
#ifndef _di_fll_program_print_help_option_long_
  extern f_status_t fll_program_print_help_option_long(const fl_print_t print, const f_string_static_t option_long, const f_string_static_t symbol_long, const char *description);
#endif // _di_fll_program_print_help_option_long_

/**
 * Print standard help option (other option only).
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param print
 *   The output structure to print to.
 *   This requires print.set to be non-NULL.
 * @param option_other
 *   The other name of the option.
 * @param description
 *   A desciption associated with the option.
 *
 * @return
 *   F_none on success.
 *
 * @see f_print_terminated()
 * @see fl_print_format()
 */
#ifndef _di_fll_program_print_help_option_other_
  extern f_status_t fll_program_print_help_option_other(const fl_print_t print, const f_string_static_t option_other, const char *description);
#endif // _di_fll_program_print_help_option_other_

/**
 * Print all standard help options.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param print
 *   The output structure to print to.
 *   This requires print.set to be non-NULL.
 * @param context
 *   The color context.
 *
 * @return
 *   F_none on success.
 *
 * @see f_print_terminated()
 * @see fl_print_format()
 */
#ifndef _di_fll_program_print_help_option_standard_
  extern f_status_t fll_program_print_help_option_standard(const fl_print_t print);
#endif // _di_fll_program_print_help_option_standard_

/**
 * Print standard help usage.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param print
 *   The output structure to print to.
 *   This requires print.set to be non-NULL.
 * @param name
 *   The name of the program.
 * @param parameters
 *   (optional) The non-option parameters to be displayed inside the brackets.
 *   Set the first array value to EOS to disable printing of parameters.
 *   Set parameters.used to 0 to disable.
 *
 * @return
 *   F_none on success.
 *
 * @see f_print_terminated()
 * @see fl_print_format()
 */
#ifndef _di_fll_program_print_help_usage_
  extern f_status_t fll_program_print_help_usage(const fl_print_t print, const f_string_static_t name, const f_string_static_t parameters);
#endif // _di_fll_program_print_help_usage_

/**
 * Print a message about a process signal being recieved, such as an interrupt signal, as a warning.
 *
 * This is only printed when verbosity is set to verbose or debug.
 *
 * @param print
 *   The output structure to print to.
 *   This requires print.set to be non-NULL.
 * @param line_first
 *   The first line character, which is expected to be set to either f_string_eol_s or f_string_empty_s.
 * @param signal
 *   The signal code received.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fll_program_print_signal_received_
  extern f_status_t fll_program_print_signal_received(const fl_print_t print, const f_string_static_t line_first, const f_status_t signal);
#endif // _di_fll_program_print_signal_received_

/**
 * Print the program version.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param print
 *   The output structure to print to.
 *   This requires print.set to be non-NULL.
 * @param version
 *   The version number of the program.
 *
 * @return
 *   F_none on success.
 *
 * @see fl_print_format()
 */
#ifndef _di_fll_program_print_version_
  extern f_status_t fll_program_print_version(const fl_print_t print, const f_string_static_t version);
#endif // _di_fll_program_print_version_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_program_print_h
