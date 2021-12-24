/**
 * FLL - Level 3
 *
 * Project: Status Code
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * This program provides status code to/from string translation.
 */
#ifndef _status_code_h

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
#include <fll/level_0/signal.h>
#include <fll/level_0/status_string.h>

// fll-1 includes
#include <fll/level_1/console.h>
#include <fll/level_1/conversion.h>
#include <fll/level_1/print.h>
#include <fll/level_1/string.h>

// fll-2 includes
#include <fll/level_2/error.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>
#include <fll/level_2/status_string.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_status_code_program_version_
  #define status_code_progam_version_major_s F_string_ascii_0_s
  #define status_code_progam_version_minor_s F_string_ascii_5_s
  #define status_code_progam_version_micro_s F_string_ascii_7_s

  #ifndef status_code_progam_version_nano_prefix_s
    #define status_code_progam_version_nano_prefix_s
  #endif

  #ifndef status_code_progam_version_nano_s
    #define status_code_progam_version_nano_s
  #endif

  #define status_code_progam_version_s status_code_progam_version_major_s F_string_ascii_period_s status_code_progam_version_minor_s F_string_ascii_period_s status_code_progam_version_micro_s status_code_progam_version_nano_prefix_s status_code_progam_version_nano_s
#endif // _di_status_code_program_version_

#ifndef _di_status_code_program_name_
  #define status_code_progam_name_s      "status_code"
  #define status_code_progam_name_long_s "FSS Status Code"
#endif // _di_status_code_program_name_

#ifndef _di_status_code_defines_
  #define status_code_signal_check_d 10000

  #define status_code_short_is_fine_s    "f"
  #define status_code_short_is_warning_s "w"
  #define status_code_short_is_error_s   "e"
  #define status_code_short_number_s     "n"

  #define status_code_long_is_fine_s    "is_fine"
  #define status_code_long_is_warning_s "is_warning"
  #define status_code_long_is_error_s   "is_error"
  #define status_code_long_number_s     "number"

  enum {
    status_code_parameter_help_e,
    status_code_parameter_light_e,
    status_code_parameter_dark_e,
    status_code_parameter_no_color_e,
    status_code_parameter_verbosity_quiet_e,
    status_code_parameter_verbosity_normal_e,
    status_code_parameter_verbosity_verbose_e,
    status_code_parameter_verbosity_debug_e,
    status_code_parameter_version_e,

    status_code_parameter_is_fine_e,
    status_code_parameter_is_warning_e,
    status_code_parameter_is_error_e,
    status_code_parameter_number_e,
  };

  #define status_code_console_parameter_t_initialize \
    { \
      f_console_parameter_t_initialize(f_console_standard_short_help_s, f_console_standard_long_help_s, 0, 0, f_console_type_normal_e), \
      f_console_parameter_t_initialize(f_console_standard_short_light_s, f_console_standard_long_light_s, 0, 0, f_console_type_inverse_e), \
      f_console_parameter_t_initialize(f_console_standard_short_dark_s, f_console_standard_long_dark_s, 0, 0, f_console_type_inverse_e), \
      f_console_parameter_t_initialize(f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, 0, 0, f_console_type_inverse_e), \
      f_console_parameter_t_initialize(f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, 0, 0, f_console_type_inverse_e), \
      f_console_parameter_t_initialize(f_console_standard_short_normal_s, f_console_standard_long_normal_s, 0, 0, f_console_type_inverse_e), \
      f_console_parameter_t_initialize(f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, 0, 0, f_console_type_inverse_e), \
      f_console_parameter_t_initialize(f_console_standard_short_debug_s, f_console_standard_long_debug_s, 0, 0, f_console_type_inverse_e), \
      f_console_parameter_t_initialize(f_console_standard_short_version_s, f_console_standard_long_version_s, 0, 0, f_console_type_inverse_e), \
      f_console_parameter_t_initialize(status_code_short_is_fine_s, status_code_long_is_fine_s, 0, 0, f_console_type_normal_e), \
      f_console_parameter_t_initialize(status_code_short_is_warning_s, status_code_long_is_warning_s, 0, 0, f_console_type_normal_e), \
      f_console_parameter_t_initialize(status_code_short_is_error_s, status_code_long_is_error_s, 0, 0, f_console_type_normal_e), \
      f_console_parameter_t_initialize(status_code_short_number_s, status_code_long_number_s, 0, 0, f_console_type_normal_e), \
    }

  #define status_code_total_parameters_d 13
#endif // _di_status_code_defines_

#ifndef _di_status_code_main_t_
  typedef struct {
    f_console_parameter_t parameters[status_code_total_parameters_d];

    f_array_lengths_t remaining;
    bool process_pipe;

    fl_print_t output;
    fl_print_t error;
    fl_print_t warning;

    f_signal_t signal;

    f_color_context_t context;
  } status_code_main_t;

  #define status_code_main_t_initialize \
    { \
      status_code_console_parameter_t_initialize, \
      f_array_lengths_t_initialize, \
      F_false, \
      fl_print_t_initialize, \
      macro_fl_print_t_initialize_error(), \
      macro_fl_print_t_initialize_warning(), \
      f_signal_t_initialize, \
      f_color_context_t_initialize, \
    }
#endif // _di_status_code_main_t_

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
#ifndef _di_status_code_print_help_
  extern f_status_t status_code_print_help(const f_file_t file, const f_color_context_t context);
#endif // _di_status_code_print_help_

/**
 * Execute main program.
 *
 * Be sure to call status_code_main_delete() after executing this.
 *
 * If main.signal is non-zero, then this blocks and handles the following signals:
 * - F_signal_abort
 * - F_signal_broken_pipe
 * - F_signal_hangup
 * - F_signal_interrupt
 * - F_signal_quit
 * - F_signal_termination
 *
 * @param main
 *   The main program data.
 * @param arguments
 *   The parameters passed to the process.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see status_code_main_delete()
 */
#ifndef _di_status_code_main_
  extern f_status_t status_code_main(status_code_main_t * const main, const f_console_arguments_t *arguments);
#endif // _di_status_code_main_

/**
 * Deallocate main.
 *
 * Be sure to call this after executing status_code_main().
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see status_code_main()
 */
#ifndef _di_status_code_main_delete_
  extern f_status_t status_code_main_delete(status_code_main_t * const main);
#endif // _di_status_code_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _status_code_h
