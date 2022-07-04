/**
 * FLL - Level 0
 *
 * Project: Environment
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the environment project.
 */
#ifndef _TEST__F_environment_exists_h
#define _TEST__F_environment_exists_h

/**
 * Test that function fails.
 *
 * @see f_environment_exists()
 */
extern void test__f_environment_exists__fails(void **state);

/**
 * Test that function works but the path is empty.
 *
 * @see f_environment_exists()
 */
extern void test__f_environment_exists__returns_data_not(void **state);

/**
 * Test that function works.
 *
 * @see f_environment_exists()
 */
extern void test__f_environment_exists__works(void **state);

#endif // _TEST__F_environment_exists_h
