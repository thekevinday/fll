/**
 * FLL - Level 3
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This program provides FSS-0008 Embedded List write functionality.
 */
#ifndef _fss_embedded_list_write_h

// libc includes
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
#include <level_0/file.h>
#include <level_0/pipe.h>
#include <level_0/print.h>

// fll-1 includes
#include <level_1/color.h>
#include <level_1/console.h>
#include <level_1/conversion.h>
#include <level_1/fss_embedded_list.h>
#include <level_1/status.h>
#include <level_1/string.h>

// fll-2 includes
#include <level_2/error.h>
#include <level_2/fss_status.h>
#include <level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_embedded_list_write_version_
  #define fss_embedded_list_write_major_version "0"
  #define fss_embedded_list_write_minor_version "5"
  #define fss_embedded_list_write_micro_version "2"
  #define fss_embedded_list_write_version fss_embedded_list_write_major_version "." fss_embedded_list_write_minor_version "." fss_embedded_list_write_micro_version
#endif // _di_fss_embedded_list_write_version_

#ifndef _di_fss_embedded_list_write_name_
  #define fss_embedded_list_write_name      "fss_embedded_list_write"
  #define fss_embedded_list_write_name_long "FSS Embedded List Write"
#endif // _di_fss_embedded_list_write_name_

#ifndef _di_fss_embedded_list_write_defines_
  #define fss_embedded_list_write_pipe_content_end    '\f'
  #define fss_embedded_list_write_pipe_content_ignore '\v'
  #define fss_embedded_list_write_pipe_content_start  '\b'

  #define fss_embedded_list_write_short_file    "f"
  #define fss_embedded_list_write_short_content "c"
  #define fss_embedded_list_write_short_double  "d"
  #define fss_embedded_list_write_short_ignore  "I"
  #define fss_embedded_list_write_short_object  "o"
  #define fss_embedded_list_write_short_partial "p"
  #define fss_embedded_list_write_short_prepend "P"
  #define fss_embedded_list_write_short_single  "s"
  #define fss_embedded_list_write_short_trim    "T"

  #define fss_embedded_list_write_long_file    "file"
  #define fss_embedded_list_write_long_content "content"
  #define fss_embedded_list_write_long_double  "double"
  #define fss_embedded_list_write_long_ignore  "ignore"
  #define fss_embedded_list_write_long_object  "object"
  #define fss_embedded_list_write_long_partial "partial"
  #define fss_embedded_list_write_long_prepend "prepend"
  #define fss_embedded_list_write_long_single  "single"
  #define fss_embedded_list_write_long_trim    "trim"

  enum {
    fss_embedded_list_write_parameter_help,
    fss_embedded_list_write_parameter_light,
    fss_embedded_list_write_parameter_dark,
    fss_embedded_list_write_parameter_no_color,
    fss_embedded_list_write_parameter_verbosity_quiet,
    fss_embedded_list_write_parameter_verbosity_normal,
    fss_embedded_list_write_parameter_verbosity_verbose,
    fss_embedded_list_write_parameter_verbosity_debug,
    fss_embedded_list_write_parameter_version,

    fss_embedded_list_write_parameter_file,
    fss_embedded_list_write_parameter_content,
    fss_embedded_list_write_parameter_double,
    fss_embedded_list_write_parameter_ignore,
    fss_embedded_list_write_parameter_object,
    fss_embedded_list_write_parameter_partial,
    fss_embedded_list_write_parameter_prepend,
    fss_embedded_list_write_parameter_single,
    fss_embedded_list_write_parameter_trim,
  };

  #define fss_embedded_list_write_console_parameter_t_initialize \
    { \
      f_console_parameter_t_initialize(f_console_standard_short_help, f_console_standard_long_help, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(f_console_standard_short_light, f_console_standard_long_light, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_dark, f_console_standard_long_dark, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_no_color, f_console_standard_long_no_color, 0, F_false, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_quiet, f_console_standard_long_quiet, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_normal, f_console_standard_long_normal, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_verbose, f_console_standard_long_verbose, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_debug, f_console_standard_long_debug, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_version, f_console_standard_long_version, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(fss_embedded_list_write_short_file, fss_embedded_list_write_long_file, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_embedded_list_write_short_content, fss_embedded_list_write_long_content, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_embedded_list_write_short_double, fss_embedded_list_write_long_double, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_embedded_list_write_short_ignore, fss_embedded_list_write_long_ignore, 0, 2, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_embedded_list_write_short_object, fss_embedded_list_write_long_object, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_embedded_list_write_short_partial, fss_embedded_list_write_long_partial, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_embedded_list_write_short_prepend, fss_embedded_list_write_long_prepend, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_embedded_list_write_short_single, fss_embedded_list_write_long_single, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_embedded_list_write_short_trim, fss_embedded_list_write_long_trim, 0, 0, f_console_type_normal), \
    }

  #define fss_embedded_list_write_total_parameters 18
#endif // _di_fss_embedded_list_write_defines_

#ifndef _di_fss_embedded_list_write_data_t_
  typedef struct {
    f_console_parameter_t parameters[fss_embedded_list_write_total_parameters];

    f_string_lengths_t remaining;
    bool process_pipe;

    f_file_t output;
    fll_error_print_t error;
    f_string_static_t prepend;

    f_color_context_t context;
  } fss_embedded_list_write_data_t;

  #define fss_embedded_list_write_data_t_initialize \
    { \
      fss_embedded_list_write_console_parameter_t_initialize, \
      f_string_lengths_t_initialize, \
      F_false, \
      f_macro_file_t_initialize(f_type_output, f_type_descriptor_output, f_file_flag_write_only), \
      fll_error_print_t_initialize, \
      f_string_static_t_initialize, \
      f_color_context_t_initialize, \
    }
#endif // _di_fss_embedded_list_write_data_t_

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
#ifndef _di_fss_embedded_list_write_print_help_
  extern f_return_status fss_embedded_list_write_print_help(const f_file_t output, const f_color_context_t context);
#endif // _di_fss_embedded_list_write_print_help_

/**
 * Execute main program.
 *
 * Be sure to call fss_embedded_list_write_delete_data() after executing this.
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
 * @see fss_embedded_list_write_delete_data()
 */
#ifndef _di_fss_embedded_list_write_main_
  extern f_return_status fss_embedded_list_write_main(const f_console_arguments_t arguments, fss_embedded_list_write_data_t *data);
#endif // _di_fss_embedded_list_write_main_

/**
 * Deallocate data.
 *
 * Be sure to call this after executing fss_embedded_list_write_main().
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fss_embedded_list_write_main()
 */
#ifndef _di_fss_embedded_list_write_delete_data_
  extern f_return_status fss_embedded_list_write_delete_data(fss_embedded_list_write_data_t *data);
#endif // _di_fss_embedded_list_write_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_embedded_list_write_h