/**
 * FLL - Level 0
 *
 * Project: Time
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the time project.
 */
#ifndef _TEST__F_time_spec_nanosecond_h
#define _TEST__F_time_spec_nanosecond_h

/**
 * Test that function fails due to an overflow.
 *
 * @see f_time_spec_nanosecond()
 */
extern void test__f_time_spec_nanosecond__number_overflow(void **state);

/**
 * Test that function fails due to an underflow.
 *
 * @see f_time_spec_nanosecond()
 */
extern void test__f_time_spec_nanosecond__number_underflow(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_time_spec_nanosecond()
 */
extern void test__f_time_spec_nanosecond__parameter_checking(void **state);

/**
 * Test that function works.
 *
 * @see f_time_spec_nanosecond()
 */
extern void test__f_time_spec_nanosecond__works(void **state);

#endif // _TEST__F_time_spec_nanosecond_h
