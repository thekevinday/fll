/**
 * FLL - Level 3
 *
 * Project: Control
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This is the Control program.
 *
 * This program utilizes the Featureless Linux Library.
 * This program is used to communicate with the "controller" program that exists as a system init (an alternative to sysvinit, initng, etc..).
 */
#ifndef _control_h

// libc includes
#include <unistd.h>

// fll-0 includes
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

// fll-1 includes
#include <fll/level_1/console.h>
#include <fll/level_1/string.h>

// fll-2 includes
#include <fll/level_2/error.h>
#include <fll/level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_control_version_
  #define control_major_version f_string_ascii_0
  #define control_minor_version f_string_ascii_5
  #define control_micro_version f_string_ascii_4

  #ifndef control_nano_version_prefix
    #define control_nano_version_prefix
  #endif

  #ifndef control_nano_version
    #define control_nano_version
  #endif

  #define control_version control_major_version f_string_ascii_period control_minor_version f_string_ascii_period control_micro_version control_nano_version_prefix control_nano_version
#endif // _di_control_version_

#ifndef _di_control_name_
  #define control_name "control"
  #define control_name_long "Control Program"
#endif // _di_control_name_

#ifndef _di_control_defines_

  enum {
    control_parameter_help,
    control_parameter_light,
    control_parameter_dark,
    control_parameter_no_color,
    control_parameter_verbosity_quiet,
    control_parameter_verbosity_normal,
    control_parameter_verbosity_verbose,
    control_parameter_verbosity_debug,
    control_parameter_version,
  };

  #define control_console_parameter_t_initialize \
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
    }

  #define control_total_parameters 9
#endif // _di_control_defines_

#ifndef _di_control_data_t_
  typedef struct {
    f_console_parameter_t parameters[control_total_parameters];

    f_array_lengths_t remaining;
    bool process_pipe;

    f_file_t output;
    fll_error_print_t error;
    fll_error_print_t warning;

    f_color_context_t context;
  } control_main_t;

  #define control_data_initialize \
    { \
      control_console_parameter_t_initialize, \
      f_array_lengths_t_initialize, \
      F_false, \
      macro_f_file_t_initialize2(f_type_output, f_type_descriptor_output, f_file_flag_write_only), \
      fll_error_print_t_initialize, \
      macro_fll_error_print_t_initialize_warning(), \
      f_color_context_t_initialize, \
    }
#endif // _di_control_data_t_

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
#ifndef _di_control_print_help_
  extern f_status_t control_print_help(const f_file_t output, const f_color_context_t context);
#endif // _di_control_print_help_

/**
 * Execute main program.
 *
 * Be sure to call control_main_delete() after executing this.
 *
 * @param arguments
 *   The parameters passed to the process.
 * @param main
 *   The program main.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see control_main_delete()
 */
#ifndef _di_control_main_
  extern f_status_t control_main(const f_console_arguments_t arguments, control_main_t *main);
#endif // _di_control_main_

/**
 * Deallocate main.
 *
 * Be sure to call this after executing control_main().
 *
 * @param main
 *   The program main.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see control_main()
 */
#ifndef _di_control_main_delete_
  extern f_status_t control_main_delete(control_main_t *main);
#endif // _di_control_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _control_h
