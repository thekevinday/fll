/**
 * FLL - Level 0
 *
 * Project: Print
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines common data to be used for/by project print.
 *
 * This is auto-included by print.h and should not need to be explicitly included.
 */
#ifndef _F_print_common_h
#define _F_print_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Defines the maximum length supported by write() for use in printing.
 *
 * This is documented in the man write(2) pages under Linux to being 0x7ffff000 regardless of 32-bit or 64-bit.
 */
#ifndef _di_f_print_write_max_
 #define f_print_write_max 0x7ffff000
#endif // _di_f_print_write_max_

/**
 * Common print sequences.
 *
 * These are sequences only used by the print function and do not represent all possible sequences.
 *
 * All characters here are longer than 1-byte.
 * The ones used here are 3-bytes wide.
 *
 * The code currently expects these to be 3-bytes wide so changing this to any other width will require changing code that utilizes these.
 */
#ifndef _di_f_print_sequences_
  #define f_print_sequence_acknowledge               "␆"
  #define f_print_sequence_acknowledge_negative      "␕"
  #define f_print_sequence_backspace                 "␈"
  #define f_print_sequence_bell                      "␇"
  #define f_print_sequence_cancel                    "␘"
  #define f_print_sequence_carriage_return           "␍"
  #define f_print_sequence_data_link_escape          "␐"
  #define f_print_sequence_delete                    "␡"
  #define f_print_sequence_device_control_1          "␑"
  #define f_print_sequence_device_control_2          "␒"
  #define f_print_sequence_device_control_3          "␓"
  #define f_print_sequence_device_control_4          "␔"
  #define f_print_sequence_end_of_medium             "␙"
  #define f_print_sequence_end_of_text               "␃"
  #define f_print_sequence_end_of_transmission       "␄"
  #define f_print_sequence_end_of_transmission_block "␗"
  #define f_print_sequence_enquiry                   "␅"
  #define f_print_sequence_escape                    "␛"
  #define f_print_sequence_form_feed                 "␌"
  #define f_print_sequence_line_feed                 "␊"
  #define f_print_sequence_null                      "␀"
  #define f_print_sequence_separator_file            "␜"
  #define f_print_sequence_separator_group           "␝"
  #define f_print_sequence_separator_record          "␞"
  #define f_print_sequence_separator_unit            "␟"
  #define f_print_sequence_shift_in                  "␏"
  #define f_print_sequence_shift_out                 "␎"
  #define f_print_sequence_start_of_header           "␁"
  #define f_print_sequence_start_of_text             "␂"
  #define f_print_sequence_substitute                "␚"
  #define f_print_sequence_synchronous_idle          "␖"
  #define f_print_sequence_tab                       "␉"
  #define f_print_sequence_tab_vertical              "␋"
  #define f_print_sequence_unknown                   "�"

  extern const f_string_t f_print_sequence_acknowledge_s;
  extern const f_string_t f_print_sequence_acknowledge_negative_s;
  extern const f_string_t f_print_sequence_backspace_s;
  extern const f_string_t f_print_sequence_bell_s;
  extern const f_string_t f_print_sequence_cancel_s;
  extern const f_string_t f_print_sequence_carriage_return_s;
  extern const f_string_t f_print_sequence_data_link_escape_s;
  extern const f_string_t f_print_sequence_delete_s;
  extern const f_string_t f_print_sequence_device_control_1_s;
  extern const f_string_t f_print_sequence_device_control_2_s;
  extern const f_string_t f_print_sequence_device_control_3_s;
  extern const f_string_t f_print_sequence_device_control_4_s;
  extern const f_string_t f_print_sequence_end_of_medium_s;
  extern const f_string_t f_print_sequence_end_of_text_s;
  extern const f_string_t f_print_sequence_end_of_transmission_s;
  extern const f_string_t f_print_sequence_end_of_transmission_block_s;
  extern const f_string_t f_print_sequence_escape_s;
  extern const f_string_t f_print_sequence_equiry_s;
  extern const f_string_t f_print_sequence_form_feed_s;
  extern const f_string_t f_print_sequence_line_feed_s;
  extern const f_string_t f_print_sequence_null_s;
  extern const f_string_t f_print_sequence_separator_file_s;
  extern const f_string_t f_print_sequence_separator_group_s;
  extern const f_string_t f_print_sequence_separator_record_s;
  extern const f_string_t f_print_sequence_separator_unit_s;
  extern const f_string_t f_print_sequence_shift_in_s;
  extern const f_string_t f_print_sequence_shift_out_s;
  extern const f_string_t f_print_sequence_start_of_header_s;
  extern const f_string_t f_print_sequence_start_of_text_s;
  extern const f_string_t f_print_sequence_substitute_s;
  extern const f_string_t f_print_sequence_synchronous_idle_s;
  extern const f_string_t f_print_sequence_tab_s;
  extern const f_string_t f_print_sequence_tab_vertical_s;
  extern const f_string_t f_print_sequence_unknown_s;
#endif // _di_f_print_sequences_

/**
 * A map for converting control ASCII codes into the representation sequences.
 *
 * The key should represents the ASCII code.
 * With the exception being ASCII code 127, which is not present in this map.
 */
#ifndef _di_f_print_sequences_set_control_
  extern const char f_print_sequence_set_control_s[32][3];
#endif // _di_f_print_sequences_set_control_

/**
 * Provide basic format flags.
 *
 * f_print_format_flag_*:
 * - align_left:     "-", Use left-justification.
 * - convert:        "#", Use alternate form conversion (prefixing 0b/0B, 0o/0O, 0t/0T, 0d/0D, 0x/0X).
 * - ignore_index:   ";", Ignore characters in the given positions from a f_array_length_t (only applies to static/dynamic string arguments but not character arguments).
 * - ignore_range:   ":", Ignore characters in the given ranges from a f_string_range_t (only applies to static/dynamic string arguments but not character arguments).
 * - precision:           Designates that a precision is in use.
 * - sign_always:    "+", Always show the signs (+ or -).
 * - sign_pad:       " ", Add a space where a sign would be if the sign is not displayed.
 * - trim:           "=", Trim leading and trailing whitespaces (only applies to static/dynamic string arguments but not character arguments).
 * - uppercase:           Display any base units as uppercase.
 * - width:               Designates that a width is in use.
 * - zeros_leading:  "0", Use leading zeros.
 *
 * @see fprintf()
 */
#ifndef _di_f_print_format_flag_
  #define f_print_format_flag_align_left     0x1
  #define f_print_format_flag_convert        0x2
  #define f_print_format_flag_ignore_index   0x4
  #define f_print_format_flag_ignore_range   0x8
  #define f_print_format_flag_precision      0x10
  #define f_print_format_flag_sign_always    0x20
  #define f_print_format_flag_sign_pad       0x40
  #define f_print_format_flag_trim           0x80
  #define f_print_format_flag_uppercase      0x100
  #define f_print_format_flag_width          0x200
  #define f_print_format_flag_zeros_leading  0x400
#endif // _di_f_print_format_flags_

/**
 * Provide base format flags.
 *
 * f_print_format_base_*:
 * - binary:      "!", Display number in Binary notation.
 * - octal:       "@", Display number in Octal notation.
 * - decimal:     "^", Display number in Octal notation.
 * - duodecimal:  "&", Display number in Duodecimal notation.
 * - hexidecimal: "_", Display number in Hexidecimal notation.
 *
 * @see fprintf()
 */

/**
 * Provide type format flags.
 *
 * The uppercase "I", "L", "LL", "UL", "ULL" designates setting the uppercase flag.
 *
 * f_print_format_type_*:
 * - character:          "c", type is a 1-byte unsigned character.
 * - character_safe:     "C", type is a 1-byte unsigned character, where control characters and other problems are handled.
 * - color_after:        "]", type is f_color_set_t such that the f_color_set_t.after is used.
 * - color_before:       "[", type is f_color_set_t such that the f_color_set_t.begin is used.
 * - number:             "n", "N", type is an f_number_signed_t.
 * - signed_8:           "iii", "III", type is a int8_t.
 * - signed_16:          "ii", "II", type is a int16_t.
 * - signed_32:          "i", "I", type is a int32_t.
 * - signed_64:          "il", "IL", type is a signed int64_t.
 * - signed_128:         "ill", "ILL", type is a f_int_128_t.
 * - size:               "z", "Z", type is a size_t.
 * - string_safe:        "S", type is a NULL terminated string, where control characters and other problems are handled.
 * - string_static:      "q", type is an f_string_static_t or f_string_dynamic_t and NULLs are ignored (not printed).
 * - string_static_raw:  "r", type is an f_string_static_t or f_string_dynamic_t and NULLs (and all other control characters) are printed.
 * - string_static_safe: "Q", type is an f_string_static_t or f_string_dynamic_t and NULLs are printed, where control characters and other problems are handled.
 * - unsigned_8:         "uii", "UII", type is an uint8_t.
 * - unsigned_16:        "ui", "UI", type is an uint16_t.
 * - unsigned_32:        "u", "U", type is an uint32_t.
 * - unsigned_64:        "ul", "UL", type is an uint64_t.
 * - unsigned_128:       "ull", "ULL", type is an f_uint_128_t.
 * - unsigned_number:    "un", "UN", type is an f_number_unsigned_t (which by default is what f_array_length_t is a type of).
 *
 * @see fprintf()
 */
#ifndef _di_f_print_format_type_
  enum {
    f_print_format_type_character = 1,
    f_print_format_type_character_safe,
    f_print_format_type_color_after,
    f_print_format_type_color_before,
    f_print_format_type_number,
    f_print_format_type_signed_8,
    f_print_format_type_signed_16,
    f_print_format_type_signed_32,
    f_print_format_type_signed_64,
    f_print_format_type_signed_128,
    f_print_format_type_size,
    f_print_format_type_string,
    f_print_format_type_string_safe,
    f_print_format_type_string_static,
    f_print_format_type_string_static_raw,
    f_print_format_type_string_static_safe,
    f_print_format_type_unsigned_8,
    f_print_format_type_unsigned_16,
    f_print_format_type_unsigned_32,
    f_print_format_type_unsigned_64,
    f_print_format_type_unsigned_128,
    f_print_format_type_unsigned_number,
  };
#endif // _di_f_print_format_type_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_print_common_h
