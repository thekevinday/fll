/**
 * FLL - Level 3
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This program provides fss basic write functionality.
 */
#ifndef _fss_extended_write_h

// libc includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// fll-0 includes
#include <level_0/console.h>
#include <level_0/pipe.h>
#include <level_0/print.h>
#include <level_0/string.h>
#include <level_0/type.h>

// fll-1 includes
#include <level_1/color.h>
#include <level_1/status.h>
#include <level_1/file.h>
#include <level_1/fss_extended.h>
#include <level_1/string.h>

// fll-2 includes
#include <level_2/fss_status.h>
#include <level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_extended_write_version_
  #define fss_extended_write_major_version "0"
  #define fss_extended_write_minor_version "5"
  #define fss_extended_write_micro_version "0"
  #define fss_extended_write_version fss_extended_write_major_version "." fss_extended_write_minor_version "." fss_extended_write_micro_version
#endif // _di_fss_extended_write_version_

#ifndef _di_fss_extended_write_name_
  #define fss_extended_write_name      "fss_extended_write"
  #define fss_extended_write_name_long "FSS Extended Write"
#endif // _di_fss_extended_write_name_

#ifndef _di_fss_extended_write_defines_
  #define fss_extended_write_short_object  "o"
  #define fss_extended_write_short_file    "f"
  #define fss_extended_write_short_string  "s"
  #define fss_extended_write_short_partial "p"

  #define fss_extended_write_long_object  "object"
  #define fss_extended_write_long_file    "file"
  #define fss_extended_write_long_string  "string"
  #define fss_extended_write_long_partial "partial"

  enum {
    fss_extended_write_parameter_help,
    fss_extended_write_parameter_light,
    fss_extended_write_parameter_dark,
    fss_extended_write_parameter_no_color,
    fss_extended_write_parameter_version,

    fss_extended_write_parameter_object,
    fss_extended_write_parameter_file,
    fss_extended_write_parameter_string,
    fss_extended_write_parameter_partial,
  };

  #define f_console_parameter_initialize_fss_extended_write \
    { \
      f_console_parameter_initialize(f_console_standard_short_help, f_console_standard_long_help, 0, f_false, f_console_type_normal), \
      f_console_parameter_initialize(f_console_standard_short_light, f_console_standard_long_light, 0, f_false, f_console_type_inverse), \
      f_console_parameter_initialize(f_console_standard_short_dark, f_console_standard_long_dark, 0, f_false, f_console_type_inverse), \
      f_console_parameter_initialize(f_console_standard_short_no_color, f_console_standard_long_no_color, 0, f_false, f_console_type_inverse), \
      f_console_parameter_initialize(f_console_standard_short_version, f_console_standard_long_version, 0, f_false, f_console_type_inverse), \
      f_console_parameter_initialize(fss_extended_write_short_object, fss_extended_write_long_object, 0, f_false, f_console_type_normal), \
      f_console_parameter_initialize(fss_extended_write_short_file, fss_extended_write_long_file, 0, f_true, f_console_type_normal), \
      f_console_parameter_initialize(fss_extended_write_short_string, fss_extended_write_long_string, 0, f_true, f_console_type_normal), \
      f_console_parameter_initialize(fss_extended_write_short_partial, fss_extended_write_long_partial, 0, f_false, f_console_type_normal), \
    }

  #define fss_extended_write_total_parameters 9
#endif // _di_fss_extended_write_defines_

#ifndef _di_fss_extended_write_data_
  typedef struct {
    f_console_parameter parameters[fss_extended_write_total_parameters];

    f_string_lengths remaining;
    bool process_pipe;

    fl_color_context context;
  } fss_extended_write_data;

  #define fss_extended_write_data_initialize \
    { \
      f_console_parameter_initialize_fss_extended_write, \
      f_string_lengths_initialize, \
      f_false, \
      fl_color_context_initialize, \
    }
#endif // _di_fss_extended_write_data_

/**
 * Print help to standard output.
 *
 * @param data
 *   The program data.
 *
 * @return
 *   f_none on success.
 */
#ifndef _di_fss_extended_write_print_help_
  extern f_return_status fss_extended_write_print_help(const fss_extended_write_data data);
#endif // _di_fss_extended_write_print_help_

/**
 * Execute main program.
 *
 * Be sure to call fss_extended_write_delete_data() after executing this.
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
 * @see fss_extended_write_delete_data()
 */
#ifndef _di_fss_extended_write_main_
  extern f_return_status fss_extended_write_main(const f_console_arguments arguments, fss_extended_write_data *data);
#endif // _di_fss_extended_write_main_

/**
 * Deallocate data.
 *
 * Be sure to call this after executing fss_extended_write_main().
 *
 * @param data
 *   The program data.
 *
 * @return
 *   f_none on success.
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fss_extended_write_main()
 */
#ifndef _di_fss_extended_write_delete_data_
  extern f_return_status fss_extended_write_delete_data(fss_extended_write_data *data);
#endif // _di_fss_extended_write_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_extended_write_h
