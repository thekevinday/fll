/**
 * FLL - Level 0
 *
 * Project: Socket
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines common data to be used for/by project socket.
 *
 * This is auto-included by socket.h and should not need to be explicitly included.
 */
#ifndef _F_socket_common_h
#define _F_socket_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Provide socket defaults.
 *
 * F_file_default_*:
 *   - read_size:  Default read size in bytes.
 *   - write_size: Default write size in bytes.
 */
#ifndef _di_f_socket_defaults_
  #define F_socket_default_read_size_d  8192
  #define F_socket_default_write_size_d 8192
#endif // _di_f_socket_defaults_

/**
 * Socket Closes.
 *
 * f_socket_close_*:
 *   - fast:       Fast Socket close, as in close().
 *   - read:       Read close, as in shutdown(, SHUT_RD).
 *   - read_write: Read/Write close, as in shutdown(, SHUT_RDWR).
 *   - write:      Write close, as in shutdown(, SHUT_WR).
 */
#ifndef _di_f_socket_closes_
  enum {
    f_socket_close_fast_e = 1,
    f_socket_close_read_e,
    f_socket_close_write_e,
    f_socket_close_read_write_e,
  };
#endif // _di_f_socket_closes_

/**
 * Socket protocol families, referred to as a domain.
 *
 * f_socket_domain_*:
 *   - atm:           Raw ATM PVC.
 *   - apple_talk:    Apple Talk.
 *   - cryptographic: Kernel cryptographic API.
 *   - file:          Unix/Local file.
 *   - ipv4:          Internet Protocol v4.
 *   - ipv6:          Internet Protocol v6.
 *   - ipx:           Novell IPX.
 *   - kernel:        Kernel user interface device.
 *   - radio:         Amateur Radio.
 *   - x25:           ITU-T X.25 / ISO-8208 protocol
 */
#ifndef _di_f_socket_domains_
  #define f_socket_domain_apple_talk_d    AF_APPLETALK
  #define f_socket_domain_atm_d           AF_ATMPVC
  #define f_socket_domain_cryptographic_d AF_ALG
  #define f_socket_domain_file_d          AF_UNIX
  #define f_socket_domain_ipv4_d          AF_INET
  #define f_socket_domain_ipv6_d          AF_INET6
  #define f_socket_domain_ipx_d           AF_IPX
  #define f_socket_domain_kernel_d        AF_NETLINK
  #define f_socket_domain_radio_d         AF_AX25
  #define f_socket_domain_x25_d           AF_X25
#endif // _di_f_socket_domains_

/**
 * Socket Options.
 *
 * f_socket_option_*:
 *   - address_reuse:            Re-use address.
 *   - advice_cnx:               CNX Advice.
 *   - bpf_attach:               Attach Berkeley Packet Filter.
 *   - bpf_detach:               Detach Berkeley Packet Filter.
 *   - bpf_extensions:           Berkeley Packet Filter extensions.
 *   - broadcast:                broadcast
 *   - buffer_receive:           Receive buffer.
 *   - buffer_receive_force:     Receive buffer (forced).
 *   - buffer_send:              Send buffer.
 *   - buffer_send_force:        Send buffer (forced).
 *   - cbpf_port_reuse_attach:   Re-use port in C-Berkeley Packet Filter.
 *   - check_not:                Don't check.
 *   - compatibility_bsd:        BSD compatibility.
 *   - connection_accept:        Accept connection.
 *   - cookie:                   Cookie.
 *   - cpu_incoming:             Incomming CPU.
 *   - credentials_pass:         Pass credentials.
 *   - credentials_peer:         Peer credentials.
 *   - debug:                    Debug setting.
 *   - device_bind:              Bind device.
 *   - domain:                   Domain.
 *   - ebpf_port_reuse_attach:   Re-use port in E-Berkeley Packet Filter.
 *   - error:                    Error.
 *   - filter_attach:            Attach filter.
 *   - filter_detach:            Detach Filter.
 *   - filter_get:               Get filter.
 *   - filter_lock:              Lock filter.
 *   - frame_check_sequence_not: No Frame Check Sequence.
 *   - groups_peer:              Peer groups.
 *   - keep_alive:               Keep alive.
 *   - linger:                   Linger.
 *   - low_at_receive:           Low at receive.
 *   - low_at_send:              Low at send.
 *   - mark:                     Mark.
 *   - memory_information:       Memory information.
 *   - name_peer:                Peer name.
 *   - napi_id_incoming:         Incomming NAPI identifier.
 *   - out_of_band_inline:       Inline Out of Band.
 *   - pacing_rate_max:          Max pacing rate.
 *   - peek_off:                 Peek off.
 *   - poll_busy:                Busy poll.
 *   - port_reuse:               Re-use port.
 *   - priority:                 Priority.
 *   - protocol:                 Protocol.
 *   - receive_overflow:         Receive Overflow.
 *   - route_not:                Don't Route.
 *   - security_authentication:  Authentication security.
 *   - security_network:         Network security.
 *   - security_pass:            Pass security.
 *   - security_peer:            Peer security.
 *   - security_transport:       Security transport.
 *   - select_error_queue:       Select error queue.
 *   - time_out_receive:         Receive time out.
 *   - time_out_send:            Send time out.
 *   - time_stamp:               Time stamp.
 *   - time_stamp_namespace:     Time stamp namespace.
 *   - time_stamping:            Time stamping.
 *   - time_stamping_packet:     Time stamping packet.
 *   - time_stamping_stats:      Time stamping statistics.
 *   - time_transmit:            Transmission time.
 *   - type:                     Type.
 *   - wifi_status:              Wifi status.
 *   - zero_copy_d               Zero copy.
 */
#ifndef _di_f_socket_options_
  #define f_socket_option_address_reuse_d            SO_REUSEADDR
  #define f_socket_option_advice_cnx_d               SO_CNX_ADVICE
  #define f_socket_option_bpf_attach_d               SO_ATTACH_BPF
  #define f_socket_option_bpf_detach_d               SO_DETACH_BPF
  #define f_socket_option_bpf_extensions_d           SO_BPF_EXTENSIONS
  #define f_socket_option_broadcast_d                SO_BROADCAST
  #define f_socket_option_buffer_receive_d           SO_RCVBUF
  #define f_socket_option_buffer_receive_force_d     SO_RCVBUFFORCE
  #define f_socket_option_buffer_send_d              SO_SNDBUF
  #define f_socket_option_buffer_send_force_d        SO_SNDBUFFORCE
  #define f_socket_option_cbpf_port_reuse_attach_d   SO_ATTACH_REUSEPORT_CBPF
  #define f_socket_option_check_not_d                SO_NO_CHECK
  #define f_socket_option_compatibility_bsd_d        SO_BSDCOMPAT
  #define f_socket_option_connection_accept_d        SO_ACCEPTCONN
  #define f_socket_option_cookie_d                   SO_COOKIE
  #define f_socket_option_cpu_incoming_d             SO_INCOMING_CPU
  #define f_socket_option_credentials_pass_d         SO_PASSCRED
  #define f_socket_option_credentials_peer_d         SO_PEERCRED
  #define f_socket_option_debug_d                    SO_DEBUG
  #define f_socket_option_device_bind_d              SO_BINDTODEVICE
  #define f_socket_option_domain_d                   SO_DOMAIN
  #define f_socket_option_ebpf_port_reuse_attach_d   SO_ATTACH_REUSEPORT_EBPF
  #define f_socket_option_error_d                    SO_ERROR
  #define f_socket_option_filter_attach_d            SO_ATTACH_FILTER
  #define f_socket_option_filter_detach_d            SO_DETACH_FILTER
  #define f_socket_option_filter_get_d               SO_GET_FILTER
  #define f_socket_option_filter_lock_d              SO_LOCK_FILTER
  #define f_socket_option_frame_check_sequence_not_d SO_NOFCS
  #define f_socket_option_groups_peer_d              SO_PEERGROUPS
  #define f_socket_option_keep_alive_d               SO_KEEPALIVE
  #define f_socket_option_linger_d                   SO_LINGER
  #define f_socket_option_low_at_receive_d           SO_RCVLOWAT
  #define f_socket_option_low_at_send_d              SO_SNDLOWAT
  #define f_socket_option_mark_d                     SO_MARK
  #define f_socket_option_memory_information_d       SO_MEMINFO
  #define f_socket_option_name_peer_d                SO_PEERNAME
  #define f_socket_option_napi_id_incoming_d         SO_INCOMING_NAPI_ID
  #define f_socket_option_out_of_band_inline_d       SO_OOBINLINE
  #define f_socket_option_pacing_rate_max_d          SO_MAX_PACING_RATE
  #define f_socket_option_peek_off_d                 SO_PEEK_OFF
  #define f_socket_option_poll_busy_d                SO_BUSY_POLL
  #define f_socket_option_port_reuse_d               SO_REUSEPORT
  #define f_socket_option_priority_d                 SO_PRIORITY
  #define f_socket_option_protocol_d                 SO_PROTOCOL
  #define f_socket_option_receive_overflow_d         SO_RXQ_OVFL
  #define f_socket_option_route_not_d                SO_DONTROUTE
  #define f_socket_option_security_authentication_d  SO_SECURITY_AUTHENTICATION
  #define f_socket_option_security_network_d         SO_SECURITY_ENCRYPTION_NETWORK
  #define f_socket_option_security_pass_d            SO_PASSSEC
  #define f_socket_option_security_peer_d            SO_PEERSEC
  #define f_socket_option_security_transport_d       SO_SECURITY_ENCRYPTION_TRANSPORT
  #define f_socket_option_select_error_queue_d       SO_SELECT_ERR_QUEUE
  #define f_socket_option_time_out_receive_d         SO_RCVTIMEO
  #define f_socket_option_time_out_send_d            SO_SNDTIMEO
  #define f_socket_option_time_stamp_d               SO_TIMESTAMP
  #define f_socket_option_time_stamp_namespace_d     SO_TIMESTAMPNS
  #define f_socket_option_time_stamping_d            SO_TIMESTAMPING
  #define f_socket_option_time_stamping_packet_d     SCM_TIMESTAMPING_PKTINFO
  #define f_socket_option_time_stamping_stats_d      SCM_TIMESTAMPING_OPT_STATS
  #define f_socket_option_time_transmit_d            SO_TXTIME
  #define f_socket_option_type_d                     SO_TYPE
  #define f_socket_option_wifi_status_d              SO_WIFI_STATUS
  #define f_socket_option_zero_copy_d                SO_ZEROCOPY
#endif // _di_f_socket_options_

/**
 * Socket Flags.
 *
 * These are flags to pass to either socket receive or socket send functions.
 *
 * f_socket_flag_*:
 *   - close_on_exit: Set the close on exit flag for a UNIX socket.
 *   - confirm:       Inform the network layer that "forward process" happened.
 *   - error_queue:   Designate that queue errors should be received from the socket error queue.
 *   - more:          Designate that there is more data to send.
 *   - out_of_band:   Enable receiving out of band data.
 *   - peek:          Process data from the queue without popping it off the stack.
 *   - record_end:    Designate end of record, terminating a sequence.
 *   - route_not:     Do not use a gateway to send this packet.
 *   - signal_not:    Do not send SIGPIPE signal if remote end closed the connection in a stream oriented connection.
 *   - truncate:      Return real length of the packet even if it is truncated to fit into the buffer.
 *   - wait_all:      Block until the full request is satisfied.
 *   - wait_not:      Use non-blocking.
 */
#ifndef _di_f_socket_flags_
  #define f_socket_flag_close_on_exit_d MSG_CMSG_CLOEXEC
  #define f_socket_flag_confirm_d       MSG_CONFIRM
  #define f_socket_flag_error_queue_d   MSG_ERRQUEUE
  #define f_socket_flag_more_d          MSG_MORE
  #define f_socket_flag_out_of_band_d   MSG_OOB
  #define f_socket_flag_peek_d          MSG_PEEK
  #define f_socket_flag_record_end_d    MSG_EOR
  #define f_socket_flag_route_not_d     MSG_DONTROUTE
  #define f_socket_flag_signal_not_d    MSG_NOSIGNAL
  #define f_socket_flag_truncate_d      MSG_TRUNC
  #define f_socket_flag_wait_all_d      MSG_WAITALL
  #define f_socket_flag_wait_not_d      MSG_DONTWAIT
#endif // _di_f_socket_flags_

/**
 * Socket Message Flags.
 *
 * These represent responses from socket messages (see recvmsg()).
 *
 * f_socket_message_flag_*:
 *   - error_queue:      No data received but extended error from the socket error queue is received.
 *   - out_of_band:      The message is expedited or out of band data is received.
 *   - record_end:       End of record reached.
 *   - truncate:         The data has been truncated due to lack of space in the buffer.
 *   - truncate_control: The control data has been truncated due to lack of space in the buffer.
 */
#ifndef _di_f_socket_message_flags_
  #define f_socket_message_flag_error_queue_d      MSG_ERRQUEUE
  #define f_socket_message_flag_out_of_band_d      MSG_OOB
  #define f_socket_message_flag_record_end_d       MSG_EOR
  #define f_socket_message_flag_truncate_d         MSG_TRUNC
  #define f_socket_message_flag_truncate_control_d MSG_CTRUNC
#endif // _di_f_socket_flags_

/**
 * Socket types.
 *
 * f_socket_type_*:
 *   - close_on_execute:  Close on execute.
 *   - datagram:          Datagram (connectionless, unreliable, fixed length).
 *   - datagram_reliable: Reliable Datagram (reliable variant of datagram, unordered)
 *   - datagram_sequence: Sequenced Datagram.
 *   - nonblocking:       Non-blocking.
 *   - raw:               Raw access.
 *   - stream:            Stream.
 */
#ifndef _di_f_socket_types_
  #define f_socket_type_close_on_execute_d  SOCK_CLOEXEC
  #define f_socket_type_datagram_d          SOCK_DGRAM
  #define f_socket_type_datagram_reliable_d SOCK_RDM
  #define f_socket_type_datagram_sequence_d SOCK_SEQPACKET
  #define f_socket_type_nonblocking_d       SOCK_NONBLOCK
  #define f_socket_type_raw_d               SOCK_RAW
  #define f_socket_type_stream_d            SOCK_STREAM
#endif // _di_f_socket_types_

/**
 * Commonly used socket related properties, loosely based off of f_file_t.
 *
 * address:    Pointer to the socket address (stored as "struct sockaddr" but may represent other types such as "struct sockaddr_un" or "struct sockaddr_in").
 * domain:     The socket domain (protocol family).
 * flag:       Flags used for opening the file.
 * id:         File descriptor, with a value of -1 represents a closed file.
 * name:       The name of the socket, if a name is given (for UNIX sockets this represents the path) (Must be a NULL terminated string).
 * protocol:   The socket protocol.
 * size_read:  The default number of 1-byte characters to read at a time and is often used for the read buffer size.
 * size_write: The default number of 1-byte characters to read at a time and is often used for the write buffer size.
 * type:       The socket type.
 */
#ifndef _di_f_socket_t_
  typedef struct {
    int id;
    int domain;
    int protocol;
    int type;

    size_t size_read;
    size_t size_write;

    socklen_t length;

    struct sockaddr *address;

    f_string_t name;
  } f_socket_t;

  #define f_socket_t_initialize { -1, 0, 0, 0, F_socket_default_read_size_d, F_socket_default_write_size_d, 0, 0 }

  #define macro_f_socket_t_initialize(address) { -1, 0, 0, 0, F_socket_default_read_size_d, F_socket_default_write_size_d, address, 0 }

  #define macro_f_socket_t_clear(file) \
    file.id = -1; \
    file.domain = 0; \
    file.protocol = 0; \
    file.type = 0; \
    file.size_read = 0; \
    file.size_write = 0; \
    file.length = 0; \
    file.name = 0;

  #define macro_f_socket_t_reset(file) \
    file.id = -1; \
    file.domain = 0; \
    file.protocol = 0; \
    file.type = 0; \
    file.size_read = F_socket_default_read_size_d; \
    file.size_write = F_socket_default_write_size_d; \
    file.length = 0; \
    file.name = 0;
#endif // _di_f_socket_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_socket_common_h
