/**
 * FLL - Level 0
 *
 * Project: Environment
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the environment project.
 */
#ifndef _TEST__F_environment_get_h
#define _TEST__F_environment_get_h

/**
 * Test that function fails.
 *
 * @see f_environment_get()
 */
extern void test__f_environment_get__fails(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_environment_get()
 */
extern void test__f_environment_get__parameter_checking(void **state);

/**
 * Test that function works but the path is empty.
 *
 * @see f_environment_get()
 */
extern void test__f_environment_get__returns_data_not(void **state);

/**
 * Test that function works.
 *
 * @see f_environment_get()
 */
extern void test__f_environment_get__works(void **state);

#endif // _TEST__F_environment_get_h
