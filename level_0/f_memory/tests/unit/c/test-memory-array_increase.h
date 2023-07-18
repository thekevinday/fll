/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test set quote increase in the fss project.
 */
#ifndef _TEST__F_fss__simple_packet_range_increase
#define _TEST__F_fss__simple_packet_range_increase

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_memory_array_increase()
 */
extern void test__f_memory_array_increase__parameter_checking(void **state);

/**
 * Test that the function returns F_array_too_large.
 *
 * @see f_memory_array_increase()
 */
extern void test__f_memory_array_increase__returns_array_too_large(void **state);

/**
 * Test that the function returns F_data_not.
 *
 * @see f_memory_array_increase()
 */
extern void test__f_memory_array_increase__returns_data_not(void **state);

/**
 * Test that the function works.
 *
 * @see f_memory_array_increase()
 */
extern void test__f_memory_array_increase__works(void **state);

#endif // _TEST__F_fss__simple_packet_range_increase
