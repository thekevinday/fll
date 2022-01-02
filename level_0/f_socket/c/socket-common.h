/**
 * FLL - Level 0
 *
 * Project: Socket
 * API Version: 0.5
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
 * - fast:       Fast Socket close, as in close().
 * - read:       Read close, as in shutdown(, SHUT_RD).
 * - write:      Write close, as in shutdown(, SHUT_WR).
 * - read_write: Read/Write close, as in shutdown(, SHUT_RDWR).
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
 * name:       The name of the socket, if a name is given (for UNIX sockets this represents the path).
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
