/**
 * FLL - Level 0
 *
 * Project: File
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the file project.
 */
#ifndef _TEST__F_file_copy_h
#define _TEST__F_file_copy_h

/**
 * Test that function fails when performing read and write.
 *
 * @see f_file_copy()
 */
extern void test__f_file_copy__fails_during_read_write(void **state);

/**
 * Test that function fails for files of type block.
 *
 * @see f_file_copy()
 */
extern void test__f_file_copy__fails_for_block(void **state);

/**
 * Test that function fails for files of type character.
 *
 * @see f_file_copy()
 */
extern void test__f_file_copy__fails_for_character(void **state);

/**
 * Test that function fails for files of type directory.
 *
 * @see f_file_copy()
 */
extern void test__f_file_copy__fails_for_directory(void **state);

/**
 * Test that function fails for files of type file-in/file-out.
 *
 * @see f_file_copy()
 */
extern void test__f_file_copy__fails_for_fifo(void **state);

/**
 * Test that function fails for files of type link.
 *
 * @see f_file_copy()
 */
extern void test__f_file_copy__fails_for_link(void **state);

/**
 * Test that function fails for files of type regular.
 *
 * @see f_file_copy()
 */
extern void test__f_file_copy__fails_for_regular(void **state);

/**
 * Test that function fails for files of type socket.
 *
 * @see f_file_copy()
 */
extern void test__f_file_copy__fails_for_socket(void **state);

/**
 * Test that function works but the path is empty.
 *
 * @see f_file_copy()
 */
extern void test__f_file_copy__returns_data_not(void **state);

/**
 * Test that function works for files of type block.
 *
 * @see f_file_copy()
 */
extern void test__f_file_copy__works_for_block(void **state);

/**
 * Test that function works for files of type character.
 *
 * @see f_file_copy()
 */
extern void test__f_file_copy__works_for_character(void **state);

/**
 * Test that function works for files of type directory.
 *
 * @see f_file_copy()
 */
extern void test__f_file_copy__works_for_directory(void **state);

/**
 * Test that function works for files of type file-in/file-out.
 *
 * @see f_file_copy()
 */
extern void test__f_file_copy__works_for_fifo(void **state);

/**
 * Test that function works for files of type link.
 *
 * @see f_file_copy()
 */
extern void test__f_file_copy__works_for_link(void **state);

/**
 * Test that function works for files of type regular.
 *
 * @see f_file_copy()
 */
extern void test__f_file_copy__works_for_regular(void **state);

/**
 * Test that function works for files of type socket.
 *
 * @see f_file_copy()
 */
extern void test__f_file_copy__works_for_socket(void **state);

#endif // _TEST__F_file_copy_h
