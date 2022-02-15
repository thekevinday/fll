/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the array types in the type project.
 */
#ifndef _TEST__F_type_array__uint128ss_append
#define _TEST__F_type_array__uint128ss_append

/**
 * Test that the function works.
 *
 * @see f_type_array_uint128ss_append()
 */
extern void test__f_type_array_uint128ss_append__works(void **state);

/**
 * Test that the function returns F_data_not when asked to copy an empty structure.
 *
 * @see f_type_array_uint128ss_append()
 */
extern void test__f_type_array_uint128ss_append__returns_data_not(void **state);

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_type_array_uint128ss_append()
 */
extern void test__f_type_array_uint128ss_append__fails_on_invalid_parameter(void **state);

#endif // _TEST__F_type_array__uint128ss_append
