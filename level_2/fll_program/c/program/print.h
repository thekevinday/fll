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
 * Print Featureless Linux Library copyright.
 *
 * @param print
 *   The output structure to print to.
 *   The print.verbosity is used to determine how much detail is printed (except for when _di_detailed_copyright_ is set).
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fll_program_print_copyright_
  extern f_status_t fll_program_print_copyright(const fl_print_t print);
#endif // _di_fll_program_print_copyright_

/**
 * Print an error message when a file is not provided.
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
#ifndef _di_fll_program_print_error_missing_file_
  extern f_status_t fll_program_print_error_missing_file(const fl_print_t print);
#endif // _di_fll_program_print_error_missing_file_

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
 * @param symbol_1
 *   The symbol string prepended to the first parameter.
 *   This is usually f_console_symbol_long_normal_s.
 * @param symbol_2
 *   The symbol string prepended to the second parameter.
 *   This is usually f_console_symbol_long_normal_s.
 * @param name_1
 *   The first parameter name.
 * @param name_2
 *   The second parameter name.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fll_program_print_error_parameter_both_specified_same_amount_
  extern f_status_t fll_program_print_error_parameter_both_specified_same_amount(const fl_print_t print, const f_string_static_t symbol_1, const f_string_static_t symbol_2, const f_string_static_t name_1, const f_string_static_t name_2);
#endif // _di_fll_program_print_error_parameter_both_specified_same_amount_

/**
 * Print an error message about two parameters being required to be specified the same number of times when not specifying the third parameter.
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
 * @param symbol_1
 *   The symbol string prepended to the first parameter.
 *   This is usually f_console_symbol_long_normal_s.
 * @param symbol_2
 *   The symbol string prepended to the second parameter.
 *   This is usually f_console_symbol_long_normal_s.
 * @param symbol_3
 *   The symbol string prepended to the third parameter.
 *   This is usually f_console_symbol_long_normal_s.
 * @param name_1
 *   The first parameter name.
 * @param name_2
 *   The second parameter name.
 * @param name_3
 *   The third parameter name, representing the "without" parameter.
 *   The first and second parameter must be specified the same amount of times without this parameter.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fll_program_print_error_parameter_both_specified_same_amount_without_
  extern f_status_t fll_program_print_error_parameter_both_specified_same_amount_without(const fl_print_t print, const f_string_static_t symbol_1, const f_string_static_t symbol_2, const f_string_static_t symbol_3, const f_string_static_t name_1, const f_string_static_t name_2, const f_string_static_t name_3);
#endif // _di_fll_program_print_error_parameter_both_specified_same_amount_without_

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
 * @param symbol_1
 *   The symbol string prepended to the first parameter.
 *   This is usually f_console_symbol_long_normal_s.
 * @param symbol_2
 *   The symbol string prepended to the second parameter.
 *   This is usually f_console_symbol_long_normal_s.
 * @param name_1
 *   The first parameter name.
 * @param name_2
 *   The second parameter name.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fll_program_print_error_parameter_cannot_use_with_
  extern f_status_t fll_program_print_error_parameter_cannot_use_with(const fl_print_t print, const f_string_static_t symbol_1, const f_string_static_t symbol_2, const f_string_static_t name_1, const f_string_static_t name_2);
#endif // _di_fll_program_print_error_parameter_cannot_use_with_

/**
 * Print message about two parameters not being allowed to be used together when a third is not used.
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
 * @param symbol_1
 *   The symbol string prepended to the first parameter.
 *   This is usually f_console_symbol_long_normal_s.
 * @param symbol_2
 *   The symbol string prepended to the second parameter.
 *   This is usually f_console_symbol_long_normal_s.
 * @param symbol_3
 *   The symbol string prepended to the second parameter.
 *   This is usually f_console_symbol_long_normal_s.
 * @param name_1
 *   The first parameter name (the parameter that cannot be used with the second parameter).
 * @param name_2
 *   The second parameter name.
 * @param name_3
 *   The third parameter name (the without parameter).
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fll_program_print_error_parameter_cannot_use_with_without_
  extern f_status_t fll_program_print_error_parameter_cannot_use_with_without(const fl_print_t print, const f_string_static_t symbol_1, const f_string_static_t symbol_2, const f_string_static_t symbol_3, const f_string_static_t name_1, const f_string_static_t name_2, const f_string_static_t name_3);
#endif // _di_fll_program_print_error_parameter_cannot_use_with_without_

/**
 * Print message about one parameter not being allowed to be used when processing a pipe.
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
 *   The symbol string prepended to the first parameter.
 *   This is usually f_console_symbol_long_normal_s.
 * @param name
 *   The parameter name.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fll_program_print_error_parameter_cannot_use_with_pipe_
  extern f_status_t fll_program_print_error_parameter_cannot_use_with_pipe(const fl_print_t print, const f_string_static_t symbol, const f_string_static_t name);
#endif // _di_fll_program_print_error_parameter_cannot_use_with_pipe_

/**
 * Print message about two parameters not being allowed to be used together with another specified parameter.
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
 * @param symbol_1
 *   The symbol string prepended to the first parameter.
 *   This is usually f_console_symbol_long_normal_s.
 * @param symbol_2
 *   The symbol string prepended to the second parameter.
 *   This is usually f_console_symbol_long_normal_s.
 * @param symbol_3
 *   The symbol string prepended to the third parameter.
 *   This is usually f_console_symbol_long_normal_s.
 * @param name_1
 *   The first parameter name.
 *
 *   This represents the parameter that imposes the exclusive or relation on the second and third parameters.
 * @param name_2
 *   The second parameter name.
 *
 *   This represents the parameter that is an exclusive or with the third parameter.
 * @param name_3
 *   The second parameter name.
 *
 *   This represents the parameter that is an exclusive or with the second parameter.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fll_program_print_error_parameter_allows_either_xor_
  extern f_status_t fll_program_print_error_parameter_cannot_use_with_xor(const fl_print_t print, const f_string_static_t symbol_1, const f_string_static_t symbol_2, const f_string_static_t symbol_3, const f_string_static_t name_1, const f_string_static_t name_2, const f_string_static_t name_3);
#endif // _di_fll_program_print_error_parameter_allows_either_xor_

/**
 * Print message about parameter not being a valid integer.
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
 *   This is usually f_console_symbol_long_normal_s.
 * @param name
 *   The parameter name.
 * @param value
 *   The value.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fll_program_print_error_parameter_integer_not_
  extern f_status_t fll_program_print_error_parameter_integer_not(const fl_print_t print, const f_string_static_t symbol, const f_string_static_t name, const f_string_static_t value);
#endif // _di_fll_program_print_error_parameter_integer_not_

/**
 * Print message about parameter not being a negative integer.
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
 *   This is usually f_console_symbol_long_normal_s.
 * @param name
 *   The parameter name.
 * @param value
 *   The value.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fll_program_print_error_parameter_integer_not_negative_
  extern f_status_t fll_program_print_error_parameter_integer_not_negative(const fl_print_t print, const f_string_static_t symbol, const f_string_static_t name, const f_string_static_t value);
#endif // _di_fll_program_print_error_parameter_integer_not_negative_

/**
 * Print message about parameter not being a positive integer.
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
 *   This is usually f_console_symbol_long_normal_s.
 * @param name
 *   The parameter name.
 * @param value
 *   The value.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fll_program_print_error_parameter_integer_not_positive_
  extern f_status_t fll_program_print_error_parameter_integer_not_positive(const fl_print_t print, const f_string_static_t symbol, const f_string_static_t name, const f_string_static_t value);
#endif // _di_fll_program_print_error_parameter_integer_not_positive_

/**
 * Print message about parameter not have the required value associated with this parameter.
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
 *   This is usually f_console_symbol_long_normal_s.
 * @param name
 *   The parameter name.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fll_program_print_error_parameter_missing_value_
  extern f_status_t fll_program_print_error_parameter_missing_value(const fl_print_t print, const f_string_static_t symbol, const f_string_static_t name);
#endif // _di_fll_program_print_error_parameter_missing_value_

/**
 * Print message about parameter not have the required amount of values associated with this parameter.
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
 *   This is usually f_console_symbol_long_normal_s.
 * @param name
 *   The parameter name.
 * @param amount
 *   A string representing the amount of missing parameters.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fll_program_print_error_parameter_missing_value_requires_amount_
  extern f_status_t fll_program_print_error_parameter_missing_value_requires_amount(const fl_print_t print, const f_string_static_t symbol, const f_string_static_t name, const f_string_static_t amount);
#endif // _di_fll_program_print_error_parameter_missing_value_requires_amount_

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
 *   This is usually f_console_symbol_long_normal_s.
 * @param name
 *   The parameter name.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fll_program_print_error_parameter_must_specify_once_
  extern f_status_t fll_program_print_error_parameter_must_specify_once(const fl_print_t print, const f_string_static_t symbol, const f_string_static_t name);
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
 *   This is usually f_console_symbol_long_normal_s.
 * @param name
 *   The parameter name.
 * @param value
 *   The value.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fll_program_print_error_parameter_must_specify_once_value_
  extern f_status_t fll_program_print_error_parameter_must_specify_once_value(const fl_print_t print, const f_string_static_t symbol, const f_string_static_t name, const f_string_static_t value);
#endif // _di_fll_program_print_error_parameter_must_specify_once_value_

/**
 * Print message about parameter processing failure.
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
 *   This is usually f_console_symbol_long_normal_s.
 * @param name
 *   The parameter name.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fll_program_print_error_parameter_process_
  extern f_status_t fll_program_print_error_parameter_process(const fl_print_t print, const f_string_static_t symbol, const f_string_static_t name);
#endif // _di_fll_program_print_error_parameter_process_

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
 *   This is usually f_console_symbol_long_normal_s.
 * @param name
 *   The parameter name.
 * @param value_start
 *   The range start value.
 * @param value_stop
 *   The range stop value.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fll_program_print_error_parameter_range_start_before_stop_
  extern f_status_t fll_program_print_error_parameter_range_start_before_stop(const fl_print_t print, const f_string_static_t symbol, const f_string_static_t name, const f_string_static_t value_start, const f_string_static_t value_stop);
#endif // _di_fll_program_print_error_parameter_range_start_before_stop_

/**
 * Print error message for when the parameter value is too long.
 *
 * @param print
 *   The output structure.
 *   This locks, uses, and unlocks the file stream.
 * @param symbol
 *   The symbol string prepended to both parameters.
 *   This locks, uses, and unlocks the file stream.
 *   This is usually f_console_symbol_long_normal_s.
 * @param name
 *   The parameter name.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fll_program_print_error_parameter_value_too_long_
  extern f_status_t fll_program_print_error_parameter_value_too_long(const fl_print_t print, const f_string_static_t symbol, const f_string_static_t name);
#endif // _di_fll_program_print_error_parameter_value_too_long_

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
 * @param signal
 *   The signal code received.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fll_program_print_signal_received_
  extern f_status_t fll_program_print_signal_received(const fl_print_t print, const uint32_t signal);
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
