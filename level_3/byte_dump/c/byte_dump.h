/**
 * FLL - Level 3
 *
 * Project: Byte Dump
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This is intendend to support Unicode 12.1.
 *
 * When using "text" mode, this program attempts to translate UTF-8 sequences such that certain codes don't cause printing problems.
 * There may be cases where there are unknown codes that get printed and the invalid UTF-8 marker may be displayed not by this program but instead by the shell or some other program.
 * This can potentially be seen with the program "less".
 * The solution is to add the invalid character codes to this project so that this project can properly print the invalid UTF-8 marker and therefore properly display the information.
 */
#ifndef _byte_dump_h

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

#ifndef _di_byte_dump_version_
  #define byte_dump_major_version f_string_ascii_0
  #define byte_dump_minor_version f_string_ascii_5
  #define byte_dump_micro_version f_string_ascii_6

  #ifndef byte_dump_nano_version_prefix
    #define byte_dump_nano_version_prefix
  #endif

  #ifndef byte_dump_nano_version
    #define byte_dump_nano_version
  #endif

  #define byte_dump_version byte_dump_major_version f_string_ascii_period byte_dump_minor_version f_string_ascii_period byte_dump_micro_version byte_dump_nano_version_prefix byte_dump_nano_version
#endif // _di_byte_dump_version_

#ifndef _di_byte_dump_name_
  #define byte_dump_name      "byte_dump"
  #define byte_dump_name_long "Byte Dump"
#endif // _di_byte_dump_name_

#ifndef _di_byte_dump_default_allocation_step_
  // Set to at least 4 to provide a UTF-8 friendly allocation step.
  #define byte_dump_default_allocation_step 4
#endif // _di_byte_dump_default_allocation_step_

#ifndef _di_byte_dump_defines_
  enum {
    byte_dump_mode_hexidecimal = 1,
    byte_dump_mode_duodecimal,
    byte_dump_mode_octal,
    byte_dump_mode_binary,
    byte_dump_mode_decimal,
  };

  enum {
    byte_dump_presentation_normal = 1,
    byte_dump_presentation_simple,
    byte_dump_presentation_classic,
  };

  #define byte_dump_sequence_acknowledge               "␆"
  #define byte_dump_sequence_acknowledge_negative      "␕"
  #define byte_dump_sequence_backspace                 "␈"
  #define byte_dump_sequence_bell                      "␇"
  #define byte_dump_sequence_cancel                    "␘"
  #define byte_dump_sequence_carriage_return           "␍"
  #define byte_dump_sequence_data_link_escape          "␐"
  #define byte_dump_sequence_delete                    "␡"
  #define byte_dump_sequence_device_control_1          "␑"
  #define byte_dump_sequence_device_control_2          "␒"
  #define byte_dump_sequence_device_control_3          "␓"
  #define byte_dump_sequence_device_control_4          "␔"
  #define byte_dump_sequence_end_of_enquiry            "␅"
  #define byte_dump_sequence_end_of_medium             "␙"
  #define byte_dump_sequence_end_of_text               "␃"
  #define byte_dump_sequence_end_of_transmission       "␄"
  #define byte_dump_sequence_end_of_transmission_block "␗"
  #define byte_dump_sequence_escape                    "␛"
  #define byte_dump_sequence_file_separator            "␜"
  #define byte_dump_sequence_form_feed                 "␌"
  #define byte_dump_sequence_group_separator           "␝"
  #define byte_dump_sequence_line_feed                 "␊"
  #define byte_dump_sequence_new_line                  "␤"
  #define byte_dump_sequence_null                      "␀"
  #define byte_dump_sequence_record_separator          "␞"
  #define byte_dump_sequence_shift_in                  "␏"
  #define byte_dump_sequence_shift_out                 "␎"
  #define byte_dump_sequence_space                     "␠"
  #define byte_dump_sequence_start_of_header           "␁"
  #define byte_dump_sequence_start_of_text             "␂"
  #define byte_dump_sequence_substitute                "␚"
  #define byte_dump_sequence_synchronous_idle          "␖"
  #define byte_dump_sequence_tab                       "␉"
  #define byte_dump_sequence_tab_vertical              "␋"
  #define byte_dump_sequence_unit_separator            "␟"

  #define byte_dump_character_wall        "|"
  #define byte_dump_character_placeholder "␣" // other likely choices: (substitute form 1: '␚', substitute form 2: '␦').
  #define byte_dump_character_incomplete  "�"
  #define byte_dump_character_unused      "�"

  #define byte_dump_short_binary      "b"
  #define byte_dump_short_decimal     "d"
  #define byte_dump_short_duodecimal  "D"
  #define byte_dump_short_hexidecimal "x"
  #define byte_dump_short_octal       "o"
  #define byte_dump_short_unicode     "U"

  #define byte_dump_short_first       "f"
  #define byte_dump_short_last        "l"
  #define byte_dump_short_text        "t"
  #define byte_dump_short_width       "w"
  #define byte_dump_short_placeholder "p"

  #define byte_dump_long_binary      "binary"
  #define byte_dump_long_decimal     "decimal"
  #define byte_dump_long_duodecimal  "duodecimal"
  #define byte_dump_long_hexidecimal "hexidecimal"
  #define byte_dump_long_octal       "octal"
  #define byte_dump_long_unicode     "unicode"

  #define byte_dump_long_first "first" // first offset byte size.
  #define byte_dump_long_last  "last"  // last offset byte size.
  #define byte_dump_long_width "width" // number of characters to display per row.

  #define byte_dump_long_text        "text"        // display text
  #define byte_dump_long_placeholder "placeholder" // display (colored) placeholders to signify codes that are UTF-8 fragments.

  #define byte_dump_long_normal  "normal"  // use normal presentation, displaying UTF-8 sequence codes for ASCII special codes.
  #define byte_dump_long_simple  "simple"  // use simple presentation, displaying spaces for ASCII special codes instead of UTF-8 sequence codes.
  #define byte_dump_long_classic "classic" // use classic presentation, displaying periods for ASCII special codes instead of UTF-8 sequence codes.

  enum {
    byte_dump_parameter_help,
    byte_dump_parameter_light,
    byte_dump_parameter_dark,
    byte_dump_parameter_no_color,
    byte_dump_parameter_verbosity_quiet,
    byte_dump_parameter_verbosity_normal,
    byte_dump_parameter_verbosity_verbose,
    byte_dump_parameter_verbosity_debug,
    byte_dump_parameter_version,

    byte_dump_parameter_binary,
    byte_dump_parameter_decimal,
    byte_dump_parameter_duodecimal,
    byte_dump_parameter_hexidecimal,
    byte_dump_parameter_octal,
    byte_dump_parameter_unicode,

    byte_dump_parameter_first,
    byte_dump_parameter_last,
    byte_dump_parameter_width,

    byte_dump_parameter_text,
    byte_dump_parameter_placeholder,

    byte_dump_parameter_normal,
    byte_dump_parameter_simple,
    byte_dump_parameter_classic,
  };

  #define byte_dump_console_parameter_t_initialize \
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
      f_console_parameter_t_initialize(byte_dump_short_binary, byte_dump_long_binary, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(byte_dump_short_decimal, byte_dump_long_decimal, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(byte_dump_short_duodecimal, byte_dump_long_duodecimal, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(byte_dump_short_hexidecimal, byte_dump_long_hexidecimal, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(byte_dump_short_octal, byte_dump_long_octal, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(byte_dump_short_unicode, byte_dump_long_unicode, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(byte_dump_short_first, byte_dump_long_first, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(byte_dump_short_last, byte_dump_long_last, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(byte_dump_short_width, byte_dump_long_width, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(byte_dump_short_text, byte_dump_long_text, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(byte_dump_short_placeholder, byte_dump_long_placeholder, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(0, byte_dump_long_normal, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(0, byte_dump_long_simple, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(0, byte_dump_long_classic, 0, 0, f_console_type_normal), \
    }

  #define byte_dump_total_parameters 23
#endif // _di_byte_dump_defines_

#ifndef _di_byte_dump_main_t_
  typedef struct {
    f_console_parameter_t parameters[byte_dump_total_parameters];

    f_array_lengths_t remaining;
    bool process_pipe;

    fl_print_t output;
    fl_print_t error;
    fl_print_t warning;

    uint64_t first;
    uint64_t last;
    uint8_t width;
    uint8_t mode;
    uint8_t presentation;

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
      0, \
      0, \
      8, \
      byte_dump_mode_hexidecimal, \
      byte_dump_presentation_normal, \
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
 * @param arguments
 *   The parameters passed to the process.
 * @param main
 *   The main data.
 *
 * @return
 *   F_none on success.
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see byte_dump_main_delete()
 */
#ifndef _di_byte_dump_main_
  extern f_status_t byte_dump_main(const f_console_arguments_t arguments, byte_dump_main_t *main);
#endif // _di_byte_dump_main_

/**
 * Deallocate main.
 *
 * Be sure to call this after executing byte_dump_main().
 *
 * @param main
 *   The main data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see byte_dump_main()
 */
#ifndef _di_byte_dump_main_delete_
  extern f_status_t byte_dump_main_delete(byte_dump_main_t *main);
#endif // _di_byte_dump_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _byte_dump_h
