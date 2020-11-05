/**
 * FLL - Level 3
 *
 * Project: Init
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This is the Init program.
 *
 * This program utilizes the Featureless Linux Library.
 * This program performs the basic system boot operations.
 *
 * This program does the following:
 * 1) perform all initial filesystem setup tasks (creating directories, mounting, setting permissions, populated device files, etc..).
 * 2) finding the desired/wanted boot partition, mounting it (and any other mount points).
 * 3) booting into target partition using a given target program (controller, bash, etc..).
 * 4) falling back into a failsafe environment on error (such as bash).
 */
#ifndef _init_h

// libc includes

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
#include <level_1/string.h>

// fll-2 includes
#include <level_2/error.h>
#include <level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_init_version_
  #define init_major_version "0"
  #define init_minor_version "5"
  #define init_micro_version "2"
  #define init_version init_major_version "." init_minor_version "." init_micro_version
#endif // _di_init_version_

#ifndef _di_init_name_
  #define init_name "init"
  #define init_name_long "Init Program"
#endif // _di_init_name_

#ifndef _di_init_defines_

  enum {
    init_parameter_help,
    init_parameter_light,
    init_parameter_dark,
    init_parameter_no_color,
    init_parameter_verbosity_quiet,
    init_parameter_verbosity_normal,
    init_parameter_verbosity_verbose,
    init_parameter_verbosity_debug,
    init_parameter_version,
  };

  #define init_console_parameter_t_initialize \
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
    }

  #define init_total_parameters 9
#endif // _di_init_defines_

#ifndef _di_init_data_t_
  typedef struct {
    f_console_parameter_t parameters[init_total_parameters];

    f_string_lengths_t remaining;
    bool process_pipe;

    f_file_t output;
    fll_error_print_t error;

    f_color_context_t context;
  } init_data_t;

  #define init_data_initialize \
    { \
      init_console_parameter_t_initialize, \
      f_string_lengths_t_initialize, \
      F_false, \
      f_macro_file_t_initialize(f_type_output, f_type_descriptor_output, f_file_flag_write_only), \
      fll_error_print_t_initialize, \
      f_color_context_t_initialize, \
    }
#endif // _di_init_data_t_

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
#ifndef _di_init_print_help_
  extern f_return_status init_print_help(const f_file_t output, const f_color_context_t context);
#endif // _di_init_print_help_

/**
 * Execute main program.
 *
 * Be sure to call init_delete_data() after executing this.
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
 * @see init_delete_data()
 */
#ifndef _di_init_main_
  extern f_return_status init_main(const f_console_arguments_t arguments, init_data_t *data);
#endif // _di_init_main_

/**
 * Deallocate data.
 *
 * Be sure to call this after executing init_main().
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see init_main()
 */
#ifndef _di_init_delete_data_
  extern f_return_status init_delete_data(init_data_t *data);
#endif // _di_init_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _init_h
