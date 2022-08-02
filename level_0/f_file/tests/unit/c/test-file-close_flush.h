/**
 * FLL - Level 0
 *
 * Project: File
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the file project.
 */
#ifndef _TEST__F_file_close_flush_h
#define _TEST__F_file_close_flush_h

/**
 * Test that function fails.
 *
 * @see f_file_close_flush()
 */
extern void test__f_file_close_flush__fails(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_file_close_flush()
 */
extern void test__f_file_close_flush__parameter_checking(void **state);

/**
 * Test that function works.
 *
 * @see f_file_close_flush()
 */
extern void test__f_file_close_flush__works(void **state);

/**
 * Test that function works.
 *
 * @see f_file_close_flush()
 */
extern void test__f_file_close_flush__works_already_closed(void **state);

#endif // _TEST__F_file_close_flush_h
