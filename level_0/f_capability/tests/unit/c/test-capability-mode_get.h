/**
 * FLL - Level 0
 *
 * Project: Capability
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the capability project.
 */
#ifndef _TEST__F_capability__mode_get_h
#define _TEST__F_capability__mode_get_h

// cap_get_mode() doesn't return failure.

/**
 * Test that parameter checking works as expected.
 *
 * @see f_capability_mode_get()
 */
extern void test__f_capability_mode_get__parameter_checking(void **state);

/**
 * Test that function works.
 *
 * @see f_capability_mode_get()
 */
extern void test__f_capability_mode_get__works(void **state);

#endif // _TEST__F_capability__mode_get_h
