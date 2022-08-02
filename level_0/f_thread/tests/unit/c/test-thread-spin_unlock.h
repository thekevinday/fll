/**
 * FLL - Level 0
 *
 * Project: Thread
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the thread project.
 */
#ifndef _TEST__F_thread__spin_unlock_h
#define _TEST__F_thread__spin_unlock_h

/**
 * Test that function fails.
 *
 * @see f_thread_spin_unlock()
 */
extern void test__f_thread_spin_unlock__fails(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_thread_spin_unlock()
 */
extern void test__f_thread_spin_unlock__parameter_checking(void **state);

/**
 * Test that function works.
 *
 * @see f_thread_spin_unlock()
 */
extern void test__f_thread_spin_unlock__works(void **state);

#endif // _TEST__F_thread__spin_unlock_h
