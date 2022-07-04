/**
 * FLL - Level 0
 *
 * Project: File
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the file project.
 */
#ifndef _TEST__F_file_stream_write_until_h
#define _TEST__F_file_stream_write_until_h

/**
 * Test that function fails.
 *
 * @see f_file_stream_write_until()
 */
extern void test__f_file_stream_write_until__fails(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_file_stream_write_until()
 */
extern void test__f_file_stream_write_until__parameter_checking(void **state);

/**
 * Test that function works but the file stream is closed.
 *
 * @see f_file_stream_write_until()
 */
extern void test__f_file_stream_write_until__returns_file_closed(void **state);

/**
 * Test that function works but the path is empty.
 *
 * @see f_file_stream_write_until()
 */
extern void test__f_file_stream_write_until__returns_data_not(void **state);

/**
 * Test that function works.
 *
 * @see f_file_stream_write_until()
 */
extern void test__f_file_stream_write_until__works(void **state);

#endif // _TEST__F_file_stream_write_until_h
