/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the array types in the type project.
 */
#ifndef _TEST__F_utf_dynamics_append_all_h
#define _TEST__F_utf_dynamics_append_all_h

/**
 * Test that the function works.
 *
 * @see f_utf_string_dynamics_append_all()
 */
extern void test__f_utf_dynamics_append_all__works(void **state);

/**
 * Test that the function returns F_data_not when asked to copy an empty structure.
 *
 * @see f_utf_string_dynamics_append_all()
 */
extern void test__f_utf_dynamics_append_all__returns_data_not(void **state);

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_utf_string_dynamics_append_all()
 */
extern void test__f_utf_dynamics_append_all__parameter_checking(void **state);

#endif // _TEST__F_utf_dynamics_append_all_h
