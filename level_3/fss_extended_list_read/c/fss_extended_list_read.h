/**
 * FLL - Level 3
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This is the FSS Basic List Read program
 * This program utilizes the Featureless Linux Library.
 * This program processes files or other input in fss format and stores the results in the fss_extended_list_read_data_t.
 *
 * This processes in accordance to the FSS-0003 Extended List specification.
 */
#ifndef _fss_extended_list_read_h

// libc includes
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/utf.h>
#include <level_0/console.h>
#include <level_0/directory.h>
#include <level_0/file.h>
#include <level_0/pipe.h>
#include <level_0/print.h>

// fll-1 includes
#include <level_1/color.h>
#include <level_1/console.h>
#include <level_1/conversion.h>
#include <level_1/print.h>
#include <level_1/string.h>

// fll-2 includes
#include <level_2/error.h>
#include <level_2/execute.h>
#include <level_2/file.h>
#include <level_2/fss_extended_list.h>
#include <level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_extended_list_read_version_
  #define fss_extended_list_read_major_version "0"
  #define fss_extended_list_read_minor_version "5"
  #define fss_extended_list_read_micro_version "1"
  #define fss_extended_list_read_version fss_extended_list_read_major_version "." fss_extended_list_read_minor_version "." fss_extended_list_read_micro_version
#endif // _di_fss_extended_list_read_version_

#ifndef _di_fss_extended_list_read_name_
  #define fss_extended_list_read_name      "fss_extended_list_read"
  #define fss_extended_list_read_name_long "FSS Extended List Read"
#endif // _di_fss_extended_list_read_name_

#ifndef _di_fss_extended_list_read_defines_
  #define fss_extended_list_read_short_at     "a"
  #define fss_extended_list_read_short_depth  "d"
  #define fss_extended_list_read_short_empty  "e"
  #define fss_extended_list_read_short_line   "l"
  #define fss_extended_list_read_short_name   "n"
  #define fss_extended_list_read_short_object "o"
  #define fss_extended_list_read_short_select "s"
  #define fss_extended_list_read_short_total  "t"
  #define fss_extended_list_read_short_trim   "T"

  #define fss_extended_list_read_long_at     "at"
  #define fss_extended_list_read_long_depth  "depth"
  #define fss_extended_list_read_long_empty  "empty"
  #define fss_extended_list_read_long_line   "line"
  #define fss_extended_list_read_long_name   "name"
  #define fss_extended_list_read_long_object "object"
  #define fss_extended_list_read_long_select "select"
  #define fss_extended_list_read_long_total  "total"
  #define fss_extended_list_read_long_trim   "trim"

  enum {
    fss_extended_list_read_parameter_help,
    fss_extended_list_read_parameter_light,
    fss_extended_list_read_parameter_dark,
    fss_extended_list_read_parameter_no_color,
    fss_extended_list_read_parameter_verbosity_quiet,
    fss_extended_list_read_parameter_verbosity_normal,
    fss_extended_list_read_parameter_verbosity_verbose,
    fss_extended_list_read_parameter_verbosity_debug,
    fss_extended_list_read_parameter_version,

    fss_extended_list_read_parameter_at,
    fss_extended_list_read_parameter_depth,
    fss_extended_list_read_parameter_empty,
    fss_extended_list_read_parameter_line,
    fss_extended_list_read_parameter_name,
    fss_extended_list_read_parameter_object,
    fss_extended_list_read_parameter_select,
    fss_extended_list_read_parameter_total,
    fss_extended_list_read_parameter_trim,
  };

  #define fss_extended_list_read_console_parameter_t_initialize \
    { \
      f_console_parameter_t_initialize(f_console_standard_short_help, f_console_standard_long_help, 0, F_false, f_console_type_normal), \
      f_console_parameter_t_initialize(f_console_standard_short_light, f_console_standard_long_light, 0, F_false, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_dark, f_console_standard_long_dark, 0, F_false, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_no_color, f_console_standard_long_no_color, 0, F_false, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_quiet, f_console_standard_long_quiet, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_normal, f_console_standard_long_normal, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_verbose, f_console_standard_long_verbose, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_debug, f_console_standard_long_debug, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_version, f_console_standard_long_version, 0, F_false, f_console_type_inverse), \
      f_console_parameter_t_initialize(fss_extended_list_read_short_at, fss_extended_list_read_long_at, 0, F_true, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_extended_list_read_short_depth, fss_extended_list_read_long_depth, 0, F_true, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_extended_list_read_short_empty, fss_extended_list_read_long_empty, 0, F_false, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_extended_list_read_short_line, fss_extended_list_read_long_line, 0, F_true, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_extended_list_read_short_name, fss_extended_list_read_long_name, 0, F_true, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_extended_list_read_short_object, fss_extended_list_read_long_object, 0, F_false, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_extended_list_read_short_select, fss_extended_list_read_long_select, 0, F_true, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_extended_list_read_short_total, fss_extended_list_read_long_total, 0, F_false, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_extended_list_read_short_trim, fss_extended_list_read_long_trim, 0, F_false, f_console_type_normal), \
    }

  #define fss_extended_list_read_total_parameters 18
#endif // _di_fss_extended_list_read_defines_

#ifndef _di_fss_extended_list_read_data_t_
  typedef struct {
    f_console_parameter_t parameters[fss_extended_list_read_total_parameters];

    f_string_lengths_t remaining;
    bool process_pipe;

    f_file_t output;
    fll_error_print_t error;

    f_string_dynamic_t buffer;
    f_fss_nest_t nest;
    f_string_quantity_t quantity;

    f_color_context_t context;
  } fss_extended_list_read_data_t;

  #define fss_extended_list_read_data_t_initialize \
    { \
      fss_extended_list_read_console_parameter_t_initialize, \
      f_string_lengths_t_initialize, \
      F_false, \
      f_macro_file_t_initialize(f_type_output, f_type_descriptor_output, f_file_flag_write_only), \
      fll_error_print_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_fss_nest_t_initialize, \
      f_string_quantity_t_initialize, \
      f_color_context_t_initialize, \
    }
#endif // _di_fss_extended_list_read_data_t_

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
#ifndef _di_fss_extended_list_read_print_help_
  extern f_return_status fss_extended_list_read_print_help(const f_file_t file, const f_color_context_t context);
#endif // _di_fss_extended_list_read_print_help_

/**
 * Execute main program.
 *
 * Be sure to call fss_extended_list_read_delete_data() after executing this.
 *
 * @param arguments
 *   The parameters passed to the process.
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fss_extended_list_read_delete_data()
 */
#ifndef _di_fss_extended_list_read_main_
  extern f_return_status fss_extended_list_read_main(const f_console_arguments_t arguments, fss_extended_list_read_data_t *data);
#endif // _di_fss_extended_list_read_main_

/**
 * Deallocate data.
 *
 * Be sure to call this after executing fss_extended_list_read_main().
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fss_extended_list_read_main()
 */
#ifndef _di_fss_extended_list_read_delete_data_
  extern f_return_status fss_extended_list_read_delete_data(fss_extended_list_read_data_t *data);
#endif // _di_fss_extended_list_read_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_extended_list_read_h
