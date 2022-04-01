/**
 * FLL - Level 3
 *
 * Project: IKI Write
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _iki_write_common_h
#define _iki_write_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program version.
 */
#ifndef _di_iki_write_program_version_
  #define IKI_WRITE_program_version_major_s F_string_ascii_0_s
  #define IKI_WRITE_program_version_minor_s F_string_ascii_5_s
  #define IKI_WRITE_program_version_micro_s F_string_ascii_9_s

  #define IKI_WRITE_program_version_major_s_length F_string_ascii_0_s_length
  #define IKI_WRITE_program_version_minor_s_length F_string_ascii_5_s_length
  #define IKI_WRITE_program_version_micro_s_length F_string_ascii_9_s_length

  #if !(defined(IKI_WRITE_program_version_nano_prefix_s) && defined(IKI_WRITE_program_version_nano_prefix_s_length))
    #define IKI_WRITE_program_version_nano_prefix_s
    #define IKI_WRITE_program_version_nano_prefix_s_length 0
  #endif // !(defined(IKI_WRITE_program_version_nano_prefix_s) && defined(IKI_WRITE_program_version_nano_prefix_s_length))

  #if !(defined(IKI_WRITE_program_version_nano_s) && defined(IKI_WRITE_program_version_nano_s_length))
    #define IKI_WRITE_program_version_nano_s
    #define IKI_WRITE_program_version_nano_s_length 0
  #endif // !(defined(IKI_WRITE_program_version_nano_s) && defined(IKI_WRITE_program_version_nano_s_length))

  #define IKI_WRITE_program_version_s IKI_WRITE_program_version_major_s F_string_ascii_period_s IKI_WRITE_program_version_minor_s F_string_ascii_period_s IKI_WRITE_program_version_micro_s IKI_WRITE_program_version_nano_prefix_s IKI_WRITE_program_version_nano_s

  #define IKI_WRITE_program_version_s_length IKI_WRITE_program_version_major_s_length + F_string_ascii_period_s_length + IKI_WRITE_program_version_minor_s_length + F_string_ascii_period_s_length + IKI_WRITE_program_version_micro_s_length + IKI_WRITE_program_version_nano_prefix_s_length + IKI_WRITE_program_version_nano_s_length

  extern const f_string_static_t iki_write_program_version_s;
#endif // _di_iki_write_program_version_

/**
 * The program name.
 */
#ifndef _di_iki_write_program_name_
  #define IKI_WRITE_program_name_s      "iki_write"
  #define IKI_WRITE_program_name_long_s "IKI Write"

  #define IKI_WRITE_program_name_s_length      9
  #define IKI_WRITE_program_name_long_s_length 9

  extern const f_string_static_t iki_write_program_name_s;
  extern const f_string_static_t iki_write_program_name_long_s;
#endif // _di_iki_write_program_name_

/**
 * The program defines.
 */
#ifndef _di_iki_write_defines_
  #define iki_write_signal_check_d 20000
#endif // _di_iki_write_defines_

/**
 * The main program parameters.
 */
#ifndef _di_iki_write_parameters_
  #define IKI_WRITE_short_file_s    "f"
  #define IKI_WRITE_short_content_s "c"
  #define IKI_WRITE_short_double_s  "d"
  #define IKI_WRITE_short_object_s  "o"
  #define IKI_WRITE_short_single_s  "s"

  #define IKI_WRITE_long_file_s    "file"
  #define IKI_WRITE_long_content_s "content"
  #define IKI_WRITE_long_double_s  "double"
  #define IKI_WRITE_long_object_s  "object"
  #define IKI_WRITE_long_single_s  "single"

  #define IKI_WRITE_short_file_s_length    1
  #define IKI_WRITE_short_content_s_length 1
  #define IKI_WRITE_short_double_s_length  1
  #define IKI_WRITE_short_object_s_length  1
  #define IKI_WRITE_short_single_s_length  1

  #define IKI_WRITE_long_file_s_length    4
  #define IKI_WRITE_long_content_s_length 7
  #define IKI_WRITE_long_double_s_length  6
  #define IKI_WRITE_long_object_s_length  6
  #define IKI_WRITE_long_single_s_length  6

  extern const f_string_static_t iki_write_short_file_s;
  extern const f_string_static_t iki_write_short_content_s;
  extern const f_string_static_t iki_write_short_double_s;
  extern const f_string_static_t iki_write_short_object_s;
  extern const f_string_static_t iki_write_short_single_s;

  extern const f_string_static_t iki_write_long_file_s;
  extern const f_string_static_t iki_write_long_content_s;
  extern const f_string_static_t iki_write_long_double_s;
  extern const f_string_static_t iki_write_long_object_s;
  extern const f_string_static_t iki_write_long_single_s;

  enum {
    iki_write_parameter_help_e,
    iki_write_parameter_light_e,
    iki_write_parameter_dark_e,
    iki_write_parameter_no_color_e,
    iki_write_parameter_verbosity_quiet_e,
    iki_write_parameter_verbosity_normal_e,
    iki_write_parameter_verbosity_verbose_e,
    iki_write_parameter_verbosity_debug_e,
    iki_write_parameter_version_e,

    iki_write_parameter_file_e,
    iki_write_parameter_content_e,
    iki_write_parameter_double_e,
    iki_write_parameter_object_e,
    iki_write_parameter_single_e,
  };

  #define iki_write_console_parameter_t_initialize \
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
      macro_f_console_parameter_t_initialize(iki_write_short_file_s.string, iki_write_long_file_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(iki_write_short_content_s.string, iki_write_long_content_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(iki_write_short_double_s.string, iki_write_long_double_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(iki_write_short_object_s.string, iki_write_long_object_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(iki_write_short_single_s.string, iki_write_long_single_s.string, 0, 0, f_console_type_normal_e), \
    }

  #define iki_write_total_parameters_d 14
#endif // _di_iki_write_parameters_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_write_common_h
