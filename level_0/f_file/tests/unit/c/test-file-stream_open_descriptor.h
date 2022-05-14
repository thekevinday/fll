/**
 * FLL - Level 0
 *
 * Project: File
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the file project.
 */
#ifndef _TEST__F_file_stream_open_descriptor_h
#define _TEST__F_file_stream_open_descriptor_h

/**
 * Test that function fails.
 *
 * @see f_file_stream_open_descriptor()
 */
extern void test__f_file_stream_open_descriptor__fails(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_file_stream_open_descriptor()
 */
#ifndef _di_level_0_parameter_checking_
  extern void test__f_file_stream_open_descriptor__parameter_checking(void **state);
#endif // _di_level_0_parameter_checking_

/**
 * Test that function works.
 *
 * @see f_file_stream_open_descriptor()
 */
extern void test__f_file_stream_open_descriptor__works(void **state);

#endif // _TEST__F_file_stream_open_descriptor_h