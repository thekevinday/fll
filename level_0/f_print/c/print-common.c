#include "print.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_print_sequences_
  const f_string_t f_print_sequence_acknowledge_s = f_print_sequence_acknowledge;
  const f_string_t f_print_sequence_acknowledge_negative_s = f_print_sequence_acknowledge_negative;
  const f_string_t f_print_sequence_backspace_s = f_print_sequence_backspace;
  const f_string_t f_print_sequence_bell_s = f_print_sequence_bell;
  const f_string_t f_print_sequence_cancel_s = f_print_sequence_cancel;
  const f_string_t f_print_sequence_carriage_return_s = f_print_sequence_carriage_return;
  const f_string_t f_print_sequence_data_link_escape_s = f_print_sequence_data_link_escape;
  const f_string_t f_print_sequence_delete_s = f_print_sequence_delete;
  const f_string_t f_print_sequence_device_control_1_s = f_print_sequence_device_control_1;
  const f_string_t f_print_sequence_device_control_2_s = f_print_sequence_device_control_2;
  const f_string_t f_print_sequence_device_control_3_s = f_print_sequence_device_control_3;
  const f_string_t f_print_sequence_device_control_4_s = f_print_sequence_device_control_4;
  const f_string_t f_print_sequence_end_of_medium_s = f_print_sequence_end_of_medium;
  const f_string_t f_print_sequence_end_of_text_s = f_print_sequence_end_of_text;
  const f_string_t f_print_sequence_end_of_transmission_s = f_print_sequence_end_of_transmission;
  const f_string_t f_print_sequence_end_of_transmission_block_s = f_print_sequence_end_of_transmission_block;
  const f_string_t f_print_sequence_enquiry_s = f_print_sequence_enquiry;
  const f_string_t f_print_sequence_escape_s = f_print_sequence_escape;
  const f_string_t f_print_sequence_form_feed_s = f_print_sequence_form_feed;
  const f_string_t f_print_sequence_line_feed_s = f_print_sequence_line_feed;
  const f_string_t f_print_sequence_null_s = f_print_sequence_null;
  const f_string_t f_print_sequence_separator_file_s = f_print_sequence_separator_file;
  const f_string_t f_print_sequence_separator_group_s = f_print_sequence_separator_group;
  const f_string_t f_print_sequence_separator_record_s = f_print_sequence_separator_record;
  const f_string_t f_print_sequence_separator_unit_s = f_print_sequence_separator_unit;
  const f_string_t f_print_sequence_shift_in_s = f_print_sequence_shift_in;
  const f_string_t f_print_sequence_shift_out_s = f_print_sequence_shift_out;
  const f_string_t f_print_sequence_start_of_header_s = f_print_sequence_start_of_header;
  const f_string_t f_print_sequence_start_of_text_s = f_print_sequence_start_of_text;
  const f_string_t f_print_sequence_substitute_s = f_print_sequence_substitute;
  const f_string_t f_print_sequence_synchronous_idle_s = f_print_sequence_synchronous_idle;
  const f_string_t f_print_sequence_tab_s = f_print_sequence_tab;
  const f_string_t f_print_sequence_tab_vertical_s = f_print_sequence_tab_vertical;
  const f_string_t f_print_sequence_unknown_s = f_print_sequence_unknown;
#endif // _di_f_print_sequences_

#ifndef _di_f_print_sequences_set_control_
  const char f_print_sequence_set_control_s[32][3] = {
    f_print_sequence_null,
    f_print_sequence_start_of_header,
    f_print_sequence_start_of_text,
    f_print_sequence_end_of_text,
    f_print_sequence_end_of_transmission,
    f_print_sequence_enquiry,
    f_print_sequence_acknowledge,
    f_print_sequence_bell,
    f_print_sequence_backspace,
    f_print_sequence_tab,
    f_print_sequence_line_feed,
    f_print_sequence_tab_vertical,
    f_print_sequence_form_feed,
    f_print_sequence_carriage_return,
    f_print_sequence_shift_out,
    f_print_sequence_shift_in,
    f_print_sequence_data_link_escape,
    f_print_sequence_device_control_1,
    f_print_sequence_device_control_2,
    f_print_sequence_device_control_3,
    f_print_sequence_device_control_4,
    f_print_sequence_acknowledge_negative,
    f_print_sequence_synchronous_idle,
    f_print_sequence_end_of_transmission_block,
    f_print_sequence_cancel,
    f_print_sequence_end_of_medium,
    f_print_sequence_substitute,
    f_print_sequence_escape,
    f_print_sequence_separator_file,
    f_print_sequence_separator_group,
    f_print_sequence_separator_record,
    f_print_sequence_separator_unit,
  };
#endif // _di_f_print_sequences_set_control_

#ifdef __cplusplus
} // extern "C"
#endif
