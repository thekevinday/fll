/* FLL - Level 3
 * Project:       FSS
 * Version:       0.3.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * This program provides error code to string translation.
 */
#ifndef _return_code_h

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

#ifndef _di_return_code_version_
  #define return_code_major_version "0"
  #define return_code_minor_version "3"
  #define return_code_micro_version "0"
  #define return_code_version return_code_major_version "." return_code_minor_version "." return_code_micro_version
#endif // _di_return_code_version_

#ifndef _di_return_code_name_
  #define return_code_name "return_code"
  #define return_code_name_long "Error Code"
#endif // _di_return_code_name_

#ifndef _di_return_code_defines_
  #define return_code_short_is_fine    "f"
  #define return_code_short_is_warning "w"
  #define return_code_short_is_error   "e"
  #define return_code_short_context    "c"

  #define return_code_long_is_fine    "is_fine"
  #define return_code_long_is_warning "is_warning"
  #define return_code_long_is_error   "is_error"
  #define return_code_long_context    "context"

  enum {
    return_code_parameter_help,
    return_code_parameter_light,
    return_code_parameter_no_color,
    return_code_parameter_version,

    return_code_parameter_is_fine,
    return_code_parameter_is_warning,
    return_code_parameter_is_error,
    return_code_parameter_context,
  };

  #define f_console_parameter_initialize_return_code \
    { \
      f_console_parameter_initialize(f_console_standard_short_help, f_console_standard_long_help, 0, 0, f_false, f_console_type_normal, 0), \
      f_console_parameter_initialize(f_console_standard_short_light, f_console_standard_long_light, 0, 0, f_false, f_console_type_inverse, 0), \
      f_console_parameter_initialize(f_console_standard_short_no_color, f_console_standard_long_no_color, 0, 0, f_false, f_console_type_inverse, 0), \
      f_console_parameter_initialize(f_console_standard_short_version, f_console_standard_long_version, 0, 0, f_false, f_console_type_normal, 0), \
      f_console_parameter_initialize(return_code_short_is_fine, return_code_long_is_fine, 0, 0, f_false, f_console_type_normal, 0), \
      f_console_parameter_initialize(return_code_short_is_warning, return_code_long_is_warning, 0, 0, f_false, f_console_type_normal, 0), \
      f_console_parameter_initialize(return_code_short_is_error, return_code_long_is_error, 0, 0, f_false, f_console_type_normal, 0), \
      f_console_parameter_initialize(return_code_short_context, return_code_long_context, 0, 0, f_false, f_console_type_normal, 0), \
    }

  #define return_code_total_parameters 8
#endif // _di_return_code_defines_

#ifndef _di_return_code_data_
  typedef struct {
    f_console_parameter parameters[return_code_total_parameters];

    f_string_lengths remaining;
    f_bool           process_pipe;

    fll_color_context context;
  } return_code_data;

  #define return_code_data_initialize \
    { \
      f_console_parameter_initialize_return_code, \
      f_string_lengths_initialize, \
      f_false, \
      fll_color_context_initialize, \
    }
#endif // _di_return_code_data_

#ifndef _di_return_code_print_version_
  extern f_return_status return_code_print_version(const return_code_data data);
#endif // _di_return_code_print_version_

#ifndef _di_return_code_print_help_
  extern f_return_status return_code_print_help(const return_code_data data);
#endif // _di_return_code_print_help_

#ifndef _di_return_code_main_
  extern f_return_status return_code_main(const f_array_length argc, const f_string argv[], return_code_data *data);
#endif // _di_return_code_main_

#ifndef _di_return_code_delete_data_
  extern f_return_status return_code_delete_data(return_code_data *data);
#endif // _di_return_code_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _return_code_h
