/**
 * FLL - Level 0
 *
 * Project: Account
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the array types in the type project.
 */
#ifndef _TEST__F_account_ss_append
#define _TEST__F_account_ss_append

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_accountss_append()
 */
extern void test__f_accountss_append__parameter_checking(void **state);

/**
 * Test that the function returns F_data_not.
 *
 * @see f_accountss_append()
 */
extern void test__f_accountss_append__returns_data_not(void **state);

/**
 * Test that the function works.
 *
 * @see f_accountss_append()
 */
extern void test__f_accountss_append__works(void **state);

#endif // _TEST__F_account_ss_append
