/**
 * FLL - Level 0
 *
 * Project: File
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the file project.
 */
#ifndef _TEST__F_file_seek_h
#define _TEST__F_file_seek_h

/**
 * Test that function fails.
 *
 * @see f_file_seek()
 */
extern void test__f_file_seek__fails(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_file_seek()
 */
extern void test__f_file_seek__parameter_checking(void **state);

/**
 * Test that function works.
 *
 * @see f_file_seek()
 */
extern void test__f_file_seek__works(void **state);

#endif // _TEST__F_file_seek_h
