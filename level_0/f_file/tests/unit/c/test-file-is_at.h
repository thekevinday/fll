/**
 * FLL - Level 0
 *
 * Project: File
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the file project.
 */
#ifndef _TEST__F_file_is_at_h
#define _TEST__F_file_is_at_h

/**
 * Test that function fails.
 *
 * @see f_file_is_at()
 */
extern void test__f_file_is_at__fails(void **state);

/**
 * Test that function works but the path is empty.
 *
 * @see f_file_is_at()
 */
extern void test__f_file_is_at__returns_data_not(void **state);

/**
 * Test that function works but the path is empty.
 *
 * @see f_file_is_at()
 */
extern void test__f_file_is_at__returns_file_descriptor_not(void **state);

/**
 * Test that function works and returns F_false.
 *
 * @see f_file_is_at()
 */
extern void test__f_file_is_at__returns_false(void **state);

/**
 * Test that function works and returns F_true.
 *
 * @see f_file_is_at()
 */
extern void test__f_file_is_at__returns_true(void **state);

#endif // _TEST__F_file_is_at_h
