/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test set quote adjust in the fss project.
 */
#ifndef _TEST__F_fss__simple_packet_range_adjust
#define _TEST__F_fss__simple_packet_range_adjust

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_memory_array_adjust()
 */
extern void test__f_memory_array_adjust__parameter_checking(void **state);

/**
 * Test that the function returns F_array_too_large.
 *
 * @see f_memory_array_adjust()
 */
extern void test__f_memory_array_adjust__returns_array_too_large(void **state);

/**
 * Test that the function works.
 *
 * @see f_memory_array_adjust()
 */
extern void test__f_memory_array_adjust__works(void **state);

#endif // _TEST__F_fss__simple_packet_range_adjust
