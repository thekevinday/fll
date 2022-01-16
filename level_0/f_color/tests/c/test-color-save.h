/**
 * FLL - Level 0
 *
 * Project: Color
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the color project.
 */
#ifndef _TEST__F_color__save
#define _TEST__F_color__save

// f_color_save() only returns failures by other functions that have their own tests.

/**
 * Test that parameter checking works as expected.
 *
 * @see f_color_save()
 */
#ifndef _di_level_0_parameter_checking_
  extern void test__f_color_save__parameter_checking(void **state);
#endif // _di_level_0_parameter_checking_

/**
 * Test that function works.
 *
 * @see f_color_save()
 */
extern void test__f_color_save__works(void **state);

#endif // _TEST__F_color__save
