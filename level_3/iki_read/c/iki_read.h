/**
 * FLL - Level 3
 *
 * Project: IKI
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This is the IKI Read program.
 *
 * This program utilizes the Featureless Linux Library.
 * This program processes files or other input in fss format and stores the results in the iki_read_main_t.
 *
 * This processes in accordance to the IKI specification.
 */
#ifndef _iki_read_h

// libc includes
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// fll-0 includes
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
#include <fll/level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_version_
  #define iki_read_major_version f_string_ascii_0
  #define iki_read_minor_version f_string_ascii_5
  #define iki_read_micro_version f_string_ascii_4

  #ifndef iki_read_nano_version_prefix
    #define iki_read_nano_version_prefix
  #endif

  #ifndef iki_read_nano_version
    #define iki_read_nano_version
  #endif

  #define iki_read_version iki_read_major_version f_string_ascii_period iki_read_minor_version f_string_ascii_period iki_read_micro_version iki_read_nano_version_prefix iki_read_nano_version
#endif // _di_iki_read_version_

#ifndef _di_iki_read_name_
  #define iki_read_name      "iki_read"
  #define iki_read_name_long "IKI Read"
#endif // _di_iki_read_name_

#ifndef _di_iki_read_defines_
  enum {
    iki_read_mode_content = 1,
    iki_read_mode_literal,
    iki_read_mode_object,
    iki_read_mode_total,
  };

  #define iki_read_short_at         "a"
  #define iki_read_short_content    "c"
  #define iki_read_short_line       "l"
  #define iki_read_short_literal    "L"
  #define iki_read_short_name       "n"
  #define iki_read_short_object     "o"
  #define iki_read_short_substitute "s"
  #define iki_read_short_total      "t"
  #define iki_read_short_whole      "w"

  #define iki_read_long_at         "at"
  #define iki_read_long_content    "content"
  #define iki_read_long_line       "line"
  #define iki_read_long_literal    "literal"
  #define iki_read_long_name       "name"
  #define iki_read_long_object     "object"
  #define iki_read_long_substitute "substitute"
  #define iki_read_long_total      "total"
  #define iki_read_long_whole      "whole"

  enum {
    iki_read_parameter_help,
    iki_read_parameter_light,
    iki_read_parameter_dark,
    iki_read_parameter_no_color,
    iki_read_parameter_verbosity_quiet,
    iki_read_parameter_verbosity_normal,
    iki_read_parameter_verbosity_verbose,
    iki_read_parameter_verbosity_debug,
    iki_read_parameter_version,

    iki_read_parameter_at,
    iki_read_parameter_content,
    iki_read_parameter_line,
    iki_read_parameter_literal,
    iki_read_parameter_name,
    iki_read_parameter_object,
    iki_read_parameter_whole,
    iki_read_parameter_substitute,
    iki_read_parameter_total,
  };

  #define iki_read_console_parameter_t_initialize \
    { \
      f_console_parameter_t_initialize(f_console_standard_short_help_s, f_console_standard_long_help_s, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(f_console_standard_short_light_s, f_console_standard_long_light_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_dark_s, f_console_standard_long_dark_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_normal_s, f_console_standard_long_normal_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_debug_s, f_console_standard_long_debug_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_version_s, f_console_standard_long_version_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(iki_read_short_at, iki_read_long_at, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(iki_read_short_content, iki_read_long_content, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(iki_read_short_line, iki_read_long_line, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(iki_read_short_literal, iki_read_long_literal, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(iki_read_short_name, iki_read_long_name, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(iki_read_short_object, iki_read_long_object, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(iki_read_short_whole, iki_read_long_whole, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(iki_read_short_substitute, iki_read_long_substitute, 0, 3, f_console_type_normal), \
      f_console_parameter_t_initialize(iki_read_short_total, iki_read_long_total, 0, 0, f_console_type_normal), \
    }

  #define iki_read_total_parameters 18
#endif // _di_iki_read_defines_

#ifndef _di_iki_read_substitution_t_
  #define iki_read_substitution_vocabulary "vocabulary"
  #define iki_read_substitution_replace    "replace"
  #define iki_read_substitution_with       "with"

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
    f_console_parameter_t parameters[iki_read_total_parameters];

    f_array_lengths_t remaining;
    bool process_pipe;

    f_file_t output;
    fll_error_print_t error;

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
      macro_f_file_t_initialize2(f_type_output, f_type_descriptor_output, f_file_flag_write_only), \
      fll_error_print_t_initialize, \
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
 * @param output
 *   The file to print to.
 * @param context
 *   The color context settings.
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_iki_read_print_help_
  extern f_status_t iki_read_print_help(const f_file_t output, const f_color_context_t context);
#endif // _di_iki_read_print_help_

/**
 * Execute main program.
 *
 * Be sure to call iki_read_main_delete() after executing this.
 *
 * @param arguments
 *   The parameters passed to the process.
 * @param main
 *   The main data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see iki_read_main_delete()
 */
#ifndef _di_iki_read_main_
  extern f_status_t iki_read_main(const f_console_arguments_t arguments, iki_read_main_t *main);
#endif // _di_iki_read_main_

/**
 * Deallocate main.
 *
 * Be sure to call this after executing iki_read_main().
 *
 * @param main
 *   The main data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see iki_read_main()
 */
#ifndef _di_iki_read_main_delete_
  extern f_status_t iki_read_main_delete(iki_read_main_t *main);
#endif // _di_iki_read_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_read_h
