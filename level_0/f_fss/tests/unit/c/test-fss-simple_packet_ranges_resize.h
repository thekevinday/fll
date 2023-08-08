/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test set quote resize in the fss project.
 */
#ifndef _TEST__F_fss__simple_packet_range_resize
#define _TEST__F_fss__simple_packet_range_resize

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_fss_simple_packet_ranges_resize()
 */
extern void test__f_fss_simple_packet_ranges_resize__parameter_checking(void **state);

/**
 * Test that the function works.
 *
 * @see f_fss_simple_packet_ranges_resize()
 */
extern void test__f_fss_simple_packet_ranges_resize__works(void **state);

#endif // _TEST__F_fss__simple_packet_range_resize