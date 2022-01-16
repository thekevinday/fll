/**
 * FLL - Level 0
 *
 * Project: Capability
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the capability project.
 */
#ifndef _TEST__F_capability__process_get_by_id
#define _TEST__F_capability__process_get_by_id

/**
 * Test that function fails.
 *
 * @see f_capability_process_get_by_id()
 */
extern void test__f_capability_process_get_by_id__fails(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_capability_process_get_by_id()
 */
#ifndef _di_level_0_parameter_checking_
  extern void test__f_capability_process_get_by_id__parameter_checking(void **state);
#endif // _di_level_0_parameter_checking_

/**
 * Test that function works.
 *
 * @see f_capability_process_get_by_id()
 */
extern void test__f_capability_process_get_by_id__works(void **state);

#endif // _TEST__F_capability__process_get_by_id
