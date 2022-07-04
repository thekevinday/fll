/**
 * FLL - Level 0
 *
 * Project: Socket
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the socket project.
 */
#ifndef _TEST__F_socket_disconnect_h
#define _TEST__F_socket_disconnect_h

/**
 * Test that function fails for f_socket_close_fast_e.
 *
 * @see f_socket_disconnect()
 */
extern void test__f_socket_disconnect__fails_for_close_fast(void **state);

/**
 * Test that function fails for f_socket_close_read_e.
 *
 * @see f_socket_disconnect()
 */
extern void test__f_socket_disconnect__fails_for_close_read(void **state);

/**
 * Test that function fails for an arbitrary unknown close value.
 *
 * @see f_socket_disconnect()
 */
extern void test__f_socket_disconnect__fails_for_close_unknown(void **state);

/**
 * Test that function fails for f_socket_close_write_e.
 *
 * @see f_socket_disconnect()
 */
extern void test__f_socket_disconnect__fails_for_close_write(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_socket_disconnect()
 */
extern void test__f_socket_disconnect__parameter_checking(void **state);

/**
 * Test that function works for f_socket_close_fast_e.
 *
 * @see f_socket_disconnect()
 */
extern void test__f_socket_disconnect__works_for_close_fast(void **state);

/**
 * Test that function works for f_socket_close_read_e.
 *
 * @see f_socket_disconnect()
 */
extern void test__f_socket_disconnect__works_for_close_read(void **state);

/**
 * Test that function works for f_socket_close_write_e.
 *
 * @see f_socket_disconnect()
 */
extern void test__f_socket_disconnect__works_for_close_write(void **state);

#endif // _TEST__F_socket_disconnect_h
