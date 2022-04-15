/**
 * FLL - Level 0
 *
 * Project: Directory
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the directory project.
 */
#ifndef _TEST__F_directory_exists_h
#define _TEST__F_directory_exists_h

/**
 * Test that function fails.
 *
 * @see f_directory_exists()
 */
extern void test__f_directory_exists__fails(void **state);

/**
 * Test that function works but the path is empty.
 *
 * @see f_directory_exists()
 */
extern void test__f_directory_exists__returns_data_not(void **state);

/**
 * Test that function works and returns F_false.
 *
 * @see f_directory_exists()
 */
extern void test__f_directory_exists__returns_false(void **state);

/**
 * Test that function works and returns F_true.
 *
 * @see f_directory_exists()
 */
extern void test__f_directory_exists__returns_true(void **state);

#endif // _TEST__F_directory_exists_h