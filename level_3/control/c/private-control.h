/**
 * FLL - Level 3
 *
 * Project: Control
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_control_h
#define _PRIVATE_control_h

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Identify the command code the given name represents.
 *
 * @param main
 *   The main program data.
 * @param data
 *   The control data.
 * @param command
 *   The parameter representing a command.
 *
 * @return
 *   F_found on success.
 *   F_found_not if name is unknown.
 */
#ifndef _di_control_command_identify_
  extern f_status_t control_command_identify(control_main_t * const main, control_data_t * const data, const f_string_static_t command) F_attribute_visibility_internal_d;
#endif // _di_control_command_identify_

/**
 * Verify that the additional parameters are reasonably correct for the identified command.
 *
 * @param main
 *   The main program data.
 * @param data
 *   The control data.
 */
#ifndef _di_control_command_verify_
  extern f_status_t control_command_verify(control_main_t * const main, control_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_control_command_verify_
/**
 * Load and process the control settings file.
 *
 * This identifies and attempts to connect to the socket.
 *
 * @param main
 *   The main program data.
 * @param data
 *   The control data.
 *
 * @return
 *   F_none on success.
 *
 *   F_interrupt (with error bit) on receiving a terminate process signal, such as an interrupt signal.
 *   F_socket_not (with error bit) on socket related error preventing the socket from being created or connected to.
 *
 *   Errors (with error bit) from: f_file_exists().
 *   Errors (with error bit) from: f_file_open().
 *   Errors (with error bit) from: f_file_stream_read().
 *   Errors (with error bit) from: f_socket_connect().
 *   Errors (with error bit) from: f_socket_create().
 *   Errors (with error bit) from: f_string_append().
 *   Errors (with error bit) from: f_string_append_assure().
 *   Errors (with error bit) from: f_string_dynamic_append_nulless().
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *   Errors (with error bit) from: f_string_dynamic_terminate_after().
 *   Errors (with error bit) from: f_string_dynamics_resize().
 *   Errors (with error bit) from: fl_fss_apply_delimit().
 *   Errors (with error bit) from: fll_fss_extended_read().
 *
 * @see f_file_exists()
 * @see f_file_open()
 * @see f_file_stream_read()
 * @see f_socket_connect()
 * @see f_socket_create()
 * @see f_string_append()
 * @see f_string_append_assure()
 * @see f_string_dynamic_append_nulless()
 * @see f_string_dynamic_partial_append_nulless()
 * @see f_string_dynamic_terminate_after()
 * @see f_string_dynamics_resize()
 * @see fl_fss_apply_delimit()
 * @see fll_fss_extended_read()
 */
#ifndef _di_control_settings_load_
  extern f_status_t control_settings_load(control_main_t * const main, control_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_control_settings_load_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_control_h
