/**
 * FLL - Level 3
 *
 * Project: FSS Identify
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * This is the program is intended to be used to identify an FSS file or FSS data.
 *
 * A valid FSS file or FSS data will have a header starting with the pound character '#'.
 *
 * This program utilizes the Featureless Linux Library.
 */
#ifndef _fss_identify_h
#define _fss_identify_h

// Libc includes.
#include <unistd.h>

// FLL-0 includes.
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
#include <fll/level_0/signal.h>

// FLL-1 includes.
#include <fll/level_1/console.h>
#include <fll/level_1/conversion.h>
#include <fll/level_1/fss.h>
#include <fll/level_1/print.h>
#include <fll/level_1/string.h>

// FLL-2 includes.
#include <fll/level_2/error.h>
#include <fll/level_2/fss.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_identify_program_version_
  #define FSS_IDENTIFY_program_version_major_s F_string_ascii_0_s
  #define FSS_IDENTIFY_program_version_minor_s F_string_ascii_5_s
  #define FSS_IDENTIFY_program_version_micro_s F_string_ascii_8_s

  #define FSS_IDENTIFY_program_version_major_s_length F_string_ascii_0_s_length
  #define FSS_IDENTIFY_program_version_minor_s_length F_string_ascii_5_s_length
  #define FSS_IDENTIFY_program_version_micro_s_length F_string_ascii_8_s_length

  #if !(defined(FSS_IDENTIFY_program_version_nano_prefix_s) && defined(FSS_IDENTIFY_program_version_nano_prefix_s_length))
    #define FSS_IDENTIFY_program_version_nano_prefix_s
    #define FSS_IDENTIFY_program_version_nano_prefix_s_length 0
  #endif // !(defined(FSS_IDENTIFY_program_version_nano_prefix_s) && defined(FSS_IDENTIFY_program_version_nano_prefix_s_length))

  #if !(defined(FSS_IDENTIFY_program_version_nano_s) && defined(FSS_IDENTIFY_program_version_nano_s_length))
    #define FSS_IDENTIFY_program_version_nano_s
    #define FSS_IDENTIFY_program_version_nano_s_length 0
  #endif // !(defined(FSS_IDENTIFY_program_version_nano_s) && defined(FSS_IDENTIFY_program_version_nano_s_length))

  #define FSS_IDENTIFY_program_version_s FSS_IDENTIFY_program_version_major_s F_string_ascii_period_s FSS_IDENTIFY_program_version_minor_s F_string_ascii_period_s FSS_IDENTIFY_program_version_micro_s FSS_IDENTIFY_program_version_nano_prefix_s FSS_IDENTIFY_program_version_nano_s

  #define FSS_IDENTIFY_program_version_s_length FSS_IDENTIFY_program_version_major_s_length + F_string_ascii_period_s_length + FSS_IDENTIFY_program_version_minor_s_length + F_string_ascii_period_s_length + FSS_IDENTIFY_program_version_micro_s_length + FSS_IDENTIFY_program_version_nano_prefix_s_length + FSS_IDENTIFY_program_version_nano_s_length

  const f_string_static_t fss_identify_program_version_s;
#endif // _di_fss_identify_program_version_

#ifndef _di_fss_identify_program_name_
  #define FSS_IDENTIFY_program_name_s      "fss_identify"
  #define FSS_IDENTIFY_program_name_long_s "FSS Identify"

  #define FSS_IDENTIFY_program_name_s_length      12
  #define FSS_IDENTIFY_program_name_long_s_length 12

  const f_string_static_t fss_identify_program_name_s;
  const f_string_static_t fss_identify_program_name_long_s;
#endif // _di_fss_identify_program_name_

#ifndef _di_fss_identify_defines_
  #define fss_identify_signal_check_d 10000

  #define fss_identify_short_content_s "c"
  #define fss_identify_short_line_s    "l"
  #define fss_identify_short_name_s    "n"
  #define fss_identify_short_object_s  "o"
  #define fss_identify_short_total_s   "t"

  #define fss_identify_long_content_s "content"
  #define fss_identify_long_line_s    "line"
  #define fss_identify_long_name_s    "name"
  #define fss_identify_long_object_s  "object"
  #define fss_identify_long_total_s   "total"

  enum {
    fss_identify_parameter_help_e,
    fss_identify_parameter_light_e,
    fss_identify_parameter_dark_e,
    fss_identify_parameter_no_color_e,
    fss_identify_parameter_verbosity_quiet_e,
    fss_identify_parameter_verbosity_normal_e,
    fss_identify_parameter_verbosity_verbose_e,
    fss_identify_parameter_verbosity_debug_e,
    fss_identify_parameter_version_e,

    fss_identify_parameter_content_e,
    fss_identify_parameter_line_e,
    fss_identify_parameter_name_e,
    fss_identify_parameter_object_e,
    fss_identify_parameter_total_e,
  };

  #define fss_identify_console_parameter_t_initialize \
    { \
      macro_f_console_parameter_t_initialize(f_console_standard_short_help_s.string, f_console_standard_long_help_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_light_s.string, f_console_standard_long_light_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_dark_s.string, f_console_standard_long_dark_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_no_color_s.string, f_console_standard_long_no_color_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_quiet_s.string, f_console_standard_long_quiet_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_normal_s.string, f_console_standard_long_normal_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_verbose_s.string, f_console_standard_long_verbose_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_debug_s.string, f_console_standard_long_debug_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_version_s.string, f_console_standard_long_version_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(fss_identify_short_content_s, fss_identify_long_content_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_identify_short_line_s, fss_identify_long_line_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_identify_short_name_s, fss_identify_long_name_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_identify_short_object_s, fss_identify_long_object_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_identify_short_total_s, fss_identify_long_total_s, 0, 0, f_console_type_normal_e), \
    }

  #define fss_identify_total_parameters_d 14
#endif // _di_fss_identify_defines_

#ifndef _di_fss_identify_data_t_
  typedef struct {
    f_console_parameters_t parameters;

    f_array_lengths_t remaining;
    bool process_pipe;

    fl_print_t output;
    fl_print_t error;
    fl_print_t warning;

    f_signal_t signal;

    f_color_context_t context;
  } fss_identify_main_t;

  #define fss_identify_data_initialize \
    { \
      f_console_parameters_t_initialize, \
      f_array_lengths_t_initialize, \
      F_false, \
      fl_print_t_initialize, \
      macro_fl_print_t_initialize_error(), \
      macro_fl_print_t_initialize_warning(), \
      f_signal_t_initialize, \
      f_color_context_t_initialize, \
    }
#endif // _di_fss_identify_data_t_

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
#ifndef _di_fss_identify_print_help_
  extern f_status_t fss_identify_print_help(const f_file_t file, const f_color_context_t context);
#endif // _di_fss_identify_print_help_

/**
 * Execute main program.
 *
 * Be sure to call fss_identify_main_delete() after executing this.
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
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fss_identify_main_delete()
 */
#ifndef _di_fss_identify_main_
  extern f_status_t fss_identify_main(fss_identify_main_t * const main, const f_console_arguments_t *arguments);
#endif // _di_fss_identify_main_

/**
 * Deallocate main.
 *
 * Be sure to call this after executing fss_identify_main().
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fss_identify_main()
 */
#ifndef _di_fss_identify_main_delete_
  extern f_status_t fss_identify_main_delete(fss_identify_main_t * const main);
#endif // _di_fss_identify_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_identify_h
