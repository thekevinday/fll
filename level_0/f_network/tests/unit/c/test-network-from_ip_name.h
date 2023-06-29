/**
 * FLL - Level 0
 *
 * Project: Network
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the network project.
 */
#ifndef _TEST__F_network_from_ip_name_h
#define _TEST__F_network_from_ip_name_h

/**
 * Test that function fails.
 *
 * @see f_network_from_ip_name()
 */
extern void test__f_network_from_ip_name__fails(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_network_from_ip_name()
 */
extern void test__f_network_from_ip_name__parameter_checking(void **state);

/**
 * Test that function works but the string is empty or the address.type is 0.
 *
 * @see f_network_from_ip_name()
 */
extern void test__f_network_from_ip_name__returns_data_not(void **state);

/**
 * Test that function works.
 *
 * @see f_network_from_ip_name()
 */
extern void test__f_network_from_ip_name__works(void **state);

#endif // _TEST__F_network_from_ip_name_h
