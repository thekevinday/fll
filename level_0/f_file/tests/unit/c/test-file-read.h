/**
 * FLL - Level 0
 *
 * Project: File
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the file project.
 */
#ifndef _TEST__F_file_read_h
#define _TEST__F_file_read_h

/**
 * Test that function fails.
 *
 * @see f_file_read()
 */
extern void test__f_file_read__fails(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_file_read()
 */
extern void test__f_file_read__parameter_checking(void **state);

/**
 * Test that function works but the file is closed.
 *
 * @see f_file_read()
 */
extern void test__f_file_read__returns_file_closed(void **state);

/**
 * Test that function works.
 *
 * @see f_file_read()
 */
extern void test__f_file_read__works(void **state);

#endif // _TEST__F_file_read_h
