/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the array types in the type project.
 */
#ifndef _TEST__F_string_dynamic_terminate_h
#define _TEST__F_string_dynamic_terminate_h

/**
 * Test that the function appends a NULL.
 *
 * @see f_string_dynamic_terminate()
 */
extern void test__f_string_dynamic_terminate__appends_null(void **state);

/**
 * Test that the function does not append a NULL.
 *
 * @see f_string_dynamic_terminate()
 */
extern void test__f_string_dynamic_terminate__doesnt_append_null(void **state);

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_string_dynamic_terminate()
 */
extern void test__f_string_dynamic_terminate__parameter_checking(void **state);

#endif // _TEST__F_string_dynamic_terminate_h
