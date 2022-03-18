/**
 * FLL - Level 3
 *
 * Project: Control
 * API Version: 0.5
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
#ifndef _di_control_program_version_
  #define CONTROL_program_version_major_s F_string_ascii_0_s
  #define CONTROL_program_version_minor_s F_string_ascii_5_s
  #define CONTROL_program_version_micro_s F_string_ascii_9_s

  #define CONTROL_program_version_major_s_length F_string_ascii_0_s_length
  #define CONTROL_program_version_minor_s_length F_string_ascii_5_s_length
  #define CONTROL_program_version_micro_s_length F_string_ascii_9_s_length

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
#endif // _di_control_program_version_

/**
 * The program name.
 */
#ifndef _di_control_program_name_
  #define CONTROL_program_name_s      "control"
  #define CONTROL_program_name_long_s "Control Program"

  #define CONTROL_program_name_s_length      7
  #define CONTROL_program_name_long_s_length 15

  extern const f_string_static_t control_program_name_s;
  extern const f_string_static_t control_program_name_long_s;
#endif // _di_control_program_name_

/**
 * The main program parameters.
 */
#ifndef _di_control_parameters_
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
    control_parameter_verbosity_normal_e,
    control_parameter_verbosity_verbose_e,
    control_parameter_verbosity_debug_e,
    control_parameter_version_e,

    control_parameter_name_e,
    control_parameter_return_e,
    control_parameter_settings_e,
    control_parameter_socket_e,
  };

  #define control_console_parameter_t_initialize \
    { \
      macro_f_console_parameter_t_initialize(f_console_standard_short_help_s.string, f_console_standard_long_help_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_light_s.string, f_console_standard_long_light_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_dark_s.string, f_console_standard_long_dark_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_no_color_s.string, f_console_standard_long_no_color_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_quiet_s.string, f_console_standard_long_quiet_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_normal_s.string, f_console_standard_long_normal_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_verbose_s.string, f_console_standard_long_verbose_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_debug_s.string, f_console_standard_long_debug_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_version_s.string, f_console_standard_long_version_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(control_short_name_s.string, control_long_name_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(control_short_return_s.string, control_long_return_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(control_short_settings_s.string, control_long_settings_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(control_short_socket_s.string, control_long_socket_s.string, 0, 1, f_console_type_normal_e), \
    }

  #define control_total_parameters_d 13
#endif // _di_control_parameters_

/**
 * Get the name of the action type.
 *
 * @param type
 *   The action type id.
 *
 * @return
 *   The string associated with the action type.
 */
#ifndef _di_control_action_type_name_
  extern f_string_static_t control_action_type_name(const uint8_t type);
#endif // _di_control_action_type_name_

/**
 * Get the name of the payload type.
 *
 * @param type
 *   The payload type id.
 *
 * @return
 *   The string associated with the payload type.
 */
#ifndef _di_control_payload_type_name_
  extern f_string_static_t control_payload_type_name(const uint8_t type);
#endif // _di_control_payload_type_name_

/**
 * Deallocate main.
 *
 * Be sure to call this after executing control_main().
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see control_main()
 */
#ifndef _di_control_main_delete_
  extern f_status_t control_main_delete(fll_program_data_t * const main);
#endif // _di_control_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _control_common_h
