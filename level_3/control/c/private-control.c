#include "control.h"
#include "private-common.h"
#include "private-control.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_control_action_identify_
  uint8_t control_action_identify(fll_program_data_t * const main, control_data_t * const data, const f_string_static_t action) {

    if (fl_string_dynamic_compare(action, control_freeze_s) == F_equal_to) {
      return control_action_type_freeze_e;
    }

    if (fl_string_dynamic_compare(action, control_kill_s) == F_equal_to) {
      return control_action_type_kill_e;
    }

    if (fl_string_dynamic_compare(action, control_pause_s) == F_equal_to) {
      return control_action_type_pause_e;
    }

    if (fl_string_dynamic_compare(action, control_reboot_s) == F_equal_to) {
      return control_action_type_reboot_e;
    }

    if (fl_string_dynamic_compare(action, control_reload_s) == F_equal_to) {
      return control_action_type_reload_e;
    }

    if (fl_string_dynamic_compare(action, control_rerun_s) == F_equal_to) {
      return control_action_type_rerun_e;
    }

    if (fl_string_dynamic_compare(action, control_restart_s) == F_equal_to) {
      return control_action_type_restart_e;
    }

    if (fl_string_dynamic_compare(action, control_resume_s) == F_equal_to) {
      return control_action_type_resume_e;
    }

    if (fl_string_dynamic_compare(action, control_shutdown_s) == F_equal_to) {
      return control_action_type_shutdown_e;
    }

    if (fl_string_dynamic_compare(action, control_start_s) == F_equal_to) {
      return control_action_type_start_e;
    }

    if (fl_string_dynamic_compare(action, control_stop_s) == F_equal_to) {
      return control_action_type_stop_e;
    }

    if (fl_string_dynamic_compare(action, control_thaw_s) == F_equal_to) {
      return control_action_type_thaw_e;
    }

    return 0;
  }
#endif // _di_control_action_identify_

#ifndef _di_control_action_type_name_
  f_string_static_t control_action_type_name(const uint8_t type) {

    switch (type) {
      case control_action_type_freeze_e:
        return control_freeze_s;

      case control_action_type_kill_e:
        return control_kill_s;

      case control_action_type_pause_e:
        return control_pause_s;

      case control_action_type_reboot_e:
        return control_reboot_s;

      case control_action_type_reload_e:
        return control_reload_s;

      case control_action_type_rerun_e:
        return control_rerun_s;

      case control_action_type_restart_e:
        return control_restart_s;

      case control_action_type_resume_e:
        return control_resume_s;

      case control_action_type_shutdown_e:
        return control_shutdown_s;

      case control_action_type_start_e:
        return control_start_s;

      case control_action_type_stop_e:
        return control_stop_s;

      case control_action_type_thaw_e:
        return control_thaw_s;
    }

    return f_string_empty_s;
  }
#endif // _di_control_action_type_name_

#ifndef _di_control_action_verify_
  f_status_t control_action_verify(fll_program_data_t * const main, control_data_t * const data) {

    switch (data->action) {
      case control_action_type_freeze_e:
      case control_action_type_kill_e:
      case control_action_type_pause_e:
      case control_action_type_reload_e:
      case control_action_type_rerun_e:
      case control_action_type_restart_e:
      case control_action_type_resume_e:
      case control_action_type_start_e:
      case control_action_type_stop_e:
      case control_action_type_thaw_e:
        if (main->parameters.remaining.used < 2) {
          control_print_error_parameter_action_rule_not(main, data->argv[main->parameters.remaining.array[0]]);

          return F_status_set_error(F_parameter);
        }
        else if (main->parameters.remaining.used > 3) {
          control_print_error_parameter_action_rule_too_many(main, data->argv[main->parameters.remaining.array[0]]);

          return F_status_set_error(F_parameter);
        }

        if (!data->argv[main->parameters.remaining.array[1]].used) {
          if (main->parameters.remaining.used == 2) {
            control_print_error_parameter_action_rule_empty(main, data->argv[main->parameters.remaining.array[0]]);
          }
          else {
            control_print_error_parameter_action_rule_directory_empty(main, data->argv[main->parameters.remaining.array[0]]);
          }

          return F_status_set_error(F_parameter);
        }

        if (main->parameters.remaining.used == 3) {
          if (!data->argv[main->parameters.remaining.array[2]].used) {
            control_print_error_parameter_action_rule_basename_empty(main, data->argv[main->parameters.remaining.array[0]]);

            return F_status_set_error(F_parameter);
          }
        }

        return F_none;
    }

    // @todo the reboot and shutdown need to support date and time actions: "now", "in (a time)", and "at (a time)".
    if (data->action == control_action_type_reboot_e) {
      // @todo (also needs to support kexec calls or kexec needs its own action, which will likely be in the controller program.)
    }

    if (data->action == control_action_type_shutdown_e) {
      // @todo
    }

    return F_none;
  }
#endif // _di_control_action_verify_

#ifndef _di_control_packet_build_
  f_status_t control_packet_build(fll_program_data_t * const main, control_data_t * const data) {

    data->cache.large.used = 0;
    data->cache.small.used = 0;

    f_array_length_t i = 0;
    f_array_length_t length = 5 + f_fss_string_header_s.used + f_fss_string_payload_s.used + control_action_s.used + control_type_s.used;
    length += f_fss_payload_list_open_s.used * 2;
    length += f_fss_payload_list_close_s.used * 4;
    length += f_string_ascii_0_s.used;

    for (; i < main->parameters.remaining.used; ++i) {
      length += f_fss_payload_header_open_s.used + data->argv[main->parameters.remaining.array[i]].used + f_fss_payload_header_close_s.used;
    } // for

    if (length > 0xffffffff) {
      return F_status_set_error(F_too_large);
    }

    f_status_t status = f_string_dynamic_resize(length, &data->cache.large);
    if (F_status_is_error(status)) return status;

    // The Packet Control Block.
    {
      f_char_t block_control = (f_char_t) control_packet_flag_binary_d;

      #ifdef _is_F_endian_big
        block_control |= (f_char_t) control_packet_flag_endian_big_d;
      #endif // _is_F_endian_big

      status = f_string_append(&block_control, 1, &data->cache.large);
      if (F_status_is_error(status)) return status;
    }

    // The Packet Size Block.
    {
      status = f_string_append((f_char_t *) &length, 1, &data->cache.large);
      if (F_status_is_error(status)) return status;
    }

    // The Payload "header:" line.
    status = f_string_dynamic_append(f_fss_string_header_s, &data->cache.large);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_append(f_fss_payload_list_open_s, &data->cache.large);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_append(f_fss_payload_list_close_s, &data->cache.large);
    if (F_status_is_error(status)) return status;

    // The Payload "type ..." line.
    status = f_string_dynamic_append(control_type_s, &data->cache.large);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_append(f_fss_payload_header_open_s, &data->cache.large);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_append(data->argv[main->parameters.remaining.array[0]], &data->cache.large);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_append(f_fss_payload_header_close_s, &data->cache.large);
    if (F_status_is_error(status)) return status;

    // Each Payload "action ..." line.
    for (i = 1; i < main->parameters.remaining.used; ++i) {

      status = f_string_dynamic_append(control_action_s, &data->cache.large);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamic_append(f_fss_payload_header_open_s, &data->cache.large);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamic_append(data->argv[main->parameters.remaining.array[i]], &data->cache.large);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamic_append(f_fss_payload_header_close_s, &data->cache.large);
      if (F_status_is_error(status)) return status;
    } // for

    // The Payload "length 0" line.
    status = f_string_dynamic_append(control_length_s, &data->cache.large);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_append(f_fss_payload_header_open_s, &data->cache.large);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_append(f_string_ascii_0_s, &data->cache.large);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_append(f_fss_payload_header_close_s, &data->cache.large);
    if (F_status_is_error(status)) return status;

    // The Payload "payload:" line.
    status = f_string_dynamic_append(f_fss_string_payload_s, &data->cache.large);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_append(f_fss_payload_list_open_s, &data->cache.large);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_append(f_fss_payload_list_open_end_s, &data->cache.large);
    if (F_status_is_error(status)) return status;

    // The Payload "payload:" Content is empty.

    return F_none;
  }
#endif // _di_control_packet_build_

#ifndef _di_control_packet_receive_
  f_status_t control_packet_receive(fll_program_data_t * const main, control_data_t * const data, control_payload_header_t * const header) {

    data->cache.large.used = 0;
    data->cache.small.used = 0;
    data->cache.packet_objects.used = 0;
    data->cache.packet_contents.used = 0;
    data->cache.header_objects.used = 0;
    data->cache.header_contents.used = 0;
    data->cache.delimits.used = 0;

    header->action = 0;
    header->type = 0;
    header->status = F_none;
    header->length = 0;

    f_status_t status = F_none;
    f_array_length_t i = 0;
    f_string_range_t range_header = f_string_range_t_initialize;
    f_string_range_t range_payload = f_string_range_t_initialize;

    {
      f_array_length_t length = 5;
      uint8_t head[length];

      memset(head, 0, sizeof(uint8_t) * length);

      status = f_socket_read(&data->socket, f_socket_flag_peek_d, (void *) head, &length);
      if (F_status_is_error(status)) return status;
      if (length < 5) return F_status_set_error(F_packet_not);

      uint8_t control = head[0] & (control_packet_flag_binary_d | control_packet_flag_endian_big_d);

      // Only the first two bits of the 8 Control bits are allowed to be set to 1 for this Packet.
      if (head[0] & (~(control_packet_flag_binary_d | control_packet_flag_endian_big_d))) {
        return F_status_set_error(F_packet_not);
      }

      #ifdef _is_F_endian_big
        if (control & control_packet_flag_endian_big_d) {
          length = ((uint8_t) head[1]) << 24;
          length |= ((uint8_t) head[2]) << 16;
          length |= ((uint8_t) head[3]) << 8;
          length |= (uint8_t) head[4];
        }
        else {
          length = ((uint8_t) head[1]);
          length |= ((uint8_t) head[2]) >> 8;
          length |= ((uint8_t) head[3]) >> 16;
          length |= (uint8_t) head[4] >> 24;
        }
      #else
        if (control & control_packet_flag_endian_big_d) {
          length = ((uint8_t) head[1]);
          length |= ((uint8_t) head[2]) >> 8;
          length |= ((uint8_t) head[3]) >> 16;
          length |= (uint8_t) head[4] >> 24;
        }
        else {
          length = ((uint8_t) head[1]) << 24;
          length |= ((uint8_t) head[2]) << 16;
          length |= ((uint8_t) head[3]) << 8;
          length |= (uint8_t) head[4];
        }
      #endif // #ifdef _is_F_endian_big

      if (length > 0xffffffff) {
        return F_status_set_error(F_too_large);
      }

      status = f_string_dynamic_increase_by(length, &data->cache.large);
      if (F_status_is_error(status)) return status;

      status = f_socket_read(&data->socket, f_socket_flag_wait_all_d, (void *) head, &length);
      if (F_status_is_error(status)) return status;
      if (length < data->cache.large.used) return F_status_set_error(F_too_small);
      if (length > data->cache.large.used) return F_status_set_error(F_too_large);
    }

    {
      f_state_t state = macro_f_state_t_initialize(control_allocation_large_d, control_allocation_small_d, 0, &control_signal_state_interrupt_fss, 0, (void *) main, 0);
      f_string_range_t range_packet = macro_f_string_range_t_initialize2(data->cache.large.used);

      status = fll_fss_basic_list_read(data->cache.large, state, &range_packet, &data->cache.packet_objects, &data->cache.packet_contents, &data->cache.delimits, 0, 0);

      if (F_status_is_error(status)) {
        control_print_debug_packet_message(main, "Failure while reading FSS Basic List in the response packet", 0, 0, &status);

        if (F_status_set_fine(status) == F_memory_not) {
          return status;
        }

        return F_status_set_error(F_header);
      }

      status = fl_fss_apply_delimit(data->cache.delimits, &data->cache.large);

      if (F_status_is_error(status)) {
        control_print_debug_packet_message(main, "Failure while processing delimits for the FSS Basic List in the response packet", 0, 0, &status);

        return F_status_set_error(F_header);
      }

      data->cache.delimits.used = 0;

      {
        f_string_ranges_t *content_header = 0;
        f_string_ranges_t *content_payload = 0;

        for (; i < data->cache.packet_objects.used; ++i) {

          if (fl_string_dynamic_partial_compare_string(f_fss_string_header_s.string, data->cache.large, f_fss_string_header_s.used, data->cache.packet_objects.array[i]) == F_equal_to) {

            // The FSS-000E (Payload) standard does not prohibit multiple "header", but such cases are not supported by the controller and the control programs.
            if (content_header) {
              control_print_debug_packet_message(main, "Multiple %[" F_fss_string_header_s "%] found in response packet", 0, 0, 0);

              return F_status_set_error(F_payload_not);
            }

            content_header = &data->cache.packet_contents.array[i];
          }
          else if (fl_string_dynamic_partial_compare_string(f_fss_string_payload_s.string, data->cache.large, f_fss_string_payload_s.used, data->cache.packet_objects.array[i]) == F_equal_to) {

            // Only a single "payload" is supported by the FSS-000E (Payload) standard.
            if (content_payload) {
              control_print_debug_packet_message(main, "Multiple %[" F_fss_string_payload_s "%] found in response packet", 0, 0, 0);

              return F_status_set_error(F_payload_not);
            }

            if (i + 1 < data->cache.packet_contents.used) {
              control_print_debug_packet_message(main, "Invalid FSS Payload format, the %[" F_fss_string_payload_s "%] is required to be the last FSS Basic List Object", 0, 0, 0);

              return F_status_set_error(F_payload_not);
            }

            content_payload = &data->cache.packet_contents.array[i];
          }
        } // for

        if (!content_header) {
          control_print_debug_packet_message(main, "Did not find a %[" F_fss_string_header_s "%] in the response packet", 0, 0, 0);

          return F_status_set_error(F_payload_not);
        }

        if (!content_payload) {
          control_print_debug_packet_message(main, "Did not find a %[" F_fss_string_payload_s "%] in the response packet", 0, 0, 0);

          return F_status_set_error(F_payload_not);
        }

        range_header = content_header->array[0];
        range_payload = content_payload->array[0];
      }

      {
        // 0x1 = found action, 0x2 = found length, 0x4 = found status, 0x8 = found_type.
        uint8_t found = 0;
        f_number_unsigned_t number = 0;
        f_string_range_t range = range_header;

        status = fll_fss_extended_read(data->cache.large, state, &range, &data->cache.header_objects, &data->cache.header_contents, 0, 0, &data->cache.delimits, 0);

        if (F_status_is_error(status)) {
          control_print_debug_packet_message(main, "Failure while reading FSS Extended in the response packet", 0, 0, &status);

          if (F_status_set_fine(status) == F_memory_not) {
            return status;
          }

          return F_status_set_error(F_header_not);
        }

        status = fl_fss_apply_delimit(data->cache.delimits, &data->cache.large);

        if (F_status_is_error(status)) {
          control_print_debug_packet_message(main, "Failure while processing delimits for the FSS Basic List in the response packet", 0, 0, &status);

          return F_status_set_error(F_header_not);
        }

        if (!data->cache.header_contents.used) {
          control_print_debug_packet_message(main, "Did not find any Content within the %[" F_fss_string_header_s "%]", 0, 0, 0);

          return F_status_set_error(F_header_not);
        }

        for (i = 0; i < data->cache.header_objects.used; ++i) {

          if (fl_string_dynamic_partial_compare_string(control_action_s.string, data->cache.large, control_action_s.used, data->cache.header_objects.array[i]) == F_equal_to) {
            if (!(found & 0x1)) {
              const f_array_length_t action_length = (data->cache.header_contents.array[i].array[0].stop - data->cache.header_contents.array[i].array[0].start) + 1;
              char action_string[action_length + 1];
              const f_string_static_t action = macro_f_string_static_t_initialize(action_string, 0, action_length);

              memcpy(action_string, data->cache.large.string + data->cache.header_contents.array[i].array[0].start, action_length);
              action_string[action_length] = 0;

              found |= 0x1;

              control_print_debug_packet_header_object_and_content(main, control_action_s, data->cache.large, data->cache.header_contents.array[i].array[0]);

              header->action = control_action_identify(main, data, action);

              if (!header->action) {
                control_print_debug_packet_message(main, "Failed to identify %[" CONTROL_action_s "%] from: ", &data->cache.large, &data->cache.header_contents.array[i].array[0], 0);

                return F_status_set_error(F_header_not);
              }
            }
            else {
              control_print_warning_packet_header_duplicate_object(main, control_action_s);
            }
          }
          else if (fl_string_dynamic_partial_compare_string(control_length_s.string, data->cache.large, control_length_s.used, data->cache.header_objects.array[i]) == F_equal_to) {
            if (!(found & 0x2)) {
              found |= 0x2;
              number = 0;

              control_print_debug_packet_header_object_and_content(main, control_length_s, data->cache.large, data->cache.header_contents.array[i].array[0]);

              status = fl_conversion_dynamic_partial_to_number_unsigned(data->cache.large, data->cache.header_contents.array[i].array[0], &number);

              if (F_status_is_error(status)) {
                control_print_debug_packet_message(main, "Failed to process number for %[" CONTROL_length_s "%] in the response packet, number is:", &data->cache.large, &data->cache.header_contents.array[i].array[0], &status);

                return F_status_set_error(F_header_not);
              }

              if (number > F_type_size_max_32_unsigned_d) {
                control_print_debug_packet_message(main, "Processed number for %[" CONTROL_length_s "%] exceeds allowed size in the response packet, number is:", &data->cache.large, &data->cache.header_contents.array[i].array[0], &status);

                return F_status_set_error(F_header_not);
              }

              header->length = (uint16_t) number;
            }
            else {
              control_print_warning_packet_header_duplicate_object(main, control_length_s);
            }
          }
          else if (fl_string_dynamic_partial_compare_string(control_status_s.string, data->cache.large, control_status_s.used, data->cache.header_objects.array[i]) == F_equal_to) {
            if (!(found & 0x4)) {
              found |= 0x4;
              number = 0;

              control_print_debug_packet_header_object_and_content(main, control_status_s, data->cache.large, data->cache.header_contents.array[i].array[0]);

              // Attempt to get status as a number.
              status = fl_conversion_dynamic_partial_to_number_unsigned(data->cache.large, data->cache.header_contents.array[i].array[0], &number);

              if (F_status_set_fine(status) == F_number) {

                // Not a number, so attempt get by status string name.
                const f_array_length_t name_length = (data->cache.header_contents.array[i].array[0].stop - data->cache.header_contents.array[i].array[0].start) + 1;
                char name_string[name_length + 1];
                const f_string_static_t name = macro_f_string_static_t_initialize(name_string, 0, name_length);

                memcpy(name_string, data->cache.large.string + data->cache.header_contents.array[i].array[0].start, name_length);
                name_string[name_length] = 0;

                status = fll_status_string_from(name, &header->status);

                if (F_status_is_error(status)) {
                  control_print_debug_packet_message(main, "Failed to process %[" CONTROL_status_s "%] in the response packet, Content is:", &data->cache.large, &data->cache.header_contents.array[i].array[0], &status);

                  return F_status_set_error(F_header_not);
                }
              }
              else if (F_status_is_error(status)) {
                control_print_debug_packet_message(main, "Failed to process number for %[" CONTROL_status_s "%] in the response packet, number is:", &data->cache.large, &data->cache.header_contents.array[i].array[0], &status);

                if (F_status_set_fine(status) == F_memory_not) {
                  return status;
                }

                return F_status_set_error(F_header_not);
              }
              else {
                if (number > F_status_size_max_with_bits_d) {
                  control_print_debug_packet_message(main, "Processed number for %[" CONTROL_status_s "%] exceeds allowed size in the response packet, number is:", &data->cache.large, &data->cache.header_contents.array[i].array[0], 0);

                  return F_status_set_error(F_header_not);
                }
              }
            }
            else {
              control_print_warning_packet_header_duplicate_object(main, control_length_s);
            }
          }
          else if (fl_string_dynamic_partial_compare_string(control_type_s.string, data->cache.large, control_type_s.used, data->cache.header_objects.array[i]) == F_equal_to) {
            if (!(found & 0x8)) {
              found |= 0x8;

              control_print_debug_packet_header_object_and_content(main, control_type_s, data->cache.large, data->cache.header_contents.array[i].array[0]);

              if (fl_string_dynamic_partial_compare_string(control_controller_s.string, data->cache.large, control_controller_s.used, data->cache.header_contents.array[i].array[0]) == F_equal_to) {
                header->type = control_payload_type_controller_e;
              }
              else if (fl_string_dynamic_partial_compare_string(control_error_s.string, data->cache.large, control_error_s.used, data->cache.header_contents.array[i].array[0]) == F_equal_to) {
                header->type = control_payload_type_error_e;
              }
              else {
                control_print_debug_packet_message(main, "Unknown %[" CONTROL_type_s "%] in response packet, Content is:", &data->cache.large, &data->cache.header_contents.array[i].array[0], 0);

                return F_status_set_error(F_header_not);
              }
            }
            else {
              control_print_warning_packet_header_duplicate_object(main, control_type_s);
            }
          }
        }
      }
    }

    return F_none;
  }
#endif // _di_control_packet_receive_

#ifndef _di_control_packet_process_
  f_status_t control_packet_process(fll_program_data_t * const main, control_data_t * const data, const control_payload_header_t header) {

    if (header.type == control_payload_type_error_e) {
      control_print_error_packet_response(main, data, header);

      return F_none;
    }

    // @todo based on header->type, handle the data.

    return F_none;
  }
#endif // _di_control_packet_process_

#ifndef _di_control_packet_send_
  f_status_t control_packet_send(fll_program_data_t * const main, control_data_t * const data) {

    // @todo
    f_array_length_t length = 0;

    //F_status_t status = f_socket_write(&data->socket, 0, data->cache.large, &length);

    return F_none;
  }
#endif // _di_control_packet_send_

#ifndef _di_control_settings_load_
  f_status_t control_settings_load(fll_program_data_t * const main, control_data_t * const data) {

    f_status_t status = F_none;

    data->cache.small.used = 0;

    if (main->parameters.array[control_parameter_settings_e].result == f_console_result_additional_e) {
      const f_array_length_t index = main->parameters.array[control_parameter_settings_e].values.array[main->parameters.array[control_parameter_settings_e].values.used - 1];

      status = f_string_dynamic_append(data->argv[index], &data->cache.small);
    }
    else {
      status = f_string_dynamic_append(control_path_settings_s, &data->cache.small);
    }

    if (F_status_is_error(status)) {
      fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_append", F_true);

      return status;
    }

    {
      f_file_t file = f_file_t_initialize;

      status = f_file_stream_open(data->cache.small, f_file_open_mode_read_s, &file);

      if (F_status_is_error(status)) {
        fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_open", F_true, data->cache.small, f_file_operation_open_s, fll_error_file_type_file_e);

        return status;
      }

      status = f_file_stream_read(file, &data->cache.large);

      f_file_stream_close(F_true, &file);

      if (F_status_is_error(status)) {
        fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_read", F_true, data->cache.small, f_file_operation_read_s, fll_error_file_type_file_e);

        return status;
      }
    }

    f_state_t state = f_state_t_initialize;
    f_string_range_t range = f_string_range_t_initialize;
    f_fss_objects_t objects = f_fss_objects_t_initialize;
    f_fss_contents_t contents = f_fss_contents_t_initialize;
    f_fss_delimits_t delimits = f_fss_delimits_t_initialize;

    status = fll_fss_extended_read(data->cache.large, state, &range, &objects, &contents, 0, 0, &delimits, 0);

    if (F_status_is_error(status)) {
      fll_error_file_print(main->error, F_status_set_fine(status), "fll_fss_extended_read", F_true, data->cache.small, f_file_operation_process_s, fll_error_file_type_file_e);
    }
    else {
      status = fl_fss_apply_delimit(delimits, &data->cache.large);

      if (F_status_is_error(status)) {
        fll_error_file_print(main->error, F_status_set_fine(status), "fl_fss_apply_delimit", F_true, data->cache.small, f_file_operation_process_s, fll_error_file_type_file_e);
      }
    }

    if (F_status_is_error_not(status)) {
      uint8_t parameter_hass[] = { 0, 0, 0, 0 };

      f_array_length_t parameter_ats[] = { 0, 0, 0, 0 };

      {
        const f_string_static_t parameter_names[] = {
          control_name_socket_s,
          control_path_socket_s,
          control_path_socket_prefix_s,
          control_path_socket_suffix_s,
        };

        f_array_length_t i = 0;
        uint8_t j = 0;
        f_string_range_t range = f_string_range_t_initialize;

        for (; i < objects.used; ++i) {

          for (j = 0; j < 4; ++j) {

            range.stop = parameter_names[j].used - 1;

            if (fl_string_dynamic_partial_compare(parameter_names[j], data->cache.large, range, objects.array[i]) == F_equal_to) {
              parameter_hass[j] = F_true;
              parameter_ats[j] = i;

              break;
            }
          } // for
        } // for
      }

      data->cache.small.used = 0;

      if (main->parameters.array[control_parameter_socket_e].result == f_console_result_additional_e) {
        const f_array_length_t index = main->parameters.array[control_parameter_socket_e].values.array[main->parameters.array[control_parameter_socket_e].values.used - 1];

        status = f_string_dynamic_append(data->argv[index], &data->cache.small);
      }
      else if (parameter_hass[1]) {
        status = f_string_dynamic_partial_append_nulless(data->cache.large, objects.array[parameter_ats[1]], &data->cache.small);
      }
      else {
        status = f_string_dynamic_append(controller_path_socket_s, &data->cache.small);
      }

      if (F_status_is_error(status)) {
        if (main->parameters.array[control_parameter_socket_e].result == f_console_result_additional_e || !parameter_hass[1]) {
          fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_append", F_true);
        }
        else {
          fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);
        }
      }

      status = f_file_exists(data->cache.small);

      if (F_status_is_error(status) || status == F_false) {
        if (F_status_is_error(status)) {
          fll_error_file_print(main->error, F_status_set_fine(status), "f_file_exists", F_true, data->cache.small, f_file_operation_find_s, fll_error_file_type_directory_e);

          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->error.to.stream);
          }
        }

        control_print_error_socket_file_missing(main, data->cache.small);

        status = F_status_set_error(F_socket_not);
      }

      // Construct the file name when the socket path is a directory.
      else if (f_file_is(data->cache.small, F_file_type_directory_d, F_true) == F_true) {
        status = f_string_dynamic_append_assure(f_path_separator_s, &data->cache.small);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_append_assure", F_true);
        }
        else {
          uint8_t append_ids[] = {
            0,
            control_parameter_name_e,
            0,
          };

          uint8_t append_hass[] = {
            parameter_hass[2],
            parameter_hass[0],
            parameter_hass[3],
          };

          const f_string_static_t append_defaults[] = {
            controller_path_socket_prefix_s,
            controller_name_socket_s,
            controller_path_socket_suffix_s,
          };

          for (uint8_t i = 0; i < 3; ++i) {

            if (append_ids[i] && main->parameters.array[append_ids[i]].result == f_console_result_additional_e) {
              const f_array_length_t index = main->parameters.array[append_ids[i]].values.array[main->parameters.array[append_ids[i]].values.used - 1];

              status = f_string_dynamic_append(data->argv[index], &data->cache.small);
            }
            else if (append_hass[i]) {
              status = f_string_dynamic_partial_append_nulless(data->cache.large, objects.array[append_hass[i]], &data->cache.small);
            }
            else {
              status = f_string_dynamic_append_nulless(append_defaults[i], &data->cache.small);
            }

            if (F_status_is_error(status)) {
              if (append_ids[i] && main->parameters.array[append_ids[i]].result == f_console_result_additional_e || !append_hass[i]) {
                fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_append", F_true);
              }
              else {
                fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);
              }

              break;
            }
          } // for

          if (F_status_is_error_not(status)) {
            status = f_file_exists(data->cache.small);

            if (F_status_is_error(status) || status == F_false) {
              if (F_status_is_error(status)) {
                fll_error_file_print(main->error, F_status_set_fine(status), "f_file_exists", F_true, data->cache.small, f_file_operation_find_s, fll_error_file_type_directory_e);

                if (main->error.verbosity != f_console_verbosity_quiet_e) {
                  fll_print_dynamic_raw(f_string_eol_s, main->error.to.stream);
                }
              }

              control_print_error_socket_file_missing(main, data->cache.small);

              status = F_status_set_error(F_socket_not);
            }
          }

          if (F_status_is_error_not(status)) {
            if (f_file_is(data->cache.small, F_file_type_socket_d, F_true) == F_false) {
              control_print_error_socket_file_not(main, data->cache.small);

              status = F_status_set_error(F_socket_not);
            }
          }

          if (F_status_is_error_not(status)) {
            status = f_socket_create(&data->socket);

            if (F_status_is_error(status)) {
              fll_error_print(main->error, F_status_set_fine(status), "f_socket_create", F_true);

              if (main->error.verbosity != f_console_verbosity_quiet_e) {
                fll_print_dynamic_raw(f_string_eol_s, main->error.to.stream);
              }

              control_print_error_socket_file_failed(main, data->cache.small);
            }
          }

          if (F_status_is_error_not(status)) {
            status = f_socket_connect(data->socket);

            if (F_status_is_error(status)) {
              fll_error_print(main->error, F_status_set_fine(status), "f_socket_connect", F_true);

              if (main->error.verbosity != f_console_verbosity_quiet_e) {
                fll_print_dynamic_raw(f_string_eol_s, main->error.to.stream);
              }

              control_print_error_socket_file_failed(main, data->cache.small);
            }
          }
        }
      }
    }

    f_string_ranges_resize(0, &objects);
    f_string_rangess_resize(0, &contents);
    f_array_lengths_resize(0, &delimits);

    data->cache.large.used = 0;
    data->cache.small.used = 0;

    if (F_status_is_error_not(status)) {
      if (data->cache.large.size > control_default_buffer_limit_soft_large_d) {
        status = f_string_dynamic_resize(control_default_buffer_limit_soft_large_d, &data->cache.large);
      }

      if (F_status_is_error_not(status)) {
        if (data->cache.small.size > control_default_buffer_limit_soft_small_d) {
          status = f_string_dynamic_resize(control_default_buffer_limit_soft_small_d, &data->cache.small);
        }
      }
    }

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_control_settings_load_

#ifdef __cplusplus
} // extern "C"
#endif
