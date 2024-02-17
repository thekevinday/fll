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
 *   - operation_show_filter:            For the show operation, show filter.
 *   - operation_show_filter_nat_mangle: A helper flag representing the show nat, show mangle, and short filter flags set.
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
    firewall_main_flag_operation_e                        = 0x31c,
    firewall_main_flag_operation_lock_e                   = 0x4,
    firewall_main_flag_operation_restart_e                = 0x8,
    firewall_main_flag_operation_show_e                   = 0x10,
    firewall_main_flag_operation_show_nat_e               = 0x20,
    firewall_main_flag_operation_show_mangle_e            = 0x40,
    firewall_main_flag_operation_show_filter_e            = 0x80,
    firewall_main_flag_operation_show_filter_nat_mangle_e = 0xe0,
    firewall_main_flag_operation_start_e                  = 0x100,
    firewall_main_flag_operation_start_restart_e          = 0x108,
    firewall_main_flag_operation_stop_e                   = 0x200,
    firewall_main_flag_operation_stop_restart_e           = 0x208,
    firewall_main_flag_operation_stop_restart_lock_e      = 0x20c,
    firewall_main_flag_pipe_e                             = 0x400,
    firewall_main_flag_print_first_e                      = 0x800,
    firewall_main_flag_print_last_e                       = 0x1000,
    firewall_main_flag_version_e                          = 0x2000,
    firewall_main_flag_version_copyright_help_e           = 0x2003,
  }; // enum
#endif // _di_firewall_main_flag_e_

/**
 * The firewall action.
 *
 * firewall_action_*_e:
 *   - none:   The action is none.
 *   - append: The action is append.
 *   - insert: The action is insert.
 *   - policy: The action is policy.
 */
#ifndef _di_firewall_action_e_
  enum {
    firewall_action_none_e,
    firewall_action_append_e,
    firewall_action_insert_e,
    firewall_action_policy_e,
  }; // enum
#endif // _di_firewall_action_e_

/**
 * The firewall chain.
 *
 * firewall_chain_*_e:
 *   - none:        The chain is none.
 *   - custom:      The chain is custom.
 *   - forward:     The chain is forward.
 *   - input:       The chain is input.
 *   - output:      The chain is output.
 *   - postrouting: The chain is postrouting.
 *   - prerouting:  The chain is prerouting.
 */
#ifndef _di_firewall_action_e_
  enum {
    firewall_chain_none_e,
    firewall_chain_custom_e,
    firewall_chain_forward_e,
    firewall_chain_input_e,
    firewall_chain_output_e,
    firewall_chain_postrouting_e,
    firewall_chain_prerouting_e,
  }; // enum
#endif // _di_firewall_action_e_

/**
 * Flags representing the current state of the processed rule.
 *
 * firewall_data_is_*_e:
 *   - none:           No flags set.
 *   - global:         The current processed rule is global.
 *   - local:          The current processed rule is lock.
 *   - main:           The current processed rule is main.
 *   - stop:           The current processed rule is stop.
 *   - stop_main_lock: Helper flag representing main, stop, and lock being set.
 */
#ifndef _di_firewall_data_is_e_
  enum {
    firewall_data_is_none_e           = 0x0,
    firewall_data_is_global_e         = 0x1,
    firewall_data_is_lock_e           = 0x2,
    firewall_data_is_main_e           = 0x4,
    firewall_data_is_stop_e           = 0x8,
    firewall_data_is_stop_main_lock_e = 0xe,
  }; // enum
#endif // _di_firewall_data_is_e_

/**
 * Flags representing the existence of reserved sets.
 *
 * firewall_data_has_*_e:
 *   - none:  No flags set.
 *   - local: The current processed rule is lock.
 *   - main:  The current processed rule is main.
 *   - stop:  The current processed rule is stop.
 */
#ifndef _di_firewall_data_has_e_
  enum {
    firewall_data_has_none_e = 0x0,
    firewall_data_has_lock_e = 0x1,
    firewall_data_has_main_e = 0x2,
    firewall_data_has_stop_e = 0x4,
  }; // enum
#endif // _di_firewall_data_has_e_

/**
 * The firewall direction.
 *
 * firewall_direction_*_e:
 *   - none:   No direction.
 *   - input:  The input direction.
 *   - output: The output direction.
 */
#ifndef _di_firewall_direction_e_
  enum {
    firewall_direction_none_e = 0,
    firewall_direction_input_e,
    firewall_direction_output_e,
  }; // enum
#endif // _di_firewall_direction_e_

/**
 * The firewall tool (the program being used).
 *
 * firewall_tool_*_e:
 *   - none:       No flags set.
 *   - ip46tables: Use both iptables and ip6tables tools.
 *   - ip6tables:  Use the ip6tables tool.
 *   - ipset:      Use the ipset tool.
 *   - iptables:   Use the iptables tool.
 */
#ifndef _di_firewall_tool_e_
  enum {
    firewall_tool_none_e = 0,
    firewall_tool_ip46tables_e,
    firewall_tool_ip6tables_e,
    firewall_tool_iptables_e,
    firewall_tool_ipset_e,
  }; // enum
#endif // _di_firewall_tool_e_

/**
 * The main program parameters.
 */
#ifndef _di_firewall_parameter_e_
  enum {
    firewall_parameter_operation_lock_e = f_console_standard_parameter_last_e,
    firewall_parameter_operation_restart_e,
    firewall_parameter_operation_show_e,
    firewall_parameter_operation_start_e,
    firewall_parameter_operation_stop_e,
  }; // enum

  #define firewall_console_parameter_t_initialize \
    { \
      macro_fll_program_console_parameter_standard_initialize, \
      \
      macro_f_console_parameter_t_initialize_6(firewall_operation_lock_s,    0, f_console_flag_simple_e), \
      macro_f_console_parameter_t_initialize_6(firewall_operation_restart_s, 0, f_console_flag_simple_e), \
      macro_f_console_parameter_t_initialize_6(firewall_operation_show_s,    0, f_console_flag_simple_e), \
      macro_f_console_parameter_t_initialize_6(firewall_operation_start_s,   0, f_console_flag_simple_e), \
      macro_f_console_parameter_t_initialize_6(firewall_operation_stop_s,    0, f_console_flag_simple_e), \
    }

  #define firewall_parameter_total_d (f_console_parameter_state_type_total_d + 5)
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
