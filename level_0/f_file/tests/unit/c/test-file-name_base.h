/**
 * FLL - Level 0
 *
 * Project: File
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the file project.
 */
#ifndef _TEST__F_file_name_base_h
#define _TEST__F_file_name_base_h

/**
 * Test that parameter checking works as expected.
 *
 * @see f_file_name_base()
 */
extern void test__f_file_name_base__parameter_checking(void **state);

/**
 * Test that function works but the path is empty.
 *
 * @see f_file_name_base()
 */
extern void test__f_file_name_base__returns_data_not(void **state);

/**
 * Test that function works.
 *
 * @see f_file_name_base()
 */
extern void test__f_file_name_base__works(void **state);

#endif // _TEST__F_file_name_base_h
