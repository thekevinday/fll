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
 * This program processes files or other input in fss format and stores the results in the iki_write_main_t.
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
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/color.h>
#include <fll/level_0/console.h>
#include <fll/level_0/conversion.h>
#include <fll/level_0/file.h>
#include <fll/level_0/iki.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>

// fll-1 includes
#include <fll/level_1/console.h>
#include <fll/level_1/conversion.h>
#include <fll/level_1/iki.h>
#include <fll/level_1/print.h>
#include <fll/level_1/string.h>

// fll-2 includes
#include <fll/level_2/error.h>
#include <fll/level_2/file.h>
#include <fll/level_2/iki.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_write_program_version_
  #define iki_write_program_version_major_s F_string_ascii_0_s
  #define iki_write_program_version_minor_s F_string_ascii_5_s
  #define iki_write_program_version_micro_s F_string_ascii_6_s

  #ifndef iki_write_program_version_nano_prefix_s
    #define iki_write_program_version_nano_prefix_s
  #endif

  #ifndef iki_write_program_version_nano_s
    #define iki_write_program_version_nano_s
  #endif

  #define iki_write_program_version_s iki_write_program_version_major_s F_string_ascii_period_s iki_write_program_version_minor_s F_string_ascii_period_s iki_write_program_version_micro_s iki_write_program_version_nano_prefix_s iki_write_program_version_nano_s
#endif // _di_iki_write_program_version_

#ifndef _di_iki_write_program_name_
  #define iki_write_program_name_s      "iki_write"
  #define iki_write_program_name_long_s "IKI Write"
#endif // _di_iki_write_program_name_

#ifndef _di_iki_write_defines_
  #define iki_write_short_file_s    "f"
  #define iki_write_short_content_s "c"
  #define iki_write_short_double_s  "d"
  #define iki_write_short_object_s  "o"
  #define iki_write_short_single_s  "s"

  #define iki_write_long_file_s    "file"
  #define iki_write_long_content_s "content"
  #define iki_write_long_double_s  "double"
  #define iki_write_long_object_s  "object"
  #define iki_write_long_single_s  "single"

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
      f_console_parameter_t_initialize(iki_write_short_file_s, iki_write_long_file_s, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(iki_write_short_content_s, iki_write_long_content_s, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(iki_write_short_double_s, iki_write_long_double_s, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(iki_write_short_object_s, iki_write_long_object_s, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(iki_write_short_single_s, iki_write_long_single_s, 0, 0, f_console_type_normal), \
    }

  #define iki_write_total_parameters_d 14
#endif // _di_iki_write_defines_

#ifndef _di_iki_write_main_t_
  typedef struct {
    f_console_parameter_t parameters[iki_write_total_parameters_d];

    f_array_lengths_t remaining;
    bool process_pipe;

    fl_print_t output;
    fl_print_t error;
    fl_print_t warning;

    f_string_dynamic_t buffer;

    f_color_context_t context;
  } iki_write_main_t;

  #define iki_write_main_t_initialize \
    { \
      iki_write_console_parameter_t_initialize, \
      f_array_lengths_t_initialize, \
      F_false, \
      fl_print_t_initialize, \
      macro_fl_print_t_initialize_error(), \
      macro_fl_print_t_initialize_warning(), \
      f_string_dynamic_t_initialize, \
      f_color_context_t_initialize, \
    }
#endif // _di_iki_write_main_t_

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
#ifndef _di_iki_write_print_help_
  extern f_status_t iki_write_print_help(const f_file_t file, const f_color_context_t context);
#endif // _di_iki_write_print_help_

/**
 * Execute main program.
 *
 * Be sure to call iki_write_main_delete() after executing this.
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
 * @see iki_write_main_delete()
 */
#ifndef _di_iki_write_main_
  extern f_status_t iki_write_main(const f_console_arguments_t arguments, iki_write_main_t *main);
#endif // _di_iki_write_main_

/**
 * Deallocate main.
 *
 * Be sure to call this after executing iki_write_main().
 *
 * @param main
 *   The main data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see iki_write_main()
 */
#ifndef _di_iki_write_main_delete_
  extern f_status_t iki_write_main_delete(iki_write_main_t *main);
#endif // _di_iki_write_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_write_h
