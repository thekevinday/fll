/**
 * FLL - Level 0
 *
 * Project: File
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the file project.
 */
#ifndef _TEST__F_file_manipulate_h
#define _TEST__F_file_manipulate_h

/**
 * Test that function fails.
 *
 * @see f_file_manipulate()
 */
extern void test__f_file_manipulate__fails(void **state);

/**
 * Test that function works but the descriptor is not valid.
 *
 * @see f_file_manipulate()
 */
extern void test__f_file_manipulate__returns_file_descriptor_not(void **state);

/**
 * Test that function works.
 *
 * @see f_file_manipulate()
 */
extern void test__f_file_manipulate__works(void **state);

#endif // _TEST__F_file_manipulate_h
