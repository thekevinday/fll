/**
 * FLL - Level 3
 *
 * Project: IKI Write
 * API Version: 0.7
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
#ifndef _di_iki_write_program_version_s_
  #define IKI_WRITE_program_version_major_s F_string_ascii_0_s
  #define IKI_WRITE_program_version_minor_s F_string_ascii_7_s
  #define IKI_WRITE_program_version_micro_s F_string_ascii_0_s

  #define IKI_WRITE_program_version_major_s_length F_string_ascii_0_s_length
  #define IKI_WRITE_program_version_minor_s_length F_string_ascii_7_s_length
  #define IKI_WRITE_program_version_micro_s_length F_string_ascii_0_s_length

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
#endif // _di_iki_write_program_version_s_

/**
 * The program name.
 */
#ifndef _di_iki_write_program_name_s_
  #define IKI_WRITE_program_name_s      "iki_write"
  #define IKI_WRITE_program_name_long_s "IKI Write"

  #define IKI_WRITE_program_name_s_length      9
  #define IKI_WRITE_program_name_long_s_length 9

  extern const f_string_static_t iki_write_program_name_s;
  extern const f_string_static_t iki_write_program_name_long_s;
#endif // _di_iki_write_program_name_s_

/**
 * The program defines.
 */
#ifndef _di_iki_write_d_
  #define iki_write_signal_check_d 20000
#endif // _di_iki_write_d_

/**
 * Special strings used by this program.
 */
#ifndef _di_iki_write_s_
  #define IKI_WRITE_object_s  "object"

  #define IKI_WRITE_object_s_length 6

  extern const f_string_static_t iki_write_object_s;
#endif // _di_iki_write_s_

/**
 * The main program parameters.
 */
#ifndef _di_iki_write_parameter_d_
  #define IKI_WRITE_short_backtick_s "b"
  #define IKI_WRITE_short_content_s  "c"
  #define IKI_WRITE_short_double_s   "d"
  #define IKI_WRITE_short_file_s     "f"
  #define IKI_WRITE_short_object_s   "o"
  #define IKI_WRITE_short_single_s   "s"

  #define IKI_WRITE_long_backtick_s "backtick"
  #define IKI_WRITE_long_content_s  "content"
  #define IKI_WRITE_long_double_s   "double"
  #define IKI_WRITE_long_file_s     "file"
  #define IKI_WRITE_long_object_s   "object"
  #define IKI_WRITE_long_single_s   "single"

  #define IKI_WRITE_short_backtick_s_length 1
  #define IKI_WRITE_short_content_s_length  1
  #define IKI_WRITE_short_double_s_length   1
  #define IKI_WRITE_short_file_s_length     1
  #define IKI_WRITE_short_object_s_length   1
  #define IKI_WRITE_short_single_s_length   1

  #define IKI_WRITE_long_backtick_s_length 8
  #define IKI_WRITE_long_content_s_length  7
  #define IKI_WRITE_long_double_s_length   6
  #define IKI_WRITE_long_file_s_length     4
  #define IKI_WRITE_long_object_s_length   6
  #define IKI_WRITE_long_single_s_length   6

  extern const f_string_static_t iki_write_short_backtick_s;
  extern const f_string_static_t iki_write_short_content_s;
  extern const f_string_static_t iki_write_short_double_s;
  extern const f_string_static_t iki_write_short_file_s;
  extern const f_string_static_t iki_write_short_object_s;
  extern const f_string_static_t iki_write_short_single_s;

  extern const f_string_static_t iki_write_long_backtick_s;
  extern const f_string_static_t iki_write_long_content_s;
  extern const f_string_static_t iki_write_long_double_s;
  extern const f_string_static_t iki_write_long_file_s;
  extern const f_string_static_t iki_write_long_object_s;
  extern const f_string_static_t iki_write_long_single_s;

  enum {
    iki_write_parameter_help_e,
    iki_write_parameter_light_e,
    iki_write_parameter_dark_e,
    iki_write_parameter_no_color_e,
    iki_write_parameter_verbosity_quiet_e,
    iki_write_parameter_verbosity_error_e,
    iki_write_parameter_verbosity_normal_e,
    iki_write_parameter_verbosity_verbose_e,
    iki_write_parameter_verbosity_debug_e,
    iki_write_parameter_version_e,
    iki_write_parameter_line_first_no_e,
    iki_write_parameter_line_last_no_e,

    iki_write_parameter_backtick_e,
    iki_write_parameter_content_e,
    iki_write_parameter_double_e,
    iki_write_parameter_file_e,
    iki_write_parameter_object_e,
    iki_write_parameter_single_e,
  }; // enum

  #define iki_write_console_parameter_t_initialize \
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
      macro_f_console_parameter_t_initialize2(iki_write_short_backtick_s.string, iki_write_long_backtick_s.string, 0, 0, f_console_flag_normal_e, 0), \
      macro_f_console_parameter_t_initialize2(iki_write_short_content_s.string,  iki_write_long_content_s.string,  0, 1, f_console_flag_normal_e, 0), \
      macro_f_console_parameter_t_initialize2(iki_write_short_double_s.string,   iki_write_long_double_s.string,   0, 0, f_console_flag_normal_e, 0), \
      macro_f_console_parameter_t_initialize2(iki_write_short_file_s.string,     iki_write_long_file_s.string,     0, 1, f_console_flag_normal_e, 0), \
      macro_f_console_parameter_t_initialize2(iki_write_short_object_s.string,   iki_write_long_object_s.string,   0, 1, f_console_flag_normal_e, 0), \
      macro_f_console_parameter_t_initialize2(iki_write_short_single_s.string,   iki_write_long_single_s.string,   0, 0, f_console_flag_normal_e, 0), \
    }

  #define iki_write_total_parameters_d 18
#endif // _di_iki_write_parameter_d_

/**
 * Flags passed to the main function or program.
 *
 * iki_write_main_flag_*_e:
 *   - none:     No flags set.
 *   - content:  The Content being written is specified.
 *   - file_to:  Using a specified destination file.
 *   - help:     Print help.
 *   - object:   The Object being written is specified.
 *   - version:  Print version.
 */
#ifndef _di_iki_write_main_flag_e_
  enum {
    iki_write_main_flag_none_e    = 0x0,
    iki_write_main_flag_content_e = 0x1,
    iki_write_main_flag_file_to_e = 0x2,
    iki_write_main_flag_help_e    = 0x4,
    iki_write_main_flag_object_e  = 0x8,
    iki_write_main_flag_version_e = 0x10,
  };
#endif // _di_iki_write_main_flag_e_

/**
 * The iki write main program settings.
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
 *
 * quote: This holds the quote used during processing.
 *
 * escaped: A buffer used for escaping strings during processing.
 * buffer:  A buffer used during processing the file.
 * object:  A buffer used to hold an Object during processing.
 * content: A buffer used to hold a Content during processing.
 *
 * objects:  An array of objects passed as values to the "--object" parameter.
 * contents: An array of objects passed as values to the "--content" parameter and must match the length of objects.
 */
#ifndef _di_iki_write_setting_t_
  typedef struct {
    uint16_t flag;

    f_status_t status;

    f_string_static_t line_first;
    f_string_static_t line_last;

    f_string_static_t quote;

    f_string_dynamic_t escaped;
    f_string_dynamic_t buffer;
    f_string_dynamic_t object;
    f_string_dynamic_t content;

    f_string_dynamics_t objects;
    f_string_dynamics_t contents;
  } iki_write_setting_t;

  #define iki_write_setting_t_initialize \
    { \
      iki_write_main_flag_none_e, \
      F_none, \
      f_string_static_t_initialize, \
      f_string_static_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_string_dynamics_t_initialize, \
    }
#endif // _di_iki_write_setting_t_

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
#ifndef _di_iki_write_setting_delete_
  extern f_status_t iki_write_setting_delete(iki_write_setting_t * const setting);
#endif // _di_iki_write_setting_delete_

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
 *     Errors (with error bit) from: f_file_stream_open().
 *     Errors (with error bit) from: f_string_dynamics_resize().
 *     Errors (with error bit) from: fll_program_parameter_process_context().
 *     Errors (with error bit) from: fll_program_parameter_process_verbosity().
 *
 * @see f_console_parameter_process()
 * @see f_file_stream_open()
 * @see f_string_dynamics_resize()
 * @see fll_program_parameter_process_context()
 * @see fll_program_parameter_process_verbosity()
 */
#ifndef _di_iki_write_setting_load_
  extern void iki_write_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, iki_write_setting_t * const setting);
#endif // _di_iki_write_setting_load_

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
#ifndef _di_iki_write_setting_unload_
  extern f_status_t iki_write_setting_unload(fll_program_data_t * const main, iki_write_setting_t * const setting);
#endif // _di_iki_write_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_write_common_h