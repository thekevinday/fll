/**
 * FLL - Level 0
 *
 * Project: Color
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the color project.
 */
#ifndef _TEST__F_color__load_context_h
#define _TEST__F_color__load_context_h

// f_color_load_context() only returns failures by other functions that have their own tests.

/**
 * Test that parameter checking works as expected.
 *
 * @see f_color_load_context()
 */
extern void test__f_color_load_context__parameter_checking(void **state);

/**
 * Test that function works.
 *
 * @see f_color_load_context()
 */
extern void test__f_color_load_context__works(void **state);

#endif // _TEST__F_color__load_context
