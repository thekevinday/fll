/**
 * FLL - Level 3
 *
 * Project: Control
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common enumeration types.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _control_common_enumeration_h
#define _control_common_enumeration_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Codes representing supported actions.
 *
 * freeze:   Perform the freeze controller operation.
 * kexec:    Perform the kexec controller operation (only for init mode).
 * kill:     Perform the kill controller operation.
 * pause:    Perform the pause controller operation.
 * reboot:   Perform the reboot controller operation (only for init mode).
 * reload:   Perform the reload controller operation.
 * rerun:    Perform the rerun controller operation.
 * restart:  Perform the restart controller operation.
 * resume:   Perform the resume controller operation.
 * shutdown: Perform the shutdown controller operation (only for init mode).
 * start:    Perform the start controller operation.
 * stop:     Perform the stop controller operation.
 * thaw:     Perform the thaw controller operation.
 */
#ifndef _di_control_action_type_e_
  enum {
    control_action_type_freeze_e = 1,
    control_action_type_kexec_e,
    control_action_type_kill_e,
    control_action_type_pause_e,
    control_action_type_reboot_e,
    control_action_type_reload_e,
    control_action_type_rerun_e,
    control_action_type_restart_e,
    control_action_type_resume_e,
    control_action_type_shutdown_e,
    control_action_type_start_e,
    control_action_type_stop_e,
    control_action_type_thaw_e,
  }; // enum
#endif // _di_control_action_type_e_

/**
 * Supported payload types.
 *
 * controller: The payload is a controller payload.
 * error:      The payload is an error payload.
 * init:       The payload is an init payload (only available when operating in "init" mode).
 */
#ifndef _di_control_payload_type_e_
  enum {
    control_payload_type_controller_e = 1,
    control_payload_type_error_e,
    control_payload_type_init_e,
  }; // enum
#endif // _di_control_payload_type_e_

/**
 * A codes repesent different flags associated with a packet.
 *
 * control_packet_flag_*:
 *   - binary:     Designate that the packet is in binary mode (when not set then packet is in string mode).
 *   - endian_big: Designate that the packet is in big endian order (when not set then packet is in little endian order).
 */
#ifndef _di_control_packet_flag_e_
  #define control_packet_flag_binary_d     0x80
  #define control_packet_flag_endian_big_d 0x40
#endif // _di_control_packet_flag_e_

/**
 * Flags passed to the main function or program.
 *
 * control_main_flag_*_e:
 *   - none:                   No flags set.
 *   - copyright:              Print copyright.
 *   - header:                 Enable printing of headers.
 *   - help:                   Print help.
 *   - pipe:                   Use the input pipe.
 *   - print_first:            When set, print new line to message output on program begin after loading settings.
 *   - print_last:             When set, print new line to message output on program end.
 *   - return:                 The parameter is specified.
 *   - version:                Print version.
 *   - version_copyright_help: A helper flag representing version, copyright, and help flag bits being set.
 */
#ifndef _di_control_main_flag_e_
  enum {
    control_main_flag_none_e                   = 0x0,
    control_main_flag_copyright_e              = 0x1,
    control_main_flag_help_e                   = 0x2,
    control_main_flag_pipe_e                   = 0x4,
    control_main_flag_print_first_e            = 0x8,
    control_main_flag_print_last_e             = 0x10,
    control_main_flag_return_e                 = 0x20,
    control_main_flag_version_e                = 0x40,
    control_main_flag_version_copyright_help_e = 0x43,
  }; // enum
#endif // _di_control_main_flag_e_

/**
 * The main program parameters.
 */
#ifndef _di_control_parameter_d_
  enum {
    control_parameter_name_e = f_console_standard_parameter_last_e,
    control_parameter_return_e,
    control_parameter_settings_e,
    control_parameter_socket_e,
  }; // enum

  #define control_console_parameter_t_initialize \
    { \
      macro_fll_program_console_parameter_standard_initialize, \
      \
      macro_f_console_parameter_t_initialize_3(control_short_name_s,     control_long_name_s,     1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(control_short_return_s,   control_long_return_s,   1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(control_short_settings_s, control_long_settings_s, 1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(control_short_socket_s,   control_long_socket_s,   1, f_console_flag_normal_e), \
    }

  #define control_parameter_total_d (f_console_parameter_state_type_total_d + 4)
#endif // _di_control_parameter_d_

/**
 * Flags for fine-tuned print control.
 *
 * control_print_flag_*_e:
 *   - none:    No flags set.
 *   - debug:   Stream is for debug printing.
 *   - error:   Stream is for error printing.
 *   - in:      Stream is a source file.
 *   - message: Stream is for message printing.
 *   - out:     Stream is a destination file.
 *   - warning: Stream is for warning printing.
 */
#ifndef _di_control_print_flag_e_
  enum {
    control_print_flag_none_e    = 0x0,
    control_print_flag_debug_e   = 0x1,
    control_print_flag_error_e   = 0x2,
    control_print_flag_file_e    = 0x4,
    control_print_flag_in_e      = 0x8,
    control_print_flag_out_e     = 0x10,
    control_print_flag_message_e = 0x20,
    control_print_flag_warning_e = 0x40,
  }; // enum
#endif // _di_control_print_flag_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _control_common_enumeration_h
