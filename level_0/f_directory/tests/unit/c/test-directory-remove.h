/**
 * FLL - Level 0
 *
 * Project: Directory
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the directory project.
 */
#ifndef _TEST__F_directory_remove_h
#define _TEST__F_directory_remove_h

/**
 * Test that function fails.
 *
 * @see f_directory_remove()
 */
extern void test__f_directory_remove__fails(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_directory_remove()
 */
#ifndef _di_level_0_parameter_checking_
  extern void test__f_directory_remove__parameter_checking(void **state);
#endif // _di_level_0_parameter_checking_

/**
 * Test that function works but the path is empty.
 *
 * @see f_directory_remove()
 */
extern void test__f_directory_remove__returns_data_not(void **state);

/**
 * Test that function works.
 *
 * @see f_directory_remove()
 */
extern void test__f_directory_remove__works(void **state);

#endif // _TEST__F_directory_remove_h