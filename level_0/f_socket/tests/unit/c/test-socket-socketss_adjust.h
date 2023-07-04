/**
 * FLL - Level 0
 *
 * Project: Socket
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the array types in the type project.
 */
#ifndef _TEST__F_socket__socketss_adjust
#define _TEST__F_socket__socketss_adjust

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_socketss_adjust()
 */
extern void test__f_socket_socketss_adjust__parameter_checking(void **state);

/**
 * Test that the function returns F_data_not.
 *
 * @see f_socketss_increase_by()
 */
extern void test__f_socket_socketss_increase_by__returns_data_not(void **state);

/**
 * Test that the function works.
 *
 * @see f_socketss_adjust()
 */
extern void test__f_socket_socketss_adjust__works(void **state);

#endif // _TEST__F_socket__socketss_adjust
