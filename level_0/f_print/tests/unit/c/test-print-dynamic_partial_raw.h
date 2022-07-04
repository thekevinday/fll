/**
 * FLL - Level 0
 *
 * Project: Print
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the print project.
 */
#ifndef _TEST__F_print_dynamic_partial_raw_h
#define _TEST__F_print_dynamic_partial_raw_h

/**
 * Test that function fails.
 *
 * @see f_print_dynamic_partial_raw()
 */
extern void test__f_print_dynamic_partial_raw__fails(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_print_dynamic_partial_raw()
 */
extern void test__f_print_dynamic_partial_raw__parameter_checking(void **state);

/**
 * Test that function works but returns F_data_not.
 *
 * @see f_print_dynamic_partial_raw()
 */
extern void test__f_print_dynamic_partial_raw__returns_data_not(void **state);

/**
 * Test that function works.
 *
 * @see f_print_dynamic_partial_raw()
 */
extern void test__f_print_dynamic_partial_raw__works(void **state);

#endif // _TEST__F_print_dynamic_partial_raw_h
