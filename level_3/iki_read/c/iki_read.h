/**
 * FLL - Level 3
 *
 * Project: IKI
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * This is the IKI Read program.
 *
 * This program utilizes the Featureless Linux Library.
 * This program processes files or other input in fss format and stores the results in the iki_read_main_t.
 *
 * This processes in accordance to the IKI specification.
 */
#ifndef _iki_read_h

// libc includes.
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// fll-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/color.h>
#include <fll/level_0/console.h>
#include <fll/level_0/conversion.h>
#include <fll/level_0/file.h>
#include <fll/level_0/iki.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>
#include <fll/level_0/signal.h>

// fll-1 includes
#include <fll/level_1/console.h>
#include <fll/level_1/conversion.h>
#include <fll/level_1/iki.h>
#include <fll/level_1/print.h>
#include <fll/level_1/signal.h>
#include <fll/level_1/string.h>

// fll-2 includes
#include <fll/level_2/error.h>
#include <fll/level_2/file.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_program_version_
  #define iki_read_program_version_major_s F_string_ascii_0_s
  #define iki_read_program_version_minor_s F_string_ascii_5_s
  #define iki_read_program_version_micro_s F_string_ascii_8_s

  #ifndef iki_read_program_version_nano_prefix_s
    #define iki_read_program_version_nano_prefix_s
  #endif

  #ifndef iki_read_program_version_nano_s
    #define iki_read_program_version_nano_s
  #endif

  #define iki_read_program_version_s iki_read_program_version_major_s F_string_ascii_period_s iki_read_program_version_minor_s F_string_ascii_period_s iki_read_program_version_micro_s iki_read_program_version_nano_prefix_s iki_read_program_version_nano_s
#endif // _di_iki_read_program_version_

#ifndef _di_iki_read_program_name_
  #define iki_read_program_name_s      "iki_read"
  #define iki_read_program_name_long_s "IKI Read"
#endif // _di_iki_read_program_name_

#ifndef _di_iki_read_defines_
  #define iki_read_signal_check_d 10000

  enum {
    iki_read_mode_content_e = 1,
    iki_read_mode_literal_e,
    iki_read_mode_object_e,
    iki_read_mode_total_e,
  };

  #define iki_read_short_at_s         "a"
  #define iki_read_short_content_s    "c"
  #define iki_read_short_line_s       "l"
  #define iki_read_short_literal_s    "L"
  #define iki_read_short_name_s       "n"
  #define iki_read_short_object_s     "o"
  #define iki_read_short_substitute_s "s"
  #define iki_read_short_total_s      "t"
  #define iki_read_short_whole_s      "w"

  #define iki_read_long_at_s         "at"
  #define iki_read_long_content_s    "content"
  #define iki_read_long_line_s       "line"
  #define iki_read_long_literal_s    "literal"
  #define iki_read_long_name_s       "name"
  #define iki_read_long_object_s     "object"
  #define iki_read_long_substitute_s "substitute"
  #define iki_read_long_total_s      "total"
  #define iki_read_long_whole_s      "whole"

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
      macro_f_console_parameter_t_initialize(iki_read_short_at_s, iki_read_long_at_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(iki_read_short_content_s, iki_read_long_content_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(iki_read_short_line_s, iki_read_long_line_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(iki_read_short_literal_s, iki_read_long_literal_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(iki_read_short_name_s, iki_read_long_name_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(iki_read_short_object_s, iki_read_long_object_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(iki_read_short_whole_s, iki_read_long_whole_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(iki_read_short_substitute_s, iki_read_long_substitute_s, 0, 3, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(iki_read_short_total_s, iki_read_long_total_s, 0, 0, f_console_type_normal_e), \
    }

  #define iki_read_total_parameters_d 18
#endif // _di_iki_read_defines_

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
      macro_f_string_static_t_initialize(replace), \
      macro_f_string_static_t_initialize(with), \
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

#ifndef _di_iki_read_main_t_
  typedef struct {
    f_console_parameter_t parameters[iki_read_total_parameters_d];

    f_array_lengths_t remaining;
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
      iki_read_console_parameter_t_initialize, \
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
 * Print help.
 *
 * @param file
 *   The file to print to.
 * @param context
 *   The color context settings.
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_iki_read_print_help_
  extern f_status_t iki_read_print_help(const f_file_t file, const f_color_context_t context);
#endif // _di_iki_read_print_help_

/**
 * Execute main program.
 *
 * Be sure to call iki_read_main_delete() after executing this.
 *
 * If main.signal is non-zero, then this blocks and handles the following signals:
 *   - F_signal_abort
 *   - F_signal_broken_pipe
 *   - F_signal_hangup
 *   - F_signal_interrupt
 *   - F_signal_quit
 *   - F_signal_termination
 *
 * @param main
 *   The main program data.
 * @param arguments
 *   The parameters passed to the process.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see iki_read_main_delete()
 */
#ifndef _di_iki_read_main_
  extern f_status_t iki_read_main(iki_read_main_t * const main, const f_console_arguments_t *arguments);
#endif // _di_iki_read_main_

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

#endif // _iki_read_h
