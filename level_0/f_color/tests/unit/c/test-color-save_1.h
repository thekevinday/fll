/**
 * FLL - Level 0
 *
 * Project: Color
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the color project.
 */
#ifndef _TEST__F_color__save_1_h
#define _TEST__F_color__save_1_h

// f_color_save_1() only returns failures by other functions that have their own tests.

/**
 * Test that parameter checking works as expected.
 *
 * @see f_color_save_1()
 */
#ifndef _di_level_0_parameter_checking_
  extern void test__f_color_save_1_parameter_checking(void **state);
#endif // _di_level_0_parameter_checking_

/**
 * Test that function works.
 *
 * @see f_color_save_1()
 */
extern void test__f_color_save_1_works(void **state);

#endif // _TEST__F_color__save_1_h
