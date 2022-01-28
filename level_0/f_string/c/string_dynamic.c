#include "string.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_string_empty_s_
  const f_string_static_t f_string_empty_s = macro_f_string_static_t_initialize2(F_string_empty_s, 0, F_string_empty_s_length);
#endif // _di_f_string_empty_s_

#ifndef _di_f_string_null_s_
  const f_string_static_t f_string_null_s = macro_f_string_static_t_initialize2(F_string_null_s, 0, F_string_null_s_length);
#endif // _di_f_string_null_s_

#ifndef _di_string_ascii_s_
  const f_string_static_t f_string_ascii_0_s = macro_f_string_static_t_initialize2(F_string_ascii_0_s, 0, F_string_ascii_0_s_length);
  const f_string_static_t f_string_ascii_1_s = macro_f_string_static_t_initialize2(F_string_ascii_1_s, 0, F_string_ascii_1_s_length);
  const f_string_static_t f_string_ascii_2_s = macro_f_string_static_t_initialize2(F_string_ascii_2_s, 0, F_string_ascii_2_s_length);
  const f_string_static_t f_string_ascii_3_s = macro_f_string_static_t_initialize2(F_string_ascii_3_s, 0, F_string_ascii_3_s_length);
  const f_string_static_t f_string_ascii_4_s = macro_f_string_static_t_initialize2(F_string_ascii_4_s, 0, F_string_ascii_4_s_length);
  const f_string_static_t f_string_ascii_5_s = macro_f_string_static_t_initialize2(F_string_ascii_5_s, 0, F_string_ascii_5_s_length);
  const f_string_static_t f_string_ascii_6_s = macro_f_string_static_t_initialize2(F_string_ascii_6_s, 0, F_string_ascii_6_s_length);
  const f_string_static_t f_string_ascii_7_s = macro_f_string_static_t_initialize2(F_string_ascii_7_s, 0, F_string_ascii_7_s_length);
  const f_string_static_t f_string_ascii_8_s = macro_f_string_static_t_initialize2(F_string_ascii_8_s, 0, F_string_ascii_8_s_length);
  const f_string_static_t f_string_ascii_9_s = macro_f_string_static_t_initialize2(F_string_ascii_9_s, 0, F_string_ascii_9_s_length);

  const f_string_static_t f_string_ascii_a_s = macro_f_string_static_t_initialize2(F_string_ascii_a_s, 0, F_string_ascii_a_s_length);
  const f_string_static_t f_string_ascii_b_s = macro_f_string_static_t_initialize2(F_string_ascii_b_s, 0, F_string_ascii_b_s_length);
  const f_string_static_t f_string_ascii_c_s = macro_f_string_static_t_initialize2(F_string_ascii_c_s, 0, F_string_ascii_c_s_length);
  const f_string_static_t f_string_ascii_d_s = macro_f_string_static_t_initialize2(F_string_ascii_d_s, 0, F_string_ascii_d_s_length);
  const f_string_static_t f_string_ascii_e_s = macro_f_string_static_t_initialize2(F_string_ascii_e_s, 0, F_string_ascii_e_s_length);
  const f_string_static_t f_string_ascii_f_s = macro_f_string_static_t_initialize2(F_string_ascii_f_s, 0, F_string_ascii_f_s_length);
  const f_string_static_t f_string_ascii_g_s = macro_f_string_static_t_initialize2(F_string_ascii_g_s, 0, F_string_ascii_g_s_length);
  const f_string_static_t f_string_ascii_h_s = macro_f_string_static_t_initialize2(F_string_ascii_h_s, 0, F_string_ascii_h_s_length);
  const f_string_static_t f_string_ascii_i_s = macro_f_string_static_t_initialize2(F_string_ascii_i_s, 0, F_string_ascii_i_s_length);
  const f_string_static_t f_string_ascii_j_s = macro_f_string_static_t_initialize2(F_string_ascii_j_s, 0, F_string_ascii_j_s_length);
  const f_string_static_t f_string_ascii_k_s = macro_f_string_static_t_initialize2(F_string_ascii_k_s, 0, F_string_ascii_k_s_length);
  const f_string_static_t f_string_ascii_l_s = macro_f_string_static_t_initialize2(F_string_ascii_l_s, 0, F_string_ascii_l_s_length);
  const f_string_static_t f_string_ascii_m_s = macro_f_string_static_t_initialize2(F_string_ascii_m_s, 0, F_string_ascii_m_s_length);
  const f_string_static_t f_string_ascii_n_s = macro_f_string_static_t_initialize2(F_string_ascii_n_s, 0, F_string_ascii_n_s_length);
  const f_string_static_t f_string_ascii_o_s = macro_f_string_static_t_initialize2(F_string_ascii_o_s, 0, F_string_ascii_o_s_length);
  const f_string_static_t f_string_ascii_p_s = macro_f_string_static_t_initialize2(F_string_ascii_p_s, 0, F_string_ascii_p_s_length);
  const f_string_static_t f_string_ascii_q_s = macro_f_string_static_t_initialize2(F_string_ascii_q_s, 0, F_string_ascii_q_s_length);
  const f_string_static_t f_string_ascii_r_s = macro_f_string_static_t_initialize2(F_string_ascii_r_s, 0, F_string_ascii_r_s_length);
  const f_string_static_t f_string_ascii_s_s = macro_f_string_static_t_initialize2(F_string_ascii_s_s, 0, F_string_ascii_s_s_length);
  const f_string_static_t f_string_ascii_t_s = macro_f_string_static_t_initialize2(F_string_ascii_t_s, 0, F_string_ascii_t_s_length);
  const f_string_static_t f_string_ascii_u_s = macro_f_string_static_t_initialize2(F_string_ascii_u_s, 0, F_string_ascii_u_s_length);
  const f_string_static_t f_string_ascii_v_s = macro_f_string_static_t_initialize2(F_string_ascii_v_s, 0, F_string_ascii_v_s_length);
  const f_string_static_t f_string_ascii_w_s = macro_f_string_static_t_initialize2(F_string_ascii_w_s, 0, F_string_ascii_w_s_length);
  const f_string_static_t f_string_ascii_x_s = macro_f_string_static_t_initialize2(F_string_ascii_x_s, 0, F_string_ascii_x_s_length);
  const f_string_static_t f_string_ascii_y_s = macro_f_string_static_t_initialize2(F_string_ascii_y_s, 0, F_string_ascii_y_s_length);
  const f_string_static_t f_string_ascii_z_s = macro_f_string_static_t_initialize2(F_string_ascii_z_s, 0, F_string_ascii_z_s_length);

  const f_string_static_t f_string_ascii_A_s = macro_f_string_static_t_initialize2(F_string_ascii_A_s, 0, F_string_ascii_A_s_length);
  const f_string_static_t f_string_ascii_B_s = macro_f_string_static_t_initialize2(F_string_ascii_B_s, 0, F_string_ascii_B_s_length);
  const f_string_static_t f_string_ascii_C_s = macro_f_string_static_t_initialize2(F_string_ascii_C_s, 0, F_string_ascii_C_s_length);
  const f_string_static_t f_string_ascii_D_s = macro_f_string_static_t_initialize2(F_string_ascii_D_s, 0, F_string_ascii_D_s_length);
  const f_string_static_t f_string_ascii_E_s = macro_f_string_static_t_initialize2(F_string_ascii_E_s, 0, F_string_ascii_E_s_length);
  const f_string_static_t f_string_ascii_F_s = macro_f_string_static_t_initialize2(F_string_ascii_F_s, 0, F_string_ascii_F_s_length);
  const f_string_static_t f_string_ascii_G_s = macro_f_string_static_t_initialize2(F_string_ascii_G_s, 0, F_string_ascii_G_s_length);
  const f_string_static_t f_string_ascii_H_s = macro_f_string_static_t_initialize2(F_string_ascii_H_s, 0, F_string_ascii_H_s_length);
  const f_string_static_t f_string_ascii_I_s = macro_f_string_static_t_initialize2(F_string_ascii_I_s, 0, F_string_ascii_I_s_length);
  const f_string_static_t f_string_ascii_J_s = macro_f_string_static_t_initialize2(F_string_ascii_J_s, 0, F_string_ascii_J_s_length);
  const f_string_static_t f_string_ascii_K_s = macro_f_string_static_t_initialize2(F_string_ascii_K_s, 0, F_string_ascii_K_s_length);
  const f_string_static_t f_string_ascii_L_s = macro_f_string_static_t_initialize2(F_string_ascii_L_s, 0, F_string_ascii_L_s_length);
  const f_string_static_t f_string_ascii_M_s = macro_f_string_static_t_initialize2(F_string_ascii_M_s, 0, F_string_ascii_M_s_length);
  const f_string_static_t f_string_ascii_N_s = macro_f_string_static_t_initialize2(F_string_ascii_N_s, 0, F_string_ascii_N_s_length);
  const f_string_static_t f_string_ascii_O_s = macro_f_string_static_t_initialize2(F_string_ascii_O_s, 0, F_string_ascii_O_s_length);
  const f_string_static_t f_string_ascii_P_s = macro_f_string_static_t_initialize2(F_string_ascii_P_s, 0, F_string_ascii_P_s_length);
  const f_string_static_t f_string_ascii_Q_s = macro_f_string_static_t_initialize2(F_string_ascii_Q_s, 0, F_string_ascii_Q_s_length);
  const f_string_static_t f_string_ascii_R_s = macro_f_string_static_t_initialize2(F_string_ascii_R_s, 0, F_string_ascii_R_s_length);
  const f_string_static_t f_string_ascii_S_s = macro_f_string_static_t_initialize2(F_string_ascii_S_s, 0, F_string_ascii_S_s_length);
  const f_string_static_t f_string_ascii_T_s = macro_f_string_static_t_initialize2(F_string_ascii_T_s, 0, F_string_ascii_T_s_length);
  const f_string_static_t f_string_ascii_U_s = macro_f_string_static_t_initialize2(F_string_ascii_U_s, 0, F_string_ascii_U_s_length);
  const f_string_static_t f_string_ascii_V_s = macro_f_string_static_t_initialize2(F_string_ascii_V_s, 0, F_string_ascii_V_s_length);
  const f_string_static_t f_string_ascii_W_s = macro_f_string_static_t_initialize2(F_string_ascii_W_s, 0, F_string_ascii_W_s_length);
  const f_string_static_t f_string_ascii_X_s = macro_f_string_static_t_initialize2(F_string_ascii_X_s, 0, F_string_ascii_X_s_length);
  const f_string_static_t f_string_ascii_Y_s = macro_f_string_static_t_initialize2(F_string_ascii_Y_s, 0, F_string_ascii_Y_s_length);
  const f_string_static_t f_string_ascii_Z_s = macro_f_string_static_t_initialize2(F_string_ascii_Z_s, 0, F_string_ascii_Z_s_length);

  const f_string_static_t f_string_ascii_ampersand_s = macro_f_string_static_t_initialize2(F_string_ascii_ampersand_s, 0, F_string_ascii_ampersand_s_length);
  const f_string_static_t f_string_ascii_asterisk_s = macro_f_string_static_t_initialize2(F_string_ascii_asterisk_s, 0, F_string_ascii_asterisk_s_length);
  const f_string_static_t f_string_ascii_brace_close_s = macro_f_string_static_t_initialize2(F_string_ascii_brace_close_s, 0, F_string_ascii_brace_close_s_length);
  const f_string_static_t f_string_ascii_brace_open_s = macro_f_string_static_t_initialize2(F_string_ascii_brace_open_s, 0, F_string_ascii_brace_open_s_length);
  const f_string_static_t f_string_ascii_bracket_close_s = macro_f_string_static_t_initialize2(F_string_ascii_bracket_close_s, 0, F_string_ascii_bracket_close_s_length);
  const f_string_static_t f_string_ascii_bracket_open_s = macro_f_string_static_t_initialize2(F_string_ascii_bracket_open_s, 0, F_string_ascii_bracket_open_s_length);
  const f_string_static_t f_string_ascii_caret_s = macro_f_string_static_t_initialize2(F_string_ascii_caret_s, 0, F_string_ascii_caret_s_length);
  const f_string_static_t f_string_ascii_comma_s = macro_f_string_static_t_initialize2(F_string_ascii_comma_s, 0, F_string_ascii_comma_s_length);
  const f_string_static_t f_string_ascii_colon_s = macro_f_string_static_t_initialize2(F_string_ascii_colon_s, 0, F_string_ascii_colon_s_length);
  const f_string_static_t f_string_ascii_colon_semi_s = macro_f_string_static_t_initialize2(F_string_ascii_colon_semi_s, 0, F_string_ascii_colon_semi_s_length);
  const f_string_static_t f_string_ascii_dollar_s = macro_f_string_static_t_initialize2(F_string_ascii_dollar_s, 0, F_string_ascii_dollar_s_length);
  const f_string_static_t f_string_ascii_equal_s = macro_f_string_static_t_initialize2(F_string_ascii_equal_s, 0, F_string_ascii_equal_s_length);
  const f_string_static_t f_string_ascii_exclamation_s = macro_f_string_static_t_initialize2(F_string_ascii_exclamation_s, 0, F_string_ascii_exclamation_s_length);
  const f_string_static_t f_string_ascii_grave_s = macro_f_string_static_t_initialize2(F_string_ascii_grave_s, 0, F_string_ascii_grave_s_length);
  const f_string_static_t f_string_ascii_mark_question_s = macro_f_string_static_t_initialize2(F_string_ascii_mark_question_s, 0, F_string_ascii_mark_question_s_length);
  const f_string_static_t f_string_ascii_minus_s = macro_f_string_static_t_initialize2(F_string_ascii_minus_s, 0, F_string_ascii_minus_s_length);
  const f_string_static_t f_string_ascii_parenthesis_open_s = macro_f_string_static_t_initialize2(F_string_ascii_parenthesis_open_s, 0, F_string_ascii_parenthesis_open_s_length);
  const f_string_static_t f_string_ascii_parenthesis_close_s = macro_f_string_static_t_initialize2(F_string_ascii_parenthesis_close_s, 0, F_string_ascii_parenthesis_close_s_length);
  const f_string_static_t f_string_ascii_percent_s = macro_f_string_static_t_initialize2(F_string_ascii_percent_s, 0, F_string_ascii_percent_s_length);
  const f_string_static_t f_string_ascii_period_s = macro_f_string_static_t_initialize2(F_string_ascii_period_s, 0, F_string_ascii_period_s_length);
  const f_string_static_t f_string_ascii_pipe_s = macro_f_string_static_t_initialize2(F_string_ascii_pipe_s, 0, F_string_ascii_pipe_s_length);
  const f_string_static_t f_string_ascii_plus_s = macro_f_string_static_t_initialize2(F_string_ascii_plus_s, 0, F_string_ascii_plus_s_length);
  const f_string_static_t f_string_ascii_pound_s = macro_f_string_static_t_initialize2(F_string_ascii_pound_s, 0, F_string_ascii_pound_s_length);
  const f_string_static_t f_string_ascii_quote_double_s = macro_f_string_static_t_initialize2(F_string_ascii_quote_double_s, 0, F_string_ascii_quote_double_s_length);
  const f_string_static_t f_string_ascii_quote_single_s = macro_f_string_static_t_initialize2(F_string_ascii_quote_single_s, 0, F_string_ascii_quote_single_s_length);
  const f_string_static_t f_string_ascii_sign_at_s = macro_f_string_static_t_initialize2(F_string_ascii_sign_at_s, 0, F_string_ascii_sign_at_s_length);
  const f_string_static_t f_string_ascii_sign_greater_than_s = macro_f_string_static_t_initialize2(F_string_ascii_sign_greater_than_s, 0, F_string_ascii_sign_greater_than_s_length);
  const f_string_static_t f_string_ascii_sign_less_than_s = macro_f_string_static_t_initialize2(F_string_ascii_sign_less_than_s, 0, F_string_ascii_sign_less_than_s_length);
  const f_string_static_t f_string_ascii_slash_forward_s = macro_f_string_static_t_initialize2(F_string_ascii_slash_forward_s, 0, F_string_ascii_slash_forward_s_length);
  const f_string_static_t f_string_ascii_slash_backward_s = macro_f_string_static_t_initialize2(F_string_ascii_slash_backward_s, 0, F_string_ascii_slash_backward_s_length);
  const f_string_static_t f_string_ascii_tilde_s = macro_f_string_static_t_initialize2(F_string_ascii_tilde_s, 0, F_string_ascii_tilde_s_length);
  const f_string_static_t f_string_ascii_underscore_s = macro_f_string_static_t_initialize2(F_string_ascii_underscore_s, 0, F_string_ascii_underscore_s_length);

  const f_string_static_t f_string_ascii_acknowledge_s = macro_f_string_static_t_initialize2(F_string_ascii_acknowledge_s, 0, F_string_ascii_acknowledge_s_length);
  const f_string_static_t f_string_ascii_acknowledge_negative_s = macro_f_string_static_t_initialize2(F_string_ascii_acknowledge_negative_s, 0, F_string_ascii_acknowledge_negative_s_length);
  const f_string_static_t f_string_ascii_bell_s = macro_f_string_static_t_initialize2(F_string_ascii_bell_s, 0, F_string_ascii_bell_s_length);
  const f_string_static_t f_string_ascii_cancel_s = macro_f_string_static_t_initialize2(F_string_ascii_cancel_s, 0, F_string_ascii_cancel_s_length);
  const f_string_static_t f_string_ascii_data_link_escape_s = macro_f_string_static_t_initialize2(F_string_ascii_data_link_escape_s, 0, F_string_ascii_data_link_escape_s_length);
  const f_string_static_t f_string_ascii_device_control_one_s = macro_f_string_static_t_initialize2(F_string_ascii_device_control_one_s, 0, F_string_ascii_device_control_one_s_length);
  const f_string_static_t f_string_ascii_device_control_two_s = macro_f_string_static_t_initialize2(F_string_ascii_device_control_two_s, 0, F_string_ascii_device_control_two_s_length);
  const f_string_static_t f_string_ascii_device_control_three_s = macro_f_string_static_t_initialize2(F_string_ascii_device_control_three_s, 0, F_string_ascii_device_control_three_s_length);
  const f_string_static_t f_string_ascii_device_control_four_s = macro_f_string_static_t_initialize2(F_string_ascii_device_control_four_s, 0, F_string_ascii_device_control_four_s_length);
  const f_string_static_t f_string_ascii_enquiry_s = macro_f_string_static_t_initialize2(F_string_ascii_enquiry_s, 0, F_string_ascii_enquiry_s_length);
  const f_string_static_t f_string_ascii_escape_s = macro_f_string_static_t_initialize2(F_string_ascii_escape_s, 0, F_string_ascii_escape_s_length);
  const f_string_static_t f_string_ascii_feed_form_s = macro_f_string_static_t_initialize2(F_string_ascii_feed_form_s, 0, F_string_ascii_feed_form_s_length);
  const f_string_static_t f_string_ascii_feed_line_s = macro_f_string_static_t_initialize2(F_string_ascii_feed_line_s, 0, F_string_ascii_feed_line_s_length);
  const f_string_static_t f_string_ascii_header_start_s = macro_f_string_static_t_initialize2(F_string_ascii_header_start_s, 0, F_string_ascii_header_start_s_length);
  const f_string_static_t f_string_ascii_medium_stop_s = macro_f_string_static_t_initialize2(F_string_ascii_medium_stop_s, 0, F_string_ascii_medium_stop_s_length);
  const f_string_static_t f_string_ascii_null_s = macro_f_string_static_t_initialize2(F_string_ascii_null_s, 0, F_string_ascii_null_s_length);
  const f_string_static_t f_string_ascii_return_carriage_s = macro_f_string_static_t_initialize2(F_string_ascii_return_carriage_s, 0, F_string_ascii_return_carriage_s_length);
  const f_string_static_t f_string_ascii_separator_file_s = macro_f_string_static_t_initialize2(F_string_ascii_separator_file_s, 0, F_string_ascii_separator_file_s_length);
  const f_string_static_t f_string_ascii_separator_group_s = macro_f_string_static_t_initialize2(F_string_ascii_separator_group_s, 0, F_string_ascii_separator_group_s_length);
  const f_string_static_t f_string_ascii_separator_record_s = macro_f_string_static_t_initialize2(F_string_ascii_separator_record_s, 0, F_string_ascii_separator_record_s_length);
  const f_string_static_t f_string_ascii_separator_unit_s = macro_f_string_static_t_initialize2(F_string_ascii_separator_unit_s, 0, F_string_ascii_separator_unit_s_length);
  const f_string_static_t f_string_ascii_shift_in_s = macro_f_string_static_t_initialize2(F_string_ascii_shift_in_s, 0, F_string_ascii_shift_in_s_length);
  const f_string_static_t f_string_ascii_shift_out_s = macro_f_string_static_t_initialize2(F_string_ascii_shift_out_s, 0, F_string_ascii_shift_out_s_length);
  const f_string_static_t f_string_ascii_space_s = macro_f_string_static_t_initialize2(F_string_ascii_space_s, 0, F_string_ascii_space_s_length);
  const f_string_static_t f_string_ascii_space_back_s = macro_f_string_static_t_initialize2(F_string_ascii_space_back_s, 0, F_string_ascii_space_back_s_length);
  const f_string_static_t f_string_ascii_substitute_s = macro_f_string_static_t_initialize2(F_string_ascii_substitute_s, 0, F_string_ascii_substitute_s_length);
  const f_string_static_t f_string_ascii_synchronous_idle_s = macro_f_string_static_t_initialize2(F_string_ascii_synchronous_idle_s, 0, F_string_ascii_synchronous_idle_s_length);
  const f_string_static_t f_string_ascii_tab_horizontal_s = macro_f_string_static_t_initialize2(F_string_ascii_tab_horizontal_s, 0, F_string_ascii_tab_horizontal_s_length);
  const f_string_static_t f_string_ascii_tab_vertical_s = macro_f_string_static_t_initialize2(F_string_ascii_tab_vertical_s, 0, F_string_ascii_tab_vertical_s_length);
  const f_string_static_t f_string_ascii_text_start_s = macro_f_string_static_t_initialize2(F_string_ascii_text_start_s, 0, F_string_ascii_text_start_s_length);
  const f_string_static_t f_string_ascii_text_stop_s = macro_f_string_static_t_initialize2(F_string_ascii_text_stop_s, 0, F_string_ascii_text_stop_s_length);
  const f_string_static_t f_string_ascii_transmission_stop_s = macro_f_string_static_t_initialize2(F_string_ascii_transmission_stop_s, 0, F_string_ascii_transmission_stop_s_length);
  const f_string_static_t f_string_ascii_transmission_block_end_s = macro_f_string_static_t_initialize2(F_string_ascii_transmission_block_end_s, 0, F_string_ascii_transmission_block_end_s_length);
#endif // _di_string_ascii_s_

#ifndef _di_f_string_dynamic_adjust_
  f_status_t f_string_dynamic_adjust(const f_array_length_t length, f_string_dynamic_t *dynamic) {
    #ifndef _di_level_0_parameter_checking_
      if (!dynamic) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_dynamic_adjust(length, dynamic);
  }
#endif // _di_f_string_dynamic_adjust_

#ifndef _di_f_string_dynamic_append_
  f_status_t f_string_dynamic_append(const f_string_static_t source, f_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    return private_f_string_append(source.string, source.used, destination);
  }
#endif // _di_f_string_dynamic_append_

#ifndef _di_f_string_dynamic_append_assure_
  f_status_t f_string_dynamic_append_assure(const f_string_static_t source, f_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (destination->used < source.used) {
      return private_f_string_append(source.string, source.used, destination);
    }

    f_array_length_t i = 1;
    f_array_length_t j = 1;

    while (i <= source.used && j <= destination->used) {

      if (!source.string[source.used - i]) {
        ++i;

        continue;
      }

      if (!destination->string[destination->used - j]) {
        ++j;

        continue;
      }

      if (source.string[source.used - i] != destination->string[destination->used - j]) {
        return private_f_string_append(source.string, source.used, destination);
      }

      ++i;
      ++j;
    } // while

    return F_none;
  }
#endif // _di_f_string_dynamic_append_assure_

#ifndef _di_f_string_dynamic_append_assure_nulless_
  f_status_t f_string_dynamic_append_assure_nulless(const f_string_static_t source, f_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (destination->used < source.used) {
      return private_f_string_append_nulless(source.string, source.used, destination);
    }

    f_array_length_t i = 1;
    f_array_length_t j = 1;

    while (i <= source.used && j <= destination->used) {

      if (!source.string[source.used - i]) {
        ++i;

        continue;
      }

      if (!destination->string[destination->used - j]) {
        ++j;

        continue;
      }

      if (source.string[source.used - i] != destination->string[destination->used - j]) {
        return private_f_string_append_nulless(source.string, source.used, destination);
      }

      ++i;
      ++j;
    } // while

    return F_none;
  }
#endif // _di_f_string_dynamic_append_assure_nulless_

#ifndef _di_f_string_dynamic_append_nulless_
  f_status_t f_string_dynamic_append_nulless(const f_string_static_t source, f_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    return private_f_string_append_nulless(source.string, source.used, destination);
  }
#endif // _di_f_string_dynamic_append_nulless_

#ifndef _di_f_string_dynamic_decimate_by_
  f_status_t f_string_dynamic_decimate_by(const f_array_length_t amount, f_string_dynamic_t *dynamic) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!dynamic) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (dynamic->size - amount > 0) {
      return private_f_string_dynamic_adjust(dynamic->size - amount, dynamic);
    }

    return private_f_string_dynamic_adjust(0, dynamic);
  }
#endif // _di_f_string_dynamic_decimate_by_

#ifndef _di_f_string_dynamic_decrease_by_
  f_status_t f_string_dynamic_decrease_by(const f_array_length_t amount, f_string_dynamic_t *dynamic) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!dynamic) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (dynamic->size - amount > 0) {
      return private_f_string_dynamic_resize(dynamic->size - amount, dynamic);
    }

    return private_f_string_dynamic_resize(0, dynamic);
  }
#endif // _di_f_string_dynamic_decrease_by_

#ifndef _di_f_string_dynamic_increase_
  f_status_t f_string_dynamic_increase(const uint16_t step, f_string_dynamic_t *dynamic) {
    #ifndef _di_level_0_parameter_checking_
      if (!step) return F_status_set_error(F_parameter);
      if (!dynamic) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (dynamic->used + 1 > dynamic->size) {
      f_array_length_t size = dynamic->used + step;

      if (size > F_string_t_size_d) {
        if (dynamic->used + 1 > F_string_t_size_d) {
          return F_status_set_error(F_string_too_large);
        }

        size = F_string_t_size_d;
      }

      return private_f_string_dynamic_resize(size, dynamic);
    }

    return F_data_not;
  }
#endif // _di_f_string_dynamic_increase_

#ifndef _di_f_string_dynamic_increase_by_
  f_status_t f_string_dynamic_increase_by(const f_array_length_t amount, f_string_dynamic_t *dynamic) {
    #ifndef _di_level_0_parameter_checking_
      if (!dynamic) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_dynamic_increase_by(amount, dynamic);
  }
#endif // _di_f_string_dynamic_increase_by_

#ifndef _di_f_string_dynamic_mash_
  f_status_t f_string_dynamic_mash(const f_string_static_t glue, const f_string_static_t source, f_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (glue.used && destination->used) {
      const f_status_t status = private_f_string_append(glue.string, glue.used, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_string_append(source.string, source.used, destination);
  }
#endif // _di_f_string_dynamic_mash_

#ifndef _di_f_string_dynamic_mash_nulless_
  f_status_t f_string_dynamic_mash_nulless(const f_string_static_t glue, const f_string_static_t source, f_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (glue.used && destination->used) {
      const f_status_t status = private_f_string_append_nulless(glue.string, glue.used, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_string_append_nulless(source.string, source.used, destination);
  }
#endif // _di_f_string_dynamic_mash_nulless_

#ifndef _di_f_string_dynamic_mish_
  f_status_t f_string_dynamic_mish(const f_string_static_t glue, const f_string_static_t source, f_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (glue.used && destination->used) {
      const f_status_t status = private_f_string_prepend(glue.string, glue.used, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_string_prepend(source.string, source.used, destination);
  }
#endif // _di_f_string_dynamic_mish_

#ifndef _di_f_string_dynamic_mish_nulless_
  f_status_t f_string_dynamic_mish_nulless(const f_string_static_t glue, const f_string_static_t source, f_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (glue.used && destination->used) {
      const f_status_t status = private_f_string_prepend_nulless(glue.string, glue.used, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_string_prepend_nulless(source.string, source.used, destination);
  }
#endif // _di_f_string_dynamic_mish_nulless_

#ifndef _di_f_string_dynamic_partial_append_
  f_status_t f_string_dynamic_partial_append(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (range.start > range.stop) {
      return F_data_not_stop;
    }

    return private_f_string_append(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_string_dynamic_partial_append_

#ifndef _di_f_string_dynamic_partial_append_assure_
  f_status_t f_string_dynamic_partial_append_assure(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (range.start > range.stop) {
      return F_data_not_stop;
    }

    const f_array_length_t length = (range.stop - range.start) + 1;

    if (destination->used < length) {
      return private_f_string_append(source.string + range.start, length, destination);
    }

    f_array_length_t i = 1;
    f_array_length_t j = 1;

    while (i <= length && j <= destination->used) {

      if (!source.string[range.stop - i]) {
        ++i;

        continue;
      }

      if (!destination->string[destination->used - j]) {
        ++j;

        continue;
      }

      if (source.string[range.stop - i] != destination->string[destination->used - j]) {
        return private_f_string_append(source.string + range.start, length, destination);
      }

      ++i;
      ++j;
    } // while

    return F_none;
  }
#endif // _di_f_string_dynamic_partial_append_assure_

#ifndef _di_f_string_dynamic_partial_append_assure_nulless_
  f_status_t f_string_dynamic_partial_append_assure_nulless(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (range.start > range.stop) {
      return F_data_not_stop;
    }

    const f_array_length_t length = (range.stop - range.start) + 1;

    if (destination->used < length) {
      return private_f_string_append_nulless(source.string + range.start, length, destination);
    }

    f_array_length_t i = 1;
    f_array_length_t j = 1;

    while (i <= length && j <= destination->used) {

      if (!source.string[range.stop - i]) {
        ++i;

        continue;
      }

      if (!destination->string[destination->used - j]) {
        ++j;

        continue;
      }

      if (source.string[range.stop - i] != destination->string[destination->used - j]) {
        return private_f_string_append_nulless(source.string + range.start, length, destination);
      }

      ++i;
      ++j;
    } // while

    return F_none;
  }
#endif // _di_f_string_dynamic_append_assure_nulless_

#ifndef _di_f_string_dynamic_partial_append_nulless_
  f_status_t f_string_dynamic_partial_append_nulless(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (range.start > range.stop) {
      return F_data_not_stop;
    }

    return private_f_string_append_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_string_dynamic_partial_append_nulless_

#ifndef _di_f_string_dynamic_partial_mash_
  f_status_t f_string_dynamic_partial_mash(const f_string_static_t glue, const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (range.start > range.stop) {
      return F_data_not_stop;
    }

    if (glue.used && destination->used) {
      f_status_t status = private_f_string_append(glue.string, glue.used, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_string_append(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_string_dynamic_partial_mash_

#ifndef _di_f_string_dynamic_partial_mash_nulless_
  f_status_t f_string_dynamic_partial_mash_nulless(const f_string_static_t glue, const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (range.start > range.stop) {
      return F_data_not_stop;
    }

    if (glue.used && destination->used) {
      f_status_t status = private_f_string_append_nulless(glue.string, glue.used, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_string_append_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_string_dynamic_partial_mash_nulless_

#ifndef _di_f_string_dynamic_partial_mish_
  f_status_t f_string_partial_dynamic_mish(const f_string_static_t glue, const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (range.start > range.stop) {
      return F_data_not_stop;
    }

    if (glue.used && destination->used) {
      f_status_t status = private_f_string_prepend(glue.string, glue.used, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_string_prepend(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_string_dynamic_partial_mish_

#ifndef _di_f_string_dynamic_partial_mish_nulless_
  f_status_t f_string_dynamic_partial_mish_nulless(const f_string_static_t glue, const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (range.start > range.stop) {
      return F_data_not_stop;
    }

    if (glue.used && destination->used) {
      f_status_t status = private_f_string_prepend_nulless(glue.string, glue.used, destination);
      if (F_status_is_error(status)) return status;
    }

    return private_f_string_prepend_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_string_dynamic_partial_mish_nulless_

#ifndef _di_f_string_dynamic_partial_prepend_
  f_status_t f_string_dynamic_partial_prepend(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (range.start > range.stop) {
      return F_data_not_stop;
    }

    return private_f_string_prepend(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_string_dynamic_partial_prepend_

#ifndef _di_f_string_dynamic_partial_prepend_assure_
  f_status_t f_string_dynamic_partial_prepend_assure(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (range.start > range.stop) {
      return F_data_not_stop;
    }

    const f_array_length_t length = (range.stop - range.start) + 1;

    if (destination->used < length) {
      return private_f_string_prepend(source.string + range.start, length, destination);
    }

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    while (i < length && j < destination->used) {

      if (!source.string[i + range.start]) {
        ++i;

        continue;
      }

      if (!destination->string[j]) {
        ++j;

        continue;
      }

      if (source.string[i + range.start] != destination->string[i]) {
        return private_f_string_prepend(source.string + range.start, length, destination);
      }

      ++i;
      ++j;
    } // while

    return F_none;
  }
#endif // _di_f_string_dynamic_partial_prepend_assure_

#ifndef _di_f_string_dynamic_partial_prepend_assure_nulless_
  f_status_t f_string_dynamic_partial_prepend_assure_nulless(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (range.start > range.stop) {
      return F_data_not_stop;
    }

    const f_array_length_t length = (range.stop - range.start) + 1;

    if (destination->used < length) {
      return private_f_string_prepend_nulless(source.string + range.start, length, destination);
    }

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    while (i < length && j < destination->used) {

      if (!source.string[i + range.start]) {
        ++i;

        continue;
      }

      if (!destination->string[j]) {
        ++j;

        continue;
      }

      if (source.string[i + range.start] != destination->string[i]) {
        return private_f_string_prepend_nulless(source.string + range.start, length, destination);
      }

      ++i;
      ++j;
    } // while

    return F_none;
  }
#endif // _di_f_string_dynamic_partial_prepend_assure_nulless

#ifndef _di_f_string_dynamic_partial_prepend_nulless_
  f_status_t f_string_dynamic_partial_prepend_nulless(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used <= range.stop) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (range.start > range.stop) {
      return F_data_not_stop;
    }

    return private_f_string_prepend_nulless(source.string + range.start, (range.stop - range.start) + 1, destination);
  }
#endif // _di_f_string_dynamic_partial_prepend_nulless

#ifndef _di_f_string_dynamic_prepend_
  f_status_t f_string_dynamic_prepend(const f_string_static_t source, f_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    return private_f_string_prepend(source.string, source.used, destination);
  }
#endif // _di_f_string_dynamic_prepend_

#ifndef _di_f_string_dynamic_prepend_assure_
  f_status_t f_string_dynamic_prepend_assure(const f_string_static_t source, f_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (destination->used < source.used) {
      return private_f_string_prepend(source.string, source.used, destination);
    }

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    while (i < source.used && j < destination->used) {

      if (!source.string[i]) {
        ++i;

        continue;
      }

      if (!destination->string[j]) {
        ++j;

        continue;
      }

      if (source.string[i] != destination->string[i]) {
        return private_f_string_prepend(source.string, source.used, destination);
      }

      ++i;
      ++j;
    } // while

    return F_none;
  }
#endif // _di_f_string_dynamic_prepend_assure_

#ifndef _di_f_string_dynamic_prepend_assure_nulless_
  f_status_t f_string_dynamic_prepend_assure_nulless(const f_string_static_t source, f_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not_eos;
    }

    if (destination->used < source.used) {
      return private_f_string_prepend_nulless(source.string, source.used, destination);
    }

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    while (i < source.used && j < destination->used) {

      if (!source.string[i]) {
        ++i;

        continue;
      }

      if (!destination->string[j]) {
        ++j;

        continue;
      }

      if (source.string[i] != destination->string[i]) {
        return private_f_string_prepend_nulless(source.string, source.used, destination);
      }

      ++i;
      ++j;
    } // while

    return F_none;
  }
#endif // _di_f_string_dynamic_prepend_assure_nulless_

#ifndef _di_f_string_dynamic_prepend_nulless_
  f_status_t f_string_dynamic_prepend_nulless(const f_string_static_t source, f_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not_eos;

    return private_f_string_prepend_nulless(source.string, source.used, destination);
  }
#endif // _di_f_string_dynamic_prepend_nulless_

#ifndef _di_f_string_dynamic_resize_
  f_status_t f_string_dynamic_resize(const f_array_length_t length, f_string_dynamic_t *buffer) {
    #ifndef _di_level_0_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_dynamic_resize(length, buffer);
  }
#endif // _di_f_string_dynamic_resize_

#ifndef _di_f_string_dynamic_seek_line_
  f_status_t f_string_dynamic_seek_line(const f_string_static_t buffer, f_string_range_t *range) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used) return F_data_not_eos;
    if (range->start > range->stop) return F_data_not_stop;

    while (buffer.string[range->start] != f_string_eol_s.string[0]) {

      ++range->start;

      if (range->start >= buffer.used) return F_none_eos;
      if (range->start > range->stop) return F_none_stop;
    } // while

    return F_none;
  }
#endif // _di_f_string_dynamic_seek_line_

#ifndef _di_f_string_dynamic_seek_line_to_
  f_status_t f_string_dynamic_seek_line_to(const f_string_static_t buffer, const char seek_to_this, f_string_range_t *range) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used) return F_data_not_eos;
    if (range->start > range->stop) return F_data_not_stop;

    while (buffer.string[range->start] != seek_to_this) {

      if (buffer.string[range->start] == f_string_eol_s.string[0]) return F_none_eol;

      ++range->start;

      if (range->start >= buffer.used) return F_none_eos;
      if (range->start > range->stop) return F_none_stop;
    } // while

    return F_none;
  }
#endif // _di_f_string_dynamic_seek_line_to_

#ifndef _di_f_string_dynamic_seek_to_
  f_status_t f_string_dynamic_seek_to(const f_string_static_t buffer, const char seek_to_this, f_string_range_t *range) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used) return F_data_not_eos;
    if (range->start > range->stop) return F_data_not_stop;

    while (buffer.string[range->start] != seek_to_this) {

      ++range->start;

      if (range->start >= buffer.used) return F_none_eos;
      if (range->start > range->stop) return F_none_stop;
    } // while

    return F_none;
  }
#endif // _di_f_string_dynamic_seek_to_

#ifndef _di_f_string_dynamic_terminate_
  f_status_t f_string_dynamic_terminate(f_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
      if (destination->used > destination->size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!destination->used && destination->size && !destination->string[destination->used - 1]) {
      return F_none;
    }

    if (destination->used == F_string_t_size_d) {
      return F_status_set_error(F_string_too_large);
    }

    const f_array_length_t total = destination->used + 1;

    if (total > destination->size) {
      const f_status_t status = private_f_string_dynamic_resize(total, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->string[destination->used] = 0;
    destination->used = total;

    return F_none;
  }
#endif // _di_f_string_dynamic_terminate_

#ifndef _di_f_string_dynamic_terminate_after_
  f_status_t f_string_dynamic_terminate_after(f_string_dynamic_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
      if (destination->used > destination->size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (destination->used) {
      for (; destination->used; --destination->used) {

        if (!destination->string[destination->used - 1]) continue;

        break;
      } // for
    }

    if (destination->used == F_string_t_size_d) {
      return F_status_set_error(F_string_too_large);
    }

    if (destination->used + 1 > destination->size) {
      const f_status_t status = private_f_string_dynamic_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->string[destination->used] = 0;

    return F_none;
  }
#endif // _di_f_string_dynamic_terminate_after_

#ifndef _di_f_string_dynamics_adjust_
  f_status_t f_string_dynamics_adjust(const f_array_length_t length, f_string_dynamics_t *dynamics) {
    #ifndef _di_level_0_parameter_checking_
      if (!dynamics) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_dynamics_adjust(length, dynamics);
  }
#endif // _di_f_string_dynamics_adjust_

#ifndef _di_f_string_dynamics_append_
  f_status_t f_string_dynamics_append(const f_string_dynamics_t source, f_string_dynamics_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not;
    }

    return private_f_string_dynamics_append(source, destination);
  }
#endif // _di_f_string_dynamics_append_

#ifndef _di_f_string_dynamics_decimate_by_
  f_status_t f_string_dynamics_decimate_by(const f_array_length_t amount, f_string_dynamics_t *dynamics) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!dynamics) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (dynamics->size - amount > 0) {
      return private_f_string_dynamics_adjust(dynamics->size - amount, dynamics);
    }

    return private_f_string_dynamics_adjust(0, dynamics);
  }
#endif // _di_f_string_dynamics_decimate_by_

#ifndef _di_f_string_dynamics_decrease_by_
  f_status_t f_string_dynamics_decrease_by(const f_array_length_t amount, f_string_dynamics_t *dynamics) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!dynamics) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (dynamics->size - amount > 0) {
      return private_f_string_dynamics_resize(dynamics->size - amount, dynamics);
    }

    return private_f_string_dynamics_resize(0, dynamics);
  }
#endif // _di_f_string_dynamics_decrease_by_

#ifndef _di_f_string_dynamics_increase_
  f_status_t f_string_dynamics_increase(const uint16_t step, f_string_dynamics_t *dynamics) {
    #ifndef _di_level_0_parameter_checking_
      if (!step) return F_status_set_error(F_parameter);
      if (!dynamics) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (dynamics->used + 1 > dynamics->size) {
      f_array_length_t size = dynamics->used + step;

      if (size > F_array_length_t_size_d) {
        if (dynamics->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_string_dynamics_resize(size, dynamics);
    }

    return F_data_not;
  }
#endif // _di_f_string_dynamics_increase_

#ifndef _di_f_string_dynamics_increase_by_
  f_status_t f_string_dynamics_increase_by(const f_array_length_t amount, f_string_dynamics_t *dynamics) {
    #ifndef _di_level_0_parameter_checking_
      if (!dynamics) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (dynamics->used + amount > dynamics->size) {
      if (dynamics->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_string_dynamics_resize(dynamics->used + amount, dynamics);
    }

    return F_data_not;
  }
#endif // _di_f_string_dynamics_increase_by_

#ifndef _di_f_string_dynamics_resize_
  f_status_t f_string_dynamics_resize(const f_array_length_t length, f_string_dynamics_t *dynamics) {
    #ifndef _di_level_0_parameter_checking_
      if (!dynamics) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_dynamics_resize(length, dynamics);
  }
#endif // _di_f_string_dynamics_resize_

#ifdef __cplusplus
} // extern "C"
#endif
