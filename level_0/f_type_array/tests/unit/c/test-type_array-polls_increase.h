/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the array types in the type project.
 */
#ifndef _TEST__F_type_array__polls_increase
#define _TEST__F_type_array__polls_increase

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_polls_increase()
 */
extern void test__f_type_array_polls_increase__parameter_checking(void **poll);

/**
 * Test that the function returns F_data_not.
 *
 * @see f_polls_increase()
 */
extern void test__f_type_array_polls_increase__returns_data_not(void **poll);

/**
 * Test that the function works.
 *
 * @see f_polls_increase()
 */
extern void test__f_type_array_polls_increase__works(void **poll);

#endif // _TEST__F_type_array__polls_increase
