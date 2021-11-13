/**
 * FLL - Level 3
 *
 * Project: UTF-8
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This is intendend to support Unicode 14.0.
 *
 * This is a program for handling basic UTF-8 related conversions.
 * - Convert from UTF-8 character to binary.
 * - Convert from Unicode Codepoint (such as U+0000) to binary.
 * - Convert from UTF-8 binary to character.
 * - Convert from UTF-8 binary to Unicode Codepoint (such as U+0000).
 */
#ifndef _utf8_h

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
#include <fll/level_0/console.h>
#include <fll/level_0/conversion.h>
#include <fll/level_0/file.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>
#include <fll/level_0/signal.h>

// fll-1 includes
#include <fll/level_1/console.h>
#include <fll/level_1/conversion.h>
#include <fll/level_1/print.h>
#include <fll/level_1/string.h>
#include <fll/level_1/utf.h>

// fll-2 includes
#include <fll/level_2/error.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_program_version_
  #define utf8_program_version_major_s F_string_ascii_0_s
  #define utf8_program_version_minor_s F_string_ascii_5_s
  #define utf8_program_version_micro_s F_string_ascii_7_s

  #ifndef utf8_program_version_nano_prefix_s
    #define utf8_program_version_nano_prefix_s
  #endif

  #ifndef utf8_program_version_nano_s
    #define utf8_program_version_nano_s
  #endif

  #define utf8_version_s utf8_program_version_major_s F_string_ascii_period_s utf8_program_version_minor_s F_string_ascii_period_s utf8_program_version_micro_s utf8_program_version_nano_prefix_s utf8_program_version_nano_s
#endif // _di_utf8_program_version_

#ifndef _di_utf8_program_name_
  #define utf8_program_name_s      "utf8"
  #define utf8_program_name_long_s "UTF-8"
#endif // _di_utf8_program_name_

/**
 * Set to at least 4 to provide a UTF-8 friendly allocation step.
 */
#ifndef _di_utf8_default_allocation_step_
  #define utf8_default_allocation_step_d 4
#endif // _di_utf8_default_allocation_step_

#ifndef _di_utf8_defines_
  #define utf8_string_from_s "from"
  #define utf8_string_to_s   "to"

  #define utf8_string_open_s    "open"
  #define utf8_string_process_s "process"

  #define utf8_string_verified_valid_s     "Verified Valid"
  #define utf8_string_verified_valid_not_s "Verified Invalid"

  #define utf8_string_from_s_length 4
  #define utf8_string_to_s_length   2

  #define utf8_string_open_s_length    4
  #define utf8_string_process_s_length 7

  #define utf8_string_verified_valid_s_length     14
  #define utf8_string_verified_valid_not_s_length 16

  #define utf8_character_valid_not_s "�"

  #define utf8_short_from_binary_s    "b"
  #define utf8_short_from_codepoint_s "c"
  #define utf8_short_from_file_s      "f"

  #define utf8_short_headers_s       "H"
  #define utf8_short_strip_invalid_s "s"
  #define utf8_short_verify_s        "v"

  #define utf8_short_to_binary_s    "B"
  #define utf8_short_to_codepoint_s "C"
  #define utf8_short_to_file_s      "F"

  #define utf8_long_from_binary_s    "from_binary"
  #define utf8_long_from_codepoint_s "from_codepoint"
  #define utf8_long_from_file_s      "from_file"

  #define utf8_long_headers_s       "headers"
  #define utf8_long_strip_invalid_s "strip_invalid"
  #define utf8_long_verify_s        "verify"

  #define utf8_long_to_binary_s    "to_binary"
  #define utf8_long_to_codepoint_s "to_codepoint"
  #define utf8_long_to_file_s      "to_file"

  enum {
    utf8_parameter_help,
    utf8_parameter_light,
    utf8_parameter_dark,
    utf8_parameter_no_color,
    utf8_parameter_verbosity_quiet,
    utf8_parameter_verbosity_normal,
    utf8_parameter_verbosity_verbose,
    utf8_parameter_verbosity_debug,
    utf8_parameter_version,

    utf8_parameter_from_binary,
    utf8_parameter_from_codepoint,
    utf8_parameter_from_file,

    utf8_parameter_headers,
    utf8_parameter_strip_invalid,

    utf8_parameter_to_binary,
    utf8_parameter_to_codepoint,
    utf8_parameter_to_file,

    utf8_parameter_verify,
  };

  #define utf8_console_parameter_t_initialize \
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
      f_console_parameter_t_initialize(utf8_short_from_binary_s, utf8_long_from_binary_s, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(utf8_short_from_codepoint_s, utf8_long_from_codepoint_s, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(utf8_short_from_file_s, utf8_long_from_file_s, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(utf8_short_headers_s, utf8_long_headers_s, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(utf8_short_strip_invalid_s, utf8_long_strip_invalid_s, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(utf8_short_to_binary_s, utf8_long_to_binary_s, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(utf8_short_to_codepoint_s, utf8_long_to_codepoint_s, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(utf8_short_to_file_s, utf8_long_to_file_s, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(utf8_short_verify_s, utf8_long_verify_s, 0, 0, f_console_type_normal), \
    }

  #define utf8_total_parameters_d 18
#endif // _di_utf8_defines_

/**
 * utf8_mode_from_*:
 *   - binary:    The input source is binary.
 *   - codepoint: The input source is codepoint (U+XXXX or U+XXXXXX).
 *
 * utf8_mode_to_*:
 *   - binary:    The outout destination is binary.
 *   - codepoint: The outout destination is codepoint (U+XXXX or U+XXXXXX).
 */
#ifndef _di_utf8_modes_
  #define utf8_mode_from_binary_d    0x1
  #define utf8_mode_from_codepoint_d 0x2
  #define utf8_mode_to_binary_d      0x4
  #define utf8_mode_to_codepoint_d   0x8
#endif // _di_utf8_modes_

#ifndef _di_utf8_main_t_
  typedef struct {
    f_console_parameter_t parameters[utf8_total_parameters_d];

    f_array_lengths_t remaining;
    bool process_pipe;

    fl_print_t output;
    fl_print_t error;
    fl_print_t warning;

    f_signal_t signal;

    f_file_t destination;
    uint8_t mode;

    f_string_dynamic_t buffer;
    f_string_dynamic_t file_input;
    f_string_dynamic_t file_output;
    f_string_dynamic_t text;

    f_string_dynamic_t separate_character;
    f_string_dynamic_t separate_source;

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
      f_file_t_initialize, \
      utf8_mode_from_binary_d | utf8_mode_to_codepoint_d, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
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
