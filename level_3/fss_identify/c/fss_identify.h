/**
 * FLL - Level 3
 *
 * Project: FSS Identify
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This is the program is intended to be used to identify an FSS file or FSS data.
 *
 * A valid FSS file or FSS data will have a header starting with the pound character '#'.
 *
 * This program utilizes the Featureless Linux Library.
 */
#ifndef _fss_identify_h

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
#include <fll/level_0/conversion.h>
#include <fll/level_0/directory.h>
#include <fll/level_0/fss.h>
#include <fll/level_0/file.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>

// fll-1 includes
#include <fll/level_1/console.h>
#include <fll/level_1/conversion.h>
#include <fll/level_1/fss.h>
#include <fll/level_1/string.h>

// fll-2 includes
#include <fll/level_2/error.h>
#include <fll/level_2/fss.h>
#include <fll/level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_identify_version_
  #define fss_identify_major_version f_string_ascii_0
  #define fss_identify_minor_version f_string_ascii_5
  #define fss_identify_micro_version f_string_ascii_4
  #define fss_identify_version fss_identify_major_version f_string_ascii_period fss_identify_minor_version f_string_ascii_period fss_identify_micro_version
#endif // _di_fss_identify_version_

#ifndef _di_fss_identify_name_
  #define fss_identify_name "fss_identify"
  #define fss_identify_name_long "FSS Identify"
#endif // _di_fss_identify_name_

#ifndef _di_fss_identify_defines_
  #define fss_identify_short_line  "l"
  #define fss_identify_short_name  "n"
  #define fss_identify_short_total "T"
  #define fss_identify_short_type  "t"

  #define fss_identify_long_line  "line"
  #define fss_identify_long_name  "name"
  #define fss_identify_long_total "total"
  #define fss_identify_long_type  "type"

  enum {
    fss_identify_parameter_help,
    fss_identify_parameter_light,
    fss_identify_parameter_dark,
    fss_identify_parameter_no_color,
    fss_identify_parameter_verbosity_quiet,
    fss_identify_parameter_verbosity_normal,
    fss_identify_parameter_verbosity_verbose,
    fss_identify_parameter_verbosity_debug,
    fss_identify_parameter_version,

    fss_identify_parameter_line,
    fss_identify_parameter_name,
    fss_identify_parameter_total,
    fss_identify_parameter_type,
  };

  #define fss_identify_console_parameter_t_initialize \
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
      f_console_parameter_t_initialize(fss_identify_short_line, fss_identify_long_line, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_identify_short_name, fss_identify_long_name, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_identify_short_total, fss_identify_long_total, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(fss_identify_short_type, fss_identify_long_type, 0, 0, f_console_type_normal), \
    }

  #define fss_identify_total_parameters 13
#endif // _di_fss_identify_defines_

#ifndef _di_fss_identify_data_t_
  typedef struct {
    f_console_parameter_t parameters[fss_identify_total_parameters];

    f_array_lengths_t remaining;
    bool process_pipe;

    f_file_t output;
    fll_error_print_t error;
    fll_error_print_t warning;

    f_color_context_t context;
  } fss_identify_main_t;

  #define fss_identify_data_initialize \
    { \
      fss_identify_console_parameter_t_initialize, \
      f_array_lengths_t_initialize, \
      F_false, \
      macro_f_file_t_initialize2(f_type_output, f_type_descriptor_output, f_file_flag_write_only), \
      fll_error_print_t_initialize, \
      macro_fll_error_print_t_initialize_warning(), \
      f_color_context_t_initialize, \
    }
#endif // _di_fss_identify_data_t_

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
#ifndef _di_fss_identify_print_help_
  extern f_status_t fss_identify_print_help(const f_file_t output, const f_color_context_t context);
#endif // _di_fss_identify_print_help_

/**
 * Execute main program.
 *
 * Be sure to call fss_identify_main_delete() after executing this.
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
 * @see fss_identify_main_delete()
 */
#ifndef _di_fss_identify_main_
  extern f_status_t fss_identify_main(const f_console_arguments_t arguments, fss_identify_main_t *main);
#endif // _di_fss_identify_main_

/**
 * Deallocate main.
 *
 * Be sure to call this after executing fss_identify_main().
 *
 * @param main
 *   The program main.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fss_identify_main()
 */
#ifndef _di_fss_identify_main_delete_
  extern f_status_t fss_identify_main_delete(fss_identify_main_t *main);
#endif // _di_fss_identify_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_identify_h
