#include "../controller.h"
#include "../common/private-common.h"
#include "private-control.h"
#include "../controller/private-controller_print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_control_accept_
  f_status_t controller_control_accept(const controller_global_t * const global, controller_control_t * const control) {

    /*if (control->client.id != -1) {
      f_socket_disconnect(&control->client, f_socket_close_fast_e);

      control->client.id = -1;
    }*/

    printf("\nDEBUG: begin client accept, addr=%ul, server id = %i, client id = %i\n", control->client, control->server.id, control->client.id);
    fll_print_format("\nDEBUG: begin client accept, addr=%ul, server id = %i, client id = %i\n", stdout, control->client, control->server.id, control->client.id);

    f_status_t status = f_socket_accept(&control->client, control->server.id);
    printf("\nDEBUG: client accept, at 1, status = %d\n", F_status_set_fine(status));

    if (F_status_is_error(status)) {
      f_socket_disconnect(&control->client, f_socket_close_fast_e);

      controller_print_error(global->thread, global->main->error, F_status_set_fine(status), "f_socket_accept", F_true);

      return status;
    }

    controller_control_configure_client(global, &control->client);

    control->input.used = 0;
    control->output.used = 0;

    unsigned char buffer[controller_control_default_socket_buffer_d + 1];
    size_t length = 0;

    memset(buffer, 0, sizeof(unsigned char) * (controller_control_default_socket_buffer_d + 1));

    // Pre-process the packet header.
    control->client.size_read = controller_control_default_socket_header_d;
    status = f_socket_read(&control->client, f_socket_flag_peek_d, buffer, &length);
    printf("\nDEBUG: client accept, at 2, status = %d\n", F_status_set_fine(status));

    if (F_status_is_error(status)) {
      f_socket_disconnect(&control->client, f_socket_close_fast_e);

      controller_print_error(global->thread, global->main->error, F_status_set_fine(status), "f_socket_read", F_true);

      return status;
    }

    if (!length) {
      status = controller_control_respond_error_string(global, control, F_empty, "Received packet is empty.");
      printf("\nDEBUG: client accept, at 3, status = %d\n", F_status_set_fine(status));

      f_socket_disconnect(&control->client, f_socket_close_fast_e);

      if (F_status_is_error(status)) return status;

      return F_valid_not;
    }

    if (length < controller_control_default_socket_header_d) {
      status = controller_control_respond_error_string(global, control, F_too_large, "Received packet is too small.");
      printf("\nDEBUG: client accept, at 4, status = %d\n", F_status_set_fine(status));

      f_socket_disconnect(&control->client, f_socket_close_fast_e);

      if (F_status_is_error(status)) return status;

      return F_valid_not;
    }

    if (length > controller_control_default_socket_buffer_max_d) {
      status = controller_control_respond_error_string(global, control, F_too_large, "Received packet is too large.");
      printf("\nDEBUG: client accept, at 5, status = %d\n", F_status_set_fine(status));

      f_socket_disconnect(&control->client, f_socket_close_fast_e);

      if (F_status_is_error(status)) return status;

      return F_valid_not;
    }

    // @todo rewrite based on control_payload_build(), but need to pre-process what is needed for the payload.
    const uint8_t packet_flag = controller_control_packet_header_flag(buffer);
    const uint32_t packet_length = controller_control_packet_header_length(packet_flag & controller_control_packet_flag_endian_big_d, buffer);

    if (packet_flag & controller_control_packet_flag_binary_d) {
      status = controller_control_respond_error_string(global, control, F_supported_not, "Binary is not a currently supported packet mode.");
      printf("\nDEBUG: client accept, at 6, status = %d\n", F_status_set_fine(status));

      f_socket_disconnect(&control->client, f_socket_close_fast_e);

      if (F_status_is_error(status)) return status;

      return F_supported_not;
    }

    control->client.size_read = controller_control_default_socket_buffer_d;

    // Pre-allocate the input buffer.
    status = f_string_dynamic_increase_by(packet_length, &control->input);

    if (F_status_is_error(status)) {
      controller_control_respond_error_string(global, control, F_memory_not, "Failure allocating memory.");

      f_socket_disconnect(&control->client, f_socket_close_fast_e);

      controller_print_error(global->thread, global->main->error, F_status_set_fine(status), "f_string_dynamic_increase_by", F_true);

      return status;
    }

    {
      size_t total = 0;

      do {
        status = f_socket_read(&control->client, 0, &control->input, &total);
      printf("\nDEBUG: client accept, at 7, status = %d\n", F_status_set_fine(status));

        if (F_status_is_error(status)) {
          controller_control_respond_error_string(global, control, F_status_set_fine(status), "Failure while reading from control->client socket.");

          f_socket_disconnect(&control->client, f_socket_close_fast_e);

          return F_status_set_fine(status);
        }

      } while (total == control->client.size_read);
    }

    if (control->input.used != length) {
      controller_control_respond_error_string(global, control, F_valid_not, "Received packet header length did not match actual received packet length.");

      f_socket_disconnect(&control->client, f_socket_close_fast_e);

      return F_valid_not;
    }

    // @todo process the data.
    fll_print_format("\nDEBUG: received packet: '%q'\n", stdout, control->input);

    // @todo send any responses.

    f_socket_disconnect(&control->client, f_socket_close_fast_e);

    // Resize memory when the allocated size is greate than the maximum preferred size.
    // Resizing could potentially copy memory to a new address, so it is assumed to be cheaper to just delete the memory entirely.
    if (control->input.size > controller_control_default_socket_buffer_d) {
      status = f_string_dynamic_resize(0, &control->input);

      if (F_status_is_error(status)) {
        controller_print_error(global->thread, global->main->error, F_status_set_fine(status), "f_string_dynamic_resize", F_true);

        return status;
      }
    }

    if (control->output.size > controller_control_default_socket_buffer_d) {
      status = f_string_dynamic_resize(0, &control->output);

      if (F_status_is_error(status)) {
        controller_print_error(global->thread, global->main->error, F_status_set_fine(status), "f_string_dynamic_resize", F_true);

        return status;
      }
    }

    return F_none;
  }
#endif // _di_controller_control_accept_

#ifndef _di_controller_control_configure_client_
  f_status_t controller_control_configure_client(const controller_global_t * const global, f_socket_t * const client) {

    struct timeval time_out;
    time_out.tv_sec = 0;
    time_out.tv_usec = controller_control_default_socket_timeout_d;

    f_status_t status = f_socket_option_set(client, 1, f_socket_option_time_out_receive_d, (void *) &time_out, sizeof(struct timeval));

    if (F_status_is_error_not(status)) {
      status = f_socket_option_set(client, 1, f_socket_option_time_out_send_d, (void *) &time_out, sizeof(struct timeval));
    }

    if (F_status_is_error(status)) {
      controller_print_error(global->thread, global->main->error, F_status_set_fine(status), "f_socket_option_set", F_true);
    }

    return status;
  }
#endif // _di_controller_control_configure_client_

#ifndef _di_controller_control_configure_server_
  f_status_t controller_control_configure_server(const controller_global_t * const global, f_socket_t * const server) {

    const struct linger value = { 1, controller_control_default_socket_linger_d };

    const f_status_t status = f_socket_option_set(server, 1, f_socket_option_linger_d, (void *) &value, sizeof(struct linger));

    if (F_status_is_error(status)) {
      controller_print_error(global->thread, global->main->error, F_status_set_fine(status), "f_socket_option_set", F_true);
    }

    return status;
  }
#endif // _di_controller_control_configure_server_

#ifndef _di_controller_control_packet_header_flag_
  uint8_t controller_control_packet_header_flag(const unsigned char buffer[]) {
    return (uint8_t) (((buffer[0] & 0x8) ? controller_control_packet_flag_binary_d : 0) | ((buffer[0] & 0x4) ? controller_control_packet_flag_endian_big_d : 0));
  }
#endif // _di_controller_control_packet_header_flag_

#ifndef _di_controller_control_packet_header_length_
  uint32_t controller_control_packet_header_length(const bool is_big, const unsigned char buffer[]) {

    register uint32_t length = (((buffer[0] & 0x3f) << 26) | (buffer[1] << 18) | (buffer[2] << 10) | (buffer[3] << 2) | ((buffer[4] & 0xc0) >> 6));

    #ifdef _is_F_endian_big
      if (is_big) {
        return length;
      }
    #else
      if (!is_big) {
        return length;
      }
    #endif // _is_F_endian_big

    length = (length & 0x55555555 << 1) | (length & 0x55555555 >> 1);
    length = (length & 0x33333333 << 2) | (length & 0xcccccccc >> 2);
    length = (length & 0x0f0f0f0f << 4) | (length & 0xf0f0f0f0 >> 4);
    length = (length & 0x00ff00ff << 8) | (length & 0xff00ff00 >> 8);

    return (length & 0x0000ffff << 16) | (length & 0xffff0000 >> 16);
  }
#endif // _di_controller_control_packet_header_length_

#ifndef _di_controller_control_respond_build_header_
  f_status_t controller_control_respond_build_header(const controller_global_t * const global, controller_control_t * const control, const f_string_static_t type, const f_string_static_t status, const f_array_length_t length) {

    f_status_t status2 = F_none;

    const f_state_t state = f_state_t_initialize;
    const f_conversion_data_t data_conversion = macro_f_conversion_data_t_initialize(10, 0, 1);

    f_string_statics_t content = f_string_statics_t_initialize;
    f_string_static_t contents[1];
    content.array = contents;
    content.used = 1;
    content.size = 1;

    control->cache_1.used = 0;
    control->cache_2.used = 0;

    // Header: type.
    if (type.used) {
      contents[0] = type;

      status2 = fll_fss_extended_write_string(controller_type_s, content, 0, state, &control->cache_1);
      if (F_status_is_error(status2)) return status2;
    }

    // Header: status.
    if (status.used) {
      contents[0] = status;

      status2 = fll_fss_extended_write_string(controller_status_s, content, 0, state, &control->cache_1);
      if (F_status_is_error(status2)) return status2;

      control->cache_2.used = 0;
    }

    // Header: length.
    status2 = f_conversion_number_unsigned_to_string(length, data_conversion, &control->cache_2);
    if (F_status_is_error(status2)) return status2;

    contents[0] = control->cache_2;

    status2 = fll_fss_extended_write_string(controller_length_s, content, 0, state, &control->cache_1);
    if (F_status_is_error(status2)) return status2;

    // Prepend the identifier comment to the output.
    status2 = f_string_dynamic_append(controller_payload_type_s, &control->output);
    if (F_status_is_error(status2)) return status2;

    // Append entire header block to the output.
    status2 = fll_fss_payload_write_string(f_fss_string_header_s, control->cache_1, F_false, 0, state, &control->output);
    if (F_status_is_error(status2)) return status2;

    return F_none;
  }
#endif // _di_controller_control_respond_build_header_

#ifndef _di_controller_control_respond_error_
  f_status_t controller_control_respond_error(const controller_global_t * const global, controller_control_t * const control, const f_status_t status, const f_string_static_t message) {

    f_status_t status2 = F_none;

    control->output.used = 0;
    control->cache_3.used = 0;
    printf("\nDEBUG: controller_control_respond_error(), at start\n");

    {
      const f_conversion_data_t data_conversion = macro_f_conversion_data_t_initialize(10, 0, 1);

      status2 = f_conversion_number_unsigned_to_string(F_status_set_fine(status), data_conversion, &control->cache_3);
      if (F_status_is_error(status2)) return status2;
    }

    status2 = controller_control_respond_build_header(global, control, controller_error_s, control->cache_3, message.used);
    if (F_status_is_error(status2)) return status2;

    {
      const f_state_t state = f_state_t_initialize;

      status2 = fll_fss_payload_write_string(f_fss_string_payload_s, message, F_false, 0, state, &control->output);
      if (F_status_is_error(status2)) return status2;
    }

    printf("\nDEBUG: controller_control_respond_error(), before write\n");

    return f_socket_write(&control->client, 0, control->output.string, 0);
  }
#endif // _di_controller_control_respond_error_

#ifndef _di_controller_control_respond_error_string_
  f_status_t controller_control_respond_error_string(const controller_global_t * const global, controller_control_t * const control, const f_status_t status, const f_string_t message) {

    const f_string_static_t string = macro_f_string_static_t_initialize2(message, strlen(message));

    return controller_control_respond_error(global, control, status, string);
  }
#endif // _di_controller_control_respond_error_string_

#ifdef __cplusplus
} // extern "C"
#endif
