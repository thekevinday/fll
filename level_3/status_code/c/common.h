/**
 * FLL - Level 3
 *
 * Project: Status Code
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _status_code_common_h
#define _status_code_common_h

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_status_code_program_version_
  #define STATUS_CODE_program_version_major_s F_string_ascii_0_s
  #define STATUS_CODE_program_version_minor_s F_string_ascii_5_s
  #define STATUS_CODE_program_version_micro_s F_string_ascii_8_s

  #define STATUS_CODE_program_version_major_s_length F_string_ascii_0_s_length
  #define STATUS_CODE_program_version_minor_s_length F_string_ascii_5_s_length
  #define STATUS_CODE_program_version_micro_s_length F_string_ascii_8_s_length

  #if !(defined(STATUS_CODE_program_version_nano_prefix_s) && defined(STATUS_CODE_program_version_nano_prefix_s_length))
    #define STATUS_CODE_program_version_nano_prefix_s
    #define STATUS_CODE_program_version_nano_prefix_s_length 0
  #endif // !(defined(STATUS_CODE_program_version_nano_prefix_s) && defined(STATUS_CODE_program_version_nano_prefix_s_length))

  #if !(defined(STATUS_CODE_program_version_nano_s) && defined(STATUS_CODE_program_version_nano_s_length))
    #define STATUS_CODE_program_version_nano_s
    #define STATUS_CODE_program_version_nano_s_length 0
  #endif // !(defined(STATUS_CODE_program_version_nano_s) && defined(STATUS_CODE_program_version_nano_s_length))

  #define STATUS_CODE_progam_version_s STATUS_CODE_program_version_major_s F_string_ascii_period_s STATUS_CODE_program_version_minor_s F_string_ascii_period_s STATUS_CODE_program_version_micro_s STATUS_CODE_progam_version_nano_prefix_s STATUS_CODE_progam_version_nano_s

  #define STATUS_CODE_progam_version_s_length STATUS_CODE_program_version_major_s_length + F_string_ascii_period_s_length + STATUS_CODE_program_version_minor_s_length + F_string_ascii_period_s_length + STATUS_CODE_program_version_micro_s_length + STATUS_CODE_progam_version_nano_prefix_s_length + STATUS_CODE_progam_version_nano_s_length

  extern const f_string_static_t status_code_program_version_s;
#endif // _di_status_code_program_version_

#ifndef _di_status_code_program_name_
  #define STATUS_CODE_progam_name_s      "status_code"
  #define STATUS_CODE_progam_name_long_s "FSS Status Code"

  #define STATUS_CODE_program_name_s_length      11
  #define STATUS_CODE_program_name_long_s_length 15

  extern const f_string_static_t status_code_program_name_s;
  extern const f_string_static_t status_code_program_name_long_s;
#endif // _di_status_code_program_name_

#ifndef _di_status_code_defines_
  #define status_code_signal_check_d 10000

  #define status_code_short_is_fine_s    "f"
  #define status_code_short_is_warning_s "w"
  #define status_code_short_is_error_s   "e"
  #define status_code_short_number_s     "n"

  #define status_code_long_is_fine_s    "is_fine"
  #define status_code_long_is_warning_s "is_warning"
  #define status_code_long_is_error_s   "is_error"
  #define status_code_long_number_s     "number"

  enum {
    status_code_parameter_help_e,
    status_code_parameter_light_e,
    status_code_parameter_dark_e,
    status_code_parameter_no_color_e,
    status_code_parameter_verbosity_quiet_e,
    status_code_parameter_verbosity_normal_e,
    status_code_parameter_verbosity_verbose_e,
    status_code_parameter_verbosity_debug_e,
    status_code_parameter_version_e,

    status_code_parameter_is_fine_e,
    status_code_parameter_is_warning_e,
    status_code_parameter_is_error_e,
    status_code_parameter_number_e,
  };

  #define status_code_console_parameter_t_initialize \
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
      macro_f_console_parameter_t_initialize(status_code_short_is_fine_s, status_code_long_is_fine_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(status_code_short_is_warning_s, status_code_long_is_warning_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(status_code_short_is_error_s, status_code_long_is_error_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(status_code_short_number_s, status_code_long_number_s, 0, 0, f_console_type_normal_e), \
    }

  #define status_code_total_parameters_d 13
#endif // _di_status_code_defines_

#ifndef _di_status_code_main_t_
  typedef struct {
    f_console_parameters_t parameters;

    f_array_lengths_t remaining;
    bool process_pipe;

    fl_print_t output;
    fl_print_t error;
    fl_print_t warning;

    f_signal_t signal;

    f_color_context_t context;
  } status_code_main_t;

  #define status_code_main_t_initialize \
    { \
      f_console_parameters_t_initialize, \
      f_array_lengths_t_initialize, \
      F_false, \
      fl_print_t_initialize, \
      macro_fl_print_t_initialize_error(), \
      macro_fl_print_t_initialize_warning(), \
      f_signal_t_initialize, \
      f_color_context_t_initialize, \
    }
#endif // _di_status_code_main_t_

/**
 * Deallocate main.
 *
 * Be sure to call this after executing status_code_main().
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see status_code_main()
 */
#ifndef _di_status_code_main_delete_
  extern f_status_t status_code_main_delete(status_code_main_t * const main);
#endif // _di_status_code_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _status_code_common_h
