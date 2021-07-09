/**
 * FLL - Level 3
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This program provides fss basic list write functionality.
 */
#ifndef _fss_basic_list_write_h

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
#include <fll/level_1/fss_basic_list.h>
#include <fll/level_1/status.h>
#include <fll/level_1/string.h>

// fll-2 includes
#include <fll/level_2/error.h>
#include <fll/level_2/fss_status.h>
#include <fll/level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_basic_list_write_version_
  #define fss_basic_list_write_major_version f_string_ascii_0
  #define fss_basic_list_write_minor_version f_string_ascii_5
  #define fss_basic_list_write_micro_version f_string_ascii_4

  #ifndef fss_basic_list_write_nano_version_prefix
    #define fss_basic_list_write_nano_version_prefix
  #endif

  #ifndef fss_basic_list_write_nano_version
    #define fss_basic_list_write_nano_version
  #endif

  #define fss_basic_list_write_version fss_basic_list_write_major_version f_string_ascii_period fss_basic_list_write_minor_version f_string_ascii_period fss_basic_list_write_micro_version fss_basic_list_write_nano_version_prefix fss_basic_list_write_nano_version
#endif // _di_fss_basic_list_write_version_

#ifndef _di_fss_basic_list_write_name_
  #define fss_basic_list_write_name      "fss_basic_list_write"
  #define fss_basic_list_write_name_long "FSS Basic List Write"
#endif // _di_fss_basic_list_write_name_

#ifndef _di_fss_basic_list_write_defines_
  #define fss_basic_list_write_pipe_content_end    '\f'
  #define fss_basic_list_write_pipe_content_ignore '\v'
  #define fss_basic_list_write_pipe_content_start  '\b'

  #define fss_basic_list_write_short_file    "f"
  #define fss_basic_list_write_short_content "c"
  #define fss_basic_list_write_short_double  "d"
  #define fss_basic_list_write_short_ignore  "I"
  #define fss_basic_list_write_short_object  "o"
  #define fss_basic_list_write_short_partial "p"
  #define fss_basic_list_write_short_prepend "P"
  #define fss_basic_list_write_short_single  "s"
  #define fss_basic_list_write_short_trim    "T"

  #define fss_basic_list_write_long_file    "file"
  #define fss_basic_list_write_long_content "content"
  #define fss_basic_list_write_long_double  "double"
  #define fss_basic_list_write_long_ignore  "ignore"
  #define fss_basic_list_write_long_object  "object"
  #define fss_basic_list_write_long_partial "partial"
  #define fss_basic_list_write_long_prepend "prepend"
  #define fss_basic_list_write_long_single  "single"
  #define fss_basic_list_write_long_trim    "trim"

  enum {
    fss_basic_list_write_parameter_help,
    fss_basic_list_write_parameter_light,
    fss_basic_list_write_parameter_dark,
    fss_basic_list_write_parameter_no_color,
    fss_basic_list_write_parameter_verbosity_quiet,
    fss_basic_list_write_parameter_verbosity_normal,
    fss_basic_list_write_parameter_verbosity_verbose,
    fss_basic_list_write_parameter_verbosity_debug,
    fss_basic_list_write_parameter_version,

    fss_basic_list_write_parameter_file,
    fss_basic_list_write_parameter_content,
    fss_basic_list_write_parameter_double,
    fss_basic_list_write_parameter_ignore,
    fss_basic_list_write_parameter_object,
    fss_basic_list_write_parameter_partial,
    fss_basic_list_write_parameter_prepend,
    fss_basic_list_write_parameter_single,
    fss_basic_list_write_parameter_trim,
  };

  #define fss_basic_list_write_console_parameter_t_initialize \
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
      f_console_parameter_t_initialize(fss_basic_list_write_short_file, fss_basic_list_write_long_file, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_basic_list_write_short_content, fss_basic_list_write_long_content, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_basic_list_write_short_double, fss_basic_list_write_long_double, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_basic_list_write_short_ignore, fss_basic_list_write_long_ignore, 0, 2, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_basic_list_write_short_object, fss_basic_list_write_long_object, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_basic_list_write_short_partial, fss_basic_list_write_long_partial, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_basic_list_write_short_prepend, fss_basic_list_write_long_prepend, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_basic_list_write_short_single, fss_basic_list_write_long_single, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_basic_list_write_short_trim, fss_basic_list_write_long_trim, 0, 0, f_console_type_normal), \
    }

  #define fss_basic_list_write_total_parameters 18
#endif // _di_fss_basic_list_write_defines_

#ifndef _di_fss_basic_list_write_main_t_
  typedef struct {
    f_console_parameter_t parameters[fss_basic_list_write_total_parameters];

    f_array_lengths_t remaining;
    bool process_pipe;

    f_file_t output;
    fll_error_print_t error;
    f_string_static_t prepend;

    f_color_context_t context;
  } fss_basic_list_write_main_t;

  #define fss_basic_list_write_main_t_initialize \
    { \
      fss_basic_list_write_console_parameter_t_initialize, \
      f_array_lengths_t_initialize, \
      F_false, \
      macro_f_file_t_initialize2(f_type_output, f_type_descriptor_output, f_file_flag_write_only), \
      fll_error_print_t_initialize, \
      f_string_static_t_initialize, \
      f_color_context_t_initialize, \
    }
#endif // _di_fss_basic_list_write_main_t_

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
#ifndef _di_fss_basic_list_write_print_help_
  extern f_status_t fss_basic_list_write_print_help(const f_file_t output, const f_color_context_t context);
#endif // _di_fss_basic_list_write_print_help_

/**
 * Execute main program.
 *
 * Be sure to call fss_basic_list_write_main_delete() after executing this.
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
 * @see fss_basic_list_write_main_delete()
 */
#ifndef _di_fss_basic_list_write_main_
  extern f_status_t fss_basic_list_write_main(const f_console_arguments_t arguments, fss_basic_list_write_main_t *main);
#endif // _di_fss_basic_list_write_main_

/**
 * Deallocate main.
 *
 * Be sure to call this after executing fss_basic_list_write_main().
 *
 * @param main
 *   The main data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fss_basic_list_write_main()
 */
#ifndef _di_fss_basic_list_write_main_delete_
  extern f_status_t fss_basic_list_write_main_delete(fss_basic_list_write_main_t *main);
#endif // _di_fss_basic_list_write_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_basic_list_write_h
