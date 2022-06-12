/**
 * FLL - Level 0
 *
 * Project: UTF
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the data types in the utf project.
 */
#ifndef _TEST__F_utf_dynamic_increase_h
#define _TEST__F_utf_dynamic_increase_h

/**
 * Test that the function works.
 *
 * @see f_utf_string_dynamic_increase()
 */
extern void test__f_utf_dynamic_increase__works(void **state);

/**
 * Test that the function returns F_data_not when asked to copy an empty structure.
 *
 * @see f_utf_string_dynamic_increase()
 */
extern void test__f_utf_dynamic_increase__returns_data_not(void **state);

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_utf_string_dynamic_increase()
 */
extern void test__f_utf_dynamic_increase__parameter_checking(void **state);

#endif // _TEST__F_utf_dynamic_increase_h
