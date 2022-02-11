/**
 * FLL - Level 0
 *
 * Project: Control Group
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the control group project.
 */
#ifndef _TEST__F_control_group_copy_h
#define _TEST__F_control_group_copy_h

// f_control_group_copy() only returns memory failures.

/**
 * Test that parameter checking works as expected.
 *
 * @see f_control_group_copy()
 */
#ifndef _di_level_0_parameter_checking_
  extern void test__f_control_group_copy__parameter_checking(void **state);
#endif // _di_level_0_parameter_checking_

/**
 * Test that function works.
 *
 * @see f_control_group_copy()
 */
extern void test__f_control_group_copy__works(void **state);

#endif // _TEST__F_control_group_copy_h
