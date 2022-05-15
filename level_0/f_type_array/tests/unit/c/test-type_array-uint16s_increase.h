/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the array types in the type project.
 */
#ifndef _TEST__F_type_array__uint16s_increase
#define _TEST__F_type_array__uint16s_increase

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_uint16s_increase()
 */
extern void test__f_type_array_uint16s_increase__parameter_checking(void **state);

/**
 * Test that the function returns F_data_not.
 *
 * @see f_uint16s_increase()
 */
extern void test__f_type_array_uint16s_increase__returns_data_not(void **state);

/**
 * Test that the function works.
 *
 * @see f_uint16s_increase()
 */
extern void test__f_type_array_uint16s_increase__works(void **state);

#endif // _TEST__F_type_array__uint16s_increase
