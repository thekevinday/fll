/**
 * FLL - Level 0
 *
 * Project: Socket
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the socket project.
 */
#ifndef _TEST__F_socket_bind_inet4_h
#define _TEST__F_socket_bind_inet4_h

/**
 * Test that function fails.
 *
 * @see f_socket_bind_inet4()
 */
extern void test__f_socket_bind_inet4__fails(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_socket_bind_inet4()
 */
extern void test__f_socket_bind_inet4__parameter_checking(void **state);

/**
 * Test that function works.
 *
 * @see f_socket_bind_inet4()
 */
extern void test__f_socket_bind_inet4__works(void **state);

#endif // _TEST__F_socket_bind_inet4_h