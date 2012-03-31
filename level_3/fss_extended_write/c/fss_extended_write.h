/* FLL - Level 3
 * Project:       FSS
 * Version:       0.3.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * This program provides fss basic write functionality.
 */
#ifndef _fss_extended_write_h

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
#include <level_2/fss_errors.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fss_extended_write_version_
  #define fss_extended_write_major_version "0"
  #define fss_extended_write_minor_version "3"
  #define fss_extended_write_micro_version "0"
  #define fss_extended_write_version fss_extended_write_major_version "." fss_extended_write_minor_version "." fss_extended_write_micro_version
#endif // _di_fss_extended_write_version_

#ifndef _di_fss_extended_write_name_
  #define fss_extended_write_name "fss_extended_write"
  #define fss_extended_write_name_long "FSS Extended Write"
#endif // _di_fss_extended_write_name_

#ifndef _di_fss_extended_write_defines_
  #define fss_extended_write_short_type    "t"
  #define fss_extended_write_short_output  "o"
  #define fss_extended_write_short_string  "s"
  #define fss_extended_write_short_partial "p"

  #define fss_extended_write_long_type    "type"
  #define fss_extended_write_long_output  "output"
  #define fss_extended_write_long_string  "string"
  #define fss_extended_write_long_partial "partial"

  enum {
    fss_extended_write_parameter_help,
    fss_extended_write_parameter_light,
    fss_extended_write_parameter_no_color,
    fss_extended_write_parameter_version,

    fss_extended_write_parameter_type,
    fss_extended_write_parameter_output,
    fss_extended_write_parameter_string,
    fss_extended_write_parameter_partial,
  };

  enum {
    fss_extended_write_type_object = 1,
    fss_extended_write_type_content,
  };

  #define f_console_parameter_initialize_fss_extended_write \
    { \
      f_console_parameter_initialize(f_console_standard_short_help, f_console_standard_long_help, 0, 0, f_false, f_console_type_normal, 0), \
      f_console_parameter_initialize(f_console_standard_short_light, f_console_standard_long_light, 0, 0, f_false, f_console_type_inverse, 0), \
      f_console_parameter_initialize(f_console_standard_short_no_color, f_console_standard_long_no_color, 0, 0, f_false, f_console_type_inverse, 0), \
      f_console_parameter_initialize(f_console_standard_short_version, f_console_standard_long_version, 0, 0, f_false, f_console_type_normal, 0), \
      f_console_parameter_initialize(fss_extended_write_short_type, fss_extended_write_long_type, 0, 0, f_true, f_console_type_normal, 0), \
      f_console_parameter_initialize(fss_extended_write_short_output, fss_extended_write_long_output, 0, 0, f_true, f_console_type_normal, 0), \
      f_console_parameter_initialize(fss_extended_write_short_string, fss_extended_write_long_string, 0, 0, f_true, f_console_type_normal, 0), \
      f_console_parameter_initialize(fss_extended_write_short_partial, fss_extended_write_long_partial, 0, 0, f_false, f_console_type_normal, 0), \
    }

  #define fss_extended_write_total_parameters 8
#endif // _di_fss_extended_write_defines_

#ifndef _di_fss_extended_write_data_
  typedef struct {
    f_console_parameter parameters[fss_extended_write_total_parameters];

    f_string_lengths remaining;
    f_bool           process_pipe;

    fll_color_context context;
  } fss_extended_write_data;

  #define fss_extended_write_data_initialize \
    { \
      f_console_parameter_initialize_fss_extended_write, \
      f_string_lengths_initialize, \
      f_false, \
      fll_color_context_initialize, \
    }
#endif // _di_fss_extended_write_data_

#ifndef _di_fss_extended_write_print_version_
  extern f_return_status fss_extended_write_print_version(const fss_extended_write_data data);
#endif // _di_fss_extended_write_print_version_

#ifndef _di_fss_extended_write_print_help_
  extern f_return_status fss_extended_write_print_help(const fss_extended_write_data data);
#endif // _di_fss_extended_write_print_help_

#ifndef _di_fss_extended_write_main_
  extern f_return_status fss_extended_write_main(const f_array_length argc, const f_string argv[], fss_extended_write_data *data);
#endif // _di_fss_extended_write_main_

#ifndef _di_fss_extended_write_delete_data_
  extern f_return_status fss_extended_write_delete_data(fss_extended_write_data *data);
#endif // _di_fss_extended_write_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_extended_write_h
