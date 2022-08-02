/**
 * FLL - Level 0
 *
 * Project: File
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the file project.
 */
#ifndef _TEST__F_file_role_change_at_h
#define _TEST__F_file_role_change_at_h

/**
 * Test that function fails for dereferenced files.
 *
 * @see f_file_role_change_at()
 */
extern void test__f_file_role_change_at__fails_for_dereference(void **state);

/**
 * Test that function fails for referenced files.
 *
 * @see f_file_role_change_at()
 */
extern void test__f_file_role_change_at__fails_for_reference(void **state);

/**
 * Test that function works but the path is empty.
 *
 * @see f_file_role_change_at()
 */
extern void test__f_file_role_change_at__returns_data_not(void **state);

/**
 * Test that function works for dereferenced files.
 *
 * @see f_file_role_change_at()
 */
extern void test__f_file_role_change_at__works_for_dereference(void **state);

/**
 * Test that function works for referenced files.
 *
 * @see f_file_role_change_at()
 */
extern void test__f_file_role_change_at__works_for_reference(void **state);

#endif // _TEST__F_file_role_change_at_h
