/**
 * FLL - Level 0
 *
 * Project: Capability
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the capability project.
 */
#ifndef _TEST__F_capability__ambient_set_h
#define _TEST__F_capability__ambient_set_h

/**
 * Test that function fails.
 *
 * @see f_capability_ambient_set()
 */
extern void test__f_capability_ambient_set__fails(void **state);

// f_capability_ambient_reset() doesn't use parameter checking.

/**
 * Test that function works.
 *
 * @see f_capability_ambient_set()
 */
extern void test__f_capability_ambient_set__works(void **state);

#endif // _TEST__F_capability__ambient_set_h
