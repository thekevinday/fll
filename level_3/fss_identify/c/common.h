/**
 * FLL - Level 3
 *
 * Project: FSS Identify
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_identify_common_h
#define _fss_identify_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program version.
 */
#ifndef _di_fss_identify_program_version_
  #define FSS_IDENTIFY_program_version_major_s F_string_ascii_0_s
  #define FSS_IDENTIFY_program_version_minor_s F_string_ascii_5_s
  #define FSS_IDENTIFY_program_version_micro_s F_string_ascii_9_s

  #define FSS_IDENTIFY_program_version_major_s_length F_string_ascii_0_s_length
  #define FSS_IDENTIFY_program_version_minor_s_length F_string_ascii_5_s_length
  #define FSS_IDENTIFY_program_version_micro_s_length F_string_ascii_9_s_length

  #if !(defined(FSS_IDENTIFY_program_version_nano_prefix_s) && defined(FSS_IDENTIFY_program_version_nano_prefix_s_length))
    #define FSS_IDENTIFY_program_version_nano_prefix_s
    #define FSS_IDENTIFY_program_version_nano_prefix_s_length 0
  #endif // !(defined(FSS_IDENTIFY_program_version_nano_prefix_s) && defined(FSS_IDENTIFY_program_version_nano_prefix_s_length))

  #if !(defined(FSS_IDENTIFY_program_version_nano_s) && defined(FSS_IDENTIFY_program_version_nano_s_length))
    #define FSS_IDENTIFY_program_version_nano_s
    #define FSS_IDENTIFY_program_version_nano_s_length 0
  #endif // !(defined(FSS_IDENTIFY_program_version_nano_s) && defined(FSS_IDENTIFY_program_version_nano_s_length))

  #define FSS_IDENTIFY_program_version_s FSS_IDENTIFY_program_version_major_s F_string_ascii_period_s FSS_IDENTIFY_program_version_minor_s F_string_ascii_period_s FSS_IDENTIFY_program_version_micro_s FSS_IDENTIFY_program_version_nano_prefix_s FSS_IDENTIFY_program_version_nano_s

  #define FSS_IDENTIFY_program_version_s_length FSS_IDENTIFY_program_version_major_s_length + F_string_ascii_period_s_length + FSS_IDENTIFY_program_version_minor_s_length + F_string_ascii_period_s_length + FSS_IDENTIFY_program_version_micro_s_length + FSS_IDENTIFY_program_version_nano_prefix_s_length + FSS_IDENTIFY_program_version_nano_s_length

  extern const f_string_static_t fss_identify_program_version_s;
#endif // _di_fss_identify_program_version_

/**
 * The program name.
 */
#ifndef _di_fss_identify_program_name_
  #define FSS_IDENTIFY_program_name_s      "fss_identify"
  #define FSS_IDENTIFY_program_name_long_s "FSS Identify"

  #define FSS_IDENTIFY_program_name_s_length      12
  #define FSS_IDENTIFY_program_name_long_s_length 12

  extern const f_string_static_t fss_identify_program_name_s;
  extern const f_string_static_t fss_identify_program_name_long_s;
#endif // _di_fss_identify_program_name_

/**
 * The program defines.
 */
#ifndef _di_fss_identify_defines_
  #define fss_identify_signal_check_d 10000
#endif // _di_fss_identify_defines_

/**
 * The main program parameters.
 */
#ifndef _di_fss_identify_parameters_
  #define FSS_IDENTIFY_short_content_s "c"
  #define FSS_IDENTIFY_short_line_s    "l"
  #define FSS_IDENTIFY_short_name_s    "n"
  #define FSS_IDENTIFY_short_object_s  "o"
  #define FSS_IDENTIFY_short_total_s   "t"

  #define FSS_IDENTIFY_long_content_s "content"
  #define FSS_IDENTIFY_long_line_s    "line"
  #define FSS_IDENTIFY_long_name_s    "name"
  #define FSS_IDENTIFY_long_object_s  "object"
  #define FSS_IDENTIFY_long_total_s   "total"

  #define FSS_IDENTIFY_short_content_s_length 1
  #define FSS_IDENTIFY_short_line_s_length    1
  #define FSS_IDENTIFY_short_name_s_length    1
  #define FSS_IDENTIFY_short_object_s_length  1
  #define FSS_IDENTIFY_short_total_s_length   1

  #define FSS_IDENTIFY_long_content_s_length 7
  #define FSS_IDENTIFY_long_line_s_length    4
  #define FSS_IDENTIFY_long_name_s_length    4
  #define FSS_IDENTIFY_long_object_s_length  6
  #define FSS_IDENTIFY_long_total_s_length   5

  extern const f_string_static_t fss_identify_short_content_s;
  extern const f_string_static_t fss_identify_short_line_s;
  extern const f_string_static_t fss_identify_short_name_s;
  extern const f_string_static_t fss_identify_short_object_s;
  extern const f_string_static_t fss_identify_short_total_s;

  extern const f_string_static_t fss_identify_long_content_s;
  extern const f_string_static_t fss_identify_long_line_s;
  extern const f_string_static_t fss_identify_long_name_s;
  extern const f_string_static_t fss_identify_long_object_s;
  extern const f_string_static_t fss_identify_long_total_s;

  enum {
    fss_identify_parameter_help_e,
    fss_identify_parameter_light_e,
    fss_identify_parameter_dark_e,
    fss_identify_parameter_no_color_e,
    fss_identify_parameter_verbosity_quiet_e,
    fss_identify_parameter_verbosity_normal_e,
    fss_identify_parameter_verbosity_verbose_e,
    fss_identify_parameter_verbosity_debug_e,
    fss_identify_parameter_version_e,

    fss_identify_parameter_content_e,
    fss_identify_parameter_line_e,
    fss_identify_parameter_name_e,
    fss_identify_parameter_object_e,
    fss_identify_parameter_total_e,
  };

  #define fss_identify_console_parameter_t_initialize \
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
      macro_f_console_parameter_t_initialize(fss_identify_short_content_s.string, fss_identify_long_content_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_identify_short_line_s.string, fss_identify_long_line_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_identify_short_name_s.string, fss_identify_long_name_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_identify_short_object_s.string, fss_identify_long_object_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_identify_short_total_s.string, fss_identify_long_total_s.string, 0, 0, f_console_type_normal_e), \
    }

  #define fss_identify_total_parameters_d 14
#endif // _di_fss_identify_parameters_

/**
 * Deallocate main.
 *
 * Be sure to call this after executing fss_identify_main().
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fss_identify_main()
 */
#ifndef _di_fss_identify_main_delete_
  extern f_status_t fss_identify_main_delete(fll_program_data_t * const main);
#endif // _di_fss_identify_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_identify_common_h
