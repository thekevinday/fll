/**
 * FLL - Level 3
 *
 * Project: IKI Write
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common type structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _iki_write_common_type_h
#define _iki_write_common_type_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program defines.
 *
 * iki_write_*:
 *   - allocation_console: An allocation step used for small buffers specifically for console parameter.
 *   - allocation_large:   An allocation step used for buffers that are anticipated to have large buffers.
 *   - allocation_small:   An allocation step used for buffers that are anticipated to have small buffers.
 *   - signal_check:       Number of iterations before performing signal check in non-threaded signal handling.
 */
#ifndef _di_iki_write_d_
  #define iki_write_allocation_console_d 4
  #define iki_write_allocation_large_d   256
  #define iki_write_allocation_small_d   16
  #define iki_write_signal_check_d       20000
#endif // _di_iki_write_d_

/**
 * Flags passed to the main function or program.
 *
 * iki_write_main_flag_*_e:
 *   - none:        No flags set.
 *   - content:     The Content being written is specified.
 *   - copyright:   Print copyright.
 *   - file_to:     Using a specified destination file.
 *   - help:        Print help.
 *   - object:      The Object being written is specified.
 *   - print_first: When set, the first character printing logic is to be processed (this is usually automatic).
 *   - version:     Print version.
 *   - wrap:        Wrap the vocabulary.
 */
#ifndef _di_iki_write_main_flag_e_
  enum {
    iki_write_main_flag_none_e        = 0x0,
    iki_write_main_flag_content_e     = 0x1,
    iki_write_main_flag_copyright_e   = 0x2,
    iki_write_main_flag_file_to_e     = 0x4,
    iki_write_main_flag_help_e        = 0x8,
    iki_write_main_flag_object_e      = 0x10,
    iki_write_main_flag_print_first_e = 0x20,
    iki_write_main_flag_version_e     = 0x40,
    iki_write_main_flag_wrap_e        = 0x80,
  }; // enum
#endif // _di_iki_write_main_flag_e_

/**
 * The main program parameters.
 */
#ifndef _di_iki_write_parameter_e_
  enum {
    iki_write_parameter_help_e,
    iki_write_parameter_copyright_e,
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
    iki_write_parameter_wrap_e,
  }; // enum

  #define iki_write_console_parameter_t_initialize \
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
      macro_f_console_parameter_t_initialize_3(iki_write_short_backtick_s, iki_write_long_backtick_s, 0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_write_short_content_s,  iki_write_long_content_s,  1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_write_short_double_s,   iki_write_long_double_s,   0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_write_short_file_s,     iki_write_long_file_s,     1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_write_short_object_s,   iki_write_long_object_s,   1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_write_short_single_s,   iki_write_long_single_s,   0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_write_short_wrap_s,     iki_write_long_wrap_s,     0, f_console_flag_normal_e), \
    }

  #define iki_write_total_parameters_d 20
#endif // _di_iki_write_parameter_e_

/**
 * The iki write main program settings.
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

    f_state_t state;

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
      iki_write_main_flag_print_first_e, \
      f_state_t_initialize, \
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

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_write_common_type_h
