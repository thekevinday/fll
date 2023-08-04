#include "control.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_control_packet_build_
  void control_packet_build(control_main_t * const main) {

    if (!main) return;

    main->cache.packet.used = 0;
    main->cache.large.used = 0;
    main->cache.small.used = 0;

    f_number_unsigned_t i = 0;

    {
      f_number_unsigned_t length = 5 + f_fss_header_s.used + f_fss_payload_s.used;
      length += control_action_s.used + control_length_s.used + control_type_s.used;
      length += (f_fss_payload_list_open_s.used + f_fss_payload_list_close_s.used) * 2;
      length += (f_fss_payload_header_open_s.used + f_fss_payload_header_close_s.used) * 3;
      length += main->setting.actions.array[0].used + f_string_ascii_0_s.used;

      // @todo This should properly handle escaping the FSS-0001 (Extended) Content and then count that length.
      for (i = 1; i < main->setting.actions.used; ++i) {
        length += f_fss_payload_header_next_s.used + main->setting.actions.array[i].used;
      } // for

      if (main->setting.action == control_action_type_kexec_e || main->setting.action == control_action_type_reboot_e || main->setting.action == control_action_type_shutdown_e) {
        length += control_init_s.used;
      }
      else {
        length += control_controller_s.used;
      }

      if (length > 0xffffffffu) {
        main->setting.state.status = F_status_set_error(F_too_large);

        return;
      }

      main->setting.state.status = f_string_dynamic_resize(length, &main->cache.packet);
      if (F_status_is_error(main->setting.state.status)) return;
    }

    f_state_t state = macro_f_state_t_initialize_1(control_allocation_large_d, control_allocation_small_d, F_none, 0, 0, 0, &fll_program_standard_signal_handle, 0, (void *) main, 0);

    f_string_static_t contents_array[main->setting.actions.used];
    f_string_statics_t contents = macro_f_string_statics_t_initialize_1(contents_array, 0, main->setting.actions.used);

    // The Packet Control Block.
    {
      f_char_t block_control = (f_char_t) control_packet_flag_binary_d;

      #ifdef _is_F_endian_big
        block_control |= (f_char_t) control_packet_flag_endian_big_d;
      #endif // _is_F_endian_big

      main->setting.state.status = f_string_append(&block_control, 1, &main->cache.packet);
      if (F_status_is_error(main->setting.state.status)) return;
    }

    // Reserve the Packet Size Block to be calculated later.
    main->cache.packet.used = 5;

    // Payload Header: type.
    if (main->setting.action == control_action_type_kexec_e || main->setting.action == control_action_type_reboot_e || main->setting.action == control_action_type_shutdown_e) {
      contents_array[0] = control_init_s;
    }
    else {
      contents_array[0] = control_controller_s;
    }

    contents.used = 1;

    fll_fss_extended_write(control_type_s, contents, 0, &main->cache.large, &state);

    // Payload Header: action.
    if (F_status_is_error_not(state.status)) {
      for (contents.used = 0; contents.used < main->setting.actions.used; ++contents.used) {
        contents_array[contents.used] = main->setting.actions.array[contents.used];
      } // for

      fll_fss_extended_write(control_action_s, contents, 0, &main->cache.large, &state);
    }

    // Payload Header: length.
    if (F_status_is_error_not(state.status)) {
      contents_array[0] = f_string_ascii_0_s;
      contents.used = 1;

      fll_fss_extended_write(control_length_s, contents, 0, &main->cache.large, &state);
    }

    // Payload Packet: Header.
    if (F_status_is_error_not(state.status)) {
      fll_fss_payload_write(f_fss_header_s, main->cache.large, F_false, 0, &main->cache.packet, &state);
    }

    // Payload Packet: Payload.
    if (F_status_is_error_not(state.status)) {
      main->cache.large.used = 0;

      fll_fss_payload_write(f_fss_payload_s, main->cache.large, F_false, 0, &main->cache.packet, &state);
    }

    if (F_status_is_error(state.status)) {
      main->setting.state.status = state.status;

      return;
    }

    // Construct Packet Size Block.
    #ifdef _is_F_endian_big
      main->cache.packet.string[1] = main->cache.packet.used & 0xffu;
      main->cache.packet.string[2] = main->cache.packet.used & 0xff00u;
      main->cache.packet.string[3] = main->cache.packet.used & 0xff0000u;
      main->cache.packet.string[4] = main->cache.packet.used & 0xff000000u;
    #else
      main->cache.packet.string[1] = main->cache.packet.used & 0xff000000u;
      main->cache.packet.string[2] = main->cache.packet.used & 0xff0000u;
      main->cache.packet.string[3] = main->cache.packet.used & 0xff00u;
      main->cache.packet.string[4] = main->cache.packet.used & 0xffu;
    #endif // _is_F_endian_big

    main->setting.state.status = F_none;
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
      if (is_big) return (buffer[1] << 24u) | (buffer[2] << 16u) | (buffer[3] << 8u) | buffer[4];
    #else
      if (!is_big) return (buffer[1] << 24u) | (buffer[2] << 16u) | (buffer[3] << 8u) | buffer[4];
    #endif // _is_F_endian_big

    return (buffer[4] << 24u) | (buffer[3] << 16u) | (buffer[2] << 8u) | buffer[1];
  }
#endif // _di_control_packet_header_length_

#ifndef _di_control_packet_receive_
  void control_packet_receive(control_main_t * const main, control_payload_header_t * const header) {

    if (!main || !header) return;

    main->cache.large.used = 0;
    main->cache.small.used = 0;
    main->cache.packet.used = 0;
    main->cache.packet_objects.used = 0;
    main->cache.packet_contents.used = 0;
    main->cache.header_objects.used = 0;
    main->cache.header_contents.used = 0;
    main->cache.delimits.used = 0;

    header->action = 0;
    header->type = 0;
    header->status = F_none;
    header->length = 0;

    f_number_unsigned_t i = 0;
    f_string_range_t range_header = f_string_range_t_initialize;
    f_string_range_t range_payload = f_string_range_t_initialize;

    {
      f_number_unsigned_t length = 5;
      uint8_t head[length];

      memset(head, 0, sizeof(uint8_t) * length);

      main->setting.state.status = f_socket_read(&main->setting.socket, f_socket_flag_peek_e, (void *) head, &length);
      if (F_status_is_error(main->setting.state.status)) return;

      if (length < 5) {
        main->setting.state.status = F_status_set_error(F_packet_not);

        return;
      }

      // Only the first two bits of the 8 Control bits are allowed to be set to 1 for this Packet.
      if (head[0] & (~(control_packet_flag_binary_d | control_packet_flag_endian_big_d))) {
        main->setting.state.status = F_status_set_error(F_packet_not);

        return;
      }

      length = control_packet_header_length(head[0] & control_packet_flag_endian_big_d, head);

      if (length > 0xffffffffu) {
        main->setting.state.status = F_status_set_error(F_too_large);

        return;
      }

      main->setting.state.status = f_string_dynamic_increase_by(length, &main->cache.large);
      if (F_status_is_error(main->setting.state.status)) return;

      main->setting.state.status = f_socket_read(&main->setting.socket, f_socket_flag_wait_all_e, (void *) head, &length);
      if (F_status_is_error(main->setting.state.status)) return;

      if (length < main->cache.large.used) {
        main->setting.state.status = F_status_set_error(F_too_small);

        return;
      }

      if (length > main->cache.large.used) {
        main->setting.state.status = F_status_set_error(F_too_large);

        return;
      }
    }

    {
      f_state_t state = macro_f_state_t_initialize_1(control_allocation_large_d, control_allocation_small_d, F_none, 0, 0, 0, &fll_program_standard_signal_handle, 0, (void *) main, 0);
      f_string_range_t range_packet = macro_f_string_range_t_initialize_2(main->cache.large.used);

      fll_fss_basic_list_read(main->cache.large, &range_packet, &main->cache.packet_objects, &main->cache.packet_contents, &main->cache.delimits, 0, 0, &state);

      if (F_status_is_error(main->setting.state.status)) {
        control_print_debug_packet_message(&main->program.debug, "Failure while reading FSS Basic List in the response packet", 0, 0);

        if (F_status_set_fine(main->setting.state.status) == F_memory_not) return;

        main->setting.state.status = F_status_set_error(F_header);

        return;
      }

      f_fss_apply_delimit(main->cache.delimits, &main->cache.large, &state);

      if (F_status_is_error(state.status)) {
        main->setting.state.status = state.status;

        control_print_debug_packet_message(&main->program.debug, "Failure while processing delimits for the FSS Basic List in the response packet", 0, 0);

        main->setting.state.status = F_status_set_error(F_header);

        return;
      }

      main->cache.delimits.used = 0;

      {
        f_string_ranges_t *content_header = 0;
        f_string_ranges_t *content_payload = 0;

        for (; i < main->cache.packet_objects.used; ++i) {

          if (f_compare_dynamic_partial_string(f_fss_header_s.string, main->cache.large, f_fss_header_s.used, main->cache.packet_objects.array[i]) == F_equal_to) {

            // The FSS-000E (Payload) standard does not prohibit multiple "header", but such cases are not supported by the controller and the control programs.
            if (content_header) {
              control_print_debug_packet_message(&main->program.debug, "Multiple %[" F_fss_header_s "%] found in response packet", 0, 0);

              main->setting.state.status = F_status_set_error(F_payload_not);

              return;
            }

            content_header = &main->cache.packet_contents.array[i];
          }
          else if (f_compare_dynamic_partial_string(f_fss_payload_s.string, main->cache.large, f_fss_payload_s.used, main->cache.packet_objects.array[i]) == F_equal_to) {

            // Only a single "payload" is supported by the FSS-000E (Payload) standard.
            if (content_payload) {
              control_print_debug_packet_message(&main->program.debug, "Multiple %[" F_fss_payload_s "%] found in response packet", 0, 0);

              main->setting.state.status = F_status_set_error(F_payload_not);

              return;
            }

            if (i + 1 < main->cache.packet_contents.used) {
              control_print_debug_packet_message(&main->program.debug, "Invalid FSS Payload format, the %[" F_fss_payload_s "%] is required to be the last FSS Basic List Object", 0, 0);

              main->setting.state.status = F_status_set_error(F_payload_not);

              return;
            }

            content_payload = &main->cache.packet_contents.array[i];
          }
        } // for

        if (!content_header) {
          control_print_debug_packet_message(&main->program.debug, "Did not find a %[" F_fss_header_s "%] in the response packet", 0, 0);

          main->setting.state.status = F_status_set_error(F_payload_not);

          return;
        }

        if (!content_payload) {
          control_print_debug_packet_message(&main->program.debug, "Did not find a %[" F_fss_payload_s "%] in the response packet", 0, 0);

          main->setting.state.status = F_status_set_error(F_payload_not);

          return;
        }

        range_header = content_header->array[0];
        range_payload = content_payload->array[0];
      }

      {
        // 0x1 = found action, 0x2 = found length, 0x4 = found status, 0x8 = found_type.
        uint8_t found = 0;
        f_number_unsigned_t number = 0;
        f_string_range_t range = range_header;

        fll_fss_extended_read(main->cache.large, &range, &main->cache.header_objects, &main->cache.header_contents, 0, 0, &main->cache.delimits, 0, &state);

        if (F_status_is_error(main->setting.state.status)) {
          control_print_debug_packet_message(&main->program.debug, "Failure while reading FSS Extended in the response packet", 0, 0);

          if (F_status_set_fine(main->setting.state.status) == F_memory_not) return;

          main->setting.state.status = F_status_set_error(F_header_not);

          return;
        }

        f_fss_apply_delimit(main->cache.delimits, &main->cache.large, &state);

        if (F_status_is_error(state.status)) {
          main->setting.state.status = state.status;

          control_print_debug_packet_message(&main->program.debug, "Failure while processing delimits for the FSS Basic List in the response packet", 0, 0);

          main->setting.state.status = F_status_set_error(F_header_not);

          return;
        }

        if (!main->cache.header_contents.used) {
          control_print_debug_packet_message(&main->program.debug, "Did not find any Content within the %[" F_fss_header_s "%]", 0, 0);

          main->setting.state.status = F_status_set_error(F_header_not);

          return;
        }

        for (i = 0; i < main->cache.header_objects.used; ++i) {

          if (f_compare_dynamic_partial_string(control_action_s.string, main->cache.large, control_action_s.used, main->cache.header_objects.array[i]) == F_equal_to) {
            if (!(found & 0x1)) {
              const f_number_unsigned_t action_length = (main->cache.header_contents.array[i].array[0].stop - main->cache.header_contents.array[i].array[0].start) + 1;
              char action_string[action_length + 1];
              const f_string_static_t action = macro_f_string_static_t_initialize_1(action_string, 0, action_length);

              memcpy(action_string, main->cache.large.string + main->cache.header_contents.array[i].array[0].start, action_length);
              action_string[action_length] = 0;

              found |= 0x1;

              control_print_debug_packet_header_object_and_content(&main->program.debug, control_action_s, main->cache.large, main->cache.header_contents.array[i].array[0]);

              header->action = control_action_type_identify(action);

              if (!header->action) {
                control_print_debug_packet_message(&main->program.debug, "Failed to identify %[" CONTROL_action_s "%] from: ", &main->cache.large, &main->cache.header_contents.array[i].array[0]);

                main->setting.state.status = F_status_set_error(F_header_not);

                return;
              }
            }
            else {
              control_print_warning_packet_header_duplicate_object(&main->program.warning, control_action_s);
            }
          }
          else if (f_compare_dynamic_partial_string(control_length_s.string, main->cache.large, control_length_s.used, main->cache.header_objects.array[i]) == F_equal_to) {
            if (!(found & 0x2)) {
              found |= 0x2;
              number = 0;

              control_print_debug_packet_header_object_and_content(&main->program.debug, control_length_s, main->cache.large, main->cache.header_contents.array[i].array[0]);

              main->setting.state.status = fl_conversion_dynamic_partial_to_unsigned_detect(fl_conversion_data_base_10_c, main->cache.large, main->cache.header_contents.array[i].array[0], &number);

              if (F_status_is_error(main->setting.state.status)) {
                control_print_debug_packet_message(&main->program.debug, "Failed to process number for %[" CONTROL_length_s "%] in the response packet, number is:", &main->cache.large, &main->cache.header_contents.array[i].array[0]);

                main->setting.state.status = F_status_set_error(F_header_not);

                return;
              }

              if (number > F_type_size_max_32_unsigned_d) {
                control_print_debug_packet_message(&main->program.debug, "Processed number for %[" CONTROL_length_s "%] exceeds allowed size in the response packet, number is:", &main->cache.large, &main->cache.header_contents.array[i].array[0]);

                main->setting.state.status = F_status_set_error(F_header_not);

                return;
              }

              header->length = (uint16_t) number;
            }
            else {
              control_print_warning_packet_header_duplicate_object(&main->program.warning, control_length_s);
            }
          }
          else if (f_compare_dynamic_partial_string(control_status_s.string, main->cache.large, control_status_s.used, main->cache.header_objects.array[i]) == F_equal_to) {
            if (!(found & 0x4)) {
              found |= 0x4;
              number = 0;

              control_print_debug_packet_header_object_and_content(&main->program.debug, control_status_s, main->cache.large, main->cache.header_contents.array[i].array[0]);

              // Attempt to get packet status as a number.
              main->setting.state.status = fl_conversion_dynamic_partial_to_unsigned_detect(fl_conversion_data_base_10_c, main->cache.large, main->cache.header_contents.array[i].array[0], &number);

              if (F_status_set_fine(main->setting.state.status) == F_number) {

                // Not a number, so attempt get by packet status string name.
                const f_number_unsigned_t name_length = (main->cache.header_contents.array[i].array[0].stop - main->cache.header_contents.array[i].array[0].start) + 1;
                char name_string[name_length + 1];
                const f_string_static_t name = macro_f_string_static_t_initialize_1(name_string, 0, name_length);

                memcpy(name_string, main->cache.large.string + main->cache.header_contents.array[i].array[0].start, name_length);
                name_string[name_length] = 0;

                main->setting.state.status = fl_status_string_from(name, &header->status);

                if (F_status_is_error(main->setting.state.status)) {
                  control_print_debug_packet_message(&main->program.debug, "Failed to process %[" CONTROL_status_s "%] in the response packet, Content is:", &main->cache.large, &main->cache.header_contents.array[i].array[0]);

                  main->setting.state.status = F_status_set_error(F_header_not);

                  return;
                }
              }
              else if (F_status_is_error(main->setting.state.status)) {
                control_print_debug_packet_message(&main->program.debug, "Failed to process number for %[" CONTROL_status_s "%] in the response packet, number is:", &main->cache.large, &main->cache.header_contents.array[i].array[0]);

                if (F_status_set_fine(main->setting.state.status) == F_memory_not) return;

                main->setting.state.status = F_status_set_error(F_header_not);

                return;
              }
              else {
                if (number > F_status_size_max_with_bits_d) {
                  control_print_debug_packet_message(&main->program.debug, "Processed number for %[" CONTROL_status_s "%] exceeds allowed size in the response packet, number is:", &main->cache.large, &main->cache.header_contents.array[i].array[0]);

                  main->setting.state.status = F_status_set_error(F_header_not);

                  return;
                }
              }
            }
            else {
              control_print_warning_packet_header_duplicate_object(&main->program.warning, control_length_s);
            }
          }
          else if (f_compare_dynamic_partial_string(control_type_s.string, main->cache.large, control_type_s.used, main->cache.header_objects.array[i]) == F_equal_to) {
            if (!(found & 0x8)) {
              found |= 0x8;

              control_print_debug_packet_header_object_and_content(&main->program.debug, control_type_s, main->cache.large, main->cache.header_contents.array[i].array[0]);

              if (f_compare_dynamic_partial_string(control_controller_s.string, main->cache.large, control_controller_s.used, main->cache.header_contents.array[i].array[0]) == F_equal_to) {
                header->type = control_payload_type_controller_e;
              }
              else if (f_compare_dynamic_partial_string(control_error_s.string, main->cache.large, control_error_s.used, main->cache.header_contents.array[i].array[0]) == F_equal_to) {
                header->type = control_payload_type_error_e;
              }
              else {
                control_print_debug_packet_message(&main->program.debug, "Unknown %[" CONTROL_type_s "%] in response packet, Content is:", &main->cache.large, &main->cache.header_contents.array[i].array[0]);

                main->setting.state.status = F_status_set_error(F_header_not);

                return;
              }
            }
            else {
              control_print_warning_packet_header_duplicate_object(&main->program.warning, control_type_s);
            }
          }
        }
      }
    }

    main->setting.state.status = F_none;
  }
#endif // _di_control_packet_receive_

#ifndef _di_control_packet_process_
  void control_packet_process(control_main_t * const main, control_payload_header_t * const header) {

    if (!main || !header) return;

    f_string_static_t string_status = f_string_static_t_initialize;

    {
      main->setting.state.status = f_status_string_to(header->status, &string_status);

      if (F_status_is_error(main->setting.state.status)) {
        control_print_warning_packet_process_string_to_failed(&main->program.warning, header->status, main->setting.state.status);

        return;
      }
    }

    if (main->setting.flag & control_main_flag_return_e) {
      fll_print_format("response %q %q %q%r", main->program.output.to, control_payload_type_name(header->type), control_action_type_name(header->action), string_status, f_string_eol_s);
    }
    else if (header->type == control_payload_type_error_e) {
      control_print_error_packet_response(&main->program.error, *header, string_status);
    }
    else if (header->status == F_failure) {
      control_print_error_packet_response_failure(&main->program.error, *header, string_status);
    }
    else if (header->status == F_busy) {
      control_print_warning_packet_response_busy(&main->program.warning, *header, string_status);
    }
    else if (header->status == F_done || header->status == F_success) {
      control_print_message_packet_response(&main->program.output, *header, string_status);
    }
    else {

      // Set type to 0 to inform the caller to handle this error.
      header->type = 0;

      main->setting.state.status = F_status_set_error(F_known_not);

      return;
    }

    if (header->type == control_payload_type_error_e || header->status == F_failure || header->status == F_busy) {
      main->setting.state.status = F_status_set_error(header->status);
    }
    else {
      main->setting.state.status = header->status;
    }
  }
#endif // _di_control_packet_process_

#ifndef _di_control_packet_send_
  void control_packet_send(control_main_t * const main) {

    if (!main) return;

    main->setting.size_write = main->cache.packet.used;

    main->setting.state.status = f_socket_write(&main->setting.socket, 0, (void *) &main->cache.packet, 0);
  }
#endif // _di_control_packet_send_

#ifdef __cplusplus
} // extern "C"
#endif
