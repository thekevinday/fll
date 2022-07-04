/**
 * FLL - Level 0
 *
 * Project: Thread
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the array types in the thread project.
 */
#ifndef _TEST__F_thread__thread_ids_increase_by
#define _TEST__F_thread__thread_ids_increase_by

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_thread_ids_increase_by()
 */
extern void test__f_thread_ids_increase_by__parameter_checking(void **state);

/**
 * Test that the function returns F_data_not.
 *
 * @see f_thread_ids_increase_by()
 */
extern void test__f_thread_ids_increase_by__returns_data_not(void **state);

/**
 * Test that the function works.
 *
 * @see f_thread_ids_increase_by()
 */
extern void test__f_thread_ids_increase_by__works(void **state);

#endif // _TEST__F_thread__thread_ids_increase_by
