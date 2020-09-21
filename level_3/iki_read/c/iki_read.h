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
 * This program processes files or other input in fss format and stores the results in the iki_read_data_t.
 *
 * This processes in accordance to the IKI specification.
 */
#ifndef _iki_read_h

// libc includes
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/utf.h>
#include <level_0/console.h>
#include <level_0/conversion.h>
#include <level_0/file.h>
#include <level_0/iki.h>
#include <level_0/pipe.h>
#include <level_0/print.h>

// fll-1 includes
#include <level_1/color.h>
#include <level_1/console.h>
#include <level_1/conversion.h>
#include <level_1/iki.h>
#include <level_1/print.h>
#include <level_1/string.h>

// fll-2 includes
#include <level_2/file.h>
#include <level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_version_
  #define iki_read_major_version "0"
  #define iki_read_minor_version "5"
  #define iki_read_micro_version "1"
  #define iki_read_version iki_read_major_version "." iki_read_minor_version "." iki_read_micro_version
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
    iki_read_parameter_quiet,
    iki_read_parameter_verbose,
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
      f_console_parameter_t_initialize(f_console_standard_short_help, f_console_standard_long_help, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(f_console_standard_short_light, f_console_standard_long_light, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_dark, f_console_standard_long_dark, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_no_color, f_console_standard_long_no_color, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_quiet, f_console_standard_long_quiet, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_verbose, f_console_standard_long_verbose, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_version, f_console_standard_long_version, 0, 0, f_console_type_inverse), \
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

  #define iki_read_total_parameters 16
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
      f_macro_string_static_t_initialize(replace), \
      f_macro_string_static_t_initialize(with), \
    }
#endif // _di_iki_read_substitution_t_

#ifndef _di_iki_read_substitutions_t_
  typedef struct {
    iki_read_substitution_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } iki_read_substitutions_t;

  #define iki_read_substitutions_t_initialize {0, 0, 0}

  #define macro_iki_read_substitutions_t_clear(replacements) f_macro_memory_structure_t_clear(replacements)

  #define macro_iki_read_substitutions_t_new(status, replacements, length) f_macro_memory_structure_t_new(status, replacements, iki_read_substitution_t, length)

  #define macro_iki_read_substitutions_t_delete_simple(replacements) \
    replacements.used = replacements.size; \
    while (replacements.used > 0) { \
      replacements.used--; \
    } \
    if (!replacements.used) f_macro_memory_structure_t_delete_simple(replacements, iki_read_substitution_t)

  #define macro_iki_read_substitutions_t_destroy_simple(replacements) \
    replacements.used = replacements.size; \
    while (replacements.used > 0) { \
      replacements.used--; \
    } \
    if (!replacements.used) f_macro_memory_structure_t_destroy_simple(replacements, iki_read_substitution_t)

  #define macro_iki_read_substitutions_t_resize(status, replacements, new_length) \
    status = F_none; \
    if (new_length < replacements.size) { \
      f_array_length_t i = replacements.size - new_length; \
      for (; i < replacements.size; i++) { \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_resize((void **) & replacements.array, sizeof(iki_read_substitution_t), replacements.size, new_length); \
    if (status == F_none) { \
      if (new_length > replacements.size) { \
        f_array_length_t i = replacements.size; \
        for (; i < new_length; i++) { \
          memset(&replacements.array[i], 0, sizeof(iki_read_substitution_t)); \
        } \
      } \
      replacements.size = new_length; \
      if (replacements.used > replacements.size) replacements.used = new_length; \
    }

  #define macro_iki_read_substitutions_t_adjust(status, replacements, new_length) \
    status = F_none; \
    if (new_length < replacements.size) { \
      f_array_length_t i = replacements.size - new_length; \
      for (; i < replacements.size; i++) { \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_adjust((void **) & replacements.array, sizeof(iki_read_substitution_t), replacements.size, new_length); \
    if (status == F_none) { \
      if (new_length > replacements.size) { \
        f_array_length_t i = replacements.size; \
        for (; i < new_length; i++) { \
          memset(&replacements.array[i], 0, sizeof(iki_read_substitution_t)); \
        } \
      } \
      replacements.size = new_length; \
      if (replacements.used > replacements.size) replacements.used = new_length; \
    }
#endif // _di_iki_read_substitutions_t_

#ifndef _di_iki_read_data_t_
  typedef struct {
    f_console_parameter_t parameters[iki_read_total_parameters];

    f_string_lengths_t remaining;
    bool process_pipe;

    uint8_t verbosity;
    uint8_t mode;

    f_number_unsigned_t at;
    f_number_unsigned_t line;

    f_string_dynamic_t buffer;

    iki_read_substitutions_t replacements;

    f_color_context_t context;
  } iki_read_data_t;

  #define iki_read_data_t_initialize \
    { \
      iki_read_console_parameter_t_initialize, \
      f_string_lengths_t_initialize, \
      F_false, \
      f_console_verbosity_normal, \
      0, \
      0, \
      0, \
      f_string_dynamic_t_initialize, \
      iki_read_substitutions_t_initialize, \
      f_color_context_t_initialize, \
    }
#endif // _di_iki_read_data_t_

/**
 * Print help to standard output.
 *
 * @param context
 *   The color context settings.
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_iki_read_print_help_
  extern f_return_status iki_read_print_help(const f_color_context_t context);
#endif // _di_iki_read_print_help_

/**
 * Execute main program.
 *
 * Be sure to call iki_read_delete_data() after executing this.
 *
 * @param arguments
 *   The parameters passed to the process.
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see iki_read_delete_data()
 */
#ifndef _di_iki_read_main_
  extern f_return_status iki_read_main(const f_console_arguments_t arguments, iki_read_data_t *data);
#endif // _di_iki_read_main_

/**
 * Deallocate data.
 *
 * Be sure to call this after executing iki_read_main().
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see iki_read_main()
 */
#ifndef _di_iki_read_delete_data_
  extern f_return_status iki_read_delete_data(iki_read_data_t *data);
#endif // _di_iki_read_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_read_h
