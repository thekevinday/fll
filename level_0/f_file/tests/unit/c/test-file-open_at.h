/**
 * FLL - Level 0
 *
 * Project: File
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the file project.
 */
#ifndef _TEST__F_file_open_at_h
#define _TEST__F_file_open_at_h

/**
 * Test that function fails.
 *
 * @see f_file_open_at()
 */
extern void test__f_file_open_at__fails(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_file_open_at()
 */
extern void test__f_file_open_at__parameter_checking(void **state);

/**
 * Test that function works but the path is empty.
 *
 * @see f_file_open_at()
 */
extern void test__f_file_open_at__returns_data_not(void **state);

/**
 * Test that function works but the descriptor is not valid.
 *
 * @see f_file_open_at()
 */
extern void test__f_file_open_at__returns_file_descriptor_not(void **state);

/**
 * Test that function works.
 *
 * @see f_file_open_at()
 */
extern void test__f_file_open_at__works(void **state);

#endif // _TEST__F_file_open_at_h
