/**
 * FLL - Level 0
 *
 * Project: File
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the file project.
 */
#ifndef _TEST__F_file_create_fifo_at_h
#define _TEST__F_file_create_fifo_at_h

/**
 * Test that function fails.
 *
 * @see f_file_create_fifo_at()
 */
extern void test__f_file_create_fifo_at__fails(void **state);

/**
 * Test that function works but the path is empty.
 *
 * @see f_file_create_fifo_at()
 */
extern void test__f_file_create_fifo_at__returns_data_not(void **state);

/**
 * Test that function works.
 *
 * @see f_file_create_fifo_at()
 */
extern void test__f_file_create_fifo_at__works(void **state);

#endif // _TEST__F_file_create_fifo_at_h
