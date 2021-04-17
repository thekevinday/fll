/**
 * FLL - Level 3
 *
 * Project: IKI
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This is the IKI Write program.
 *
 * This program utilizes the Featureless Linux Library.
 * This program processes files or other input in fss format and stores the results in the iki_write_data_t.
 *
 * This processes in accordance to the IKI specification.
 */
#ifndef _iki_write_h

// libc includes
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/utf.h>
#include <level_0/color.h>
#include <level_0/console.h>
#include <level_0/conversion.h>
#include <level_0/file.h>
#include <level_0/iki.h>
#include <level_0/pipe.h>
#include <level_0/print.h>

// fll-1 includes
#include <level_1/console.h>
#include <level_1/conversion.h>
#include <level_1/iki.h>
#include <level_1/print.h>
#include <level_1/string.h>

// fll-2 includes
#include <level_2/error.h>
#include <level_2/file.h>
#include <level_2/iki.h>
#include <level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_write_version_
  #define iki_write_major_version "0"
  #define iki_write_minor_version "5"
  #define iki_write_micro_version "3"
  #define iki_write_version iki_write_major_version f_string_ascii_period iki_write_minor_version f_string_ascii_period iki_write_micro_version
#endif // _di_iki_write_version_

#ifndef _di_iki_write_name_
  #define iki_write_name      "iki_write"
  #define iki_write_name_long "IKI Write"
#endif // _di_iki_write_name_

#ifndef _di_iki_write_defines_
  #define iki_write_short_file    "f"
  #define iki_write_short_content "c"
  #define iki_write_short_double  "d"
  #define iki_write_short_object  "o"
  #define iki_write_short_single  "s"

  #define iki_write_long_file    "file"
  #define iki_write_long_content "content"
  #define iki_write_long_double  "double"
  #define iki_write_long_object  "object"
  #define iki_write_long_single  "single"

  enum {
    iki_write_parameter_help,
    iki_write_parameter_light,
    iki_write_parameter_dark,
    iki_write_parameter_no_color,
    iki_write_parameter_verbosity_quiet,
    iki_write_parameter_verbosity_normal,
    iki_write_parameter_verbosity_verbose,
    iki_write_parameter_verbosity_debug,
    iki_write_parameter_version,

    iki_write_parameter_file,
    iki_write_parameter_content,
    iki_write_parameter_double,
    iki_write_parameter_object,
    iki_write_parameter_single,
  };

  #define iki_write_console_parameter_t_initialize \
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
      f_console_parameter_t_initialize(iki_write_short_file, iki_write_long_file, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(iki_write_short_content, iki_write_long_content, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(iki_write_short_double, iki_write_long_double, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(iki_write_short_object, iki_write_long_object, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(iki_write_short_single, iki_write_long_single, 0, 0, f_console_type_normal), \
    }

  #define iki_write_total_parameters 14
#endif // _di_iki_write_defines_

#ifndef _di_iki_write_data_t_
  typedef struct {
    f_console_parameter_t parameters[iki_write_total_parameters];

    f_array_lengths_t remaining;
    bool process_pipe;

    f_file_t output;
    fll_error_print_t error;

    f_string_dynamic_t buffer;

    f_color_context_t context;
  } iki_write_data_t;

  #define iki_write_data_t_initialize \
    { \
      iki_write_console_parameter_t_initialize, \
      f_array_lengths_t_initialize, \
      F_false, \
      f_macro_file_t_initialize2(f_type_output, f_type_descriptor_output, f_file_flag_write_only), \
      fll_error_print_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_color_context_t_initialize, \
    }
#endif // _di_iki_write_data_t_

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
#ifndef _di_iki_write_print_help_
  extern f_status_t iki_write_print_help(const f_file_t output, const f_color_context_t context);
#endif // _di_iki_write_print_help_

/**
 * Execute main program.
 *
 * Be sure to call iki_write_delete_data() after executing this.
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
 * @see iki_write_delete_data()
 */
#ifndef _di_iki_write_main_
  extern f_status_t iki_write_main(const f_console_arguments_t arguments, iki_write_data_t *data);
#endif // _di_iki_write_main_

/**
 * Deallocate data.
 *
 * Be sure to call this after executing iki_write_main().
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see iki_write_main()
 */
#ifndef _di_iki_write_delete_data_
  extern f_status_t iki_write_delete_data(iki_write_data_t *data);
#endif // _di_iki_write_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_write_h
