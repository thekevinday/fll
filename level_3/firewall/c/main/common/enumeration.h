/**
 * FLL - Level 3
 *
 * Project: Firewall
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common enumeration types.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _firewall_common_enumeration_h
#define _firewall_common_enumeration_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Flags passed to the main function or program.
 *
 * firewall_main_flag_*_e:
 *   - none:                             No flags set.
 *   - copyright:                        Print copyright.
 *   - help:                             Print help.
 *   - operation:                        A helper flag representing every operation flag bit being set.
 *   - operation_lock:                   Perform the lock operation.
 *   - operation_restart:                Perform the restart operation.
 *   - operation_show:                   Perform the show operation.
 *   - operation_show_nat:               For the show operation, show nat.
 *   - operation_show_mangle:            For the show operation, show mangle.
 *   - operation_show_filter:            For the show operation, show ports.
 *   - operation_show_filter_nat_mangle: A helper flag representing the show nat, show mangle, and short port flags set.
 *   - operation_start:                  Perform the start operation.
 *   - operation_start_restart:          A helper flag representing both the start and restart operation flag set.
 *   - operation_stop:                   Perform the stop operation.
 *   - operation_stop_restart:           A helper flag representing both the stop and restart operation flag set.
 *   - operation_stop_restart_lock:      A helper flag representing both the stop, restart, and lock operation flag set.
 *   - pipe:                             Use the input pipe.
 *   - print_first:                      When set, print new line to message output on program begin after loading settings.
 *   - print_last:                       When set, print new line to message output on program end.
 *   - version:                          Print version.
 *   - version_copyright_help:           A helper flag representing version, copyright, and help flag bits being set.
 */
#ifndef _di_firewall_main_flag_e_
  enum {
    firewall_main_flag_none_e                             = 0x0,
    firewall_main_flag_copyright_e                        = 0x1,
    firewall_main_flag_help_e                             = 0x2,
    firewall_main_flag_operation_e                        = 0x4,
    firewall_main_flag_operation_lock_e                   = 0x8,
    firewall_main_flag_operation_restart_e                = 0x10,
    firewall_main_flag_operation_show_e                   = 0x20,
    firewall_main_flag_operation_show_nat_e               = 0x40,
    firewall_main_flag_operation_show_mangle_e            = 0x80,
    firewall_main_flag_operation_show_filter_e            = 0x100,
    firewall_main_flag_operation_show_filter_nat_mangle_e = 0x1c0,
    firewall_main_flag_operation_start_e                  = 0x200,
    firewall_main_flag_operation_start_restart_e          = 0x210,
    firewall_main_flag_operation_stop_e                   = 0x400,
    firewall_main_flag_operation_stop_restart_e           = 0x410,
    firewall_main_flag_operation_stop_restart_lock_e      = 0x418,
    firewall_main_flag_pipe_e                             = 0x800,
    firewall_main_flag_print_first_e                      = 0x1000,
    firewall_main_flag_print_last_e                       = 0x2000,
    firewall_main_flag_version_e                          = 0x4000,
    firewall_main_flag_version_copyright_help_e           = 0x4003,
  }; // enum
#endif // _di_firewall_main_flag_e_

/**
 * Flags representing the current state of the processed rule.
 *
 * firewall_data_flag_*_e:
 *   - none:   No flags set.
 *   - global: The current processed rule is global.
 *   - local:  The current processed rule is lock.
 *   - main:   The current processed rule is main.
 *   - stop:   The current processed rule is stop.
 */
#ifndef _di_firewall_data_flag_e_
  enum {
    firewall_data_is_none_e   = 0x0,
    firewall_data_is_global_e = 0x1,
    firewall_data_is_lock_e   = 0x2,
    firewall_data_is_main_e   = 0x4,
    firewall_data_is_stop_e   = 0x8,
  }; // enum
#endif // _di_firewall_data_flag_e_

/**
 * Flags representing the existence of reserved sets.
 *
 * firewall_data_flag_*_e:
 *   - none:  No flags set.
 *   - local: The current processed rule is lock.
 *   - main:  The current processed rule is main.
 *   - stop:  The current processed rule is stop.
 */
#ifndef _di_firewall_data_flag_e_
  enum {
    firewall_data_has_none_e   = 0x0,
    firewall_data_has_lock_e   = 0x1,
    firewall_data_has_main_e   = 0x2,
    firewall_data_has_stop_e   = 0x4,
  }; // enum
#endif // _di_firewall_data_flag_e_

/**
 * The main program parameters.
 */
#ifndef _di_firewall_parameter_e_
  enum {
    fake_parameter_operation_build_e = f_console_standard_parameter_last_e,
    fake_parameter_operation_clean_e,
    fake_parameter_operation_make_e,
    fake_parameter_operation_skeleton_e,
  }; // enum

  #define firewall_console_parameter_t_initialize \
    { \
      macro_fll_program_console_parameter_standard_initialize, \
      \
      macro_f_console_parameter_t_initialize_6(fake_other_operation_build_s,    0, f_console_flag_simple_e), \
      macro_f_console_parameter_t_initialize_6(fake_other_operation_clean_s,    0, f_console_flag_simple_e), \
      macro_f_console_parameter_t_initialize_6(fake_other_operation_make_s,     0, f_console_flag_simple_e), \
      macro_f_console_parameter_t_initialize_6(fake_other_operation_skeleton_s, 0, f_console_flag_simple_e), \
    }

  #define firewall_parameter_total_d (f_console_parameter_state_type_total_d + 4)
#endif // _di_firewall_parameter_e_

/**
 * Flags for fine-tuned print control.
 *
 * firewall_print_flag_*_e:
 *   - none:    No flags set.
 *   - debug:   Stream is for debug printing.
 *   - error:   Stream is for error printing.
 *   - in:      Stream is a source file.
 *   - message: Stream is for message printing.
 *   - out:     Stream is a destination file.
 *   - warning: Stream is for warning printing.
 */
#ifndef _di_firewall_print_flag_e_
  enum {
    firewall_print_flag_none_e    = 0x0,
    firewall_print_flag_debug_e   = 0x1,
    firewall_print_flag_error_e   = 0x2,
    firewall_print_flag_file_e    = 0x4,
    firewall_print_flag_in_e      = 0x8,
    firewall_print_flag_out_e     = 0x10,
    firewall_print_flag_message_e = 0x20,
    firewall_print_flag_warning_e = 0x40,
  }; // enum
#endif // _di_firewall_print_flag_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _firewall_common_enumeration_h
