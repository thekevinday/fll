/**
 * FLL - Level 3
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This is the FSS Basic List Read program
 * This program utilizes the Featureless Linux Library.
 * This program processes files or other input in fss format and stores the results in the fss_basic_list_read_main_t.
 *
 * This processes in accordance to the FSS-0002 Basic List specification.
 */
#ifndef _fss_basic_list_read_h

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
#include <fll/level_0/directory.h>
#include <fll/level_0/file.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>

// fll-1 includes
#include <fll/level_1/console.h>
#include <fll/level_1/conversion.h>
#include <fll/level_1/print.h>
#include <fll/level_1/string.h>

// fll-2 includes
#include <fll/level_2/error.h>
#include <fll/level_2/file.h>
#include <fll/level_2/fss_basic_list.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_basic_list_read_version_
  #define fss_basic_list_read_major_version f_string_ascii_0
  #define fss_basic_list_read_minor_version f_string_ascii_5
  #define fss_basic_list_read_micro_version f_string_ascii_6

  #ifndef fss_basic_list_read_nano_version_prefix
    #define fss_basic_list_read_nano_version_prefix
  #endif

  #ifndef fss_basic_list_read_nano_version
    #define fss_basic_list_read_nano_version
  #endif

  #define fss_basic_list_read_version fss_basic_list_read_major_version f_string_ascii_period fss_basic_list_read_minor_version f_string_ascii_period fss_basic_list_read_micro_version fss_basic_list_read_nano_version_prefix fss_basic_list_read_nano_version
#endif // _di_fss_basic_list_read_version_

#ifndef _di_fss_basic_list_read_name_
  #define fss_basic_list_read_name      "fss_basic_list_read"
  #define fss_basic_list_read_name_long "FSS Basic List Read"
#endif // _di_fss_basic_list_read_name_

#ifndef _di_fss_basic_list_read_defines_
  #define fss_basic_list_read_pipe_content_end    '\f'
  #define fss_basic_list_read_pipe_content_ignore '\v'
  #define fss_basic_list_read_pipe_content_start  '\b'

  #define fss_basic_list_read_short_at      "a"
  #define fss_basic_list_read_short_content "c"
  #define fss_basic_list_read_short_columns "C"
  #define fss_basic_list_read_short_delimit "D"
  #define fss_basic_list_read_short_depth   "d"
  #define fss_basic_list_read_short_empty   "e"
  #define fss_basic_list_read_short_line    "l"
  #define fss_basic_list_read_short_name    "n"
  #define fss_basic_list_read_short_object  "o"
  #define fss_basic_list_read_short_pipe    "p"
  #define fss_basic_list_read_short_raw     "R"
  #define fss_basic_list_read_short_select  "s"
  #define fss_basic_list_read_short_total   "t"
  #define fss_basic_list_read_short_trim    "T"

  #define fss_basic_list_read_long_at      "at"
  #define fss_basic_list_read_long_content "content"
  #define fss_basic_list_read_long_columns "columns"
  #define fss_basic_list_read_long_delimit "delimit"
  #define fss_basic_list_read_long_depth   "depth"
  #define fss_basic_list_read_long_empty   "empty"
  #define fss_basic_list_read_long_line    "line"
  #define fss_basic_list_read_long_name    "name"
  #define fss_basic_list_read_long_object  "object"
  #define fss_basic_list_read_long_pipe    "pipe"
  #define fss_basic_list_read_long_raw     "raw"
  #define fss_basic_list_read_long_select  "select"
  #define fss_basic_list_read_long_total   "total"
  #define fss_basic_list_read_long_trim    "trim"

  enum {
    fss_basic_list_read_parameter_help,
    fss_basic_list_read_parameter_light,
    fss_basic_list_read_parameter_dark,
    fss_basic_list_read_parameter_no_color,
    fss_basic_list_read_parameter_verbosity_quiet,
    fss_basic_list_read_parameter_verbosity_normal,
    fss_basic_list_read_parameter_verbosity_verbose,
    fss_basic_list_read_parameter_verbosity_debug,
    fss_basic_list_read_parameter_version,

    fss_basic_list_read_parameter_at,
    fss_basic_list_read_parameter_content,
    fss_basic_list_read_parameter_columns,
    fss_basic_list_read_parameter_delimit,
    fss_basic_list_read_parameter_depth,
    fss_basic_list_read_parameter_empty,
    fss_basic_list_read_parameter_line,
    fss_basic_list_read_parameter_name,
    fss_basic_list_read_parameter_object,
    fss_basic_list_read_parameter_pipe,
    fss_basic_list_read_parameter_raw,
    fss_basic_list_read_parameter_select,
    fss_basic_list_read_parameter_total,
    fss_basic_list_read_parameter_trim,
  };

  #define fss_basic_list_read_console_parameter_t_initialize \
    { \
      f_console_parameter_t_initialize(f_console_standard_short_help_s, f_console_standard_long_help_s, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(f_console_standard_short_light_s, f_console_standard_long_light_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_dark_s, f_console_standard_long_dark_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, 0, F_false, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_normal_s, f_console_standard_long_normal_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_debug_s, f_console_standard_long_debug_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_version_s, f_console_standard_long_version_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(fss_basic_list_read_short_at, fss_basic_list_read_long_at, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_basic_list_read_short_content, fss_basic_list_read_long_content, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_basic_list_read_short_columns, fss_basic_list_read_long_columns, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_basic_list_read_short_delimit, fss_basic_list_read_long_delimit, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_basic_list_read_short_depth, fss_basic_list_read_long_depth, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_basic_list_read_short_empty, fss_basic_list_read_long_empty, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_basic_list_read_short_line, fss_basic_list_read_long_line, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_basic_list_read_short_name, fss_basic_list_read_long_name, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_basic_list_read_short_object, fss_basic_list_read_long_object, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_basic_list_read_short_pipe, fss_basic_list_read_long_pipe, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_basic_list_read_short_raw, fss_basic_list_read_long_raw, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_basic_list_read_short_select, fss_basic_list_read_long_select, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_basic_list_read_short_total, fss_basic_list_read_long_total, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_basic_list_read_short_trim, fss_basic_list_read_long_trim, 0, 0, f_console_type_normal), \
    }

  #define fss_basic_list_read_total_parameters 23
#endif // _di_fss_basic_list_read_defines_

/**
 * FSS Delimit Parameter data.
 *
 * fss_basic_list_read_delimit_mode_*:
 *   - all:                    All delimits are to be aplied.
 *   - content:                Content are to have delimits applied.
 *   - content_greater:        Content at this number or higher are to have delimits applied.
 *   - content_greater_object: Objects and Content at this number or higher are to have delimits applied.
 *   - content_lesser:         Content at this number or lower are to have delimits applied.
 *   - content_lesser_object:  Objects and Content at this number or lower are to have delimits applied.
 *   - content_object:         Objects and Content are to have delimits applied
 *   - object:                 Objects arre to have delimits applied.
 */
#ifndef _di_fss_basic_list_read_delimit_mode_
  #define fss_basic_list_read_delimit_mode_name_none    "none"
  #define fss_basic_list_read_delimit_mode_name_all     "all"
  #define fss_basic_list_read_delimit_mode_name_object  "object"
  #define fss_basic_list_read_delimit_mode_name_greater "+"
  #define fss_basic_list_read_delimit_mode_name_lesser  "-"

  #define fss_basic_list_read_delimit_mode_name_none_length    4
  #define fss_basic_list_read_delimit_mode_name_all_length     3
  #define fss_basic_list_read_delimit_mode_name_object_length  6
  #define fss_basic_list_read_delimit_mode_name_greater_length 1
  #define fss_basic_list_read_delimit_mode_name_lesser_length  1

  enum {
    fss_basic_list_read_delimit_mode_none = 1,
    fss_basic_list_read_delimit_mode_all,
    fss_basic_list_read_delimit_mode_content,
    fss_basic_list_read_delimit_mode_content_greater,
    fss_basic_list_read_delimit_mode_content_greater_object,
    fss_basic_list_read_delimit_mode_content_lesser,
    fss_basic_list_read_delimit_mode_content_lesser_object,
    fss_basic_list_read_delimit_mode_content_object,
    fss_basic_list_read_delimit_mode_object,
  };
#endif // _di_fss_basic_list_read_delimit_modes_

#ifndef _di_fss_basic_list_read_main_t_
  typedef struct {
    f_console_parameter_t parameters[fss_basic_list_read_total_parameters];

    f_array_lengths_t remaining;
    bool process_pipe;

    f_file_t output;
    fll_error_print_t error;
    fll_error_print_t warning;

    f_color_context_t context;
  } fss_basic_list_read_main_t;

  #define fss_basic_list_read_main_t_initialize \
    { \
      fss_basic_list_read_console_parameter_t_initialize, \
      f_array_lengths_t_initialize, \
      F_false, \
      macro_f_file_t_initialize2(f_type_output, f_type_descriptor_output, f_file_flag_write_only), \
      fll_error_print_t_initialize, \
      macro_fll_error_print_t_initialize_warning(), \
      f_color_context_t_initialize, \
    }
#endif // _di_fss_basic_list_read_main_t_

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
#ifndef _di_fss_basic_list_read_print_help_
  extern f_status_t fss_basic_list_read_print_help(const f_file_t output, const f_color_context_t context);
#endif // _di_fss_basic_list_read_print_help_

/**
 * Execute main program.
 *
 * Be sure to call fss_basic_list_read_main_delete() after executing this.
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
 * @see fss_basic_list_read_main_delete()
 */
#ifndef _di_fss_basic_list_read_main_
  extern f_status_t fss_basic_list_read_main(f_console_arguments_t * const arguments, fss_basic_list_read_main_t *main);
#endif // _di_fss_basic_list_read_main_

/**
 * Deallocate main.
 *
 * Be sure to call this after executing fss_basic_list_read_main().
 *
 * @param main
 *   The main data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fss_basic_list_read_main()
 */
#ifndef _di_fss_basic_list_read_main_delete_
  extern f_status_t fss_basic_list_read_main_delete(fss_basic_list_read_main_t *main);
#endif // _di_fss_basic_list_read_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_basic_list_read_h
