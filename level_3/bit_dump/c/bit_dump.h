/**
 * FLL - Level 3
 *
 * Project: Bit Dump
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
#ifndef _bit_dump_h

// libc includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// fll-0 includes
#include <level_0/console.h>
#include <level_0/conversion.h>
#include <level_0/pipe.h>
#include <level_0/print.h>
#include <level_0/status.h>
#include <level_0/string.h>
#include <level_0/type.h>
#include <level_0/utf.h>

// fll-1 includes
#include <level_1/color.h>
#include <level_1/console.h>
#include <level_1/string.h>
#include <level_1/utf.h>

// fll-2 includes
#include <level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_bit_dump_version_
  #define bit_dump_major_version "0"
  #define bit_dump_minor_version "5"
  #define bit_dump_micro_version "0"
  #define bit_dump_version bit_dump_major_version "." bit_dump_minor_version "." bit_dump_micro_version
#endif // _di_bit_dump_version_

#ifndef _di_bit_dump_name_
  #define bit_dump_name      "bit_dump"
  #define bit_dump_name_long "Bit Dump"
#endif // _di_bit_dump_name_

#ifndef _di_bit_dump_default_allocation_step_
  // provide a UTF-8 friendly allocation step.
  #define bit_dump_default_allocation_step 4
#endif // _di_bit_dump_default_allocation_step_

#ifndef _di_bit_dump_defines_
  enum {
    bit_dump_mode_hexidecimal,
    bit_dump_mode_octal,
    bit_dump_mode_binary,
    bit_dump_mode_digit,
  };

  #define bit_dump_sequence_acknowledge               "␆"
  #define bit_dump_sequence_backspace                 "␈"
  #define bit_dump_sequence_bell                      "␇"
  #define bit_dump_sequence_cancel                    "␘"
  #define bit_dump_sequence_carriage_return           "␍"
  #define bit_dump_sequence_data_link_escape          "␐"
  #define bit_dump_sequence_delete                    "␡"
  #define bit_dump_sequence_device_control_1          "␑"
  #define bit_dump_sequence_device_control_2          "␒"
  #define bit_dump_sequence_device_control_3          "␓"
  #define bit_dump_sequence_device_control_4          "␔"
  #define bit_dump_sequence_end_of_enquiry            "␅"
  #define bit_dump_sequence_end_of_medium             "␙"
  #define bit_dump_sequence_end_of_text               "␃"
  #define bit_dump_sequence_end_of_transmission       "␄"
  #define bit_dump_sequence_end_of_transmission_block "␗"
  #define bit_dump_sequence_escape                    "␛"
  #define bit_dump_sequence_file_separator            "␜"
  #define bit_dump_sequence_form_feed                 "␌"
  #define bit_dump_sequence_group_separator           "␝"
  #define bit_dump_sequence_line_feed                 "␊"
  #define bit_dump_sequence_negative_acknowledge      "␕"
  #define bit_dump_sequence_new_line                  "␤"
  #define bit_dump_sequence_null                      "␀"
  #define bit_dump_sequence_record_separator          "␞"
  #define bit_dump_sequence_shift_in                  "␏"
  #define bit_dump_sequence_shift_out                 "␎"
  #define bit_dump_sequence_space                     "␠"
  #define bit_dump_sequence_start_of_header           "␁"
  #define bit_dump_sequence_start_of_text             "␂"
  #define bit_dump_sequence_substitute                "␚"
  #define bit_dump_sequence_synchronous_idle          "␖"
  #define bit_dump_sequence_tab                       "␉"
  #define bit_dump_sequence_tab_vertical              "␋"
  #define bit_dump_sequence_unit_separator            "␟"
  #define bit_dump_sequence_utf_bom                   "␂"

  #define bit_dump_character_wall        "|"
  #define bit_dump_character_placeholder "␣" // other likely choices: (substitute form 1: '␚', substitute form 2: '␦').
  #define bit_dump_character_incomplete  "�"
  #define bit_dump_character_unused      "�"

  #define bit_dump_short_binary      "b"
  #define bit_dump_short_hex         "x"
  #define bit_dump_short_octal       "o"

  #define bit_dump_short_first       "f"
  #define bit_dump_short_last        "l"
  #define bit_dump_short_text        "t"
  #define bit_dump_short_width       "w"
  #define bit_dump_short_placeholder "p"

  #define bit_dump_long_binary       "binary"
  #define bit_dump_long_hex          "hex"
  #define bit_dump_long_octal        "octal"

  #define bit_dump_long_first        "first"       // first offset byte size.
  #define bit_dump_long_last         "last"        // last offset byte size.
  #define bit_dump_long_width        "width"       // number of characters to display per row.

  #define bit_dump_long_text         "text"        // display text
  #define bit_dump_long_placeholder  "placeholder" // display (colored) placeholders to signify codes that are UTF-8 fragments.

  enum {
    bit_dump_parameter_help,
    bit_dump_parameter_light,
    bit_dump_parameter_dark,
    bit_dump_parameter_no_color,
    bit_dump_parameter_version,

    bit_dump_parameter_binary,
    bit_dump_parameter_hexidecimal,
    bit_dump_parameter_octal,
    // @todo: add digit print support bit_dump_parameter_digit,

    bit_dump_parameter_first,
    bit_dump_parameter_last,
    bit_dump_parameter_width,

    bit_dump_parameter_text,
    bit_dump_parameter_placeholder,
  };

  #define bit_dump_console_parameter_initialize \
    { \
      f_console_parameter_initialize(f_console_standard_short_help, f_console_standard_long_help, 0, 0, f_console_type_normal), \
      f_console_parameter_initialize(f_console_standard_short_light, f_console_standard_long_light, 0, 0, f_console_type_inverse), \
      f_console_parameter_initialize(f_console_standard_short_dark, f_console_standard_long_dark, 0, 0, f_console_type_inverse), \
      f_console_parameter_initialize(f_console_standard_short_no_color, f_console_standard_long_no_color, 0, 0, f_console_type_inverse), \
      f_console_parameter_initialize(f_console_standard_short_version, f_console_standard_long_version, 0, 0, f_console_type_inverse), \
      f_console_parameter_initialize(bit_dump_short_binary, bit_dump_long_binary, 0, 0, f_console_type_normal), \
      f_console_parameter_initialize(bit_dump_short_hex, bit_dump_long_hex, 0, 0, f_console_type_normal), \
      f_console_parameter_initialize(bit_dump_short_octal, bit_dump_long_octal, 0, 0, f_console_type_normal), \
      f_console_parameter_initialize(bit_dump_short_first, bit_dump_long_first, 0, 1, f_console_type_normal), \
      f_console_parameter_initialize(bit_dump_short_last, bit_dump_long_last, 0, 1, f_console_type_normal), \
      f_console_parameter_initialize(bit_dump_short_width, bit_dump_long_width, 0, 1, f_console_type_normal), \
      f_console_parameter_initialize(bit_dump_short_text, bit_dump_long_text, 0, 0, f_console_type_normal), \
      f_console_parameter_initialize(bit_dump_short_placeholder, bit_dump_long_placeholder, 0, 0, f_console_type_normal), \
    }

  #define bit_dump_total_parameters 13
#endif // _di_bit_dump_defines_

#ifndef _di_bit_dump_data_
  typedef struct {
    f_console_parameter parameters[bit_dump_total_parameters];

    f_string_lengths remaining;
    f_bool process_pipe;

    uint64_t first;
    uint64_t last;
    uint8_t  width;
    uint8_t  mode;

    fl_color_context context;
  } bit_dump_data;

  #define bit_dump_data_initialize \
    { \
      bit_dump_console_parameter_initialize, \
      f_string_lengths_initialize, \
      f_false, \
      0, \
      0, \
      8, \
      bit_dump_mode_hexidecimal, \
      fl_color_context_initialize, \
    }
#endif // _di_bit_dump_data_

/**
 * Print help to standard output.
 *
 * @param data
 *   The program data.
 *
 * @return
 *   f_none on success.
 */
#ifndef _di_bit_dump_print_help_
  extern f_return_status bit_dump_print_help(const bit_dump_data data);
#endif // _di_bit_dump_print_help_

/**
 * Execute main program.
 *
 * Be sure to call bit_dump_delete_data() after executing this.
 *
 * @param arguments
 *   The parameters passed to the process.
 * @param data
 *   The program data.
 *
 * @return
 *   f_none on success.
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see bit_dump_delete_data()
 */
#ifndef _di_bit_dump_main_
  extern f_return_status bit_dump_main(const f_console_arguments arguments, bit_dump_data *data);
#endif // _di_bit_dump_main_

/**
 * Deallocate data.
 *
 * Be sure to call this after executing bit_dump_main().
 *
 * @param data
 *   The program data.
 *
 * @return
 *   f_none on success.
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see bit_dump_main()
 */
#ifndef _di_bit_dump_delete_data_
  extern f_return_status bit_dump_delete_data(bit_dump_data *data);
#endif // _di_bit_dump_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _bit_dump_h
