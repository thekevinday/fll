/**
 * FLL - Level 0
 *
 * Project: Account
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the account project.
 */
#ifndef _TEST__F_account_id_user_by_name_
#define _TEST__F_account_id_user_by_name_

/**
 * Test that function fails.
 *
 * @see f_account_id_by_name()
 */
extern void test__f_account_id_by_name__fails(void **state);

/**
 * Test that function works but the group does not exist.
 *
 * @see f_account_id_by_name()
 */
extern void test__f_account_id_by_name__not_found(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_account_id_by_name()
 */
#ifndef _di_level_0_parameter_checking_
  extern void test__f_account_id_by_name__parameter_checking(void **state);
#endif // _di_level_0_parameter_checking_

/**
 * Test that function works.
 *
 * @see f_account_id_by_name()
 */
extern void test__f_account_id_by_name__works(void **state);

#endif // _TEST__F_account_id_user_by_name_
