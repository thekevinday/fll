/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the array types in the type project.
 */
#ifndef _TEST__F_type_array__pollss_append
#define _TEST__F_type_array__pollss_append

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_pollss_append()
 */
extern void test__f_type_array_pollss_append__parameter_checking(void **poll);

/**
 * Test that the function returns F_data_not.
 *
 * @see f_pollss_append()
 */
extern void test__f_type_array_pollss_append__returns_data_not(void **poll);

/**
 * Test that the function works.
 *
 * @see f_pollss_append()
 */
extern void test__f_type_array_pollss_append__works(void **poll);

#endif // _TEST__F_type_array__pollss_append
