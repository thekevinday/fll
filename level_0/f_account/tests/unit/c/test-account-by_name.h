/**
 * FLL - Level 0
 *
 * Project: Account
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the account project.
 */
#ifndef _TEST__F_account_by_name_h
#define _TEST__F_account_by_name_h

/**
 * Test that function fails.
 *
 * @see f_account_by_name()
 */
extern void test__f_account_by_name__fails(void **state);

/**
 * Test that function works but the account does not exist.
 *
 * @see f_account_by_name()
 */
extern void test__f_account_by_name__not_found(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_account_by_name()
 */
extern void test__f_account_by_name__parameter_checking(void **state);

/**
 * Test that function works.
 *
 * @see f_account_by_name()
 */
extern void test__f_account_by_name__works(void **state);

#endif // _TEST__F_account_by_name_h
