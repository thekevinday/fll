/**
 * FLL - Level 3
 *
 * Project: Byte Dump
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print error functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _byte_dump_print_error_h
#define _byte_dump_print_error_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print generic error message regarding a function failing in some way.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_print()
 */
#ifndef _di_byte_dump_print_error_
  extern f_status_t byte_dump_print_error(fl_print_t * const print, const f_string_t function);
#endif // _di_byte_dump_print_error_

/**
 * Print file related error or warning messages.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param function
 *   The name of the function where the error happened.
 *   Set to 0 to disable.
 * @param name
 *   The name of the file or directory.
 * @param operation
 *   The operation that fails, such as 'create' or 'access'.
 * @param type
 *   A valid file type code from the fll_error_file_type enum.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_byte_dump_print_error_file_
  extern f_status_t byte_dump_print_error_file(fl_print_t * const print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type);
#endif // _di_byte_dump_print_error_file_

/**
 * Print error message for when file contains invalid UTF-8 codes.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param name
 *   The name of the file the header is associated with.
 *   If name.used is 0 then this is assumed to be the input pipe.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fll_program_print_error_file_code_invalid_
  extern f_status_t fll_program_print_error_file_code_invalid(fl_print_t * const print, const f_string_static_t name);
#endif // _di_fll_program_print_error_file_code_invalid_

/**
 * Print error message for when no files are provided.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_byte_dump_print_error_file_none_
  extern f_status_t byte_dump_print_error_file_none(fl_print_t * const print);
#endif // _di_byte_dump_print_error_file_none_

/**
 * Print error message on file read error.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param name
 *   The name of the file the header is associated with.
 *   If name.used is 0 then this is assumed to be the input pipe.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fll_program_print_error_file_read_
  extern f_status_t fll_program_print_error_file_read(fl_print_t * const print, const f_string_static_t name);
#endif // _di_fll_program_print_error_file_read_

/**
 * Print error about "first" parameter value being greater than the "last" parameter value.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fll_program_print_error_parameter_first_greater_than_last_
  extern f_status_t fll_program_print_error_parameter_first_greater_than_last(fl_print_t * const print);
#endif // _di_fll_program_print_error_parameter_first_greater_than_last_

/**
 * Print error about given value being out of range.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param name
 *   The name of the parameter.
 * @param minimum
 *   The inclusive non-negative minimum allowed number.
 * @param maximum
 *   The inclusive non-negative maximum allowed number.
 * @param number
 *   A string that is supposed to be a valid number within range (but is not).
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_byte_dump_print_error_parameter_range_out_
  extern f_status_t byte_dump_print_error_parameter_range_out(fl_print_t * const print, const f_string_static_t name, const f_number_unsigned_t minimum, const f_number_unsigned_t maximum, const f_string_static_t number);
#endif // _di_byte_dump_print_error_parameter_range_out_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _byte_dump_print_error_h
