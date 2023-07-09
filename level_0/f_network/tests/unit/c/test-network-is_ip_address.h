/**
 * FLL - Level 0
 *
 * Project: Network
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the network project.
 */
#ifndef _TEST__F_network_is_ip_address_h
#define _TEST__F_network_is_ip_address_h

/**
 * Test that function works but address.used is 0.
 *
 * @see f_network_is_ip_address()
 */
extern void test__f_network_is_ip_address__returns_data_not(void **state);

/**
 * Test that function works and returns F_false.
 *
 * @see f_network_is_ip_address()
 */
extern void test__f_network_is_ip_address__returns_false(void **state);

/**
 * Test that function works and returns F_network_version_four.
 *
 * @see f_network_is_ip_address()
 */
extern void test__f_network_is_ip_address__returns_network_version_four(void **state);

/**
 * Test that function works and returns F_network_version_four_not.
 *
 * @see f_network_is_ip_address()
 */
extern void test__f_network_is_ip_address__returns_network_version_four_not(void **state);

/**
 * Test that function works and returns F_network_version_six.
 *
 * @see f_network_is_ip_address()
 */
extern void test__f_network_is_ip_address__returns_network_version_six(void **state);

/**
 * Test that function works and returns F_network_version_six_not.
 *
 * @see f_network_is_ip_address()
 */
extern void test__f_network_is_ip_address__returns_network_version_six_not(void **state);

#endif // _TEST__F_network_is_ip_address_h
