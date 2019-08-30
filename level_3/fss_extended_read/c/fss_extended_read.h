/**
 * FLL - Level 3
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This is the FSS Basic Read program
 * This program utilizes the Featureless Linux Library.
 * This program processes files or other input in fss format and stores the results in the fss_extended_read_data.
 */
#ifndef _fss_extended_read_h

// libc includes
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// fll-0 includes
#include <level_0/console.h>
#include <level_0/file.h>
#include <level_0/pipe.h>
#include <level_0/print.h>
#include <level_0/strings.h>
#include <level_0/types.h>

// fll-1 includes
#include <level_1/colors.h>
#include <level_1/console.h>
#include <level_1/directory.h>
#include <level_1/file.h>
#include <level_1/program.h>
#include <level_1/strings.h>

// fll-2 includes
#include <level_2/colors.h>
#include <level_2/execute.h>
#include <level_2/fss_extended.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_extended_read_version_
  #define fss_extended_read_major_version "0"
  #define fss_extended_read_minor_version "5"
  #define fss_extended_read_micro_version "0"
  #define fss_extended_read_version fss_extended_read_major_version "." fss_extended_read_minor_version "." fss_extended_read_micro_version
#endif // _di_fss_extended_read_version_

#ifndef _di_fss_extended_read_name_
  #define fss_extended_read_name "fss_extended_read"
  #define fss_extended_read_name_long "FSS Extended Read"
#endif // _di_fss_extended_read_name_

#ifndef _di_fss_extended_read_defines_
  #define fss_extended_read_short_name   "n"
  #define fss_extended_read_short_count  "c"
  #define fss_extended_read_short_total  "t"
  #define fss_extended_read_short_object "o"
  #define fss_extended_read_short_select "s"

  #define fss_extended_read_long_name   "name"
  #define fss_extended_read_long_count  "count"
  #define fss_extended_read_long_total  "total"
  #define fss_extended_read_long_object "object"
  #define fss_extended_read_long_select "select"

  enum {
    fss_extended_read_parameter_help,
    fss_extended_read_parameter_light,
    fss_extended_read_parameter_no_color,
    fss_extended_read_parameter_version,

    fss_extended_read_parameter_name,
    fss_extended_read_parameter_count,
    fss_extended_read_parameter_total,
    fss_extended_read_parameter_object,
    fss_extended_read_parameter_select,
  };

  #define f_console_parameter_initialize_fss_extended_read \
    { \
      f_console_parameter_initialize(f_console_standard_short_help, f_console_standard_long_help, 0, f_false, f_console_type_normal), \
      f_console_parameter_initialize(f_console_standard_short_light, f_console_standard_long_light, 0, f_false, f_console_type_inverse), \
      f_console_parameter_initialize(f_console_standard_short_no_color, f_console_standard_long_no_color, 0, f_false, f_console_type_inverse), \
      f_console_parameter_initialize(f_console_standard_short_version, f_console_standard_long_version, 0, f_false, f_console_type_inverse), \
      f_console_parameter_initialize(fss_extended_read_short_name, fss_extended_read_long_name, 0, f_true, f_console_type_normal), \
      f_console_parameter_initialize(fss_extended_read_short_count, fss_extended_read_long_count, 0, f_true, f_console_type_normal), \
      f_console_parameter_initialize(fss_extended_read_short_total, fss_extended_read_long_total, 0, f_false, f_console_type_normal), \
      f_console_parameter_initialize(fss_extended_read_short_object, fss_extended_read_long_object, 0, f_false, f_console_type_normal), \
      f_console_parameter_initialize(fss_extended_read_short_select, fss_extended_read_long_select, 0, f_true, f_console_type_normal), \
    }

  #define fss_extended_read_total_parameters 9
#endif // _di_fss_extended_read_defines_

#ifndef _di_fss_extended_read_data_
  typedef struct {
    f_console_parameter parameters[fss_extended_read_total_parameters];

    f_dynamic_string buffer;
    f_fss_objects objects;
    f_fss_contents contents;
    f_file_position file_position;
    f_string_lengths remaining;
    f_bool process_pipe;

    fl_color_context context;
  } fss_extended_read_data;

  #define fss_extended_read_data_initialize \
    { \
      f_console_parameter_initialize_fss_extended_read, \
      f_dynamic_string_initialize, \
      f_fss_objects_initialize, \
      f_fss_contents_initialize, \
      f_file_position_initialize, \
      f_string_lengths_initialize, \
      f_false, \
      fl_color_context_initialize, \
    }
#endif // _di_fss_extended_read_data_

#ifndef _di_fss_extended_read_print_help_
  /**
   * Print help.
   */
  extern f_return_status fss_extended_read_print_help(const fss_extended_read_data data);
#endif // _di_fss_extended_read_print_help_

#ifndef _di_fss_extended_read_main_
  /**
   * Main.
   */
  extern f_return_status fss_extended_read_main(const f_array_length argc, const f_string argv[], fss_extended_read_data *data);
#endif // _di_fss_extended_read_main_

#ifndef _di_fss_extended_read_delete_data_
  /**
   * Deallocate data.
   */
  extern f_return_status fss_extended_read_delete_data(fss_extended_read_data *data);
#endif // _di_fss_extended_read_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_extended_read_h
