#include "controller.h"
#include "private-common.h"
#include "private-control.h"
#include "private-controller_print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_control_configure_client_
  f_status_t controller_control_configure_client(const controller_global_t *global, f_socket_t * const client) {

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
  f_status_t controller_control_configure_server(const controller_global_t *global, f_socket_t * const server) {

    struct linger value = { 1, 1 };

    f_status_t status = f_socket_option_set(server, controller_control_default_socket_linger_d, f_socket_option_linger_d, (void *) &value, sizeof(struct linger));

    if (F_status_is_error(status)) {
      controller_print_error(global->thread, global->main->error, F_status_set_fine(status), "f_socket_option_set", F_true);
    }

    return status;
  }
#endif // _di_controller_control_configure_server_

#ifndef _di_controller_control_accept_
  f_status_t controller_control_accept(const controller_global_t *global, f_socket_t * const server, controller_packet_t * const packet) {

    f_socket_t client = f_socket_t_initialize;

    f_status_t status = f_socket_accept(&client, server->id);

    if (F_status_is_error(status)) {
      f_socket_disconnect(&client, f_socket_close_read_write_e);

      controller_print_error(global->thread, global->main->error, F_status_set_fine(status), "f_socket_accept", F_true);

      return status;
    }

    controller_control_configure_client(global, &client);

    char buffer[controller_control_default_socket_buffer_d + 1];
    size_t length = 0;

    memset(buffer, 0, controller_control_default_socket_buffer_d + 1);
    packet->payload.used = 0;

    // Pre-process the packet header.
    client.size_read = controller_control_default_socket_header_d;
    status = f_socket_read(&client, f_socket_flag_peek_d, buffer, &length);

    if (F_status_is_error(status)) {
      f_socket_disconnect(&client, f_socket_close_read_write_e);

      controller_print_error(global->thread, global->main->error, F_status_set_fine(status), "f_socket_read", F_true);

      return status;
    }

    client.size_read = controller_control_default_socket_buffer_d;

    // Get all remaining data.
    //while (???) { // until done, based on expected length that should be described in the packet header.
      //message_length = recv(&client, buffer, input_size, receive_flags);

    //} // while

    // process the data.

    // send any responses.
    // sent = send(&client, packet, output_size, send_flags);

    f_socket_disconnect(&client, f_socket_close_read_write_e);

    return F_none;
  }
#endif // _di_controller_control_accept_

#ifdef __cplusplus
} // extern "C"
#endif
