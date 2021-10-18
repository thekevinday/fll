/**
 * FLL - Level 3
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This program provides FSS-0003 Extended List write functionality.
 */
#ifndef _fss_extended_list_write_h

// libc includes
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
#include <fll/level_0/file.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>

// fll-1 includes
#include <fll/level_1/console.h>
#include <fll/level_1/conversion.h>
#include <fll/level_1/fss_extended_list.h>
#include <fll/level_1/print.h>
#include <fll/level_1/status.h>
#include <fll/level_1/string.h>

// fll-2 includes
#include <fll/level_2/error.h>
#include <fll/level_2/fss_status.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_extended_list_write_program_version_
  #define fss_extended_list_write_program_version_major_s F_string_ascii_0_s
  #define fss_extended_list_write_program_version_minor_s F_string_ascii_5_s
  #define fss_extended_list_write_program_version_micro_s F_string_ascii_6_s

  #ifndef fss_extended_list_write_program_version_nano_prefix_s
    #define fss_extended_list_write_program_version_nano_prefix_s
  #endif

  #ifndef fss_extended_list_write_program_version_nano_s
    #define fss_extended_list_write_program_version_nano_s
  #endif

  #define fss_extended_list_write_program_version_s fss_extended_list_write_program_version_major_s F_string_ascii_period_s fss_extended_list_write_program_version_minor_s F_string_ascii_period_s fss_extended_list_write_program_version_micro_s fss_extended_list_write_program_version_nano_prefix_s fss_extended_list_write_program_version_nano_s
#endif // _di_fss_extended_list_write_program_version_

#ifndef _di_fss_extended_list_write_program_name_
  #define fss_extended_list_write_program_name_s      "fss_extended_list_write"
  #define fss_extended_list_write_program_name_long_s "FSS Extended List Write"
#endif // _di_fss_extended_list_write_program_name_

#ifndef _di_fss_extended_list_write_defines_
  #define fss_extended_list_write_pipe_content_end_s    '\f'
  #define fss_extended_list_write_pipe_content_ignore_s '\v'
  #define fss_extended_list_write_pipe_content_start_s  '\b'

  #define fss_extended_list_write_short_file_s    "f"
  #define fss_extended_list_write_short_content_s "c"
  #define fss_extended_list_write_short_double_s  "d"
  #define fss_extended_list_write_short_ignore_s  "I"
  #define fss_extended_list_write_short_object_s  "o"
  #define fss_extended_list_write_short_partial_s "p"
  #define fss_extended_list_write_short_prepend_s "P"
  #define fss_extended_list_write_short_single_s  "s"
  #define fss_extended_list_write_short_trim_s    "T"

  #define fss_extended_list_write_long_file_s    "file"
  #define fss_extended_list_write_long_content_s "content"
  #define fss_extended_list_write_long_double_s  "double"
  #define fss_extended_list_write_long_ignore_s  "ignore"
  #define fss_extended_list_write_long_object_s  "object"
  #define fss_extended_list_write_long_partial_s "partial"
  #define fss_extended_list_write_long_prepend_s "prepend"
  #define fss_extended_list_write_long_single_s  "single"
  #define fss_extended_list_write_long_trim_s    "trim"

  enum {
    fss_extended_list_write_parameter_help,
    fss_extended_list_write_parameter_light,
    fss_extended_list_write_parameter_dark,
    fss_extended_list_write_parameter_no_color,
    fss_extended_list_write_parameter_verbosity_quiet,
    fss_extended_list_write_parameter_verbosity_normal,
    fss_extended_list_write_parameter_verbosity_verbose,
    fss_extended_list_write_parameter_verbosity_debug,
    fss_extended_list_write_parameter_version,

    fss_extended_list_write_parameter_file,
    fss_extended_list_write_parameter_content,
    fss_extended_list_write_parameter_double,
    fss_extended_list_write_parameter_ignore,
    fss_extended_list_write_parameter_object,
    fss_extended_list_write_parameter_partial,
    fss_extended_list_write_parameter_prepend,
    fss_extended_list_write_parameter_single,
    fss_extended_list_write_parameter_trim,
  };

  #define fss_extended_list_write_console_parameter_t_initialize \
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
      f_console_parameter_t_initialize(fss_extended_list_write_short_file_s, fss_extended_list_write_long_file_s, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_extended_list_write_short_content_s, fss_extended_list_write_long_content_s, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_extended_list_write_short_double_s, fss_extended_list_write_long_double_s, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_extended_list_write_short_ignore_s, fss_extended_list_write_long_ignore_s, 0, 2, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_extended_list_write_short_object_s, fss_extended_list_write_long_object_s, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_extended_list_write_short_partial_s, fss_extended_list_write_long_partial_s, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_extended_list_write_short_prepend_s, fss_extended_list_write_long_prepend_s, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_extended_list_write_short_single_s, fss_extended_list_write_long_single_s, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_extended_list_write_short_trim_s, fss_extended_list_write_long_trim_s, 0, 0, f_console_type_normal), \
    }

  #define fss_extended_list_write_total_parameters_d 18
#endif // _di_fss_extended_list_write_defines_

#ifndef _di_fss_extended_list_write_main_t_
  typedef struct {
    f_console_parameter_t parameters[fss_extended_list_write_total_parameters_d];

    f_array_lengths_t remaining;
    bool process_pipe;

    fl_print_t output;
    fl_print_t error;
    fl_print_t warning;

    f_string_static_t prepend;

    f_color_context_t context;
  } fss_extended_list_write_main_t;

  #define fss_extended_list_write_main_t_initialize \
    { \
      fss_extended_list_write_console_parameter_t_initialize, \
      f_array_lengths_t_initialize, \
      F_false, \
      fl_print_t_initialize, \
      macro_fl_print_t_initialize_error(), \
      macro_fl_print_t_initialize_warning(), \
      f_string_static_t_initialize, \
      f_color_context_t_initialize, \
    }
#endif // _di_fss_extended_list_write_main_t_

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
#ifndef _di_fss_extended_list_write_print_help_
  extern f_status_t fss_extended_list_write_print_help(const f_file_t file, const f_color_context_t context);
#endif // _di_fss_extended_list_write_print_help_

/**
 * Execute main program.
 *
 * Be sure to call fss_extended_list_write_main_delete() after executing this.
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
 * @see fss_extended_list_write_main_delete()
 */
#ifndef _di_fss_extended_list_write_main_
  extern f_status_t fss_extended_list_write_main(const f_console_arguments_t arguments, fss_extended_list_write_main_t *main);
#endif // _di_fss_extended_list_write_main_

/**
 * Deallocate main.
 *
 * Be sure to call this after executing fss_extended_list_write_main().
 *
 * @param main
 *   The main data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fss_extended_list_write_main()
 */
#ifndef _di_fss_extended_list_write_main_delete_
  extern f_status_t fss_extended_list_write_main_delete(fss_extended_list_write_main_t *main);
#endif // _di_fss_extended_list_write_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_extended_list_write_h
