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

// fll-0 includes
#include <level_0/conversion.h>
#include <level_0/console.h>
#include <level_0/pipe.h>
#include <level_0/print.h>
#include <level_0/status.h>
#include <level_0/string.h>
#include <level_0/type.h>

// fll-1 includes
#include <level_1/color.h>
#include <level_1/console.h>
#include <level_1/status.h>
#include <level_1/string.h>

// fll-2 includes
#include <level_2/program.h>
#include <level_2/status.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_status_code_version_
  #define status_code_major_version "0"
  #define status_code_minor_version "5"
  #define status_code_micro_version "0"
  #define status_code_version status_code_major_version "." status_code_minor_version "." status_code_micro_version
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
    status_code_parameter_version,

    status_code_parameter_is_fine,
    status_code_parameter_is_warning,
    status_code_parameter_is_error,
    status_code_parameter_number,
  };

  #define f_console_parameter_initialize_status_code \
    { \
      f_console_parameter_initialize(f_console_standard_short_help, f_console_standard_long_help, 0, f_false, f_console_type_normal), \
      f_console_parameter_initialize(f_console_standard_short_light, f_console_standard_long_light, 0, f_false, f_console_type_inverse), \
      f_console_parameter_initialize(f_console_standard_short_dark, f_console_standard_long_dark, 0, f_false, f_console_type_inverse), \
      f_console_parameter_initialize(f_console_standard_short_no_color, f_console_standard_long_no_color, 0, f_false, f_console_type_inverse), \
      f_console_parameter_initialize(f_console_standard_short_version, f_console_standard_long_version, 0, f_false, f_console_type_inverse), \
      f_console_parameter_initialize(status_code_short_is_fine, status_code_long_is_fine, 0, f_false, f_console_type_normal), \
      f_console_parameter_initialize(status_code_short_is_warning, status_code_long_is_warning, 0, f_false, f_console_type_normal), \
      f_console_parameter_initialize(status_code_short_is_error, status_code_long_is_error, 0, f_false, f_console_type_normal), \
      f_console_parameter_initialize(status_code_short_number, status_code_long_number, 0, f_false, f_console_type_normal), \
    }

  #define status_code_total_parameters 9
#endif // _di_status_code_defines_

#ifndef _di_status_code_data_
  typedef struct {
    f_console_parameter parameters[status_code_total_parameters];

    f_string_lengths remaining;
    bool process_pipe;

    fl_color_context context;
  } status_code_data;

  #define status_code_data_initialize \
    { \
      f_console_parameter_initialize_status_code, \
      f_string_lengths_initialize, \
      f_false, \
      fl_color_context_initialize, \
    }
#endif // _di_status_code_data_

/**
 * Print help to standard output.
 *
 * @param context
 *   The color context settings.
 *
 * @return
 *   f_none on success.
 */
#ifndef _di_status_code_print_help_
  extern f_return_status status_code_print_help(const fl_color_context context);
#endif // _di_status_code_print_help_

/**
 * Execute main program.
 *
 * Be sure to call status_code_delete_data() after executing this.
 *
 * @param arguments
 *   The parameters passed to the process.
 * @param data
 *   The program data.
 *
 * @return
 *   f_none on success.
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see status_code_delete_data()
 */
#ifndef _di_status_code_main_
  extern f_return_status status_code_main(const f_console_arguments arguments, status_code_data *data);
#endif // _di_status_code_main_

/**
 * Deallocate data.
 *
 * Be sure to call this after executing status_code_main().
 *
 * @param data
 *   The program data.
 *
 * @return
 *   f_none on success.
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see status_code_main()
 */
#ifndef _di_status_code_delete_data_
  extern f_return_status status_code_delete_data(status_code_data *data);
#endif // _di_status_code_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _status_code_h
