/**
 * FLL - Level 0
 *
 * Project: Random
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the array shuffle function in the random project.
 */
#ifndef _TEST__F_random_array_shuffle_h
#define _TEST__F_random_array_shuffle_h

/**
 * Test that the function fails.
 *
 * @see f_random_array_shuffle()
 */
extern void test__f_random_array_shuffle__fails(void **state);

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_random_array_shuffle()
 */
extern void test__f_random_array_shuffle__parameter_checking(void **state);

/**
 * Test that the function returns F_data_not.
 *
 * @see f_random_array_shuffle()
 */
extern void test__f_random_array_shuffle__returns_data_not(void **state);

/**
 * Test that the function returns F_too_small (with error bit).
 *
 * @see f_random_array_shuffle()
 */
extern void test__f_random_array_shuffle__returns_too_small(void **state);

/**
 * Test that the function works.
 *
 * @see f_random_array_shuffle()
 */
extern void test__f_random_array_shuffle__works(void **state);

#endif // _TEST__F_random_array_shuffle_h
