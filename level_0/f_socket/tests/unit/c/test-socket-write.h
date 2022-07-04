/**
 * FLL - Level 0
 *
 * Project: Socket
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the socket project.
 */
#ifndef _TEST__F_socket_write_h
#define _TEST__F_socket_write_h

/**
 * Test that function fails.
 *
 * @see f_socket_write()
 */
extern void test__f_socket_write__fails(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_socket_write()
 */
extern void test__f_socket_write__parameter_checking(void **state);

/**
 * Test that function works.
 *
 * @see f_socket_write()
 */
extern void test__f_socket_write__works(void **state);

#endif // _TEST__F_socket_write_h
