/**
 * FLL - Level 0
 *
 * Project: Account
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the account project.
 */
#ifndef _TEST__F_account_name_user_by_id_h
#define _TEST__F_account_name_user_by_id_h

/**
 * Test that function fails.
 *
 * @see f_account_name_by_id()
 */
extern void test__f_account_name_by_id__fails(void **state);

/**
 * Test that function works but the group does not exist.
 *
 * @see f_account_name_by_id()
 */
extern void test__f_account_name_by_id__not_found(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_account_name_by_id()
 */
extern void test__f_account_name_by_id__parameter_checking(void **state);

/**
 * Test that function works.
 *
 * @see f_account_name_by_id()
 */
extern void test__f_account_name_by_id__works(void **state);

#endif // _TEST__F_account_name_user_by_id_h
