/**
 * FLL - Level 0
 *
 * Project: Socket
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the socket project.
 */
#ifndef _TEST__F_socket_name_host_h
#define _TEST__F_socket_name_host_h

/**
 * Test that function allocates the string size using the default size.
 *
 * @see f_socket_name_host()
 */
extern void test__f_socket_name_host__allocates_default(void **state);

/**
 * Test that function fails.
 *
 * @see f_socket_name_host()
 */
extern void test__f_socket_name_host__fails(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_socket_name_host()
 */
extern void test__f_socket_name_host__parameter_checking(void **state);

/**
 * Test that function works.
 *
 * @see f_socket_name_host()
 */
extern void test__f_socket_name_host__works(void **state);

#endif // _TEST__F_socket_name_host_h
