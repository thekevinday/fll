#include "string.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_string_empty_s_
  const f_string_t f_string_empty_s = "";
#endif // _di_f_string_empty_s_

#ifndef _di_string_format_s_
  const f_string_t f_string_format_string_s = f_string_format_string;
  const f_string_t f_string_format_character_s = f_string_format_character;
  const f_string_t f_string_format_wide_string_s = f_string_format_wide_string;
  const f_string_t f_string_format_wide_character_s = f_string_format_wide_character;
  const f_string_t f_string_format_integer_s = f_string_format_integer;
  const f_string_t f_string_format_unsigned_s = f_string_format_unsigned;
  const f_string_t f_string_format_digit_s = f_string_format_digit;
  const f_string_t f_string_format_float_s = f_string_format_float;
  const f_string_t f_string_format_short_integer_s = f_string_format_short_integer;
  const f_string_t f_string_format_short_unsigned_s = f_string_format_short_unsigned;
  const f_string_t f_string_format_long_integer_s = f_string_format_long_integer;
  const f_string_t f_string_format_long_unsigned_s = f_string_format_long_unsigned;
  const f_string_t f_string_format_long_double_s = f_string_format_long_double;
  const f_string_t f_string_format_long_long_integer_s = f_string_format_long_long_integer;
  const f_string_t f_string_format_long_long_unsigned_s = f_string_format_long_long_unsigned;
#endif // _di_string_format_s_

#ifndef _di_string_ascii_s_
  const f_string_t f_string_ascii_0_s = f_string_ascii_0;
  const f_string_t f_string_ascii_1_s = f_string_ascii_1;
  const f_string_t f_string_ascii_2_s = f_string_ascii_2;
  const f_string_t f_string_ascii_3_s = f_string_ascii_3;
  const f_string_t f_string_ascii_4_s = f_string_ascii_4;
  const f_string_t f_string_ascii_5_s = f_string_ascii_5;
  const f_string_t f_string_ascii_6_s = f_string_ascii_6;
  const f_string_t f_string_ascii_7_s = f_string_ascii_7;
  const f_string_t f_string_ascii_8_s = f_string_ascii_8;
  const f_string_t f_string_ascii_9_s = f_string_ascii_9;

  const f_string_t f_string_ascii_a_s = f_string_ascii_a;
  const f_string_t f_string_ascii_b_s = f_string_ascii_b;
  const f_string_t f_string_ascii_c_s = f_string_ascii_c;
  const f_string_t f_string_ascii_d_s = f_string_ascii_d;
  const f_string_t f_string_ascii_e_s = f_string_ascii_e;
  const f_string_t f_string_ascii_f_s = f_string_ascii_f;
  const f_string_t f_string_ascii_g_s = f_string_ascii_g;
  const f_string_t f_string_ascii_h_s = f_string_ascii_h;
  const f_string_t f_string_ascii_i_s = f_string_ascii_i;
  const f_string_t f_string_ascii_j_s = f_string_ascii_j;
  const f_string_t f_string_ascii_k_s = f_string_ascii_k;
  const f_string_t f_string_ascii_l_s = f_string_ascii_l;
  const f_string_t f_string_ascii_m_s = f_string_ascii_m;
  const f_string_t f_string_ascii_n_s = f_string_ascii_n;
  const f_string_t f_string_ascii_o_s = f_string_ascii_o;
  const f_string_t f_string_ascii_p_s = f_string_ascii_p;
  const f_string_t f_string_ascii_q_s = f_string_ascii_q;
  const f_string_t f_string_ascii_r_s = f_string_ascii_r;
  const f_string_t f_string_ascii_s_s = f_string_ascii_s;
  const f_string_t f_string_ascii_t_s = f_string_ascii_t;
  const f_string_t f_string_ascii_u_s = f_string_ascii_u;
  const f_string_t f_string_ascii_v_s = f_string_ascii_v;
  const f_string_t f_string_ascii_w_s = f_string_ascii_w;
  const f_string_t f_string_ascii_x_s = f_string_ascii_x;
  const f_string_t f_string_ascii_y_s = f_string_ascii_y;
  const f_string_t f_string_ascii_z_s = f_string_ascii_z;

  const f_string_t f_string_ascii_A_s = f_string_ascii_A;
  const f_string_t f_string_ascii_B_s = f_string_ascii_B;
  const f_string_t f_string_ascii_C_s = f_string_ascii_C;
  const f_string_t f_string_ascii_D_s = f_string_ascii_D;
  const f_string_t f_string_ascii_E_s = f_string_ascii_E;
  const f_string_t f_string_ascii_F_s = f_string_ascii_F;
  const f_string_t f_string_ascii_G_s = f_string_ascii_G;
  const f_string_t f_string_ascii_H_s = f_string_ascii_H;
  const f_string_t f_string_ascii_I_s = f_string_ascii_I;
  const f_string_t f_string_ascii_J_s = f_string_ascii_J;
  const f_string_t f_string_ascii_K_s = f_string_ascii_K;
  const f_string_t f_string_ascii_L_s = f_string_ascii_L;
  const f_string_t f_string_ascii_M_s = f_string_ascii_M;
  const f_string_t f_string_ascii_N_s = f_string_ascii_N;
  const f_string_t f_string_ascii_O_s = f_string_ascii_O;
  const f_string_t f_string_ascii_P_s = f_string_ascii_P;
  const f_string_t f_string_ascii_Q_s = f_string_ascii_Q;
  const f_string_t f_string_ascii_R_s = f_string_ascii_R;
  const f_string_t f_string_ascii_S_s = f_string_ascii_S;
  const f_string_t f_string_ascii_T_s = f_string_ascii_T;
  const f_string_t f_string_ascii_U_s = f_string_ascii_U;
  const f_string_t f_string_ascii_V_s = f_string_ascii_V;
  const f_string_t f_string_ascii_W_s = f_string_ascii_W;
  const f_string_t f_string_ascii_X_s = f_string_ascii_X;
  const f_string_t f_string_ascii_Y_s = f_string_ascii_Y;
  const f_string_t f_string_ascii_Z_s = f_string_ascii_Z;

  const f_string_t f_string_ascii_ampersand_s = f_string_ascii_ampersand;
  const f_string_t f_string_ascii_asterisk_s = f_string_ascii_asterisk;
  const f_string_t f_string_ascii_brace_close_s = f_string_ascii_brace_close;
  const f_string_t f_string_ascii_brace_open_s = f_string_ascii_brace_open;
  const f_string_t f_string_ascii_bracket_close_s = f_string_ascii_bracket_close;
  const f_string_t f_string_ascii_bracket_open_s = f_string_ascii_bracket_open;
  const f_string_t f_string_ascii_caret_s = f_string_ascii_caret;
  const f_string_t f_string_ascii_comma_s = f_string_ascii_comma;
  const f_string_t f_string_ascii_colon_s = f_string_ascii_colon;
  const f_string_t f_string_ascii_colon_semi_s = f_string_ascii_colon_semi;
  const f_string_t f_string_ascii_dollar_s = f_string_ascii_dollar;
  const f_string_t f_string_ascii_equal_s = f_string_ascii_equal;
  const f_string_t f_string_ascii_exclamation_s = f_string_ascii_exclamation;
  const f_string_t f_string_ascii_grave_s = f_string_ascii_grave;
  const f_string_t f_string_ascii_mark_question_s = f_string_ascii_mark_question;
  const f_string_t f_string_ascii_minus_s = f_string_ascii_minus;
  const f_string_t f_string_ascii_parenthesis_open_s = f_string_ascii_parenthesis_open;
  const f_string_t f_string_ascii_parenthesis_close_s = f_string_ascii_parenthesis_close;
  const f_string_t f_string_ascii_percent_s = f_string_ascii_percent;
  const f_string_t f_string_ascii_period_s = f_string_ascii_period;
  const f_string_t f_string_ascii_pipe_s = f_string_ascii_pipe;
  const f_string_t f_string_ascii_plus_s = f_string_ascii_plus;
  const f_string_t f_string_ascii_pound_s = f_string_ascii_pound;
  const f_string_t f_string_ascii_quote_double_s = f_string_ascii_quote_double;
  const f_string_t f_string_ascii_quote_single_s = f_string_ascii_quote_single;
  const f_string_t f_string_ascii_sign_at_s = f_string_ascii_sign_at;
  const f_string_t f_string_ascii_sign_greater_than_s = f_string_ascii_sign_greater_than;
  const f_string_t f_string_ascii_sign_less_than_s = f_string_ascii_sign_less_than;
  const f_string_t f_string_ascii_slash_forward_s = f_string_ascii_slash_forward;
  const f_string_t f_string_ascii_slash_backward_s = f_string_ascii_slash_backward;
  const f_string_t f_string_ascii_tilde_s = f_string_ascii_tilde;
  const f_string_t f_string_ascii_underscore_s = f_string_ascii_underscore;

  const f_string_t f_string_ascii_acknowledge_s = f_string_ascii_acknowledge;
  const f_string_t f_string_ascii_acknowledge_negative_s = f_string_ascii_acknowledge_negative;
  const f_string_t f_string_ascii_bell_s = f_string_ascii_bell;
  const f_string_t f_string_ascii_cancel_s = f_string_ascii_cancel;
  const f_string_t f_string_ascii_data_link_escape_s = f_string_ascii_data_link_escape;
  const f_string_t f_string_ascii_device_control_one_s = f_string_ascii_device_control_one;
  const f_string_t f_string_ascii_device_control_two_s = f_string_ascii_device_control_two;
  const f_string_t f_string_ascii_device_control_three_s = f_string_ascii_device_control_three;
  const f_string_t f_string_ascii_device_control_four_s = f_string_ascii_device_control_four;
  const f_string_t f_string_ascii_enquiry_s = f_string_ascii_enquiry;
  const f_string_t f_string_ascii_escape_s = f_string_ascii_escape;
  const f_string_t f_string_ascii_feed_form_s = f_string_ascii_feed_form;
  const f_string_t f_string_ascii_feed_line_s = f_string_ascii_feed_line;
  const f_string_t f_string_ascii_header_start_s = f_string_ascii_header_start;
  const f_string_t f_string_ascii_medium_stop_s = f_string_ascii_medium_stop;
  const f_string_t f_string_ascii_null_s = f_string_ascii_null;
  const f_string_t f_string_ascii_return_carriage_s = f_string_ascii_return_carriage;
  const f_string_t f_string_ascii_separator_file_s = f_string_ascii_separator_file;
  const f_string_t f_string_ascii_separator_group_s = f_string_ascii_separator_group;
  const f_string_t f_string_ascii_separator_record_s = f_string_ascii_separator_record;
  const f_string_t f_string_ascii_separator_unit_s = f_string_ascii_separator_unit;
  const f_string_t f_string_ascii_shift_in_s = f_string_ascii_shift_in;
  const f_string_t f_string_ascii_shift_out_s = f_string_ascii_shift_out;
  const f_string_t f_string_ascii_space_s = f_string_ascii_space;
  const f_string_t f_string_ascii_space_back_s = f_string_ascii_space_back;
  const f_string_t f_string_ascii_substitute_s = f_string_ascii_substitute;
  const f_string_t f_string_ascii_synchronous_idle_s = f_string_ascii_synchronous_idle;
  const f_string_t f_string_ascii_tab_horizontal_s = f_string_ascii_tab_horizontal;
  const f_string_t f_string_ascii_tab_vertical_s = f_string_ascii_tab_vertical;
  const f_string_t f_string_ascii_text_start_s = f_string_ascii_text_start;
  const f_string_t f_string_ascii_text_stop_s = f_string_ascii_text_stop;
  const f_string_t f_string_ascii_transmission_stop_s = f_string_ascii_transmission_stop;
  const f_string_t f_string_ascii_transmission_block_end_s = f_string_ascii_transmission_block_end;
#endif // _di_string_ascii_s_

#ifdef __cplusplus
} // extern "C"
#endif
