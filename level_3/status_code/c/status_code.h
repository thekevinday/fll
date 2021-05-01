/**
 * FLL - Level 3
 *
 * Project: Status Code
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This program provides status code to/from string translation.
 */
#ifndef _status_code_h

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
#include <fll/level_0/conversion.h>
#include <fll/level_0/console.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>

// fll-1 includes
#include <fll/level_1/console.h>
#include <fll/level_1/conversion.h>
#include <fll/level_1/status.h>
#include <fll/level_1/string.h>

// fll-2 includes
#include <fll/level_2/error.h>
#include <fll/level_2/program.h>
#include <fll/level_2/status.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_status_code_version_
  #define status_code_major_version "0"
  #define status_code_minor_version "5"
  #define status_code_micro_version "4"
  #define status_code_version status_code_major_version f_string_ascii_period status_code_minor_version f_string_ascii_period status_code_micro_version
#endif // _di_status_code_version_

#ifndef _di_status_code_name_
  #define status_code_name "status_code"
  #define status_code_name_long "FSS Status Code"
#endif // _di_status_code_name_

#ifndef _di_status_code_defines_
  #define status_code_short_is_fine    "f"
  #define status_code_short_is_warning "w"
  #define status_code_short_is_error   "e"
  #define status_code_short_number     "n"

  #define status_code_long_is_fine    "is_fine"
  #define status_code_long_is_warning "is_warning"
  #define status_code_long_is_error   "is_error"
  #define status_code_long_number     "number"

  enum {
    status_code_parameter_help,
    status_code_parameter_light,
    status_code_parameter_dark,
    status_code_parameter_no_color,
    status_code_parameter_verbosity_quiet,
    status_code_parameter_verbosity_normal,
    status_code_parameter_verbosity_verbose,
    status_code_parameter_verbosity_debug,
    status_code_parameter_version,

    status_code_parameter_is_fine,
    status_code_parameter_is_warning,
    status_code_parameter_is_error,
    status_code_parameter_number,
  };

  #define status_code_console_parameter_t_initialize \
    { \
      f_console_parameter_t_initialize(f_console_standard_short_help_s, f_console_standard_long_help_s, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(f_console_standard_short_light_s, f_console_standard_long_light_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_dark_s, f_console_standard_long_dark_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_normal_s, f_console_standard_long_normal_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_debug_s, f_console_standard_long_debug_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_version_s, f_console_standard_long_version_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(status_code_short_is_fine, status_code_long_is_fine, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(status_code_short_is_warning, status_code_long_is_warning, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(status_code_short_is_error, status_code_long_is_error, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(status_code_short_number, status_code_long_number, 0, 0, f_console_type_normal), \
    }

  #define status_code_total_parameters 13
#endif // _di_status_code_defines_

#ifndef _di_status_code_main_t_
  typedef struct {
    f_console_parameter_t parameters[status_code_total_parameters];

    f_array_lengths_t remaining;
    bool process_pipe;

    f_file_t output;
    fll_error_print_t error;

    f_color_context_t context;
  } status_code_main_t;

  #define status_code_main_t_initialize \
    { \
      status_code_console_parameter_t_initialize, \
      f_array_lengths_t_initialize, \
      F_false, \
      f_macro_file_t_initialize2(f_type_output, f_type_descriptor_output, f_file_flag_write_only), \
      fll_error_print_t_initialize, \
      f_color_context_t_initialize, \
    }
#endif // _di_status_code_main_t_

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
#ifndef _di_status_code_print_help_
  extern f_status_t status_code_print_help(const f_file_t output, const f_color_context_t context);
#endif // _di_status_code_print_help_

/**
 * Execute main program.
 *
 * Be sure to call status_code_main_delete() after executing this.
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
 * @see status_code_main_delete()
 */
#ifndef _di_status_code_main_
  extern f_status_t status_code_main(const f_console_arguments_t arguments, status_code_main_t *main);
#endif // _di_status_code_main_

/**
 * Deallocate main.
 *
 * Be sure to call this after executing status_code_main().
 *
 * @param main
 *   The main data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see status_code_main()
 */
#ifndef _di_status_code_main_delete_
  extern f_status_t status_code_main_delete(status_code_main_t *main);
#endif // _di_status_code_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _status_code_h
