#include "print.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_print_sequences_
  const f_string_t f_print_sequence_acknowledge_s = F_print_sequence_acknowledge_s;
  const f_string_t f_print_sequence_acknowledge_negative_s = F_print_sequence_acknowledge_negative_s;
  const f_string_t f_print_sequence_backspace_s = F_print_sequence_backspace_s;
  const f_string_t f_print_sequence_bell_s = F_print_sequence_bell_s;
  const f_string_t f_print_sequence_cancel_s = F_print_sequence_cancel_s;
  const f_string_t f_print_sequence_carriage_return_s = F_print_sequence_carriage_return_s;
  const f_string_t f_print_sequence_data_link_escape_s = F_print_sequence_data_link_escape_s;
  const f_string_t f_print_sequence_delete_s = F_print_sequence_delete_s;
  const f_string_t f_print_sequence_device_control_1_s = F_print_sequence_device_control_1_s;
  const f_string_t f_print_sequence_device_control_2_s = F_print_sequence_device_control_2_s;
  const f_string_t f_print_sequence_device_control_3_s = F_print_sequence_device_control_3_s;
  const f_string_t f_print_sequence_device_control_4_s = F_print_sequence_device_control_4_s;
  const f_string_t f_print_sequence_end_of_medium_s = F_print_sequence_end_of_medium_s;
  const f_string_t f_print_sequence_end_of_text_s = F_print_sequence_end_of_text_s;
  const f_string_t f_print_sequence_end_of_transmission_s = F_print_sequence_end_of_transmission_s;
  const f_string_t f_print_sequence_end_of_transmission_block_s = F_print_sequence_end_of_transmission_block_s;
  const f_string_t f_print_sequence_enquiry_s = F_print_sequence_enquiry_s;
  const f_string_t f_print_sequence_escape_s = F_print_sequence_escape_s;
  const f_string_t f_print_sequence_form_feed_s = F_print_sequence_form_feed_s;
  const f_string_t f_print_sequence_line_feed_s = F_print_sequence_line_feed_s;
  const f_string_t f_print_sequence_null_s = F_print_sequence_null_s;
  const f_string_t f_print_sequence_separator_file_s = F_print_sequence_separator_file_s;
  const f_string_t f_print_sequence_separator_group_s = F_print_sequence_separator_group_s;
  const f_string_t f_print_sequence_separator_record_s = F_print_sequence_separator_record_s;
  const f_string_t f_print_sequence_separator_unit_s = F_print_sequence_separator_unit_s;
  const f_string_t f_print_sequence_shift_in_s = F_print_sequence_shift_in_s;
  const f_string_t f_print_sequence_shift_out_s = F_print_sequence_shift_out_s;
  const f_string_t f_print_sequence_start_of_header_s = F_print_sequence_start_of_header_s;
  const f_string_t f_print_sequence_start_of_text_s = F_print_sequence_start_of_text_s;
  const f_string_t f_print_sequence_substitute_s = F_print_sequence_substitute_s;
  const f_string_t f_print_sequence_synchronous_idle_s = F_print_sequence_synchronous_idle_s;
  const f_string_t f_print_sequence_tab_s = F_print_sequence_tab_s;
  const f_string_t f_print_sequence_tab_vertical_s = F_print_sequence_tab_vertical_s;
  const f_string_t f_print_sequence_unknown_s = F_print_sequence_unknown_s;
#endif // _di_f_print_sequences_

#ifndef _di_f_print_sequences_set_control_
  const char f_print_sequence_set_control_s[32][3] = {
    F_print_sequence_null_s,
    F_print_sequence_start_of_header_s,
    F_print_sequence_start_of_text_s,
    F_print_sequence_end_of_text_s,
    F_print_sequence_end_of_transmission_s,
    F_print_sequence_enquiry_s,
    F_print_sequence_acknowledge_s,
    F_print_sequence_bell_s,
    F_print_sequence_backspace_s,
    F_print_sequence_tab_s,
    F_print_sequence_line_feed_s,
    F_print_sequence_tab_vertical_s,
    F_print_sequence_form_feed_s,
    F_print_sequence_carriage_return_s,
    F_print_sequence_shift_out_s,
    F_print_sequence_shift_in_s,
    F_print_sequence_data_link_escape_s,
    F_print_sequence_device_control_1_s,
    F_print_sequence_device_control_2_s,
    F_print_sequence_device_control_3_s,
    F_print_sequence_device_control_4_s,
    F_print_sequence_acknowledge_negative_s,
    F_print_sequence_synchronous_idle_s,
    F_print_sequence_end_of_transmission_block_s,
    F_print_sequence_cancel_s,
    F_print_sequence_end_of_medium_s,
    F_print_sequence_substitute_s,
    F_print_sequence_escape_s,
    F_print_sequence_separator_file_s,
    F_print_sequence_separator_group_s,
    F_print_sequence_separator_record_s,
    F_print_sequence_separator_unit_s,
  };
#endif // _di_f_print_sequences_set_control_

#ifdef __cplusplus
} // extern "C"
#endif
