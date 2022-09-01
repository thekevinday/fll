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
 * Print an error message a variable not being defined or the variable has a length is 0.
 *
 * This is only printed when verbosity is not set to quiet.
 *
 * This uses the following:
 *   - print.set->error: For the error context.
 *   - print.set->strong: For the highlighting context
 *   - print.prefix: For the prefixing a string to the message (such as "ERROR:").
 *
 * @param print
 *   The output structure.
 *   This locks, uses, and unlocks the file stream.
 * @param variable
 *   The name of the variable that is not defined or has a length of 0.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fll_program_print_error_missing_variable_not_zero_
  extern f_status_t fll_program_print_error_missing_variable_not_zero(const fl_print_t print, const f_string_static_t variable);
#endif // _di_fll_program_print_error_missing_variable_not_zero_

/**
 * Print an error message about two parameters being required to be specified the same number of times.
 *
 * This is only printed when verbosity is not set to quiet.
 *
 * This uses the following:
 *   - print.set->error: For the error context.
 *   - print.set->strong: For the highlighting context
 *   - print.prefix: For the prefixing a string to the message (such as "ERROR:").
 *
 * @param print
 *   The output structure.
 *   This locks, uses, and unlocks the file stream.
 * @param symbol
 *   The symbol string prepended to both parameters.
 *   This is usually f_console_symbol_long_enable_s.
 * @param first
 *   The first parameter name.
 * @param second
 *   The second parameter name.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fll_program_print_error_parameter_both_specified_same_amount_
  extern f_status_t fll_program_print_error_parameter_both_specified_same_amount(const fl_print_t print, const f_string_static_t symbol, const f_string_static_t first, const f_string_static_t second);
#endif // _di_fll_program_print_error_parameter_both_specified_same_amount_

/**
 * Print message about two parameters not being allowed to be used together.
 *
 * This is only printed when verbosity is not set to quiet.
 *
 * This uses the following:
 *   - print.set->error: For the error context.
 *   - print.set->strong: For the highlighting context
 *   - print.prefix: For the prefixing a string to the message (such as "ERROR:").
 *
 * @param print
 *   The output structure.
 *   This locks, uses, and unlocks the file stream.
 * @param symbol
 *   The symbol string prepended to both parameters.
 *   This is usually f_console_symbol_long_enable_s.
 * @param first
 *   The first parameter name.
 * @param second
 *   The second parameter name.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fll_program_print_error_parameter_cannot_use_with_
  extern f_status_t fll_program_print_error_parameter_cannot_use_with(const fl_print_t print, const f_string_static_t symbol, const f_string_static_t first, const f_string_static_t second);
#endif // _di_fll_program_print_error_parameter_cannot_use_with_

/**
 * Print message about parameter not have the required value associated with this.
 *
 * This is only printed when verbosity is not set to quiet.
 *
 * This uses the following:
 *   - print.set->error: For the error context.
 *   - print.set->strong: For the highlighting context
 *   - print.prefix: For the prefixing a string to the message (such as "ERROR:").
 *
 * @param print
 *   The output structure.
 *   This locks, uses, and unlocks the file stream.
 * @param symbol
 *   The symbol string prepended to both parameters.
 *   This locks, uses, and unlocks the file stream.
 *   This is usually f_console_symbol_long_enable_s.
 * @param parameter
 *   The parameter name.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fll_program_print_error_parameter_missing_value_
  f_status_t fll_program_print_error_parameter_missing_value(const fl_print_t print, const f_string_static_t symbol, const f_string_static_t parameter);
#endif // _di_fll_program_print_error_parameter_missing_value_

/**
 * Print message about parameter only being allowed to be used once.
 *
 * This is only printed when verbosity is not set to quiet.
 *
 * This uses the following:
 *   - print.set->error: For the error context.
 *   - print.set->strong: For the highlighting context
 *   - print.prefix: For the prefixing a string to the message (such as "ERROR:").
 *
 * @param print
 *   The output structure.
 *   This locks, uses, and unlocks the file stream.
 * @param symbol
 *   The symbol string prepended to both parameters.
 *   This locks, uses, and unlocks the file stream.
 *   This is usually f_console_symbol_long_enable_s.
 * @param parameter
 *   The parameter name.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fll_program_print_error_parameter_must_specify_once_
  extern f_status_t fll_program_print_error_parameter_must_specify_once(const fl_print_t print, const f_string_static_t symbol, const f_string_static_t parameter);
#endif // _di_fll_program_print_error_parameter_must_specify_once_

/**
 * Print message about a specific value only being allowed to be used once for the parameter.
 *
 * This is only printed when verbosity is not set to quiet.
 *
 * This uses the following:
 *   - print.set->error: For the error context.
 *   - print.set->strong: For the highlighting context
 *   - print.prefix: For the prefixing a string to the message (such as "ERROR:").
 *
 * @param print
 *   The output structure.
 *   This locks, uses, and unlocks the file stream.
 * @param symbol
 *   The symbol string prepended to both parameters.
 *   This locks, uses, and unlocks the file stream.
 *   This is usually f_console_symbol_long_enable_s.
 * @param parameter
 *   The parameter name.
 * @param value
 *   The value.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fll_program_print_error_parameter_must_specify_once_value_
  extern f_status_t fll_program_print_error_parameter_must_specify_once_value(const fl_print_t print, const f_string_static_t symbol, const f_string_static_t parameter, const f_string_static_t value);
#endif // _di_fll_program_print_error_parameter_must_specify_once_value_

/**
 * Print a message about the pipe having an invalid form-feed character '\f' (U+000C).
 *
 * This is only printed when verbosity is not set to quiet.
 *
 * This uses the following:
 *   - print.set->error: For the error context.
 *   - print.set->strong: For the highlighting context
 *   - print.prefix: For the prefixing a string to the message (such as "ERROR:").
 *
 * @param print
 *   The output structure.
 *   This locks, uses, and unlocks the file stream.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fll_program_print_error_pipe_invalid_form_feed_
  extern f_status_t fll_program_print_error_pipe_invalid_form_feed(const fl_print_t print);
#endif // _di_fll_program_print_error_pipe_invalid_form_feed_

/**
 * Print a message about the pipe not having any content.
 *
 * This is only printed when verbosity is not set to quiet.
 *
 * This uses the following:
 *   - print.set->error: For the error context.
 *   - print.set->strong: For the highlighting context
 *   - print.prefix: For the prefixing a string to the message (such as "ERROR:").
 *
 * @param print
 *   The output structure.
 *   This locks, uses, and unlocks the file stream.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fll_program_print_error_pipe_missing_content_
  extern f_status_t fll_program_print_error_pipe_missing_content(const fl_print_t print);
#endif // _di_fll_program_print_error_pipe_missing_content_

/**
 * Print a message about the pipe having an Object without Content.
 *
 * This generally refers to an FSS Object and an FSS Content.
 *
 * This is only printed when verbosity is not set to quiet.
 *
 * This uses the following:
 *   - print.set->error: For the error context.
 *   - print.set->strong: For the highlighting context
 *   - print.prefix: For the prefixing a string to the message (such as "ERROR:").
 *
 * @param print
 *   The output structure.
 *   This locks, uses, and unlocks the file stream.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fll_program_print_error_pipe_object_without_content_
  extern f_status_t fll_program_print_error_pipe_object_without_content(const fl_print_t print);
#endif // _di_fll_program_print_error_pipe_object_without_content_

/**
 * Print standard help header.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param print
 *   The output structure to print to.
 *   This uses but does not lock or unlock file stream.
 *   This requires print.set to be non-NULL.
 * @param name
 *   The name of the program.
 * @param version
 *   The version number of the program.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
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
 *   This uses but does not lock or unlock file stream.
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
 *   F_output_not on success, but no printing is performed.
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
 *   This uses but does not lock or unlock file stream.
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
 *   F_output_not on success, but no printing is performed.
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
 *   This uses but does not lock or unlock file stream.
 *   This requires print.set to be non-NULL.
 * @param option_other
 *   The other name of the option.
 * @param description
 *   A desciption associated with the option.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
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
 *   The output structure to print to
 *   This uses but does not lock or unlock file stream.
 *   This requires print.set to be non-NULL.
 * @param context
 *   The color context.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
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
 *   This uses but does not lock or unlock file stream.
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
 *   F_output_not on success, but no printing is performed.
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
 *   This locks, uses, and unlocks the file stream.
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
  extern f_status_t fll_program_print_signal_received(const fl_print_t print, const f_string_static_t line_first, const uint32_t signal);
#endif // _di_fll_program_print_signal_received_

/**
 * Print the program version.
 *
 * @param print
 *   The output structure to print to.
 *   This uses but does not lock or unlock file stream.
 *   This requires print.set to be non-NULL.
 * @param version
 *   The version number of the program.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
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
