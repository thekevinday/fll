/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines common string data.
 *
 * This is auto-included by string.h and should not need to be explicitly included.
 */
#ifndef _F_string_common_h
#define _F_string_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * BUG: for whatever reason strnlen is considered not included with -Wall, even with __USE_GNU defined.
 *      therefore this gets defined here.
 */
#ifdef _en_BUG_strnlen_
  extern size_t strnlen (const char *string, size_t max_length);
#endif // _en_BUG_strnlen_

/**
 * Define the basic string type.
 *
 * Dynamic allocation macros are provided, but it is recommended to utilize the f_string_dynamic_t for dynamic allocation.
 *
 *  is provided as a way t have a string max for systems that do not support max string length in 64-bits (when f_array_length_t is set to uint64_t).
 *
 * The ideal length for a string is f_array_length_t_size, which generally defaults to 2^64 (unsigned).
 * However, the libc/POSIX appears to limit this to 2^63 (signed).
 * f_string_t_size is provided to help safely navigate this.
 */
#ifndef _di_f_string_t_
  typedef char *f_string_t;

  #define f_string_t_initialize 0

  #define macro_f_string_t_clear(string) string = 0;

  #define macro_f_string_t_resize(status, string, length_old, length_new) status = f_memory_resize(length_old, length_new, sizeof(f_string_t), (void **) & string);
  #define macro_f_string_t_adjust(status, string, length_old, length_new) status = f_memory_adjust(length_old, length_new, sizeof(f_string_t), (void **) & string);

  #define macro_f_string_t_delete_simple(string, length)  f_memory_resize(length, 0, sizeof(f_string_t), (void **) & string);
  #define macro_f_string_t_destroy_simple(string, length) f_memory_adjust(length, 0, sizeof(f_string_t), (void **) & string);

  // @fixme update all code utilizing f_array_length_t on a string, such as strnlen().
  #define f_string_t_size f_type_size_64_positive
#endif // _di_f_string_t_

/**
 * Define the constant string type.
 *
 * This is needed when passing a constant string as a function argument.
 * This cannot be allocated or deallocated.
 * This is provided for compatibility with some projects that return "const char *".
 *
 * GCC errors such as: "warning: assignment discards ‘const’ qualifier from pointer target type [-Wdiscarded-qualifiers]" can be avoided using this.
 *
 * Do not confuse this with "const f_string_t".
 * When "const f_string_t * xxx" is passed to a function, then "xxx" cannot be changed.
 * When "f_string_constant_t * xxx" is passed to a function, then "xxx" can be changed.
 */
#ifndef _di_f_string_constant_t_
  typedef const char *f_string_constant_t;

  #define f_string_constant_t_initialize 0

  #define macro_f_string_constant_t_clear(string) string = 0;
#endif // _di_f_string_t_

/**
 * Define the end of line character.
 * FLL forbids '\r' and '\r\n' as end of line characters, \r will be silently ignored.
 */
#ifndef _di_f_string_eol_s_
  #define f_string_eol_s f_string_ascii_feed_line_s
  #define f_string_eol_s_length 1
#endif // _di_f_string_eol_s_

#ifndef _di_f_string_empty_s_
  const extern f_string_t f_string_empty_s;
#endif // _di_f_string_empty_s_

#ifndef _di_f_string_placeholder_s_
  #define f_string_placeholder_s f_string_empty_s
  #define f_string_placeholder_s_length 1
#endif // _di_f_string_placeholder_s_

#ifndef _di_f_string_space_s_
  #define f_string_space_s f_string_ascii_space_s
  #define f_string_space_s_length 1
#endif // _di_f_string_space_s_

#ifndef _di_string_format_s_
  #define f_string_format_string             "%s"
  #define f_string_format_character          "%c"
  #define f_string_format_wide_string        "%ls"
  #define f_string_format_wide_character     "%lc"
  #define f_string_format_integer            "%i"
  #define f_string_format_unsigned           "%u"
  #define f_string_format_digit              "%d"
  #define f_string_format_float              "%f"
  #define f_string_format_short_integer      "%hi"
  #define f_string_format_short_unsigned     "%hu"
  #define f_string_format_long_integer       "%li"
  #define f_string_format_long_unsigned      "%lu"
  #define f_string_format_long_double        "%ld"
  #define f_string_format_long_long_integer  "%lli"
  #define f_string_format_long_long_unsigned "%llu"

  extern const f_string_t f_string_format_string_s;
  extern const f_string_t f_string_format_character_s;
  extern const f_string_t f_string_format_wide_string_s;
  extern const f_string_t f_string_format_wide_character_s;
  extern const f_string_t f_string_format_integer_s;
  extern const f_string_t f_string_format_unsigned_s;
  extern const f_string_t f_string_format_digit_s;
  extern const f_string_t f_string_format_float_s;
  extern const f_string_t f_string_format_short_integer_s;
  extern const f_string_t f_string_format_short_unsigned_s;
  extern const f_string_t f_string_format_long_integer_s;
  extern const f_string_t f_string_format_long_unsigned_s;
  extern const f_string_t f_string_format_long_double_s;
  extern const f_string_t f_string_format_long_long_integer_s;
  extern const f_string_t f_string_format_long_long_unsigned_s;
#endif // _di_string_format_s_

#ifndef _di_f_array_length_printf_
  #define f_array_length_printf       string_format_integer
  #define f_array_length_short_printf string_format_short_integer
  #define f_array_length_long_printf  string_format_long_integer
#endif // _di_f_array_length_printf_

/**
 * Provide a set of ASCII strings.
 *
 * This is not intended to be exhaustive or language-specific.
 * Instead, this is for very common uses such as converting a hex-digit string into a number.
 * These are standardized not be the language, per-say, but instead by the specific standard (such as hexidecimal).
 *
 * The NULL ASCII string can be represented by the integer 0; however, given that these are all NULL-terminated strings the NULL character is represented with a NULL termination as well.
 * The NULL ASCII string therefore has two NULLs, first the NULL represents the NULL and the second represents the NULL termination.
 *
 * @todo provide extended ASCII-characters.
 */
#ifndef _di_string_ascii_s_
  #define f_string_ascii_0 "0"
  #define f_string_ascii_1 "1"
  #define f_string_ascii_2 "2"
  #define f_string_ascii_3 "3"
  #define f_string_ascii_4 "4"
  #define f_string_ascii_5 "5"
  #define f_string_ascii_6 "6"
  #define f_string_ascii_7 "7"
  #define f_string_ascii_8 "8"
  #define f_string_ascii_9 "9"

  #define f_string_ascii_a "a"
  #define f_string_ascii_b "b"
  #define f_string_ascii_c "c"
  #define f_string_ascii_d "d"
  #define f_string_ascii_e "e"
  #define f_string_ascii_f "f"
  #define f_string_ascii_g "g"
  #define f_string_ascii_h "h"
  #define f_string_ascii_i "i"
  #define f_string_ascii_j "j"
  #define f_string_ascii_k "k"
  #define f_string_ascii_l "l"
  #define f_string_ascii_m "m"
  #define f_string_ascii_n "n"
  #define f_string_ascii_o "o"
  #define f_string_ascii_p "p"
  #define f_string_ascii_q "q"
  #define f_string_ascii_r "r"
  #define f_string_ascii_s "s"
  #define f_string_ascii_t "t"
  #define f_string_ascii_u "u"
  #define f_string_ascii_v "v"
  #define f_string_ascii_w "w"
  #define f_string_ascii_x "x"
  #define f_string_ascii_y "y"
  #define f_string_ascii_z "z"

  #define f_string_ascii_A "A"
  #define f_string_ascii_B "B"
  #define f_string_ascii_C "C"
  #define f_string_ascii_D "D"
  #define f_string_ascii_E "E"
  #define f_string_ascii_F "F"
  #define f_string_ascii_G "G"
  #define f_string_ascii_H "H"
  #define f_string_ascii_I "I"
  #define f_string_ascii_J "J"
  #define f_string_ascii_K "K"
  #define f_string_ascii_L "L"
  #define f_string_ascii_M "M"
  #define f_string_ascii_N "N"
  #define f_string_ascii_O "O"
  #define f_string_ascii_P "P"
  #define f_string_ascii_Q "Q"
  #define f_string_ascii_R "R"
  #define f_string_ascii_S "S"
  #define f_string_ascii_T "T"
  #define f_string_ascii_U "U"
  #define f_string_ascii_V "V"
  #define f_string_ascii_W "W"
  #define f_string_ascii_X "X"
  #define f_string_ascii_Y "Y"
  #define f_string_ascii_Z "Z"

  #define f_string_ascii_ampersand         "&"
  #define f_string_ascii_asterisk          "*"
  #define f_string_ascii_brace_close       "}"
  #define f_string_ascii_brace_open        "{"
  #define f_string_ascii_bracket_close     "]"
  #define f_string_ascii_bracket_open      "["
  #define f_string_ascii_caret             "^"
  #define f_string_ascii_comma             ","
  #define f_string_ascii_colon             ":"
  #define f_string_ascii_colon_semi        ";"
  #define f_string_ascii_dollar            "$"
  #define f_string_ascii_equal             "="
  #define f_string_ascii_exclamation       "!"
  #define f_string_ascii_grave             "`"
  #define f_string_ascii_mark_question     "?"
  #define f_string_ascii_minus             "-"
  #define f_string_ascii_parenthesis_open  "("
  #define f_string_ascii_parenthesis_close ")"
  #define f_string_ascii_percent           "%"
  #define f_string_ascii_period            "."
  #define f_string_ascii_pipe              "|"
  #define f_string_ascii_plus              "+"
  #define f_string_ascii_pound             "#"
  #define f_string_ascii_quote_double      "\""
  #define f_string_ascii_quote_single      "'"
  #define f_string_ascii_sign_at           "@"
  #define f_string_ascii_sign_greater_than ">"
  #define f_string_ascii_sign_less_than    "<"
  #define f_string_ascii_slash_forward     "/"
  #define f_string_ascii_slash_backward    "\\"
  #define f_string_ascii_tilde             "~"
  #define f_string_ascii_underscore        "_"

  #define f_string_ascii_acknowledge            ""
  #define f_string_ascii_acknowledge_negative   ""
  #define f_string_ascii_bell                   ""
  #define f_string_ascii_cancel                 ""
  #define f_string_ascii_data_link_escape       ""
  #define f_string_ascii_device_control_one     ""
  #define f_string_ascii_device_control_two     ""
  #define f_string_ascii_device_control_three   ""
  #define f_string_ascii_device_control_four    ""
  #define f_string_ascii_enquiry                ""
  #define f_string_ascii_escape                 ""
  #define f_string_ascii_feed_form              "\f"
  #define f_string_ascii_feed_line              "\n"
  #define f_string_ascii_header_start           ""
  #define f_string_ascii_medium_stop            ""
  #define f_string_ascii_null                   "\0"
  #define f_string_ascii_return_carriage        "\r"
  #define f_string_ascii_separator_file         ""
  #define f_string_ascii_separator_group        ""
  #define f_string_ascii_separator_record       ""
  #define f_string_ascii_separator_unit         ""
  #define f_string_ascii_shift_in               ""
  #define f_string_ascii_shift_out              ""
  #define f_string_ascii_space                  " "
  #define f_string_ascii_space_back             ""
  #define f_string_ascii_substitute             ""
  #define f_string_ascii_synchronous_idle       ""
  #define f_string_ascii_tab_horizontal         "\t"
  #define f_string_ascii_tab_vertical           "\v"
  #define f_string_ascii_text_start             ""
  #define f_string_ascii_text_stop              ""
  #define f_string_ascii_transmission_stop      ""
  #define f_string_ascii_transmission_block_end ""

  extern const f_string_t f_string_ascii_0_s;
  extern const f_string_t f_string_ascii_1_s;
  extern const f_string_t f_string_ascii_2_s;
  extern const f_string_t f_string_ascii_3_s;
  extern const f_string_t f_string_ascii_4_s;
  extern const f_string_t f_string_ascii_5_s;
  extern const f_string_t f_string_ascii_6_s;
  extern const f_string_t f_string_ascii_7_s;
  extern const f_string_t f_string_ascii_8_s;
  extern const f_string_t f_string_ascii_9_s;

  extern const f_string_t f_string_ascii_a_s;
  extern const f_string_t f_string_ascii_b_s;
  extern const f_string_t f_string_ascii_c_s;
  extern const f_string_t f_string_ascii_d_s;
  extern const f_string_t f_string_ascii_e_s;
  extern const f_string_t f_string_ascii_f_s;
  extern const f_string_t f_string_ascii_g_s;
  extern const f_string_t f_string_ascii_h_s;
  extern const f_string_t f_string_ascii_i_s;
  extern const f_string_t f_string_ascii_j_s;
  extern const f_string_t f_string_ascii_k_s;
  extern const f_string_t f_string_ascii_l_s;
  extern const f_string_t f_string_ascii_m_s;
  extern const f_string_t f_string_ascii_n_s;
  extern const f_string_t f_string_ascii_o_s;
  extern const f_string_t f_string_ascii_p_s;
  extern const f_string_t f_string_ascii_q_s;
  extern const f_string_t f_string_ascii_r_s;
  extern const f_string_t f_string_ascii_s_s;
  extern const f_string_t f_string_ascii_t_s;
  extern const f_string_t f_string_ascii_u_s;
  extern const f_string_t f_string_ascii_v_s;
  extern const f_string_t f_string_ascii_w_s;
  extern const f_string_t f_string_ascii_x_s;
  extern const f_string_t f_string_ascii_y_s;
  extern const f_string_t f_string_ascii_z_s;

  extern const f_string_t f_string_ascii_A_s;
  extern const f_string_t f_string_ascii_B_s;
  extern const f_string_t f_string_ascii_C_s;
  extern const f_string_t f_string_ascii_D_s;
  extern const f_string_t f_string_ascii_E_s;
  extern const f_string_t f_string_ascii_F_s;
  extern const f_string_t f_string_ascii_G_s;
  extern const f_string_t f_string_ascii_H_s;
  extern const f_string_t f_string_ascii_I_s;
  extern const f_string_t f_string_ascii_J_s;
  extern const f_string_t f_string_ascii_K_s;
  extern const f_string_t f_string_ascii_L_s;
  extern const f_string_t f_string_ascii_M_s;
  extern const f_string_t f_string_ascii_N_s;
  extern const f_string_t f_string_ascii_O_s;
  extern const f_string_t f_string_ascii_P_s;
  extern const f_string_t f_string_ascii_Q_s;
  extern const f_string_t f_string_ascii_R_s;
  extern const f_string_t f_string_ascii_S_s;
  extern const f_string_t f_string_ascii_T_s;
  extern const f_string_t f_string_ascii_U_s;
  extern const f_string_t f_string_ascii_V_s;
  extern const f_string_t f_string_ascii_W_s;
  extern const f_string_t f_string_ascii_X_s;
  extern const f_string_t f_string_ascii_Y_s;
  extern const f_string_t f_string_ascii_Z_s;

  extern const f_string_t f_string_ascii_ampersand_s;
  extern const f_string_t f_string_ascii_asterisk_s;
  extern const f_string_t f_string_ascii_brace_close_s;
  extern const f_string_t f_string_ascii_brace_open_s;
  extern const f_string_t f_string_ascii_bracket_close_s;
  extern const f_string_t f_string_ascii_bracket_open_s;
  extern const f_string_t f_string_ascii_caret_s;
  extern const f_string_t f_string_ascii_comma_s;
  extern const f_string_t f_string_ascii_colon_s;
  extern const f_string_t f_string_ascii_colon_semi_s;
  extern const f_string_t f_string_ascii_dollar_s;
  extern const f_string_t f_string_ascii_equal_s;
  extern const f_string_t f_string_ascii_exclamation_s;
  extern const f_string_t f_string_ascii_grave_s;
  extern const f_string_t f_string_ascii_mark_question_s;
  extern const f_string_t f_string_ascii_minus_s;
  extern const f_string_t f_string_ascii_parenthesis_open_s;
  extern const f_string_t f_string_ascii_parenthesis_close_s;
  extern const f_string_t f_string_ascii_percent_s;
  extern const f_string_t f_string_ascii_period_s;
  extern const f_string_t f_string_ascii_pipe_s;
  extern const f_string_t f_string_ascii_plus_s;
  extern const f_string_t f_string_ascii_pound_s;
  extern const f_string_t f_string_ascii_quote_double_s;
  extern const f_string_t f_string_ascii_quote_single_s;
  extern const f_string_t f_string_ascii_sign_at_s;
  extern const f_string_t f_string_ascii_sign_greater_than_s;
  extern const f_string_t f_string_ascii_sign_less_than_s;
  extern const f_string_t f_string_ascii_slash_forward_s;
  extern const f_string_t f_string_ascii_slash_backward_s;
  extern const f_string_t f_string_ascii_tilde_s;
  extern const f_string_t f_string_ascii_underscore_s;

  extern const f_string_t f_string_ascii_acknowledge_s;
  extern const f_string_t f_string_ascii_acknowledge_negative_s;
  extern const f_string_t f_string_ascii_bell_s;
  extern const f_string_t f_string_ascii_cancel_s;
  extern const f_string_t f_string_ascii_data_link_escape_s;
  extern const f_string_t f_string_ascii_device_control_one_s;
  extern const f_string_t f_string_ascii_device_control_two_s;
  extern const f_string_t f_string_ascii_device_control_three_s;
  extern const f_string_t f_string_ascii_device_control_four_s;
  extern const f_string_t f_string_ascii_enquiry_s;
  extern const f_string_t f_string_ascii_escape_s;
  extern const f_string_t f_string_ascii_feed_form_s;
  extern const f_string_t f_string_ascii_feed_line_s;
  extern const f_string_t f_string_ascii_header_start_s;
  extern const f_string_t f_string_ascii_medium_stop_s;
  extern const f_string_t f_string_ascii_null_s;
  extern const f_string_t f_string_ascii_return_carriage_s;
  extern const f_string_t f_string_ascii_separator_file_s;
  extern const f_string_t f_string_ascii_separator_group_s;
  extern const f_string_t f_string_ascii_separator_record_s;
  extern const f_string_t f_string_ascii_separator_unit_s;
  extern const f_string_t f_string_ascii_shift_in_s;
  extern const f_string_t f_string_ascii_shift_out_s;
  extern const f_string_t f_string_ascii_space_s;
  extern const f_string_t f_string_ascii_space_back_s;
  extern const f_string_t f_string_ascii_substitute_s;
  extern const f_string_t f_string_ascii_synchronous_idle_s;
  extern const f_string_t f_string_ascii_tab_horizontal_s;
  extern const f_string_t f_string_ascii_tab_vertical_s;
  extern const f_string_t f_string_ascii_text_start_s;
  extern const f_string_t f_string_ascii_text_stop_s;
  extern const f_string_t f_string_ascii_transmission_stop_s;
  extern const f_string_t f_string_ascii_transmission_block_end_s;
#endif // _di_string_ascii_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_common_h
