/**
 * FLL - Level 3
 *
 * Project: UTF-8
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * This is intendend to support Unicode 14.0.
 *
 * This is a program for handling basic UTF-8 related conversions.
 *   - Convert from UTF-8 character to binary.
 *   - Convert from Unicode Codepoint (such as U+0000) to binary.
 *   - Convert from UTF-8 binary to character.
 *   - Convert from UTF-8 binary to Unicode Codepoint (such as U+0000).
 */
#ifndef _utf8_h
#define _utf8_h

// Libc includes.
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// If limits.h does not provide PATH_MAX, define it instead of relying on <linux/limits.h>.
#ifndef PATH_MAX
#define PATH_MAX 4096
#endif /* PATH_MAX */

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/color.h>
#include <fll/level_0/console.h>
#include <fll/level_0/conversion.h>
#include <fll/level_0/file.h>
#include <fll/level_0/path.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>
#include <fll/level_0/signal.h>

// FLL-1 includes.
#include <fll/level_1/console.h>
#include <fll/level_1/conversion.h>
#include <fll/level_1/print.h>
#include <fll/level_1/string.h>
#include <fll/level_1/utf.h>

// FLL-2 includes.
#include <fll/level_2/error.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_program_version_
  #define UTF8_program_version_major_s F_string_ascii_0_s
  #define UTF8_program_version_minor_s F_string_ascii_5_s
  #define UTF8_program_version_micro_s F_string_ascii_8_s

  #define UTF8_program_version_major_s_length F_string_ascii_0_s_length
  #define UTF8_program_version_minor_s_length F_string_ascii_5_s_length
  #define UTF8_program_version_micro_s_length F_string_ascii_8_s_length

  #if !(defined(UTF8_program_version_nano_prefix_s) && defined(UTF8_program_version_nano_prefix_s_length))
    #define UTF8_program_version_nano_prefix_s
    #define UTF8_program_version_nano_prefix_s_length 0
  #endif // !(defined(UTF8_program_version_nano_prefix_s) && defined(UTF8_program_version_nano_prefix_s_length))

  #if !(defined(UTF8_program_version_nano_s) && defined(UTF8_program_version_nano_s_length))
    #define UTF8_program_version_nano_s
    #define UTF8_program_version_nano_s_length 0
  #endif // !(defined(UTF8_program_version_nano_s) && defined(UTF8_program_version_nano_s_length))

  #define UTF8_program_version_s UTF8_program_version_major_s F_string_ascii_period_s UTF8_program_version_minor_s F_string_ascii_period_s UTF8_program_version_micro_s UTF8_program_version_nano_prefix_s UTF8_program_version_nano_s

  #define UTF8_program_version_s_length UTF8_program_version_major_s_length + F_string_ascii_period_s_length + UTF8_program_version_minor_s_length + F_string_ascii_period_s_length + UTF8_program_version_micro_s_length + UTF8_program_version_nano_prefix_s_length + UTF8_program_version_nano_s_length

    extern const f_string_static_t utf8_program_version_s;
#endif // _di_utf8_program_version_

#ifndef _di_utf8_program_name_
  #define UTF8_program_name_s      "utf8"
  #define UTF8_program_name_long_s "UTF-8"

  #define UTF8_program_name_s_length      4
  #define UTF8_program_name_long_s_length 5

  extern const f_string_static_t utf8_program_name_s;
  extern const f_string_static_t utf8_program_name_long_s;
#endif // _di_utf8_program_name_

/**
 * Set to at least 4 to provide a UTF-8 friendly allocation step.
 */
#ifndef _di_utf8_default_allocation_step_
  #define utf8_default_allocation_step_d 16
#endif // _di_utf8_default_allocation_step_

#ifndef _di_utf8_defines_
  #define utf8_signal_check_d 10000

  #define utf8_string_from_s "from"
  #define utf8_string_to_s   "to"

  #define utf8_string_open_s    "open"
  #define utf8_string_process_s "process"

  #define utf8_string_verified_valid_s     "Verified Valid"
  #define utf8_string_verified_valid_not_s "Verified Invalid"

  #define utf8_string_combining_is_s  "C"
  #define utf8_string_combining_not_s "N"
  #define utf8_string_unknown_s       "?"

  #define utf8_string_width_0_s "0"
  #define utf8_string_width_1_s "1"
  #define utf8_string_width_2_s "2"

  #define utf8_string_from_s_length 4
  #define utf8_string_to_s_length   2

  #define utf8_string_open_s_length    4
  #define utf8_string_process_s_length 7

  #define utf8_string_verified_valid_s_length     14
  #define utf8_string_verified_valid_not_s_length 16

  #define utf8_string_combining_is_s_length  1
  #define utf8_string_combining_not_s_length 1
  #define utf8_string_unknown_s_length       1

  #define utf8_string_width_0_s_length 1
  #define utf8_string_width_1_s_length 1
  #define utf8_string_width_2_s_length 1

  #define utf8_character_valid_not_s "�"

  #define utf8_short_from_binary_s    "b"
  #define utf8_short_from_codepoint_s "c"
  #define utf8_short_from_file_s      "f"

  #define utf8_short_headers_s       "H"
  #define utf8_short_separate_s      "S"
  #define utf8_short_strip_invalid_s "s"
  #define utf8_short_verify_s        "v"

  #define utf8_short_to_binary_s    "B"
  #define utf8_short_to_codepoint_s "C"
  #define utf8_short_to_combining_s "O"
  #define utf8_short_to_file_s      "F"
  #define utf8_short_to_width_s     "W"

  #define utf8_long_from_binary_s    "from_binary"
  #define utf8_long_from_codepoint_s "from_codepoint"
  #define utf8_long_from_file_s      "from_file"

  #define utf8_long_headers_s       "headers"
  #define utf8_long_separate_s      "separate"
  #define utf8_long_strip_invalid_s "strip_invalid"
  #define utf8_long_verify_s        "verify"

  #define utf8_long_to_binary_s    "to_binary"
  #define utf8_long_to_codepoint_s "to_codepoint"
  #define utf8_long_to_combining_s "to_combining"
  #define utf8_long_to_file_s      "to_file"
  #define utf8_long_to_width_s     "to_width"

  enum {
    utf8_parameter_help_e,
    utf8_parameter_light_e,
    utf8_parameter_dark_e,
    utf8_parameter_no_color_e,
    utf8_parameter_verbosity_quiet_e,
    utf8_parameter_verbosity_normal_e,
    utf8_parameter_verbosity_verbose_e,
    utf8_parameter_verbosity_debug_e,
    utf8_parameter_version_e,

    utf8_parameter_from_binary_e,
    utf8_parameter_from_codepoint_e,
    utf8_parameter_from_file_e,

    utf8_parameter_headers_e,
    utf8_parameter_separate_e,
    utf8_parameter_strip_invalid_e,

    utf8_parameter_to_binary_e,
    utf8_parameter_to_codepoint_e,
    utf8_parameter_to_combining_e,
    utf8_parameter_to_file_e,
    utf8_parameter_to_width_e,

    utf8_parameter_verify_e,
  };

  #define utf8_console_parameter_t_initialize \
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
      macro_f_console_parameter_t_initialize(utf8_short_from_binary_s, utf8_long_from_binary_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(utf8_short_from_codepoint_s, utf8_long_from_codepoint_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(utf8_short_from_file_s, utf8_long_from_file_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(utf8_short_headers_s, utf8_long_headers_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(utf8_short_separate_s, utf8_long_headers_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(utf8_short_strip_invalid_s, utf8_long_strip_invalid_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(utf8_short_to_binary_s, utf8_long_to_binary_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(utf8_short_to_codepoint_s, utf8_long_to_codepoint_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(utf8_short_to_combining_s, utf8_long_to_combining_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(utf8_short_to_file_s, utf8_long_to_file_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(utf8_short_to_width_s, utf8_long_to_width_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(utf8_short_verify_s, utf8_long_verify_s, 0, 0, f_console_type_normal_e), \
    }

  #define utf8_total_parameters_d 21
#endif // _di_utf8_defines_

/**
 * Modes used to designate how to the input and output are to be processed.
 *
 * utf8_mode_from_*:
 *   - binary:    The input format is binary.
 *   - codepoint: The input format is codepoint (U+XXXX or U+XXXXXX).
 *
 * utf8_mode_to_*:
 *   - binary:    The outout format is binary.
 *   - codepoint: The outout format is codepoint (U+XXXX or U+XXXXXX).
 *   - combining: The outout format is whether or not character is combining (may be used with "width").
 *   - width:     The outout format is how wide the character is (may be used with "combining").
 */
#ifndef _di_utf8_modes_
  #define utf8_mode_from_binary_d    0x1
  #define utf8_mode_from_codepoint_d 0x2
  #define utf8_mode_to_binary_d      0x4
  #define utf8_mode_to_codepoint_d   0x8
  #define utf8_mode_to_combining_d   0x10
  #define utf8_mode_to_width_d       0x20
#endif // _di_utf8_modes_

/**
 * The main program data.
 *
 * parameters:   The state of pre-defined parameters passed to the program.
 * remaining:    The remaining, non-pre-defined parameters, passed to the program.
 * process_pipe: Designate whether or not to process the input pipe.
 * output:       The output file for general printing.
 * error:        The output file for error printing.
 * warning:      The output file for warning printing.
 * signal:       The process signal management structure.
 * context:      The color context.
 */
#ifndef _di_utf8_main_t_
  typedef struct {
    f_console_parameter_t parameters[utf8_total_parameters_d];

    f_array_lengths_t remaining;
    bool process_pipe;

    fl_print_t output;
    fl_print_t error;
    fl_print_t warning;

    f_signal_t signal;

    f_color_context_t context;
  } utf8_main_t;

  #define utf8_main_t_initialize \
    { \
      utf8_console_parameter_t_initialize, \
      f_array_lengths_t_initialize, \
      F_false, \
      fl_print_t_initialize, \
      macro_fl_print_t_initialize_error(), \
      macro_fl_print_t_initialize_warning(), \
      f_signal_t_initialize, \
      f_color_context_t_initialize, \
    }
#endif // _di_utf8_main_t_

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
#ifndef _di_utf8_print_help_
  extern f_status_t utf8_print_help(const f_file_t file, const f_color_context_t context);
#endif // _di_utf8_print_help_

/**
 * Execute main program.
 *
 * Be sure to call utf8_main_delete() after executing this.
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
 *   F_true on success when performing verification and verify passed.
 *   F_false on success when performing verification and verify failed.
 *   F_signal on (exit) signal received.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see utf8_main_delete()
 */
#ifndef _di_utf8_main_
  extern f_status_t utf8_main(utf8_main_t * const main, const f_console_arguments_t *arguments);
#endif // _di_utf8_main_

/**
 * Deallocate main.
 *
 * Be sure to call this after executing utf8_main().
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see utf8_main()
 */
#ifndef _di_utf8_main_delete_
  extern f_status_t utf8_main_delete(utf8_main_t *main);
#endif // _di_utf8_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _utf8_h
