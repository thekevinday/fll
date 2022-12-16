/**
 * FLL - Level 3
 *
 * Project: Control
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _control_common_h
#define _control_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program version.
 */
#ifndef _di_control_program_version_s_
  #define CONTROL_program_version_major_s F_string_ascii_0_s
  #define CONTROL_program_version_minor_s F_string_ascii_7_s
  #define CONTROL_program_version_micro_s F_string_ascii_0_s

  #define CONTROL_program_version_major_s_length F_string_ascii_0_s_length
  #define CONTROL_program_version_minor_s_length F_string_ascii_7_s_length
  #define CONTROL_program_version_micro_s_length F_string_ascii_0_s_length

  #if !(defined(CONTROL_program_version_nano_prefix_s) && defined(CONTROL_program_version_nano_prefix_s_length))
    #define CONTROL_program_version_nano_prefix_s
    #define CONTROL_program_version_nano_prefix_s_length 0
  #endif // !(defined(CONTROL_program_version_nano_prefix_s) && defined(CONTROL_program_version_nano_prefix_s_length))

  #if !(defined(CONTROL_program_version_nano_s) && defined(CONTROL_program_version_nano_s_length))
    #define CONTROL_program_version_nano_s
    #define CONTROL_program_version_nano_s_length 0
  #endif // !(defined(CONTROL_program_version_nano_s) && defined(CONTROL_program_version_nano_s_length))

  #define CONTROL_program_version_s CONTROL_program_version_major_s F_string_ascii_period_s CONTROL_program_version_minor_s F_string_ascii_period_s CONTROL_program_version_micro_s CONTROL_program_version_nano_prefix_s CONTROL_program_version_nano_s

  #define CONTROL_program_version_s_length CONTROL_program_version_major_s_length + F_string_ascii_period_s_length + CONTROL_program_version_minor_s_length + F_string_ascii_period_s_length + CONTROL_program_version_micro_s_length + CONTROL_program_version_nano_prefix_s_length + CONTROL_program_version_nano_s_length

  extern const f_string_static_t control_program_version_s;
#endif // _di_control_program_version_s_

/**
 * The program name.
 */
#ifndef _di_control_program_name_s_
  #define CONTROL_program_name_s      "control"
  #define CONTROL_program_name_long_s "Control Program"

  #define CONTROL_program_name_s_length      7
  #define CONTROL_program_name_long_s_length 15

  extern const f_string_static_t control_program_name_s;
  extern const f_string_static_t control_program_name_long_s;
#endif // _di_control_program_name_s_

/**
 * The main program parameters.
 */
#ifndef _di_control_parameter_d_
  #define CONTROL_short_name_s     "n"
  #define CONTROL_short_return_s   "R"
  #define CONTROL_short_settings_s "s"
  #define CONTROL_short_socket_s   "k"

  #define CONTROL_long_name_s     "name"
  #define CONTROL_long_return_s   "return"
  #define CONTROL_long_settings_s "settings"
  #define CONTROL_long_socket_s   "socket"

  #define CONTROL_short_name_s_length     1
  #define CONTROL_short_return_s_length   1
  #define CONTROL_short_settings_s_length 1
  #define CONTROL_short_socket_s_length   1

  #define CONTROL_long_name_s_length     4
  #define CONTROL_long_return_s_length   6
  #define CONTROL_long_settings_s_length 8
  #define CONTROL_long_socket_s_length   6

  extern const f_string_static_t control_short_name_s;
  extern const f_string_static_t control_short_return_s;
  extern const f_string_static_t control_short_settings_s;
  extern const f_string_static_t control_short_socket_s;

  extern const f_string_static_t control_long_name_s;
  extern const f_string_static_t control_long_return_s;
  extern const f_string_static_t control_long_settings_s;
  extern const f_string_static_t control_long_socket_s;

  enum {
    control_parameter_help_e = 0,
    control_parameter_light_e,
    control_parameter_dark_e,
    control_parameter_no_color_e,
    control_parameter_verbosity_quiet_e,
    control_parameter_verbosity_error_e,
    control_parameter_verbosity_normal_e,
    control_parameter_verbosity_verbose_e,
    control_parameter_verbosity_debug_e,
    control_parameter_version_e,
    control_parameter_line_first_no_e,
    control_parameter_line_last_no_e,

    control_parameter_name_e,
    control_parameter_return_e,
    control_parameter_settings_e,
    control_parameter_socket_e,
  }; // enum

  #define control_console_parameter_t_initialize \
    { \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_help_s,          f_console_standard_long_help_s,          0, f_console_flag_normal_e, 0), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_light_s,         f_console_standard_long_light_s,         0, f_console_flag_inverse_e, 0), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_dark_s,          f_console_standard_long_dark_s,          0, f_console_flag_inverse_e, 0), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_no_color_s,      f_console_standard_long_no_color_s,      0, f_console_flag_inverse_e, 0), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_quiet_s,         f_console_standard_long_quiet_s,         0, f_console_flag_inverse_e, 0), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_error_s,         f_console_standard_long_error_s,         0, f_console_flag_inverse_e, 0), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_normal_s,        f_console_standard_long_normal_s,        0, f_console_flag_inverse_e, 0), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_verbose_s,       f_console_standard_long_verbose_s,       0, f_console_flag_inverse_e, 0), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_debug_s,         f_console_standard_long_debug_s,         0, f_console_flag_inverse_e, 0), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_version_s,       f_console_standard_long_version_s,       0, f_console_flag_inverse_e, 0), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_line_first_no_s, f_console_standard_long_line_first_no_s, 0, f_console_flag_inverse_e, 0), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_line_last_no_s,  f_console_standard_long_line_last_no_s,  0, f_console_flag_inverse_e, 0), \
      \
      macro_f_console_parameter_t_initialize2(control_short_name_s.string, control_long_name_s.string, 0, 1, f_console_flag_normal_e, 0), \
      macro_f_console_parameter_t_initialize2(control_short_return_s.string, control_long_return_s.string, 0, 1, f_console_flag_normal_e, 0), \
      macro_f_console_parameter_t_initialize2(control_short_settings_s.string, control_long_settings_s.string, 0, 1, f_console_flag_normal_e, 0), \
      macro_f_console_parameter_t_initialize2(control_short_socket_s.string, control_long_socket_s.string, 0, 1, f_console_flag_normal_e, 0), \
    }

  #define control_total_parameters_d 16
#endif // _di_control_parameter_d_

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
 * Flags passed to the main function or program.
 *
 * control_main_flag_*_e:
 *   - none:          No flags set.
 *   - file_from:     Using a specified source file.
 *   - file_to:       Using a specified destination file.
 *   - help:          Print help.
 *   - header:        Enable printing of headers.
 *   - separate:      Enable printing of separators.
 *   - strip_invalid: Using strip invalid character mode.
 *   - verify:        Using verify mode.
 *   - version:       Print version.
 */
#ifndef _di_control_main_flag_e_
  enum {
    control_main_flag_none_e          = 0x0,
    control_main_flag_file_from_e     = 0x1,
    control_main_flag_file_to_e       = 0x2,
    control_main_flag_header_e        = 0x4,
    control_main_flag_help_e          = 0x8,
    control_main_flag_separate_e      = 0x10,
    control_main_flag_strip_invalid_e = 0x20,
    control_main_flag_verify_e        = 0x40,
    control_main_flag_version_e       = 0x80,
  }; // enum
#endif // _di_control_main_flag_e_

/**
 * The control main program settings.
 *
 * This is passed to the program-specific main entry point to designate program settings.
 * These program settings are often processed from the program arguments (often called the command line arguments).
 *
 * flag: Flags passed to the main function.
 *
 * status: The main status code, generally used by the load settings and main functions.
 *
 * line_first: A string expected to represent either "\n" or NULL to allow for easy handling of when to print first new line or not.
 * line_last:  A string expected to represent either "\n" or NULL to allow for easy handling of when to print last new line or not.
 */
#ifndef _di_control_setting_t_
  typedef struct {
    uint16_t flag;

    f_status_t status;

    f_string_static_t line_first;
    f_string_static_t line_last;
  } control_setting_t;

  #define control_setting_t_initialize \
    { \
      control_main_flag_none_e, \
      F_none, \
      f_string_static_t_initialize, \
      f_string_static_t_initialize, \
    }
#endif // _di_control_setting_t_

/**
 * Identify the action code the given name represents.
 *
 * @param action
 *   The string representing an action.
 *
 * @return
 *   The action type code on success.
 *   0 if name is unknown.
 */
#ifndef _di_control_action_type_identify_
  extern uint8_t control_action_type_identify(const f_string_static_t action);
#endif // _di_control_action_type_identify_

/**
 * Get a string representing the action type.
 *
 * @param type
 *   The action type id.
 *
 * @return
 *   The string with used > 0 on success.
 *   The string with used == 0 if no match was found.
 */
#ifndef _di_control_action_type_name_
  extern f_string_static_t control_action_type_name(const uint8_t type);
#endif // _di_control_action_type_name_

/**
 * Identify the payload code the given name represents.
 *
 * @param payload
 *   The string representing a payload.
 *
 * @return
 *   The payload type code on success.
 *   0 if name is unknown.
 */
#ifndef _di_control_payload_type_identify_
  extern uint8_t control_payload_type_identify(const f_string_static_t payload);
#endif // _di_control_payload_type_identify_

/**
 * Get a string representing the payload type.
 *
 * @param type
 *   The payload type id.
 *
 * @return
 *   The string with used > 0 on success.
 *   The string with used == 0 if no match was found.
 */
#ifndef _di_control_payload_type_name_
  extern f_string_static_t control_payload_type_name(const uint8_t type);
#endif // _di_control_payload_type_name_

/**
 * Delete the program main setting data.
 *
 * @param setting
 *   The program main setting data.
 *
 *   This does not alter setting.status.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_control_setting_delete_
  extern f_status_t control_setting_delete(control_setting_t * const setting);
#endif // _di_control_setting_delete_

/**
 * Perform the standard program setting load process.
 *
 * This prints error messages as appropriate.
 *
 * If either main or setting is NULL, then this immediately returns without doing anything.
 *
 * @param arguments
 *   The parameters passed to the process (often referred to as command line arguments).
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This alters setting.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: f_console_parameter_process().
 *     Errors (with error bit) from: fll_program_parameter_process_context().
 *
 * @see f_console_parameter_process()
 * @see fll_program_parameter_process_context()
 */
#ifndef _di_control_setting_load_
  extern void control_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, control_setting_t * const setting);
#endif // _di_control_setting_load_

/**
 * Perform the standard program setting unload process.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *   All buffers are deallocated.
 *
 *   This does not alter setting.status.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: utf8_setting_delete().
 *
 * @see utf8_setting_delete()
 */
#ifndef _di_control_setting_unload_
  extern f_status_t control_setting_unload(fll_program_data_t * const main, control_setting_t * const setting);
#endif // _di_control_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _control_common_h
