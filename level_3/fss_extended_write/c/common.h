/**
 * FLL - Level 3
 *
 * Project: FSS Extended Write
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_extended_write_common_h
#define _fss_extended_write_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program version.
 */
#ifndef _di_fss_extended_write_program_version_
  #define FSS_EXTENDED_WRITE_program_version_major_s F_string_ascii_0_s
  #define FSS_EXTENDED_WRITE_program_version_minor_s F_string_ascii_6_s
  #define FSS_EXTENDED_WRITE_program_version_micro_s F_string_ascii_8_s

  #define FSS_EXTENDED_WRITE_program_version_major_s_length F_string_ascii_0_s_length
  #define FSS_EXTENDED_WRITE_program_version_minor_s_length F_string_ascii_6_s_length
  #define FSS_EXTENDED_WRITE_program_version_micro_s_length F_string_ascii_7_s_length

  #if !(defined(FSS_EXTENDED_WRITE_program_version_nano_prefix_s) && defined(FSS_EXTENDED_WRITE_program_version_nano_prefix_s_length))
    #define FSS_EXTENDED_WRITE_program_version_nano_prefix_s
    #define FSS_EXTENDED_WRITE_program_version_nano_prefix_s_length 0
  #endif // !(defined(FSS_EXTENDED_WRITE_program_version_nano_prefix_s) && defined(FSS_EXTENDED_WRITE_program_version_nano_prefix_s_length))

  #if !(defined(FSS_EXTENDED_WRITE_program_version_nano_s) && defined(FSS_EXTENDED_WRITE_program_version_nano_s_length))
    #define FSS_EXTENDED_WRITE_program_version_nano_s
    #define FSS_EXTENDED_WRITE_program_version_nano_s_length 0
  #endif // !(defined(FSS_EXTENDED_WRITE_program_version_nano_s) && defined(FSS_EXTENDED_WRITE_program_version_nano_s_length))

  #define FSS_EXTENDED_WRITE_program_version_s FSS_EXTENDED_WRITE_program_version_major_s F_string_ascii_period_s FSS_EXTENDED_WRITE_program_version_minor_s F_string_ascii_period_s FSS_EXTENDED_WRITE_program_version_micro_s FSS_EXTENDED_WRITE_program_version_nano_prefix_s FSS_EXTENDED_WRITE_program_version_nano_s

  #define FSS_EXTENDED_WRITE_program_version_s_length FSS_EXTENDED_WRITE_program_version_major_s_length + F_string_ascii_period_s_length + FSS_EXTENDED_WRITE_program_version_minor_s_length + F_string_ascii_period_s_length + FSS_EXTENDED_WRITE_program_version_micro_s_length + FSS_EXTENDED_WRITE_program_version_nano_prefix_s_length + FSS_EXTENDED_WRITE_program_version_nano_s_length

  extern const f_string_static_t fss_extended_write_program_version_s;
#endif // _di_fss_extended_write_program_version_

/**
 * The program name.
 */
#ifndef _di_fss_extended_write_program_name_
  #define FSS_EXTENDED_WRITE_program_name_s      "fss_extended_write"
  #define FSS_EXTENDED_WRITE_program_name_long_s "FSS Extended Write"

  #define FSS_EXTENDED_WRITE_program_name_s_length      18
  #define FSS_EXTENDED_WRITE_program_name_long_s_length 18

  extern const f_string_static_t fss_extended_write_program_name_s;
  extern const f_string_static_t fss_extended_write_program_name_long_s;
#endif // _di_fss_extended_write_program_name_

/**
 * The main program defines.
 *
 * fss_extended_write_pipe_*:
 *   - name:           A name used to represent the pipe when printing file names.
 *   - content_end:    A code used to represent the end of Content for use in binary formats.
 *   - content_ignore: A code used to represent the ignoring Content for use in binary formats.
 *   - content_start:  A code used to represent the start of Content for use in binary formats.
 */
#ifndef _di_fss_extended_write_defines_
  #define fss_extended_write_signal_check_d 20000

  #define FSS_EXTENDED_WRITE_pipe_name_s "(pipe)"

  #define FSS_EXTENDED_WRITE_pipe_content_end_s    "\f"
  #define FSS_EXTENDED_WRITE_pipe_content_ignore_s "\v"
  #define FSS_EXTENDED_WRITE_pipe_content_start_s  "\b"

  #define FSS_EXTENDED_WRITE_pipe_name_s_length 6

  #define FSS_EXTENDED_WRITE_pipe_content_end_s_length    1
  #define FSS_EXTENDED_WRITE_pipe_content_ignore_s_length 1
  #define FSS_EXTENDED_WRITE_pipe_content_start_s_length  1

  extern const f_string_static_t fss_extended_write_pipe_name_s;

  extern const f_string_static_t fss_extended_write_pipe_content_end_s;
  extern const f_string_static_t fss_extended_write_pipe_content_ignore_s;
  extern const f_string_static_t fss_extended_write_pipe_content_start_s;
#endif // _di_fss_extended_write_defines_

/**
 * The main program parameters.
 */
#ifndef _di_fss_extended_write_parameters_
  #define FSS_EXTENDED_WRITE_short_file_s    "f"
  #define FSS_EXTENDED_WRITE_short_content_s "c"
  #define FSS_EXTENDED_WRITE_short_double_s  "d"
  #define FSS_EXTENDED_WRITE_short_ignore_s  "I"
  #define FSS_EXTENDED_WRITE_short_object_s  "o"
  #define FSS_EXTENDED_WRITE_short_partial_s "p"
  #define FSS_EXTENDED_WRITE_short_prepend_s "P"
  #define FSS_EXTENDED_WRITE_short_single_s  "s"
  #define FSS_EXTENDED_WRITE_short_trim_s    "T"

  #define FSS_EXTENDED_WRITE_long_file_s    "file"
  #define FSS_EXTENDED_WRITE_long_content_s "content"
  #define FSS_EXTENDED_WRITE_long_double_s  "double"
  #define FSS_EXTENDED_WRITE_long_ignore_s  "ignore"
  #define FSS_EXTENDED_WRITE_long_object_s  "object"
  #define FSS_EXTENDED_WRITE_long_partial_s "partial"
  #define FSS_EXTENDED_WRITE_long_prepend_s "prepend"
  #define FSS_EXTENDED_WRITE_long_single_s  "single"
  #define FSS_EXTENDED_WRITE_long_trim_s    "trim"

  #define FSS_EXTENDED_WRITE_short_file_s_length    1
  #define FSS_EXTENDED_WRITE_short_content_s_length 1
  #define FSS_EXTENDED_WRITE_short_double_s_length  1
  #define FSS_EXTENDED_WRITE_short_ignore_s_length  1
  #define FSS_EXTENDED_WRITE_short_object_s_length  1
  #define FSS_EXTENDED_WRITE_short_partial_s_length 1
  #define FSS_EXTENDED_WRITE_short_prepend_s_length 1
  #define FSS_EXTENDED_WRITE_short_single_s_length  1
  #define FSS_EXTENDED_WRITE_short_trim_s_length    1

  #define FSS_EXTENDED_WRITE_long_file_s_length    4
  #define FSS_EXTENDED_WRITE_long_content_s_length 7
  #define FSS_EXTENDED_WRITE_long_double_s_length  6
  #define FSS_EXTENDED_WRITE_long_ignore_s_length  6
  #define FSS_EXTENDED_WRITE_long_object_s_length  6
  #define FSS_EXTENDED_WRITE_long_partial_s_length 7
  #define FSS_EXTENDED_WRITE_long_prepend_s_length 7
  #define FSS_EXTENDED_WRITE_long_single_s_length  6
  #define FSS_EXTENDED_WRITE_long_trim_s_length    4

  extern const f_string_static_t fss_extended_write_short_file_s;
  extern const f_string_static_t fss_extended_write_short_content_s;
  extern const f_string_static_t fss_extended_write_short_double_s;
  extern const f_string_static_t fss_extended_write_short_ignore_s;
  extern const f_string_static_t fss_extended_write_short_object_s;
  extern const f_string_static_t fss_extended_write_short_partial_s;
  extern const f_string_static_t fss_extended_write_short_prepend_s;
  extern const f_string_static_t fss_extended_write_short_single_s;
  extern const f_string_static_t fss_extended_write_short_trim_s;

  extern const f_string_static_t fss_extended_write_long_file_s;
  extern const f_string_static_t fss_extended_write_long_content_s;
  extern const f_string_static_t fss_extended_write_long_double_s;
  extern const f_string_static_t fss_extended_write_long_ignore_s;
  extern const f_string_static_t fss_extended_write_long_object_s;
  extern const f_string_static_t fss_extended_write_long_partial_s;
  extern const f_string_static_t fss_extended_write_long_prepend_s;
  extern const f_string_static_t fss_extended_write_long_single_s;
  extern const f_string_static_t fss_extended_write_long_trim_s;

  enum {
    fss_extended_write_parameter_help_e,
    fss_extended_write_parameter_copyright_e,
    fss_extended_write_parameter_light_e,
    fss_extended_write_parameter_dark_e,
    fss_extended_write_parameter_no_color_e,
    fss_extended_write_parameter_verbosity_quiet_e,
    fss_extended_write_parameter_verbosity_error_e,
    fss_extended_write_parameter_verbosity_normal_e,
    fss_extended_write_parameter_verbosity_verbose_e,
    fss_extended_write_parameter_verbosity_debug_e,
    fss_extended_write_parameter_version_e,

    fss_extended_write_parameter_file_e,
    fss_extended_write_parameter_content_e,
    fss_extended_write_parameter_double_e,
    fss_extended_write_parameter_ignore_e,
    fss_extended_write_parameter_object_e,
    fss_extended_write_parameter_partial_e,
    fss_extended_write_parameter_prepend_e,
    fss_extended_write_parameter_single_e,
    fss_extended_write_parameter_trim_e,
  };

  #define fss_extended_write_console_parameter_t_initialize \
    { \
      macro_f_console_parameter_t_initialize(f_console_standard_short_help_s.string, f_console_standard_long_help_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_copyright_s.string, f_console_standard_long_copyright_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_light_s.string, f_console_standard_long_light_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_dark_s.string, f_console_standard_long_dark_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_no_color_s.string, f_console_standard_long_no_color_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_quiet_s.string, f_console_standard_long_quiet_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_error_s.string, f_console_standard_long_error_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_normal_s.string, f_console_standard_long_normal_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_verbose_s.string, f_console_standard_long_verbose_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_debug_s.string, f_console_standard_long_debug_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_version_s.string, f_console_standard_long_version_s.string, 0, F_false, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(fss_extended_write_short_file_s.string, fss_extended_write_long_file_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_extended_write_short_content_s.string, fss_extended_write_long_content_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_extended_write_short_double_s.string, fss_extended_write_long_double_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_extended_write_short_ignore_s.string, fss_extended_write_long_ignore_s.string, 0, 2, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_extended_write_short_object_s.string, fss_extended_write_long_object_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_extended_write_short_partial_s.string, fss_extended_write_long_partial_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_extended_write_short_prepend_s.string, fss_extended_write_long_prepend_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_extended_write_short_single_s.string, fss_extended_write_long_single_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_extended_write_short_trim_s.string, fss_extended_write_long_trim_s.string, 0, 0, f_console_type_normal_e), \
    }

  #define fss_extended_write_total_parameters_d 19
#endif // _di_fss_extended_write_parameters_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_extended_write_common_h
