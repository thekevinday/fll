/**
 * FLL - Level 0
 *
 * Project: Thread
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the thread project.
 */
#ifndef _TEST__F_thread__semaphore_value_get_h
#define _TEST__F_thread__semaphore_value_get_h

/**
 * Test that function fails.
 *
 * @see f_thread_semaphore_value_get()
 */
extern void test__f_thread_semaphore_value_get__fails(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_thread_semaphore_value_get()
 */
extern void test__f_thread_semaphore_value_get__parameter_checking(void **state);

/**
 * Test that function works.
 *
 * @see f_thread_semaphore_value_get()
 */
extern void test__f_thread_semaphore_value_get__works(void **state);

#endif // _TEST__F_thread__semaphore_value_get_h
