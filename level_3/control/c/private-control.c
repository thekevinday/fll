#include "control.h"
#include "private-common.h"
#include "private-control.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_control_action_verify_
  f_status_t control_action_verify(const fll_program_data_t * const main, control_data_t * const data) {

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
        if (main->parameters.remaining.used < 3) {
          control_print_error_parameter_action_rule_not(main, data->argv[main->parameters.remaining.array[0]]);

          return F_status_set_error(F_parameter);
        }

        if (main->parameters.remaining.used > 3) {
          if (fl_string_dynamic_compare(control_at_s, data->argv[main->parameters.remaining.array[3]]) == F_equal_to) {
            if (main->parameters.remaining.used < 5) {
              control_print_error_parameter_action_rule_too_few_with(main, data->argv[main->parameters.remaining.array[0]], control_at_s);

              return F_status_set_error(F_parameter);
            }

            if (main->parameters.remaining.used > 5) {
              control_print_error_parameter_action_rule_too_many_with(main, data->argv[main->parameters.remaining.array[0]], control_at_s);

              return F_status_set_error(F_parameter);
            }
          }
          else if (fl_string_dynamic_compare(control_in_s, data->argv[main->parameters.remaining.array[3]]) == F_equal_to) {
            if (main->parameters.remaining.used < 6) {
              control_print_error_parameter_action_rule_too_few_with(main, data->argv[main->parameters.remaining.array[0]], control_in_s);

              return F_status_set_error(F_parameter);
            }
          }
          else if (fl_string_dynamic_compare(control_now_s, data->argv[main->parameters.remaining.array[3]]) == F_equal_to) {
            if (main->parameters.remaining.used > 4) {
              control_print_error_parameter_action_rule_too_many_with(main, data->argv[main->parameters.remaining.array[0]], control_now_s);

              return F_status_set_error(F_parameter);
            }
          }
          else {
            control_print_error_parameter_action_rule_with_unknown(main, data->argv[main->parameters.remaining.array[0]], data->argv[main->parameters.remaining.array[2]]);

            return F_status_set_error(F_parameter);
          }
        }

        if (!data->argv[main->parameters.remaining.array[1]].used) {
          if (main->parameters.remaining.used == 3) {
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

      case control_action_type_kexec_e:
      case control_action_type_reboot_e:
      case control_action_type_shutdown_e:
        if (main->parameters.remaining.used < 2) {
          control_print_error_parameter_action_rule_too_few(main, data->argv[main->parameters.remaining.array[0]]);

          return F_status_set_error(F_parameter);
        }

        if (fl_string_dynamic_compare(control_at_s, data->argv[main->parameters.remaining.array[1]]) == F_equal_to) {
          if (main->parameters.remaining.used < 3) {
            control_print_error_parameter_action_rule_too_few_with(main, data->argv[main->parameters.remaining.array[0]], control_at_s);

            return F_status_set_error(F_parameter);
          }

          if (main->parameters.remaining.used > 3) {
            control_print_error_parameter_action_rule_too_many_with(main, data->argv[main->parameters.remaining.array[0]], control_at_s);

            return F_status_set_error(F_parameter);
          }
        }
        else if (fl_string_dynamic_compare(control_in_s, data->argv[main->parameters.remaining.array[1]]) == F_equal_to) {
          if (main->parameters.remaining.used < 4) {
            control_print_error_parameter_action_rule_too_few_with(main, data->argv[main->parameters.remaining.array[0]], control_in_s);

            return F_status_set_error(F_parameter);
          }
        }
        else if (fl_string_dynamic_compare(control_now_s, data->argv[main->parameters.remaining.array[1]]) == F_equal_to) {
          if (main->parameters.remaining.used > 2) {
            control_print_error_parameter_action_rule_too_many_with(main, data->argv[main->parameters.remaining.array[0]], control_now_s);

            return F_status_set_error(F_parameter);
          }
        }
        else {
          control_print_error_parameter_action_rule_with_unknown(main, data->argv[main->parameters.remaining.array[0]], data->argv[main->parameters.remaining.array[1]]);

          return F_status_set_error(F_parameter);
        }
    }

    return F_none;
  }
#endif // _di_control_action_verify_

#ifndef _di_control_packet_build_
  f_status_t control_packet_build(const fll_program_data_t * const main, control_data_t * const data) {

    data->cache.packet.used = 0;
    data->cache.large.used = 0;
    data->cache.small.used = 0;

    f_array_length_t i = 0;
    f_status_t status = F_none;

    {
      f_array_length_t length = 5 + f_fss_header_s.used + f_fss_payload_s.used;
      length += control_action_s.used + control_length_s.used + control_type_s.used;
      length += (f_fss_payload_list_open_s.used + f_fss_payload_list_close_s.used) * 2;
      length += (f_fss_payload_header_open_s.used + f_fss_payload_header_close_s.used) * 3;
      length += data->argv[main->parameters.remaining.array[0]].used + f_string_ascii_0_s.used;

      // @todo This should properly handle escaping the FSS-0001 (Extended) Content and then count that length.
      for (i = 1; i < main->parameters.remaining.used; ++i) {
        length += f_fss_payload_header_next_s.used + data->argv[main->parameters.remaining.array[i]].used;
      } // for

      if (data->action == control_action_type_kexec_e || data->action == control_action_type_reboot_e || data->action == control_action_type_shutdown_e) {
        length += control_init_s.used;
      }
      else {
        length += control_controller_s.used;
      }

      if (length > 0xffffffffu) {
        return F_status_set_error(F_too_large);
      }

      status = f_string_dynamic_resize(length, &data->cache.packet);
      if (F_status_is_error(status)) return status;
    }

    const f_state_t state = macro_f_state_t_initialize(control_allocation_large_d, control_allocation_small_d, 0, 0, &fll_program_standard_signal_state, 0, (void *) main, 0);

    f_string_static_t contents_array[main->parameters.remaining.used];
    f_string_statics_t contents = macro_f_string_statics_t_initialize(contents_array, 0, main->parameters.remaining.used);

    // The Packet Control Block.
    {
      f_char_t block_control = (f_char_t) control_packet_flag_binary_d;

      #ifdef _is_F_endian_big
        block_control |= (f_char_t) control_packet_flag_endian_big_d;
      #endif // _is_F_endian_big

      status = f_string_append(&block_control, 1, &data->cache.packet);
      if (F_status_is_error(status)) return status;
    }

    // Reserve the Packet Size Block to be calculated later.
    data->cache.packet.used = 5;

    // Payload Header: type.
    if (data->action == control_action_type_kexec_e || data->action == control_action_type_reboot_e || data->action == control_action_type_shutdown_e) {
      contents_array[0] = control_init_s;
    }
    else {
      contents_array[0] = control_controller_s;
    }

    contents.used = 1;

    status = fll_fss_extended_write(control_type_s, contents, 0, state, &data->cache.large);
    if (F_status_is_error(status)) return status;

    // Payload Header: action.
    for (contents.used = 0; contents.used < main->parameters.remaining.used; ++contents.used) {
      contents_array[contents.used] = data->argv[main->parameters.remaining.array[contents.used]];
    } // for

    status = fll_fss_extended_write(control_action_s, contents, 0, state, &data->cache.large);
    if (F_status_is_error(status)) return status;

    // Payload Header: length.
    contents_array[0] = f_string_ascii_0_s;
    contents.used = 1;

    status = fll_fss_extended_write(control_length_s, contents, 0, state, &data->cache.large);
    if (F_status_is_error(status)) return status;

    // Payload Packet: Header.
    status = fll_fss_payload_write(f_fss_header_s, data->cache.large, F_false, 0, state, &data->cache.packet);
    if (F_status_is_error(status)) return status;

    // Payload Packet: Payload.
    data->cache.large.used = 0;

    status = fll_fss_payload_write(f_fss_payload_s, data->cache.large, F_false, 0, state, &data->cache.packet);
    if (F_status_is_error(status)) return status;

    // Construct Packet Size Block.
    #ifdef _is_F_endian_big
      data->cache.packet.string[1] = data->cache.packet.used & 0xffu;
      data->cache.packet.string[2] = data->cache.packet.used & 0xff00u;
      data->cache.packet.string[3] = data->cache.packet.used & 0xff0000u;
      data->cache.packet.string[4] = data->cache.packet.used & 0xff000000u;
    #else
      data->cache.packet.string[1] = data->cache.packet.used & 0xff000000u;
      data->cache.packet.string[2] = data->cache.packet.used & 0xff0000u;
      data->cache.packet.string[3] = data->cache.packet.used & 0xff00u;
      data->cache.packet.string[4] = data->cache.packet.used & 0xffu;
    #endif // _is_F_endian_big

    return F_none;
  }
#endif // _di_control_packet_build_

#ifndef _di_control_packet_header_flag_
  uint8_t control_packet_header_flag(const uint8_t buffer[]) {
    return (uint8_t) (((buffer[0] & 0x8u) ? control_packet_flag_binary_d : 0) | ((buffer[0] & 0x4u) ? control_packet_flag_endian_big_d : 0));
  }
#endif // _di_control_packet_header_flag_

#ifndef _di_control_packet_header_length_
  uint32_t control_packet_header_length(const bool is_big, const uint8_t buffer[]) {

    #ifdef _is_F_endian_big
      if (is_big) {
        return (buffer[1] << 24u) | (buffer[2] << 16u) | (buffer[3] << 8u) | buffer[4];
      }
    #else
      if (!is_big) {
        return (buffer[1] << 24u) | (buffer[2] << 16u) | (buffer[3] << 8u) | buffer[4];
      }
    #endif // _is_F_endian_big

    return (buffer[4] << 24u) | (buffer[3] << 16u) | (buffer[2] << 8u) | buffer[1];
  }
#endif // _di_control_packet_header_length_

#ifndef _di_control_packet_receive_
  f_status_t control_packet_receive(const fll_program_data_t * const main, control_data_t * const data, control_payload_header_t * const header) {

    data->cache.large.used = 0;
    data->cache.small.used = 0;
    data->cache.packet.used = 0;
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

      // Only the first two bits of the 8 Control bits are allowed to be set to 1 for this Packet.
      if (head[0] & (~(control_packet_flag_binary_d | control_packet_flag_endian_big_d))) {
        return F_status_set_error(F_packet_not);
      }

      length = control_packet_header_length(head[0] & control_packet_flag_endian_big_d, head);

      if (length > 0xffffffffu) {
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
      f_state_t state = macro_f_state_t_initialize(control_allocation_large_d, control_allocation_small_d, 0, 0, &fll_program_standard_signal_state, 0, (void *) main, 0);
      f_string_range_t range_packet = macro_f_string_range_t_initialize2(data->cache.large.used);

      status = fll_fss_basic_list_read(data->cache.large, state, &range_packet, &data->cache.packet_objects, &data->cache.packet_contents, &data->cache.delimits, 0, 0);

      if (F_status_is_error(status)) {
        control_print_debug_packet_message(main, "Failure while reading FSS Basic List in the response packet", 0, 0, &status);

        if (F_status_set_fine(status) == F_memory_not) {
          return status;
        }

        return F_status_set_error(F_header);
      }

      status = f_fss_apply_delimit(state, data->cache.delimits, &data->cache.large);

      if (F_status_is_error(status)) {
        control_print_debug_packet_message(main, "Failure while processing delimits for the FSS Basic List in the response packet", 0, 0, &status);

        return F_status_set_error(F_header);
      }

      data->cache.delimits.used = 0;

      {
        f_string_ranges_t *content_header = 0;
        f_string_ranges_t *content_payload = 0;

        for (; i < data->cache.packet_objects.used; ++i) {

          if (fl_string_dynamic_partial_compare_string(f_fss_header_s.string, data->cache.large, f_fss_header_s.used, data->cache.packet_objects.array[i]) == F_equal_to) {

            // The FSS-000E (Payload) standard does not prohibit multiple "header", but such cases are not supported by the controller and the control programs.
            if (content_header) {
              control_print_debug_packet_message(main, "Multiple %[" F_fss_header_s "%] found in response packet", 0, 0, 0);

              return F_status_set_error(F_payload_not);
            }

            content_header = &data->cache.packet_contents.array[i];
          }
          else if (fl_string_dynamic_partial_compare_string(f_fss_payload_s.string, data->cache.large, f_fss_payload_s.used, data->cache.packet_objects.array[i]) == F_equal_to) {

            // Only a single "payload" is supported by the FSS-000E (Payload) standard.
            if (content_payload) {
              control_print_debug_packet_message(main, "Multiple %[" F_fss_payload_s "%] found in response packet", 0, 0, 0);

              return F_status_set_error(F_payload_not);
            }

            if (i + 1 < data->cache.packet_contents.used) {
              control_print_debug_packet_message(main, "Invalid FSS Payload format, the %[" F_fss_payload_s "%] is required to be the last FSS Basic List Object", 0, 0, 0);

              return F_status_set_error(F_payload_not);
            }

            content_payload = &data->cache.packet_contents.array[i];
          }
        } // for

        if (!content_header) {
          control_print_debug_packet_message(main, "Did not find a %[" F_fss_header_s "%] in the response packet", 0, 0, 0);

          return F_status_set_error(F_payload_not);
        }

        if (!content_payload) {
          control_print_debug_packet_message(main, "Did not find a %[" F_fss_payload_s "%] in the response packet", 0, 0, 0);

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

        status = f_fss_apply_delimit(state, data->cache.delimits, &data->cache.large);

        if (F_status_is_error(status)) {
          control_print_debug_packet_message(main, "Failure while processing delimits for the FSS Basic List in the response packet", 0, 0, &status);

          return F_status_set_error(F_header_not);
        }

        if (!data->cache.header_contents.used) {
          control_print_debug_packet_message(main, "Did not find any Content within the %[" F_fss_header_s "%]", 0, 0, 0);

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

              header->action = control_action_type_identify(action);

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

              status = fl_conversion_dynamic_partial_to_unsigned_detect(fl_conversion_data_base_10_c, data->cache.large, data->cache.header_contents.array[i].array[0], &number);

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
              status = fl_conversion_dynamic_partial_to_unsigned_detect(fl_conversion_data_base_10_c, data->cache.large, data->cache.header_contents.array[i].array[0], &number);

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
  f_status_t control_packet_process(const fll_program_data_t * const main, control_data_t * const data, control_payload_header_t * const header) {

    f_string_static_t string_status = f_string_static_t_initialize;

    {
      const f_status_t status = f_status_string_to(header->status, &string_status);

      if (F_status_is_error(status)) {
        control_print_warning_packet_process_string_to_failed(main, header->status, status);
      }
    }

    if (main->parameters.array[control_parameter_return_e].result & f_console_result_found_e) {
      fll_print_format("%rresponse %q %q %q%r", main->output.to, f_string_eol_s, control_payload_type_name(header->type), control_action_type_name(header->action), string_status, f_string_eol_s);
    }
    else if (header->type == control_payload_type_error_e) {
      control_print_error_packet_response(main, data, *header, string_status);
    }
    else if (header->status == F_failure || header->status == F_busy || header->status == F_done || header->status == F_success) {
      control_print_controller_packet_response(main, data, *header, string_status);
    }
    else {

      // Set type to 0 to inform the caller to handle this error.
      header->type = 0;

      return F_status_set_error(F_known_not);
    }

    if (header->type == control_payload_type_error_e || header->status == F_failure || header->status == F_busy) {
      return F_status_set_error(header->status);
    }

    return header->status;
  }
#endif // _di_control_packet_process_

#ifndef _di_control_packet_send_
  f_status_t control_packet_send(const fll_program_data_t * const main, control_data_t * const data) {

    data->socket.size_write = data->cache.packet.used;

    return f_socket_write(&data->socket, 0, (void *) &data->cache.packet, 0);
  }
#endif // _di_control_packet_send_

#ifndef _di_control_settings_load_
  f_status_t control_settings_load(const fll_program_data_t * const main, control_data_t * const data) {

    f_status_t status = F_none;

    data->cache.small.used = 0;

    if (main->parameters.array[control_parameter_settings_e].result & f_console_result_value_e) {
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

      f_file_stream_flush(file);
      f_file_stream_close(&file);

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
      status = f_fss_apply_delimit(state, delimits, &data->cache.large);

      if (F_status_is_error(status)) {
        fll_error_file_print(main->error, F_status_set_fine(status), "f_fss_apply_delimit", F_true, data->cache.small, f_file_operation_process_s, fll_error_file_type_file_e);
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

      if (main->parameters.array[control_parameter_socket_e].result & f_console_result_value_e) {
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
        if (main->parameters.array[control_parameter_socket_e].result & f_console_result_value_e || !parameter_hass[1]) {
          fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_append", F_true);
        }
        else {
          fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);
        }
      }

      status = f_file_exists(data->cache.small, F_true);

      if (F_status_is_error(status) || status == F_false) {
        if (F_status_is_error(status)) {
          fll_error_file_print(main->error, F_status_set_fine(status), "f_file_exists", F_true, data->cache.small, f_file_operation_find_s, fll_error_file_type_directory_e);

          if (main->error.verbosity > f_console_verbosity_quiet_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->error.to);
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

            if (append_ids[i] && main->parameters.array[append_ids[i]].result & f_console_result_value_e) {
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
              if ((append_ids[i] && main->parameters.array[append_ids[i]].result & f_console_result_value_e) || !append_hass[i]) {
                fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_append", F_true);
              }
              else {
                fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);
              }

              break;
            }
          } // for

          if (F_status_is_error_not(status)) {
            status = f_file_exists(data->cache.small, F_true);

            if (F_status_is_error(status) || status == F_false) {
              if (F_status_is_error(status)) {
                fll_error_file_print(main->error, F_status_set_fine(status), "f_file_exists", F_true, data->cache.small, f_file_operation_find_s, fll_error_file_type_directory_e);

                if (main->error.verbosity > f_console_verbosity_quiet_e) {
                  fll_print_dynamic_raw(f_string_eol_s, main->error.to);
                }
              }

              control_print_error_socket_file_missing(main, data->cache.small);

              status = F_status_set_error(F_socket_not);
            }
          }
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

          control_print_error_socket_file_failed(main, data->cache.small);
        }
      }

      if (F_status_is_error_not(status)) {
        status = f_socket_connect(data->socket);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "f_socket_connect", F_true);

          control_print_error_socket_file_failed(main, data->cache.small);
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
