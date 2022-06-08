/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test nests increase in the fss project.
 */
#ifndef _TEST__F_fss__nests_increase
#define _TEST__F_fss__nests_increase

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_fss_nests_increase()
 */
extern void test__f_fss_nests_increase__parameter_checking(void **state);

/**
 * Test that the function returns F_data_not.
 *
 * @see f_fss_nests_increase()
 */
extern void test__f_fss_nests_increase__returns_data_not(void **state);

/**
 * Test that the function works.
 *
 * @see f_fss_nests_increase()
 */
extern void test__f_fss_nests_increase__works(void **state);

#endif // _TEST__F_fss__nests_increase