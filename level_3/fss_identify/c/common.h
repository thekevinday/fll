/**
 * FLL - Level 3
 *
 * Project: FSS Identify
 * API Version: 0.7
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
#ifndef _di_fss_identify_program_version_s_
  #define FSS_IDENTIFY_program_version_major_s F_string_ascii_0_s
  #define FSS_IDENTIFY_program_version_minor_s F_string_ascii_7_s
  #define FSS_IDENTIFY_program_version_micro_s F_string_ascii_0_s

  #define FSS_IDENTIFY_program_version_major_s_length F_string_ascii_0_s_length
  #define FSS_IDENTIFY_program_version_minor_s_length F_string_ascii_7_s_length
  #define FSS_IDENTIFY_program_version_micro_s_length F_string_ascii_0_s_length

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
#endif // _di_fss_identify_program_version_s_

/**
 * The program name.
 */
#ifndef _di_fss_identify_program_name_s_
  #define FSS_IDENTIFY_program_name_s      "fss_identify"
  #define FSS_IDENTIFY_program_name_long_s "FSS Identify"

  #define FSS_IDENTIFY_program_name_s_length      12
  #define FSS_IDENTIFY_program_name_long_s_length 12

  extern const f_string_static_t fss_identify_program_name_s;
  extern const f_string_static_t fss_identify_program_name_long_s;
#endif // _di_fss_identify_program_name_s_

/**
 * The program defines.
 *
 * fss_identify_*:
 *   - allocation_console: An allocation step used for small buffers specifically for console parameter.
 *   - allocation_large:   An allocation step used for buffers that are anticipated to have large buffers.
 *   - allocation_small:   An allocation step used for buffers that are anticipated to have small buffers.
 *   - signal_check:       Number of iterations before performing signal check in non-threaded signal handling.
 */
#ifndef _di_fss_identify_d_
  #define fss_identify_allocation_console_d 4
  #define fss_identify_allocation_large_d   256
  #define fss_identify_allocation_small_d   16
  #define fss_identify_signal_check_d       20000
#endif // _di_fss_identify_d_

/**
 * The main program parameters.
 */
#ifndef _di_fss_identify_parameter_d_
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
    fss_identify_parameter_copyright_e,
    fss_identify_parameter_light_e,
    fss_identify_parameter_dark_e,
    fss_identify_parameter_no_color_e,
    fss_identify_parameter_verbosity_quiet_e,
    fss_identify_parameter_verbosity_error_e,
    fss_identify_parameter_verbosity_normal_e,
    fss_identify_parameter_verbosity_verbose_e,
    fss_identify_parameter_verbosity_debug_e,
    fss_identify_parameter_version_e,
    fss_identify_parameter_line_first_no_e,
    fss_identify_parameter_line_last_no_e,

    fss_identify_parameter_content_e,
    fss_identify_parameter_line_e,
    fss_identify_parameter_name_e,
    fss_identify_parameter_object_e,
    fss_identify_parameter_total_e,
  }; // enum

  #define fss_identify_console_parameter_t_initialize \
    { \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_help_s,          f_console_standard_long_help_s,          0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_copyright_s,     f_console_standard_long_copyright_s,     0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_light_s,         f_console_standard_long_light_s,         0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_dark_s,          f_console_standard_long_dark_s,          0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_no_color_s,      f_console_standard_long_no_color_s,      0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_quiet_s,         f_console_standard_long_quiet_s,         0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_error_s,         f_console_standard_long_error_s,         0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_normal_s,        f_console_standard_long_normal_s,        0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_verbose_s,       f_console_standard_long_verbose_s,       0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_debug_s,         f_console_standard_long_debug_s,         0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_version_s,       f_console_standard_long_version_s,       0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_line_first_no_s, f_console_standard_long_line_first_no_s, 0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_line_last_no_s,  f_console_standard_long_line_last_no_s,  0, f_console_flag_inverse_e), \
      \
      macro_f_console_parameter_t_initialize_3(fss_identify_short_content_s, fss_identify_long_content_s, 0, 0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_identify_short_line_s, fss_identify_long_line_s, 0, 1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_identify_short_name_s, fss_identify_long_name_s, 0, 1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_identify_short_object_s, fss_identify_long_object_s, 0, 0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_identify_short_total_s, fss_identify_long_total_s, 0, 0, f_console_flag_normal_e), \
    }

  #define fss_identify_total_parameters_d 18
#endif // _di_fss_identify_parameter_d_

/**
 * Flags passed to the main function or program.
 *
 * fss_identify_main_flag_*_e:
 *   - none:          No flags set.
 *   - copyright:     Print copyright.
 *   - file_from:     Using a specified source file.
 *   - file_to:       Using a specified destination file.
 *   - help:          Print help.
 *   - header:        Enable printing of headers.
 *   - separate:      Enable printing of separators.
 *   - strip_invalid: Using strip invalid character mode.
 *   - verify:        Using verify mode.
 *   - version:       Print version.
 */
#ifndef _di_fss_identify_main_flag_e_
  enum {
    fss_identify_main_flag_none_e          = 0x0,
    fss_identify_main_flag_copyright_e     = 0x1,
    fss_identify_main_flag_file_from_e     = 0x2,
    fss_identify_main_flag_file_to_e       = 0x4,
    fss_identify_main_flag_header_e        = 0x8,
    fss_identify_main_flag_help_e          = 0x10,
    fss_identify_main_flag_separate_e      = 0x20,
    fss_identify_main_flag_strip_invalid_e = 0x40,
    fss_identify_main_flag_verify_e        = 0x80,
    fss_identify_main_flag_version_e       = 0x100,
  }; // enum
#endif // _di_fss_identify_main_flag_e_

/**
 * The fss identify main program settings.
 *
 * This is passed to the program-specific main entry point to designate program settings.
 * These program settings are often processed from the program arguments (often called the command line arguments).
 *
 * flag: Flags passed to the main function.
 *
 * state: The state information.
 *
 * line_first: A string expected to represent either "\n" or NULL to allow for easy handling of when to print first new line or not.
 * line_last:  A string expected to represent either "\n" or NULL to allow for easy handling of when to print last new line or not.
 */
#ifndef _di_fss_identify_setting_t_
  typedef struct {
    uint16_t flag;

    f_state_t state;

    f_string_static_t line_first;
    f_string_static_t line_last;
  } fss_identify_setting_t;

  #define fss_identify_setting_t_initialize \
    { \
      fss_identify_main_flag_none_e, \
      f_state_t_initialize, \
      f_string_static_t_initialize, \
      f_string_static_t_initialize, \
    }
#endif // _di_fss_identify_setting_t_

/**
 * Delete the program main setting data.
 *
 * @param setting
 *   The program main setting data.
 *
 *   This does not alter setting.state.status.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fss_identify_setting_delete_
  extern f_status_t fss_identify_setting_delete(fss_identify_setting_t * const setting);
#endif // _di_fss_identify_setting_delete_

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
 *   This alters setting.state.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: f_console_parameter_process().
 *     Errors (with error bit) from: fll_program_parameter_process_context().
 *
 * @see f_console_parameter_process()
 * @see fll_program_parameter_process_context()
 */
#ifndef _di_fss_identify_setting_load_
  extern void fss_identify_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, fss_identify_setting_t * const setting);
#endif // _di_fss_identify_setting_load_

/**
 * Perform the standard program setting unload process.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *   All buffers are deallocated.
 *
 *   This does not alter setting.state.status.
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
#ifndef _di_fss_identify_setting_unload_
  extern f_status_t fss_identify_setting_unload(fll_program_data_t * const main, fss_identify_setting_t * const setting);
#endif // _di_fss_identify_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_identify_common_h
