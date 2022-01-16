/**
 * FLL - Level 0
 *
 * Project: Account
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the account project.
 */
#ifndef _TEST__F_account_by_id_
#define _TEST__F_account_by_id_

/**
 * Test that function fails.
 *
 * @see f_account_by_id()
 */
extern void test__f_account_by_id__fails(void **state);

/**
 * Test that function works but the account does not exist.
 *
 * @see f_account_by_id()
 */
extern void test__f_account_by_id__not_found(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_account_by_id()
 */
#ifndef _di_level_0_parameter_checking_
  extern void test__f_account_by_id__parameter_checking(void **state);
#endif // _di_level_0_parameter_checking_

/**
 * Test that function works.
 *
 * @see f_account_by_id()
 */
extern void test__f_account_by_id__works(void **state);

#endif // _TEST__F_account_by_id_
