#include "../print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_print_sequences_
  const f_string_static_t f_print_sequence_acknowledge_s = macro_f_string_static_t_initialize(F_print_sequence_acknowledge_s, 0, F_print_sequence_acknowledge_s_length);
  const f_string_static_t f_print_sequence_acknowledge_negative_s = macro_f_string_static_t_initialize(F_print_sequence_acknowledge_negative_s, 0, F_print_sequence_acknowledge_negative_s_length);
  const f_string_static_t f_print_sequence_backspace_s = macro_f_string_static_t_initialize(F_print_sequence_backspace_s, 0, F_print_sequence_backspace_s_length);
  const f_string_static_t f_print_sequence_bell_s = macro_f_string_static_t_initialize(F_print_sequence_bell_s, 0, F_print_sequence_bell_s_length);
  const f_string_static_t f_print_sequence_cancel_s = macro_f_string_static_t_initialize(F_print_sequence_cancel_s, 0, F_print_sequence_cancel_s_length);
  const f_string_static_t f_print_sequence_carriage_return_s = macro_f_string_static_t_initialize(F_print_sequence_carriage_return_s, 0, F_print_sequence_carriage_return_s_length);
  const f_string_static_t f_print_sequence_data_link_escape_s = macro_f_string_static_t_initialize(F_print_sequence_data_link_escape_s, 0, F_print_sequence_data_link_escape_s_length);
  const f_string_static_t f_print_sequence_delete_s = macro_f_string_static_t_initialize(F_print_sequence_delete_s, 0, F_print_sequence_delete_s_length);
  const f_string_static_t f_print_sequence_device_control_1_s = macro_f_string_static_t_initialize(F_print_sequence_device_control_1_s, 0, F_print_sequence_device_control_1_s_length);
  const f_string_static_t f_print_sequence_device_control_2_s = macro_f_string_static_t_initialize(F_print_sequence_device_control_2_s, 0, F_print_sequence_device_control_2_s_length);
  const f_string_static_t f_print_sequence_device_control_3_s = macro_f_string_static_t_initialize(F_print_sequence_device_control_3_s, 0, F_print_sequence_device_control_3_s_length);
  const f_string_static_t f_print_sequence_device_control_4_s = macro_f_string_static_t_initialize(F_print_sequence_device_control_4_s, 0, F_print_sequence_device_control_4_s_length);
  const f_string_static_t f_print_sequence_end_of_medium_s = macro_f_string_static_t_initialize(F_print_sequence_end_of_medium_s, 0, F_print_sequence_end_of_medium_s_length);
  const f_string_static_t f_print_sequence_end_of_text_s = macro_f_string_static_t_initialize(F_print_sequence_end_of_text_s, 0, F_print_sequence_end_of_text_s_length);
  const f_string_static_t f_print_sequence_end_of_transmission_s = macro_f_string_static_t_initialize(F_print_sequence_end_of_transmission_s, 0, F_print_sequence_end_of_transmission_s_length);
  const f_string_static_t f_print_sequence_end_of_transmission_block_s = macro_f_string_static_t_initialize(F_print_sequence_end_of_transmission_block_s, 0, F_print_sequence_end_of_transmission_block_s_length);
  const f_string_static_t f_print_sequence_enquiry_s = macro_f_string_static_t_initialize(F_print_sequence_enquiry_s, 0, F_print_sequence_enquiry_s_length);
  const f_string_static_t f_print_sequence_escape_s = macro_f_string_static_t_initialize(F_print_sequence_escape_s, 0, F_print_sequence_escape_s_length);
  const f_string_static_t f_print_sequence_form_feed_s = macro_f_string_static_t_initialize(F_print_sequence_form_feed_s, 0, F_print_sequence_form_feed_s_length);
  const f_string_static_t f_print_sequence_line_feed_s = macro_f_string_static_t_initialize(F_print_sequence_line_feed_s, 0, F_print_sequence_line_feed_s_length);
  const f_string_static_t f_print_sequence_line_new_s = macro_f_string_static_t_initialize(F_print_sequence_line_new_s, 0, F_print_sequence_line_new_s_length);
  const f_string_static_t f_print_sequence_null_s = macro_f_string_static_t_initialize(F_print_sequence_null_s, 0, F_print_sequence_null_s_length);
  const f_string_static_t f_print_sequence_separator_file_s = macro_f_string_static_t_initialize(F_print_sequence_separator_file_s, 0, F_print_sequence_separator_file_s_length);
  const f_string_static_t f_print_sequence_separator_group_s = macro_f_string_static_t_initialize(F_print_sequence_separator_group_s, 0, F_print_sequence_separator_group_s_length);
  const f_string_static_t f_print_sequence_separator_record_s = macro_f_string_static_t_initialize(F_print_sequence_separator_record_s, 0, F_print_sequence_separator_record_s_length);
  const f_string_static_t f_print_sequence_separator_unit_s = macro_f_string_static_t_initialize(F_print_sequence_separator_unit_s, 0, F_print_sequence_separator_unit_s_length);
  const f_string_static_t f_print_sequence_shift_in_s = macro_f_string_static_t_initialize(F_print_sequence_shift_in_s, 0, F_print_sequence_shift_in_s_length);
  const f_string_static_t f_print_sequence_shift_out_s = macro_f_string_static_t_initialize(F_print_sequence_shift_out_s, 0, F_print_sequence_shift_out_s_length);
  const f_string_static_t f_print_sequence_space_s = macro_f_string_static_t_initialize(F_print_sequence_space_s, 0, F_print_sequence_space_s_length);
  const f_string_static_t f_print_sequence_start_of_header_s = macro_f_string_static_t_initialize(F_print_sequence_start_of_header_s, 0, F_print_sequence_start_of_header_s_length);
  const f_string_static_t f_print_sequence_start_of_text_s = macro_f_string_static_t_initialize(F_print_sequence_start_of_text_s, 0, F_print_sequence_start_of_text_s_length);
  const f_string_static_t f_print_sequence_substitute_s = macro_f_string_static_t_initialize(F_print_sequence_substitute_s, 0, F_print_sequence_substitute_s_length);
  const f_string_static_t f_print_sequence_synchronous_idle_s = macro_f_string_static_t_initialize(F_print_sequence_synchronous_idle_s, 0, F_print_sequence_synchronous_idle_s_length);
  const f_string_static_t f_print_sequence_tab_s = macro_f_string_static_t_initialize(F_print_sequence_tab_s, 0, F_print_sequence_tab_s_length);
  const f_string_static_t f_print_sequence_tab_vertical_s = macro_f_string_static_t_initialize(F_print_sequence_tab_vertical_s, 0, F_print_sequence_tab_vertical_s_length);
  const f_string_static_t f_print_sequence_unknown_s = macro_f_string_static_t_initialize(F_print_sequence_unknown_s, 0, F_print_sequence_unknown_s_length);
#endif // _di_f_print_sequences_

#ifndef _di_f_print_sequences_set_control_
  const f_string_static_t f_print_sequence_set_control_s[32] = {
    f_print_sequence_null_s,
    f_print_sequence_start_of_header_s,
    f_print_sequence_start_of_text_s,
    f_print_sequence_end_of_text_s,
    f_print_sequence_end_of_transmission_s,
    f_print_sequence_enquiry_s,
    f_print_sequence_acknowledge_s,
    f_print_sequence_bell_s,
    f_print_sequence_backspace_s,
    f_print_sequence_tab_s,
    f_print_sequence_line_feed_s,
    f_print_sequence_tab_vertical_s,
    f_print_sequence_form_feed_s,
    f_print_sequence_carriage_return_s,
    f_print_sequence_shift_out_s,
    f_print_sequence_shift_in_s,
    f_print_sequence_data_link_escape_s,
    f_print_sequence_device_control_1_s,
    f_print_sequence_device_control_2_s,
    f_print_sequence_device_control_3_s,
    f_print_sequence_device_control_4_s,
    f_print_sequence_acknowledge_negative_s,
    f_print_sequence_synchronous_idle_s,
    f_print_sequence_end_of_transmission_block_s,
    f_print_sequence_cancel_s,
    f_print_sequence_end_of_medium_s,
    f_print_sequence_substitute_s,
    f_print_sequence_escape_s,
    f_print_sequence_separator_file_s,
    f_print_sequence_separator_group_s,
    f_print_sequence_separator_record_s,
    f_print_sequence_separator_unit_s,
  };
#endif // _di_f_print_sequences_set_control_

#ifdef __cplusplus
} // extern "C"
#endif
