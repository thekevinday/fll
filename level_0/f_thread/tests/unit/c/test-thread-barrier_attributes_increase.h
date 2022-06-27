/**
 * FLL - Level 0
 *
 * Project: Thread
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the array types in the thread project.
 */
#ifndef _TEST__F_thread__thread_barrier_attributes_increase
#define _TEST__F_thread__thread_barrier_attributes_increase

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_thread_barrier_attributes_increase()
 */
extern void test__f_thread_barrier_attributes_increase__parameter_checking(void **state);

/**
 * Test that the function returns F_data_not.
 *
 * @see f_thread_barrier_attributes_increase()
 */
extern void test__f_thread_barrier_attributes_increase__returns_data_not(void **state);

/**
 * Test that the function works.
 *
 * @see f_thread_barrier_attributes_increase()
 */
extern void test__f_thread_barrier_attributes_increase__works(void **state);

#endif // _TEST__F_thread__thread_barrier_attributes_increase
