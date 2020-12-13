/**
 * FLL - Level 3
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This program provides status code to/from string translation.
 */
#ifndef _fss_status_code_h

// libc includes
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
#include <level_0/conversion.h>
#include <level_0/console.h>
#include <level_0/pipe.h>
#include <level_0/print.h>

// fll-1 includes
#include <level_1/color.h>
#include <level_1/console.h>
#include <level_1/conversion.h>
#include <level_1/status.h>
#include <level_1/string.h>

// fll-2 includes
#include <level_2/error.h>
#include <level_2/fss_status.h>
#include <level_2/program.h>
#include <level_2/status.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_status_code_version_
  #define fss_status_code_major_version "0"
  #define fss_status_code_minor_version "5"
  #define fss_status_code_micro_version "2"
  #define fss_status_code_version fss_status_code_major_version "." fss_status_code_minor_version "." fss_status_code_micro_version
#endif // _di_fss_status_code_version_

#ifndef _di_fss_status_code_name_
  #define fss_status_code_name "fss_status_code"
  #define fss_status_code_name_long "FSS Status Code"
#endif // _di_fss_status_code_name_

#ifndef _di_fss_status_code_defines_
  #define fss_status_code_short_is_fine    "f"
  #define fss_status_code_short_is_warning "w"
  #define fss_status_code_short_is_error   "e"
  #define fss_status_code_short_number     "n"

  #define fss_status_code_long_is_fine    "is_fine"
  #define fss_status_code_long_is_warning "is_warning"
  #define fss_status_code_long_is_error   "is_error"
  #define fss_status_code_long_number     "number"

  enum {
    fss_status_code_parameter_help,
    fss_status_code_parameter_light,
    fss_status_code_parameter_dark,
    fss_status_code_parameter_no_color,
    fss_status_code_parameter_verbosity_quiet,
    fss_status_code_parameter_verbosity_normal,
    fss_status_code_parameter_verbosity_verbose,
    fss_status_code_parameter_verbosity_debug,
    fss_status_code_parameter_version,

    fss_status_code_parameter_is_fine,
    fss_status_code_parameter_is_warning,
    fss_status_code_parameter_is_error,
    fss_status_code_parameter_number,
  };

  #define fss_status_code_console_parameter_t_initialize \
    { \
      f_console_parameter_t_initialize(f_console_standard_short_help, f_console_standard_long_help, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(f_console_standard_short_light, f_console_standard_long_light, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_dark, f_console_standard_long_dark, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_no_color, f_console_standard_long_no_color, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_quiet, f_console_standard_long_quiet, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_normal, f_console_standard_long_normal, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_verbose, f_console_standard_long_verbose, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_debug, f_console_standard_long_debug, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_version, f_console_standard_long_version, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(fss_status_code_short_is_fine, fss_status_code_long_is_fine, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_status_code_short_is_warning, fss_status_code_long_is_warning, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_status_code_short_is_error, fss_status_code_long_is_error, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_status_code_short_number, fss_status_code_long_number, 0, 0, f_console_type_normal), \
    }

  #define fss_status_code_total_parameters 13
#endif // _di_fss_status_code_defines_

#ifndef _di_fss_status_code_data_t_
  typedef struct {
    f_console_parameter_t parameters[fss_status_code_total_parameters];

    f_string_lengths_t remaining;
    bool process_pipe;

    f_file_t output;
    fll_error_print_t error;

    f_color_context_t context;
  } fss_status_code_data_t;

  #define fss_status_code_data_t_initialize \
    { \
      fss_status_code_console_parameter_t_initialize, \
      f_string_lengths_t_initialize, \
      F_false, \
      f_macro_file_t_initialize(f_type_output, f_type_descriptor_output, f_file_flag_write_only), \
      fll_error_print_t_initialize, \
      f_color_context_t_initialize, \
    }
#endif // _di_fss_status_code_data_t_

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
#ifndef _di_fss_status_code_print_help_
  extern f_return_status fss_status_code_print_help(const f_file_t output, const f_color_context_t context);
#endif // _di_fss_status_code_print_help_

/**
 * Execute main program.
 *
 * Be sure to call fss_status_code_delete_data() after executing this.
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
 * @see fss_status_code_delete_data()
 */
#ifndef _di_fss_status_code_main_
  extern f_return_status fss_status_code_main(const f_console_arguments_t arguments, fss_status_code_data_t *data);
#endif // _di_fss_status_code_main_

/**
 * Deallocate data.
 *
 * Be sure to call this after executing fss_status_code_main().
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fss_status_code_main()
 */
#ifndef _di_fss_status_code_delete_data_
  extern f_return_status fss_status_code_delete_data(fss_status_code_data_t *data);
#endif // _di_fss_status_code_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_status_code_h
