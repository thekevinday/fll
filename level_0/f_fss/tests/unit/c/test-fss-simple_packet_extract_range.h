/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the array types in the FSS project.
 */
#ifndef _TEST__F_fss__simple_packet_extract_range
#define _TEST__F_fss__simple_packet_extract_range

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_fss_simple_packet_extract_range()
 */
extern void test__f_fss_simple_packet_extract_range__parameter_checking(void **state);

/**
 * Test that the function returns F_packet_too_small.
 *
 * @see f_fss_simple_packet_extract_range()
 */
extern void test__f_fss_simple_packet_extract_range__returns_packet_too_small(void **state);

/**
 * Test that the function works, with the control bit set to big endian.
 *
 * @see f_fss_simple_packet_extract_range()
 */
extern void test__f_fss_simple_packet_extract_range__works_big_endian(void **state);

/**
 * Test that the function works, with the control bit set to little endian.
 *
 * @see f_fss_simple_packet_extract_range()
 */
extern void test__f_fss_simple_packet_extract_range__works_little_endian(void **state);

#endif // _TEST__F_fss__simple_packet_extract_range
