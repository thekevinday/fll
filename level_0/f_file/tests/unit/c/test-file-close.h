/**
 * FLL - Level 0
 *
 * Project: File
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the file project.
 */
#ifndef _TEST__F_file_close_h
#define _TEST__F_file_close_h

/**
 * Test that function fails.
 *
 * @see f_file_close()
 */
extern void test__f_file_close__fails(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_file_close()
 */
extern void test__f_file_close__parameter_checking(void **state);

/**
 * Test that function works but the descriptor is not valid.
 *
 * @see f_file_close()
 */
extern void test__f_file_close__returns_file_descriptor_not(void **state);

/**
 * Test that function works.
 *
 * @see f_file_close()
 */
extern void test__f_file_close__works(void **state);

#endif // _TEST__F_file_close_h
