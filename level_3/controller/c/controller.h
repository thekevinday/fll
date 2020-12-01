/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This is the Controller program.
 *
 * This program utilizes the Featureless Linux Library.
 * This program provides system service management, much like sysvcontroller and controllerng.
 * This program can be controlled from user-space via the "control" program.
 *
 * @todo research containers and build in container support into this, providing "container" appropriate verbiage for individual rules.
 * @todo research namespaces and user_namespaces, they may be important to support.
 */
#ifndef _controller_h

// libc includes
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/utf.h>
#include <level_0/console.h>
#include <level_0/directory.h>
#include <level_0/file.h>
#include <level_0/fss.h>
#include <level_0/path.h>
#include <level_0/pipe.h>
#include <level_0/print.h>

// fll-1 includes
#include <level_1/color.h>
#include <level_1/console.h>
#include <level_1/fss.h>
#include <level_1/string.h>

// fll-2 includes
#include <level_2/error.h>
#include <level_2/fss.h>
#include <level_2/fss_basic_list.h>
#include <level_2/fss_extended.h>
#include <level_2/fss_extended_list.h>
#include <level_2/path.h>
#include <level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_version_
  #define controller_major_version "0"
  #define controller_minor_version "5"
  #define controller_micro_version "2"
  #define controller_version controller_major_version "." controller_minor_version "." controller_micro_version
#endif // _di_controller_version_

#ifndef _di_controller_name_
  #define controller_name "controller"
  #define controller_name_long "Controller Program"
#endif // _di_controller_name_

#ifndef _di_controller_defines_

  // must be at least 2.
  #define controller_default_allocation_step 4

  #define controller_path_pid      "/var/run/controller/controller.pid"
  #define controller_path_settings "/etc/controller"

  #define controller_path_pid_length      34
  #define controller_path_settings_length 15

  #define controller_short_interruptable "i"
  #define controller_short_pid           "p"
  #define controller_short_settings      "s"
  #define controller_short_test          "t"
  #define controller_short_validate      "V"

  #define controller_long_interruptable "interruptable"
  #define controller_long_pid           "pid"
  #define controller_long_settings      "settings"
  #define controller_long_test          "test"
  #define controller_long_validate      "validate"

  enum {
    controller_parameter_help,
    controller_parameter_light,
    controller_parameter_dark,
    controller_parameter_no_color,
    controller_parameter_verbosity_quiet,
    controller_parameter_verbosity_normal,
    controller_parameter_verbosity_verbose,
    controller_parameter_verbosity_debug,
    controller_parameter_version,

    controller_parameter_interruptable,
    controller_parameter_pid,
    controller_parameter_settings,
    controller_parameter_test,
    controller_parameter_validate,
  };

  #define controller_console_parameter_t_initialize \
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
      f_console_parameter_t_initialize(controller_short_interruptable, controller_long_interruptable, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(controller_short_pid, controller_long_pid, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(controller_short_settings, controller_long_settings, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(controller_short_test, controller_long_test, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(controller_short_validate, controller_long_validate, 0, 0, f_console_type_normal), \
    }

  #define controller_total_parameters 14
#endif // _di_controller_defines_

#ifndef _di_controller_data_t_
  typedef struct {
    f_console_parameter_t parameters[controller_total_parameters];

    f_string_lengths_t remaining;
    bool process_pipe;
    pid_t pid;

    f_file_t output;
    fll_error_print_t error;
    fll_error_print_t warning;

    f_color_context_t context;
  } controller_data_t;

  #define controller_data_t_initialize \
    { \
      controller_console_parameter_t_initialize, \
      f_string_lengths_t_initialize, \
      F_false, \
      0, \
      f_macro_file_t_initialize(f_type_output, f_type_descriptor_output, f_file_flag_write_only), \
      fll_error_print_t_initialize, \
      fll_macro_error_print_t_initialize_warning(), \
      f_color_context_t_initialize, \
    }
#endif // _di_controller_data_t_

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
#ifndef _di_controller_print_help_
  extern f_return_status controller_print_help(const f_file_t output, const f_color_context_t context);
#endif // _di_controller_print_help_

/**
 * Execute main program.
 *
 * Be sure to call controller_delete_data() after executing this.
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
 * @see controller_delete_data()
 */
#ifndef _di_controller_main_
  extern f_return_status controller_main(const f_console_arguments_t arguments, controller_data_t *data);
#endif // _di_controller_main_

/**
 * Deallocate data.
 *
 * Be sure to call this after executing controller_main().
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see controller_main()
 */
#ifndef _di_controller_delete_data_
  extern f_return_status controller_delete_data(controller_data_t *data);
#endif // _di_controller_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_h
