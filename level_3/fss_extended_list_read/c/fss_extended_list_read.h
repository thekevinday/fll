/**
 * FLL - Level 3
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * This is the FSS Extended List Read program
 * This program utilizes the Featureless Linux Library.
 * This program processes files or other input in fss format and stores the results in the fss_extended_list_read_main_t.
 *
 * This processes in accordance to the FSS-0003 Extended List specification.
 */
#ifndef _fss_extended_list_read_h

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
#include <fll/level_0/signal.h>

// fll-1 includes
#include <fll/level_1/console.h>
#include <fll/level_1/conversion.h>
#include <fll/level_1/print.h>
#include <fll/level_1/string.h>

// fll-2 includes
#include <fll/level_2/error.h>
#include <fll/level_2/file.h>
#include <fll/level_2/fss_extended_list.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_extended_list_read_program_version_
  #define fss_extended_list_read_program_version_major_s F_string_ascii_0_s
  #define fss_extended_list_read_program_version_minor_s F_string_ascii_5_s
  #define fss_extended_list_read_program_version_micro_s F_string_ascii_7_s

  #ifndef fss_extended_list_read_version_nano_prefix_s
    #define fss_extended_list_read_version_nano_prefix_s
  #endif

  #ifndef fss_extended_list_read_version_nano_s
    #define fss_extended_list_read_version_nano_s
  #endif

  #define fss_extended_list_read_program_version_s fss_extended_list_read_program_version_major_s F_string_ascii_period_s fss_extended_list_read_program_version_minor_s F_string_ascii_period_s fss_extended_list_read_program_version_micro_s fss_extended_list_read_version_nano_prefix_s fss_extended_list_read_version_nano_s
#endif // _di_fss_extended_list_read_program_version_

#ifndef _di_fss_extended_list_read_program_name_
  #define fss_extended_list_read_program_name_s      "fss_extended_list_read"
  #define fss_extended_list_read_program_name_long_s "FSS Extended List Read"
#endif // _di_fss_extended_list_read_program_name_

#ifndef _di_fss_extended_list_read_defines_
  #define fss_extended_list_read_signal_check_d 10000

  #define fss_extended_list_read_pipe_content_end    '\f'
  #define fss_extended_list_read_pipe_content_ignore '\v'
  #define fss_extended_list_read_pipe_content_start  '\b'

  #define fss_extended_list_read_short_at_s      "a"
  #define fss_extended_list_read_short_content_s "c"
  #define fss_extended_list_read_short_columns_s "C"
  #define fss_extended_list_read_short_delimit_s "D"
  #define fss_extended_list_read_short_depth_s   "d"
  #define fss_extended_list_read_short_empty_s   "e"
  #define fss_extended_list_read_short_line_s    "l"
  #define fss_extended_list_read_short_name_s    "n"
  #define fss_extended_list_read_short_object_s  "o"
  #define fss_extended_list_read_short_pipe_s    "p"
  #define fss_extended_list_read_short_raw_s     "R"
  #define fss_extended_list_read_short_select_s  "s"
  #define fss_extended_list_read_short_total_s   "t"
  #define fss_extended_list_read_short_trim_s    "T"

  #define fss_extended_list_read_long_at_s      "at"
  #define fss_extended_list_read_long_content_s "content"
  #define fss_extended_list_read_long_columns_s "columns"
  #define fss_extended_list_read_long_delimit_s "delimit"
  #define fss_extended_list_read_long_depth_s   "depth"
  #define fss_extended_list_read_long_empty_s   "empty"
  #define fss_extended_list_read_long_line_s    "line"
  #define fss_extended_list_read_long_name_s    "name"
  #define fss_extended_list_read_long_object_s  "object"
  #define fss_extended_list_read_long_pipe_s    "pipe"
  #define fss_extended_list_read_long_raw_s     "raw"
  #define fss_extended_list_read_long_select_s  "select"
  #define fss_extended_list_read_long_total_s   "total"
  #define fss_extended_list_read_long_trim_s    "trim"

  enum {
    fss_extended_list_read_parameter_help,
    fss_extended_list_read_parameter_light,
    fss_extended_list_read_parameter_dark,
    fss_extended_list_read_parameter_no_color,
    fss_extended_list_read_parameter_verbosity_quiet,
    fss_extended_list_read_parameter_verbosity_normal,
    fss_extended_list_read_parameter_verbosity_verbose,
    fss_extended_list_read_parameter_verbosity_debug,
    fss_extended_list_read_parameter_version,

    fss_extended_list_read_parameter_at,
    fss_extended_list_read_parameter_content,
    fss_extended_list_read_parameter_columns,
    fss_extended_list_read_parameter_delimit,
    fss_extended_list_read_parameter_depth,
    fss_extended_list_read_parameter_empty,
    fss_extended_list_read_parameter_line,
    fss_extended_list_read_parameter_name,
    fss_extended_list_read_parameter_object,
    fss_extended_list_read_parameter_pipe,
    fss_extended_list_read_parameter_raw,
    fss_extended_list_read_parameter_select,
    fss_extended_list_read_parameter_total,
    fss_extended_list_read_parameter_trim,
  };

  #define fss_extended_list_read_console_parameter_t_initialize \
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
      f_console_parameter_t_initialize(fss_extended_list_read_short_at_s, fss_extended_list_read_long_at_s, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_extended_list_read_short_content_s, fss_extended_list_read_long_content_s, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_extended_list_read_short_columns_s, fss_extended_list_read_long_columns_s, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_extended_list_read_short_delimit_s, fss_extended_list_read_long_delimit_s, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_extended_list_read_short_depth_s, fss_extended_list_read_long_depth_s, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_extended_list_read_short_empty_s, fss_extended_list_read_long_empty_s, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_extended_list_read_short_line_s, fss_extended_list_read_long_line_s, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_extended_list_read_short_name_s, fss_extended_list_read_long_name_s, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_extended_list_read_short_object_s, fss_extended_list_read_long_object_s, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_extended_list_read_short_pipe_s, fss_extended_list_read_long_pipe_s, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_extended_list_read_short_raw_s, fss_extended_list_read_long_raw_s, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_extended_list_read_short_select_s, fss_extended_list_read_long_select_s, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_extended_list_read_short_total_s, fss_extended_list_read_long_total_s, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_extended_list_read_short_trim_s, fss_extended_list_read_long_trim_s, 0, 0, f_console_type_normal), \
    }

  #define fss_extended_list_read_total_parameters_d 23
#endif // _di_fss_extended_list_read_defines_

/**
 * FSS Delimit Parameter data.
 *
 * fss_extended_list_read_delimit_mode_*:
 *   - all:                    All delimits are to be aplied.
 *   - content:                Content are to have delimits applied.
 *   - content_greater:        Content at this number or higher are to have delimits applied.
 *   - content_greater_object: Objects and Content at this number or higher are to have delimits applied.
 *   - content_lesser:         Content at this number or lower are to have delimits applied.
 *   - content_lesser_object:  Objects and Content at this number or lower are to have delimits applied.
 *   - content_object:         Objects and Content are to have delimits applied
 *   - object:                 Objects arre to have delimits applied.
 */
#ifndef _di_fss_extended_list_read_delimit_mode_
  #define fss_extended_list_read_delimit_mode_name_none_s    "none"
  #define fss_extended_list_read_delimit_mode_name_all_s     "all"
  #define fss_extended_list_read_delimit_mode_name_object_s  "object"
  #define fss_extended_list_read_delimit_mode_name_greater_s "+"
  #define fss_extended_list_read_delimit_mode_name_lesser_s  "-"

  #define fss_extended_list_read_delimit_mode_name_none_s_length    4
  #define fss_extended_list_read_delimit_mode_name_all_s_length     3
  #define fss_extended_list_read_delimit_mode_name_object_s_length  6
  #define fss_extended_list_read_delimit_mode_name_greater_s_length 1
  #define fss_extended_list_read_delimit_mode_name_lesser_s_length  1

  enum {
    fss_extended_list_read_delimit_mode_none = 1,
    fss_extended_list_read_delimit_mode_all,
    fss_extended_list_read_delimit_mode_content,
    fss_extended_list_read_delimit_mode_content_greater,
    fss_extended_list_read_delimit_mode_content_greater_object,
    fss_extended_list_read_delimit_mode_content_lesser,
    fss_extended_list_read_delimit_mode_content_lesser_object,
    fss_extended_list_read_delimit_mode_content_object,
    fss_extended_list_read_delimit_mode_object,
  };
#endif // _di_fss_extended_list_read_delimit_modes_

#ifndef _di_fss_extended_list_read_main_t_
  typedef struct {
    f_console_parameter_t parameters[fss_extended_list_read_total_parameters_d];

    f_array_lengths_t remaining;
    bool process_pipe;

    fl_print_t output;
    fl_print_t error;
    fl_print_t warning;

    f_signal_t signal;

    f_color_context_t context;
  } fss_extended_list_read_main_t;

  #define fss_extended_list_read_main_t_initialize \
    { \
      fss_extended_list_read_console_parameter_t_initialize, \
      f_array_lengths_t_initialize, \
      F_false, \
      fl_print_t_initialize, \
      macro_fl_print_t_initialize_error(), \
      macro_fl_print_t_initialize_warning(), \
      f_signal_t_initialize, \
      f_color_context_t_initialize, \
    }
#endif // _di_fss_extended_list_read_main_t_

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
#ifndef _di_fss_extended_list_read_print_help_
  extern f_status_t fss_extended_list_read_print_help(const f_file_t file, const f_color_context_t context);
#endif // _di_fss_extended_list_read_print_help_

/**
 * Execute main program.
 *
 * Be sure to call fss_extended_list_read_main_delete() after executing this.
 *
 * If main.signal is non-zero, then this blocks and handles the following signals:
 * - F_signal_abort
 * - F_signal_broken_pipe
 * - F_signal_hangup
 * - F_signal_interrupt
 * - F_signal_quit
 * - F_signal_termination
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
 * @see fss_extended_list_read_main_delete()
 */
#ifndef _di_fss_extended_list_read_main_
  extern f_status_t fss_extended_list_read_main(fss_extended_list_read_main_t * const main, const f_console_arguments_t *arguments);
#endif // _di_fss_extended_list_read_main_

/**
 * Deallocate main.
 *
 * Be sure to call this after executing fss_extended_list_read_main().
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fss_extended_list_read_main()
 */
#ifndef _di_fss_extended_list_read_main_delete_
  extern f_status_t fss_extended_list_read_main_delete(fss_extended_list_read_main_t *main);
#endif // _di_fss_extended_list_read_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_extended_list_read_h
