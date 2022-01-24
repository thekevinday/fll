/**
 * FLL - Level 0
 *
 * Project: Capability
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the capability project.
 */
#ifndef _TEST__F_capability__ambient_get_h
#define _TEST__F_capability__ambient_get_h

/**
 * Test that function fails.
 *
 * @see f_capability_ambient_get()
 */
extern void test__f_capability_ambient_get__fails(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_capability_ambient_get()
 */
#ifndef _di_level_0_parameter_checking_
  extern void test__f_capability_ambient_get__parameter_checking(void **state);
#endif // _di_level_0_parameter_checking_

/**
 * Test that function works.
 *
 * @see f_capability_ambient_get()
 */
extern void test__f_capability_ambient_get__works(void **state);

#endif // _TEST__F_capability__ambient_get_h
