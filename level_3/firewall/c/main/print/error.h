/**
 * FLL - Level 3
 *
 * Project: Firewall
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print error functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _firewall_print_error_h
#define _firewall_print_error_h

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
 * @param function
 *   The name of the function associated with the error.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_print()
 */
#ifndef _di_firewall_print_error_
  extern f_status_t firewall_print_error(fl_print_t * const print, const f_string_t function);
#endif // _di_firewall_print_error_

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
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_firewall_print_error_file_
  extern f_status_t firewall_print_error_file(fl_print_t * const print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type);
#endif // _di_firewall_print_error_file_

/**
 * Print file related error message regarding that there is no relevant data in the file.
 *
 * The file is effectively empty but could have comments or other non-valid (aka non-Object) data.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param file
 *   The name of the file.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_firewall_print_error_file_empty_
  extern f_status_t firewall_print_error_file_empty(fl_print_t * const print, const f_string_static_t file);
#endif // _di_firewall_print_error_file_empty_

/**
 * Print error message regarding being unable to find any devices.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_print()
 */
#ifndef _di_firewall_print_error_network_device_none_
  extern f_status_t firewall_print_error_network_device_none(fl_print_t * const print);
#endif // _di_firewall_print_error_network_device_none_

/**
 * Print an error about the given operation failed.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param tool
 *   The tool, such as iptables, that failed.
 * @param arguments
 *   The arguments passed to the tool.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_firewall_print_error_operation_
  extern f_status_t firewall_print_error_operation(fl_print_t * const print, const f_string_static_t tool, const f_string_statics_t arguments);
#endif // _di_firewall_print_error_operation_

/**
 * Print an error about the operation setting missing from the file.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param operation
 *   The operation setting that is missing from the file.
 *   This is also the name of the operation itself.
 * @param file
 *   The file that is missing the operation.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_firewall_print_error_operation_files_missing_
  extern f_status_t firewall_print_error_operation_files_missing(fl_print_t * const print, const f_string_static_t operation, const f_string_static_t file);
#endif // _di_firewall_print_error_operation_files_missing_

/**
 * Print an error about the given operation failed according to the given return code.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param tool
 *   The tool, such as iptables, that failed.
 * @param arguments
 *   The arguments passed to the tool.
 * @param return_code
 *   The code returned by the tool.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_firewall_print_error_operation_return_code_
  extern f_status_t firewall_print_error_operation_return_code(fl_print_t * const print, const f_string_static_t tool, const f_string_statics_t arguments, const int return_code);
#endif // _di_firewall_print_error_operation_return_code_

/**
 * Print generic error message regarding a function failing in some way.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_print()
 */
#ifndef _di_firewall_print_error_operation_specified_not_
  extern f_status_t firewall_print_error_operation_specified_not(fl_print_t * const print);
#endif // _di_firewall_print_error_operation_specified_not_

/**
 * Print an unhandled error for the given function.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param function
 *   The name of the function associated with the error.
 * @param file
 *   The name of the file, if this error is assocaited with a file.
 *   Otherwise, set file.used to 0 to not have an file related error message.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_firewall_print_error_unhandled_
  extern f_status_t firewall_print_error_unhandled(fl_print_t * const print, const f_string_t function, const f_string_static_t file);
#endif // _di_firewall_print_error_unhandled_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _firewall_print_error_h
