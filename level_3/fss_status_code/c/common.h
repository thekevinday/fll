/**
 * FLL - Level 3
 *
 * Project: FSS Status code
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_status_code_common_h
#define _fss_status_code_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program version.
 */
#ifndef _di_fss_status_code_program_version_
  #define FSS_STATUS_code_program_version_major_s F_string_ascii_0_s
  #define FSS_STATUS_code_program_version_minor_s F_string_ascii_5_s
  #define FSS_STATUS_code_program_version_micro_s F_string_ascii_8_s

  #define FSS_STATUS_code_program_version_major_s_length F_string_ascii_0_s_length
  #define FSS_STATUS_code_program_version_minor_s_length F_string_ascii_5_s_length
  #define FSS_STATUS_code_program_version_micro_s_length F_string_ascii_8_s_length

  #if !(defined(FSS_STATUS_program_version_nano_prefix_s) && defined(FSS_STATUS_program_version_nano_prefix_s_length))
    #define FSS_STATUS_program_version_nano_prefix_s
    #define FSS_STATUS_program_version_nano_prefix_s_length 0
  #endif // !(defined(FSS_STATUS_program_version_nano_prefix_s) && defined(FSS_STATUS_program_version_nano_prefix_s_length))

  #if !(defined(FSS_STATUS_program_version_nano_s) && defined(FSS_STATUS_program_version_nano_s_length))
    #define FSS_STATUS_program_version_nano_s
    #define FSS_STATUS_program_version_nano_s_length 0
  #endif // !(defined(FSS_STATUS_program_version_nano_s) && defined(FSS_STATUS_program_version_nano_s_length))

  #define FSS_STATUS_code_program_version_length_s FSS_STATUS_code_program_version_major_s F_string_ascii_period_s FSS_STATUS_code_program_version_minor_s F_string_ascii_period_s FSS_STATUS_code_program_version_micro_s FSS_STATUS_code_program_version_nano_prefix_s FSS_STATUS_code_program_version_nano_s

  extern const f_string_static_t fss_status_code_program_version_s;
#endif // _di_fss_status_code_program_version_

/**
 * The program name.
 */
#ifndef _di_fss_status_code_program_name_
  #define FSS_STATUS_code_program_name_s      "FSS_STATUS_code"
  #define FSS_STATUS_code_program_name_long_s "FSS Status Code"

  #define FSS_STATUS_CODE_program_name_s_length
  #define FSS_STATUS_CODE_program_name_long_s_length

  const f_string_static_t fss_status_code_program_name_s;
  const f_string_static_t fss_status_code_program_name_long_s;
#endif // _di_fss_status_code_program_name_

/**
 * The program help related data.
 */
#ifndef _di_fss_status_code_program_help_parameters_
  #define FSS_STATUS_CODE_program_help_parameters_s "status code(s)"
  #define FSS_STATUS_CODE_program_help_parameters_s_length 14

  extern const f_string_static_t fss_status_code_program_help_parameters_s;
#endif // _di_fss_status_code_program_help_parameters_

/**
 * The program defines.
 */
#ifndef _di_fss_status_code_defines_
  #define fss_status_code_signal_check_d 10000
#endif // _di_fss_status_code_defines_

/**
 * The main program parameters.
 */
#ifndef _di_fss_status_code_parameters_
  #define FSS_STATUS_CODE_short_is_fine_s    "f"
  #define FSS_STATUS_CODE_short_is_warning_s "w"
  #define FSS_STATUS_CODE_short_is_error_s   "e"
  #define FSS_STATUS_CODE_short_number_s     "n"

  #define FSS_STATUS_CODE_long_is_fine_s    "is_fine"
  #define FSS_STATUS_CODE_long_is_warning_s "is_warning"
  #define FSS_STATUS_CODE_long_is_error_s   "is_error"
  #define FSS_STATUS_CODE_long_number_s     "number"

  #define FSS_STATUS_CODE_short_is_fine_s_length    1
  #define FSS_STATUS_CODE_short_is_warning_s_length 1
  #define FSS_STATUS_CODE_short_is_error_s_length   1
  #define FSS_STATUS_CODE_short_number_s_length     1

  #define FSS_STATUS_CODE_long_is_fine_s_length    7
  #define FSS_STATUS_CODE_long_is_warning_s_length 10
  #define FSS_STATUS_CODE_long_is_error_s_length   8
  #define FSS_STATUS_CODE_long_number_s_length     6

  extern const f_string_static_t fss_status_code_short_is_fine_s;
  extern const f_string_static_t fss_status_code_short_is_warning_s;
  extern const f_string_static_t fss_status_code_short_is_error_s;
  extern const f_string_static_t fss_status_code_short_number_s;

  extern const f_string_static_t fss_status_code_long_is_fine_s;
  extern const f_string_static_t fss_status_code_long_is_warning_s;
  extern const f_string_static_t fss_status_code_long_is_error_s;
  extern const f_string_static_t fss_status_code_long_number_s;

  enum {
    fss_status_code_parameter_help_e,
    fss_status_code_parameter_light_e,
    fss_status_code_parameter_dark_e,
    fss_status_code_parameter_no_color_e,
    fss_status_code_parameter_verbosity_quiet_e,
    fss_status_code_parameter_verbosity_normal_e,
    fss_status_code_parameter_verbosity_verbose_e,
    fss_status_code_parameter_verbosity_debug_e,
    fss_status_code_parameter_version_e,

    fss_status_code_parameter_is_fine_e,
    fss_status_code_parameter_is_warning_e,
    fss_status_code_parameter_is_error_e,
    fss_status_code_parameter_number_e,
  };

  #define fss_status_code_console_parameter_t_initialize \
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
      macro_f_console_parameter_t_initialize(fss_status_code_short_is_fine_s.string, fss_status_code_long_is_fine_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_status_code_short_is_warning_s.string, fss_status_code_long_is_warning_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_status_code_short_is_error_s.string, fss_status_code_long_is_error_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_status_code_short_number_s.string, fss_status_code_long_number_s.string, 0, 0, f_console_type_normal_e), \
    }

  #define fss_status_code_total_parameters_d 13
#endif // _di_fss_status_code_defines_

/**
 * Deallocate main.
 *
 * Be sure to call this after executing fss_status_code_main().
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fss_status_code_main()
 */
#ifndef _di_fss_status_code_main_delete_
  extern f_status_t fss_status_code_main_delete(fll_program_data_t * const main);
#endif // _di_fss_status_code_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_status_code_common_h
