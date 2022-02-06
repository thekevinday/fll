/**
 * FLL - Level 3
 *
 * Project: IKI Read
 * API Version: 0.5
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
  #define IKI_READ_program_version_minor_s F_string_ascii_5_s
  #define IKI_READ_program_version_micro_s F_string_ascii_8_s

  #define IKI_READ_program_version_major_s_length F_string_ascii_0_s_length
  #define IKI_READ_program_version_minor_s_length F_string_ascii_5_s_length
  #define IKI_READ_program_version_micro_s_length F_string_ascii_8_s_length

  #if !(defined(IKI_READ_program_version_nano_prefix_s) && defined(IKI_READ_program_version_nano_prefix_s_length))
    #define IKI_READ_program_version_nano_prefix_s
    #define IKI_READ_program_version_nano_prefix_s_length 0
  #endif // !(defined(IKI_READ_program_version_nano_prefix_s) && defined(IKI_READ_program_version_nano_prefix_s_length))

  #if !(defined(IKI_READ_program_version_nano_s) && defined(IKI_READ_program_version_nano_s_length))
    #define IKI_READ_program_version_nano_s
    #define IKI_READ_program_version_nano_s_length 0
  #endif // !(defined(IKI_READ_program_version_nano_s) && defined(IKI_READ_program_version_nano_s_length))

  #define IKI_READ_program_version_s IKI_READ_program_version_major_s F_string_ascii_period_s IKI_READ_program_version_minor_s F_string_ascii_period_s IKI_READ_program_version_micro_s IKI_READ_program_version_nano_prefix_s IKI_READ_program_version_nano_s

  #define IKI_READ_program_version_s_length iki_read_program_version_major_s_length + F_string_ascii_period_s iki_read_program_version_minor_s_length + F_string_ascii_period_s_length + iki_read_program_version_micro_s_length + iki_read_program_version_nano_prefix_s_length + iki_read_program_version_nano_s_length

  extern const f_string_static_t iki_read_program_version_s;
#endif // _di_iki_read_program_version_

/**
 * The program name.
 */
#ifndef _di_iki_read_program_name_
  #define IKI_READ_program_name_s      "iki_read"
  #define IKI_READ_program_name_long_s "IKI Read"

  #define IKI_READ_program_name_s_length      9
  #define IKI_READ_program_name_long_s_length 9

  extern const f_string_static_t iki_read_program_name_s;
  extern const f_string_static_t iki_read_program_name_long_s;
#endif // _di_iki_read_program_name_

/**
 * The program defines.
 */
#ifndef _di_iki_read_defines_
  #define iki_read_signal_check_d 10000

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
  #define IKI_READ_short_substitute_s "s"
  #define IKI_READ_short_total_s      "t"
  #define IKI_READ_short_whole_s      "w"

  #define IKI_READ_long_at_s         "at"
  #define IKI_READ_long_content_s    "content"
  #define IKI_READ_long_line_s       "line"
  #define IKI_READ_long_literal_s    "literal"
  #define IKI_READ_long_name_s       "name"
  #define IKI_READ_long_object_s     "object"
  #define IKI_READ_long_substitute_s "substitute"
  #define IKI_READ_long_total_s      "total"
  #define IKI_READ_long_whole_s      "whole"

  #define IKI_READ_short_at_s_length         1
  #define IKI_READ_short_content_s_length    1
  #define IKI_READ_short_line_s_length       1
  #define IKI_READ_short_literal_s_length    1
  #define IKI_READ_short_name_s_length       1
  #define IKI_READ_short_object_s_length     1
  #define IKI_READ_short_substitute_s_length 1
  #define IKI_READ_short_total_s_length      1
  #define IKI_READ_short_whole_s_length      1

  #define IKI_READ_long_at_s_length         2
  #define IKI_READ_long_content_s_length    7
  #define IKI_READ_long_line_s_length       4
  #define IKI_READ_long_literal_s_length    7
  #define IKI_READ_long_name_s_length       4
  #define IKI_READ_long_object_s_length     7
  #define IKI_READ_long_substitute_s_length 10
  #define IKI_READ_long_total_s_length      5
  #define IKI_READ_long_whole_s_length      5

  extern const f_string_static_t iki_read_short_at_s;
  extern const f_string_static_t iki_read_short_content_s;
  extern const f_string_static_t iki_read_short_line_s;
  extern const f_string_static_t iki_read_short_literal_s;
  extern const f_string_static_t iki_read_short_name_s;
  extern const f_string_static_t iki_read_short_object_s;
  extern const f_string_static_t iki_read_short_substitute_s;
  extern const f_string_static_t iki_read_short_total_s;
  extern const f_string_static_t iki_read_short_whole_s;

  extern const f_string_static_t iki_read_long_at_s;
  extern const f_string_static_t iki_read_long_content_s;
  extern const f_string_static_t iki_read_long_line_s;
  extern const f_string_static_t iki_read_long_literal_s;
  extern const f_string_static_t iki_read_long_name_s;
  extern const f_string_static_t iki_read_long_object_s;
  extern const f_string_static_t iki_read_long_substitute_s;
  extern const f_string_static_t iki_read_long_total_s;
  extern const f_string_static_t iki_read_long_whole_s;

  enum {
    iki_read_parameter_help_e,
    iki_read_parameter_light_e,
    iki_read_parameter_dark_e,
    iki_read_parameter_no_color_e,
    iki_read_parameter_verbosity_quiet_e,
    iki_read_parameter_verbosity_normal_e,
    iki_read_parameter_verbosity_verbose_e,
    iki_read_parameter_verbosity_debug_e,
    iki_read_parameter_version_e,

    iki_read_parameter_at_e,
    iki_read_parameter_content_e,
    iki_read_parameter_line_e,
    iki_read_parameter_literal_e,
    iki_read_parameter_name_e,
    iki_read_parameter_object_e,
    iki_read_parameter_whole_e,
    iki_read_parameter_substitute_e,
    iki_read_parameter_total_e,
  };

  #define iki_read_console_parameter_t_initialize \
    { \
      macro_f_console_parameter_t_initialize(f_console_standard_short_help_s.string, f_console_standard_long_help_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_light_s.string, f_console_standard_long_light_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_dark_s.string, f_console_standard_long_dark_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_quiet_s.string, f_console_standard_long_quiet_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_no_color_s.string, f_console_standard_long_no_color_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_normal_s.string, f_console_standard_long_normal_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_verbose_s.string, f_console_standard_long_verbose_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_debug_s.string, f_console_standard_long_debug_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_version_s.string, f_console_standard_long_version_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(iki_read_short_at_s.string, iki_read_long_at_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(iki_read_short_content_s.string, iki_read_long_content_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(iki_read_short_line_s.string, iki_read_long_line_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(iki_read_short_literal_s.string, iki_read_long_literal_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(iki_read_short_name_s.string, iki_read_long_name_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(iki_read_short_object_s.string, iki_read_long_object_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(iki_read_short_whole_s.string, iki_read_long_whole_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(iki_read_short_substitute_s.string, iki_read_long_substitute_s.string, 0, 3, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(iki_read_short_total_s.string, iki_read_long_total_s.string, 0, 0, f_console_type_normal_e), \
    }

  #define iki_read_total_parameters_d 18
#endif // _di_iki_read_parameters_

#ifndef _di_iki_read_substitution_t_
  #define iki_read_substitution_vocabulary_s "vocabulary"
  #define iki_read_substitution_replace_s    "replace"
  #define iki_read_substitution_with_s       "with"

  typedef struct {
    f_string_static_t replace;
    f_string_static_t with;
  } iki_read_substitution_t;

  #define iki_read_substitution_t_initialize \
    { \
      f_string_static_t_initialize, \
      f_string_static_t_initialize, \
    }

  #define macro_iki_read_substitution_t_initialize(replace, with) \
    { \
      macro_f_string_static_t_initialize2(replace), \
      macro_f_string_static_t_initialize2(with), \
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
 * The main program data.
 *
 * parameters:   The state of pre-defined parameters passed to the program.
 * remaining:    The remaining, non-pre-defined parameters, passed to the program.
 * process_pipe: Designate whether or not to process the input pipe.
 * output:       The output file for general printing.
 * error:        The output file for error printing.
 * warning:      The output file for warning printing.
 * signal:       The process signal management structure.
 * context:      The color context.
 *
 * @todo
 */
#ifndef _di_iki_read_main_t_
  typedef struct {
    f_console_parameters_t parameters;

    bool process_pipe;

    fl_print_t output;
    fl_print_t error;
    fl_print_t warning;

    f_signal_t signal;

    uint8_t mode;

    f_number_unsigned_t at;
    f_number_unsigned_t line;

    f_string_dynamic_t buffer;

    iki_read_substitutions_t replacements;

    f_color_context_t context;
  } iki_read_main_t;

  #define iki_read_main_t_initialize \
    { \
      f_console_parameters_t_initialize, \
      f_array_lengths_t_initialize, \
      F_false, \
      fl_print_t_initialize, \
      macro_fl_print_t_initialize_error(), \
      macro_fl_print_t_initialize_warning(), \
      f_signal_t_initialize, \
      0, \
      0, \
      0, \
      f_string_dynamic_t_initialize, \
      iki_read_substitutions_t_initialize, \
      f_color_context_t_initialize, \
    }
#endif // _di_iki_read_main_t_

/**
 * Deallocate main.
 *
 * Be sure to call this after executing iki_read_main().
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see iki_read_main()
 */
#ifndef _di_iki_read_main_delete_
  extern f_status_t iki_read_main_delete(iki_read_main_t * const main);
#endif // _di_iki_read_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_read_common_h
