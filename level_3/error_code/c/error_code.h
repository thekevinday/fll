/* FLL - Level 3
 * Project:       FSS
 * Version:       0.3.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * This program provides error code to string translation.
 */
#ifndef _error_code_h

// libc includes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// fll-0 includes
#include <level_0/types.h>
#include <level_0/strings.h>
#include <level_0/console.h>
#include <level_0/output.h>
#include <level_0/pipe.h>

// fll-1 includes
#include <level_1/colors.h>
#include <level_1/console.h>
#include <level_1/strings.h>
#include <level_1/errors.h>

// fll-2 includes
#include <level_2/colors.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_error_code_version_
  #define error_code_major_version "0"
  #define error_code_minor_version "3"
  #define error_code_micro_version "0"
  #define error_code_version error_code_major_version "." error_code_minor_version "." error_code_micro_version
#endif // _di_error_code_version_

#ifndef _di_error_code_name_
  #define error_code_name "error_code"
  #define error_code_name_long "Error Code"
#endif // _di_error_code_name_

#ifndef _di_error_code_defines_
  enum {
    error_code_parameter_help,
    error_code_parameter_light,
    error_code_parameter_no_color,
    error_code_parameter_version,
  };

  #define f_console_parameter_initialize_error_code \
    { \
      f_console_parameter_initialize(f_console_standard_short_help, f_console_standard_long_help, 0, 0, f_false, f_console_type_normal, 0), \
      f_console_parameter_initialize(f_console_standard_short_light, f_console_standard_long_light, 0, 0, f_false, f_console_type_inverse, 0), \
      f_console_parameter_initialize(f_console_standard_short_no_color, f_console_standard_long_no_color, 0, 0, f_false, f_console_type_inverse, 0), \
      f_console_parameter_initialize(f_console_standard_short_version, f_console_standard_long_version, 0, 0, f_false, f_console_type_normal, 0), \
    }

  #define error_code_total_parameters 4
#endif // _di_error_code_defines_

#ifndef _di_error_code_data_
  typedef struct {
    f_console_parameter parameters[error_code_total_parameters];

    f_string_lengths remaining;
    f_bool           process_pipe;

    fll_color_context context;
  } error_code_data;

  #define error_code_data_initialize \
    { \
      f_console_parameter_initialize_error_code, \
      f_string_lengths_initialize, \
      f_false, \
      fll_color_context_initialize, \
    }
#endif // _di_error_code_data_

#ifndef _di_error_code_print_version_
  extern f_return_status error_code_print_version(const error_code_data data);
#endif // _di_error_code_print_version_

#ifndef _di_error_code_print_help_
  extern f_return_status error_code_print_help(const error_code_data data);
#endif // _di_error_code_print_help_

#ifndef _di_error_code_main_
  extern f_return_status error_code_main(const f_array_length argc, const f_string argv[], error_code_data *data);
#endif // _di_error_code_main_

#ifndef _di_error_code_delete_data_
  extern f_return_status error_code_delete_data(error_code_data *data);
#endif // _di_error_code_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _error_code_h
