/**
 * FLL - Level 0
 *
 * Project: Print
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the print project.
 */
#ifndef _TEST__F_print_to_except_raw_h
#define _TEST__F_print_to_except_raw_h

/**
 * Test that function fails.
 *
 * @see f_print_to_except_raw()
 */
extern void test__f_print_to_except_raw__fails(void **state);

/**
 * Test that function works but returns F_data_not.
 *
 * @see f_print_to_except_raw()
 */
extern void test__f_print_to_except_raw__returns_data_not(void **state);

/**
 * Test that function works but returns F_file_descriptor_not.
 *
 * @see f_print_to_except_raw()
 */
extern void test__f_print_to_except_raw__returns_file_descriptor_not(void **state);

/**
 * Test that function works.
 *
 * @see f_print_to_except_raw()
 */
extern void test__f_print_to_except_raw__works(void **state);

#endif // _TEST__F_print_to_except_raw_h
