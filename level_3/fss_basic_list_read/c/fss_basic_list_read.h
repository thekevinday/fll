/**
 * FLL - Level 3
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This is the FSS Basic List Read program
 * This program utilizes the Featureless Linux Library.
 * This program processes files or other input in fss format and stores the results in the fss_basic_list_read_data.
 *
 * This processes in accordance to the FSS-0002 Basic List specification.
 */
#ifndef _fss_basic_list_read_h

// libc includes
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/string.h>
#include <level_0/console.h>
#include <level_0/directory.h>
#include <level_0/file.h>
#include <level_0/pipe.h>
#include <level_0/print.h>

// fll-1 includes
#include <level_1/color.h>
#include <level_1/console.h>
#include <level_1/file.h>
#include <level_1/print.h>
#include <level_1/string.h>

// fll-2 includes
#include <level_2/execute.h>
#include <level_2/file.h>
#include <level_2/fss_basic_list.h>
#include <level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_basic_list_read_version_
  #define fss_basic_list_read_major_version "0"
  #define fss_basic_list_read_minor_version "5"
  #define fss_basic_list_read_micro_version "0"
  #define fss_basic_list_read_version fss_basic_list_read_major_version "." fss_basic_list_read_minor_version "." fss_basic_list_read_micro_version
#endif // _di_fss_basic_list_read_version_

#ifndef _di_fss_basic_list_read_name_
  #define fss_basic_list_read_name      "fss_basic_list_read"
  #define fss_basic_list_read_name_long "FSS Basic List Read"
#endif // _di_fss_basic_list_read_name_

#ifndef _di_fss_basic_list_read_defines_
  #define fss_basic_list_read_short_at     "a"
  #define fss_basic_list_read_short_depth  "d"
  #define fss_basic_list_read_short_empty  "e"
  #define fss_basic_list_read_short_line   "l"
  #define fss_basic_list_read_short_name   "n"
  #define fss_basic_list_read_short_object "o"
  #define fss_basic_list_read_short_select "s"
  #define fss_basic_list_read_short_total  "t"
  #define fss_basic_list_read_short_trim   "T"

  #define fss_basic_list_read_long_at     "at"
  #define fss_basic_list_read_long_depth  "depth"
  #define fss_basic_list_read_long_empty  "empty"
  #define fss_basic_list_read_long_line   "line"
  #define fss_basic_list_read_long_name   "name"
  #define fss_basic_list_read_long_object "object"
  #define fss_basic_list_read_long_select "select"
  #define fss_basic_list_read_long_total  "total"
  #define fss_basic_list_read_long_trim   "trim"

  enum {
    fss_basic_list_read_parameter_help,
    fss_basic_list_read_parameter_light,
    fss_basic_list_read_parameter_dark,
    fss_basic_list_read_parameter_no_color,
    fss_basic_list_read_parameter_version,

    fss_basic_list_read_parameter_at,
    fss_basic_list_read_parameter_depth,
    fss_basic_list_read_parameter_empty,
    fss_basic_list_read_parameter_line,
    fss_basic_list_read_parameter_name,
    fss_basic_list_read_parameter_object,
    fss_basic_list_read_parameter_select,
    fss_basic_list_read_parameter_total,
    fss_basic_list_read_parameter_trim,
  };

  #define f_console_parameter_initialize_fss_basic_list_read \
    { \
      f_console_parameter_initialize(f_console_standard_short_help, f_console_standard_long_help, 0, F_false, f_console_type_normal), \
      f_console_parameter_initialize(f_console_standard_short_light, f_console_standard_long_light, 0, F_false, f_console_type_inverse), \
      f_console_parameter_initialize(f_console_standard_short_dark, f_console_standard_long_dark, 0, F_false, f_console_type_inverse), \
      f_console_parameter_initialize(f_console_standard_short_no_color, f_console_standard_long_no_color, 0, F_false, f_console_type_inverse), \
      f_console_parameter_initialize(f_console_standard_short_version, f_console_standard_long_version, 0, F_false, f_console_type_inverse), \
      f_console_parameter_initialize(fss_basic_list_read_short_at, fss_basic_list_read_long_at, 0, F_true, f_console_type_normal), \
      f_console_parameter_initialize(fss_basic_list_read_short_depth, fss_basic_list_read_long_depth, 0, F_true, f_console_type_normal), \
      f_console_parameter_initialize(fss_basic_list_read_short_empty, fss_basic_list_read_long_empty, 0, F_false, f_console_type_normal), \
      f_console_parameter_initialize(fss_basic_list_read_short_line, fss_basic_list_read_long_line, 0, F_true, f_console_type_normal), \
      f_console_parameter_initialize(fss_basic_list_read_short_name, fss_basic_list_read_long_name, 0, F_true, f_console_type_normal), \
      f_console_parameter_initialize(fss_basic_list_read_short_object, fss_basic_list_read_long_object, 0, F_false, f_console_type_normal), \
      f_console_parameter_initialize(fss_basic_list_read_short_select, fss_basic_list_read_long_select, 0, F_true, f_console_type_normal), \
      f_console_parameter_initialize(fss_basic_list_read_short_total, fss_basic_list_read_long_total, 0, F_false, f_console_type_normal), \
      f_console_parameter_initialize(fss_basic_list_read_short_trim, fss_basic_list_read_long_trim, 0, F_false, f_console_type_normal), \
    }

  #define fss_basic_list_read_total_parameters 14
#endif // _di_fss_basic_list_read_defines_

#ifndef _di_fss_basic_list_read_data_
  typedef struct {
    f_console_parameter parameters[fss_basic_list_read_total_parameters];

    f_string_dynamic buffer;
    f_fss_objects objects;
    f_fss_contents contents;
    f_string_quantity quantity;
    f_string_lengths remaining;
    bool process_pipe;

    fl_color_context context;
  } fss_basic_list_read_data;

  #define fss_basic_list_read_data_initialize \
    { \
      f_console_parameter_initialize_fss_basic_list_read, \
      f_string_dynamic_initialize, \
      f_fss_objects_initialize, \
      f_fss_contents_initialize, \
      f_string_quantity_initialize, \
      f_string_lengths_initialize, \
      F_false, \
      fl_color_context_initialize, \
    }
#endif // _di_fss_basic_list_read_data_

/**
 * Print help to standard output.
 *
 * @param context
 *   The color context settings.
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_fss_basic_list_read_print_help_
  extern f_return_status fss_basic_list_read_print_help(const fl_color_context context);
#endif // _di_fss_basic_list_read_print_help_

/**
 * Execute main program.
 *
 * Be sure to call fss_basic_list_read_delete_data() after executing this.
 *
 * @param arguments
 *   The parameters passed to the process.
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fss_basic_list_read_delete_data()
 */
#ifndef _di_fss_basic_list_read_main_
  extern f_return_status fss_basic_list_read_main(const f_console_arguments arguments, fss_basic_list_read_data *data);
#endif // _di_fss_basic_list_read_main_

/**
 * Deallocate data.
 *
 * Be sure to call this after executing fss_basic_list_read_main().
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fss_basic_list_read_main()
 */
#ifndef _di_fss_basic_list_read_delete_data_
  extern f_return_status fss_basic_list_read_delete_data(fss_basic_list_read_data *data);
#endif // _di_fss_basic_list_read_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_basic_list_read_h
