/**
 * FLL - Level 0
 *
 * Project: File
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the file project.
 */
#ifndef _TEST__F_file_size_by_id_h
#define _TEST__F_file_size_by_id_h

/**
 * Test that function fails.
 *
 * @see f_file_size_by_id()
 */
extern void test__f_file_size_by_id__fails(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_file_size_by_id()
 */
extern void test__f_file_size_by_id__parameter_checking(void **state);

/**
 * Test that function works but the file is closed.
 *
 * @see f_file_size_by_id()
 */
extern void test__f_file_size_by_id__returns_file_closed(void **state);

/**
 * Test that function works.
 *
 * @see f_file_size_by_id()
 */
extern void test__f_file_size_by_id__works(void **state);

#endif // _TEST__F_file_size_by_id_h
