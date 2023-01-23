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
#ifndef _fss_write_common_h
#define _fss_write_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program version.
 */
#ifndef _di_fss_write_program_version_s_
  #define FSS_WRITE_program_version_major_s F_string_ascii_0_s
  #define FSS_WRITE_program_version_minor_s F_string_ascii_7_s
  #define FSS_WRITE_program_version_micro_s F_string_ascii_0_s

  #define FSS_WRITE_program_version_major_s_length F_string_ascii_0_s_length
  #define FSS_WRITE_program_version_minor_s_length F_string_ascii_7_s_length
  #define FSS_WRITE_program_version_micro_s_length F_string_ascii_0_s_length

  #if !(defined(FSS_WRITE_program_version_nano_prefix_s) && defined(FSS_WRITE_program_version_nano_prefix_s_length))
    #define FSS_WRITE_program_version_nano_prefix_s
    #define FSS_WRITE_program_version_nano_prefix_s_length 0
  #endif // !(defined(FSS_WRITE_program_version_nano_prefix_s) && defined(FSS_WRITE_program_version_nano_prefix_s_length))

  #if !(defined(FSS_WRITE_program_version_nano_s) && defined(FSS_WRITE_program_version_nano_s_length))
    #define FSS_WRITE_program_version_nano_s
    #define FSS_WRITE_program_version_nano_s_length 0
  #endif // !(defined(FSS_WRITE_program_version_nano_s) && defined(FSS_WRITE_program_version_nano_s_length))

  #define FSS_WRITE_program_version_s FSS_WRITE_program_version_major_s F_string_ascii_period_s FSS_WRITE_program_version_minor_s F_string_ascii_period_s FSS_WRITE_program_version_micro_s FSS_WRITE_program_version_nano_prefix_s FSS_WRITE_program_version_nano_s

  #define FSS_WRITE_program_version_s_length FSS_WRITE_program_version_major_s_length + F_string_ascii_period_s_length + FSS_WRITE_program_version_minor_s_length + F_string_ascii_period_s_length + FSS_WRITE_program_version_micro_s_length + FSS_WRITE_program_version_nano_prefix_s_length + FSS_WRITE_program_version_nano_s_length

  extern const f_string_static_t fss_write_program_version_s;
#endif // _di_fss_write_program_version_s_

/**
 * The program name.
 */
#ifndef _di_fss_write_program_name_s_
  #define FSS_WRITE_program_name_s      "fss_write"
  #define FSS_WRITE_program_name_long_s "FSS Write"

  #define FSS_WRITE_program_name_s_length      9
  #define FSS_WRITE_program_name_long_s_length 9

  extern const f_string_static_t fss_write_program_name_s;
  extern const f_string_static_t fss_write_program_name_long_s;
#endif // _di_fss_write_program_name_s_

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
 * The program pipe strings.
 *
 * The fss_write_pipe_content_*_s strings are strings rather than characters to allow for wide characters.
 *
 * fss_write_pipe_content_*_s:
 *   - end:    The character representing the end of content.
 *   - ignore: The character representing the start of or end of a set of characters to ignore.
 *   - start:  The character representing the start of content.
 *
 * macro_fss_write_setting:
 *   - Used to represent a cast to ((fss_write_setting_t *) setting).
 *   - Simplifies the number of parenthesis used to make code slightly cleaner.
 *   - Is wrapped in a parenthesis and not a block.
 */
#ifndef _di_fss_write_pipe_s_
  #define FSS_WRITE_pipe_content_end_s    "\f"
  #define FSS_WRITE_pipe_content_ignore_s "\v"
  #define FSS_WRITE_pipe_content_start_s  "\b"

  #define FSS_WRITE_pipe_content_end_s_length    1
  #define FSS_WRITE_pipe_content_ignore_s_length 1
  #define FSS_WRITE_pipe_content_start_s_length  1

  extern const f_string_static_t fss_write_pipe_content_end_s;
  extern const f_string_static_t fss_write_pipe_content_ignore_s;
  extern const f_string_static_t fss_write_pipe_content_start_s;
#endif // _di_fss_write_pipe_s_

/**
 * A collection of static strings associated with FSS Payload Write.
 */
#ifndef _di_fss_write_s_
  #define FSS_WRITE_string_two_s "two"

  #define FSS_WRITE_string_two_s_length 3

  extern const f_string_static_t fss_write_string_two_s;
#endif // _di_fss_write_s_

/**
 * The main program parameters.
 */
#ifndef _di_fss_write_parameter_d_
  #define FSS_WRITE_short_as_s           "a"
  #define FSS_WRITE_short_backtick_s     "b"
  #define FSS_WRITE_short_content_s      "c"
  #define FSS_WRITE_short_content_end_s  "E"
  #define FSS_WRITE_short_content_next_s "N"
  #define FSS_WRITE_short_double_s       "d"
  #define FSS_WRITE_short_file_s         "f"
  #define FSS_WRITE_short_ignore_s       "I"
  #define FSS_WRITE_short_object_s       "o"
  #define FSS_WRITE_short_object_open_s  "O"
  #define FSS_WRITE_short_partial_s      "p"
  #define FSS_WRITE_short_prepend_s      "P"
  #define FSS_WRITE_short_single_s       "s"
  #define FSS_WRITE_short_trim_s         "T"

  #define FSS_WRITE_long_as_s           "as"
  #define FSS_WRITE_long_backtick_s     "backtick"
  #define FSS_WRITE_long_content_s      "content"
  #define FSS_WRITE_long_content_end_s  "content_end"
  #define FSS_WRITE_long_content_next_s "content_next"
  #define FSS_WRITE_long_double_s       "double"
  #define FSS_WRITE_long_file_s         "file"
  #define FSS_WRITE_long_ignore_s       "ignore"
  #define FSS_WRITE_long_object_s       "object"
  #define FSS_WRITE_long_object_open_s  "object_open"
  #define FSS_WRITE_long_partial_s      "partial"
  #define FSS_WRITE_long_prepend_s      "prepend"
  #define FSS_WRITE_long_single_s       "single"
  #define FSS_WRITE_long_trim_s         "trim"

  #define FSS_WRITE_short_as_s_length           1
  #define FSS_WRITE_short_backtick_s_length     1
  #define FSS_WRITE_short_content_s_length      1
  #define FSS_WRITE_short_content_end_s_length  1
  #define FSS_WRITE_short_content_next_s_length 1
  #define FSS_WRITE_short_double_s_length       1
  #define FSS_WRITE_short_file_s_length         1
  #define FSS_WRITE_short_ignore_s_length       1
  #define FSS_WRITE_short_object_s_length       1
  #define FSS_WRITE_short_object_open_s_length  1
  #define FSS_WRITE_short_partial_s_length      1
  #define FSS_WRITE_short_prepend_s_length      1
  #define FSS_WRITE_short_single_s_length       1
  #define FSS_WRITE_short_trim_s_length         1

  #define FSS_WRITE_long_as_s_length           2
  #define FSS_WRITE_long_backtick_s_length     8
  #define FSS_WRITE_long_content_s_length      7
  #define FSS_WRITE_long_content_end_s_length  11
  #define FSS_WRITE_long_content_next_s_length 12
  #define FSS_WRITE_long_double_s_length       6
  #define FSS_WRITE_long_file_s_length         4
  #define FSS_WRITE_long_ignore_s_length       6
  #define FSS_WRITE_long_object_s_length       6
  #define FSS_WRITE_long_object_open_s_length  11
  #define FSS_WRITE_long_partial_s_length      7
  #define FSS_WRITE_long_prepend_s_length      7
  #define FSS_WRITE_long_single_s_length       6
  #define FSS_WRITE_long_trim_s_length         4

  extern const f_string_static_t fss_write_short_as_s;
  extern const f_string_static_t fss_write_short_backtick_s;
  extern const f_string_static_t fss_write_short_content_s;
  extern const f_string_static_t fss_write_short_content_end_s;
  extern const f_string_static_t fss_write_short_content_next_s;
  extern const f_string_static_t fss_write_short_double_s;
  extern const f_string_static_t fss_write_short_file_s;
  extern const f_string_static_t fss_write_short_ignore_s;
  extern const f_string_static_t fss_write_short_object_s;
  extern const f_string_static_t fss_write_short_object_open_s;
  extern const f_string_static_t fss_write_short_partial_s;
  extern const f_string_static_t fss_write_short_prepend_s;
  extern const f_string_static_t fss_write_short_single_s;
  extern const f_string_static_t fss_write_short_trim_s;

  extern const f_string_static_t fss_write_long_as_s;
  extern const f_string_static_t fss_write_long_backtick_s;
  extern const f_string_static_t fss_write_long_content_s;
  extern const f_string_static_t fss_write_long_content_end_s;
  extern const f_string_static_t fss_write_long_content_next_s;
  extern const f_string_static_t fss_write_long_double_s;
  extern const f_string_static_t fss_write_long_file_s;
  extern const f_string_static_t fss_write_long_ignore_s;
  extern const f_string_static_t fss_write_long_object_s;
  extern const f_string_static_t fss_write_long_object_open_s;
  extern const f_string_static_t fss_write_long_partial_s;
  extern const f_string_static_t fss_write_long_prepend_s;
  extern const f_string_static_t fss_write_long_single_s;
  extern const f_string_static_t fss_write_long_trim_s;

  enum {
    fss_write_parameter_help_e,
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

  #define fss_write_total_parameters_d 26
#endif // _di_fss_write_parameter_d_

/**
 * Flags passed to the main function or program.
 *
 * fss_write_flag_*_e:
 *   - none:             No flags set.
 *   - content:          The Content being written is specified.
 *   - content_end:      The Content end characters are to be printed.
 *   - content_multiple: Designate that multiple Content is allowed for an Object for this standard rather than a single Content per Object.
 *   - content_next:     The Content next characters are to be printed.
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
    fss_write_flag_file_to_e          = 0x10,
    fss_write_flag_help_e             = 0x20,
    fss_write_flag_ignore_e           = 0x40,
    fss_write_flag_object_e           = 0x80,
    fss_write_flag_object_open_e      = 0x100,
    fss_write_flag_partial_e          = 0x200,
    fss_write_flag_prepend_e          = 0x400,
    fss_write_flag_trim_e             = 0x800,
    fss_write_flag_version_e          = 0x1000,
  }; // enum
#endif // _di_fss_write_flag_e_

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
#ifndef _di_fss_write_setting_delete_
  extern f_status_t fss_write_setting_delete(fss_write_setting_t * const setting);
#endif // _di_fss_write_setting_delete_

/**
 * Perform the standard program setting load process.
 *
 * This prints error messages as appropriate.
 *
 * If either main or setting is NULL, then this immediately returns without doing anything.
 *
 * @param arguments
 *   The parameters passed to the process (often referred to as command line arguments).
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This alters setting.status:
 *     F_none on success.
 *     F_data_not on success but nothing was provided to operate with.
 *
 *     F_parameter (with error bit) on parameter error.
 *
 *     Errors (with error bit) from: f_console_parameter_process().
 *     Errors (with error bit) from: f_file_stream_open().
 *     Errors (with error bit) from: f_string_dynamics_resize().
 *     Errors (with error bit) from: fll_program_parameter_process_context().
 *     Errors (with error bit) from: fll_program_parameter_process_verbosity().
 * @param callback
 *   (optional) Designate a function to call after performing the initial processing, but before printing help.
 *   If the function returns F_done, then this function immediately returns, resetting status to F_none.
 *   Set to NULL to disable.
 *
 * @see f_console_parameter_process()
 * @see f_file_stream_open()
 * @see f_string_dynamics_resize()
 * @see fll_program_parameter_process_context()
 * @see fll_program_parameter_process_verbosity()
 */
#ifndef _di_fss_write_setting_load_
  extern void fss_write_setting_load(const f_console_arguments_t arguments, f_state_t state, fll_program_data_t * const main, fss_write_setting_t * const setting, void (*callback)(const f_console_arguments_t arguments, f_state_t state, fll_program_data_t * const main, fss_write_setting_t * const setting));
#endif // _di_fss_write_setting_load_

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
#ifndef _di_fss_write_setting_unload_
  extern f_status_t fss_write_setting_unload(fll_program_data_t * const main, fss_write_setting_t * const setting);
#endif // _di_fss_write_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_write_common_h
