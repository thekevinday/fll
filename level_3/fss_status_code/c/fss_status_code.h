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
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/color.h>
#include <fll/level_0/conversion.h>
#include <fll/level_0/console.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>

// fll-1 includes
#include <fll/level_1/console.h>
#include <fll/level_1/conversion.h>
#include <fll/level_1/print.h>
#include <fll/level_1/status.h>
#include <fll/level_1/string.h>

// fll-2 includes
#include <fll/level_2/error.h>
#include <fll/level_2/fss_status.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>
#include <fll/level_2/status.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_status_code_program_version_
  #define fss_status_code_program_version_major_s F_string_ascii_0_s
  #define fss_status_code_program_version_minor_s F_string_ascii_5_s
  #define fss_status_code_program_version_micro_s F_string_ascii_7_s

  #ifndef fss_status_code_program_version_nano_prefix_s
    #define fss_status_code_program_version_nano_prefix_s
  #endif

  #ifndef fss_status_code_program_version_nano_s
    #define fss_status_code_program_version_nano_s
  #endif

  #define fss_status_code_program_version_s fss_status_code_program_version_major_s F_string_ascii_period_s fss_status_code_program_version_minor_s F_string_ascii_period_s fss_status_code_program_version_micro_s fss_status_code_program_version_nano_prefix_s fss_status_code_program_version_nano_s
#endif // _di_fss_status_code_program_version_

#ifndef _di_fss_status_code_program_name_
  #define fss_status_code_program_name_s      "fss_status_code"
  #define fss_status_code_program_name_long_s "FSS Status Code"
#endif // _di_fss_status_code_program_name_

#ifndef _di_fss_status_code_defines_
  #define fss_status_code_short_is_fine_s    "f"
  #define fss_status_code_short_is_warning_s "w"
  #define fss_status_code_short_is_error_s   "e"
  #define fss_status_code_short_number_s     "n"

  #define fss_status_code_long_is_fine_s    "is_fine"
  #define fss_status_code_long_is_warning_s "is_warning"
  #define fss_status_code_long_is_error_s   "is_error"
  #define fss_status_code_long_number_s     "number"

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
      f_console_parameter_t_initialize(f_console_standard_short_help_s, f_console_standard_long_help_s, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(f_console_standard_short_light_s, f_console_standard_long_light_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_dark_s, f_console_standard_long_dark_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_normal_s, f_console_standard_long_normal_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_debug_s, f_console_standard_long_debug_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_version_s, f_console_standard_long_version_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(fss_status_code_short_is_fine_s, fss_status_code_long_is_fine_s, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_status_code_short_is_warning_s, fss_status_code_long_is_warning_s, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_status_code_short_is_error_s, fss_status_code_long_is_error_s, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_status_code_short_number_s, fss_status_code_long_number_s, 0, 0, f_console_type_normal), \
    }

  #define fss_status_code_total_parameters_d 13
#endif // _di_fss_status_code_defines_

#ifndef _di_fss_status_code_main_t_
  typedef struct {
    f_console_parameter_t parameters[fss_status_code_total_parameters_d];

    f_array_lengths_t remaining;
    bool process_pipe;

    fl_print_t output;
    fl_print_t error;
    fl_print_t warning;

    f_color_context_t context;
  } fss_status_code_main_t;

  #define fss_status_code_main_t_initialize \
    { \
      fss_status_code_console_parameter_t_initialize, \
      f_array_lengths_t_initialize, \
      F_false, \
      fl_print_t_initialize, \
      macro_fl_print_t_initialize_error(), \
      macro_fl_print_t_initialize_warning(), \
      f_color_context_t_initialize, \
    }
#endif // _di_fss_status_code_main_t_

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
#ifndef _di_fss_status_code_print_help_
  extern f_status_t fss_status_code_print_help(const f_file_t file, const f_color_context_t context);
#endif // _di_fss_status_code_print_help_

/**
 * Execute main program.
 *
 * Be sure to call fss_status_code_main_delete() after executing this.
 *
 * @param arguments
 *   The parameters passed to the process.
 * @param main
 *   The main data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fss_status_code_main_delete()
 */
#ifndef _di_fss_status_code_main_
  extern f_status_t fss_status_code_main(const f_console_arguments_t arguments, fss_status_code_main_t *main);
#endif // _di_fss_status_code_main_

/**
 * Deallocate main.
 *
 * Be sure to call this after executing fss_status_code_main().
 *
 * @param main
 *   The main data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fss_status_code_main()
 */
#ifndef _di_fss_status_code_main_delete_
  extern f_status_t fss_status_code_main_delete(fss_status_code_main_t *main);
#endif // _di_fss_status_code_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_status_code_h
