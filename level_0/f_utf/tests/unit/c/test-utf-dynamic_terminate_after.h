/**
 * FLL - Level 0
 *
 * Project: UTF
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the data types in the utf project.
 */
#ifndef _TEST__F_utf_dynamic_terminate_after_h
#define _TEST__F_utf_dynamic_terminate_after_h

/**
 * Test that the function appends a new line.
 *
 * @see f_utf_string_dynamic_terminate_after()
 */
extern void test__f_utf_dynamic_terminate_after__appends_null(void **state);

/**
 * Test that the function does not append a new line.
 *
 * @see f_utf_string_dynamic_terminate_after()
 */
extern void test__f_utf_dynamic_terminate_after__doesnt_append_null(void **state);

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_utf_string_dynamic_terminate_after()
 */
extern void test__f_utf_dynamic_terminate_after__parameter_checking(void **state);

#endif // _TEST__F_utf_dynamic_terminate_after_h
