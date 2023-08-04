/**
 * FLL - Level 3
 *
 * Project: Control
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _control_common_print_h
#define _control_common_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A special array of strings intended for representing funciton names.
 *
 * These are primarily used for printing errors with the function names.
 *
 * The macro macro_control_f() is used to reference the array index by the enum name.
 *
 * macro_control_f():
 *   - name: The name of the function.
 */
#ifndef _di_control_f_a_
  extern const f_string_t control_f_a[];

  #define macro_control_f(name) control_f_a[control_f_##name##_e]
#endif // _di_control_f_a_

/**
 * An enum representing specific indexes within the above array.
 *
 * This is a convenience enum used to make code slightly more readable.
 */
#ifndef _di_control_f_e_
  enum {
    control_f_control_packet_build_e,
    control_f_control_packet_process_e,
    control_f_control_packet_receive_e,
    control_f_control_packet_send_e,
    control_f_f_console_parameter_process_e,
    control_f_f_file_exists_e,
    control_f_f_file_stream_open_e,
    control_f_f_file_stream_read_e,
    control_f_f_fss_apply_delimit_e,
    control_f_f_socket_connect_e,
    control_f_f_socket_create_e,
    control_f_f_string_dynamic_append_e,
    control_f_f_string_dynamic_append_assure_e,
    control_f_f_string_dynamic_partial_append_nulless_e,
    control_f_f_string_dynamic_resize_e,
    control_f_f_string_dynamics_increase_by_e,
    control_f_f_thread_create_e,
    control_f_fll_fss_extended_read_e,
    control_f_fll_program_parameter_process_context_standard_e,
    control_f_fll_program_parameter_process_verbosity_standard_e,
  }; // enum
#endif // _di_control_f_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _control_common_print_h
