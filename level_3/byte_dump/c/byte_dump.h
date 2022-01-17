/**
 * FLL - Level 3
 *
 * Project: Byte Dump
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * This is intendend to support Unicode 14.0.
 *
 * When using "text" mode, this program attempts to translate UTF-8 sequences such that certain codes don't cause printing problems.
 * There may be cases where there are unknown codes that get printed and the invalid UTF-8 marker may be displayed not by this program but instead by the shell or some other program.
 * This can potentially be seen with the program "less".
 * The solution is to add the invalid character codes to this project so that this project can properly print the invalid UTF-8 marker and therefore properly display the information.
 */
#ifndef _byte_dump_h

// libc includes.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// fll-0 includes.
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

#ifndef _di_byte_dump_program_version_
  #define byte_dump_program_version_major_s F_string_ascii_0_s
  #define byte_dump_program_version_minor_s F_string_ascii_5_s
  #define byte_dump_program_version_micro_s F_string_ascii_8_s

  #ifndef byte_dump_program_version_nano_prefix_s
    #define byte_dump_program_version_nano_prefix_s
  #endif

  #ifndef byte_dump_program_version_nano_s
    #define byte_dump_program_version_nano_s
  #endif

  #define byte_dump_version_s byte_dump_program_version_major_s F_string_ascii_period_s byte_dump_program_version_minor_s F_string_ascii_period_s byte_dump_program_version_micro_s byte_dump_program_version_nano_prefix_s byte_dump_program_version_nano_s
#endif // _di_byte_dump_program_version_

#ifndef _di_byte_dump_program_name_
  #define byte_dump_program_name_s      "byte_dump"
  #define byte_dump_program_name_long_s "Byte Dump"
#endif // _di_byte_dump_program_name_

/**
 * Set to at least 4 to provide a UTF-8 friendly allocation step.
 */
#ifndef _di_byte_dump_default_allocation_step_
  #define byte_dump_default_allocation_step_d 4
#endif // _di_byte_dump_default_allocation_step_

/**
 * Byte Dump defines.
 *
 * byte_dump_mode_*:
 *   - hexidecimal: Display using hexidecimal notation (base 16).
 *   - duodecimal:  Display using duodecimal notation (base 12).
 *   - octal:       Display using octal notation (base 8).
 *   - binary:      Display using binary notation (base 2).
 *   - decimal:     Display using decimal notation (base 10).
 *
 * byte_dump_presentation_*:
 *   - normal:  Normal presentation mode.
 *   - simple:  Simple presentation mode.
 *   - classic: Classic presentation mode.
 */
#ifndef _di_byte_dump_defines_
  enum {
    byte_dump_mode_hexidecimal_e = 1,
    byte_dump_mode_duodecimal_e,
    byte_dump_mode_octal_e,
    byte_dump_mode_binary_e,
    byte_dump_mode_decimal_e,
  };

  enum {
    byte_dump_presentation_normal_e = 1,
    byte_dump_presentation_simple_e,
    byte_dump_presentation_classic_e,
  };

  #define byte_dump_option_wide_d 0x1

  #define byte_dump_signal_check_d 10000

  #define byte_dump_sequence_acknowledge_s               "␆"
  #define byte_dump_sequence_acknowledge_negative_s      "␕"
  #define byte_dump_sequence_backspace_s                 "␈"
  #define byte_dump_sequence_bell_s                      "␇"
  #define byte_dump_sequence_cancel_s                    "␘"
  #define byte_dump_sequence_carriage_return_s           "␍"
  #define byte_dump_sequence_data_link_escape_s          "␐"
  #define byte_dump_sequence_delete_s                    "␡"
  #define byte_dump_sequence_device_control_1_s          "␑"
  #define byte_dump_sequence_device_control_2_s          "␒"
  #define byte_dump_sequence_device_control_3_s          "␓"
  #define byte_dump_sequence_device_control_4_s          "␔"
  #define byte_dump_sequence_end_of_enquiry_s            "␅"
  #define byte_dump_sequence_end_of_medium_s             "␙"
  #define byte_dump_sequence_end_of_text_s               "␃"
  #define byte_dump_sequence_end_of_transmission_s       "␄"
  #define byte_dump_sequence_end_of_transmission_block_s "␗"
  #define byte_dump_sequence_escape_s                    "␛"
  #define byte_dump_sequence_file_separator_s            "␜"
  #define byte_dump_sequence_form_feed_s                 "␌"
  #define byte_dump_sequence_group_separator_s           "␝"
  #define byte_dump_sequence_line_feed_s                 "␊"
  #define byte_dump_sequence_new_line_s                  "␤"
  #define byte_dump_sequence_null_s                      "␀"
  #define byte_dump_sequence_record_separator_s          "␞"
  #define byte_dump_sequence_shift_in_s                  "␏"
  #define byte_dump_sequence_shift_out_s                 "␎"
  #define byte_dump_sequence_space_s                     "␠"
  #define byte_dump_sequence_start_of_header_s           "␁"
  #define byte_dump_sequence_start_of_text_s             "␂"
  #define byte_dump_sequence_substitute_s                "␚"
  #define byte_dump_sequence_synchronous_idle_s          "␖"
  #define byte_dump_sequence_tab_s                       "␉"
  #define byte_dump_sequence_tab_vertical_s              "␋"
  #define byte_dump_sequence_unit_separator_s            "␟"

  #define byte_dump_character_wall_s        "|"
  #define byte_dump_character_placeholder_s "␣" // other likely choices: (substitute form 1: '␚', substitute form 2: '␦').
  #define byte_dump_character_incomplete_s  "�"
  #define byte_dump_character_unused_s      "�"

  #define byte_dump_short_binary_s      "b"
  #define byte_dump_short_decimal_s     "d"
  #define byte_dump_short_duodecimal_s  "D"
  #define byte_dump_short_hexidecimal_s "x"
  #define byte_dump_short_octal_s       "o"
  #define byte_dump_short_unicode_s     "U"

  #define byte_dump_short_first_s       "f"
  #define byte_dump_short_last_s        "l"

  #define byte_dump_short_narrow_s      "N"
  #define byte_dump_short_placeholder_s "p"
  #define byte_dump_short_text_s        "t"
  #define byte_dump_short_wide_s        "W"
  #define byte_dump_short_width_s       "w"

  #define byte_dump_long_binary_s      "binary"
  #define byte_dump_long_decimal_s     "decimal"
  #define byte_dump_long_duodecimal_s  "duodecimal"
  #define byte_dump_long_hexidecimal_s "hexidecimal"
  #define byte_dump_long_octal_s       "octal"
  #define byte_dump_long_unicode_s     "unicode"

  #define byte_dump_long_first_s "first" // First offset byte size.
  #define byte_dump_long_last_s  "last"  // Last offset byte size.

  #define byte_dump_long_narrow_s      "narrow"      // Each character in the displyed text will take at least 1 columns.
  #define byte_dump_long_placeholder_s "placeholder" // Display (colored) placeholders to signify codes that are UTF-8 fragments.
  #define byte_dump_long_text_s        "text"        // Display text
  #define byte_dump_long_wide_s        "wide"        // Each character in the displyed text will take at least 2 columns.
  #define byte_dump_long_width_s       "width"       // Number of characters to display per row.

  #define byte_dump_long_normal_s  "normal"  // Use normal presentation, displaying UTF-8 sequence codes for ASCII special codes.
  #define byte_dump_long_simple_s  "simple"  // Use simple presentation, displaying spaces for ASCII special codes instead of UTF-8 sequence codes.
  #define byte_dump_long_classic_s "classic" // Use classic presentation, displaying periods for ASCII special codes instead of UTF-8 sequence codes.

  enum {
    byte_dump_parameter_help_e,
    byte_dump_parameter_light_e,
    byte_dump_parameter_dark_e,
    byte_dump_parameter_no_color_e,
    byte_dump_parameter_verbosity_quiet_e,
    byte_dump_parameter_verbosity_normal_e,
    byte_dump_parameter_verbosity_verbose_e,
    byte_dump_parameter_verbosity_debug_e,
    byte_dump_parameter_version_e,

    byte_dump_parameter_binary_e,
    byte_dump_parameter_decimal_e,
    byte_dump_parameter_duodecimal_e,
    byte_dump_parameter_hexidecimal_e,
    byte_dump_parameter_octal_e,
    byte_dump_parameter_unicode_e,

    byte_dump_parameter_first_e,
    byte_dump_parameter_last_e,

    byte_dump_parameter_narrow_e,
    byte_dump_parameter_placeholder_e,
    byte_dump_parameter_text_e,
    byte_dump_parameter_wide_e,
    byte_dump_parameter_width_e,

    byte_dump_parameter_normal_e,
    byte_dump_parameter_simple_e,
    byte_dump_parameter_classic_e,
  };

  #define byte_dump_console_parameter_t_initialize \
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
      macro_f_console_parameter_t_initialize(byte_dump_short_binary_s, byte_dump_long_binary_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(byte_dump_short_decimal_s, byte_dump_long_decimal_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(byte_dump_short_duodecimal_s, byte_dump_long_duodecimal_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(byte_dump_short_hexidecimal_s, byte_dump_long_hexidecimal_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(byte_dump_short_octal_s, byte_dump_long_octal_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(byte_dump_short_unicode_s, byte_dump_long_unicode_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(byte_dump_short_first_s, byte_dump_long_first_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(byte_dump_short_last_s, byte_dump_long_last_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(byte_dump_short_narrow_s, byte_dump_long_narrow_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(byte_dump_short_placeholder_s, byte_dump_long_placeholder_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(byte_dump_short_text_s, byte_dump_long_text_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(byte_dump_short_wide_s, byte_dump_long_wide_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(byte_dump_short_width_s, byte_dump_long_width_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(0, byte_dump_long_normal_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(0, byte_dump_long_simple_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(0, byte_dump_long_classic_s, 0, 0, f_console_type_normal_e), \
    }

  #define byte_dump_total_parameters_d 25
#endif // _di_byte_dump_defines_

#ifndef _di_byte_dump_main_t_
  typedef struct {
    f_console_parameter_t parameters[byte_dump_total_parameters_d];

    f_array_lengths_t remaining;
    bool process_pipe;

    fl_print_t output;
    fl_print_t error;
    fl_print_t warning;

    f_signal_t signal;

    uint64_t first;
    uint64_t last;
    uint8_t width;
    uint8_t mode;
    uint8_t presentation;
    uint8_t options;

    f_color_context_t context;
  } byte_dump_main_t;

  #define byte_dump_main_t_initialize \
    { \
      byte_dump_console_parameter_t_initialize, \
      f_array_lengths_t_initialize, \
      F_false, \
      fl_print_t_initialize, \
      macro_fl_print_t_initialize_error(), \
      macro_fl_print_t_initialize_warning(), \
      f_signal_t_initialize, \
      0, \
      0, \
      8, \
      byte_dump_option_wide_d, \
      byte_dump_mode_hexidecimal_e, \
      byte_dump_presentation_normal_e, \
      f_color_context_t_initialize, \
    }
#endif // _di_byte_dump_main_t_

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
#ifndef _di_byte_dump_print_help_
  extern f_status_t byte_dump_print_help(const f_file_t file, const f_color_context_t context);
#endif // _di_byte_dump_print_help_

/**
 * Execute main program.
 *
 * Be sure to call byte_dump_main_delete() after executing this.
 *
 * @param main
 *   The main program data.
 * @param arguments
 *   The parameters passed to the process.
 *
 * If main.signal is non-zero, then this blocks and handles the following signals:
 *   - F_signal_abort
 *   - F_signal_broken_pipe
 *   - F_signal_hangup
 *   - F_signal_interrupt
 *   - F_signal_quit
 *   - F_signal_termination
 *
 * @return
 *   F_none on success.
 *
 *   F_interrupt (with error bit) on receiving a process signal, such as an interrupt signal.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see byte_dump_main_delete()
 */
#ifndef _di_byte_dump_main_
  extern f_status_t byte_dump_main(byte_dump_main_t * const main, const f_console_arguments_t *arguments);
#endif // _di_byte_dump_main_

/**
 * Deallocate main.
 *
 * Be sure to call this after executing byte_dump_main().
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see byte_dump_main()
 */
#ifndef _di_byte_dump_main_delete_
  extern f_status_t byte_dump_main_delete(byte_dump_main_t * const main);
#endif // _di_byte_dump_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _byte_dump_h
