/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Defines dynamic (and static) string data.
 *
 * This is auto-included by string.h and should not need to be explicitly included.
 */
#ifndef _F_string_dynamic_h
#define _F_string_dynamic_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A string that is analogous to f_string_dynamic_t but intended for static-only uses.
 *
 * The f_string_static_t type should never be directly allocated or deallocated.
 *
 * A special macro_f_string_static_t_initialize2() is provided for the special purpose of easily initialize a static string with an identical used and size.
 * A special macro_f_string_static_t_initialize() is provided for the special purpose of easily initialize a static string.
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

  #define macro_f_string_static_t_clear(string_static) \
    string_static.string = 0; \
    string_static.size = 0; \
    string_static.used = 0;

  #define macro_f_string_static_t_initialize(string, size, used) { string, size, used }
  #define macro_f_string_static_t_initialize2(string, length) { string, length, length }
#endif // _di_f_string_static_t_

/**
 * A string that supports contains a size attribute to handle dynamic allocations and deallocations.
 *
 * Save the string size along with the string, so that strlen(..) commands can be avoided as much as possible.
 *
 * This is a sub-type of f_string_static_t, allowing it to be passed into any f_string_static_t type.
 * It is recommended that f_string_static_t are not otherwise casted into f_string_dynamic_t to avoid potential memory allocation issues.
 *
 * string: The string.
 * size:   Total amount of allocated space.
 * used:   Total number of allocated spaces used.
 */
#ifndef _di_f_string_dynamic_t_
  typedef f_string_static_t f_string_dynamic_t;

  #define f_string_dynamic_t_initialize f_string_static_t_initialize

  #define macro_f_string_dynamic_t_clear(dynamic) macro_f_string_static_t_clear(dynamic)

  #define macro_f_string_dynamic_t_resize(status, dynamic, length) status = f_string_dynamic_resize(length, &dynamic);
  #define macro_f_string_dynamic_t_adjust(status, dynamic, length) status = f_string_dynamic_adjust(length, &dynamic);

  #define macro_f_string_dynamic_t_delete_simple(dynamic)  f_string_dynamic_resize(0, &dynamic);
  #define macro_f_string_dynamic_t_destroy_simple(dynamic) f_string_dynamic_adjust(0, &dynamic);

  #define macro_f_string_dynamic_t_increase(status, step, dynamic)      status = f_string_dynamic_increase(step, &dynamic);
  #define macro_f_string_dynamic_t_increase_by(status, dynamic, amount) status = f_string_dynamic_increase_by(amount, &dynamic);
  #define macro_f_string_dynamic_t_decrease_by(status, dynamic, amount) status = f_string_dynamic_decrease_by(amount, &dynamic);
  #define macro_f_string_dynamic_t_decimate_by(status, dynamic, amount) status = f_string_dynamic_decimate_by(amount, &dynamic);
#endif // _di_f_string_dynamic_t_

/**
 * An array of static strings.
 *
 * array: The array of static strings.
 * size:  Total amount of space available.
 * used:  Total number of space used.
 */
#ifndef _di_f_string_statics_t_
  typedef struct {
    f_string_static_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_string_statics_t;

  #define f_string_statics_t_initialize { 0, 0, 0 }

  #define macro_f_string_statics_t_clear(statics) \
    statics.array = 0; \
    statics.size = 0; \
    statics.used = 0;
#endif // _di_f_string_statics_t_

/**
 * An array of dynamic dynamics.
 *
 * array: The array of dynamic dynamics.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_string_dynamics_t_
  typedef f_string_statics_t f_string_dynamics_t;

  #define f_string_dynamics_t_initialize f_string_statics_t_initialize

  #define macro_f_string_dynamics_t_clear(dynamics) macro_f_string_statics_t_clear(dynamics)

  #define macro_f_string_dynamics_t_resize(status, dynamics, length) status = f_string_dynamics_resize(length, &dynamics);
  #define macro_f_string_dynamics_t_adjust(status, dynamics, length) status = f_string_dynamics_adjust(length, &dynamics);

  #define macro_f_string_dynamics_t_delete_simple(dynamics)  f_string_dynamics_resize(0, &dynamics);
  #define macro_f_string_dynamics_t_destroy_simple(dynamics) f_string_dynamics_adjust(0, &dynamics);

  #define macro_f_string_dynamics_t_increase(status, step, dynamics)      status = f_string_dynamics_increase(step, &dynamics);
  #define macro_f_string_dynamics_t_increase_by(status, dynamics, amount) status = f_string_dynamics_increase_by(amount, &dynamics);
  #define macro_f_string_dynamics_t_decrease_by(status, dynamics, amount) status = f_string_dynamics_decrease_by(amount, &dynamics);
  #define macro_f_string_dynamics_t_decimate_by(status, dynamics, amount) status = f_string_dynamics_decimate_by(amount, &dynamics);
#endif // _di_f_string_dynamics_t_

/**
 * An array of static strings.
 *
 * array: The array of static strings.
 * size:  Total amount of space available.
 * used:  Total number of space used.
 */
#ifndef _di_f_string_staticss_t_
  typedef struct {
    f_string_statics_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_string_staticss_t;

  #define f_string_staticss_t_initialize { 0, 0, 0 }

  #define macro_f_string_staticss_t_clear(staticss) \
    staticss.array = 0; \
    staticss.size = 0; \
    staticss.used = 0;
#endif // _di_f_string_staticss_t_

/**
 * An array of dynamic dynamicss.
 *
 * array: The array of dynamic dynamicss.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_string_dynamicss_t_
  typedef f_string_staticss_t f_string_dynamicss_t;

  #define f_string_dynamicss_t_initialize f_string_staticss_t_initialize

  #define macro_f_string_dynamicss_t_clear(dynamicss) macro_f_string_staticss_t_clear(dynamicss)

  #define macro_f_string_dynamicss_t_resize(status, dynamicss, length) status = f_string_dynamicss_resize(length, &dynamicss);
  #define macro_f_string_dynamicss_t_adjust(status, dynamicss, length) status = f_string_dynamicss_adjust(length, &dynamicss);

  #define macro_f_string_dynamicss_t_delete_simple(dynamicss)  f_string_dynamicss_resize(0, &dynamicss);
  #define macro_f_string_dynamicss_t_destroy_simple(dynamicss) f_string_dynamicss_adjust(0, &dynamicss);

  #define macro_f_string_dynamicss_t_increase(status, step, dynamicss)      status = f_string_dynamicss_increase(step, &dynamicss);
  #define macro_f_string_dynamicss_t_increase_by(status, dynamicss, amount) status = f_string_dynamicss_increase_by(amount, &dynamicss);
  #define macro_f_string_dynamicss_t_decrease_by(status, dynamicss, amount) status = f_string_dynamicss_decrease_by(amount, &dynamicss);
  #define macro_f_string_dynamicss_t_decimate_by(status, dynamicss, amount) status = f_string_dynamicss_decimate_by(amount, &dynamicss);
#endif // _di_f_string_dynamicss_t_

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
 *
 * @todo provide extended ASCII-characters.
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

/**
 * Resize the dynamic string.
 *
 * @param length
 *   The new size to use.
 * @param dynamic
 *   The string to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_dynamic_adjust_
  extern f_status_t f_string_dynamic_adjust(const f_array_length_t length, f_string_dynamic_t *dynamic);
#endif // _di_f_string_dynamic_adjust_

/**
 * Append the source string onto the destination.
 *
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_append_
  extern f_status_t f_string_dynamic_append(const f_string_dynamic_t source, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_append_

/**
 * Append the source string onto the destination only if the string is not already at the end.
 *
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_append_assure_
  extern f_status_t f_string_dynamic_append_assure(const f_string_static_t source, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_append_assure_

/**
 * Append the source string onto the destination only if the string is not already at the end.
 *
 * Skips over NULL characters from source when appending.
 *
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_append_assure_nulless_
  extern f_status_t f_string_dynamic_append_assure_nulless(const f_string_static_t source, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_append_assure_nulless_

/**
 * Append the source string onto the destination.
 *
 * Skips over NULL characters from source when appending.
 *
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_append_nulless_
  extern f_status_t f_string_dynamic_append_nulless(const f_string_static_t source, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_append_nulless_

/**
 * Resize the dynamic string to a smaller size.
 *
 * This will resize making the string smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param dynamic
 *   The string to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_decrease_by_
  extern f_status_t f_string_dynamic_decrease_by(const f_array_length_t amount, f_string_dynamic_t *dynamic);
#endif // _di_f_string_dynamic_decrease_by_

/**
 * Resize the dynamic string to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param dynamic
 *   The string to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_increase_
  extern f_status_t f_string_dynamic_increase(const uint16_t step, f_string_dynamic_t *dynamic);
#endif // _di_f_string_dynamic_increase_

/**
 * Resize the dynamic string to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param dynamic
 *   The string to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_increase_by_
  extern f_status_t f_string_dynamic_increase_by(const f_array_length_t amount, f_string_dynamic_t *dynamic);
#endif // _di_f_string_dynamic_increase_by_

/**
 * Append the source string onto the destination with the glue in between.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_mash_
  extern f_status_t f_string_dynamic_mash(const f_string_static_t glue, const f_string_static_t source, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_mash_

/**
 * Append the source string onto the destination with the glue in between.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * Skips over NULL characters from glue and source when appending.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_mash_nulless_
  extern f_status_t f_string_dynamic_mash_nulless(const f_string_static_t glue, const f_string_static_t source, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_mash_nulless_

/**
 * Prepend the source string onto the destination with the glue in between.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_mish_
  extern f_status_t f_string_dynamic_mish(const f_string_static_t glue, const f_string_static_t source, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_mish_

/**
 * Prepend the source string onto the destination with the glue in between.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * Skips over NULL characters from glue and source when appending.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_mish_nulless_
  extern f_status_t f_string_dynamic_mish_nulless(const f_string_static_t glue, const f_string_static_t source, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_mish_nulless_

/**
 * Append the source string onto the destination, but restricted to the given range.
 *
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_partial_append_
  extern f_status_t f_string_dynamic_partial_append(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_partial_append_

/**
 * Append the source string onto the destination only if the string is not already at the end and restricted to the given range.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 *
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_partial_append_assure_
  extern f_status_t f_string_dynamic_partial_append_assure(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_partial_append_assure_

/**
 * Append the source string onto the destination only if the string is not already at the end and restricted to the given range.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 *
 * Skips over NULL characters from source when appending.
 *
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_partial_append_assure_nulless_
  extern f_status_t f_string_dynamic_partial_append_assure_nulless(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_partial_append_assure_nulless_

/**
 * Append the source string onto the destination, but restricted to the given range.
 *
 * Skips over NULL characters from source when appending.
 *
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_partial_append_nulless_
  extern f_status_t f_string_dynamic_partial_append_nulless(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_partial_append_nulless_

/**
 * Append the source string onto the destination with the glue in between, but restricted to the given range.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_partial_mash_
  extern f_status_t f_string_dynamic_partial_mash(const f_string_static_t glue, const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_partial_mash_

/**
 * Append the source string onto the destination with the glue in between, but restricted to the given range.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * Skips over NULL characters from glue and source when appending.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_partial_mash_nulless_
  extern f_status_t f_string_dynamic_partial_mash_nulless(const f_string_static_t glue, const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_partial_mash_nulless_

/**
 * Prepend the source string onto the destination with the glue in between, but restricted to the given range.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_partial_mish_
  extern f_status_t f_string_dynamic_partial_mish(const f_string_static_t glue, const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_partial_mish_

/**
 * Prepend the source string onto the destination with the glue in between, but restricted to the given range.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * Skips over NULL characters from glue and source when appending.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_partial_mish_nulless_
  extern f_status_t f_string_dynamic_partial_mish_nulless(const f_string_static_t glue, const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_partial_mish_nulless_

/**
 * Prepend the source string onto the destination, but restricted to the given range.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * @param source
 *   The source string to prepend.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_partial_prepend_
  extern f_status_t f_string_dynamic_partial_prepend(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_partial_prepend_

/**
 * Prepend the source string onto the destination only if the string is not already at the beginning and restricted to the given range.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 *
 * @param source
 *   The source string to prepend.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_partial_prepend_assure_
  extern f_status_t f_string_dynamic_partial_prepend_assure(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_partial_prepend_assure_

/**
 * Prepend the source string onto the destination only if the string is not already at the beginning and restricted to the given range.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 *
 * @param source
 *   The source string to prepend.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_partial_prepend_assure_nulless_
  extern f_status_t f_string_dynamic_partial_prepend_assure_nulless(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_partial_prepend_assure_nulless_

/**
 * Prepend the source string onto the destination, but restricted to the given range.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * @param source
 *   The source string to prepend.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_partial_prepend_nulless_
  extern f_status_t f_string_dynamic_partial_prepend_nulless(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_partial_prepend_nulless_

/**
 * Prepend the source string onto the destination.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * @param source
 *   The source string to prepend.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_prepend_
  extern f_status_t f_string_dynamic_prepend(const f_string_static_t source, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_prepend_

/**
 * Prepend the source string onto the destination only if the string is not already at the beginning.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 *
 * @param source
 *   The source string to prepend.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_prepend_assure_
  extern f_status_t f_string_dynamic_prepend_assure(const f_string_static_t source, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_prepend_assure_

/**
 * Prepend the source string onto the destination only if the string is not already at the beginning.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 *
 * @param source
 *   The source string to prepend.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_prepend_assure_nulless_
  extern f_status_t f_string_dynamic_prepend_assure_nulless(const f_string_static_t source, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_prepend_assure_nulless_

/**
 * Prepend the source string onto the destination.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * @param source
 *   The source string to prepend.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_prepend_nulless_
  extern f_status_t f_string_dynamic_prepend_nulless(const f_string_static_t source, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_prepend_nulless_

/**
 * Resize the dynamic string.
 *
 * @param length
 *   The new size to use.
 * @param buffer
 *   The string to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_resize_
  extern f_status_t f_string_dynamic_resize(const f_array_length_t length, f_string_dynamic_t *buffer);
#endif // _di_f_string_dynamic_resize_

/**
 * Seek the buffer location forward until EOL is reached.
 *
 * @param buffer
 *   The buffer to traverse.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 *
 * @return
 *   F_none on success.
 *   F_none_eos on success, but stopped at end of string.
 *   F_none_stop on success, but stopped at end of range.
 *   F_data_not on success, but there was no string data to seek.
 *   F_data_not_stop on success, but the range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_seek_line_
  extern f_status_t f_string_dynamic_seek_line(const f_string_static_t buffer, f_string_range_t *range);
#endif // _di_f_string_dynamic_seek_line_

/**
 * Seek the buffer location forward until the character (1-byte wide) or EOL is reached.
 *
 * @param buffer
 *   The buffer to traverse.
 * @param seek_to_this
 *   A single-width character representing a character to seek to.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 *
 * @return
 *   F_none on success.
 *   F_none_eos on success, but stopped at end of string.
 *   F_none_stop on success, but stopped at end of range.
 *   F_data_not on success, but there was no string data to seek.
 *   F_data_not_stop on success, but the range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_seek_line_to_
  extern f_status_t f_string_dynamic_seek_line_to(const f_string_static_t buffer, const char seek_to_this, f_string_range_t *range);
#endif // _di_f_string_dynamic_seek_line_to_

/**
 * Seek the buffer location forward until the character (1-byte wide) is reached.
 *
 * @param buffer
 *   The buffer to traverse.
 * @param seek_to_this
 *   A single-width character representing a character to seek to.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 *
 * @return
 *   F_none on success.
 *   F_none_eos on success, but stopped at end of string.
 *   F_none_stop on success, but stopped at end of range.
 *   F_data_not on success, but there was no string data to seek.
 *   F_data_not_stop on success, but the range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_seek_to_
  extern f_status_t f_string_dynamic_seek_to(const f_string_static_t buffer, const char seek_to_this, f_string_range_t *range);
#endif // _di_f_string_dynamic_seek_to_

/**
 * Guarantee that an end of string (NULL) exists at the end of the string.
 *
 * This is intended to be used for anything requiring NULL terminated strings.
 * This will reallocate more space if necessary.
 *
 * If destination size is 0, then it will be reallocated and have the NULL assigned at index 0.
 *
 * @param destination
 *   The new string, which will be allocated or reallocated as necessary.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if string is too large to fit into the buffer.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_terminate_
  extern f_status_t f_string_dynamic_terminate(f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_terminate_

/**
 * Guarantee that an end of string (NULL) exists at the end of the string.
 *
 * This ensures that the terminating NULL not only exists but is not counted in destination.used.
 *
 * This is intended to be used for anything requiring NULL terminated strings whose used length cannot be counted.
 * This will reallocate more space if necessary.
 *
 * If destination size is 0, then it will be reallocated and have the NULL assigned at index 0.
 *
 * @param destination
 *   The new string, which will be allocated or reallocated as necessary.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if string is too large to fit into the buffer.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_terminate_after_
  extern f_status_t f_string_dynamic_terminate_after(f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_terminate_after_

/**
 * Resize the dynamic string array.
 *
 * @param length
 *   The new size to use.
 * @param dynamics
 *   The array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_string_dynamics_adjust_
  extern f_status_t f_string_dynamics_adjust(const f_array_length_t length, f_string_dynamics_t * const dynamics);
#endif // _di_f_string_dynamics_adjust_

/**
 * Append the source strings onto the destination.
 *
 * @param source
 *   The source strings to append.
 * @param destination
 *   The destination strings the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamics_append_
  extern f_status_t f_string_dynamics_append(const f_string_dynamics_t source, f_string_dynamics_t *destination);
#endif // _di_f_string_dynamics_append_

/**
 * Resize the dynamic string array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param dynamics
 *   The array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamics_decimate_by_
  extern f_status_t f_string_dynamics_decimate_by(const f_array_length_t amount, f_string_dynamics_t * const dynamics);
#endif // _di_f_string_dynamics_decimate_by_

/**
 * Resize the dynamic string array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param dynamics
 *   The array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamics_decrease_by_
  extern f_status_t f_string_dynamics_decrease_by(const f_array_length_t amount, f_string_dynamics_t * const dynamics);
#endif // _di_f_string_dynamics_decrease_by_

/**
 * Increase the size of the dynamic string array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param dynamics
 *   The array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamics_increase_
  extern f_status_t f_string_dynamics_increase(const uint16_t step, f_string_dynamics_t * const dynamics);
#endif // _di_f_string_dynamics_increase_

/**
 * Resize the dynamic string array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param dynamics
 *   The array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamics_increase_by_
  extern f_status_t f_string_dynamics_increase_by(const f_array_length_t amount, f_string_dynamics_t * const dynamics);
#endif // _di_f_string_dynamics_increase_by_

/**
 * Resize the dynamic string array.
 *
 * @param length
 *   The new size to use.
 * @param dynamics
 *   The array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamics_resize_
  extern f_status_t f_string_dynamics_resize(const f_array_length_t length, f_string_dynamics_t * const dynamics);
#endif // _di_f_string_dynamics_resize_

/**
 * Resize the dynamics string array.
 *
 * @param length
 *   The new size to use.
 * @param dynamicss
 *   The array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_string_dynamicss_adjust_
  extern f_status_t f_string_dynamicss_adjust(const f_array_length_t length, f_string_dynamicss_t * const dynamicss);
#endif // _di_f_string_dynamicss_adjust_

/**
 * Append the source strings onto the destination.
 *
 * @param source
 *   The source strings to append.
 * @param destination
 *   The destination strings the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamicss_append_
  extern f_status_t f_string_dynamicss_append(const f_string_dynamicss_t source, f_string_dynamicss_t *destination);
#endif // _di_f_string_dynamicss_append_

/**
 * Resize the dynamics string array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param dynamicss
 *   The array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamicss_decimate_by_
  extern f_status_t f_string_dynamicss_decimate_by(const f_array_length_t amount, f_string_dynamicss_t * const dynamicss);
#endif // _di_f_string_dynamicss_decimate_by_

/**
 * Resize the dynamics string array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param dynamicss
 *   The array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamicss_decrease_by_
  extern f_status_t f_string_dynamicss_decrease_by(const f_array_length_t amount, f_string_dynamicss_t * const dynamicss);
#endif // _di_f_string_dynamicss_decrease_by_

/**
 * Increase the size of the dynamics string array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param dynamicss
 *   The array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamicss_increase_
  extern f_status_t f_string_dynamicss_increase(const uint16_t step, f_string_dynamicss_t * const dynamicss);
#endif // _di_f_string_dynamicss_increase_

/**
 * Resize the dynamics string array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param dynamicss
 *   The array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamicss_increase_by_
  extern f_status_t f_string_dynamicss_increase_by(const f_array_length_t amount, f_string_dynamicss_t * const dynamicss);
#endif // _di_f_string_dynamicss_increase_by_

/**
 * Resize the dynamics string array.
 *
 * @param length
 *   The new size to use.
 * @param dynamicss
 *   The array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamicss_resize_
  extern f_status_t f_string_dynamicss_resize(const f_array_length_t length, f_string_dynamicss_t * const dynamicss);
#endif // _di_f_string_dynamicss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_dynamic_h
