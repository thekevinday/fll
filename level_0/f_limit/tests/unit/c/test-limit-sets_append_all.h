/**
 * FLL - Level 0
 *
 * Project: Limit
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the array types in the limit project.
 */
#ifndef _TEST__F_limit__sets_append_all
#define _TEST__F_limit__sets_append_all

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_limit_sets_append_all()
 */
extern void test__f_limit_sets_append_all__parameter_checking(void **state);

/**
 * Test that the function returns F_data_not when asked to copy an empty structure.
 *
 * @see f_limit_sets_append_all()
 */
extern void test__f_limit_sets_append_all__returns_data_not(void **state);

/**
 * Test that the function works.
 *
 * @see f_limit_sets_append_all()
 */
extern void test__f_limit_sets_append_all__works(void **state);

#endif // _TEST__F_limit__sets_append_all
