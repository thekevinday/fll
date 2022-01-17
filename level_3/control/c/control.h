/**
 * FLL - Level 3
 *
 * Project: Control
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * This is the Control program.
 *
 * This program utilizes the Featureless Linux Library.
 * This program is used to communicate with the "controller" program that exists as a system init (an alternative to sysvinit, initng, etc..).
 */
#ifndef _control_h

// libc includes.
#include <unistd.h>

// fll-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/color.h>
#include <fll/level_0/console.h>
#include <fll/level_0/directory.h>
#include <fll/level_0/file.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>
#include <fll/level_0/signal.h>

// fll-1 includes
#include <fll/level_1/console.h>
#include <fll/level_1/print.h>
#include <fll/level_1/string.h>

// fll-2 includes
#include <fll/level_2/error.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_control_program_version_
  #define control_program_version_major_s F_string_ascii_0_s
  #define control_program_version_minor_s F_string_ascii_5_s
  #define control_program_version_micro_s F_string_ascii_8_s

  #ifndef control_program_version_nano_prefix_s
    #define control_program_version_nano_prefix_s
  #endif

  #ifndef control_program_version_nano_s
    #define control_program_version_nano_s
  #endif

  #define control_program_version_s control_program_version_major_s F_string_ascii_period_s control_program_version_minor_s F_string_ascii_period_s control_program_version_micro_s control_program_version_nano_prefix_s control_program_version_nano_s
#endif // _di_control_program_version_

#ifndef _di_control_program_name_
  #define control_program_name_s      "control"
  #define control_program_name_long_s "Control Program"
#endif // _di_control_program_name_

#ifndef _di_control_defines_

  enum {
    control_parameter_help_e,
    control_parameter_light_e,
    control_parameter_dark_e,
    control_parameter_no_color_e,
    control_parameter_verbosity_quiet_e,
    control_parameter_verbosity_normal_e,
    control_parameter_verbosity_verbose_e,
    control_parameter_verbosity_debug_e,
    control_parameter_version_e,
  };

  #define control_console_parameter_t_initialize \
    { \
      macro_f_console_parameter_t_initialize(f_console_standard_short_help_s, f_console_standard_long_help_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_light_s, f_console_standard_long_light_s, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_dark_s, f_console_standard_long_dark_s, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_normal_s, f_console_standard_long_normal_s, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_debug_s, f_console_standard_long_debug_s, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_version_s, f_console_standard_long_version_s, 0, 0, f_console_type_inverse_e), \
    }

  #define control_total_parameters_d 9
#endif // _di_control_defines_

#ifndef _di_control_data_t_
  typedef struct {
    f_console_parameter_t parameters[control_total_parameters_d];

    f_array_lengths_t remaining;
    bool process_pipe;

    fl_print_t output;
    fl_print_t error;
    fl_print_t warning;

    f_signal_t signal;

    f_color_context_t context;
  } control_main_t;

  #define control_data_initialize \
    { \
      control_console_parameter_t_initialize, \
      f_array_lengths_t_initialize, \
      F_false, \
      fl_print_t_initialize, \
      macro_fl_print_t_initialize_error(), \
      macro_fl_print_t_initialize_warning(), \
      f_signal_t_initialize, \
      f_color_context_t_initialize, \
    }
#endif // _di_control_data_t_

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
#ifndef _di_control_print_help_
  extern f_status_t control_print_help(const f_file_t file, const f_color_context_t context);
#endif // _di_control_print_help_

/**
 * Execute main program.
 *
 * Be sure to call control_main_delete() after executing this.
 *
 * If main.signal is non-zero, then this blocks and handles the following signals:
 *   - F_signal_abort
 *   - F_signal_broken_pipe
 *   - F_signal_hangup
 *   - F_signal_interrupt
 *   - F_signal_quit
 *   - F_signal_termination
 *
 * @param main
 *   The main program data.
 * @param arguments
 *   The parameters passed to the process.
 *
 * @return
 *   F_none on success.
 *
 *   F_interrupt (with error bit) on receiving a process signal, such as an interrupt signal.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see control_main_delete()
 */
#ifndef _di_control_main_
  extern f_status_t control_main(control_main_t * const main, const f_console_arguments_t *arguments);
#endif // _di_control_main_

/**
 * Deallocate main.
 *
 * Be sure to call this after executing control_main().
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see control_main()
 */
#ifndef _di_control_main_delete_
  extern f_status_t control_main_delete(control_main_t * const main);
#endif // _di_control_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _control_h
