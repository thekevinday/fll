/**
 * FLL - Level 0
 *
 * Project: Print
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the print project.
 */
#ifndef _TEST__F_print_except_in_h
#define _TEST__F_print_except_in_h

/**
 * Test that function fails.
 *
 * @see f_print_except_in()
 */
extern void test__f_print_except_in__fails(void **state);

/**
 * Test that function works but returns F_data_not.
 *
 * @see f_print_except_in()
 */
extern void test__f_print_except_in__returns_data_not(void **state);

/**
 * Test that function works but returns F_stream_not.
 *
 * @see f_print_except_in()
 */
extern void test__f_print_except_in__returns_stream_not(void **state);

/**
 * Test that function works.
 *
 * @see f_print_except_in()
 */
extern void test__f_print_except_in__works(void **state);

#endif // _TEST__F_print_except_in_h
