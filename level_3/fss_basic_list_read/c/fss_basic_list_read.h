/* FLL - Level 3
 * Project:       FSS
 * Version:       0.2.1
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * This is the FSS Basic List Read program
 * This program utilizes the Featureless Linux Library.
 * This program processes files or other input in fss format and stores the results in the fss_basic_list_read_data
 */
#ifndef _fss_basic_list_read_h

// libc includes
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

// fll-0 includes
#include <level_0/types.h>
#include <level_0/strings.h>
#include <level_0/file.h>
#include <level_0/console.h>
#include <level_0/output.h>
#include <level_0/pipe.h>

// fll-1 includes
#include <level_1/colors.h>
#include <level_1/console.h>
#include <level_1/file.h>
#include <level_1/execute.h>
#include <level_1/strings.h>
#include <level_1/directory.h>

// fll-2 includes
#include <level_2/fss_basic_list.h>
#include <level_2/colors.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fss_basic_list_read_version_
  #define fss_basic_list_read_major_version "0"
  #define fss_basic_list_read_minor_version "3"
  #define fss_basic_list_read_micro_version "0"
  #define fss_basic_list_read_version fss_basic_list_read_major_version "." fss_basic_list_read_minor_version "." fss_basic_list_read_micro_version
#endif // _di_fss_basic_list_read_version_

#ifndef _di_fss_basic_list_read_name_
  #define fss_basic_list_read_name "fss_basic_list_read"
  #define fss_basic_list_read_name_long "FSS Basic List Read"
#endif // _di_fss_basic_list_read_name_

#ifndef _di_fss_basic_list_read_defines_
  #define f_console_standard_short_name   "n"
  #define f_console_standard_short_count  "c"
  #define f_console_standard_short_total  "t"
  #define f_console_standard_short_object "o"
  #define f_console_standard_short_size   "s"
  #define f_console_standard_short_line   "l"

  #define f_console_standard_long_name   "name"
  #define f_console_standard_long_count  "count"
  #define f_console_standard_long_total  "total"
  #define f_console_standard_long_object "object"
  #define f_console_standard_long_size   "size"
  #define f_console_standard_long_line   "line"

  enum {
    fss_basic_list_read_parameter_help,
    fss_basic_list_read_parameter_light,
    fss_basic_list_read_parameter_no_color,
    fss_basic_list_read_parameter_version,

    fss_basic_list_read_parameter_name,
    fss_basic_list_read_parameter_count,
    fss_basic_list_read_parameter_total,
    fss_basic_list_read_parameter_object,
    fss_basic_list_read_parameter_size,
    fss_basic_list_read_parameter_line,
  };

  #define f_console_parameter_initialize_fss_basic_list_read \
    { \
      f_console_parameter_initialize(f_console_standard_short_help, f_console_standard_long_help, 0, 0, f_false, f_console_type_normal, 0), \
      f_console_parameter_initialize(f_console_standard_short_light, f_console_standard_long_light, 0, 0, f_false, f_console_type_inverse, 0), \
      f_console_parameter_initialize(f_console_standard_short_no_color, f_console_standard_long_no_color, 0, 0, f_false, f_console_type_inverse, 0), \
      f_console_parameter_initialize(f_console_standard_short_version, f_console_standard_long_version, 0, 0, f_false, f_console_type_normal, 0), \
      f_console_parameter_initialize(f_console_standard_short_name, f_console_standard_long_name, 0, 0, f_true, f_console_type_normal, 0), \
      f_console_parameter_initialize(f_console_standard_short_count, f_console_standard_long_count, 0, 0, f_true, f_console_type_normal, 0), \
      f_console_parameter_initialize(f_console_standard_short_total, f_console_standard_long_total, 0, 0, f_false, f_console_type_normal, 0), \
      f_console_parameter_initialize(f_console_standard_short_object, f_console_standard_long_object, 0, 0, f_false, f_console_type_normal, 0), \
      f_console_parameter_initialize(f_console_standard_short_size, f_console_standard_long_size, 0, 0, f_false, f_console_type_normal, 0), \
      f_console_parameter_initialize(f_console_standard_short_line, f_console_standard_long_line, 0, 0, f_true, f_console_type_normal, 0), \
    }

  #define fss_basic_list_read_total_parameters 10
#endif // _di_fss_basic_list_read_defines_

#ifndef _di_fss_basic_list_read_data_
  typedef struct {
    f_console_parameter parameters[fss_basic_list_read_total_parameters];

    f_dynamic_string  buffer;
    f_fss_objects     objects;
    f_fss_contents    contents;
    f_file_position   file_position;
    f_string_lengths  remaining;
    f_bool            process_pipe;

    fll_color_context context;
  } fss_basic_list_read_data;

  #define fss_basic_list_read_data_initialize \
    { \
      f_console_parameter_initialize_fss_basic_list_read, \
      f_dynamic_string_initialize, \
      f_fss_objects_initialize, \
      f_fss_contents_initialize, \
      f_file_position_initialize, \
      f_string_lengths_initialize, \
      f_false, \
      fll_color_context_initialize, \
    }
#endif // _di_fss_basic_list_read_data_

#ifndef _di_fss_basic_list_read_print_version_
  extern f_return_status fss_basic_list_read_print_version(const fss_basic_list_read_data data);
#endif // _di_fss_basic_list_read_print_version_

#ifndef _di_fss_basic_list_read_print_help_
  extern f_return_status fss_basic_list_read_print_help(const fss_basic_list_read_data data);
#endif // _di_fss_basic_list_read_print_help_

#ifndef _di_fss_basic_list_read_main_
  extern f_return_status fss_basic_list_read_main(const f_array_length argc, const f_string argv[], fss_basic_list_read_data *data);
#endif // _di_fss_basic_list_read_main_

#ifndef _di_fss_basic_list_read_delete_data_
  extern f_return_status fss_basic_list_read_delete_data(fss_basic_list_read_data *data);
#endif // _di_fss_basic_list_read_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_basic_list_read_h
