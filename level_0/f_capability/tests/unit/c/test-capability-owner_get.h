/**
 * FLL - Level 0
 *
 * Project: Capability
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the capability project.
 */
#ifndef _TEST__F_capability__owner_get_h
#define _TEST__F_capability__owner_get_h

// cap_mode_name() doesn't return failure.

/**
 * Test that parameter checking works as expected.
 *
 * @see f_capability_owner_get()
 */
extern void test__f_capability_owner_get__parameter_checking(void **state);

/**
 * Test that function works.
 *
 * @see f_capability_owner_get()
 */
extern void test__f_capability_owner_get__works(void **state);

#endif // _TEST__F_capability__owner_get_h
