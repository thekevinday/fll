/**
 * FLL - Level 0
 *
 * Project: Socket
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the array types in the type project.
 */
#ifndef _TEST__F_socket__sockets_decimate_by
#define _TEST__F_socket__sockets_decimate_by

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_sockets_decimate_by()
 */
extern void test__f_socket_sockets_decimate_by__parameter_checking(void **state);

/**
 * Test that the function returns F_data_not.
 *
 * @see f_sockets_decimate_by()
 */
extern void test__f_socket_sockets_decimate_by__returns_data_not(void **state);

/**
 * Test that the function works.
 *
 * @see f_sockets_decimate_by()
 */
extern void test__f_socket_sockets_decimate_by__works(void **state);

#endif // _TEST__F_socket__sockets_decimate_by
