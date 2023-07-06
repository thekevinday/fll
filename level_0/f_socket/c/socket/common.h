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
 *   - name_max:   Default buffer size for names.
 *   - read_size:  Default read size in bytes.
 *   - write_size: Default write size in bytes.
 */
#ifndef _di_f_socket_default_d_
  #define F_socket_default_name_max_d   256
  #define F_socket_default_read_size_d  8192
  #define F_socket_default_write_size_d 8192
#endif // _di_f_socket_default_d_

/**
 * Socket address families.
 *
 * Many libc implementations have the AF_* directly map to PF_*.
 *
 * f_socket_address_family_*_e:
 *   - unspecified: No protocol family specified.
 *   - local:       Localhost, pipes, Unix sockets, or file sockets (PF_LOCAL, PF_UNIX, PF_FILE).
 *   - inet:        IP protocol family.
 *   - ax25:        Amateur Radio AX.25.
 *   - ipx:         Novell Internet Protocol.
 *   - appletalk:   Appletalk DDP.
 *   - netrom:      Amateur radio NetROM.
 *   - bridge:      Multiprotocol bridge.
 *   - atmpvc:      ATM PVCs.
 *   - x25:         Reserved for X.25 project.
 *   - inet6:       IP version 6.
 *   - rose:        Amateur Radio X.25 PLP.
 *   - decnet:      Reserved for DECnet project.
 *   - netbeui:     Reserved for 802.2LLC project.
 *   - security:    Security callback pseudo AF.
 *   - key:         PF_KEY key management API.
 *   - netlink:     Netlink and BSD (PF_NETLINK and PF_ROUTE).
 *   - packet:      Packet family.
 *   - ash:         Ash.
 *   - econet:      Acorn Econet.
 *   - atmsvc:      ATM SVCs.
 *   - rds:         RDS sockets.
 *   - sna:         Linux SNA Project.
 *   - irda:        IRDA sockets.
 *   - pppox:       PPPoX sockets.
 *   - wanpipe:     Wanpipe API sockets.
 *   - llc:         Linux LLC.
 *   - ib:          Native InfiniBand address.
 *   - mpls:        MPLS.
 *   - can:         Controller Area Network.
 *   - tipc:        TIPC sockets.
 *   - bluetooth:   Bluetooth sockets.
 *   - iucb:        IUCV sockets.
 *   - rxrpc:       RxRPC sockets.
 *   - isdn:        mISDN sockets.
 *   - phonet:      Phonet sockets.
 *   - ieee802154:  IEEE 802.15.4 sockets.
 *   - caif:        CAIF sockets.
 *   - alg:         Algorithm sockets.
 *   - nfc:         NFC sockets.
 *   - vsock:       vSockets.
 *   - kcm:         Kernel Connection Multiplexor.
 *   - qipcrtr:     Qualcomm IPC Router.
 *   - smc:         SMC sockets.
 *   - max:         The maximum value for known protocol families (this is not a protocol family).
 */
#ifndef _di_f_socket_address_family_e_
  enum {
    f_socket_address_family_unspecified_e = AF_UNSPEC,
    f_socket_address_family_local_e = AF_LOCAL,
    f_socket_address_family_inet_e = AF_INET,
    f_socket_address_family_ax25_e = AF_AX25,
    f_socket_address_family_ipx_e = AF_IPX,
    f_socket_address_family_appletalk_e = AF_APPLETALK,
    f_socket_address_family_netrom_e = AF_NETROM,
    f_socket_address_family_bridge_e = AF_BRIDGE,
    f_socket_address_family_atmpvc_e = AF_ATMPVC,
    f_socket_address_family_x25_e = AF_X25,
    f_socket_address_family_inet6_e = AF_INET6,
    f_socket_address_family_rose_e = AF_ROSE,
    f_socket_address_family_decnet_e = AF_DECnet,
    f_socket_address_family_netbeui_e = AF_NETBEUI,
    f_socket_address_family_security_e = AF_SECURITY,
    f_socket_address_family_key_e = AF_KEY,
    f_socket_address_family_netlink_e = AF_NETLINK,
    f_socket_address_family_packet_e = AF_PACKET,
    f_socket_address_family_ash_e = AF_ASH,
    f_socket_address_family_econet_e = AF_ECONET,
    f_socket_address_family_atmsvc_e = AF_ATMSVC,
    f_socket_address_family_rds_e = AF_RDS,
    f_socket_address_family_sna_e = AF_SNA,
    f_socket_address_family_irda_e = AF_IRDA,
    f_socket_address_family_pppox_e = AF_PPPOX,
    f_socket_address_family_wanpipe_e = AF_WANPIPE,
    f_socket_address_family_llc_e = AF_LLC,
    f_socket_address_family_ib_e = AF_IB,
    f_socket_address_family_mpls_e = AF_MPLS,
    f_socket_address_family_can_e = AF_CAN,
    f_socket_address_family_tipc_e = AF_TIPC,
    f_socket_address_family_bluetooth_e = AF_BLUETOOTH,
    f_socket_address_family_iucb_e = AF_IUCV,
    f_socket_address_family_rxrpc_e = AF_RXRPC,
    f_socket_address_family_isdn_e = AF_ISDN,
    f_socket_address_family_phonet_e = AF_PHONET,
    f_socket_address_family_ieee802154_e = AF_IEEE802154,
    f_socket_address_family_caif_e = AF_CAIF,
    f_socket_address_family_alg_e = AF_ALG,
    f_socket_address_family_nfc_e = AF_NFC,
    f_socket_address_family_vsock_e = AF_VSOCK,
    f_socket_address_family_kcm_e = AF_KCM,
    f_socket_address_family_qipcrtr_e = AF_QIPCRTR,
    f_socket_address_family_smc_e = AF_SMC,
    f_socket_address_family_max_e = AF_MAX,
  };
#endif // _di_f_socket_address_family_e_

/**
 * Socket Closes.
 *
 * f_socket_close_*:
 *   - fast:       Fast Socket close, as in close().
 *   - read:       Read close, as in shutdown(, SHUT_RD).
 *   - read_write: Read/Write close, as in shutdown(, SHUT_RDWR).
 *   - write:      Write close, as in shutdown(, SHUT_WR).
 */
#ifndef _di_f_socket_close_e_
  enum {
    f_socket_close_fast_e = 1,
    f_socket_close_read_e,
    f_socket_close_write_e,
    f_socket_close_read_write_e,
  };
#endif // _di_f_socket_close_e_

/**
 * Socket protocol codes.
 *
 * Disclaimer: This may be different from system to system depending on the libc and other factors.
 *
 * f_socket_protocol_*_e:
 *  - ip:              Internet Protocol and pseudo protocol number or IPv6 Hop by Hop Option (RFC1883).
 *  - icmp:            internet control message protocol.
 *  - igmp:            Internet Group Management.
 *  - ggp:             Gateway-Gateway Protocol.
 *  - ipencap:         IP Encapsulated in IP.
 *  - st:              ST datagram mode.
 *  - tcp:             Transmission Control Protocol
 *  - egp:             Exterior Gateway Protocol
 *  - igp:             Any private Interior Gateway Protocol.
 *  - pup:             PARC Universal Packet.
 *  - udp:             User Datagram Protocol.
 *  - hmp:             Host Monitoring Protocol.
 *  - xns_idp          Xerox NS IDP.
 *  - rdp:             Reliable Datagram Protocol.
 *  - iso_tp4          ISO Transport Protocol class 4 (RFC905).
 *  - dccp:            Datagram Congestion Control Prot. (RFC4340).
 *  - xtp:             Xpress Transfer Protocol.
 *  - ddp:             Datagram Delivery Protocol.
 *  - idpr_cmtp:       IDPR Control Message Transport.
 *  - ipv6:            Internet Protocol Version 6.
 *  - ipv6_route       Internet Protocol Version 6 Routing Header.
 *  - ipv6_frag        Internet Protocol Version 6 Fragment Header.
 *  - idrp:            Inter-Domain Routing Protocol.
 *  - rsvp:            Reservation Protocol.
 *  - gre:             General Routing Encapsulation.
 *  - esp:             Encapsulated Security Payload (RFC2406).
 *  - ah:              Authentication Header (RFC2402).
 *  - skip:            SKIP.
 *  - ipv6_icmp        ICMP for IPv6.
 *  - ipv6_nonxt       No Next Header for IPv6.
 *  - ipv6_opts        Destination Options for IPv6.
 *  - rspf:            Radio Shortest Path First.
 *  - vmtp:            Versatile Message Transport.
 *  - eigrp:           Enhanced Interior Routing Protocol.
 *  - ospf:            Open Shortest Path First IGP.
 *  - ax_25            AX.25 Frames.
 *  - ipip:            IP within IP Encapsulation Protocol
 *  - etherip:         Ethernet within IP Encapsulation (RFC3378).
 *  - encap:           Yet Another IP Encapsulation (RFC1241).
 *  - encryption       Any private encryption scheme.
 *  - pim:             Protocol Independent Multicast.
 *  - ipcomp:          IP Payload Compression Protocol.
 *  - vrrp:            Virtual Router Redundancy Protocol (RFC5798).
 *  - l2tp:            Layer Two Tunneling Protocol (RFC2661).
 *  - isis:            IS-IS over IPv4.
 *  - sctp:            Stream Control Transmission Protocol.
 *  - fc:              Fibre Channel.
 *  - mobility_header: Mobility Support for IPv6 (RFC3775).
 *  - udplite:         UDP-Lite (RFC3828).
 *  - mpls_in_ip:      MPLS-in-IP (RFC4023).
 *  - manet:           MANET Protocols (RFC5498).
 *  - hip:             Host Identity Protocol.
 *  - shim6:           Shim6 Protocol (RFC5533).
 *  - wesp:            Wrapped Encapsulating Security Payload.
 *  - rohc:            Robust Header Compression.
 */
#ifndef _di_f_socket_protocol_e_
  enum {
    f_socket_protocol_ip              = 0,
    f_socket_protocol_icmp            = 1,
    f_socket_protocol_igmp            = 2,
    f_socket_protocol_ggp             = 3,
    f_socket_protocol_ipencap         = 4,
    f_socket_protocol_st              = 5,
    f_socket_protocol_tcp             = 6,
    f_socket_protocol_egp             = 8,
    f_socket_protocol_igp             = 9,
    f_socket_protocol_pup             = 12,
    f_socket_protocol_udp             = 17,
    f_socket_protocol_hmp             = 20,
    f_socket_protocol_xns_idp         = 22,
    f_socket_protocol_rdp             = 27,
    f_socket_protocol_iso_tp4         = 29,
    f_socket_protocol_dccp            = 33,
    f_socket_protocol_xtp             = 36,
    f_socket_protocol_ddp             = 37,
    f_socket_protocol_idpr_cmtp       = 38,
    f_socket_protocol_ipv6            = 41,
    f_socket_protocol_ipv6_route      = 43,
    f_socket_protocol_ipv6_frag       = 44,
    f_socket_protocol_idrp            = 45,
    f_socket_protocol_rsvp            = 46,
    f_socket_protocol_gre             = 47,
    f_socket_protocol_esp             = 50,
    f_socket_protocol_ah              = 51,
    f_socket_protocol_skip            = 57,
    f_socket_protocol_ipv6_icmp       = 58,
    f_socket_protocol_ipv6_nonxt      = 59,
    f_socket_protocol_ipv6_opts       = 60,
    f_socket_protocol_rspf            = 73,
    f_socket_protocol_vmtp            = 81,
    f_socket_protocol_eigrp           = 88,
    f_socket_protocol_ospf            = 89,
    f_socket_protocol_ax_25           = 93,
    f_socket_protocol_ipip            = 94,
    f_socket_protocol_etherip         = 97,
    f_socket_protocol_encap           = 98,
    f_socket_protocol_encrypted       = 99,
    f_socket_protocol_pim             = 103,
    f_socket_protocol_ipcomp          = 108,
    f_socket_protocol_vrrp            = 112,
    f_socket_protocol_l2tp            = 115,
    f_socket_protocol_isis            = 124,
    f_socket_protocol_sctp            = 132,
    f_socket_protocol_fc              = 133,
    f_socket_protocol_mobility_header = 135,
    f_socket_protocol_udplite         = 136,
    f_socket_protocol_mpls_in_ip      = 137,
    f_socket_protocol_manet           = 138,
    f_socket_protocol_hip             = 139,
    f_socket_protocol_shim6           = 140,
    f_socket_protocol_wesp            = 141,
    f_socket_protocol_rohc            = 142,
  };
#endif // _di_f_socket_protocol_e_

/**
 * Socket protocol families, referred to as a domain.
 *
 * f_socket_protocol_family_*_e:
 *   - unspecified: No protocol family specified.
 *   - local:       Localhost, pipes, Unix sockets, or file sockets (PF_LOCAL, PF_UNIX, PF_FILE).
 *   - inet:        IP protocol family.
 *   - ax25:        Amateur Radio AX.25.
 *   - ipx:         Novell Internet Protocol.
 *   - appletalk:   Appletalk DDP.
 *   - netrom:      Amateur radio NetROM.
 *   - bridge:      Multiprotocol bridge.
 *   - atmpvc:      ATM PVCs.
 *   - x25:         Reserved for X.25 project.
 *   - inet6:       IP version 6.
 *   - rose:        Amateur Radio X.25 PLP.
 *   - decnet:      Reserved for DECnet project.
 *   - netbeui:     Reserved for 802.2LLC project.
 *   - security:    Security callback pseudo AF.
 *   - key:         PF_KEY key management API.
 *   - netlink:     Netlink and BSD (PF_NETLINK and PF_ROUTE).
 *   - packet:      Packet family.
 *   - ash:         Ash.
 *   - econet:      Acorn Econet.
 *   - atmsvc:      ATM SVCs.
 *   - rds:         RDS sockets.
 *   - sna:         Linux SNA Project.
 *   - irda:        IRDA sockets.
 *   - pppox:       PPPoX sockets.
 *   - wanpipe:     Wanpipe API sockets.
 *   - llc:         Linux LLC.
 *   - ib:          Native InfiniBand address.
 *   - mpls:        MPLS.
 *   - can:         Controller Area Network.
 *   - tipc:        TIPC sockets.
 *   - bluetooth:   Bluetooth sockets.
 *   - iucb:        IUCV sockets.
 *   - rxrpc:       RxRPC sockets.
 *   - isdn:        mISDN sockets.
 *   - phonet:      Phonet sockets.
 *   - ieee802154:  IEEE 802.15.4 sockets.
 *   - caif:        CAIF sockets.
 *   - alg:         Algorithm sockets.
 *   - nfc:         NFC sockets.
 *   - vsock:       vSockets.
 *   - kcm:         Kernel Connection Multiplexor.
 *   - qipcrtr:     Qualcomm IPC Router.
 *   - smc:         SMC sockets.
 *   - max:         The maximum value for known protocol families (this is not a protocol family).
 */
#ifndef _di_f_socket_protocol_family_e_
  enum {
    f_socket_protocol_family_unspecified_e = PF_UNSPEC,
    f_socket_protocol_family_local_e = PF_LOCAL,
    f_socket_protocol_family_inet_e = PF_INET,
    f_socket_protocol_family_ax25_e = PF_AX25,
    f_socket_protocol_family_ipx_e = PF_IPX,
    f_socket_protocol_family_appletalk_e = PF_APPLETALK,
    f_socket_protocol_family_netrom_e = PF_NETROM,
    f_socket_protocol_family_bridge_e = PF_BRIDGE,
    f_socket_protocol_family_atmpvc_e = PF_ATMPVC,
    f_socket_protocol_family_x25_e = PF_X25,
    f_socket_protocol_family_inet6_e = PF_INET6,
    f_socket_protocol_family_rose_e = PF_ROSE,
    f_socket_protocol_family_decnet_e = PF_DECnet,
    f_socket_protocol_family_netbeui_e = PF_NETBEUI,
    f_socket_protocol_family_security_e = PF_SECURITY,
    f_socket_protocol_family_key_e = PF_KEY,
    f_socket_protocol_family_netlink_e = PF_NETLINK,
    f_socket_protocol_family_packet_e = PF_PACKET,
    f_socket_protocol_family_ash_e = PF_ASH,
    f_socket_protocol_family_econet_e = PF_ECONET,
    f_socket_protocol_family_atmsvc_e = PF_ATMSVC,
    f_socket_protocol_family_rds_e = PF_RDS,
    f_socket_protocol_family_sna_e = PF_SNA,
    f_socket_protocol_family_irda_e = PF_IRDA,
    f_socket_protocol_family_pppox_e = PF_PPPOX,
    f_socket_protocol_family_wanpipe_e = PF_WANPIPE,
    f_socket_protocol_family_llc_e = PF_LLC,
    f_socket_protocol_family_ib_e = PF_IB,
    f_socket_protocol_family_mpls_e = PF_MPLS,
    f_socket_protocol_family_can_e = PF_CAN,
    f_socket_protocol_family_tipc_e = PF_TIPC,
    f_socket_protocol_family_bluetooth_e = PF_BLUETOOTH,
    f_socket_protocol_family_iucb_e = PF_IUCV,
    f_socket_protocol_family_rxrpc_e = PF_RXRPC,
    f_socket_protocol_family_isdn_e = PF_ISDN,
    f_socket_protocol_family_phonet_e = PF_PHONET,
    f_socket_protocol_family_ieee802154_e = PF_IEEE802154,
    f_socket_protocol_family_caif_e = PF_CAIF,
    f_socket_protocol_family_alg_e = PF_ALG,
    f_socket_protocol_family_nfc_e = PF_NFC,
    f_socket_protocol_family_vsock_e = PF_VSOCK,
    f_socket_protocol_family_kcm_e = PF_KCM,
    f_socket_protocol_family_qipcrtr_e = PF_QIPCRTR,
    f_socket_protocol_family_smc_e = PF_SMC,
    f_socket_protocol_family_max_e = PF_MAX,
  };
#endif // _di_f_socket_protocol_family_e_

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
#ifndef _di_f_socket_option_e_
  enum {
    f_socket_option_address_reuse_e            = SO_REUSEADDR,
    f_socket_option_advice_cnx_e               = SO_CNX_ADVICE,
    f_socket_option_bpf_attach_e               = SO_ATTACH_BPF,
    f_socket_option_bpf_detach_e               = SO_DETACH_BPF,
    f_socket_option_bpf_extensions_e           = SO_BPF_EXTENSIONS,
    f_socket_option_broadcast_e                = SO_BROADCAST,
    f_socket_option_buffer_receive_e           = SO_RCVBUF,
    f_socket_option_buffer_receive_force_e     = SO_RCVBUFFORCE,
    f_socket_option_buffer_send_e              = SO_SNDBUF,
    f_socket_option_buffer_send_force_e        = SO_SNDBUFFORCE,
    f_socket_option_cbpf_port_reuse_attach_e   = SO_ATTACH_REUSEPORT_CBPF,
    f_socket_option_check_not_e                = SO_NO_CHECK,
    f_socket_option_compatibility_bsd_e        = SO_BSDCOMPAT,
    f_socket_option_connection_accept_e        = SO_ACCEPTCONN,
    f_socket_option_cookie_e                   = SO_COOKIE,
    f_socket_option_cpu_incoming_e             = SO_INCOMING_CPU,
    f_socket_option_credentials_pass_e         = SO_PASSCRED,
    f_socket_option_credentials_peer_e         = SO_PEERCRED,
    f_socket_option_debug_e                    = SO_DEBUG,
    f_socket_option_device_bind_e              = SO_BINDTODEVICE,
    f_socket_option_domain_e                   = SO_DOMAIN,
    f_socket_option_ebpf_port_reuse_attach_e   = SO_ATTACH_REUSEPORT_EBPF,
    f_socket_option_error_e                    = SO_ERROR,
    f_socket_option_filter_attach_e            = SO_ATTACH_FILTER,
    f_socket_option_filter_detach_e            = SO_DETACH_FILTER,
    f_socket_option_filter_get_e               = SO_GET_FILTER,
    f_socket_option_filter_lock_e              = SO_LOCK_FILTER,
    f_socket_option_frame_check_sequence_not_e = SO_NOFCS,
    f_socket_option_groups_peer_e              = SO_PEERGROUPS,
    f_socket_option_keep_alive_e               = SO_KEEPALIVE,
    f_socket_option_linger_e                   = SO_LINGER,
    f_socket_option_low_at_receive_e           = SO_RCVLOWAT,
    f_socket_option_low_at_send_e              = SO_SNDLOWAT,
    f_socket_option_mark_e                     = SO_MARK,
    f_socket_option_memory_information_e       = SO_MEMINFO,
    f_socket_option_name_peer_e                = SO_PEERNAME,
    f_socket_option_napi_id_incoming_e         = SO_INCOMING_NAPI_ID,
    f_socket_option_out_of_band_inline_e       = SO_OOBINLINE,
    f_socket_option_pacing_rate_max_e          = SO_MAX_PACING_RATE,
    f_socket_option_peek_off_e                 = SO_PEEK_OFF,
    f_socket_option_poll_busy_e                = SO_BUSY_POLL,
    f_socket_option_port_reuse_e               = SO_REUSEPORT,
    f_socket_option_priority_e                 = SO_PRIORITY,
    f_socket_option_protocol_e                 = SO_PROTOCOL,
    f_socket_option_receive_overflow_e         = SO_RXQ_OVFL,
    f_socket_option_route_not_e                = SO_DONTROUTE,
    f_socket_option_security_authentication_e  = SO_SECURITY_AUTHENTICATION,
    f_socket_option_security_network_e         = SO_SECURITY_ENCRYPTION_NETWORK,
    f_socket_option_security_pass_e            = SO_PASSSEC,
    f_socket_option_security_peer_e            = SO_PEERSEC,
    f_socket_option_security_transport_e       = SO_SECURITY_ENCRYPTION_TRANSPORT,
    f_socket_option_select_error_queue_e       = SO_SELECT_ERR_QUEUE,
    f_socket_option_time_out_receive_e         = SO_RCVTIMEO,
    f_socket_option_time_out_send_e            = SO_SNDTIMEO,
    f_socket_option_time_stamp_e               = SO_TIMESTAMP,
    f_socket_option_time_stamp_namespace_e     = SO_TIMESTAMPNS,
    f_socket_option_time_stamping_e            = SO_TIMESTAMPING,
    f_socket_option_time_stamping_packet_e     = SCM_TIMESTAMPING_PKTINFO,
    f_socket_option_time_stamping_stats_e      = SCM_TIMESTAMPING_OPT_STATS,
    f_socket_option_time_transmit_e            = SO_TXTIME,
    f_socket_option_type_e                     = SO_TYPE,
    f_socket_option_wifi_status_e              = SO_WIFI_STATUS,
    f_socket_option_zero_copy_e                = SO_ZEROCOPY,
  };
#endif // _di_f_socket_option_e_

/**
 * Socket Flags.
 *
 * These are flags to pass to either socket receive or socket send functions.
 *
 * f_socket_flag_*_e:
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
#ifndef _di_f_socket_flag_e_
  enum {
    f_socket_flag_close_on_exit_e = MSG_CMSG_CLOEXEC,
    f_socket_flag_confirm_e       = MSG_CONFIRM,
    f_socket_flag_error_queue_e   = MSG_ERRQUEUE,
    f_socket_flag_more_e          = MSG_MORE,
    f_socket_flag_out_of_band_e   = MSG_OOB,
    f_socket_flag_peek_e          = MSG_PEEK,
    f_socket_flag_record_end_e    = MSG_EOR,
    f_socket_flag_route_not_e     = MSG_DONTROUTE,
    f_socket_flag_signal_not_e    = MSG_NOSIGNAL,
    f_socket_flag_truncate_e      = MSG_TRUNC,
    f_socket_flag_wait_all_e      = MSG_WAITALL,
    f_socket_flag_wait_not_e      = MSG_DONTWAIT,
  };
#endif // _di_f_socket_flag_e_

/**
 * Socket Message Flags.
 *
 * These represent responses from socket messages (see recvmsg()).
 *
 * f_socket_message_flag_*_e:
 *   - error_queue:      No data received but extended error from the socket error queue is received.
 *   - out_of_band:      The message is expedited or out of band data is received.
 *   - record_end:       End of record reached.
 *   - truncate:         The data has been truncated due to lack of space in the buffer.
 *   - truncate_control: The control data has been truncated due to lack of space in the buffer.
 */
#ifndef _di_f_socket_message_flag_e_
  enum {
    f_socket_message_flag_error_queue_e      = MSG_ERRQUEUE,
    f_socket_message_flag_out_of_band_e      = MSG_OOB,
    f_socket_message_flag_record_end_e       = MSG_EOR,
    f_socket_message_flag_truncate_e         = MSG_TRUNC,
    f_socket_message_flag_truncate_control_e = MSG_CTRUNC,
  };
#endif // _di_f_socket_message_flag_e_

/**
 * Socket types.
 *
 * f_socket_type_*_e:
 *   - close_on_execute:  Close on execute.
 *   - datagram:          Datagram (connectionless, unreliable, fixed length).
 *   - datagram_reliable: Reliable Datagram (reliable variant of datagram, unordered)
 *   - datagram_sequence: Sequenced Datagram.
 *   - nonblocking:       Non-blocking.
 *   - raw:               Raw access.
 *   - stream:            Stream.
 */
#ifndef _di_f_socket_type_e_
  enum {
    f_socket_type_close_on_execute_e  = SOCK_CLOEXEC,
    f_socket_type_datagram_e          = SOCK_DGRAM,
    f_socket_type_datagram_reliable_e = SOCK_RDM,
    f_socket_type_datagram_sequence_e = SOCK_SEQPACKET,
    f_socket_type_nonblocking_e       = SOCK_NONBLOCK,
    f_socket_type_raw_e               = SOCK_RAW,
    f_socket_type_stream_e            = SOCK_STREAM,
  };
#endif // _di_f_socket_type_e_

/**
 * Commonly used socket related properties, loosely based off of f_file_t.
 *
 * id:       File descriptor, with a value of -1 represents a closed file.
 * domain:   The socket domain (protocol family).
 * protocol: The socket protocol.
 * type:     The socket type (address family).
 *
 * size_read:  The default number of 1-byte characters to read at a time and is often used for the read buffer size.
 * size_write: The default number of 1-byte characters to read at a time and is often used for the write buffer size.
 *
 * length:  The length of the socket.
 * address: Pointer to the socket address (stored as "struct sockaddr" but may represent other types such as "struct sockaddr_un" or "struct sockaddr_in").
 *
 * name: The name of the socket, if a name is given (for UNIX sockets this represents the path) (Must be a NULL terminated string).
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

    f_string_static_t name;
  } f_socket_t;

  #define f_socket_t_initialize { -1, 0, 0, 0, F_socket_default_read_size_d, F_socket_default_write_size_d, 0, 0, f_string_empty_s }

  #define macro_f_socket_t_initialize_1(address, length) { \
    -1, \
    0, \
    0, \
    0, \
    F_socket_default_read_size_d, \
    F_socket_default_write_size_d, \
    address, \
    length, \
    f_string_empty_s \
  }

  #define macro_f_socket_t_initialize_2(address, length, name) { \
    -1, \
    0, \
    0, \
    0, \
    F_socket_default_read_size_d, \
    F_socket_default_write_size_d, \
    address, \
    length, \
    name \
  }

  #define macro_f_socket_t_initialize_3(id, domain, protocol, type, address, length, name) { \
    id, \
    domain, \
    protocol, \
    type, \
    F_socket_default_read_size_d, \
    F_socket_default_write_size_d, \
    address, \
    length, \
    name \
  }

  #define macro_f_socket_t_initialize_4(id, domain, protocol, type, size_read, size_write, address, length, name) { \
    id, \
    domain, \
    protocol, \
    type, \
    size_read, \
    size_write, \
    address, \
    length, \
    name \
  }

  #define macro_f_socket_t_clear(file) \
    file.id = -1; \
    file.domain = 0; \
    file.protocol = 0; \
    file.type = 0; \
    file.size_read = 0; \
    file.size_write = 0; \
    file.length = 0; \
    file.address = 0; \
    macro_f_string_static_t_clear(file);

  #define macro_f_socket_t_reset(file) \
    file.id = -1; \
    file.domain = 0; \
    file.protocol = 0; \
    file.type = 0; \
    file.size_read = F_socket_default_read_size_d; \
    file.size_write = F_socket_default_write_size_d; \
    file.length = 0; \
    file.address = 0; \
    macro_f_string_static_t_clear(file);
#endif // _di_f_socket_t_

/**
 * An array of f_socket_t.
 *
 * array: The array of f_socket_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_sockets_t_
  typedef struct {
    f_socket_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_sockets_t;

  #define f_sockets_t_initialize { 0, 0, 0 }

  #define macro_f_sockets_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_sockets_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_sockets_t_

/**
 * This holds an array of f_sockets_t.
 *
 * array: The array of f_socket_t arrays.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_socketss_t_
  typedef struct {
    f_sockets_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_socketss_t;

  #define f_socketss_t_initialize { 0, 0, 0 }

  #define macro_f_socketss_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_socketss_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_socketss_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_socket_common_h
