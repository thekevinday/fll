/**
 * FLL - Level 0
 *
 * Project: Socket
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the socket project.
 */
#ifndef _MOCK__socket_h
#define _MOCK__socket_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/socket.h>

#ifdef __cplusplus
extern "C" {
#endif

const static int mock_errno_generic = 32767;

extern int mock_unwrap;
extern int mock_unwrap_f_memory;

extern f_status_t __real_f_memory_array_adjust(const f_number_unsigned_t length, const size_t width, void ** array, f_number_unsigned_t * const used, f_number_unsigned_t * const size);
extern f_status_t __real_f_memory_array_resize(const f_number_unsigned_t length, const size_t width, void ** array, f_number_unsigned_t * const used, f_number_unsigned_t * const size);

extern f_status_t __wrap_f_memory_array_adjust(const f_number_unsigned_t length, const size_t width, void ** array, f_number_unsigned_t * const used, f_number_unsigned_t * const size);
extern f_status_t __wrap_f_memory_array_resize(const f_number_unsigned_t length, const size_t width, void ** array, f_number_unsigned_t * const used, f_number_unsigned_t * const size);

extern int __wrap_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
extern int __wrap_bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
extern int __wrap_close(int fd);
extern int __wrap_connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
extern int __wrap_gethostname(char *name, size_t len);
extern int __wrap_getpeername(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
extern int __wrap_getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen);
extern int __wrap_listen(int sockfd, int backlog);
extern ssize_t __wrap_recv(int sockfd, void *buf, size_t len, int flags);
extern ssize_t __wrap_recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
extern ssize_t __wrap_recvmsg(int sockfd, struct msghdr *msg, int flags);
extern ssize_t __wrap_send(int sockfd, const void *buf, size_t len, int flags);
extern ssize_t __wrap_sendmsg(int sockfd, const struct msghdr *msg, int flags);
extern ssize_t __wrap_sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
extern int __wrap_setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
extern int __wrap_shutdown(int sockfd, int how);
extern int __wrap_socket(int domain, int type, int protocol);
extern int __wrap_socketpair(int domain, int type, int protocol, int sv[2]);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _MOCK__socket_h
