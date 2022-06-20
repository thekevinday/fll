/**
 * FLL - Level 0
 *
 * Project: Signal
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the signal project.
 */
#ifndef _TEST__F_signal_set_has_h
#define _TEST__F_signal_set_has_h

/**
 * Test that function fails.
 *
 * @see f_signal_set_has()
 */
extern void test__f_signal_set_has__fails(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_signal_set_has()
 */
extern void test__f_signal_set_has__parameter_checking(void **state);

/**
 * Test that function works.
 *
 * @see f_signal_set_has()
 */
extern void test__f_signal_set_has__works(void **state);

#endif // _TEST__F_signal_set_has_h