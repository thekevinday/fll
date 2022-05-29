/**
 * FLL - Level 0
 *
 * Project: File
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the file project.
 */
#ifndef _TEST__F_file_stream_close_h
#define _TEST__F_file_stream_close_h

/**
 * Test that function fails for a file using the file descriptor.
 *
 * @see f_file_stream_close()
 */
extern void test__f_file_stream_close__fails_for_file_descriptor(void **state);

/**
 * Test that function fails for a file stream.
 *
 * @see f_file_stream_close()
 */
extern void test__f_file_stream_close__fails_for_stream(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_file_stream_close()
 */
extern void test__f_file_stream_close__parameter_checking(void **state);

/**
 * Test that function works.
 *
 * @see f_file_stream_close()
 */
extern void test__f_file_stream_close__works(void **state);

#endif // _TEST__F_file_stream_close_h
