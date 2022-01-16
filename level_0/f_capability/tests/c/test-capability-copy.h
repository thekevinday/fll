/**
 * FLL - Level 0
 *
 * Project: Capability
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the capability project.
 */
#ifndef _TEST__F_capability__copy
#define _TEST__F_capability__copy

/**
 * Test that function fails.
 *
 * @see f_capability_copy()
 */
extern void test__f_capability_copy__fails(void **state);

/**
 * Test that function works.
 *
 * @see f_capability_copy()
 */
extern void test__f_capability_copy__works(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_capability_copy()
 */
#ifndef _di_level_0_parameter_checking_
  extern void test__f_capability_copy__parameter_checking(void **state);
#endif // _di_level_0_parameter_checking_

#endif // _TEST__F_capability__copy
