#include "string.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_string_empty_s_
  const f_string_t f_string_empty_s = "";
#endif // _di_f_string_empty_s_

#ifndef _di_string_format_s_
  const f_string_t f_string_format_string_s = F_string_format_string_s;
  const f_string_t f_string_format_character_s = F_string_format_character_s;
  const f_string_t f_string_format_wide_string_s = F_string_format_wide_string_s;
  const f_string_t f_string_format_wide_character_s = F_string_format_wide_character_s;
  const f_string_t f_string_format_integer_s = F_string_format_integer_s;
  const f_string_t f_string_format_unsigned_s = F_string_format_unsigned_s;
  const f_string_t f_string_format_digit_s = F_string_format_digit_s;
  const f_string_t f_string_format_float_s = F_string_format_float_s;
  const f_string_t f_string_format_short_integer_s = F_string_format_short_integer_s;
  const f_string_t f_string_format_short_unsigned_s = F_string_format_short_unsigned_s;
  const f_string_t f_string_format_long_integer_s = F_string_format_long_integer_s;
  const f_string_t f_string_format_long_unsigned_s = F_string_format_long_unsigned_s;
  const f_string_t f_string_format_long_double_s = F_string_format_long_double_s;
  const f_string_t f_string_format_long_long_integer_s = F_string_format_long_long_integer_s;
  const f_string_t f_string_format_long_long_unsigned_s = F_string_format_long_long_unsigned_s;
#endif // _di_string_format_s_

#ifndef _di_string_ascii_s_
  const f_string_t f_string_ascii_0_s = F_string_ascii_0_s;
  const f_string_t f_string_ascii_1_s = F_string_ascii_1_s;
  const f_string_t f_string_ascii_2_s = F_string_ascii_2_s;
  const f_string_t f_string_ascii_3_s = F_string_ascii_3_s;
  const f_string_t f_string_ascii_4_s = F_string_ascii_4_s;
  const f_string_t f_string_ascii_5_s = F_string_ascii_5_s;
  const f_string_t f_string_ascii_6_s = F_string_ascii_6_s;
  const f_string_t f_string_ascii_7_s = F_string_ascii_7_s;
  const f_string_t f_string_ascii_8_s = F_string_ascii_8_s;
  const f_string_t f_string_ascii_9_s = F_string_ascii_9_s;

  const f_string_t f_string_ascii_a_s = F_string_ascii_a_s;
  const f_string_t f_string_ascii_b_s = F_string_ascii_b_s;
  const f_string_t f_string_ascii_c_s = F_string_ascii_c_s;
  const f_string_t f_string_ascii_d_s = F_string_ascii_d_s;
  const f_string_t f_string_ascii_e_s = F_string_ascii_e_s;
  const f_string_t f_string_ascii_f_s = F_string_ascii_f_s;
  const f_string_t f_string_ascii_g_s = F_string_ascii_g_s;
  const f_string_t f_string_ascii_h_s = F_string_ascii_h_s;
  const f_string_t f_string_ascii_i_s = F_string_ascii_i_s;
  const f_string_t f_string_ascii_j_s = F_string_ascii_j_s;
  const f_string_t f_string_ascii_k_s = F_string_ascii_k_s;
  const f_string_t f_string_ascii_l_s = F_string_ascii_l_s;
  const f_string_t f_string_ascii_m_s = F_string_ascii_m_s;
  const f_string_t f_string_ascii_n_s = F_string_ascii_n_s;
  const f_string_t f_string_ascii_o_s = F_string_ascii_o_s;
  const f_string_t f_string_ascii_p_s = F_string_ascii_p_s;
  const f_string_t f_string_ascii_q_s = F_string_ascii_q_s;
  const f_string_t f_string_ascii_r_s = F_string_ascii_r_s;
  const f_string_t f_string_ascii_s_s = F_string_ascii_s_s;
  const f_string_t f_string_ascii_t_s = F_string_ascii_t_s;
  const f_string_t f_string_ascii_u_s = F_string_ascii_u_s;
  const f_string_t f_string_ascii_v_s = F_string_ascii_v_s;
  const f_string_t f_string_ascii_w_s = F_string_ascii_w_s;
  const f_string_t f_string_ascii_x_s = F_string_ascii_x_s;
  const f_string_t f_string_ascii_y_s = F_string_ascii_y_s;
  const f_string_t f_string_ascii_z_s = F_string_ascii_z_s;

  const f_string_t f_string_ascii_A_s = F_string_ascii_A_s;
  const f_string_t f_string_ascii_B_s = F_string_ascii_B_s;
  const f_string_t f_string_ascii_C_s = F_string_ascii_C_s;
  const f_string_t f_string_ascii_D_s = F_string_ascii_D_s;
  const f_string_t f_string_ascii_E_s = F_string_ascii_E_s;
  const f_string_t f_string_ascii_F_s = F_string_ascii_F_s;
  const f_string_t f_string_ascii_G_s = F_string_ascii_G_s;
  const f_string_t f_string_ascii_H_s = F_string_ascii_H_s;
  const f_string_t f_string_ascii_I_s = F_string_ascii_I_s;
  const f_string_t f_string_ascii_J_s = F_string_ascii_J_s;
  const f_string_t f_string_ascii_K_s = F_string_ascii_K_s;
  const f_string_t f_string_ascii_L_s = F_string_ascii_L_s;
  const f_string_t f_string_ascii_M_s = F_string_ascii_M_s;
  const f_string_t f_string_ascii_N_s = F_string_ascii_N_s;
  const f_string_t f_string_ascii_O_s = F_string_ascii_O_s;
  const f_string_t f_string_ascii_P_s = F_string_ascii_P_s;
  const f_string_t f_string_ascii_Q_s = F_string_ascii_Q_s;
  const f_string_t f_string_ascii_R_s = F_string_ascii_R_s;
  const f_string_t f_string_ascii_S_s = F_string_ascii_S_s;
  const f_string_t f_string_ascii_T_s = F_string_ascii_T_s;
  const f_string_t f_string_ascii_U_s = F_string_ascii_U_s;
  const f_string_t f_string_ascii_V_s = F_string_ascii_V_s;
  const f_string_t f_string_ascii_W_s = F_string_ascii_W_s;
  const f_string_t f_string_ascii_X_s = F_string_ascii_X_s;
  const f_string_t f_string_ascii_Y_s = F_string_ascii_Y_s;
  const f_string_t f_string_ascii_Z_s = F_string_ascii_Z_s;

  const f_string_t f_string_ascii_ampersand_s = F_string_ascii_ampersand_s;
  const f_string_t f_string_ascii_asterisk_s = F_string_ascii_asterisk_s;
  const f_string_t f_string_ascii_brace_close_s = F_string_ascii_brace_close_s;
  const f_string_t f_string_ascii_brace_open_s = F_string_ascii_brace_open_s;
  const f_string_t f_string_ascii_bracket_close_s = F_string_ascii_bracket_close_s;
  const f_string_t f_string_ascii_bracket_open_s = F_string_ascii_bracket_open_s;
  const f_string_t f_string_ascii_caret_s = F_string_ascii_caret_s;
  const f_string_t f_string_ascii_comma_s = F_string_ascii_comma_s;
  const f_string_t f_string_ascii_colon_s = F_string_ascii_colon_s;
  const f_string_t f_string_ascii_colon_semi_s = F_string_ascii_colon_semi_s;
  const f_string_t f_string_ascii_dollar_s = F_string_ascii_dollar_s;
  const f_string_t f_string_ascii_equal_s = F_string_ascii_equal_s;
  const f_string_t f_string_ascii_exclamation_s = F_string_ascii_exclamation_s;
  const f_string_t f_string_ascii_grave_s = F_string_ascii_grave_s;
  const f_string_t f_string_ascii_mark_question_s = F_string_ascii_mark_question_s;
  const f_string_t f_string_ascii_minus_s = F_string_ascii_minus_s;
  const f_string_t f_string_ascii_parenthesis_open_s = F_string_ascii_parenthesis_open_s;
  const f_string_t f_string_ascii_parenthesis_close_s = F_string_ascii_parenthesis_close_s;
  const f_string_t f_string_ascii_percent_s = F_string_ascii_percent_s;
  const f_string_t f_string_ascii_period_s = F_string_ascii_period_s;
  const f_string_t f_string_ascii_pipe_s = F_string_ascii_pipe_s;
  const f_string_t f_string_ascii_plus_s = F_string_ascii_plus_s;
  const f_string_t f_string_ascii_pound_s = F_string_ascii_pound_s;
  const f_string_t f_string_ascii_quote_double_s = F_string_ascii_quote_double_s;
  const f_string_t f_string_ascii_quote_single_s = F_string_ascii_quote_single_s;
  const f_string_t f_string_ascii_sign_at_s = F_string_ascii_sign_at_s;
  const f_string_t f_string_ascii_sign_greater_than_s = F_string_ascii_sign_greater_than_s;
  const f_string_t f_string_ascii_sign_less_than_s = F_string_ascii_sign_less_than_s;
  const f_string_t f_string_ascii_slash_forward_s = F_string_ascii_slash_forward_s;
  const f_string_t f_string_ascii_slash_backward_s = F_string_ascii_slash_backward_s;
  const f_string_t f_string_ascii_tilde_s = F_string_ascii_tilde_s;
  const f_string_t f_string_ascii_underscore_s = F_string_ascii_underscore_s;

  const f_string_t f_string_ascii_acknowledge_s = F_string_ascii_acknowledge_s;
  const f_string_t f_string_ascii_acknowledge_negative_s = F_string_ascii_acknowledge_negative_s;
  const f_string_t f_string_ascii_bell_s = F_string_ascii_bell_s;
  const f_string_t f_string_ascii_cancel_s = F_string_ascii_cancel_s;
  const f_string_t f_string_ascii_data_link_escape_s = F_string_ascii_data_link_escape_s;
  const f_string_t f_string_ascii_device_control_one_s = F_string_ascii_device_control_one_s;
  const f_string_t f_string_ascii_device_control_two_s = F_string_ascii_device_control_two_s;
  const f_string_t f_string_ascii_device_control_three_s = F_string_ascii_device_control_three_s;
  const f_string_t f_string_ascii_device_control_four_s = F_string_ascii_device_control_four_s;
  const f_string_t f_string_ascii_enquiry_s = F_string_ascii_enquiry_s;
  const f_string_t f_string_ascii_escape_s = F_string_ascii_escape_s;
  const f_string_t f_string_ascii_feed_form_s = F_string_ascii_feed_form_s;
  const f_string_t f_string_ascii_feed_line_s = F_string_ascii_feed_line_s;
  const f_string_t f_string_ascii_header_start_s = F_string_ascii_header_start_s;
  const f_string_t f_string_ascii_medium_stop_s = F_string_ascii_medium_stop_s;
  const f_string_t f_string_ascii_null_s = F_string_ascii_null_s;
  const f_string_t f_string_ascii_return_carriage_s = F_string_ascii_return_carriage_s;
  const f_string_t f_string_ascii_separator_file_s = F_string_ascii_separator_file_s;
  const f_string_t f_string_ascii_separator_group_s = F_string_ascii_separator_group_s;
  const f_string_t f_string_ascii_separator_record_s = F_string_ascii_separator_record_s;
  const f_string_t f_string_ascii_separator_unit_s = F_string_ascii_separator_unit_s;
  const f_string_t f_string_ascii_shift_in_s = F_string_ascii_shift_in_s;
  const f_string_t f_string_ascii_shift_out_s = F_string_ascii_shift_out_s;
  const f_string_t f_string_ascii_space_s = F_string_ascii_space_s;
  const f_string_t f_string_ascii_space_back_s = F_string_ascii_space_back_s;
  const f_string_t f_string_ascii_substitute_s = F_string_ascii_substitute_s;
  const f_string_t f_string_ascii_synchronous_idle_s = F_string_ascii_synchronous_idle_s;
  const f_string_t f_string_ascii_tab_horizontal_s = F_string_ascii_tab_horizontal_s;
  const f_string_t f_string_ascii_tab_vertical_s = F_string_ascii_tab_vertical_s;
  const f_string_t f_string_ascii_text_start_s = F_string_ascii_text_start_s;
  const f_string_t f_string_ascii_text_stop_s = F_string_ascii_text_stop_s;
  const f_string_t f_string_ascii_transmission_stop_s = F_string_ascii_transmission_stop_s;
  const f_string_t f_string_ascii_transmission_block_end_s = F_string_ascii_transmission_block_end_s;
#endif // _di_string_ascii_s_

#ifdef __cplusplus
} // extern "C"
#endif
