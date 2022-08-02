/**
 * FLL - Level 0
 *
 * Project: File
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the file project.
 */
#ifndef _TEST__F_file_clone_h
#define _TEST__F_file_clone_h

/**
 * Test that function fails when performing read and write.
 *
 * @see f_file_clone()
 */
extern void test__f_file_clone__fails_during_read_write(void **state);

/**
 * Test that function fails for files of type link.
 *
 * @see f_file_clone()
 */
extern void test__f_file_clone__fails_for_link(void **state);

/**
 * Test that function fails for non-regular and non-link file of types.
 *
 * @see f_file_clone()
 */
extern void test__f_file_clone__fails_for_other(void **state);

/**
 * Test that function fails for files of type regular.
 *
 * @see f_file_clone()
 */
extern void test__f_file_clone__fails_for_regular(void **state);

/**
 * Test that function works but the path is empty.
 *
 * @see f_file_clone()
 */
extern void test__f_file_clone__returns_data_not(void **state);

/**
 * Test that function works for files of type link.
 *
 * @see f_file_clone()
 */
extern void test__f_file_clone__works_for_link(void **state);

/**
 * Test that function works for files of type regular.
 *
 * @see f_file_clone()
 */
extern void test__f_file_clone__works_for_regular(void **state);

#endif // _TEST__F_file_clone_h
