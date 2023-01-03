/**
 * FLL - Level 0
 *
 * Project: Signal
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the signal project.
 */
#ifndef _TEST__F_signal_close_h
#define _TEST__F_signal_close_h

/**
 * Test that function fails.
 *
 * @see f_signal_close()
 */
extern void test__f_signal_close__fails(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_signal_close()
 */
extern void test__f_signal_close__parameter_checking(void **state);

/**
 * Test that function works but returns F_data_not when file descriptor is -1.
 *
 * @see f_signal_close()
 */
extern void test__f_signal_close__returns_data_not(void **state);

/**
 * Test that function works.
 *
 * @see f_signal_close()
 */
extern void test__f_signal_close__works(void **state);

#endif // _TEST__F_signal_close_h
