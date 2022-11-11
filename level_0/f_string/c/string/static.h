/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines static string data.
 *
 * This is auto-included by string.h and should not need to be explicitly included.
 */
#ifndef _F_string_static_h
#define _F_string_static_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A string that is analogous to f_string_dynamic_t but intended for static-only uses.
 *
 * The f_string_static_t type should always have size set to 0 to represent that it is a static string.
 * This allows for easier integration with f_string_dynamic_t.
 *
 * If size is set to some value other than 0 for a static string, then take special care not to intermix it with f_string_dynamic_t.
 *
 * A special macro_f_string_static_t_initialize() is provided to easily initialize a static string.
 * A special macro_f_string_static_t_initialize2() is provided to easily initialize a static string with an identical used and size.
 *
 * string: The string.
 * size:   Total amount of space available.
 * used:   Total number of space used.
 */
#ifndef _di_f_string_static_t_
  typedef struct {
    f_string_t string;

    f_array_length_t size;
    f_array_length_t used;
  } f_string_static_t;

  #define f_string_static_t_initialize { 0, 0, 0 }

  #define macro_f_string_static_t_initialize(string, size, used) { string, size, used }
  #define macro_f_string_static_t_initialize2(string, length) { string, length, length }

  #define macro_f_string_static_t_clear(string_static) \
    string_static.string = 0; \
    string_static.size = 0; \
    string_static.used = 0;
#endif // _di_f_string_static_t_

/**
 * Provide a static empty string.
 *
 * This is intended to represent an empty string.
 */
#ifndef _di_f_string_empty_s_
  #define F_string_empty_s ""
  #define F_string_empty_s_length 0

  extern const f_string_static_t f_string_empty_s;
#endif // _di_f_string_empty_s_

/**
 * Provide a static string focusing on the NULL character.
 *
 * This is different from f_string_empty_s in that it's used is set to 1 to represent the NULL character.
 */
#ifndef _di_f_string_null_s_
  #define F_string_null_s ""
  #define F_string_null_s_length 1

  extern const f_string_static_t f_string_null_s;
#endif // _di_f_string_null_s_

/**
 * Provide a character to use as a placeholder within some string.
 *
 * This is generally the NULL character and should be effectively the same as f_string_null_s.
 */
#ifndef _di_f_string_placeholder_s_
  #define F_string_placeholder_s F_string_null_s
  #define F_string_placeholder_s_length F_string_null_s_length

  #define f_string_placeholder_s f_string_null_s
#endif // _di_f_string_placeholder_s_

/**
 * Provide a set of ASCII strings.
 *
 * This is not intended to be exhaustive or language-specific.
 * Instead, this is for very common uses such as converting a hex-digit string into a number.
 * These are standardized not be the language, per-say, but instead by the specific standard (such as hexidecimal).
 *
 * The NULL ASCII string can be represented by the integer 0; however, given that these are all NULL-terminated strings the NULL character is represented with a NULL termination as well.
 * The NULL ASCII string therefore has two NULLs, first the NULL represents the NULL and the second represents the NULL termination.
 */
#ifndef _di_string_ascii_s_
  #define F_string_ascii_0_s "0"
  #define F_string_ascii_1_s "1"
  #define F_string_ascii_2_s "2"
  #define F_string_ascii_3_s "3"
  #define F_string_ascii_4_s "4"
  #define F_string_ascii_5_s "5"
  #define F_string_ascii_6_s "6"
  #define F_string_ascii_7_s "7"
  #define F_string_ascii_8_s "8"
  #define F_string_ascii_9_s "9"

  #define F_string_ascii_a_s "a"
  #define F_string_ascii_b_s "b"
  #define F_string_ascii_c_s "c"
  #define F_string_ascii_d_s "d"
  #define F_string_ascii_e_s "e"
  #define F_string_ascii_f_s "f"
  #define F_string_ascii_g_s "g"
  #define F_string_ascii_h_s "h"
  #define F_string_ascii_i_s "i"
  #define F_string_ascii_j_s "j"
  #define F_string_ascii_k_s "k"
  #define F_string_ascii_l_s "l"
  #define F_string_ascii_m_s "m"
  #define F_string_ascii_n_s "n"
  #define F_string_ascii_o_s "o"
  #define F_string_ascii_p_s "p"
  #define F_string_ascii_q_s "q"
  #define F_string_ascii_r_s "r"
  #define F_string_ascii_s_s "s"
  #define F_string_ascii_t_s "t"
  #define F_string_ascii_u_s "u"
  #define F_string_ascii_v_s "v"
  #define F_string_ascii_w_s "w"
  #define F_string_ascii_x_s "x"
  #define F_string_ascii_y_s "y"
  #define F_string_ascii_z_s "z"

  #define F_string_ascii_A_s "A"
  #define F_string_ascii_B_s "B"
  #define F_string_ascii_C_s "C"
  #define F_string_ascii_D_s "D"
  #define F_string_ascii_E_s "E"
  #define F_string_ascii_F_s "F"
  #define F_string_ascii_G_s "G"
  #define F_string_ascii_H_s "H"
  #define F_string_ascii_I_s "I"
  #define F_string_ascii_J_s "J"
  #define F_string_ascii_K_s "K"
  #define F_string_ascii_L_s "L"
  #define F_string_ascii_M_s "M"
  #define F_string_ascii_N_s "N"
  #define F_string_ascii_O_s "O"
  #define F_string_ascii_P_s "P"
  #define F_string_ascii_Q_s "Q"
  #define F_string_ascii_R_s "R"
  #define F_string_ascii_S_s "S"
  #define F_string_ascii_T_s "T"
  #define F_string_ascii_U_s "U"
  #define F_string_ascii_V_s "V"
  #define F_string_ascii_W_s "W"
  #define F_string_ascii_X_s "X"
  #define F_string_ascii_Y_s "Y"
  #define F_string_ascii_Z_s "Z"

  #define F_string_ascii_ampersand_s         "&"
  #define F_string_ascii_asterisk_s          "*"
  #define F_string_ascii_brace_close_s       "}"
  #define F_string_ascii_brace_open_s        "{"
  #define F_string_ascii_bracket_close_s     "]"
  #define F_string_ascii_bracket_open_s      "["
  #define F_string_ascii_caret_s             "^"
  #define F_string_ascii_comma_s             ","
  #define F_string_ascii_colon_s             ":"
  #define F_string_ascii_colon_semi_s        ";"
  #define F_string_ascii_dollar_s            "$"
  #define F_string_ascii_equal_s             "="
  #define F_string_ascii_exclamation_s       "!"
  #define F_string_ascii_grave_s             "`"
  #define F_string_ascii_mark_question_s     "?"
  #define F_string_ascii_minus_s             "-"
  #define F_string_ascii_parenthesis_open_s  "("
  #define F_string_ascii_parenthesis_close_s ")"
  #define F_string_ascii_percent_s           "%"
  #define F_string_ascii_period_s            "."
  #define F_string_ascii_pipe_s              "|"
  #define F_string_ascii_plus_s              "+"
  #define F_string_ascii_pound_s             "#"
  #define F_string_ascii_quote_double_s      "\""
  #define F_string_ascii_quote_single_s      "'"
  #define F_string_ascii_sign_at_s           "@"
  #define F_string_ascii_sign_greater_than_s ">"
  #define F_string_ascii_sign_less_than_s    "<"
  #define F_string_ascii_slash_forward_s     "/"
  #define F_string_ascii_slash_backward_s    "\\"
  #define F_string_ascii_tilde_s             "~"
  #define F_string_ascii_underscore_s        "_"

  #define F_string_ascii_acknowledge_s            ""
  #define F_string_ascii_acknowledge_negative_s   ""
  #define F_string_ascii_bell_s                   ""
  #define F_string_ascii_cancel_s                 ""
  #define F_string_ascii_data_link_escape_s       ""
  #define F_string_ascii_device_control_one_s     ""
  #define F_string_ascii_device_control_two_s     ""
  #define F_string_ascii_device_control_three_s   ""
  #define F_string_ascii_device_control_four_s    ""
  #define F_string_ascii_enquiry_s                ""
  #define F_string_ascii_escape_s                 ""
  #define F_string_ascii_feed_form_s              "\f"
  #define F_string_ascii_feed_line_s              "\n"
  #define F_string_ascii_header_start_s           ""
  #define F_string_ascii_medium_stop_s            ""
  #define F_string_ascii_null_s                   "\0"
  #define F_string_ascii_return_carriage_s        "\r"
  #define F_string_ascii_separator_file_s         ""
  #define F_string_ascii_separator_group_s        ""
  #define F_string_ascii_separator_record_s       ""
  #define F_string_ascii_separator_unit_s         ""
  #define F_string_ascii_shift_in_s               ""
  #define F_string_ascii_shift_out_s              ""
  #define F_string_ascii_space_s                  " "
  #define F_string_ascii_space_back_s             ""
  #define F_string_ascii_substitute_s             ""
  #define F_string_ascii_synchronous_idle_s       ""
  #define F_string_ascii_tab_horizontal_s         "\t"
  #define F_string_ascii_tab_vertical_s           "\v"
  #define F_string_ascii_text_start_s             ""
  #define F_string_ascii_text_stop_s              ""
  #define F_string_ascii_transmission_stop_s      ""
  #define F_string_ascii_transmission_block_end_s ""

  #define F_string_ascii_0_s_length 1
  #define F_string_ascii_1_s_length 1
  #define F_string_ascii_2_s_length 1
  #define F_string_ascii_3_s_length 1
  #define F_string_ascii_4_s_length 1
  #define F_string_ascii_5_s_length 1
  #define F_string_ascii_6_s_length 1
  #define F_string_ascii_7_s_length 1
  #define F_string_ascii_8_s_length 1
  #define F_string_ascii_9_s_length 1

  #define F_string_ascii_a_s_length 1
  #define F_string_ascii_b_s_length 1
  #define F_string_ascii_c_s_length 1
  #define F_string_ascii_d_s_length 1
  #define F_string_ascii_e_s_length 1
  #define F_string_ascii_f_s_length 1
  #define F_string_ascii_g_s_length 1
  #define F_string_ascii_h_s_length 1
  #define F_string_ascii_i_s_length 1
  #define F_string_ascii_j_s_length 1
  #define F_string_ascii_k_s_length 1
  #define F_string_ascii_l_s_length 1
  #define F_string_ascii_m_s_length 1
  #define F_string_ascii_n_s_length 1
  #define F_string_ascii_o_s_length 1
  #define F_string_ascii_p_s_length 1
  #define F_string_ascii_q_s_length 1
  #define F_string_ascii_r_s_length 1
  #define F_string_ascii_s_s_length 1
  #define F_string_ascii_t_s_length 1
  #define F_string_ascii_u_s_length 1
  #define F_string_ascii_v_s_length 1
  #define F_string_ascii_w_s_length 1
  #define F_string_ascii_x_s_length 1
  #define F_string_ascii_y_s_length 1
  #define F_string_ascii_z_s_length 1

  #define F_string_ascii_A_s_length 1
  #define F_string_ascii_B_s_length 1
  #define F_string_ascii_C_s_length 1
  #define F_string_ascii_D_s_length 1
  #define F_string_ascii_E_s_length 1
  #define F_string_ascii_F_s_length 1
  #define F_string_ascii_G_s_length 1
  #define F_string_ascii_H_s_length 1
  #define F_string_ascii_I_s_length 1
  #define F_string_ascii_J_s_length 1
  #define F_string_ascii_K_s_length 1
  #define F_string_ascii_L_s_length 1
  #define F_string_ascii_M_s_length 1
  #define F_string_ascii_N_s_length 1
  #define F_string_ascii_O_s_length 1
  #define F_string_ascii_P_s_length 1
  #define F_string_ascii_Q_s_length 1
  #define F_string_ascii_R_s_length 1
  #define F_string_ascii_S_s_length 1
  #define F_string_ascii_T_s_length 1
  #define F_string_ascii_U_s_length 1
  #define F_string_ascii_V_s_length 1
  #define F_string_ascii_W_s_length 1
  #define F_string_ascii_X_s_length 1
  #define F_string_ascii_Y_s_length 1
  #define F_string_ascii_Z_s_length 1

  #define F_string_ascii_ampersand_s_length         1
  #define F_string_ascii_asterisk_s_length          1
  #define F_string_ascii_brace_close_s_length       1
  #define F_string_ascii_brace_open_s_length        1
  #define F_string_ascii_bracket_close_s_length     1
  #define F_string_ascii_bracket_open_s_length      1
  #define F_string_ascii_caret_s_length             1
  #define F_string_ascii_comma_s_length             1
  #define F_string_ascii_colon_s_length             1
  #define F_string_ascii_colon_semi_s_length        1
  #define F_string_ascii_dollar_s_length            1
  #define F_string_ascii_equal_s_length             1
  #define F_string_ascii_exclamation_s_length       1
  #define F_string_ascii_grave_s_length             1
  #define F_string_ascii_mark_question_s_length     1
  #define F_string_ascii_minus_s_length             1
  #define F_string_ascii_parenthesis_open_s_length  1
  #define F_string_ascii_parenthesis_close_s_length 1
  #define F_string_ascii_percent_s_length           1
  #define F_string_ascii_period_s_length            1
  #define F_string_ascii_pipe_s_length              1
  #define F_string_ascii_plus_s_length              1
  #define F_string_ascii_pound_s_length             1
  #define F_string_ascii_quote_double_s_length      1
  #define F_string_ascii_quote_single_s_length      1
  #define F_string_ascii_sign_at_s_length           1
  #define F_string_ascii_sign_greater_than_s_length 1
  #define F_string_ascii_sign_less_than_s_length    1
  #define F_string_ascii_slash_forward_s_length     1
  #define F_string_ascii_slash_backward_s_length    1
  #define F_string_ascii_tilde_s_length             1
  #define F_string_ascii_underscore_s_length        1

  #define F_string_ascii_acknowledge_s_length            1
  #define F_string_ascii_acknowledge_negative_s_length   1
  #define F_string_ascii_bell_s_length                   1
  #define F_string_ascii_cancel_s_length                 1
  #define F_string_ascii_data_link_escape_s_length       1
  #define F_string_ascii_device_control_one_s_length     1
  #define F_string_ascii_device_control_two_s_length     1
  #define F_string_ascii_device_control_three_s_length   1
  #define F_string_ascii_device_control_four_s_length    1
  #define F_string_ascii_enquiry_s_length                1
  #define F_string_ascii_escape_s_length                 1
  #define F_string_ascii_feed_form_s_length              1
  #define F_string_ascii_feed_line_s_length              1
  #define F_string_ascii_header_start_s_length           1
  #define F_string_ascii_medium_stop_s_length            1
  #define F_string_ascii_null_s_length                   1
  #define F_string_ascii_return_carriage_s_length        1
  #define F_string_ascii_separator_file_s_length         1
  #define F_string_ascii_separator_group_s_length        1
  #define F_string_ascii_separator_record_s_length       1
  #define F_string_ascii_separator_unit_s_length         1
  #define F_string_ascii_shift_in_s_length               1
  #define F_string_ascii_shift_out_s_length              1
  #define F_string_ascii_space_s_length                  1
  #define F_string_ascii_space_back_s_length             1
  #define F_string_ascii_substitute_s_length             1
  #define F_string_ascii_synchronous_idle_s_length       1
  #define F_string_ascii_tab_horizontal_s_length         1
  #define F_string_ascii_tab_vertical_s_length           1
  #define F_string_ascii_text_start_s_length             1
  #define F_string_ascii_text_stop_s_length              1
  #define F_string_ascii_transmission_stop_s_length      1
  #define F_string_ascii_transmission_block_end_s_length 1

  extern const f_string_static_t f_string_ascii_0_s;
  extern const f_string_static_t f_string_ascii_1_s;
  extern const f_string_static_t f_string_ascii_2_s;
  extern const f_string_static_t f_string_ascii_3_s;
  extern const f_string_static_t f_string_ascii_4_s;
  extern const f_string_static_t f_string_ascii_5_s;
  extern const f_string_static_t f_string_ascii_6_s;
  extern const f_string_static_t f_string_ascii_7_s;
  extern const f_string_static_t f_string_ascii_8_s;
  extern const f_string_static_t f_string_ascii_9_s;

  extern const f_string_static_t f_string_ascii_a_s;
  extern const f_string_static_t f_string_ascii_b_s;
  extern const f_string_static_t f_string_ascii_c_s;
  extern const f_string_static_t f_string_ascii_d_s;
  extern const f_string_static_t f_string_ascii_e_s;
  extern const f_string_static_t f_string_ascii_f_s;
  extern const f_string_static_t f_string_ascii_g_s;
  extern const f_string_static_t f_string_ascii_h_s;
  extern const f_string_static_t f_string_ascii_i_s;
  extern const f_string_static_t f_string_ascii_j_s;
  extern const f_string_static_t f_string_ascii_k_s;
  extern const f_string_static_t f_string_ascii_l_s;
  extern const f_string_static_t f_string_ascii_m_s;
  extern const f_string_static_t f_string_ascii_n_s;
  extern const f_string_static_t f_string_ascii_o_s;
  extern const f_string_static_t f_string_ascii_p_s;
  extern const f_string_static_t f_string_ascii_q_s;
  extern const f_string_static_t f_string_ascii_r_s;
  extern const f_string_static_t f_string_ascii_s_s;
  extern const f_string_static_t f_string_ascii_t_s;
  extern const f_string_static_t f_string_ascii_u_s;
  extern const f_string_static_t f_string_ascii_v_s;
  extern const f_string_static_t f_string_ascii_w_s;
  extern const f_string_static_t f_string_ascii_x_s;
  extern const f_string_static_t f_string_ascii_y_s;
  extern const f_string_static_t f_string_ascii_z_s;

  extern const f_string_static_t f_string_ascii_A_s;
  extern const f_string_static_t f_string_ascii_B_s;
  extern const f_string_static_t f_string_ascii_C_s;
  extern const f_string_static_t f_string_ascii_D_s;
  extern const f_string_static_t f_string_ascii_E_s;
  extern const f_string_static_t f_string_ascii_F_s;
  extern const f_string_static_t f_string_ascii_G_s;
  extern const f_string_static_t f_string_ascii_H_s;
  extern const f_string_static_t f_string_ascii_I_s;
  extern const f_string_static_t f_string_ascii_J_s;
  extern const f_string_static_t f_string_ascii_K_s;
  extern const f_string_static_t f_string_ascii_L_s;
  extern const f_string_static_t f_string_ascii_M_s;
  extern const f_string_static_t f_string_ascii_N_s;
  extern const f_string_static_t f_string_ascii_O_s;
  extern const f_string_static_t f_string_ascii_P_s;
  extern const f_string_static_t f_string_ascii_Q_s;
  extern const f_string_static_t f_string_ascii_R_s;
  extern const f_string_static_t f_string_ascii_S_s;
  extern const f_string_static_t f_string_ascii_T_s;
  extern const f_string_static_t f_string_ascii_U_s;
  extern const f_string_static_t f_string_ascii_V_s;
  extern const f_string_static_t f_string_ascii_W_s;
  extern const f_string_static_t f_string_ascii_X_s;
  extern const f_string_static_t f_string_ascii_Y_s;
  extern const f_string_static_t f_string_ascii_Z_s;

  extern const f_string_static_t f_string_ascii_ampersand_s;
  extern const f_string_static_t f_string_ascii_asterisk_s;
  extern const f_string_static_t f_string_ascii_brace_close_s;
  extern const f_string_static_t f_string_ascii_brace_open_s;
  extern const f_string_static_t f_string_ascii_bracket_close_s;
  extern const f_string_static_t f_string_ascii_bracket_open_s;
  extern const f_string_static_t f_string_ascii_caret_s;
  extern const f_string_static_t f_string_ascii_comma_s;
  extern const f_string_static_t f_string_ascii_colon_s;
  extern const f_string_static_t f_string_ascii_colon_semi_s;
  extern const f_string_static_t f_string_ascii_dollar_s;
  extern const f_string_static_t f_string_ascii_equal_s;
  extern const f_string_static_t f_string_ascii_exclamation_s;
  extern const f_string_static_t f_string_ascii_grave_s;
  extern const f_string_static_t f_string_ascii_mark_question_s;
  extern const f_string_static_t f_string_ascii_minus_s;
  extern const f_string_static_t f_string_ascii_parenthesis_open_s;
  extern const f_string_static_t f_string_ascii_parenthesis_close_s;
  extern const f_string_static_t f_string_ascii_percent_s;
  extern const f_string_static_t f_string_ascii_period_s;
  extern const f_string_static_t f_string_ascii_pipe_s;
  extern const f_string_static_t f_string_ascii_plus_s;
  extern const f_string_static_t f_string_ascii_pound_s;
  extern const f_string_static_t f_string_ascii_quote_double_s;
  extern const f_string_static_t f_string_ascii_quote_single_s;
  extern const f_string_static_t f_string_ascii_sign_at_s;
  extern const f_string_static_t f_string_ascii_sign_greater_than_s;
  extern const f_string_static_t f_string_ascii_sign_less_than_s;
  extern const f_string_static_t f_string_ascii_slash_forward_s;
  extern const f_string_static_t f_string_ascii_slash_backward_s;
  extern const f_string_static_t f_string_ascii_tilde_s;
  extern const f_string_static_t f_string_ascii_underscore_s;

  extern const f_string_static_t f_string_ascii_acknowledge_s;
  extern const f_string_static_t f_string_ascii_acknowledge_negative_s;
  extern const f_string_static_t f_string_ascii_bell_s;
  extern const f_string_static_t f_string_ascii_cancel_s;
  extern const f_string_static_t f_string_ascii_data_link_escape_s;
  extern const f_string_static_t f_string_ascii_device_control_one_s;
  extern const f_string_static_t f_string_ascii_device_control_two_s;
  extern const f_string_static_t f_string_ascii_device_control_three_s;
  extern const f_string_static_t f_string_ascii_device_control_four_s;
  extern const f_string_static_t f_string_ascii_enquiry_s;
  extern const f_string_static_t f_string_ascii_escape_s;
  extern const f_string_static_t f_string_ascii_feed_form_s;
  extern const f_string_static_t f_string_ascii_feed_line_s;
  extern const f_string_static_t f_string_ascii_header_start_s;
  extern const f_string_static_t f_string_ascii_medium_stop_s;
  extern const f_string_static_t f_string_ascii_null_s;
  extern const f_string_static_t f_string_ascii_return_carriage_s;
  extern const f_string_static_t f_string_ascii_separator_file_s;
  extern const f_string_static_t f_string_ascii_separator_group_s;
  extern const f_string_static_t f_string_ascii_separator_record_s;
  extern const f_string_static_t f_string_ascii_separator_unit_s;
  extern const f_string_static_t f_string_ascii_shift_in_s;
  extern const f_string_static_t f_string_ascii_shift_out_s;
  extern const f_string_static_t f_string_ascii_space_s;
  extern const f_string_static_t f_string_ascii_space_back_s;
  extern const f_string_static_t f_string_ascii_substitute_s;
  extern const f_string_static_t f_string_ascii_synchronous_idle_s;
  extern const f_string_static_t f_string_ascii_tab_horizontal_s;
  extern const f_string_static_t f_string_ascii_tab_vertical_s;
  extern const f_string_static_t f_string_ascii_text_start_s;
  extern const f_string_static_t f_string_ascii_text_stop_s;
  extern const f_string_static_t f_string_ascii_transmission_stop_s;
  extern const f_string_static_t f_string_ascii_transmission_block_end_s;
#endif // _di_string_ascii_s_

/**
 * Define the end of line character.
 * FLL forbids '\r' and '\r\n' as end of line characters, \r will be silently ignored.
 */
#ifndef _di_f_string_eol_s_
  #define f_string_eol_s f_string_ascii_feed_line_s
  #define F_string_eol_s F_string_ascii_feed_line_s

  #define F_string_eol_s_length 1
#endif // _di_f_string_eol_s_

/**
 * Provide a character to represent a single basic space.
 *
 * This is generally intended to be an ASCII space character and should be effectively the same as F_string_ascii_space_s.
 */
#ifndef _di_f_string_space_s_
  #define F_string_space_s F_string_ascii_space_s
  #define F_string_space_s_length F_string_ascii_space_s_length

  #define f_string_space_s f_string_ascii_space_s
#endif // _di_f_string_space_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_static_h
