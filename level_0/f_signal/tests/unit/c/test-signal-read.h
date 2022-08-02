/**
 * FLL - Level 0
 *
 * Project: Signal
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the signal project.
 */
#ifndef _TEST__F_signal_read_h
#define _TEST__F_signal_read_h

/**
 * Test that function fails.
 *
 * @see f_signal_read()
 */
extern void test__f_signal_read__fails(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_signal_read()
 */
extern void test__f_signal_read__parameter_checking(void **state);

/**
 * Test that function works.
 *
 * @see f_signal_read()
 */
extern void test__f_signal_read__works(void **state);

#endif // _TEST__F_signal_read_h
