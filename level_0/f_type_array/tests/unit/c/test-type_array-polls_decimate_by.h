/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the array types in the type project.
 */
#ifndef _TEST__F_type_array__polls_decimate_by
#define _TEST__F_type_array__polls_decimate_by

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_polls_decimate_by()
 */
extern void test__f_type_array_polls_decimate_by__parameter_checking(void **poll);

/**
 * Test that the function returns F_data_not.
 *
 * @see f_polls_decimate_by()
 */
extern void test__f_type_array_polls_decimate_by__returns_data_not(void **poll);

/**
 * Test that the function works.
 *
 * @see f_polls_decimate_by()
 */
extern void test__f_type_array_polls_decimate_by__works(void **poll);

#endif // _TEST__F_type_array__polls_decimate_by
