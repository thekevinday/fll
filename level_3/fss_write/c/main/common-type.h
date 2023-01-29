/**
 * FLL - Level 3
 *
 * Project: FSS Write
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_write_common_type_h
#define _fss_write_common_type_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program default defines.
 *
 * fss_write_default_allocation_*:
 *   - large: An allocation step used for buffers that are anticipated to have large buffers.
 *   - small: An allocation step used for buffers that are anticipated to have small buffers.
 */
#ifndef _di_fss_write_default_d_
  #define fss_write_default_allocation_large_d 2048
  #define fss_write_default_allocation_small_d 128
#endif // _di_fss_write_default_d_

/**
 * The program defines.
 *
 * macro_fss_write_setting:
 *   - Used to represent a cast to ((fss_write_setting_t *) setting).
 *   - Simplifies the number of parenthesis used to make code slightly cleaner.
 *   - Is wrapped in a parenthesis and not a block.
 */
#ifndef _di_fss_write_d_
  #define fss_write_signal_check_d 20000

  #define macro_fss_write_setting(setting) ((fss_write_setting_t *) setting)
#endif // _di_fss_write_d_

/**
 * Flags passed to the main function or program.
 *
 * fss_write_flag_*_e:
 *   - none:             No flags set.
 *   - content:          The Content being written is specified.
 *   - content_end:      The Content end characters are to be printed.
 *   - content_multiple: Designate that multiple Content is allowed for an Object for this standard rather than a single Content per Object.
 *   - content_next:     The Content next characters are to be printed.
 *   - copyright:        Print copyright.
 *   - file_to:          Using a specified destination file.
 *   - help:             Print help.
 *   - ignore:           Ignore a given range within a Content (specify flag before setting loading to designate ignores is supported by standard).
 *   - object:           The Object being written is specified.
 *   - object_open:      The Object open characters are to be printed.
 *   - partial:          Do not write end of Object/Content character.
 *   - prepend:          Prepend the given white space characters to the start of each multi-line Content.
 *   - trim:             Trim Object names.
 *   - version:          Print version.
 */
#ifndef _di_fss_write_flag_e_
  enum {
    fss_write_flag_none_e             = 0x0,
    fss_write_flag_content_e          = 0x1,
    fss_write_flag_content_end_e      = 0x2,
    fss_write_flag_content_multiple_e = 0x4,
    fss_write_flag_content_next_e     = 0x8,
    fss_write_flag_copyright_e        = 0x10,
    fss_write_flag_file_to_e          = 0x20,
    fss_write_flag_help_e             = 0x40,
    fss_write_flag_ignore_e           = 0x80,
    fss_write_flag_object_e           = 0x100,
    fss_write_flag_object_open_e      = 0x200,
    fss_write_flag_partial_e          = 0x400,
    fss_write_flag_prepend_e          = 0x800,
    fss_write_flag_trim_e             = 0x1000,
    fss_write_flag_version_e          = 0x2000,
  }; // enum
#endif // _di_fss_write_flag_e_

/**
 * The main program parameters.
 */
#ifndef _di_fss_write_parameter_e_
  enum {
    fss_write_parameter_help_e,
    fss_write_parameter_copyright_e,
    fss_write_parameter_light_e,
    fss_write_parameter_dark_e,
    fss_write_parameter_no_color_e,
    fss_write_parameter_verbosity_quiet_e,
    fss_write_parameter_verbosity_error_e,
    fss_write_parameter_verbosity_normal_e,
    fss_write_parameter_verbosity_verbose_e,
    fss_write_parameter_verbosity_debug_e,
    fss_write_parameter_version_e,
    fss_write_parameter_line_first_no_e,
    fss_write_parameter_line_last_no_e,

    fss_write_parameter_as_e,
    fss_write_parameter_backtick_e,
    fss_write_parameter_content_e,
    fss_write_parameter_content_end_e,
    fss_write_parameter_content_next_e,
    fss_write_parameter_double_e,
    fss_write_parameter_file_e,
    fss_write_parameter_ignore_e,
    fss_write_parameter_object_e,
    fss_write_parameter_object_open_e,
    fss_write_parameter_partial_e,
    fss_write_parameter_prepend_e,
    fss_write_parameter_single_e,
    fss_write_parameter_trim_e,
  }; // enum

  #define fss_write_console_parameter_t_initialize \
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
      macro_f_console_parameter_t_initialize_3(fss_write_short_as_s,           fss_write_long_as_s,           1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_write_short_backtick_s,     fss_write_long_backtick_s,     0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_write_short_content_s,      fss_write_long_content_s,      1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_write_short_content_end_s,  fss_write_long_content_end_s,  0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_write_short_content_next_s, fss_write_long_content_next_s, 0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_write_short_double_s,       fss_write_long_double_s,       0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_write_short_file_s,         fss_write_long_file_s,         1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_write_short_ignore_s,       fss_write_long_ignore_s,       2, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_write_short_object_s,       fss_write_long_object_s,       1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_write_short_object_open_s,  fss_write_long_object_open_s,  0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_write_short_partial_s,      fss_write_long_partial_s,      0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_write_short_prepend_s,      fss_write_long_prepend_s,      1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_write_short_single_s,       fss_write_long_single_s,       0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_write_short_trim_s,         fss_write_long_trim_s,         0, f_console_flag_normal_e), \
    }

  #define fss_write_total_parameters_d 27
#endif // _di_fss_write_parameter_e_

/**
 * The fss payload write main program settings.
 *
 * This is passed to the program-specific main entry point to designate program settings.
 * These program settings are often processed from the program arguments (often called the command line arguments).
 *
 * flag: Flags passed to the main function.
 *
 * status: The main status code, generally used by the load settings and main functions.
 *
 * state: The state data used when processing the FSS data.
 * range: A range used as a buffer during processing.
 *
 * line_first: A string expected to represent either "\n" or NULL to allow for easy handling of when to print first new line or not.
 * line_last:  A string expected to represent either "\n" or NULL to allow for easy handling of when to print last new line or not.
 *
 * quote:    This holds the quote used during processing.
 * standard: A human-friendly string describing the standard in use, such as "FSS-0000 (Basic)".
 *
 * escaped: A buffer used for escaping strings during processing.
 * block:   A buffer used to storing one or more blocks while processing a file line by line.
 * buffer:  A buffer used during processing the file.
 * prepend: A string to prepend to each multi-line Content.
 *
 * ignoress:  An array of range sets passed as values to the "--ignore" parameter or via the input pipe.
 * objects:   An array of objects passed as values to the "--object" parameter or via the input pipe.
 * contentss: An array of content sets passed as values to the "--content" parameter or via the input pipe.
 *
 * object:   A pointer to a specific Object used during processing.
 * content:  A pointer to a specific Content used during processing.
 * contents: A pointer to a specific set of Content used during processing.
 *
 * process_content: Process a single Content.
 * process_help:    Process help (generally printing help).
 * process_normal:  Process normally (data from parameters and files).
 * process_object:  Process a single Object.
 * process_pipe:    Process using the data from input pipe.
 * process_set:     Process a set of Object and one or more Content.
 */
#ifndef _di_fss_write_setting_t_
  typedef struct {
    uint16_t flag;

    f_status_t status;

    f_state_t state;
    f_string_range_t range;

    f_string_static_t line_first;
    f_string_static_t line_last;

    f_string_static_t quote;
    f_string_static_t standard;

    f_string_dynamic_t escaped;
    f_string_dynamic_t block;
    f_string_dynamic_t buffer;
    f_string_dynamic_t prepend;

    f_string_rangess_t ignoress;
    f_string_dynamics_t objects;
    f_string_dynamicss_t contentss;

    f_string_ranges_t *ignores;
    f_string_static_t *object;
    f_string_static_t *content;
    f_string_statics_t *contents;

    void (*process_content)(fll_program_data_t * const main, void * const setting, const bool last);
    void (*process_help)(fll_program_data_t * const main, void * const setting);
    void (*process_normal)(fll_program_data_t * const main, void * const setting);
    void (*process_object)(fll_program_data_t * const main, void * const setting);
    void (*process_pipe)(fll_program_data_t * const main, void * const setting);
    void (*process_set)(fll_program_data_t * const main, void * const setting);
  } fss_write_setting_t;

  #define fss_write_setting_t_initialize \
    { \
      fss_write_flag_none_e, \
      F_none, \
      macro_f_state_t_initialize(fss_write_default_allocation_large_d, fss_write_default_allocation_small_d, 0, 0, &fll_program_standard_signal_state, 0, 0, 0), \
      f_string_range_t_initialize, \
      f_string_static_t_initialize, \
      f_string_static_t_initialize, \
      f_string_static_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_rangess_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_string_dynamicss_t_initialize, \
      0, \
      0, \
      0, \
      0, \
      0, \
      0, \
      0, \
      0, \
      0, \
      0, \
    }
#endif // _di_fss_write_setting_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_write_common_type_h
