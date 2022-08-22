/**
 * FLL - Level 3
 *
 * Project: IKI Read
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _iki_read_common_h
#define _iki_read_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program version.
 */
#ifndef _di_iki_read_program_version_
  #define IKI_READ_program_version_major_s F_string_ascii_0_s
  #define IKI_READ_program_version_minor_s F_string_ascii_7_s
  #define IKI_READ_program_version_micro_s F_string_ascii_0_s

  #define IKI_READ_program_version_major_s_length F_string_ascii_0_s_length
  #define IKI_READ_program_version_minor_s_length F_string_ascii_7_s_length
  #define IKI_READ_program_version_micro_s_length F_string_ascii_0_s_length

  #if !(defined(IKI_READ_program_version_nano_prefix_s) && defined(IKI_READ_program_version_nano_prefix_s_length))
    #define IKI_READ_program_version_nano_prefix_s
    #define IKI_READ_program_version_nano_prefix_s_length 0
  #endif // !(defined(IKI_READ_program_version_nano_prefix_s) && defined(IKI_READ_program_version_nano_prefix_s_length))

  #if !(defined(IKI_READ_program_version_nano_s) && defined(IKI_READ_program_version_nano_s_length))
    #define IKI_READ_program_version_nano_s
    #define IKI_READ_program_version_nano_s_length 0
  #endif // !(defined(IKI_READ_program_version_nano_s) && defined(IKI_READ_program_version_nano_s_length))

  #define IKI_READ_program_version_s IKI_READ_program_version_major_s F_string_ascii_period_s IKI_READ_program_version_minor_s F_string_ascii_period_s IKI_READ_program_version_micro_s IKI_READ_program_version_nano_prefix_s IKI_READ_program_version_nano_s

  #define IKI_READ_program_version_s_length IKI_READ_program_version_major_s_length + F_string_ascii_period_s_length + IKI_READ_program_version_minor_s_length + F_string_ascii_period_s_length + IKI_READ_program_version_micro_s_length + IKI_READ_program_version_nano_prefix_s_length + IKI_READ_program_version_nano_s_length

  extern const f_string_static_t iki_read_program_version_s;
#endif // _di_iki_read_program_version_

/**
 * The program name.
 */
#ifndef _di_iki_read_program_name_
  #define IKI_READ_program_name_s      "iki_read"
  #define IKI_READ_program_name_long_s "IKI Read"

  #define IKI_READ_program_name_s_length      8
  #define IKI_READ_program_name_long_s_length 8

  extern const f_string_static_t iki_read_program_name_s;
  extern const f_string_static_t iki_read_program_name_long_s;
#endif // _di_iki_read_program_name_

/**
 * The program defines.
 */
#ifndef _di_iki_read_defines_
  #define iki_read_signal_check_d 20000

  enum {
    iki_read_mode_content_e = 1,
    iki_read_mode_literal_e,
    iki_read_mode_object_e,
    iki_read_mode_total_e,
  };
#endif // _di_iki_read_defines_

/**
 * The main program parameters.
 */
#ifndef _di_iki_read_parameters_
  #define IKI_READ_short_at_s         "a"
  #define IKI_READ_short_content_s    "c"
  #define IKI_READ_short_line_s       "l"
  #define IKI_READ_short_literal_s    "L"
  #define IKI_READ_short_name_s       "n"
  #define IKI_READ_short_object_s     "o"
  #define IKI_READ_short_replace_s    "r"
  #define IKI_READ_short_substitute_s "s"
  #define IKI_READ_short_total_s      "t"
  #define IKI_READ_short_whole_s      "w"
  #define IKI_READ_short_wrap_s       "W"

  #define IKI_READ_long_at_s         "at"
  #define IKI_READ_long_content_s    "content"
  #define IKI_READ_long_line_s       "line"
  #define IKI_READ_long_literal_s    "literal"
  #define IKI_READ_long_name_s       "name"
  #define IKI_READ_long_object_s     "object"
  #define IKI_READ_long_replace_s    "replace"
  #define IKI_READ_long_substitute_s "substitute"
  #define IKI_READ_long_total_s      "total"
  #define IKI_READ_long_whole_s      "whole"
  #define IKI_READ_long_wrap_s       "wrap"

  #define IKI_READ_short_at_s_length         1
  #define IKI_READ_short_content_s_length    1
  #define IKI_READ_short_line_s_length       1
  #define IKI_READ_short_literal_s_length    1
  #define IKI_READ_short_name_s_length       1
  #define IKI_READ_short_object_s_length     1
  #define IKI_READ_short_replace_s_length    1
  #define IKI_READ_short_substitute_s_length 1
  #define IKI_READ_short_total_s_length      1
  #define IKI_READ_short_whole_s_length      1
  #define IKI_READ_short_wrap_s_length       1

  #define IKI_READ_long_at_s_length         2
  #define IKI_READ_long_content_s_length    7
  #define IKI_READ_long_line_s_length       4
  #define IKI_READ_long_literal_s_length    7
  #define IKI_READ_long_name_s_length       4
  #define IKI_READ_long_object_s_length     6
  #define IKI_READ_long_replace_s_length    7
  #define IKI_READ_long_substitute_s_length 10
  #define IKI_READ_long_total_s_length      5
  #define IKI_READ_long_whole_s_length      5
  #define IKI_READ_long_wrap_s_length       4

  extern const f_string_static_t iki_read_short_at_s;
  extern const f_string_static_t iki_read_short_content_s;
  extern const f_string_static_t iki_read_short_line_s;
  extern const f_string_static_t iki_read_short_literal_s;
  extern const f_string_static_t iki_read_short_name_s;
  extern const f_string_static_t iki_read_short_object_s;
  extern const f_string_static_t iki_read_short_replace_s;
  extern const f_string_static_t iki_read_short_substitute_s;
  extern const f_string_static_t iki_read_short_total_s;
  extern const f_string_static_t iki_read_short_whole_s;
  extern const f_string_static_t iki_read_short_wrap_s;

  extern const f_string_static_t iki_read_long_at_s;
  extern const f_string_static_t iki_read_long_content_s;
  extern const f_string_static_t iki_read_long_line_s;
  extern const f_string_static_t iki_read_long_literal_s;
  extern const f_string_static_t iki_read_long_name_s;
  extern const f_string_static_t iki_read_long_object_s;
  extern const f_string_static_t iki_read_long_replace_s;
  extern const f_string_static_t iki_read_long_substitute_s;
  extern const f_string_static_t iki_read_long_total_s;
  extern const f_string_static_t iki_read_long_whole_s;
  extern const f_string_static_t iki_read_long_wrap_s;

  enum {
    iki_read_parameter_help_e,
    iki_read_parameter_light_e,
    iki_read_parameter_dark_e,
    iki_read_parameter_no_color_e,
    iki_read_parameter_verbosity_quiet_e,
    iki_read_parameter_verbosity_error_e,
    iki_read_parameter_verbosity_normal_e,
    iki_read_parameter_verbosity_verbose_e,
    iki_read_parameter_verbosity_debug_e,
    iki_read_parameter_version_e,
    iki_read_parameter_line_first_no_e,
    iki_read_parameter_line_last_no_e,

    iki_read_parameter_at_e,
    iki_read_parameter_content_e,
    iki_read_parameter_line_e,
    iki_read_parameter_literal_e,
    iki_read_parameter_name_e,
    iki_read_parameter_object_e,
    iki_read_parameter_replace_e,
    iki_read_parameter_substitute_e,
    iki_read_parameter_total_e,
    iki_read_parameter_whole_e,
    iki_read_parameter_wrap_e,
  };

  #define iki_read_console_parameter_t_initialize \
    { \
      mac
      macro_f_console_parameter_t_initialize4(f_console_standard_short_help_s,          f_console_standard_long_help_s,          0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_light_s,         f_console_standard_long_light_s,         0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_dark_s,          f_console_standard_long_dark_s,          0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_no_color_s,      f_console_standard_long_no_color_s,      0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_quiet_s,         f_console_standard_long_quiet_s,         0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_error_s,         f_console_standard_long_error_s,         0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_normal_s,        f_console_standard_long_normal_s,        0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_verbose_s,       f_console_standard_long_verbose_s,       0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_debug_s,         f_console_standard_long_debug_s,         0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_version_s,       f_console_standard_long_version_s,       0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_line_first_no_s, f_console_standard_long_line_first_no_s, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_line_last_no_s,  f_console_standard_long_line_last_no_s,  0, f_console_type_inverse_e), \
      \
      macro_f_console_parameter_t_initialize2(iki_read_short_at_s.string, iki_read_long_at_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize2(iki_read_short_content_s.string, iki_read_long_content_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize2(iki_read_short_line_s.string, iki_read_long_line_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize2(iki_read_short_literal_s.string, iki_read_long_literal_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize2(iki_read_short_name_s.string, iki_read_long_name_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize2(iki_read_short_object_s.string, iki_read_long_object_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize2(iki_read_short_replace_s.string, iki_read_long_replace_s.string, 0, 2, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize2(iki_read_short_substitute_s.string, iki_read_long_substitute_s.string, 0, 3, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize2(iki_read_short_total_s.string, iki_read_long_total_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize2(iki_read_short_whole_s.string, iki_read_long_whole_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize2(iki_read_short_wrap_s.string, iki_read_long_wrap_s.string, 0, 3, f_console_type_normal_e), \
    }

  #define iki_read_total_parameters_d 23
#endif // _di_iki_read_parameters_

#ifndef _di_iki_read_substitution_t_
  #define IKI_READ_substitution_after_s      "after"
  #define IKI_READ_substitution_before_s     "before"
  #define IKI_READ_substitution_replace_s    "replace"
  #define IKI_READ_substitution_vocabulary_s "vocabulary"
  #define IKI_READ_substitution_with_s       "with"

  #define IKI_READ_substitution_after_s_length      5
  #define IKI_READ_substitution_before_s_length     6
  #define IKI_READ_substitution_replace_s_length    7
  #define IKI_READ_substitution_vocabulary_s_length 10
  #define IKI_READ_substitution_with_s_length       4

  extern const f_string_static_t iki_read_substitution_after_s;
  extern const f_string_static_t iki_read_substitution_before_s;
  extern const f_string_static_t iki_read_substitution_replace_s;
  extern const f_string_static_t iki_read_substitution_vocabulary_s;
  extern const f_string_static_t iki_read_substitution_with_s;

  typedef struct {
    f_string_static_t replace;
    f_string_static_t with;
  } iki_read_substitution_t;

  #define iki_read_substitution_t_initialize \
    { \
      f_string_static_t_initialize, \
      f_string_static_t_initialize, \
    }

  #define macro_iki_read_substitution_t_initialize(replace, with, extra) \
    { \
      replace, \
      with, \
    }
#endif // _di_iki_read_substitution_t_

#ifndef _di_iki_read_substitutions_t_
  typedef struct {
    iki_read_substitution_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } iki_read_substitutions_t;

  #define iki_read_substitutions_t_initialize { 0, 0, 0 }

  #define macro_iki_read_substitutions_t_clear(replacements) macro_f_memory_structure_clear(replacements)

  #define macro_iki_read_substitutions_t_delete_simple(replacements)  macro_f_memory_structure_delete_simple(replacements, iki_read_substitution_t)
  #define macro_iki_read_substitutions_t_destroy_simple(replacements) macro_f_memory_structure_destroy_simple(replacements, iki_read_substitution_t)

  #define macro_iki_read_substitutions_t_resize(status, replacements, length) macro_f_memory_structure_resize(status, replacements, iki_read_substitution_t, length)
  #define macro_iki_read_substitutions_t_adjust(status, replacements, length) macro_f_memory_structure_adjust(status, replacements, iki_read_substitution_t, length)
#endif // _di_iki_read_substitutions_t_

/**
 * Flags used to represent flags passed to the main function.
 *
 * iki_read_main_flag_*_e:
 *   - none:          No modes in use.
 *   - file_from:     Using a specified source file.
 *   - file_to:       Using a specified destination file.
 *   - help:          Print help.
 *   - header:        Enable printing of headers.
 *   - separate:      Enable printing of separators.
 *   - strip_invalid: Using strip invalid character mode.
 *   - verify:        Using verify mode.
 *   - version:       Print version.
 */
#ifndef _di_iki_read_main_flag_e_
  enum {
    iki_read_main_flag_none_e          = 0x0,
    iki_read_main_flag_file_from_e     = 0x1,
    iki_read_main_flag_file_to_e       = 0x2,
    iki_read_main_flag_header_e        = 0x4,
    iki_read_main_flag_help_e          = 0x8,
    iki_read_main_flag_separate_e      = 0x10,
    iki_read_main_flag_strip_invalid_e = 0x20,
    iki_read_main_flag_verify_e        = 0x40,
    iki_read_main_flag_version_e       = 0x80,
  };
#endif // _di_iki_read_main_flag_e_

/**
 * The iki read main program settings.
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
 */
#ifndef _di_iki_read_setting_t_
  typedef struct {
    uint16_t flag;

    f_status_t status;

    f_string_static_t line_first;
    f_string_static_t line_last;
  } iki_read_setting_t;

  #define iki_read_setting_t_initialize \
    { \
      iki_read_main_flag_none_e, \
      F_none, \
      f_string_static_t_initialize, \
      f_string_static_t_initialize, \
    }
#endif // _di_iki_read_setting_t_

/**
 * Delete the program main setting data.
 *
 * @param setting
 *   The program main setting data.
 *   This does not alter setting.status.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_iki_read_setting_delete_
  extern f_status_t iki_read_setting_delete(iki_read_setting_t * const setting);
#endif // _di_iki_read_setting_delete_

/**
 * Perform the standard program setting load process.
 *
 * This prints error messages as appropriate.
 *
 * If either main or setting is NULL, then this immediately retuns without doing anything.
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
 *     Errors (with error bit) from: fll_program_parameter_process_context().
 *
 * @see f_console_parameter_process()
 * @see fll_program_parameter_process_context()
 */
#ifndef _di_iki_read_setting_load_
  extern void iki_read_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, iki_read_setting_t * const setting);
#endif // _di_iki_read_setting_load_

/**
 * Perform the standard program setting unload process.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *   This does not alter setting.status.
 *   All buffers are deallocated.
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
#ifndef _di_iki_read_setting_unload_
  extern f_status_t iki_read_setting_unload(fll_program_data_t * const main, iki_read_setting_t * const setting);
#endif // _di_iki_read_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_read_common_h
