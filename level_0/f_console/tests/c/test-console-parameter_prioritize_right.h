/**
 * FLL - Level 0
 *
 * Project: Console
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the console project.
 */
#ifndef _TEST__F_console_parameter_prioritize_right_h
#define _TEST__F_console_parameter_prioritize_right_h

/**
 * Test that function fails.
 *
 * @see f_console_parameter_prioritize_right()
 */
extern void test__f_console_parameter_prioritize_right__fails(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_console_parameter_prioritize_right()
 */
#ifndef _di_level_0_parameter_checking_
  extern void test__f_console_parameter_prioritize_right__parameter_checking(void **state);
#endif // _di_level_0_parameter_checking_

/**
 * Test that function works.
 *
 * @see f_console_parameter_prioritize_right()
 */
extern void test__f_console_parameter_prioritize_right__works(void **state);

#endif // _TEST__F_console_parameter_prioritize_right_h
